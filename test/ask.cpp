//
// Standard dialogs demo for eFLTK
//
// $Id$

#include <stdlib.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Return_Button.h>
#include <efltk/fl_ask.h>

// Popup dialog and rename widget, if OK pressed
void rename_me(Fl_Widget *o)
{
    if (Fl::event() == FL_BUTTON_PRESSED) {
        const char *input = fl_input("Input:", o->label());
        if(input) {
            o->label(input);
            o->redraw();
        }
    }
}

void window_callback(Fl_Widget*)
{
    if (Fl::event() == FL_WINDOW_CLOSE) {
        if(!fl_ask("Are you sure you want to quit?")) {
            return;
        }
        exit(0);
    }
}

int main(int argc, char **argv)
{
    Fl_Window window(200, 55);

    Fl_Return_Button b(20, 10, 160, 35, "Test text");
    b.callback(rename_me);

    // Also we test to see if the exit callback works:
    window.callback(window_callback);
    window.show(argc, argv);

    return Fl::run();
}
