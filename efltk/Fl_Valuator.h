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

#ifndef _FL_VALUATOR_H_
#define _FL_VALUATOR_H_

#include "Fl_Widget.h"

class FL_API Fl_Valuator : public Fl_Widget {
public:
    double value() const {return value_;}
    int value(double);

    float minimum() const {return minimum_;}
    void minimum(double a) {minimum_ = float(a);}

    float maximum() const {return maximum_;}
    void maximum(double a) {maximum_ = float(a);}

    void range(double a, double b) {minimum_ = float(a); maximum_ = float(b);}

    float step() const {return step_;}
    void step(double a) {step_ = float(a);}

    float linesize() const {return linesize_;}
    void linesize(double a) {linesize_ = float(a);}

    virtual int format(char*);

    int handle(int);

protected:
    Fl_Valuator(int X, int Y, int W, int H, const char* L);

    double previous_value() const { return previous_value_; }
    void handle_push() { previous_value_ = value_; }
    void handle_drag(double newvalue);
    void handle_release();

    virtual void value_damage(); // callback whenever value changes
    void set_value(double v) {value_ = v;} // change w/o doing value_damage

private:
    double value_;
    static double previous_value_;
    float minimum_;
    float maximum_;
    float step_;
    float linesize_;
};

#endif
