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

#ifndef _FL_CHECK_BUTTON_H_
#define _FL_CHECK_BUTTON_H_

#include "Fl_Button.h"

/**
 * Buttons generate callbacks when they are clicked by the user. 
 * You control exactly when and how by changing the values for type() and when(). 
 *
 * The Fl_Check_Button subclass display the "on" state by turning on a light, rather than drawing pushed in. 
 */
class FL_API Fl_Check_Button : public Fl_Button {
public:
    static Fl_Named_Style* default_style;

    /** The traditional constructor creates the check button using the position, size, and label. */
    Fl_Check_Button(int x,int y,int w,int h,const char *l = 0);

    /** The new style constructor creates the check button using the label, size, alignment, and label_width. */
    Fl_Check_Button(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP);

    virtual void preferred_size(int& w, int& h) const;
    virtual void draw();
};

#endif
