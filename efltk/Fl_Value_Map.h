#ifndef FL_VALUE_MAP_H_
#define FL_VALUE_MAP_H_

#define Fl_Map Fl_Value_Map

#include "Fl_Value_List.h"

template <class KEY, class VALUE> class Fl_Map_Pair {
public:
    Fl_Map_Pair(const KEY &_key, const VALUE &_value) : key(_key), value(_value) { }
    Fl_Map_Pair(const Fl_Map_Pair<KEY, VALUE> &m) { key=m.key; value=m.value; }
    Fl_Map_Pair() { }

    Fl_Map_Pair<KEY, VALUE>& operator = (const Fl_Map_Pair<KEY, VALUE> &m) { key=m.key; value=m.value; return *this; }

    KEY key;
    VALUE value;
};

template <class KEY, class VALUE> class Fl_Value_Map : public Fl_Value_List< Fl_Map_Pair<KEY, VALUE> >
{
public:
    typedef Fl_Map_Pair<KEY, VALUE> MapPair;

    Fl_Value_Map() { }
    ~Fl_Value_Map() { }

    VALUE &value_end() { return item_node->stor.value; }

    void add(KEY &key, VALUE &value) { append(key, value); }
    void append(KEY &key, VALUE &value) {
        MapPair pair(key, value);
        append(pair);
    }
    void append(MapPair &pair) {
        Fl_Value_List<MapPair>::append(pair);
    }

    VALUE find(KEY key) { return __get(key, false); }
    VALUE &operator[](KEY key) { KEY tmp(key); return __get(tmp, true); }
    void set(KEY key, VALUE value) { __set(key, value); }

    bool contains(KEY key) {
        Iterator iter = begin();
        while(iter != end()) {
            if(iter.item->stor.key == key)
                return true;
            ++iter;
        }
        return false;
    }

private:
    VALUE &__get(KEY &key, bool add) {
        Iterator iter = begin();
        while(iter != end()) {
            if(iter.item->stor.key == key)
                return iter.item->stor.value;
            ++iter;
        }
        if(add) {
            VALUE v;
            MapPair val(key, v);
            Iterator it = Fl_Value_List<MapPair>::append(val);
            return it.item->stor.value;
        }
        return item_node->stor.value;
    }

    void __set(KEY &key, VALUE &value) {
        Iterator iter = begin();
        while(iter != end()) {
            if(iter.item->stor.key == key)
                iter.item->stor.value = value;
            ++iter;
        }
        append(key, value);
    }
};

template <class KEY, class VALUE> inline Fl_Map_Pair<KEY, VALUE> fl_makepair(const KEY &key, const VALUE &val) {
    return Fl_Map_Pair<KEY, VALUE>(key, val);
}

#endif
