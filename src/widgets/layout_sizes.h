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

#ifndef __LAYOUT_SIZE_H__
#define __LAYOUT_SIZE_H__

#include <efltk/Fl_Widget.h>

int widget_layout_width(const Fl_Widget *w,int pref_w=-1);
int widget_layout_height(const Fl_Widget *w,int pref_h=-1);
bool widget_layout_resize(Fl_Widget *widget,int x,int y,int& w,int& h);
void widget_layout_position(const Fl_Widget *w,int x,int y,int& wx,int& wy);
void widget_layout_size(const Fl_Widget *w,int ow,int oh,int& nw,int& nh);

#endif
