#ifndef _FL_PTR_STACK_H_
#define _FL_PTR_STACK_H_

#include "Fl_Ptr_List.h"

class Fl_Ptr_Stack {	
public:
    Fl_Ptr_Stack() { }
    virtual ~Fl_Ptr_Stack() { }

    virtual void push(void *data);
    virtual void *pop();
    virtual void clear();
    void *peek();
    bool empty() { return (items.size()==0); }
    uint size() { return items.size(); }

protected:
    Fl_Ptr_List items;
};

#endif

