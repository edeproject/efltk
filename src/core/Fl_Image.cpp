#include <efltk/Fl_Image.h>
#include <efltk/Fl_Image_Filter.h>
#include <efltk/Fl_PtrList.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl.h>
#include <efltk/x.h>
#include <efltk/fl_utf8.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "fl_internal.h"

////////////////////////////////////
// EFLTK IMAGE IO METHODS

static Fl_Ptr_List imageio_list;

Fl_Image_IO *fl_find_imageio(Fl_Image_IO *io) {
    int index = imageio_list.index_of(io);
    return (Fl_Image_IO *)(index!=-1?imageio_list[index]:0);
}

void fl_unregister_imageio(Fl_Image_IO *io) {
    Fl_Image_IO *item = fl_find_imageio(io);
    if(!item) return;
    imageio_list.remove(io);
}

void fl_register_imageio(Fl_Image_IO *io) {
    if(fl_find_imageio(io)) return;
    imageio_list.append(io);
}

Fl_Image_IO *fl_find_imageio(const char *name, const char *extension) {

    for(uint n=0; n<imageio_list.size(); n++) {
        Fl_Image_IO *item = (Fl_Image_IO *)imageio_list[n];
        if(name) if(!strcasecmp(item->name, name)) return item;
        if(extension) if(strstr(item->extensions, extension)) return item;
    }
    return 0;
}

Fl_Image_IO *fl_find_imageio(int index) {
    return (Fl_Image_IO *)imageio_list.item(index);
}

uint fl_count_imageio() {
    return imageio_list.size();
}

Fl_Ptr_List &fl_list_imageio() {
    return imageio_list;
}

//////////////////////////////////////

bool Fl_Image::_state_effect_all = true;

Fl_Image::Fl_Image() 
{ 
	init(0,0,0,0,0,0,0,0); 
}

Fl_Image::Fl_Image(const char *filename, int quality)
{
	init(0,0,0,0,0,0,0,0);
	quality_ = quality;
	read_image(filename);
}

Fl_Image::Fl_Image(const uint8 *data, uint32 data_size, int quality)
{
	init(0,0,0,0,0,0,0,0);
	quality_ = quality;
	read_image(0, data, data_size);
}

Fl_Image::Fl_Image(const char * const *data, int quality)
{
	init(0,0,0,0,0,0,0,0);
	quality_ = quality;
	read_image(0, data);
}

Fl_Image::Fl_Image(int W, int H, Fl_PixelFormat *fmt, uint8 *data)
{
    init(W, H, fmt->bitspp, data, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);
}

Fl_Image::Fl_Image(int W, int H, int bits_pp)
{
    uint32 Rmask=0, Gmask=0, Bmask=0, Amask=0;
    switch(bits_pp)
    {
    case 32:
        Amask = 0xFF000000;
    case 24:
        Rmask = 0x00FF0000;
        Gmask = 0x0000FF00;
        Bmask = 0x000000FF;
        break;
    case 15:
    case 16:
        Rmask = 0x7C00;
        Gmask = 0x03E0;
        Bmask = 0x001F;
        break;
    }
    init(W, H, bits_pp, 0, Rmask, Gmask, Bmask, Amask);
}

Fl_Image::Fl_Image(int W, int H, int bits_pp, uint8 *data, uint32 Rmask, uint32 Gmask, uint32 Bmask, uint32 Amask)
{
    init(W, H, bits_pp, data, Rmask, Gmask, Bmask, Amask);
}

Fl_Image::Fl_Image(Fl_Image &i)
{
    init(0,0,0,0,0,0,0,0);
    copy(i, *this);
}

void Fl_Image::copy(Fl_Image &src, Fl_Image &dst)
{
	dst.clear();

	dst.w = src.w;
	dst.h = src.h;
	dst._pitch = src._pitch;
	dst._threshold = src._threshold;
	dst.quality_ = src.quality_;
	dst._state_effect = src._state_effect;
	dst._data_alloc = true;

	dst.fmt.copy(&src.fmt);

	dst._data = new uint8[src.h*src._pitch];
    memcpy(dst._data, src._data, src.h*src._pitch);
}

void Fl_Image::init(int W, int H, int bits_pp, uint8 *data, uint32 Rmask, uint32 Gmask, uint32 Bmask, uint32 Amask)
{
    _state_effect = true;

    _state = 0;
    _mod_data = 0;
    last_w = last_h = 0;
    _mask_alloc = false;
    _id_alloc = false;

    w = W;
    h = H;

    fmt.init(bits_pp, Rmask, Gmask, Bmask, Amask);

	quality_ = FL_QUALITY_NORMAL;
    draw_flags = 0;
    _data_alloc = false;
    _data = data;
    _pitch = 0;

    if(W>0 && H>0 && bits_pp>0) {
        _pitch = Fl_Renderer::calc_pitch(fmt.bytespp, w);
        if(!_data) {
            _data_alloc = true;
            // Allocate uint8 data array and initialize it to 0
            _data = new uint8[H*_pitch];
            memset(_data, 0, H*_pitch);
        }
    }

	// Masking:
	_threshold = 128;
    id = mask = 0;

    no_screen_ = false;
}

Fl_Image::~Fl_Image()
{
    clear();
}

bool Fl_Image::check_map(Fl_PixelFormat *new_map)
{
    return check_map(&fmt, new_map);
}

bool Fl_Image::check_map(Fl_PixelFormat *cur_fmt, Fl_PixelFormat *new_fmt)
{
    if(fl_format_equal(cur_fmt, new_fmt) && !cur_fmt->palette) {
        return false;
    }
    return cur_fmt->map_this(new_fmt);
}

void Fl_Image::system_convert()
{
    Fl_Renderer::system_init();

    Fl_PixelFormat *format = Fl_Renderer::system_format();

    if( fl_format_equal((&fmt), format) ) {
        return;
    }

    fmt.invalidate_map();
    // Check to make sure the blit mapping is valid
    check_map(format);

    Fl_Size s(w,h);
    uint8 *system_fmt = Fl_Renderer::system_convert(&fmt, &s, _data, FL_BLIT_HW_PALETTE);
    if(_data_alloc) delete []_data;

    _data = system_fmt;
    _data_alloc = true;

    fmt.bitspp = format->bitspp;
    fmt.bytespp = format->bytespp;
    fmt.Rloss = format->Rloss;
    fmt.Gloss = format->Gloss;
    fmt.Bloss = format->Bloss;
    fmt.Aloss = format->Aloss;
    fmt.Rshift = format->Rshift;
    fmt.Gshift = format->Gshift;
    fmt.Bshift = format->Bshift;
    fmt.Ashift = format->Ashift;
    fmt.Rmask = format->Rmask;
    fmt.Gmask = format->Gmask;
    fmt.Bmask = format->Bmask;
    fmt.Amask = format->Amask;

    if(!format->palette) {
        if(fmt.palette) delete fmt.palette;
        fmt.palette=0;
    } else {
        if(!fmt.palette) fmt.palette = new Fl_Colormap();
        fmt.palette->copy(format->palette);
        fmt.map_this(format);
    }

    _pitch = Fl_Renderer::calc_pitch(fmt.bytespp, w);

    invalidate();
}

void Fl_Image::invalidate()
{
    if(mask && _mask_alloc) {
        fl_delete_bitmap((Pixmap)mask);
        _mask_alloc = false;
        mask = 0;
    }
    if(id) {
        fl_delete_offscreen((Pixmap)id);
        _id_alloc = false;
        id = 0;
    }
}

void Fl_Image::clear()
{
    invalidate();
    if(_data && _data_alloc) {
        delete []_data;
    }
	_data = 0;
	_data_alloc = false;
}

Fl_Image *Fl_Image::grayscale(Fl_PixelFormat *new_format)
{
    Fl_Image *ret = new Fl_Image(w, h, new_format->bitspp);
    ret->fmt.realloc(new_format->bitspp,
                     new_format->Rmask,
                     new_format->Gmask,
                     new_format->Bmask,
                     new_format->Amask);

    if(new_format->palette) {
        if(!ret->fmt.palette) ret->fmt.palette = new Fl_Colormap();
        ret->fmt.palette->copy(new_format->palette);
    }

    ret->check_map(new_format);

    Fl_Rect r(0,0,w,h);
    Fl_Renderer::blit(_data, &r, format(), pitch(),
                       ret->data(), &r, ret->format(), ret->pitch(), 0);

    Fl_Image_Filter::apply_to_this(ret, 0, FILTER_DESATURATE);

    return ret;
}

Fl_Image *Fl_Image::scale(int W, int H)
{
    Fl_Image *ret = new Fl_Image(W, H, fmt.bitspp);
    ret->format()->copy(format());

    Fl_Rect olds(0,0,w,h); Fl_Rect news(0,0,W,H);
    bool success = Fl_Renderer::stretch(_data, fmt.bytespp, _pitch, &olds,
                                         ret->data(), fmt.bytespp, ret->pitch(), &news);
    if(!success) {
        delete ret;
        ret = 0;
    }
    return ret;
}

uint8 *render_box(int w, int h, int bitspp, uint color, Fl_Colormap *pal, uint8 *buffer=0)
{
    int bpp = (bitspp+7)/8;
    int pitch = Fl_Renderer::calc_pitch(bpp, w);
    uint8 *ret = buffer;
    if(!buffer) ret = new uchar[pitch*h];

    uint8 r=0,g=0,b=0;
    fl_get_color(color, r, g, b);
    uint32 fill_color=0;
    switch(bitspp) {
    case 32: fl_rgb888_from_rgb(fill_color ,r,g,b); break;
    case 16: fl_rgb565_from_rgb((uint16&)fill_color ,r,g,b); break;
    case 15: fl_rgb555_from_rgb((uint16&)fill_color ,r,g,b); break;
    case 8:  fill_color = pal->find_color(r,g,b); break;
    default: break;
    }

    // Fill box, using fast duffs looping
    uint8 *ptr = ret;
    int skip = pitch - w * bpp;
    int height = h; int width = w;
    while ( height-- ) {
        DUFFS_LOOP(
                    {
                        switch(bitspp)
                        {
                        case 32: (uint32&)(*ptr) = fill_color; break;
                        case 24: ptr[0] = r; ptr[1] = g; ptr[2] = b; break;
                        case 16: (uint16&)(*ptr) = (uint16&)fill_color; break;
                        case 15: (uint16&)(*ptr) = (uint16&)fill_color; break;
                        case 8:  (uint8&)(*ptr) = (uint8&)fill_color; break;
                        default: break;
                        }
                        ptr += bpp;
                    }, width);
        ptr += skip;
    }

    return ret;
}

Fl_Image *Fl_Image::fore_blend(uint color, Fl_PixelFormat *new_format)
{
    Fl_Image *ret = new Fl_Image(w, h, new_format->bitspp);
    ret->fmt.realloc(new_format->bitspp,
                     new_format->Rmask,
                     new_format->Gmask,
                     new_format->Bmask,
                     new_format->Amask);

    uint8 *src = _data;
    uint8 *dst = ret->data();

    Fl_PixelFormat *srcfmt = &fmt;
    Fl_PixelFormat *dstfmt = &ret->fmt;

    int srcbpp = srcfmt->bytespp;
    int dstbpp = dstfmt->bytespp;

    int srcskip = _pitch - w * srcbpp;
    int dstskip = ret->pitch() - w * dstbpp;

    int width = w;
    int height = h;

    uint8 sA = srcfmt->alpha;
    uint8 dA = dstfmt->Amask ? 255 : 0;

    uint32 pixel=0;
    uint8 sR=0, sG=0, sB=0;
    uint8 dR=0, dG=0, dB=0;
    fl_get_color(color, dR, dG, dB);

    if(srcbpp==1) {
        check_map(dstfmt);
    }

    ERROR_DIFF_START();

    while ( height-- ) {
        DUFFS_LOOP4(
        {
            fl_disemble_rgb(src, srcbpp, srcfmt, pixel, sR, sG, sB);

            fl_alpha_blend(dR, dG, dB, sA, sR, sG, sB);
            if(dstbpp==1) {
                ERROR_DIFF(sR,sG,sB,*dst);
            } else
                fl_assemble_rgba(dst, dstbpp, dstfmt, sR, sG, sB, dA);

            src += srcbpp;
            dst += dstbpp;
        }, width);
        src += srcskip;
        dst += dstskip;
    }

    ERROR_DIFF_END();
    return ret;
}

Fl_Image *Fl_Image::back_blend(uint color, Fl_PixelFormat *new_format)
{
    Fl_Image *ret = new Fl_Image(w, h, new_format->bitspp);
    ret->fmt.realloc(new_format->bitspp,
                     new_format->Rmask,
                     new_format->Gmask,
                     new_format->Bmask,
                     new_format->Amask);

    if(new_format->palette) {
        if(!ret->fmt.palette) ret->fmt.palette = new Fl_Colormap();
        ret->fmt.palette->copy(new_format->palette);
    }

    ret->check_map(new_format);
    render_box(w, h, ret->bitspp(), color, ret->format()->palette, ret->data());

    check_map(new_format);
    Fl_Rect R(0,0,w,h);
    Fl_Renderer::alpha_blit(_data, &R, &fmt, _pitch,
                            ret->data(), &R, ret->format(), ret->pitch(),
                            FL_BLIT_HW_PALETTE);
    return ret;
}

Fl_Image *Fl_Image::blend(Fl_Image *back, Fl_Rect *back_rect, Fl_PixelFormat *new_format)
{
    //Check boundary...
    int X=0,Y=0,W=w,H=h;
    if(back_rect->x() < 0) {
        W+=back_rect->x();
        X=(back_rect->x()*-1);
        back_rect->x(0);
        back_rect->w(W);
    }
    if(back_rect->y() < 0) {
        H+=back_rect->y();
        Y=(back_rect->y()*-1);
        back_rect->y(0);
        back_rect->h(H);
    }
    if(back_rect->x()+back_rect->w() >= back->width()) {
        W-=back_rect->x()+back_rect->w()-back->width();
        back_rect->w(W);
    }
    if(back_rect->y()+back_rect->h() >= back->height()) {
        H-=back_rect->y()+back_rect->h()-back->height();
        back_rect->h(H);
    }

    if(back_rect->w() < 1 || back_rect->h() < 1)
        return 0;

    Fl_Image *ret = new Fl_Image(W, H, new_format);
    ret->fmt.copy(new_format);

    Fl_Rect tmp_r(0, 0, W, H);
    back->fmt.map_this(new_format);
    Fl_Renderer::blit(back->data(), back_rect, back->format(), back->pitch(),
                      ret->data(), &tmp_r, new_format, ret->pitch(), 0);

    // Be sure that blit map is valid for 'ret' image
    check_map(new_format);

    Fl_Rect tmp_r2(X, Y, W, H);
    Fl_Renderer::alpha_blit(_data, &tmp_r2, &fmt, _pitch,
                             ret->data(), &tmp_r, ret->format(), ret->pitch(),
                             FL_BLIT_HW_PALETTE);

    return ret;
}

void Fl_Image::set_offscreen(Pixmap p, bool allow_free)
{
    if(id && _id_alloc) fl_delete_offscreen((Pixmap)id);
    id = (void*)p;
    _id_alloc = allow_free;
}

void Fl_Image::set_mask(Pixmap m, bool allow_free)
{
    if(mask && _mask_alloc) fl_delete_bitmap((Pixmap)mask);
    mask = (void*)m;
    _mask_alloc = allow_free;
}

#ifdef _WIN32

#define begin_mask() \
    maskbitmap = CreateCompatibleBitmap(fl_getDC(), rect.w(), rect.h()); \
    fl_begin_offscreen(maskbitmap); \

#define end_mask() fl_end_offscreen()

#else
// X window seems to need some more stuff here :)
#define begin_mask() \
    fl_push_matrix(); \
    Window swin = fl_window; \
    fl_window = RootWindow(fl_display, fl_screen); \
    maskbitmap = XCreatePixmap(fl_display, fl_window, rect.w(), rect.h(), 1); \
    Fl_Drawable *_sd = fl_drawable; \
    Fl_Drawable _nd(maskbitmap); \
    _nd.make_current(); \
    if(fl_gc) fl_push_no_clip(); \
    GC gc = fl_gc;  \
    XGCValues xv; xv.line_width = 1; \
    xv.foreground = XBlackPixel(fl_display, fl_screen); \
    xv.background = XBlackPixel(fl_display, fl_screen); \
    fl_gc = XCreateGC(fl_display, maskbitmap, GCForeground, &xv)

#define end_mask() \
    fl_gc = gc; \
    _nd.free_gc(); \
    if(_sd) _sd->make_current(); \
    else fl_drawable=0; \
    fl_pop_clip(); \
    fl_pop_matrix(); \
    fl_window = swin

#endif

Pixmap Fl_Image::create_alpha_mask(Fl_Rect &rect, uint8 *data, int pitch, Fl_PixelFormat *format, uint8 threshold)
{
    if(!format->Amask) {
        //printf("No alpha channel\n");
        return 0;
    }
    if(rect.w() < 1 || rect.h() < 1) {
        return 0;
    }

    bool mask_found=false;
    Pixmap maskbitmap;
    begin_mask();

    // Fill with white...
    fl_color(fl_rgb(255,255,255));
    fl_rectf(0,0,rect.w(), rect.h());

    // Set color to black...
    fl_color(fl_rgb(0,0,0));

    uint8 *ptr;
    for(int y = rect.y(), a=0; y < (rect.y()+rect.h()); y++,a++)
    {
        ptr = (data + (y * pitch) + (rect.x() * format->bytespp));
        for(int x = 0; x < rect.w(); x++)
        {
            uint8 r,g,b, alpha;
            uint32 pixel;
            fl_disemble_rgba(ptr, format->bytespp, (format), pixel, r, g, b, alpha);

            if(alpha < threshold) {
                mask_found = true;
                fl_line(x,a,x,a); // Draw a dot.
            }
            ptr+=format->bytespp;
        }
    }

    end_mask();

    if(!mask_found) {
        fl_delete_offscreen(maskbitmap);
        maskbitmap=0;
    }

    return maskbitmap;
}

Pixmap Fl_Image::create_color_mask(Fl_Rect &rect, uint8 *data, int pitch, Fl_PixelFormat *format, uint32 color)
{
    if(rect.w() < 1 || rect.h() < 1) {
        return 0;
    }

    bool use_table = false;
    Fl_PixelFormat pf;
    if(bitspp() < 16) {
        use_table = true;
        if(!fmt.table) {
            pf.init(32,0xFF000000, 0x00FF0000,0x0000FF00, 0x000000FF);
            check_map(&pf);
        }
    }

    bool mask_found=false;
    Pixmap maskbitmap;
    begin_mask();

    // Fill with white...
    fl_color(fl_rgb(255,255,255));
    fl_rectf(0,0,rect.w(),rect.h());

    // Set color to black...
    fl_color(fl_rgb(0,0,0));

    uint32 pixel;
    uint8 cr,cg,cb,ca,r=0,g=0,b=0;
    //fl_rgb_from_rgb888(color, cr, cg, cb);
    fl_rgba_from_rgba8888(color, cr, cg, cb, ca);	

    bool is_xpm = (color==0xFFFFFFFF);

    uint8 *ptr;
    for(int y = rect.y(), a=0; y < (rect.y()+rect.h()); y++,a++)
    {
        ptr = (data + (y * pitch) + (rect.x() * format->bytespp));
        for(int x = 0; x < rect.w(); x++)
        {
            fl_disemble_rgb(ptr, format->bytespp, (format), pixel, r, g, b);
            if(fmt.bytespp==1) {
                if(is_xpm && format->palette->colors[*ptr].a) {
                    // Fixes indexed XPM's
                    fl_line(x, a, x, a);
                    mask_found = true;
                }
                else if(!is_xpm && r==cr && g==cg && b==cb) {
                    // For non-indexed images
                    fl_line(x, a, x, a);
                    mask_found = true;
                }
            }
            else if(r==cr && g==cg && b==cb) {
                // For non-indexed images
                fl_line(x, a, x, a);
                mask_found = true;
            }
            ptr+=format->bytespp;
        }
    }

    end_mask();

    if(!mask_found) {
        fl_delete_offscreen(maskbitmap);
        maskbitmap=0;
    }

    return maskbitmap;
}

Pixmap Fl_Image::create_pixel_mask(Fl_Rect &rect, uint8 *data, int pitch, Fl_PixelFormat *format, uint32 pixel)
{
    if(rect.w() < 1 || rect.h() < 1) {
        return 0;
    }

    bool mask_found = false;
    Pixmap maskbitmap;
    begin_mask();

    // Fill with white...
    fl_color(fl_rgb(255,255,255));
    fl_rectf(0,0,rect.w(),rect.h());

    // Set color to black...
    fl_color(fl_rgb(0,0,0));

    uint8 *ptr;
    for(int y = rect.y(), a=0; y < (rect.y()+rect.h()); y++,a++)
    {
        ptr = (data + (y * pitch) + (rect.x() * format->bytespp));
        for(int x = 0; x < rect.w(); x++)
        {
            if(*ptr==pixel) {
                fl_line(x, a, x, a);
                mask_found = true;
            }
            ptr+=format->bytespp;
        }
    }

    end_mask();

    if(!mask_found) {
        fl_delete_offscreen(maskbitmap);
        maskbitmap=0;
    }

    return maskbitmap;
}

Pixmap Fl_Image::create_mask(int W, int H)
{
    if(mask_type()==FL_MASK_NONE) return 0;

    Fl_Rect rect1(0,0,w,h);
    Fl_Rect rect2(0,0,W,H);

    int newpitch = Fl_Renderer::calc_pitch(fmt.bytespp, W);
    Pixmap bitmap=0;
    uint8 *dataptr=0, *alloc=0;

    if(W!=w || H!=h) {
        alloc = new uint8[newpitch*H];
        if(!Fl_Renderer::stretch(data(), bytespp(), pitch(), &rect1, alloc, bytespp(), newpitch, &rect2)) {
            delete []alloc;
            return 0;
        }
        dataptr = alloc;
    } else {
        dataptr = data();
    }

    if(mask_type() == FL_MASK_ALPHA) {
        bitmap = create_alpha_mask(rect2, dataptr, newpitch, format(), threshold());
    }
    else if(mask_type() == FL_MASK_COLORKEY) {
        bitmap = create_color_mask(rect2, dataptr, newpitch, format(), colorkey());
    }
    else if(mask_type() == FL_MASK_PIXELKEY) {
        bitmap = create_pixel_mask(rect2, dataptr, newpitch, format(), colorkey());
    }
    if(!bitmap) {
        mask_type(FL_MASK_NONE);
    }

    if(alloc) delete []alloc;

    return bitmap;
}

void Fl_Image::draw(int dx, int dy, int dw, int dh,
                    int sx, int sy, int sw, int sh,
                    Fl_Flags f)
{
    if(!_data || w < 1 || h < 1 || dw<1 || dh<1)
        return;

    // Init renderer before first draw!!!
    Fl_Renderer::system_init();

    if(sw<=0) sw=w;
    if(sh<=0) sh=h;

    bool need_redraw=false;

    uint8 *draw_data = _data;
    Fl_PixelFormat *draw_fmt = &fmt;
    int draw_pitch = Fl_Renderer::calc_pitch(Fl_Renderer::system_format()->bytespp, w);

    if((f&FL_ALIGN_SCALE)==FL_ALIGN_SCALE) {
        draw_flags |= FL_ALIGN_SCALE;
    } else {
        if((draw_flags&FL_ALIGN_SCALE)) {
            // If we were in scale mode, we have to delete mask, if we ahve one..
            if(mask && _mask_alloc) fl_delete_offscreen((Pixmap)mask);
            mask=0;
            need_redraw=true;
        }
        draw_flags &= ~FL_ALIGN_SCALE;
        last_w = last_h = 0;
    }

    //Detect scaling
    if((last_w!=dw || last_h!=dh) && (draw_flags&FL_ALIGN_SCALE) ) {
        need_redraw=true;
        last_w = dw;
        last_h = dh;
    }

    int save_alpha = alpha();
    _mod_data = 0;

    //Detect and change state, if needed
    int F = (f&0x00029000);
    if(_state_effect_all)
    if(_state != F && _state_effect) {
        if(!F) {
            //printf("NORMAL\n\n");
            need_redraw=true;

        } else if((F & FL_SELECTED)==FL_SELECTED) {
            //printf("SELECTED\n\n");
            alpha(60);

            _mod_data = fore_blend(fl_get_color(Fl_Widget::default_style->selection_color));
            if(_mod_data) {
                draw_data = _mod_data->data();
                draw_fmt = Fl_Renderer::system_format();
                need_redraw=true;
            }

        } else if((F & FL_INACTIVE)==FL_INACTIVE) {
            //printf("INACTIVE\n\n");

            alpha(128);

            _mod_data = fore_blend(fl_get_color(FL_GRAY));
            if(_mod_data) {
                draw_data = _mod_data->data();
                draw_fmt = Fl_Renderer::system_format();
                need_redraw=true;
            }
        } else if((F & FL_HIGHLIGHT)==FL_HIGHLIGHT && bitspp()>=16) {
            //printf("HIGHLIGHT\n\n");

            _mod_data = Fl_Image_Filter::apply_to_new(this, 0, FILTER_BRIGHTNESS, 0.2f);
            if(_mod_data) {
                draw_data = _mod_data->data();
                draw_fmt = format();
                need_redraw=true;
            }
        }
        _state = F;
    }
    alpha(save_alpha);

    if(!id || need_redraw)
    {
        if(id) fl_delete_offscreen((Pixmap)id);

        if((draw_flags&FL_ALIGN_SCALE)==FL_ALIGN_SCALE) {
            id = (void *)fl_create_offscreen(dw, dh);

            // Stretching with mask! This very NOT EFFICIENT!
            // This should be should used only when it's absolutely necessary!
            // THIS IS DISABLED! IF SOME APP WANTS TO DO THIS, ITHAS TO IT BY IT SELF!
            if(mask && _mask_alloc) fl_delete_offscreen((Pixmap)mask);
            //mask = (void *)create_mask(dw, dh);
            _mask_alloc = false;//(mask!=0);
            mask=0;

        } else {

            id = (void *)fl_create_offscreen(w, h);
            _id_alloc = true;
            if(!mask) {
                mask = (void *)create_mask(w, h);
                _mask_alloc = (mask!=0);
            }
        }

        fl_begin_offscreen((Pixmap)id);

        Fl_Rect srcr(sx,sy,sw,sh);
        Fl_Rect dstr(0, 0, dw, dh);

        // Check format
        if(check_map(draw_fmt, Fl_Renderer::system_format()))
        {
            // If not on system format, convert it to system fmt
            // This is NOT very efficent, thats why user should convert images to system fmt
            // before draw it!
            uint8 *system_fmt = 0;
            Fl_Size size(w, h);
            system_fmt = Fl_Renderer::system_convert(draw_fmt, &size, draw_data, FL_BLIT_HW_PALETTE);

            //printf("draw %d %d %d %d -> %d %d %d %d\n", sx,sy,sw,sh, dx,dy,dw,dh);

            Fl_Renderer::render_to_pixmap(system_fmt, &srcr, draw_fmt, draw_pitch,
                                          (Pixmap)id, &dstr, fl_gc, draw_flags);
            if(system_fmt) delete []system_fmt;
        } else {

            //Already on system fmt
            Fl_Renderer::render_to_pixmap(draw_data, &srcr, draw_fmt, draw_pitch,
                                          (Pixmap)id, &dstr, fl_gc, draw_flags);
        }
        fl_end_offscreen();
    }

    if(_mod_data) {
        delete _mod_data;
    }

    if(no_screen_) return;

    if((!draw_flags && (f&FL_ALIGN_TILED)!=FL_ALIGN_TILED)
      && (!sx && !sy)) { dw=w; dh=h; }

    if( (f&FL_ALIGN_TILED)==FL_ALIGN_TILED) {
        to_screen_tiled(dx, dy, dw, dh, 0, 0);
    } else {
        to_screen(dx, dy, dw, dh, 0, 0);
    }
}

extern Fl_Image_IO xpm_reader;
extern Fl_Image_IO bmp_reader;
extern Fl_Image_IO gif_reader;

static bool xpm_data=false;

Fl_Image* Fl_Image::read_xpm(const char *filename, const char * const *data)
{	
	xpm_data=true;
	Fl_Image *ret = new Fl_Image();	
	if(ret->read_image(filename, (const uint8 *)data, sizeof(data)))
		return ret;
	delete ret;
	return 0;
}

Fl_Image* Fl_Image::read(const char *filename, const uint8 *data, uint32 data_size)
{	
	xpm_data=false;
	Fl_Image *ret = new Fl_Image();
	if(ret->read_image(filename, data, data_size))
		return ret;
	delete ret;
	return 0;
}

bool Fl_Image::read_image(const char *filename, const char * const *data)
{
	xpm_data=true;	
	return read_image(filename, (const uint8 *)data, sizeof(data));
}

bool Fl_Image::read_image(const char *filename, const uint8 *data, uint32 data_size)
{
    fl_register_imageio(&xpm_reader);
    fl_register_imageio(&bmp_reader);
    fl_register_imageio(&gif_reader);

    clear();

    bool ret = false;
    FILE *fp = 0;

    if(filename && fl_file_exists(filename)) {
        fp = fl_fopen(filename, "rb");
        if(!fp) return ret;
    } else if(!data && data_size<=0) {
        return ret;
    }

    if(xpm_data && !fp) {

        // ONLY XPM DATA READ:
        Fl_Image_IO *r = &xpm_reader;
        if(r->is_valid_xpm && r->read_mem && r->is_valid_xpm((const uint8**)data))
            ret = r->read_mem((uint8*)data, data_size, quality_, _data, fmt, w, h);

    } else {

        for(uint n=0; n<imageio_list.size(); n++) {
            Fl_Image_IO *r = (Fl_Image_IO *)imageio_list[n];
            if(fp) {
                if(r->is_valid_file && r->read_file && r->is_valid_file(filename, fp))
                    ret = r->read_file(fp, 0, _data, fmt, w, h);
            } else {
                if(r->is_valid_mem && r->is_valid_mem(data, data_size))
                    ret = r->read_mem((uint8*)data, data_size, quality_, _data, fmt, w, h);
            }
        }
    }

    if(ret && format()->Amask) {
        // Default mask for images with alpha mask
        mask_type(FL_MASK_ALPHA);
    }

    if(ret && _data) {
        _data_alloc = true;
        _pitch = Fl_Renderer::calc_pitch(bytespp(), width());
    }

    xpm_data=false;
    if(fp) fclose(fp);
    return ret;
}

bool Fl_Image::write_image(const char *filename, const char *io_name)
{
    return write_image(filename, fl_find_imageio(io_name, 0));
}

bool Fl_Image::write_image(const char *filename, Fl_Image_IO *io)
{
    if(!filename || !io || !io->write_file) return false;

    fl_register_imageio(&xpm_reader);
    fl_register_imageio(&bmp_reader);
    fl_register_imageio(&gif_reader);

    FILE *fp = fl_fopen(filename, "wb");
    if(!fp) return false;

    bool ret = io->write_file(fp, quality_, _data, fmt, w, h);

    if(fp) fclose(fp);
    return ret;
}

bool Fl_Image::write_image(uint8 *&data, int &data_size, const char *io_name) 
{
    return write_image(data, data_size, fl_find_imageio(io_name, 0));
}

bool Fl_Image::write_image(uint8 *&data, int &data_size, Fl_Image_IO *io)
{
    if(!io || !io->write_mem) return false;

    fl_register_imageio(&xpm_reader);
    fl_register_imageio(&bmp_reader);
    fl_register_imageio(&gif_reader);

    return io->write_mem(data, data_size, quality_, _data, fmt, w, h);
}


