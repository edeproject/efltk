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

#ifndef _FL_STYLE_SET_H_
#define _FL_STYLE_SET_H_

#include "Fl_Style.h"

class FL_API Fl_Style_Set {
public:
    Fl_Style_Set();
    ~Fl_Style_Set();

    void make_current();

private:
    Fl_Named_Style* first_style;
    Fl_Theme theme;
    const char* scheme;
    Fl_Color background;
    void* reserved; // pointer to extra saved stuff
};

#endif
