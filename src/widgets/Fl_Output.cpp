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

bool Fl_Output::replace(int, int, const char*, int)
{
    // By making this function return false, all editing is disallowed:
    return false;
}


int Fl_Output::handle(int event)
{
    // The Fl_Input may grab the focus if sent a shortcut, prevent this:
    if (event == FL_SHORTCUT) return 0;
    // You can't drag&drop on it either:
    if (event == FL_DND_ENTER) return 0;
    // Don't return 3 for FL_FOCUS, return 1 instead:
    return Fl_Input::handle(event)&1;
}


// Output has it's own style so the color can be set to gray like
// some themes want:
static Fl_Named_Style style("Output", 0, &Fl_Output::default_style);
Fl_Named_Style* Fl_Output::default_style = &::style;

Fl_Output::Fl_Output(int x, int y, int w, int h, const char *l)
: Fl_Input(x, y, w, h, l)
{
    style(default_style);
}


//
// End of "$Id$".
//
