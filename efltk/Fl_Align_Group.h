// Layout header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Layout_H
#define Fl_Layout_H

#ifndef Fl_Group_H
#include "Fl_Group.h"
#endif

class FL_API Fl_Align_Group : public Fl_Group {
  bool vertical_;
  uchar n_to_break_,dw_,dh_;
  Fl_Align align_;

public:

  void layout();

  Fl_Align_Group(int X, int Y, int W, int H, const char* L = 0,
		 uchar n_to_break = 0, bool vertical = 1,
		 Fl_Align align = FL_ALIGN_LEFT,
		 uchar dw = 0,uchar dh = 0)
    : Fl_Group(X,Y,W,H,L),
      vertical_(vertical), n_to_break_(n_to_break), dw_(dw), dh_(dh),
      align_(align) {}

  bool vertical() const {return vertical_;}
  void vertical(bool v) {vertical_ = v;}

  uchar n_to_break() const {return n_to_break_;}
  void n_to_break(uchar n) {n_to_break_ = n;}

  uchar dw() const {return dw_;}
  void dw(uchar d) {dw_ = d;}
  uchar dh() const {return dh_;}
  void dh(uchar d) {dh_ = d;}

  Fl_Align align() const {return align_;}
  void align(Fl_Align a) {align_ = a;}
};

#endif
