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

#ifndef _FL_IMAGE_H_
#define _FL_IMAGE_H_

#include "Enumerations.h"
#include "Fl_Renderer.h"
#include "Fl_PtrList.h"
#include "Fl_Export.h"
#include "Fl_Flags.h"

#include <stdio.h> //For FILE

// Fl_Image quality types:
enum {	
    FL_QUALITY_POOR = 0,
    FL_QUALITY_NORMAL, // Default quality type.
    FL_QUALITY_GOOD,
    FL_QUALITY_BEST
};

// EFltk image IO struct:
typedef struct
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

class Fl_Image;

typedef bool (check_mask_pixel)(const Fl_Image *i, uint8 *buf);

/*!
 IMAGE
 */
class Fl_Image {
    friend class Fl_Image_Filter;

public:
    // This reads all supported file formats from file or data stream.
    // Except XPM stream, from file it will work.
    static Fl_Image *read(const char *filename, const uint8 *data = 0, uint32 data_size=0);
    // XPM ONLY: from file or data stream.
    static Fl_Image *read_xpm(const char *filename, const char * const *data=0);

    /**
     * Create image from compressed data.
     * Reads any supported image type from file 'filename',
     * with given quality option.
     */
    Fl_Image(const char *filename, int quality=FL_QUALITY_NORMAL);

    /**
     * Create image from compressed data.
     * Reads any supported image type from 'data',
     * with given quality option.
     * 'data_size' MUST be supplied also
     */
    Fl_Image(const uint8 *data, uint32 data_size, int quality=FL_QUALITY_NORMAL);

    /**
     * Create image from XPM data with given quality option.
     */
    Fl_Image(const char * const *data, int quality=FL_QUALITY_NORMAL); //XPM

    /**
     * Create image from uncompressed data with given format.
     * If data is NULL, data is allocated/freed by Fl_Image.
     * if 'allow_free' flag is set, Fl_Image will de-allocate data on clear() (destructor)
     */
    Fl_Image(int W, int H, Fl_PixelFormat *fmt, uint8 *data, bool allow_free=false);

    /**
     * Create image from uncompressed data with given bits per pixel 'bits_pp'.
     * If data is NULL, data is allocated/freed by Fl_Image.
     * if 'allow_free' flag is set, Fl_Image will de-allocate data on clear() (destructor)
     *
     * You may also want to provide color masks, e.g. RGBA 32-bit image they are Rmask=0xFF000000, Gmask=0x00FF0000, Bmask=0x0000FF00, Amask=0x000000FF
     * Otherwise default masks are calculated from bits per pixel.
     */
    Fl_Image(int W, int H, int bits_pp, uint8 *data=0, bool allow_free=false, uint32 Rmask=0, uint32 Gmask=0, uint32 Bmask=0, uint32 Amask=0);

    /**
     * Create copy of image 'i'
     */
    Fl_Image(Fl_Image &i);

    /**
     * Deletes all data, masks and offscreen pixmaps,
     * if they were allocated by Fl_Image or permission to free given.
     * @see clear()
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
    int quality() const { return m_quality; }
    void quality(int q) { m_quality = q; }

    // Copies 'src' to 'dst'
    void copy(Fl_Image &src, Fl_Image &dst);

    /*!
     @param W As a reference integer, Width is stored to this.
     @param H As a reference integer, Heigth is stored to this.

     Get image width and heigth. Fl_Image overloaded function.

     @see width() and height()
     */
    virtual void measure(int &W, int &H) { W=width(); H=height(); }

    /*!
     Draws image to screen.

     <i>dx, dy, dw, dh</i> are destination coordinates in widget to draw.<br>
     <i>sx, sy, dw, sh</i> are source coordinates in image.
     */
    void draw(int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, Fl_Flags f) { _draw(dx, dy, dw, dh, sx, sy, sw, sh, f); }
    /*!
     Draws image to screen. Fl_Image override function.

     <i>x, y, w, h</i> are destination coordinates in widget to draw.
     */
    void draw(int x, int y, int w=0, int h=0, Fl_Flags f=0) { if(!w) w=width(); if(!h) h=height(); _draw(x,y,w,h,0,0,0,0,f); }

    // Mask handling
    int mask_type() const { return m_fmt.masktype; }
    void mask_type(int mask) { m_fmt.masktype = mask; }

    void set_mask(Pixmap m, bool allow_free=false);
    Pixmap get_mask() const { return (Pixmap)mask; }

    void set_offscreen(Pixmap p, bool allow_free=false);
    Pixmap get_offscreen() const { return (Pixmap)id; }

    Region create_region_mask(check_mask_pixel *func = 0) const;
    Region create_scaled_region_mask(int w, int h, check_mask_pixel *func = 0);

    // Create masks.
    Pixmap create_bitmap_mask(check_mask_pixel *func = 0) const;
    Pixmap create_scaled_bitmap_mask(int w, int h, check_mask_pixel *func = 0);
    Pixmap create_mask(int w, int h) { return create_scaled_bitmap_mask(w,h); }

    /*!
     Scales image, Returns new image.
     Format of image is pre-served
     */
    Fl_Image *scale(int W, int H);

    /*!
     Converts image to grayscale.
     Format of image is pre-served
     */
    Fl_Image *grayscale();

    /*!
     Blends image to new image, using 'color' as foregroud (top of it)
     alpha() is used as opacity of 'color'
     Format of this image is preserved to returned image
     */
    Fl_Image *fore_blend(uint color);

    /*!
     Blends image to new image, using 'color' as backgroud.
     alpha() is used as opacity of image, if no alpha pixel in image.
     Format of this image is preserved to returned image
    */
    Fl_Image *back_blend(uint color);

    /*!
     Blends this to top of 'back'. New image is returned.
     Format of 'back' image is preserved to returned image
     */
    Fl_Image *blend(Fl_Image *back, int x, int y);

    // Frees all allocated buffers
    void clear();

    // Makes offscreen pixmaps redraw
    void invalidate();

    // Converts image to system screen depth
    void system_convert();

    // Image data
    uint8 *data() { return m_data; }

    int width()  const { return m_width; }
    int height() const { return m_height; }

    int pitch()   const { return m_pitch; }
    int bytespp() const { return m_fmt.bytespp; } //Bytes per pixel
    int bitspp()  const { return m_fmt.bitspp;  } //Bits per pixel

    int state() const { return m_state; }
    void state(int s) { m_state = s; }

    // For colorkey blitting and masking (colorkey in RGBA)
    inline uint32 colorkey() const { return m_fmt.colorkey; }
    inline void colorkey(uint32 c) { m_fmt.colorkey = c; }

    // 0 - 255 Surface alpha
    inline uint8 alpha() const { return m_fmt.alpha; }
    inline void alpha(uint8 a) { m_fmt.alpha = a; }

    // For masks:
    inline uint8 threshold() const { return m_threshold; }
    inline void threshold(uint8 t) { m_threshold = t; }

    // Indexed images colormap:
    inline Fl_Colormap *colormap() const { return m_fmt.palette; }
    Fl_Colormap *colormap(Fl_Colormap *new_map) { Fl_Colormap *old = m_fmt.palette; m_fmt.palette = new_map; return old; }

    Fl_PixelFormat *format() const { return (Fl_PixelFormat*)&m_fmt; }

    // Checks and maps format to other, if needed
    bool check_map(Fl_PixelFormat *cur_fmt, Fl_PixelFormat *new_fmt);
    bool check_map(Fl_PixelFormat *new_fmt);

    // Only draw to offscreen.
    void no_screen(bool v) { m_no_screen = v; }
    bool no_screen() const { return m_no_screen; }

    // Set this to false, to disable state effects in THIS image, e.g. DISABLED, SELECTED...
    void state_effect(bool value) { m_state_effect = value; }
    bool state_effect() const { return m_state_effect; }

    // Set this to false, to disable state effects in ALL images, e.g. DISABLED, SELECTED...
    static bool state_effect_all() { return m_state_effect_all; }
    static void state_effect_all(bool value) { m_state_effect_all = value; }

protected:
    /**
     Constructs empty image.
     */
    Fl_Image();

    void init(int W, int H, int bits_pp, uint8 *data, uint32 Rmask, uint32 Gmask, uint32 Bmask, uint32 Amask);
    virtual void _draw(int dx, int dy, int dw, int dh,
                       int sx, int sy, int sw, int sh,
                       Fl_Flags f);

    //Draws offscreen pixmap to screen
    void to_screen(int X, int Y, int W, int H, int cx, int cy);
    void to_screen_tiled(int X, int Y, int W, int H, int cx, int cy);

    int m_width;  ///< Width of image in pixels
    int m_height; ///< Height of image in pixels
    int m_pitch;  ///< Pitch is word aligment bits per line value.

    uint8 *m_data; ///< Uncompressed data is stored to this.

    bool m_data_alloc;   ///< True, if m_data is allocated by Fl_Image or free permission is granted
    bool m_id_alloc;     ///< True, 'id' offscreen pixmap is allocated by Fl_Image or permission to free granted
    bool m_mask_alloc;   ///< True, 'mask' offscreen bitmap is allocated by Fl_Image or permission to free granted

    void *id;   ///< offsreen id for drawing to screen. type of this is Pixmap. (under w32 HBITMAP)
    void *mask; ///< mask for offscreen id. type of this is Pixmap. (under w32 HBITMAP)

private:
    bool m_no_screen;
    uint8 m_threshold;

    Fl_PixelFormat m_fmt;

    bool m_state_effect;
    static bool m_state_effect_all;

    int m_state;
    int m_quality;

    int m_old_drawflags;  //last drawubg flags passed
    int m_lastw, m_lasth; //last scaled size
    // Data storage for selected, inactive...
    Fl_Image *m_mod_data;
};

// Image IO functions:
extern void fl_register_imageio(Fl_Image_IO *reader);
extern void fl_unregister_imageio(Fl_Image_IO *reader);
extern Fl_Image_IO *fl_find_imageio(Fl_Image_IO *reader);
extern Fl_Image_IO *fl_find_imageio(const char *name, const char *extension);

extern Fl_Image_IO *fl_find_imageio(int index);
extern uint fl_count_imageio();
Fl_Ptr_List &fl_list_imageio();

#endif
