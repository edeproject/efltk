//
// "$Id$"
//
// Bitmap header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Bitmap_H
#define Fl_Bitmap_H

#include "Fl_Image.h"

class FL_API Fl_Bitmap : public Fl_Image {
public:
    Fl_Bitmap(const uint8 *bits, int W, int H, bool allow_free=false) : Fl_Image(W, H, 1, (uint8*)bits, allow_free) { }
    Fl_Bitmap(const char  *bits, int W, int H, bool allow_free=false) : Fl_Image(W, H, 1, (uint8*)bits, allow_free) { }

    virtual void draw(int dx, int dy, int dw, int dh,
                      int sx, int sy, int sw, int sh,
                      Fl_Flags f);
    void draw(int x, int y) { draw(x,y,w,h,0,0,0,0,0); }
};

#endif

//
// End of "$Id$".
//
