//
// "$Id$"
//
// Bitmap drawing routines for the Fast Light Tool Kit (FLTK).
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

#include <config.h>

#include <efltk/Fl.h>
#include <efltk/x.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Bitmap.h>

#ifdef _WIN32
Pixmap fl_create_bitmap(const uchar* bitmap, int w, int h)
{
    // we need to pad the lines out to words & swap the bits
    // in each byte.
    int w1 = (w+7)/8;
    int w2 = ((w+15)/16)*2;
    uchar* newarray = new uchar[w2*h];
    const uchar* src = bitmap;
    uchar* dest = newarray;
    Pixmap id;
    // Bit reversal lookup table
    static uchar reverse[16] = {
        0x00, 0x88, 0x44, 0xcc, 0x22, 0xaa, 0x66, 0xee,
        0x11, 0x99, 0x55, 0xdd, 0x33, 0xbb, 0x77, 0xff
    };
    for (int y=0; y < h; y++) {
        for (int n = 0; n < w1; n++, src++)
            *dest++ = (reverse[*src & 0x0f] & 0xf0) |
                (reverse[(*src >> 4) & 0x0f] & 0x0f);
        dest += w2-w1;
    }
    id = CreateBitmap(w, h, 1, 1, newarray);
    delete[] newarray;
    return id;
}
#endif

void Fl_Bitmap::_draw(int dx, int dy, int dw, int dh,
                      int sx, int sy, int sw, int sh,
                      Fl_Flags f)
{
    if(!mask) {
        mask = (void*)fl_create_bitmap(m_data, width(), height());
    }

    if( (f&FL_ALIGN_TILED)==FL_ALIGN_TILED ) {
        to_screen_tiled(dx, dy, dw, dh, 0, 0);
    } else {
        to_screen(dx,dy, width(), height(), 0, 0);
    }
}

//
// End of "$Id$".
//
