/*
    Signal/Slot example
*/

#include <efltk/Fl.h>
#include <efltk/Fl_Widget.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Input.h>

/*
NOTES:
1) Fl_Widget::set_label() doesn't redraw the label... why ?!
2) FL_CALLBACK remained, FL_CHANGED already defined for something else
2) It would be too complicated to add FL_WINDOW_CLOSE. FL_CALLBACK
   is emitted in do_callback. In order to use FL_WINDOW_CLOSE, the
   window::handle couldn't use do_callback, but than it won't be
   back compatible...
*/

static void bye_bye(Fl_Widget*, void *)
{
    printf("Bye-Bye!\n");
}

static void show_visibility(Fl_Widget*w, void *)
{
    printf("Visible: %s!\n", w->visible()?"yes":"no");
}

int main()
{
    Fl_Window win(400,200);
        Fl_Group grp_left(0, 200, FL_ALIGN_LEFT);
            Fl_Check_Button b0("(de)activate", 20, FL_ALIGN_TOP);
            Fl_Check_Button b1("show/hide", 20, FL_ALIGN_TOP);
            Fl_Input  i0("Some text:", 20, FL_ALIGN_TOP, 50);
        grp_left.end();
        Fl_Group grp("This is a group", 0, FL_ALIGN_CLIENT);
            grp.box(FL_UP_BOX);
            grp.align(FL_ALIGN_CENTER);
            Fl_Button nop0("Nop", 20, FL_ALIGN_TOP);
            Fl_Button nop1("Nop", 20, FL_ALIGN_TOP);
            Fl_Button nop2("Nop", 20, FL_ALIGN_TOP);
        grp.end();
    win.end();

    b0.value(1);
    b1.value(1);

    // make connections
    // this is the most interesting part
    b0.connect(FL_VALUE_CHANGED, SLOT(&grp, slot_active));
    b1.connect(FL_VALUE_CHANGED, SLOT(&grp, slot_visibility));
    i0.connect(FL_VALUE_CHANGED, SLOT(&grp, slot_label));
    win.connect(FL_WINDOW_CLOSE, STATIC_SLOT(bye_bye));
    grp.connect(FL_SHOW, STATIC_SLOT(show_visibility));
    grp.connect(FL_HIDE, STATIC_SLOT(show_visibility));
    // ---

    win.show();
    return Fl::run();
}

