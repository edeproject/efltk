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
 * Author : Szasz Pal
 * Email  : space2@atlastelecom.ro
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_SPLIT_H_
#define _FL_SPLIT_H_

#include "Fl_Box.h"

//****************************************************************************
/** \class Fl_Split
\brief A simple splitter widget.

This widgets is intended to be used, when you're window has a client
area and some panels at left/right/top/bottom, and you wan't
them to be resizable.

This widgets works both with the new style layouting, and the old
style widget positioning.

In the first case you have to give the constructor the panel
widget. The Fl_Split widget will than attach itself to that widget,
making it resizable.

In the second case you position this widget as it would be a normal
one, giving it's x, y coordinates, it's width and height.
When it's dragged, it creates a list with all neighbouring widgets
(so you must place the other widgets precisely), and changes
the their size.

In both cases Fl_Split will block the resizing, when a neighbouring
widget (or the attached, or client widget) will have 0 dimensions.
*****************************************************************************/
class Fl_Split: public Fl_Widget
{
	Fl_Widget * ref_;
    int dir_;
public:
	static Fl_Named_Style* default_style;

	/// This constructor should be used, when you use the old style widget positioning
    Fl_Split(int x, int y, int w, int h, const char *l=0);

    /**
     * This constructor should be use with the new layout design
     * @param _ref_ the widget to attach the Fl_Split to
     * @param layout_size the width or height of the splitter
     * \note The layout_align of the splitter will be identicall
     * with the layout_align of _ref_
     */
     Fl_Split(Fl_Widget * _ref_, int layout_size=5);
     
	 virtual int handle(int ev);
};

#endif
