#include <efltk/Fl.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Images.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Double_Window.h>

#include <stdio.h>

#include <config.h>

static int X = 10, Y=100;
static int oX=0, oY=0;
static int dX = 1, dY = 1;

static int tY=-20, tW=0;
char *str = "EFLTK ROCKS!";

typedef Fl_Window BBWinType;
//typedef Fl_Double_Window BBWinType;

//Bouncing Ball
class BBWin : public BBWinType
{
public:
    BBWin(Fl_Image *back, Fl_Image *ball) : BBWinType(200, 200, "Bouncing Ball") {
        this->back = backing = back;
        this->ball = ball;
        blended=0;
    }

    void layout()
    {
        if(backing->width() != w() || backing->height() != h()) {
            if(backing!=back) delete backing;
            backing = back->scale(w(), h());
        }
        backing->no_screen(true);
        BBWinType::layout();
    }

    void draw()
    {
        if(!tW) {
            fl_font(FL_HELVETICA_BOLD, 14);
            tW = int(fl_width(str));
        }

        if(!backing->get_offscreen())
            backing->draw(0,0);

        Pixmap id = backing->get_offscreen();

        int tX = (w()/2)-(tW/2);
        int bW = ball->width();
        int bH = ball->height();

        if(damage()!=FL_DAMAGE_VALUE) {

            fl_copy_offscreen(0, 0, w(), h(), id, 0, 0);

        } else {

            // Erase bg under text
            fl_copy_offscreen(tX, tY, tW, int(fl_height()), id, tX, tY);

            // Erase only area affected, by moving ball!

            // X axis
            if(dX>0) fl_copy_offscreen(oX, Y, dX, bH, id, oX, Y);
            else fl_copy_offscreen(X+bW, Y, -dX, bH, id, X+bW, Y);

            // Y axis
            if(dY>0) fl_copy_offscreen(X, oY, bW, dY, id, X, oY);
            else fl_copy_offscreen(X, Y+bH, bW, -dY, id, X, Y+bH);
        }

        if(blended) delete blended;
        // Do alphablend and draw it to screen
        if( (blended = ball->blend(backing, X,Y, bW, bH)) ) {
            blended->draw(X, Y);
        }

        // Draw string
        fl_draw(str, tX, tY+int(fl_height()));

        oX=X; oY=Y;
    }

    Fl_Image *ball, *back, *backing, *blended;
};

void bb_timeout(void *data)
{
    if(X > ((BBWin *)data)->width()-((BBWin *)data)->ball->width()+1)
        dX = -2;
    else if(X < 1)
        dX = 2;

    X += dX;

    if(Y > ((BBWin *)data)->height()-((BBWin *)data)->ball->height()+1)
        dY = -3;
    else if(Y < 1)
        dY = 1;

    Y += dY;

    tY++;
    if(tY-20>((BBWin *)data)->h())
        tY=-20;

    ((BBWin *)data)->redraw(FL_DAMAGE_VALUE);

    Fl::repeat_timeout(.01f, bb_timeout, data);
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
