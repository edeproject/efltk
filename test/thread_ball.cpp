#include <stdlib.h>
#include <stdio.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/fl_draw.h>
#include <efltk/x.h>
#include <efltk/Fl_Color.h>

#include <efltk/Fl_Image.h>
#include <efltk/Fl_Images.h>
#include <efltk/Fl_Thread.h>

#include <config.h>

#define WIDTH 300
#define HEIGHT 300

#define BALL_CNT 5

class Ball;
Ball *balls[BALL_CNT];

//Bouncing Balls
class BallWindow : public Fl_Group
{
public:
    BallWindow(Fl_Image *back) : Fl_Group(0, 0, WIDTH, HEIGHT) {
        image(back);
        align(FL_ALIGN_SCALE);
    }
    ~BallWindow() { }

    void draw() {
        draw_label(0,0,w(),h(),flags());
        for(int n=children(); n--;) {
            child(n)->draw();
        }
    }
    // No layout!
    void layout() { }
};

class WBall : public Fl_Widget
{
public:
    WBall(Fl_Image *img) : Fl_Widget(0,0, img->width(), img->height(), 0) {
        image(img);
        //Random start pos:
        x((rand()%WIDTH)-img->width());
        y((rand()%HEIGHT)-img->height());
    }
    ~WBall() { }
    void draw(){
        if(image()) image()->draw(x(), y(), w(), h());
        fl_draw(label(), x()+2, y()+2);
    }
};

class Ball : public Fl_Thread
{
public:
    Ball(Fl_Image *image, BallWindow *win, int id) {
        widget = new WBall(image);
        bWin = win;
        xdir = 1, ydir = 1;
        char tmp[12];
        sprintf(tmp, "Thread %d", id+1);
        widget->copy_label(tmp);
    }
    ~Ball() { }
    void calculate(int &X, int &Y);

    virtual int single_step() {
        Fl::lock();
        calculate(x,y);

        widget->position(x,y);
        bWin->redraw();

        Fl::unlock();
        Fl::awake();

        return 1;
    }

    int x,y;
    int xdir, ydir;

    WBall *widget;
    BallWindow *bWin;
};

void Ball::calculate(int &X, int &Y)
{
    X = widget->x();
    Y = widget->y();

    if(X > bWin->w() - widget->w())
        xdir = -(rand() % 3);
    else if(X < 1)
        xdir = (rand() % 3);

    if(Y > bWin->h() - widget->h())
        ydir = -(rand() % 3);
    else if(Y < 1)
        ydir = (rand() % 3);

    X += xdir;
    Y += ydir;
}

void send_threads_exit(Fl_Widget *w, void *d)
{
    // Unlock EFLTK mutex (callbacks are always locked by efltk)
    Fl::unlock();

    int i;

    // Send kill_thread for all threads
    for(i=0; i<BALL_CNT; i++) {
        balls[i]->kill_thread();
    }

    // Join all threads (wait exit)
    for(i=0; i<BALL_CNT; i++) {
        balls[i]->join();
        printf("Killed thread: %d\n", i);
        delete balls[i];
    }

    // Lock mutex again, FLTK unlocks it
    Fl::lock();

    w->hide();
}

Fl_Image *make_bg(int w, int h)
{
    Fl_Image *ret = new Fl_Image(w,h,24);

    int pitch=Fl_Renderer::calc_pitch(ret->format()->bytespp, w);
    int skip = pitch - w * ret->format()->bytespp;

    uint8 *p = ret->data();
    uint8 r,g,b;

    for (int y = 0; y < h; y++) {
        double Y = double(y)/(h-1);
        for (int x = 0; x < w; x++) {
            double X = double(x)/(w-1);
            r = uchar(255*((1-X)*(1-Y))); // red in upper-left
            g = uchar(255*((1-X)*Y));	// green in lower-left
            b = uchar(255*(X*Y));	// blue in lower-right
            fl_assemble_rgb(p,
                            ret->format()->bytespp, ret->format(),
                            r, g, b);
            p+=ret->format()->bytespp;
        }
        p+=skip;
    }
    return ret;
}

int main(int argc, char *argv[])
{	
#ifdef HAVE_PNG
    // Initialize extension for PNG
    fl_init_images_lib();

    Fl::args(argc, argv);
    fl_open_display();
    Fl_Renderer::system_init();

    Fl_Image *bb_bg, *bb;
    bb_bg = make_bg(WIDTH, HEIGHT);
#ifdef _MSC_VER
    bb = Fl_Image::read("../test/bb.png");
#else
    bb = Fl_Image::read("bb.png");
#endif

    bb_bg->system_convert();

    // Create mask now, and then manually set it to image
    // Now we can convert image to system_fmt, even if that is 8,15,16,24
    Pixmap mask = bb->create_mask(bb->width(), bb->height());

    // Speed up things (no need for convert, in each draw
    bb->system_convert();

    // Set mask to none, so Fl_Image doesnt try generate mask by it self
    bb->mask_type(MASK_NONE);
    // Set earlier created mask
    bb->set_mask(mask);

    // Init random generator
    srand(100000);

    // Init EFLTK system mutex
    Fl::lock();

    char title[64];
    sprintf(title, "Bouncing Balls, %d Threads", BALL_CNT);
    Fl_Double_Window win(WIDTH, HEIGHT, title);
    win.begin();
    BallWindow bwin(bb_bg);
    bwin.begin();

    int i;
    for(i=0; i<BALL_CNT; i++) {
        balls[i] = new Ball(bb, &bwin, i);
        // Set sleep in single_step
        balls[i]->ms_sleep(10); //10 milliseconds
    }

    bwin.end();
    win.end();

    win.callback(send_threads_exit);
    win.resizable(bwin);
    win.show();

    // Start the all threads
    for(i=0; i<BALL_CNT;i++) {
        balls[i]->create();
        balls[i]->set_priority(Fl_Thread::HIGHEST_PR);
    }

    while(win.visible()) {
        // Wait for events and handle while unlocked.
        Fl::wait();
    }

    // Delete images
    delete bb_bg;
    delete bb;
#else
    Fl::warning("This test works only with PNG lib support");
#endif
    return 0;
}

