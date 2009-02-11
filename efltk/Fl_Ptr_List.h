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
typedef int (*Fl_Foreach_Function)(void *item, void *arg);
typedef int (*Fl_Sort_Function)(const void *item1, const void *item2);
typedef int (*Fl_Search_Function)(const void *key, const void *other);

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

    /**
     * Sort array using qsort algorithm.
     *
     * 'cmpfunc' returns:
     *  @li 0 if item1 == item2
     *  @li > 0 (positive integer) if item1 > item2
     *  @li < 0 (negative integer) if item1 < item2
     *
     * @param cmpfunc user provided compare function.
     */
    void sort(Fl_Sort_Function cmpfunc);

    /**
     * Search from list, using linear search algorithm.
     *
     * 'cmpfunc' returns:
     *  @li 0 if item1 == item2
     *  @li !=0 (non-zero integer) if item1 != item2
     *
     * @param cmpfunc user provided compare function.
     */
    Fl_Ptr_List_Item search(Fl_Ptr_List_Item key, Fl_Search_Function cmpfunc);

    /**
     * Search from list, using linear search algorithm.
     * @note List MUST be sorted before doing binary search.
     *
     * 'cmpfunc' returns:
     *  @li 0 if item1 == item2
     *  @li > 0 (positive integer) if item1 > item2
     *  @li < 0 (negative integer) if item1 < item2
     *
     * @param cmpfunc user provided compare function.
     */
    Fl_Ptr_List_Item binary_search(Fl_Ptr_List_Item key, Fl_Search_Function cmpfunc);

    /**
     * Returns index item 'p', support only pointer comparing.
     * Returns -1, if item not in list.
     */
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
