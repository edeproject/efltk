#ifndef _FL_STRING_STACK_H_
#define _FL_STRING_STACK_H_

#include <efltk/Fl_String_List.h>

class Fl_String_Stack {
public:
    // Max size, 0=unlimited
    Fl_String_Stack(int max_size=0) { max_size_ = max_size; }
    virtual ~Fl_String_Stack() { clear(); }

    void clear();

    void push(Fl_String data);
    Fl_String pop();
    Fl_String peek();

    bool empty() { return (items.size()==0); }
    uint size() { return items.size(); }

    uint max_size() { return max_size_; }
    void max_size(int m) { max_size_ = m; }

protected:
    void check_size();
    Fl_String_List items;
    uint max_size_;
};

#endif

