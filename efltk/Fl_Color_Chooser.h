//
// "$Id$"
//
// Color chooser header file for the Fast Light Tool Kit (FLTK).
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

// The color chooser object and the color chooser popup.  The popup
// is just a window containing a single color chooser and some boxes
// to indicate the current and cancelled color.

#ifndef Fl_Color_Chooser_H
#define Fl_Color_Chooser_H

#include "Fl_Group.h"
#include "Fl_Box.h"
#include "Fl_Return_Button.h"
#include "Fl_Choice.h"
#include "Fl_Value_Input.h"

class FL_API Flcc_HueBox : public Fl_Widget {
  int px, py;
protected:
  void draw();
public:
  int handle(int);
  Flcc_HueBox(int X, int Y, int W, int H) : Fl_Widget(X,Y,W,H) {
  px = py = 0;}
};

class FL_API Flcc_ValueBox : public Fl_Widget {
  int py;
protected:
  void draw();
public:
  int handle(int);
  Flcc_ValueBox(int X, int Y, int W, int H) : Fl_Widget(X,Y,W,H) {
  py = 0;}
};

class FL_API Flcc_Value_Input : public Fl_Value_Input {
public:
  int format(char*);
  Flcc_Value_Input(int X, int Y, int W, int H) : Fl_Value_Input(X,Y,W,H) {}
};

class FL_API Fl_Color_Chooser : public Fl_Group {
  Flcc_HueBox huebox;
  Flcc_ValueBox valuebox;
  Fl_Group nrgroup; // no resize group
  Fl_Choice choice;
  Flcc_Value_Input rvalue;
  Flcc_Value_Input gvalue;
  Flcc_Value_Input bvalue;
  double hue_, saturation_, value_;
  double r_, g_, b_;
  void set_valuators();
  static void rgb_cb(Fl_Widget*, void*);
  static void mode_cb(Fl_Widget*, void*);
public:
  int mode() {return choice.value();}
  double h() const {return hue_;}
  double s() const {return saturation_;}
  double v() const {return value_;}
  double r() const {return r_;}
  double g() const {return g_;}
  double b() const {return b_;}
  Fl_Color value() const;
  void value(Fl_Color);
  int hsv(double,double,double);
  int rgb(double,double,double);
  static void hsv2rgb(double, double, double,double&,double&,double&);
  static void rgb2hsv(double, double, double,double&,double&,double&);
  Fl_Color_Chooser(int,int,int,int,const char* = 0);

  static Fl_Named_Style* default_style;
};

FL_API int fl_color_chooser(const char*name,double& r,double& g,double& b);
FL_API int fl_color_chooser(const char*name, uchar& r, uchar& g, uchar& b);
FL_API int fl_color_chooser(const char*name, Fl_Color& c);

#endif

//
// End of "$Id$".
//
