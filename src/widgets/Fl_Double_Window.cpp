//
// "$Id$"
//
// Double-buffered window code for the Fast Light Tool Kit (FLTK).
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

#include <config.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/x.h>
#include <efltk/fl_draw.h>

Fl_Double_Window::Fl_Double_Window(int W, int H, const char *l) 
	: Fl_Window(W,H,l) 
{
}

Fl_Double_Window::Fl_Double_Window(int X, int Y, int W, int H, const char *l)
    : Fl_Window(X,Y,W,H,l) 
{
}

// On systems that support double buffering "naturally" the base
// Fl_Window class will probably do double-buffer and this subclass
// does nothing.

#if USE_XDBE

#include <X11/extensions/Xdbe.h>

static bool use_xdbe;

static bool can_xdbe()
{
    static bool tried;
    if (!tried)
    {
        tried = true;
        int event_base, error_base;
        if (!XdbeQueryExtension(fl_display, &event_base, &error_base)) return 0;
        Drawable root = RootWindow(fl_display,fl_screen);
        int numscreens = 1;
        XdbeScreenVisualInfo *a = XdbeGetVisualInfo(fl_display,&root,&numscreens);
        if (!a) return 0;
        for (int j = 0; j < a->count; j++)
            if (a->visinfo[j].visual == fl_visual->visualid
            )                /*&& a->visinfo[j].perflevel > 0*/
        {
            use_xdbe = true; break;
        }
        XdbeFreeVisualInfo(a);
    }
    return use_xdbe;
}
#endif

void Fl_Double_Window::create()
{
    #ifndef _WIN32
    // don't set the background pixel
    Fl_X::create(this, fl_visual, fl_colormap, -1);
    #else
    Fl_Window::create();
    #endif
}


#ifdef _WIN32
extern void fl_restore_clip();
#endif

void Fl_Double_Window::flush()
{
    flush(0);
    fl_clip_region(0);           // turn off any clip it left on
}


// Update the window but leave the clip region set to the damaged area.
// If eraseoverlay is true then the entire window is updated and the
// clip region is turned off, this is used by Fl_Overlay_Window.
void Fl_Double_Window::flush(bool eraseoverlay)
{
    make_current();              // make sure fl_gc is non-zero
    Fl_X *i = Fl_X::i(this);
    // create the offscreen window:
    if (!i->backbuffer.xid)
    {
#if USE_XDBE
        if (can_xdbe())
            i->backbuffer.xid =
                XdbeAllocateBackBufferName(fl_display, i->xid, XdbeUndefined);
        else
#endif
            i->backbuffer.create(w(), h());
        set_damage(FL_DAMAGE_ALL);
    }

#if USE_XDBE

    bool expose_only = !(damage()&~FL_DAMAGE_EXPOSE);

    // Previous swaps may have left garbage in the back buffer:
    if (i->backbuffer_bad)
    {
        set_damage(FL_DAMAGE_ALL);
        i->backbuffer_bad = false;
    }
    // expose events can damage the back buffer in Xdbe:
    else if (i->region) set_damage(damage() | FL_DAMAGE_EXPOSE);
#endif

    // draw the back buffer if it needs anything:
    if (damage())
    {
        // set the graphics context to draw into back buffer:
        i->backbuffer.make_current();

        // draw all the changed widgets:
        if (damage() & ~FL_DAMAGE_EXPOSE)
        {
            set_damage(damage() & ~FL_DAMAGE_EXPOSE);
            draw();
        }
        // draw for any expose events (if Xdbe is not being used this will
        // only happen for redraw(x,y,w,h) calls):
        if (i->region && !(damage() & FL_DAMAGE_ALL))
        {
            fl_clip_region(i->region); i->region = 0;
            set_damage(FL_DAMAGE_EXPOSE); draw();
            // conditional on next line doesn't work right for
            // keyboard focus drawing on Win32 with double-buffered windows.
            //if (eraseoverlay || !expose_only) fl_clip_region(0);
            fl_clip_region(0);
        }
        // restore the graphics context:
        i->make_current();
#ifdef _WIN32
        fl_restore_clip();       // duplicate region into new gc
#endif
#if USE_XDBE
        // use the faster Xdbe swap command for all normal redraw():
        if (use_xdbe && !eraseoverlay && !expose_only)
        {
            i->backbuffer_bad = true;
            XdbeSwapInfo s;
            s.swap_window = i->xid;
            s.swap_action = XdbeUndefined;
            XdbeSwapBuffers(fl_display, &s, 1);
            return;
        }
#endif
    }
    else if (!eraseoverlay)
    {
        // Clip the copying of the pixmap to the damage area,
        // this makes it faster, especially if the damage area is small:
        fl_clip_region(i->region); i->region = 0;
    }
    // Must be an implementation problem in the server, but on Irix (at least)
    // it is much faster if I clip the rectangle requested down:
    int X,Y,W,H; fl_clip_box(0,0,w(),h(),X,Y,W,H);
    // Copy the backbuffer to the window:
    i->backbuffer.copy(X, Y, W, H, X, Y);
}


void Fl_Double_Window::free_backbuffer()
{
    Fl_X* i = Fl_X::i(this);
    if (i)
    {
#if USE_XDBE
        if (use_xdbe) i->backbuffer.free_gc(); else
#endif
            i->backbuffer.destroy();
    }
}


void Fl_Double_Window::layout()
{
    if (layout_damage() & FL_LAYOUT_WH) free_backbuffer();
    Fl_Window::layout();
}


void Fl_Double_Window::destroy()
{
    free_backbuffer();
    Fl_Window::destroy();
}


Fl_Double_Window::~Fl_Double_Window()
{
    destroy();
}


//
// End of "$Id$".
//
