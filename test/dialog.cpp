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
#include <efltk/fl_ask.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Calendar.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Dialog.h>
#include <efltk/Fl_Input.h>
#include <efltk/fl_ask.h>

#include <stdio.h>

#include "smile.xpm"
Fl_Pixmap smile_pixmap(smile_xpm);

Fl_Dialog *dlg;
Fl_Input *input1, *input2;

static void cb_test(Fl_Widget*, void*) {
    char buffer[128];
    Fl_Dialog& dialog = *dlg;
   // define widgets contents
    dialog["first_name"] = input1->value();
    dialog["last_name"]  = input2->value();
   // show modal dialog, and get results after it's closed
    Fl_String fname, lname;
    switch (dialog.show_modal()) {
        case FL_DLG_OK:      
            fname = dialog["first_name"].get_string();
            lname = dialog["last_name"].get_string();
            sprintf(buffer,"Ok pressed, %s %s",
                fname.c_str(), lname.c_str()
            );
            fl_alert(buffer);
            input1->value(fname);
            input2->value(lname);
            break;
        case FL_DLG_CANCEL:  fl_alert("Cancel pressed");
            break;
    }
}

void dialog_callback(Fl_Widget *widget,void *data) {
    // we only need dialog buttons' events here
    if (Fl::event() == FL_DIALOG_BTN) { 
        // we only want to process user-defined buttons here
        if (widget->argument() > Fl_Dialog::BTN_HELP) {
            fl_alert("User defined button clicked.\nButton id is "+Fl_String((int)widget->argument()));
        }
    }
}

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(300,180);

    Fl_Button *btn = new Fl_Button(170,70,70,25,"Test dialog");
    input1 = new Fl_Input(100,10,70,22,"First Name");
    input2 = new Fl_Input(100,35,70,22,"Last Name");
    btn->callback(cb_test);

    input1->value("Jonh");
    input2->value("Doe");

    window->end();
    window->show(argc, argv);

    dlg = new Fl_Dialog(400,300,"Demo dialog");
    dlg->new_page("default");
    Fl_Input *firstNameInput = new Fl_Input(100,20,100,24,"First Name:");
    firstNameInput->field_name("first_name");
    Fl_Input *lastNameInput = new Fl_Input(100,50,100,24,"Last Name:");
    lastNameInput->field_name("last_name");
    dlg->end();
    dlg->buttons(FL_DLG_OK|FL_DLG_CANCEL|FL_DLG_HELP,FL_DLG_OK);

    // User may add his own buttons. The button bitmap is optional,
    // and it should 20x20 or less if presented. The button id should 
    // be unique inside the dialog.
    dlg->user_button(1024,"User Button",&smile_pixmap);

    dlg->callback(dialog_callback);

    return Fl::run();
}

//
// End of "$Id$".
//
