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

#ifndef _FL_SECRET_INPUT_H_
#define _FL_SECRET_INPUT_H_

#include "Fl_Input.h"

/** Fl_Secret_Input */
class Fl_Secret_Input : public Fl_Input {
public:
    /** Creates new input widget using the given position, size, and label string. */
    Fl_Secret_Input(int x,int y,int w,int h,const char *l = 0) 
    : Fl_Input(x,y,w,h,l) { type(SECRET); }

    /** Creates new input widget using the label, size, alignment, and label width. */
    Fl_Secret_Input(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100)
    : Fl_Input(l,layout_size,layout_al,label_w) { type(SECRET); }
};

#endif
