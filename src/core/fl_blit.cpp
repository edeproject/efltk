#include <efltk/Fl_Renderer.h>

extern Blit_Function get_blit_a(Fl_PixelFormat *srcfmt, Fl_PixelFormat *dstfmt, int flags);

extern Blit_Function get_blit_1(Fl_PixelFormat *srcfmt, Fl_PixelFormat *dstfmt, int flags);
extern Blit_Function get_blit_n(Fl_PixelFormat *srcfmt, Fl_PixelFormat *dstfmt, int flags);

static void BlitCopy(BlitInfo *info)
{
    uint8 *src, *dst;
    int w, h;
    int srcskip, dstskip;

    w = info->d_width*info->dst->bytespp;
    h = info->d_height;
    src = info->s_pixels;
    dst = info->d_pixels;
    srcskip = w+info->s_skip;
    dstskip = w+info->d_skip;
    while ( h-- ) {
        memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}

bool Fl_Renderer::blit(uint8 *src, Fl_Rect *src_rect, Fl_PixelFormat *src_fmt, int src_pitch,
                        uint8 *dst, Fl_Rect *dst_rect, Fl_PixelFormat *dst_fmt, int dst_pitch, int flags)
{
    BlitInfo info;

    info.s_pixels 	= (uint8 *)src + (uint16)src_rect->y() * src_pitch + (uint16)src_rect->x() * src_fmt->bytespp;
    info.s_width  	= src_rect->w();
    info.s_height 	= src_rect->h();
    info.s_skip   	= src_pitch - info.s_width * src_fmt->bytespp;

    info.d_pixels 	= (uint8 *)dst + (uint16)dst_rect->y() * dst_pitch + (uint16)dst_rect->x() * dst_fmt->bytespp;
    info.d_width  	= dst_rect->w();
    info.d_height 	= dst_rect->h();
    info.d_skip   	= dst_pitch - info.d_width * dst_fmt->bytespp;

    info.src = src_fmt;
    info.table = src_fmt->table;
    info.dst = dst_fmt;

    if(flags&HW_PALETTE) info.hw_surface=true;
    else info.hw_surface=false;

    Blit_Function blit_f = 0;

    int index = 0;
    index |= (!!(flags & COLOR_KEY)) << 0;
    if((src_fmt->alpha != 255 || src_fmt->Amask)) {
        index |= 2;
    }

    if(src_fmt->identity && index==0) {
        blit_f = BlitCopy;
    } else {
        switch(src_fmt->bytespp)
        {
        case 1:
            if(info.table) {
                blit_f = get_blit_1(src_fmt, dst_fmt, index);
            }
            break;

        case 2:
        case 3:
        case 4:
            blit_f = get_blit_n(src_fmt, dst_fmt, index);
            break;

        default:
            break;
        }
    }

    if(!blit_f)
        return false;

    blit_f(&info);
    return true;
}

bool Fl_Renderer::alpha_blit(uint8 *src, Fl_Rect *src_rect, Fl_PixelFormat *src_fmt, int src_pitch,
                              uint8 *dst, Fl_Rect *dst_rect, Fl_PixelFormat *dst_fmt, int dst_pitch, int flags)
{
    BlitInfo info;

    info.s_pixels 	= (uint8 *)src + (uint16)src_rect->y() * src_pitch + (uint16)src_rect->x() * src_fmt->bytespp;
    info.s_width  	= src_rect->w();
    info.s_height 	= src_rect->h();
    info.s_skip   	= src_pitch - info.s_width * src_fmt->bytespp;

    info.d_pixels 	= (uint8 *)dst + (uint16)dst_rect->y() * dst_pitch + (uint16)dst_rect->x() * dst_fmt->bytespp;
    info.d_width  	= dst_rect->w();
    info.d_height 	= dst_rect->h();
    info.d_skip   	= dst_pitch - info.d_width * dst_fmt->bytespp;

    info.src = src_fmt;
    info.table = src_fmt->table;
    info.dst = dst_fmt;

    if(flags&HW_PALETTE) info.hw_surface=true;
    else info.hw_surface=false;

    int index = 0;
    index |= (flags & COLOR_KEY) ? 1 : 0;

    Blit_Function blit_f = 0;

    if(src_fmt->identity && index==0) {
        blit_f = BlitCopy;
    } else {
        switch(src_fmt->bytespp)
        {
        case 1:
            if(info.table)
                blit_f = get_blit_1(src_fmt, dst_fmt, index);
            break;

        case 2:
        case 3:
        case 4:
            blit_f = get_blit_a(src_fmt, dst_fmt, flags);
            break;

        default:
            break;
        }
    }

    if(!blit_f)
        return false;

    // Perform blit!
    blit_f(&info);

    return true;
}


