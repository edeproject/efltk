//
// "$Id$"
//
// Highlight button widget for the Fast Light Tool Kit (FLTK).
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
#include <efltk/Fl_Highlight_Button.h>

static void revert(Fl_Style* s)
{
    s->color = FL_GRAY;
    s->box = FL_HIGHLIGHT_BOX;
    s->highlight_color = FL_LIGHT1;
}


static Fl_Named_Style style("Highlight_Button", revert, &Fl_Highlight_Button::default_style);
Fl_Named_Style* Fl_Highlight_Button::default_style = &::style;

// Traditional ctor
Fl_Highlight_Button::Fl_Highlight_Button(int x,int y,int w,int h,const char *l)
: Fl_Button(x,y,w,h,l)
{
    style(default_style);
}

// New style ctor
Fl_Highlight_Button::Fl_Highlight_Button(const char* l,int layout_size,Fl_Align layout_al)
: Fl_Button(l,layout_size,layout_al)
{
    style(default_style);
}

//
// End of "$Id$".
//
