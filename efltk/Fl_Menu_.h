//
// "$Id$"
//
// Menu base class header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Menu__H
#define Fl_Menu__H

#include "Fl_Group.h"
#ifndef FLTK_2
#include "Fl_Menu_Item.h" // for back compatability,should not be necessary,
#endif

#define MAX_LEVELS 64

class MenuWindow;
class FL_API Fl_Menu_;

class FL_API Fl_List {
public:
  virtual int children(const Fl_Menu_*, const int* indexes, int level);
  virtual Fl_Widget* child(const Fl_Menu_*, const int* indexes, int level);
  virtual void flags_changed(const Fl_Menu_*, Fl_Widget*);
};

class FL_API Fl_Menu_ : public Fl_Group {
public:
    // Contructs 0x0 size menu, does end() in contructor
    Fl_Menu_();
	// Does also end()
	Fl_Menu_(int,int,int,int, const char* l=0);

	Fl_List* list() const {return list_;}
	void list(Fl_List* l) {list_ = l;}
	
	int children(const int* indexes, int level) const ;
	int children() const ;
	Fl_Widget* child(const int* indexes, int level) const ;
	Fl_Widget* child(int index) const ;
	Fl_Widget* item() const {return item_;}
	Fl_Widget* item(Fl_Widget* v) {return item_ = v;}
	bool focus(const int* indexes, int level);
	Fl_Widget* get_focus();
	
	int value() const {return Fl_Group::focus();}
	void value(int v) {Fl_Group::focus(v);}
	int  size() const {return children();}
	
	virtual int popup(int x,int y,int w=0,int h=0);
	int handle_shortcut();
	static void default_callback(Fl_Widget*, void*);
	void execute(Fl_Widget*);
	void global();
	
	Fl_Widget* find(const char* label) const;
	Fl_Widget* add(const char*, int shortcut, Fl_Callback*, void* = 0, int = 0);
	Fl_Widget* replace(const char*, int scut, Fl_Callback*, void* = 0, int = 0);
	Fl_Widget* add(const char*, void*);
	Fl_Widget* add(const char*);
	Fl_Widget* insert(int n, const char* s, void* data = 0);
	void remove(const char* l) { delete find(l); }
	
	// Undo the overrides of stuff from Fl_Group:
	void add(Fl_Widget& o) {Fl_Group::add(o);}
	void add(Fl_Widget* o) {add(*o);}
	void insert(Fl_Widget& o, int n) {Fl_Group::insert(o, n);}
	void replace(int index, Fl_Widget& o) {Fl_Group::replace(index, o);}
	void replace(Fl_Widget& old, Fl_Widget& o) {Fl_Group::replace(old,o);}
	void remove(int index) {Fl_Group::remove(index);}
	void remove(Fl_Widget& o) {Fl_Group::remove(o);}
	void remove(Fl_Widget* o) {Fl_Group::remove(o);}
	
	enum {
		TOP_TO_BOTTOM=1,
			BOTTOM_TO_TOP=2,
			LEFT_TO_RIGHT=4,
			RIGHT_TO_LEFT=8
	};
	void anim_flags(int f) { anim_flags_ = f; }
	int anim_flags() { return anim_flags_; }
	
	// Relayouts current menuwindow, useful when adding items after show
	static void relayout_current_menu();
	
#ifndef FLTK_2
	// Commented-out methods cannot be emulated.
	//const Fl_Menu_Item* test_shortcut();
	//Fl_Menu_Item* menu() const;
	void copy(const Fl_Menu_Item* m, void* data = 0) {clear(); m->add_to(this,data);}
	void menu(const Fl_Menu_Item* m) {copy(m,0);}
	void replace(int n, const char* s) { child(n)->label(s); }
	void replace(const char* l, const char* s) { find(l)->label(s); }
	void shortcut(const char* l, int s) { find(l)->shortcut(s); }
	void shortcut(int s) {Fl_Widget::shortcut(s);}
	int shortcut() const {return Fl_Widget::shortcut();}
	void shortcut(int i, int s) { child(i)->shortcut(s); }
	//int index(Fl_Menu_Item* m) const { return m - menu_; }
	//int index(const char* label) const;
	//void replace(Fl_Menu_Item* m, const char* s) { replace(index(m), s); }
	//void remove(Fl_Menu_Item* m) { remove(index(m)); }
	//void shortcut(Fl_Menu_Item* m, int s) {shortcut(index(m), s);}
	//void mode(int i,int x);
	//void mode(Fl_Menu_Item* m, int x) {mode(index(m), x);}
	//void mode(const char* l, int x) {mode(index(l), x);}
	unsigned mode(int i) const {return child(i)->flags() >> 8;}
	//unsigned mode(Fl_Menu_Item* m) const {return mode(index(m));}
	unsigned mode(const char* l) const {return find(l)->flags() >> 8;}
	
	// in fltk 1.0 these returned/took an Fl_Menu_Item*:
	Fl_Widget* mvalue() {return item();}
	//void value(Fl_Widget* o) {set_item(o);}
	
	const char *text(int i) const {return i >= 0 ? child(i)->label() : 0;}
	const char *text() const {Fl_Widget* w = item(); return w ? w->label() : 0;}
#endif
	
	// Set/Get default delay of all menus
	static float default_delay() { return default_delay_; }
	static void  default_delay(float v) { default_delay_ = v; }

	// Set/Get delay ONLY for this menu
	float delay() { return delay_; }
	void delay(float v) { delay_ = v; }

	// Set/Get animate speed, ONLY for this menu
	float anim_speed() { return anim_speed_; }
	void anim_speed(float v) { anim_speed_ = v; }

    static bool animate() { return animate_; }
    static void animate(bool v) { animate_ = v; }

    static bool subwindow_animate() { return subwindow_animate_; }
    static void subwindow_animate(bool v) { subwindow_animate_ = v; }

private:
    friend class MenuWindow;
    Fl_List* list_;	

	static float default_delay_;
	float delay_;

	static bool animate_;
	static bool subwindow_animate_;

    float anim_speed_;

protected:
		
	static bool key_event;
    static MenuWindow *first_menu;

    int indexes[MAX_LEVELS];
    int level;
	
    Fl_Widget *item_;
    Fl_Widget *executed_;
	
    int anim_flags_;
};

#endif

//
// End of "$Id$".
//
