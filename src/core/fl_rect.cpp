//
// "$Id$"
//
// Non-path routines from fl_draw.h that are used by the standard boxtypes
// and thus are always linked into an fltk program.
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

#include "fl_internal.h"

#include <efltk/fl_draw.h>
#include <efltk/x.h>

void Fl_Device::rect(int x, int y, int w, int h)
{
    if (w<=0 || h<=0) return;
    fl_transform(x,y);
#ifdef _WIN32
	fl_set_cosmetic_pen();

	w--; h--;
	fl_line_drawer.move(x,y);
	fl_line_drawer.line(x+w, y);
    fl_line_drawer.line(x+w, y+h);
    fl_line_drawer.line(x, y+h);
    fl_line_drawer.line(x, y);
#else
    XDrawRectangle(fl_display, fl_window, fl_gc, x, y, w-1, h-1);
#endif
}

void Fl_Device::rectf(int x, int y, int w, int h)
{
    if (w<=0 || h<=0) return;
    fl_transform(x,y);
#ifdef _WIN32
    RECT rect;
    rect.left = x; rect.top = y;
    rect.right = x + w; rect.bottom = y + h;
#if 1 
     // From the MFC CDC class, apparently this is faster: 
     SetBkColor(fl_gc, fl_colorref); 
     ExtTextOut(fl_gc, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL); 
#else 
     FillRect(fl_gc, &rect, fl_brush()); 
#endif 

#else
    XFillRectangle(fl_display, fl_window, fl_gc, x, y, w, h);
#endif
}

#ifdef _WIN32
void Fl_Device::rectf(int x, int y, int w, int h, Fl_Color C)
{
    fl_color(C);
    fl_rectf(x,y,w,h);
}
#endif

void Fl_Device::line(int x, int y, int x1, int y1)
{
    fl_transform(x,y);
    fl_transform(x1,y1);
#ifdef _WIN32	
	fl_set_cosmetic_pen();
	fl_line_drawer.move(x, y);
	fl_line_drawer.line(x1, y1);
#else
    XDrawLine(fl_display, fl_window, fl_gc, x, y, x1, y1);
#endif
}


void Fl_Device::point(int x, int y)
{
    fl_transform(x,y);
#ifdef _WIN32
    SetPixel(fl_gc, x, y, fl_colorref);
#else
    XDrawPoint(fl_display, fl_window, fl_gc, x, y);
#endif
}


//
// End of "$Id$".
//
