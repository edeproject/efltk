/***************************************************************************
                          Fl_Directory_DS.h  -  description
                             -------------------
    begin                : Thu Nov 28 2002
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

#ifndef FL_DIRECTORY_DS_H
#define FL_DIRECTORY_DS_H

#include <efltk/Fl_Data_Fields.h>
#include <efltk/Fl_Data_Source.h>

class Fl_Directory_DS : public Fl_Data_Source  {
   Fl_Ptr_List     m_list;
   Fl_Data_Fields *m_current;
   int             m_currentIndex;
   Fl_String       m_directory;
   bool            m_eof;
protected:
   // these methods should be implemented in derived class
   virtual bool              load_data() { return true; }
   virtual bool              save_data() { return true; }
public:
   // ctor, dtor
   Fl_Directory_DS() : Fl_Data_Source(0L) { m_current = 0L; m_currentIndex = -1; }
   virtual ~Fl_Directory_DS() { close(); }

   void directory(const char *d) { m_directory = d; }
   const char *directory() const { return m_directory.c_str(); }

   void clear();

   // access to the field by name
   virtual const Fl_Variant& operator [] (const char *field_name) const;
   virtual Fl_Variant&       operator [] (const char *field_name);

   virtual const Fl_Data_Field& field (int field_index) const;
   virtual Fl_Data_Field&       field (int field_index);

   // how many fields do we have in the current record?
   virtual unsigned          field_count() const;
   virtual int               field_index(const char *field_name) const;

   // access to the field by number, 0..field_count()-1
   virtual const Fl_Variant& operator [] (int) const;
   virtual Fl_Variant&       operator [] (int);

   virtual bool              read_field(const char *fname,Fl_Variant& fvalue);
   virtual bool              write_field(const char *fname,const Fl_Variant& fvalue);

   // dataset navigation
   virtual bool              open();
   virtual bool              close();
   virtual bool              first();
   virtual bool              next();
   virtual bool              prior();
   virtual bool              last();
   virtual bool              find(Fl_Variant position);
   virtual bool              eof() const { return m_eof; }
};

#endif
