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

#ifndef _FL_DATABASE_H_
#define _FL_DATABASE_H_

#include <efltk/Fl_String.h>
#include <efltk/Fl_Ptr_List.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Thread.h>
#include <efltk/db/Fl_Query.h>

class Fl_Database {
    friend class   Fl_Query;

protected:
    Fl_Ptr_List    m_queryList;
    Fl_String      m_connString;
    bool           m_active;
    bool           m_inTransaction;
    Fl_Mutex      *m_mutex;

protected:
    // Operations over query handle
    // These methods should be implemented in actual database class
    virtual void allocate_query(Fl_Query *) = 0;
    virtual void deallocate_query(Fl_Query *) = 0;
    virtual void prepare_query(Fl_Query *) = 0;
    virtual void open_query(Fl_Query *)  = 0;
    virtual void fetch_query(Fl_Query *) = 0;
    virtual void close_query(Fl_Query *) = 0;

    // These methods should be implemented in actual database class
    virtual void open_connection() = 0;
    virtual void close_connection() = 0;

    // These methods provide access to protected data of Fl_Query
    void *query_handle(const Fl_Query *q) const     { return q->m_stmt; }
    void  query_handle(Fl_Query *q,void *handle)    { q->m_stmt = handle; }
    bool  query_active(Fl_Query *q)                 { return q->m_active; }
    void  query_active(Fl_Query *q,bool active)     { q->m_active = active; }
    void  query_eof(Fl_Query *q,bool eof)           { q->m_eof = eof; }
    Fl_Data_Fields& query_fields(Fl_Query *q)       { return q->m_fields; }

public:
    // Capabilities:
    enum {
        UNKNOWN = 0,
        TRANSACTIONS,
        STMT_PREPARE,
    };

    Fl_Database(const Fl_String connString,bool threadSafe=false);
    virtual ~Fl_Database();

    void open(const char *connString="");
    void close();

    const Fl_String &connect_string() const         { return m_connString; }
    void connect_string(const char *connString)     { m_connString = connString; }

    bool active() const                             { return m_active; }
    bool in_transaction() const                     { return m_inTransaction; }

    bool thread_safe() const                        { return (m_mutex!=0); }
    void lock()                                     { if (m_mutex) m_mutex->lock(); }
    void unlock()                                   { if (m_mutex) m_mutex->unlock(); }

    // These methods should be implemented in actual database class
    virtual unsigned capabilities()                 { return UNKNOWN; }

    virtual void begin_transaction()                { fl_throw("Transactions are not supported"); }
    virtual void commit_transaction()               { fl_throw("Transactions are not supported"); }
    virtual void rollback_transaction()             { fl_throw("Transactions are not supported"); }
};

#define FL_DB_UNKNOWN      Fl_Database::UNKNOWN
#define FL_DB_TRANSACTIONS Fl_Database::TRANSACTIONS
#define FL_DB_STMT_PREPARE Fl_Database::STMT_PREPARE

#endif
