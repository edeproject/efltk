/***************************************************************************
                          Fl_ODBC_Database.cpp  -  description
                             -------------------
    begin                : Sun Dec 29 2002
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

#include <efltk/db/Fl_ODBC_Database.h>
#include <efltk/db/Fl_Query.h>

void Fl_ODBC_Database::open(const Fl_String connString) {
   if (connString != m_connString) {
      close();
      m_connString = connString;
      open_connection();
   }
}

void Fl_ODBC_Database::close() {
   unsigned cnt = m_queryList.count();
   for (unsigned i = 0; i < cnt; i++) {
      ((Fl_Query *)m_queryList[i])->close();
   }
   close_connection();
   m_active = false;
}
