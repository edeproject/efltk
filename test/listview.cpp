#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_ListView_Item.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Date_Time.h>

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

static Fl_Image *im;

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

void cb_stripes(Fl_Widget *w, void *d)
{
    Fl_ListView *l = (Fl_ListView *)d;
    if(w->value())
        l->draw_stripes(true);
    else
        l->draw_stripes(false);

    l->redraw();
}

void make_listview_ext()
{
    Fl_Window *w = new Fl_Window(300, 300, "ListView Test");
    w->begin();

    Fl_ListView *l = new Fl_ListView(10,20,280,240, "LIST VIEW: Extended items");
    //l->header()->hide();
    l->callback((Fl_Callback*)callback);

    // Add 4 cols
    l->add_column("First", 120);
    l->add_column("Second", 100);
    l->add_column("Third", 100);
    l->add_column("Fourth", 100);

    // Set some look for header
    l->header()->button_box(FL_VERT_SHADE_UP_BOX);
    l->header()->column_label_font(0, FL_HELVETICA_BOLD);
    l->header()->column_label_color(1, FL_RED);

    // Add images for cols
    l->column_image(0, im);
    l->column_image(1, im);
    //l->image(2, im);
    l->column_image(3, im);

    // Set alignment flags
    l->column_flags(0, FL_ALIGN_LEFT);
    l->column_flags(1, FL_ALIGN_CENTER);
    l->column_flags(2, FL_ALIGN_CENTER);
    l->column_flags(3, FL_ALIGN_RIGHT);

    Fl_Date_Time start = Fl_Date_Time::Now();

    // Add 1000 items
    for(int a=0; a<1000; a++) {
        Fl_ListView_ItemExt *i = new Fl_ListView_ItemExt(0, "Some Text", "COL 3", "-----------Long column-----------");

        char tmp[32];
        sprintf(tmp, "Column1: (%d)", a);
        // Copy tmp to column one, ListView will deallocate it.
        i->copy_label(0, tmp);

        // Set some alignment flags
        i->flags(0, FL_ALIGN_CENTER);
        i->flags(1, FL_ALIGN_CENTER);
        i->flags(2, FL_ALIGN_CENTER);
        i->flags(3, FL_ALIGN_CENTER);

        // Set color for column 1 and 2
        Fl_Color c=FL_BLACK;
        switch(a%5) {
        case 1: c=FL_RED; break;
        case 2: c=fl_darker(FL_GREEN); break;
        case 3: c=FL_BLUE; break;
        case 4: c=fl_darker(FL_YELLOW); break;
        case 5: c=FL_GRAY; break;
        default: break;
        }
        i->label_color(1, c);
        i->label_color(2, c);

        i->label_type(0, FL_EMBOSSED_LABEL);
        i->label_type(2, FL_ENGRAVED_LABEL);

        // Set font for column 3
        i->label_font(2, FL_HELVETICA_BOLD);
        i->label_size(2, 16);

        // Images for cols 1,2,3
        i->image(0, im);
        i->image(1, im);
        i->image(2, im);
    }

    Fl_Date_Time end = Fl_Date_Time::Now();
    double t = double(end - start) * 24 * 3600;
    printf("Fl_ListView with extended 1000 items: Duration: %f\n", t);

    l->end();

    Fl_Button *but = new Fl_Button(10, 265, 50, 20, "Move");
    but->type(Fl_Button::TOGGLE);
    but->callback(cb_move, l);

    but = new Fl_Button(70, 265, 50, 20, "Multi");
    but->type(Fl_Button::TOGGLE);
    but->callback(cb_multi, l);

    but = new Fl_Button(190, 265, 50, 20, "Stripes");
    but->type(Fl_Button::TOGGLE);
    but->callback(cb_stripes, l);

    w->resizable(l);
    w->end();
    w->show();
}

void make_listview()
{
    Fl_Window *w = new Fl_Window(300, 300, "ListView Test");
    w->begin();

    Fl_ListView *l = new Fl_ListView(10,20,280,240, "LIST VIEW: Normal items");
    //l->header()->hide();
    l->callback((Fl_Callback*)callback);

    // Add 4 cols
    l->add_column("First", 120);
    l->add_column("Second", 100);
    l->add_column("Third", 100);
    l->add_column("Fourth", 100);

    // Set alignment flags
    l->column_flags(0, FL_ALIGN_LEFT);
    l->column_flags(1, FL_ALIGN_CENTER);
    l->column_flags(2, FL_ALIGN_CENTER);

    l->column_image(0, im);

    Fl_Date_Time start = Fl_Date_Time::Now();

    // Add 1000 items
    for(int a=0; a<1000; a++) {
        Fl_ListView_Item *i = new Fl_ListView_Item(0, "Some Text", "COL 3", "-----------Long column-----------");
        i->image(im);

        char tmp[32];
        sprintf(tmp, "Column1: (%d)", a);
        // Copy tmp to column one, ListView will deallocate it.
        i->copy_label(0, tmp);
    }

    Fl_Date_Time end = Fl_Date_Time::Now();
    double t = double(end - start) * 24 * 3600;
    printf("Fl_ListView with normal 1000 items: Duration: %f\n", t);
 
    l->end();

    Fl_Button *but = new Fl_Button(10, 265, 50, 20, "Move");
    but->type(Fl_Button::TOGGLE);
    but->callback(cb_move, l);

    but = new Fl_Button(70, 265, 50, 20, "Multi");
    but->type(Fl_Button::TOGGLE);
    but->callback(cb_multi, l);

    but = new Fl_Button(190, 265, 50, 20, "Stripes");
    but->type(Fl_Button::TOGGLE);
    but->callback(cb_stripes, l);

    w->resizable(l);
    w->end();
    w->show();

}

int main()
{
    Fl::init();

    im = Fl_Image::read_xpm(0, ball_xpm);

    make_listview();
    make_listview_ext();

    Fl::run();

    delete im;

    return 0;
}
