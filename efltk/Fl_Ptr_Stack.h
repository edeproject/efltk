#ifndef _FL_PTR_STACK_H_
#define _FL_PTR_STACK_H_

#include "Fl_Ptr_List.h"

class Fl_Ptr_Stack {	
public:
    // Max size, 0=unlimited
    Fl_Ptr_Stack(int max_size=0) { max_size_ = max_size; }
    virtual ~Fl_Ptr_Stack() { clear(); }

    void clear();

    void push(void *data);
    void *pop();
    void *peek();

    bool empty() { return (items.size()==0); }
    uint size() { return items.size(); }

    uint max_size() { return max_size_; }
    void max_size(int m) { max_size_ = m; }

protected:
    // Free item in list e.g.: delete (SomeClass*)(item);
    virtual void free_item(void *item);

    void check_size();
    Fl_Ptr_List items;
    uint max_size_;
};

#endif

