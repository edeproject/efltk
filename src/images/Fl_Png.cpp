#include <config.h>
#if HAVE_PNG

#include <efltk/Fl_Image.h>
#include <efltk/Fl.h>

#include <png.h>
#include <stdlib.h>

#include "../core/fl_internal.h"
static Fl_IO png_io;
static int png_quality;

#define PNG_BYTES_TO_CHECK 4
bool setup_png_transformations(png_structp png_ptr, png_infop info_ptr, png_color_16 *transv,int &col_type, int &ckey, int &bitspp, int &w, int &h);

static void my_png_warning(png_structp png_ptr, png_const_charp message)
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

////////////////////////////////////////////
// PNG READ METHODS:

static void read_data_fn(png_structp /*png_ptr*/, png_bytep d, png_size_t length) {
    png_io.read(d, length);
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

    png_set_error_fn(png_ptr, (png_voidp)0, my_png_warning, my_png_warning);
    png_set_read_fn(png_ptr, (png_voidp)0, read_data_fn);

    png_read_info(png_ptr, info_ptr);

    if(!setup_png_transformations(png_ptr, info_ptr, transv, ctype, ckey, bitspp, w, h))
        goto error;

    if(ctype != PNG_COLOR_TYPE_PALETTE) {
#if !WORDS_BIGENDIAN
        Rmask = 0x000000FF;
        Gmask = 0x0000FF00;
        Bmask = 0x00FF0000;
        Amask = (info_ptr->channels == 4) ? 0xFF000000 : 0;
#else
        int s = (info_ptr->channels == 4) ? 0 : 8;
        Rmask = 0xFF000000 >> s;
        Gmask = 0x00FF0000 >> s;
        Bmask = 0x0000FF00 >> s;
        Amask = 0x000000FF >> s;
#endif
        if(info_ptr->channels == 4)
            fmt.masktype = FL_MASK_ALPHA;
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

////////////////////////////////////////////
// PNG WRITE METHODS:

static void write_data_fn(png_structp /*png_ptr*/, png_bytep d, png_size_t length) {
    png_io.write(d, length);
}

static void write_flush(png_structp) {
    // No need for flush...
    // since we use synchronous output method.
}

static bool setup_write_data(uint8 *data, int pitch, Fl_PixelFormat &fmt, int w, int h,
                             uint8 *&newdata, uint &newpitch, Fl_PixelFormat &newfmt)
{
    if(fmt.bitspp>8) {

        // It's not paletted image!
        // Make sure that data is in correct format.

        Fl_Rect rect(0,0,w,h);

        if(fmt.bitspp<32 && !fmt.Amask) {
#if WORDS_BIGENDIAN
            newfmt.realloc(24, 0xFF0000, 0x00FF00, 0x0000FF, 0);
#else
            newfmt.realloc(24, 0x0000FF, 0x00FF00, 0xFF0000, 0);
#endif
        } else {
#if WORDS_BIGENDIAN
            newfmt.realloc(32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#else
            newfmt.realloc(32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#endif
        }

        newpitch = Fl_Renderer::calc_pitch(newfmt.bytespp, w);
        newdata  = new uint8[h*newpitch];
        if(!Fl_Renderer::blit(data, &rect, &fmt, pitch, newdata, &rect, &newfmt, newpitch, 0)) {
            delete []newdata;
            newdata = 0;
            return false;
        }
        return true;
    }
    return false;
}

static bool png_write(uint8 *data, Fl_PixelFormat &fmt, int w, int h)
{
    png_bytepp rows = 0;
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette=0;
    uint pitch = Fl_Renderer::calc_pitch(fmt.bytespp, w);
	uint y; 
	int n;

    png_uint_32 width;
    png_uint_32 height;
    int bit_depth;
    int color_type;

    bool allocated = false;
    uint8 *wr_data = data;
    uint  wr_pitch = pitch;
    Fl_PixelFormat newfmt;
    Fl_PixelFormat *wr_fmt = &fmt;

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr) goto error;
    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr) goto error;

    png_set_error_fn(png_ptr, 0, 0, &my_png_warning);

    if(setjmp(png_ptr->jmpbuf)) goto error;

    int comp_level;
    switch(png_quality) {
    case FL_QUALITY_POOR:
        comp_level = 0; break;
    case FL_QUALITY_GOOD:
        comp_level = 6; break;
    case FL_QUALITY_BEST:
        comp_level = 9; break;
    default:
    case FL_QUALITY_NORMAL:
        comp_level = 3; break;
    }
    png_set_compression_level(png_ptr, comp_level);

    png_set_write_fn(png_ptr, (void *)0, write_data_fn, write_flush);

    // Be sure that data is in correct format!
    if(setup_write_data(data, pitch, fmt, w, h,
                        wr_data, wr_pitch, newfmt)) {
        if(!wr_data) {
            goto error;
        }
        allocated = true;
        wr_fmt = &newfmt;
    }

    /* Set the image information here.  Width and height are up to 2^31,
     * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
     * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
     * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
     * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
     * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
     * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
     */
    info_ptr->channels = wr_fmt->bytespp;
    png_set_IHDR(png_ptr, info_ptr, w, h,
                 (wr_fmt->bitspp==1) == 1 ? 1 : 8 /* per channel */,

                 wr_fmt->palette ? PNG_COLOR_TYPE_PALETTE :
                 (wr_fmt->Amask ? PNG_COLOR_TYPE_RGB_ALPHA : PNG_COLOR_TYPE_RGB),

                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE
                );

    info_ptr->sig_bit.red = 8;
    info_ptr->sig_bit.green = 8;
    info_ptr->sig_bit.blue = 8;
#if !WORDS_BIGENDIAN
    if(wr_fmt->bitspp==1) png_set_packswap(png_ptr);
#endif

    /* set the palette if there is one.  REQUIRED for indexed-color images */
    if(wr_fmt->palette) {
        palette = new png_color[wr_fmt->palette->ncolors];
        //int* trans = new int[fmt.palette->ncolors];
        //int num_trans = 0;
        for(n=0; n<wr_fmt->palette->ncolors; n++) {
            palette[n].red   = wr_fmt->palette->colors[n].r;
            palette[n].green = wr_fmt->palette->colors[n].g;
            palette[n].blue  = wr_fmt->palette->colors[n].b;
            /*if(fmt.Amask) {
                if(fmt.palette->colors[n].a > 0) {
                    num_trans = i+1;
                }
            }*/
        }
        /*if(num_trans) {
            copy_trans = new png_byte[num_trans];
            for (int i=0; i<num_trans; i++)
                copy_trans[i] = trans[i];
            png_set_tRNS(png_ptr, info_ptr, copy_trans, num_trans, 0);
        }
        delete [] trans;
        */
        png_set_PLTE(png_ptr, info_ptr, palette, wr_fmt->palette->ncolors);
    }

    if(wr_fmt->Amask) {
        info_ptr->sig_bit.alpha = 8;
    }

    /* Write the file header information.  REQUIRED */
    png_write_info(png_ptr, info_ptr);

    /* pack pixels into bytes */
    if(wr_fmt->bitspp!=1)
        png_set_packing(png_ptr);

    if(wr_fmt->bitspp == 32 && !wr_fmt->Amask)
        png_set_filler(png_ptr, 0,
#if WORDS_BIGENDIAN
                       PNG_FILLER_BEFORE
#else
                       PNG_FILLER_AFTER
#endif
                      );

    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 0, 0, 0);

    rows = new png_bytep[height];
    for(y=0; y<height; y++) {
        rows[y] = wr_data + y * wr_pitch;
    }
    png_write_image(png_ptr, rows);
    delete []rows;

    /* It is REQUIRED to call this to finish writing the rest of the file */
    png_write_end(png_ptr, info_ptr);

    if(palette) {
        delete []palette;
        palette=0;
    }

    /* clean up after the write, and free any memory allocated */
    png_destroy_write_struct(&png_ptr, &info_ptr);
    if(allocated && wr_data) delete []wr_data;

    return true;

error:
    if(png_ptr) png_destroy_write_struct(&png_ptr, &info_ptr);
    if(allocated && wr_data) delete []wr_data;
    return false;
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

static bool png_write_file(FILE *fp, int quality, uint8 *data, Fl_PixelFormat &format, int w, int h)
{
    png_io.init_io(fp, 0, 0);
    png_quality = quality;
    return png_write(data, format, w, h);
}

static bool png_write_mem(uint8 *&stream, int &size, int quality, uint8 *data, Fl_PixelFormat &format, int w, int h)
{
    png_io.init_io(0, stream, size);
    png_quality = quality;
    return png_write(data, format, w, h);
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
    png_write_mem, //bool (*write_mem)(uint8 *&stream, int &size, int quality, uint8 *data, Fl_PixelFormat &data_format, int w, int h);
    png_write_file //bool (*write_file)(FILE *fp, int quality, uint8 *data, Fl_PixelFormat &format, int w, int h);
};

#endif

