#include "fl_internal.h"

#include <efltk/Fl_Image.h>
#include <efltk/Fl.h>

#define BMP_BYTES_TO_CHECK 2

static bool bmp_is_valid_file(const char *filename)
{	
#ifndef VALIDATE_IMAGE_CONTENT
	int len=strlen(filename)-3;
	if(len<1) return false;
	return !strncasecmp(filename+len, "BMP", 3);
#else
	FILE *fp = fopen(filename, "rb");
	if(fp) {
		char type[BMP_BYTES_TO_CHECK];
		uint32 pos = ftell(fp);
		fread(type, BMP_BYTES_TO_CHECK, 1, fp);    
		fclose(fp);
		return !(strncmp(type, "BM", BMP_BYTES_TO_CHECK));
	}
	return false;
#endif
}
       
static bool bmp_is_valid_mem(const uint8 *stream, uint32 size)
{	
    return size>=BMP_BYTES_TO_CHECK && !(strncmp((const char*)stream, "BM", BMP_BYTES_TO_CHECK));
}

// BMP Compression specifications
#ifndef BI_RGB
#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L
#endif

typedef struct tagRGBQUAD2
{
	uint8 rgbBlue;
	uint8 rgbGreen;
	uint8 rgbRed;
	uint8 rgbReserved;
}
RGBQuad;

uint16 ReadLe16(Fl_IO &bmp_io)
{
    uint16 tmp;
    bmp_io.read(&tmp, sizeof(uint16));
    return fl_swap_le16(tmp);
}

uint32 ReadLe32(Fl_IO &bmp_io)
{
    uint32 tmp;
    bmp_io.read(&tmp, sizeof(uint32));
    return fl_swap_le32(tmp);
}

#define UNUSED(x) (void)x;

static bool bmp_create(Fl_IO &bmp_io, uint8 *&data, Fl_PixelFormat &fmt, int &w, int &h)
{
    char *error_str=0;
    Fl_Colormap *palette=0;
    int bmpPitch;
    int i, pad;
    uint32 Rmask;
    uint32 Gmask;
    uint32 Bmask;
    uint8 *bits;
    int ExpandBMP;

    uint pitch;
	uint32 file_offset;

    /* The Win32 BMP file header (14 bytes) */
    char   magic[2];
    uint32 bfSize;
    uint16 bfReserved1;
    uint16 bfReserved2;
    uint32 bfOffBits;

    /* The Win32 BITMAPINFOHEADER struct (40 bytes) */
    uint32 biSize;
    int32 biWidth;
    int32 biHeight;
    uint16 biPlanes;
    uint16 biBitCount;
    uint32 biCompression;
    uint32 biSizeImage;
    int32 biXPelsPerMeter;
    int32 biYPelsPerMeter;
    uint32 biClrUsed;
    uint32 biClrImportant;
    
    file_offset = bmp_io.tell();

    bmp_io.read(magic, 2);
    if(strncmp(magic, "BM", 2)) {
        error_str = "BMP: File is not BMP";
        goto error;
    }

    // Header
    bfSize	= ReadLe32(bmp_io);
    bfReserved1 = ReadLe16(bmp_io);
    bfReserved2	= ReadLe16(bmp_io);
    bfOffBits	= ReadLe32(bmp_io);

    /* Read the Win32 BITMAPINFOHEADER */
    biSize = ReadLe32(bmp_io);

    if(biSize == 12) /* BITMAPCOREINFO */
    {
        biWidth		= (uint32)ReadLe16(bmp_io);
        biHeight	= (uint32)ReadLe16(bmp_io);
        biPlanes	= ReadLe16(bmp_io);
        biBitCount	= ReadLe16(bmp_io);
        biCompression	= BI_RGB;
        biSizeImage	= 0;
        biXPelsPerMeter	= 0;
        biYPelsPerMeter	= 0;
        biClrImportant	= 0;
        biClrUsed	= 0;

        //imgsize = size - offset;
    }
    else if(biSize == 40) /* BITMAPINFO */
    {
        biWidth		= ReadLe32(bmp_io);
        biHeight	= ReadLe32(bmp_io);
        biPlanes	= ReadLe16(bmp_io);
        biBitCount	= ReadLe16(bmp_io);
        biCompression= ReadLe32(bmp_io);
        biSizeImage	= ReadLe32(bmp_io);
        biXPelsPerMeter	= ReadLe32(bmp_io);
        biYPelsPerMeter	= ReadLe32(bmp_io);
        biClrUsed		= ReadLe32(bmp_io);
        biClrImportant	= ReadLe32(bmp_io);
    }
    else
        goto error;

    /* Expand 1 and 4 bit bitmaps to 8 bits per pixel */
    switch (biBitCount) {
    case 1:
    case 4:
        ExpandBMP = biBitCount;
        biBitCount = 8;
        break;
    default:
        ExpandBMP = 0;
        break;
    }

    /* We don't support any BMP compression right now */
    Rmask = Gmask = Bmask = 0;
    switch (biCompression) {
    case BI_RGB:
        /* If there are no masks, use the defaults */
        if ( bfOffBits == (14+biSize) ) {
            /* Default values for the BMP format */
            switch (biBitCount) {
            case 15:
            case 16:
                Rmask = 0x7C00;
                Gmask = 0x03E0;
                Bmask = 0x001F;
                break;
            case 24:
                if(Fl_Renderer::big_endian()) {
                    Rmask = 0x000000FF;
                    Gmask = 0x0000FF00;
                    Bmask = 0x00FF0000;
                    break;
                }
            case 32:
                Rmask = 0x00FF0000;
                Gmask = 0x0000FF00;
                Bmask = 0x000000FF;
                break;
            default:
                break;
            }
            break;
        }
        /* Fall through -- read the RGB masks */

    case BI_BITFIELDS:
        switch (biBitCount) {
        case 15:
        case 16:
        case 32:
            Rmask = ReadLe32(bmp_io);
            Gmask = ReadLe32(bmp_io);
            Bmask = ReadLe32(bmp_io);
            break;
        default:
            break;
        }
        break;
    default:
        error_str = "BMP: Compressed BMP files not supported";
        goto error;
    }

    /* Create a compatible surface, note that the colors are RGB ordered */
    w = biWidth;
    h = biHeight;
    fmt.realloc(biBitCount, Rmask, Gmask, Bmask, 0);
    pitch = Fl_Renderer::calc_pitch(fmt.bytespp, w);
    data = new uint8[h*pitch];

    /* Load the palette, if any */
    palette = fmt.palette;
    if(palette) {
        if(biClrUsed == 0) {
            biClrUsed = 1 << biBitCount;
        }
        if ( biSize == 12 ) {
            for ( i = 0; i < (int)biClrUsed; ++i )
            {
                bmp_io.read(&palette->colors[i].b, 1);
                bmp_io.read(&palette->colors[i].g, 1);
                bmp_io.read(&palette->colors[i].r, 1);
                palette->colors[i].a = 0;
            }
        } else {
            for ( i = 0; i < (int)biClrUsed; ++i ) {
                bmp_io.read(&palette->colors[i].b, 1);
                bmp_io.read(&palette->colors[i].g, 1);
                bmp_io.read(&palette->colors[i].r, 1);
                bmp_io.read(&palette->colors[i].a, 1);
            }
        }
        palette->ncolors = biClrUsed;
    }

    bmp_io.seek(file_offset+bfOffBits);

    bits = (uint8 *)data+(h*pitch);
    switch (ExpandBMP) {
    case 1:
        bmpPitch = (biWidth + 7) >> 3;
        pad  = (((bmpPitch)%4) ? (4-((bmpPitch)%4)) : 0);
        break;
    case 4:
        bmpPitch = (biWidth + 1) >> 1;
        pad  = (((bmpPitch)%4) ? (4-((bmpPitch)%4)) : 0);
        break;
    default:
        pad  = ((pitch%4) ? (4-(pitch%4)) : 0);
        break;
    }
    while ( bits > (uint8 *)data ) {
        bits -= pitch;
        switch (ExpandBMP) {
        case 1:
        case 4: {
            uint8 pixel = 0;
            int   shift = (8-ExpandBMP);
            for ( i=0; i<w; ++i ) {
                if ( i%(8/ExpandBMP) == 0 ) {
                    if ( !bmp_io.read(&pixel, 1) ) {
                        error_str = "BMP: Error reading file";
                        goto error;
                    }
                }
                *(bits+i) = (pixel>>shift);
                pixel <<= ExpandBMP;
            }
        }
        break;

        default:
            if(bmp_io.read(bits, pitch) != pitch) {
                error_str = "BMP: Error reading file";
                goto error;
            }
            if(Fl_Renderer::big_endian()) {
                /* Byte-swap the pixels if needed. Note that the 24bpp
                 case has already been taken care of above. */
                switch(biBitCount) {
                case 15:
                case 16: {
                    uint16 *pix = (uint16 *)bits;
                    for(i = 0; i < w; i++)
                        pix[i] = fl_swap_16(pix[i]);
                    break;
                }

                case 32: {
                    uint32 *pix = (uint32 *)bits;
                    for(i = 0; i < w; i++)
                        pix[i] = fl_swap_32(pix[i]);
                    break;
                }
                }
            }
            break;
        }
        /* Skip padding bytes, ugh */
        if ( pad ) {
            uint8 padbyte;
            for ( i=0; i<pad; ++i ) {
                bmp_io.read(&padbyte, 1);
            }
        }
    }

    return true;

error:
    if(data) delete []data;
    data = 0;
    fputs(error_str ? error_str : "BMP: Unknown error!", stderr);
}

static bool bmp_read_file(const char *filename, int quality, uint8 *&data, Fl_PixelFormat &data_format, int &w, int &h)
{
	FILE *fp = fopen(filename, "rb");
	if(!fp) return false;

    Fl_IO bmp_io;
    bmp_io.init_io(fp, 0, 0);
    bool ret = bmp_create(bmp_io, data, data_format, w, h);

	fclose(fp);
	return ret;
}

static bool bmp_read_mem(const uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &data_format, int &w, int &h)
{
    Fl_IO bmp_io;
    bmp_io.init_io(0, (uint8*)stream, size);
    return bmp_create(bmp_io, data, data_format, w, h);
}

Fl_Image_IO bmp_reader =
{
    /* GENERAL: */
    "BMP", //name
    "bmp", //filename extension

    /* VALIDATE FUNCTIONS: */
    bmp_is_valid_file, //bool (*is_valid_file)(const char *filename, FILE *fp);
    bmp_is_valid_mem, //bool (*is_valid_mem)(uint8 *stream, uint32 size);

    /* READ FUNCTIONS: */
    bmp_read_file, //bool (*read_file)(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);
    bmp_read_mem, //bool (*read_mem)(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);

    /* WRITE FUNCTIONS: */
    NULL, //bool (*write_mem)(uint8 *&stream, int &size, int quality, uint8 *data, Fl_PixelFormat &data_format, int w, int h);
    NULL //bool (*write_file)(FILE *fp, int quality, uint8 *data, Fl_PixelFormat &format, int w, int h);
};
