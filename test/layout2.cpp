#include <efltk/Fl.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Window.h>

int main(int argc, char *argv[])
{
    Fl_Window *window = new Fl_Window(300,300,"Layout Test");
    Fl_Group *group = new Fl_Group(5,5,290,290);
    window->resizable(group);
    group->resizable(group);

    group->begin();

    Fl_Button   *button1 = new Fl_Button(30,30,30,30,"Left");
    Fl_Button   *button2 = new Fl_Button(30,30,30,30,"Right");
    Fl_Button   *button3 = new Fl_Button(30,30,30,30,"Top");
    Fl_Button   *button4 = new Fl_Button(30,30,30,30,"Bottom");
    Fl_Button   *button5 = new Fl_Button(50,50,50,50,"Client");
    Fl_Button   *button6 = new Fl_Button(30,30,30,30,"Left\nat\nthe\nend");


    button1->layout_align(FL_ALIGN_LEFT);
    button2->layout_align(FL_ALIGN_RIGHT);
    button3->layout_align(FL_ALIGN_TOP);
    button4->layout_align(FL_ALIGN_BOTTOM);
    button5->layout_align(FL_ALIGN_CLIENT);
    button6->layout_align(FL_ALIGN_LEFT);

    group->end();
    window->end();
    window->show();

    return Fl::run();
}
