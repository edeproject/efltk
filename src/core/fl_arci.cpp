//
// "$Id$"
//
// Arc (integer) drawing functions for the Fast Light Tool Kit (FLTK).
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

// Draw pie slices, chord shapes, and curved lines, using the facilities
// of X or Windows instead of the line segment drawing that fl_arc(...)
// uses.  These draw the limited
// circle types provided by X and NT graphics.  The advantage of
// these is that small ones draw quite nicely (probably due to stored
// hand-drawn bitmaps of small circles!) and may be implemented by
// hardware and thus are fast.
// This is merged into a single function to make writing a dispatch
// table easier.

#ifdef _WIN32
#include <efltk/fl_math.h>
#endif

#include <config.h>

#include <efltk/fl_draw.h>
#include <efltk/x.h>

void Fl_Device::pie(int x,int y,int w,int h,float a1,float a2, int what) 
{
	if (w <= 0 || h <= 0) return;
	fl_transform(x,y);
#ifndef _WIN32_WCE
#ifdef _WIN32
	if (a1 == a2) return;
	w++; h++; // is this needed to match X?
	int xa = x+w/2+int(w*cosf(a1*float(M_PI/180.0)));
	int ya = y+h/2-int(h*sinf(a1*float(M_PI/180.0)));
	int xb = x+w/2+int(w*cosf(a2*float(M_PI/180.0)));
	int yb = y+h/2-int(h*sinf(a2*float(M_PI/180.0)));
	fl_set_geometric_pen();
	switch (what) {
	case FL_PIE:
		fl_setbrush();
		Pie(fl_gc, x, y, x+w, y+h, xa, ya, xb, yb); 
		break;
	case FL_CHORD:
		fl_setbrush();
		Chord(fl_gc, x, y, x+w, y+h, xa, ya, xb, yb); 
		break;
	case FL_ARC:
		Arc(fl_gc, x, y, x+w, y+h, xa, ya, xb, yb);
		break;
	}
#else
	int A = int(a1*64);
	int B = int(a2*64)-A;
	switch(what) {
	case FL_PIE:
		XSetArcMode(fl_display, fl_gc, ArcPieSlice);
		goto J1;
	case FL_CHORD:
		XSetArcMode(fl_display, fl_gc, ArcChord);
J1:
		XFillArc(fl_display, fl_window, fl_gc, x, y, w, h, A, B);
		break;
	case FL_ARC:
		XDrawArc(fl_display, fl_window, fl_gc, x, y, w, h, A, B);
		break;
	}
#endif
#endif //WCE
}

//
// End of "$Id$".
//
