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

// An Fl_Image that draws inline XPM data.

// See fl_draw_pixmap.C for code used to get the actual data into pixmap.
// Implemented without using the xpm library (which I can't use because
// it interferes with the color cube used by fl_draw_image).

#include <efltk/Fl.h>
#include <efltk/fl_draw.h>
#include <efltk/x.h>
#include <efltk/Fl_Pixmap.h>

void Fl_Pixmap::measure(int& W,int& H) {
    if(w < 0) fl_measure_pixmap(data, w, h);
    W=w;
    H=h;
}

extern ImageReader xpm_reader;
void Fl_Pixmap::draw(int X, int Y, int W, int H, Fl_Flags flags)
{
    if(!id && xpm_reader.is_valid_xpm((void**)data)) {
        Fl_Image *i = Fl_Image::read_xpm(0, (const char **)data);
        if(i) {
            copy(*i, *this);
            delete i;
        }
    }

    Fl_Image::draw(X,Y,W,H,0,0,w,h,flags);
}

//
// End of "$Id$".
//
