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

#include <Fl_Variant.h>
#include <string.h>
#include <stdlib.h>

void Fl_Variant::releaseBuffers() {
   if (m_type == CVT_STRING || m_type == CVT_BUFFER) {
      if (m_data.stringData)
         free(m_data.stringData);
   }
}
//---------------------------------------------------------------------------
void Fl_Variant::setInteger(int value) {
   releaseBuffers();
   m_type = CVT_INT;
   m_size = sizeof(value);

   m_data.intData = value;
}
//---------------------------------------------------------------------------
void Fl_Variant::setFloat(double value) {
   releaseBuffers();
   m_type = CVT_FLOAT;
   m_size = sizeof(value);
   m_data.floatData = value;
}
//---------------------------------------------------------------------------
void Fl_Variant::setString(const char * value,int maxlen) {
   if (m_type == CVT_STRING && maxlen && m_size == maxlen+1) {
      if (value)
            strncpy(m_data.stringData,value,m_size);
      else  m_data.stringData[0] = 0;
   } else {
      releaseBuffers();
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
   m_type = CVT_STRING;
}
//---------------------------------------------------------------------------
void Fl_Variant::setText(const char * value) {
   releaseBuffers();
   m_type = CVT_TEXT;
   if (value) {
      m_size = strlen(value);
      m_data.stringData = strdup(value);
   } else {
      m_data.stringData = NULL;
      m_size = 0;
   }
}
//---------------------------------------------------------------------------
void Fl_Variant::setBuffer(const void * value,int sz) {
   releaseBuffers();
   m_type = CVT_BUFFER;
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
void Fl_Variant::setDateTime(Fl_Date_Time value) {
   releaseBuffers();
   m_type = CVT_DATETIME;
   m_size = sizeof(value);
   m_data.floatData = value;
}
//---------------------------------------------------------------------------
int Fl_Variant::getInteger() const {
   return m_data.intData;
}
//---------------------------------------------------------------------------
double Fl_Variant::getFloat() const {
   return m_data.floatData;
}
//---------------------------------------------------------------------------
const char * Fl_Variant::getString() const {
   return m_data.stringData;
}
//---------------------------------------------------------------------------
const void * Fl_Variant::getBuffer() const {
   return m_data.stringData;
}
//---------------------------------------------------------------------------
Fl_Date_Time Fl_Variant::getDateTime() const {
   return m_data.floatData;
}
//---------------------------------------------------------------------------
void Fl_Variant::setData(const Fl_Variant &C) {
   switch (C.m_type) {
   case CVT_INT:     	setInteger(C.getInteger());            break;
   case CVT_FLOAT:   	setFloat(C.getFloat());                break;
   case CVT_STRING:  	setString(C.getString());              break;
   case CVT_TEXT:  	   setBuffer(C.getBuffer(),C.dataSize()); break;
   case CVT_BUFFER:  	setBuffer(C.getBuffer(),C.dataSize()); break;
   case CVT_DATETIME:   setDateTime(C.getDateTime());          break;
   case CVT_NONE:    	break;
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

