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
#include "fl_odbc.h"

Fl_ODBC_Database::Fl_ODBC_Database(const Fl_String connString) 
: Fl_Database(connString) {
   m_connect = new ODBCConnection;
}

Fl_ODBC_Database::~Fl_ODBC_Database() {
   delete m_connect;
}

void Fl_ODBC_Database::open_connection() {
   Fl_String finalConnectionString;
   m_connect->connect(m_connString,finalConnectionString,false);
}

void Fl_ODBC_Database::close_connection() {
   m_connect->disconnect();
}

void Fl_ODBC_Database::begin_transaction() {
   if (m_inTransaction)
      fl_throw("Transaction already started.");

   m_connect->beginTransaction();
   m_inTransaction = true;
}

void Fl_ODBC_Database::commit_transaction() {
   if (!m_inTransaction)
      fl_throw("Transaction isn't started.");

   m_connect->commit();
   m_connect->setConnectOption(SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON);   
   m_inTransaction = false;
}

void Fl_ODBC_Database::rollback_transaction() {
   if (!m_inTransaction)
      fl_throw("Transaction isn't started.");

   m_connect->rollback();
   m_connect->setConnectOption(SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON);   
   m_inTransaction = false;
}

void Fl_ODBC_Database::allocate_query(Fl_Query *query) {
}

void Fl_ODBC_Database::deallocate_query(Fl_Query *query) {
}

void Fl_ODBC_Database::prepare_query(Fl_Query *query) {
}

void Fl_ODBC_Database::open_query(Fl_Query *query) {
}

void Fl_ODBC_Database::fetch_query(Fl_Query *query) {
}

void Fl_ODBC_Database::close_query(Fl_Query *query) {
}

void Fl_ODBC_Database::bind_parameters(Fl_Query *query) {
}
