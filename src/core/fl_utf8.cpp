//
// "$Id$"
//
// Unicode to UTF-8 conversion functions.
//
// Copyright 2000-2001 by O'ksi'D.
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
// Please report all bugs and problems to "xd640@oksid.ch".
//
// Author: Jean-Marc Lienher ( http://oksid.ch )
//
// Modifed: Mikko Lahteenmaki <mikko@fltk.net>
//

#include <config.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
# include <windows.h>
# include <io.h>
# include <direct.h>
#else
# include <fcntl.h>
# include <unistd.h>
#endif

#ifdef _WIN32_WCE
  extern int _open( const char *filename, int oflag , int pmode );
  extern int _chmod( const char *filename, int pmode );
  extern int _access(const char *, int);
  extern int unlink(const char *f);
# define open(a,b,c) _open(a,b,c)
# define chmod(a,b) _chmod(a,b)
# define access(a,b) _access(a,b)
#endif

int fl_is_nt4(void)
{
#ifdef _WIN32
    static int ret = -1;
    if(ret >= 0) return ret;
	OSVERSIONINFO o;
    o.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&o);
    if(o.dwPlatformId == VER_PLATFORM_WIN32_NT && o.dwMajorVersion >= 4) {
        ret = (int) o.dwMajorVersion;
    } else {
        ret = 0;
    }
    return ret;
#else
    return 0;
#endif
}

int fl_is_ce(void)
{
#ifdef _WIN32_CE
	return 1;
#else
	return 0;
#endif
}

#include "headers/spacing.h"
#include "headers/case.h"

/*** NOTE : all functions are LIMITED to 24 bits Unicode values !!! ***/
/***        but only 16 bits are realy used under Linux and win32  ***/

/*
 * return the Unicode lower case value of ucs
 */
int fl_tolower(unsigned int ucs)
{
#if HAVE_XUTF8
    int ret;

    if (ucs <= 0x02B6) {
        if (ucs >= 0x0041) {
            ret = ucs_table_0041[ucs - 0x0041];
            if (ret > 0) return ret;
        }
        return ucs;
    }

    if (ucs <= 0x0556) {
        if (ucs >= 0x0386) {
            ret = ucs_table_0386[ucs - 0x0386];
            if (ret > 0) return ret;
        }
        return ucs;
    }

    if (ucs <= 0x10C5) {
        if (ucs >= 0x10A0) {
            ret = ucs_table_10A0[ucs - 0x10A0];
            if (ret > 0) return ret;
        }
        return ucs;
    }

    if (ucs <= 0x1FFC) {
        if (ucs >= 0x1E00) {
            ret = ucs_table_1E00[ucs - 0x1E00];
            if (ret > 0) return ret;
        }
        return ucs;
    }

    if (ucs <= 0x2133) {
        if (ucs >= 0x2102) {
            ret = ucs_table_2102[ucs - 0x2102];
            if (ret > 0) return ret;
        }
        return ucs;
    }

    if (ucs <= 0x24CF) {
        if (ucs >= 0x24B6) {
            ret = ucs_table_24B6[ucs - 0x24B6];
            if (ret > 0) return ret;
        }
        return ucs;
    }

    if (ucs <= 0x33CE) {
        if (ucs >= 0x33CE) {
            ret = ucs_table_33CE[ucs - 0x33CE];
            if (ret > 0) return ret;
        }
        return ucs;
    }

    if (ucs <= 0xFF3A) {
        if (ucs >= 0xFF21) {
            ret = ucs_table_FF21[ucs - 0xFF21];
            if (ret > 0) return ret;
        }
        return ucs;
    }

    return ucs;
#else
    return tolower(ucs);
#endif        
}

/*
 * return the Unicode upper case value of ucs
 */
int fl_toupper(unsigned int ucs)
{
#if HAVE_XUTF8
    int i;
    static unsigned short *table = NULL;

    if (!table) {
        table = (unsigned short*)malloc(0x10000*sizeof(short));
        for (i = 0; i < 0x10000; i++) {
            table[i] = (unsigned short)i;
        }
        for (i = 0; i < 0x10000; i++) {
            int l = fl_tolower(i);
            if(l != i) table[l] = (unsigned short)i;
        }
    }
    if (ucs >= 0x10000) return ucs;
    return table[ucs];
#else
    return toupper(ucs);
#endif    
}

// Returns charlen, 0 if inside char
int fl_utf_charlen(char c)
{
#if HAVE_XUTF8
    if (!(c & 0x80)) return 1;
    if (c & 0x40) {
        if (c & 0x20) {
            if (c & 0x10) {
                if (c & 0x08) {
                    if (c & 0x04) {
                        return 6;
                    }
                    return 5;
                }
                return 4;
            }
            return 3;
        }
        return 2;
    }
    return 0;
#else
    return 1;
#endif    
}

/*** converts the first char UTF-8 string to an Unicode value ***/
/*** returns the byte length of the converted UTF-8 char **/
/*** returns -1 if the UTF-8 string is not valid ***/
int fl_utf2ucs(const unsigned char     *buf,
		       int                     len,
			   unsigned int            *ucs)
{
#if HAVE_XUTF8
    if (buf[0] & 0x80)
    {
        if (buf[0] & 0x40)
        {
            if (buf[0] & 0x20)
            {
                if (buf[0] & 0x10)
                {
                    if (buf[0] & 0x08)
                    {
                        if (buf[0] & 0x04)
                        {
                            if (buf[0] & 0x02)
                            {
                                /* bad UTF-8 string */
                            }
                            else
                            {
                                /* 0x04000000 - 0x7FFFFFFF */
                            }
                        }
                        else if (len > 4)
                        {
                            /* 0x00200000 - 0x03FFFFFF */
                            *ucs =  ((buf[0] & ~0xF8) << 24) +
                                ((buf[1] & ~0x80) << 18) +
                                ((buf[2] & ~0x80) << 12) +
                                ((buf[3] & ~0x80) << 6) +
                                (buf[4] & ~0x80);
                            if (*ucs > 0x001FFFFF && *ucs < 0x01000000) return 5;
                        }
                    }
                    else if (len > 3)
                    {
                        /* 0x00010000 - 0x001FFFFF */
                        *ucs =  ((buf[0] & ~0xF0) << 18) +
                            ((buf[1] & ~0x80) << 12) +
                            ((buf[2] & ~0x80) << 6) +
                            (buf[3] & ~0x80);
                        if (*ucs > 0x0000FFFF) return 4;
                    }
                }
                else if (len > 2)
                {
                    /* 0x00000800 - 0x0000FFFF */
                    *ucs =  ((buf[0] & ~0xE0) << 12) +
                        ((buf[1] & ~0x80) << 6) +
                        (buf[2] & ~0x80);
                    if (*ucs > 0x000007FF) return 3;
                }
            }
            else if (len > 1)
            {
                /* 0x00000080 - 0x000007FF */
                *ucs = ((buf[0] & ~0xC0) << 6) +
                    (buf[1] & ~0x80);
                if (*ucs > 0x0000007F) return 2;
            }
        }
    }
    else if (len > 0)
    {
        /* 0x00000000 - 0x0000007F */
        *ucs = buf[0];
        return 1;
    }

    *ucs = (unsigned int) '?';   /* bad utf-8 string */
    return -1;
#else
    *ucs = buf[0];
    return 1;
#endif        
}

/* 
 * Same as fl_utf2ucs but no sanity check is done.
 */
int fl_fast_utf2ucs(const unsigned char     *buf,
                    int                     len,
                    unsigned int            *ucs)
{
#if HAVE_XUTF8
    if (buf[0] & 0x80) {
        if (buf[0] & 0x40) {
            if (buf[0] & 0x20) {
                if (buf[0] & 0x10) {
                    if (buf[0] & 0x08) {
                        if (buf[0] & 0x04) {
                            if (buf[0] & 0x02) {
                                /* bad UTF-8 string */
                            } else {
                                /* 0x04000000 - 0x7FFFFFFF */
                            }
                        } else if (len > 4) {
                            /* 0x00200000 - 0x03FFFFFF */
                            *ucs =  ((buf[0] & ~0xF8) << 24) +
                                ((buf[1] & ~0x80) << 18) +
                                ((buf[2] & ~0x80) << 12) +
                                ((buf[3] & ~0x80) << 6) +
                                (buf[4] & ~0x80);
                            return 5;
                        }
                    } else if (len > 3) {
                        /* 0x00010000 - 0x001FFFFF */
                        *ucs =  ((buf[0] & ~0xF0) << 18) +
                            ((buf[1] & ~0x80) << 12) +
                            ((buf[2] & ~0x80) << 6) +
                            (buf[3] & ~0x80);
                        return 4;
                    }
                } else if (len > 2) {
                    /* 0x00000800 - 0x0000FFFF */
                    *ucs =  ((buf[0] & ~0xE0) << 12) +
                        ((buf[1] & ~0x80) << 6) +
                        (buf[2] & ~0x80);
                    return 3;
                }
            } else if (len > 1) {
                /* 0x00000080 - 0x000007FF */
                *ucs = ((buf[0] & ~0xC0) << 6) +
                    (buf[1] & ~0x80);
                return 2;
            }
        }
    } else if (len > 0) {
        /* 0x00000000 - 0x0000007F */
        *ucs = buf[0];
        return 1;
    }
    *ucs = (unsigned int)'?'; /* bad utf-8 string */
    return -1;
#else
    *ucs = buf[0];
    return 1;
#endif        
}


/*** converts an Unicode value to an UTF-8 string  ***/
/*** NOTE : the buffer (buf) must be at least 5 bytes long !!!  ***/
int fl_ucs2utf(unsigned int ucs,
               char         *buf)
{
#if HAVE_XUTF8    
    if (ucs < 0x000080)
    {
        buf[0] = ucs;
        return 1;
    }
    else if (ucs < 0x000800)
    {
        buf[0] = 0xC0 | (ucs >> 6);
        buf[1] = 0x80 | (ucs & 0x3F);
        return 2;
    }
    else if (ucs < 0x010000)
    {
        buf[0] = 0xE0 | (ucs >> 12);
        buf[1] = 0x80 | ((ucs >> 6) & 0x3F);
        buf[2] = 0x80 | (ucs & 0x3F);
        return 3;
    }
    else if (ucs < 0x00200000)
    {
        buf[0] = 0xF0 | (ucs >> 18);
        buf[1] = 0x80 | ((ucs >> 12) & 0x3F);
        buf[2] = 0x80 | ((ucs >> 6) & 0x3F);
        buf[3] = 0x80 | (ucs & 0x3F);
        return 4;
    }
    else if (ucs < 0x01000000)
    {
        buf[0] = 0xF8 | (ucs >> 24);
        buf[1] = 0x80 | ((ucs >> 18) & 0x3F);
        buf[2] = 0x80 | ((ucs >> 12) & 0x3F);
        buf[3] = 0x80 | ((ucs >> 6) & 0x3F);
        buf[4] = 0x80 | (ucs & 0x3F);
        return 5;
    }
    buf[0] = '?';
    return -1;
#else
    buf[0] = char(ucs);
    return 1;    
#endif    
}


/*** returns the byte length of the first UTF-8 char ***/
/*** (returns -1 if not valid) ***/
int fl_utflen(const unsigned char *buf,
              int                 len)
{
#if HAVE_XUTF8
    static unsigned int ucs;
    return fl_utf2ucs(buf, len, &ucs);
#else
    return (len<1)?0:1;
#endif        
}


/**** returns the number of Unicode chars in the UTF-8 string ***/
int fl_utf_nb_char(const unsigned char *buf,
                   int             len)
{
#if HAVE_XUTF8
    int i = 0;
    int nbc = 0;
    while (i < len) {
        int cl = fl_utflen(buf + i, len - i);
        if (cl < 1) cl = 1;
        nbc++;
        i += cl;
    }
    return nbc;
#else
    return 0;
#endif        
}

/*
 * compare only the first n bytes
 * return 0 if the strings are equal;
 * return 1 if s1 is greater than s2
 * return -1 if s1 is less than s2
 */
int fl_utf_strncasecmp(const char *s1, const char *s2, int n)
{
#if HAVE_XUTF8
    int i;
    int s1_l;
    int s2_l;

    s1_l = 0;
    while (s1_l < n && s1[s1_l]) s1_l++;
    s2_l = 0;
    while (s2_l < n && s2[s2_l]) s2_l++;

    if (s1_l < s2_l)
    {
        return -1;
    }
    else if (s1_l > s2_l)
    {
        return 1;
    }
    for (i = 0; i < n;)
    {
        int l1, l2;
        unsigned int u1, u2;
        int res;

        l1 = fl_utf2ucs((unsigned char*)s1 + i, n - i, &u1);
        l2 = fl_utf2ucs((unsigned char*)s2 + i, n - i, &u2);
        if (l1 - l2 != 0) return l1 - l2;
        res = fl_tolower(u1) - fl_tolower(u2);
        if (res != 0) return res;
        if (l1 < 1) {
            i += 1;
        } else {
            i += l1;
        }
    }
    return 0;
#else
    return strncasecmp(s1, s2, n);
#endif    
}

/*
 * return 0 if the strings are equal;
 * return 1 if s1 is greater than s2
 * return -1 if s1 is less than s2
 */
int fl_utf_strcasecmp(const char *s1, int s1_l, const char *s2, int s2_l)
{
    if (s1_l < s2_l) {
        return -1;
    }
    else if (s1_l > s2_l) {
        return 1;
    }
    return fl_utf_strncasecmp(s1, s2, s1_l);
}

/*
 * return 0 if the strings are equal;
 * return 1 if s1 is greater than s2
 * return -1 if s1 is less than s2
 */
int fl_utf_strcasecmp(const char *s1, const char *s2)
{
    return fl_utf_strcasecmp(s1, strlen(s1), s2, strlen(s2));
}

/*
 * converts the str string to the lower case equivalent into buf.
 * Warning: to be safe buf length must be at least 3 * len
 */
int fl_utf_tolower(const unsigned char *str, int len, char *buf)
{
#if HAVE_XUTF8
	int i;
	int l = 0;
        for (i = 0; i < len;) {
                int l1, l2;
                unsigned int u1;

                l1 = fl_utf2ucs((unsigned char*)str + i, len - i, &u1);
                l2 = fl_ucs2utf((unsigned int) fl_tolower(u1), buf + l);
                if (l1 < 1) {
                        i += 1;
                } else {
                        i += l1;
		}
                if (l2 < 1) {
                        l += 1;
                } else {
                        l += l2;
		}

	}
	return l;
#else
    int n;
    for(n=0; n<=len; n++)
	buf[n] = tolower(str[n]);
    return len;
#endif    	
}

/*
 * converts the str string to the upper case equivalent into buf.
 * Warning: to be safe buf length must be at least 3 * len
 */
int fl_utf_toupper(const unsigned char *str, int len, char *buf)
{
#if HAVE_XUTF8
	int i;
	int l = 0;
        for (i = 0; i < len;) {
                int l1, l2;
                unsigned int u1;

                l1 = fl_utf2ucs((unsigned char*)str + i, len - i, &u1);
                l2 = fl_ucs2utf((unsigned int) fl_toupper(u1), buf + l);
                if (l1 < 1) {
                        i += 1;
                } else {
                        i += l1;
		}
                if (l2 < 1) {
                        l += 1;
                } else {
                        l += l2;
		}
	}
	return l;
#else
    int n;
    for(n=0; n<=len; n++)
	buf[n] = toupper(str[n]);
    return len;
#endif    	
}

/*
 * converts a UTF-8 str to unicode
 * Warning: buf must a least len long
 */
int fl_utf2unicode(const unsigned char *str, int len, unsigned short *buf)
{
#if HAVE_XUTF8
    int l = 0;
    for(int i = 0; i < len;) {
        unsigned int u1;
        int l1 = fl_utf2ucs((unsigned char*)str + i, len - i, &u1);
        buf[l] = (unsigned short) u1;
        if (l1 < 1) i += 1;
        else i += l1;
        l++;
    }
    return l;
#else
    for(int i=0; i < len; i++)
	buf[i] = (char) str[i];    
    return len;
#endif    
}


/*
 * convert Unicode str to UTF-8
 * Warning: buf must be at least 3 * len long
 */
int fl_unicode2utf(unsigned short *str, int len, char *buf)
{
#if HAVE_XUTF8
    int l = 0;
    for(int i = 0; i < len; i++) {
        int l1 = fl_ucs2utf((unsigned int) str[i], buf + l);
        if (l1 < 1) l += 1;
        else l += l1;
    }
    return l;
#else
    for(int i=0; i < len; i++)
	buf[i] = str[i];    
    return len;
#endif    
}

/*
 * convert UTF-8 str to latin1
 * Warning: buf must be at least len long
 */
int fl_utf2latin1(const unsigned char *str, int len, char *buf)
{
#if HAVE_XUTF8
    int l = 0;
    for(int i = 0; i < len;) {
        unsigned int u1;
		int l1 = fl_utf2ucs((unsigned char*)str + i, len - i, &u1);
		if (u1 > 0xFF) u1 = '?';
		buf[l] = (char) u1;
        if (l1 < 1) i += 1;
        else i += l1;
		l++;
	}
	return l;
#else
    memcpy(buf,str,len);
    return len;
#endif	
}

/*
 * convert latin1 str to UTF-8
 * Warning: buf must be at least 2 * len long
 */
int fl_latin12utf(const unsigned char *str, int len, char *buf)
{
#if HAVE_XUTF8
	int l = 0;
    for(int i = 0; i < len; i++) {
		int l1 = fl_ucs2utf((unsigned int) str[i], buf + l);
        if (l1 < 1) l += 1;
        else l += l1;
	}
	return l;
#else
    memcpy(buf,str,len);
    return len;
#endif	
}

unsigned short fl_nonspacing(unsigned int ucs)
{
    if (ucs <= 0x0361) {
        if (ucs >= 0x0300) return ucs_table_0300[ucs - 0x0300];
        return 0;
    }
    if (ucs <= 0x0486) {
        if (ucs >= 0x0483) return ucs_table_0483[ucs - 0x0483];
        return 0;
    }
    if (ucs <= 0x05C4) {
        if (ucs >= 0x0591) return ucs_table_0591[ucs - 0x0591];
        return 0;
    }
    if (ucs <= 0x06ED) {
        if (ucs >= 0x064B) return ucs_table_064B[ucs - 0x064B];
        return 0;
    }
    if (ucs <= 0x0D4D) {
        if (ucs >= 0x0901) return ucs_table_0901[ucs - 0x0901];
        return 0;
    }
    if (ucs <= 0x0FB9) {
        if (ucs >= 0x0E31) return ucs_table_0E31[ucs - 0x0E31];
        return 0;
    }
    if (ucs <= 0x20E1) {
        if (ucs >= 0x20D0) return ucs_table_20D0[ucs - 0x20D0];
        return 0;
    }
    if (ucs <= 0x309A) {
        if (ucs >= 0x302A) return ucs_table_302A[ucs - 0x302A];
        return 0;
    }
    if (ucs <= 0xFB1E) {
        if (ucs >= 0xFB1E) return ucs_table_FB1E[ucs - 0xFB1E];
        return 0;
    }
    if (ucs <= 0xFE23) {
        if (ucs >= 0xFE20) return ucs_table_FE20[ucs - 0xFE20];
        return 0;
    }
    return 0;
}

char *fl_utf2mbcs(const char *s)
{
#ifdef _WIN32
    if (!s) return NULL;
    
    static char *buf = NULL;
	static int buf_size=0;

    wchar_t *wbuf;

    int l = strlen(s);

    wbuf = (wchar_t*)malloc(sizeof(wchar_t)*(l+6));
    l = fl_utf2unicode((unsigned char*)s, l, (unsigned short*)wbuf);
    wbuf[l] = 0;
    
	int size = (l * 6 + 1);
	if(!buf) {
		buf_size = size;;
		buf = (char*)malloc(buf_size*sizeof(char));
	} else if(buf_size < size){
		buf_size = size;;		
		buf = (char*)realloc(buf, size*sizeof(char));
	}
    l = wcstombs(buf, wbuf, l);
    free((wchar_t*)wbuf);
    buf[l] = 0;
    return buf;
#else
    return (char*)s;
#endif
}

char *fl_mbcs2utf(const char *s)
{
#ifdef _WIN32
    static char *buf = NULL;
	static int buf_size=0;

    wchar_t *wbuf;
    int l;

    if (!s) return NULL;
    l = strlen(s);

    wbuf = (wchar_t*)malloc(sizeof(wchar_t)*(l*6+6));
    l = mbstowcs(wbuf, s, l);

    int size = (l * 6 + 1);
    if(!buf) {
    	buf_size = size;;
    	buf = (char*)malloc(buf_size*sizeof(char));
    } else if(buf_size < size){
    	buf_size = size;;
    	buf = (char*)realloc(buf, size*sizeof(char));
    }
    l = fl_unicode2utf((unsigned short *)wbuf, l, buf);
    free(wbuf);
    buf[l] = 0;
    return buf;
#else
    return (char*) s;
#endif
}

#ifdef _WIN32
extern char *fl_utf82locale(const char *s, UINT codepage=0);
static wchar_t *wbuf = NULL;
static int wbuf_size = 0;

#define grow_wbuf(len) if(len>wbuf_size) { wbuf = (wchar_t*)realloc(wbuf, sizeof(wchar_t) * (len+1)); wbuf_size = len; }
#define SHORT(s) ((unsigned short*)s)
#endif

char *fl_getenv(const char *v)
{
#ifdef _WIN32

	TCHAR *text;
#ifdef UNICODE	
    int len = fl_utf_nb_char((unsigned char*)v, strlen(v));
    text = (TCHAR*)malloc((len + 1) * sizeof(TCHAR));
    fl_utf2unicode((unsigned char*)v, len, (unsigned short*)text);
	text[len] = 0;
#else	
	text = fl_utf82locale(v);	
#endif

	static TCHAR buf[32767]; //Max env size	
	int buflen = GetEnvironmentVariable(text, buf, sizeof(buf));
	if(!buflen) return 0;

#ifdef UNICODE	
	static char ret[32767*3]; //Max env size
	ret[fl_unicode2utf((unsigned short*)buf, buflen, ret)] = 0;
	return ret;
#else
	return buf;
#endif
	
#else
    return getenv(v);
#endif
}

int fl_open(const char *f, int oflags, int pmode)
{
#if defined(_WIN32) && !defined(_WIN32_WCE)
	if (fl_is_nt4()) {
		int l = strlen(f);
		grow_wbuf(l);
		wbuf[fl_utf2unicode((const unsigned char*)f, l, SHORT(wbuf))] = 0;
		if (pmode == -1) return _wopen(wbuf, oflags);
		return _wopen(wbuf, oflags, pmode);
	}

    if (pmode == -1) return open(fl_utf2mbcs(f), oflags);
	return open(fl_utf2mbcs(f), oflags, pmode);
#else
	if (pmode == -1) return open(f, oflags);
	return open(f, oflags, pmode);
#endif
}

FILE *fl_fopen(const char* f, const char *mode)
{
#ifdef _WIN32
	if (fl_is_nt4()) {
		int l = strlen(f);
		grow_wbuf(l);
		wbuf[fl_utf2unicode((const unsigned char*)f, l, SHORT(wbuf))] = 0;
		
		l = strlen(mode);
		static wchar_t *wbuf1 = NULL;
		wbuf1 = (wchar_t*)realloc(wbuf1, sizeof(wchar_t) * (l+1));
		wbuf1[fl_utf2unicode((const unsigned char*)mode, l, SHORT(wbuf1))] = 0;

		return _wfopen(wbuf, wbuf1);
	} else {
		return fopen(fl_utf2mbcs(f), mode);
	}
#else
	return fopen(f, mode);
#endif
}

int fl_chmod(const char* f, int mode)
{
#if defined(_WIN32) && !defined(_WIN32_WCE)
    if (fl_is_nt4()) {
        int l = strlen(f);
        grow_wbuf(l);
        wbuf[fl_utf2unicode((const unsigned char*)f, l, SHORT(wbuf))] = 0;
        return _wchmod(wbuf, mode);
    } else {
        return _chmod(fl_utf2mbcs(f), mode);
    }
#else
    return chmod(f, mode);
#endif
}

int fl_access(const char* f, int mode)
{
#if defined(_WIN32) && !defined(_WIN32_WCE)
	if (fl_is_nt4()) {
		int l = strlen(f);
		grow_wbuf(l);
		wbuf[fl_utf2unicode((const unsigned char*)f, l, SHORT(wbuf))] = 0;
		return _waccess(wbuf, mode);
	} else {
		return _access(fl_utf2mbcs(f), mode);
	}
#else
	return access(f, mode);
#endif
}

int fl_stat(const char* f, struct stat *b)
{
#if defined(_WIN32) && !defined(_WIN32_WCE)
	if (fl_is_nt4()) {
		int l = strlen(f);
		grow_wbuf(l);
		wbuf[fl_utf2unicode((const unsigned char*)f, l, SHORT(wbuf))] = 0;
		return _wstat(wbuf, (struct _stat*)b);
	} 
	
	return _stat(fl_utf2mbcs(f), (struct _stat*)b);	
#else
	return stat(f, b);
#endif
}

char *fl_getcwd(char* b, int l)
{
#if defined(_WIN32) && !defined(_WIN32_WCE)
   /*	if (fl_is_nt4()) {

		grow_wbuf(l);
		wchar_t *ret = _wgetcwd(wbuf, l / 5);
		if (ret) {
				l = wcslen(wbuf);
				b[fl_unicode2utf(SHORT(wbuf), l, b)] = 0;
				return b;
		} else {
			return NULL;
		}
	} else
    */
    {
		char *ret = _getcwd(b, l / 5);
		if (ret) {
			int i;
			char *s;

			s = fl_mbcs2utf(b);
			l = strlen(s);
			for(i= 0; i < l; i++) b[i] = s[i];
			b[l] = 0;
			return b;
		} else {
			return NULL;
		}
	}
#else
	return getcwd(b, l);
#endif
}

int fl_unlink(const char* f)
{
#if defined(_WIN32) && !defined(_WIN32_WCE)
	if (fl_is_nt4()) {
		int l = strlen(f);
		grow_wbuf(l);
		wbuf[fl_utf2unicode((const unsigned char*)f, l, SHORT(wbuf))] = 0;
		return _wunlink(wbuf);
	} else {
		return _unlink(fl_utf2mbcs(f));
	}
#else
        return unlink(f);
#endif
}
