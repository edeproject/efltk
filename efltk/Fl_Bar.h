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

#ifndef _FL_BAR_H_
#define _FL_BAR_H_

#include "Fl_Group.h"

/** Fl_Bar */
class FL_API Fl_Bar : public Fl_Group {
public:
    static Fl_Named_Style* default_style;

    Fl_Bar(int x,int y,int w ,int h,const char *l = 0);
    Fl_Bar(const char* l = 0,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    // values for type(int)
    enum {
        VERTICAL    = GROUP_TYPE,
        HORIZONTAL  = GROUP_TYPE+1
    };

    void layout();
    int handle(int);
    void draw();
    bool opened() const {return open_;}
    bool opened(bool);
    bool open() {return opened(true);}
    bool close() {return opened(false);}
    int glyph_size() const {return glyph_size_;}
    void glyph_size(int v) {glyph_size_ = v;}

protected:
    bool highlighted;
    bool pushed;

private:
    void initialize(int h);

    bool open_;
    int glyph_size_;
    int saved_size;
    void glyph_box(int& x, int& y, int& w, int& h);
};

#endif
