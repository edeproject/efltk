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

#ifndef _FL_MENU_WINDOW_H_
#define _FL_MENU_WINDOW_H_

#include "Fl_Single_Window.h"

class FL_API Fl_Menu_Window : public Fl_Single_Window {
    enum {NO_OVERLAY = 0x08000000};

public:
    Fl_Menu_Window(int W, int H, const char *l = 0);
    Fl_Menu_Window(int X, int Y, int W, int H, const char *l = 0);
    ~Fl_Menu_Window();

    virtual void create();
    virtual void flush();
    virtual void destroy();
    virtual void layout();

    int overlay() {return !(flags()&NO_OVERLAY);}
    void set_overlay() {clear_flag(NO_OVERLAY);}
    void clear_overlay() {set_flag(NO_OVERLAY);}

    void fade(int x, int y, int w, int h, uchar opacity=255);

    void animate(int fx, int fy, int fw, int fh,
                 int tx, int ty, int tw, int th);

    // Set/Get animate speed, ONLY for this window
    float anim_speed() { return anim_speed_; }
    void anim_speed(float v) { anim_speed_ = v; }

protected:
    float anim_speed_;

    bool animating; //set true, while animating
};

#endif
