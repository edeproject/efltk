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

#ifndef _FL_VSNPRINTF_H_
#define _FL_VSNPRINTF_H_

/*
 * vsnprintf() function for the Fast Light Tool Kit (FLTK).
 *
 * Include this file instead of stdio.h to get the snprintf and vsnprintf
 * functions on systems that lack it (pretty much everything except glibc
 * systems). PLEASE FIX FOR SYSTEMS THAT HAVE THESE FUNCTIONS!
 *
 * KNOWN BUGS:
 * Field width & Precision is ignored for %%, %c, and %s.
 *
 * A malicious user who manages to create a %-fmt string that prints
 * more than 99 characters can still overflow the temporary buffer.
 * For instance %110f will overflow.
 *
 * Only handles formats that are both documented in the glibc man page
 * for printf and also handled by your system's sprintf().
 */

#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
# define vsnprintf _vsnprintf
# define snprintf _snprintf

#elif defined(__linux)
/* linux has vsnprintf */

#elif _COMPILER_VERSION>=730
/* newer SGI compilers have vsnprintf */

#else
/* all other machines need our emulation function: */

# define need_fl_vsnprintf 1 /* make the function compile */

# ifdef __cplusplus
extern "C" {
# endif

# include <sys/types.h>
  int fl_vsnprintf(char* str, size_t size, const char* fmt, va_list ap);
  int fl_snprintf(char* str, size_t size, const char* fmt, ...);
# define vsnprintf fl_vsnprintf
# define snprintf fl_snprintf

# ifdef __cplusplus
};
# endif

#endif

#endif
