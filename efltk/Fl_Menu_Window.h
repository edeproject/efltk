//
// "$Id$"
//
// Menu window header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Menu_Window_H
#define Fl_Menu_Window_H

#include "Fl_Single_Window.h"

class FL_API Fl_Menu_Window : public Fl_Single_Window {
    enum {NO_OVERLAY = 0x08000000};

public:

    virtual void create();
    virtual void flush();
    virtual void destroy();

    int overlay() {return !(flags()&NO_OVERLAY);}
    void set_overlay() {clear_flag(NO_OVERLAY);}
    void clear_overlay() {set_flag(NO_OVERLAY);}

    ~Fl_Menu_Window();

    Fl_Menu_Window(int W, int H, const char *l = 0);
    Fl_Menu_Window(int X, int Y, int W, int H, const char *l = 0);

    static float default_step_div;

    // Calculated steps needed for animating is divided by this number,
    // So You can control the speed. DEFAULT=4
    void step_divider(float div) { step_div_ = div; }
    float step_divider() { return step_div_; }

    static bool animate() { return animate_; }
    static void animate(bool v) { animate_ = v; }

    void animate(int fx, int fy, int fw, int fh,
                 int tx, int ty, int tw, int th);

protected:
    static bool animate_;
    bool animating; //set true, while animating

    float step_div_;
};

#endif

//
// End of "$Id$".
//
