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

static const char
   cantAllocateStmt[] = "Can't allocate ODBC statement";
//   cantFreeStmt[]     = "Can't free ODBC statement";

static inline BOOL successful(int ret) {
   return ret==SQL_SUCCESS || ret==SQL_SUCCESS_WITH_INFO;
}

Fl_ODBC_Database::Fl_ODBC_Database(const Fl_String connString) 
: Fl_Database(connString) {
   m_connect = new ODBCConnection;
}

Fl_ODBC_Database::~Fl_ODBC_Database() {
	 close();
	 close_connection();
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
   deallocate_query(query);
   
   void *qhandle;
   if (SQLAllocStmt((SQLHDBC)m_connect->handle(),&qhandle) != SQL_SUCCESS) {
      query_handle(query,SQL_NULL_HSTMT);
      fl_throw(cantAllocateStmt);
   }
   query_handle(query,qhandle);
}

void Fl_ODBC_Database::deallocate_query(Fl_Query *query) {
   void *qhandle = query_handle(query);
   if (!qhandle) // Not allocated
      return;

   SQLFreeStmt(qhandle,SQL_DROP);
   query_handle(query,SQL_NULL_HSTMT);
}

Fl_String Fl_ODBC_Database::query_error(Fl_Query *query) const {
   char  errorDescription[SQL_MAX_MESSAGE_LENGTH];
   char  errorState[SQL_MAX_MESSAGE_LENGTH];

   SQLINTEGER nativeError = 0;
   
   SWORD  pcnmsg = 0;
   *errorDescription = 0;
   *errorState = 0;

   if (SQL_SUCCESS!=SQLError(SQL_NULL_HENV,SQL_NULL_HDBC,query_handle(query),(UCHAR FAR*)errorState,&nativeError,(UCHAR FAR*)errorDescription,sizeof(errorDescription),&pcnmsg))
      if (!*errorDescription) strcpy(errorDescription,"Unknown error");

   return errorDescription;
}

void Fl_ODBC_Database::prepare_query(Fl_Query *query) {
   if (!successful(SQLPrepare(query_handle(query),(UCHAR FAR *)(LPCSTR)query->sql().c_str(),SQL_NTS))) {
      Fl_String error = query_error(query);
      fl_throw(error);
   }
}

void Fl_ODBC_Database::open_query(Fl_Query *query) {
}

void Fl_ODBC_Database::fetch_query(Fl_Query *query) {
}

void Fl_ODBC_Database::close_query(Fl_Query *query) {
}

void Fl_ODBC_Database::bind_parameters(Fl_Query *query) {
}
