#include <efltk/Fl_Image.h>
#include <efltk/Fl.h>

#include <string.h>

static uint8 *read_ptr = 0;
static int BmpRead(void *buf, int len)
{
    memcpy(buf, read_ptr, len);
    read_ptr+=len;
    return len;
}

bool bmp_is_valid(void *stream, bool file)
{
    if(stream) {
        char type[2];
        memcpy(type, stream, 2);
        if(strncmp(type, "BM", 2)) {
            return false;
        }
        return true;
    }
    return false;
}

/////////////////////////////
// BMP IMAGE HANDLING (copy/paste from xmms) =)

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
	uint16 tmp;
	BmpRead(&tmp, sizeof(uint16));
    return tmp;
}

uint32 ReadLe32()
{
    uint32 tmp;
	BmpRead(&tmp, sizeof(uint32));
    return tmp;
}

Fl_Image *bmp_create(void *stream, bool file)
{	
	read_ptr=(uint8*)stream; 

	char *error_str=0;
    Fl_Image *surface=0;
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

	BmpRead(magic, 2);
    if(strncmp(magic, "BM", 2))
        goto error;

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
#if __BYTE_ORDER == __BIG_ENDIAN
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
    surface = new Fl_Image(biWidth, biHeight, biBitCount, 0, Rmask, Gmask, Bmask, 0, 0);

    /* Load the palette, if any */
    palette = surface->format()->palette;
    if(palette) {
        if(biClrUsed == 0) {
            biClrUsed = 1 << biBitCount;
        }
        if ( biSize == 12 ) {
            for ( i = 0; i < (int)biClrUsed; ++i )
            {
                BmpRead(&palette->colors[i].b, 1);
                BmpRead(&palette->colors[i].g, 1);
                BmpRead(&palette->colors[i].r, 1);
                palette->colors[i].a = 0;
            }
        } else {
            for ( i = 0; i < (int)biClrUsed; ++i ) {
                BmpRead(&palette->colors[i].b, 1);
                BmpRead(&palette->colors[i].g, 1);
                BmpRead(&palette->colors[i].r, 1);
                BmpRead(&palette->colors[i].a, 1);
            }
        }
        palette->ncolors = biClrUsed;
    }


	read_ptr = ((uint8 *)stream)+bfOffBits;	

    bits = (uint8 *)surface->data()+(surface->height()*surface->pitch());
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
        pad  = ((surface->pitch()%4) ?
                (4-(surface->pitch()%4)) : 0);
        break;
    }
    while ( bits > (uint8 *)surface->data() ) {
        bits -= surface->pitch();
        switch (ExpandBMP) {
        case 1:
        case 4: {
            uint8 pixel = 0;
            int   shift = (8-ExpandBMP);
            for ( i=0; i<surface->width(); ++i ) {
                if ( i%(8/ExpandBMP) == 0 ) {
                    if ( !BmpRead(&pixel, 1) ) {
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
            if(BmpRead(bits, surface->pitch()) != surface->pitch()) {
                goto error;
            }
#if __BYTEORDER == __BIG_ENDIAN
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
                BmpRead(&padbyte, 1);
            }
        }
    }

    return surface;

error:
	Fl::warning("Error reading BMP, reason: %s", error_str?error_str:"Unknown");
    if(surface) delete surface;
    return 0;
}

#if 0
static void read_1b_rgb(uint8 *input, int input_size, uint8 *output, uint32 w, uint32 h, RGBQuad palette[])
{
        uint8 *input_end = input + input_size;
        uint8 *output_ptr = output + ((h - 1) * w * 3);
	int padding = (4 - ((w + 7) / 8) % 4) & 3;
	unsigned int x, y, i;
	
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w && input < input_end;)
		{
			uint8 byte = *(input++);
			for (i = 0; i < 8 && x < w; i++, x++)
			{
				*output_ptr++ = palette[(byte >> (7 - i)) & 1].rgbRed;
				*output_ptr++ = palette[(byte >> (7 - i)) & 1].rgbGreen;
				*output_ptr++ = palette[(byte >> (7 - i)) & 1].rgbBlue;
			}
		}
		input += padding;
		output_ptr -= w * 6;        /* Back up two scanlines */
	}
}

static void read_4b_rle(uint8 *input, uint32 compr_size, uint8 *output, uint32 w, uint32 h, RGBQuad palette[])
{
	bool at_end = 0;
	int j;
	uint16 x = 0, y = 0;
	uint8 *output_ptr = output + ((h - 1) * w * 3);
	uint8 *input_ptr = input;
	uint8 *input_end = input + compr_size;
	uint8 *output_end = output + w * h * 3;
	uint8 col, col1 = 0, col2 = 0, num, byte;


	while (!at_end && input_ptr < input_end)
	{
		byte = *(input_ptr++);
		if (byte)
		{
			/* "Encoded mode" */
			num = byte;
			byte = *(input_ptr++);
			col1 = byte & 0xF;
			col2 = (byte >> 4);
			for (j = 0; j < num; j++)
			{
				col = (j & 1) ? col1 : col2;

				if (x >= w)
					break;

				*output_ptr++ = palette[col].rgbRed;
				*output_ptr++ = palette[col].rgbGreen;
				*output_ptr++ = palette[col].rgbBlue;
				x++;
				if (output_ptr > output_end)
					output_ptr = output_end;
			}
		}
		else
		{
			byte = *(input_ptr++);
			switch (byte)
			{
				case 0:
					/* End of line */
					x = 0;
					y++;
					output_ptr = output + ((h - y - 1) * w * 3) + (x * 3);
					if (output_ptr > output_end)
						output_ptr = output_end;
					break;
				case 1:
					/* End of bitmap */
					at_end = 1;
					break;
				case 2:
					/* Delta */
					x += *(input_ptr++);
					y += *(input_ptr++);
					output_ptr = output + ((h - y - 1) * w * 3) + (x * 3);
					if (output_ptr > output_end)
						output_ptr = output_end;
					break;
				default:
					/*
					 * "Absolute mode"
					 *  non RLE encoded
					 */
					num = byte;
					for (j = 0; j < num; j++)
					{
						if ((j & 1) == 0)
						{
							byte = *(input_ptr++);
							col1 = byte & 0xF;
							col2 = (byte >> 4);
						}
						col = (j & 1) ? col1 : col2;

						if (x >= w)
						{
							input_ptr += (num - j) / 2;
							break;
						}

						*output_ptr++ = palette[col].rgbRed;
						*output_ptr++ = palette[col].rgbGreen;
						*output_ptr++ = palette[col].rgbBlue;

						x++;

						if (output_ptr > output_end)
							output_ptr = output_end;
					}

					/* Skip padding */
					if ((num & 3) == 1 || (num & 3) == 2)
						input_ptr++;
					break;
			}
		}
	}
}

static void read_4b_rgb(uint8 *input, int input_size, uint8 *output, uint32 w, uint32 h, RGBQuad palette[])
{
	uint8 *input_end = input + input_size;
	uint8 *output_ptr = output + ((h - 1) * w * 3);
	int padding = ((((w + 7) / 8) * 8) - w) / 2;
	uint x, y;
	
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w && input < input_end; x+=2)
		{
			uint8 byte = *(input++);

			*output_ptr++ = palette[byte >> 4].rgbRed;
			*output_ptr++ = palette[byte >> 4].rgbGreen;
			*output_ptr++ = palette[byte >> 4].rgbBlue;

			if (x + 1 == w)
				break;
			
			*output_ptr++ = palette[byte & 0xF].rgbRed;
			*output_ptr++ = palette[byte & 0xF].rgbGreen;
			*output_ptr++ = palette[byte & 0xF].rgbBlue;
		}
		input += padding;
		output_ptr -= w * 6;        /* Back up two scanlines */
	}
}


static void read_8b_rle(uint8 *input, uint32 compr_size, uint8 *output, uint32 w, uint32 h, RGBQuad palette[])
{
	bool at_end = 0;
	int j;
	uint16 x = 0, y = 0;
	uint8 *output_ptr = output + ((h - 1) * w * 3);
	uint8 *input_ptr = input;
	uint8 *input_end = input + compr_size;
	uint8 *output_end = output + w * h * 3;
	uint8 num, byte;

	while (!at_end && input_ptr < input_end)
	{
		byte = *(input_ptr++);
		if (byte)
		{
			/* "Encoded mode" */
			num = byte;
			byte = *(input_ptr++);
			for (j = 0; j < num; j++)
			{
				if (x >= w)
					break;
				
				*output_ptr++ = palette[byte].rgbRed;
				*output_ptr++ = palette[byte].rgbGreen;
				*output_ptr++ = palette[byte].rgbBlue;
				x++;
				if (output_ptr > output_end)
					output_ptr = output_end;

			}

		}
		else
		{
			byte = *(input_ptr++);
			switch (byte)
			{
				/* End of line */
				case 0:
					x = 0;
					y++;
					output_ptr = output + ((h - y - 1) * w * 3) + (x * 3);
					if (output_ptr > output_end)
						output_ptr = output_end;
					break;
				case 1:
					/* End of bitmap */
					at_end = 1;
					break;
				case 2:
					/* Delta */
					x += *(input_ptr++);
					y += *(input_ptr++);
					output_ptr = output + ((h - y - 1) * w * 3) + (x * 3);
					if (output_ptr > output_end)
						output_ptr = output_end;
					break;
				default:
					/*
					 * "Absolute mode"
					 *  non RLE encoded
					 */
					num = byte;
					for (j = 0; j < num; j++)
					{
						byte = *(input_ptr++);
						
						if (x >= w)
						{
							input_ptr += num - j;
							break;
						}
						
						*output_ptr++ = palette[byte].rgbRed;
						*output_ptr++ = palette[byte].rgbGreen;
						*output_ptr++ = palette[byte].rgbBlue;
						x++;
						
						if (output_ptr > output_end)
							output_ptr = output_end;

					}

					/* Skip padding */
					if (num & 1)
						input_ptr++;
					break;
			}
		}
	}
}

static void read_8b_rgb(uint8 *input, int input_size, uint8 *output, uint32 w, uint32 h, RGBQuad palette[])
{
	uint8 *input_end = input + input_size;
	uint8 *output_ptr = output + ((h - 1) * w * 3);
	int padding = (((w + 3) / 4) * 4) - w;
	uint8 byte;
	uint x, y;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w && input < input_end; x++)
		{
			byte = *(input++);
			*output_ptr++ = palette[byte].rgbRed;
			*output_ptr++ = palette[byte].rgbGreen;
			*output_ptr++ = palette[byte].rgbBlue;
		}
    output_ptr -= w * 6;
		input += padding;
	}
}


static void read_16b_rgb(uint8 *input, int input_size, uint8 *output, uint32 w, uint32 h)
{
	uint8 *input_end = input + input_size;
	uint8 *output_ptr = output + ((h - 1) * w * 3);
	int padding = (4 - ((w * 2) % 4)) & 3;
	uint16 rgb16;
	uint x, y;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w && input < (input_end - 1); x++)
		{
			rgb16 = ((*(input + 1)) << 8) | (*input);
			input += 2;
			*output_ptr++ = (rgb16 & 0x7C00) >> 7;
			*output_ptr++ = (rgb16 & 0x03E0) >> 2;				
			*output_ptr++ = (rgb16 & 0x001F) << 3;
		}			
		output_ptr -= w * 6; /* Back up two scanlines */
		input += padding;
	}
}

static void read_24b_rgb(uint8 *input, int input_size, uint8 *output, uint32 w, uint32 h)
{
	uint8 *input_end = input + input_size;
	uint8 *output_ptr = output + ((h - 1) * w * 3);
	int padding = (4 - ((w * 3) % 4)) & 3;
	//uint8 r, g, b;
	uint x, y;
	
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w && input < (input_end - 2); x++)
    {
         *output_ptr++ = *(input++);
         *output_ptr++ = *(input++);
         *output_ptr++ = *(input++);
    }
		output_ptr -= w * 6;
		input += padding;
	}
}

#endif

ImageReader bmp_reader =
{
    bmp_is_valid,
    0, //is_valid2
    bmp_create
};

