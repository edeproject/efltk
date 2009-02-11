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

/** 
 * Fl_Clock_Output can be used to display a program-supplied time 
 */
class FL_API Fl_Clock_Output : public Fl_Widget {
public:
    enum { SQUARE = 0, ANALOG = 0, ROUND, DIGITAL };
    Fl_Clock_Output(int x,int y,int w,int h, const char *l = 0);
    Fl_Clock_Output(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=-1);

    void value(ulong v);    // set to this Unix time
    void value(int,int,int);    // set hour, minute, second

    ulong value() const {return value_;}
    int hour() const {return hour_;}
    int minute() const {return minute_;}
    int second() const {return second_;}

    virtual void draw();
private:
    void draw(int, int, int, int);
    void drawhands(Fl_Color,Fl_Color); // part of draw

    void ctor_init();

    int hour_, minute_, second_;
    ulong value_;
};

/** 
 * Fl_Clock displays the current time always by using a timeout
 */
class FL_API Fl_Clock : public Fl_Clock_Output {
public:
    static Fl_Named_Style* default_style;

    /** Creates a new clock widget using the given position, size, and label. */
    Fl_Clock(int x,int y,int w,int h, const char *l = 0)
    : Fl_Clock_Output(x, y, w, h, l) {}

    /** The new style constructor creates the clock widget using the label, size, alignment, and label_width. */
    Fl_Clock(const char* l = 0,int layout_size=100,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=-1)
    : Fl_Clock_Output(l,layout_size,layout_al,label_w) {}

    virtual ~Fl_Clock();

    void update();
    virtual int handle(int);
};

#endif
