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

#ifndef _FL_SLIDER_H_
#define _FL_SLIDER_H_

#include "Fl_Valuator.h"

class FL_API Fl_Slider : public Fl_Valuator {
public:
    static Fl_Named_Style* default_style;

    Fl_Slider(int x,int y,int w,int h, const char *l = 0);

    enum { // bit flags for type():
        VERTICAL		= 0,
        HORIZONTAL		= 1,
        TICK_ABOVE		= 2,
        TICK_LEFT		= TICK_ABOVE,
        TICK_BELOW		= 4,
        TICK_RIGHT		= TICK_BELOW,
        TICK_BOTH		= TICK_ABOVE|TICK_BELOW,
        LOG			= 8,
        FILL		= 16 // for back compatability only
    };

    bool horizontal() const {return (type()&HORIZONTAL)!=0;}
    bool log() const {return (type()&LOG)!=0;}

    unsigned short slider_size() const {return slider_size_;}
    void slider_size(int n) {slider_size_ = (unsigned short)n;}

    unsigned short tick_size() const {return tick_size_;}
    void tick_size(int n) {tick_size_ = (unsigned short)n;}

    virtual void draw();
    virtual int handle(int);

protected:
    int slider_position(double value, int w);
    double position_value(int x, int w);
    int handle(int event, int, int, int, int);
    void draw_ticks(int,int,int,int, int min_spacing);
    bool draw(int, int, int, int, Fl_Flags flags, bool slot);

private:
    unsigned short slider_size_;
    unsigned short tick_size_;
    unsigned short old_position;
};

#endif
