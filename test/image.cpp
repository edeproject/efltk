//
// "$Id:"
//
// Test of Fl_Image types for the Fast Light Tool Kit (FLTK).
//
// Notice that Fl_Image is for a static, multiple-reuse image, such
// as an icon or postage stamp.  Use fl_draw_image to go directly
// from an buffered image that changes often.
//
// Copyright 1998-2001 by Bill Spitzak and others.
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

#include <efltk/Fl_Image.h>
#include <efltk/Fl_Pixmap.h>
#include <efltk/Fl_Bitmap.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <stdio.h>
#include <stdlib.h>

#include <efltk/Enumerations.h>

////////////////////////////////////////////////////////////////

#include "escherknot.xbm"
Fl_Bitmap bitmap(escherknot_bits, escherknot_width, escherknot_height);

////////////////////////////////////////////////////////////////

#include "porsche.xpm"
//Fl_Image pixmap = *Fl_Image::read_xpm(0, porsche_xpm);
Fl_Pixmap pixmap(porsche_xpm);

////////////////////////////////////////////////////////////////

#define WIDTH 75
#define HEIGHT 75
uchar* make_image()
{
    // pitch = WORD alignment bits per line
    int pitch=Fl_Renderer::calc_pitch(3, WIDTH);
    int skip = pitch - WIDTH * 3;

    uchar *image = new uchar[HEIGHT*pitch];
    uchar *p = image;

    for (int y = 0; y < HEIGHT; y++) {
        double Y = double(y)/(HEIGHT-1);
        for (int x = 0; x < WIDTH; x++) {
            double X = double(x)/(WIDTH-1);
            *p++ = uchar(255*((1-X)*(1-Y))); // red in upper-left
            *p++ = uchar(255*((1-X)*Y));	// green in lower-left
            *p++ = uchar(255*(X*Y));	// blue in lower-right
        }
        p+=skip;
    }
    return image;
}

// Make RGB image
Fl_Image rgb_image(WIDTH, HEIGHT, 24, make_image(), 0x0000FF, 0x00FF00, 0xFF0000, 0 ,0);

////////////////////////////////////////////////////////////////

#include <efltk/Fl_Toggle_Button.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Choice.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Box.h>

Fl_Check_Button *leftb,*rightb,*topb,*bottomb,*insideb,*tileb,
  *clipb, *wrapb, *scaleb;
Fl_Button *b;
Fl_Window *w;

void button_cb(Fl_Widget *,void *) {
  int i = 0;
  if (leftb->value()) i |= FL_ALIGN_LEFT;
  if (rightb->value()) i |= FL_ALIGN_RIGHT;
  if (topb->value()) i |= FL_ALIGN_TOP;
  if (bottomb->value()) i |= FL_ALIGN_BOTTOM;
  if (insideb->value()) i |= FL_ALIGN_INSIDE;
  if (clipb->value()) i |= FL_ALIGN_CLIP;
  if (wrapb->value()) i |= FL_ALIGN_WRAP;
  if (tileb->value()) i |= FL_ALIGN_TILED;
  if (scaleb->value()) i |= FL_ALIGN_SCALE;
  b->clear_flag(FL_ALIGN_MASK);
  b->set_flag(i);
  w->redraw();
}

void choice_cb(Fl_Widget* item, void* data) {
  b->label(item->label());
  b->image((Fl_Image*)data);
  w->redraw();
}

#ifndef _WIN32
#include <efltk/x.h>
#include "list_visuals.cpp"

int visid = -1;
int arg(int argc, char **argv, int &i) {
    if (argv[i][1] == 'v') {
        if (i+1 >= argc) return 0;
        visid = atoi(argv[i+1]);
        i += 2;
        return 2;
    }
    return 0;
}
#endif

int main(int argc, char **argv)
{
#ifndef _WIN32
    int i = 1;
    if (Fl::args(argc,argv,i,arg) < argc) {
        fprintf(stderr," -v # : use visual\n%s\n",Fl::help);
        exit(1);
    }

    if (visid >= 0) {
        fl_open_display();
        XVisualInfo templt; int num;
        templt.visualid = visid;
        fl_visual = XGetVisualInfo(fl_display, VisualIDMask, &templt, &num);
        if (!fl_visual) {
            fprintf(stderr, "No visual with id %d, use one of:\n",visid);
            list_visuals();
            exit(1);
        }
        fl_colormap = XCreateColormap(fl_display, RootWindow(fl_display,fl_screen),
                                      fl_visual->visual, AllocNone);
        fl_xpixel(FL_BLACK); // make sure black is allocated in overlay visuals
    } else {
        Fl::visual(FL_RGB);
    }
#endif

    //Fl_Double_Window window(300,300); ::w = &window;
    Fl_Window window(400,300); ::w = &window;

    Fl_Toggle_Button b(100,55,100,100,"Fl_Pixmap"); ::b = &b;
    b.image(pixmap);
    b.tooltip("This Fl_Toggle_Button has:\n"
              "image() set to the Fl_Image class selected below.\n"
              "label() set to the name of that class.\n"
              "align() set to the flags selected below.\n"
              "Be sure to resize the window to see how it lays out");

#define BWIDTH 60
#define BHEIGHT 21

    Fl_Group controls(10, 300-3*BHEIGHT-20, 380, 3*BHEIGHT+10);
    controls.box(FL_ENGRAVED_BOX);

    Fl_Choice choice(5, 5, 110, BHEIGHT);
    choice.begin();
    Fl_Item i1("Fl_Bitmap");
    i1.callback(choice_cb, &bitmap);
    Fl_Item i2("Fl_Pixmap");
    i2.callback(choice_cb, &pixmap);
    Fl_Item i3("Fl_RGB_Image");
    i3.callback(choice_cb, &rgb_image);
    choice.end();
    choice.value(1); // set it to pixmap
    choice.tooltip("Subclass of Fl_Image to use");

    int y = 5+BHEIGHT;
    int x = 5;
    topb = new Fl_Check_Button(x, y, BWIDTH, BHEIGHT, "top"); x += BWIDTH;
    topb->callback(button_cb);
    topb->tooltip("FL_ALIGN_TOP");
    bottomb= new Fl_Check_Button(x, y, BWIDTH, BHEIGHT, "bottom");x += BWIDTH;
    bottomb->callback(button_cb);
    bottomb->tooltip("FL_ALIGN_BOTTOM");
    leftb = new Fl_Check_Button(x, y, BWIDTH, BHEIGHT, "left"); x += BWIDTH;
    leftb->callback(button_cb);
    leftb->tooltip("FL_ALIGN_LEFT");
    rightb = new Fl_Check_Button(x, y, BWIDTH, BHEIGHT, "right"); x += BWIDTH;
    rightb->callback(button_cb);
    rightb->tooltip("FL_ALIGN_RIGHT");
    scaleb = new Fl_Check_Button(x, y, BWIDTH, BHEIGHT, "scale"); x += BWIDTH;
    scaleb->callback(button_cb);
    scaleb->tooltip("FL_ALIGN_SCALE");
    y += BHEIGHT;
    x = 5;
    insideb= new Fl_Check_Button(x, y, BWIDTH, BHEIGHT, "inside");x += BWIDTH;
    insideb->callback(button_cb);
    insideb->tooltip("FL_ALIGN_INSIDE");
    clipb= new Fl_Check_Button(x, y, BWIDTH, BHEIGHT, "clip"); x += BWIDTH;
    clipb->callback(button_cb);
    clipb->tooltip("FL_ALIGN_CLIP");
    wrapb= new Fl_Check_Button(x, y, BWIDTH, BHEIGHT, "wrap"); x += BWIDTH;
    wrapb->callback(button_cb);
    wrapb->tooltip("FL_ALIGN_WRAP");
    tileb= new Fl_Check_Button(x, y, BWIDTH, BHEIGHT, "tile"); x += BWIDTH;
    tileb->callback(button_cb);
    tileb->tooltip("FL_ALIGN_TILED");

    controls.end();

    Fl_Box box(10,0,290,controls.y());
    box.hide();
    window.resizable(box);
    window.end();
    window.show(argc, argv);
    return Fl::run();
}

//
// End of "$Id$".
//
