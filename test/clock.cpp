//
// Clock demo for eFLTK
//
// "$Id$"
//

#include <efltk/Fl.h>
#include <efltk/Fl_Shaped_Window.h>
#include <efltk/Fl_Round_Clock.h>
#include <efltk/Fl_Menu_Button.h>
#include <efltk/Fl_Item.h>
#include <efltk/fl_ask.h>
#include <stdlib.h>

#include "circle.xbm" // bitmap mask for window shape

class ClockWindow : public Fl_Shaped_Window {
public:
    ClockWindow(int W, int H, const char *l = 0) : Fl_Shaped_Window(W,H,l) {}
    int handle(int);
};

int ClockWindow::handle(int e)
{
    static int bx, by;
    static int button1 = 0;

    if(e == FL_PUSH) button1 = (Fl::event_button() == 1);

    if(button1) {
        switch(e) {
        case FL_DRAG:
            position(x()+Fl::event_x_root()-bx, y()+Fl::event_y_root()-by);
        case FL_PUSH:
            bx = Fl::event_x_root(); by = Fl::event_y_root();
            show(); // so the window will click-to-front
            return 1;
        }
    }
    return Fl_Shaped_Window::handle(e);
}

void callback(Fl_Widget *w, long) {
    int id = ((Fl_Menu_*)w)->item()->argument();
    switch(id) {
    case 1:
        fl_message(
                   "FLTK (C) 1998-2002 Bill Spitzak and others\n"
                   "eFLTK (C) 2002-2003 EDE-Team\n"
                  );
        break;
    case 2:
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    ClockWindow window(220, 220, "Fl_Round_Clock");
    window.color(FL_BLACK);

    // don't show window manager border-- some window managers do this for you
    // if an arbitrary shape is assigned to the window.
    window.clear_border();

    Fl_Round_Clock clock(2,2,216,216);

    Fl_Menu_Button popup(0, 0, 220, 220);
    popup.callback(callback);
    popup.type(Fl_Menu_Button::POPUP3);
    popup.begin();
    Fl_Item *about_item = new Fl_Item("About clock");
    about_item->argument(1);
    Fl_Item *exit_item = new Fl_Item("Exit clock");
    exit_item->argument(2);
    popup.end();

    window.end();

    Fl_Bitmap shape(circle_bits, circle_width, circle_height); // window shape data
    window.shape(shape);

    window.show(argc, argv);
    return Fl::run();
}
