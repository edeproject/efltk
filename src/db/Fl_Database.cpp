/***************************************************************************
                          Fl_Database.cpp  -  description
                             -------------------
    begin                : Sat Dec 28 2002
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

#include <efltk/db/Fl_Database.h>
#include <efltk/db/Fl_Query.h>

void Fl_Database::open(const Fl_String connString) {
   if (connString.length() && connString != m_connString) {
      close();
      m_connString = connString;
   }

   if (!m_active) {
      m_inTransaction = false;
      open_connection();
   }
   m_active = true;
}

void Fl_Database::close() {
   unsigned cnt = m_queryList.count();
   for (unsigned i = 0; i < cnt; i++) {
      ((Fl_Query *)m_queryList[i])->close();
   }
   close_connection();
   m_active = false;
   m_inTransaction = false;
}

