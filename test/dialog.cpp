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
#include <efltk/Fl_Int_Input.h>
#include <efltk/Fl_Float_Input.h>
#include <efltk/fl_ask.h>
#include <efltk/Fl_Config_Dialog_DS.h>
#include <efltk/Fl_Date_Time_Input.h>

#include <stdio.h>

#include "smile.xpm"
#include "dialog_dialog.xpm"
#include "dialog_disk.xpm"

Fl_Pixmap smile_pixmap(smile_xpm);
Fl_Pixmap dialog_pixmap_1(dialog_dialog_xpm);
Fl_Pixmap dialog_pixmap_2(dialog_disk_xpm);

Fl_Dialog *dlg;
Fl_Dialog *config_dlg;
Fl_Input *input1, *input2;

Fl_Config my_config("dialog_test.ini");

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
            fname = dialog["first_name"];
            lname = dialog["last_name"];
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

static void cb_test2(Fl_Widget*, void*) {
    switch (config_dlg->show_modal()) {
        case FL_DLG_OK:
            my_config.flush();
            break;
    }
}

void dialog_callback(Fl_Widget *widget,void *data) {
    // we only want to process user-defined buttons here
    if (widget->argument() > Fl_Dialog::BTN_HELP) {
        fl_alert("User defined button clicked.\nButton id is "+Fl_String((int)widget->argument()));
    }
}

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(300,150);

    Fl_Button *btn = new Fl_Button(20,80,120,25,"Simple dialog");
    btn->image(&dialog_pixmap_1);

    // using auto-layout
    input1 = new Fl_Input("First Name");
    input2 = new Fl_Input("Last Name");
    btn->callback(cb_test);

    input1->value("Jonh");
    input2->value("Doe");

    btn = new Fl_Button(170,80,120,25,"Config dialog");
    btn->image(&dialog_pixmap_2);
    btn->callback(cb_test2);

    window->end();
    window->show(argc, argv);

    dlg = new Fl_Dialog(400,300,"Demo dialog");
    dlg->new_group("default");
    // Using auto-layout
    Fl_Input *firstNameInput = new Fl_Input("First Name:");
    firstNameInput->field_name("first_name");
    Fl_Input *lastNameInput = new Fl_Input("Last Name:");
    lastNameInput->field_name("last_name");
    dlg->end();
    dlg->buttons(FL_DLG_OK|FL_DLG_CANCEL|FL_DLG_HELP,FL_DLG_OK);

    // User may add his own buttons. The button bitmap is optional,
    // and it should 20x20 or less if presented. The button id should
    // be unique inside the dialog.
    dlg->user_button(1024,"User Button",&smile_pixmap);

    // This is the callback for the whole dialog. In this test,
    // we process the user buttons in this callback function.
    dlg->callback(dialog_callback);


    // This part of the test illustrates the usage of the Dialog
    // as a 'preferences' dialog box. All the widgets with the defined
    // field names will be stored/restored in the defined config file
    // section.

    // First, define a config file
    Fl_Config my_config("dialog.ini");

    // Second, define a config datasource as a config file and a section
    Fl_Config_Dialog_DS my_config_ds(&my_config);

    // Third, create the dialog with the datasource
    config_dlg = new Fl_Dialog(400,300,"Config dialog",&my_config_ds);
    config_dlg->new_group("default");

    // Using auto-layout

    firstNameInput = new Fl_Input("First Name:");
    firstNameInput->field_name("first_name");

    lastNameInput = new Fl_Input("Last Name:");
    lastNameInput->field_name("last_name");

    Fl_Input *inp;

    inp = new Fl_Float_Input("Age:");
    inp->field_name("age");
    inp->maximum_size(5);

    inp = new Fl_Int_Input("Children:");
    inp->field_name("children");
    inp->maximum_size(3);

    Fl_Date_Input *dinp = new Fl_Date_Input("Date:");
    dinp->field_name("date");

    config_dlg->end();
    config_dlg->buttons(FL_DLG_OK|FL_DLG_CANCEL,FL_DLG_OK);

    return Fl::run();
}

//
// End of "$Id$".
//
