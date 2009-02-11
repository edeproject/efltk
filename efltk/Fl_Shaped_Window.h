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

#ifndef _FL_SHAPED_WINDOW_H_
#define _FL_SHAPED_WINDOW_H_

#include "Fl_Double_Window.h"
#include "Fl_Bitmap.h"

/** Fl_Shaped_Window */
class FL_API Fl_Shaped_Window : public Fl_Double_Window {
public:
    Fl_Shaped_Window(int W, int H, const char *l = 0) : Fl_Double_Window(W,H,l) { shape_ = 0; lw = lh = 0; changed = 0; }
    Fl_Shaped_Window(int X, int Y, int W, int H, const char *l = 0) : Fl_Double_Window(X,Y,W,H,l) { shape_ = 0; lw = lh = 0; }

    void shape(Fl_Bitmap* b) { shape_ = b; changed = 1; }
    void shape(Fl_Bitmap& b) { shape(&b); }

    virtual void draw();

protected:
    Fl_Bitmap* shape_;
    int lw, lh;
    int changed;
};

#endif
