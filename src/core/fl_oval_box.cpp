//
// "$Id$"
//
// Oval box drawing code for the Fast Light Tool Kit (FLTK).
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

// Less-used box types are in seperate files so they are not linked
// in if not used.

#include <efltk/Fl_Boxtype.h>
#include <efltk/fl_draw.h>

void Fl_Oval_Flat_Box::draw(int x, int y, int w, int h, Fl_Color color, Fl_Flags) const
{
    fl_ellipse(float(x), float(y), float(w-1), float(h-1));
    fl_color(color);
    fl_fill();
}


Fl_Oval_Flat_Box::Fl_Oval_Flat_Box(const char* n) : Fl_Boxtype_(n)
{
    dx_ = dy_ = dw_ = dh_ = 0;
    fills_rectangle_ = 0;
}


const Fl_Oval_Flat_Box fl_oval_flat_box("oval flat");

void Fl_Oval_Box::draw(int x, int y, int w, int h, Fl_Color color, Fl_Flags f) const
{
    fl_ellipse(float(x), float(y), float(w-1), float(h-1));
    fl_color(color);
    fl_fill_stroke(fl_inactive(FL_BLACK,f));
}


Fl_Oval_Box::Fl_Oval_Box(const char* n) : Fl_Boxtype_(n)
{
    dx_ = dy_ = 1; dw_ = dh_ = 2;
    fills_rectangle_ = 0;
}


const Fl_Oval_Box fl_oval_box("oval");

void Fl_Oval_Shadow_Box::draw(int x, int y, int w, int h, Fl_Color color, Fl_Flags f) const
{
    w-=3; h-=3;
    fl_ellipse(float(x+3), float(y+3), float(w), float(h));
    fl_color(FL_DARK3);
    fl_fill();
    fl_oval_box.draw(x, y, w, h, color, f);
}


Fl_Oval_Shadow_Box::Fl_Oval_Shadow_Box(const char* n) : Fl_Boxtype_(n)
{
    dx_ = dy_ = 1; dw_ = dh_ = 5;
    fills_rectangle_ = 0;
}


const Fl_Oval_Shadow_Box fl_oval_shadow_box("oval shadow");

//
// End of "$Id$".
//
