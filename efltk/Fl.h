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

#ifndef _Fl_H_
#define _Fl_H_

#include "Enumerations.h"

class FL_API Fl_Widget;
class FL_API Fl_Window;

/** Fl_Screen_Info */
struct Fl_Screen_Info {
    int x, y, w, h;
    int width;
    int height;
    int depth;
    int width_mm;
    int height_mm;
};

typedef void (*Fl_Timeout_Handler)(void*);

/** Fl */
class FL_API Fl {
    friend class Fl_Widget;
    Fl() { }; // no constructor!

public: // should be private!

    static int damage_;
    static int e_type;
    static int e_x;
    static int e_y;
    static int e_dx;
    static int e_dy;
    static int e_x_root;
    static int e_y_root;
    static int e_state;
    static int e_clicks;
    static int e_is_click;
    static int e_keysym;
    static int e_length;
    static char* e_text;
    static int compose_state;
    static Fl_Widget* belowmouse_;
    static Fl_Widget* pushed_;
    static Fl_Widget* focus_;
    static Fl_Widget* modal_;
    static bool grab_;
    static bool exit_modal_;
    static void damage(int x) {damage_ = x;}
    static void (*idle)();

public:

    static float version();

    // Read widgets default values.
    static void read_defaults();

    // Initializes locale support for EFLTK
    static bool init_locale();
    // Initializes locale support for application
    static bool init_locale(const char *app_domain, const char *directory);

    // Sleep milliseconds.
    static void sleep(int milliseconds);
    // Get ticks since EFltk initialize, in milliseconds
    static uint32 ticks();

    // argument parsers:
    static int arg(int, char**, int&);
    static int args(int, char**, int&, int (*)(int,char**,int&) = 0);
    static const char* const help;
    static void args(int, char**);

    // things called by initialization:
    static void display(const char*);
    static int visual(int);
    static void own_colormap();

    // execution:
    static int wait();
    static int wait(float time);
    static int check();
    static int ready();
    static int run();

    static void modal(Fl_Widget*, bool grab = false);
    static Fl_Widget* modal() {return modal_;}
    static bool grab() {return grab_;}
    static void exit_modal() {exit_modal_ = true;}
    static bool exit_modal_flag() {return exit_modal_;}

    static void add_timeout(float t,Fl_Timeout_Handler,void* v = 0);
    static void repeat_timeout(float t, Fl_Timeout_Handler,void* = 0);
    static bool has_timeout(Fl_Timeout_Handler, void* = 0);
    static void remove_timeout(Fl_Timeout_Handler, void* = 0);
    static void add_check(Fl_Timeout_Handler, void* = 0);
    static bool has_check(Fl_Timeout_Handler, void* = 0);
    static void remove_check(Fl_Timeout_Handler, void* = 0);
    static void add_fd(int fd, int when, void (*cb)(int,void*),void* =0);
    static void add_fd(int fd, void (*cb)(int, void*), void* = 0);
    static void remove_fd(int, int when = -1);
    static void set_idle(void (*cb)()) {idle = cb;}
    static void add_idle(void (*cb)(void*), void* = 0);
    static bool has_idle(void (*cb)(void*), void* = 0);
    static void remove_idle(void (*cb)(void*), void* = 0);
    static int damage() {return damage_;}
    static void redraw();
    static void flush();
    static void (*warning)(const char*, ...);
    static void (*error)(const char*, ...);
    static void (*fatal)(const char*, ...);

    // list of top-level shown() windows:
    static Fl_Window* first_window();
    static void first_window(Fl_Window*);
    static Fl_Window* next_window(const Fl_Window*);

    // event information:
    static int event()      {return e_type;}
    static int event_x()        {return e_x;}
    static int event_y()        {return e_y;}
    static int event_dx()       {return e_dx;}
    static int event_dy()       {return e_dy;}
    static int event_x_root()   {return e_x_root;}
    static int event_y_root()   {return e_y_root;}
    static int event_clicks()   {return e_clicks;}
    static void event_clicks(int i) {e_clicks = i;}
    static bool event_is_click()    {return e_is_click != 0;}
    static void event_is_click(bool) {e_is_click = 0;} // only false works!
    static int event_button()   {return e_keysym-FL_Button(0);}
    static int event_state()    {return e_state;}
    static bool event_state(int i) {return (e_state&i) != 0;}
    static int event_key()  {return e_keysym;}
    static bool event_key_state(int);
    static const char* event_text() {return e_text;}
    static int event_length() {return e_length;}

    static bool event_inside(int,int,int,int);
    static bool test_shortcut(int shortcut);
    static const char* key_name(int key);
    static bool compose(int &del);
    static void compose_reset() {compose_state = 0;}

    static bool get_key_state(int);
    static void get_mouse(int &,int &);

  // event destinations:
    static bool handle(int, Fl_Window*);
    static void add_handler(int (*h)(int));
    static Fl_Widget* belowmouse() {return belowmouse_;}
    static void belowmouse(Fl_Widget*);
    static void belowmouse(Fl_Widget& w) {belowmouse(&w);}
    static Fl_Widget* pushed()  {return pushed_;}
    static void pushed(Fl_Widget*);
    static void pushed(Fl_Widget& w) {pushed(&w);}
    static Fl_Widget* focus()   {return focus_;}
    static void focus(Fl_Widget*);
    static void focus(Fl_Widget& w) {focus(&w);}

  // cut/paste:
    static void copy(const char* stuff, int len, bool clipboard = false);
    static void paste(Fl_Widget &receiver, bool clipboard = false);
    static bool dnd();

  // screen size (any any other static information from system):
    static const Fl_Screen_Info& info();

  // Multithreading support:
    static void lock();
    static void unlock();
    static void awake(void* message = 0);
    static void* thread_message();

    static int x() { return info().x; }
    static int y() { return info().y; }
    static int w() { return info().width; }
    static int h() { return info().height; }
};

#endif
