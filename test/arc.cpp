//
// Arc drawing demo for eFLTK
//
// $Id$
//

#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Value_Slider.h>
#include <efltk/fl_draw.h>

float args[7] = { 90, 90, 100, 100, 0, 360, 0 };
const char* name[7] = { "X", "Y", "W", "H", "start", "end", "rotate" };

class Drawing : public Fl_Widget
{
public:
    void draw() {
        fl_push_clip(0, 0, w(), h());
        draw_box();

        fl_push_matrix();

        fl_translate(w()/2.0f, h()/2.0f);
        fl_rotate(args[6]);
        fl_translate(-w()/2.0f, -h()/2.0f);

        fl_arc(args[0],args[1],args[2],args[3],args[4],args[5]);
        fl_closepath();

        fl_arc(120,120,40,40,0,-360);
        fl_ellipse(20,20,args[2],args[3]); // hardware circle
        fl_color(FL_WHITE);
        fl_fill_stroke(FL_RED);
        fl_pop_matrix();

        fl_pop_clip();
    }

    Drawing(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H) {
        color(FL_DARK3);
    }
};

Drawing *d;

void slider_cb(Fl_Widget* o, void* v)
{
    Fl_Slider* s = (Fl_Slider*)o;
    args[long(v)] = s->value();
    d->redraw();
}

int main(int argc, char** argv)
{
    Fl_Double_Window window(300,500);
    Drawing drawing(10,10,280,280);
    d = &drawing;

    int y = 300;
    for (int n = 0; n<7; n++) {
        Fl_Value_Slider* s = new Fl_Value_Slider(50,y,240,25,name[n]); y += 25;

        if (n<4) { s->range(0, 300); }
        else if (n==6) { s->range(0, 360); }
        else { s->range(-360, 360); }

        s->type(Fl_Slider::HORIZONTAL | Fl_Slider::TICK_ABOVE);
        s->step(1);
        s->value(args[n]);
        s->align(FL_ALIGN_LEFT);
        s->callback(slider_cb, (void*)n);
    }

    window.end();
    window.show(argc,argv);
    return Fl::run();
}
