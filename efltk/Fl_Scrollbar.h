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

#ifndef _FL_SCROLLBAR_H_
#define _FL_SCROLLBAR_H_

#include "Fl_Slider.h"

class FL_API Fl_Scrollbar : public Fl_Slider {

public:
    static Fl_Named_Style* default_style;
    Fl_Scrollbar(int x,int y,int w,int h, const char *l = 0);

    int value() {return int(Fl_Slider::value());}
    int value(int position, int size, int top, int total);

    int pagesize() const {return pagesize_;}
    void pagesize(int a) {pagesize_ = a;}

    virtual void draw();
    virtual int handle(int);

private:
    int pagesize_;
    static void timeout_cb(void*);
    void increment_cb();
};

#endif
