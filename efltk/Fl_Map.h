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

#define HASH_LOOKUP_SMALL  17
#define HASH_LOOKUP_MEDIUM 101
#define HASH_LOOKUP_BIG    1007
#define HASH_LOOKUP_HUGE   10017

#define HASH_LOOKUP_DEFAULT HASH_LOOKUP_SMALL

class Fl_Map;

////////////////////////////////////////

class Fl_Map_Iterator {
    friend class Fl_Map;
public:
    Fl_Map_Iterator(const Fl_Map &map);
    Fl_Map_Iterator(const Fl_Map_Iterator &i) { m_map = i.m_map; m_x = i.m_x; m_y = i.m_y; }

    bool is_valid();

    bool operator == (const Fl_Map_Iterator &i) const { return (get_pair()==i.get_pair()); }
    bool operator != (const Fl_Map_Iterator &i) const { return (get_pair()!=i.get_pair()); }

    Fl_Map_Iterator &first();
    Fl_Map_Iterator &last();
    Fl_Map_Iterator &next();
    Fl_Map_Iterator &prior();

protected:
    void *get_pair() const;

    const Fl_Map *m_map;
    int m_x, m_y;
};

/** Fl_Map */
class Fl_Map {
    friend class Fl_Map_Iterator;
public:
    static unsigned hash_string( const char *key, int table_size );
    static unsigned hash_int( int key, int table_size );

    virtual void clear();

    unsigned hash_size() const { return m_lists_size; }
    unsigned size() const { return m_items; }

protected:
    Fl_Map(int hash_size);
    virtual ~Fl_Map() { }

    unsigned insert_pair(int Y, void *pair);
    bool remove_pair(int Y, void *pair);

    virtual void free_pair(void *item) const = 0;

    unsigned m_items;     ///< Number of items in map
    uint m_lists_size;    ///< Size of m_lists array
    Fl_Ptr_List *m_lists; ///< Array of lists
};

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

class Fl_String_String_Iterator;

/** Fl_String_String_Map */
class Fl_String_String_Map : public Fl_Map {
public:
    struct Pair { Fl_String id; Fl_String val; };
    typedef Fl_String_String_Iterator Iterator;

    static Pair *pair(const char *id, const char *val);
    static Pair *pair(const char *id, const Fl_String &val);

    Fl_String_String_Map(int hash_size=HASH_LOOKUP_DEFAULT) : Fl_Map(hash_size) { }
    virtual ~Fl_String_String_Map() { clear(); }

    bool contains(const char *id) const;

    bool insert(const char *id, const char *val);
    bool insert(const char *id, const Fl_String &val);
    bool remove(const char *id);

    void set_value(const char *id, const char *val);
    void set_value(const char *id, const Fl_String &val);
    Fl_String &get_value(const char *id) const;

    Fl_String &operator [](const char *id);
    const Fl_String &operator [](const char *id) const;

protected:
    virtual void free_pair(void *item) const { delete (Pair*)(item); }

private:
    Pair *find_pair(int Y, const char *id) const;
};

class Fl_String_String_Iterator : public Fl_Map_Iterator
{
public:
    Fl_String_String_Iterator(const Fl_Map &map) : Fl_Map_Iterator(map) { }
    Fl_String_String_Iterator(const Fl_Map_Iterator &i) : Fl_Map_Iterator(i) { }

    const Fl_String &id() const { Fl_String_String_Map::Pair *p=current_pair(); return (p ? p->id : Fl_String::null_object); }
    Fl_String &value() const    { Fl_String_String_Map::Pair *p=current_pair(); return (p ? p->val : Fl_String::null_object); }

    Fl_String_String_Map::Pair *operator*() const { return current_pair(); }
    Fl_String_String_Map::Pair *current()   const { return current_pair(); }

    Fl_String_String_Iterator& operator++()    { next(); return *this; }
    Fl_String_String_Iterator operator++(int) { Fl_String_String_Iterator tmp=*this; next(); return tmp; }
    Fl_String_String_Iterator& operator--()    { prior(); return *this; }
    Fl_String_String_Iterator operator--(int) { Fl_String_String_Iterator tmp=*this; prior(); return tmp; }

private:
    Fl_String_String_Map::Pair *current_pair() const { return (Fl_String_String_Map::Pair*)get_pair(); }
};

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

class Fl_Int_String_Iterator;

/** Fl_Int_String_Map */
class Fl_Int_String_Map : public Fl_Map {
public:
    struct Pair { int id; Fl_String val; };
    typedef Fl_Int_String_Iterator Iterator;

    static Pair *pair(int id, const char *val);
    static Pair *pair(int id, const Fl_String &val);

    Fl_Int_String_Map(int hash_size=HASH_LOOKUP_DEFAULT) : Fl_Map(hash_size) { }
    virtual ~Fl_Int_String_Map() { clear(); }

    bool contains(int id) const;

    bool insert(int id, const char *val);
    bool insert(int id, const Fl_String &val);
    bool remove(int id);

    void set_value(int id, const char *val);
    void set_value(int id, const Fl_String &val);
    Fl_String &get_value(int id) const;

    Fl_String &operator [](int id);
    const Fl_String &operator [](int id) const;

protected:
    virtual void free_pair(void *item) const { delete (Pair*)(item); }

private:
    Pair *find_pair(int Y, int id) const;
};

class Fl_Int_String_Iterator : public Fl_Map_Iterator
{
public:
    Fl_Int_String_Iterator(const Fl_Map &map) : Fl_Map_Iterator(map) { }
    Fl_Int_String_Iterator(const Fl_Map_Iterator &i) : Fl_Map_Iterator(i) { }

    int id() const { Fl_Int_String_Map::Pair *p=current_pair(); return (p ? p->id : -1); }
    Fl_String &value() const { Fl_Int_String_Map::Pair *p=current_pair(); return (p ? p->val : Fl_String::null_object); }

    Fl_Int_String_Map::Pair *operator*() const { return current_pair(); }
    Fl_Int_String_Map::Pair *current()   const { return current_pair(); }

    Fl_Int_String_Iterator& operator++()    { next(); return *this; }
    Fl_Int_String_Iterator& operator++(int) { next(); return *this; }
    Fl_Int_String_Iterator& operator--()    { prior(); return *this; }
    Fl_Int_String_Iterator& operator--(int) { prior(); return *this; }

private:
    Fl_Int_String_Map::Pair *current_pair() const { return (Fl_Int_String_Map::Pair*)get_pair(); }
};

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

class Fl_String_Ptr_Iterator;

/** Fl_String_Ptr_Map */
class Fl_String_Ptr_Map : public Fl_Map {
public:
    struct Pair { Fl_String id; void *val; };
    typedef Fl_String_Ptr_Iterator Iterator;

    static Pair *pair(const char *id, void *val);

    Fl_String_Ptr_Map(int hash_size=HASH_LOOKUP_DEFAULT) : Fl_Map(hash_size) { }
    virtual ~Fl_String_Ptr_Map() { clear(); }

    bool contains(const char *id) const;

    bool insert(const char *id, void *val);
    bool remove(const char *id);

    void set_value(const char *id, void *val);
    void *get_value(const char *id) const;

    void *operator [](const char *id);
    const void *operator [](const char *id) const;

protected:
    virtual void free_pair(void *item) const { delete (Pair *)(item); }

private:
    Pair *find_pair(int Y, const char *id) const;
};

class Fl_String_Ptr_Iterator : public Fl_Map_Iterator
{
public:
    Fl_String_Ptr_Iterator(const Fl_Map &map) : Fl_Map_Iterator(map) { }
    Fl_String_Ptr_Iterator(const Fl_Map_Iterator &i) : Fl_Map_Iterator(i) { }

    const Fl_String &id() const { Fl_String_Ptr_Map::Pair *p=current_pair(); return (p ? p->id : Fl_String::null_object); }
    void *value() const { Fl_String_Ptr_Map::Pair *p=current_pair(); return (p ? p->val : 0); }

    Fl_String_Ptr_Map::Pair    *operator*() const { return current_pair(); }
    Fl_String_Ptr_Map::Pair    *current()   const { return current_pair(); }

    Fl_String_Ptr_Iterator& operator++()    { next(); return *this; }
    Fl_String_Ptr_Iterator& operator++(int) { next(); return *this; }
    Fl_String_Ptr_Iterator& operator--()    { prior(); return *this; }
    Fl_String_Ptr_Iterator& operator--(int) { prior(); return *this; }
private:
    Fl_String_Ptr_Map::Pair *current_pair() const { return (Fl_String_Ptr_Map::Pair*)get_pair(); }
};

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

class Fl_Int_Ptr_Iterator;

/** Fl_Int_Ptr_Map */
class Fl_Int_Ptr_Map : public Fl_Map {
public:
    struct Pair { int id; void *val; };
    typedef Fl_Int_Ptr_Iterator Iterator;

    static Pair *pair(int id, void *val);

    Fl_Int_Ptr_Map(int hash_size=HASH_LOOKUP_DEFAULT) : Fl_Map(hash_size) { }
    virtual ~Fl_Int_Ptr_Map() { clear(); }

    bool contains(int id) const;

    bool insert(int id, void *val);
    bool remove(int id);

    void set_value(int id, void *val);
    void *get_value(int id) const;

    void *operator [](int id);
    const void *operator [](int id) const;

protected:
    virtual void free_pair(void *item) const { delete (Pair *)(item); }

private:
    Pair *find_pair(int Y, int id) const;
};

class Fl_Int_Ptr_Iterator : public Fl_Map_Iterator
{
public:
    Fl_Int_Ptr_Iterator(const Fl_Map &map) : Fl_Map_Iterator(map) { }
    Fl_Int_Ptr_Iterator(const Fl_Map_Iterator &i) : Fl_Map_Iterator(i) { }

    int id() const { Fl_Int_Ptr_Map::Pair *p=current_pair(); return (p ? p->id : -1); }
    void *value() const { Fl_Int_Ptr_Map::Pair *p=current_pair(); return (p ? p->val : 0); }

    Fl_Int_Ptr_Map::Pair    *operator*() const { return current_pair(); }
    Fl_Int_Ptr_Map::Pair    *current()   const { return current_pair(); }

    Fl_Int_Ptr_Iterator& operator++()    { next(); return *this; }
    Fl_Int_Ptr_Iterator& operator++(int) { next(); return *this; }
    Fl_Int_Ptr_Iterator& operator--()    { prior(); return *this; }
    Fl_Int_Ptr_Iterator& operator--(int) { prior(); return *this; }
private:
    Fl_Int_Ptr_Map::Pair *current_pair() const { return (Fl_Int_Ptr_Map::Pair*)get_pair(); }
};

#endif
