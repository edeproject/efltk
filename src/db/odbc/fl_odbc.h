/***************************************************************************
                          fl_odbc.h  -  description
                             -------------------
    begin                : Tue Dec 14 1999
    copyright            : (C) 1999 by Alexey Parshin
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
#ifndef FL_ODBC_H
#define FL_ODBC_H

#include <efltk/Fl_String.h>
#include <efltk/Fl_Exception.h>

#ifdef WIN32
#include <windows.h>
#include <sys/types.h>
#include <time.h>
#else
#define LPCVOID  const void *
#endif

#include <sqlext.h>

//typedef const void FAR * LPCVOID;

//=============================================================================

class ODBCEnvironment;
class ODBCConnection;

//=============================================================================
// Base class for all ODBC classes
class ODBCBase {
protected:
   //Fl_String     m_lastError;
   SQLRETURN   m_Retcode;        // Last RETCODE returned from ODBC function
   //long        m_NativeError;    // Last native error

   ODBCBase() : m_Retcode(SQL_SUCCESS)/*,m_NativeError(0)*/ { }

public:

   ~ODBCBase(){}

   RETCODE retcode() const { return m_Retcode; }

private:

   ODBCBase & operator = (const ODBCBase & d);  // Disable operator equal
   ODBCBase(const ODBCBase &);       // Disable copy constructor
};

//=============================================================================

// Environment class is private and is only used by class ODBCConnection
class ODBCEnvironment : public ODBCBase {
   friend class ODBCConnection;
private:
   SQLHENV m_hEnvironment;

protected:
   ODBCEnvironment();
   void allocEnv();
   void freeEnv();

   bool valid()  const { return m_hEnvironment!=SQL_NULL_HENV; }
   SQLHENV Handle() const { return m_hEnvironment; }

   Fl_String errorInformation(LPCSTR action);
public:
   ~ODBCEnvironment();
};

//=============================================================================
// Class that represents the connection to a database.
// You need one object of this class for each database you want to access.
//=============================================================================
class ODBCConnection : public ODBCBase {
   ODBCEnvironment&  m_cEnvironment;
   static int        s_CountConnections;

   SQLHDBC           m_hConnection;
   int               m_CountStatements;
   bool              m_Connected;
protected:
   bool valid()  const { return m_hConnection!=SQL_NULL_HDBC; }
public:

   ODBCConnection();
   ~ODBCConnection();

   void allocConnect();
   void freeConnect();

   // Connect to database passing ODBC connection string
   // The full connection string is returned in FinalConnectionString
   void connect(const Fl_String& ConnectionString,Fl_String& FinalConnectionString,bool EnableDriverPrompt=false);
   void disconnect();

   SQLHDBC handle()   const { return m_hConnection; }
   bool isConnected() const { return m_Connected; }

   void setConnectOption(UWORD fOption, UDWORD vParam);

   void getInfo(unsigned short fInfoType,LPSTR str, int size);
   void getInfo(unsigned short fInfoType,short * num) { getInfo(fInfoType,(LPSTR)num,sizeof(num)); }
   void getInfo(unsigned short fInfoType,DWORD & num) { getInfo(fInfoType,(LPSTR)num,sizeof(num)); }

   // Transactions
   void beginTransaction() { setConnectOption(SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_OFF);}
   void transact(unsigned short fType);
   void commit()   { transact(SQL_COMMIT); }
   void rollback() { transact(SQL_ROLLBACK); }

private:

   static ODBCEnvironment & GetStaticEnv();

protected:

   Fl_String errorInformation(LPCSTR action);
};

const char *removeDriverIdentification(const char *error);

#endif


