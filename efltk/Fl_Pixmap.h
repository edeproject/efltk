//
// "$Id$"
//
// Pixmap header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Pixmap_H
#define Fl_Pixmap_H

#include "Fl_Image.h"

/*
 * Fl_Pixmap is good for static XPM's
 * like built-in images, It parses image only
 * when it's needed. i.e. just before first draw.
 * This allows applications run w/o X11 running. (e.g. efluid -c)
 */

class FL_API Fl_Pixmap : public Fl_Image
{
public:
    const char * const * data; //XPM data

    Fl_Pixmap(char * const *d) : Fl_Image() { data = (const char **)d; measure(w,h); }
    Fl_Pixmap(uchar* const *d) : Fl_Image() { data = (const char **)d; measure(w,h); }
    Fl_Pixmap(const char * const *d) : Fl_Image() { data = (const char **)d; measure(w,h); }
    Fl_Pixmap(const uchar* const *d) : Fl_Image() { data = (const char **)d; measure(w,h); }
    virtual ~Fl_Pixmap() { }

    virtual void measure(int &w, int &h);
    virtual void draw(int dx, int dy, int dw, int dh,
                      int sx, int sy, int sw, int sh,
                      Fl_Flags f);
};

#endif

//
// End of "$Id$".
//
