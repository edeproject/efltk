//
// Curve demo for eFLTK
//
// $Id$
//

#include <efltk/Fl.h>
#include <efltk/x.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Hor_Value_Slider.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Toggle_Button.h>

float args[10] = {
    20,20, 50,200, 100,20, 200,200, 0, 1
};

const char* name[10] = {
    "X0", "Y0", "X1", "Y1", "X2", "Y2", "X3", "Y3", "rotate", "scale"
};

Fl_Slider *s[10];

bool points = false;
bool double_buffer = false;

class Drawing : public Fl_Widget {
    Pixmap back_buffer;
public:
    void do_drawing()
    {
        int X=0, Y=0, W=w(), H=h();

        draw_box();
        box()->inset(X,Y,W,H);

        fl_push_clip(X,Y,W,H);

        fl_push_matrix();

        if(args[9]!=1.0) {
            // Scale
            fl_scale(args[9]);
        }

        if (args[8]) {
            // Rotate
            H = W = 280;
            fl_translate(H/2.0f, H/2.0f); //Translate to center
            fl_rotate(args[8]);
            fl_translate(-W/2.0f, -H/2.0f); // And back to corner
        }

        fl_color(FL_BLACK);
        fl_vertex(args[0],args[1]);
        fl_vertex(args[2],args[3]);
        fl_vertex(args[4],args[5]);
        fl_vertex(args[6],args[7]);
        fl_stroke();

        fl_curve(args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7]);

        fl_color(FL_WHITE);
        if(points)  fl_points();
        else        fl_fill_stroke(FL_RED);

        fl_pop_matrix();
        fl_pop_clip();
    }

    void draw() 
    {
        if(double_buffer) 
        {
            fl_begin_offscreen(back_buffer);
            do_drawing();
            fl_end_offscreen();
            fl_copy_offscreen(x(), y(), w(), h(), back_buffer, 0, 0);
        } else
            do_drawing();
    }

    void layout() {

        if(double_buffer) {

            if((layout_damage() & FL_LAYOUT_WH) || !back_buffer) {
                if(back_buffer) {
                    fl_delete_offscreen(back_buffer);
                    back_buffer = 0;
                }
                back_buffer = fl_create_offscreen(w(), h());
            }

        } else {

            if(back_buffer) {
                fl_delete_offscreen(back_buffer);
                back_buffer = 0;
            }   

        }

        Fl_Widget::layout();
    }

    Drawing(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H) {
        color(FL_DARK3);
        back_buffer = 0;
    }
};

Drawing *d;

float s_dir = .01f, r_dir = 1;
void anim_timeout(void *)
{
    args[8] += r_dir;   
    args[9] += s_dir;   

    if(args[9] >= 2) {
        s_dir = -.01f;
    } else if(args[9] <= 0) {
        s_dir = .01f;
    }

    if(args[8] >= 360) {
        r_dir = -1;
    } else if(args[8] <= 0) {
        r_dir = 1;
    }

    s[8]->value(args[8]);
    s[9]->value(args[9]);

    d->redraw();

    Fl::repeat_timeout(0.03f, anim_timeout);
}

void anim_cb(Fl_Button *o, void*) 
{
    if (Fl::event() == FL_BUTTON_PRESSED) {
        if(o->value()) {
            Fl::add_timeout(0, anim_timeout);
            s[8]->set_output();
            s[9]->set_output();
        } else {
            Fl::remove_timeout(anim_timeout);
            s[8]->clear_output();
            s[9]->clear_output();
        }
        d->redraw();
    }
}

void db_cb(Fl_Button *o, void*) {
    if(Fl::event() == FL_BUTTON_PRESSED) {
        double_buffer = o->value();
        d->relayout();
        d->redraw();
    }
}

void points_cb(Fl_Button *o, void*) 
{
    if(Fl::event() == FL_BUTTON_PRESSED) {
        points = o->value();
        d->redraw();
    }
}

void slider_cb(Fl_Slider *s, long v) 
{
    args[v] = s->value();
    d->redraw();
}

int main(int argc, char** argv) 
{
    Fl_Window window(300,600, "Curve test");

    Drawing drawing(10,10,280,280);
    d = &drawing;

    Fl_Group g(0, 300, 300, 275);
    g.layout_spacing(2);

    for (int n = 0; n<10; n++) {
        s[n] = new Fl_Value_Slider(name[n], 22, FL_ALIGN_TOP, 50);
        s[n]->align(FL_ALIGN_LEFT);
        s[n]->type(Fl_Slider::HORIZONTAL | Fl_Slider::TICK_ABOVE);
        s[n]->step(1);
        s[n]->value(args[n]);
        s[n]->callback((Fl_Callback1*)slider_cb, n);
        s[n]->minimum(0); 
        s[n]->maximum(280);
        s[n]->when(FL_LOGICAL_EVENTS);

        if (n == 8) {
            s[n]->maximum(360);
        } else if (n == 9) {
            s[n]->maximum(2);
            s[n]->step(0.01);
        }
    }       

    g.end();

    Fl_Group g2(0, 575, 300, 25);
    g2.layout_spacing(2);

    Fl_Toggle_Button points_but("points", 0, FL_ALIGN_LEFT);
    points_but.callback((Fl_Callback*)points_cb);   

    Fl_Toggle_Button anim_but("animate", 0, FL_ALIGN_LEFT);     
    anim_but.callback((Fl_Callback*)anim_cb);   

    Fl_Toggle_Button db_but("double buffer", 0, FL_ALIGN_LEFT);     
    db_but.callback((Fl_Callback*)db_cb);   

    g2.end();

    window.end();
    window.resizable(d);
    window.show(argc,argv); 

    return Fl::run();
}
