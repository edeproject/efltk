/* This is a GIF image file loading framework */
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl.h>

#include <stdlib.h>

/* Code from here to end of file has been adapted from XPaint:   */
/* +-------------------------------------------------------------------+ */
/* | Copyright 1990, 1991, 1993 David Koblas.			               | */
/* | Copyright 1996 Torsten Martinsen.				                   | */
/* |   Permission to use, copy, modify, and distribute this software   | */
/* |   and its documentation for any purpose and without fee is hereby | */
/* |   granted, provided that the above copyright notice appear in all | */
/* |   copies and that both that copyright notice and this permission  | */
/* |   notice appear in supporting documentation.  This software is    | */
/* |   provided "as is" without express or implied warranty.	       | */
/* +-------------------------------------------------------------------+ */

/* and SDL: */
/*    Copyright (C) 1999, 2000, 2001  Sam Lantinga */
/*    This library is free software; you can redistribute it and/or		*/
/*    modify it under the terms of the GNU Library General Public		*/
/*    License as published by the Free Software Foundation; either		*/
/*    version 2 of the License, or (at your option) any later version.	*/

/* and EFLTK: */
/*    Copyright (C) 1999, 2000, 2001 Mikko Lahteenmaki */
/*    This library is free software; you can redistribute it and/or		*/
/*    modify it under the terms of the GNU Library General Public		*/
/*    License as published by the Free Software Foundation; either		*/
/*    version 2 of the License, or (at your option) any later version.	*/

#include "fl_internal.h"

#define RWSetMsg fl_throw

#define SetCmap(i, R, G, B) do { \
    fmt.palette->colors[i].r = R; \
    fmt.palette->colors[i].g = G; \
    fmt.palette->colors[i].b = B; \
} while (0)
/* * * * * */

#define	MAXCOLORMAPSIZE	256

#define	TRUE	1
#define	FALSE	0

#define CM_RED		0
#define CM_GREEN	1
#define CM_BLUE		2

#define	MAX_LWZ_BITS		12

#define INTERLACE		0x40
#define LOCALCOLORMAP	0x80
#define BitSet(byte, bit)	(((byte) & (bit)) == (bit))

#define LM_to_uint(a,b)			(((b)<<8)|(a))

static struct {
    int transparent;
    int delayTime;
    int inputFlag;
    int disposal;
} Gif89;

static struct {
    unsigned int Width;
    unsigned int Height;
    unsigned char ColorMap[3][MAXCOLORMAPSIZE];
    unsigned int BitPixel;
    unsigned int ColorResolution;
    unsigned int Background;
    unsigned int AspectRatio;
    int GrayScale2;
} GifScreen;

static int ReadColorMap(Fl_IO &gif_io, int number, unsigned char buffer[3][MAXCOLORMAPSIZE], int *flag);
static int DoExtension(Fl_IO &gif_io, int label);
static int GetDataBlock(Fl_IO &gif_io, unsigned char *buf);
static int GetCode(Fl_IO &gif_io, int code_size, int flag);
static int LWZReadByte(Fl_IO &gif_io, int flag, int input_code_size);
static uint8 *ReadImage(Fl_IO &gif_io, int len, int height, int,
			unsigned char cmap[3][MAXCOLORMAPSIZE],
			int gray, int interlace, int ignore, Fl_PixelFormat &fmt, int &im_w, int &im_h);

/* See if an image is contained in a data source */
#define GIF_BYTES_TO_CHECK 6

static bool gif_is_valid_file(const char *filename, FILE *fp)
{	
	char type[GIF_BYTES_TO_CHECK];
	uint32 pos = ftell(fp);
	fread(type, GIF_BYTES_TO_CHECK, 1, fp);    
	fseek(fp, pos, SEEK_SET); //return position in file
	
	return (strncmp(type, "GIF", 3) == 0) && 
			((memcmp(type + 3, "87a", 3) == 0) ||
			(memcmp(type + 3, "89a", 3) == 0));
}
       
static bool gif_is_valid_mem(const uint8 *stream, uint32 size)
{	
    return size>=GIF_BYTES_TO_CHECK && (strncmp((const char*)stream, "GIF", 3) == 0) && 
										((memcmp(stream + 3, "87a", 3) == 0) ||
										(memcmp(stream + 3, "89a", 3) == 0));
}

static bool gif_create(Fl_IO &gif_io, uint8 *&data, Fl_PixelFormat &fmt, int &w, int &h)
{
    data = 0;
    unsigned char buf[16];
    unsigned char c;
    unsigned char localColorMap[3][MAXCOLORMAPSIZE];
    int grayScale;
    int useGlobalColormap;
    int bitPixel;
    int imageCount = 0;
    char version[4];
    int imageNumber = 1;
	
    if(!gif_io.read(buf, 6)) {
        RWSetMsg("GIF: Can't read magic number");
        goto done;
    }
    if (strncmp((char *) buf, "GIF", 3) != 0) {
        RWSetMsg("GIF: Not a GIF file");
        goto done;
    }
    strncpy(version, (char *) buf + 3, 3);
    version[3] = '\0';
	
    if ((strcmp(version, "87a") != 0) && (strcmp(version, "89a") != 0)) {
        RWSetMsg("GIF: Bad version number, not '87a' or '89a'");
        goto done;
    }
    Gif89.transparent = -1;
    Gif89.delayTime = -1;
    Gif89.inputFlag = -1;
    Gif89.disposal = 0;

    if (!gif_io.read(buf, 7)) {
        RWSetMsg("GIF: Failed to read screen descriptor");
        goto done;
    }
    GifScreen.Width = LM_to_uint(buf[0], buf[1]);
    GifScreen.Height = LM_to_uint(buf[2], buf[3]);
    GifScreen.BitPixel = 2 << (buf[4] & 0x07);
    GifScreen.ColorResolution = (((buf[4] & 0x70) >> 3) + 1);
    GifScreen.Background = buf[5];
    GifScreen.AspectRatio = buf[6];

    if (BitSet(buf[4], LOCALCOLORMAP)) {	/* Global Colormap */
        if (ReadColorMap(gif_io, GifScreen.BitPixel, GifScreen.ColorMap,
                         &GifScreen.GrayScale2)) {
            RWSetMsg("GIF: Error reading global colormap");
            goto done;
        }
    }
    do {
        if (!gif_io.read(&c, 1)) {
            RWSetMsg("GIF: EOF / read error on image data");
            goto done;
        }
        if (c == ';') {		/* GIF terminator */
            if (imageCount < imageNumber) {
                RWSetMsg("GIF: Too few image(s) found in file");
                goto done;
            }
        }
        if (c == '!') {		/* Extension */
            if (!gif_io.read(&c, 1)) {
                RWSetMsg("GIF: EOF / read error on extention function code");
                goto done;
            }
            DoExtension(gif_io, c);
            continue;
        }
        if (c != ',') {		/* Not a valid start character */
            continue;
        }
        ++imageCount;

        if (!gif_io.read(buf, 9)) {
            RWSetMsg("GIF: Couldn't read left/top/width/height");
            goto done;
        }
        useGlobalColormap = !BitSet(buf[8], LOCALCOLORMAP);

        bitPixel = 1 << ((buf[8] & 0x07) + 1);

        if (!useGlobalColormap) {
            if (ReadColorMap(gif_io, bitPixel, localColorMap, &grayScale)) {
                RWSetMsg("GIF: Error reading local colormap");
                goto done;
            }
            data = ReadImage(gif_io, LM_to_uint(buf[4], buf[5]),
                             LM_to_uint(buf[6], buf[7]),
                             bitPixel, localColorMap, grayScale,
                             BitSet(buf[8], INTERLACE),
                             imageCount != imageNumber, fmt, w, h);
        } else {
            data = ReadImage(gif_io, LM_to_uint(buf[4], buf[5]),
                             LM_to_uint(buf[6], buf[7]),
                             GifScreen.BitPixel, GifScreen.ColorMap,
                             GifScreen.GrayScale2, BitSet(buf[8], INTERLACE),
                             imageCount != imageNumber, fmt, w, h);
        }
    } while(!data);

    if ( Gif89.transparent >= 0 ) {
        //Try to get some gifs transparent working, thus some doesnt then...
        fmt.colorkey = Gif89.transparent==-1?0:Gif89.transparent;
        fmt.masktype = FL_MASK_PIXELKEY;
    }

done:
    return (data!=0);
}

static int ReadColorMap(Fl_IO &gif_io, int number, unsigned char buffer[3][MAXCOLORMAPSIZE], int *gray)
{
    int i;
    unsigned char rgb[3];
    int flag;

    flag = TRUE;

    for (i = 0; i < number; ++i) {
        if (!gif_io.read(rgb, sizeof(rgb))) {
            RWSetMsg("GIF: Bad colormap");
            return 1;
        }
        buffer[CM_RED][i] = rgb[0];
        buffer[CM_GREEN][i] = rgb[1];
        buffer[CM_BLUE][i] = rgb[2];
        flag &= (rgb[0] == rgb[1] && rgb[1] == rgb[2]);
    }

#if 0
    if (flag)
        *gray = (number == 2) ? PBM_TYPE : PGM_TYPE;
    else
        *gray = PPM_TYPE;
#else
    *gray = 0;
#endif

    return FALSE;
}

static int DoExtension(Fl_IO &gif_io, int label)
{
    static unsigned char buf[256];
    char *str;

    switch (label) {
    case 0x01:			/* Plain Text Extension */
        str = "Plain Text Extension";
        break;
    case 0xff:			/* Application Extension */
        str = "Application Extension";
        break;
    case 0xfe:			/* Comment Extension */
        str = "Comment Extension";
        while (GetDataBlock(gif_io, (unsigned char *) buf) != 0);
        return FALSE;
    case 0xf9:			/* Graphic Control Extension */
        str = "Graphic Control Extension";
        (void) GetDataBlock(gif_io, (unsigned char *) buf);
        Gif89.disposal = (buf[0] >> 2) & 0x7;
        Gif89.inputFlag = (buf[0] >> 1) & 0x1;
        Gif89.delayTime = LM_to_uint(buf[1], buf[2]);
        if ((buf[0] & 0x1) != 0)
            Gif89.transparent = buf[3];

        while (GetDataBlock(gif_io, (unsigned char *) buf) != 0);
        return FALSE;
    default:
        str = (char *)buf;
        sprintf(str, "UNKNOWN (0x%02x)", label);
        break;
    }

    while (GetDataBlock(gif_io, (unsigned char *) buf) != 0);

    return FALSE;
}

static int ZeroDataBlock = FALSE;

static int GetDataBlock(Fl_IO &gif_io, unsigned char *buf)
{
    unsigned char count;

    if (!gif_io.read(&count, 1)) {
        /* pm_message("error in getting DataBlock size" ); */
        return -1;
    }
    ZeroDataBlock = count == 0;

    if ((count != 0) && (!gif_io.read(buf, count))) {
        /* pm_message("error in reading DataBlock" ); */
        return -1;
    }
    return count;
}

static int GetCode(Fl_IO &gif_io, int code_size, int flag)
{
    static unsigned char buf[280];
    static int curbit, lastbit, done, last_byte;
    int i, j, ret;
    unsigned char count;

    if (flag) {
        curbit = 0;
        lastbit = 0;
        done = FALSE;
        return 0;
    }
    if ((curbit + code_size) >= lastbit) {
        if (done) {
            if (curbit >= lastbit)
                RWSetMsg("GIF: Ran off the end of my bits");
            return -1;
        }
        buf[0] = buf[last_byte - 2];
        buf[1] = buf[last_byte - 1];

        if ((count = GetDataBlock(gif_io, &buf[2])) == 0)
            done = TRUE;

        last_byte = 2 + count;
        curbit = (curbit - lastbit) + 16;
        lastbit = (2 + count) * 8;
    }
    ret = 0;
    for (i = curbit, j = 0; j < code_size; ++i, ++j)
        ret |= ((buf[i / 8] & (1 << (i % 8))) != 0) << j;

    curbit += code_size;

    return ret;
}

static int LWZReadByte(Fl_IO &gif_io, int flag, int input_code_size)
{
    static int fresh = FALSE;
    int code, incode;
    static int code_size, set_code_size;
    static int max_code, max_code_size;
    static int firstcode, oldcode;
    static int clear_code, end_code;
    static int table[2][(1 << MAX_LWZ_BITS)];
    static int stack[(1 << (MAX_LWZ_BITS)) * 2], *sp;
    register int i;

    if (flag) {
        set_code_size = input_code_size;
        code_size = set_code_size + 1;
        clear_code = 1 << set_code_size;
        end_code = clear_code + 1;
        max_code_size = 2 * clear_code;
        max_code = clear_code + 2;

	GetCode(gif_io, 0, TRUE);

        fresh = TRUE;

        for (i = 0; i < clear_code; ++i) {
            table[0][i] = 0;
            table[1][i] = i;
        }
        for (; i < (1 << MAX_LWZ_BITS); ++i)
            table[0][i] = table[1][0] = 0;

        sp = stack;

        return 0;
    } else if (fresh) {
        fresh = FALSE;
        do {
            firstcode = oldcode = GetCode(gif_io, code_size, FALSE);
        } while (firstcode == clear_code);
        return firstcode;
    }
    if (sp > stack)
        return *--sp;

    while ((code = GetCode(gif_io, code_size, FALSE)) >= 0) {
        if (code == clear_code) {
            for (i = 0; i < clear_code; ++i) {
                table[0][i] = 0;
                table[1][i] = i;
            }
            for (; i < (1 << MAX_LWZ_BITS); ++i)
                table[0][i] = table[1][i] = 0;
            code_size = set_code_size + 1;
            max_code_size = 2 * clear_code;
            max_code = clear_code + 2;
            sp = stack;
            firstcode = oldcode = GetCode(gif_io, code_size, FALSE);
            return firstcode;
        } else if (code == end_code) {
            int count;
            unsigned char buf[260];

            if (ZeroDataBlock)
                return -2;

            while ((count = GetDataBlock(gif_io, buf)) > 0);

            if (count != 0) {
                /*
                 * pm_message("missing EOD in data stream (common occurence)");
                 */
            }
            return -2;
        }
        incode = code;

        if (code >= max_code) {
            *sp++ = firstcode;
            code = oldcode;
        }
        while (code >= clear_code) {
            *sp++ = table[1][code];
            if (code == table[0][code])
                RWSetMsg("GIF: Circular table entry");
            code = table[0][code];
        }

        *sp++ = firstcode = table[1][code];

        if ((code = max_code) < (1 << MAX_LWZ_BITS)) {
            table[0][code] = oldcode;
            table[1][code] = firstcode;
            ++max_code;
            if ((max_code >= max_code_size) &&
                (max_code_size < (1 << MAX_LWZ_BITS))) {
                max_code_size *= 2;
                ++code_size;
            }
        }
        oldcode = incode;

        if (sp > stack)
            return *--sp;
    }
    return code;
}

static uint8 *ReadImage(Fl_IO &gif_io, int len, int height, int cmapSize,
                        unsigned char cmap[3][MAXCOLORMAPSIZE],
                        int gray, int interlace, int ignore, Fl_PixelFormat &fmt, int &im_w, int &im_h)
{
    uint8 *data=0;
    unsigned char c;
    int i, v;
    int xpos = 0, ypos = 0, pass = 0;

    /*
     **	Initialize the compression routines
     */
    if (!gif_io.read(&c, 1)) {
        RWSetMsg("GIF: EOF / read error on image data");
        return NULL;
    }
    if (LWZReadByte(gif_io, TRUE, c) < 0) {
        RWSetMsg("GIF: Error reading image");
        return NULL;
    }
    /*
     **	If this is an "uninteresting picture" ignore it.
     */
    if (ignore) {
        while (LWZReadByte(gif_io, FALSE, c) >= 0);
        return NULL;
    }
    int pitch = Fl_Renderer::calc_pitch(1, len);
    fmt.realloc(8, 0,0,0,0);
    im_w = len;
    im_h = height;
    data = (uint8*)malloc(im_h*pitch*sizeof(uint8));

    for (i = 0; i < cmapSize; i++)
        SetCmap(i, cmap[CM_RED][i],
                cmap[CM_GREEN][i], cmap[CM_BLUE][i]);

    while ((v = LWZReadByte(gif_io, FALSE, c)) >= 0) {

        data[xpos + ypos * pitch] = v;

        ++xpos;
        if (xpos == len) {
            xpos = 0;
            if (interlace) {
                switch (pass) {
                case 0:
                case 1:
                    ypos += 8;
                    break;
                case 2:
                    ypos += 4;
                    break;
                case 3:
                    ypos += 2;
                    break;
                }

                if (ypos >= height) {
                    ++pass;
                    switch (pass) {
                    case 1:
                        ypos = 4;
                        break;
                    case 2:
                        ypos = 2;
                        break;
                    case 3:
                        ypos = 1;
                        break;
                    default:
                        goto fini;
                    }
                }
            } else {
                ++ypos;
            }
        }
        if (ypos >= height)
            break;
    }

fini:
    return data;
}

static bool gif_read_file(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h)
{
    Fl_IO gif_io;
    gif_io.init_io(fp, 0, 0);
    return gif_create(gif_io, data, format, w, h);
}

static bool gif_read_mem(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h)
{
    Fl_IO gif_io;
    gif_io.init_io(0, stream, size);
    return gif_create(gif_io, data, format, w, h);
}

Fl_Image_IO gif_reader =
{
    /* GENERAL: */
    "GIF", //name
    "gif", //filename extension

    /* VALIDATE FUNCTIONS: */
    gif_is_valid_file, //bool (*is_valid_file)(const char *filename, FILE *fp);
    gif_is_valid_mem, //bool (*is_valid_mem)(uint8 *stream, uint32 size);
    NULL, //bool (*is_valid_xpm)(uint8 **stream);

    /* READ FUNCTIONS: */
    gif_read_file, //bool (*read_file)(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);
    gif_read_mem, //bool (*read_mem)(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);

    /* WRITE FUNCTIONS: */
    NULL, //bool (*write_mem)(uint8 *&stream, int &size, int quality, uint8 *data, Fl_PixelFormat &data_format, int w, int h);
    NULL //bool (*write_file)(FILE *fp, int quality, uint8 *data, Fl_PixelFormat &format, int w, int h);
};
