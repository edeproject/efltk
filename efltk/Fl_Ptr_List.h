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

#ifndef _FL_PTR_LIST_H_
#define _FL_PTR_LIST_H_

#include "Enumerations.h"

typedef void* Fl_Ptr_List_Item;
typedef int (*Fl_Foreach_Function)(void *item,void *arg);

/**
 * Fl_Ptr_List is implementation of EFLTK generic pointer-list...
 *
 * (More information about this class is comming soon, or not.. :)
 */
class FL_API Fl_Ptr_List {
public:
    Fl_Ptr_List();
    virtual ~Fl_Ptr_List();

    virtual void clear();

    void resize(unsigned newsize);

    void auto_delete(bool val) { auto_delete_ = val; }
    bool auto_delete() { return auto_delete_; }

    //Default is 0, means auto-calculated
    void blocksize(int s) { blocksize_ = s; }
    int blocksize() { return blocksize_; }

    bool empty() const { return size_==0; }
    unsigned count() const { return size_; }
    unsigned size() const { return size_; }

    void append(void *item);
    void prepend(void *item);

    void insert(unsigned pos, Fl_Ptr_List_Item item);
    void replace(unsigned pos, Fl_Ptr_List_Item item);

    void remove(unsigned pos);
    bool remove(Fl_Ptr_List_Item ptr);

    void sort(int (*fcmp)(const void *, const void *));
    int index_of(const Fl_Ptr_List_Item p) const;

    Fl_Ptr_List_Item item(unsigned index) const;
    Fl_Ptr_List_Item& operator [] (unsigned ind) const { return items[ind]; }

    Fl_Ptr_List_Item *data() const { return items; }	

    // Copy
    Fl_Ptr_List& operator = (const Fl_Ptr_List &list);
    Fl_Ptr_List(const Fl_Ptr_List &list);

    // Call 'todo' for every item til 'todo' returns 'true',
    // then return item index or (-1) if 'todo' never return 'true'.
    int for_each(Fl_Foreach_Function todo,void * arg);
    int for_each(Fl_Foreach_Function todo,void * arg) const;


protected:
    // Free item in list e.g.: delete (SomeClass*)(item);
    virtual void free_item(Fl_Ptr_List_Item item);

    Fl_Ptr_List_Item *items;
    bool auto_delete_;

private:
    unsigned blocksize_;
    unsigned capacity_;
    unsigned size_;
};

#endif
