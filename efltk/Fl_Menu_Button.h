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

#ifndef _FL_MENU_BUTTON_H_
#define _FL_MENU_BUTTON_H_

#include "Fl_Menu_.h"

class FL_API Fl_Menu_Button : public Fl_Menu_ {
public:
    static Fl_Named_Style* default_style;

    Fl_Menu_Button(int,int,int,int,const char * =0);

    // values for type:
    enum {
        NORMAL = GROUP_TYPE,
        POPUP1,
        POPUP2,
        POPUP12,
        POPUP3,
        POPUP13,
        POPUP23,
        POPUP123
    };

    virtual int handle(int);
    virtual void draw();

    virtual int popup();
    virtual int popup(int X, int Y, int W=0, int H=0);
};

#endif
