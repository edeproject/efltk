//
// "$Id$"
//
// Widget to draw a divider line in a menu
//
// Copyright 1998-2000 by Bill Spitzak and others.
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

#ifndef Fl_Divider_H
#define Fl_Divider_H

#ifndef Fl_Widget_H
#include "Fl_Widget.h"
#endif

class FL_API Fl_Divider : public Fl_Widget {
public:
    enum {
        HORIZONTAL = RESERVED_TYPE+10,
        VERTICAL   = RESERVED_TYPE+11
    };

    Fl_Divider(int x, int y, int w, int h, const char *l=0);
    Fl_Divider(int w, int h);
    Fl_Divider();
    void draw();
};

class Fl_VertDivider : public Fl_Divider {
public:
    Fl_VertDivider(int x, int y, int w, int h, const char *l) : Fl_Divider(x,y,w,h,l) { type(Fl_Divider::VERTICAL); }
    Fl_VertDivider(int w, int h) : Fl_Divider(w,h) { type(Fl_Divider::VERTICAL); }
    Fl_VertDivider() : Fl_Divider() { type(Fl_Divider::VERTICAL); }
};

#endif
