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

#ifndef _FL_WINDOW_H_
#define _FL_WINDOW_H_

#include "Fl_Group.h"

// value for x,y to indicate window system places window
#define FL_USEDEFAULT ((int)0x80000000) // same as Win32 value

/** Fl_Window */
class FL_API Fl_Window : public Fl_Group {
public:
    static Fl_Named_Style* default_style;

    Fl_Window(int,int,int,int, const char* = 0);
    Fl_Window(int,int, const char* = 0);
    virtual ~Fl_Window();

    // Types from Fl_WM.h
    // Type is set before first map, straight after creating xid.
    void window_type(int type) { window_type_ = type; }
    int window_type() { return window_type_; }

    const Fl_String &label() const     { return Fl_Widget::label(); }
    const Fl_String &iconlabel() const { return iconlabel_; }

    void copy_label(const char *l) { label(l); }
    void copy_label(const Fl_String &l) { label(l); }

    void label(const char *l) { label(l, iconlabel_.c_str()); }
    void label(const Fl_String &l) { label(l, iconlabel_); }
    void iconlabel(const char *il) { label(label().c_str(), il); }
    void iconlabel(const Fl_String &il) { label(label(), il); }

    void label(const char *l, const char *il);
    void label(const Fl_String &l, const Fl_String &il);

    const void* icon() const	{ return icon_; }
    void icon(const void * ic)	{ icon_ = ic; }

    static const Fl_String &xclass() { return xclass_; }
    static void xclass(const char* v) { xclass_ = v; }
    static void xclass(const Fl_String &v) { xclass_ = v; }

    void clear_border()	{ set_flag(FL_NOBORDER); }
    bool border() const	{ return !flags().is_set(FL_NOBORDER); }
    void set_override()	{ set_flag(FL_NOBORDER|FL_OVERRIDE); }
    bool override() const { return flags().is_set(FL_OVERRIDE); }
    const Fl_Window* child_of() const { return child_of_; }
    void child_of(const Fl_Window* w);

     // back compatability only!
    void set_modal()	 { set_flag(FL_MODAL); }
    void set_non_modal() { set_flag(FL_NON_MODAL); }

    void hotspot(int x, int y, bool offscreen = false);
    void hotspot(const Fl_Widget*, bool offscreen = false);
    void hotspot(const Fl_Widget& p, bool offscrn = false) { hotspot(&p,offscrn); }

    bool shown() const { return i != 0; }

    void show();
    void show(int, char**);
    void show(const Fl_Window* parent);
    void show_inside(const Fl_Window* parent);

    bool exec(const Fl_Window* parent = 0, bool grab = false);

    void iconize();
    bool iconic() const;
    virtual void destroy();

    void fullscreen();
    void fullscreen_off(int,int,int,int);

    static const Fl_Window *current() { return current_; }
    void make_current() const;

    void cursor(Fl_Cursor, Fl_Color=FL_BLACK, Fl_Color=FL_WHITE);
    static void default_callback(Fl_Window*, void* v);

    virtual int handle(int);
    virtual void layout();
    virtual void flush();
    virtual void draw();

    void size_range(int minw, int minh, int maxw=0, int maxh=0, int dw=0, int dh=0);
    bool has_size_range() { return m_size_range; }

    int minw() { return m_minw; }
    int minh() { return m_minh; }
    int maxw() { return m_maxw; }
    int maxh() { return m_maxh; }
    int dw() { return m_dw; }
    int dh() { return m_dh; }

protected:
    virtual void create();
    static const Fl_Window *current_;

private:
    /// size_range stuff:
    short m_minw, m_minh, m_maxw, m_maxh;
    unsigned char m_dw, m_dh;
    bool m_size_range;

    int window_type_;

    friend class Fl_X;
    Fl_X *i; // points at the system-specific stuff

    const Fl_Window* child_of_;

    Fl_String iconlabel_;
    const void* icon_;

    void size_range_();

    // values for flags():
    enum {
        FL_MODAL		= 0x80000000,
        FL_NOBORDER 	= 0x40000000,
        FL_OVERRIDE         = 0x20000000,
        FL_NON_MODAL	= 0x10000000
    };

    static Fl_String xclass_;
    void _Fl_Window(); // constructor innards
};

#endif
