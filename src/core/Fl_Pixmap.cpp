//
// "$Id$"
//
// Pixmap drawing code for the Fast Light Tool Kit (FLTK).
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

#include <efltk/Fl_Pixmap.h>
#include <efltk/fl_draw.h>

void Fl_Pixmap::measure(int &w, int &h)
{
    if(!fl_measure_pixmap(data, w, h)) {
        w = h = 0;
    }
}

void Fl_Pixmap::draw(int dx, int dy, int dw, int dh,
                     int sx, int sy, int sw, int sh,
                     Fl_Flags f)
{
    if(!id) {
        read_image(0, data);
    }
    Fl_Image::draw(dx, dy, dw, dh, sx, sy, sw, sh, f);
}

//
// End of "$Id$".
//
