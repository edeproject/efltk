//
// "$Id$"
//
// Group header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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

#ifndef Fl_Group_H
#define Fl_Group_H

#ifndef Fl_Widget_H
#include "Fl_Widget.h"
#endif

#include "Fl_Data_Source.h"
#include "Fl_Widget_List.h"

class FL_API Fl_Group : public Fl_Widget {
public:

  int children() const { return array_.size(); }
  Fl_Widget* child(int n) const { return array_[n]; }
  Fl_Widget_List &array() { return array_; }

  void draw();
  void draw_group_box() const;
  void layout();
  int handle(int);

  void begin() {current_ = this;}
  void end() {current_ = (Fl_Group*)parent();}
  static Fl_Group *current() {return current_;}
  static void current(Fl_Group *g) {current_ = g;}

  int find(const Fl_Widget*) const;
  int find(const Fl_Widget& o) const {return find(&o);}

  Fl_Group(int,int,int,int, const char * = 0);
  virtual ~Fl_Group();
  void add(Fl_Widget&);
  void add(Fl_Widget* o) {add(*o);}
  void insert(Fl_Widget&, int index);
  void insert(Fl_Widget& o, Fl_Widget* before) {insert(o,find(before));}
  void remove(int index);
  void remove(Fl_Widget& o) {remove(find(o));}
  void remove(Fl_Widget* o) {remove(find(*o));}
  void replace(int index, Fl_Widget&);
  void replace(Fl_Widget& old, Fl_Widget& o) {replace(find(old),o);}
  void clear();

  void resizable(Fl_Widget& o) {resizable_ = &o;}
  void resizable(Fl_Widget* o) {resizable_ = o;}
  Fl_Widget* resizable() const {return resizable_;}
  void add_resizable(Fl_Widget& o) {resizable_ = &o; add(o);}
  void init_sizes();

  void focus(int i) {focus_ = i;}
  void focus(Fl_Widget* w) {focus(find(w));}
  int focus() const {return focus_;}
  static int navigation_key();

  // data source support methods
  void data_source(Fl_Data_Source *ds);
  Fl_Data_Source* data_source() const { return data_source_; }
  bool load();
  bool save();

protected:

  void draw_child(Fl_Widget&) const;
  void update_child(Fl_Widget&) const;
  void draw_outside_label(Fl_Widget&) const ;
  int* sizes();

private:

    Fl_Widget_List array_;
    int focus_;

    Fl_Widget* resizable_;
    int *sizes_; // remembered initial sizes of children

    Fl_Data_Source* data_source_;

    static Fl_Group *current_;
};

// This dummy class can be used in constructors to set the parent
// group to any desired value before creating child widget instances.
class FL_API Fl_End {
public:
  Fl_End() {Fl_Group::current()->end();}
  Fl_End(Fl_Group* g) {Fl_Group::current(g);}
};

#endif

//
// End of "$Id$".
//
