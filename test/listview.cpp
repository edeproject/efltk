#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_ListView_Item.h>
#include <efltk/Fl_Image.h>

static Fl_Image *im, *bg;

Fl_Button *moveb, *multib, *imb, *stripeb;

void callback(Fl_ListView *l, void *)
{
    Fl_ListView_Item *i = (Fl_ListView_Item *)l->item();
    if(i) {
        if(Fl::event_clicks()) printf("Double ");
        printf("Clicked '");
        for(int a=0; a<l->columns(); a++)
            printf("%s ", i->label(a));
        printf("'\n");
    }
}

void cb_multi(Fl_Widget *w, void *d)
{
	Fl_ListView *l = (Fl_ListView *)d;
	if(w->value())
		l->type(l->type() | Fl_ListView::MULTI_SELECTION);
	else
		l->type(l->type() &~ Fl_ListView::MULTI_SELECTION);
}
void cb_move(Fl_Widget *w, void *d)
{
	Fl_ListView *l = (Fl_ListView *)d;
	if(w->value())
		l->type(l->type() | Fl_ListView::MOVE_SELECTION);
	else
		l->type(l->type() &~ Fl_ListView::MOVE_SELECTION);
}
void cb_single(Fl_Widget *w, void *d)
{
	Fl_ListView *l = (Fl_ListView *)d;
	l->type( l->type() &~ (Fl_ListView::MULTI_SELECTION|Fl_ListView::MOVE_SELECTION) );

        l->draw_stripes(false);
        l->bg_image(0);

        multib->value(0);
        moveb->value(0);
        imb->value(0);
        stripeb->value(0);

        l->redraw();
}
void cb_image(Fl_Widget *w, void *d)
{
    Fl_ListView *l = (Fl_ListView *)d;
    if(w->value())
        l->bg_image(bg);
    else
        l->bg_image(0);

    l->redraw();
    l->relayout();
}
void cb_stripes(Fl_Widget *w, void *d)
{
    Fl_ListView *l = (Fl_ListView *)d;
    if(w->value())
        l->draw_stripes(true);
    else
        l->draw_stripes(false);

    l->redraw();
}

static char * ball_xpm[] = {
"16 16 13 1",
" 	c None",
".	c #FFECEC",
"+	c #FFC1C1",
"@	c #FF9A9A",
"#	c #FF8585",
"$	c #FFD9D9",
"%	c #FF8686",
"&	c #FF4141",
"*	c #FF1A1A",
"=	c #FF0505",
"-	c #FF7373",
";	c #FF1919",
">	c #FF0000",
"                ",
"    .+@##@+.    ",
"   $%&*==*&%$   ",
"  $-;>>>>>>;-$  ",
" .%;>>>>>>>>;%. ",
" +&>>>>>>>>>>&+ ",
" @*>>>>>>>>>>*@ ",
" #=>>>>>>>>>>=# ",
" #=>>>>>>>>>>=# ",
" @*>>>>>>>>>>*@ ",
" +&>>>>>>>>>>&+ ",
" .%;>>>>>>>>;%. ",
"  $-;>>>>>>;-$  ",
"   $%&*==*&%$   ",
"    .+@##@+.    ",
"                "};

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

int main()
{
    Fl::init();

    im = Fl_Image::read_xpm(0, ball_xpm);
    bg = new Fl_Image(WIDTH, HEIGHT, 24, make_image(), 0x0000FF, 0x00FF00, 0xFF0000, 0);

    //Fl_Double_Window w(300,300,"ListView Test");
    Fl_Window w(300, 300, "ListView Test");
    w.begin();

    Fl_ListView l(10,10,280,250);
    //l.header()->hide();
    l.callback((Fl_Callback*)callback);

    // Set some look for header
    l.header()->box(FL_VERT_SHADE_UP_BOX);
    l.header()->label_color(FL_WHITE);
    l.header()->label_font(FL_HELVETICA_BOLD);

    // Add 4 cols
    l.add_column("First");
    l.add_column("Second");
    l.add_column("Third");
    l.add_column("Fourth");

    // Add images for cols
    l.column_image(0, im);
    l.column_image(1, im);
    l.column_image(2, im);
    l.column_image(3, im);

    // Set alignment flags
    l.column_flags(0, FL_ALIGN_LEFT);
    l.column_flags(1, FL_ALIGN_CENTER);
    l.column_flags(2, FL_ALIGN_CENTER);
    l.column_flags(3, FL_ALIGN_RIGHT);

    // Set type for multi and move selection support
    //l.type(l.type()|Fl_ListView::MULTI_SELECTION|Fl_ListView::MOVE_SELECTION);


    // Add 100 items
    for(int a=0; a<100; a++) {
        Fl_ListView_Item *i = new Fl_ListView_Item(0, "Some Text", "COL 3", "-----------Long column-----------");

        char tmp[32];
        sprintf(tmp, "COL1: %d", a);
        // Copy tmp to column one, ListView will deallocate it.
        i->copy_label(0, tmp);

        // Set some alignment flags
        i->column_flags(0, FL_ALIGN_LEFT);
        i->column_flags(1, FL_ALIGN_CENTER);
        i->column_flags(2, FL_ALIGN_CENTER);
        i->column_flags(3, FL_ALIGN_RIGHT);

        // Set color for column 2
        i->color(1, FL_RED);

        // Set font for column 3
        i->font(2, FL_HELVETICA_BOLD, 14);

        // Images for cols 1,2,3
        i->image(0, im);
        i->image(1, im);
        i->image(2, im);
    }

    l.relayout();
    l.end();

    Fl_Button but(10, 265, 50, 20, "Move");
    but.type(Fl_Button::TOGGLE);
    but.callback(cb_move, &l);
    Fl_Button but2(70, 265, 50, 20, "Multi");
    but2.type(Fl_Button::TOGGLE);
    but2.callback(cb_multi, &l);

    Fl_Button but4(130, 265, 50, 20, "Image");
    but4.type(Fl_Button::TOGGLE);
    but4.callback(cb_image, &l);

    Fl_Button but5(190, 265, 50, 20, "Stripes");
    but5.type(Fl_Button::TOGGLE);
    but5.callback(cb_stripes, &l);

    Fl_Button but3(250, 265, 40, 20, "Clear");
    but3.callback(cb_single, &l);

    moveb = &but;
    multib = &but2;
    imb = &but4;
    stripeb = &but5;

    w.resizable(&l);
    w.end();
    w.show();

    // Speed up things littlebit
    Fl::check(); // Get FLTK display info
    bg->system_convert(); // Convert to system format, no conversion during scaling...

    Fl::run();

    delete im;
    delete bg;

    return 0;
}

