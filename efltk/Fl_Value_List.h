#ifndef FL_VALUE_LIST_H_
#define FL_VALUE_LIST_H_

/*
 Simple "value" based double linked list.
 This is like std::vector.
 Items stored in this list, must have:
 - copy constructor
 - assing operator
 - !=, == compare operators

 These kind a objects could be, e.g. std::string, Fl_String, int, float...

 example usage:

 Fl_Value_List<int> list;
 for(int n=0; n<1000; n++)
   list.append(n);

 Fl_Value_List<int>::Iterator it = list.begin();
 while(it!=list.end())
   do_something( (*it++) );

*/

template <class T> class Fl_Value_Item {
public:
    Fl_Value_Item(const T &t) : next(0), prev(0), stor(t) { }
    Fl_Value_Item() : next(0), prev(0) { }

    Fl_Value_Item<T> *next;
    Fl_Value_Item<T> *prev;
    T stor;
};

template <class  T> class Fl_Value_Iterator
{
public:
    Fl_Value_Iterator() : item(0) { }
    Fl_Value_Iterator(Fl_Value_Item<T> *i) : item(i) { }

    Fl_Value_Item<T> *item;

    bool operator==( const Fl_Value_Iterator<T>& it ) { return item == it.item; }
    bool operator!=( const Fl_Value_Iterator<T>& it ) { return item != it.item; }

    // de-reference operator returns reference to item
    const T& operator*() { return item->stor; }
    Fl_Value_Iterator<T>& operator++() {
        item = item->next;
        return *this;
    }
    Fl_Value_Iterator<T> operator++(int) {
        Fl_Value_Iterator<T> tmp = *this;
        item = item->next;
        return tmp;
    }
    Fl_Value_Iterator<T>& operator--() {
        item = item->prev;
        return *this;
    }
    Fl_Value_Iterator<T> operator--(int) {
        Fl_Value_Iterator<T> tmp = *this;
        item = item->prev;
        return tmp;
    }
};

template <class T> class Fl_Value_List
{
public:
    typedef Fl_Value_Iterator<T> Iterator;
    typedef Fl_Value_Item<T> Item;

protected:
    int items;
    Item *item_node;

public:
    Fl_Value_List() : items(0) { item_node = new Item; item_node->next=item_node->prev=item_node; }
    Fl_Value_List(Fl_Value_List<T> &list) { item_node = new Item; item_node->next=item_node->prev=item_node; copy(list); }
    ~Fl_Value_List() { clear(); }

    //////////////////////
    // Operators

    // Assing:
    Fl_Value_List<T>& operator = (const Fl_Value_List<T> &list) { if(this==&list) return *this; copy(list); return *this; }

    //Compare:
    bool operator!= (const Fl_Value_List<T> &list ) { return !( *this == list ); }
    bool operator== (const Fl_Value_List<T> &list ) {
        if( count() != list.count() ) return false;
        Iterator first = Iterator( item_node->next );
        Iterator first2 = Iterator( item_node->next );
        Iterator end = Iterator( item_node );
        for( ; first != end; ++first, ++first2 )
            if ( !( *first == *first2 ) ) return false;
        return true;
    }

    // Returns item at 'index', index starts from 0!
    inline T operator[](int index) {
        return item(index);
    }

    ///////////////

    // Copies list to this
    virtual void copy(const Fl_Value_List<T> &list) {
        clear();
        if(list.items>0) {
            Iterator first( list.item_node->next );
            Iterator last( list.item_node );
            Iterator it( item_node );
            while( first != last) {
                Item *p = new Item(first.item->stor);
                p->next = it.item;
                p->prev = it.item->prev;
                it.item->prev->next = p;
                it.item->prev = p;
                items++;

                ++first;
            }
        }
    }

    //////////////////

    // Iterators
    inline Iterator begin()     { return Iterator(item_node->next); }
    inline Iterator end()	{ return Iterator(item_node); }

    // Returns copy of item
    inline T first() 	 { return item_node->next ? item_node->next->stor : T(); }
    inline T last() 	 { return item_node->prev ? item_node->prev->stor : T(); }

    // Returns item at 'index', index starts from 0!
    inline T item(int index) {
        if(index < 0 || index >= items) return T();
        Item *p = item_node->next;
        for(int n = 0; n < index; n++) p = p->next;
        return p ? p->stor : T();
    }

    // Return count of items found
    inline int contains(T &item) {
        int result = 0;
        Iterator first = Iterator( item_node->next );
        Iterator last = Iterator( item_node );
        while( first != last) {
            if ( item == *first )
                ++result;
            ++first;
        }
        return result;
    }

    inline void remove(int index) { remove(at(index)); }

    //Returns number of deleted items
    inline int remove(T &it) {
        int result = 0;
        Iterator first = Iterator(item_node->next);
        Iterator last = Iterator(item_node);
        while(first != last) {
            if(it == *first) {
                first = remove(first);
                ++result;
            } else
                ++first;
        }
        return result;
    }

    // Returns Iterator at 'index', index starts from 0!
    inline Iterator at(int index) {
        if(index < 0 || index >= items) return Iterator();
        Item *p = item_node->next;
        for(int n = 0; n < index; ++n) p = p->next;
        return Iterator(p);
    }

    // Returns iterator from list, very fast method
    inline Iterator remove( Iterator it ) {
        Item *next = it.item->next;
        Item *prev = it.item->prev;
        prev->next = next;
        next->prev = prev;
        delete it.item;
        items--;
        return Iterator(next);
    }

    inline Iterator prepend(T &item) {	return insert(begin(), item); }
    inline Iterator append(T &item)  {	return insert(end(), item);   }

    // Inserts item T, after index pos
    inline Iterator insert(int pos, T &item) { return insert(at(pos), item); }
    // Inserts item T, after Iterator it
    inline Iterator insert(Iterator it, T &item) {
        Item *p = new Item(item);
        p->next = it.item;
        p->prev = it.item->prev;
        it.item->prev->next = p;
        it.item->prev = p;
        items++;
        return p;
    }

    inline void clear() {
        items = 0;
        Item *p = item_node->next;
        while(p != item_node) {
            Item *next = p->next;
            delete p;
            p = next;
        }
        item_node->next = item_node->prev = item_node;
    }

    inline const int count() { return items; }
    inline const bool empty() { return (count()==0); }
};

#endif

