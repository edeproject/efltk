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

#ifndef _FL_REDIO_BUTTON_H_
#define _FL_REDIO_BUTTON_H_

#include "Fl_Check_Button.h"

class FL_API Fl_Radio_Button : public Fl_Check_Button {
public:
    static Fl_Named_Style* default_style;
    Fl_Radio_Button(int x, int y, int w, int h, const char *l=0);
};

#endif
