#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_ListView_Item.h>
#include <efltk/Fl_Image.h>

static Fl_Image *im;

Fl_Button *moveb, *multib, *stripeb;

void callback(Fl_ListView *l, void *)
{
    Fl_ListView_Item *i = (Fl_ListView_Item *)l->item();
    if(i) {
        if(Fl::event_clicks()) printf("Double ");
        printf("Clicked: ");
        for(int a=0; a<l->columns(); a++)
            printf("'%s' ", i->label(a));
        printf("\n");
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

	multib->value(0);
	moveb->value(0);
	stripeb->value(0);

	l->redraw();
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

int main()
{
    Fl::init();

    im = Fl_Image::read_xpm(0, ball_xpm);

    //Fl_Double_Window w(300,300,"ListView Test");
    Fl_Window w(300, 300, "ListView Test");
    w.begin();

    Fl_ListView l(10,10,280,250);
	l.array().blocksize(512);
    //l.header()->hide();
    l.callback((Fl_Callback*)callback);

    // Add 4 cols
    l.add_column("First", 100);
    l.add_column("Second", 80);
    l.add_column("Third");
    l.add_column("Fourth");

    // Set some look for header
    l.header()->box(FL_VERT_SHADE_UP_BOX);
    l.header()->label_font(0, FL_HELVETICA_BOLD);
	l.header()->label_color(1, FL_RED);

    // Add images for cols
    l.column_image(0, im);
    l.column_image(1, im);
    //l.column_image(2, im);
    l.column_image(3, im);

    // Set alignment flags
    l.column_flags(0, FL_ALIGN_LEFT);
    l.column_flags(1, FL_ALIGN_CENTER);
    l.column_flags(2, FL_ALIGN_CENTER);
    l.column_flags(3, FL_ALIGN_RIGHT);

    // Set type for multi and move selection support
    //l.type(l.type()|Fl_ListView::MULTI_SELECTION|Fl_ListView::MOVE_SELECTION);

    // Add 1000 items
    for(int a=0; a<1000; a++) {
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
        i->label_font(2, FL_HELVETICA_BOLD);
		i->label_size(2, 16);

        // Images for cols 1,2,3
        i->image(0, im);
        i->image(1, im);
        i->image(2, im);
		
    }

    l.end();

    Fl_Button but(10, 265, 50, 20, "Move");
    but.type(Fl_Button::TOGGLE);
    but.callback(cb_move, &l);
    Fl_Button but2(70, 265, 50, 20, "Multi");
    but2.type(Fl_Button::TOGGLE);
    but2.callback(cb_multi, &l);

    Fl_Button but5(190, 265, 50, 20, "Stripes");
    but5.type(Fl_Button::TOGGLE);
    but5.callback(cb_stripes, &l);

    Fl_Button but3(250, 265, 40, 20, "Clear");
    but3.callback(cb_single, &l);

    moveb = &but;
    multib = &but2;
    stripeb = &but5;

    w.resizable(&l);
    w.end();
    w.show();

    Fl::run();

    delete im;

    return 0;
}

