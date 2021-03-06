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

#ifndef _FL_MULTILINE_INPUT_H_
#define _FL_MULTILINE_INPUT_H_

#include "Fl_Input.h"

// This class is entirely inline.  If that changes, add FL_API to its declaration

/** Fl_Multiline_Input */
class Fl_Multiline_Input : public Fl_Input {
public:
    /** Creates new multiline input widget using the given position, size, and label string. */
    Fl_Multiline_Input(int x,int y,int w,int h,const char *l = 0) 
    : Fl_Input(x,y,w,h,l) { input_type(MULTILINE); }

    /** Creates new multiline input widget using the label, size, alignment, and label_width. */
    Fl_Multiline_Input(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100)
    : Fl_Input(l,layout_size,layout_al,label_w) { input_type(MULTILINE); }

    /** We do not want to limit multiline inputs */
    virtual void preferred_size(int& w, int& h) const {}
};

#endif
