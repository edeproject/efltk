//
// "$Id$"
//
// Input field test program for the Fast Light Tool Kit (FLTK).
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

#include <stdio.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Float_Input.h>
#include <efltk/Fl_Int_Input.h>
#include <efltk/Fl_Secret_Input.h>
#include <efltk/Fl_Wordwrap_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Toggle_Button.h>
#include <efltk/fl_show_colormap.h>

#define INPUTS  7

void cb(Fl_Widget *ob) {
    printf("Callback for %s '%s'\n", ob->label().c_str(), ((Fl_Input*)ob)->value());
}

int when = 0;
Fl_Input *input[INPUTS];

void toggle_cb(Fl_Widget *o, long v) {
  if (((Fl_Toggle_Button*)o)->value()) when |= v; else when &= ~v;
  for (int i=0; i<INPUTS; i++) input[i]->when(when);
}

void test(Fl_Input *i) {
  if (i->changed()) {
    i->clear_changed(); printf("%s '%s'\n", i->label().c_str(), i->value());
  }
}

void button_cb(Fl_Widget *,void *) {
  for (int i=0; i<INPUTS; i++) test(input[i]);
}

void color_cb(Fl_Widget* button, void* v) {
  Fl_Style& s = *Fl_Input::default_style;
  Fl_Color c;
  
  switch ((long)v) {
    case 0: c = s.color; break;
    case 1: c = s.selection_color; break;
    case 3: c = s.button_color; break;
    case 4: c = s.selection_text_color; break;
    default: c = s.text_color; break;
  }
  c = fl_show_colormap(c);
  switch ((long)v) {
    case 0: s.color = c; break;
    case 1: s.selection_color = c; break;
    case 3: s.button_color = c; break;
    case 4: s.selection_text_color = c; break;
    default: s.text_color = c; break;
  }
  //s.selection_text_color = fl_contrast(s.text_color, s.selection_color);
  button->color(c);
  button->label_color(c);
  Fl::redraw();
}

int main(int argc, char **argv) {

  Fl_Window *window = new Fl_Window(400,400);

  int y = 10;
  input[0] = new Fl_Input(70,y,300,23,"Normal:"); y += 27;
  input[0]->tooltip("Normal input field");
  input[0]->box(FL_NO_BOX);
  // input[0]->cursor_color(FL_SELECTION_COLOR);
  //  input[0]->maximum_size(20);
  // input[0]->static_value("this is a testgarbage");
  input[1] = new Fl_Float_Input(70,y,300,23,"Float:"); y += 27;
  input[1]->tooltip("Input field for floating-point number");
  input[2] = new Fl_Int_Input(70,y,300,23,"Int:"); y += 27;
  input[2]->tooltip("Input field for integer number");
  input[3] = new Fl_Secret_Input(70,y,300,23,"Secret:"); y += 27;
  input[3]->tooltip("Input field for password");
  input[4] = new Fl_Wordwrap_Input(70,y,300,70,"Wordwrap:"); y += 75;
  input[4]->tooltip("Input field for short text with newlines");
  input[5] = new Fl_Input(70,y,300,23,"Right al."); y += 30;
  input[5]->text_align(FL_ALIGN_RIGHT);
  input[5]->tooltip("Input field with text aligned to right");
  input[6] = new Fl_Input(70,y,300,23,"Center"); y += 30;
  input[6]->text_align(FL_ALIGN_CENTER);
  input[6]->tooltip("Input field with text aligned to center");

  for (int i = 0; i < INPUTS; i++) {
    input[i]->when(0); input[i]->callback(cb);
  }
  int y1 = y;

// silly replacements for the FL_WHEN_* constants, but at least now compiles
  Fl_Button *b;
  b = new Fl_Toggle_Button(10,y,200,23,"FL_WHEN_&CHANGED");
  b->tooltip("Do callback each time the text changes");
  b->callback(toggle_cb, FL_DATA_CHANGE); y += 23;
  b = new Fl_Toggle_Button(10,y,200,23,"FL_WHEN_&RELEASE");
  b->callback(toggle_cb, FL_MOUSE_RELEASE); y += 23;
  b->tooltip("Do callback when widget loses focus");
  b = new Fl_Toggle_Button(10,y,200,23,"FL_WHEN_&ENTER_KEY");
  b->callback(toggle_cb, FL_BUTTON_PRESSED); y += 23;
  b->tooltip("Do callback when user hits Enter key");
  b = new Fl_Toggle_Button(10,y,200,23,"FL_WHEN_&NOT_CHANGED");
  b->callback(toggle_cb, FL_MOUSE_LEAVE); y += 23;
  b->tooltip("Do callback even if the text is not changed");
  y += 5;

  b = new Fl_Button(10,y,200,23,"&print changed()");
  b->callback(button_cb);
  b->tooltip("Print widgets that have changed() flag set");

  b = new Fl_Button(220,y1,130,23,"color"); y1 += 23;
  b->label_color(input[0]->color()); b->callback(color_cb, (void*)0);
  b->tooltip("Color behind the text");

  b = new Fl_Button(220,y1,130,23,"button color"); y1 += 23;
  b->label_color(input[0]->button_color()); b->callback(color_cb, (void*)3);
  b->tooltip("Cursor color");

  b = new Fl_Button(220,y1,130,23,"text_color"); y1 += 23;
  b->label_color(input[0]->text_color()); b->callback(color_cb, (void*)2);
  b->tooltip("Color of the text");

  b = new Fl_Button(220,y1,130,23,"selection_color"); y1 += 23;
  b->label_color(input[0]->selection_color()); b->callback(color_cb, (void*)1);
  b->tooltip("Color behind selected text");

  b = new Fl_Button(220,y1,130,23,"selection_text_color"); y1 += 23;
  b->label_color(input[0]->selection_text_color()); b->callback(color_cb, (void*)4);
  b->tooltip("Text color, when selected");


  window->resizable(window);
  window->end();
  window->show(argc,argv);

  return Fl::run();
}

//
// End of "$Id$".
//
