//
// "$Id$"
//
// Scrolling routines for the Fast Light Tool Kit (FLTK).
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

// Drawing function to move the contents of a rectangle.  This is passed
// a "callback" which is called to draw rectangular areas that are moved
// into the drawing area.

#include <config.h>

#include <efltk/Fl_Window.h>
#include <efltk/x.h>
#include <efltk/fl_draw.h>
#include <efltk/fl_utf8.h>

#ifdef _WIN32

#ifndef SYSRGN
// Missing declaration in old WIN32 API headers.
// However, GDI32.dll exports this function since Windows 95
extern "C" {
	WINGDIAPI int WINAPI GetRandomRgn(
		HDC  hdc,    // handle to DC
		HRGN hrgn,   // handle to region
		INT  iNum    // must be SYSRGN
	);
}
#define SYSRGN 4

#endif /* SYSRGN */

// Return true if rect is completely visible on screen.
bool is_visible(int x, int y, int w, int h) 
{
	// Get visible region of window
	HRGN rgn0 = CreateRectRgn (0, 0, 0, 0);
	GetRandomRgn (fl_gc, rgn0, SYSRGN);

	if(fl_is_nt4()) {
		// Windows 9x operating systems the region is returned in window coordinates, 
		// and on Windows NT machines the region is in screen coordinates.. SIGH!
		POINT pt = { 0, 0 };
		ClientToScreen(fl_xid(Fl_Window::current()), &pt);
		OffsetRgn(rgn0, -pt.x, -pt.y);
	}

	Region rect	= CreateRectRgn(x,y,x+w,y+h);
	Region temp = CreateRectRgn(0,0,0,0);

	bool ret;

	if(CombineRgn(temp, rect, rgn0, RGN_AND) == NULLREGION)
		ret = false;
	else if (EqualRgn(temp, rect)) {
		ret = true;
	} else
		ret = false;

	// Free resources
	DeleteObject(rect);
	DeleteObject(temp);
	DeleteObject(rgn0);
	
	return ret;
}

#endif /* _WIN32 */

// scroll a rectangle and redraw the newly exposed portions:
void fl_scroll(int X, int Y, int W, int H, int dx, int dy,
void (*draw_area)(void*, int,int,int,int), void* data)
{
    if (!dx && !dy) return;
    if (dx <= -W || dx >= W || dy <= -H || dy >= H)
    {
        // no intersection of old an new scroll
        draw_area(data,X,Y,W,H);
        return;
    }
    int src_x, src_w, dest_x, clip_x, clip_w;
    if (dx > 0)
    {
        src_x = X;
        dest_x = X+dx;
        src_w = W-dx;
        clip_x = X;
        clip_w = dx;
    }
    else
    {
        src_x = X-dx;
        dest_x = X;
        src_w = W+dx;
        clip_x = X+src_w;
        clip_w = W-src_w;
    }
    int src_y, src_h, dest_y, clip_y, clip_h;
    if (dy > 0)
    {
        src_y = Y;
        dest_y = Y+dy;
        src_h = H-dy;
        clip_y = Y;
        clip_h = dy;
    }
    else
    {
        src_y = Y-dy;
        dest_y = Y;
        src_h = H+dy;
        clip_y = Y+src_h;
        clip_h = H-src_h;
    }
    int ox = 0; int oy = 0; fl_transform(ox, oy);
#ifdef _WIN32
	if(is_visible(src_x+ox, src_y+oy, src_w, src_h)) {
	    BitBlt(	fl_gc, dest_x+ox, dest_y+oy, src_w, src_h,
				fl_gc, src_x+ox, src_y+oy, SRCCOPY);
	} else {
		draw_area(data, X, Y, W, H);
		return;
	}
#else
    XCopyArea(	fl_display, fl_window, fl_window, fl_gc,
				src_x+ox, src_y+oy, src_w, src_h,
				dest_x+ox, dest_y+oy);
    
	// Synchronous update by waiting for graphics expose events:
    for (;;)
    {
        XEvent e; XWindowEvent(fl_display, fl_window, ExposureMask, &e);
        if (e.type == NoExpose) break;
        // otherwise assumme it is a GraphicsExpose event:
        draw_area(data, e.xexpose.x-ox, e.xexpose.y-oy,
            e.xexpose.width, e.xexpose.height);
        if (!e.xgraphicsexpose.count) break;
    }
#endif
    if (dx) draw_area(data, clip_x, dest_y, clip_w, src_h);
    if (dy) draw_area(data, X, clip_y, W, clip_h);
}

//
// End of "$Id$".
//
