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

#ifndef _FL_DIVIDER_H_
#define _FL_DIVIDER_H_

#include "Fl_Widget.h"

/** Fl_Divider */
class FL_API Fl_Divider : public Fl_Widget {
public:
    Fl_Divider(int x, int y, int w, int h, const char *l=0);
    Fl_Divider(int w, int h);
    Fl_Divider();

    enum {
        HORIZONTAL = RESERVED_TYPE+10,
        VERTICAL   = RESERVED_TYPE+11
    };

    virtual void draw();
};

/** Fl_VertDivider */
class Fl_VertDivider : public Fl_Divider {
public:
    Fl_VertDivider(int x, int y, int w, int h, const char *l) : Fl_Divider(x,y,w,h,l) { type(Fl_Divider::VERTICAL); }
    Fl_VertDivider(int w, int h) : Fl_Divider(w,h) { type(Fl_Divider::VERTICAL); }
    Fl_VertDivider() : Fl_Divider() { type(Fl_Divider::VERTICAL); }
};

/** Fl_Menu_Divider */
class Fl_Menu_Divider : public Fl_Divider {
public:
    Fl_Menu_Divider() : Fl_Divider() { h(2); }
};

#endif
