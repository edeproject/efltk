//
// "$Id$"
//
// Color chooser test program for the Fast Light Tool Kit (FLTK).
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

#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Renderer.h>
#include <efltk/fl_show_colormap.h>
#include <efltk/Fl_Color_Chooser.h>
#include <efltk/x.h>
#include <efltk/fl_draw.h>

#include <stdlib.h>
#include <stdio.h>
#ifndef _WIN32
#include "list_visuals.cpp"
#endif

int width = 75;
int height = 75;
uchar *image;

void make_image() {
    // pitch = WORD alignment bits per line
    int pitch=Fl_Renderer::calc_pitch(3, width);
    int skip = pitch - width * 3;

    image = new uchar[height*pitch];
    uchar *p = image;

    for (int y = 0; y < height; y++) {
        double Y = double(y)/(height-1);
        for (int x = 0; x < width; x++) {
            double X = double(x)/(width-1);
            *p++ = uchar(255*((1-X)*(1-Y))); // red in upper-left
            *p++ = uchar(255*((1-X)*Y));	// green in lower-left
            *p++ = uchar(255*(X*Y));	// blue in lower-right
        }
        p+=skip;
    }
}


class Pens : public Fl_Box {
  void draw();
public:
  Pens(int X, int Y, int W, int H, const char* L)
    : Fl_Box(X,Y,W,H,L) {}
};
void Pens::draw() {
  // use every color in the gray ramp:
  for (int i = 0; i < 3*8; i++) {
    fl_color((Fl_Color)(FL_GRAY_RAMP+i));
    fl_line(i, 0, i, h());
  }
}

Fl_Color c = FL_GRAY;
#define fullcolor_cell (FL_FREE_COLOR)

void cb1(Fl_Widget *, void *v) {
  c = fl_show_colormap(c);
  Fl_Box* b = (Fl_Box*)v;
  b->color(c);
  b->parent()->redraw();
}

void cb2(Fl_Widget *, void *v) {
  uchar r,g,b;
//  Fl::get_color(c,r,g,b);
  fl_get_color(c,r,g,b);
  if (!fl_color_chooser("New color:",r,g,b)) return;
  c = fullcolor_cell;
  fl_set_color(fullcolor_cell, fl_rgb(r,g,b));
  Fl_Box* bx = (Fl_Box*)v;
  bx->color(fullcolor_cell);
  bx->parent()->redraw();
}

int main(int argc, char ** argv) {
  fl_set_color(fullcolor_cell, fl_rgb(145,159,170));
  Fl_Window window(400,400);
  Fl_Box box(50,50,300,300);
  box.box(FL_THIN_DOWN_BOX);
  c = fullcolor_cell;
  box.color(c);
  Fl_Button b1(140,120,120,30,"fl_show_colormap");
  b1.callback(cb1,&box);
  Fl_Button b2(140,160,120,30,"fl_choose_color");
  b2.callback(cb2,&box);
  Fl_Box image_box(140,200,120,120,0);
  make_image();

  image_box.image(new Fl_Image(width, height, 24, image, 0x0000FF, 0x00FF00, 0xFF0000, 0 ,0));

  Fl_Box b(140,320,120,0,"Example of fl_draw_image()");
  Pens p(80,200,3*8,120,"lines");
  p.set_flag(FL_ALIGN_TOP);
  int i = 1;
  if (!Fl::args(argc,argv,i) || i != argc-1) {
    printf("usage: %s <switches> visual-number\n"
	   " - : default visual\n"
	   " r : call Fl::visual(FL_RGB)\n"
	   " c : call Fl::own_colormap()\n",argv[0]);
#ifndef _WIN32
    printf(" # : use this visual with an empty colormap:\n");
    list_visuals();
#endif
    puts(Fl::help);
    exit(1);
  }
  if (argv[i][0] == 'r') {
    if (!Fl::visual(FL_RGB)) printf("Fl::visual(FL_RGB) returned false.\n");
  } else if (argv[i][0] == 'c') {
    Fl::own_colormap();
  } else if (argv[i][0] != '-') {
#ifndef _WIN32
    int visid = atoi(argv[i]);
    fl_open_display();
    XVisualInfo templt; int num;
    templt.visualid = visid;
    fl_visual = XGetVisualInfo(fl_display, VisualIDMask, &templt, &num);
    if (!fl_visual) Fl::fatal("No visual with id %d",visid);
    fl_colormap = XCreateColormap(fl_display, RootWindow(fl_display,fl_screen),
				  fl_visual->visual, AllocNone);
    fl_xpixel(FL_BLACK); // make sure black is allocated
#else
    Fl::fatal("Visual id's not supported on MSWindows");
#endif
  }
  window.show(argc,argv);
  return Fl::run();
}

//
// End of "$Id$".
//
