//
// Another button demo for eFLTK
//
// $Id$
//

#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Return_Button.h>
#include <efltk/Fl_Repeat_Button.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Radio_Button.h>
#include <efltk/Fl_Light_Button.h>
#include <efltk/Fl_Highlight_Button.h>

int main(int argc, char ** argv)
{
    Fl_Window *window = new Fl_Window(0,0,"Buttons test");
    window->auto_grow(FL_GROUP_GROW_BOTH);

    new Fl_Button("Fl_Button");
    new Fl_Return_Button("Fl_Return_Button");
    new Fl_Repeat_Button("Fl_Repeat_Button");
    new Fl_Highlight_Button("Fl_Highlight_Button");
    new Fl_Light_Button("Fl_Light_Button");
    new Fl_Radio_Button("Fl_Radio_Button");
    new Fl_Radio_Button("Fl_Radio_Button");
    new Fl_Check_Button("Fl_Check_Button");

    window->resizable(window);
    window->end();
    window->show(argc,argv);

    return Fl::run();
}
