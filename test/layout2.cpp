#include <efltk/Fl.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Window.h>

int main(int argc, char *argv[])
{
    Fl_Window *window = new Fl_Window(300,300,"Layout Test");
    Fl_Group *group = new Fl_Group(5,5,290,290);
    window->resizable(group);
    group->layout_align(FL_ALIGN_CLIENT);

    group->begin();

    Fl_Box   *button1 = new Fl_Box(30,30,30,30,"Left");
    Fl_Box   *button2 = new Fl_Box(30,30,30,30,"Right");
    Fl_Box   *button3 = new Fl_Box(30,30,30,30,"Top");
    Fl_Box   *button4 = new Fl_Box(30,30,30,30,"Bottom");
    Fl_Box   *button5 = new Fl_Box(50,50,50,50,"Client");
    Fl_Box   *button6 = new Fl_Box(30,30,30,30,"Left\nat\nthe\nend");


    button1->layout_align(FL_ALIGN_LEFT);
    button2->layout_align(FL_ALIGN_RIGHT);
    button3->layout_align(FL_ALIGN_TOP);
    button4->layout_align(FL_ALIGN_BOTTOM);
    button5->layout_align(FL_ALIGN_CLIENT);
    button6->layout_align(FL_ALIGN_LEFT);

    button1->box(FL_THIN_UP_BOX);
    button2->box(FL_THIN_UP_BOX);
    button3->box(FL_THIN_UP_BOX);
    button4->box(FL_THIN_UP_BOX);
    button5->box(FL_THIN_UP_BOX);
    button6->box(FL_THIN_UP_BOX);

    group->end();
    window->end();
    window->show();

    return Fl::run();
}
