#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Value_Slider.h>
#include <efltk/Fl_Radio_Button.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Image_Filter.h>

Fl_Value_Slider *slider[3];
Fl_Image *image, *show_image=0;
Fl_Image_Filter *current=0;
Fl_Check_Button *lock;
Fl_Box *image_box;

void slider_cb(Fl_Widget *w, void *d)
{
    if(lock->value()) {
        Fl_Slider *s = (Fl_Slider*)w;
        double val = s->value();
        slider[0]->value(val); slider[1]->value(val); slider[2]->value(val);
    }
    if(show_image) delete show_image;
    show_image = Fl_Image_Filter::apply_to_new(image, 0, current, slider[0]->value(), slider[1]->value(), slider[2]->value());
    image_box->image(show_image);
    image_box->redraw();
}

void button_cb(Fl_Widget *w, void *d)
{
    int b = (int)d;
    switch(b) {
    case 1:
        slider[0]->activate();
        slider[1]->deactivate();
        slider[2]->deactivate();
        slider[0]->range(-1, 1);
        slider[0]->value(0); slider[1]->value(0); slider[2]->value(0);
        current = FILTER_BRIGHTNESS;
        break;
    case 2:
        slider[0]->activate();
        slider[1]->activate();
        slider[2]->activate();
        slider[0]->range(-3, 3);
        slider[0]->value(1); slider[1]->value(1); slider[2]->value(1);
        current = FILTER_CONTRAST;
        break;
    case 3:
        slider[0]->activate();
        slider[1]->activate();
        slider[2]->activate();
        slider[0]->range(-3, 3);
        slider[0]->value(1); slider[1]->value(1); slider[2]->value(1);
        current = FILTER_GAMMA;
        break;
    case 4:
        slider[0]->deactivate();
        slider[1]->deactivate();
        slider[2]->deactivate();
        slider[0]->range(-3, 3);
        slider[0]->value(1); slider[1]->value(1); slider[2]->value(1);
        current = FILTER_DESATURATE;
        break;
    };

    slider_cb(slider[0], 0);
}

#define WIDTH 200
#define HEIGHT 200
uchar* make_image()
{
    // pitch = WORD alignment bits per line
    int pitch=Fl_Renderer::calc_pitch(3, WIDTH);
    int skip = pitch - WIDTH * 3;

    uchar *image = new uchar[HEIGHT*pitch];
    uchar *p = image;

    for (int y = 0; y < HEIGHT; y++) {
        double Y = double(y)/(HEIGHT-1);
        for (int x = 0; x < WIDTH; x++) {
            double X = double(x)/(WIDTH-1);
            *p++ = uchar(255*((1-X)*(1-Y))); // red in upper-left
            *p++ = uchar(255*((1-X)*Y));	// green in lower-left
            *p++ = uchar(255*(X*Y));	// blue in lower-right
        }
        p+=skip;
    }
    return image;
}

// Make RGB image
Fl_Image rgb_image(WIDTH, HEIGHT, 24, make_image(), 0x0000FF, 0x00FF00, 0xFF0000, 0 ,0);

int main(int argc, char *argv[])
{
    Fl::args(argc, argv);

    image = &rgb_image;

    Fl_Window w(500,270,"Image filter test");
    Fl_Box b(10,10,250,250);
    b.box(FL_DOWN_BOX);
    b.image(image);
    image_box = &b;

    Fl_Value_Slider s1(280, 20, 30, 240, "R");
    s1.when(FL_WHEN_RELEASE);
    s1.callback(slider_cb, (void*)1);
    s1.deactivate();
    s1.range(-3, 3);
    s1.value(1);
    s1.align(FL_ALIGN_TOP);
    s1.type(Fl_Value_Slider::VERTICAL);
    slider[0] = &s1;

    Fl_Value_Slider s2(320, 20, 30, 240, "G");
    s2.when(FL_WHEN_RELEASE);
    s2.callback(slider_cb, (void*)2);
    s2.deactivate();
    s2.range(-3, 3);
    s2.value(1);
    s2.align(FL_ALIGN_TOP);
    s2.type(Fl_Value_Slider::VERTICAL);
    slider[1] = &s2;

    Fl_Value_Slider s3(360, 20, 30, 240, "B");
    s3.when(FL_WHEN_RELEASE);
    s3.callback(slider_cb, (void*)3);
    s3.deactivate();
    s3.range(-3, 3);
    s3.value(1);
    s3.align(FL_ALIGN_TOP);
    s3.type(Fl_Value_Slider::VERTICAL);
    slider[2] = &s3;

    Fl_Group g(400, 20, 90, 100, "Filter:");
    g.box(FL_ENGRAVED_BOX);
    Fl_Radio_Button b1(2,10,88,20,"Brightness");
    b1.callback(button_cb, (void*)1);
    Fl_Radio_Button b2(2,30,88,20,"Contrast");
    b2.callback(button_cb, (void*)2);
    Fl_Radio_Button b3(2,50,88,20,"Gamma");
    b3.callback(button_cb, (void*)3);
    Fl_Radio_Button b4(2,70,88,20,"Desaturate");
    b4.callback(button_cb, (void*)4);
    g.end();

    Fl_Check_Button l(400, 140, 90, 20, "Lock sliders");
    lock = &l;

    w.show();
    return Fl::run();
}

