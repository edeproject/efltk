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

#ifndef _FL_LOCALE_H_
#define _FL_LOCALE_H_

#include <locale.h>

#include "Fl.h"
#include "Fl_Translator.h"

# define _(String) Fl_Translator::tr(String)
# define N_(String) (String)

// Backward compatibilty
#define fl_init_locale_support(app, dir) Fl::init_locale(app, dir)

#endif
