//
// Calendar demo for eFLTK
//
// $Id$
//

#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Calendar.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Input.h>

Fl_Popup_Calendar *pc;
Fl_Input          *input;

static void cb_test(Fl_Widget*, void*)
{
    if (Fl::event() == FL_BUTTON_PRESSED) {
        char buffer[36];
        pc->popup();
        pc->date().format_date(buffer);
        if(pc->value()) input->value(buffer);
        else            input->value("Cancelled");
    }
}

int main(int argc, char **argv)
{
    Fl_Window *window = new Fl_Window(200,200);
    window->resizable(window);

    new Fl_Calendar("", -1, FL_ALIGN_CLIENT);

    Fl_Group group("",-1,FL_ALIGN_BOTTOM);
    group.auto_grow(FL_GROUP_GROW_BOTH);

    Fl_Button *btn = new Fl_Button("Popup calendar", 0, FL_ALIGN_RIGHT);
    btn->callback(cb_test);

    input = new Fl_Input("",0,FL_ALIGN_CLIENT,-1);

    group.end();

    window->end();
    window->show(argc, argv);

    pc = new Fl_Popup_Calendar(btn);

    return Fl::run();
}
