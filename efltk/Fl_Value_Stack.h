#ifndef FL_VALUE_STACK_H_
#define FL_VALUE_STACK_H_

#define Fl_Stack Fl_Value_Stack

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

