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
#include <efltk/Fl_Exception.h>

#include <stdio.h>
#include <stdlib.h>

// ctor
Fl_Data_Field::Fl_Data_Field(const char *name) {
    m_name = name;
    width = -1;
    flags = FL_ALIGN_LEFT;
    m_dataSize = 0;
    visible = true;
    precision = 3; // default precision, only affects floating point fields
}

Fl_String Fl_Data_Field::as_string() const {
    char print_buffer[32];
    switch (value.type()) {
        case VAR_INT:
            sprintf(print_buffer,"%i",value.get_int());
            return Fl_String(print_buffer);
        case VAR_FLOAT:
            {
                char formatString[] = "%0.1f";
                int prec = precision;
                if (prec < 0) {
                    formatString[4] = 'e';
                    prec = -prec;
                }
                if (prec > 9) prec = 9;
                formatString[3] = '0' + prec;
                sprintf(print_buffer,formatString,value.get_float());               
                return Fl_String(print_buffer);
            }
        case VAR_STRING:
        case VAR_TEXT:
        case VAR_BUFFER:     return Fl_String(value.get_string(), m_dataSize);
        case VAR_DATE:       return value.get_date().date_string();
        case VAR_DATETIME:   return value.get_date().date_string() + " " + value.get_date().time_string();
        case VAR_IMAGEPTR:   fl_throw("Can't convert image field");
        case VAR_NONE:       fl_throw("Can't convert field w/o type");
    }
    return "";
}

void Fl_Data_Fields::clear() {
    unsigned cnt = m_list.count();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Data_Field *field = (Fl_Data_Field *)m_list[i];
        delete field;
    }
    m_list.clear();
}

static Fl_Data_Field error("");
Fl_Data_Field& Fl_Data_Fields::add(const char *fname) {
    int index = field_index(fname);
    if (index < 0) {
        Fl_Data_Field *field = new Fl_Data_Field(fname);
        m_list.append(field);
        return *field;
    }
    fl_throw("Attempt to duplicate field name");
}

Fl_Data_Field& Fl_Data_Fields::add(Fl_Data_Field *field) {
    m_list.append(field);
    return *field;
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
    Fl_Data_Field *field=0;
    int index = field_index(fname); 
    if (index < 0) {
        fl_throw("Field name not found");
    } else {
        field = (Fl_Data_Field *)m_list[index];
    }
    return field->value;
}

const Fl_Variant& Fl_Data_Fields::operator [] (const char *fname) const {
    int index = field_index(fname);
    if (index < 0) {
        fl_throw("Field name not found");
    }
    Fl_Data_Field *field = (Fl_Data_Field *)m_list[index];
    return field->value;
}

const Fl_Data_Field& Fl_Data_Fields::field(unsigned index) const {
    return *(Fl_Data_Field *)m_list[index];
}

Fl_Data_Field& Fl_Data_Fields::field(unsigned index) {
    return *(Fl_Data_Field *)m_list[index];
}

const Fl_Data_Field& Fl_Data_Fields::field(int index) const {
    return *(Fl_Data_Field *)m_list[index];
}

Fl_Data_Field& Fl_Data_Fields::field(int index) {
    return *(Fl_Data_Field *)m_list[index];
}

const Fl_Data_Field& Fl_Data_Fields::field(const char *field_name) const {
    int index = field_index(field_name);
    if (index < 0) 
        fl_throw("Invalid field name: "+Fl_String(field_name));
    return *(Fl_Data_Field *)m_list[index];
}

Fl_Data_Field& Fl_Data_Fields::field(const char *field_name) {
    int index = field_index(field_name);
    if (index < 0) 
        fl_throw("Invalid field name: "+Fl_String(field_name));
    return *(Fl_Data_Field *)m_list[index];
}
