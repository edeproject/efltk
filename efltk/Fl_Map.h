#ifndef _FL_MAP_H_
#define _FL_MAP_H_

#include "Fl_String.h"
#include "Fl_Ptr_List.h"

struct Fl_MapPair {
    Fl_MapPair() { }
    virtual ~Fl_MapPair() { }
};

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

    Fl_MapPair **data() { return (Fl_MapPair**)items.data(); }
    Fl_MapPair *item(uint index) const { return (Fl_MapPair*)items.item(index); }

    uint size() { return items.size(); }

protected:
    virtual void free_pair(Fl_MapPair *item) { delete (Fl_MapPair*)(item); }
    Fl_Ptr_List items;
};

////////////////////////////////////////

struct Fl_String2String_MapPair : public Fl_MapPair {
    Fl_String id;
    Fl_String val;
};

class Fl_String2String_Map : public Fl_Map {
public:
    static Fl_String2String_MapPair *pair(const Fl_String id, Fl_String val);

    Fl_String2String_Map() : Fl_Map() { }
    virtual ~Fl_String2String_Map() { clear(); }

    Fl_String2String_MapPair *find_pair(Fl_String id);

    void set_value(const Fl_String id, Fl_String val);
    Fl_String *get_value(const Fl_String id);

    Fl_String2String_MapPair *item(uint index) const { return (Fl_String2String_MapPair*)Fl_Map::item(index); }
    Fl_String &operator [](Fl_String id);
};

////////////////////////////////////////

struct Fl_Int2String_MapPair : public Fl_MapPair {
    int id;
    Fl_String val;
};

class Fl_Int2String_Map : public Fl_Map {
public:
    static Fl_Int2String_MapPair *pair(const int id, Fl_String val);

    Fl_Int2String_Map() : Fl_Map() { }
    virtual ~Fl_Int2String_Map() { }

    Fl_Int2String_MapPair *find_pair(int id);

    void set_value(const int id, Fl_String val);
    Fl_String *get_value(const int id);

    Fl_Int2String_MapPair *item(uint index) const { return (Fl_Int2String_MapPair *)Fl_Map::item(index); }
    Fl_String &operator [](const int id);
};

#endif