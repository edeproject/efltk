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

#ifndef _FL_WIDGET_LIST_H_
#define _FL_WIDGET_LIST_H_

#include "Fl_Ptr_List.h"
#include "Fl_Widget.h"

class Fl_Widget_List : public Fl_Ptr_List {
public:
    Fl_Widget_List() : Fl_Ptr_List() { }

    void append(Fl_Widget *item) { Fl_Ptr_List::append((void *)item); }
    void prepend(Fl_Widget *item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(uint pos, Fl_Widget *item) { Fl_Ptr_List::insert(pos, (void *)item); }
    void replace(uint pos, Fl_Widget *item) { Fl_Ptr_List::replace(pos, (void *)item); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(Fl_Widget *item) { return Fl_Ptr_List::remove((void *)item); }
    int index_of(const Fl_Widget *w) const { return Fl_Ptr_List::index_of((void*)w); }
    Fl_Widget *item(uint index) const { return (Fl_Widget*)Fl_Ptr_List::item(index); }

    Fl_Widget **data() { return (Fl_Widget**)items; }

    Fl_Widget *operator [](uint ind) const { return (Fl_Widget *)items[ind]; }

protected:
    void free_item(Fl_Widget *item) { delete (Fl_Widget*)(item); }
};

#endif
