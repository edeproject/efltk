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

// Fl_String based string list
class Fl_String_List : public Fl_Ptr_List {
public:
    Fl_String_List() : Fl_Ptr_List() { auto_delete_ = true; }
	~Fl_String_List() { clear(); }

    void sort();

    void append(const Fl_String &item);
    void append(const char *item);
    
	void prepend(const Fl_String &item);
    void prepend(const char *item);

    void insert(uint pos, const Fl_String &item);
    void insert(uint pos, const Fl_String_List &list);

    //Returns number of removed items
    int remove(Fl_String item);
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    //Return first index of found string. -1 if none
    int index_of(const Fl_String &str) const;
    int index_of(const char *str) const;

	// Returns allocated char* string of list
    char *to_cstring(const char *separator) const;
    Fl_String to_string(const char *separator) const;
    void from_string(const char *str, const char *separator);

    Fl_String *item(uint index) const { return (Fl_String*)Fl_Ptr_List::item(index); }
    Fl_String &operator [](uint ind) const { return *((Fl_String *)items[ind]); }
protected:
    void free_item(Fl_Ptr_List_Item item);
};

// Char pointer based string list
class Fl_CString_List : public Fl_Ptr_List {
public:
    Fl_CString_List() : Fl_Ptr_List() { }

    void sort();

    void append(const char *item) { Fl_Ptr_List::append((void *)item); }
    void prepend(const char *item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(unsigned pos, const char *item) { Fl_Ptr_List::insert(pos, (void *)item); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(const char *item) { return Fl_Ptr_List::remove((void *)item); }
    int index_of(const char *w) const { return Fl_Ptr_List::index_of((void*)w); }

    const char *item(uint index) const { return (const char *)Fl_Ptr_List::item(index); }
    const char *operator [](uint ind) const { return (const char *)items[ind]; }
};

#endif
