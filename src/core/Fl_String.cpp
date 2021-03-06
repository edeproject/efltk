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

#include <efltk/fl_math.h>
#include <config.h>

#include <efltk/fl_utf8.h>
#include <efltk/vsnprintf.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_Util.h>

#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#ifdef _WIN32_WCE
#include <wince.h>
#endif

Fl_String operator +(const char*s, const Fl_String& rhs) {
    return Fl_String(s) + rhs;
}

//------------------------------------------------------------------------------
// constructors & destructors
//------------------------------------------------------------------------------

Fl_String Fl_String::null_object;

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
        if(!s) s="";
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
    len_ = repeater;
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
void Fl_String::assign(const char *s, int len)
{
    if(s && len>0) {
        len_ = len;
        str_ = (char*)realloc(str_, (len_+1)*sizeof(char));
        memcpy(str_, s, len_);
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
    if(str_==s) return *this;
    assign(s, s?strlen(s):0);
    return *this;
}

Fl_String& Fl_String::operator = (const Fl_String& s)
{
    if(this==&s) return *this;
    assign(s.str_, s.len_);
    return *this;
}

//------------------------------------------------------------------------------
// comparisions
//------------------------------------------------------------------------------

bool Fl_String::cmp(Fl_String &s) const {
    return strcmp(str_, s.str_) != 0;
}

bool Fl_String::casecmp(Fl_String &s) const {
    return fl_utf_strcasecmp(str_, s.str_) != 0;
}

//------------------------------------------------------------------------------
// operations
//------------------------------------------------------------------------------
Fl_String Fl_String::operator + (const char * s) const
{
    char *temp;
    int len = length();
    int slen = 0;
    if(s) { slen=strlen(s); len += slen; }

    temp = (char*)malloc(len+1);
    strncpy(temp, str_, length());
    if(s) strncpy(temp+length(), s, slen);

    temp[len] = '\0';

    Fl_String s1(temp, len, true);
    return s1;
}

Fl_String Fl_String::operator + (const char s) const
{
    int len = length()+1;
    char *temp = (char*)malloc(len+1);
    strncpy(temp, str_, length());

    temp[len-1] = s;
    temp[len] = '\0';

    Fl_String s1(temp, len, true);
    return s1;
}

Fl_String Fl_String::operator + (const Fl_String& s) const
{
    int len = length() + s.length();
    char *temp = (char*)malloc(len+1);
    strncpy(temp, str_, length());
    if(s.length()) strncpy(temp+length(), s.c_str(), s.length());

    temp[len] = '\0';

    Fl_String s1(temp, len, true);
    return s1;
}

Fl_String& Fl_String::operator += (const char * s)
{
    if(s) {
        int oldlen = len_;
        int slen = strlen(s);
        len_ += slen;
        str_ = (char *)realloc(str_, len_+1);
        strncpy(str_+oldlen, s, slen);
        str_[len_] = '\0';
    }
    return *this;
}

Fl_String& Fl_String::operator += (const char s)
{
    len_ += 1;
    str_ = (char *)realloc(str_, len_+1);
    str_[len_-1] = s;
    str_[len_] = '\0';
    return *this;
}

Fl_String& Fl_String::operator += (const Fl_String& s)
{
    int oldlen = len_;
    len_ += s.length();
    str_ = (char *) realloc(str_, len_+1);
    if(s.length()) strncpy(str_+oldlen, s.str_, s.length());
    str_[len_] = '\0';

    return *this;
}

Fl_String &Fl_String::append(const char *str, int len)
{
    int oldlen = len_;
    len_ += len;
    str_ = (char *)realloc(str_, len_+1);
    memcpy(str_+oldlen, str, len);
    str_[len_] = '\0';
    return *this;
}

Fl_String &Fl_String::prepend(const char *str, int len)
{
    int oldlen = len_;
    len_ += len;
    str_ = (char *)realloc(str_, len_+1);
    memmove(str_+len, str_, oldlen);
    memcpy(str_, str, len);
    str_[len_] = '\0';
    return *this;
}

//------------------------------------------------------------------------------
// usefull methods
//------------------------------------------------------------------------------
void Fl_String::clear()
{
    free((char*)str_);
    str_ = (char*)malloc(1);
    str_[0] = '\0';
    len_ = 0;
}

Fl_String Fl_String::trim_right() const
{
    Fl_String ret(str_);
    char *s = ret.str_;
    s = fl_trimright(s);
    return ret;
}

Fl_String Fl_String::trim_left() const
{
    char *s = str_;
    s = fl_trimleft(s);
    return s;
}

Fl_String Fl_String::lower_case() const
{
    char *temp = (char*)malloc(length()*3);
    int len = fl_utf_tolower((const uchar*)str_, length(), temp);
    temp[len] = '\0';
    return Fl_String(temp, len, true);
}

Fl_String Fl_String::upper_case() const
{
    char *temp = (char*)malloc(length()*3);
    int len = fl_utf_toupper((const uchar*)str_, length(), temp);
    temp[len] = '\0';
    return Fl_String(temp, len, true);
}

extern int fl_va_len(char *format, va_list ap); //Fl_Util.cpp
Fl_String &Fl_String::printf(const char *string, ...)
{
    char *s;
    int valen = 0;

    if(!string || !*string)
        return *this;

    va_list ap;
    va_start(ap, string);
    valen = fl_va_len((char *)string, ap);
    va_end(ap);

    s = (char*)malloc(valen+1);
    va_start(ap, string);
    vsnprintf(s, valen, string, ap);
    va_end(ap);
    s[valen] = '\0';

    free((char*)str_);
    str_ = s;
    len_ = strlen(str_);
    return *this;
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
    Fl_String s = trim_right();
    return s.trim_left();
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
    if (start >= (int)len_)
        return Fl_String("");
    if (count > (int)len_ - start)
        count = len_ - start;
    return Fl_String(str_+start, count);
}

int Fl_String::to_int(int defvalue) const
{
    Fl_String t = trim();
    if (!t.length()) return defvalue;
    int value = strtol(t.c_str(), NULL, 10);
    if(errno == ERANGE) return defvalue;
    if(value == 0 && t != "0") return defvalue;
    return value;
}

float Fl_String::to_float(float defvalue) const
{
    Fl_String t = trim();
    if(!t.length()) return defvalue;
    float value = (float)strtod(t.c_str(), NULL);
    if(errno == ERANGE) return defvalue;
    return value;
}

double Fl_String::to_double(double defvalue) const
{
    Fl_String t = trim();
    if (!t.length()) return defvalue;
    double value = strtod(t.c_str(), NULL);
    if (errno == ERANGE) return defvalue;
    return value;
}

void Fl_String::sub_insert(int start, const char *in_str)
{
    if(start > length()) start = length();
    int in_len = strlen(in_str);
    int new_len = length()+in_len;
    str_ = (char *)realloc(str_, new_len+1);
    if(start<length()) memmove(str_+start+in_len, str_+start, new_len-start);
    memcpy(str_+start, in_str, in_len);
    str_[new_len] = '\0';
    len_ = new_len;
}

void Fl_String::sub_insert(int start, char ch)
{
    if(start > length()) start = length();
    int new_len = length()+1;
    str_ = (char *)realloc(str_, new_len+1);
    if(start<length()) memmove(str_+start+1, str_+start, new_len-start);
    str_[start] = ch;
    str_[new_len] = '\0';
    len_ = new_len;
}

void Fl_String::sub_delete(int start, int count)
{
    if (count) {
        int l = len_+1;
        if (count > (int)len_ - start)
            count = len_ - start;
        if (count > 0) {
            memmove(str_+start, str_+start+count, l-count-start);
            len_ -= count;
            str_[len_] = '\0';
        }
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
    assign(s.str_, s.len_);
}

void Fl_String::set_length(int new_len)
{
    str_ = (char *)realloc(str_, new_len+1);
    str_[new_len] = '\0';
    len_ = new_len;
}

//------------------------------------------------------------------------------

int Fl_String::to_latin1(char *&str)
{
	str = (char*)malloc(sizeof(char) * length());
	int len = fl_utf2latin1((const uchar*)c_str(), length(), str);
	str[len] = '\0';
	return len;
}

int Fl_String::to_unicode(unsigned short *&str)
{
	str = (unsigned short *)malloc(sizeof(unsigned short) * (length()+10));
	int len = fl_utf2unicode((const uchar*)c_str(), length(), str);
	str[len] = 0;
	return len;
}

//------------------------------------------------------------------------------

Fl_String Fl_String::from_codeset(int conv_index, const char *str, int str_len)
{
    if(str_len<=0) str_len = strlen(str);

    int outsize = str_len*3;
    char *outbuf = (char*)malloc(outsize);

    int len = fl_convert2utf(conv_index,
                             (const uchar*)str, str_len,
                             outbuf, outsize);
    Fl_String ret;
    if(len>0) ret.append(outbuf, len);
    //else ret.append(str, str_len);

    free(outbuf);
    return ret;
}

Fl_String Fl_String::from_codeset(Fl_String codeset, const char *str, int str_len) {
    return Fl_String::from_codeset(fl_find_converter(codeset.c_str()), str, str_len);
}

Fl_String Fl_String::from_latin1(const char *str, int str_len)
{
	char *buf = (char*)malloc(sizeof(char) * (str_len*3));
	int len = fl_latin12utf((const uchar*)str, str_len, buf);	
	Fl_String ret(buf, len);
	free((char*)buf);
	return ret;	
}

Fl_String Fl_String::from_unicode(const unsigned short *str, int str_len)
{
	char *buf = (char*)malloc(sizeof(char) * (str_len*5));
	int len = fl_unicode2utf((unsigned short *)str, str_len, buf);
	Fl_String ret(buf, len);
	free((char*)buf);
	return ret;	
}

