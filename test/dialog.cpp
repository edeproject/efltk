//
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
#include <efltk/Fl_Dialog.h>

static void cb_test(Fl_Widget*, void*) {
   Fl_Dialog dlg(200,100);
   dlg.buttons(FL_DLG_OK|FL_DLG_CANCEL,FL_DLG_OK);
   dlg.show_modal();
}

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(300,180);

    Fl_Button *btn = new Fl_Button(170,70,70,25,"Test dialog");
    btn->callback(cb_test);
    window->end();
    window->show(argc, argv);

    return Fl::run();
}

//
// End of "$Id$".
//
