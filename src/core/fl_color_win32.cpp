//
// "$Id$"
//
// _WIN32 color functions for the Fast Light Tool Kit (FLTK).
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

// This file does not compile independently, it is included by fl_color.cxx

#include "fl_internal.h"

#include <efltk/win32.h>
#include <efltk/fl_utf8.h>
#include <efltk/fl_math.h>

#include <stdio.h>

Fl_Line_Drawer fl_line_drawer;

#ifdef _WIN32_WINNT
 #if _WIN32_WINNT >= 0x0500
  #define _USE_FAST_BRUSH_
 #endif
#endif

// The current color:
Fl_Color fl_color_	= 0;
COLORREF fl_colorref= 0;
HPALETTE fl_palette = 0;
HBRUSH   fl_brush	= 0;

HPEN     fl_pen		= 0; // "geometric" pen
HPEN     fl_cosm_pen= 0; // "cosmetic" pen

// Current brush is created with this color and DC
static COLORREF	brush_colorref;
static HDC brush_dc;

// Current "geometric" pen is created with this color
static COLORREF	pen_colorref;

// Current "cosmetic" pen is created with this color
static COLORREF	cosm_pen_colorref;

COLORREF fl_wincolor(Fl_Color i) 
{
	int index = i;
	COLORREF rgb;
	// this is the same as nearest_color(i) but it also sets rgb:
	if (i & 0xffffff00) { // an rgb color
		uchar r = i>>24;
		uchar g = i>>16;
		uchar b = i>> 8;
		rgb = RGB(r,g,b);
		//if (r == g && r == b) index = GRAY00+r*(GRAY99-GRAY00)/256;
		index = (FL_BLACK + (b*5/256 * 5 + r*5/256) * 8 + g*8/256);
	} else {
		unsigned c = fl_cmap[i];
		rgb = RGB(uchar(c>>24), uchar(c>>16), uchar(c>>8));
	}
#if USE_COLORMAP
	if (fl_palette) rgb = PALETTEINDEX(index);
#endif
	return rgb;
}

static bool styled   = false;	// Do we have styled line selected
static int cap_style = 0;		// ENDCAP style
static int pen_style = 0;		// PEN style

static DWORD dash_pattern[16];	//User defined dash pattern
static int dash_pattern_size = 0; //Number of patterns
static int line_width = 1;		// Line width

void Fl_Device::line_style(int style, int width, char* dashes) 
{
#ifndef _WIN32_WCE
	static DWORD Cap[4]  = {
		PS_ENDCAP_ROUND, 
		PS_ENDCAP_FLAT, 
		PS_ENDCAP_ROUND, 
		PS_ENDCAP_SQUARE
	};
	static DWORD Join[4] = {
		PS_JOIN_ROUND, 
		PS_JOIN_MITER, 
		PS_JOIN_ROUND, 
		PS_JOIN_BEVEL
	};

	cap_style = Cap[(style>>8)&3] | Join[(style>>12)&3];

	if (dashes && dashes[0]) {
		pen_style = PS_USERSTYLE;		
		int n; for (n = 0; n < 16 && *dashes;) dash_pattern[n++] = *dashes++;
		dash_pattern_size = n;
	} else {
		dash_pattern_size = 0;
		// allow any low 8 bits for style
		pen_style = (style & 0xff);
	}

	// for some reason zero width does not work at all:
	if(width<=0) width = 1;
	line_width = (width > 0 ? width : 1);

	styled = (cap_style || pen_style);

	// Reset pens
	if (fl_pen) { DeleteObject(fl_pen); fl_pen = 0; }
	if (fl_cosm_pen) { DeleteObject(fl_cosm_pen); fl_cosm_pen = 0; }
#endif
}

#ifdef _USE_FAST_BRUSH_
// Stock objects for "fast brush"
static HPEN stockpen		= (HPEN)GetStockObject(DC_PEN);
static HBRUSH stockbrush	= (HBRUSH)GetStockObject(DC_BRUSH);
#endif

HPEN fl_set_geometric_pen() 
{
#ifdef _USE_FAST_BRUSH_
	if(!styled && line_width <= 1) {
		SelectObject(fl_gc, stockpen);
		SetDCPenColor(fl_gc, fl_colorref);
		return stockpen;
	}
#endif
	bool need_select = false;
	if(!fl_pen || pen_colorref != fl_colorref) 
	{
		if(styled) {			
			LOGBRUSH penbrush = { BS_SOLID, fl_colorref, 0 };
			fl_pen = ExtCreatePen(pen_style | cap_style | PS_GEOMETRIC, line_width, &penbrush,
   	 							dash_pattern_size, dash_pattern_size?dash_pattern:0);
		} else {
			fl_pen = CreatePen(PS_SOLID, line_width, fl_colorref);
		}
		pen_colorref = fl_colorref;
		need_select = true;
	}

	if(need_select) {
		HPEN oldp = (HPEN)SelectObject(fl_gc, fl_pen);
		DeleteObject(oldp);
		// Delete cosmetic pen
		if (fl_cosm_pen) { DeleteObject(fl_cosm_pen); fl_cosm_pen = 0; }
	}
	return fl_pen;
}

HPEN fl_set_cosmetic_pen()
{
#ifdef _USE_FAST_BRUSH_
	if(!styled && line_width <= 1) {
		SelectObject(fl_gc, stockpen);
		SetDCPenColor(fl_gc, fl_colorref);
		return stockpen;
	}
#endif
	bool need_select = false;
	if(!fl_cosm_pen || cosm_pen_colorref != fl_colorref) 
	{
		LOGBRUSH penbrush = { BS_SOLID, fl_colorref, 0 };
		if(line_width<2) {
			// We can use cosmetic pen, since line_width is <2
			fl_cosm_pen = ExtCreatePen(PS_SOLID | cap_style | PS_COSMETIC, line_width, &penbrush, 0,0);
		} else {			
			// Pen must be geometric, if line_width>1			
			fl_cosm_pen = ExtCreatePen(PS_SOLID | cap_style | PS_GEOMETRIC, line_width, &penbrush, 0,0);					
		}

		fl_line_drawer.set_pattern(line_width, dash_pattern_size ? dash_pattern : 0, dash_pattern_size);

		cosm_pen_colorref = fl_colorref;
		need_select = true;
	}	

	if(need_select) {
		HPEN oldp = (HPEN)SelectObject(fl_gc, fl_cosm_pen);
		DeleteObject(oldp);
		// Delete geometric pen
		if(fl_pen) { DeleteObject(fl_pen); fl_pen = 0; }
	}
	return fl_cosm_pen;
}

HBRUSH fl_setbrush()
{
#ifdef _USE_FAST_BRUSH_
	SelectObject(fl_gc, stockbrush);
	SetDCBrushColor(fl_gc, fl_colorref);
	fl_brush = stockbrush;
#else
	bool need_select = false;
    if(!fl_brush || brush_colorref != fl_colorref || brush_dc != fl_gc) 
	{
        fl_brush = CreateSolidBrush(fl_colorref);
        brush_colorref = fl_colorref;
		brush_dc = fl_gc;
		need_select = true;
    }

	if(need_select) {
		HBRUSH oldb = (HBRUSH)SelectObject(fl_gc, fl_brush);
		DeleteObject(oldb);
	}
#endif
    return fl_brush;
}

void Fl_Device::color(Fl_Color i)
{
	if(fl_color_ == i) return;

	fl_color_ = i;
	fl_colorref = fl_wincolor(i);
}

// Used by setcolor_index
static void fl_free_color(Fl_Color) {
	// CET - FIXME - Are there colormapped displays on Windows?
	//               Would this only be used for private colormaps?
}

#if USE_COLORMAP

// 'select_palette()' - Make a color palette for 8-bit displays if necessary
// Thanks to Michael Sweet @ Easy Software Products for this

HPALETTE fl_select_palette(void)
{
	static char beenhere;
	if (!beenhere) {
		beenhere = 1;
		
		//if (GetDeviceCaps(gc, BITSPIXEL) > 8) return NULL;
		int nColors = GetDeviceCaps(fl_gc, SIZEPALETTE);
		if (nColors <= 0 || nColors > 256) return NULL;
		// this will try to work on < 256 color screens, but will probably
		// come out quite badly.
		
		// I lamely try to get this variable-sized object allocated on stack:
		unsigned long foo[(sizeof(LOGPALETTE)+256*sizeof(PALETTEENTRY))/sizeof(unsigned long)+1];
		LOGPALETTE *pPal = (LOGPALETTE*)foo;
		
		pPal->palVersion    = 0x300;
		pPal->palNumEntries = nColors;
		
		// Build 256 colors from the standard FLTK colormap...
		
		for (int i = 0; i < nColors; i ++) {
			pPal->palPalEntry[i].peRed   = (fl_cmap[i] >> 24) & 255;
			pPal->palPalEntry[i].peGreen = (fl_cmap[i] >> 16) & 255;
			pPal->palPalEntry[i].peBlue  = (fl_cmap[i] >>  8) & 255;
			pPal->palPalEntry[i].peFlags = 0;
		};
		
		// Create the palette:
		fl_palette = CreatePalette(pPal);
	}
	if (fl_palette) {
		SelectPalette(fl_gc, fl_palette, FALSE);
		RealizePalette(fl_gc);
	}
	return fl_palette;
}

#endif

/////////////////////////////////////////
// Fl_Line_Drawer class
// Cosmetic line drawer with styles, ALL win32 platforms supported.
// Used in drawing functions that bypasses path mechanism.
/////////////////////////////////////////

// Set pattern for drawer. If dash_pattern!=0 it will be used as custom pattern.
void Fl_Line_Drawer::set_pattern(int size, DWORD *dash_pattern, int dash_count)
{
	if (pen_style == PS_SOLID) {
		// Solid pen, don't do anything
		patterns.clear();
		reset();
		return;
	}

	int gap	 = size;
	int dot	 = size;
	int dash = size * 3;

	if(cap_style==0 || cap_style & PS_ENDCAP_ROUND || cap_style & PS_ENDCAP_SQUARE) {
		if(size>1 || pen_style != PS_DOT) {
			dot = 1;
			gap += size;			
			dash -= size;
		}
	} 

	if(dash_pattern) 
	{
		//User defined dash pattern

		int offset = (dash_count % 2);
		int total_count = dash_count + offset;
		patterns.resize(total_count);

		for(int n=0; n<total_count; n++) {
			if(n >= dash_count)	patterns[n] = patterns[n-1];
			else				patterns[n] = dash_pattern[n];
		}

		reset();
		return;
	}

	switch(pen_style)
	{
		case PS_DOT:
			patterns.resize(2);
			patterns[0] = dot;
			patterns[1] = gap;
			break;

		case PS_DASH:
			patterns.resize(2);
			patterns[0] = dash;
			patterns[1] = gap;
			break;
	
		case PS_DASHDOT:
			patterns.resize(4);
			patterns[0] = dash;
			patterns[2] = dot;
			patterns[1] = patterns[3] = gap;
			break;

		case PS_DASHDOTDOT:
			patterns.resize(6);
			patterns[0] = dash;
			patterns[2] = patterns[4] = dot;
			patterns[1] = patterns[3] = patterns[5] = gap;
			break;

		default:
			break;
	}
	reset();
}

void Fl_Line_Drawer::move(int x, int y)
{
	// save current position
	cur_pos.x = x; 
	cur_pos.y = y;

	// reset parameters
	reset();

	// move to position
	MoveToEx(fl_gc, cur_pos.x, cur_pos.y, 0L);
}


void Fl_Line_Drawer::line(int x, int y)
{
	if(patterns.empty()) {
		// No pattern defined.
		// Move position.
		cur_pos.x = x; 
		cur_pos.y = y;

		// Draw line using W32 native drawing function.
		LineTo(fl_gc, x, y);
		
		// Draw the last point *again* because the GDI line drawing
	    // functions will not draw the last point ("it's a feature!"...)
		SetPixel(fl_gc, x, y, fl_colorref);
		
	} else {
		// calculate and draw next points
		bresenham_line(x, y);
	}
}

void Fl_Line_Drawer::reset()
{
	cur_pat = 0;
	if(!patterns.empty())
		cur_stretch = patterns[0]+1;
	else
		cur_stretch = 1;
}

// Slightly optimized horizontal line drawing
void Fl_Line_Drawer::h_line(int to_x, int direction)
{
	int dX = abs(to_x - cur_pos.x);
	bool line_to = (cur_pat % 2)==0;

	// process each point in the line one at a time
	for (; dX>=0; dX--)
	{
		if(!--cur_stretch) {
			// use next pattern for next segment
			cur_pat = (cur_pat + 1) % patterns.count();
			cur_stretch = patterns[cur_pat];

			// draw segment or skip gap
			if(line_to)	LineTo(fl_gc, cur_pos.x, cur_pos.y);
			else		MoveToEx(fl_gc, cur_pos.x, cur_pos.y, 0L);
			line_to = !line_to;
		}		
		// Break on last
		if(dX==0) break; 		

		cur_pos.x += direction;		
	}

	// draw to last point if necessary
	if(line_to)	LineTo(fl_gc, cur_pos.x, cur_pos.y);
	else		MoveToEx(fl_gc, cur_pos.x, cur_pos.y, 0L);
}

// Slightly optimized vertical line drawing
void Fl_Line_Drawer::v_line(int to_y, int direction)
{
	int dY = abs(to_y - cur_pos.y);
	bool line_to = (cur_pat % 2)==0;	

	// process each point in the line one at a time
	for (; dY>=0; dY--)
	{
		if(!--cur_stretch)
		{
			// use next pattern for next segment
			cur_pat = (cur_pat + 1) % patterns.count();
			cur_stretch = patterns[cur_pat];

			// draw segment or skip gap
			if(line_to)	LineTo(fl_gc, cur_pos.x, cur_pos.y);
			else		MoveToEx(fl_gc, cur_pos.x, cur_pos.y, 0L);				
			line_to = !line_to;			
		}		

		// Break on last
		if(dY==0) break;

		cur_pos.y += direction;
	}

	// draw to last point if necessary
	if(line_to)	LineTo(fl_gc, cur_pos.x, cur_pos.y);
	else		MoveToEx(fl_gc, cur_pos.x, cur_pos.y, 0L);
}

//============================================================================
// Fills the intermediate points along a line between the two given endpoints
// using Bresenham's line drawing algorithm. NOTE: this routine does no clipping
// so the coordinate values must be within the FrameBuffer bounds.
// NOTE: code may be slightly longer since efficiency was the most important
// consideration. Care was taken to ensure only integer additions, subtractions,
// and bit-shifts, and comparisons to zero. Inner loop was replicated to
// handle X and Y as independent variables separately with only one comparison
// of overhead that is outside the loop.
//============================================================================

// Original author: Kenny Hoff at http://timewarp.uncg.edu/~hoffkx/kenny/bresen.html
// Highly modified for eFLTK purpose by Mikko Lahteenmaki
void Fl_Line_Drawer::bresenham_line(int to_x, int to_y)
{
	//------------------------------------------------------------------------
	// DETERMINE "DIRECTIONS" TO INCREMENT X AND Y (REGARDLESS OF DECISION)
	//------------------------------------------------------------------------
	int Xincr=0, Yincr=0;
	
	// which direction in X?
	if(cur_pos.x > to_x) { Xincr=-1; } else if(cur_pos.x < to_x) { Xincr=1; }
	// which direction in Y?
	if(cur_pos.y > to_y) { Yincr=-1; } else if(cur_pos.y < to_y) { Yincr=1; }

	if(!Yincr) {
		// HORIZONTAL LINE! optimize this!
		h_line(to_x, Xincr);
		return;
	} else if(!Xincr) {
		// VERTICAL LINE! optimize this!
		v_line(to_y, Yincr);
		return;
	}

	//------------------------------------------------------------------------
	// INITIALIZE THE COMPONENTS OF THE ALGORITHM THAT ARE NOT AFFECTED BY THE
	// SLOPE OR DIRECTION OF THE LINE
	//------------------------------------------------------------------------

	// store the change in X and Y of the line endpoints
	int dX = abs(to_x - cur_pos.x);
	int dY = abs(to_y - cur_pos.y);
	
	bool line_to = (cur_pat % 2)==0;

	//------------------------------------------------------------------------
	// DETERMINE INDEPENDENT VARIABLE (ONE THAT ALWAYS INCREMENTS BY 1 (OR -1) )
	// AND INITIATE APPROPRIATE LINE DRAWING ROUTINE (BASED ON FIRST OCTANT
	// ALWAYS). THE X AND Y'S MAY BE FLIPPED IF Y IS THE INDEPENDENT VARIABLE.
	//------------------------------------------------------------------------
	if (dX >= dY)	// if X is the independent variable
	{           
		int dPr 	= dY<<1;   						// amount to increment decision if right is chosen (always)
		int dPru 	= dPr - (dX<<1);				// amount to increment decision if up is chosen
		int P 		= dPr - dX;						// decision variable start value

		for (; dX>=0; dX--)							// process each point in the line one at a time (just use dX)
		{
			if(!--cur_stretch)
			{
				// use next pattern for next segment
				cur_pat = (cur_pat + 1) % patterns.count();
				cur_stretch = patterns[cur_pat];

				// draw segment or skip gap
				if(line_to)	LineTo(fl_gc, cur_pos.x, cur_pos.y);
				else		MoveToEx(fl_gc, cur_pos.x, cur_pos.y, 0L);				
				line_to = !line_to;
			}
			// Break on last
			if(dX==0) break; 

			if (P > 0)                              // is the pixel going right AND up?
			{ 
				cur_pos.x += Xincr;					// increment independent variable
				cur_pos.y += Yincr; 				// increment dependent variable
				P+=dPru;							// increment decision (for up)
			}
			else									// is the pixel just going right?
			{
				cur_pos.x += Xincr;					// increment independent variable
				P+=dPr;								// increment decision (for right)
			}
		}		
	}
	else			// if Y is the independent variable
	{
		int dPr 	= dX<<1;   						// amount to increment decision if right is chosen (always)
		int dPru 	= dPr - (dY<<1);    			// amount to increment decision if up is chosen
		int P 		= dPr - dY;						// decision variable start value

		for (; dY>=0; dY--)							// process each point in the line one at a time (just use dY)
		{
			if(!--cur_stretch)
			{
				// use next pattern for next segment
				cur_pat = (cur_pat + 1) % patterns.count();
				cur_stretch = patterns[cur_pat];

				// draw segment or skip gap
				if(line_to)	LineTo(fl_gc, cur_pos.x, cur_pos.y);
				else		MoveToEx(fl_gc, cur_pos.x, cur_pos.y, 0L);				
				line_to = !line_to;
			}
			// Break on last
			if(dY==0) break;

			if (P > 0)                              // is the pixel going up AND right?
			{ 
				cur_pos.x += Xincr; 				// increment dependent variable
				cur_pos.y += Yincr;					// increment independent variable
				P+=dPru;							// increment decision (for up)
			}
			else									// is the pixel just going up?
			{
				cur_pos.y += Yincr;					// increment independent variable
				P+=dPr;								// increment decision (for right)
			}
		}		
	}			

	// draw to last point if necessary
	if(line_to)	LineTo(fl_gc, cur_pos.x, cur_pos.y);
	else		MoveToEx(fl_gc, cur_pos.x, cur_pos.y, 0L);
}

//
// End of "$Id$".
//

