/***************************************************************************
                          Fl_String.cpp  -  description
                             -------------------
    begin                : Tue Dec 14 1999
    copyright            : (C) 1999 by Alexey Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <config.h>

#include <efltk/math.h>
#include <config.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

#include <efltk/vsnprintf.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_Util.h>

#ifdef _WIN32_WCE
#include <wince.h>
#endif

//------------------------------------------------------------------------------
// constructors & destructors
//------------------------------------------------------------------------------

Fl_String::Fl_String(const char *s, int maxlen, bool pre_allocated)
{
    if(maxlen>0) {
        if(pre_allocated) str_ = (char*)s;
        else {
            str_ = (char*)malloc(maxlen + 1);
            strncpy(str_, s, maxlen);
            str_[maxlen] = '\0';
        }
        len_ = maxlen;
    } else {
        if(pre_allocated) str_ = (char*)s;
        else str_ = strdup(s);
        len_ = strlen(str_);
    }
}

Fl_String::Fl_String(char c, int repeater)
{
    if (repeater == 1) {
        str_ = (char*)malloc(2);
        str_[0] = c;
    } else {
        str_ = (char*)malloc(repeater + 1);
        memset(str_, c, repeater);
    }
    str_[repeater] = '\0';
    len_ = strlen(str_);
}

Fl_String::Fl_String(int number)
{
    str_ = (char*)malloc(33);
    snprintf(str_, 32, "%i", number);
    len_ = strlen(str_);
}

Fl_String::Fl_String(unsigned number)
{
    str_ = (char*)malloc(33);
    snprintf(str_, 32, "%i", number);
    len_ = strlen(str_);
}

Fl_String::Fl_String(const Fl_String &s)
{
    str_ = strdup(s.str_);
    len_ = s.len_;
}

Fl_String::~Fl_String()
{
    free((char*)str_);
}

//------------------------------------------------------------------------------
// assignments
//------------------------------------------------------------------------------
void Fl_String::assign(const char *s)
{
    if(s) {
        len_ = strlen(s);
        str_ = (char*)realloc(str_, (len_+1)*sizeof(char));
        strncpy(str_, s, len_);
        str_[len_] = '\0';
    } else {
        free((char*)str_);
        str_ = (char*)malloc(1);
        str_[0] = '\0';
        len_ = 0;
    }
}

Fl_String& Fl_String::operator = (const char *s)
{
    assign(s);
    return *this;
}

Fl_String& Fl_String::operator = (const Fl_String& s)
{
    assign(s.str_);
    return *this;
}

//------------------------------------------------------------------------------
// comparisions
//------------------------------------------------------------------------------
bool operator <  (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str_,s2.str_) < 0;
}

bool operator <= (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str_,s2.str_) <= 0;
}

bool operator >  (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str_,s2.str_) > 0;
}

bool operator >= (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str_,s2.str_) >= 0;
}

bool operator == (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str_,s2.str_) == 0;
}

bool operator != (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str_,s2.str_) != 0;
}

bool Fl_String::cmp(Fl_String &s) {
    return strcmp(str_, s.str_) != 0;
}

bool Fl_String::casecmp(Fl_String &s) {
    return strcasecmp(str_, s.str_) != 0;
}

//------------------------------------------------------------------------------
// operations
//------------------------------------------------------------------------------
Fl_String Fl_String::operator + (const char * s) const
{
    char *temp;
    int len = 0;
    if(s) len = length() + strlen(s) + 1;
    else len = length() + 1;

    temp = (char*)malloc(len);
    strcpy(temp, str_);
    if(s) strcat(temp, s);

    Fl_String s1(temp, len, true);
    return s1;
}

Fl_String Fl_String::operator + (const Fl_String& s) const
{
    int len = length() + s.length() + 1;
    char *temp = (char*)malloc(len);
    strcpy(temp, str_);
    if(s.length()) strcat(temp, s.c_str());

    Fl_String s1(temp, len, true);
    return s1;
}

Fl_String& Fl_String::operator += (const char * s)
{
    if(s) {
        len_ += strlen(s);
        str_ = (char *)realloc(str_, len_ + 1);
        strcat(str_, s);
    }
    return *this;
}

Fl_String& Fl_String::operator += (const Fl_String& s)
{
    len_ += s.length();
    str_ = (char *) realloc(str_, len_ + 1);
    if(s.length()) strcat(str_, s.str_);
    return *this;
}
//------------------------------------------------------------------------------
// usefull methods
//------------------------------------------------------------------------------
void Fl_String::clear()
{
    str_ = (char *) realloc(str_, sizeof(char));
    str_[0] = '\0';
}

Fl_String Fl_String::trimRight() const
{
    Fl_String ret(str_);
    char *s = ret.str_;
    s = fl_trimright(s);
    return ret;
}

Fl_String Fl_String::trimLeft() const
{
    char *s = str_;
    s = fl_trimleft(s);
    return s;
}

Fl_String Fl_String::lower_case() const
{
    Fl_String  s = str_;
    fl_tolower(s.str_);
    return s;
}

Fl_String Fl_String::upper_case() const
{
    Fl_String  s = str_;
    fl_toupper(s.str_);
    return s;
}

extern int fl_va_len(char *format, va_list ap); //Fl_Util.cpp
void Fl_String::printf(const char *string, ...)
{
    char *s;
    int valen = 0;

    if(!string || !strcmp(string, ""))
        return;

    va_list ap;
    va_start(ap, string);
    valen = fl_va_len((char *)string, ap);
    va_end(ap);

    s = (char*)malloc(valen);
    va_start(ap, string);
    vsnprintf(s, valen, string, ap);
    va_end(ap);
    s[valen] = '\0';

    free((char*)str_);
    str_ = s;
    len_ = strlen(str_);
}

Fl_String Fl_String::remove(const char *pattern) const
{
    if(!pattern) return str_;
    Fl_String result;
    int patternLength = strlen(pattern);
    if (!patternLength) return str_;
    char *temp = strdup(str_);
    char *head = temp;
    char *tail = strstr(head, pattern);
    while (tail) {
        *tail = 0;
        result += head;
        head = tail + patternLength;
        tail = strstr(head,pattern);
    }
    result += head;
    free(temp);
    return result;
}

Fl_String Fl_String::replace(const char *pattern,const char *replacement) const
{
    if(pattern) return str_;
    Fl_String result;
    int patternLength = strlen(pattern);
    if (!patternLength) return str_;
    char *temp = strdup(str_);
    char *head = temp;
    char *tail = strstr(head,pattern);
    while (tail) {
        *tail = 0;
        result += head;
        result += replacement?replacement:"";
        head = tail + patternLength;
        tail = strstr(head,pattern);
    }
    result += head;
    free(temp);
    return result;
}

Fl_String Fl_String::trim() const
{
    Fl_String s = trimRight();
    return s.trimLeft();
}

int Fl_String::length() const {
    if(len_<=0) ((Fl_String*)this)->len_ = strlen(str_);
    return len_;
}

bool Fl_String::empty() const {
    return (len_==0);
}

int Fl_String::pos(const char *substr, int index) const
{
    char *ptr = (str_+index);
    char *p = strstr( ptr, substr );
    if(!p) return -1;
    return int(p - str_);
}

int Fl_String::pos(int c, int index) const
{
    char *ptr = (str_+index);
    char *p = strchr( ptr, c );
    if (!p) return -1;
    return int(p - str_);
}

int Fl_String::rpos(int c, int index) const
{
    char *ptr = (str_+index);
    char *p = strrchr( ptr, c );
    if (!p) return -1;
    return int(p - str_);
}

Fl_String Fl_String::sub_str(int start,int count) const
{
    return Fl_String(str_+start, count);
}

int Fl_String::to_int(int defvalue) const
{
    Fl_String t = trim();
    if (!t.length()) return defvalue;
    int value = atoi(t.c_str());
    if(value == 0 && t != "0")
        return defvalue;
    return value;
}

float Fl_String::to_float(float defvalue) const
{
    Fl_String t = trim();
    if (!t.length()) return defvalue;
    float value = (float)atof(t.c_str());
    if (errno == ERANGE) return defvalue;
    return value;
}

double Fl_String::to_double(double defvalue) const
{
    Fl_String t = trim();
    if (!t.length()) return defvalue;
    double value = atof(t.c_str());
    if (errno == ERANGE) return defvalue;
    return value;
}

void Fl_String::sub_insert(int start,const char *insStr)
{
    int l = length();
    if (l < start) start = l;
    Fl_String ending(str_ + start);
    str_[start] = 0;
    *this += insStr + ending;
}

void Fl_String::sub_insert(int start,char ch)
{
    char st[2] = { ch, '\0' };
    sub_insert(start, st);
}

void Fl_String::sub_delete(int start, int count)
{
    if(count) {
        int l = len_+1;
        if(count > l) count = l;
        memmove(str_+start, str_+start+count, l-count);
    }
}

void Fl_String::sub_replace(const char *s_str,const char *r_str)
{
    Fl_String  s;
    int   l = strlen(s_str);
    char *ptext = str_;
    char *pstart = strstr(str_,s_str);
    while (pstart) {
        *pstart = 0;
        s += ptext;
        if (r_str)
            s += r_str;
        ptext = pstart + l;
        pstart = strstr(ptext,s_str);
    }
    s += ptext;
    assign(s.str_);
}

void Fl_String::set_length(int newLength)
{
    str_ = (char *)realloc(str_, newLength+1);
    str_[newLength] = 0;
    len_ = newLength+1;
}

Fl_String Fl_String::word_at(long position) const
{
    char *temp;

    // rewind to start of current word
    while(!isspace(str_[position-1]) && !ispunct(str_[position-1]))
        if(position) position--;
        else break;

    // skip leading punctuation
    int len = length();
    while(ispunct(str_[position]))
        if(position < len) position++;
        else break;

    char word[4096];
    temp = word;
    int l=0;
    while(str_[position] && !(isspace(str_[position])))
    {
        if(ispunct(str_[position]))
            if(str_[position] != '\'')
                break;
        *temp++ = str_[position++];
        l++;
    }
    *temp = '\0';
    return Fl_String(word, l);
}

//------------------------------------------------------------------------------
Fl_String Fl_String::IntToString(int val)
{
    Fl_String s("", 33);
    snprintf((char*)s.c_str(), 32, "%i", val);
    return s;
}
//------------------------------------------------------------------------------
Fl_String operator +(const char*s, const Fl_String& rhs)
{
    return Fl_String(s) + rhs;
}

//------------------------------------------------------------------------------
bool operator <  (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str_,s2) < 0;
}

bool operator <= (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str_,s2) <= 0;
}

bool operator >  (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str_,s2) > 0;
}

bool operator >= (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str_,s2) >= 0;
}

bool operator == (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str_,s2) == 0;
}

bool operator != (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str_,s2) != 0;
}
//------------------------------------------------------------------------------

