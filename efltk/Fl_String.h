#ifndef _Fl_STRING_H__
#define _Fl_STRING_H__

#include "Enumerations.h"
#include <string.h>
#include <stdlib.h>

class Fl_String;

extern FL_API bool operator <  (const Fl_String &s1, const Fl_String &s2);
extern FL_API bool operator <  (const Fl_String &s1, const Fl_String &s2);
extern FL_API bool operator <= (const Fl_String &s1, const Fl_String &s2);
extern FL_API bool operator >  (const Fl_String &s1, const Fl_String &s2);
extern FL_API bool operator >= (const Fl_String &s1, const Fl_String &s2);
extern FL_API bool operator == (const Fl_String &s1, const Fl_String &s2);
extern FL_API bool operator != (const Fl_String &s1, const Fl_String &s2);

extern FL_API bool operator <  (const Fl_String &s1, const char *s2);
extern FL_API bool operator <= (const Fl_String &s1, const char *s2);
extern FL_API bool operator >  (const Fl_String &s1, const char *s2);
extern FL_API bool operator >= (const Fl_String &s1, const char *s2);
extern FL_API bool operator == (const Fl_String &s1, const char *s2);
extern FL_API bool operator != (const Fl_String &s1, const char *s2);

class FL_API Fl_String {
    friend FL_API Fl_String operator +(const char*, const Fl_String& rhs);
protected:
    char *str_;
    ulong len_;
    void assign(const char *str);

public:
    // constructors & destructors
    Fl_String(char c,int repeater = 1);
    Fl_String(int number);
    Fl_String(unsigned number);
    Fl_String(const char *s="", int maxlen=0, bool pre_allocated=false);
    Fl_String(const Fl_String &s);
    ~Fl_String();

    // assignments
    Fl_String& operator = (const char *s);
    Fl_String& operator = (const Fl_String& s);

    // comparisions
    friend FL_API bool operator <  (const Fl_String &s1, const Fl_String &s2);
    friend FL_API bool operator <= (const Fl_String &s1, const Fl_String &s2);
    friend FL_API bool operator >  (const Fl_String &s1, const Fl_String &s2);
    friend FL_API bool operator >= (const Fl_String &s1, const Fl_String &s2);
    friend FL_API bool operator == (const Fl_String &s1, const Fl_String &s2);
    friend FL_API bool operator != (const Fl_String &s1, const Fl_String &s2);

    bool cmp(Fl_String &s);
    bool casecmp(Fl_String &s);

    // comparisions with regular strings
    friend FL_API bool operator <  (const Fl_String &s1, const char *s2);
    friend FL_API bool operator <= (const Fl_String &s1, const char *s2);
    friend FL_API bool operator >  (const Fl_String &s1, const char *s2);
    friend FL_API bool operator >= (const Fl_String &s1, const char *s2);
    friend FL_API bool operator == (const Fl_String &s1, const char *s2);
    friend FL_API bool operator != (const Fl_String &s1, const char *s2);

    // operations
    Fl_String  operator +  (const char * s) const;
    Fl_String  operator +  (const Fl_String& s) const;
    Fl_String  operator +  (const char s) const;
    Fl_String& operator += (const char * s);
    Fl_String& operator += (const Fl_String& s);
    Fl_String& operator += (const char s);

    // usefull methods
    Fl_String &append(const char *str, int len);

    void clear();
    Fl_String trimRight() const;
    Fl_String trimLeft()  const;
    Fl_String trim()      const;
    Fl_String remove(const char *pattern) const;
    Fl_String replace(const char *pattern,const char *replacement) const;
    Fl_String lower_case() const;
    Fl_String upper_case() const;
    Fl_String sub_str(int start, int count) const;
    void sub_delete(int start, int count=1);
    void sub_delete(const char *s) { sub_replace(s, 0); }
    void sub_insert(int start, const char *str);
    void sub_insert(int start, char ch);
    void sub_replace(const char *s_str, const char *r_str);
    Fl_String word_at(long position) const;
    int length() const;
    int pos(const char *substr, int index=0) const;
    int pos(int c, int index=0) const;
    int rpos(int c, int index=0) const;
    int to_int(int defvalue=0) const;
    float to_float(float defvalue=0) const;
    double to_double(double defvalue=0) const;
    bool empty() const;
    void set_length(int newLength);

    const char *c_str() const { return str_; }

	// Returns reference to this
    Fl_String &printf(const char *str, ...);

    // auto conversion to char* when needed
    operator const char *() { return str_; }
    operator char *() { return str_; }

    // element access
    char& operator [] (const int i) { return str_[i]; }
    char  operator [] (const int i) const { return str_[i]; }

    static Fl_String IntToString(int val);
};

#endif
