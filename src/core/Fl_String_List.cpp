////////////////////////////////////
// FL_STRING_LIST IMPLEMENTATION: //
////////////////////////////////////

#include <efltk/Fl_String_List.h>

#include <stdlib.h>

Fl_String_List::Fl_String_List()
{
    blocksize_ = capacity_ = size_ = 0;
    items=0;
}

Fl_String_List::Fl_String_List(const Fl_String_List& sl)
{
    blocksize_ = capacity_ = size_ = 0;
    items=0;
    append(sl);
}

Fl_String_List::Fl_String_List(const char *str, const char *separator)
{
    blocksize_ = capacity_ = size_ = 0;
    items=0;
    from_string(str, separator);
}

void Fl_String_List::clear()
{
    if(items) {
        free((Fl_String *)items);
        items=0;
    }
    capacity_ = size_ = 0;
}

void Fl_String_List::resize(unsigned newsize)
{
    unsigned newcap;
    if(blocksize_<=0) newcap = (newsize * 9 / 64 + 1) * 8;
    else              newcap = (newsize/blocksize_+1)*blocksize_;

    if(newcap!=capacity_) {
        capacity_ = newcap;
        int memblk = capacity_ * sizeof(Fl_String);
        // Realloc list capacity
        if(items) {
            items = (Fl_String *)realloc(items, memblk);
            memset(items+size_, 0, memblk-(size_*sizeof(Fl_String)));
        } else {
            items = (Fl_String *)malloc(memblk);
            memset(items, 0, memblk);
        }
    }
    size_ = newsize;
}

int fl_string_sort_func(const void *s1, const void *s2) {
    return strcmp((*(Fl_String**)s1)->c_str(), (*(Fl_String**)s2)->c_str());
}

void Fl_String_List::sort() {
    //sort(fl_string_sort_func);
    if(size_>0) {
        qsort(items, size_, sizeof(Fl_String), fl_string_sort_func);
    }
}

void Fl_String_List::append(const Fl_String_List& alist) {
    unsigned cnt = alist.count();
    for (unsigned i = 0; i < cnt; i++) {
        append(alist[i]);
    }
}

void Fl_String_List::append(const char *item)
{
    if(size_ == capacity_) {
        resize(size_ + 1);
        items[size_ - 1] = item;
    } else {
        items[size_++] = item;
    }
}

void Fl_String_List::append(const Fl_String &item)
{
    if(size_ == capacity_) {
        resize(size_ + 1);
        items[size_ - 1] = item;
    } else {
        items[size_++] = item;
    }
}

void Fl_String_List::insert(unsigned pos, const Fl_String &item)
{
    if(size_ == capacity_) resize(size_ + 1);
    else                   size_++;
    int mvSize = (size_-1-pos);
    if(mvSize > 0)
        memmove(items+pos+1, items+pos, mvSize*sizeof(Fl_String));
    items[pos] = item;
}

void Fl_String_List::insert(unsigned pos, const Fl_String_List &list)
{
    unsigned n=list.size();
    while(n--) insert(pos, list[n]);
}

void Fl_String_List::remove(unsigned pos)
{
    int mvSize = size_-pos-1;
    if(mvSize > 0) {
        memmove(items+pos, items+(pos+1), mvSize*sizeof(Fl_String));
    }
    resize(size_-1);
}

//Returns number of removed items
int Fl_String_List::remove(Fl_String i)
{
    int removed=0;
    unsigned n=size();
    while(n--) {
        if(items[n]==i) {
            removed++;
            remove(n);
        }
    }
    return removed>0?removed:-1;
}

//Return first index of found string. -1 if none
int Fl_String_List::index_of(const Fl_String &str) const
{
    /*
    // Do binary search
    int bottom=0, top=size()-1, mid;
    int L = ( top + bottom ) / 2 ;
    if(items[L] == str) return L;

    while(bottom <= top) {
        mid = top + bottom / 2 ;
        int d = strcmp(str, items[mid]);
        if(!d)
            return mid;
        else if(d>0)
            bottom = mid + 1;
        else
            top = mid-1;
    }
     */
    const char *s = str.c_str();
    unsigned cnt = size();
    for (unsigned i = 0; i < cnt; i++) {
        if (strcmp(s, items[i]) == 0)
            return (int)i;
    }

    return -1;
}

int Fl_String_List::index_of(const char *str) const
{
    Fl_String search(str);
    return index_of(search);
}

char *Fl_String_List::to_cstring(const char *separator) const
{
    char *ret=0;
    if(!size()) return ret;
    int ret_len=0;
    int str_len=0;
    int sep_len=strlen(separator);
    ret = new char[1];

    for(unsigned n = 0; n < size(); n++) {
        str_len = item(n).length();
        int len;
        if(n<size()-1) len = str_len+sep_len;
        else len = str_len;
        ret_len += len;
        ret = (char*)realloc(ret, sizeof(char)*ret_len);

        memcpy(ret+(ret_len-len), item(n).c_str(), str_len);
        if(n<size()-1)
            memcpy(ret+(ret_len-sep_len), separator, sep_len);
    }
    ret[ret_len]='\0';
    return ret;
}

Fl_String Fl_String_List::to_string(const char *separator) const
{
    Fl_String ret;
    if(!size()) return ret;

    for(unsigned n = 0; n < size(); n++) {
        ret += item(n).c_str();
        if(n<size()-1)
            ret += separator;
    }
    return ret;
}

void Fl_String_List::from_string(const char *str, const char *separator)
{
    if(!str) return;

    clear();

    const char *ptr = str;
    const char *s = strstr(ptr, separator);
    if(s) {
        unsigned separator_len = strlen(separator);
        do {
            unsigned len = s - ptr;
            if (len) {
                Fl_String string(ptr, len);
                append(string);
            } else {
                append("");
            }

            ptr = s + separator_len;
            s = strstr(ptr, separator);
        }
        while(s);

        if(*ptr) {
            append(ptr);
        }
    } else {
        append(ptr);
    }
}

void Fl_String_List::print(FILE *fp) const
{
    unsigned cnt = count();
    for (unsigned i = 0; i < cnt; i++)
        fprintf(fp,"%s\n", item(i).c_str());
}

/////////////////////////////////////
// FL_CSTRING_LIST IMPLEMENTATION: //
/////////////////////////////////////

int char_sort_func(const void *s1, const void *s2) {
    return strcmp(*(const char**)s1, *(const char**)s2);
}

void Fl_CString_List::sort() {
    Fl_Ptr_List::sort(char_sort_func);
}

void Fl_CString_List::print(FILE *fp) const
{
    unsigned cnt = count();
    for (unsigned i = 0; i < cnt; i++)
        fputs(item(i),fp);
}

/////////////////////////////////////
// FL_STRING_STACK IMPLEMENTATION: //
/////////////////////////////////////

#include <efltk/Fl_String_Stack.h>

void Fl_String_Stack::push(Fl_String data)
{
    items.append(data);
    check_size();
}

Fl_String Fl_String_Stack::pop()
{
    if(empty()) return 0;
    unsigned pos = items.size()-1;
    Fl_String ret = items[pos];
    items.remove(pos);
    return ret;
}

void Fl_String_Stack::clear() {
    items.clear();
}

Fl_String Fl_String_Stack::peek()
{
    if(empty()) return 0;
    return items[items.size()-1];
}

void Fl_String_Stack::check_size()
{
    if(max_size_>0 && items.size() > max_size_) {
        items.remove(0);
        items.resize(max_size_);
    }
}
