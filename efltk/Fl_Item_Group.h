//
// "$Id$"
//
// Widget designed to be a nested list in a menu or browser.
// Code is in Fl_Item.cxx
//
// Copyright 1998-2000 by Bill Spitzak and others.
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

#ifndef Fl_Item_Group_H
#define Fl_Item_Group_H

#include "Fl_Group.h"

class FL_API Fl_Item_Group : public Fl_Group {
public:
  void draw();
  void layout();
  Fl_Item_Group(const char* label = 0);
};

#endif
