//
// "$Id$"
//
// Unicode to UTF-8 conversion functions header.
//
// Copyright 2000 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
//

/*** NOTE : all functions are LIMITED to 24 bits Unicode values !!! ***/

#ifndef fl_utf8_h
#define fl_utf8_h

#include "Fl_Export.h"
#include <stdio.h> //For FILE

#ifdef __cplusplus
extern "C" {
#endif

// Returns true, if UTF-8 support compiled in.
FL_API int fl_supports_utf8();

FL_API int fl_utf2ucs( const unsigned char *buf, int len, unsigned int *ucs);
FL_API int fl_ucs2utf(unsigned int ucs, char *buf);
FL_API int fl_utflen(const unsigned char *buf, int len);
FL_API int fl_utf_charlen(char c);
FL_API int fl_utf_nb_char(const unsigned char *buf, int len);
FL_API int fl_utf_strncasecmp(const char *s1, const char *s2, int n);
FL_API int fl_utf_strcasecmp(const char *s1, const char *s2);
FL_API int fl_tolower(unsigned int ucs);
FL_API int fl_toupper(unsigned int ucs);
FL_API int fl_utf_tolower(const unsigned char *str, int len, char *buf);
FL_API int fl_utf_toupper(const unsigned char *str, int len, char *buf);
FL_API int fl_utf2unicode(const unsigned char *str, int len, unsigned short *buf);
FL_API int fl_unicode2utf(unsigned short *str, int len, char *buf);
FL_API int fl_utf2latin1(const unsigned char *str, int len, char *buf);
FL_API int fl_latin12utf(const unsigned char *str, int len, char *buf);
FL_API unsigned short fl_nonspacing(unsigned int ucs);
FL_API char* fl_utf2mbcs(const char * s);
FL_API char* fl_mbcs2utf(const char *s);

FL_API int fl_is_nt4(void);
FL_API int fl_chmod(const char* f, int mode);
FL_API int fl_access(const char* f, int mode);
FL_API int fl_stat( const char *path, struct stat *buffer );
FL_API char* fl_getcwd( char *buf, int maxlen);
FL_API FILE* fl_fopen(const char *f, const char *mode);
FL_API int fl_open(const char* f, int o, int p);
FL_API int fl_unlink(const char *f);
FL_API char* fl_getenv(const char *name);

#define fl_open(a, b) fl_open(a, b, -1)

#ifdef __cplusplus
}
#endif

#endif
 
//
// End of "$Id$".
//

