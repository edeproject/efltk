#include "fl_internal.h"
#include <efltk/Fl_Image.h>
#include <efltk/Fl.h>

static Fl_IO bmp_io;

#define BMP_BYTES_TO_CHECK 2

static bool bmp_is_valid_file(const char *filename, FILE *fp)
{	
	char type[BMP_BYTES_TO_CHECK];
	uint32 pos = ftell(fp);
	fread(type, BMP_BYTES_TO_CHECK, 1, fp);    
	fseek(fp, pos, SEEK_SET); //return position in file
	
	return !(strncmp(type, "BM", BMP_BYTES_TO_CHECK));
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

uint16 ReadLe16()
{
	// SWAP IF BIG ENDIAN!
	uint16 tmp;
	bmp_io.read(&tmp, sizeof(uint16));	
    return tmp;
}

uint32 ReadLe32()
{
	// SWAP IF BIG ENDIAN!
    uint32 tmp;
	bmp_io.read(&tmp, sizeof(uint32));
    return tmp;
}

static bool bmp_create(uint8 *&data, Fl_PixelFormat &fmt, int &w, int &h)
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

    /* The Win32 BMP file header (14 bytes) */
    char   magic[2];
    uint32 bfSize;
    uint16 bfReserved1;
    uint16 bfReserved2;
    uint32 bfOffBits;
	uint pitch;

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
	uint32 file_offset;

	file_offset = bmp_io.tell();
		
	bmp_io.read(magic, 2);
    if(strncmp(magic, "BM", 2)) {
		error_str = "File is not BMP";
        goto error;
	}

    // Header
    bfSize		  = ReadLe32();
    bfReserved1	= ReadLe16();
    bfReserved2	= ReadLe16();
    bfOffBits	  = ReadLe32();		

    /* Read the Win32 BITMAPINFOHEADER */
    biSize		 = ReadLe32();	

    if(biSize == 12) /* BITMAPCOREINFO */
    {
        biWidth		= (uint32)ReadLe16();
        biHeight	= (uint32)ReadLe16();
        biPlanes	= ReadLe16();
        biBitCount	= ReadLe16();
        biCompression	= BI_RGB;
        biSizeImage	= 0;
        biXPelsPerMeter	= 0;
        biYPelsPerMeter	= 0;
        biClrUsed	= 0;
        biClrImportant	= 0;

        //imgsize = size - offset;
    }
    else if(biSize == 40) /* BITMAPINFO */
    {
        biWidth		= ReadLe32();
        biHeight	= ReadLe32();
        biPlanes	= ReadLe16();
        biBitCount	= ReadLe16();
        biCompression	= ReadLe32();
        biSizeImage	= ReadLe32();
        biXPelsPerMeter	= ReadLe32();
        biYPelsPerMeter	= ReadLe32();
        biClrUsed	= ReadLe32();
        biClrImportant	= ReadLe32();
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
#if WORDS_BIGENDIAN
                Rmask = 0x000000FF;
                Gmask = 0x0000FF00;
                Bmask = 0x00FF0000;
                break;
#endif
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
            Rmask = ReadLe32();
            Gmask = ReadLe32();
            Bmask = ReadLe32();
            break;
        default:
					break;
        }
        break;
    default:
		error_str = "Compressed BMP files not supported";
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
                        //printf("Error reading from BMP\n");
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
                goto error;
			}
#if WORDS_BIGENDIAN
            /* Byte-swap the pixels if needed. Note that the 24bpp
             case has already been taken care of above. */
            switch(biBitCount) {
            case 15:
            case 16: {
                uint16 *pix = (uint16 *)bits;
                for(i = 0; i < surface->w; i++)
                    pix[i] = SDL_Swap16(pix[i]);
                break;
            }

            case 32: {
                uint32 *pix = (uint32 *)bits;
                for(i = 0; i < surface->w; i++)
                    pix[i] = SDL_Swap32(pix[i]);
                break;
            }
            }
#endif
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
	Fl::warning("Error reading BMP: %s", error_str?error_str:"Unknown");
    if(data) delete []data;
	data = 0;
    return false;
}

static bool bmp_read_file(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h)
{
	bmp_io.init_io(fp, 0, 0);
	return bmp_create(data, format, w, h);
}

static bool bmp_read_mem(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h)
{
	bmp_io.init_io(0, stream, size);
	return bmp_create(data, format, w, h);
}

Fl_Image_IO bmp_reader =
{
	/* GENERAL: */
	"BMP", //name
	"bmp", //filename extension

	/* VALIDATE FUNCTIONS: */
    bmp_is_valid_file, //bool (*is_valid_file)(const char *filename, FILE *fp);
    bmp_is_valid_mem, //bool (*is_valid_mem)(uint8 *stream, uint32 size);
    NULL, //bool (*is_valid_xpm)(uint8 **stream);

	/* READ FUNCTIONS: */
	bmp_read_file, //bool (*read_file)(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);
    bmp_read_mem, //bool (*read_mem)(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);

	/* WRITE FUNCTIONS: */
	NULL, //bool (*write_mem)(uint8 *&stream, int &size, int quality, uint8 *data, Fl_PixelFormat &data_format, int w, int h);
	NULL //bool (*write_file)(FILE *fp, int quality, uint8 *data, Fl_PixelFormat &format, int w, int h);
};

