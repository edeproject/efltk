/***************************************************************************
                          Fl_Data_Fields.h  -  description
                             -------------------
    begin                : Mon Nov 25 2002
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

#ifndef __Fl_Data_Fields_h__
#define __Fl_Data_Fields_h__

#include <efltk/Fl_Variant.h>
#include <efltk/Fl_Ptr_List.h>

class Fl_Data_Fields;

class FL_API Fl_Data_Field {
   friend class Fl_Data_Fields;
protected:
   Fl_String   m_name;
public:
   Fl_Data_Field(const char *name) { m_name = name; width = -1; }
   Fl_Variant  value;
   int         width;
   const char *name() const { return m_name.c_str(); }
};

class FL_API Fl_Data_Fields {
   Fl_Ptr_List       m_list;
   static const Fl_Variant m_fieldNotFound;
public:
   Fl_Data_Fields() {}
   ~Fl_Data_Fields() { clear(); }
   void              clear();
   int               count() const { return m_list.count(); }
   int               field_index(const char * fname) const;
   Fl_Variant&       operator [] (int index);
   const Fl_Variant& operator [] (int index) const;
   Fl_Variant&       operator [] (const char *fname);
   const Fl_Variant& operator [] (const char *fname) const;
   const Fl_Data_Field& field(unsigned index) const;
   Fl_Data_Field&    field(unsigned index);
};

#endif
