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

#ifndef _FL_BUTTON_H_
#define _FL_BUTTON_H_

#include "Fl_Widget.h"

class FL_API Fl_Button : public Fl_Widget {
public:
    static Fl_Named_Style* default_style;

    Fl_Button(int,int,int,int,const char * = 0);

    // values for type(), should match Fl_Item
    enum {
        NORMAL = 0,
        TOGGLE = 1,
        RADIO  = 2,
        HIDDEN = 3
    };

    bool value() const { return Fl_Widget::value(); }
    bool value(bool);
    bool set();
    bool clear();
    void setonly();

    virtual void draw();
    virtual int handle(int);

protected:
    void draw(int glyph, int glyph_width) const;
};

#endif
