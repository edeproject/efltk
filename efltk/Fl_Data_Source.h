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

#ifndef _FL_DATA_SOURCE_H_
#define _FL_DATA_SOURCE_H_

#include "Fl_Variant.h"
#include "Fl_Data_Fields.h"

class Fl_Group;

/** Fl_Data_Source */
class Fl_Data_Source {
    friend class Fl_Group;
public:
    // ctor, dtor
    Fl_Data_Source(Fl_Group *group) { parent_ = group; }
    virtual ~Fl_Data_Source() {}

    // access to the field by name
    virtual const Fl_Variant& operator [] (const char *field_name) const = 0;
    virtual Fl_Variant&       operator [] (const char *field_name) = 0;

     // how many rows do we have ds?
    virtual unsigned          record_count() const = 0;

    // how many fields do we have in the current record?
    virtual unsigned          field_count() const = 0;
    virtual int               field_index(const char *) const { return -1; }

    // access to the field by number, 0..field_count()-1
    virtual const Fl_Variant& operator [] (int) const = 0;
    virtual Fl_Variant&       operator [] (int) = 0;

    virtual const Fl_Data_Field& field (int field_index) const = 0;
    virtual Fl_Data_Field&       field (int field_index) = 0;
    virtual void             *user_data() const { return 0L; } 

    virtual bool              read_field(const char *fname,Fl_Variant& value) = 0;
    virtual bool              write_field(const char *fname,const Fl_Variant& fvalue) = 0;

    // dataset navigation
    virtual bool              open()  { return false; }
    virtual bool              close() { return false; }
    virtual bool              first() { return false; }
    virtual bool              next()  { return false; }
    virtual bool              prior() { return false; }
    virtual bool              last()  { return false; }
    virtual bool              find(Fl_Variant position) { return false; }
    virtual bool              eof() const  { return false; }

    // load data into widgets
    bool load();
    // unload data from widgets
    bool save();

protected:
    // these methods should be implemented in derived class
    virtual bool              load_data() = 0;
    virtual bool              save_data() = 0;
    Fl_Group* parent_;
};

#endif
