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

#ifndef _FL_FLAGS_H_
#define _FL_FLAGS_H_

// This same value is used to:

// 1. store state and other information in a widget or menu item
// 2. provide hints to boxes, labeltypes, and images for how to draw
// 3. provide structural information to an array of menu items

// These are shared because various parts of the code, especially
// drawing, want all of this information at once, and providing it
// as a single word is the easiest way.

typedef int Fl_Flags;
typedef Fl_Flags Fl_Align; // for back compatability

enum {
  FL_NO_FLAGS		= 0,

// from Fl_Align, values are comptable with fltk 1.0:
// These control the location and appearance of labels:
  FL_ALIGN_CENTER	= 0,
  FL_ALIGN_TOP          = 0x00000001,
  FL_ALIGN_BOTTOM       = 0x00000002,
  FL_ALIGN_LEFT         = 0x00000004,
  FL_ALIGN_RIGHT        = 0x00000008,
  FL_ALIGN_INSIDE       = 0x00000010,
  FL_ALIGN_CLIP         = 0x00000040,
  FL_ALIGN_WRAP         = 0x00000080,
  FL_ALIGN_TILED        = 0x00000100,
  FL_ALIGN_SCALE        = 0x00000200,
  FL_ALIGN_MASK		= 0x00000FFF,

  FL_INACTIVE		= 0x00001000, // does not get events, gray it out
  FL_OUTPUT		= 0x00002000, // does not get events
  FL_VALUE		= 0x00004000, // indicates true/down/on state
  FL_SELECTED		= 0x00008000, // draw using selection colors
  FL_INVISIBLE		= 0x00010000, // does not get events, does not draw
  FL_HIGHLIGHT		= 0x00020000, // draw highlighted
  FL_CHANGED		= 0x00040000, // value changed since last callback
  FL_COPIED_LABEL	= 0x00080000, // copy_label() was called
  FL_RAW_LABEL		= 0x00100000, // don't interpret & or @ in label
  FL_PACK_VERTICAL	= 0x00200000, // Fl_Pack puts this widget vertical
  FL_CLICK_TO_FOCUS     = 0x00400000  // Set true if clicking this widget causes it to take focus

};

#endif
