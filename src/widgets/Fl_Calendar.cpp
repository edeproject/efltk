/***************************************************************************
                          Fl_Calendar.cpp  -  description
                             -------------------
    begin                : Sun Aug 18 2002
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

#include <efltk/Fl_Calendar.h>
#include <efltk/Fl.h>

// For NLS stuff
#include "../core/fl_internal.h"

static const char *weekDayLabels[7] = {
    "Su","Mo","Tu","We","Th","Fr","Sa"
};

static const char *monthDayLabels[31] = {
    "1","2","3","4","5","6","7","8","9","10",
    "11","12","13","14","15","16","17","18","19","20",
    "21","22","23","24","25","26","27","28","29","30",
    "31"
};

static const char *switchLabels[4] = {
    "@-1<<","@-1<","@-1>","@-1>>"
};

static const int monthChanges[4] = {
    -12,-1,1,12
};

// Callback function for day buttons
void Fl_Calendar::cbDayButtonClicked(Fl_Widget *button, void *param) {
    if (Fl::event() == FL_BUTTON_PRESSED) {
        Fl_Calendar *c = (Fl_Calendar *)button->parent()->parent();
        c->dayButtonClicked((unsigned)param);
    }
}

// Callback function for switch buttons
void Fl_Calendar::cbSwitchButtonClicked(Fl_Widget *button, void *param) {
    if (Fl::event() == FL_BUTTON_PRESSED) {
        Fl_Calendar *c = (Fl_Calendar *)button->parent();
        c->switchButtonClicked((int)param);
    }
}

void Fl_Calendar::dayButtonClicked(unsigned day) {
    if (day < 1 || day > 31) return;
    m_activeButtonIndex = day - 1;
    redraw();
    do_callback(FL_DATA_CHANGE);
}

void Fl_Calendar::switchButtonClicked(int monthChange) {
    short year, month, day;
    m_date.decode_date(&year,&month,&day);
    month += monthChange;
    if (month < 1) {
        month += 12;
        year--;
    }
    if (month > 12) {
        month -= 12;
        year++;
    }
    Fl_Date_Time newDate(year,month,day);
    date(newDate);
}

static void revert(Fl_Style* s) {
    s->color = FL_GRAY;
    s->button_color = FL_GRAY;
    s->box = FL_FLAT_BOX;
    s->button_box = FL_THIN_UP_BOX;
    s->text_font = FL_HELVETICA_BOLD;
}

static Fl_Named_Style style("Calendar", revert, &Fl_Calendar::default_style);
Fl_Named_Style* Fl_Calendar::default_style = &::style;

// ctor initializer - used in both ctors
void Fl_Calendar::ctor_init(int x,int y,int w,int h) {
    style(default_style);
    unsigned i;
    // Header box
    m_headerBox = new Fl_Group(x,y,w,32);
    m_monthNameBox = new Fl_Box(x,0,w-64,16);
    m_monthNameBox->box(FL_NO_BOX);

    // NLS stuff
    for (i=0; i<7;i++) weekDayLabels[i]=_(weekDayLabels[i]);

    // Weekday headers
    for (i = 0; i < 7; i++) {
        m_dayNameBoxes[i] = new Fl_Box(x+i*16,y+16,16,16,weekDayLabels[i]);
    }
    m_headerBox->end();

    // Day buttons, correct positions are set by resize()
    m_buttonBox = new Fl_Group(0,32,w,64);
    m_buttonBox->box(FL_FLAT_BOX);
    for (i = 0; i < 31; i++) {
        Fl_Button *btn = new Fl_Button(0,0,16,16,monthDayLabels[i]);
        m_dayButtons[i] = btn;
        btn->callback(Fl_Calendar::cbDayButtonClicked, (void *)(i+1));
    }
    m_buttonBox->end();

    // Switch buttons, correct positions are set by resize()
    for (i = 0; i < 4; i++) {
        m_switchButtons[i] = new Fl_Button(x,y,16,16,switchLabels[i]);
        m_switchButtons[i]->callback(Fl_Calendar::cbSwitchButtonClicked, (void *)monthChanges[i]);
        m_switchButtons[i]->label_type(FL_SYMBOL_LABEL);
    }

    end();
    date(Fl_Date_Time::Now());
}

// Traditional ctor
Fl_Calendar::Fl_Calendar(int x,int y,int w,int h,const char *lbl)
: Fl_Group(x,y,w,h,lbl) {
    ctor_init(x,y,w,h);
}

// New style ctor
Fl_Calendar::Fl_Calendar(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Group (l,layout_size,layout_al,label_w) 
{
    ctor_init(0,0,w(),h());
}

void Fl_Calendar::layout() {
    int xx=0, yy=0;
    int ww = w(), hh = h();
    box()->inset(xx,yy,ww,hh);
    unsigned i;

    int bh = hh / 10;
    int bw = ww / 7;
    ww = bw * 7;
    hh = hh / bh * bh;

    xx = (w()-ww)/2+1;
    if(xx<box()->dx()) xx=box()->dx();

    // resize header
    m_headerBox->resize(xx,yy,ww,bh * 2+2);
    m_monthNameBox->resize(xx,0,ww,bh);

    for (i=0; i < 7; i++) {
        m_dayNameBoxes[i]->resize(i*bw,bh+2,bw,bh);
    }

    // compute the month start date
    short year, month, day;
    if ((double)m_date < 1) m_date = Fl_Date_Time::Now();
    m_date.decode_date(&year,&month,&day);
    Fl_Date_Time    monthDate(year,month,1);
    m_headerLabel = monthDate.month_name() + ", " + Fl_String(year);

    m_monthNameBox->label(m_headerLabel.c_str());

    // resize day buttons
    m_buttonBox->resize(xx,bh*2+yy+2,ww,hh-bh*2);
    int dayOffset   = monthDate.day_of_week()-1;
    int daysInMonth = monthDate.days_in_month();
    int weekOffset  = 0;
    for (i = 0; i < 31; i++) {
        Fl_Button *btn = m_dayButtons[i];
        btn->resize(dayOffset*bw,weekOffset,bw,bh);
        dayOffset++;
        if ((int)i < daysInMonth) {
            if (dayOffset > 6) {
                dayOffset = 0;
                weekOffset += bh;
            }
            btn->show();
        }
        else  btn->hide();
    }
    m_buttonBox->size(bw*7,bh*6);

    int sby = m_buttonBox->y() + m_buttonBox->h();

    for (i = 0; i < 2; i++)
        m_switchButtons[i]->resize(xx+i*bw,sby,bw,bh);

    int x1 = ww - bw * 2;
    for (i = 2; i < 4; i++) {
        m_switchButtons[i]->resize(xx+x1+(i-2)*bw,sby,bw,bh);
    }

   //Clear layout flags
    Fl_Widget::layout();
}

void Fl_Calendar::draw() {
    Fl_Color btn_color = fl_color_average(button_color(), FL_WHITE, .4f);
    Fl_Color btn_color_hl = fl_color_average(button_color(), FL_GRAY, .5f);

    unsigned i;

    for (i = 0; i < 31; i++) {
        Fl_Button *btn = m_dayButtons[i];
        btn->box(button_box());
        btn->color(btn_color);
        btn->highlight_color(btn_color_hl);
        btn->label_font(label_font());
        btn->label_color(label_color());
        btn->label_size(label_size());
        if((int)i==m_activeButtonIndex) {
            btn->box(FL_FLAT_BOX);
            btn->color(button_color());
        }
    }

    for (i = 0; i < 4; i++) {
        m_switchButtons[i]->box(button_box());
        m_switchButtons[i]->color(btn_color);
        m_switchButtons[i]->label_color(button_color());
        m_switchButtons[i]->highlight_color(btn_color_hl);
    }

    for (i=0; i < 7; i++) {
        m_dayNameBoxes[i]->box(button_box());
        m_dayNameBoxes[i]->color(button_color());
        m_dayNameBoxes[i]->label_color(label_color());
        m_dayNameBoxes[i]->label_size(label_size());
//       if(weekDayLabels[i][0] == 'S')
        if(i==0 || i==6)       
            m_dayNameBoxes[i]->label_color(FL_RED);
    }

    m_monthNameBox->label_font(text_font());
    m_monthNameBox->label_size(text_size());
    m_monthNameBox->label_color(text_color());

    m_buttonBox->color(fl_darker(button_color()));

    Fl_Group::draw();
}

void Fl_Calendar::measure(int& ww,int& hh) const {
    ww = (w() / 7) * 7;
    hh = (h() / 10) * 10;
}

void Fl_Calendar::date(Fl_Date_Time dt) {
    m_date = dt;

    short year, month, day;
    m_date.decode_date(&year,&month,&day);
    m_activeButtonIndex = day-1;

    Fl::focus(m_dayButtons[m_activeButtonIndex]);

    relayout();
    redraw();
}

Fl_Date_Time Fl_Calendar::date() const {
    short year, month, day;
    m_date.decode_date(&year,&month,&day);
    if (m_activeButtonIndex > -1)
        day = short(m_activeButtonIndex + 1);
    return Fl_Date_Time(year, month, day);
}

//------------------------------------------------------------------------------------------------------

static void popup_revert(Fl_Style* s)
{
    s->color = FL_GRAY;
    s->button_color = FL_GRAY;
    s->box = FL_BORDER_BOX;
    s->button_box = FL_THIN_UP_BOX;
    s->text_font = FL_HELVETICA_BOLD;
}

static Fl_Named_Style popup_style("Popup_Calendar", popup_revert, &Fl_Popup_Calendar::default_style);
Fl_Named_Style* Fl_Popup_Calendar::default_style = &::popup_style;

void cb_clicked(Fl_Widget *w, void *d) {
    Fl_Window *win = w->window();
    if(win) {
        win->set_value();
        win->hide();
    }
    Fl::exit_modal(); //Just in case :)
}

Fl_Popup_Calendar::Fl_Popup_Calendar(Fl_Widget *dateControl)
: Fl_Popup_Window(150,150,"Calendar")
{
    style(default_style);
    m_dateControl = dateControl;
    m_calendar = new Fl_Calendar(0,0,w(),h());
    m_calendar->callback(cb_clicked);
    m_calendar->box(FL_NO_BOX);
    m_calendar->copy_style(style());

    end();
}

void Fl_Popup_Calendar::draw()
{
    m_calendar->copy_style(style());
    Fl_Popup_Window::draw();
}

void Fl_Popup_Calendar::layout() {
    m_calendar->resize(box()->dx(),box()->dy(),w()-box()->dw(),h()-box()->dh());
    m_calendar->layout();
    Fl_Popup_Window::layout();
}

bool Fl_Popup_Calendar::popup() {
    if (m_dateControl) {
        int width = m_dateControl->w();
        if (width < 175) width = 175;
        int X=0, Y=0;
        for(Fl_Widget* w = m_dateControl; w; w = w->parent()) {
            X += w->x();
            Y += w->y();
        }
        int height = 160;
        m_calendar->size(width,height);
        m_calendar->measure(width,height);

        resize(X, Y+m_dateControl->h()-1, width+box()->dw(), height+box()->dh());
    }
    return Fl_Popup_Window::show_popup();
}

bool Fl_Popup_Calendar::popup(Fl_Widget *dateControl, int X, int Y, int W, int H) {
    if(dateControl) {
        int width = (W>0) ? W : dateControl->w();
        if (width < 175) width = 175;
        int height = (H>0) ? H : 175;
        if (height < 175) height = 175;
        for(Fl_Widget* w = m_dateControl; w; w = w->parent()) {
            X += w->x();
            Y += w->y();
        }
        resize(X, Y, width, height);
    }
    return Fl_Popup_Window::show_popup();
}


int Fl_Popup_Calendar::handle(int event) {
    int rc = Fl_Popup_Window::handle(event);

    if (rc) return rc;

    return m_calendar->handle(event);
}
