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

#ifndef _FL_TILE_H_
#define _FL_TILE_H_

#include "Fl_Group.h"

/** Fl_Tile */
class FL_API Fl_Tile : public Fl_Group {
public:
    /** Creates new tile widget using the given position, size, and label string. */
    Fl_Tile(int X,int Y,int W,int H,const char*l=0) 
    : Fl_Group(X,Y,W,H,l) {}

    /** Creates new tile widget using the label, size, alignment, and label width. */
    Fl_Tile(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100)
    : Fl_Group(l,layout_size,layout_al,label_w) {}

    void position(int, int, int, int);

    virtual int handle(int);
    virtual void layout();
};

#endif
