/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Alexey Parshin
 * Email  : alexey@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _Fl_STRING_H_
#define _Fl_STRING_H_

#include "Enumerations.h"
#include <string.h>

class FL_API Fl_String {
    friend FL_API Fl_String operator +(const char*, const Fl_String& rhs);
public:
    static Fl_String null_object;

    // constructors & destructors
    Fl_String(char c,int repeater = 1);
    Fl_String(int number);
    Fl_String(unsigned number);
    Fl_String(const char *s="", int maxlen=0, bool pre_allocated=false);
    Fl_String(const Fl_String &s);
    ~Fl_String();

    void clear();

    // assignments
    Fl_String& operator = (const char *s);
    Fl_String& operator = (const Fl_String& s);

    // operations
    Fl_String  operator +  (const char * s) const;
    Fl_String  operator +  (const Fl_String& s) const;
    Fl_String  operator +  (const char s) const;
    Fl_String& operator += (const char * s);
    Fl_String& operator += (const Fl_String& s);
    Fl_String& operator += (const char s);

    // usefull methods
    Fl_String &append(const char *str, int len);
    Fl_String &prepend(const char *str, int len);

    bool cmp(Fl_String &s);
    bool casecmp(Fl_String &s);

    Fl_String trim_right() const;
    Fl_String trim_left()  const;
    Fl_String trim()       const;
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

    int length() const;
    int pos(const char *substr, int index=0) const;
    int pos(int c, int index=0) const;
    int rpos(int c, int index=0) const;

    int    to_int(int defvalue=0) const;
    float  to_float(float defvalue=0) const;
    double to_double(double defvalue=0) const;

    bool empty() const;
    void set_length(int new_len);

    const char *c_str() const { return str_; }

    // Returns reference to this
    Fl_String &printf(const char *str, ...);

    // auto conversion to char* when needed
    operator const char *() const { return str_; }
    operator char *() const { return str_; }

    // element access
    char& operator [] (const int i) { return str_[i]; }
    char operator [] (const int i) const { return str_[i]; }

    static Fl_String IntToString(int val);

    static Fl_String from_codeset(int conv_index, const char *str, int str_len);
    static Fl_String from_codeset(Fl_String codeset, const char *str, int str_len);

protected:
    void assign(const char *str);

    char *str_;
    unsigned len_;
};

static inline bool operator <  (const Fl_String &s1, const Fl_String &s2) { return (strcmp(s1.c_str(),s2.c_str())<0);  }
static inline bool operator <= (const Fl_String &s1, const Fl_String &s2) { return (strcmp(s1.c_str(),s2.c_str())<=0); }
static inline bool operator >  (const Fl_String &s1, const Fl_String &s2) { return (strcmp(s1.c_str(),s2.c_str())>0);  }
static inline bool operator >= (const Fl_String &s1, const Fl_String &s2) { return (strcmp(s1.c_str(),s2.c_str())>=0); }
static inline bool operator == (const Fl_String &s1, const Fl_String &s2) { if(&s1==&s2) return true; return (strcmp(s1.c_str(),s2.c_str())==0); }
static inline bool operator != (const Fl_String &s1, const Fl_String &s2) { return (strcmp(s1.c_str(),s2.c_str())!=0); }

static inline bool operator <  (const Fl_String &s1, const char *s2) { return (strcmp(s1.c_str(),s2)<0);  }
static inline bool operator <= (const Fl_String &s1, const char *s2) { return (strcmp(s1.c_str(),s2)<=0); }
static inline bool operator >  (const Fl_String &s1, const char *s2) { return (strcmp(s1.c_str(),s2)>0);  }
static inline bool operator >= (const Fl_String &s1, const char *s2) { return (strcmp(s1.c_str(),s2)>=0); }
static inline bool operator == (const Fl_String &s1, const char *s2) { return (strcmp(s1.c_str(),s2)==0); }
static inline bool operator != (const Fl_String &s1, const char *s2) { return (strcmp(s1.c_str(),s2)!=0); }

static inline bool operator <  (const char *s1, const Fl_String &s2) { return (strcmp(s1,s2.c_str())<0);  }
static inline bool operator <= (const char *s1, const Fl_String &s2) { return (strcmp(s1,s2.c_str())<=0); }
static inline bool operator >  (const char *s1, const Fl_String &s2) { return (strcmp(s1,s2.c_str())>0);  }
static inline bool operator >= (const char *s1, const Fl_String &s2) { return (strcmp(s1,s2.c_str())>=0); }
static inline bool operator == (const char *s1, const Fl_String &s2) { return (strcmp(s1,s2.c_str())==0); }
static inline bool operator != (const char *s1, const Fl_String &s2) { return (strcmp(s1,s2.c_str())!=0); }

extern FL_API Fl_String operator +(const char*, const Fl_String& rhs);

#endif
