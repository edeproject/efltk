#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Date_Time_Input.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_ListView.h>

int main(int argc,char *argv[]) {
    Fl_Window   *window = new Fl_Window(500,400,"Group grow test");

    Fl_Group *group = new Fl_Group(10,20,30,30,"Auto-grow group");
    group->box(FL_THIN_DOWN_BOX);
    group->auto_grow(FL_GROUP_GROW_BOTH);

    Fl_Input *inp;

    inp = new Fl_Input("Input 1");
    inp->maximum_size(3);

    inp = new Fl_Input("Input 2");
    inp->maximum_size(6);

    inp = new Fl_Input("Input 3");
    inp->maximum_size(9);

    inp = new Fl_Input("Input 4");
    inp->maximum_size(20);

    new Fl_Date_Input("Date Input");

    new Fl_ListView("List View",100);

    group->end();
    window->end();

    window->show(argc,argv);
    Fl::run();

    return 0;
}
