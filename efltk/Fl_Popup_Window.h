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
 * Author : Alexey Parshin
 * Email  : alexey@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_POPUP_WINDOW_H_
#define _FL_POPUP_WINDOW_H_

#include "Fl_Menu_Window.h"

class Fl_Popup_Window : public Fl_Menu_Window {
public:
    Fl_Popup_Window(int w, int h, const char *label = 0);
    Fl_Popup_Window(int x,int y,int w, int h, const char *label = 0);

    bool show_popup();
    virtual int handle(int event);
};

#endif
