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

#ifndef _FL_DIAL_H_
#define _FL_DIAL_H_

#include "Fl_Valuator.h"

/** Fl_Dial */
class FL_API Fl_Dial : public Fl_Valuator {

public:
    static Fl_Named_Style* default_style;

    /** Creates the dial widget using the given position, size, and label string. */
    Fl_Dial(int x,int y,int w,int h, const char *l = 0);

    /** Creates the dial widget using the label, size, alignment, and label_width. */
    Fl_Dial(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    // values for type()
    enum {
        NORMAL = 0,
        LINE,
        FILL
    };

    short angle1() const {return a1;}
    void angle1(short a) {a1 = a;}
    short angle2() const {return a2;}
    void angle2(short a) {a2 = a;}
    void angles(short a, short b) {a1 = a; a2 = b;}

    virtual int handle(int);
    virtual void draw();

private:
    short a1,a2;
};

#endif
