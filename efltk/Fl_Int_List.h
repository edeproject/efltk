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

#ifndef _FL_INT_LIST_H_
#define _FL_INT_LIST_H_

#include "Fl_Ptr_List.h"

class Fl_Int_List : public Fl_Ptr_List {
public:
    Fl_Int_List() : Fl_Ptr_List() { }
	virtual ~Fl_Int_List() { clear(); }

    void sort();

    void append(int item) { Fl_Ptr_List::append((void *)item); }
    void prepend(int item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(unsigned pos, int item) { Fl_Ptr_List::insert(pos, (void *)item); }

    //Return first index of found integer. -1 if none
    int index_of(const int i);
    int contains(const int i);

    char *to_string(const char *separator=",");
    void from_string(const char * s, const char * separator=",");

    int item(uint index) const { return (int)Fl_Ptr_List::item(index); }
    int &operator [](uint ind) const { return (int&)items[ind]; }
};

#endif
