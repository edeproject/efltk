//
// $Id$
//
// Slider widget demo for eFLTK
//

#include <efltk/Fl_Slider.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl.h>

Fl_Box *info_box;
Fl_Slider *control;
Fl_Slider *fast;
Fl_Slider *slow;

static void cb_control(Fl_Slider* o, void*)
{
    static int event_count=0;
    Fl_String label;

    switch(Fl::event()) {
    case FL_VALUATOR_DOWN:
    case FL_VALUATOR_UP:
        event_count=0;
        break;

    case FL_VALUATOR_DRAGGED:
        label.printf("Last event: FL_VALUATOR_DRAGGED, Count: %d", ++event_count);
        fast->value(o->value());
        break;

    case FL_VALUATOR_CHANGED:
        label.printf("Last event: FL_VALUATOR_CHANGED, Count: %d", ++event_count);
        fast->value(o->value());
        slow->value(o->value());
        break;
    };

    info_box->label(label);
    info_box->redraw();
}

int main (int argc, char **argv)
{
    Fl_Window win(300, 420, "fast_slow test");

    Fl_Box *box = new Fl_Box(1, 1, 298, 200,
                             "The left slider process FL_VALUATOR_DRAGGED and FL_VALUATOR_CHANGED events in callback.\n\n"
                             "The middle slider (representing a widget with low overhead) is changed on every mouse movement by FL_VALUATOR_DRAGGED\n\n"
                             "The right slider (representing a widget with high overhead) is only updated when value changed by FL_VALUATOR_CHANGED.");
    box->align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
    box->box(FL_THIN_DOWN_BOX);
    box->color(FL_WHITE);

    control = new Fl_Slider(80, 210, 30, 150, "Move\nthis");
    control->callback((Fl_Callback*)cb_control);

    fast = new Fl_Slider(140, 210, 30, 150, "Fast\nredraw");
    fast->set_output();

    slow = new Fl_Slider(200, 210, 30, 150, "Slow\nredraw");
    slow->set_output();

    info_box = new Fl_Box(1, 400, 300, 19, "Last event: None, Count: 0");
    info_box->label_size(10);
    info_box->box(FL_THIN_DOWN_BOX);

    win.end();
    win.show(argc, argv);
    return  Fl::run();
}
