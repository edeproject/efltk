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

#ifndef __FL_SIZE_H__
#define __FL_SIZE_H__

/** Fl_Size */
class FL_API Fl_Size
{
	int width_, height_;
public:
	Fl_Size() : width_(0), height_(0) {}
	Fl_Size(int w, int h) : width_(w), height_(h) {}

	Fl_Size &operator=( const Fl_Size &s ) { width(s.w()); height(s.h()); return *this; }

	int width() const { return width_; }
	int w() const { return width_; }

	int h() const { return height_; }	
	int height() const { return height_; }

	void width(int w) { width_ = w; }
	void height(int h) { height_ = h; }
};

#endif
