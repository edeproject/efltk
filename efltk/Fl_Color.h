//
// "$Id$"
//
// Color value used by the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Color_h
#define Fl_Color_h

#include "Enumerations.h" // for FL_API and uchar
#include "Fl_Flags.h" // for Fl_Flags & FL_INACTIVE

typedef unsigned Fl_Color;

enum {
  FL_NO_COLOR		= 0,
  FL_GRAY_RAMP		= 32,
  FL_GRAY		= 49,	// 'R' default color, 75%
  FL_INACTIVE_COLOR	= 39,	// same as fl_inactive(FL_BLACK)
  FL_COLOR_CUBE		= 0x38,
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
  FL_FREE_COLOR		= 16,
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
inline Fl_Color fl_color_cube(int r, int g, int b) {
  return (Fl_Color)((b*FL_NUM_RED + r) * FL_NUM_GREEN + g + FL_COLOR_CUBE);}
inline Fl_Color fl_rgb(unsigned char r, unsigned char g, unsigned char b) {
  return Fl_Color((r<<24)+(g<<16)+(b<<8));}
FL_API Fl_Color fl_rgb(const char*);
FL_API Fl_Color fl_color_average(Fl_Color, Fl_Color, double weight);
FL_API Fl_Color fl_inactive(Fl_Color);
FL_API Fl_Color fl_inactive(Fl_Color, Fl_Flags f);
FL_API Fl_Color fl_contrast(Fl_Color fg, Fl_Color bg);
FL_API Fl_Color fl_invert(Fl_Color);
#ifndef FLTK_2
#define contrast(a,b) fl_contrast(a,b)
#define inactive(a) fl_inactive(a)
#endif
FL_API Fl_Color fl_get_color(Fl_Color c);
FL_API void fl_get_color(Fl_Color c, uchar& r, uchar& g, uchar& b);
FL_API void fl_set_color(Fl_Color c, Fl_Color);
FL_API void fl_free_color(Fl_Color c);
FL_API void fl_background(Fl_Color);
FL_API Fl_Color fl_nearest_color(Fl_Color);

inline Fl_Color fl_lighter(Fl_Color c) { return fl_color_average(c, FL_WHITE, .67f); }
inline Fl_Color fl_darker(Fl_Color c) { return fl_color_average(c, FL_BLACK, .67f); }

#endif

//
// End of "$Id$".
//
