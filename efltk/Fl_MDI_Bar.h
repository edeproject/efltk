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

#ifndef _FL_MDI_BAR_H_
#define _FL_MDI_BAR_H_

#include "Fl_Group.h"
#include "Fl_MDI_Window.h"

/** Fl_MDI_Bar */
class Fl_MDI_Bar : public Fl_Group
{
public:
    static Fl_Named_Style *default_style;

    Fl_MDI_Bar(int x, int y, int w, int h, const char *l=0);
    virtual ~Fl_MDI_Bar();

    virtual void layout();

    int spacing() { return spacing_; }
    void spacing(int val) { spacing_ = val; }

    int max_button_width() { return max_button_width_; }
    void max_button_width(int w) { max_button_width_ = w; }

    Fl_Widget *find_task(Fl_MDI_Window *win);

    // These are called by Fl_MDI_Viewport..
    void add_task(Fl_MDI_Window *win);
    void remove_task(Fl_MDI_Window *win);
    void update_task(Fl_MDI_Window *win);
    void update_tasks();

private:
    int max_button_width_;
    int spacing_;
};

#endif
