/***************************************************************************
                          Fl_Buffer.h  -  description
                             -------------------
    begin                : Sun Feb 2 2003
    copyright            : (C) 2000 by Alexey S.Parshin
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

#ifndef __FL_BUFFER_H__
#define __FL_BUFFER_H__

#include <efltk/Fl_Export.h>
#include <efltk/Fl_String.h>

class FL_API Fl_Buffer {
protected:
    unsigned m_size;
    unsigned m_bytes;
    char *   m_buffer;
public:
    Fl_Buffer(unsigned sz=16);
    ~Fl_Buffer();
    char *data() const { return m_buffer; }
    bool check_size(unsigned sz);

    void set(const char *data,unsigned sz);
    void set(const Fl_Buffer& buffer);
    void set(const Fl_String& str);

    void append(const char *data,unsigned sz);
    void append(const Fl_Buffer& buffer);
    void append(const Fl_String& buffer);

    Fl_Buffer& operator = (const Fl_Buffer& buffer) {
        set(buffer);
        return *this;
    }

    Fl_Buffer& operator = (const Fl_String& buffer) {
        set(buffer);
        return *this;
    }

    Fl_Buffer& operator += (const Fl_Buffer& buffer) {
        append(buffer);
        return *this;
    }

    Fl_Buffer& operator += (const Fl_String& buffer) {
        append(buffer);
        return *this;
    }

    void reset();
    void fill(char c);

    unsigned size()  const { return m_size; }
    unsigned bytes() const { return m_bytes; }
    void bytes(unsigned b) { set(0L,b); }
};

class FL_API Fl_String_Buffer : public Fl_Buffer {
public:
    Fl_String_Buffer(unsigned sz=16) : Fl_Buffer(sz) {}
    char& operator [] (int ndx) { return m_buffer[ndx]; }
};

#endif
