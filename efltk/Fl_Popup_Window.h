/***************************************************************************
                          Fl_Popup_Window.h  -  description
                             -------------------
    begin                : Tue Apr 4 2000
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
#ifndef __Fl_Popup_Window_H__
#define __Fl_Popup_Window_H__
#include <efltk/Fl_Window.h>

class Fl_Popup_Window : public Fl_Window {
protected:
   int  m_clicked;
   int  handle(int);
public:
   Fl_Popup_Window(int w, int h, const char *label = 0);
   Fl_Popup_Window(int x,int y,int w, int h, const char *label = 0);

   bool show_popup();
};

#endif
