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

#ifndef _FL_GL_H_
#define _FL_GL_H_

//
// You must include this instead of GL/gl.h to get the Microsoft
// APIENTRY stuff included (from <windows.h>) prior to the OpenGL
// header files.
//
// This file also provides "missing" OpenGL functions, and
// gl_start() and gl_finish() to allow OpenGL to be used in any window
//

#include "Fl_Color.h"
#include "Fl_Flags.h"
#include "Fl_Font.h"

#ifdef _WIN32
# include <windows.h>
#endif
#ifndef APIENTRY
# if defined(__CYGWIN__)
#  define APIENTRY __attribute__ ((__stdcall__))
# else
#  define APIENTRY
# endif
#endif

#ifdef __APPLE__
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>
#endif

FL_API void gl_start();
FL_API void gl_finish();

FL_API void gl_color(Fl_Color);

FL_API void gl_rect(int x,int y,int w,int h);
inline void gl_rectf(int x,int y,int w,int h) {glRecti(x,y,x+w,y+h); }

FL_API void gl_font(Fl_Font f, float size);
FL_API float gl_height();
FL_API float gl_descent();
FL_API float gl_width(const char *);
FL_API float gl_width(const char *, int n);

FL_API void gl_draw(const char*);
FL_API void gl_draw(const char*, int n);
FL_API void gl_draw(const char*, float x, float y, float z = 0);
FL_API void gl_draw(const char*, int n, float x, float y, float z = 0);

FL_API void gl_draw_image(const uchar *, int x,int y,int w,int h, int d=3, int ld=0);

#endif
