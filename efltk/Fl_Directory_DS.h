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

#ifndef _FL_DIRECTORY_DS_H_
#define _FL_DIRECTORY_DS_H_

#include <efltk/Fl_Memory_DS.h>

class Fl_Directory_DS : public Fl_Memory_DS  {
public:
    // ctor, dtor 
    Fl_Directory_DS() : Fl_Memory_DS(), m_showpolicy(0) { }
    virtual ~Fl_Directory_DS() { close(); }

    enum {
        SHOW_ALL = 0,
        HIDE_FILES = 1,
        HIDE_DOT_FILES = 2,
        HIDE_DIRECTORIES = 4,
        NO_SORT = 8
    };

    char showpolicy() const { return m_showpolicy; }
    void showpolicy(char type) { m_showpolicy = type; }

    void directory(const char *d) { m_directory = d; }
    void directory(const Fl_String &d) { m_directory = d; }
    const Fl_String &directory() const { return m_directory; }

    void pattern(const char *pattern) { m_pattern = pattern; }
    void pattern(const Fl_String &pattern) { m_pattern = pattern; }
    const Fl_String &pattern() const { return m_pattern; }

    // dataset navigation
    virtual bool              open();

protected:

    Fl_String get_file_type(const struct stat &st, const Fl_Image *&image) const;

private:
    Fl_String           m_directory;
    Fl_String           m_pattern;
    char                    m_showpolicy;
};

#endif
