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

#include <config.h>
#include <efltk/win32.h>
#include <stdio.h>

// The current color:
Fl_Color    fl_color_;
COLORREF    fl_colorref;
HPALETTE    fl_palette;
HBRUSH      fl_brush;
HPEN        fl_pen;

static COLORREF	brush_for;
static COLORREF	pen_for;

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

static int lstyle = 0;
static DWORD dash_pattern[16];
static int dash_pattern_size = 0;
static int line_width = 0;

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

	if (dashes && dashes[0]) {
		lstyle = PS_USERSTYLE | Cap[(style>>8)&3] | Join[(style>>12)&3];
		int n; for (n = 0; n < 16 && *dashes;) dash_pattern[n++] = *dashes++;
		dash_pattern_size = n;
		// fix cards that ignore dash pattern for zero width:
		//if (!width) width = 1;
	} else {
		dash_pattern_size = 0;
		// allow any low 8 bits for style
		lstyle = style & 0xff | Cap[(style>>8)&3] | Join[(style>>12)&3];
	}
	// for some reason zero width does not work at all:
	if (!width) width = 1;
	line_width = width;

	if (fl_pen) {
		DeleteObject(fl_pen);
		fl_pen = 0;
	}
#endif
}

#if _WIN32_WINNT >= 0x0500
static HPEN stockpen = (HPEN)GetStockObject(DC_PEN);
static HBRUSH stockbrush = (HBRUSH)GetStockObject(DC_BRUSH);
#endif

HPEN fl_setpen() 
{
#if _WIN32_WINNT >= 0x0500
	if (!lstyle && line_width <= 1) {
		SelectObject(fl_gc, stockpen);
		SetDCPenColor(fl_gc, fl_colorref);
		return stockpen;
	}
#endif
	if (!fl_pen) goto J1;
	if (pen_for != fl_colorref) {
		DeleteObject(fl_pen);
J1:
		if (lstyle) {
			LOGBRUSH penbrush = {BS_SOLID, fl_colorref, 0};
			fl_pen = ExtCreatePen(lstyle|PS_GEOMETRIC, line_width, &penbrush,
				dash_pattern_size, dash_pattern_size?dash_pattern:0);
		} else {
			fl_pen = CreatePen(PS_SOLID, line_width, fl_colorref);
		}
		pen_for = fl_colorref;
	}
	SelectObject(fl_gc, fl_pen);
	return fl_pen;
}

HBRUSH fl_setbrush() 
{
#if _WIN32_WINNT >= 0x0500
	SelectObject(fl_gc, stockbrush);
	SetDCBrushColor(fl_gc, fl_colorref);
#else
	if (!fl_brush) goto J1;
	if (brush_for != fl_colorref) {
		DeleteObject(fl_brush);
J1:
		fl_brush = CreateSolidBrush(fl_colorref);
		brush_for = fl_colorref;
	}
	SelectObject(fl_gc, fl_brush);
#endif
	return fl_brush;
}

void Fl_Device::color(Fl_Color i)
{
	if(i==fl_color_) 
		return;

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

HPALETTE
fl_select_palette(void)
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

//
// End of "$Id$".
//

