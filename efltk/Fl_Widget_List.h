#ifndef _FL_WIDGET_LIST_H_
#define _FL_WIDGET_LIST_H_

#include "Fl_Ptr_List.h"
#include "Fl_Widget.h"

class Fl_Widget_List : public Fl_Ptr_List {
public:
    Fl_Widget_List() : Fl_Ptr_List() { }

    void append(Fl_Widget *item) { Fl_Ptr_List::append((void *)item); }
    void prepend(Fl_Widget *item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(uint pos, Fl_Widget *item) { Fl_Ptr_List::insert(pos, (void *)item); }
    void replace(uint pos, Fl_Widget *item) { Fl_Ptr_List::replace(pos, (void *)item); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(Fl_Widget *item) { return Fl_Ptr_List::remove((void *)item); }
    int index_of(const Fl_Widget *w) const { return Fl_Ptr_List::index_of((void*)w); }
    Fl_Widget *item(uint index) const { return (Fl_Widget*)Fl_Ptr_List::item(index); }

    Fl_Widget **data() { return (Fl_Widget**)items; }

    Fl_Widget *operator [](uint ind) const { return (Fl_Widget *)items[ind]; }
};

#endif

