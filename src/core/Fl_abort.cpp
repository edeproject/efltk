//
// "$Id$"
//
// Warning/error message code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

// This method is in it's own source file so that stdlib and stdio
// do not need to be included in Fl.C:
// You can also override this by redefining all of these.

#include <config.h>

#include <efltk/Fl.h>

#include <efltk/vsnprintf.h>
#include <stdlib.h>

#ifndef _WIN32

static void warning(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputc('\n', stderr);
    fflush(stderr);
}


static void error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputc('\n', stderr);
    // done by abort() fflush(stderr);
    exit(1);
}


#elif defined(_WIN32_WCE)

#include <wince.h>
#include <efltk/fl_utf8.h>

static void warning(const char *format, ...)
{
    va_list args;
    char buf[1024];
	static wchar_t wbuf[1024];
    va_start(args, format);
    vsnprintf(buf, 1024, format, args);
    va_end(args);
    fl_utf2unicode((const unsigned char*)buf,strlen(buf) * sizeof(wchar_t),wbuf);
	MessageBox(0,wbuf,L"Warning",MB_ICONEXCLAMATION|MB_OK);
}


static void error(const char *format, ...)
{
    va_list args;
    char buf[1024];
	static wchar_t wbuf[1024];
    va_start(args, format);
    vsnprintf(buf, 1024, format, args);
    va_end(args);
    fl_utf2unicode((const unsigned char*)buf,strlen(buf) * sizeof(wchar_t),wbuf);
    MessageBox(0,wbuf,L"Error",MB_ICONSTOP);
    exit(1);
}


#else

#include <windows.h>
#include <efltk/fl_utf8.h>

extern char *fl_utf82locale(const char *s, UINT codepage=0);

static void warning(const char *format, ...)
{
    va_list args;
    char buf[1024];
    va_start(args, format);
    vsnprintf(buf, 1024, format, args);
    va_end(args);

	TCHAR *text;
#ifdef UNICODE
    int len = fl_utf_nb_char((unsigned char*)buf, strlen(buf));
    text = (TCHAR*)malloc((len + 1) * sizeof(TCHAR));
    fl_utf2unicode((unsigned char*)buf, len, (unsigned short*)text);
	text[len] = 0;
#else
	text = fl_utf82locale(buf);
#endif

    MessageBox(0, text, TEXT("Warning"), MB_ICONEXCLAMATION|MB_OK);

#ifdef UNICODE
	free(text);
#endif
}


static void error(const char *format, ...)
{
    va_list args;
    char buf[1024];
    va_start(args, format);
    vsnprintf(buf, 1024, format, args);
    va_end(args);

	TCHAR *text;
#ifdef UNICODE
    int len = fl_utf_nb_char((unsigned char*)buf, strlen(buf));
    text = (TCHAR*)malloc((len + 1) * sizeof(TCHAR));
    fl_utf2unicode((unsigned char*)buf, len, (unsigned short*)text);
	text[len] = 0;
#else
	text = fl_utf82locale(buf);
#endif

    
	MessageBox(0, text, TEXT("Error"), MB_ICONSTOP|MB_SYSTEMMODAL);

#ifdef UNICODE
	free(text);
#endif

    exit(1);
}
#endif

void (*Fl::warning)(const char* format, ...) = ::warning;
void (*Fl::error)(const char* format, ...) = ::error;
void (*Fl::fatal)(const char* format, ...) = ::error;

//
// End of "$Id$".
//
