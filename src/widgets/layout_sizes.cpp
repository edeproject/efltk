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
 * Author : Alexey Parshin
 * Email  : alexey@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#include "layout_sizes.h"

int widget_layout_width(Fl_Widget *w) 
{
	if (!(w->align() & FL_ALIGN_INSIDE)) {
		int label_w = w->label_width();
		if (label_w < 0) label_w = 0;
		if (w->align() & (FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) 
			return max(label_w, w->w());
		return w->w() + label_w;
	}
	return w->w();
}

int widget_layout_height(Fl_Widget *w) 
{
	if (!(w->align() & FL_ALIGN_INSIDE)) {
		int label_h = w->label_height();
		if (label_h < 0) label_h = 0;		
		if (w->align() & (FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) 
			return max(label_h, w->h());
		return w->h() + label_h;
	}
	return w->h();
}

void widget_layout_position(Fl_Widget *w,int x,int y,int& wx,int& wy) {
	int label_w = w->label_width();
	if (label_w < 0) label_w = 0;
	if (w->align() & (FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) {
		wx = x;
		wy = y;
		if (!(w->align() & FL_ALIGN_INSIDE)) {
			if (w->align() & FL_ALIGN_TOP)
				wy = y + w->label_height();
		}
	} else {
		wx = x;
		wy = y;
		if (!(w->align() & FL_ALIGN_INSIDE)) {
			if (w->align() & FL_ALIGN_LEFT)
				wx = x + label_w;
		}
	}
}

