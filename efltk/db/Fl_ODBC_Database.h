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
class ODBCConnection;

class Fl_ODBC_Database : public Fl_Database {
   friend class   Fl_Query;

private:
   ODBCConnection *m_connect;

   // ODBC-specific dataset description functions
   unsigned query_count_cols(Fl_Query *query) const;
   void query_col_attributes(Fl_Query *query,short column,short descType,long& value);
   void query_col_attributes(Fl_Query *query,short column,short descType,char *buff,int len);

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
   // Connection manipulations
   virtual void open_connection();
   virtual void close_connection();

   Fl_String query_error(Fl_Query *) const;

public:
   // ctor, dtor
   Fl_ODBC_Database(const Fl_String connString);
   ~Fl_ODBC_Database();

   // Database capabilities
   virtual unsigned capabilities() { return FL_DB_TRANSACTIONS|FL_DB_STMT_PREPARE|FL_DB_STMT_BINDING; }
   
   // Transcation support
   virtual void begin_transaction();
   virtual void commit_transaction();
   virtual void rollback_transaction();
};

#define FETCH_BUFFER_SIZE 2048

#endif
