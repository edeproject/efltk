//
// "$Id$"
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

#include <efltk/Fl_Window.h>
#include <efltk/x.h>

#include <efltk/Fl.h>
#include <efltk/Fl_WM.h>
#include <efltk/Fl_Box.h>

#include <stdio.h>

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(300,180);

    //Set type to DIALOG
    window->window_type(Fl_WM::DIALOG);

    window->begin();
    Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
    box->box(FL_UP_BOX);
    box->label_font(FL_HELVETICA_BOLD_ITALIC);
    box->label_size(36);
    box->label_type(FL_SHADOW_LABEL);
    window->end();
    window->show(argc, argv);

    return Fl::run();
}

//
// End of "$Id$".
//
