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

/** Fl_AlignEnum */
enum Fl_AlignEnum {
    FL_ALIGN_CENTER       = 0,
    FL_ALIGN_TOP          = 0x00000001,
    FL_ALIGN_BOTTOM       = 0x00000002,
    FL_ALIGN_LEFT         = 0x00000004,
    FL_ALIGN_RIGHT        = 0x00000008,
    FL_ALIGN_INSIDE       = 0x00000010,
    FL_ALIGN_CLIENT       = 0x00000010,
    FL_ALIGN_CLIP         = 0x00000040,
    FL_ALIGN_WRAP         = 0x00000080,
    FL_ALIGN_TILED        = 0x00000100,
    FL_ALIGN_SCALE        = 0x00000200,
    FL_ALIGN_MASK         = 0x00000FFF,

    // Short-cuts:
    FL_ALIGN_TOP_LEFT     = FL_ALIGN_TOP | FL_ALIGN_LEFT,
    FL_ALIGN_TOP_RIGHT	  = FL_ALIGN_TOP | FL_ALIGN_RIGHT,
    FL_ALIGN_BOTTOM_LEFT  = FL_ALIGN_BOTTOM | FL_ALIGN_LEFT,
    FL_ALIGN_BOTTOM_RIGHT = FL_ALIGN_BOTTOM | FL_ALIGN_RIGHT,
    FL_ALIGN_LEFT_TOP	  = FL_ALIGN_TOP_LEFT,
    FL_ALIGN_RIGHT_TOP	  = FL_ALIGN_TOP_RIGHT,
    FL_ALIGN_LEFT_BOTTOM  = FL_ALIGN_BOTTOM_LEFT,
    FL_ALIGN_RIGHT_BOTTOM = FL_ALIGN_BOTTOM_RIGHT,
};

/** Fl_FlagsEnum */
enum Fl_FlagsEnum {
    FL_INACTIVE           = 0x00001000, // does not get events, gray it out
    FL_OUTPUT             = 0x00002000, // does not get events
    FL_VALUE              = 0x00004000, // indicates true/down/on state
    FL_SELECTED           = 0x00008000, // draw using selection colors
    FL_INVISIBLE          = 0x00010000, // does not get events, does not draw
    FL_HIGHLIGHT          = 0x00020000, // draw highlighted
    FL_CHANGED            = 0x00040000, // value changed since last callback
    FL_FOCUS_ON_CLICK     = 0x00080000, // Set true if clicking this widget causes it to take focus
    FL_FOCUS_ON_KEYBOARD  = 0x00100000, // Set true if clicking this widget causes it to take focus

    FL_RAW_LABEL          = 0x00200000, // don't interpret & or @ in label
    FL_PACK_VERTICAL      = 0x00400000  // Fl_Pack puts this widget vertical
};

/** Fl_Align */
typedef Fl_AlignEnum Fl_Align;

/** Fl_Flags */
class Fl_Flags
{
    int m_flags;
public:
    Fl_Flags(const Fl_Flags &f) { m_flags = f.m_flags; }
    Fl_Flags(Fl_Align align) : m_flags(align) { }
    Fl_Flags(long flags) : m_flags(flags) { }
    Fl_Flags(unsigned flags) : m_flags(flags) { }
    Fl_Flags(int flags) : m_flags(flags) { }
    Fl_Flags(void* flags) : m_flags((int)flags) { }
    Fl_Flags() : m_flags(0) { }

    bool is_set(int flags) const { return (m_flags&flags)!=0; }

    Fl_Flags &flags(Fl_Flags f)  { m_flags = f.m_flags; return *this; }
    Fl_Flags &set(int flags)    { m_flags |= flags;  return *this; }
    Fl_Flags &clear(int flags)  { m_flags &= ~flags; return *this; }
    Fl_Flags &invert(int flags) { m_flags ^= flags;  return *this; }

    Fl_Flags& operator = (Fl_Flags f) { m_flags = f.m_flags; return *this; }
    Fl_Flags& operator = (int f) { m_flags = f; return *this; }

    Fl_Align align() const { return Fl_Align(m_flags&FL_ALIGN_MASK); }
    void align(int a) { m_flags = (m_flags & (~FL_ALIGN_MASK)) | a; }

    int flags() { return m_flags; }
    int flags() const { return m_flags; }

    operator int& () { return m_flags; }
};

#endif
