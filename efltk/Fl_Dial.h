//
// "$Id$"
//
// Dial header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Dial_H
#define Fl_Dial_H

#ifndef Fl_Valuator_H
#include "Fl_Valuator.h"
#endif

class FL_API Fl_Dial : public Fl_Valuator {

public:
  enum {NORMAL = 0, LINE, FILL}; // values for type()
  int handle(int);
  Fl_Dial(int x,int y,int w,int h, const char *l = 0);
  static Fl_Named_Style* default_style;
  short angle1() const {return a1;}
  void angle1(short a) {a1 = a;}
  short angle2() const {return a2;}
  void angle2(short a) {a2 = a;}
  void angles(short a, short b) {a1 = a; a2 = b;}

protected:

  void draw();

private:

  short a1,a2;

};

#ifndef FLTK_2
#define FL_NORMAL_DIAL	Fl_Dial::NORMAL
#define FL_LINE_DIAL	Fl_Dial::LINE
#define FL_FILL_DIAL	Fl_Dial::FILL
#endif

#endif

//
// End of "$Id$".
//
