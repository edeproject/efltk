/***************************************************************************
                          Fl_String.cpp  -  description
                             -------------------
    begin                : Tue Dec 14 1999
    copyright            : (C) 1999 by Alexey Parshin
    email                : sparx@olma.co.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
 /*  modified by Martin Pekar 01/04/2002 */
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

#include <efltk/Fl_String.h>
#include <efltk/Fl_Util.h>

//------------------------------------------------------------------------------
// constructors & destructors
//------------------------------------------------------------------------------
Fl_String::Fl_String(char c,int repeater)
{
    if (repeater == 1) {
        str = new char[1];
        str[0] = c;
    } else {
        str = (char *)malloc(repeater + 1);
        memset(str,c,repeater);
        str[repeater] = '\0';
    }
}

Fl_String::Fl_String(int number)
{
    str = new char[33];
    snprintf(str, 32, "%i", number);
}

Fl_String::Fl_String(unsigned number)
{
    str = new char[33];
    snprintf(str, 32, "%i", number);
}

Fl_String::Fl_String(const char *s,int maxlen)
{
    if (maxlen>=0) {
        str = new char[maxlen + 1];
        strncpy(str, s, maxlen);
        str[maxlen] = '\0';
    } else {
        if(s) {
            str = strdup(s);
        } else {
            str = new char[1];
            str[0] = '\0';
        }
    }
}

//------------------------------------------------------------------------------
// assignments
//------------------------------------------------------------------------------
void Fl_String::assign(const char *s)
{
    if(s) {
        int len = strlen(s)+1;
        str = (char*)realloc(str, len*sizeof(char));
        strncpy(str, s, len-1);
        str[len-1] = '\0';
    } else {
        str = (char*)realloc(str, sizeof(char));
        str[0] = '\0';
    }
}

Fl_String& Fl_String::operator = (const char *s)
{
    assign(s);
    return *this;
}

Fl_String& Fl_String::operator = (const Fl_String& s)
{
    assign(s.str);
    return *this;
}

//------------------------------------------------------------------------------
// comparisions
//------------------------------------------------------------------------------
bool operator <  (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str,s2.str) < 0;
}

bool operator <= (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str,s2.str) <= 0;
}

bool operator >  (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str,s2.str) > 0;
}

bool operator >= (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str,s2.str) >= 0;
}

bool operator == (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str,s2.str) == 0;
}

bool operator != (const Fl_String &s1, const Fl_String &s2) {
    return strcmp(s1.str,s2.str) != 0;
}

bool Fl_String::cmp(Fl_String &s) {
    return strcmp(str, s.str) != 0;
}

bool Fl_String::casecmp(Fl_String &s) {
    return strcasecmp(str, s.str) != 0;
}

//------------------------------------------------------------------------------
// operations
//------------------------------------------------------------------------------
Fl_String Fl_String::operator + (const char * s) const
{
    char *temp;
    if(s) temp = new char[length() + strlen(s) + 1];
    else temp = new char[length() + 1];
    strcpy(temp,str);
    if(s) strcat(temp, s);

    Fl_String s1(temp, true, true);
    return s1;
}

Fl_String Fl_String::operator + (const Fl_String& s) const
{
    char *temp = new char[length() + s.length() + 1];
    strcpy(temp,str);
    if(s.length()) strcat(temp, s.c_str());

    Fl_String s1(temp, true, true);
    return s1;
}

Fl_String& Fl_String::operator += (const char * s)
{
    if(s) {
        str = (char *)realloc(str, length() + strlen(s) + 1);
        strcat(str, s);
    }
    return *this;
}

Fl_String& Fl_String::operator += (const Fl_String& s)
{
    str = (char *) realloc(str, length() + s.length() + 1);
    if(s.length()) strcat(str,s.str);
    return *this;
}
//------------------------------------------------------------------------------
// usefull methods
//------------------------------------------------------------------------------
void Fl_String::clear()
{
    str = (char *) realloc(str, sizeof(char));
    str[0] = '\0';
}

Fl_String Fl_String::trimRight() const
{
    Fl_String ret(str);
    char *s = ret.str;
    s = fl_trimright(s);
    return ret;
}

Fl_String Fl_String::trimLeft() const
{
    char *s = str;
    s = fl_trimleft(s);
    return s;
}

Fl_String Fl_String::lowerCase() const
{
    Fl_String  s = str;
    fl_tolower(s.str);
    return s;
}

Fl_String Fl_String::upperCase() const
{
    Fl_String  s = str;
    fl_toupper(s.str);
    return s;
}

extern int fl_va_len(char *format, va_list ap); //Fl_Util.cpp
void Fl_String::printf(const char *string, ...)
{
    char *s;
    int len = 0;

    if(!string || !strcmp(string, ""))
        return;

    va_list ap;
    va_start(ap, string);
    len = fl_va_len((char *)string, ap);
    va_end(ap);

    len += strlen(string);
    s = new char[len];

    va_start(ap, string);
    vsprintf(s, string, ap);
    va_end(ap);

    assign(s);
}

Fl_String Fl_String::remove(const char *pattern) const
{
    if(!pattern) return str;
    Fl_String result;
    int patternLength = strlen(pattern);
    if (!patternLength) return str;
    char *temp = strdup(str);
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
    if(pattern) return str;
    Fl_String result;
    int patternLength = strlen(pattern);
    if (!patternLength) return str;
    char *temp = strdup(str);
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
    return strlen(str);
}

bool Fl_String::isEmpty() const {
    return str[0] == '\0';
}

int Fl_String::pos(const char *substr, int index) const
{
    char *ptr = (str+index);
    char *p = strstr( ptr, substr );
    if(!p) return -1;
    return int(p - str);
}

int Fl_String::pos(int c, int index) const
{
    char *ptr = (str+index);
    char *p = strchr( ptr, c );
    if (!p) return -1;
    return int(p - str);
}

int Fl_String::rpos(int c, int index) const
{
    char *ptr = (str+index);
    char *p = strrchr( ptr, c );
    if (!p) return -1;
    return int(p - str);
}

Fl_String Fl_String::subString(int start,int count) const
{
    return Fl_String(str+start, count);
}

int Fl_String::toInt(int defvalue) const
{
    Fl_String t = trim();
    if (!t.length()) return defvalue;
    int value = atoi(t.c_str());
    if(value == 0 && t != "0")
        return defvalue;
    return value;
}

float Fl_String::toFloat(float defvalue) const
{
    Fl_String t = trim();
    if (!t.length()) return defvalue;
    float value = (float)atof(t.c_str());
    if (errno == ERANGE) return defvalue;
    return value;
}

double Fl_String::toDouble(double defvalue) const
{
    Fl_String t = trim();
    if (!t.length()) return defvalue;
    double value = atof(t.c_str());
    if (errno == ERANGE) return defvalue;
    return value;
}

void Fl_String::subInsert(int start,const char *insStr)
{
    int l = length();
    if (l < start) start = l;
    Fl_String ending(str + start);
    str[start] = 0;
    *this += insStr + ending;
}

void Fl_String::subInsert(int start,char ch)
{
    char st[2] = { ch, '\0' };
    subInsert(start,st);
}

void Fl_String::subDelete(int start,int count)
{
    if (count) {
        int l = strlen(str)+1;
        if (count > l) count = l;
        memmove(str+start, str+start+count, l-count);
    }
}

void Fl_String::subReplace(const char *s_str,const char *r_str)
{
    Fl_String  s;
    int   l = strlen(s_str);
    char *ptext = str;
    char *pstart = strstr(str,s_str);
    while (pstart) {
        *pstart = 0;
        s += ptext;
        if (r_str)
            s += r_str;
        ptext = pstart + l;
        pstart = strstr(ptext,s_str);
    }
    s += ptext;
    assign(s.str);
}

void Fl_String::setLength(int newLength)
{
    str = (char *)realloc(str,newLength+1);
    str[newLength] = 0;
}

Fl_String Fl_String::wordAt(long position) const
{
    char *temp;

    Fl_String s("", strlen(str));

    // rewind to start of current word
    while(!isspace(str[position-1]) && !ispunct(str[position-1]))
        if(position)
            position--;
        else
            break;
    // skip leading punctuation
    int len = length();
    while(ispunct(str[position]))
        if(position < len)
            position++;
        else
            break;
    temp = s.str;
    while(str[position] && !(isspace(str[position])))
    {
        if(ispunct(str[position]))
            if(str[position] != '\'')
                break;
        *temp++ = str[position++];
    }
    *temp = '\0';
    return s;
}

Fl_String& Fl_String::chopAt(long  limit, Fl_String *remainder)
{
    int l = length();
    if (limit > l) limit = l;
    if ( limit < 0) limit = 0;
    if (remainder)
        remainder->assign(str+limit);
    str[limit] = '\0';
    return(*this);
}

Fl_String& Fl_String::wrapAt(long limit, Fl_String *remainder)
{
    if (remainder)
        *remainder = "";

    int l = length();
    if (limit > l) limit = l;
    if ( limit < 0) limit = 0;

    if (isspace(str[limit]) || (str[limit] == '\0'))
        chopAt(limit,remainder);
    else
    {
        while(limit && !isspace(str[limit]))
            limit--;
        if(limit)
            chopAt(++limit,remainder);  // skip past space, clip rest of line
    }

    return *this;
}

Fl_String Fl_String::substituteSpecialChars(char prefix) const
{
    Fl_String  newstr;
    char *tempStr = strdup(str);
    char *start = tempStr;
    char cc[] = " ";

    for (;;) {
        char *end = strchr(start,prefix);
        if (!end) {
            newstr += start;
            break;
        }
        bool doublePrefix = false;
        if (*(end+1) == prefix) {
            // Duplicated prefix - leave one of them
            end++;
            doublePrefix = true;
        }
        *end = 0;

        newstr += start;
        start = end + 1;

        if (!doublePrefix) {
            char *nextItem;
            int charCode = (int)strtol(start,&nextItem,0);
            if (nextItem != start) {
                cc[0] = charCode;
                newstr += cc;
                start = nextItem;
            }
        }
    }
    free(tempStr);
    return newstr;
}
//------------------------------------------------------------------------------
Fl_String Fl_String::IntToString(int val)
{
    Fl_String str("", 33);
    snprintf((char*)str.c_str(), 32, "%i", val);
    return str;
}
//------------------------------------------------------------------------------
Fl_String operator +(const char*s, const Fl_String& rhs)
{
    return Fl_String(s) + rhs;
}

//------------------------------------------------------------------------------
bool operator <  (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str,s2) < 0;
}

bool operator <= (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str,s2) <= 0;
}

bool operator >  (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str,s2) > 0;
}

bool operator >= (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str,s2) >= 0;
}

bool operator == (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str,s2) == 0;
}

bool operator != (const Fl_String &s1, const char *s2) {
    return strcmp(s1.str,s2) != 0;
}
//------------------------------------------------------------------------------

