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

#ifndef _FL_GL_WINDOW_H_
#define _FL_GL_WINDOW_H_

#include "Fl_Window.h"

#ifndef GLContext
typedef void* GLContext; // actually a GLXContext or HGLDC
#endif

class Fl_Gl_Choice; // structure to hold result of glXChooseVisual

enum {
    FL_NO_AUTO_SWAP = 1024,
    FL_NO_ERASE_OVERLAY = 2048
};

class FL_API Fl_Gl_Window : public Fl_Window {

public:
    Fl_Gl_Window(int W, int H, const char *l=0) : Fl_Window(W,H,l) { init(); }
    Fl_Gl_Window(int X, int Y, int W, int H, const char *l=0) : Fl_Window(X,Y,W,H,l) { init(); }
    ~Fl_Gl_Window();

    virtual void create();
    virtual void flush();
    virtual void destroy();
    virtual void layout();

    char valid() const {return valid_;}
    void valid(char i) {valid_ = i;}
    void invalidate();

    int mode() const {return mode_;}
    bool mode(int a);
    static bool can_do(int);
    bool can_do() {return can_do(mode_);}

    void* context() const {return context_;}
    void context(void*, bool destroy_flag = false);
    void make_current();
    void swap_buffers();
    void ortho();

    bool can_do_overlay();
    void redraw_overlay();
    void hide_overlay();
    void make_overlay_current();

private:
    int mode_;
    Fl_Gl_Choice *gl_choice;
    GLContext context_;
    char valid_;
    char damage1_; // damage() of back buffer
    virtual void draw_overlay();
    void init();

    void *overlay;
    void make_overlay();
    friend class _Fl_Gl_Overlay;

    void draw_swap();
};

#endif
