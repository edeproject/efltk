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

#ifndef _FL_CLOCK_H_
#define _FL_CLOCK_H_

#include "Fl_Widget.h"

// a Fl_Clock_Output can be used to display a program-supplied time:
class FL_API Fl_Clock_Output : public Fl_Widget {
public:
    enum { SQUARE = 0, ANALOG = 0, ROUND, DIGITAL };
    Fl_Clock_Output(int x,int y,int w,int h, const char *l = 0);

    void value(ulong v);	// set to this Unix time
    void value(int,int,int);	// set hour, minute, second

    ulong value() const {return value_;}
    int hour() const {return hour_;}
    int minute() const {return minute_;}
    int second() const {return second_;}

    virtual void draw();
private:
    void draw(int, int, int, int);
    void drawhands(Fl_Color,Fl_Color); // part of draw

    int hour_, minute_, second_;
    ulong value_;
};

// a Fl_Clock displays the current time always by using a timeout:
class FL_API Fl_Clock : public Fl_Clock_Output {
public:
    static Fl_Named_Style* default_style;

    Fl_Clock(int x,int y,int w,int h, const char *l = 0);
    virtual ~Fl_Clock();

    void update();
    virtual int handle(int);
};

#endif
