/***************************************************************************
                          Fl_Exception.h  -  description
                             -------------------
    begin                : Thu Apr 27 2000
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
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <efltk/Fl_String.h>

class Fl_Exception {
	Fl_String	m_file;
	Fl_String	m_text;
	int		m_line;
public:
	Fl_Exception(const Fl_String text,const Fl_String p="",int line=0);
	Fl_String text(bool shortVersion=false) const;
};

#if __FL_EXCEPTIONS__

#define fl_try try
#define fl_catch(exception_variable) catch(Fl_Exception& exception_variable)
#define fl_throw(a) throw a

#else

#define fl_try 
#define fl_catch(exception_variable) for (Fl_Exception exception_variable("");false;)
#define fl_throw(a) 

#endif

#endif

