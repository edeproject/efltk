/***************************************************************************
                          Fl_Popup_Window.cpp  -  description
                             -------------------
    begin                : Fri Mar 31 2000
    copyright            : (C) 2000-2002 by Alexey S.Parshin
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
#include <efltk/fl_draw.h>
#include <efltk/Fl_Popup_Window.h>

//===========================================================================
Fl_Popup_Window::Fl_Popup_Window(int w, int h, const char *label)
: Fl_Window(w,h,label) {
   m_clicked = 0;
   clear_border();
}

Fl_Popup_Window::Fl_Popup_Window(int x,int y,int w, int h, const char *label) 
: Fl_Window(x,y,w,h,label) {
   m_clicked = 0;
   clear_border();
}

bool Fl_Popup_Window::show_popup() {
   m_clicked = 0;
   fl_cursor(FL_CURSOR_DEFAULT);

   show();

   Fl::modal(this,true);

   while (!Fl::exit_modal_flag()) {
      Fl::wait();
   }

   hide();

   Fl::modal(0,false);

   return m_clicked == 1;
}

int Fl_Popup_Window::handle(int event) {
   int key;

   switch( event ) {

   case FL_PUSH:
      if ( !Fl::event_inside(0,0,w(),h()) ) {
         m_clicked = -1;
         Fl::exit_modal();
         return 1;
      }
      break;

   case FL_KEYBOARD:
      key = Fl::event_key();
      switch(key) {
      case FL_Escape:
      case FL_Tab:
         m_clicked = -1;
         Fl::exit_modal();
         return 1;
      case FL_Enter:
         m_clicked = 1;
         Fl::exit_modal();
         return 1;
      }
      break;
   }

   if (m_clicked) {
      Fl::exit_modal();
      return 1;
   }

   return Fl_Window::handle(event);
}
