/***************************************************************************
                          Fl_Query.cpp  -  description
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

#include <ctype.h>
#include <stdlib.h>

#ifdef _WIN32_WCE
#include <stdlibx.h>
#endif

Fl_Query::Fl_Query(Fl_Database *db,const Fl_String& _sql)
: Fl_Data_Source(0L) {
   if (!db) fl_throw("Database must exist");
   m_prepared = false;
   m_active = false;
   m_eof = false;
   m_database = db;
   m_stmt = 0L;
   sql(_sql);
}

Fl_Query::Fl_Query(Fl_Database *db,const char *_sql)
: Fl_Data_Source(0L) {
   if (!db) fl_throw("Database must exist");
   m_prepared = false;
   m_active = false;
   m_eof = false;
   m_database = db;
   m_stmt = 0L;
   sql(_sql);
}

void Fl_Query::checkDatabaseState() {
   if (!m_database->active())
      m_database->open();
}

void Fl_Query::alloc_stmt() {
   if (!m_stmt) 
   fl_try {
      m_database->lock();
      m_database->allocate_query(this);
   }
   fl_catch (exception) {
      m_database->unlock();
      fl_rethrow;
   }
   m_database->unlock();
}

void Fl_Query::free_stmt() {
   m_active = false;
   m_stmt = 0L;
   m_prepared = false;

   if (m_stmt) 
   fl_try {
      m_database->lock();
      m_database->deallocate_query(this);
   }
   fl_catch (exception) {
      m_database->unlock();
      fl_rethrow;
   }

   m_database->unlock();
}

void Fl_Query::prepare() {
   if (m_database->capabilities() & FL_DB_STMT_PREPARE == 0)
      return;  // Prepare isn't supported, ignore the attempt
   checkDatabaseState();
   fl_try {
      m_database->lock();
      if (!m_stmt) 
         m_database->allocate_query(this);
      m_database->prepare_query(this);
   }
   fl_catch (exception) {
      m_database->unlock();
      fl_rethrow;
   }

   m_database->unlock();
   m_prepared = true;
}

bool Fl_Query::open() {
   checkDatabaseState();
   
   fl_try {
      m_database->lock();
      if (!m_stmt)
         alloc_stmt();
      m_database->open_query(this);
   }
   fl_catch (exception) {
      m_database->unlock();
      fl_rethrow;
   }

   m_database->unlock();

   m_active = true;
   m_eof = false;
   return true;
}

void Fl_Query::exec() {
   open();
   close();
}

void Fl_Query::fetch() {
   checkDatabaseState();
   fl_try {
      m_database->lock();
      m_database->fetch_query(this);
   }
   fl_catch (exception) {
      m_database->unlock();
      fl_rethrow;
   }

   m_database->unlock();
}

bool Fl_Query::close() {
   fl_try {
      m_database->lock();
      m_database->close_query(this);
   }
   fl_catch (exception) {
      m_database->unlock();
      fl_rethrow;
   }

   m_database->unlock();
   m_eof = true;
   return true;
}

void Fl_Query::sql(const char *_sql) {
   Fl_String  tempSQL = _sql;
   sql(tempSQL);
}

Fl_Param *theParam;

void Fl_Query::sql(const Fl_String& _sql) {
   // Looking up for SQL parameters
   Fl_String  paramName;
   char     delimitter[] = " ";
   char     delimitters[] = "'\":'";
   char     *s = strdup(_sql.c_str());
   char     *paramStart = s;
   char     *paramEnd;
   int      paramNumber = 0;
   for (unsigned i = 0; i < m_params.count(); i++) {
      Fl_Param& param = m_params[i];
      param.bind_clear();
   }

   Fl_String  odbcSQL = "";
   bool     endOfString;
   for (;;) {
      paramEnd = strpbrk(paramStart,delimitters);
      if ( !paramEnd ) {
         odbcSQL += paramStart;
         break;
      }
      *delimitter = *paramEnd;

      if (*paramEnd == ':') {
         if (paramEnd != s && isalnum(*(paramEnd-1)) ) {
            *paramEnd = char(0);
            odbcSQL += paramStart;
            odbcSQL += ":";
            paramStart = paramEnd + 1;
            continue;
         }
         if (paramEnd[1] == ':') {
            paramEnd++;
            *paramEnd = char(0);
            odbcSQL += paramStart;
            paramStart = paramEnd + 1;
            continue;
         }
      }

      if ( *paramEnd == '\'' || *paramEnd == '"' ) {
         paramEnd = strpbrk(paramEnd + 1,delimitter);
         if ( !paramEnd ) {
            break; // Unmatched quotes
         }
         *paramEnd = char(0);
         odbcSQL += paramStart;
         odbcSQL += delimitter;
         paramStart = paramEnd + 1;
         continue;
      }

      *paramEnd = char(0);
      odbcSQL += paramStart;
      paramStart = paramEnd + 1;

      delimitter[0] = 0;
      char *ptr = paramStart;
      for (; *ptr; ptr++) {
         char c = *ptr;
         if ( c == '_' ) continue;
         if (!isalnum(c)) {
            delimitter[0] = c;
            break;
         }
      }

      paramEnd = ptr;
      endOfString = (*paramEnd == 0);
      *paramEnd = char(0);
      if (ptr != paramStart) {
         //Fl_Param *param;
         int   index = m_params.param_index(paramStart);
         if ( index == -1 ) {
            theParam = new Fl_Param(paramStart);
            m_params.add(theParam);
         } else {
            theParam = &m_params[index];
         }
         theParam->bind_add(paramNumber);
         paramNumber++;
         odbcSQL += "?";
         odbcSQL += delimitter;
      } else {
         odbcSQL += ":";
      }
      paramStart = paramEnd + 1;
      if (endOfString) break;
   }

   free(s);

   for (int p = m_params.count() - 1; p >= 0; p--)
   if (!m_params[p].bind_count())
      m_params.remove(p);

   if (m_sql != odbcSQL) {
      m_sql = odbcSQL;
      if ( active() )
         close();
      free_stmt();
   }
}

unsigned Fl_Query::record_count() const {
   fl_throw("Record count is not supported for Fl_Query");
   return 0; // Just to block warning
}

