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

#ifndef _FL_HELP_DIALOG_H_
#define _FL_HELP_DIALOG_H_

#include "Fl.h"
#include "Fl_Main_Window.h"
#include "Fl_Menu_Bar.h"
#include "Fl_Item_Group.h"
#include "Fl_Item.h"
#include "Fl_Group.h"
#include "Fl_Button.h"
#include "Fl_File_Dialog.h"
#include "Fl_Simple_Html.h"

/** Fl_Help_Dialog */
class Fl_Help_Dialog : public Fl_Main_Window
{
public:
    Fl_Help_Dialog(int x, int y, int w, int h, const char *l);
    Fl_Help_Dialog(int w, int h, const char *l);
    virtual ~Fl_Help_Dialog();

    void init();
    void make_group(int w, int h);

    void load(const char *f) { load_file(f); }
    void load_file(const char *f);
    void previous_url();
    void next_url();
    void open_file();

    // Method add/remove from history
    void push_prev(const char *url);
    char *pop_prev();

    void push_next(const char *url);
    char *pop_next();

private:
    Fl_Simple_Html *htmlWidget;

    static void cb_close(Fl_Widget*, void*);
    static void cb_back(Fl_Button*, void*);
    static void cb_next(Fl_Button*, void*);
    static void cb_open(Fl_Button*, void*);
    static void cb_html_link(Fl_Widget *w, void *d);

    char *prev_hist[10];
    char *next_hist[10];

    Fl_Button *back, *next;
};

#endif
