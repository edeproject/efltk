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

#ifndef _FL_LINE_DIAL_H_
#define _FL_LINE_DIAL_H_

#include "Fl_Dial.h"

/** Fl_Line_Dial */
class Fl_Line_Dial : public Fl_Dial {
public:
    Fl_Line_Dial(int x,int y,int w,int h, const char *l = 0) : Fl_Dial(x,y,w,h,l) { type(LINE); }
};

#endif
