#include <efltk/Fl.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_Text_Editor.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Split.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Window.h>

#include <efltk/Fl_Split.h>

int main(int argc, char *argv[])
{
    // First window demonstrates the use of Fl_Split with
    // the new layout style
    Fl_Window *window = new Fl_Window(300,300,"Fl_Split and new style layout");

    Fl_Group *grp1 = new Fl_Group("");

    new Fl_Button("Button 1",70,FL_ALIGN_LEFT);
    new Fl_Button("Button 2",70,FL_ALIGN_LEFT);
    new Fl_Button("Button 3",70,FL_ALIGN_LEFT);

    grp1->box(FL_THIN_UP_BOX);
    grp1->layout_spacing(2);
    grp1->end();

    Fl_ListView *lv = new Fl_ListView("",150,FL_ALIGN_BOTTOM);
    new Fl_Split(lv);

    Fl_Text_Editor *editor = new Fl_Text_Editor("",10,FL_ALIGN_CLIENT);
    editor->buffer(new Fl_Text_Buffer);

    window->end();
    window->show();


    return Fl::run();
}
