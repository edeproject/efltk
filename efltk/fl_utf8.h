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

#ifndef FL_API
#if defined(FL_DLL) && defined(_MSC_VER)
#  ifdef FL_LIBRARY
#    define FL_API   __declspec(dllexport)
#  else
#    define FL_API   __declspec(dllimport)
#  endif /* FL_LIBRARY */
#else
#  define FL_API
#endif /* FL_DLL && _MSC_VER */
#endif /* FL_EXPORT */

#  ifdef __cplusplus
extern "C" {
#  endif

FL_API int fl_utf2ucs( const unsigned char *buf, int len, unsigned int *ucs);
FL_API int fl_ucs2utf(unsigned int ucs, char *buf);
FL_API int fl_utflen(const unsigned char *buf, int len);
FL_API int fl_utf_nb_char(const unsigned char *buf, int len);
FL_API int fl_utf_strncasecmp(const char *s1, const char *s2, int n);
FL_API int fl_utf_strcasecmp(const char *s1, const char *s2);
FL_API int fl_tolower(unsigned int ucs);
FL_API int fl_toupper(unsigned int ucs);
FL_API int fl_utf_tolower(const unsigned char *str, int len, char *buf);
FL_API int fl_utf_toupper(const unsigned char *str, int len, char *buf);
FL_API int fl_utf2unicode(const unsigned char *str, int len, 
		unsigned short *buf);
FL_API int fl_unicode2utf(unsigned short *str, int len, char *buf);
FL_API int fl_utf2latin1(const unsigned char *str, int len, char *buf);
FL_API int fl_latin12utf(const unsigned char *str, int len, char *buf);
FL_API unsigned int fl_nonspacing(unsigned int ucs);

#  ifdef __cplusplus
}
#  endif

#endif
 
//
// End of "$Id$".
//

