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

#ifndef __FL_POINT_H__
#define __FL_POINT_H__

/** Fl_Point */
class FL_API Fl_Point
{
	int x_, y_;
public:
	Fl_Point() : x_(0), y_(0) {}
	Fl_Point(int x, int y) : x_(x), y_(y) {}

	Fl_Point &operator=( const Fl_Point &p ) { x(p.x()); y(p.y()); return *this; }

	int x() const { return x_; }
	int y() const { return y_; }
	void x(int x) { x_ = x; }
	void y(int y) { y_ = y; }
};

#endif
