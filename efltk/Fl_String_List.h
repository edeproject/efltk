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

#ifndef _FL_STRING_LIST_H_
#define _FL_STRING_LIST_H_

#include "Fl_Ptr_List.h"
#include "Fl_String.h"
#include <stdio.h>

/** Fl_String based string list */
class Fl_String_List {
public:
    Fl_String_List();
    Fl_String_List(const Fl_String_List& sl);
    Fl_String_List(const char *str, const char *separator);
    ~Fl_String_List() { clear(); }

    void clear();

    void resize(unsigned newsize);

    //Default is 0, means auto-calculated
    void blocksize(int s) { blocksize_ = s; }
    int blocksize() { return blocksize_; }

    bool empty() const { return size_==0; }
    unsigned count() const { return size_; }
    unsigned size() const { return size_; }

    void sort(int (*fcmp)(const void *, const void *));
    void sort();

    void append(const Fl_String_List &items);
    void append(const Fl_String &item);
    void append(const char *item);

    void prepend(const Fl_String &item) { insert(0, item); }
    void prepend(const char *item)      { insert(0, item); }
    void prepend(const Fl_String_List &list) { insert(0, list); }

    void insert(unsigned pos, const Fl_String &item);
    void insert(unsigned pos, const Fl_String_List &list);

    //Returns number of removed items
    int remove(Fl_String item);
    void remove(unsigned pos);

    //Return first index of found string. -1 if none
    int index_of(const Fl_String &str) const;
    int index_of(const char *str) const;

    // Returns allocated char* string of list
    char *to_cstring(const char *separator) const;
    Fl_String to_string(const char *separator) const;
    void from_string(const char *str, const char *separator);

    Fl_String &item(unsigned index) { return items[index]; }
    const Fl_String &item(unsigned index) const { return items[index]; }

    Fl_String &operator [](unsigned ind) { return items[ind]; }
    const Fl_String &operator [](unsigned ind) const { return items[ind]; }

    Fl_String_List& operator = (const Fl_String_List& sl) { clear(); append(sl); return *this; }

    void print(FILE *fp=stdout) const;

private:
    Fl_String *items;

    unsigned blocksize_;
    unsigned capacity_;
    unsigned size_;
};

// Char pointer based string list
class Fl_CString_List : public Fl_Ptr_List {
public:
    Fl_CString_List() : Fl_Ptr_List() { }

    void sort();

    void append(const char *item)  { Fl_Ptr_List::append((void *)item); }
    void prepend(const char *item) { Fl_Ptr_List::prepend((void *)item); }

    void insert(unsigned pos, const char *item) { Fl_Ptr_List::insert(pos, (void *)item); }

    void remove(unsigned pos) { Fl_Ptr_List::remove(pos); }
    bool remove(const char *item) { return Fl_Ptr_List::remove((void *)item); }

    int index_of(const char *w) const { return Fl_Ptr_List::index_of((void*)w); }

    const char *item(unsigned index) const { return (const char *)Fl_Ptr_List::item(index); }
    const char *operator [](unsigned ind) const { return (const char *)items[ind]; }

    void print(FILE *fp=stdout) const;
};

#endif
