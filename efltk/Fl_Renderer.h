/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _Fl_RENDERER_H_
#define _Fl_RENDERER_H_

#include "Enumerations.h"
#include "Fl_Util.h"
#include "x.h"

// Mask types:
enum {
    FL_MASK_NONE = 0,
    FL_MASK_ALPHA,
    FL_MASK_COLORKEY,
    FL_MASK_PIXELKEY,

    // Backward compatibility:
    MASK_NONE = FL_MASK_NONE,
    MASK_ALPHA = FL_MASK_ALPHA,
    MASK_COLORKEY = FL_MASK_COLORKEY,
    MASK_PIXELKEY = FL_MASK_PIXELKEY
};

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
    Fl_Colormap(int cols=0);
    ~Fl_Colormap();
    void realloc(int cols);
    void copy(Fl_Colormap *map);

    // Calculate an 8-bit (3 red, 3 green, 2 blue) dithered palette of colors
    void dither_colors(int bitspp);

    // Match an RGB value to a particular palette index
    uint8 find_color(uint8 R, uint8 G, uint8 B);

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

    uint32 map_rgb(uint8 r, uint8 g, uint8 b);
    uint32 map_rgba(uint8 r, uint8 g, uint8 b, uint8 a);

    void get_rgb(uint32 pixel, uint8 &r, uint8 &g, uint8 &b);
    void get_rgba(uint32 pixel, uint8 &r, uint8 &g, uint8 &b, uint8 &a);

    Fl_Colormap *palette;
    uint8  bitspp;
    uint8  bytespp;

    uint8  Rloss, Rshift;
    uint8  Gloss, Gshift;
    uint8  Bloss, Bshift;
    uint8  Aloss, Ashift;
    uint32 Rmask;
    uint32 Gmask;
    uint32 Bmask;
    uint32 Amask;
    /* RGB color key information */
    uint32 colorkey;
    /* Alpha value information (per-surface alpha) */
    uint8  alpha;
    /* Mask type */
    int masktype;

    // Mapping
    void invalidate_map();
    bool map_this(Fl_PixelFormat *dstfmt);
    Fl_PixelFormat *dst;
    uint8 *table;
    int format_version;
    bool identity;
};

// blitting flags for Fl_Renderer blit functions:
#define FL_BLIT_COLOR_KEY     (1<<1) // Blits using colorkey...
#define	FL_BLIT_HW_PALETTE    (1<<2) // Blits using hw palette (indexed 8bit)

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

    // Returns root/desktop window handle
    static Window root_window();

    // Returns data, either from PIXMAP or WINDOW. data is in "desired" format
    static uint8 *data_from_pixmap(Pixmap src, Fl_Rect &rect, Fl_PixelFormat *desired);
    static uint8 *data_from_window(Window src, Fl_Rect &rect, Fl_PixelFormat *desired);

#ifndef _WIN32
    // Special XWindows method
    static XImage *ximage_from_pixmap(Pixmap src, Fl_Rect &rect);
#endif

    static inline int calc_pitch(int bytespp, int width) {
        if(!bytespp || !width) return 0;
        int pitch = width * bytespp;
        return (pitch + 3) & ~3;	/* word aligning */
    }

    // Init renderer
    static void system_init();
    static bool system_inited();

    // Converts to system format, if flags is set to HW_SURFACE, then system
    // colormap is used if needed
    static uint8 *system_convert(Fl_PixelFormat *src_fmt, Fl_Size *src_size, uint8 *src, int flags=FL_BLIT_HW_PALETTE);
    static Fl_PixelFormat *system_format();

    // Image byte order
    static bool big_endian();
    static bool lil_endian();
};

typedef struct
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

typedef void (*Blit_Function)(BlitInfo *info);

// Fast pixel modifier color functions:
extern bool fl_format_equal(Fl_PixelFormat *A, Fl_PixelFormat *B);

/* Load pixel of the specified format from a buffer and get its R-G-B values */
extern void fl_rgb_from_pixel(uint32 pixel, Fl_PixelFormat *fmt, uint8 &r, uint8 &g, uint8 &b);
extern void fl_rgb_from_rgb565(uint16 pixel, uint8 &r, uint8 &g, uint8 &b);
extern void fl_rgb_from_rgb555(uint16 pixel, uint8 &r, uint8 &g, uint8 &b);
extern void fl_rgb_from_rgb888(uint32 pixel, uint8 &r, uint8 &g, uint8 &b);

extern void fl_rgba_from_pixel(uint32 pixel, Fl_PixelFormat *fmt, uint8 &r, uint8 &g, uint8 &b, uint8 &a);
extern void fl_rgba_from_8888(uint32 pixel, Fl_PixelFormat *fmt, uint8 &r, uint8 &g, uint8 &b, uint8 &a);
extern void fl_rgba_from_rgba8888(uint32 pixel, uint8 &r, uint8 &g, uint8 &b, uint8 &a);
extern void fl_rgba_from_argb8888(uint32 pixel, uint8 &r, uint8 &g, uint8 &b, uint8 &a);
extern void fl_rgba_from_abgr8888(uint32 pixel, uint8 &r, uint8 &g, uint8 &b, uint8 &a);

/* Assemble R-G-B values into a specified pixel format and store them */
extern void fl_pixel_from_rgb(uint32 &pixel, Fl_PixelFormat *fmt, uint8 r, uint8 g, uint8 b);
extern void fl_rgb888_from_rgb(uint32 &pixel, uint8 r, uint8 g, uint8 b);
extern void fl_rgb555_from_rgb(uint16 &pixel, uint8 r, uint8 g, uint8 b);
extern void fl_rgb565_from_rgb(uint16 &pixel, uint8 r, uint8 g, uint8 b);

extern void fl_assemble_rgb(uint8 *buf, int bpp, Fl_PixelFormat *fmt, uint8 r, uint8 g, uint8 b);
extern void fl_assemble_rgb_amask(uint8 *buf, int bpp, Fl_PixelFormat *fmt, uint8 r, uint8 g, uint8 b, uint8 Amask);
extern void fl_assemble_rgba(uint8 *buf, int bpp, Fl_PixelFormat *fmt, uint8 r, uint8 g, uint8 b, uint8 a);

extern void fl_retrieve_rgb_pixel(uint8 *buf, int bpp, uint32 &pixel);
extern void fl_disemble_rgb(uint8 *buf, int bpp, Fl_PixelFormat *fmt, uint32 &pixel, uint8 &R, uint8 &G, uint8 &B);
extern void fl_disemble_rgba(uint8 *buf, int bpp, Fl_PixelFormat *fmt, uint32 &pixel, uint8 &r, uint8 &g, uint8 &b, uint8 &a);
extern void fl_pixel_from_rgba(uint32 &pixel, Fl_PixelFormat *fmt, uint8 r, uint8 g, uint8 b, uint8 a);

/* Blend the RGB values of two pixels based on a source alpha value */
extern void fl_alpha_blend(uint8 sR, uint8 sG, uint8 sB, uint8 A, uint8 &dR, uint8 &dG, uint8 &dB);

// Byte swapping functions for EFltk:
extern uint16 fl_swap_16(uint16 d);
extern uint32 fl_swap_32(uint32 d);

// Endian independ, swaps bytes, if needed. (e.g. big endian machine will swap bytes in 'fl_swap_le16')
extern uint16 fl_swap_le16(uint16 d);
extern uint32 fl_swap_le32(uint32 d);
extern uint16 fl_swap_be16(uint16 d);
extern uint32 fl_swap_be32(uint32 d);

#endif
