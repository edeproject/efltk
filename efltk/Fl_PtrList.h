#ifndef FL_LIST_H_
#define FL_LIST_H_

// Backward compatible defines
//#define Fl_List  Fl_PtrList

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

    void copy(const Fl_PtrList<T> &list) {
        clear();
        First = 0;
        if(list.First) {
            items = 1;
            First = new Item(list.First->stor);
            Item *oldI = list.First;
            Item *newI = First;
            while(oldI = oldI->next) {
                items++;
                newI->next = new Item(oldI->stor);
                newI = newI->next;
            }
        }
    }

public:
    Fl_PtrList() : items(0), First(0), Last(0), Current(0) { autodel_=false; }
    Fl_PtrList(const Fl_PtrList<T> &list) { autodel_=false; copy(list); }
    ~Fl_PtrList() { clear(); }

    void begin() { Current = 0; }
    void end()	 { Current = 0; }
    T *first() 	 { Current = First; return First ? First->stor : 0; }
    T *last() 	 { Current = Last;  return Last ? Last->stor : 0; 	}
    T *current() { return Current ? Current->stor : 0; }

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

    inline T *item(int index) {
        if(index < 0 || index >= items)
            return 0;
        Item *it = First;
        if(index != 0)
            for(int a = 0; a < index; a++)
                it = it->next;
        Current = it;
        return it ? it->stor : 0;
    }

    inline T *item(T *it) {
        if(items<=0 || !First || !it) return;
        if(First && it == First->stor) {
            Current = First;
            return Current->stor;
        } else if(Last && it == Last->stor) {
            Current = Last;
            return Current->stor;
        }
        Current = First;
        while(Current = Current->next) {
            if(Current->stor == it) {
                break;
            }
        }
        return Current->stor;
    }

    inline void remove(T *it) {
        if(items<=0 || !First || !it) return;
        if(First && it == First->stor) {
            --items;
            Item *save_next = First->next;
            delete First;
            First = save_next;
            if(save_next&&items>0) First->prev=0;
            else First = Last = 0;
            Current = 0;
            return;
        } else if(Last && it == Last->stor) {
            --items;
            Item *save_prev = Last->prev;
            delete Last;
            Last = save_prev;
            if(save_prev&&items>0) Last->next = 0;
            else First = Last = 0;
            Current = 0;
            return;
        }

        Item *r = 0;
        Current = First;
        First = Last = Current;
        while(Current = Current->next) {
            if(Current->stor != it) {
                Last->next = Current;
                Current->prev = Last;
                Last = Current;
            } else {
                --items;
                r = Current;
            }
        }
        if(r) delete r;
        Current = 0;
    }

    inline void remove(int index) {
        remove(item(index));
    }

    T *next() {
        if(Current) {
            Current = Current->next;
            if(!Current) return 0;
        } else
            return first();
        return Current ? Current->stor : 0;
    }

    T *prev() {
        if(Current) {
            Current = Current->prev;
            if(!Current) return 0;
        } else
            return last();
        return Current ? Current->stor : 0;
    }

    inline void prepend(T *item) {
        Item *temp = new Item(item);
        items++;

        if(!First) {
            temp->prev = 0;
            temp->next = 0;
            First = Last = temp;
            return;
        }
        First->prev = temp;
        temp->next = First;
        temp->prev = 0;
        First = temp;
    }

    inline void append(T *item) {
        Item *temp = new Item(item);
        items++;

        if(!First) {
            temp->prev = 0;
            temp->next = 0;
            First = Last = temp;
            return;
        }
        Last->next = temp;
        temp->prev = Last;
        temp->next = 0;
        Last = temp;
    }

    inline void clear() {
        items = 0;
        Item *temp;
        while(First) {
            temp = First->next;
            if(autodel_ && First->stor) delete First->stor;
            delete First;
            First = temp;
        }
    }

    inline const int  count() { return items; }
    inline const bool empty() { return (count()==0); }

    inline bool auto_delete() { return autodel_; }
    inline void auto_delete(bool d) { autodel_ = d; }
};

#endif

