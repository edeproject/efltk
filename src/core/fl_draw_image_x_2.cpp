//
// "$Id$"
//
// Image drawing routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

// This file is not independently compiled, it is included by fl_draw_image.cxx

#include "Fl_XColor.h"

// A list of assumptions made about the X display:

// bits_per_pixel must be one of 8, 16, 24, 32.

// scanline_pad must be a power of 2 and greater or equal to 8.

// PsuedoColor visuals must have 8 bits_per_pixel (although the depth
// may be less than 8).  This is the only limitation that affects any
// modern X displays, you can't use 12 or 16 bit colormaps.

// The mask bits in TrueColor visuals for each color are
// contiguous and have at least one bit of each color.  This
// is not checked for.

// For 24 and 32 bit visuals there must be at least 8 bits of each color.

////////////////////////////////////////////////////////////////

static int bytes_per_pixel;

static void (*converter)(const uchar *from, uchar *to, int w, int delta);
static void (*mono_converter)(const uchar *from, uchar *to, int w, int delta);

static int dir;		// direction-alternator
static int ri,gi,bi;	// saved error-diffusion value

#if USE_COLORMAP
////////////////////////////////////////////////////////////////
// 8-bit converter with error diffusion

static void color8_converter(const uchar *from, uchar *to, int w, int delta) {
  int r=ri, g=gi, b=bi;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    to = to+(w-1);
    d = -delta;
    td = -1;
  } else {
    dir = 1;
    d = delta;
    td = 1;
  }
  for (;; from += d, to += td) {
    r += from[0]; if (r < 0) r = 0; else if (r>255) r = 255;
    g += from[1]; if (g < 0) g = 0; else if (g>255) g = 255;
    b += from[2]; if (b < 0) b = 0; else if (b>255) b = 255;
    Fl_Color i = fl_color_cube(r*FL_NUM_RED/256,g*FL_NUM_GREEN/256,b*FL_NUM_BLUE/256);
    Fl_XColor& xmap = fl_xmap[i];
    if (!xmap.mapped) fl_allocate_xpixel(xmap,r,g,b);
    r -= xmap.r;
    g -= xmap.g;
    b -= xmap.b;
    *to = uchar(xmap.pixel);
    if (!--w) break;
  }
  ri = r; gi = g; bi = b;
}

static void mono8_converter(const uchar *from, uchar *to, int w, int delta) {
  int r=ri, g=gi, b=bi;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    to = to+(w-1);
    d = -delta;
    td = -1;
  } else {
    dir = 1;
    d = delta;
    td = 1;
  }
  for (;; from += d, to += td) {
    r += from[0]; if (r < 0) r = 0; else if (r>255) r = 255;
    g += from[0]; if (g < 0) g = 0; else if (g>255) g = 255;
    b += from[0]; if (b < 0) b = 0; else if (b>255) b = 255;
    Fl_Color i = fl_color_cube(r*FL_NUM_RED/256,g*FL_NUM_GREEN/256,b*FL_NUM_BLUE/256);
    Fl_XColor& xmap = fl_xmap[i];
    if (!xmap.mapped) fl_allocate_xpixel(xmap,r,g,b);
    r -= xmap.r;
    g -= xmap.g;
    b -= xmap.b;
    *to = uchar(xmap.pixel);
    if (!--w) break;
  }
  ri = r; gi = g; bi = b;
}

#endif

////////////////////////////////////////////////////////////////
// 16 bit TrueColor converters with error diffusion
// Cray computers have no 16-bit type, so we use character pointers
// (which may be slow)

#ifdef U16
#define OUTTYPE U16
#define OUTSIZE 1
#define OUTASSIGN(v) *t = v
#else
#define OUTTYPE uchar
#define OUTSIZE 2
#define OUTASSIGN(v) int tt=v; t[0] = uchar(tt>>8); t[1] = uchar(tt)
#endif

static void color16_converter(const uchar *from, uchar *to, int w, int delta) {
  OUTTYPE *t = (OUTTYPE *)to;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    t = t+(w-1)*OUTSIZE;
    d = -delta;
    td = -OUTSIZE;
  } else {
    dir = 1;
    d = delta;
    td = OUTSIZE;
  }
  int r=ri, g=gi, b=bi;
  for (;; from += d, t += td) {
    r = (r&~fl_redmask)  +from[0]; if (r>255) r = 255;
    g = (g&~fl_greenmask)+from[1]; if (g>255) g = 255;
    b = (b&~fl_bluemask) +from[2]; if (b>255) b = 255;
    OUTASSIGN((
      ((r&fl_redmask)<<fl_redshift)+
      ((g&fl_greenmask)<<fl_greenshift)+
      ((b&fl_bluemask)<<fl_blueshift)
      ) >> fl_extrashift);
    if (!--w) break;
  }
  ri = r; gi = g; bi = b;
}

static void mono16_converter(const uchar *from,uchar *to,int w, int delta) {
  OUTTYPE *t = (OUTTYPE *)to;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    t = t+(w-1)*OUTSIZE;
    d = -delta;
    td = -OUTSIZE;
  } else {
    dir = 1;
    d = delta;
    td = OUTSIZE;
  }
  uchar mask = fl_redmask & fl_greenmask & fl_bluemask;
  int r=ri;
  for (;; from += d, t += td) {
    r = (r&~mask) + *from; if (r > 255) r = 255;
    uchar m = r&mask;
    OUTASSIGN((
      (m<<fl_redshift)+
      (m<<fl_greenshift)+
      (m<<fl_blueshift)
      ) >> fl_extrashift);
    if (!--w) break;
  }
  ri = r;
}

// special-case the 5r6g5b layout used by XFree86:

static void c565_converter(const uchar *from, uchar *to, int w, int delta) {
  OUTTYPE *t = (OUTTYPE *)to;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    t = t+(w-1)*OUTSIZE;
    d = -delta;
    td = -OUTSIZE;
  } else {
    dir = 1;
    d = delta;
    td = OUTSIZE;
  }
  int r=ri, g=gi, b=bi;
  for (;; from += d, t += td) {
    r = (r&7)+from[0]; if (r>255) r = 255;
    g = (g&3)+from[1]; if (g>255) g = 255;
    b = (b&7)+from[2]; if (b>255) b = 255;
    OUTASSIGN(((r&0xf8)<<8) + ((g&0xfc)<<3) + (b>>3));
    if (!--w) break;
  }
  ri = r; gi = g; bi = b;
}

static void m565_converter(const uchar *from,uchar *to,int w, int delta) {
  OUTTYPE *t = (OUTTYPE *)to;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    t = t+(w-1)*OUTSIZE;
    d = -delta;
    td = -OUTSIZE;
  } else {
    dir = 1;
    d = delta;
    td = OUTSIZE;
  }
  int r=ri;
  for (;; from += d, t += td) {
    r = (r&7) + *from; if (r > 255) r = 255;
    OUTASSIGN((r>>3) * 0x841);
    if (!--w) break;
  }
  ri = r;
}

////////////////////////////////////////////////////////////////
// 24bit TrueColor converters:

static void rgb_converter(const uchar *from, uchar *to, int w, int delta) {
  int d = delta-3;
  for (;; from += d) {
    *to++ = *from++;
    *to++ = *from++;
    *to++ = *from++;
    if (!--w) break;
  }
}

static void bgr_converter(const uchar *from, uchar *to, int w, int delta) {
  for (;; from += delta) {
    uchar r = from[0];
    uchar g = from[1];
    *to++ = from[2];
    *to++ = g;
    *to++ = r;
    if (!--w) break;
  }
}

static void rrr_converter(const uchar *from, uchar *to, int w, int delta) {
  for (;; from += delta) {
    *to++ = *from;
    *to++ = *from;
    *to++ = *from;
    if (!--w) break;
  }
}

////////////////////////////////////////////////////////////////
// 32bit TrueColor converters on a 32 or 64-bit machine:

#ifdef U64
# define STORETYPE U64
# if WORDS_BIGENDIAN
# define INNARDS32(f) \
  U64 *t = (U64*)to; \
  int w1 = (w+1)/2; \
  for (;;from += delta) {U64 i = f; from += delta; *t++ = (i<<32)|(f); if (!--w1) break;}
#else
# define INNARDS32(f) \
  U64 *t = (U64*)to; \
  int w1 = (w+1)/2; \
  for (;; from += delta) {U64 i = f; from += delta; *t++ = ((U64)(f)<<32)|i; if (!--w1) break;}
#endif
#else
#define STORETYPE U32
#define INNARDS32(f) \
  U32 *t = (U32*)to; for (; w--; from += delta) *t++ = f
#endif

static void rgbx_converter(const uchar *from, uchar *to, int w, int delta) {
  INNARDS32((unsigned(from[0])<<24)+(from[1]<<16)+(from[2]<<8));
}

static void xbgr_converter(const uchar *from, uchar *to, int w, int delta) {
  INNARDS32((from[0])+(from[1]<<8)+(from[2]<<16));
}

static void xrgb_converter(const uchar *from, uchar *to, int w, int delta) {
  INNARDS32((from[0]<<16)+(from[1]<<8)+(from[2]));
}

static void bgrx_converter(const uchar *from, uchar *to, int w, int delta) {
  INNARDS32((from[0]<<8)+(from[1]<<16)+(unsigned(from[2])<<24));
}

static void rrrx_converter(const uchar *from, uchar *to, int w, int delta) {
  INNARDS32(unsigned(*from) * 0x1010100U);
}

static void xrrr_converter(const uchar *from, uchar *to, int w, int delta) {
  INNARDS32(*from * 0x10101U);
}

static void
color32_converter(const uchar *from, uchar *to, int w, int delta) {
  INNARDS32(
    (from[0]<<fl_redshift)+(from[1]<<fl_greenshift)+(from[2]<<fl_blueshift));
}

static void
mono32_converter(const uchar *from,uchar *to,int w, int delta) {
  INNARDS32(
    (*from << fl_redshift)+(*from << fl_greenshift)+(*from << fl_blueshift));
}

////////////////////////////////////////////////////////////////

static void figure_out_visual()
{
    if(!Fl_Renderer::system_inited())
        Fl_Renderer::system_init();

    bytes_per_pixel = sys_fmt.bytespp;
#if USE_COLORMAP
    if (bytes_per_pixel == 1) {
        converter = color8_converter;
        mono_converter = mono8_converter;
        return;
    }
    if (!fl_visual->red_mask)
        Fl::fatal("Can't do %d bits_per_pixel colormap",i.bits_per_pixel);
#endif

    // otherwise it is a TrueColor visual:
    int rs = sys_fmt.Rshift;
    int gs = sys_fmt.Gshift;
    int bs = sys_fmt.Bshift;

    switch (bytes_per_pixel) {

    case 2:
        // All 16-bit TrueColor visuals are supported on any machine with
        // 24 or more bits per integer.
#ifdef U16
        //::i.byte_order = WORDS_BIGENDIAN;
#else
        //::i.byte_order = 1;
#endif
        if (rs == 11 && gs == 6 && bs == 0 && fl_extrashift == 3) {
            converter = c565_converter;
            mono_converter = m565_converter;
        } else {
            converter = color16_converter;
            mono_converter = mono16_converter;
        }
        break;

    case 3:
        if(s_image.byte_order) {rs = 16-rs; gs = 16-gs; bs = 16-bs;}
        if (rs == 0 && gs == 8 && bs == 16) {
            converter = rgb_converter;
            mono_converter = rrr_converter;
        } else if (rs == 16 && gs == 8 && bs == 0) {
            converter = bgr_converter;
            mono_converter = rrr_converter;
        } else {
            Fl::fatal("Can't do arbitrary 24bit color");
        }
        break;

    case 4:
        if ((s_image.byte_order!=0) != WORDS_BIGENDIAN)
        {rs = 24-rs; gs = 24-gs; bs = 24-bs;}
        if (rs == 0 && gs == 8 && bs == 16) {
            converter = xbgr_converter;
            mono_converter = xrrr_converter;
        } else if (rs == 24 && gs == 16 && bs == 8) {
            converter = rgbx_converter;
            mono_converter = rrrx_converter;
        } else if (rs == 8 && gs == 16 && bs == 24) {
            converter = bgrx_converter;
            mono_converter = rrrx_converter;
        } else if (rs == 16 && gs == 8 && bs == 0) {
            converter = xrgb_converter;
            mono_converter = xrrr_converter;
        } else {
            //::i.byte_order = WORDS_BIGENDIAN;
            converter = color32_converter;
            mono_converter = mono32_converter;
        }
        break;

    default:
        Fl::fatal("Can't do %d bits_per_pixel", s_image.bits_per_pixel);
    }

}

#define MAXBUFFER 0x40000 // 256k

static void innards(const uchar *buf, int X, int Y, int W, int H,
		    int delta, int linedelta, int mono,
		    Fl_Draw_Image_Cb cb, void* userdata)
{
  if (!linedelta) linedelta = W*delta;

  int dx, dy, w, h;
  fl_clip_box(X,Y,W,H,dx,dy,w,h);
  if (w<=0 || h<=0) return;
  dx -= X; dy -= Y;
  fl_transform(X,Y);

  if (!bytes_per_pixel) figure_out_visual();
  s_image.width = w;
  s_image.height = h;

  void (*conv)(const uchar *from, uchar *to, int w, int delta) = converter;
  if (mono) conv = mono_converter;

  // See if the data is already in the right format.  Unfortunately
  // some 32-bit x servers (XFree86) care about the unknown 8 bits
  // and they must be zero.  I can't confirm this for user-supplied
  // data, so the 32-bit shortcut is disabled...
  // This can set bytes_per_line negative if image is bottom-to-top
  // I tested it on Linux, but it may fail on other Xlib implementations:
  if (buf && (
#if 0	// set this to 1 to allow 32-bit shortcut
      delta == 4 &&
#if WORDS_BIGENDIAN
      conv == rgbx_converter
#else
      conv == xbgr_converter
#endif
      ||
#endif
      conv == rgb_converter && delta==3
      ) && !(linedelta&_scanline_add)) {
    s_image.data = (char *)(buf+delta*dx+linedelta*dy);
    s_image.bytes_per_line = linedelta;

  } else {
    int linesize = ((w*bytes_per_pixel+_scanline_add)&_scanline_mask)/sizeof(STORETYPE);
    int blocking = h;
    static STORETYPE *buffer=0;	// our storage, always word aligned
    static long buffer_size=0;
    {int size = linesize*h;
    if (size > MAXBUFFER) {
      size = MAXBUFFER;
      blocking = MAXBUFFER/linesize;
    }
    if (size > buffer_size) {
        if(buffer) delete[] buffer;
      buffer_size = size;
      buffer = new STORETYPE[size];
    }}
    s_image.data = (char *)buffer;
    s_image.bytes_per_line = linesize*sizeof(STORETYPE);
    if (buf) {
      buf += delta*dx+linedelta*dy;
      for (int j=0; j<h; ) {
	STORETYPE *to = buffer;
	int k;
	for (k = 0; j<h && k<blocking; k++, j++) {
	  conv(buf, (uchar*)to, w, delta);
	  buf += linedelta;
	  to += linesize;
	}
	XPutImage(fl_display,fl_window,fl_gc, &s_image, 0, 0, X+dx, Y+dy+j-k, w, k);
      }
    } else {
      STORETYPE* linebuf = new STORETYPE[(W*delta+(sizeof(STORETYPE)-1))/sizeof(STORETYPE)];
      for (int j=0; j<h; ) {
	STORETYPE *to = buffer;
	int k;
	for (k = 0; j<h && k<blocking; k++, j++) {
	  cb(userdata, dx, dy+j, w, (uchar*)linebuf);
	  conv((uchar*)linebuf, (uchar*)to, w, delta);
	  to += linesize;
	}
	XPutImage(fl_display,fl_window,fl_gc, &s_image, 0, 0, X+dx, Y+dy+j-k, w, k);
      }
      delete[] linebuf;
    }
  }
}

#define DITHER_RECTF (fl_visual->depth > 16)

//
// End of "$Id$"
//
