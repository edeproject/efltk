/***************************************************************************
                          fl_odbc.cpp  -  description
                             -------------------
    begin                : Tue Jan 7 2003
    copyright            : (C) 2003 by Alexey Parshin
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
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "fl_odbc.h"

static const char
	cantSetConnectOption[] = "Can't set connect option",
	cantStartTranscation[] = "Can't start transcation",
	cantGetInformation[]   = "Can't get connect information";

// Returns true if result code indicates success
static inline bool Successful(RETCODE ret) {
   return ret==SQL_SUCCESS || ret==SQL_SUCCESS_WITH_INFO;
}

// Return true if the result code indicates a warning
static inline bool IsWarning(RETCODE ret) {
  return ret==SQL_SUCCESS_WITH_INFO || ret==SQL_NO_DATA_FOUND;
}

// Return true if result code indicates an error
static inline bool IsError(RETCODE ret) {
  return !Successful(ret) && !IsWarning(ret); // ret==SQL_ERROR || ret==SQL_INVALID_HANDLE;
}

// String description of ODBC return code
/*
static LPCSTR GetRetcodeDescription(RETCODE retcode) {
   switch(retcode) {
   case SQL_INVALID_HANDLE     : return "SQL_INVALID_HANDLE";
   case SQL_ERROR              : return "SQL_ERROR"         ;
   case SQL_SUCCESS            : return "SQL_SUCCESS"       ;
   case SQL_SUCCESS_WITH_INFO  : return "SQL_SUCCESS_WITH_INFO";
   case SQL_NO_DATA_FOUND      : return "SQL_NO_DATA_FOUND" ;
   case SQL_STILL_EXECUTING    : return "SQL_STILL_EXECUTING (unsupported)";
   case SQL_NEED_DATA          : return "SQL_NEED_DATA (unsupported)";
   default                     : return "Unexpected sql retcode";
   }
}
*/
//---------------------------------------------------------------------------
// ODBC Environment class
//---------------------------------------------------------------------------
ODBCEnvironment::ODBCEnvironment()
                :m_hEnvironment(SQL_NULL_HENV) {}

ODBCEnvironment::~ODBCEnvironment() {
   if (valid()) freeEnv();
}

void ODBCEnvironment::allocEnv() {
   if (valid()) return; // Already allocated
   if (SQLAllocEnv(&m_hEnvironment)!=SQL_SUCCESS) {
      m_hEnvironment=SQL_NULL_HENV;
      fl_throw("Can't allocate ODBC environment");
  }
}

void ODBCEnvironment::freeEnv() {
   if (!valid()) return; // Never allocated

   SQLFreeEnv(m_hEnvironment);
   m_hEnvironment=SQL_NULL_HENV;
}

//--------------------------------------------------------------------------------------------
// ODBC Connection class
//--------------------------------------------------------------------------------------------

// Counter of connections, set to zero by compiler
int ODBCConnection::s_CountConnections;

ODBCConnection::ODBCConnection()
:m_cEnvironment(GetStaticEnv()),m_hConnection(SQL_NULL_HDBC),
m_CountStatements(0) ,m_Connected(false) {
   ++s_CountConnections;
}

ODBCConnection::~ODBCConnection() {
   if (m_CountStatements) // Disconnecting with active statements?
      fl_throw("Can't free ODBC connection with active statements");

   if (isConnected()) disconnect();
   freeConnect();
}

// Static environment object inside this function
ODBCEnvironment & ODBCConnection::GetStaticEnv() {
  static ODBCEnvironment Env;
  return Env;
}

void ODBCConnection::allocConnect() {
   // If already connected, return false
   if (valid()) return;

   // Allocate environment if not already done
   m_cEnvironment.allocEnv();

   // Create connection handle
   if (SQLAllocConnect(m_cEnvironment.Handle(),&m_hConnection)!=SQL_SUCCESS) {
      m_hConnection=SQL_NULL_HDBC;
      fl_throw(errorInformation("Can't alloc connection"));
   }
}

void ODBCConnection::freeConnect() {
   if (!valid()) return; // Not connected
   if (isConnected()) disconnect();

   m_Retcode = SQLFreeConnect(m_hConnection);
   /*
   if (m_Retcode!=SQL_SUCCESS)
      fl_throw(errorInformation("Can't free connection"));
   */
   m_hConnection=SQL_NULL_HDBC;
}

void ODBCConnection::connect(const Fl_String& ConnectionString,Fl_String& pFinalString,bool /*EnableDriverPrompt*/) {
   // Check parameters
   if (!ConnectionString.length())
      fl_throw("Can'connect: connection string is empty");

   // If handle not allocated, allocate it
   allocConnect();

   // If we are  already connected, disconnect
   if (isConnected()) disconnect();

   char  *buff= new char [2048];
   SWORD bufflen=0;
/*
   int   driverMode1 = SQL_DRIVER_COMPLETE;
   int   driverMode2 = SQL_DRIVER_PROMPT;
   if (!EnableDriverPrompt)
      driverMode1 = driverMode2 = SQL_DRIVER_NOPROMPT;
*/
#ifdef WIN32
   HWND ParentWnd = 0;
#else
   void *ParentWnd = 0;
#endif
   m_Retcode=::SQLDriverConnect( m_hConnection,ParentWnd,
                                 (UCHAR FAR *)ConnectionString.c_str(),SQL_NTS,
                                 (UCHAR FAR *)buff,(short)sizeof(buff),&bufflen,
                                 SQL_DRIVER_COMPLETE);

   if (m_Retcode!=SQL_SUCCESS && m_Retcode!=SQL_SUCCESS_WITH_INFO) {
      sprintf(buff,"SQLDriverConnect(%s)",(LPCSTR)ConnectionString.c_str());
      Fl_String errorInfo = errorInformation(buff);
      delete [] buff;
      fl_throw(errorInfo);
   }
   pFinalString = buff;
   delete [] buff;

   m_Connected = true;
}

void ODBCConnection::disconnect() {
   if (!isConnected()) return; // Not connected

   m_Retcode=::SQLDisconnect(m_hConnection);
   if (m_Retcode!=SQL_SUCCESS)
      fl_throw(errorInformation("Can't disconnect"));

   m_Connected=false;
}

void ODBCConnection::setConnectOption(UWORD fOption, UDWORD vParam) {
   if (!isConnected())
      fl_throw(errorInformation(cantSetConnectOption));

  m_Retcode=::SQLSetConnectOption(m_hConnection,fOption,vParam);

  if (m_Retcode!=SQL_SUCCESS)
		fl_throw(errorInformation(cantSetConnectOption));
}

void ODBCConnection::transact(UWORD fType) {
   if (!isConnected() || !m_cEnvironment.valid())
      fl_throw(errorInformation(cantStartTranscation));

   m_Retcode = SQLTransact(m_cEnvironment.Handle(),m_hConnection,fType);

   if (m_Retcode!=SQL_SUCCESS)
      fl_throw(errorInformation(cantStartTranscation));
}

void ODBCConnection::getInfo(UWORD fInfoType,LPSTR str, int size) {
   if (!str || size<1 || !isConnected())
      fl_throw(errorInformation(cantGetInformation));

   m_Retcode=::SQLGetInfo(m_hConnection,fInfoType,str,(short)size,NULL);

   if (m_Retcode!=SQL_SUCCESS)
      fl_throw(errorInformation(cantGetInformation));
}
//==============================================================================
const char *removeDriverIdentification(const char *error) {
   const char *p = error;
   const char *p1 = error;
   while (p1) {
      p1 = strstr(p,"][");
      if (p1)
         p = p1 + 1;
   }
   p1 = strstr(p,"]");
   if (p1)
      p = p1 + 1;
   return p;
}

Fl_String ODBCEnvironment::errorInformation(LPCSTR action) {
   if (!action) return "<Unknown ODBC error>";

   char        errorDescription[SQL_MAX_MESSAGE_LENGTH];
   char        errorState[SQL_MAX_MESSAGE_LENGTH];

   SWORD       pcnmsg=0;
   SQLINTEGER	nativeError=0;

   *errorDescription=0;
   *errorState=0;

   if (SQLError(m_hEnvironment,SQL_NULL_HDBC,SQL_NULL_HSTMT,(UCHAR FAR*)errorState,(SQLINTEGER *)&nativeError,(UCHAR FAR*)errorDescription,sizeof(errorDescription),&pcnmsg) != SQL_SUCCESS)
      fl_throw(cantGetInformation);

   return Fl_String(errorDescription);
}

Fl_String ODBCConnection::errorInformation(LPCSTR function) {
   if (!function) return "<Unknown ODBC error>";

   char        errorDescription[SQL_MAX_MESSAGE_LENGTH];
   char        errorState[SQL_MAX_MESSAGE_LENGTH];
   SWORD       pcnmsg=0;
   SQLINTEGER	nativeError=0;
   *errorState=0;
   *errorDescription = 0;

   if (SQL_SUCCESS!=SQLError(SQL_NULL_HENV,m_hConnection,SQL_NULL_HSTMT,(UCHAR FAR*)errorState,(SQLINTEGER *)&nativeError,(UCHAR FAR*)errorDescription,sizeof(errorDescription),&pcnmsg))
      fl_throw(cantGetInformation);

   return removeDriverIdentification(errorDescription);
}
//----------------------------------------------------------------------------------------------------------------
// Convert from a CTime to a TIMESTAMP_STRUCT
bool CTime_to_TIMESTAMP_STRUCT(const time_t & time, TIMESTAMP_STRUCT & t) {
   struct tm tt;

   memcpy(&tt,localtime(&time),sizeof(struct tm));

   t.year    = short(tt.tm_year + 1900);
   t.month   = short(tt.tm_mon);
   t.day     = short(tt.tm_mday);
   t.hour    = short(tt.tm_hour);
   t.minute  = short(tt.tm_min);
   t.second  = short(tt.tm_sec);
   t.fraction = 0;

   return true;
}

// Convert a TIMESTAMP_STRUCT to a CTime
bool TIMESTAMP_STRUCT_to_CTime(const TIMESTAMP_STRUCT & t, time_t & time) {
   struct tm tt;

   tt.tm_year = t.year - 1900;
   tt.tm_mon  = t.month;
   tt.tm_mday = t.day;
   tt.tm_hour = t.hour;
   tt.tm_min  = t.minute;
   tt.tm_sec  = t.second;
   tt.tm_isdst = -1;

   time = mktime(&tt);

   return true;
}
