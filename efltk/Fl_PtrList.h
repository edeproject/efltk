#ifndef FL_LIST_H_
#define FL_LIST_H_

/*
 Simple double-linked template list.

 Example usage:
 Fl_PtrList<Object> list;
 list.append(obj);
 ...
 list.prepend(obj);
 ...
 list.remove(obj);


 Iterating throught the list: (several ways)
 reverse iterating by changing calls: "[first()|begin()] to [last()|end()]" and "next() to prev()"

 for(Object *o=list.first(); o; o=list.next())
   do_something(o);

 OR

 list.begin();
 while(list.next())
   do_something(list.current());

 */

template <class T> class Fl_PtrList
{
private:
    class Item {
    public:
        Item(T *t) : next(0), prev(0) { stor = t; }
        Item() 	   : next(0), prev(0) { stor = 0; }
        Item *next, *prev;
        T *stor;
    };

    bool autodel_;
    int items;
    Item *First, *Last, *Current;

public:
    Fl_PtrList() : items(0), First(0), Last(0), Current(0) { autodel_=false; }
    Fl_PtrList(const Fl_PtrList<T> &list) : items(0), First(0), Last(0), Current(0) { autodel_=false; copy(list); }
    ~Fl_PtrList() { clear(); }

    // Moves to the begin of list
    inline void begin()  { Current = First; }
    // Moves to the end of list
    inline void end()	 { Current = Last; }
    // Moves to begin and returns item
    inline T *first() 	 { Current = First; return First ? First->stor : 0; }
    // Moves to end and returns item
    inline T *last() 	 { Current = Last;  return Last ? Last->stor : 0; 	}

    // Returns current item, changed by calls: begin(), end(), first(), last(), next(), prev(), item()
    inline T *current() { return Current ? Current->stor : 0; }
    // Sets current pointer
    inline void current(T *it) { Current = item(it); }

    //////////////////////
    // Operators

    // Assing:
    Fl_PtrList<T>& operator = (const Fl_PtrList<T> &list) { if(this==&list) return *this; copy(list); return *this; }
    //Compare:
    bool operator!= (const Fl_PtrList<T> &list ) { return !( *this == list ); }
    bool operator== (const Fl_PtrList<T> &list ) {
        if( count() != list.count() ) return false;
        Item *it = First;
        Item *it2= list.First;
        for(; it!=0; it=it->next, it2=it2->next )
            if ( !(it->stor==it2->stor) ) return false;
        return true;
    }
    // Returns item at 'index', index starts from 0!
    inline T *operator[](int index) {
        return item(index);
    }

    //////////////////

    // Copies list to this
    void copy(const Fl_PtrList<T> &list) {
        clear();
        First = Last = Current = 0;
        if(!list.First) return;

        Item *iter = list.First;
        do {
            if(!First) {
                First = Current = new Item(iter->stor);
            } else {
                Current->next = new Item(iter->stor);
                Current = Current->next;
            }
            items++;
        } while(iter = iter->next);
        Last=Current;
        Current=0;
    }

    // Returns item at position 'index'
    // NOTE: This function sets 'Current' pointer!
    inline T *item(int index) {
        if(index < 0 || index >= items) return 0;
        Item *it = First;
        for(int a = 0; a < index; a++)
            it = it->next;
        Current = it;
        return it ? it->stor : 0;
    }

    // Returns item 'it', if it's found in list.
    // NOTE: This function sets 'Current' pointer!
    inline T *item(T *it) {
        if(items<=0 || !First || !it) return;
        if(Current && it == Current->stor) {
            return Current->stor;
        }
        Item *iter=Fisrt;
        do {
            if(iter->stor == it) {
                Current = iter;
                break;
            }
        } while(iter = iter->next);
        return iter?iter->stor:0;
    }

    // Remove item 'it' from list,
    // NOTE: DOES NOT set 'Current' pointer, this allows fast removing while iterating throught the list.
    inline void remove(T *it) {
        if(items<=0 || !First || !it) return;

        Item *remove = 0;
        Item *iter = First;

        // Check if removed item is Current pointer
        if(Current && it == Current->stor) {
            --items;
            remove = Current;
            Item *prev = remove->prev;
            Item *next = remove->next;
            if(prev) prev->next = next;
            if(next) next->prev = prev;
            Current = prev;
        }

        // It's not on list, so we have to go throught whole list,
        // until we got item to remove.
        if(!remove) {
            do {
                if(iter->stor == it) {
                    --items;
                    Item *prev = iter->prev;
                    Item *next = iter->next;
                    if(prev) prev->next = next;
                    if(next) next->prev = prev;
                    remove = iter;
                    break;
                }
            } while(iter = iter->next);
        }

        // Assing new 'Current' pointer, if needed.
        if(remove && remove==Current) Current=remove->prev;
        if(remove && remove==First) First=remove->next;
        if(remove && remove==Last) Last=remove->prev;

        if(remove) {
            if(autodel_ && remove->stor) delete remove->stor;
            delete remove; remove=0;
        }
    }

    // Remove item at 'index'
    inline void remove(int index) {
        remove(item(index));
    }

    // Returns and moves to the next item in list
    inline T *next() {
        if(Current) {
            Current = Current->next;
            if(!Current) return 0;
        } else
            return first();
        return Current ? Current->stor : 0;
    }

    // Returns and moves to the previous item in list
    inline T *prev() {
        if(Current) {
            Current = Current->prev;
            if(!Current) return 0;
        } else
            return last();
        return Current ? Current->stor : 0;
    }

    // Adds 'item' to start of the list
    inline void prepend(T *item) {
        Item *temp = new Item(item);
        if(First) First->prev = temp;
        if(!Last) Last=temp;
        temp->next = First;
        temp->prev = 0;
        First = temp;
        items++;
    }

    // Adds 'item' at end of the list.
    inline void append(T *item) {
        Item *temp = new Item(item);
        if(Last) Last->next = temp;
        if(!First) First=temp;
        temp->prev = Last;
        temp->next = 0;
        Last = temp;
        items++;
    }

    // Clear the list
    // NOTE: items are deleted, if auto_delete is set to true!
    inline void clear() {
        items = 0;
        if(!First) return;
        Item *iter, *next=First;
        do {
            iter=next;
            if(autodel_ && iter->stor) 
				if(iter->stor) delete iter->stor;
            next = iter->next;
            delete iter;
        } while(next);
        First=Last=Current=0;
    }

    // Returns items in list
    inline const int  count() { return items; }

    // Returns true if empty
    inline const bool empty() { return (count()==0); }

    // If auto_delete is true, item are deleted automaticaly, when removing from list.
    inline bool auto_delete() { return autodel_; }
    inline void auto_delete(bool d) { autodel_ = d; }
};

#endif

