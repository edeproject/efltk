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

/**
 * The Fl_Main_Window class provides easy interface for applications main windows.
 * It provides automatic placement and creation for typical main window widgets,
 * such as menu bar or tool bar.
 * However, it is possible to bypass auto creation by setting already created widgets
 * for main window object.
 */
class Fl_Main_Window : public Fl_Main_WindowType
{
public:
    /**
     * Create main window with given position/size and label.
     */
    Fl_Main_Window(int x, int y, int w, int h, const char *l=0);

    /**
     * Create main window with given size and label.
     */
    Fl_Main_Window(int w, int h, const char *l=0);

    /** Destructor */
    ~Fl_Main_Window();

    /**
     * Set menu for main window.
     * Menu will be inserted to window and placed correctly.
     */
    void menu(Fl_Menu_Bar *w);
    /**
     * Returns menu for main window. If no menu set, it will be created.
     * It is always safe to call this function.
     */
    Fl_Menu_Bar *menu();

    /**
     * Set tool bar for main window.
     * Tool bar will be inserted to window and placed correctly.
     */
    void toolbar(Fl_Tool_Bar *w);
    /**
     * Returns tool bar for main window. If no tool bar set, it will be created.
     * It is always safe to call this function.
     */
    Fl_Tool_Bar *toolbar();

    /**
     * Set view group for main window.
     * view group will be inserted to window and placed correctly.
     * You may want to call this, if you are e.g. using MDI viewport.
     * It is more clever to set MDI viewport to main window view, than
     * create it as child of default view group.
     */
    void view(Fl_Group *w);
    /**
     * Returns view group for main window. If no view group set, it will be created.
     * It is always safe to call this function.
     */
    Fl_Group *view();

    /**
     * Set status bar widget for main window.
     * Status bar will be inserted at bottom of the window.
     * You may want to call this function, if you need more complex status bar than,
     * single Fl_Box widget.
     */
    void status(Fl_Widget *w);
    /**
     * Returns status bar for main window. If no status bar set, it will be created.
     * @note Created widget is Fl_Box, if you need more complex grouping status bar, use void status(Fl_Widget *w)
     * It is always safe to call this function.
     */
    Fl_Widget *status();

private:
    Fl_Menu_Bar *m_menu;
    Fl_Tool_Bar *m_toolbar;
    Fl_Group    *m_view;
    Fl_Widget   *m_status;
};

#endif
