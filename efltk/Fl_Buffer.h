/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Alexey Parshin
 * Email  : alexey@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_BUFFER_H_
#define _FL_BUFFER_H_

#include "Fl_Export.h"
#include "Fl_String.h"

/**
 * Fl_Buffer is core buffer class in eFLTK.
 */
class FL_API Fl_Buffer 
{
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
    void append(char ch);
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

    void save_file(const char *fileName);
    void read_file(const char *fileName);
};

/**
 * Fl_String_Buffer is Fl_Buffer derived class
 * used for all kind of string buffering...
 */
class FL_API Fl_String_Buffer : public Fl_Buffer {
public:
    Fl_String_Buffer(unsigned sz=16) : Fl_Buffer(sz) {}
    char& operator [] (int ndx) { return m_buffer[ndx]; }
};

#endif
