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

#ifndef _FL_ALIGN_GROUP_H_
#define _FL_ALIGN_GROUP_H_

#include "Fl_Group.h"

class FL_API Fl_Align_Group : public Fl_Group {
public:
    void layout();

    Fl_Align_Group(int X, int Y, int W, int H, const char* L = 0) : Fl_Group(X,Y,W,H,L) {
        n_to_break_ = 0; vertical_ = 1;
        align_ = FL_ALIGN_LEFT;
        dw_ = dh_ = 0;
    }

    bool vertical() const {return vertical_;}
    void vertical(bool v) {vertical_ = v;}

    uchar n_to_break() const { return n_to_break_; }
    void n_to_break(uchar n) { n_to_break_ = n; }

    uchar dw() const {return dw_;}
    void dw(uchar d) {dw_ = d;}

    uchar dh() const {return dh_;}
    void dh(uchar d) {dh_ = d;}

    Fl_Align align() const {return align_;}
    void align(Fl_Align a) {align_ = a;}

private:
    bool vertical_;
    uchar n_to_break_,dw_,dh_;
    Fl_Align align_;
};

#endif
