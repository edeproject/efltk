//
// "$Id$"
//
// Copyright 1998-2000 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#ifndef Fl_Browser_H
#define Fl_Browser_H

#include "Fl_Menu_.h"
#include "Fl_Scrollbar.h"

class FL_API Fl_Browser : public Fl_Menu_ {
  Fl_End endgroup;

public:

  int handle(int);
  void layout();
  void draw();

  Fl_Browser(int X,int Y,int W,int H,const char*l=0);
  static Fl_Named_Style* default_style;
  ~Fl_Browser();

  enum { // values for type()
    NORMAL = 0,
    MULTI = 1
  };

  int width() const {return width_;}
  int height() const {return height_;}
  int box_width() const {return W;}
  int box_height() const {return H;}
  int xposition() const {return xposition_;}
  void xposition(int);
  int yposition() const {return yposition_;}
  void yposition(int);
  bool indented() const {return indented_;}
  void indented(bool v) {indented_ = v;}

  Fl_Scrollbar scrollbar;
  Fl_Scrollbar hscrollbar;

  Fl_Widget* goto_top();
  Fl_Widget* goto_focus() {return goto_mark(FOCUS);}
  Fl_Widget* goto_position(int y);
  Fl_Widget* goto_index(const int* indexes, int level);
  Fl_Widget* goto_index(int);
  Fl_Widget* goto_index(int,int,int=-1,int=-1,int=-1);
  Fl_Widget* next();
  Fl_Widget* next_visible();
  Fl_Widget* previous_visible();
  bool item_is_visible() const;
  bool item_is_parent() const;

  bool set_focus();
  bool set_item_selected(bool value = true, int do_callback = 0);
  bool select_only_this(int do_callback = 0);
  bool deselect(int do_callback = 0);
  enum linepos { NOSCROLL, TOP, MIDDLE, BOTTOM };
  bool make_item_visible(linepos = NOSCROLL);
  void damage_item() {damage_item(HERE);}
  bool set_item_opened(bool);
  bool set_item_visible(bool);

  int current_level() const {return item_level[HERE];}
  const int* current_index() const {return item_index[HERE];}
  int current_position() const {return item_position[HERE];}

  int focus_level() const {return item_level[FOCUS];}
  const int* focus_index() const {return item_index[FOCUS];}
  int focus_position() const {return item_position[FOCUS];}
  void value(int v) {goto_index(v); set_focus();}
  int value() const {return focus_index()[0];}

  // Maybe these should be moved to base Fl_Menu_ class:
  char format_char() const {return format_char_;}
  void format_char(char c) {format_char_ = c;}
  const int *column_widths() const { return column_widths_; }
  void column_widths(const int *pWidths)  { column_widths_ = pWidths; }

  // Convienence functions for flat browsers:
  bool select(int line, bool value = true);
  bool selected(int line);
  int topline() const {return item_index[FIRST_VISIBLE][0];}
  void topline(int line) {goto_index(line); make_item_visible(TOP);}
  void bottomline(int line) {goto_index(line); make_item_visible(BOTTOM);}
  void middleline(int line) {goto_index(line); make_item_visible();}
  bool displayed(int line);
  bool display(int line, bool value = true);

private:

  bool indented_;
  char format_char_;
  const int *column_widths_;
  int xposition_, yposition_;
  int width_, height_;
  int scrolldx, scrolldy;
  static void hscrollbar_cb(Fl_Widget*, void*);
  static void scrollbar_cb(Fl_Widget*, void*);
  void draw_item();
  void draw_clip(int,int,int,int);
  static void draw_clip_cb(void*,int,int,int,int);
  int X,Y,W,H; // bounding box area

  int multi() const {return type()&MULTI;}

  // Marks serve as "indexes" into the hierarchial browser. We probably
  // need to make some sort of public interface but I have not figured
  // it out completely.
  enum { // predefined marks
    HERE = 0, // current item, the one moved by all the calls
    FOCUS,
    FIRST_VISIBLE,
    REDRAW_0,
    REDRAW_1,
    TEMP,
    NUMMARKS
  };
  Fl_Widget* goto_mark(int mark); // set HERE to mark
  Fl_Widget* goto_visible_focus(); // set HERE to focus if visible
  void set_mark(int dest, int mark); // set dest to mark
  int compare_marks(int mark1, int mark2); // returns >0 if mark1 after mark2
  bool at_mark(int mark) { return !compare_marks(HERE,mark); }
  void unset_mark(int mark);  // makes mark have illegal value
  bool is_set(int mark);  // false if unset_mark was called
  void damage_item(int mark); // make this item redraw

  int siblings; // # of children of parent of HERE item

  // For each mark:
  unsigned char item_level[NUMMARKS]; // depth in hierarchy of the item
  unsigned char open_level[NUMMARKS]; // depth of highest closed parent
  int item_position[NUMMARKS]; // distance in pixels from top of browser
  int* item_index[NUMMARKS]; // indexes at each level of hierarchy
  int levels; // maximum depth of all items encountered so far
  void set_level(int); // increases levels by reallocating the arrays

};

#ifndef FLTK_2
#define FL_NORMAL_BROWSER Fl_Browser::NORMAL
#define FL_MULTI_BROWSER  Fl_Browser::MULTI
#define FL_SELECT_BROWSER Fl_Browser::NORMAL
#define FL_HOLD_BROWSER   Fl_Browser::NORMAL
#endif

#endif

//
// End of "$Id$".
//
