#ifndef FL_VALUE_STACK_H_
#define FL_VALUE_STACK_H_

/*
 Simple "value" based stack
 Items stored in this list, must have:
 - copy constructor
 - assing operator
 - !=, == compare operators

 This is very self-explaining :)

 push() appends item
 pop() returns and removes item
 top() returns last pushed item

*/

#include "Fl_Value_List.h"

template <class T> class Fl_ValueStack : public Fl_ValueList<T>
{
public:
    Fl_ValueStack() { }
    void push(T &item) { append(item); }
    T pop() {
        T elem(last());
        if(!empty()) remove(last_iter());
        return elem;
    }
    T top() { return last(); }
};

#endif

