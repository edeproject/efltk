#include <efltk/Fl.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Window.h>

#include <efltk/Fl_Split.h>

int main(int argc, char *argv[])
{
    Fl_Window *window = new Fl_Window(300,300,"Layout Test");
    Fl_Group *group = new Fl_Group(5,5,290,290);
    window->resizable(group);
    group->layout_align(FL_ALIGN_CLIENT);

    group->begin();

    Fl_Box   *button1 = new Fl_Box("Left",40,FL_ALIGN_LEFT);
                        new Fl_Split(button1);
    Fl_Box   *button2 = new Fl_Box("Right",40,FL_ALIGN_RIGHT);
                        new Fl_Split(button2);
    Fl_Box   *button3 = new Fl_Box("Top",10,FL_ALIGN_TOP);
                        new Fl_Split(button3);
    Fl_Box   *button4 = new Fl_Box("Bottom",40,FL_ALIGN_BOTTOM);
                        new Fl_Split(button4);
    Fl_Box   *button5 = new Fl_Box("Client",40,FL_ALIGN_CLIENT);
    Fl_Box   *button6 = new Fl_Box("Left\nat\nthe\nend",40,FL_ALIGN_LEFT);

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
