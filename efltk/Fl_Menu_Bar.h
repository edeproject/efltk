//
// "$Id$"
//
// Menu bar header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Menu_Bar_H
#define Fl_Menu_Bar_H

#include "Fl_Widget.h"
#include "Fl_Menu_.h"
#include "Fl_Menu_Window.h"

class Fl_Menu_Bar : public Fl_Menu_ {
public:
    static Fl_Named_Style* default_style;

    Fl_Menu_Bar(int x,int y,int w,int h,const char *l=0);

    int handle(int ev);
    void layout();
    void draw();

    int popup(int X, int Y, int W, int H);

    // This one is layouted to most right of the menubar (often help)
    void right_layout(Fl_Widget *w) { right_ = w; }
    Fl_Widget *right_layout() { return right_; }

    // If this is set to FALSE, then menubar won't layout to many lines when it's too small.
    void layout_menubar(bool val) { do_layout = val; }
    bool layout_menubar() { return do_layout; }

private:
    Fl_Widget *right_;

    int highlight_, last_highlight_;
    int selected_, last_selected_;
    int lines;

    bool do_layout;
};

#endif

//
// End of "$Id$".
//
