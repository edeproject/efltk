#include <string.h>
#include <stdlib.h>
#include <efltk/vsnprintf.h>

/////////////////////////////////
// FL_PTR_LIST IMPLEMENTATION: //
/////////////////////////////////

#include <efltk/Fl_Ptr_List.h>

Fl_Ptr_List::Fl_Ptr_List()
{
    auto_delete_ = false;
    blocksize_ = 32;
    items = 0;
    capacity_ = 0;
    resize(0);
}

Fl_Ptr_List::~Fl_Ptr_List()
{
    clear();
}

void Fl_Ptr_List::clear()
{
    if(items) {
        if(auto_delete_) for(uint i = 0; i < size_; i++) free(items[i]);
        free(items);
    }
    items=0;
    size_=0;
    capacity_=0;
}

void Fl_Ptr_List::resize(uint newsize)
{
    if(newsize>capacity_) {
        // Grow list capacity
        capacity_= (newsize/blocksize_+1)*blocksize_;
        if(items) items = (Fl_Ptr_List_Item *)realloc(items, capacity_ * sizeof(Fl_Ptr_List_Item));
        else items = (Fl_Ptr_List_Item *)malloc(capacity_ * sizeof(Fl_Ptr_List_Item));
    }
    else if(newsize>0 && newsize<size_ && newsize<capacity_-blocksize_) {

        // Delete items, if needed. (see Fl_String_List)
        if(auto_delete_) for (uint i = newsize+1; i < size_; i++) free(items[i]);

        // Shrink list capacity
        capacity_= (newsize/blocksize_+1)*blocksize_;
        if(items) items = (Fl_Ptr_List_Item *)realloc(items, capacity_ * sizeof(Fl_Ptr_List_Item));
    }

    size_ = newsize;
}

void Fl_Ptr_List::append(Fl_Ptr_List_Item item)
{
    resize(size_+1);
    items[size_-1] = item;
}

void Fl_Ptr_List::prepend(Fl_Ptr_List_Item item)
{
    insert(0, item);
}

void Fl_Ptr_List::insert(uint pos, Fl_Ptr_List_Item item)
{
    resize(size_+1);

    int mvSize = (size_-1-pos);
    if(mvSize > 0)
        memmove(items+pos+1, items+pos, mvSize*sizeof(Fl_Ptr_List_Item));
    items[pos] = item;
}

void Fl_Ptr_List::replace(uint pos, Fl_Ptr_List_Item item)
{
    if(auto_delete_) free(items[pos]);
    items[pos] = item;
}

void Fl_Ptr_List::remove(uint pos)
{
    if(auto_delete_) free(items[pos]);

    int mvSize = size_-pos-1;
    if(mvSize > 0) {
        memmove(items+pos, items+(pos+1), mvSize*sizeof(Fl_Ptr_List_Item));
    }
    resize(size_-1);
}

bool Fl_Ptr_List::remove(void *p)
{
    for (uint pos = 0; pos < size_; pos++) {
        if (items[pos] == p) {
            remove(pos);
            return true;
        }
    }
    return false;
}

void Fl_Ptr_List::sort(int (*sort_function)(const void *, const void *))
{
    if(size_>0) {
        qsort(items, size_, sizeof(Fl_Ptr_List_Item), sort_function);
    }
}

int Fl_Ptr_List::index_of(const Fl_Ptr_List_Item p) const
{
    for (uint pos = 0; pos < size_; pos++) {
        if (items[pos] == p)
            return pos;
    }
    return -1;
}

Fl_Ptr_List_Item Fl_Ptr_List::item(uint index) const
{
    if(index>=size_) return 0;
    return items[index];
}

////////////////////////////////////
// FL_STRING_LIST IMPLEMENTATION: //
////////////////////////////////////

#include <efltk/Fl_String_List.h>

int fl_string_sort_func(const void *s1, const void *s2) {
    return strcmp((*(Fl_String**)s1)->c_str(), (*(Fl_String**)s2)->c_str());
}

void Fl_String_List::sort() {
    Fl_Ptr_List::sort(fl_string_sort_func);
}

void Fl_String_List::append(Fl_String item) {
    Fl_Ptr_List::append((void *)new Fl_String(item));
}

void Fl_String_List::prepend(Fl_String item) {
    Fl_Ptr_List::prepend((void *)new Fl_String(item));
}

void Fl_String_List::insert(uint pos, Fl_String &item) {
    Fl_Ptr_List::insert(pos, (void *)new Fl_String(item));
}

void Fl_String_List::insert(uint pos, const Fl_String_List &list) {
    uint n=list.size();
    while(n--) insert(pos, list[n]);
}

//Returns number of removed items
int Fl_String_List::remove(Fl_String i) {
    int removed=0;
    uint n=size();
    while(n--) 
        if(*item(n)==i) {
            removed++;
            Fl_Ptr_List::remove(n);
        }
    return removed>0?removed:-1;
}

//Return first index of found string. -1 if none
int Fl_String_List::index_of(const Fl_String str) {
    for(uint n=0; n<size(); n++)
        if(*item(n)==str) return n;
    return -1;
}

int Fl_String_List::contains(const Fl_String str) {
    int ret=0;
    for(uint n=0; n<size(); n++)
        if(*item(n)==str) ret++;
    return ret;
}

/*
Fl_String Fl_String_List::to_string(const char *separator)
{
    char *ret=0;
    if(!size()) return ret;
    int str_len=0;
    int num_len=0;
    char num[36];
    snprintf(num, sizeof(num)-1, "%d", item(0));
    ret = strdup(num);
    str_len = strlen(num);
    for(uint n = 1; n < size(); n++) {
        snprintf(num, sizeof(num)-1, "%s%d", separator, item(n));
        num_len = strlen(num);
        str_len += num_len;
        ret = (char*)realloc(ret, sizeof(char)*str_len);
        strncpy(ret+(str_len-num_len), num, num_len);
    }
    ret[str_len]='\0';
    return ret;
}

void Fl_Int_List::from_string(const char *s, const char *separator)
{
    if(!s) return;

    clear();
    char *buf = strdup(s);
    char *p = strtok(buf, separator);
    while (p) {
        append(atoi(p));
        p = strtok(NULL, separator);
    }
    free(buf);
}
*/

/////////////////////////////////////
// FL_CSTRING_LIST IMPLEMENTATION: //
/////////////////////////////////////

int char_sort_func(const void *s1, const void *s2) {
    return strcmp(*(const char**)s1, *(const char**)s2);
}

void Fl_CString_List::sort() {
    Fl_Ptr_List::sort(char_sort_func);
}

/////////////////////////////////
// FL_INT_LIST IMPLEMENTATION: //
/////////////////////////////////

#include <efltk/Fl_Int_List.h>

int int_sort_func(const void *s1, const void *s2) {
    return ( *(int*)s1 - *(int*)s2 );
}

void Fl_Int_List::sort() {
    Fl_Ptr_List::sort(int_sort_func);
}

//Return first index of found int. -1 if none
int Fl_Int_List::index_of(const int i) {
    for(uint n=0; n<size(); n++)
        if(item(n)==i) return n;
    return -1;
}

int Fl_Int_List::contains(const int i) {
    int ret=0;
    for(uint n=0; n<size(); n++)
        if(item(n)==i) ret++;
    return ret;
}

char *Fl_Int_List::to_string(const char *separator)
{
    char *ret=0;
    if(!size()) return ret;
    int str_len=0;
    int num_len=0;
    char num[36];
    snprintf(num, sizeof(num)-1, "%d", item(0));
    ret = strdup(num);
    str_len = strlen(num);
    for(uint n = 1; n < size(); n++) {
        snprintf(num, sizeof(num)-1, "%s%d", separator, item(n));
        num_len = strlen(num);
        str_len += num_len;
        ret = (char*)realloc(ret, sizeof(char)*str_len);
        strncpy(ret+(str_len-num_len), num, num_len);
    }
    ret[str_len]='\0';
    return ret;
}

void Fl_Int_List::from_string(const char *s, const char *separator)
{
    if(!s) return;

    clear();
    char *buf = strdup(s);
    char *p = strtok(buf, separator);
    while (p) {
        append(atoi(p));
        p = strtok(NULL, separator);
    }
    free(buf);
}
