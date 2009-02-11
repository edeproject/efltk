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

#ifndef _FL_CHOICE_H_
#define _FL_CHOICE_H_

#include "Fl_Menu_.h"

/**
 * This is a button that when pushed pops up a menu (or hierarchy of menus) defined by an array of child items. 
 * The appearance is designed to look like a Windows "combo box" but it is somewhat different in that it does not contain a text editor, 
 * also the menu pops up with the current item under the cursor, which is immensely easier to use once you get used to it. Motif calls this an OptionButton. 
 *
 * The user can change the value by popping up the menu by clicking anywhere in the widget and moving the cursor to a different item, 
 * or by typing up and down arrow keys to cycle amoung the items. Typing the shortcut() of any of the items will also change the value to that item (The '&' character in item names are only looked at when the menu is popped up, however).
 *
 * The menu will also pop up in response to shortcuts indicated by putting a '&' character in the label() or to the shortcut() of the Fl_Choice widget itself. The user can then use arrow keys or the mouse to change the selected item.
 *
 * When the user changes the value() the callback is done.
 */
class FL_API Fl_Choice : public Fl_Menu_ {
public:
    static Fl_Named_Style* default_style;

     /** Creates a new choice widget using the given position, size, and label string. */
    Fl_Choice(int x, int y, int w, int h, const char *l=0);

    /** The new style constructor creates the choice widget using the label, size, alignment, and label_width. */
    Fl_Choice(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

     /**
     * The value is the index into the Fl_Menu array of the last item chosen by the user. 
     * It is zero initially. You can set it as an integer. 
     * The set routines return non-zero if the new value is different than the old one. Changing it causes a redraw(). 
     */
    int value(int v);

     /**
     * The value is the index into the Fl_Menu array of the last item chosen by the user. 
     * It is zero initially. You can set it as an integer. 
     * Returns current selected item index.
     */
    int value() const { return Fl_Menu_::value(); }

    virtual int popup(int X, int Y, int W, int H);
    virtual int handle(int);
    virtual void draw();
    virtual void reset() { value(0); }
private:
    void ctor_init();
};

#endif
