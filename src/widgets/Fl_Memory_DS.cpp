/***************************************************************************
                                                    Fl_Memory_DS.cpp  -  description
                                                          -------------------
        begin                : Wed Feb 12 2003
        copyright            : (C) 2003 by Alexey Parshin
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

#include <config.h>

#include <efltk/Fl_Memory_DS.h>
#include <efltk/Fl_Exception.h>

#include <stdlib.h>

#define checkDSopen(ds) if (!ds) fl_throw("Dataset isn't open") 

      // access to the field by name
const Fl_Variant& Fl_Directory_DS::operator [] (const char *field_name) const {
    checkDSopen(m_current);
    return (*m_current)[field_name];
}

Fl_Variant& Fl_Directory_DS::operator [] (const char *field_name) {
    checkDSopen(m_current);
    return (*m_current)[field_name];
}

const Fl_Data_Field& Fl_Directory_DS::field (int field_index) const {
    checkDSopen(m_current);
    return m_current->field(field_index);
}

Fl_Data_Field& Fl_Directory_DS::field (int field_index) {
    checkDSopen(m_current);
    return m_current->field(field_index);
}

unsigned Fl_Directory_DS::record_count() const {
    checkDSopen(m_current);
    return m_list.count();
}

// how many fields do we have in the current record?
unsigned Fl_Directory_DS::field_count() const {
    checkDSopen(m_current);
    return m_current->count();
}

int Fl_Directory_DS::field_index(const char *field_name) const {
    checkDSopen(m_current);
    return m_current->field_index(field_name);
}

// access to the field by number, 0..field_count()-1
const Fl_Variant& Fl_Directory_DS::operator [] (int index) const {
    checkDSopen(m_current);
    return (*m_current)[index];
}

Fl_Variant& Fl_Directory_DS::operator [] (int index) {
    checkDSopen(m_current);
    return (*m_current)[index];
}

// read this field data into external value
bool Fl_Directory_DS::read_field(const char *fname,Fl_Variant& fvalue) {
    fl_try {
        fvalue = (*this)[fname];      
    }
fl_catch(exc) { return false; }
return true;
}

// write this field data from external value
bool Fl_Directory_DS::write_field(const char *fname, const Fl_Variant& fvalue) {
    fl_try {
        (*this)[fname] = fvalue;      
    }
fl_catch(exc) { return false; }
return true;
}


bool Fl_Directory_DS::close() {
    clear();
    return true;
}

bool Fl_Directory_DS::first() {
    if (m_list.count()) {
        m_currentIndex = 0;
        m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
        m_eof = false;
        return true;
    }
    m_eof = true;
    return false;
}

bool Fl_Directory_DS::last() {
    unsigned cnt = m_list.count();
    if (cnt) {
        m_currentIndex = cnt - 1;
        m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
        m_eof = false;
        return true;
    }
    m_eof = true;
    return false;
}

bool Fl_Directory_DS::next() {
    unsigned cnt = m_list.count();
    if (m_currentIndex + 1 < (int)cnt) {
        m_currentIndex++;
        m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
        m_eof = false;
        return true;
    }
    m_eof = true;
    return false;
}

bool Fl_Directory_DS::prior() {
    if (m_currentIndex > 0) {
        m_currentIndex--;
        m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
        m_eof = false;
        return true;
    }
    m_eof = true;
    return false;
}

bool Fl_Directory_DS::find(Fl_Variant position) {
    unsigned    cnt = m_list.count();
    Fl_String   name;
    unsigned i;
    switch (position.type()) {
        case VAR_INT:  if (position.get_int() < (int)cnt) {
                m_currentIndex = position.get_int();
                m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
                return true;
            }
            break;
        case VAR_STRING:
            name = position.get_string();
            for (i = 0; i < cnt; i++) {
                Fl_Data_Fields& entry = *(Fl_Data_Fields *)m_list[i];
                if (entry["Name"] == name) {
                    m_currentIndex = i;
                    m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
                    return true;
                }
            }
            break;
        default:       break;
    }
    return false;
}

void Fl_Directory_DS::clear() {
    unsigned cnt = m_list.count();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Data_Fields *df = (Fl_Data_Fields *) m_list[i];
        delete df;
    }
    m_list.clear();
    m_current = 0L;
    m_currentIndex = -1;
    m_eof = true;
}
