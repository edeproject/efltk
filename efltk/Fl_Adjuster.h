//
// "$Id$"
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

// Undocumented valuator provided for back-compatability.
// This may be removed before the final version.
// 3-button "slider", made for Nuke

#ifndef Fl_Adjuster_H
#define Fl_Adjuster_H

#ifndef Fl_Valuator_H
#include "Fl_Valuator.h"
#endif

class FL_API Fl_Adjuster : public Fl_Valuator {
public:
  Fl_Adjuster(int x,int y,int w,int h,const char *l=0);
  static Fl_Named_Style* default_style;
  void soft(int x) {soft_ = x;}
  int soft() const {return soft_;}
  int handle(int);

protected:
  void draw();
  void value_damage();

private:
  int drag, highlight, last;
  int ix;
  int soft_;
};

#endif

//
// End of "$Id$".
//
