//
// "$Id$"
//
// Unicode to UTF-8 conversion functions.
//
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
//

#include <config.h>

#ifdef HAVE_XUTF8
#include "fl_utf8_x.h"
#include "../../headers/spacing.h"
#include <efltk/fl_utf8.h>
#include <string.h>

/*** NOTE : all functions are LIMITED to 24 bits Unicode values !!! ***/
/***        but only 16 bits are realy used under Linux and win32  ***/

/*** converts the first char UTF-8 string to an Unicode value ***/
/*** returns the byte length of the converted UTF-8 char **/
/*** returns -1 if the UTF-8 string is not valid ***/
int
fl_utf2ucs(const unsigned char     *buf,
	   int                     len,
	   unsigned int            *ucs)
{
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
}


/*** converts an Unicode value to an UTF-8 string  ***/
/*** NOTE : the buffer (buf) must be at least 5 bytes long !!!  ***/
int
fl_ucs2utf(unsigned int    ucs,
	   char        *buf)
{
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
}


/*** returns the byte length of the first UTF-8 char ***/
/*** (returns -1 if not valid) ***/
int
fl_utflen(const unsigned char     *buf,
	  int                     len)
{
    unsigned int ucs;
    return fl_utf2ucs(buf, len, &ucs);
}


/**** returns the number of Unicode chars in the UTF-8 string ***/
int
fl_utf_nb_char(const unsigned char     *buf,
	       int             len)
{
    int i = 0;
    int nbc = 0;
    while (i < len)
    {
        int cl = fl_utflen(buf + i, len - i);
        if (cl < 1) cl = 1;
        nbc++;
        i += cl;
    }
    return nbc;
}


/*
 * compare only the first n bytes
 * return 0 if the strings are equal;
 * return 1 if s1 is greater than s2
 * return -1 if s1 is less than s2
 */
int fl_utf_strncasecmp(const char *s1, const char *s2, int n)
{
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
        res = XUtf8Tolower(u1) - XUtf8Tolower(u2);
        if (res != 0) return res;
        if (l1 < 1)
        {
            i += 1;
        }
        else
        {
            i += l1;
        }
    }
    return 0;
}


/*
 * return 0 if the strings are equal;
 * return 1 if s1 is greater than s2
 * return -1 if s1 is less than s2
 */
int fl_utf_strcasecmp(const char *s1, const char *s2)
{
    int s1_l = strlen(s1);
    int s2_l = strlen(s2);

    if (s1_l < s2_l)
    {
        return -1;
    }
    else if (s1_l > s2_l)
    {
        return 1;
    }
    return fl_utf_strncasecmp(s1, s2, s1_l);
}


/*
 * return the Unicode lower case value of ucs
 */
int fl_tolower(unsigned int ucs)
{
    return XUtf8Tolower(ucs);
}


/*
 * return the Unicode upper case value of ucs
 */
int fl_toupper(unsigned int ucs)
{
    return XUtf8Toupper(ucs);
}


/*
 * converts the str string to the lower case equivalent into buf.
 * Warning: to be safe buf length must be at least 3 * len
 */
int fl_utf_tolower(const unsigned char *str, int len, char *buf)
{
    int i;
    int l = 0;
    for (i = 0; i < len;)
    {
        int l1, l2;
        unsigned int u1;

        l1 = fl_utf2ucs((unsigned char*)str + i, len - i, &u1);
        l2 = fl_ucs2utf((unsigned int) XUtf8Tolower(u1), buf + l);
        if (l1 < 1)
        {
            i += 1;
        }
        else
        {
            i += l1;
        }
        if (l2 < 1)
        {
            l += 1;
        }
        else
        {
            l += l2;
        }

    }
    return l;
}


/*
 * converts the str string to the upper case equivalent into buf.
 * Warning: to be safe buf length must be at least 3 * len
 */
int fl_utf_toupper(const unsigned char *str, int len, char *buf)
{
    int i;
    int l = 0;
    for (i = 0; i < len;)
    {
        int l1, l2;
        unsigned int u1;

        l1 = fl_utf2ucs((unsigned char*)str + i, len - i, &u1);
        l2 = fl_ucs2utf((unsigned int) XUtf8Toupper(u1), buf + l);
        if (l1 < 1)
        {
            i += 1;
        }
        else
        {
            i += l1;
        }
        if (l2 < 1)
        {
            l += 1;
        }
        else
        {
            l += l2;
        }
    }
    return l;
}


/*
 * converts a UTF-8 str to unicode
 * Warning: buf must a least len long
 */
int fl_utf2unicode(const unsigned char *str, int len, unsigned short *buf)
{
    int i;
    int l = 0;
    for (i = 0; i < len;)
    {
        unsigned int u1;
        int l1;

        l1 = fl_utf2ucs((unsigned char*)str + i, len - i, &u1);
        buf[l] = (unsigned short) u1;
        if (l1 < 1)
        {
            i += 1;
        }
        else
        {
            i += l1;
        }
        l++;

    }
    return l;
}


/*
 * convert Unicode str to UTF-8
 * Warning: buf must be at least 3 * len long
 */
int fl_unicode2utf(unsigned short *str, int len, char *buf)
{
    int i;
    int l = 0;
    for (i = 0; i < len; i++)
    {
        int l1;
        l1 = fl_ucs2utf((unsigned int) str[i], buf + l);
        if (l1 < 1)
        {
            l += 1;
        }
        else
        {
            l += l1;
        }

    }
    return l;
}


/*
 * convert UTF-8 str to latin1
 * Warning: buf must be at least len long
 */
int fl_utf2latin1(const unsigned char *str, int len, char *buf)
{
    int i;
    int l = 0;
    for (i = 0; i < len;)
    {
        unsigned int u1;
        int l1;

        l1 = fl_utf2ucs((unsigned char*)str + i, len - i, &u1);
        if (u1 > 0xFF) u1 = '?';
        buf[l] = (char) u1;
        if (l1 < 1)
        {
            i += 1;
        }
        else
        {
            i += l1;
        }
        l++;

    }
    return l;
}


/*
 * convert latin1 str to UTF-8
 * Warning: buf must be at least 2 * len long
 */
int fl_latin12utf(const unsigned char *str, int len, char *buf)
{
    int i;
    int l = 0;
    for (i = 0; i < len; i++)
    {
        int l1;
        l1 = fl_ucs2utf((unsigned int) str[i], buf + l);
        if (l1 < 1)
        {
            l += 1;
        }
        else
        {
            l += l1;
        }

    }
    return l;
}


unsigned int fl_nonspacing(unsigned int ucs)
{
    if (ucs <= 0x0361)
    {
        if (ucs >= 0x0300) return ucs_table_0300[ucs - 0x0300];
        return 0;
    }

    if (ucs <= 0x0486)
    {
        if (ucs >= 0x0483) return ucs_table_0483[ucs - 0x0483];
        return 0;
    }

    if (ucs <= 0x05C4)
    {
        if (ucs >= 0x0591) return ucs_table_0591[ucs - 0x0591];
        return 0;
    }

    if (ucs <= 0x06ED)
    {
        if (ucs >= 0x064B) return ucs_table_064B[ucs - 0x064B];
        return 0;
    }

    if (ucs <= 0x0D4D)
    {
        if (ucs >= 0x0901) return ucs_table_0901[ucs - 0x0901];
        return 0;
    }

    if (ucs <= 0x0FB9)
    {
        if (ucs >= 0x0E31) return ucs_table_0E31[ucs - 0x0E31];
        return 0;
    }

    if (ucs <= 0x20E1)
    {
        if (ucs >= 0x20D0) return ucs_table_20D0[ucs - 0x20D0];
        return 0;
    }

    if (ucs <= 0x309A)
    {
        if (ucs >= 0x302A) return ucs_table_302A[ucs - 0x302A];
        return 0;
    }

    if (ucs <= 0xFB1E)
    {
        if (ucs >= 0xFB1E) return ucs_table_FB1E[ucs - 0xFB1E];
        return 0;
    }

    if (ucs <= 0xFE23)
    {
        if (ucs >= 0xFE20) return ucs_table_FE20[ucs - 0xFE20];
        return 0;
    }

    return 0;
}

#else  

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int fl_ucs2utf(unsigned int ucs, char *buf)
{
        buf[0] = ucs & 0xFF;
        return 1;
}

int fl_utflen(const unsigned char *buf, int len)
{
	if (len < 1) return 0;
	return 1;
}

int fl_utf2ucs( const unsigned char *buf, int len, unsigned int *ucs)
{
	if (len < 1) return 0;
	*ucs = (unsigned int) buf[0];
	return 1;
}


#define fl_utf_strncasecmp strncasecmp
#define fl_tolower tolower
//#define fl_rtl_draw fl_draw

// todo - rest of compatibility

#endif




//
// End of "$Id$".
//
