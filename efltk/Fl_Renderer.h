#ifndef _Fl_RENDERER_H
#define _Fl_RENDERER_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Enumerations.h"
#include "Fl_Util.h"
#include "x.h"

#include <string.h>

#ifdef _WIN32

# include <windows.h>
# define __LITTLE_ENDIAN 1234
# define __BIG_ENDIAN    4321
# define __BYTE_ORDER __LITTLE_ENDIAN

#else

# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <endian.h>

#endif

// blitting flags:
#define COLOR_KEY     (1<<1) // Blits using colorkey...
#define	HW_PALETTE    (1<<2) // Blits using hw palette (index 8bit)

//Internally used only
typedef struct {
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
} Fl_Colormap_Color;

class Fl_Colormap
{
public:
    Fl_Colormap(int cols=0) {
        colors=0;
        realloc(cols);
    }
    ~Fl_Colormap() {
        if(colors) delete []colors;
    }
    void realloc(int cols) {
        if(colors) delete []colors;
        if(cols) colors = new Fl_Colormap_Color[cols]; else colors=0;
        ncolors = cols;
    }
    void copy(Fl_Colormap *map) {
        realloc(map->ncolors);
        memcpy(colors, map->colors, sizeof(Fl_Colormap_Color)*map->ncolors);
    }

    Fl_Colormap_Color *colors;
    int ncolors;
};

/* Everything in the pixel format structure is read-only */
class Fl_PixelFormat
{
public:
    Fl_PixelFormat();
    ~Fl_PixelFormat();
    void init(int bits_pp, uint32 Rmask, uint32 Gmask, uint32 Bmask, uint32 Amask);
    void realloc(int bits_pp, uint32 Rmask, uint32 Gmask, uint32 Bmask, uint32 Amask);
    void copy(Fl_PixelFormat *fmt);

    Fl_Colormap *palette;
    uint8  bitspp;
    uint8  bytespp;

    uint8  Rloss;
    uint8  Gloss;
    uint8  Bloss;
    uint8  Aloss;
    uint8  Rshift;
    uint8  Gshift;
    uint8  Bshift;
    uint8  Ashift;
    uint32 Rmask;
    uint32 Gmask;
    uint32 Bmask;
    uint32 Amask;
    /* RGB color key information */
    uint32 colorkey;
    /* Alpha value information (per-surface alpha) */
    uint8  alpha;

    // Mapping
    void invalidate_map();
    bool map_this(Fl_PixelFormat *dstfmt);
    Fl_PixelFormat *dst;
    uint8 *table;
    uint format_version;
    bool identity;
};

typedef struct _blit_info BlitInfo;
typedef void (*Blit_Function)(BlitInfo *info);
typedef struct _blit_info
{
    uint8 *s_pixels;
    int s_width;
    int s_height;
    int s_skip;

    uint8 *d_pixels;
    int d_width;
    int d_height;
    int d_skip;

    Fl_PixelFormat *src;
    uint8 *table;
    Fl_PixelFormat *dst;

    bool hw_surface;
} BlitInfo;

class Fl_Renderer {
public:
    static bool alpha_blit(uint8 *src, Fl_Rect *src_rect, Fl_PixelFormat *src_fmt, int src_pitch,
                           uint8 *dst, Fl_Rect *dst_rect, Fl_PixelFormat *fmt_fmt, int dst_pitch, int flags);

    static bool stretch(uint8 *src, int src_bpp, int src_pitch, Fl_Rect *srcrect,
                        uint8 *dst, int dst_bpp, int dst_pitch, Fl_Rect *dstrect);

    // General blitting, copies src -> dst, does also conversion
    static bool blit(uint8 *src, Fl_Rect *src_rect, Fl_PixelFormat *src_fmt, int src_pitch,
                     uint8 *dst, Fl_Rect *dst_rect, Fl_PixelFormat *dst_fmt, int dst_pitch, int flags);

    static bool render_to_pixmap(uint8 *src, Fl_Rect *src_rect, Fl_PixelFormat *src_fmt, int src_pitch,
                                 Pixmap dst, Fl_Rect *dst_rect, GC dst_gc, int flags);

#ifndef _WIN32
    static uint8 *data_from_window(Display *dsp, Window src, Fl_Rect &rect);
    static uint8 *data_from_pixmap(Display *dsp, Pixmap src, Fl_Rect &rect);
    static XImage *ximage_from_pixmap(Display *dsp, Pixmap src, Fl_Rect &rect);
#endif

    static inline int calc_pitch(int bytespp, int width) {
        if(!bytespp || !width) return 0;
        int pitch = width * bytespp;
        return (pitch + 3) & ~3;	/* word aligning */
    }

    // All Functions starting with "system_" needs system TO BE INITIALIZED
    // If not, all of these will fail...
    static bool system_inited();
    // Init renderer
    static void system_init();

    // Converts to system format, if flags is set to HW_SURFACE, then system
    // colormap is used if needed
    static uint8 *system_convert(Fl_PixelFormat *src_fmt, Fl_Size *src_size, uint8 *src, int flags=HW_PALETTE);
    static Fl_PixelFormat *system_format();
};

#define FORMAT_EQUAL(A, B) ( (A)->bitspp == (B)->bitspp && ((A)->Rmask == (B)->Rmask) && ((A)->Amask == (B)->Amask))

/* Load pixel of the specified format from a buffer and get its R-G-B values */
/* FIXME: rescale values to 0..255 here? */
#define RGB_FROM_PIXEL(pixel, fmt, r, g, b)				\
{									\
	r = (((pixel&fmt->Rmask)>>fmt->Rshift)<<fmt->Rloss)&0xFF; 		\
	g = (((pixel&fmt->Gmask)>>fmt->Gshift)<<fmt->Gloss)&0xFF; 		\
	b = (((pixel&fmt->Bmask)>>fmt->Bshift)<<fmt->Bloss)&0xFF; 		\
}
#define RGB_FROM_RGB565(pixel, r, g, b)					\
{									\
	r = (((pixel&0xF800)>>11)<<3);		 			\
	g = (((pixel&0x07E0)>>5)<<2); 					\
	b = ((pixel&0x001F)<<3); 					\
}
#define RGB_FROM_RGB555(pixel, r, g, b)					\
{									\
	r = (((pixel&0x7C00)>>10)<<3);		 			\
	g = (((pixel&0x03E0)>>5)<<3); 					\
	b = ((pixel&0x001F)<<3); 					\
    }
#define RGB_FROM_RGB888(pixel, r, g, b)					\
{									\
	r = ((pixel&0xFF0000)>>16);		 			\
	g = ((pixel&0xFF00)>>8);		 			\
	b = (pixel&0xFF);			 			\
}

#define RETRIEVE_RGB_PIXEL(buf, bpp, pixel)				   \
do {									   \
    switch (bpp) {							   \
		case 2:							   \
			pixel = *((uint16 *)(buf));			   \
		break;							   \
									   \
		case 3: {						   \
		        uint8 *B = (uint8 *)(buf);			   \
			if(__BYTE_ORDER == __LITTLE_ENDIAN) {		   \
			        pixel = B[0] + (B[1] << 8) + (B[2] << 16); \
			} else {					   \
			        pixel = (B[0] << 16) + (B[1] << 8) + B[2]; \
			}						   \
		}							   \
		break;							   \
									   \
		case 4:							   \
			pixel = *((uint32 *)(buf));			   \
		break;							   \
									   \
		default:						   \
			pixel = 0; /* appease gcc */			   \
		break;							   \
	}								   \
} while(0)

#define DISEMBLE_RGB(buf, bpp, fmt, pixel, R, G, B)			   \
do {									   \
    switch (bpp) {							   \
    case 1:\
    R = fmt->palette->colors[*buf].r;\
    G = fmt->palette->colors[*buf].g;\
    B = fmt->palette->colors[*buf].b;\
    pixel = (R<<16)|(G<<8)|B;\
    break;\
    \
    case 2:							   \
    pixel = *((uint16 *)(buf));			   \
    RGB_FROM_PIXEL(pixel, fmt, R, G, B);				   \
    break;							   \
    \
    case 3: {						   \
    uint8 *B = (uint8 *)buf;			   \
    if(__BYTE_ORDER == __LITTLE_ENDIAN) {		   \
    pixel = B[0] + (B[1] << 8) + (B[2] << 16); \
    } else {					   \
    pixel = (B[0] << 16) + (B[1] << 8) + B[2]; \
    }						   \
    }							   \
    RGB_FROM_PIXEL(pixel, fmt, R, G, B);				   \
    break;							   \
									   \
    case 4:							   \
    pixel = *((uint32 *)(buf));			   \
    RGB_FROM_PIXEL(pixel, fmt, R, G, B);				   \
    break;							   \
    \
    default:						   \
    pixel = 0;	/* prevent gcc from complaining */ \
    break;							   \
    }								   \
} while(0)

/* Assemble R-G-B values into a specified pixel format and store them */
#define PIXEL_FROM_RGB(pixel, fmt, r, g, b)				\
{									\
	pixel = ((r>>fmt->Rloss)<<fmt->Rshift)|				\
		((g>>fmt->Gloss)<<fmt->Gshift)|				\
		((b>>fmt->Bloss)<<fmt->Bshift);				\
}
#define RGB565_FROM_RGB(pixel, r, g, b)					\
{									\
	pixel = ((r>>3)<<11)|((g>>2)<<5)|(b>>3);			\
}
#define RGB555_FROM_RGB(pixel, r, g, b)					\
{									\
	pixel = ((r>>3)<<10)|((g>>3)<<5)|(b>>3);			\
}
#define RGB888_FROM_RGB(pixel, r, g, b)					\
{									\
	pixel = (r<<16)|(g<<8)|b;					\
}
#define ASSEMBLE_RGB(buf, bpp, fmt, r, g, b) 				\
{									\
    switch (bpp) {\
    case 2: {						\
      uint16 pixel;					\
      \
      PIXEL_FROM_RGB(pixel, fmt, r, g, b);		\
      *((uint16 *)(buf)) = pixel;			\
    }							\
    break;							\
									\
    case 3: {						\
      if(__BYTE_ORDER == __LITTLE_ENDIAN) {		\
      *((buf)+fmt->Rshift/8) = r;		\
      *((buf)+fmt->Gshift/8) = g;		\
      *((buf)+fmt->Bshift/8) = b;		\
    } else {					\
      *((buf)+2-fmt->Rshift/8) = r;		\
      *((buf)+2-fmt->Gshift/8) = g;		\
      *((buf)+2-fmt->Bshift/8) = b;		\
    }						\
    }							\
    break;							\
									\
    case 4: {						\
      uint32 pixel;					\
    \
      PIXEL_FROM_RGB(pixel, fmt, r, g, b);		\
      *((uint32 *)(buf)) = pixel;			\
    }							\
    break;							\
    }								\
}

#define ASSEMBLE_RGB_AMASK(buf, bpp, fmt, r, g, b, Amask)		\
{									\
	switch (bpp) {							\
		case 2: {						\
			uint16 *bufp;					\
			uint16 pixel;					\
									\
			bufp = (uint16 *)buf;				\
			PIXEL_FROM_RGB(pixel, fmt, r, g, b);		\
			*bufp = pixel | (*bufp & Amask);		\
		}							\
		break;							\
									\
		case 3: {						\
                        if(__BYTE_ORDER == __LITTLE_ENDIAN) {		\
			        *((buf)+fmt->Rshift/8) = r;		\
				*((buf)+fmt->Gshift/8) = g;		\
				*((buf)+fmt->Bshift/8) = b;		\
			} else {					\
			        *((buf)+2-fmt->Rshift/8) = r;		\
				*((buf)+2-fmt->Gshift/8) = g;		\
				*((buf)+2-fmt->Bshift/8) = b;		\
			}						\
		}							\
		break;							\
									\
		case 4: {						\
			uint32 *bufp;					\
			uint32 pixel;					\
									\
			bufp = (uint32 *)buf;				\
			PIXEL_FROM_RGB(pixel, fmt, r, g, b);		\
			*bufp = pixel | (*bufp & Amask);		\
		}							\
		break;							\
	}								\
}

/* FIXME: Should we rescale alpha into 0..255 here? */
#define RGBA_FROM_PIXEL(pixel, fmt, r, g, b, a)				\
{									\
	r = ((pixel&fmt->Rmask)>>fmt->Rshift)<<fmt->Rloss; 		\
	g = ((pixel&fmt->Gmask)>>fmt->Gshift)<<fmt->Gloss; 		\
	b = ((pixel&fmt->Bmask)>>fmt->Bshift)<<fmt->Bloss; 		\
	a = ((pixel&fmt->Amask)>>fmt->Ashift)<<fmt->Aloss;	 	\
}
#define RGBA_FROM_8888(pixel, fmt, r, g, b, a)	\
{						\
	r = (pixel&fmt->Rmask)>>fmt->Rshift;	\
	g = (pixel&fmt->Gmask)>>fmt->Gshift;	\
	b = (pixel&fmt->Bmask)>>fmt->Bshift;	\
	a = (pixel&fmt->Amask)>>fmt->Ashift;	\
}
#define RGBA_FROM_RGBA8888(pixel, r, g, b, a)				\
{									\
	r = (pixel>>24);						\
	g = ((pixel>>16)&0xFF);						\
	b = ((pixel>>8)&0xFF);						\
	a = (pixel&0xFF);						\
}
#define RGBA_FROM_ARGB8888(pixel, r, g, b, a)				\
{									\
	r = ((pixel>>16)&0xFF);						\
	g = ((pixel>>8)&0xFF);						\
	b = (pixel&0xFF);						\
	a = (pixel>>24);						\
}
#define RGBA_FROM_ABGR8888(pixel, r, g, b, a)				\
{									\
	r = (pixel&0xFF);						\
	g = ((pixel>>8)&0xFF);						\
	b = ((pixel>>16)&0xFF);						\
	a = (pixel>>24);						\
}
#define DISEMBLE_RGBA(buf, bpp, fmt, pixel, r, g, b, a)			   \
do {									   \
	switch (bpp) {							   \
		case 2:							   \
			pixel = *((uint16 *)(buf));			   \
		break;							   \
									   \
		case 3:	{/* FIXME: broken code (no alpha) */		   \
		        uint8 *b = (uint8 *)buf;			   \
			if(__BYTE_ORDER == __LITTLE_ENDIAN) {		   \
			        pixel = b[0] + (b[1] << 8) + (b[2] << 16); \
			} else {					   \
			        pixel = (b[0] << 16) + (b[1] << 8) + b[2]; \
			}						   \
		}							   \
		break;							   \
									   \
		case 4:							   \
			pixel = *((uint32 *)(buf));			   \
		break;							   \
									   \
		default:						   \
		        pixel = 0; /* stop gcc complaints */		   \
		break;							   \
	}								   \
	RGBA_FROM_PIXEL(pixel, fmt, r, g, b, a);			   \
	pixel &= ~fmt->Amask;						   \
} while(0)

/* FIXME: this isn't correct, especially for Alpha (maximum != 255) */
#define PIXEL_FROM_RGBA(pixel, fmt, r, g, b, a)				\
{									\
	pixel = ((r>>fmt->Rloss)<<fmt->Rshift)|				\
		((g>>fmt->Gloss)<<fmt->Gshift)|				\
		((b>>fmt->Bloss)<<fmt->Bshift)|				\
		((a<<fmt->Aloss)<<fmt->Ashift);				\
}
#define ASSEMBLE_RGBA(buf, bpp, fmt, r, g, b, a)			\
{									\
	switch (bpp) {							\
		case 2: {						\
			uint16 pixel;					\
									\
			PIXEL_FROM_RGBA(pixel, fmt, (unsigned)r, (unsigned)g, (unsigned)b, (unsigned)a);	\
			*((uint16 *)(buf)) = pixel;			\
		}							\
		break;							\
									\
		case 3: { /* FIXME: broken code (no alpha) */		\
    if(__BYTE_ORDER == __LITTLE_ENDIAN) {		\
    *((buf)+fmt->Rshift/8) = r;		\
    *((buf)+fmt->Gshift/8) = g;		\
    *((buf)+fmt->Bshift/8) = b;		\
    } else {					\
    *((buf)+2-fmt->Rshift/8) = r;		\
    *((buf)+2-fmt->Gshift/8) = g;		\
    *((buf)+2-fmt->Bshift/8) = b;		\
    }						\
		}							\
		break;							\
									\
		case 4: {						\
			uint32 pixel;					\
									\
			PIXEL_FROM_RGBA(pixel, fmt, r, g, b, a);	\
			*((uint32 *)(buf)) = pixel;			\
		}							\
		break;							\
	}								\
}

/* Blend the RGB values of two pixels based on a source alpha value */
#define ALPHA_BLEND(sR, sG, sB, A, dR, dG, dB)	\
do {						\
	dR = (((sR-dR)*(A))>>8)+dR;		\
	dG = (((sG-dG)*(A))>>8)+dG;		\
	dB = (((sB-dB)*(A))>>8)+dB;		\
} while(0)


/* This is a very useful loop for optimizing blitters */
#if USE_DUFFS_LOOP

/* 8-times unrolled loop */
#define DUFFS_LOOP8(pixel_copy_increment, width)			\
{ int n = (width+7)/8;							\
	switch (width & 7) {						\
	case 0: do {	pixel_copy_increment;				\
	case 7:		pixel_copy_increment;				\
	case 6:		pixel_copy_increment;				\
	case 5:		pixel_copy_increment;				\
	case 4:		pixel_copy_increment;				\
	case 3:		pixel_copy_increment;				\
	case 2:		pixel_copy_increment;				\
	case 1:		pixel_copy_increment;				\
		} while ( --n > 0 );					\
	}								\
}

/* 4-times unrolled loop */
#define DUFFS_LOOP4(pixel_copy_increment, width)			\
{ int n = (width+3)/4;							\
	switch (width & 3) {						\
	case 0: do {	pixel_copy_increment;				\
	case 3:		pixel_copy_increment;				\
	case 2:		pixel_copy_increment;				\
	case 1:		pixel_copy_increment;				\
		} while ( --n > 0 );					\
	}								\
}

/* Use the 8-times version of the loop by default */
#define DUFFS_LOOP(pixel_copy_increment, width)				\
	DUFFS_LOOP8(pixel_copy_increment, width)

#else

/* Don't use Duff's device to unroll loops */
#define DUFFS_LOOP(pixel_copy_increment, width)				\
{ int n;								\
  for ( n=width; n > 0; --n ) {					\
    pixel_copy_increment;					\
  }								\
}
#define DUFFS_LOOP8(pixel_copy_increment, width)			\
	DUFFS_LOOP(pixel_copy_increment, width)
#define DUFFS_LOOP4(pixel_copy_increment, width)			\
	DUFFS_LOOP(pixel_copy_increment, width)

#endif /* USE_DUFFS_LOOP */

/* Prevent Visual C++ 6.0 from printing out stupid warnings */
#if defined(_MSC_VER) && (_MSC_VER >= 600)
 #pragma warning(disable: 4550)
#endif

#endif
