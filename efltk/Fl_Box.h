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

#ifndef _FL_BOX_H_
#define _FL_BOX_H_

#include "Fl_Widget.h"

/**
 * This widget is the same as an plain Fl_Widget except if the box is set to FL_NO_BOX it is completely invisible and attemps to draw it do absolutely nothing. 
 * This can be used as the resizable() of a group or window to get more complex resize effects. 
 *
 * You can also set the box to provide decorations, but you can use the plain Fl_Widget for that, too.
 */ 
class FL_API Fl_Box : public Fl_Widget {
public:
    static Fl_Named_Style* default_style;

    /**
     * The first constructor sets box() to FL_NO_BOX, which means it is invisible. 
     * However such widgets are useful as placeholders or Fl_Group::resizable() values. 
     * To change the box to something visible, use box(n). 
     */
    Fl_Box(int x, int y, int w, int h, const char *label=0);
   /**
     * By default, box label has the label inside
    */
    Fl_Box(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=-1);

    virtual void draw();
};

#endif
