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

#ifndef _FL_TABS_H_
#define _FL_TABS_H_

#include "Fl_Group.h"

class FL_API Fl_Tabs : public Fl_Group {
public:
    static Fl_Named_Style* default_style;
    Fl_Tabs(int,int,int,int,const char * = 0);

    Fl_Widget *value();
    int value(Fl_Widget *);

    Fl_Widget *push() const {return push_;}
    int push(Fl_Widget *);

    Fl_Widget *which(int event_x, int event_y);

    virtual int handle(int);
    virtual void draw();

private:
    friend class Fl_Group;
    Fl_Widget *push_;
    int tab_positions(int*, int*);
    int tab_height();
    void draw_tab(int x1, int x2, int W, int H, Fl_Widget* o, int sel=0);
    int tabH;
};

#endif
