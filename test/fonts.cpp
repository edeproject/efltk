//
// "$Id$"
//
// Font demo program for the Fast Light Tool Kit (FLTK).
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

#include <config.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Browser.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Box.h>
#include <efltk/fl_utf8.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Fl_Window *form;

class FontDisplay : public Fl_Widget {
  void draw();
public:
    Fl_Font font;
    unsigned size;
    const char* encoding;
    FontDisplay(Fl_Boxtype B, int X, int Y, int W, int H, const char* L = 0) :
        Fl_Widget(X,Y,W,H,L) {box(B); font = 0; size = 14;}
};

void FontDisplay::draw() {
  draw_box();
  int ix = 0, iy = 0, iw = w(), ih = h();
  box()->inset(ix, iy, iw, ih);
  fl_push_clip(ix, iy, iw, ih);
  const char* saved_encoding = fl_encoding();
  fl_encoding(encoding);
  fl_font(font, size);
  fl_color(FL_BLACK);
  char buffer[32];
  char outbuf[64];
  for (int Y = 1; Y < 8; Y++) {
      for (int X = 0; X < 32; X++) buffer[X] = (32*Y+X);
#if HAVE_XUTF8
      int len = fl_latin12utf((uint8*)buffer, 32, outbuf);
      fl_draw(outbuf, len, 3, 3+fl_height()*Y);
#else
      fl_draw(buffer, 32, 3, 3+fl_height()*Y);
#endif
  }
  fl_encoding(saved_encoding);
  fl_pop_clip();
}

FontDisplay *textobj;

Fl_Browser *fontobj, *sizeobj, *encobj;

Fl_Font* fonts; // list returned by fltk

Fl_Group *button_group;
Fl_Check_Button* bold_button, *italic_button;
Fl_Box* id_box;

int pickedsize = 14;

void font_cb(Fl_Widget *, long) {
  int fn = fontobj->value();
  //printf("font: %d    name: %s   bigname: %s\n", fn, fonts[fn]->name(), fonts[fn]->system_name());

  Fl_Font f = fonts[fn];
  if (f->bold() == f) bold_button->deactivate();
  else bold_button->activate();
  if (f->italic() == f) italic_button->deactivate();
  else italic_button->activate();
  if (bold_button->value()) f = f->bold();
  if (italic_button->value()) f = f->italic();
  textobj->font = f;

  char saved[30];
  strncpy(saved, textobj->encoding, 29);
  encobj->clear();
  const char** encodings;
  int ne = f->encodings(encodings);
  int picked = -1;
  int iso8859 = 0;
  for (int i = 0; i < ne; i++) {
      encobj->add(encodings[i]);
      if (!strcmp(encodings[i], saved)) picked = i;
      if (!strcmp(encodings[i], fl_encoding())) iso8859 = i;
  }
  if (picked < 0) picked = iso8859;
  textobj->encoding = encodings[picked];
  encobj->value(picked);

  sizeobj->clear();
  int *s;
  int n = f->sizes(s);
  if(!n) {
      // no sizes (this only happens on X)
      fl_font(f, pickedsize);
      textobj->size = (int)fl_height();
  } else if (s[0] == 0) {
      // many sizes;
      int j = 1;
      for (int i = 1; i<64 || i<s[n-1]; i++) {
          char buf[20];
          sprintf(buf,"%d",i);
          Fl_Widget *w = sizeobj->add(buf);
          if (j < n && i==s[j]) {
              w->label_font(w->label_font()->bold());
              w->label_color(FL_RED);
              j++;
          }
      }
      sizeobj->value(pickedsize-1);
      textobj->size = pickedsize;
  } else {
      // some sizes
      int w = 0;
      for (int i = 0; i < n; i++) {
          if (s[i]<=pickedsize) w = i;
          char buf[20];
          sprintf(buf,"%d",s[i]);
          Fl_Widget *w = sizeobj->add(buf);
          w->label_font(w->label_font()->bold());
      }
      sizeobj->value(w);
      textobj->size = s[w];
  }

  encobj->redraw();
  sizeobj->redraw();
  textobj->redraw();
  encobj->relayout();
  sizeobj->relayout();
  textobj->relayout();

  id_box->label(textobj->font->system_name());
  id_box->redraw();
  button_group->redraw();
}

void encoding_cb(Fl_Widget *, long) {
  int i = encobj->value();
// CET - FIXME - new browser code has value starting from 0!
//  if (!i) return;
  textobj->encoding = encobj->text(i);
  textobj->redraw();
  id_box->redraw();
}

void size_cb(Fl_Widget *, long) {
  int i = sizeobj->value();
// CET - FIXME - new browser code has value starting from 0!
//  if (!i) return;
  const char *c = sizeobj->text(i);
  while (*c < '0' || *c > '9') c++;
  pickedsize = atoi(c);
  textobj->size = pickedsize;
  textobj->redraw();
  id_box->redraw();
}

void create_the_forms() {
  form = new Fl_Double_Window(550,390);

  textobj = new FontDisplay(FL_ENGRAVED_BOX,10,10,530,160);
  textobj->clear_flag(FL_ALIGN_MASK);
  textobj->set_flag(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_CLIP);
  id_box = new Fl_Box(10, 172, 530, 15);
  id_box->box(FL_ENGRAVED_BOX);
  id_box->label_size(10);
  id_box->set_flag(FL_ALIGN_INSIDE|FL_ALIGN_CLIP);
  button_group = new Fl_Group(10, 190, 140, 20);
  bold_button = new Fl_Check_Button(0, 0, 70, 20, "Bold");
  bold_button->callback(font_cb, 1);
  italic_button = new Fl_Check_Button(70, 0, 70, 20, "Italic");
  italic_button->callback(font_cb, 1);
  button_group->end();
  fontobj = new Fl_Browser(10, 210, 280, 170);
  fontobj->when(FL_WHEN_CHANGED);
  fontobj->callback(font_cb);
  form->resizable(fontobj);
  encobj = new Fl_Browser(300, 210, 100, 170);
  encobj->when(FL_WHEN_CHANGED);
  encobj->callback(encoding_cb, 1);
  sizeobj = new Fl_Browser(410, 210, 130, 170);
  sizeobj->when(FL_WHEN_CHANGED);
  sizeobj->callback(size_cb);
  form->end();
}

#include <efltk/fl_ask.h>

int main(int argc, char **argv) {
  create_the_forms();
  int numfonts = fl_list_fonts(fonts);

  for(int i = 0; i < numfonts; i++) {
      fontobj->add(fonts[i]->name());
  }

  fontobj->value(0);
  textobj->encoding = fl_encoding();
  font_cb(fontobj,0);
  form->show(argc,argv);
  return Fl::run();
}

//
// End of "$Id$".
//
