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

/**
 * \defgroup Fl_Color Fl_Color Functions
 */
/*@{*/

typedef unsigned Fl_Color;

/**
 * Pre-defined colors.
 * The following color constants can be used to access the colors from the eFLTK standard colormap:
 */
enum Colors {
    FL_NO_COLOR	        = 0,
    FL_GRAY_RAMP	= 32,
    FL_GRAY		= 49,	///< 'R' default color, 75%
    FL_INACTIVE_COLOR	= 39,	///< same as fl_inactive(FL_BLACK)
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
    FL_GRAY0		= 32,	///<  'A' black
    FL_DARK3		= 39,	///<  'H' about 33%
    FL_DARK2		= 45,   ///<  'N'
    FL_DARK1		= 47,	///<  'P' about 66%
    FL_LIGHT1		= 51,	///<  'T'
    FL_LIGHT2		= 53,	///<  'V'
    FL_LIGHT3		= 55,	///< 'X' white
    FL_SELECTION_COLOR	= FL_GRAY, // older selection color
    FL_FREE_COLOR      	= 16,
#endif
    FL_BLUE_SELECTION_COLOR = 0x88 ///< WIN32-like selection color
};

/** Number of colors in gray ramp. */
#define FL_NUM_GRAY	24

/**
 * Returns a gray color value from black (i == 0) to white ( i == FL_NUM_GRAY - 1).
 * FL_NUM_GRAY is defined to be 24 in the current eFLTK release.
 * To get the closest eFLTK gray value to an 8-bit grayscale color 'I' use:
 <PRE>fl_gray_ramp(I * (FL_NUM_GRAY - 1) / 255)</PRE>
 * @param i index of gray color: 0 to (FL_NUM_GRAY-1)
 */
inline Fl_Color fl_gray_ramp(int i) {return (Fl_Color)(i+FL_GRAY_RAMP);}

#define FL_NUM_GREEN	8
#define FL_GREEN_DELTA	1
#define FL_NUM_RED	5
#define FL_RED_DELTA	8
#define FL_NUM_BLUE	5
#define FL_BLUE_DELTA	40

/** fl_color_cube */
inline Fl_Color fl_color_cube(int r, int g, int b) { return (Fl_Color)((b*FL_NUM_RED + r) * FL_NUM_GREEN + g + FL_COLOR_CUBE); }

/**
 * Returns Fl_Color of r,g,b
 */
inline Fl_Color fl_rgb(unsigned char r, unsigned char g, unsigned char b) { return Fl_Color((r<<24)+(g<<16)+(b<<8)); }

/**
 * Returns Fl_Color from string e.g. "#FF0000", which is same as "red".
 * If color is not found, 0 is returned.
 */
FL_API Fl_Color fl_rgb(const char *color);

/**
 * Returns the weighted average color between the two colors. The red, green, and blue values are averaged using the following formula:
 <PRE>color = c1 * weight + c2 * (1 - weight)</PRE>
 * Thus, a weight value of 1.0 will return the first color, while a value of 0.0 will return the second color.
 */
FL_API Fl_Color fl_color_average(Fl_Color c1, Fl_Color c2, double weight);

/** Returns "greyed" color between 'color' and FL_GRAY. */
FL_API Fl_Color fl_inactive(Fl_Color color);

/** Returns "greyed" color between 'color' and FL_GRAY.
 * Only if flags 'f' has FL_INACTIVE bit set.
 */
FL_API Fl_Color fl_inactive(Fl_Color color, Fl_Flags f);

/**
 * Decides if 'fg' can be seen against 'bg' and returns 'fg' if so.
 * If not this returns either FL_NO_COLOR or FL_WHITE, whichever one is more different than 'bg'.
 * This function is often used by eFLTK for labels and text when no color is specified in the style.
 */
FL_API Fl_Color fl_contrast(Fl_Color fg, Fl_Color bg);

/** Returns inverted color of 'color' */
FL_API Fl_Color fl_invert(Fl_Color color);

/**
 * Turns an indexed color into an rgb color by looking it up in the colormap.
 * If 'color' is not an indexed color it is returned unchanged.
 */
FL_API Fl_Color fl_get_color(Fl_Color color);

/**
 * Turns an indexed color into an rgb color if necessary, and then the rgb portions of the color are extracted and put in the passed variables (r,g,b).
 */
FL_API void fl_get_color(Fl_Color c, uchar& r, uchar& g, uchar& b);

/**
 * Set entry index in the eFLTK colormap.
 * @param color is changed to colormap.
 * $param index must be in the range 1-31.
 */
FL_API void fl_set_color(Fl_Color index, Fl_Color color);

/**
 * Tell a colormapped-display that we don't need this indexed color anymore.
 * eFLTK will free any hardware colormap it allocated so that it can be reused by this or another program.
 */
FL_API void fl_free_color(Fl_Color c);

/**
 * Modifies the "gray ramp" in the eFLTK colormap so that the color FL_GRAY is set the the rgb values of the passed color.
 * This is the best way to change the overall color of your application, because it sets all the shaded borders and works on 8-bit screens.
 */
FL_API void fl_background(Fl_Color);

/**
 * Turns an rgb color into an indexed color.
 * If 'color' is already an indexed color it is returned unchanged.
 * Otherwise, the closest color from the color cube is returned.
 */
FL_API Fl_Color fl_nearest_color(Fl_Color color);

/**
 * Returns a lighter version of the specified color.
 */
inline Fl_Color fl_lighter(Fl_Color c) { return fl_color_average(c, FL_WHITE, .67f); }

/**
 * Returns a darker version of the specified color. 
 */
inline Fl_Color fl_darker(Fl_Color c) { return fl_color_average(c, FL_BLACK, .67f); }

/*@)*/

#endif
