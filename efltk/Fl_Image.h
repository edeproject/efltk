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
#include "Fl_PtrList.h"
#include "Fl_Export.h"
#include "Fl_Flags.h"

#include <stdio.h>

// Forward declaration
typedef struct _fl_image_io_ Fl_Image_IO;

// Fl_Image quality types:
typedef enum {	
	FL_QUALITY_POOR = 0,
	FL_QUALITY_NORMAL, // Default quality type.
	FL_QUALITY_GOOD,
	FL_QUALITY_BEST	
};

/*!
 IMAGE
 */
class Fl_Image {
    friend class Fl_Image_Filter;

public:
    // STATIC READ FUNCTIONS (read/read_xpm) ARE DEPRECATED!
    // USE "read_image / write_image" or Constructor instead!

    // This reads all supported file formats from file or data stream.
    // Except XPM stream, from file it will work.
    static Fl_Image *read(const char *filename, const uint8 *data = 0, uint32 data_size=0);
    // XPM ONLY: from file or data stream.
    static Fl_Image *read_xpm(const char *filename, const char * const *data=0);


    /*!
     Constructs empty image, with nothing allocated.
     */
    Fl_Image();

    /*!
     Reads any supported image type, with given quality option
     */
    Fl_Image(const char *filename, int quality=FL_QUALITY_NORMAL);
    Fl_Image(const uint8 *data, uint32 data_size, int quality=FL_QUALITY_NORMAL);
    Fl_Image(const char * const *data, int quality=FL_QUALITY_NORMAL); //XPM

    /*!
     @param W As a width of image
     @param H As a height of image
     @param fmt As a Pixel format to use in image
     @param data As pre-allocated data of image, or 0 (allocated by Fl_Image)
     */
    Fl_Image(int W, int H, Fl_PixelFormat *fmt, uint8 *data=0);
    /*!
     @param W As a width of image
     @param H As a height of image
     @param bits_pp As a bits per pixel (8,15,16,24,32)
     @param data As pre-allocated data of image, or 0 (allocated by Fl_Image)

     You may also want to provide color masks, e.g. ARGB 32-bit image they are Rmask=0x00FF0000, Gmask=0x0000FF00, Bmask=0x000000FF, Amask=0xFF000000
     */
    Fl_Image(int W, int H, int bits_pp, uint8 *data, uint32 Rmask=0, uint32 Gmask=0, uint32 Bmask=0, uint32 Amask=0);
    /*!
     @param W As a width of image
     @param H As a height of image
     @param bits_pp As a bits per pixel (8,15,16,24,32)

     Simplier contructor, data is allocated always by Fl_Image.
     */
    Fl_Image(int W, int H, int bits_pp=32);

    // Copies image 'i' to this
    Fl_Image(Fl_Image &i);

    /*!
     Destructor, cleans image. Deletes all mask and offscreen pixmaps.
     Deallocates data.
     */
    virtual ~Fl_Image();

    // New read/write methods:
    // Read image:
    bool read_image(const char *filename, const uint8 *data = 0, uint32 data_size=0);
    bool read_image(const char *filename, const char * const *data);
    bool read_image(const char *filename, char **data) { return read_image(filename, (const char **)data); }

    // Write image to file,
    bool write_image(const char *filename, const char *io_name);
    bool write_image(const char *filename, Fl_Image_IO *io);

    // Write image to memory pointer 'data'. Size of allocated data is set to 'data_size'.
    bool write_image(uint8 *&data, int &data_size, const char *io_name);
    bool write_image(uint8 *&data, int &data_size, Fl_Image_IO *io);

    // Quality in read/write time
    int quality() { return quality_; }
    void quality(int q) { quality_ = q; }

    // Copies 'src' to 'dst'
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
    void draw(int x, int y, int w=0, int h=0, Fl_Flags f=0) { if(!w) w=width(); if(!h) h=height(); draw(x,y,w,h,0,0,0,0,f); }

    // Mask handling
    int mask_type() { return fmt.masktype; }
    void mask_type(int mask) { fmt.masktype = mask; }

    void set_mask(Pixmap m, bool allow_free=false);
    Pixmap get_mask() { return (Pixmap)mask; }

    void set_offscreen(Pixmap p, bool allow_free=false);
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

    // Blends image to new image, using 'back' as background
    // Default makes new image to be system fmt(no need to convert)
    // supported bits_per_pixels = 8, 15, 16, 24, 32
    Fl_Image *blend(Fl_Image *back, Fl_Rect *back_rect, Fl_PixelFormat *new_format=Fl_Renderer::system_format());
    Fl_Image *blend(Fl_Image *back, int x, int y, int w, int h, Fl_PixelFormat *new_format=Fl_Renderer::system_format()) {
        Fl_Rect tmp(x,y,w,h); return blend(back, &tmp, new_format);
    }

    // Frees all allocated buffers
    void clear();

    // Makes offscreen pixmaps redraw
    void invalidate();

    // Converts image to system screen depth
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

    // For colorkey blitting and masking (colorkey in RGBA)
    inline uint32 colorkey()       { return fmt.colorkey; }
    inline void colorkey(uint32 c) { fmt.colorkey = c; }

    // 0 - 255 Surface alpha
    inline uint8 alpha()       { return fmt.alpha; }
    inline void alpha(uint8 a) { fmt.alpha = a; }

    // For masks:
    inline void threshold(uint8 t) { _threshold = t; }
    inline uint8 threshold() { return _threshold; }

    // Indexed images colormap:
    inline Fl_Colormap *colormap() { return fmt.palette; }
    Fl_Colormap *colormap(Fl_Colormap *new_map) { Fl_Colormap *old = fmt.palette; fmt.palette = new_map; return old; }

    Fl_PixelFormat *format() { return &fmt; }

    // Checks and maps format to other, if needed
    bool check_map(Fl_PixelFormat *cur_fmt, Fl_PixelFormat *new_fmt);
    bool check_map(Fl_PixelFormat *new_fmt);

    // Only draw to offscreen.
    void no_screen(bool v) { no_screen_ = v; }
    bool no_screen() { return no_screen_; }

    // Set this to false, to disable state effects in THIS image, e.g. DISABLED, SELECTED...
    void state_effect(bool value) { _state_effect = value; }
    bool state_effect() { return _state_effect; }

    // Set this to false, to disable state effects in ALL images, e.g. DISABLED, SELECTED...
    static bool state_effect_all() { return _state_effect_all; }
    static void state_effect_all(bool value) { _state_effect_all = value; }

protected:

    void init(int W, int H, int bits_pp, uint8 *data, uint32 Rmask, uint32 Gmask, uint32 Bmask, uint32 Amask);
    void _draw(int x, int y, Fl_Flags f) { if(f&FL_ALIGN_TILED) to_screen_tiled(x,y,w,h,0,0); else to_screen(x,y,w,h,0,0); }

    //Draws offscreen pixmap to screen
    void to_screen(int X, int Y, int W, int H, int cx, int cy);
    void to_screen_tiled(int X, int Y, int W, int H, int cx, int cy);

    int w, h;
    void *id, *mask;

    bool _state_effect;
    static bool _state_effect_all;

    bool no_screen_;
    Fl_PixelFormat fmt;

    int quality_;
    unsigned int draw_flags;
    int _state;
    int _pitch;

    uint8 _threshold;
    uint8 *_data;

    bool _data_alloc, _id_alloc, _mask_alloc;
    int last_w, last_h; //last scaled size

    // Data store for selected, inactive...
    Fl_Image *_mod_data;
};


// EFltk image IO struct:
typedef struct _fl_image_io_
{
    /* GENERAL: */
    /* Name of image type, e.g. "JPEG" or "PNG" */
    char *name;
    /* Supported file extension, e.g. "jpeg;jpg" */
    char *extensions;

    /* VALIDATE FUNCTIONS: */
    /* Check if filename has valid extension and/or is data valid. 'fp' is opened already. */
    bool (*is_valid_file)(const char *filename, FILE *fp);
    /* Check if 'stream' memory pointer is valid stream. 'size' is size of 'stream' */
    bool (*is_valid_mem)(const uint8 *stream, uint32 size);
    //XPM ONLY:
    bool (*is_valid_xpm)(const uint8 **stream);

    /* READ FUNCTIONS: */
    /* data will be stored in 'data' and its format in 'format' in both functions */
    /* read from file, 'fp' is opened already. Called ONLY if valid_file function passed. */
    bool (*read_file)(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);
    /* read 'stream' memory pointer. 'size' is size of 'stream'. Called ONLY if valid_mem function passed. */
    bool (*read_mem)(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);

    /* WRITE FUNCTIONS: */
    /* Write to memory, stream is allocated in this function, size of allocated stream is stored in 'size'. */
    bool (*write_mem)(uint8 *&stream, int &size, int quality, uint8 *data, Fl_PixelFormat &data_format, int w, int h);
    /* Write to file, 'fp' is opened already. */
    bool (*write_file)(FILE *fp, int quality, uint8 *data, Fl_PixelFormat &data_format, int w, int h);

} Fl_Image_IO;

// Image IO functions:
extern void fl_register_imageio(Fl_Image_IO *reader);
extern void fl_unregister_imageio(Fl_Image_IO *reader);
extern Fl_Image_IO *fl_find_imageio(Fl_Image_IO *reader);
extern Fl_Image_IO *fl_find_imageio(const char *name, const char *extension);

extern Fl_Image_IO *fl_find_imageio(int index);
extern uint fl_count_imageio();
Fl_Ptr_List &fl_list_imageio();

#endif

//
// End of "$Id$".
//
