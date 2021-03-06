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

int widget_layout_width(const Fl_Widget *w,int pref_w)
{
	if (pref_w < 0) pref_w = w->w();
	return pref_w;
}

int widget_layout_height(const Fl_Widget *w,int pref_h)
{
	if (pref_h < 0) pref_h = w->h();
	return pref_h;
}

void widget_layout_position(const Fl_Widget *w,int x,int y,int& wx,int& wy) {
    wx = x;
	wy = y;
}

// similar to widget_layout_position: finds the width and height in the layout rect
void widget_layout_size(const Fl_Widget *w,int ow,int oh,int& nw,int& nh) {
    nw = ow;
    nh = oh;
    if (nw < 0) nw = 0;
    if (nh < 0) nh = 0;
}

// Takes widget position (x,y) and layout (w,h) - including label if needed.
bool widget_layout_resize(Fl_Widget *o,int x,int y,int& w,int& h) 
{
	int new_w = w;
	int new_h = h;

	// Find out if widget wants to take it
	o->preferred_size(new_w, new_h);

	int new_layout_width = widget_layout_width(o,new_w);
	int new_layout_height = widget_layout_height(o,new_h);

	// finds the widget position inside layout rect
	int new_x, new_y;
	widget_layout_position(o,x,y,new_x,new_y);
	/*	
	switch (o->layout_align()) {
		default: 
			o->resize(new_x, new_y, new_w, new_h);
			break;

		case FL_ALIGN_LEFT:
			if (!o->visible()) break;

			pref_w = o->w();
			pref_h = hh;

			if(!(o->align() & FL_ALIGN_INSIDE) && o->align()&(FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) {
				pref_h -= o->label_height();
			}

			o->preferred_size(pref_w, pref_h);

			total_w = widget_total_width(o, pref_w);

			if(!(o->align() & FL_ALIGN_INSIDE) && o->align()&(FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) {
				label_w = o->label_width();
				if(label_w<0) label_w=0;
			}					

			widget_position(o, xx, yy, pref_x, pref_y);

			o->resize(pref_x, pref_y, pref_w, pref_h);
			xx += total_w + offset * 2;
			ww -= total_w + offset * 2;
			break;

		case FL_ALIGN_RIGHT:
			if(!o->visible()) break;

			pref_w = o->w();
			pref_h = hh;

			if(!(o->align() & FL_ALIGN_INSIDE) && o->align()&(FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) {
				pref_h -= o->label_height();
			}

			o->preferred_size(pref_w, pref_h);

			total_w = widget_total_width(o, pref_w);					

			if(!(o->align() & FL_ALIGN_INSIDE) && o->align()&(FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) {
				label_w = o->label_width();
				if(label_w<0) label_w=0;
			}

			widget_position(o, xx+ww-total_w, yy, pref_x, pref_y);

			o->resize(pref_x, pref_y, pref_w, pref_h);

			ww -= total_w + offset * 2;
			break;

		case FL_ALIGN_TOP:
			if (!o->visible()) break;

			pref_w = ww;
			pref_h = o->h();

			if(!(o->align() & FL_ALIGN_INSIDE) && o->align()&(FL_ALIGN_RIGHT|FL_ALIGN_LEFT)) {
				label_w = o->label_width();
				if (label_w < 0) label_w = 0;
				pref_w -= label_w;
			}

			o->preferred_size(pref_w, pref_h);

			total_h = widget_total_height(o, pref_h);					

			widget_position(o, xx, yy, pref_x, pref_y);

			if(!(o->align() & FL_ALIGN_INSIDE) && o->align()&(FL_ALIGN_RIGHT|FL_ALIGN_LEFT)) {
				int label_h = o->label_height();
				if (label_h < 0) label_h = 0;
			}

			o->resize(pref_x, pref_y, pref_w, pref_h);

			yy += total_h + offset * 2;
			hh -= total_h + offset * 2;
			break;

		case FL_ALIGN_BOTTOM:
			if(!o->visible()) break;

			pref_w = ww;
			pref_h = o->h();

			if(!(o->align() & FL_ALIGN_INSIDE) && o->align()&(FL_ALIGN_RIGHT|FL_ALIGN_LEFT)) {
				label_w = o->label_width();
				if (label_w < 0) label_w = 0;
				pref_w -= label_w;
			}

			o->preferred_size(pref_w,pref_h);

			total_h = widget_total_height(o, pref_h);
			widget_position(o, xx, yy+hh-total_h, pref_x, pref_y);

			if(!(o->align() & FL_ALIGN_INSIDE) && o->align()&(FL_ALIGN_RIGHT|FL_ALIGN_LEFT)) {
				int label_h = o->label_height();
				if (label_h < 0) label_h = 0;
			}

			o->resize(pref_x, pref_y, pref_w, pref_h);

			hh -= total_h + offset * 2;
			break;

		case FL_ALIGN_CLIENT:
			if(!o->visible()) break;
			client = o;
			break;

		default:
			break;
	}
	*/
	return (new_layout_width == w && new_layout_height == h);
}
