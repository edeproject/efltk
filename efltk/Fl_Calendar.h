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

#ifndef _FL_CALENDAR_H_
#define _FL_CALENDAR_H_

#include "Fl_Popup_Window.h"
#include "Fl_Date_Time.h"
#include "Fl_Box.h"
#include "Fl_Button.h"

/** Fl_Calendar */
class Fl_Calendar : public Fl_Group {
public:
    static Fl_Named_Style* default_style;

    /** The traditional constructor creates the calendar using the position, size, and label. */
    Fl_Calendar(int x,int y,int w,int h,const char *lbl=0L);

    /** The new style constructor creates the calendar using the label, size, alignment, and label_width. */
    Fl_Calendar(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    virtual void layout();
    virtual void draw();
    virtual void measure(int& w,int& h) const;

    virtual void reset() { date(Fl_Date_Time::Now()); }

    void date(Fl_Date_Time dt);
    Fl_Date_Time date() const;

    void dayButtonClicked(unsigned day);
    void switchButtonClicked(int monthChange);

private:
    static void cbDayButtonClicked(Fl_Widget *,void *);
    static void cbSwitchButtonClicked(Fl_Widget *,void *);

    Fl_Group     *m_headerBox;
    Fl_Group     *m_buttonBox;
    Fl_Box       *m_monthNameBox;
    Fl_Box       *m_dayNameBoxes[7];
    Fl_Button    *m_dayButtons[31];
    Fl_Button    *m_switchButtons[4];
    Fl_Date_Time  m_date;
    Fl_String     m_headerLabel;
    int           m_activeButtonIndex;

    void ctor_init(int x,int y,int w,int h);
};

class Fl_Popup_Calendar : public Fl_Popup_Window {
public:
    static Fl_Named_Style* default_style;

    Fl_Popup_Calendar(Fl_Widget *dateControl=NULL);

    Fl_Calendar *calendar() { return m_calendar; }

    void clicked() { set_value(); }
    void layout();
    void draw();
    int  handle(int);

    void date(Fl_Date_Time dt) { m_calendar->date(dt); }
    Fl_Date_Time date() const       { return m_calendar->date(); }

    bool popup();
    // Popup calendar, relative to widget
    bool popup(Fl_Widget *dateControl, int X, int Y, int W=0, int H=0);

private:
    friend class Fl_Calendar;
    Fl_Calendar *m_calendar;
    Fl_Widget   *m_dateControl;
};

#endif
