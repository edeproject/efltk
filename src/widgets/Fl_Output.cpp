//
// "$Id$"
//
// Output widget for the Fast Light Tool Kit (FLTK).
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
#include <efltk/Fl_Output.h>
#include <efltk/fl_draw.h>

// Output has it's own style so the color can be set to gray like
// some themes want:

static void revert(Fl_Style *s) {
    s->color = FL_GRAY;
    s->button_color = fl_color_average(FL_RED, FL_BLACK, 0.5);
}

static Fl_Named_Style style("Output", revert, &Fl_Output::default_style);
Fl_Named_Style* Fl_Output::default_style = &::style;

// Traditional ctor
Fl_Output::Fl_Output(int x, int y, int w, int h, const char *l)
: Fl_Input(x, y, w, h, l)
{
    style(default_style);
    readonly(1);
}

// New style ctor
Fl_Output::Fl_Output(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Input(l,layout_size,layout_al,label_w)
{
    style(default_style);
    readonly(1);
}

//
// End of "$Id$".
//
