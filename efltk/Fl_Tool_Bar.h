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

#ifndef _FL_TOOL_BAR_H_
#define _FL_TOOL_BAR_H_

#include "Fl_Bar.h"
#include "Fl_Menu_Button.h"

/** Fl_Tool_Bar */
class Fl_Tool_Bar : public Fl_Bar
{
public:
    static Fl_Named_Style* default_style;

    /** Creates new toolbar widget using the given position, size, and label string. */
    Fl_Tool_Bar(int x, int y, int w, int h, const char *label=0);

    /** Creates new toolbar widget using the label, size, alignment, and label width. */
    Fl_Tool_Bar(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=-1);

    /** Destructor */
    ~Fl_Tool_Bar();

    static int button_w;
    static int button_h;
    Fl_Widget *add_button(const char *label, const char *tip, Fl_Image *image, Fl_Callback *cb);
    Fl_Widget *add_divider();

    virtual void draw();
    virtual void layout();
    virtual int handle(int ev);

    static void button_glyph(const Fl_Widget* widget, int glyph, int x,int y,int w,int h, Fl_Flags flags);

    // Space between items
    int spacing() { return space_; }
    void spacing(int v) { space_ = v; }

private:
    int space_;

    Fl_Menu_ *menu_;
    Fl_Widget *menu_but, *right_;
    static void cb_menu(Fl_Widget *w, void *data);
};

#endif
