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
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */
#ifndef _FL_PACKED_STRINGS_H_
#define _FL_PACKED_STRINGS_H_

#include "Enumerations.h"

/**
 * Fl_Packed_Strings
 */
class FL_API Fl_Packed_Strings {
public:
    Fl_Packed_Strings();
    Fl_Packed_Strings(int cnt, const char *strings[]);
    ~Fl_Packed_Strings();

    void resize(unsigned count);

    void set(unsigned index, const char *string);
    const char *get(unsigned index) const;

    unsigned count() const { return *(unsigned *)m_buffer; }

    const char *operator[](unsigned index) const { return get(index); }
    Fl_Packed_Strings& operator=(const Fl_Packed_Strings&);

private:
    unsigned m_size;
    void  *m_buffer;
};

#endif
