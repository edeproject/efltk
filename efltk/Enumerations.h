//
// "$Id$"
//
// Enumerations for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Enumerations_H
#define Fl_Enumerations_H

#include "Fl_Export.h"

//
// The FLTK version number; this is changed slightly from the beta versions
// because the old "const double" definition would not allow for conditional
// compilation...
//
// FL_VERSION is a float that describes the major, minor, and patch version
// numbers.  Version 1.1 is actually stored as 1.01 to allow for more than 9
// minor releases.  Similarly, version 1.0.5 is stored as 1.0005.
//
// The FL_MAJOR_VERSION, FL_MINOR_VERSION, and FL_PATCH_VERSION constants
// give the integral values for the major, minor, and patch releases
// respectively.
//

#define FL_MAJOR_VERSION	2
#define FL_MINOR_VERSION	0
#define FL_PATCH_VERSION        3
#define FL_VERSION		(FL_MAJOR_VERSION + \
				 FL_MINOR_VERSION * 0.01f + \
				 FL_PATCH_VERSION * 0.0001f)

#if defined(_WIN32) && !defined(__GNUC__)
 typedef __int64           int64;
 typedef unsigned __int64  uint64;
#else
 typedef signed long long   int64;
 typedef unsigned long long uint64;
#endif

#ifdef _WIN32
# undef slash
# define slash '\\'
#else
# undef slash
# define slash '/'
#endif

typedef unsigned char uchar;
typedef unsigned long ulong;
typedef signed int    int32;
typedef unsigned int  uint32;
typedef signed short  int16;
typedef unsigned short uint16;
typedef signed char   int8;
typedef unsigned char uint8;
typedef uint32		  uint;

enum {	// events
  FL_NO_EVENT		= 0,
  FL_PUSH		= 1,
  FL_RELEASE		= 2,
  FL_ENTER		= 3,
  FL_LEAVE		= 4,
  FL_DRAG		= 5,
  FL_FOCUS		= 6,
  FL_UNFOCUS		= 7,
  FL_KEY		= 8,
  FL_KEYUP		= 9,
  FL_MOVE		= 10,
  FL_SHORTCUT		= 11,
  FL_ACTIVATE		= 12,
  FL_DEACTIVATE		= 13,
  FL_SHOW		= 14,
  FL_HIDE		= 15,
  FL_MOUSEWHEEL		= 16,
  FL_PASTE		= 17,
  FL_DND_ENTER		= 18,
  FL_DND_DRAG		= 19,
  FL_DND_LEAVE		= 20,
  FL_DND_RELEASE	= 21,

// back compatability values:
  FL_KEYBOARD		= FL_KEY
};

enum { // Fl_Widget::when():
  FL_WHEN_NEVER		= 0,
  FL_WHEN_CHANGED	= 1,
  FL_WHEN_RELEASE	= 4,
  FL_WHEN_RELEASE_ALWAYS= 6,
  FL_WHEN_ENTER_KEY	= 8,
  FL_WHEN_ENTER_KEY_ALWAYS=10,
  FL_WHEN_ENTER_KEY_CHANGED=11,
  FL_WHEN_NOT_CHANGED	= 2 // modifier bit to disable changed() test
};

// Fl::event_key() and Fl::get_key(n) (use ascii letters for all other keys):
#define FL_Space	32
#define FL_Button(n)	(0xfee8+(n))	// use Fl_Button(FL_*_MOUSE)
#define FL_BackSpace	0xff08
#define FL_Tab		0xff09
#define FL_Clear	0xff0b // '5' key on windows, ^K
#define FL_Enter	0xff0d
#define FL_Pause	0xff13
#define FL_Scroll_Lock	0xff14
#define FL_Escape	0xff1b
#define FL_Home		0xff50
#define FL_Left		0xff51
#define FL_Up		0xff52
#define FL_Right	0xff53
#define FL_Down		0xff54
#define FL_Page_Up	0xff55
#define FL_Page_Down	0xff56
#define FL_End		0xff57
#define FL_Print	0xff61
#define FL_Insert	0xff63
#define FL_Menu		0xff67
#define FL_Num_Lock	0xff7f
#define FL_KP(c)	(0xff80+(c)) // FL_KP('x') is 'x' on numeric keypad
#define FL_KP_Enter	0xff8d // same as Fl_KP('\r')
#define FL_KP_Last	0xffbc // use to range-check keypad
#define FL_F(n)		(0xffbd+(n))
#define FL_F_Last	0xffe0 // use to range-check function keys
#define FL_Shift_L	0xffe1
#define FL_Shift_R	0xffe2
#define FL_Control_L	0xffe3
#define FL_Control_R	0xffe4
#define FL_Caps_Lock	0xffe5
#define FL_Alt_L	0xffe9
#define FL_Alt_R	0xffea
#define FL_Win_L	0xffeb // equals the keysym XK_Super_L
#define FL_Win_R	0xffec // equals the keysym XK_Super_L
#define FL_Meta_L	FL_Win_L	// for back compatibility
#define FL_Meta_R	FL_Win_R	// for back compatibility
#define FL_Delete	0xffff

// Fl::event_button():
#define FL_LEFT_MOUSE	1
#define FL_MIDDLE_MOUSE	2
#define FL_RIGHT_MOUSE	3

// Fl::event_state():
#define FL_SHIFT	0x00010000
#define FL_CAPS_LOCK	0x00020000
#define FL_CTRL		0x00040000
#define FL_ALT		0x00080000
// Not all X servers agree on these assignments but XFree86 uses them:
#define FL_NUM_LOCK	0x00100000
#define FL_WIN		0x00400000
#define FL_META		FL_WIN	   // for back compatability
#define FL_SCROLL_LOCK	0x00800000

#define FL_BUTTON1	0x01000000
#define FL_BUTTON2	0x02000000
#define FL_BUTTON3	0x04000000
#define FL_BUTTONS	0x7f000000
#define FL_BUTTON(n)	(0x00800000<<(n))

enum Fl_Cursor {	// standard cursors
  FL_CURSOR_DEFAULT	= 0,
  FL_CURSOR_ARROW	= 35,
  FL_CURSOR_CROSS	= 66,
  FL_CURSOR_WAIT	= 76,
  FL_CURSOR_INSERT	= 77,
  FL_CURSOR_HAND	= 31,
  FL_CURSOR_HELP	= 47,
  FL_CURSOR_MOVE	= 27,
  // fltk provides bitmaps for these:
  FL_CURSOR_NS		= 78,
  FL_CURSOR_WE		= 79,
  FL_CURSOR_NWSE	= 80,
  FL_CURSOR_NESW	= 81,
  FL_CURSOR_NO          = 82,
  FL_CURSOR_NONE	= 255,
  // for back compatability (non MSWindows ones):
  FL_CURSOR_N		= 70,
  FL_CURSOR_NE		= 69,
  FL_CURSOR_E		= 49,
  FL_CURSOR_SE		= 8,
  FL_CURSOR_S		= 9,
  FL_CURSOR_SW		= 7,
  FL_CURSOR_W		= 36,
  FL_CURSOR_NW		= 68
  //FL_CURSOR_NS	= 22,
  //FL_CURSOR_WE	= 55,
};

enum { // values for "when" passed to Fl::add_fd()
  FL_READ = 1,
  FL_WRITE = 4,
  FL_EXCEPT = 8
};

enum { // Values for Fl::visual(), Fl::gl_visual(), Fl_Gl_Window::mode()
  FL_RGB	= 0,
  FL_INDEX	= 1,
  FL_SINGLE	= 0,
  FL_DOUBLE	= 2,
  FL_ACCUM	= 4,
  FL_ALPHA	= 8,
  FL_DEPTH	= 16,
  FL_STENCIL	= 32,
  FL_RGB8	= 64,
  FL_MULTISAMPLE= 128,
  FL_STEREO	= 256
};

// damage
enum {
  FL_DAMAGE_VALUE	= 0x01,
  FL_DAMAGE_PUSHED	= 0x02,
  FL_DAMAGE_SCROLL	= 0x04,
  FL_DAMAGE_OVERLAY	= 0x04, // reused value
  FL_DAMAGE_HIGHLIGHT   = 0x08,
  FL_DAMAGE_CHILD       = 0x10,
  FL_DAMAGE_CHILD_LABEL = 0x20,
  FL_DAMAGE_EXPOSE      = 0x40,
  FL_DAMAGE_CONTENTS	= 0x40, // reused value
  FL_DAMAGE_ALL         = 0x80
};

// layout damage
enum {
  FL_LAYOUT_X		= 0x01,
  FL_LAYOUT_Y		= 0x02,
  FL_LAYOUT_XY		= 0x03,
  FL_LAYOUT_W		= 0x04,
  FL_LAYOUT_H		= 0x08,
  FL_LAYOUT_WH		= 0x0C,
  FL_LAYOUT_XYWH	= 0x0F,
  FL_LAYOUT_CHILD	= 0x10,
  FL_LAYOUT_DAMAGE	= 0x80
};

// effect types for menus/tooltips
enum {
  FL_EFFECT_NONE = 0,
  FL_EFFECT_ANIM,
  FL_EFFECT_FADE
};

inline Fl_Color fl_lighter(Fl_Color c) { return fl_color_average(c, FL_WHITE, .67f); }
inline Fl_Color fl_darker(Fl_Color c) { return fl_color_average(c, FL_BLACK, .67f); }

/* Prevent Visual C++ 6.0 from printing out stupid warnings */
#if defined(_MSC_VER) && (_MSC_VER >= 600)
	#pragma warning(disable: 4550)
	#pragma warning(disable: 4244)
#endif

#endif

//
// End of "$Id$".
//
