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

#ifndef _FL_MENU_ITEM_H_
#define _FL_MENU_ITEM_H_

#include "Fl_Widget.h"

enum { // values for flags:
    FL_MENU_INACTIVE = 1,
    FL_MENU_TOGGLE= 2,
    FL_MENU_VALUE = 4,
    FL_MENU_RADIO = 8,
    FL_MENU_INVISIBLE = 0x10,
    FL_SUBMENU_POINTER = 0x20,
    FL_SUBMENU = 0x40,
    FL_MENU_DIVIDER = 0x80,
    FL_MENU_HORIZONTAL = 0x100, // not used!
    FL_MENU_RIGHTLAYOUT = 0x200
};

class FL_API Fl_Menu_;

struct FL_API Fl_Menu_Item {
    const char *text;
    int shortcut_;
    Fl_Callback *callback_;
    void *user_data_;
    int flags;
    Fl_Labeltype labeltype_;
    Fl_Font labelfont_;
    unsigned labelsize_;
    Fl_Color labelcolor_;

    // Used to add or set an Fl_Menu_ widget:
    void add_to(Fl_Menu_*, void* data = 0) const;

    // popup menus without using an Fl_Menu_ widget:
    // Warning: this is now quite expensive, as it creates a temporary
    // Fl_Menu_ and child widgets!  These also do not match the fltk 1.0
    // calls, if there is any callback it is called directly (with the
    // dummy Fl_Menu_ as an argument).
    const Fl_Menu_Item*
        pulldown(int X, int Y, int W, int H,
                 const Fl_Menu_Item* picked = 0,
                 const char* title = 0) const;
    const Fl_Menu_Item*
        popup(int X, int Y, const char* title=0,
              const Fl_Menu_Item* picked = 0) const {
            return pulldown(X, Y, 0, 0, picked, title);}
    const Fl_Menu_Item*
        test_shortcut() const;

    // return offset of terminating null item:
    int size() const ;

    // advance a pointer by N items, skipping submenus:
    const Fl_Menu_Item *next(int=1) const;
    Fl_Menu_Item *next(int i=1) {
        return (Fl_Menu_Item*)(((const Fl_Menu_Item*)this)->next(i));}

    const char* label() const {return text;}
    Fl_Labeltype labeltype() const {return labeltype_;}
    Fl_Color labelcolor() const {return labelcolor_;}
    Fl_Font labelfont() const {return labelfont_;}
    unsigned labelsize() const {return labelsize_;}
    Fl_Callback_p callback() const {return callback_;}
    void* user_data() const {return user_data_;}
    long argument() const {return (long)user_data_;}
    int shortcut() const {return shortcut_;}
    int submenu() const {return flags&(FL_SUBMENU|FL_SUBMENU_POINTER);}
    int checkbox() const {return flags&FL_MENU_TOGGLE;}
    int radio() const {return flags&FL_MENU_RADIO;}
    int value() const {return flags&FL_MENU_VALUE;}
    int visible() const {return !(flags&FL_MENU_INVISIBLE);}
    int active() const {return !(flags&FL_MENU_INACTIVE);}
    int activevisible() const {return !(flags&0x11);}

    void label(const char* a) {text=a;}
    void label(Fl_Labeltype a,const char* b) {labeltype_ = a; text = b;}
    void labeltype(Fl_Labeltype a) {labeltype_ = a;}
    void labelcolor(uchar a) {labelcolor_ = a;}
    void labelfont(Fl_Font a) {labelfont_ = a;}
    void labelsize(uchar a) {labelsize_ = a;}
    void callback(Fl_Callback* c, void* p) {callback_=c; user_data_=p;}
    void callback(Fl_Callback* c) {callback_=c;}
    void callback(Fl_Callback0*c) {callback_=(Fl_Callback*)c;}
    void callback(Fl_Callback1*c, long p=0) {callback_=(Fl_Callback*)c; user_data_=(void*)p;}
    void user_data(void* v) {user_data_ = v;}
    void argument(long v) {user_data_ = (void*)v;}
    void shortcut(int s) {shortcut_ = s;}
    void set() {flags |= FL_MENU_VALUE;}
    void clear() {flags &= ~FL_MENU_VALUE;}
    void setonly();
    void show() {flags &= ~FL_MENU_INVISIBLE;}
    void hide() {flags |= FL_MENU_INVISIBLE;}
    void activate() {flags &= ~FL_MENU_INACTIVE;}
    void deactivate() {flags |= FL_MENU_INACTIVE;}

    const Fl_Menu_Item* find_shortcut(int *ip=0) const;

    void do_callback(Fl_Widget* o) const {callback_(o, user_data_);}
    void do_callback(Fl_Widget* o,void* arg) const {callback_(o, arg);}
    void do_callback(Fl_Widget* o,long arg) const {callback_(o, (void*)arg);}

    // back-compatability, do not use:
    int checked() const {return flags&FL_MENU_VALUE;}
    void check() {flags |= FL_MENU_VALUE;}
    void uncheck() {flags &= ~FL_MENU_VALUE;}
};

#endif
