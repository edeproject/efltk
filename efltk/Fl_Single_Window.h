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

#ifndef _FL_SINGLE_WINDOW_H_
#define _FL_SINGLE_WINDOW_H_

#include "Fl_Window.h"

/** Fl_Single_Window */
class FL_API Fl_Single_Window : public Fl_Window {
public:
    Fl_Single_Window(int W, int H, const char *l=0) : Fl_Window(W,H,l) { }
    Fl_Single_Window(int X, int Y, int W, int H, const char *l=0) : Fl_Window(X,Y,W,H,l) { }
};

#endif
