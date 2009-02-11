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

#ifndef _FL_ROUND_BUTTON_H_
#define _FL_ROUND_BUTTON_H_

#include "Fl_Radio_Button.h"

// Back-compatability, this is a radio button with check-button behavior
// This class is entirely inline.  If that changes, add FL_API to its declaration

/** Fl_Round_Button */
class Fl_Round_Button : public Fl_Radio_Button {
public:
    /** Creates the round button widget using the position, size, and label. */
    Fl_Round_Button(int x,int y,int w,int h,const char *l) 
    : Fl_Radio_Button(x,y,w,h,l) { type(TOGGLE); }

    /** Creates the round button widget using the label, size, and alignment. */
    Fl_Round_Button(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP)
    : Fl_Radio_Button(l,layout_size,layout_al) { type(TOGGLE); }

};

#endif
