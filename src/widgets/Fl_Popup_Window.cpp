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

#include <efltk/Fl_Popup_Window.h>
#include <efltk/Fl.h>
#include <efltk/Enumerations.h>
#include <efltk/fl_draw.h>

//===========================================================================
Fl_Popup_Window::Fl_Popup_Window(int w, int h, const char *label)
: Fl_Menu_Window(w,h,label) 
{
	set_override();
}

Fl_Popup_Window::Fl_Popup_Window(int x,int y,int w, int h, const char *label) 
: Fl_Menu_Window(x,y,w,h,label) 
{
	set_override();
}

bool Fl_Popup_Window::show_popup() 
{
	return exec(0, true);
}

int Fl_Popup_Window::handle(int event) 
{	
	switch( event ) {
	case FL_PUSH:
		if ( !Fl::event_inside(-2,-2,w()+4,h()+4) ) {
			clear_value();
			Fl::exit_modal();
		}
		Fl_Menu_Window::handle(event);
		return 1;		

	case FL_KEYBOARD:
		switch(Fl::event_key()) {
		case FL_Escape:
		case FL_Tab:
			clear_value();
			Fl::exit_modal();
			return 1;
		case FL_Enter:
			set_value();         
			Fl::exit_modal();
			return 1;
		}
		break;
	}
	return Fl_Menu_Window::handle(event);	
}
