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

#ifndef _FL_SCROLL_H_
#define _FL_SCROLL_H_

#include "Fl_Group.h"
#include "Fl_Scrollbar.h"

class FL_API Fl_Scroll : public Fl_Group {
    Fl_End endgroup;
public:
    Fl_Scroll(int X,int Y,int W,int H,const char*l=0);

    enum { // values for type()
        HORIZONTAL = 1,
        VERTICAL = 2,
        BOTH = 3,
        ALWAYS_ON = 4,
        HORIZONTAL_ALWAYS = 5,
        VERTICAL_ALWAYS = 6,
        BOTH_ALWAYS = 7
    };

    virtual int handle(int);
    virtual void layout();
    virtual void draw();

    int xposition() const {return xposition_;}
    int yposition() const {return yposition_;}
    void position(int, int);

    // Set offset, from edge to widget
    int edge_offset() { return edge_offset_; }
    void edge_offset(int v) { edge_offset_ = v; }

    void bbox(int&,int&,int&,int&);
    Fl_Scrollbar scrollbar;
    Fl_Scrollbar hscrollbar;

private:
    int edge_offset_;
    int xposition_, yposition_;
    int layoutdx, layoutdy;
    int scrolldx, scrolldy;
    static void hscrollbar_cb(Fl_Widget*, void*);
    static void scrollbar_cb(Fl_Widget*, void*);
    static void draw_clip(void*,int,int,int,int);
};

#endif
