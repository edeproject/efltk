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

#ifndef _FL_TOOLTIP_H_
#define _FL_TOOLTIP_H_

#include "Fl.h"
#include "Fl_Widget.h"

class FL_API Fl_Tooltip {
    static Fl_Widget* widget;
public:
  static float delay() { return delay_; }
  static void delay(float f) { delay_ = f; }

  static bool enabled() { return enabled_; }
  static void enable(bool b = true) { enabled_ = b; }
  static void disable() { enabled_ = false; }

  static bool effects() { return effects_; }
  static void effects(bool v) { effects_ = v; }

  static int effect_type() { return effect_type_; }
  static void effect_type(int v) { effect_type_ = v; }

  typedef const char* (*Generator)(Fl_Widget*, void*);
  static void enter(Fl_Widget* w, int X, int Y, int W, int H, Generator, void* = 0);
  static void enter(Fl_Widget* w, int X, int Y, int W, int H, const char* t) { enter(w, X, Y, W, H, 0, (void*)t); }
  static void enter(Fl_Widget* w);
  static void exit();
  static Fl_Widget* current() {return widget;}
  static void current(Fl_Widget*);

  static Fl_Named_Style* default_style;
  static Fl_Font font()		{ return default_style->label_font; }
  static void font(Fl_Font i)	{ default_style->label_font = i; }
  static unsigned size()	{ return default_style->label_size; }
  static void size(unsigned s)	{ default_style->label_size = s; }
  static void color(Fl_Color c)	{ default_style->color = c; }
  static Fl_Color color()	{ return default_style->color; }
  static void textcolor(Fl_Color c) {default_style->label_color = c; }
  static Fl_Color textcolor()	{ return default_style->label_color; }
  static void boxtype(Fl_Boxtype b) {default_style->box = b; }
  static Fl_Boxtype boxtype()	{ return default_style->box; }

private:
  static float delay_;
  static bool enabled_, effects_;
  static int effect_type_;
  static void tooltip_timeout(void*);
};

#endif
