/***************************************************************************
                          Fl_Variant.cpp  -  description
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

#include <efltk/Fl_Variant.h>
#include <string.h>
#include <stdlib.h>

void Fl_Variant::free_buffers() {
   if (m_type == STRING || m_type == BUFFER) {
      if (m_data.stringData)
         free(m_data.stringData);
   }
}
//---------------------------------------------------------------------------
void Fl_Variant::set_int(int value) {
   free_buffers();
   m_type = INT;
   m_size = sizeof(value);

   m_data.intData = value;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_float(double value) {
   free_buffers();
   m_type = FLOAT;
   m_size = sizeof(value);
   m_data.floatData = value;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_string(const char * value,int maxlen) {
   if (m_type == STRING && maxlen && m_size == maxlen+1) {

      if (value) strncpy(m_data.stringData,value,m_size);
      else m_data.stringData[0] = 0;

   } else {

      free_buffers();
      if (value) {
         if (maxlen) {
            m_size = maxlen + 1;
            m_data.stringData = (char *)malloc(m_size);
            strncpy(m_data.stringData,value,m_size);
            //memcpy(m_data.stringData,value,m_size);
         } else {
            m_size = strlen(value) + 1;
            m_data.stringData = strdup(value);
         }
      } else {
         m_data.stringData = NULL;
         m_size = 0;
      }
   }
   m_type = STRING;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_text(const char * value) {
   free_buffers();
   m_type = TEXT;
   if (value) {
      m_size = strlen(value);
      m_data.stringData = strdup(value);
   } else {
      m_data.stringData = NULL;
      m_size = 0;
   }
}
//---------------------------------------------------------------------------
void Fl_Variant::set_buffer(const void *value, int sz) {
   free_buffers();
   m_type = BUFFER;
   if (value) {
      m_size = sz;
      m_data.stringData = (char *)malloc(sz);
      memcpy(m_data.stringData,value,sz);
   } else {
      m_data.stringData = NULL;
      m_size = 0;
   }
}
//---------------------------------------------------------------------------
void Fl_Variant::set_date(Fl_Date_Time value) {
   free_buffers();
   m_type = DATETIME;
   m_size = sizeof(value);
   m_data.floatData = value;
}
//---------------------------------------------------------------------------
int Fl_Variant::get_int() const {
   return m_data.intData;
}
//---------------------------------------------------------------------------
double Fl_Variant::get_float() const {
   return m_data.floatData;
}
//---------------------------------------------------------------------------
const char * Fl_Variant::get_string() const {
   return m_data.stringData;
}
//---------------------------------------------------------------------------
const void * Fl_Variant::get_buffer() const {
   return m_data.stringData;
}
//---------------------------------------------------------------------------
Fl_Date_Time Fl_Variant::get_date() const {
   return m_data.floatData;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_data(const Fl_Variant &C) {
   switch (C.m_type) {
   case INT:     	set_int(C.get_int());            break;
   case FLOAT:   	set_float(C.get_float());                break;
   case STRING:  	set_string(C.get_string());              break;
   case TEXT:  	    set_buffer(C.get_buffer(),C.size()); break;
   case BUFFER:  	set_buffer(C.get_buffer(),C.size()); break;
   case DATETIME:   set_date(C.get_date());          break;
   case NONE:    	break;
   }
}
//---------------------------------------------------------------------------
Fl_Variant::operator int () const {
   return m_data.intData;
}

Fl_Variant::operator double () const {
   return m_data.floatData;
}

Fl_Variant::operator const char * () const {
   return m_data.stringData;
}

Fl_Variant::operator Fl_Date_Time () const {
   return m_data.floatData;
}

