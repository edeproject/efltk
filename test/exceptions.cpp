/***************************************************************************
                          exceptions.cpp  -  description
                             -------------------
    begin                : Mon Dec 23 2002
    copyright            : (C) 2000 by Alexey S.Parshin
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
#include <config.h>

#include <efltk/fl_ask.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Exception.h>

void cb(Fl_Widget *,void *) {
   fl_try {
      fl_throw(Fl_Exception("Error happened",__FILE__,__LINE__));
   }
   fl_catch(exc) {
      fl_alert(exc.text().c_str());
   }
}

int main (int argc,char *argv[]) {
   Fl_Window window(400,300);
   Fl_Button button(50,50,150,30,"Create exception");
   button.callback(cb);
   window.end();
   window.show();
   
Fl::run();
}