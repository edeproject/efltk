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

#ifndef __FL_RECT_H__
#define __FL_RECT_H__

#include "Fl_Point.h"

/** Fl_Rect */
class FL_API Fl_Rect
{
	int x_, y_, width_, height_;
public:
	Fl_Rect() : x_(0), y_(0), width_(0), height_(0) {}
	Fl_Rect(int x, int y, int w, int h) : x_(x), y_(y), width_(w), height_(h) {}

	Fl_Rect &operator=( const Fl_Rect &r ) { set(r.x(), r.y(), r.w(), r.h()); return *this; }

	bool pos_in_rect(int xs, int ys) const {
		if( xs > x_  && xs < (x_ + width_) && ys > y_  && ys < (y_ + height_) ) {
			return true;
		}
		return false;
	}
	bool posInRect(int x, int y) const { return pos_in_rect(x,y); }

	bool pos_in_rect(Fl_Point p) const {
		if( p.x() > x_  && p.x() < (x_ + width_) && p.y() > y_  && p.y() < (y_ + height_) ) {
			return true;
		}
		return false;
	}
	bool posInRect(Fl_Point p) const { return pos_in_rect(p); }

	int x() const { return x_; }
	int y() const { return y_; }

	int w() const { return width(); }
	int width() const { return width_; }

	int h() const { return height(); }
	int height() const { return height_; }

	int left() const { return x(); }
	int right() const { return x()+w(); }
	int top() const { return y(); }
	int bottom() const { return y()+h(); }

	void x(int x) { x_ = x; }
	void y(int y) { y_ = y; }
	void w(int w) { width_ = w; }
	void h(int h) { height_ = h; }

	void set(int x, int y, int w, int h) { x_=x; y_=y; width_=w; height_=h; }
};

#endif
