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

/**
 * Fl_Valuator, base widget for range controls - such as Fl_Slider.
 *
 * events:
 <table border=0 bgcolor=#e8e8e8>
 <tr><td>Event name</td>		<td>When</td></tr>
 <tr><td>FL_VALUATOR_DOWN</td>		<td>When mouse button is pressed down</td></tr>
 <tr><td>FL_VALUATOR_UP</td>		<td>When mouse button is released</td></tr>
 <tr><td>FL_VALUATOR_DRAGGED</td>       <td>When dragged by mouse</td></tr>
 <tr><td>FL_VALUATOR_CHANGED</td>	<td>When value is changed by any event or value(double)</td></tr>
 </table>
 *
 * FL_VALUATOR_CHANGED is NOT sent when value changes by draggin mouse,
 * You must process FL_VALUATOR_DRAGGED for that.
 * Reason: If valuator callback does some heavy calculation,
 * it is possible to process only FL_VALUE_CHANGED when value is really changed.
 * Processing FL_VALUATOR_DRAGGED would cause huge overheat, if calculation is done for all value changes during drag.
 */
class FL_API Fl_Valuator : public Fl_Widget {
public:
    double value() const { return value_; }
    bool value(double newvalue);

    double minimum() const { return minimum_; }
    void minimum(double min) { minimum_ = min; }

    double maximum() const { return maximum_; }
    void maximum(double max) { maximum_ = max; }

    void range(double min, double max) { minimum_ = min; maximum_ = max; }

    double step() const { return step_; }
    void step(double a) { step_ = a; }

    double linesize() const { return linesize_; }
    void linesize(double lsize) { linesize_ = lsize; }

    virtual int format(char *fmt);
    virtual void reset() { value(0); }

    virtual int handle(int event);

protected:
    /** Creates the valuator widget using the given position, size, and label string. */
    Fl_Valuator(int X, int Y, int W, int H, const char* L);

    /** Creates the valuator widget using the label, size, alignment, and label_width. */
    Fl_Valuator(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    double previous_value() const { return previous_value_; }
    void handle_push();
    void handle_drag(double newvalue, Fl_Event_Type cb_event = FL_VALUATOR_DRAGGED);
    void handle_release();

    virtual void value_damage(); // callback whenever value changes
    void set_value(double v) { value_ = v; } // change w/o doing value_damage

private:
    double value_;
    static double previous_value_;
    double minimum_;
    double maximum_;
    double step_;
    double linesize_;

    void ctor_init();
};

#endif
