/*
 * $Id$
 * 
 * Signal/Slot demo for Extended Fast Light Toolkit - eFLTK
 */

#include <efltk/Fl.h>
#include <efltk/Fl_Widget.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Input.h>

// Called upon FL_WINDOW_CLOSE - When user clickc "X" in title bar
static void bye_bye(Fl_Window *window)
{
	static bool exit = false;    
	if(exit)	window->hide();
	else		printf("Bye-Bye! - One more time and we're out\n");
	exit = true;
}

// Called upon grp_right FL_HIDE/FL_SHOW events - see connections
static void show_visibility(Fl_Group *grp_right)
{
    printf("grp_right visible: %s!\n", grp_right->visible() ? "yes" : "no");
}

int main(int argc, char *argv[])
{
	// Create window & some groups
    Fl_Window win(400,200);
	win.layout_spacing(5);
        
		Fl_Group grp_left(0, 200, FL_ALIGN_LEFT);
            Fl_Check_Button activate_button("(de)activate", 20, FL_ALIGN_TOP);
            Fl_Check_Button show_button("show/hide", 20, FL_ALIGN_TOP);
            Fl_Input label_input("Group label", 20, FL_ALIGN_TOP);
			label_input.align(FL_ALIGN_INSIDE);
			label_input.when(FL_WHEN_CHANGED);
        grp_left.end();
        
		Fl_Group grp_right("This is a group", 0, FL_ALIGN_CLIENT);
            grp_right.box(FL_UP_BOX);
            grp_right.align(FL_ALIGN_CENTER | FL_ALIGN_WRAP);
            Fl_Button nop0("Nop", 20, FL_ALIGN_TOP);
            Fl_Button nop1("Nop", 20, FL_ALIGN_TOP);
            Fl_Button nop2("Nop", 20, FL_ALIGN_TOP);
        grp_right.end();

    win.end();

    activate_button.value(1);
    show_button.value(1);

    // Make connections.
    // This is the most interesting part

	// Connect activate_button to default slot: Fl_Widget::slot_active
    activate_button.connect(FL_VALUE_CHANGED, SLOT(&grp_right, slot_active));

	// Connect show_button to default slot: Fl_Widget::slot_visibility
    show_button.connect(FL_VALUE_CHANGED, SLOT(&grp_right, slot_visibility));

	// Connect label_input to default slot: Fl_Widget::slot_label
    label_input.connect(FL_VALUE_CHANGED, SLOT(&grp_right, slot_label));

	// Called when user clicks "X" in titlebar
    win.connect(FL_WINDOW_CLOSE, STATIC_SLOT(bye_bye));

	// Called upon FL_SHOW event
    grp_right.connect(FL_SHOW, STATIC_SLOT(show_visibility));

	// Called upon FL_HIDE event
    grp_right.connect(FL_HIDE, STATIC_SLOT(show_visibility));

    win.show(argc, argv);
    return Fl::run();
}

