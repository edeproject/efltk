/***************************************************************************
                          Fl_Database.h  -  description
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

#ifndef __Fl_Database_H__
#define __Fl_Database_H__

#include <efltk/Fl_String.h>
#include <efltk/Fl_Ptr_List.h>
#include <efltk/Fl_Exception.h>

enum Fl_Database_Capabilities {
   FL_DB_UNKNOWN = 0, 
   FL_DB_TRANSACTIONS = 1,
   FL_DB_STMT_PREPARE = 2,
   FL_DB_STMT_BINDING = 4
};

class Fl_Query;

class Fl_Database {
   friend class   Fl_Query;

protected:
   Fl_Ptr_List    m_queryList;
   Fl_String      m_connString;
   bool           m_active;
   bool           m_inTransaction;

protected:
   // Operations over query handle
   // These methods should be implemented in actual database class
   virtual void allocate_query(Fl_Query *) = 0;
   virtual void deallocate_query(Fl_Query *) = 0;
   virtual void prepare_query(Fl_Query *) = 0;
   virtual void open_query(Fl_Query *)  = 0;
   virtual void fetch_query(Fl_Query *) = 0;
   virtual void close_query(Fl_Query *) = 0;
   virtual void bind_parameters(Fl_Query *) = 0;

protected:
   // These methods should be implemented in actual database class
   virtual void open_connection() = 0;
   virtual void close_connection()                 { fl_throw("Method not implemented"); }

public:
   Fl_Database(const Fl_String connString)         { m_inTransaction = m_active = false; }
   virtual ~Fl_Database()                          { close(); close_connection(); }
   void open(const Fl_String connString="");
   void close();
   Fl_String connect_string() const                { return m_connString; }

   bool active() const                             { return m_active; }
   bool in_transaction() const                     { return m_inTransaction; }

   // These methods should be implemented in actual database class
   virtual unsigned capabilities()                 { return  FL_DB_UNKNOWN; }
   virtual void begin_transaction()                { fl_throw("Transactions are not supported"); }
   virtual void commit_transaction()               { fl_throw("Transactions are not supported"); }
   virtual void rollback_transaction()             { fl_throw("Transactions are not supported"); }
};

#endif
