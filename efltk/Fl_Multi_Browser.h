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

#ifndef _FL_MULTI_BROWSER_H_
#define _FL_MULTI_BROWSER_H_

#include "Fl_Browser.h"

// This class is entirely inline.  If that changes, add FL_API to its declaration

/** Fl_Multi_Browser */
class Fl_Multi_Browser : public Fl_Browser {
public:

    /** Creates new multi browser widget using the given position, size, and label. */
    Fl_Multi_Browser(int x,int y,int w,int h,const char *l=0) 
    : Fl_Browser(x,y,w,h,l) { type(MULTI); }

    /** Creates new multi browser widget using the label, size, alignment, and label_width. */
    Fl_Multi_Browser(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100)
    : Fl_Browser(l,layout_size,layout_al,label_w) { type(MULTI); }

};

#endif
