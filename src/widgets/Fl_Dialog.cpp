/***************************************************************************
                          Fl_Dialog.cpp  -  description
                             -------------------
    begin                : Tue Nov 12 2002
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

#include <efltk/Fl.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Multi_Tabs.h>
#include <efltk/Fl_Dialog.h>


// THESE ARE REPLACED BY Fl_Stobk_Button?
struct Fl_Dialog_Button_Template {
   int         id;
   const char *label;
//   Fl_Pixmap   pixmap;
};

// THESE ARE REPLACED BY Fl_Stobk_Button?
static const Fl_Dialog_Button_Template buttonTemplates[] = {
   { FL_DLG_OK,     "Ok" },
   { FL_DLG_CANCEL, "Cancel" },
   { FL_DLG_YES,    "Yes" },
   { FL_DLG_NO,     "No" },
   { FL_DLG_RETRY,  "Retry" },
   { FL_DLG_CONFIRM,"Confirm" },
   { FL_DLG_IGNORE, "Ignore" },
   { FL_DLG_HELP,   "Help" },
   { 0 }
};

void Fl_Dialog::buttons_callback(Fl_Widget *,void *id) {
   Fl::exit_modal();
}

Fl_Dialog::Fl_Dialog(int ww,int hh) : Fl_Window(ww,hh) {
   m_defaultButton = NULL;
   m_buttonPanel = new Fl_Group(0,0,10,10);
   m_buttonPanel->end();
   m_tabs = new Fl_Multi_Tabs(0,0,10,10);
   end();
}

const Fl_Variant Fl_Dialog::operator [] (const char *field_name) const {
   // stub
   Fl_Variant tmp;
   return tmp;
}

Fl_Variant Fl_Dialog::operator [] (const char *field_name) {
   // stub
   Fl_Variant tmp;
   return tmp;
}

bool Fl_Dialog::valid() {
   return true;
}

void Fl_Dialog::clear_buttons() {
   unsigned cnt = m_buttonList.count();
   for (unsigned i = 0; i < cnt; i++) {
      Fl_Widget *btn = m_buttonList[i];
      m_buttonPanel->remove(btn);
      delete btn;
   }
}

void Fl_Dialog::buttons(int buttons_mask,int default_button) {
   Fl_Button *btn;
   m_defaultButton = 0L;
   m_buttons = buttons_mask;
   clear_buttons();
   m_buttonPanel->begin();
   for (unsigned i = 0; buttonTemplates[i].id; i++) {
      const Fl_Dialog_Button_Template& buttonTemplate = buttonTemplates[i];
      int id = buttonTemplate.id;
      if (buttons_mask & id) {
         if (id == default_button) {
            Fl_Group *default_box = new Fl_Group(0,0,10,10);
            default_box->color(FL_BLACK);
            default_box->box(FL_THIN_DOWN_BOX);
            btn = new Fl_Button(0,0,10,10,buttonTemplate.label);
            default_box->end();
            m_defaultButton = btn;
         } else
            btn = new Fl_Button(0,0,10,10,buttonTemplate.label);
         btn->callback(Fl_Dialog::buttons_callback);
         btn->user_data((void *)id);
         m_buttonList.append(btn);
      }
   }
   m_buttonPanel->end();
   relayout();
}

void Fl_Dialog::layout() {
   unsigned cnt = m_buttonList.count();
   // find the tallest button
   int maxh = 15;
   for (unsigned i = 0; i < cnt; i++) {
      Fl_Widget *btn = m_buttonList[i];
      int ww = 0, hh = 0;
      btn->measure_label(ww,hh);
      hh += btn->box()->dh() * 2;
      if (hh > maxh) maxh = hh;
   }

   // resize button panel
   int bpanelh = maxh + 6;
   m_buttonPanel->resize(4,h() - (bpanelh + 2),w()-8,bpanelh);

   // resize widget area
   m_tabs->resize(4,4,w()-8,m_buttonPanel->y()-4);
   //m_tabs->relayout();

   // resize buttons
   int bx = m_buttonPanel->w();
   for (unsigned i = 0; i < cnt; i++) {
      Fl_Widget *btn = m_buttonList[i];
      int ww = 0, hh = 0;
      btn->measure_label(ww,hh);
      ww += btn->box()->dw() * 2 + 4;
      bx -= ww + 4;
      if (btn == m_defaultButton) {
         Fl_Widget *default_box = btn->parent();
         default_box->resize(bx-2,2,ww+4,maxh+4);
         btn->resize(2,2,ww,maxh);
      } else {
         btn->resize(bx,4,ww,maxh);
      }
   }
}

int Fl_Dialog::handle(int event) {
   return inherited::handle(event);
}


