#ifndef _FL_CALLBACK_LIST_H_
#define _FL_CALLBACK_LIST_H_

#include "Fl_Ptr_List.h"
#include "Fl_Widget.h"

typedef struct CallbackDataStruct {
    CallbackDataStruct(Fl_Callback *c, void *a) { cb=c; arg=a; }
    Fl_Callback *cb;
    void *arg;
} CallbackData;

class Fl_Callback_List : public Fl_Ptr_List {
public:
    Fl_Callback_List() : Fl_Ptr_List() { auto_delete(true); }

    void do_callback(Fl_Widget *w);
    void do_callback(Fl_Widget *w, void *arg);

    void append(Fl_Callback *cb, void *arg) { Fl_Ptr_List::append((void *)new CallbackData(cb, arg)); }
    void prepend(Fl_Callback *cb, void *arg) { Fl_Ptr_List::prepend((void *)new CallbackData(cb, arg)); }
    void insert(uint pos, Fl_Callback *cb, void *arg) { Fl_Ptr_List::insert(pos, (void *)new CallbackData(cb, arg)); }
    void replace(uint pos,Fl_Callback *cb, void *arg) { Fl_Ptr_List::replace(pos, (void *)new CallbackData(cb, arg)); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(Fl_Callback *cb, void *arg);
    int index_of(Fl_Callback *cb, const void *arg) const;

    Fl_Callback *callback(uint index) const { return (Fl_Callback*)((CallbackData*)Fl_Ptr_List::item(index))->cb; }
    void *arg(uint index) const { return (void*)((CallbackData*)Fl_Ptr_List::item(index))->arg; }
    CallbackData *item(uint index) const { return (CallbackData*)Fl_Ptr_List::item(index); }

    CallbackData **data() { return (CallbackData**)items; }
    CallbackData *operator [](uint ind) const { return (CallbackData*)items[ind]; }

protected:
    void free_item(CallbackData *item) { delete (CallbackData*)(item); }
};

#endif
