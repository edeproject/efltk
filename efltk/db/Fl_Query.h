/***************************************************************************
                          Fl_Query.h  -  description
                             -------------------
    begin                : Wed Dec 15 1999
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

#ifndef __Fl_Query_H__
#define __Fl_Query_H__

#include <Fl_Params.h>
#include <Fl_Data_Fields.h>

class Fl_Database;

class Fl_Query {
private:
   bool              m_prepared;
   bool              m_active;
   bool              m_eof;
   Fl_ParamList      m_params;
   Fl_Data_Fields    m_fields;
protected:
   Fl_Database *     m_database;
   void *            m_handle;
   long              m_NativeError;
protected:
   Fl_String         m_sql;

   void alloc_stmt();
   void free_stmt();
   void colAttributes(short column,short descType,long& value);
   void colAttributes(short column,short descType,char *buff,int len);

   // Copy constructor isn't supported
   Fl_Query(const Fl_Query& ) {};

public:
   Fl_Query(Fl_Database *db,Fl_String sql = "");
   ~Fl_Query() { close(); free_stmt(); }
public:
   void prepare();
   void open();
   void exec();
   void fetch();
   void close();
   Fl_String sql() { return m_sql; }
public:
   Fl_Data_Field&   operator [] (int fieldIndex) const { return m_fields[fieldIndex]; }
   Fl_Data_Field&   operator [] (const char *fieldName) const { return m_fields[fieldName]; }
   Fl_Data_Field&   operator [] (const Fl_String& fieldName) const { return m_fields[fieldName.c_str()]; }
   Fl_Data_Fields&  fields ()           { return m_fields; }
   bool             eof() const         { return m_eof; }
   unsigned         field_count() const { return m_fields.count(); }
   unsigned         param_count() const { return m_params.count(); }
   Fl_Param&        param(const char *paramName) const;
   Fl_Param&        param(const Fl_String& paramName) const;
   Fl_Param&        param(unsigned paramIndex) const;

   Fl_String        sql() const         { return m_sql; }
   void             sql(Fl_String _sql);

   Fl_Database     *database() const    { return m_db; }

   bool             active() const      { return m_active; }
};

#define FETCH_BUFFER_SIZE 1024

#endif
