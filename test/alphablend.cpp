#include <efltk/Fl.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Images.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Double_Window.h>

#include <stdio.h>

#include <config.h>

static int X = 10, Y=100, TY=-20;

//Bouncing Ball
class BBWin : public Fl_Double_Window
{
public:
    BBWin(Fl_Image *back, Fl_Image *ball) : Fl_Double_Window(200, 200, "Bouncing Ball") {
        bg = back;
        b = ball;
        scale_bg=0;
        alpha_b=0;
    }
	
    void draw()
    {
        if(scale_bg) {
            if(scale_bg->width() != w() || scale_bg->height() != h()) {
                delete scale_bg;
                scale_bg = 0;
            }
        }
        if(!scale_bg) {
            scale_bg = bg->scale(w(),h());
        }
        if(scale_bg)
            scale_bg->draw(0, 0, w(), h());
        else
            bg->draw(0, 0, bg->width(), bg->height());

        if(alpha_b) {
            delete alpha_b;
            alpha_b = 0;
        }
        if(!alpha_b && scale_bg) {
            alpha_b = b->blend(scale_bg, X,Y, b->width(), b->height());
        }
        if(alpha_b)
            alpha_b->draw(X, Y, b->width(), b->height());

        fl_font(FL_HELVETICA, 12);
        fl_draw("Alpha Blending with\neFLTK, nice...", 10, TY, w()-20, 20, FL_ALIGN_CENTER);
    }

    Fl_Image *b, *bg, *scale_bg, *alpha_b;
};

void bb_timeout(void *data)
{
    static int xdir = 1, ydir = 1;
    if(X > ((BBWin *)data)->width()-((BBWin *)data)->b->width()+1)
        xdir = -2;
    else if(X < 1)
        xdir = 2;

    X += xdir;

    if(Y > ((BBWin *)data)->height()-((BBWin *)data)->b->height()+1)
        ydir = -3;
    else if(Y < 1)
        ydir = 1;

    Y += ydir;

    TY++;
    if(TY-20>((BBWin *)data)->h())
        TY=-20;

    ((BBWin *)data)->redraw();

    Fl::repeat_timeout(0.01, bb_timeout, data);
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

int main(int argc, char *argv[])
{
#ifdef HAVE_PNG
    // Initialize extension for PNG
    fl_init_images_lib();
    Fl::args(argc, argv);

    //////////////////////////////
    // Bouncing ball...
    Fl_Image *bb_bg, *bb;
    bb_bg = new Fl_Image(WIDTH, HEIGHT, 24, make_image(), 0x0000FF, 0x00FF00, 0xFF0000, 0 ,0);
    bb = Fl_Image::read("bb.png");

    if(bb_bg && bb) {
        // Speed up things
        bb_bg->system_convert();

        BBWin bwin(bb_bg, bb);
        bwin.resizable(bwin);
        Fl::add_timeout(0.1, bb_timeout, (void *)&bwin);

        //////////////////////////////

        bwin.show();
        while(bwin.visible()) {
            Fl::wait();
        }

        delete bb_bg;
        delete bb;
    }
#else
    Fl::warning("This test works only with PNG lib support");
#endif
    return 0;
}
