/***************************************************************************
                          Fl_Data_Fields.cpp  -  description
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

#include <efltk/Fl_Data_Fields.h>

const Fl_Variant Fl_Data_Fields::m_fieldNotFound;

void Fl_Data_Fields::clear() {
   unsigned cnt = m_list.count();
   for (unsigned i = 0; i < cnt; i++) {
      Fl_Data_Field *field = (Fl_Data_Field *)m_list[i];
      delete field;
   }
}

int Fl_Data_Fields::field_index(const char *fname) const {
   unsigned cnt = m_list.count();
   for (unsigned i = 0; i < cnt; i++) {
      Fl_Data_Field *field = (Fl_Data_Field *)m_list[i];
      if (strcmp(field->name(),fname) == 0)
         return i;
   }
   return -1;  // field not found
}

Fl_Variant& Fl_Data_Fields::operator [] (int index) {
   Fl_Data_Field *field = (Fl_Data_Field *)m_list[index];
   return field->value;
}

const Fl_Variant& Fl_Data_Fields::operator [] (int index) const {
   Fl_Data_Field *field = (Fl_Data_Field *)m_list[index];
   return field->value;
}

Fl_Variant& Fl_Data_Fields::operator [] (const char *fname) {
   Fl_Data_Field *field;
   int index = field_index(fname);
   if (index < 0) {
      field = new Fl_Data_Field(fname);
      m_list.append(field);
   } else {
      field = (Fl_Data_Field *)m_list[index];
   }
   return field->value;
}

const Fl_Variant& Fl_Data_Fields::operator [] (const char *fname) const {
   int index = field_index(fname);
   if (index < 0) {
      return m_fieldNotFound;
   } else {
      Fl_Data_Field *field = (Fl_Data_Field *)m_list[index];
      return field->value;
   }
}
