#include <efltk/Fl.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/math.h>

#include <stdio.h>

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
            int DX = dX>0?dX:-dX;
            int DY = dY>0?dY:-dY;

            // X axis
            if(dX>0) fl_copy_offscreen(oX, Y-DY, dX, bH+DY, id, oX, Y);
            else fl_copy_offscreen(X+bW, Y, -dX, bH+DY, id, X+bW, Y);

            // Y axis
            if(dY>0) fl_copy_offscreen(oX, oY, bW+DX, dY, id, oX, oY);
            else fl_copy_offscreen(oX, Y+bH, bW, -dY, id, oX, Y+bH);
        }

        if(blended) delete blended;
        // Do alphablend and draw it to screen
        if( (blended = ball->blend(backing, X,Y, bW, bH)) ) {
            blended->draw(X, Y);
        }

        // Draw string
        fl_draw(str, float(tX), float(tY+int(fl_height())));

        oX=X; oY=Y;
    }

	int handle(int e)
	{		
		return BBWinType::handle(e);
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

// Generate 16 bit images
// #define GENERATE_16BIT

Fl_Image *make_ball(int radius)
{
    uint8  trans, alphamask;
    int    range, addition;
    int    xdist, ydist;
    uint16 x, y;
    uint16 skip;
    uint32 pixel;
    Fl_Image *light;

#ifdef GENERATE_16BIT
    uint16 *buf;
    /* Create a 16 (4/4/4/4) bpp square with a full 4-bit alpha channel */
    /* Note: this isn't any faster than a 32 bit alpha surface */
    alphamask = 0x0000000F;
    light = new Fl_Image(2*radius, 2*radius, 16, 0,
                         0x0000F000, 0x00000F00, 0x000000F0, alphamask);
#else
    uint32 *buf;
    /* Create a 32 (8/8/8/8) bpp square with a full 8-bit alpha channel */
    alphamask = 0x000000FF;
    light = new Fl_Image(2*radius, 2*radius, 32, 0,
                         0xFF000000, 0x00FF0000, 0x0000FF00, alphamask);
#endif

    /* Fill with a light yellow-orange color */
    skip = light->pitch()-(light->width()*light->format()->bytespp);
#ifdef GENERATE_16BIT
    buf = (uint16 *)light->data();
#else
    buf = (uint32 *)light->data();
#endif
    /* Get a tranparent pixel value - we'll add alpha later */
    pixel = light->format()->map_rgba(0xFF, 0xDD, 0x88, 0);
    for ( y=0; y<light->height(); ++y ) {
        for ( x=0; x<light->width(); ++x ) {
            *buf++ = pixel;
        }
        buf += skip;	/* Almost always 0, but just in case... */
    }

    /* Calculate alpha values for the surface. */
#ifdef GENERATE_16BIT
    buf = (uint16 *)light->data();
#else
    buf = (uint32 *)light->data();
#endif
    for ( y=0; y<light->height(); ++y ) {
        for ( x=0; x<light->width(); ++x ) {
            /* Slow distance formula (from center of light) */
            xdist = x-(light->width()/2);
            ydist = y-(light->height()/2);
            range = (int)sqrt(xdist*xdist+ydist*ydist);

            /* Scale distance to range of transparency (0-255) */
            if ( range > radius ) {
                trans = alphamask;
            } else {
                /* Increasing transparency with distance */
                trans = (uint8)((range*alphamask)/radius);

                /* Lights are very transparent */
                addition = (alphamask+1)/8;
                if ( (int)trans+addition > alphamask ) {
                    trans = alphamask;
                } else {
                    trans += addition;
                }
            }
            /* We set the alpha component as the right N bits */
            *buf++ |= (255-trans);
        }
        buf += skip;	/* Almost always 0, but just in case... */
    }

    return light;
}

Fl_Image *make_bg(int w, int h)
{
#ifdef GENERATE_16BIT
    Fl_Image *ret = new Fl_Image(w,h,16);
#else
    Fl_Image *ret = new Fl_Image(w,h,24);
#endif

    // pitch = WORD alignment bits per line
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
    Fl_Renderer::system_init();
    Fl::args(argc, argv);

    //////////////////////////////
    // Bouncing ball...
    Fl_Image *bb_bg, *bb;
    bb_bg = make_bg(200,200);
    bb = make_ball(30);

    if(bb_bg && bb) {
        // Speed up things
        bb_bg->system_convert();

        BBWin bwin(bb_bg, bb);
        bwin.resizable(bwin);
        Fl::add_timeout(0.1f, bb_timeout, (void *)&bwin);

        //////////////////////////////

        bwin.show();
        while(bwin.visible()) {
            Fl::wait();
        }

        delete bb_bg;
        delete bb;
    }
    return 0;
}
