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

#ifndef _FL_ITEM_H_
#define _FL_ITEM_H_

#include "Fl_Widget.h"

/** Fl_Item */
class FL_API Fl_Item : public Fl_Widget {
public:
    static Fl_Named_Style* default_style;

    enum { // values for type(), should match Fl_Button
        NORMAL = 0,
        TOGGLE = 1,
        RADIO  = 2,

        //Menubar doesnt try to execute this, it will send events there.
        //This allows widgets like, MDI buttons in menubar
        NO_EXECUTE = 3
    };

    Fl_Item(const char* label = 0);
    virtual void draw();
    virtual void layout();

    int x_offset() { return x_offset_; }
    void x_offset(int o) { x_offset_ = o; w(0); }

private:
    int x_offset_;
};

#endif
