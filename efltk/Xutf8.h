/*
 * "$Id$"
 *
 * X11 UTF-8 text drawing functions.
 *
 *      Copyright (c) 2000,2001 by O'ksi'D.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * O'KSI'D BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the O'ksi'D shall
 * not be used in advertising or otherwise to promote the sale, use or other
 * dealings in this Software without prior written authorization from O'ksi'D.
 *
 *
 *  Author: Jean-Marc Lienher ( http://oksid.ch )
 */


#ifndef _Xutf8_h
#define _Xutf8_h

#  ifdef __cplusplus
extern "C" {
#  endif

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xlocale.h>
#include <X11/Xutil.h>

typedef struct {
	int nb_font;
	char **font_name_list;
	int *encodings;
	XFontStruct **fonts;
	Font fid;
	int ascent;
	int descent;
	int *ranges;
} XUtf8FontStruct;

XUtf8FontStruct *
XCreateUtf8FontStruct (
	Display         *dpy, 
	const char      *base_font_name_list); 

void
XUtf8DrawString(
        Display         	*display,
        Drawable        	d,
        XUtf8FontStruct  *font_set,
        GC              	gc,
        int             	x,
        int             	y,
        const char      	*string,
        int             	num_bytes);

void
XUtf8DrawRtlString(
        Display         	*display,
        Drawable        	d,
        XUtf8FontStruct  *font_set,
        GC              	gc,
        int             	x,
        int             	y,
        const char      	*string,
        int             	num_bytes);

void
XUtf8DrawImageString(
        Display         *display,
        Drawable        d,
        XUtf8FontStruct         *font_set,
        GC              gc,
        int             x,
        int             y,
        const char      *string,
        int             num_bytes);

int
XUtf8TextWidth(
        XUtf8FontStruct  *font_set,
        const char      	*string,
        int             	num_bytes);
int 
XUtf8UcsWidth(
	XUtf8FontStruct  *font_set,
	unsigned int            ucs);
	
void
XFreeUtf8FontStruct(
        Display         	*dpy,
        XUtf8FontStruct 	*font_set);


int 
XConvertUtf8ToUcs( 
	const unsigned char 	*buf, 
	int 			len, 
	unsigned int 		*ucs);

int 
XConvertUcsToUtf8(
	unsigned int 		ucs, 
	char 			*buf);

int 
XUtf8CharByteLen(
	const unsigned char 	*buf, 
	int 			len);

int 
XCountUtf8Char(
	const unsigned char *buf, 
	int len);

int 
XFastConvertUtf8ToUcs( 
	const unsigned char 	*buf, 
	int 			len, 
	unsigned int 		*ucs);

long 
XKeysymToUcs(
	KeySym 	keysym);

int
XUtf8LookupString(
    XIC                 ic,
    XKeyPressedEvent*   event,
    char*               buffer_return,
    int                 bytes_buffer,
    KeySym*             keysym,
    Status*             status_return);

unsigned short 
XUtf8IsNonSpacing(
	unsigned int ucs);

unsigned short
XUtf8IsRightToLeft(
        unsigned int ucs);


int 
XUtf8Tolower(
        int ucs);

int 
XUtf8Toupper(
        int ucs);


#  ifdef __cplusplus
}
#  endif

#endif

/*
 *  End of "$Id$".
 */ 
