/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_COLOR_H_
#define _FL_COLOR_H_

#include "Enumerations.h" // for FL_API and uchar
#include "Fl_Flags.h" // for Fl_Flags & FL_INACTIVE

typedef unsigned Fl_Color;

enum {
    FL_NO_COLOR	        = 0,
    FL_GRAY_RAMP	= 32,
    FL_GRAY		= 49,	// 'R' default color, 75%
    FL_INACTIVE_COLOR	= 39,	// same as fl_inactive(FL_BLACK)
    FL_COLOR_CUBE	= 0x38,
    FL_BLACK		= 0x38,
    FL_RED		= 0x58,
    FL_GREEN		= 0x3f,
    FL_YELLOW		= 0x5f,
    FL_BLUE		= 0xd8,
    FL_MAGENTA		= 0xf8,
    FL_CYAN		= 0xdf,
    FL_WHITE		= 0xff,
#ifndef FLTK_2
    FL_GRAY0		= 32,	// 'A' black
    FL_DARK3		= 39,	// 'H' about 33%
    FL_DARK2		= 45,   // 'N'
    FL_DARK1		= 47,	// 'P' about 66%
    FL_LIGHT1		= 51,	// 'T'
    FL_LIGHT2		= 53,	// 'V'
    FL_LIGHT3		= 55,	// 'X' white
    FL_SELECTION_COLOR	= FL_GRAY, // older selection color
    FL_FREE_COLOR      	= 16,
#endif
    FL_BLUE_SELECTION_COLOR = 0x88 // _WIN32-like selection color
};

#define FL_NUM_GRAY	24
inline Fl_Color fl_gray_ramp(int i) {return (Fl_Color)(i+FL_GRAY_RAMP);}

#define FL_NUM_GREEN	8
#define FL_GREEN_DELTA	1
#define FL_NUM_RED	5
#define FL_RED_DELTA	8
#define FL_NUM_BLUE	5
#define FL_BLUE_DELTA	40
inline Fl_Color fl_color_cube(int r, int g, int b) { return (Fl_Color)((b*FL_NUM_RED + r) * FL_NUM_GREEN + g + FL_COLOR_CUBE); }
inline Fl_Color fl_rgb(unsigned char r, unsigned char g, unsigned char b) { return Fl_Color((r<<24)+(g<<16)+(b<<8)); }
FL_API Fl_Color fl_rgb(const char*);
FL_API Fl_Color fl_color_average(Fl_Color, Fl_Color, double weight);
FL_API Fl_Color fl_inactive(Fl_Color);
FL_API Fl_Color fl_inactive(Fl_Color, Fl_Flags f);
FL_API Fl_Color fl_contrast(Fl_Color fg, Fl_Color bg);
FL_API Fl_Color fl_invert(Fl_Color);
FL_API Fl_Color fl_get_color(Fl_Color c);
FL_API void fl_get_color(Fl_Color c, uchar& r, uchar& g, uchar& b);
FL_API void fl_set_color(Fl_Color c, Fl_Color);
FL_API void fl_free_color(Fl_Color c);
FL_API void fl_background(Fl_Color);
FL_API Fl_Color fl_nearest_color(Fl_Color);

inline Fl_Color fl_lighter(Fl_Color c) { return fl_color_average(c, FL_WHITE, .67f); }
inline Fl_Color fl_darker(Fl_Color c) { return fl_color_average(c, FL_BLACK, .67f); }

#endif
