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

#ifndef _FL_DATE_TIME_INPUT_H_
#define _FL_DATE_TIME_INPUT_H_

#include "Fl_Group.h"
#include "Fl_Date_Time.h"

class Fl_Masked_Input;
class Fl_Calendar_Button;

/** Fl_Date_Input */
class FL_API Fl_Date_Input : public Fl_Group {
public:
    static Fl_Named_Style* default_style;

    /** Creates a new date input widget using the given position, size, and label. */
    Fl_Date_Input(int,int,int,int,const char * = 0);

    /** Creates the date input widget using the label, size, alignment, and label_width. */
    Fl_Date_Input(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    void value(const char *);
    const char *value();

    void date_value(Fl_Date_Time);
    Fl_Date_Time date_value();

    virtual void draw();
    virtual void preferred_size(int& w,int &h) const;

protected:
    static void input_callback(Fl_Widget *,void *);
    static void button_callback(Fl_Widget *,void *);

    void ctor_init();

    Fl_Masked_Input     *m_input;
    Fl_Calendar_Button  *m_button;
};

class FL_API Fl_Date_Time_Input : public Fl_Date_Input {
public:
    static Fl_Named_Style* default_style;

    /** Creates a new date time input widget using the given position, size, and label. */
    Fl_Date_Time_Input(int,int,int,int,const char * = 0);

    /** Creates the date time input widget using the label, size, alignment, and label_width. */
    Fl_Date_Time_Input(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    void value(const char *);
    const char *value();

    void date_time_value(Fl_Date_Time);
    Fl_Date_Time date_time_value();

    virtual void draw();
    virtual void preferred_size(int& w,int &h) const;

protected:
    Fl_Masked_Input  *m_timeInput;
    char                     m_buffer[20];

    void ctor_init();
};

class FL_API Fl_Date_Interval_Input : public Fl_Date_Input {
public:
    static Fl_Named_Style* default_style;

    /** Creates a new date interval input widget using the given position, size, and label. */
    Fl_Date_Interval_Input(int,int,int,int,const char * = 0);

    /** Creates the date interval input widget using the label, size, alignment, and label_width. */
    Fl_Date_Interval_Input(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    void value2(const char *);
    const char *value2();

    void date2_value(Fl_Date_Time);
    Fl_Date_Time date2_value();

    virtual void draw();
    virtual void preferred_size(int& w,int &h) const;

protected:
    Fl_Masked_Input     *m_input2;
    Fl_Calendar_Button  *m_button2;

    void ctor_init();
};

#endif
