/***************************************************************************
                          Fl_Query.h  -  description
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

#ifndef __Fl_Query_H__
#define __Fl_Query_H__

#include <efltk/db/Fl_Params.h>
#include <efltk/Fl_Data_Source.h>

class Fl_Database;

class Fl_Query : public Fl_Data_Source {
   friend class Fl_Database;
protected:
   bool              m_prepared;
   bool              m_active;
   bool              m_eof;
   Fl_Params         m_params;

   void checkDatabaseState();

   Fl_Database *     m_database;    // Parent database
   void *            m_stmt;        // Statement handle
   Fl_Data_Fields    m_fields;      // Data fields
protected:
   Fl_String         m_sql;

   void alloc_stmt();
   void free_stmt();

   // Copy constructor isn't supported
   Fl_Query(const Fl_Query& ) : Fl_Data_Source(0L) {};

public:
   Fl_Query(Fl_Database *db,Fl_String sql = "");
   ~Fl_Query() { close(); free_stmt(); }
public:
   void prepare();
   bool open();
   void exec();
   void fetch();
   bool close();
   const Fl_String& sql()               { return m_sql; }
   Fl_Params& params()                  { return m_params; }
public:
   bool             eof() const         { return m_eof; }
   bool             prepared() const    { return m_prepared; }
   unsigned         param_count() const { return m_params.count(); }
   Fl_Param&        param(const char *paramName) const;
   Fl_Param&        param(const Fl_String& paramName) const;
   Fl_Param&        param(unsigned paramIndex) const;

   Fl_String        sql() const         { return m_sql; }
   void             sql(Fl_String _sql);

   Fl_Database     *database() const    { return m_database; }

   bool             active() const      { return m_active; }
};

#endif
