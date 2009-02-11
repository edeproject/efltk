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
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_UTF8_H_
#define _FL_UTF8_H_

#include "Fl_Export.h"
#include <stdio.h> //For FILE

/*** NOTE : all functions are LIMITED to 24 bits Unicode values !!! ***/

/** 
 * Converts the first char UTF-8 string to an Unicode value
 * returns the byte length of the converted UTF-8 char
 * returns -1 if the UTF-8 string is not valid */
extern FL_API int fl_utf2ucs( const unsigned char *buf, int len, unsigned int *ucs);
/** 
 *  Same as fl_utf2ucs but no sanity check is done. */
extern FL_API int fl_fast_utf2ucs(const unsigned char *buf, int len, unsigned int *ucs);

/** Returns next UTF-8 charlen, 0 if inside char */
extern FL_API int fl_utf_charlen(char c);

/** 
 *  Converts an Unicode value to an UTF-8 string
 * NOTE : the buffer (buf) must be at least 5 bytes long! */
extern FL_API int fl_ucs2utf(unsigned int ucs, char *buf);

/** 
 *  Returns the byte length of the first UTF-8 char
 * (returns -1 if not valid) */
extern FL_API int fl_utflen(const unsigned char *buf, int len);

/** 
 *  Returns the number of Unicode chars in the UTF-8 string */
extern FL_API int fl_utf_nb_char(const unsigned char *buf, int len);

/** 
 * Compare only the first 'n' bytes
 * return 0 if the strings are equal;
 * return 1 if s1 is greater than s2
 * return -1 if s1 is less than s2 */
extern FL_API int fl_utf_strncasecmp(const char *s1, const char *s2, int n);

/** 
 * return 0 if the strings are equal;
 * return 1 if s1 is greater than s2
 * return -1 if s1 is less than s2 */
extern FL_API int fl_utf_strcasecmp(const char *s1, const char *s2);

/** 
 * return 0 if the strings are equal;
 * return 1 if s1 is greater than s2
 * return -1 if s1 is less than s2 */
extern FL_API int fl_utf_strcasecmp(const char *s1, int s1_len, const char *s2, int s2_len);

/**  Return the Unicode lower case value of ucs */
extern FL_API int fl_tolower(unsigned int ucs);
/* Return the Unicode upper case value of ucs */
extern FL_API int fl_toupper(unsigned int ucs);

/** Converts the str string to the lower case equivalent into buf.
 * Warning: to be safe buf length must be at least 3 * len */
extern FL_API int fl_utf_tolower(const unsigned char *str, int len, char *buf);

/** converts the str string to the upper case equivalent into buf.
 * Warning: to be safe buf length must be at least 3 * len */
extern FL_API int fl_utf_toupper(const unsigned char *str, int len, char *buf);

/** converts a UTF-8 str to unicode
 * Warning: buf must a least 'len' long */
extern FL_API int fl_utf2unicode(const unsigned char *str, int len, unsigned short *buf);

/** convert Unicode str to UTF-8
 * Warning: buf must be at least 3 * len long */
extern FL_API int fl_unicode2utf(unsigned short *str, int len, char *buf);

/** convert UTF-8 str to latin1
 * Warning: buf must be at least len long */
extern FL_API int fl_utf2latin1(const unsigned char *str, int len, char *buf);

/** convert latin1 str to UTF-8
 * Warning: buf must be at least 2 * len long */
extern FL_API int fl_latin12utf(const unsigned char *str, int len, char *buf);

/** Returns non-spacing unicode, if ucs is non-spacing. Otherwise 0 */
extern FL_API unsigned short fl_nonspacing(unsigned int ucs);

/*
 * Following functions are only usable in WIN32!
 * But it's highly recommended to use these functions
 * in your application, cause of portability issues.
 */
extern FL_API char* fl_utf2mbcs(const char * s);
extern FL_API char* fl_mbcs2utf(const char *s);
extern FL_API int fl_chmod(const char* f, int mode);
extern FL_API int fl_access(const char* f, int mode);
extern FL_API int fl_stat( const char *path, struct stat *buffer );
extern FL_API char* fl_getcwd( char *buf, int maxlen);
extern FL_API FILE* fl_fopen(const char *f, const char *mode);
extern FL_API int fl_open(const char* f, int o, int p = -1);
extern FL_API int fl_unlink(const char *f);
extern FL_API char* fl_getenv(const char *name);

extern FL_API int fl_is_nt4(void);
extern FL_API int fl_is_ce(void);

/** Try to find converter index from cache.
 * Returns -1 on error. */
extern FL_API int fl_find_converter(const char *from_codeset);

/** Convert inbuf to UTF-8 with converter find in cache at 'conv_index'
 * returns bytes converted. 'inlen' points to last
 * converted position in 'inbuf' */
extern FL_API int fl_convert2utf(int conv_index,
                   const unsigned char *inbuf, int &inlen,
                   char *outbuf, int outlen);

/** Shortcut for fl_find_converter and fl_convert2utf.
 * This should be used only, when converting 1-2 times.
 */
extern FL_API int fl_convert2utf(const char *from_codeset,
                          const unsigned char *inbuf, int &inlen,
                          char *outbuf, int outlen);

#endif
