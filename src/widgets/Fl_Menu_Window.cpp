//
// "$Id$"
//
// Menu window code for the Fast Light Tool Kit (FLTK).
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

#include <efltk/Fl.h>
#include <efltk/Fl_Menu_Window.h>
#include <efltk/Fl_Menu_.h>
#include <efltk/math.h>
#include <efltk/x.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Util.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Renderer.h>

#include <config.h>
#include <stdio.h>

#ifdef _WIN32
# include <winsock.h>
#else
# include <unistd.h>
# define Sleep(x) {\
        timeval t; \
        t.tv_sec = 0; \
        t.tv_usec = 1000*(x); \
        ::select(1,0,0,0,&t); }
#endif

Fl_Menu_Window::Fl_Menu_Window(int W, int H, const char *l)
    : Fl_Single_Window(W,H,l)
{
    animating=false;
    anim_speed_=Fl_Menu_::default_anim_speed();
    slow_down_to_h=0;
    slow_down_to_w=0;
}

Fl_Menu_Window::Fl_Menu_Window(int X, int Y, int W, int H, const char *l)
: Fl_Single_Window(X,Y,W,H,l)
{
    animating=false;
    anim_speed_=Fl_Menu_::default_anim_speed();
    slow_down_to_h=0;
    slow_down_to_w=0;
}


// This is the window type used by Fl_Menu to make the pop-ups, and for
// tooltip popups.
//
// It used to draw in the overlay planes if possible. Because xft does
// not work in overlays this has been disabled except on Irix (where
// overlays are still faster and save-under does not work):

#if USE_OVERLAY && !defined(__sgi)
#undef USE_OVERLAY
#define USE_OVERLAY 0
#endif

// _WIN32 note: USE_OVERLAY is false
#if USE_OVERLAY
extern XVisualInfo *fl_find_overlay_visual();
extern XVisualInfo *fl_overlay_visual;
extern Colormap fl_overlay_colormap;
extern unsigned long fl_transparent_pixel;
static GC gc;                    // the GC used by all X windows
extern uchar fl_overlay;         // changes how fl_color(x) works
#endif

void Fl_Menu_Window::create()
{
#if USE_OVERLAY
    if (overlay() && fl_find_overlay_visual())
    {
        XInstallColormap(fl_display, fl_overlay_colormap);
        Fl_X::create(this, fl_overlay_visual, fl_overlay_colormap, int(fl_transparent_pixel));
    } else
#endif
        Fl_Single_Window::create();
}


void Fl_Menu_Window::flush()
{
#if USE_OVERLAY
    if (!fl_overlay_visual || !overlay()) {Fl_Single_Window::flush(); return;}
    Fl_X *i = Fl_X::i(this);
    fl_window = i->xid;
    if (!gc) gc = XCreateGC(fl_display, i->xid, 0, 0);
    fl_gc = gc;
    fl_overlay = 1;
    current_ = this;
    bool expose =
        (damage() & FL_DAMAGE_EXPOSE) && !(damage() & FL_DAMAGE_ALL);
    if (expose) set_damage(damage() & ~FL_DAMAGE_EXPOSE);
    if (damage()) draw();
    if (expose)
    {
        fl_clip_region(i->region); i->region = 0;
        set_damage(FL_DAMAGE_EXPOSE); draw();
        fl_clip_region(0);
    }
    fl_overlay = 0;
#else
    Fl_Single_Window::flush();
#endif
}

void Fl_Menu_Window::destroy()
{
#if USE_OVERLAY
    // Fix the colormap flashing on Maximum Impact Graphics by erasing the
    // menu before unmapping it:
    if (gc && shown()) XClearWindow(fl_display, fl_xid(this));
#endif
    Fl_Single_Window::destroy();
}


Fl_Menu_Window::~Fl_Menu_Window()
{
    destroy();
}


void Fl_Menu_Window::layout()
{
#ifdef _WIN32
    if(shown())
        SetWindowPos(fl_xid(this), HWND_TOPMOST, x(), y(), w(), h(), (SWP_NOSENDCHANGING | SWP_NOACTIVATE));
    Fl_Group::layout();
#else
    Fl_Window::layout();
#endif
}

// Fade effect, blend to opacity (thats NYI)
void Fl_Menu_Window::fade(int x, int y, int w, int h, uchar opacity)
{
	Fl_Renderer::system_init();

    int ow=w, oh=h; // original W&H
    int cx=0, cy=0; // copy points from offscreen pixmap

    // Clip xywh to fit screen
    if(x<0) { cx=-x; w+=x; x=0; }
    if(y<0) { cy=-y; h+=y; y=0; }
    if(x+w>Fl::w()) w -= (x+w)-Fl::w();
    if(y+h>Fl::h()) h -= (y+h)-Fl::h();

    int bpp=0;

    Fl_Rect screen_rect(x, y, w, h);
    uint8 *screen_data = Fl_Renderer::data_from_window(Fl_Renderer::root_window(), screen_rect, bpp);
    int screen_pitch = Fl_Renderer::calc_pitch(Fl_Renderer::system_format()->bytespp, w);
    if(!screen_data) {
        //printf("data_from_window(1) FAILED\n");
        return;
    }

    // Make sure that fl_gc is NOT NULL!
    make_current();

    Pixmap pm = fl_create_offscreen(ow, oh);
    fl_begin_offscreen(pm);
    set_damage(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE);
    draw();
    fl_end_offscreen();

    Fl_Window::show();

    animating=true;

    Fl_Rect window_rect(0,0,ow,oh);
    uint8 *window_data = Fl_Renderer::data_from_pixmap(pm, window_rect, bpp);
    if(!window_data) {
        delete []screen_data;
        //printf("data_from_pixmap(2) FAILED\n");
        animating=false;
        return;
    }    

    int window_pitch = Fl_Renderer::calc_pitch(Fl_Renderer::system_format()->bytespp, ow);

    Fl_PixelFormat fmt;
    fmt.copy(Fl_Renderer::system_format());
    fmt.map_this(Fl_Renderer::system_format());

#ifdef _WIN32
    SetWindowPos(fl_xid(this), HWND_TOPMOST, x, y, w, h, (SWP_NOSENDCHANGING | SWP_NOACTIVATE));
#else
    XMoveResizeWindow(fl_display, fl_xid(this), x, y, w, h);
#endif

    Fl_Rect src_rect(cx,cy,w,h);
    Fl_Rect dst_rect(0,0,w,h);

    int step = 8;
    if(anim_speed()>0) { step=int(floor((step*anim_speed())+.5f)); }
    int alpha=50; //start from alpha value 50...
    bool error=false;
    opacity = 150;
    while(!error && alpha<opacity)
    {
        Fl::check();

        if(!animating || !shown() || !visible()) {
            break;
        }

        fmt.alpha = alpha;
        alpha+=step;

        if(Fl_Renderer::alpha_blit(window_data, &src_rect, &fmt, window_pitch,
                                   screen_data, &dst_rect, Fl_Renderer::system_format(), screen_pitch, 0))
        {
            make_current();
            if(!Fl_Renderer::render_to_pixmap(screen_data, &dst_rect, Fl_Renderer::system_format(), screen_pitch,
                                              (Pixmap)fl_xid(this), &dst_rect, fl_gc, 0))
                error=true;
        } else
            error=true;

        Sleep(15);
    }

    delete []screen_data;
    delete []window_data;

    /*if(opacity==255)*/
    {
#ifdef _WIN32
        make_current();
        fl_copy_offscreen(0, 0, w, h, pm, 0, 0);
#else
        XCopyArea(fl_display, pm, fl_xid(this), fl_gc, 0, 0, w, h, 0, 0);
#endif
    }

    animating=false;
    fl_delete_offscreen(pm);
}

void Fl_Menu_Window::animate(int fx, int fy, int fw, int fh,
                             int tx, int ty, int tw, int th)
{
#undef max
#define max(a,b) (a) > (b) ? (a) : (b)

    // Make sure that fl_gc is NOT NULL!
    make_current();

    Pixmap pm = fl_create_offscreen(tw, th);
    fl_begin_offscreen(pm);
    set_damage(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE);
    draw();
    fl_end_offscreen();

    Fl_Window::resize(fx,fy,fw,fh);
    Fl_Window::show();

    animating=true;

    float max_steps = max( (tw-fw), (th-fh) );
    float min_steps = max( (fw-tw), (fh-th) );
    float steps = max(max_steps, min_steps);
    if(anim_speed()>0) {
        steps/=anim_speed();
    }

    float sx = max( ((float)(fx-tx)/steps), ((float)(tx-fx)/steps) );
    float sy = max( ((float)(fy-ty)/steps), ((float)(ty-fy)/steps) );
    float sw = max( ((float)(fw-tw)/steps), ((float)(tw-fw)/steps) );
    float sh = max( ((float)(fh-th)/steps), ((float)(th-fh)/steps) );

    int xinc = fx < tx ? 1 : -1;
    int yinc = fy < ty ? 1 : -1;
    int winc = fw < tw ? 1 : -1;
    int hinc = fh < th ? 1 : -1;
    float rx=fx,ry=fy,rw=fw,rh=fh;

    int X=fx,Y=fy,W=fw,H=fh;
    int ox=fx,oy=fy,ow=fw,oh=fh;

    while(steps-- > 0) {

        if(!animating || !shown() || !visible()) {
            break;
        }

        rx+=(sx*xinc);
        ry+=(sy*yinc);
        rw+=(sw*winc);
        rh+=(sh*hinc);

        X=(int)rx;
        Y=(int)ry;
        W=(int)rw;
        H=(int)rh;

        if(X!=ox || Y!=oy || W!=ow || H!=oh) {
            // Make drop down slower at begining
            if((slow_down_to_h<0 || H<slow_down_to_h) ||
               (slow_down_to_w<0 || W<slow_down_to_w))
                Sleep(1);
            // Make sure we copy to this window!
            make_current();
#ifdef _WIN32
            make_current();
            SetWindowPos(fl_xid(this), HWND_TOPMOST, X, Y, W, H, (SWP_NOSENDCHANGING | SWP_NOACTIVATE));
            fl_copy_offscreen(0, 0, W, H, pm, tw-W, th-H);

            // Flush the GDI
            GdiFlush();
#else
            XMoveResizeWindow(fl_display, fl_xid(this), X, Y, W, H);
            fl_copy_offscreen(0, 0, W, H, pm, tw-W, th-H);
            //XCopyArea(fl_display, pm, fl_xid(this), fl_gc, 0, 0, W, H, tw-W, th-H); //This is a bit too fast :)) If we use this we dont need to call make_current()
            XFlush(fl_display);
#endif
            Fl::check();
        }

        ox=X;
        oy=Y;
        ow=W;
        oh=H;
    }

    fl_delete_offscreen(pm);

    animating=false;
}


//
// End of "$Id$".
//
