/***************************************************************************
                          Fl_String.h  -  description
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
#ifndef __Fl_STRING_H__
#define __Fl_STRING_H__

#include "Enumerations.h"
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32

# ifndef strcasecmp
#  define strcasecmp(a,b) stricmp(a,b)
# endif
# ifndef strncasecmp
#  define strncasecmp(a,b,c) strnicmp(a,b,c)
# endif
# ifndef strtok_r
#  define strtok_r(a,b,c) strtok(a,b)
# endif

#endif

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
   char *str;
   void assign(const char *st);

public:
   // constructors & destructors
   Fl_String(char c,int repeater = 1);
   Fl_String(int number);
   Fl_String(unsigned number);
   Fl_String(const char *s="") { if(!s) s=""; str = strdup(s); }
   Fl_String(const char *s, int maxlen);
   Fl_String(const Fl_String& s) { str = strdup(s.str); }
   ~Fl_String() { delete []str; }

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
   Fl_String& operator += (const char * s);
   Fl_String& operator += (const Fl_String& s);

   // usefull methods
   void clear();
   Fl_String  trimRight() const;
   Fl_String  trimLeft()  const;
   Fl_String  trim()      const;
   Fl_String  remove(const char *pattern) const;
   Fl_String  replace(const char *pattern,const char *replacement) const;
   Fl_String  lowerCase() const;
   Fl_String  upperCase() const;
   Fl_String  subString(int start,int count) const;
   void     subDelete(int start,int count=1);
   void     subDelete(const char *s) { subReplace(s,NULL); }
   void     subInsert(int start,const char *str);
   void     subInsert(int start,char ch);
   void     subReplace(const char *s_str,const char *r_str);
   Fl_String  wordAt(long position) const;
   Fl_String& wrapAt(long limit, Fl_String *remainder=NULL);
   Fl_String& chopAt(long limit, Fl_String *remainder=NULL);
   int      length() const;
   int      pos(const char *substr, int index=0) const;
   int      pos(int c, int index=0) const;
   int      rpos(int c, int index=0) const;
   int      toInt(int defvalue=0) const;
   double   toFloat(float defvalue=0) const;
   bool     isEmpty() const;
   void     setLength(int newLength);
   Fl_String  substituteSpecialChars(char prefix) const;
   const char *c_str() const { return str; }

   void printf(const char *str, ...);

   // auto conversion to char* when needed    
   operator const char *() { return str; }   
   operator char *() { return str; }   
   
   // element access
   char& operator [] (const int i) { return str[i]; }
   char  operator [] (const int i) const { return str[i]; }

   // extra functionality to support CEditor
   char& lastCharacter() const { return str[strlen(str)-1]; };

   static Fl_String IntToString(int val);
};

#endif
