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

#ifndef _FL_REPEAT_BUTTON_H_
#define _FL_REPEAT_BUTTON_H_

#include "Fl_Button.h"

/** Fl_Repeat_Button */
class FL_API Fl_Repeat_Button : public Fl_Button {
public:
    /** Creates the repeat button widget using the position, size, and label. */
    Fl_Repeat_Button(int x,int y,int w,int h,const char *l=0)
    : Fl_Button(x,y,w,h,l) { }

    /** Creates the repeat button using the label, size, and alignment. */
    Fl_Repeat_Button(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP)
    : Fl_Button(l,layout_size,layout_al) { }

    virtual int handle(int);

private:
    static void repeat_callback(void *);
};

#endif
