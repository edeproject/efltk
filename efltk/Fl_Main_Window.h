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

#ifndef _FL_MAINWINDOW_H_
#define _FL_MAINWINDOW_H_

#include "Fl_Double_Window.h"
#include "Fl_Window.h"
#include "Fl_Button.h"
#include "Fl_Box.h"
#include "Fl_Widget.h"
#include "Fl_Pack.h"
#include "Fl_Bar.h"
#include "Fl.h"
#include "Fl_Menu_Bar.h"
#include "Fl_Tool_Bar.h"

typedef Fl_Window Fl_Main_WindowType;
//typedef Fl_Double_Window Fl_Main_WindowType;

class Fl_Main_Window : public Fl_Main_WindowType
{
public:
    static Fl_Named_Style* default_style;

    Fl_Main_Window(int x, int y, int w, int h, const char *l=0);
    Fl_Main_Window(int w, int h, const char *l=0);
    ~Fl_Main_Window();

    void menu(Fl_Menu_Bar *w);
    Fl_Menu_Bar *menu();

    void toolbar(Fl_Tool_Bar *w);
    Fl_Tool_Bar *toolbar();

    void view(Fl_Group *w);
    Fl_Group *view();

    void status(Fl_Group *w);
    Fl_Group *status();

protected:
    // If you inherit this class, you get access to pack,
    // where you can add e.g. second toolbar
    Fl_Pack *pack() { return pack_; }

private:
    Fl_Pack   *pack_;
    Fl_Menu_Bar  *menu_;
    Fl_Tool_Bar  *toolbar_;
    Fl_Group  *view_;
    Fl_Group  *status_;
};

#endif
