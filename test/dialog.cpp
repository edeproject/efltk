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
#include <efltk/Fl_Input.h>
#include <efltk/fl_ask.h>

Fl_Dialog *dlg;

// I'm still thinking on operator [] implementation :(
// It's not a problem if we always have Fl_Input.
// Otherwise, value() should be Fl_Variant and in Fl_Widget.
static void cb_test(Fl_Widget*, void*) {
   Fl_Dialog& dialog = *dlg;
   Fl_Input *fname = (Fl_Input *)dialog["first_name"];
   Fl_Input *lname = (Fl_Input *)dialog["last_name"];
   fname->value("Jonh");
   lname->value("Doe");
   switch (dialog.show_modal()) {
   case FL_DLG_OK:      fl_alert("Ok pressed");
                        break;
   case FL_DLG_CANCEL:  fl_alert("Cancel pressed");
                        break;
   }
}

int main(int argc, char **argv) {
   Fl_Window *window = new Fl_Window(300,180);

   Fl_Button *btn = new Fl_Button(170,70,70,25,"Test dialog");
   btn->callback(cb_test);
   window->end();
   window->show(argc, argv);

   dlg = new Fl_Dialog(400,300);
   dlg->new_page("default");
   Fl_Input *firstNameInput = new Fl_Input(100,20,100,24,"First Name:");
   firstNameInput->field_name("first_name");
   Fl_Input *lastNameInput = new Fl_Input(100,50,100,24,"Last Name:");
   lastNameInput->field_name("last_name");
   dlg->end();
   dlg->buttons(FL_DLG_OK|FL_DLG_CANCEL|FL_DLG_HELP,FL_DLG_OK);
   dlg->relayout();

   return Fl::run();
}

//
// End of "$Id$".
//
