//
// "$Id$"
//
// Image header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Image_H
#define Fl_Image_H

#include "Enumerations.h"
#include "Fl_Renderer.h"
#include "Fl_Export.h"
#include "Fl_Flags.h"

class Fl_Image;

typedef struct _reader
{
    bool  (*is_valid)(void *stream, bool file);
    Fl_Image *(*create)(void *stream, int size, bool file);
} ImageReader;

typedef enum
{
    MASK_NONE = 0,
    MASK_ALPHA,
    MASK_COLORKEY,
    MASK_PIXELKEY
} Mask_Type;

/*!
 IMAGE
 */
class Fl_Image {
    friend class Fl_Image_Filter;

public:
    //If you provide data, you may want to provide also data size, otherwise it's sizeof(data)
    static Fl_Image *read(const char *filename, const uint8 *data = 0, uint data_size=0);

    Fl_Image() { }

    /*!
     @param W As a width of image
     @param H As a height of image
     @param fmt As a Pixel format to use in image
     @param data As pre-allocated data of image, or 0 (allocated by Fl_Image)
     @param flags can be 0 or COLOR_KEY, flags are passed to blitting functions
     */
    Fl_Image(int W, int H, Fl_PixelFormat *fmt, uint8 *data=0, int flags=0);
    /*!
     @param W As a width of image
     @param H As a height of image
     @param bits_pp As a bits per pixel (8,15,16,24,32)
     @param data As pre-allocated data of image, or 0 (allocated by Fl_Image)
     @param flags can be 0 or COLOR_KEY, flags are passed to blitting functions

     You may also want to provide color masks, e.g. ARGB 32-bit image they are Rmask=0x00FF0000, Gmask=0x0000FF00, Bmask=0x000000FF, Amask=0xFF000000
     */
    Fl_Image(int W, int H, int bits_pp, uint8 *data, uint32 Rmask=0, uint32 Gmask=0, uint32 Bmask=0, uint32 Amask=0, int flags=0);
    /*!
     @param W As a width of image
     @param H As a height of image
     @param bits_pp As a bits per pixel (8,15,16,24,32)
     @param flags can be 0 or COLOR_KEY, flags are passed to blitting functions

     Simplier contructor, data is allocated always by Fl_Image.
     */
    Fl_Image(int W, int H, int bits_pp=32, int flags=0);

    // Copies image 'i' to this
    Fl_Image(Fl_Image &i);

    /*!
     Destructor, cleans image. Deletes all mask and offscreen pixmaps.
     Deallocates data.
     */
    virtual ~Fl_Image();

    void copy(Fl_Image &src, Fl_Image &dst);

    /*!
     @param W As a reference integer, Width is stored to this.
     @param H As a reference integer, Heigth is stored to this.

     Get image width and heigth. Fl_Image overloaded function.

     @see width() and height()
     */
    virtual void measure(int &W, int &H) { W=w; H=h; }

    /*!
     Draws image to screen.

     <i>dx, dy, dw, dh</i> are destination coordinates in widget to draw.<br>
     <i>sx, sy, dw, sh</i> are source coordinates in image.
     */
    virtual void draw(int dx, int dy, int dw, int dh,
                      int sx, int sy, int sw, int sh,
                      Fl_Flags f);
    /*!
     Draws image to screen. Fl_Image override function.

     <i>x, y, w, h</i> are destination coordinates in widget to draw.
     */
    virtual void draw(int x, int y, int w=0, int h=0, Fl_Flags f = 0) { if(!w) w=width(); if(!h) h=height(); draw(x,y,w,h,0,0,0,0,f); }

    // Mask handling
    Mask_Type mask_type() { return _masktype; }
    void mask_type(Mask_Type val) { _masktype = val; }
    void set_mask(Pixmap m);
    Pixmap get_mask() { return (Pixmap)mask; }
    Pixmap get_offscreen() { return (Pixmap)id; }

    // Creates masks, scales if needed. Uses automatically mask_type and threshold/colorkey...
    // Call this for creating mask.
    Pixmap create_mask(int w, int h);

    // Create masks from data, do not call directly, unless you know what you are doing
    Pixmap create_alpha_mask(Fl_Rect &rect, uint8 *data, int pitch, Fl_PixelFormat *format, uint8 threshold);
    Pixmap create_color_mask(Fl_Rect &rect, uint8 *data, int pitch, Fl_PixelFormat *format, uint32 color);
    Pixmap create_pixel_mask(Fl_Rect &rect, uint8 *data, int pitch, Fl_PixelFormat *format, uint32 pixel);

    // Scales image to new image. SLOW (Only very little asm optimization)
    Fl_Image *scale(int W, int H);

    /*!
     Converts image to grayscale.

     Default argument makes new image to be system format

     Supported depths in format are <b>15, 16, 24, 32</b>
     */
    Fl_Image *grayscale(Fl_PixelFormat *new_format=Fl_Renderer::system_format());

    /*!
     Blends image to new image, using <i>color</i> as foregroud (top of it)

     Default argument makes new image to be system format

     Supported depths in format are <b>8, 15, 16, 24, 32</b>
     */
    Fl_Image *fore_blend(uint color, Fl_PixelFormat *new_format=Fl_Renderer::system_format());

    /*!
     Blends image to new image, using <i>color</i> as backgroud

     Default argument makes new image to be system format

     Supported depths in format are <b>8, 15, 16, 24, 32</b>
    */
    Fl_Image *back_blend(uint color, Fl_PixelFormat *new_format=Fl_Renderer::system_format());

    // Blends image to new image, using back as background
    // Default makes new image to be system fmt(no need to convert)
    // supported bits_per_pixels = 15, 16, 24, 32
    Fl_Image *blend(Fl_Image *back, Fl_Rect *back_rect, Fl_PixelFormat *new_format=Fl_Renderer::system_format());
    Fl_Image *blend(Fl_Image *back, int x, int y, int w, int h, Fl_PixelFormat *new_format=Fl_Renderer::system_format()) {
        Fl_Rect tmp(x,y,w,h); return blend(back, &tmp, new_format);
    }

    // Frees all allocated buffers
    void clear();

    // Makes offscreen pixmaps redraw
    void invalidate();

    void system_convert();

    // Image data
    uint8 *data() { return _data; }

    int width()  { return w; }
    int height() { return h; }

    int pitch() { if(!_pitch) _pitch = Fl_Renderer::calc_pitch(fmt.bytespp, w); return _pitch; }
    inline int bytespp() { return fmt.bytespp; 	} //Bytes per pixel
    inline int bitspp()  { return fmt.bitspp; 	} //Bits per pixel

    int state()       { return _state; }
    void state(int s) { _state = s; }

    // Flag handling
    int  flags() 		{ return _flags;   }
    void flags(int flags) 	{ _flags = flags;  }
    void set_flags(int flags)	{ _flags |= flags; }
    void clear_flags(int flags) { _flags &= ~flags;}
    bool isset(int flags) 	{ return ((_flags & (unsigned)flags) == (unsigned)flags); }

    // For colorkey blitting and masking (colorkey in RGBA)
    inline uint32 colorkey()       { return fmt.colorkey; }
    inline void colorkey(uint32 c) { fmt.colorkey = c; }

    // 0 - 255 Surface alpha
    inline uint8 alpha()       { return fmt.alpha; }
    inline void alpha(uint8 a) { fmt.alpha = a; }

    inline void threshold(uint8 t) { _threshold = t; }
    inline uint8 threshold() { return _threshold; }

    inline Fl_Colormap *colormap() { return fmt.palette; }
    Fl_Colormap *colormap(Fl_Colormap *new_map) { Fl_Colormap *old = fmt.palette; fmt.palette = new_map; return old; }

    Fl_PixelFormat *format() { return &fmt; }
    bool check_map(Fl_PixelFormat *cur_fmt, Fl_PixelFormat *new_fmt);
    bool check_map(Fl_PixelFormat *new_fmt);

    static void register_reader(ImageReader *reader);
    static void unregister_reader(ImageReader *reader);
    static ImageReader *find_reader(ImageReader *reader);

    void no_screen(bool v) { no_screen_ = v; }
    bool no_screen() { return no_screen_; }

    // Set this to false, to disable state effects in THIS image, e.g. DISABLED, SELECTED...
    void state_effect(bool value) { _state_effect = value; }
    bool state_effect() { return _state_effect; }

    // Set this to false, to disable state effects in ALL images, e.g. DISABLED, SELECTED...
    static bool state_effect_all() { return _state_effect_all; }
    static void state_effect_all(bool value) { _state_effect_all = value; }

protected:

    void init(int W, int H, int bits_pp, uint8 *data, uint32 Rmask, uint32 Gmask, uint32 Bmask, uint32 Amask, int flags);

    void _draw(int x, int y, Fl_Flags) { to_screen(x,y,w,h,0,0); }

    void to_screen(int X, int Y, int W, int H, int cx, int cy);
    void to_screen_tiled(int X, int Y, int W, int H, int cx, int cy);

    int w, h;
    void *id, *mask;

    bool _state_effect;
    static bool _state_effect_all;

    bool no_screen_;

    Fl_PixelFormat fmt;

    int _state;

    Mask_Type _masktype;

    unsigned _flags, draw_flags;
    int _pitch;

    uint8 _threshold;
    uint8 *_data;

    bool _data_alloc, _mask_alloc;
    int last_w, last_h; //last scaled size

    // Data store for selected, inactive...
    Fl_Image *_mod_data;
};

#endif

//
// End of "$Id$".
//
