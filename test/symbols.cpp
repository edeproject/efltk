//
// "$Id$"
//
// Symbol test program for the Fast Light Tool Kit (FLTK).
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Single_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_Value_Slider.h>
#include <efltk/fl_draw.h>

int N = 0;
#define W 70
#define H 70
#define ROWS 5
#define COLS 5

Fl_Window *window;
Fl_Slider *scale, *rot;

void update()
{
    int rot_val = (int)rot->value();
    int scale_val = (int)scale->value();
    for (int i = window->children(); i--; )
    {
        // all window children
        Fl_Widget *wc = window->child(i);

        if(wc==scale||wc==rot) continue;

        Fl_String str("@");
        if(scale_val>0) {
            str+="+"+Fl_String(scale_val);
        } else if(scale_val<0) {
            str+=Fl_String(scale_val);
        }
        if(rot_val>0) {
            str+=Fl_String(rot_val);
        }
        str+=(char*)wc->user_data();
        wc->copy_label(str.c_str());
    }
    window->redraw();
}

void slider_cb(Fl_Widget *w, void *data) {
    update();
}

void bt(const char *name)
{
  int x = N%COLS;
  int y = N/COLS;
  N++;
  x = x*W+10;
  y = y*H+10;

  Fl_Box *a = new Fl_Box(x,y,W-20,H-20,name);
  a->user_data((void*)(name+1));
  a->align(FL_ALIGN_BOTTOM);
  a->label_size(11);

  Fl_Box *b = new Fl_Box(x,y,W-20,H-20,name);
  b->user_data((void*)(name+1));
  b->align(FL_ALIGN_CLIP);
  b->box(FL_THIN_UP_BOX);
  b->label_type(FL_SYMBOL_LABEL);
  b->label_color(FL_DARK3);
}

int main(int argc, char ** argv) {
  window = new Fl_Single_Window(COLS*W,ROWS*H+90);
bt("@->");
bt("@>");
bt("@>>");
bt("@>|");
bt("@>[]");
bt("@|>");
bt("@<-");
bt("@<");
bt("@<<");
bt("@|<");
bt("@[]<");
bt("@<|");
bt("@<->");
bt("@-->");
bt("@+");
bt("@->|");
bt("@||");
bt("@arrow");
bt("@returnarrow");
bt("@square");
bt("@circle");
bt("@line");
bt("@menu");
bt("@UpArrow");
bt("@DnArrow");

  Fl_Value_Slider slider(80,
                         window->h()-60,
                         window->w()-90,
                         16,
                         "Orientation");
  slider.align(FL_ALIGN_LEFT);
  slider.type(Fl_Slider::HORIZONTAL);
  slider.range(0.0, 9.0);
  slider.value(0.0);
  slider.step(1);
  slider.callback(slider_cb, &slider);

  Fl_Value_Slider slider2(80,
                          window->h()-30,
                          window->w()-90,
                          16,
                          "Scale");
  slider2.align(FL_ALIGN_LEFT);
  slider2.type(Fl_Slider::HORIZONTAL);
  slider2.range(-9.0, 9.0);
  slider2.value(0.0);
  slider2.step(1);
  slider2.callback(slider_cb, &slider);

  rot = &slider;
  scale = &slider2;

  window->resizable(window);
  window->show(argc,argv);
  return Fl::run();
}

//
// End of "$Id$".
//
