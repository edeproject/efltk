/***************************************************************************
                          Fl_Params.h  -  description
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

#ifndef _FL_PARAMS_H_
#define _FL_PARAMS_H_

#include "../Fl_String.h"
#include "../Fl_Variant.h"
#include "../Fl_Ptr_List.h"

class Fl_Param : public Fl_Variant {
    Fl_String         m_name;
    Fl_Ptr_List       m_bindParamIndexes;

public:
    Fl_Param(const char *name);
    ~Fl_Param();

    const Fl_String& name() const { return m_name; }
    void       bind_clear() { m_bindParamIndexes.clear(); }
    void       bind_add(unsigned bindIndex);
    unsigned   bind_count() { return m_bindParamIndexes.count(); }
    unsigned   bind_index(unsigned ind) { return (unsigned)m_bindParamIndexes[ind]; }

    // ASSIGNMENT OPERATORS
    Fl_Variant& operator =(const Fl_Variant &C) {
        if (this == &C) return *this;
        set_data(C);
        return *this;
    }

    Fl_Variant& operator =(const char *s) {
        set_string(s);
        return *this;
    }

    Fl_Variant& operator =(const Fl_String &s) {
        set_string(s.c_str(), s.length());
        return *this;
    }

    Fl_Variant& operator =(int v) {
        set_int(v);
        return *this;
    }

    Fl_Variant& operator =(double v) {
        set_float(v);
        return *this;
    }

    Fl_Variant& operator =(Fl_Date_Time dt) {
        set_date(dt);
        return *this;
    }

    Fl_Variant& operator =(const Fl_Image *pm) {
        set_image_ptr(pm);
        return *this;
    }
};

class Fl_Params {
    Fl_Ptr_List m_items;
    void       clear();
public:
    Fl_Params() {};
    ~Fl_Params() { clear(); }

    int        param_index(const char *paramName);
    Fl_Param&  operator[] (unsigned index) const;
    Fl_Param&  operator[] (const char *paramName) const;
    Fl_Param&  operator[] (const Fl_String& paramName) const;
    void       add(const Fl_Param * item);
    void       remove(unsigned index);
    unsigned   count() const { return m_items.count(); }
};

#endif
