/***************************************************************************
                          Fl_Dialog.h  -  description
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
#ifndef __Fl_Dialog_H__
#define __Fl_Dialog_H__

#include <efltk/Fl_Window.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Widget_List.h>
#include <efltk/Fl_Variant.h>

#define FL_DLG_OK       1
#define FL_DLG_CANCEL   2
#define FL_DLG_YES      4
#define FL_DLG_NO       8
#define FL_DLG_RETRY    16
#define FL_DLG_CONFIRM  32
#define FL_DLG_IGNORE   64
#define FL_DLG_HELP     128

class Fl_Button;
class Fl_Multi_Tabs;

class FL_API Fl_Dialog : public Fl_Window {
   typedef Fl_Window inherited;

   static void buttons_callback(Fl_Widget *,void *);

   Fl_Button      *m_defaultButton;
   Fl_Group       *m_buttonPanel;
   Fl_Multi_Tabs  *m_tabs;
   Fl_Widget_List  m_buttonList;
   int             m_buttons;

public:
   Fl_Dialog(int w,int h);

   const Fl_Variant operator [] (const char *field_name) const;
   Fl_Variant operator [] (const char *field_name);

   int   show_modal();
   bool  valid();
   void  buttons(int buttons_mask,int default_button);
   void  user_button(Fl_Button *);
   void  clear_buttons();

   int   handle(int);
   void  layout();
};

#endif
