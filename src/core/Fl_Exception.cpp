/***************************************************************************
                          Fl_Exception.cpp  -  description
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
#include <config.h>
#include <efltk/Fl_Exception.h>

#if __FL_EXCEPTIONS__

Fl_Exception::Fl_Exception(const Fl_String text,const Fl_String file,int line) {
   m_file = file;
   m_text = text;
   m_line = line;
}

Fl_String Fl_Exception::text(bool shortVersion) const {
   if (!shortVersion && m_line)
         return "Error in file "+m_file+"["+Fl_String(m_line)+"]: " + m_text;
   else  return m_text;
}

#endif
