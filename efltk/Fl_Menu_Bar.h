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

#ifndef _FL_MENU_BAR_H_
#define _FL_MENU_BAR_H_

#include "Fl_Widget.h"
#include "Fl_Menu_.h"
#include "Fl_Menu_Window.h"

/** Fl_Menu_Bar */
class Fl_Menu_Bar : public Fl_Menu_ {
public:
    static Fl_Named_Style* default_style;

    /** Creates new menu bar widget using the given position, size, and label. */
    Fl_Menu_Bar(int x,int y,int w,int h,const char *l=0);

    /** Creates new menu bar widget using the label, size, alignment, and label_width. */
    Fl_Menu_Bar(const char* l = 0,int layout_size=20,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=-1);

    virtual int handle(int ev);
    virtual void layout();
    virtual void draw();

    int popup(int X, int Y, int W, int H);

    // This one is layouted to most right of the menubar (often help)
    void right_layout(Fl_Widget *w) { right_ = w; }
    Fl_Widget *right_layout() { return right_; }

    // If this is set to FALSE, then menubar won't layout to many lines when it's too small.
    void layout_menubar(bool val) { do_layout = val; }
    bool layout_menubar() { return do_layout; }

private:
    Fl_Widget *right_;

    void ctor_init();    

    int highlight_, last_highlight_;
    int selected_, last_selected_;
    int lines;

    bool do_layout;
};

#endif
