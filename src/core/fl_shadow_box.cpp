//
// "$Id$"
//
// Shadow box drawing routines for the Fast Light Tool Kit (FLTK).
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

#include <efltk/Fl_Boxtype.h>
#include <efltk/fl_draw.h>

#define BW 3

void Fl_Shadow_Box::draw(
int x, int y, int w, int h, Fl_Color color, Fl_Flags f) const
{
    w-=BW; h-=BW;
    if (!(f & FL_INVISIBLE))
    {
        fl_color(color);
        fl_rectf(x+1,y+1,w-2,h-2);
    }
    fl_color(FL_DARK3);
    fl_rectf(x+BW, y+h,  w, BW);
    fl_rectf(x+w,  y+BW, BW,  h);
    fl_color(fl_inactive(FL_BLACK,f));
    fl_rect(x,y,w,h);
}


Fl_Shadow_Box::Fl_Shadow_Box(const char* n) : Fl_Boxtype_(n)
{
    dx_ = dy_ = 1; dw_ = dh_ = 2+BW;
    fills_rectangle_ = 0;
}


const Fl_Shadow_Box fl_shadow_box("shadow");

//
// End of "$Id$".
//
