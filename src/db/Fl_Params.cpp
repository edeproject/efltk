/***************************************************************************
                          Fl_Params.cpp  -  description
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

#include <efltk/db/Fl_Params.h>
#include <efltk/Fl_Exception.h>
#include <string.h>
#include <ctype.h>

//---------------------------------------------------------------------------
Fl_Param::Fl_Param(const char *name) : Fl_Variant() {
   m_name = name;
   m_name = m_name.lower_case();
}
//---------------------------------------------------------------------------
Fl_Param::~Fl_Param() {
}
//---------------------------------------------------------------------------
/*
Fl_Param& Fl_Param::operator = (const Fl_Param& param) {
   this->set_data(param);
   this->m_bindParamIndexes = param.m_bindParamIndexes;
   return *this;
}
*/
//---------------------------------------------------------------------------
void Fl_Param::bind_add(unsigned bindIndex) {
   m_bindParamIndexes.append((void *)bindIndex);
}
//---------------------------------------------------------------------------
void Fl_Params::clear() {
   for (unsigned i = 0; i < count(); i++) {
      Fl_Param *item = (Fl_Param *)m_items[i];
      delete item;
   }
   m_items.clear();
}
//---------------------------------------------------------------------------
void Fl_Params::add(const Fl_Param * item) {
   m_items.append((void *)item);
}
//---------------------------------------------------------------------------
Fl_Param& Fl_Params::operator [] (const unsigned index) const {
   if (index >= count())
      fl_throw("Invalid parameter index");
   return *(Fl_Param *)m_items[index];
}
//---------------------------------------------------------------------------
int Fl_Params::param_index(const char *paramName) {
   for (unsigned i = 0; i < count(); i++) {
      Fl_Param *item = (Fl_Param *)m_items[i];
      if ( item->name() == paramName )
         return i;
   }
   return -1;
}
//---------------------------------------------------------------------------
Fl_Param& Fl_Params::operator [] (const char *paramName) const {
   Fl_String pname = Fl_String(paramName).lower_case();
   for (unsigned i = 0; i < count(); i++) {
      Fl_Param *item = (Fl_Param *)m_items[i];
      if ( item->name() == pname )
         return *item;
   }
   fl_throw("Invalid parameter name: "+Fl_String(paramName));
   return *(Fl_Param *)0L;  // Just blocking the warning
}
//---------------------------------------------------------------------------
Fl_Param& Fl_Params::operator [] (const Fl_String& paramName) const {
   return operator[] (paramName.c_str());
}
//---------------------------------------------------------------------------
void Fl_Params::remove(unsigned index) {
   Fl_Param *item = (Fl_Param *)m_items[index];
   delete item;
   m_items.remove(index);
}
//---------------------------------------------------------------------------
