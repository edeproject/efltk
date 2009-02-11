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

#ifndef _FL_VALUE_OUTPUT_H_
#define _FL_VALUE_OUTPUT_H_

#include "Fl_Value_Input.h"
#include "Fl_Output.h"

/** Fl_Value_Output */
class FL_API Fl_Value_Output : public Fl_Value_Input {
public:
    /** Creates new value output widget using the given position, size, and label string. */
    Fl_Value_Output(int x,int y,int w,int h,const char *l = 0) 
    : Fl_Value_Input(x, y, w, h, l) {
        input.readonly(1);
        copy_style(Fl_Output::default_style);
    }

    /** Creates new value output widget using the label, size, alignment, and label width. */
    Fl_Value_Output(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100)
    : Fl_Value_Input(l,layout_size,layout_al,label_w) {
        input.readonly(1);
        copy_style(Fl_Output::default_style);
    }

    void soft(uchar x) { } // unimplemented, it acts like true allways
    bool soft() const { return true; }
};

#endif
