/***************************************************************************
                          Fl_Query.h  -  description
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

#ifndef __Fl_Query_H__
#define __Fl_Query_H__

#include <efltk/db/Fl_Params.h>
#include <efltk/Fl_Data_Source.h>

class Fl_Database;

class Fl_Query : public Fl_Data_Source {
   friend class Fl_Database;
protected:
   bool              m_prepared;
   bool              m_active;
   bool              m_eof;
   Fl_Params         m_params;

   void checkDatabaseState();

   Fl_Database *     m_database;    // Parent database
   void *            m_stmt;        // Statement handle
   Fl_Data_Fields    m_fields;      // Data fields
protected:
   Fl_String         m_sql;

   void alloc_stmt();
   void free_stmt();

   void connect(Fl_Database *db);
   void disconnect();

   // Copy constructor isn't supported
   Fl_Query(const Fl_Query& ) : Fl_Data_Source(0L) {};

public:
   // ctor, dtor
   Fl_Query(Fl_Database *db,const Fl_String& sql);
   Fl_Query(Fl_Database *db=0L,const char *sql="");
   ~Fl_Query();
public:
   void prepare();
   bool open();
   void exec();
   void fetch();
   bool close();
   const Fl_String& sql()               { return m_sql; }
   Fl_Params& params()                  { return m_params; }
public:
   bool             eof() const         { return m_eof; }
   bool             prepared() const    { return m_prepared; }
   unsigned         param_count() const                     { return m_params.count(); }
   Fl_Param&        param(const char *paramName) const      { return m_params[paramName]; }
   Fl_Param&        param(const Fl_String& paramName) const { return m_params[paramName]; }
   Fl_Param&        param(unsigned paramIndex) const        { return m_params[paramIndex]; }

   Fl_String        sql() const         { return m_sql; }
   void             sql(const Fl_String& _sql);
   void             sql(const char * _sql);

   Fl_Database     *database() const    { return m_database; }
   void             database(Fl_Database *db);

   bool             active() const      { return m_active; }

public: // acting as a Data Source
   virtual const Fl_Variant& operator [] (const char *field_name) const { return m_fields[field_name]; }
   virtual Fl_Variant&       operator [] (const char *field_name)       { return m_fields[field_name]; }

   virtual unsigned          field_count() const                        { return m_fields.count();     }
   virtual int               field_index(const char *fname) const       { return m_fields.field_index(fname); }
   virtual void             *user_data() const                          { return m_fields.user_data(); }

   // access to the field value by field number, 0..field_count()-1
   virtual const Fl_Variant& operator [] (int fnum) const               { return m_fields[fnum]; }
   virtual Fl_Variant&       operator [] (int fnum)                     { return m_fields[fnum]; }

   // access to the field by field number, 0..field_count()-1
   virtual const Fl_Data_Field& field (int field_index) const           { return m_fields.field(field_index); }
   virtual Fl_Data_Field&       field (int field_index)                 { return m_fields.field(field_index); }

   // access to the field by field name
   virtual const Fl_Data_Field& field (const char *field_name) const    { return m_fields.field(field_name); }
   virtual Fl_Data_Field&       field (const char *field_name)          { return m_fields.field(field_name); }

   // Not supported yet:
   virtual unsigned          record_count() const;
   virtual bool              read_field(const char *,Fl_Variant&)       { return false; }
   virtual bool              write_field(const char *,const Fl_Variant&){ return false; }
   virtual bool              load_data()                                { return false; }
   virtual bool              save_data()                                { return false; }
};

#endif
