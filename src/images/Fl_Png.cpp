#include <config.h>
#if HAVE_PNG

#include <efltk/Fl_Image.h>
#include <efltk/Fl.h>

#include "../core/fl_internal.h"
static Fl_IO png_io;

#include <png.h>
#include <stdlib.h>

#define PNG_BYTES_TO_CHECK 4
bool setup_png_transformations(png_structp png_ptr, png_infop info_ptr, png_color_16 *transv,int &col_type, int &ckey, int &bitspp, int &w, int &h);

static void read_data_fn(png_structp /*png_ptr*/, png_bytep d, png_size_t length) {	
	png_io.read(d, length);
}

static void png_warning(png_structp png_ptr, png_const_charp message)
{
   char *name = "UNKNOWN (ERROR!)";
   if (png_ptr != NULL && png_ptr->error_ptr != NULL)
      name = (char *)png_ptr->error_ptr;
   Fl::warning("%s: libpng warning: %s", name, message);
}

static bool png_is_valid_file(const char *filename, FILE *fp)
{	
	uint8 type[PNG_BYTES_TO_CHECK];
	uint32 pos = ftell(fp);
	fread(type, PNG_BYTES_TO_CHECK, 1, fp);    
	fseek(fp, pos, SEEK_SET); //return position in file

    return (!png_sig_cmp((png_byte *)type, (png_size_t)0, PNG_BYTES_TO_CHECK));
}
       
static bool png_is_valid_mem(const uint8 *stream, uint32 size)
{	
    return size>=PNG_BYTES_TO_CHECK && (!png_sig_cmp((png_byte *)stream, (png_size_t)0, PNG_BYTES_TO_CHECK));
}

static bool png_create(uint8 *&data, Fl_PixelFormat &fmt, int &w, int &h)
{
	w=0, h=0;

	png_structp png_ptr = 0;
	png_infop info_ptr = 0, end_info_ptr = 0;
	png_bytepp rows = 0;	

	int ctype = 0;
	int pitch=0, bitspp=0;
	int ckey = -1;
	int i=0;
	uint32 Rmask=0, Gmask=0, Bmask=0, Amask=0;
	png_color_16 *transv=0;
	Fl_Colormap *palette=0;	

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png_ptr) goto error;

	info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr) goto error;
	
	end_info_ptr = png_create_info_struct(png_ptr);
	if(!end_info_ptr) goto error;

	if(setjmp (png_ptr->jmpbuf)) goto error;

	png_set_error_fn(png_ptr, (png_voidp)0, png_warning, png_warning);
	png_set_read_fn(png_ptr, (png_voidp)0, read_data_fn);

	png_read_info(png_ptr, info_ptr);

	if(!setup_png_transformations(png_ptr, info_ptr, transv, ctype, ckey, bitspp, w, h))
		goto error;

	if(ctype != PNG_COLOR_TYPE_PALETTE) {
		Rmask = 0x000000FF;
		Gmask = 0x0000FF00;
		Bmask = 0x00FF0000;
		if(info_ptr->channels == 4) {
			Amask = 0xFF000000;
			fmt.masktype = FL_MASK_ALPHA;
		} else
			Amask = 0;
	}  

	if(ckey != -1) {		
		// FIXME: Should these be truncated or shifted down?
		fmt.masktype = FL_MASK_COLORKEY;
		fmt.colorkey = fl_rgb((uint8)transv->red,
					          (uint8)transv->green,
						      (uint8)transv->blue);
	}
	
	fmt.realloc(bitspp,Rmask,Gmask,Bmask,Amask);
	pitch = Fl_Renderer::calc_pitch(fmt.bytespp, w);
	data = new uint8[h*pitch];

	rows = new png_bytep[h];
	for(i = 0; i < h; i++)
		rows[i] = data + i * pitch;

	png_read_image(png_ptr, rows);

	/* read rest of file, get additional chunks in info_ptr - REQUIRED */
	png_read_end(png_ptr, end_info_ptr);

	/* Load the palette, if any */
	palette = fmt.palette;
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
	}

	if(rows) free(rows);
	if(png_ptr) png_destroy_read_struct (&png_ptr, &info_ptr, &end_info_ptr);

	return true;

error:
    if(rows) free(rows);    
	if(png_ptr) png_destroy_read_struct (&png_ptr, &info_ptr, &end_info_ptr);
    return false;
}

bool setup_png_transformations(png_structp png_ptr, png_infop info_ptr, png_color_16 *transv, int &col_type, int &ckey, int &bitspp, int &width, int &height)
{
	int bit_depth, interlace_type, compression_type, filter_type;
	int channels;	

	/* Get the image info */
	png_get_IHDR(png_ptr, info_ptr,
				(ulong*)&width, (ulong*)&height,
                &bit_depth,
                &col_type,
                &interlace_type,
                &compression_type,
                &filter_type);	

	/* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
	* byte into separate bytes (useful for paletted and grayscale images).
	*/
	if (info_ptr->bit_depth < 8)
		png_set_packing(png_ptr);
	/* tell libpng to strip 16 bit/color files down to 8 bits/color */
	else if (info_ptr->bit_depth == 16)
		png_set_strip_16(png_ptr) ;	

	/* scale greyscale values to the range 0..255 */
	if(col_type==PNG_COLOR_TYPE_GRAY)
		png_set_expand(png_ptr);

	/* For images with a single "transparent color", set color key;
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
			ckey = -1; /* actual value will be set later */
	}

	/* If interlaced, handle that */
	if(interlace_type != PNG_INTERLACE_NONE) {
  		png_set_interlace_handling(png_ptr);
	}

	/* Update the info the reflect our transformations */
	png_read_update_info(png_ptr, info_ptr);

	png_get_IHDR(png_ptr, info_ptr,
		        (ulong*)&width, (ulong*)&height,
                &bit_depth,
                &col_type,
                &interlace_type,
                &compression_type,
                &filter_type);

	channels = png_get_channels(png_ptr, info_ptr);
	bitspp = bit_depth*channels;		

	if(channels < 1 || channels > 4) {
		return false;
	}

	return true;
}

static bool png_read_file(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h)
{
	png_io.init_io(fp, 0, 0);
	return png_create(data, format, w, h);
}

static bool png_read_mem(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h)
{
	png_io.init_io(0, stream, size);
	return png_create(data, format, w, h);
}

Fl_Image_IO png_reader =
{
	/* GENERAL: */
	"PNG", //name
	"png", //filename extension

	/* VALIDATE FUNCTIONS: */
	png_is_valid_file, //bool (*is_valid_file)(const char *filename, FILE *fp);
    png_is_valid_mem, //bool (*is_valid_mem)(uint8 *stream, uint32 size);
    NULL, //bool (*is_valid_xpm)(uint8 **stream);

	/* READ FUNCTIONS: */
	png_read_file, //bool (*read_file)(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);
    png_read_mem, //bool (*read_mem)(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);

	/* WRITE FUNCTIONS: */
	NULL, //bool (*write_mem)(uint8 *&stream, int &size, int quality, uint8 *data, Fl_PixelFormat &data_format, int w, int h);
	NULL //bool (*write_file)(FILE *fp, int quality, uint8 *data, Fl_PixelFormat &format, int w, int h);
};

#endif

