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

#ifndef _FL_MATH_H_
#define _FL_MATH_H_

//
// The purpose of this header file is to make math.h look the same as
// Unix on other operating systems.
//

/* maybe we should define this?  */
/* #define __NO_LONG_DOUBLE_MATH */

#include <math.h>

#ifdef _WIN32
// things missing from <math.h>:
# include <float.h>

# ifndef M_PI
#  define M_PI		3.14159265358979323846
#  define M_PI_2	1.57079632679489661923
#  define M_PI_4	0.78539816339744830962
#  define M_1_PI	0.31830988618379067154
#  define M_2_PI	0.63661977236758134308
#  define M_SQRT2	1.41421356237309504880
#  define M_SQRT1_2	0.70710678118654752440
# endif

# define rint(v)	floor((v)+.5)
# define copysign	_copysign
# define drand48()	((double)rand()/RAND_MAX)
# define srand48(n)	srand((n));

#endif

#ifdef __EMX__
# include <float.h>
#endif

#ifndef M_PI
# define M_PI          3.14159265358979323846
#endif

#define rintf(v)	floorf((v)+.5f)

#ifdef __alpha // powf is broken on alphas, at least in gcc
# define powf(a,b)	pow(a,b)
#endif
#ifdef _WIN32
# define expm1f(a)	expm1(a)
# define log1pf(a)	log1p(a)
#endif

#endif
