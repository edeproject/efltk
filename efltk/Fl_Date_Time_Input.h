/***************************************************************************
                          Fl_Date_Time_Input.h  -  description
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

#ifndef __Fl_Date_Time_Input_H__
#define __Fl_Date_Time_Input_H__

#include <efltk/Fl_Group.h>
#include <efltk/Fl_Date_Time.h>

class Fl_Masked_Input;
class Fl_Button;

class FL_API Fl_Date_Input : public Fl_Group {
   Fl_Masked_Input  *m_input;
   Fl_Button        *m_button;
protected:
   static void input_callback(Fl_Widget *,void *);
   static void button_callback(Fl_Widget *,void *);
public:
   Fl_Date_Input(int,int,int,int,const char * = 0);

   void layout();

   void value(const char *);
   const char *value();

   void date_value(Fl_Date_Time);
   Fl_Date_Time date_value();
};

#endif
