#include <efltk/Fl_Slider.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl.h>

Fl_Slider* control;
Fl_Slider* fast;
Fl_Slider* slow;

static void cb_control(Fl_Slider* o, void*) {
  fast->value(o->value());
  if (!Fl::pushed()) slow->value(o->value());
}

int main (int argc, char **argv) {

  Fl_Window* w;
   {Fl_Window* o = new Fl_Window(318, 443);
    w = o;
     {Fl_Slider* o = control = new Fl_Slider(90, 200, 30, 200, "move\nthis");
      o->callback((Fl_Callback*)cb_control);
      o->when(FL_WHEN_CHANGED|FL_WHEN_RELEASE|FL_WHEN_NOT_CHANGED);
    }
     {Fl_Slider* o = fast = new Fl_Slider(140, 200, 30, 200, "fast\nredraw");
      o->set_output();
    }
     {Fl_Slider* o = slow = new Fl_Slider(190, 200, 30, 200, "slow\nredraw");
      o->set_output();
    }
     {Fl_Box* o = new Fl_Box(10, 10, 300, 180, "The left slider has\nchanged(FL_WHEN_CHANGED | FL_WHEN_RELEASE | FL_WHEN_NOT_\
CHANGED) so it produces a callback on both drag and release mouse events.\n\nT\
he middle slider (representing a widget with low overhead) is changed on every\
 mouse movement.\n\nThe right slider (representing a widget with high overhead\
) is only updated when the mouse is released, by checking if Fl::pushed() is z\
ero.");
      o->box(FL_DOWN_BOX);
      o->color((Fl_Color)53);
      o->selection_color((Fl_Color)47);
      o->align(132|FL_ALIGN_INSIDE);
    }
    o->end();
    o->resizable(o);
  }
  w->show(argc, argv);
  return  Fl::run();
}
