#ifndef _FL_STRING_LIST_H_
#define _FL_STRING_LIST_H_

#include "Fl_Ptr_List.h"
#include "Fl_String.h"

// Fl_String based string list
class Fl_String_List : public Fl_Ptr_List {
public:
    Fl_String_List() : Fl_Ptr_List() { auto_delete_ = true; }

    void sort();

    void append(Fl_String item);
    void append(const char*item);
    void prepend(Fl_String item);
    void insert(uint pos, Fl_String &item);
    void insert(uint pos, const Fl_String_List &list);

    //Returns number of removed items
    int remove(Fl_String item);
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    //Return first index of found string. -1 if none
    int index_of(const Fl_String str);
    int contains(const Fl_String str);

    char *to_cstring(const char *separator);
    Fl_String to_string(const char *separator);
    void from_string(const char *s, const char *separator);

    Fl_String *item(uint index) const { return (Fl_String*)Fl_Ptr_List::item(index); }
    Fl_String &operator [](uint ind) const { return *((Fl_String *)items[ind]); }
protected:
    void free_item(Fl_Ptr_List_Item item);
};

// Char pointer based string list
class Fl_CString_List : public Fl_Ptr_List {
public:
    Fl_CString_List() : Fl_Ptr_List() { }

    void sort();

    void append(const char *item) { Fl_Ptr_List::append((void *)item); }
    void prepend(const char *item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(unsigned pos, const char *item) { Fl_Ptr_List::insert(pos, (void *)item); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(const char *item) { return Fl_Ptr_List::remove((void *)item); }
    int index_of(const char *w) const { return Fl_Ptr_List::index_of((void*)w); }

    const char *item(uint index) const { return (const char *)Fl_Ptr_List::item(index); }
    const char *operator [](uint ind) const { return (const char *)items[ind]; }
};

#endif
