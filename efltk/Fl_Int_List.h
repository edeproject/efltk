#ifndef _FL_INT_LIST_H_
#define _FL_INT_LIST_H_

#include "Fl_Ptr_List.h"

class Fl_Int_List : public Fl_Ptr_List {
public:
    Fl_Int_List() : Fl_Ptr_List() { }

    void sort();

    void append(int item) { Fl_Ptr_List::append((void *)item); }
    void prepend(int item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(unsigned pos, int item) { Fl_Ptr_List::insert(pos, (void *)item); }

    //Return first index of found integer. -1 if none
    int index_of(const int i);
    int contains(const int i);

    char *to_string(const char *separator=",");
    void from_string(const char * s, const char * separator=",");

    int item(uint index) const { return (int)Fl_Ptr_List::item(index); }
    int &operator [](uint ind) const { return (int&)items[ind]; }
};

#endif
