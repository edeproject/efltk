#include <efltk/Fl_Image.h>

#include <config.h>

#ifdef HAVE_PNG

#include <png.h>
#include <stdlib.h>

bool setup_png_transformations(png_structp png_ptr, png_infop info_ptr, png_color_16 *transv,int &col_type, int &ckey, int &bitspp, int &w, int &h);

static png_bytep cur_datas;
static void read_data_fn(png_structp /*png_ptr*/,png_bytep d,png_size_t length)
{
  memcpy(d, cur_datas, length);
  cur_datas += length;
}

static bool png_is_valid(void *stream, bool file)
{
    if(stream) {
        uint8 type[4];
        memcpy(type, stream, 4);
        if(png_sig_cmp((png_byte *)type, (png_size_t)0, 4)) {
            return false;
        }		
        return true;
    }
    return false;
}

void SwapData(uint8 *Data, uint SizeOfData, int bpp)
{
#ifdef __LITTLE_ENDIAN
  uint8 r,b;
	uint i;
	switch(bpp)
	{
  case 3:
      for(i = 0; i < SizeOfData; i += 3) {
          b=Data[i];
          r=Data[i+2];
          Data[i]=r;
          Data[i+2]=b;
      }
      break;
  case 4:
      for(i = 0; i < SizeOfData; i += 4) {
          b=Data[i];
          r=Data[i+2];
          Data[i]=r;
          Data[i+2]=b;
      }
			break;
	}
#endif
}

static Fl_Image *png_create(void *stream, int size, bool file)
{
  png_structp png_ptr = 0;
  png_infop info_ptr = 0, end_info = 0;
  png_bytepp rows = 0;
  int ctype = 0;
  int bitspp=0, w=0, h=0;
  int ckey = -1;
  int i=0;
  uint8 *str_ptr = (uint8 *)stream; //Needs to be set!
  uint32 Rmask=0, Gmask=0, Bmask=0, Amask=0;
  png_color_16 *transv=0;
  Fl_Image *ret=0;
  Fl_Colormap *palette=0;

  if(!str_ptr)
      return 0;

  uint8 type[8];
  memcpy(type, stream, 8);
  if(png_sig_cmp((uint8*)type, (png_size_t)0, 8))
      return 0;

  png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png_ptr)
      goto error;

	info_ptr = png_create_info_struct (png_ptr);
  if(!info_ptr)
      goto error;

	end_info = png_create_info_struct (png_ptr);
  if(!end_info)
      goto error;

  if(setjmp (png_ptr->jmpbuf))
      goto error;

  cur_datas = (png_bytep)str_ptr;
  png_set_read_fn(png_ptr, cur_datas, read_data_fn);

  png_read_info (png_ptr, info_ptr);

  if(!setup_png_transformations(png_ptr, info_ptr, transv, ctype, ckey, bitspp, w, h))
      goto error;

  if(ctype != PNG_COLOR_TYPE_PALETTE) {
      Rmask = 0x00FF0000;
      Gmask = 0x0000FF00;
      Bmask = 0x000000FF;
      Amask = (info_ptr->channels == 4) ? 0xFF000000 : 0;
  }
  ret = new Fl_Image(w, h, bitspp,0,Rmask,Gmask,Bmask,Amask,0);
  if(ckey != -1)
  {
      //printf("CKEY in png\n");
      /*if(ctype != PNG_COLOR_TYPE_PALETTE)
          // FIXME: Should these be truncated or shifted down?
          ckey = SDL_MapRGB(surface->format,
                            (Uint8)transv->red,
                            (Uint8)transv->green,
                            (Uint8)transv->blue);
                            SDL_SetColorKey(surface, SDL_SRCCOLORKEY, ckey);
                            */
  }

  rows = new png_bytep[h];
  for(i = 0; i < h; i++)
      rows[i] = ret->data() + i * ret->pitch();

	png_read_image(png_ptr, rows);

  /* read rest of file, get additional chunks in info_ptr - REQUIRED */
  //png_read_end(png_ptr, info_ptr);

  /* Load the palette, if any */
  palette = ret->format()->palette;
  if(palette) {
      if(ctype == PNG_COLOR_TYPE_GRAY)
      {
          palette->ncolors = 256;
          for(i = 0; i < 256; i++) {
              palette->colors[i].r = i;
              palette->colors[i].g = i;
              palette->colors[i].b = i;
          }
      } else if(info_ptr->num_palette > 0 )
      {
          palette->ncolors = info_ptr->num_palette;
          for( i=0; i<info_ptr->num_palette; ++i ) {
              palette->colors[i].b = info_ptr->palette[i].blue;
              palette->colors[i].g = info_ptr->palette[i].green;
              palette->colors[i].r = info_ptr->palette[i].red;
          }
      }
  } else if(ctype != PNG_COLOR_TYPE_PALETTE && (info_ptr->channels==3 || info_ptr->channels==4))
      SwapData(ret->data(), ret->pitch()*h, info_ptr->channels);

	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	
  if(rows) free(rows);
  
  return ret;

error:
		printf("error reading png\n");
    png_destroy_read_struct (&png_ptr, &info_ptr, &end_info);
    if(rows) free(rows);
    if(ret) delete ret;
    return 0;
}

bool setup_png_transformations(png_structp png_ptr, png_infop info_ptr, png_color_16 *transv, int &col_type, int &ckey, int &bitspp, int &w, int &h)
{
	png_uint_32 width, height;
  int bit_depth, interlace_type, compression_type, filter_type;
  int channels;

  /* Get the image info */
  png_get_IHDR (png_ptr, info_ptr,
                &width, &height,
                &bit_depth,
                &col_type,
                &interlace_type,
                &compression_type,
                &filter_type);

  /* tell libpng to strip 16 bit/color files down to 8 bits/color */
  png_set_strip_16(png_ptr) ;

  /* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
   * byte into separate bytes (useful for paletted and grayscale images).
   */
	png_set_packing(png_ptr);

  /* scale greyscale values to the range 0..255 */
  if(col_type==PNG_COLOR_TYPE_GRAY)
      png_set_expand(png_ptr);

  /* For images with a single "transparent colour", set colour key;
   if more than one index has transparency, use full alpha channel */
  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
      int num_trans;
      uint8 *trans;
      png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, &transv);
      if(col_type == PNG_COLOR_TYPE_PALETTE) {
          if(num_trans == 1) {
              /* exactly one transparent value: set colour key */
              ckey = trans[0];
          } else
              png_set_expand(png_ptr);
      } else
          ckey = 0; /* actual value will be set later */
  }

  /* If interlaced, handle that */
  if(interlace_type != PNG_INTERLACE_NONE) {
  	//printf("ITERLACED! not supported png\n");
  	png_set_interlace_handling(png_ptr);
  }

  /* Update the info the reflect our transformations */
  png_read_update_info(png_ptr, info_ptr);

  png_get_IHDR (png_ptr, info_ptr,
                &width, &height,
                &bit_depth,
                &col_type,
                &interlace_type,
                &compression_type,
                &filter_type);

  channels = png_get_channels(png_ptr, info_ptr);

  w = width;
  h = height;
  bitspp = bit_depth*channels;

  if(channels < 1 || channels > 4) {
    return false;
  }

  return true;
}

ImageReader png_reader =
{
    png_is_valid,
    0,
    png_create
};

#endif

