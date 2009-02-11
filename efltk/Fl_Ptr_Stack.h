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

#ifndef _FL_PTR_STACK_H_
#define _FL_PTR_STACK_H_

#include "Fl_Ptr_List.h"

/** Fl_Ptr_Stack */
class FL_API Fl_Ptr_Stack {
public:
    // Max size, 0=unlimited
    Fl_Ptr_Stack(int max_size=0) { max_size_ = max_size; }
    virtual ~Fl_Ptr_Stack() { clear(); }

    void clear();

    void push(void *data);
    void *pop();
    void *peek();

    bool empty() { return (items.size()==0); }
    uint size() { return items.size(); }

    uint max_size() { return max_size_; }
    void max_size(int m) { max_size_ = m; }

protected:
    // Free item in list e.g.: delete (SomeClass*)(item);
    virtual void free_item(void *item);

    void check_size();
    Fl_Ptr_List items;
    uint max_size_;
};

#endif

