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

class Fl_Calendar_Button : public Fl_Button {
public:
    Fl_Calendar_Button() : Fl_Button (0,0,10,20) {}
    void preferred_size(int& w,int& h) const { w = 20; }
};

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
    align(FL_ALIGN_LEFT);
    box(FL_DOWN_BOX);
    layout_spacing(0);
    m_input = new Fl_Masked_Input(0,0,10,10);
    m_input->box(FL_FLAT_BOX);
    m_input->callback(Fl_Date_Input::input_callback);
    m_input->mask(Fl_Date_Time::dateInputFormat);
    m_input->layout_align(FL_ALIGN_LEFT);
    m_button = new Fl_Calendar_Button();
    m_button->box(FL_UP_BOX);
    m_button->callback(Fl_Date_Input::button_callback);
    m_button->image(&buttonPixmap);
    m_button->layout_align(FL_ALIGN_LEFT);
    end();
}

void Fl_Date_Input::prepare_layout() {
    Fl_Boxtype bbt = m_button->box();
    m_input->copy_style(style());
    m_input->box(FL_FLAT_BOX);
    m_input->button_color(FL_BLACK);
    m_button->copy_style(style());
    m_button->box(bbt);

    // We only need to set width for m_input
    int ww = dateInputWidth(true);
    m_input->resize(m_input->h(),m_input->y(),ww,h());
}

int Fl_Date_Input::dateInputWidth(bool set_font) const {
    if (set_font)
        fl_font(text_font(), float(text_size()));
    return (int) fl_width("00/00/0000 ") + 2;
}

void Fl_Date_Input::preferred_size(int& w,int &h) const {
    w = dateInputWidth(true) + m_button->w() + box()->dw();
    h = int(fl_height()+fl_descent()) + box()->dh() + 2;
}

void Fl_Date_Input::layout() {
    prepare_layout();
    Fl_Group::layout();
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
//-------------------------------------------------------------------------------
Fl_Date_Time_Input::Fl_Date_Time_Input(int xx,int yy,int ww,int hh,const char *lbl)
: Fl_Date_Input(xx,yy,ww,hh,lbl) {
    begin();
    m_timeInput = new Fl_Masked_Input(0,0,10,10," ");
    m_timeInput->box(FL_FLAT_BOX);
    m_timeInput->callback(Fl_Date_Input::input_callback);
    m_timeInput->mask(Fl_Date_Time::timeInputFormat);
    m_timeInput->label_width(16);
    m_timeInput->align(FL_ALIGN_LEFT);
    m_timeInput->layout_align(FL_ALIGN_LEFT);
    end();
}

void Fl_Date_Time_Input::prepare_layout() {
    Fl_Date_Input::prepare_layout();

    m_timeInput->copy_style(style());
    m_timeInput->box(FL_FLAT_BOX);
    m_timeInput->button_color(FL_BLACK);

    // We only need to set width for m_input
    int ww = timeInputWidth(true);
    m_timeInput->resize(m_timeInput->h(),m_timeInput->y(),ww,h());
}

int Fl_Date_Time_Input::timeInputWidth(bool set_font) const {
    if (set_font)
        fl_font(text_font(), float(text_size()));
    return (int) fl_width("00:00AM ") + 2;
}

void Fl_Date_Time_Input::preferred_size(int& w,int &h) const {
    w = dateInputWidth(true) + timeInputWidth(false) + m_button->w() + box()->dw() + m_timeInput->label_width();
    h = int(fl_height()+fl_descent()) + box()->dh() + 2;
}

void Fl_Date_Time_Input::value(const char *v) {
    m_input->value(v);
}

const char *Fl_Date_Time_Input::value() {
    return m_input->value();
}

void Fl_Date_Time_Input::date_value(Fl_Date_Time dt) {
    m_input->value(dt.date_string().c_str());
}

Fl_Date_Time Fl_Date_Time_Input::date_value() {
    return Fl_Date_Time(m_input->value());
}
