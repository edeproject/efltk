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

#ifndef _FL_INPUT_BROWSER_H_
#define _FL_INPUT_BROWSER_H_

#include "Fl_Input.h"
#include "Fl_Menu_.h"
#include "Fl_Menu_Window.h"

class ComboBrowser;
class ComboWindow;

class Fl_Input_Browser : public Fl_Menu_ {
public:
    static Fl_Named_Style* default_style;
    enum { // values for type()
        NORMAL = 0,
        NONEDITABLE = 1,
        INDENTED = 2,
        NONEDITABLE_INDENTED = 3
    };

    Fl_Input_Browser(int,int,int,int,const char * = 0);
    virtual ~Fl_Input_Browser();

    void popup();
    void hide_popup();
    virtual int popup(int x, int y, int w, int h) { Fl_Input_Browser::popup(); return Fl_Menu_::popup(x,y,w,h); }

    virtual void draw();
    virtual int handle(int);

    void clear() { Fl_Menu_::clear(); item(0); }

    void value(const char *v) { input()->value(v); }
    const char *value() { return input()->value(); }

    Fl_Input *input() { return &m_input; }
    
private:
	Fl_Input m_input;

    ComboWindow *win;
    ComboBrowser *list;

    friend class ComboWindow;
    friend class ComboBrowser;

    bool over_now, over_last;
    static void input_cb(Fl_Input *in, Fl_Input_Browser *d);
};

#endif
