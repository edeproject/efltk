/***************************************************************************
                          Fl_Date_Time_Input.cpp  -  description
                             -------------------
    begin                : Mon Nov 11 2002
    copyright            : (C) 2002 by Alexey Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <efltk/Fl_Date_Time_Input.h>
#include <efltk/Fl_Masked_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Pixmap.h>
#include <efltk/Fl_Calendar.h>
#include <efltk/fl_draw.h>

static const char * calendar_xpm[] = {
    "15 15 7 1",
    "   c None",
    ".  c #000000",
    "+  c #FFFFFF",
    "@  c #C0C0C0",
    "#  c #008080",
    "$  c #0000FF",
    "%  c #800000",
    " ..........    ",
    " .$$$$$$$$.    ",
    " ..............",
    " .+@+.$$$$$$$$.",
    " .@%%..........",
    " .+%+.+@+@+@+@.",
    " .@%%.@%%%%%@+.",
    " .+%+.+@+@%%+@.",
    " .@%%.@+@%%+@+.",
    " .+@+.+@%%+@+@.",
    " .@$$.@+%%@+@+.",
    " .+@+.+@+@+@+@.",
    " .....@$$$$$$$.",
    "     .+@+@+@+@.",
    "     .........."};

void Fl_Date_Input::input_callback(Fl_Widget *di,void *) {
    Fl_Group *parent = (Fl_Group *) di->parent();
    if (parent)
        parent->do_callback(FL_DATA_CHANGE);
}

void Fl_Date_Input::button_callback(Fl_Widget *button,void *) {
    Fl_Date_Input *dateInput = (Fl_Date_Input *) button->parent();
    Fl_Popup_Calendar calendar(dateInput);
    calendar.date(dateInput->date_value());
    if (calendar.popup())
        dateInput->date_value(calendar.date());
}

static Fl_Pixmap buttonPixmap(calendar_xpm);

Fl_Date_Input::Fl_Date_Input(int xx,int yy,int ww,int hh,const char *lbl)
: Fl_Group(xx,yy,ww,hh,lbl) {
    box(FL_NO_BOX);
    m_input = new Fl_Masked_Input(0,0,10,10);
    m_input->callback(Fl_Date_Input::input_callback);
    m_input->mask(Fl_Date_Time::dateInputFormat);
    m_button = new Fl_Button(0,0,10,10);
    m_button->callback(Fl_Date_Input::button_callback);
    m_button->image(&buttonPixmap);
    end();
}

void Fl_Date_Input::layout() {
    Fl_Boxtype ibt = m_input->box();
    Fl_Boxtype bbt = m_button->box();
    m_input->copy_style(style());
    m_input->box(ibt);
    m_input->button_color(FL_BLACK);
    m_button->copy_style(style());
    m_button->box(bbt);

    int border = box()->dx();
    int buttonSize = h() - box()->dh();
    m_input->resize(box()->dx(),box()->dy(),w()-box()->dw()-buttonSize,buttonSize);
    m_button->resize(w()-border-buttonSize,border,buttonSize,buttonSize);
}

void Fl_Date_Input::value(const char *v) {
    m_input->value(v);
}

const char *Fl_Date_Input::value() {
    return m_input->value();
}

void Fl_Date_Input::date_value(Fl_Date_Time dt) {
    m_input->value(dt.date_string().c_str());
}

Fl_Date_Time Fl_Date_Input::date_value() {
    return Fl_Date_Time(m_input->value());
}
