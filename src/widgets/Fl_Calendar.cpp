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

static const char *weekDayLabels[7] = {
   "S","M","T","W","T","F","S"
};

static const char *monthDayLabels[31] = {
   "1","2","3","4","5","6","7","8","9","10",
   "11","12","13","14","15","16","17","18","19","20",
   "21","22","23","24","25","26","27","28","29","30",
   "31"
};

static const char *switchLabels[4] = {
   "@<<","@<","@>","@>>"
};

static const int monthChanges[4] = {
   -12,-1,1,12
};

// Callback function for day buttons
void Fl_Calendar::cbDayButtonClicked(Fl_Widget *button,void *param) {
   Fl_Group       *buttonBox = button->parent();
   Fl_Calendar  *calendar = dynamic_cast<Fl_Calendar *>(buttonBox->parent());
   if (!calendar) return;
   calendar->dayButtonClicked((unsigned)param);
}

// Callback function for switch buttons
void Fl_Calendar::cbSwitchButtonClicked(Fl_Widget *button,void *param) {
   Fl_Calendar  *calendar = dynamic_cast<Fl_Calendar *>(button->parent());
   if (!calendar) return;
   calendar->switchButtonClicked((int)param);
}

void Fl_Calendar::dayButtonClicked(unsigned day) {
   if (day < 1 || day > 31) return;
   if (m_activeButtonIndex > -1) {
      Fl_Button *btn = m_dayButtons[m_activeButtonIndex];
      btn->box(FL_THIN_UP_BOX);
      btn->color(fl_lighter(color()));
   }
   m_activeButtonIndex = day - 1;
   Fl_Button *btn = m_dayButtons[m_activeButtonIndex];
   btn->box(FL_FLAT_BOX);
   btn->color(color());
   redraw();

   // Check if this calendar is on a popup-window
   Fl_Popup_Calendar *w = dynamic_cast<Fl_Popup_Calendar *>(btn->window());
   if (w) {
      w->clicked();
      w->hide();
   }
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

Fl_Calendar::Fl_Calendar(int x,int y,int w,int h,const char *lbl)
: Fl_Group(x,y,w,h,lbl) {
   m_activeButtonIndex = -1;

   //box(FL_FLAT_BOX);

   // Header box
   m_headerBox = new Fl_Group(x,y,w,32);
   m_monthNameBox = new Fl_Box(x,y,w-64,16);
   m_monthNameBox->box(FL_FLAT_BOX);
   m_monthNameBox->labelfont(1);

   // Weekday headers
   for (unsigned i = 0; i < 7; i++) {
      m_dayNameBoxes[i] = new Fl_Box(x+i*16,y+16,16,16,weekDayLabels[i]);
      m_dayNameBoxes[i]->box(FL_THIN_UP_BOX);
      if (weekDayLabels[i][0] == 'S')
         m_dayNameBoxes[i]->labelcolor(FL_RED);
   }
   m_headerBox->end();

   // Day buttons, correct positions are set by resize()
   m_buttonBox = new Fl_Group(0,32,w,64);
   m_buttonBox->box(FL_FLAT_BOX);
   m_buttonBox->color(fl_darker(FL_GRAY));
   for (unsigned i = 0; i < 31; i++) {
      Fl_Button *btn = new Fl_Button(0,0,16,16,monthDayLabels[i]);
      m_dayButtons[i] = btn;
      btn->callback(cbDayButtonClicked,(void *)(i+1));
      btn->color(fl_lighter(fl_lighter(color())));
      btn->box(FL_THIN_UP_BOX);
   }
   m_buttonBox->end();

   // Switch buttons, correct positions are set by resize()
   for (unsigned i = 0; i < 4; i++) {
      m_switchButtons[i] = new Fl_Button(x,y,16,16,switchLabels[i]);
      m_switchButtons[i]->box(FL_THIN_UP_BOX);
      m_switchButtons[i]->labelcolor(fl_darker(FL_GREEN));
      m_switchButtons[i]->callback(cbSwitchButtonClicked,(void *)monthChanges[i]);
      m_switchButtons[i]->label_type(FL_SYMBOL_LABEL);
   }

   end();
   m_date = (int) Fl_Date_Time::Now();
}

void Fl_Calendar::layout() {
   int ww = w(), hh = h();
   int bh = hh / 10;
   int bw = ww / 7;
   ww = bw * 7;
   hh = hh / bh * bh;

   //Fl_Group::resize(xx,yy,ww,hh);

   // resize header
   m_headerBox->resize(0,0,ww,bh * 2);
   m_monthNameBox->resize(0,0,ww,bh);

   for (unsigned i=0; i < 7; i++)
      m_dayNameBoxes[i]->resize(i*bw,bh,bw,bh);

   // compute the month start date
   short year, month, day;
   if ((double)m_date < 1) m_date = Fl_Date_Time::Now();
   m_date.decode_date(&year,&month,&day);
   Fl_Date_Time	monthDate(year,month,1);
   m_headerLabel = monthDate.month_name() + ", " + Fl_String(year);
   m_monthNameBox->label(m_headerLabel.c_str());

   // resize day buttons
   m_buttonBox->resize(0,bh*2,ww,hh-bh*2);
   int dayOffset   = monthDate.day_of_week()-1;
   int daysInMonth = monthDate.days_in_month();
   int weekOffset  = 0;
   for (int i = 0; i < 31; i++) {
      Fl_Button *btn = m_dayButtons[i];
      btn->resize(dayOffset*bw,weekOffset,bw,bh);
      dayOffset++;
      if (i < daysInMonth) {
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

   for (unsigned i = 0; i < 2; i++)
      m_switchButtons[i]->resize(i*bw,sby,bw,bh);

   int x1 = ww - bw * 2;
   for (unsigned i = 2; i < 4; i++)
      m_switchButtons[i]->resize(x1+(i-2)*bw,sby,bw,bh);
}

void Fl_Calendar::measure(int& ww,int& hh) const {
   ww = (w() / 7) * 7;
   hh = (h() / 10) * 10;
}

void Fl_Calendar::date(Fl_Date_Time dt) {
   m_date = dt;
   resize(x(),y(),w(),h());
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
Fl_Popup_Calendar::Fl_Popup_Calendar(Fl_Widget *dateControl)
: Fl_Popup_Window(100,140,"Calendar") {
   m_dateControl = dateControl;
   m_calendar = new Fl_Calendar(0,0,100,100);
   end();
}

void Fl_Popup_Calendar::layout() {
   m_calendar->resize(2,2,w()-4,h()-4);
   m_calendar->layout();
}

bool Fl_Popup_Calendar::popup() {
   bool rc = false;
   if (m_dateControl) {
      int width = m_dateControl->w();
      if (width < 175) width = 175;
      resize(m_dateControl->x()+m_dateControl->window()->x(),
             m_dateControl->y()+m_dateControl->window()->y()+m_dateControl->h()-1,
             width,
             140);
   }
   rc = Fl_Popup_Window::show_popup();
   return rc;
}

int Fl_Popup_Calendar::handle(int event) {
   int rc = Fl_Popup_Window::handle(event);

   if (rc) return rc;

   return m_calendar->handle(event);
}
