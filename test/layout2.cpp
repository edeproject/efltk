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

    Fl_Box   *button1 = new Fl_Box("Left",FL_ALIGN_LEFT,40);
    Fl_Box   *button2 = new Fl_Box("Right",FL_ALIGN_RIGHT,40);
    Fl_Box   *button3 = new Fl_Box("Top",FL_ALIGN_TOP,40);
    Fl_Box   *button4 = new Fl_Box("Bottom",FL_ALIGN_BOTTOM,40);
    Fl_Box   *button5 = new Fl_Box("Client",FL_ALIGN_CLIENT);
    Fl_Box   *button6 = new Fl_Box("Left\nat\nthe\nend",FL_ALIGN_LEFT,40);

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
