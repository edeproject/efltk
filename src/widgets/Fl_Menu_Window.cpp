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
#include <efltk/x.h>
#include <efltk/fl_draw.h>
#include <config.h>

#ifdef _WIN32
# include <winsock.h>
#endif

extern bool menu_anim;
extern float menu_speed;

float Fl_Menu_Window::default_step_div = menu_speed;
bool Fl_Menu_Window::animate_ = menu_anim;

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

void Fl_Menu_Window::animate(int fx, int fy, int fw, int fh,
                             int tx, int ty, int tw, int th)
{
#undef max
#define max(a,b) (a) > (b) ? (a) : (b)

    // Make sure that fl_gc is NOT NULL!
    make_current();

    animating=true;

    Pixmap pm = fl_create_offscreen(tw, th);
    fl_begin_offscreen(pm);
    set_damage(FL_DAMAGE_ALL);
    draw();
    fl_end_offscreen();

    Fl_Window::resize(fx,fy,fw,fh);
    Fl_Window::show();
    Fl_Window::layout();
    Fl::check();

    double max_steps = max( (tw-fw), (th-fh) );
    double min_steps = max( (fw-tw), (fh-th) );
    double steps = max(max_steps, min_steps);
	steps/=step_div_;

    double sx = max( ((double)(fx-tx)/steps), ((double)(tx-fx)/steps) );
    double sy = max( ((double)(fy-ty)/steps), ((double)(ty-fy)/steps) );
    double sw = max( ((double)(fw-tw)/steps), ((double)(tw-fw)/steps) );
    double sh = max( ((double)(fh-th)/steps), ((double)(th-fh)/steps) );

    int xinc = fx < tx ? 1 : -1;
    int yinc = fy < ty ? 1 : -1;
    int winc = fw < tw ? 1 : -1;
    int hinc = fh < th ? 1 : -1;
    double rx=fx,ry=fy,rw=fw,rh=fh;
	
	// Make sure we copy to this window!
	make_current();

	timeval t;
    while(steps-- > 0) {

        if(!visible()) {
            break;
        }
        rx+=(sx*xinc);
        ry+=(sy*yinc);
        rw+=(sw*winc);
        rh+=(sh*hinc);

#ifdef _WIN32
		SetWindowPos(fl_xid(this), HWND_TOPMOST, (int)rx, (int)ry, (int)rw, (int)rh, (SWP_SHOWWINDOW|SWP_NOACTIVATE));
		fl_copy_offscreen(0, 0, (int)rw, (int)rh, pm, 0, 0);
		GdiFlush();
#else
        XMoveResizeWindow(fl_display, fl_xid(this), (int)rx, (int)ry, (int)rw, (int)rh);
        XCopyArea(fl_display, pm, fl_xid(this), fl_gc, 0, 0, (int)rw, (int)rh, 0, 0);
        XFlush(fl_display);
#endif
		t.tv_sec = 0;
        t.tv_usec = 1000;
		::select(0,0,0,0, &t);		
	}

    fl_delete_offscreen(pm);

    animating=false;
}


//
// End of "$Id$".
//
