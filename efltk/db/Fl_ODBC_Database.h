/***************************************************************************
                          Fl_ODBC_Database.h  -  description
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

#ifndef __Fl_ODBC_Database_H__
#define __Fl_ODBC_Database_H__

#include <efltk/db/Fl_Database.h>

class Fl_Query;

class Fl_ODBC_Database : public Fl_Database {
   friend class   Fl_Query;

protected:
   // Operations over query handle
   virtual void allocate_query(Fl_Query *);
   virtual void deallocate_query(Fl_Query *);
   virtual void prepare_query(Fl_Query *);
   virtual void open_query(Fl_Query *);
   virtual void fetch_query(Fl_Query *);
   virtual void close_query(Fl_Query *);
   virtual void bind_parameters(Fl_Query *);

protected:
   virtual void open_connection();
   virtual void close_connection();

public:
   Fl_ODBC_Database(const Fl_String connString) : Fl_Database(connString) {}

   virtual unsigned capabilities() { return FL_DB_TRANSACTIONS|FL_DB_STMT_PREPARE|FL_DB_STMT_BINDING; }
   
   virtual void begin_transaction();
   virtual void commit_transaction();
   virtual void rollback_transaction();
};

#endif
