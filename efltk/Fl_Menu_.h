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

#ifndef _FL_MENU_H_
#define _FL_MENU_H_

#include "Fl_Group.h"
#include "Fl_Menu_Item.h" // for back compatability,should not be necessary,

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
    // Constructors does end()
    Fl_Menu_();
    Fl_Menu_(int,int,int,int, const char* l=0);

    Fl_Callback *about_to_show;
    Fl_Callback *about_to_hide;

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

#ifndef FLTK_2
    // Commented-out methods cannot be emulated.
    void copy(const Fl_Menu_Item* m, void* data = 0) { clear(); m->add_to(this,data); }
    void menu(const Fl_Menu_Item* m) { copy(m,0); }
    void replace(int n, const char* s) { child(n)->label(s); }
    void replace(const char* l, const char* s) { find(l)->label(s); }
    void shortcut(const char* l, int s) { find(l)->shortcut(s); }
    void shortcut(int s) {Fl_Widget::shortcut(s);}
    int shortcut() const {return Fl_Widget::shortcut();}
    void shortcut(int i, int s) { child(i)->shortcut(s); }
    unsigned mode(int i) const {return child(i)->flags() >> 8;}
    unsigned mode(const char* l) const {return find(l)->flags() >> 8;}

    const Fl_String &text(int i) const { return child(i)->label(); }
    const Fl_String &text() const { Fl_Widget* w = item(); return w ? w->label() : Fl_String::null_object; }
#endif

    // Set/Get default effect type for all menus
    static int default_effect_type() { return default_effect_type_; }
    static void default_effect_type(int v) { default_effect_type_ = v; }

    // Effect type, ONLY for this menu
    int effect_type() { return effect_type_; }
    void effect_type(int v) { effect_type_ = v; }

    // Set/Get default sub-menu delay of all menus
    static float default_delay() { return default_delay_; }
    static void  default_delay(float v) { default_delay_ = v; }

    // sub-menu delay, ONLY for this menu
    float delay() { return delay_; }
    void delay(float v) { delay_ = v; }

    // Set/Get default animate speed of all menua
    static float default_anim_speed() { return default_anim_speed_; }
    static void default_anim_speed(float v) { default_anim_speed_ = v; }

    // Set/Get animate speed, ONLY for this menu
    float anim_speed() { return anim_speed_; }
    void anim_speed(float v) { anim_speed_ = v; }

    // Are menu effects enabled?
    static bool effects() { return effects_; }
    static void effects(bool v) { effects_ = v; }

    // Does sub-menus animate, like first menuwindow?
    static bool subwindow_effect() { return subwindow_effect_; }
    static void subwindow_effect(bool v) { subwindow_effect_ = v; }

private:
    friend class MenuWindow;
    Fl_List* list_;

    static float default_delay_;
    float delay_;

    static bool effects_;
    static bool subwindow_effect_;

    static int default_effect_type_;
    int effect_type_;

    static float default_anim_speed_;
    float anim_speed_;

protected:
    static bool key_event;

    Fl_Widget *item_;
    int anim_flags_;
};

#endif
