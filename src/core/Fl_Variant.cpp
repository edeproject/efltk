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

#include <config.h>

#include <stdio.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Variant.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32_WCE
#include <wince.h>
#endif

Fl_Variant Fl_Variant::null_object;

void Fl_Variant::free_buffers() {
    if (m_type & (VAR_STRING|VAR_BUFFER)) {
        if (m_data.stringData)
            free(m_data.stringData);
    }
}
//---------------------------------------------------------------------------
// Various constructors

Fl_Variant::Fl_Variant(int value) {
    m_type = VAR_INT;
    m_size = sizeof(value);
    m_data.intData = value;
}

Fl_Variant::Fl_Variant(float value) {
    m_type = VAR_FLOAT;
    m_size = sizeof(value);
    m_data.floatData = value;
}

Fl_Variant::Fl_Variant(const char* value) {
    if (value) {
        m_size = strlen(value) + 1;
        m_data.stringData = strdup(value);
    } else {
        m_data.stringData = NULL;
        m_size = 0;
    }
    m_type = VAR_STRING;
}

Fl_Variant::Fl_Variant(const Fl_String& value) {
    m_size = value.length() + 1;
    m_data.stringData = strdup(value.c_str());
    m_type = VAR_STRING;
}

Fl_Variant::Fl_Variant(const void *value,int sz) {
    m_type = VAR_BUFFER;
    if (value) {
        m_size = sz;
        m_data.stringData = (char *)malloc(sz);
        memcpy(m_data.stringData,value,sz);
    } else {
        m_data.stringData = NULL;
        m_size = 0;
    }
}

Fl_Variant::Fl_Variant(Fl_Date_Time value) {
    m_type = VAR_DATETIME;
    m_size = sizeof(value);
    m_data.floatData = value;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_int(int value) {
    free_buffers();
    m_type = VAR_INT;
    m_size = sizeof(value);
    m_data.intData = value;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_float(double value) {
    free_buffers();
    m_type = VAR_FLOAT;
    m_size = sizeof(value);
    m_data.floatData = value;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_string(const char * value,int maxlen) {
    if (m_type == VAR_STRING && maxlen && m_size == maxlen+1) {
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
    m_type = VAR_STRING;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_text(const char * value) {
    free_buffers();
    m_type = VAR_TEXT;
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
    m_type = VAR_BUFFER;
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
void Fl_Variant::resize_buffer(int sz) {
    m_type = VAR_BUFFER;
    if (sz) {
        m_size = sz;
        m_data.stringData = (char *)realloc(m_data.stringData,sz);
    } else {
        free_buffers();
        m_data.stringData = NULL;
        m_size = 0;
    }
}
//---------------------------------------------------------------------------
void Fl_Variant::set_image_ptr(const Fl_Image *value) {
    free_buffers();
    m_type = VAR_IMAGEPTR;
    m_size = sizeof(value);
    m_data.imagePtr = value;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_date(Fl_Date_Time value) {
    free_buffers();
    m_type = VAR_DATE;
    m_size = sizeof(value);
    m_data.floatData = (int)value;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_datetime(Fl_Date_Time value) {
    free_buffers();
    m_type = VAR_DATETIME;
    m_size = sizeof(value);
    m_data.floatData = value;
}
//---------------------------------------------------------------------------
void Fl_Variant::set_data(const Fl_Variant &C) {
    switch (C.m_type) {
        case VAR_INT:        set_int(C.m_data.intData);           break;
        case VAR_FLOAT:      set_float(C.m_data.floatData);       break;
        case VAR_STRING:     set_string(C.m_data.stringData);     break;
        case VAR_TEXT:       set_buffer(C.m_data.stringData,C.size()); break;
        case VAR_BUFFER:     set_buffer(C.m_data.blobData,C.size()); break;
        case VAR_DATE:        set_date(C.m_data.floatData);         break;
        case VAR_DATETIME:   set_datetime(C.m_data.floatData);      break;
        case VAR_IMAGEPTR:   set_image_ptr(C.m_data.imagePtr);    break;
        case VAR_NONE:       break;
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

Fl_Variant::operator const Fl_Image * () const {
    return m_data.imagePtr;
}
//---------------------------------------------------------------------------
// convertors
int Fl_Variant::as_int() const {
    switch (m_type) {
        case VAR_INT:        return m_data.intData;
        case VAR_FLOAT:      return (int)m_data.floatData;
        case VAR_STRING:
        case VAR_TEXT:
        case VAR_BUFFER:     return strtol(m_data.stringData,0,10);
        case VAR_DATE:
        case VAR_DATETIME:   return int(m_data.floatData);
        case VAR_IMAGEPTR:   fl_throw("Can't convert image field");
        case VAR_NONE:       fl_throw("Can't convert field w/o type");
    }
    return 0;
}

bool Fl_Variant::as_bool() const {
    char ch;
    switch (m_type) {
        case VAR_INT:        return (m_data.intData>0);
        case VAR_FLOAT:      return (m_data.floatData>.5f);
        case VAR_STRING:
        case VAR_TEXT:
        case VAR_BUFFER:     ch = m_data.stringData[0];
            return (strchr("YyTt1",ch)!=0);
        case VAR_DATE:       
        case VAR_DATETIME:   return bool(m_data.floatData!=0);
        case VAR_IMAGEPTR:   fl_throw("Can't convert image field");
        case VAR_NONE:       fl_throw("Can't convert field w/o type");
    }
    return 0;
}

double Fl_Variant::as_float() const {
    switch (m_type) {
        case VAR_INT:        return m_data.intData;
        case VAR_FLOAT:      return m_data.floatData;
        case VAR_STRING:
        case VAR_TEXT:
        case VAR_BUFFER:     return strtod(m_data.stringData, 0);
        case VAR_DATE:       
        case VAR_DATETIME:   return m_data.floatData;
        case VAR_IMAGEPTR:   fl_throw("Can't convert image field");
        case VAR_NONE:       fl_throw("Can't convert field w/o type");
    }
    return 0;
}

Fl_String Fl_Variant::as_string() const {
    char print_buffer[32];
    switch (m_type) {
        case VAR_INT:
            sprintf(print_buffer,"%i",m_data.intData);
            return Fl_String(print_buffer);
        case VAR_FLOAT:
            {
                char formatString[] = "%0.4f";
                sprintf(print_buffer,formatString,m_data.floatData);                
                return Fl_String(print_buffer);
            }
        case VAR_STRING:
        case VAR_TEXT:
        case VAR_BUFFER:     return m_data.stringData;
        case VAR_DATE:       return Fl_Date_Time(m_data.floatData).date_string();
        case VAR_DATETIME:   {
                Fl_Date_Time dt(m_data.floatData);
                return dt.date_string() + " " + dt.time_string();
            }
        case VAR_IMAGEPTR:   fl_throw("Can't convert image field");
        case VAR_NONE:       fl_throw("Can't convert field w/o type");
    }
    return "";
}

Fl_Date_Time Fl_Variant::as_date() const {
    Fl_Date_Time   result;
    switch (m_type) {
        case VAR_INT:        result = m_data.intData;
            break;
        case VAR_FLOAT:      result = m_data.floatData;
            break;
        case VAR_STRING:
        case VAR_TEXT:
        case VAR_BUFFER:     result = m_data.stringData;
            break;
        case VAR_DATE:       
        case VAR_DATETIME:   result = int(m_data.floatData);
            break;
        case VAR_IMAGEPTR:   fl_throw("Can't convert image field");
        case VAR_NONE:       fl_throw("Can't convert field w/o type");
    }
    return result;
}

Fl_Date_Time Fl_Variant::as_datetime() const {
    Fl_Date_Time   result;
    switch (m_type) {
        case VAR_INT:        result = m_data.intData;
            break;
        case VAR_FLOAT:      result = m_data.floatData;
            break;
        case VAR_STRING:
        case VAR_TEXT:
        case VAR_BUFFER:     result = m_data.stringData;
            break;
        case VAR_DATE:       
        case VAR_DATETIME:   result = m_data.floatData;
            break;
        case VAR_IMAGEPTR:   fl_throw("Can't convert image field");
        case VAR_NONE:       fl_throw("Can't convert field w/o type");
    }
    return result;
}

const Fl_Image *Fl_Variant::as_image() const {
    switch (m_type) {
        default:             fl_throw("Can't convert image field");
        case VAR_IMAGEPTR:   return m_data.imagePtr;
    }
}
