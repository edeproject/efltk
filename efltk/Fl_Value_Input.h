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

#ifndef _FL_VALUE_INPUT_H_
#define _FL_VALUE_INPUT_H_

#include "Fl_Valuator.h"
#include "Fl_Float_Input.h"

/** Fl_Value_Input */
class FL_API Fl_Value_Input : public Fl_Valuator {
public:
    Fl_Value_Input(int x,int y,int w,int h,const char *l=0);
    ~Fl_Value_Input();

    Fl_Float_Input input;

    virtual int handle(int);
    virtual void draw();
    virtual void layout();

private:
    virtual void value_damage(); // cause damage() due to value() changing
    static void input_cb(Fl_Widget*,void*);

    void increment_cb();
    static void repeat_callback(void* v);
};

#endif
