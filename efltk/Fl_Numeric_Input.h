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

#ifndef _FL_NUMERIC_INPUT_H_
#define _FL_NUMERIC_INPUT_H_

#include "Fl_Input.h"

class FL_API Fl_Numeric_Input : public Fl_Input {
public:
    Fl_Numeric_Input(int x,int y, int w,int h,const char* l = 0) : Fl_Input(x,y,w,h,l) {when(FL_WHEN_ENTER_KEY|FL_WHEN_RELEASE);}

    void value(double);
    void value(int);
    void value(const char* s) { Fl_Input::value(s); }
    const char* value() const { return Fl_Input::value(); }

    virtual int handle(int);

protected:
    int handle_arrow(int);
};

#endif
