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

#ifndef _FL_IMAGE_LIST_H_
#define _FL_IMAGE_LIST_H_

#include "Fl_Ptr_List.h"
#include "Fl_Image.h"

class Fl_Image_List : public Fl_Ptr_List {
public:
    Fl_Image_List() : Fl_Ptr_List() { }
	virtual ~Fl_Image_List() { clear(); }

    void append(Fl_Image *item) { Fl_Ptr_List::append((void *)item); }
    void prepend(Fl_Image  *item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(unsigned pos, Fl_Image *item) { Fl_Ptr_List::insert(pos, (void *)item); }
    void replace(uint pos, Fl_Image *item) { Fl_Ptr_List::replace(pos, (void *)item); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(Fl_Image *item) { return Fl_Ptr_List::remove((void *)item); }
    int index_of(const Fl_Image *w) const { return Fl_Ptr_List::index_of((void*)w); }

    Fl_Image **data() { return (Fl_Image**)items; }

    Fl_Image *item(uint index) const { return (Fl_Image*)Fl_Ptr_List::item(index); }
    Fl_Image *operator [](uint ind) const { return (Fl_Image *)items[ind]; }

protected:
    virtual void free_item(Fl_Ptr_List_Item item) { delete (Fl_Image*)(item); }
};

#endif
