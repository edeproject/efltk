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

#ifndef _FL_ROLLER_H_
#define _FL_ROLLER_H_

#include "Fl_Valuator.h"

/** Fl_Roller */
class FL_API Fl_Roller : public Fl_Valuator {
public:

    /** Creates new roller widget using the given position, size, and label string. */
    Fl_Roller(int X,int Y,int W,int H,const char* L=0);

    /** Creates new roller widget using the label, size, alignment, and label width. */
    Fl_Roller(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    enum { // values for type()
        VERTICAL = 0,
        HORIZONTAL = 1
    };

    virtual int handle(int);
    virtual void draw();
};

#endif
