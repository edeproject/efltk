//
// "$Id$"
//
// Widget type code for the Fast Light Tool Kit (FLTK).
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

// Each object created by Fluid is a subclass of Fl_Type. The majority
// of these are going to describe Fl_Widgets, so you will see the word
// "widget" used a lot instead of Fl_Type. But there are also functions
// and lines of code and anything else that can go into the browser.
//
// A hierarchial list of all Fl_Types is managed. The Widget Browser
// is the display in the main window of this list. Most of this code
// is concerned with drawing and updating the widget browser, with
// keeping the list up to date and rearranging it, and keeping track
// of which objects are selected.
//
// The "Type Browser" is also a list of Fl_Type, but is used for the
// popup menu of new objects to create. In this case these are
// "factory instances", not "real" ones.  Factory instances exist only
// so the "make" method can be called on them.  They are not in the
// linked list and are not written to files or copied or otherwise
// examined.

#include <efltk/Fl.h>
#include <efltk/Fl_Multi_Browser.h>
#include <efltk/Fl_Item.h>
#include <efltk/fl_draw.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <config.h> // for strcasecmp

#include "Fl_Type.h"
#include "Fluid_Image.h"

////////////////////////////////////////////////////////////////
// Code to access lists of enuerations:

const Enumeration* from_value(void* data, const Enumeration* table)
{
  for (;table->menu_entry; table++)
    if (table->compiled == data) return table;
  return 0;
}

const Enumeration* from_value(int data, const Enumeration* table)
{
  for (;table->menu_entry; table++)
    if (int(table->compiled) == data) return table;
  return 0;
}

const Enumeration* from_text(const char* text, const Enumeration* table)
{
  // For back compatability we strip leading FL_ from symbols:
  if (text[0]=='F' && text[1]=='L' && text[2]=='_') text += 3;
  for (;table->menu_entry; table++) {
    if (table->symbol && !strcmp(table->symbol, text)) return table;
    // also for back compatability we match the menu entry and subclass:
    if (!strcasecmp(table->menu_entry, text)) return table;
    if (table->subclass && !strcmp(table->subclass, text)) return table;
  }
  return 0;
}

const char* to_text(void* data, const Enumeration* table)
{
  for (;table->menu_entry; table++) {
    if (table->compiled == data) {
      if (table->symbol && !table->subclass) return table->symbol;
      return table->menu_entry;
    }
  }
  return 0;
}

int number_from_text(const char* text, const Enumeration* table)
{
  if (table) {
    const Enumeration* t = from_text(text, table);
    if (t) return int(t->compiled);
  }
  return strtol(text, 0, 0);
}

const char* number_to_text(int number, const Enumeration* table)
{
  if (table) {
    const char* t = to_text((void*)number, table);
    if (t) return t;
  }
  static char buffer[20];
  sprintf(buffer, "%d", number);
  return buffer;
}

////////////////////////////////////////////////////////////////
// Code to translate a table of Enumeration entries into Fl_Menu items:

class Enumeration_List : public Fl_List {
  virtual int children(const Fl_Menu_*, const int* indexes, int level);
  virtual Fl_Widget* child(const Fl_Menu_*, const int* indexes, int level);
};

static Enumeration_List enumeration_list;

void set_menu(Fl_Menu_* menu, const Enumeration* list) {
  menu->list(&enumeration_list);
  menu->user_data((void*)list);
}

int Enumeration_List::children(const Fl_Menu_* menu, const int*, int level)
{
  if (level) return -1;
  const Enumeration* e = (const Enumeration*)(menu->user_data());
  int n = 0;
  while (e->menu_entry) {n++; e++;}
  return n;
}

Fl_Widget* Enumeration_List::child(const Fl_Menu_* menu, const int* indexes, int)
{
  const Enumeration* e = (const Enumeration*)(menu->user_data());
  int n = *indexes;
  while (n && e->menu_entry) {n--; e++;}
  if (!e->menu_entry) return 0;
  static Fl_Widget* widget;
  if (!widget) {
    Fl_Group::current(0);
    widget = new Fl_Item();
  }
  widget->user_data((void*)e);
  widget->label(e->menu_entry);
  widget->w(0);
  widget->h(0);
  widget->layout();
  return widget;
}

////////////////////////////////////////////////////////////////

Fl_Type *Fl_Type::first;
Fl_Type *Fl_Type::current;

class Widget_List : public Fl_List {
  virtual int children(const Fl_Menu_*, const int* indexes, int level);
  virtual Fl_Widget* child(const Fl_Menu_*, const int* indexes, int level);
  virtual void flags_changed(const Fl_Menu_*, Fl_Widget*);
};

static Widget_List widgetlist;

static Fl_Browser *widget_browser;

static void Widget_Browser_callback(Fl_Widget *,void *) {
  if (Fl_Type::current) Fl_Type::current->open();
}

Fl_Widget *make_widget_browser(int x,int y,int w,int h) {
  widget_browser = new Fl_Multi_Browser(x,y,w,h);
  widget_browser->end();
  widget_browser->list(&widgetlist);
  widget_browser->callback(Widget_Browser_callback);
  widget_browser->when(FL_WHEN_ENTER_KEY);
  widget_browser->indented(1);
  return widget_browser;
}

int Widget_List::children(const Fl_Menu_*, const int* indexes, int level) {
  Fl_Type* item = Fl_Type::first;
  if (!item) return 0;
  for (int l = 0; l < level; l++) {
    for (int i = indexes[l]; item && i; --i) item = item->next_brother;
    if (!item || !item->is_parent()) return -1;
    item = item->first_child;
  }
  int n; for (n = 0; item; item = item->next_brother) n++;
  return n;
}

Fl_Widget* Widget_List::child(const Fl_Menu_*, const int* indexes, int level) {
  Fl_Type* item = Fl_Type::first;
  if (!item) return 0;
  for (int l = 0;; l++) {
    for (int i = indexes[l]; item && i; --i) item = item->next_brother;
    if (!item) return 0;
    if (l >= level) break;
    item = item->first_child;
  }
  static Fl_Widget* widget;
  if (!widget) {
    Fl_Group::current(0);
    widget = new Fl_Item();
  }
  widget->user_data(item);
  if (item->selected) widget->set_selected();
  else widget->clear_selected();
  if (item->is_parent() && item->open_) widget->set_value();
  else widget->clear_value();

  widget->label(item->title());
  widget->w(0);
  widget->h(0);

  return widget;
}

void Widget_List::flags_changed(const Fl_Menu_*, Fl_Widget* w) {
  Fl_Type* item = (Fl_Type*)(w->user_data());
  item->open_ = w->value();
  item->new_selected = w->selected();
  if (item->new_selected != item->selected) selection_changed(item);
}

void select(Fl_Type* item, int value) {
  item->new_selected = value != 0;
  if (item->new_selected != item->selected) {
    selection_changed(item);
    widget_browser->redraw();
  }
}

void select_only(Fl_Type* i) {
  for (Fl_Type* item = Fl_Type::first; item; item = item->walk())
    select(item, item == i);
  if (!widget_browser || !i) return;
  int indexes[100];
  int L = 100;
  while (i) {
    Fl_Type* child = i->parent ? i->parent->first_child : Fl_Type::first;
    int n; for (n = 0; child != i; child=child->next_brother) n++;
    indexes[--L] = n;
    i = i->parent;
  }
  widget_browser->goto_index(indexes+L, 99-L);
  widget_browser->set_focus();
}

void deselect() {
  for (Fl_Type* item = Fl_Type::first; item; item = item->walk())
    select(item,0);
}

// Generate a descriptive text for this item, to put in browser & window
// titles. Warning: the buffer used is overwritten each time!
const char* Fl_Type::title() {
#define MAXLABEL 128
  static char buffer[MAXLABEL];
  const char* t1 = type_name();
  const char* type = 0;
  if (is_widget()) type = t1 = ((Fl_Widget_Type*)this)->subclass();
  const char* name = this->name();
  bool quoted = false;
  if (!name || !*name) {
    name = label();
    if (!name || !*name) return t1;
    quoted = true;
  }
  // copy but stop at any newline or when the buffer fills up:
  char* e = buffer+MAXLABEL-1; if (quoted) e--;
  char* p = buffer;
  if (type) {
    while (p < e && *type) *p++ = *type++;
    if (p >= e-4) return name;
    *p++ = ' ';
  }
  if (quoted) *p++ = '"';
  while (p < e && (*name&~31)) *p++ = *name++;
  if (*name) {
    if (p > e-3) p = e-3;
    strcpy(p, quoted ? "...\"" : "...");
  } else {
    if (quoted) *p++ = '"';
    *p++ = 0;
  }
  return buffer;
}

// Call this when the descriptive text changes:
void redraw_browser() {
  widget_browser->redraw();
}

Fl_Type::Fl_Type() {
  factory = 0;
  parent = 0;
  first_child = 0;
  next_brother = previous_brother = 0;
  selected = new_selected = 0;
  name_ = 0;
  label_ = 0;
  tooltip_ = 0;
  user_data_ = 0;
  user_data_type_ = 0;
  callback_ = 0;
}

// Calling walk(N) will return every Fl_Type under N by scanning
// the tree. Start with N->first_child. If N is null this will
// walk the entire tree, start with Fl_Type::first.

Fl_Type* Fl_Type::walk(const Fl_Type* topmost) const {
  if (first_child) return first_child;
  const Fl_Type* p = this;
  while (!p->next_brother) {
    p = p->parent;
    if (p == topmost) return 0;
  }
  return p->next_brother;
}

// walk() is the same as walk(0), which walks the entire tree:

Fl_Type* Fl_Type::walk() const {
  if (first_child) return first_child;
  const Fl_Type* p = this;
  while (!p->next_brother) {
    p = p->parent;
    if (!p) return 0;
  }
  return p->next_brother;
}

// turn a click at x,y on this into the actual picked object:
Fl_Type* Fl_Type::click_test(int,int) {return 0;}
void Fl_Type::add_child(Fl_Type*, Fl_Type*) {}
void Fl_Type::move_child(Fl_Type*, Fl_Type*) {}
void Fl_Type::remove_child(Fl_Type*) {}

// add as a new child of p:
void Fl_Type::add(Fl_Type *p) {
  parent = p;
  Fl_Type* q = p ? p->first_child : Fl_Type::first;
  if (q) {
    // find the last child:
    while (q->next_brother) q = q->next_brother;
    this->previous_brother = q;
    q->next_brother = this;
  } else {
    // no other children
    this->previous_brother = 0;
    if (p)
      p->first_child = this;
    else
      Fl_Type::first = this;
  }
  if (p) p->add_child(this,0);
  open_ = 1;
  modflag = 1;
  widget_browser->relayout();
}

// add to a parent before another widget:
void Fl_Type::insert(Fl_Type *g) {
  parent = g->parent;
  previous_brother = g->previous_brother;
  if (previous_brother) previous_brother->next_brother = this;
  else if (parent) parent->first_child = this;
  else Fl_Type::first = this;
  next_brother = g;
  g->previous_brother = this;
  if (parent) parent->add_child(this, g);
  widget_browser->relayout();
}

// delete from parent:
void Fl_Type::remove() {
  if (previous_brother) previous_brother->next_brother = next_brother;
  else if (parent) parent->first_child = next_brother;
  else Fl_Type::first = next_brother;
  if (next_brother) next_brother->previous_brother = previous_brother;
  previous_brother = next_brother = 0;
  if (parent) parent->remove_child(this);
  parent = 0;
  widget_browser->relayout();
  selection_changed(0);
}

// update a string member:
int storestring(const char *n, Fl_String& p, int nostrip) 
{
	if(!n) { p.clear(); return 0; }
	if(p==n) return 0;
	
	Fl_String N = n;
	if(!nostrip)	p = N.trim();
	else			p = N;

	modflag = 1;
	return !p.empty();
}

void Fl_Type::name(const char *n) {
  if (storestring(n, name_)) widget_browser->redraw();
}

void Fl_Type::label(const char *n) {
  if (storestring(n,label_,1)) {
    setlabel(label_);
    if (!name_) widget_browser->redraw();
  }
}

void Fl_Type::tooltip(const char *n) {
  storestring(n,tooltip_,1);
}

void Fl_Type::callback(const char *n) {
    storestring(n,callback_);
}

void Fl_Type::user_data(const char *n) {
  storestring(n,user_data_);
}

void Fl_Type::user_data_type(const char *n) {
  storestring(n,user_data_type_);
}

void Fl_Type::open() {
  printf("Open of '%s' is not yet implemented\n",type_name());
}

void Fl_Type::setlabel(const char *) {}

Fl_Type::~Fl_Type() {
  for (Fl_Type* f = first_child; f;) {
    Fl_Type* next = f->next_brother;
    delete f;
    f = next;
  }
  if (previous_brother) previous_brother->next_brother = next_brother;
  else if (parent) parent->first_child = next_brother;
  else first = next_brother;
  if (next_brother) next_brother->previous_brother = previous_brother;
  if (current == this) current = 0;
  modflag = 1;
  if (widget_browser) widget_browser->relayout();
}

int Fl_Type::is_parent() const {return 0;}
int Fl_Type::is_widget() const {return 0;}
int Fl_Type::is_valuator() const {return 0;}
int Fl_Type::is_button() const {return 0;}
int Fl_Type::is_light_button() const {return 0;}
int Fl_Type::is_menu_item() const {return 0;}
int Fl_Type::is_menu_button() const {return 0;}
int Fl_Type::is_group() const {return 0;}
int Fl_Type::is_window() const {return 0;}
int Fl_Type::is_code_block() const {return 0;}
int Fl_Type::is_decl() const {return 0;}
int Fl_Type::is_decl_block() const {return 0;}
int Fl_Type::is_class() const {return 0;}
int Fl_Type::is_counter() const {return 0;}
int Fl_Type::is_adjuster() const {return 0;}
int Fl_Type::is_slider() const {return 0;}
int Fl_Type::is_scrollbar() const {return 0;}
int Fl_Type::is_choice() const {return 0;}
int Fl_Type::is_browser() const {return 0;}
int Fl_Type::is_input() const {return 0;}
int Fl_Type::is_value_input() const {return 0;}
int Fl_Type::is_value_output() const {return 0;}
int Fl_Type::is_value_slider() const {return 0;}

////////////////////////////////////////////////////////////////

Fl_Type *in_this_only; // set if menu popped-up in window

void select_all_cb(Fl_Widget *,void *) {
  Fl_Type *parent = Fl_Type::current ? Fl_Type::current->parent : 0;
  if (in_this_only) {
    // make sure we don't select outside the current window
    Fl_Type* p;
    for (p = parent; p && p != in_this_only; p = p->parent);
    if (!p) parent = in_this_only;
  }
  for (;;) {
    // select all children of parent:
    int changed = 0;
    for (Fl_Type *t = parent ? parent->first_child : Fl_Type::first;
	 t; t = t->walk(parent))
      if (!t->selected) {changed = 1; select(t,1);}
    if (changed) break;
    // if everything was selected, try a higher parent:
    if (!parent || parent == in_this_only) break;
    parent = parent->parent;
  }
}

void delete_all(int selected_only) {
  for (Fl_Type *f = Fl_Type::first; f;) {
    if (f->selected || !selected_only) {
      Fl_Type* next = f->next_brother;
      delete f;
      f = next;
    } else {
      f = f->walk();
    }
  }
  if(!selected_only) {
    include_H_from_C = 1;
    images_dir = ""; //"./";
  }
  selection_changed(0);
}

// move f (and it's children) into list before g:
// returns pointer to whatever is after f & children
void Fl_Type::move_before(Fl_Type* g) {
  remove();
  insert(g);
}

// move selected widgets in their parent's list:
void earlier_cb(Fl_Widget*,void*) {
  Fl_Type *parent = Fl_Type::current ? Fl_Type::current->parent : 0;
  for (Fl_Type* f = parent ? parent->first_child : Fl_Type::first; f; ) {
    Fl_Type* next = f->next_brother;
    if (f->selected) {
      Fl_Type* g = f->previous_brother;
      if (g && !g->selected) f->move_before(g);
    }
    f = next;
  }
}

void later_cb(Fl_Widget*,void*) {
  Fl_Type *parent = Fl_Type::current ? Fl_Type::current->parent : 0;
  Fl_Type *f;
  for (f = parent ? parent->first_child : Fl_Type::first;f && f->next_brother;)
    f = f->next_brother;
  for (;f;) {
    Fl_Type* prev = f->previous_brother;
    if (f->selected) {
      Fl_Type* g = f->next_brother;
      if (g && !g->selected) g->move_before(f);
    }
    f = prev;
  }
}

////////////////////////////////////////////////////////////////

// write a widget and all it's children:
void Fl_Type::write() {
  int level = 0;
  for (Fl_Type* p = parent; p; p = p->parent) level++;
  write_indent(level);
  write_word(type_name());
  write_word(name());
  write_open(level);
  write_properties();
  write_close(level);
  if (!is_parent()) return;
  // now do children:
  write_open(level);
  Fl_Type *child;
  for (child = first_child; child; child = child->next_brother) child->write();
  write_close(level);
}

void Fl_Type::write_properties() 
{
	int level = 0;
	for (Fl_Type* p = parent; p; p = p->parent) level++;
	// repeat this for each attribute:
	if (!label().empty()) {
		write_indent(level+1);
		write_word("label");
		write_word(label());
	}
	if (!user_data().empty()) {
		write_indent(level+1);
		write_word("user_data");
		write_word(user_data());
		if (!user_data_type().empty()) {
			write_word("user_data_type");
			write_word(user_data_type());
		}
	}
	if (!callback().empty()) {
		write_indent(level+1);
		write_word("callback");
		write_word(callback());
	}
	if (is_parent() && open_) write_word("open");
	if (selected) write_word("selected");
	if (!tooltip().empty()) {
		write_indent(level+1);
		write_word("tooltip");
		write_word(tooltip());
	}
}

void Fl_Type::read_property(const Fl_String &c) {
  if (!strcmp(c,"label"))
    label(read_word());
  else if (!strcmp(c,"tooltip"))
    tooltip(read_word());
  else if (!strcmp(c,"user_data"))
    user_data(read_word());
  else if (!strcmp(c,"user_data_type"))
    user_data_type(read_word());
  else if (!strcmp(c,"callback"))
    callback(read_word());
  else if (!strcmp(c,"open"))
    open_ = 1;
  else if (!strcmp(c,"selected"))
    select(this,1);
  else
    read_error("Unknown property \"%s\"", c);
}

//
// End of "$Id$".
//
