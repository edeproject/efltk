#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Date_Time.h>
#include <efltk/Fl_Date_Time_Input.h>
#include <efltk/Fl_Combo_Box.h>

Fl_Box *statusBox;

void datetime_cb(Fl_Widget *w, void *) {
    if (w->event() == FL_DATA_CHANGE) {
        Fl_Date_Interval_Input *dii = dynamic_cast<Fl_Date_Interval_Input *>(w);
        if (dii) {
            puts(dii->value());
            puts(dii->value2());
            statusBox->label(dii->value() + Fl_String("..") + dii->value2());
            statusBox->redraw();
            return;
        }
        Fl_Date_Time_Input *dti = dynamic_cast<Fl_Date_Time_Input *>(w);
        if (dti) {
            puts(dti->value());
            statusBox->label(dti->value());
            statusBox->redraw();
            return;
        }
        Fl_Date_Input *di = dynamic_cast<Fl_Date_Input *>(w);
        if (di) {
            puts(di->value());
            statusBox->label(di->value());
            statusBox->redraw();
            return;
        }
    }
}

int main() {
    Fl_Window   window(400,300,"Date and Time widgets test");
    window.layout_spacing(4);

    Fl_Date_Input   dateInput(0,0,10,10,"Date Input:");
    dateInput.layout_align(FL_ALIGN_TOP);
    dateInput.label_width(100);
    dateInput.callback(datetime_cb);

    Fl_Date_Time_Input dateTimeInput(0,0,10,10,"Date Time Input:");
    dateTimeInput.layout_align(FL_ALIGN_TOP);
    dateTimeInput.label_width(100);
    dateTimeInput.callback(datetime_cb);

    Fl_Date_Interval_Input dateIntervalInput(0,0,10,10,"Date Interval Input:");
    dateIntervalInput.layout_align(FL_ALIGN_TOP);
    dateIntervalInput.label_width(100);
    dateIntervalInput.callback(datetime_cb);

    statusBox = new Fl_Box(0,0,10,22);
    statusBox->box(FL_THIN_DOWN_BOX);
    statusBox->layout_align(FL_ALIGN_BOTTOM);
    statusBox->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);

    window.end();
    window.show();
    return Fl::run();
}
