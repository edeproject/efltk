//
// Demo program from the fltk documentation.
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
#include <efltk/Fl_Calendar.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Input.h>

Fl_Popup_Calendar *pc;
Fl_Input          *input;
static void cb_test(Fl_Widget*, void*) {
    if (Fl::event() == FL_BUTTON_PRESSED) {
        char buffer[24];
        pc->popup();
        pc->date().format_date(buffer);
        if (pc->value())
            input->value(buffer);
        else  input->value("Canceled");
    }
}

//#include <efltk/fl_utf8.h>
int main(int argc, char **argv)
{
    Fl_Window *window = new Fl_Window(300,180);

    Fl_Calendar *c = new Fl_Calendar(10,20,150,150,"date:");
    c->box(FL_EMBOSSED_BOX);
    Fl_Button *btn = new Fl_Button(170,70,120,25,"Popup calendar");
    input = new Fl_Input(170,100,120,25);
    btn->callback(cb_test);
    window->end();
    pc = new Fl_Popup_Calendar(btn);
    window->show(argc, argv);

    return Fl::run();
}

//
// End of "$Id$".
//
