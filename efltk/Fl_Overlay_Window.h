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

#ifndef _FL_OVERLAY_WINDOW_H_
#define _FL_OVERLAY_WINDOW_H_

#include "Fl_Double_Window.h"

/** Fl_Overlay_Window */
class FL_API Fl_Overlay_Window : public Fl_Double_Window {
public:
    Fl_Overlay_Window(int W, int H, const char *l=0) : Fl_Double_Window(W,H,l) { overlay_ = 0; }
    Fl_Overlay_Window(int X, int Y, int W, int H, const char *l=0) : Fl_Double_Window(X,Y,W,H,l) { overlay_ = 0; }

    int can_do_overlay();
    void redraw_overlay();

    virtual void draw_overlay() = 0;
    virtual void layout();

protected:
    virtual void flush();

private:
    friend class _Fl_Overlay;
    Fl_Window* overlay_;
};

#endif
