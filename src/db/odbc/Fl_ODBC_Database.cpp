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
#include <efltk/db/Fl_Params.h>
#include <efltk/db/Fl_Query.h>
#include <stdio.h>
#include "fl_odbc.h"

static const char
   cantAllocateStmt[] = "Can't allocate ODBC statement";
//   cantFreeStmt[]     = "Can't free ODBC statement";

static inline BOOL successful(int ret) {
   return ret==SQL_SUCCESS || ret==SQL_SUCCESS_WITH_INFO;
}

class Fl_ODBC_Param : public Fl_Param {
   friend class Fl_ODBC_Database;
protected:
   TIMESTAMP_STRUCT m_timeData;
public:
   Fl_ODBC_Param(const char *paramName) : Fl_Param(paramName) {}
};

class FL_API Fl_ODBC_Field : public Fl_Data_Field {
   friend class Fl_Data_Fields;
protected:
   short       m_columnNumber;
   short       m_columnType;
   short       m_columnLength;
   short       m_columnScale;
public:
   Fl_ODBC_Field(const char *name,short number,short type,short length,short scale) : Fl_Data_Field(name)   {
      m_columnNumber = number;
      m_columnType = type;
      m_columnLength = length;
      m_columnScale = scale; 
   }
   char *check_buffer(unsigned sz);
};

char *Fl_ODBC_Field::check_buffer(unsigned sz) {
   if ((unsigned)value.size() <= sz) {
      sz = sz * 5 / 4 + 1;
      value.resize_buffer(sz);
   }
   return (char *)value.get_buffer();
}

// Constructor
Fl_ODBC_Database::Fl_ODBC_Database(const Fl_String connString) 
: Fl_Database(connString) {
   m_connect = new ODBCConnection;
}

// Destructor
Fl_ODBC_Database::~Fl_ODBC_Database() {
   close();
   close_connection();
   delete m_connect;
}

// Create a database connection
void Fl_ODBC_Database::open_connection() {
   Fl_String finalConnectionString;
   m_connect->connect(m_connString,finalConnectionString,false);
}

// Close a database connection
void Fl_ODBC_Database::close_connection() {
   m_connect->disconnect();
}

// Begin database transaction
void Fl_ODBC_Database::begin_transaction() {
   if (m_inTransaction)
      fl_throw("Transaction already started.");

   m_connect->beginTransaction();
   m_inTransaction = true;
}

// Commit database transaction
void Fl_ODBC_Database::commit_transaction() {
   if (!m_inTransaction)
      fl_throw("Transaction isn't started.");

   m_connect->commit();
   m_connect->setConnectOption(SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON);   
   m_inTransaction = false;
}

// Rollback database transaction
void Fl_ODBC_Database::rollback_transaction() {
   if (!m_inTransaction)
      fl_throw("Transaction isn't started.");

   m_connect->rollback();
   m_connect->setConnectOption(SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON);   
   m_inTransaction = false;
}

// Create query handle
void Fl_ODBC_Database::allocate_query(Fl_Query *query) {
   deallocate_query(query);
   
   void *qhandle;
   if (SQLAllocStmt((SQLHDBC)m_connect->handle(),&qhandle) != SQL_SUCCESS) {
      query_handle(query,SQL_NULL_HSTMT);
      fl_throw(cantAllocateStmt);
   }
   query_handle(query,qhandle);
}

// Release query handle
void Fl_ODBC_Database::deallocate_query(Fl_Query *query) {
   void *qhandle = query_handle(query);
   if (!qhandle) // Not allocated
      return;

   SQLFreeStmt(qhandle,SQL_DROP);
   query_handle(query,SQL_NULL_HSTMT);
}

// Get error description for the query
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

// Prepare query handle
void Fl_ODBC_Database::prepare_query(Fl_Query *query) {
   if (!successful(SQLPrepare(query_handle(query),(UCHAR FAR *)(LPCSTR)query->sql().c_str(),SQL_NTS))) {
      fl_throw(query_error(query));
   }
}

// Bind binary query parameters to query handle
void Fl_ODBC_Database::bind_parameters(Fl_Query *query) {
   int rc;

   SQLHSTMT    statement = (SQLHSTMT)query_handle(query);
   Fl_Params&  params = query->params();
   unsigned    cnt = params.count();
   for (unsigned i = 0; i < cnt; i++) {
      Fl_ODBC_Param *param = (Fl_ODBC_Param *)&params[i];
      unsigned  pcnt = param->bind_count();
      for (unsigned j = 0; j < pcnt; j++) {

         short paramType = 0, sqlType = 0, scale = 0;
         void  *buff = param->data();
         long  len = 0;
         short paramNumber = short(param->bind_index(j) + 1);

         short parameterMode = SQL_PARAM_INPUT;
         switch (param->type()) {
         case VAR_INT:
            paramType = SQL_C_SLONG;
            sqlType   = SQL_INTEGER;
            break;
         case VAR_FLOAT:
            paramType = SQL_C_DOUBLE;
            sqlType   = SQL_DOUBLE;
            break;
         case VAR_STRING:
            buff      = (void *)param->get_string();
            len       = param->size();
            paramType = SQL_C_CHAR;
            sqlType   = SQL_CHAR;
            break;
         case VAR_TEXT:
            buff      = (void *)param->get_string();
            len       = param->size();
            paramType = SQL_C_CHAR;
            sqlType   = SQL_LONGVARCHAR;
            break;
         case VAR_BUFFER:
            buff      = (void *)param->get_string();
            len       = param->size();
            paramType = SQL_C_BINARY;
            sqlType   = SQL_LONGVARBINARY;
            break;
         case VAR_DATETIME:
            {
               paramType = SQL_C_TIMESTAMP;
               sqlType   = SQL_TIMESTAMP;
               len = sizeof(TIMESTAMP_STRUCT);
               TIMESTAMP_STRUCT *t = &param->m_timeData;
               Fl_Date_Time dt = param->get_date();
               short ms;
               buff = t;
               if (dt) {
                  dt.decode_date((short *)&t->year,(short *)&t->month,(short *)&t->day);
                  dt.decode_time((short *)&t->hour,(short *)&t->minute,(short *)&t->second,&ms);
                  t->fraction = 0;
               } else {
                  paramType = SQL_C_CHAR;
                  sqlType   = SQL_CHAR;
                  *(char *)buff = 0;
               }
            }
            break;
         default:
            fl_throw("Unknown type of parameter " + Fl_String(paramNumber));
         }
         rc = SQLBindParameter(statement,paramNumber,parameterMode,paramType,sqlType,len,scale,buff,short(len),NULL/*&cbValue*/);
         if (rc != 0)
            //fl_throw("Can't bind parameter " + Fl_String(paramNumber));
            fl_throw(query->sql());
      }
   }
}

// Get the number of columns in result dataset
unsigned Fl_ODBC_Database::query_count_cols(Fl_Query *query) const {
   short count;

   if (!successful(SQLNumResultCols(query_handle(query),&count)))
      fl_throw(query_error(query));

   return count;
}

// Get the column information
void Fl_ODBC_Database::query_col_attributes(Fl_Query *query,short column,short descType,long& value) {
   int m_retcode = SQLColAttributes(query_handle(query),column,descType,0,0,0,(SQLINTEGER *)&value);

   if (!successful(m_retcode))
      fl_throw(query_error(query));
}

// Get the extended column information
void Fl_ODBC_Database::query_col_attributes(Fl_Query *query,short column,short descType,LPSTR buff,int len) {
   short available;
   if (!buff || len <= 0)
      fl_throw("Invalid buffer");

   int m_retcode = SQLColAttributes(query_handle(query),(short)column,descType,buff,(short)len,&available,0);

   if (!successful(m_retcode))
      fl_throw(query_error(query));
}

// Conversion of ODBC data type to C data type
static short ODBCtypeToCType(int odbcType) {
   switch(odbcType) {
   case SQL_BIGINT:
   case SQL_TINYINT:
   case SQL_SMALLINT:
   case SQL_INTEGER:    return SQL_C_SLONG;

   case SQL_NUMERIC:
   case SQL_REAL:
   case SQL_DECIMAL:
   case SQL_DOUBLE:
   case SQL_FLOAT:      return SQL_C_DOUBLE;

   case SQL_LONGVARCHAR:
   case SQL_VARCHAR:
   case SQL_CHAR:       return SQL_C_CHAR;

   // ODBC 3.0 only
   case SQL_TYPE_TIME:
   case SQL_TYPE_TIMESTAMP:
   case SQL_TYPE_DATE:  return SQL_C_TIMESTAMP;

   case SQL_TIME:
   case SQL_TIMESTAMP:
   case SQL_DATE:       return SQL_C_TIMESTAMP;

   case SQL_BINARY:
   case SQL_LONGVARBINARY:
   case SQL_VARBINARY:  return SQL_C_BINARY;


   case SQL_BIT:        return SQL_C_BIT;
   }
   return VAR_NONE;
}

// Execute query and fetch results, if any
void Fl_ODBC_Database::open_query(Fl_Query *query) {
   // Open the database if necessary
   if (!active()) open();

   // Allocate query handle if necessary
   if (active() && !query_handle(query)) allocate_query(query);

   if (query->active())
      fl_throw("Query is already opened");

   // Binary binding of parameters
   bind_parameters(query);

   if (!query->prepared()) {
      prepare_query(query);
   }

   if (!successful(SQLExecute(query_handle(query)))) {
      Fl_String error = query_error(query);
      fl_throw(error);
   }

   query_active(query,true);

   short count = (short) query_count_cols(query);

   Fl_Data_Fields& fields = query_fields(query);

   fields.clear();

   if (count < 1) {
      close_query(query);
      return;
   } else {
      // Reading the column attributes
      char  *columnName = new char[65];
      long  columnType;
      long  columnLength;
      long  columnScale;
      for (short column = 1; column <= count; column++) {
         query_col_attributes(query,column,SQL_COLUMN_NAME,columnName,64);
         query_col_attributes(query,column,SQL_COLUMN_TYPE,columnType);
         query_col_attributes(query,column,SQL_COLUMN_LENGTH,columnLength);
         query_col_attributes(query,column,SQL_COLUMN_SCALE,columnScale);
         columnType = ODBCtypeToCType(columnType);
         if (columnName[0] == 0)
            sprintf(columnName,"column%02i",column);
         if (columnLength > FETCH_BUFFER_SIZE)
            columnLength = FETCH_BUFFER_SIZE;

         Fl_Data_Field *field = new Fl_ODBC_Field(
            columnName,
            column,
            columnType,
            columnLength,
            columnScale);

         query_fields(query).add(field);
      }
      delete [] columnName;
   }

   query_eof(query,false);

   fetch_query(query);
}

unsigned trim_field(char *s,int sz) {
   register char *p = s + sz;
   char ch = s[0];
   s[0] = '!';
   while ( *(--p) == ' ' ) {
   }
   *(++p) = 0;
   if (ch == ' ' && s[1] == 0)
      return 0;
   s[0] = ch;
   return p - s;
}

void Fl_ODBC_Database::fetch_query(Fl_Query *query) {
   if (!query->active())
      fl_throw("Dataset isn't open");

   HSTMT stmt = query_handle(query);
   int rc = SQLFetch(stmt);

   bool  fetchError = false;
   if (!successful(rc)) {
      if (rc < 0) {
         fl_throw(query_error(query));
      } else {
         query_eof(query,rc==SQL_NO_DATA);
         return;
      }
   }

   Fl_Data_Fields& fields = query_fields(query); 
   unsigned	fieldCount = fields.count();
   SQLINTEGER  dataLength;

   if (!fieldCount) return;

   for (unsigned column = 0; column < fieldCount; ) {
      Fl_ODBC_Field *field = (Fl_ODBC_Field *)&fields[column];
      const short fieldType = (short) field->value.type();
      int         readSize = field->value.size();
      char       *buffer = (char *)field->value.get_buffer();

      column++;

      int rc = 0;

      switch (fieldType) {

      case SQL_C_SLONG:
      case SQL_C_DOUBLE:
      case SQL_C_TIMESTAMP:
         rc = SQLGetData(stmt,column,fieldType,buffer,0,&dataLength);
         break;

      case SQL_C_BINARY:
      case SQL_C_CHAR:
         rc = SQLGetData(stmt,column,fieldType,buffer,readSize,&dataLength);
         if (dataLength > readSize) { // continue to fetch BLOB data
            buffer = field->check_buffer(dataLength);
            char *offset = buffer + readSize - 1;
            readSize = dataLength - readSize + 1;
            rc = SQLGetData(stmt,column,fieldType,offset,readSize,NULL);
         }
         break;

      case SQL_BIT:
         rc = SQLGetData(stmt,column,fieldType,buffer,1,&dataLength);
         break;

      default:
         dataLength = 0;
         break;
      }

      if (fieldType == SQL_C_CHAR && dataLength > 0) {
         if (fetchError) dataLength = strlen(buffer);
         dataLength = trim_field(buffer,dataLength);
      }
      if (dataLength <= 0) {
         memset(buffer, 0, field->value.size());
         field->data_size(0);
      } else {
         field->data_size(dataLength);
      }
   }
}

void Fl_ODBC_Database::close_query(Fl_Query *query) {
   query_active(query,false);

   query_active(query,false);
   query_eof(query,true);

   SQLFreeStmt(query_handle(query),SQL_CLOSE);

   Fl_Data_Fields& fields = query_fields(query);
   fields.clear();
}

