#include <efltk/Fl.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Window.h>

#include <efltk/Fl_Split.h>

int main(int argc, char *argv[])
{
    // First window demonstrates the use of Fl_Split with
    // the new layout style
    Fl_Window *window = new Fl_Window(300,300,"Fl_Split and new style layout");
    Fl_Group *group = new Fl_Group(5,5,290,290);
    window->resizable(group);
    group->layout_align(FL_ALIGN_CLIENT);

    group->begin();

    Fl_Box   *button1 = new Fl_Box("Left",40,FL_ALIGN_LEFT);
    Fl_Split *split1  = new Fl_Split(button1);
    Fl_Box   *button2 = new Fl_Box("Right",40,FL_ALIGN_RIGHT);
    Fl_Split *split2  = new Fl_Split(button2);
    Fl_Box   *button3 = new Fl_Box("Top",10,FL_ALIGN_TOP);
    Fl_Split *split3  = new Fl_Split(button3);
    Fl_Box   *button4 = new Fl_Box("Bottom",40,FL_ALIGN_BOTTOM);
    Fl_Split *split4  = new Fl_Split(button4);
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

    // Second window demonstrates the use of Fl_Split with the
    // old style layouting (eg. X Y W H give)
    window = new Fl_Window(300,300,"Fl_Split and old style positioning");
    group = new Fl_Group(5,5,290,290);
	group->layout_align(FL_ALIGN_CLIENT);    
    
    group->begin();

    button1 = new Fl_Box(5, 5, 40, 290,"Left");
    split1  = new Fl_Split(45, 5, 5, 290);

    button2 = new Fl_Box(255,5,40,290,"Right");
    split2  = new Fl_Split(250,5,5,290);

    button3 = new Fl_Box(50,5,200,20,"Top");
    split3  = new Fl_Split(50,25,200,5);

    button4 = new Fl_Box(50,255,200,40,"Bottom");
    split4  = new Fl_Split(50,250,200,5);

	button5 = new Fl_Box(50,30,200,220,"Client");

    button1->box(FL_THIN_UP_BOX);
    button2->box(FL_THIN_UP_BOX);
    button3->box(FL_THIN_UP_BOX);
    button4->box(FL_THIN_UP_BOX);
    button5->box(FL_THIN_UP_BOX);

	window->resizable(group);
	group->resizable(button5);

    group->end();
    window->end();
    window->show();


    return Fl::run();
}