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

#ifndef _FL_MAP_H_
#define _FL_MAP_H_

#include "Fl_String.h"
#include "Fl_Ptr_List.h"

struct Fl_MapPair {
    Fl_MapPair() { }
    virtual ~Fl_MapPair() { }
};

/** Fl_Map */
class Fl_Map {
public:
    Fl_Map() { }
    virtual ~Fl_Map();

    virtual void clear();

    Fl_MapPair *append_pair(Fl_MapPair *item);
    Fl_MapPair *prepend_pair(Fl_MapPair *item);
    Fl_MapPair *insert_pair(uint pos, Fl_MapPair *item);
    Fl_MapPair *replace_pair(uint pos, Fl_MapPair *item);

    bool remove_pair(uint pos);
    bool remove_pair(Fl_MapPair *item);

    int index_of(const Fl_MapPair *w) const { return items.index_of((void*)w); }

    Fl_MapPair **data() const { return (Fl_MapPair**)items.data(); }
    Fl_MapPair *item(uint index) const { return (Fl_MapPair*)items.item(index); }

    unsigned size() const { return items.size(); }

protected:
    virtual void free_pair(Fl_MapPair *item) { delete (Fl_MapPair*)(item); }
    Fl_Ptr_List items;
};

////////////////////////////////////////

struct Fl_String_String_Pair : public Fl_MapPair {
    Fl_String id;
    Fl_String val;
};

/** Fl_String_String_Map */
class Fl_String_String_Map : public Fl_Map {
public:
	typedef Fl_String_String_Pair Pair;
    
	static Pair *pair(const char *id, const char *val);
	static Pair *pair(const char *id, const Fl_String &val);

    Fl_String_String_Map() : Fl_Map() { }
    virtual ~Fl_String_String_Map() { clear(); }

    Fl_String_String_Pair *find_pair(const char *id) const;

    void set_value(const char *id, const char *val);
    void set_value(const char *id, const Fl_String &val);
    Fl_String *get_value(const char *id) const;

    Pair *item(unsigned index) const { return (Pair*)Fl_Map::item(index); }
    Fl_String &operator [](const char *id);
};

////////////////////////////////////////

struct Fl_Int_String_Pair : public Fl_MapPair {
    int id;
    Fl_String val;
};

/** Fl_Int_String_Map */
class Fl_Int_String_Map : public Fl_Map {
public:
	typedef Fl_Int_String_Pair Pair;
    
	static Fl_Int_String_Pair *pair(const int id, const char *val);
	static Fl_Int_String_Pair *pair(const int id, const Fl_String &val);

    Fl_Int_String_Map() : Fl_Map() { }
    virtual ~Fl_Int_String_Map() { }

    Pair *find_pair(int id) const;

    void set_value(const int id, const Fl_String &val);
    void set_value(const int id, const char *val);
    Fl_String *get_value(const int id) const;

    Fl_Int_String_Pair *item(uint index) const { return (Fl_Int_String_Pair *)Fl_Map::item(index); }
    Fl_String &operator [](const int id);
};

#endif
