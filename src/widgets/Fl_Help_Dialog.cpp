#include <efltk/Fl_Help_Dialog.h>

#include "../core/fl_internal.h"

static const char *datas_open[] = {
  "16 16 8 1",
  " 	c None",
  ".	c #5D5D5D",
  "+	c #000000",
  "@	c #A0A0A0",
  "#	c #C3C3C3",
  "$	c #DCDCDC",
  "%	c #FFA858",
  "&	c #FFDCA8",
  "      ++++      ",
  "     ++ ++++ +  ",
  "    +     ++++  ",
  "           +++  ",
  "          ++++  ",
  " ++++           ",
  "+%&&%+++++++    ",
  "+&&&&%%%%%%%+   ",
  "+&&+++++++++++++",
  "+&%+$$$$$$$$$$$+",
  "+&+$####@#@#@@+ ",
  "+%+$###@#@#@@@+ ",
  "++$###@#@#@@@+  ",
  "++$##@#@#@@@@+  ",
  "+$##@#@#@@@@+   ",
  "+++++++++++++   "};

static bool no_prevpush = false;

void Fl_Help_Dialog::cb_close(Fl_Widget*, void *d) 
{
	((Fl_Help_Dialog *)d)->do_callback();
}

void Fl_Help_Dialog::cb_back(Fl_Button*, void *d) 
{
	((Fl_Help_Dialog *)d)->previous_url();
}

void Fl_Help_Dialog::cb_next(Fl_Button*, void *d) 
{
	((Fl_Help_Dialog *)d)->next_url();
}

void Fl_Help_Dialog::cb_open(Fl_Button*, void *d) 
{
	((Fl_Help_Dialog *)d)->open_file();	
}

void Fl_Help_Dialog::cb_html_link(Fl_Widget *w, void *d)
{
    if(no_prevpush) {
        return;
    }
    if(((Fl_Simple_Html *)w)->prev_filename())
        ((Fl_Help_Dialog *)d)->push_prev(((Fl_Simple_Html *)w)->prev_filename());
}

Fl_Help_Dialog::Fl_Help_Dialog(int x, int y, int w, int h, const char *l)
	: Fl_Main_Window(x,y,w,h,l)
{
    make_group(w,h);
    init();
}

Fl_Help_Dialog::Fl_Help_Dialog(int w, int h, const char *l)
: Fl_Main_Window(w,h,l)
{
    make_group(w,h);
    init();
}

Fl_Help_Dialog::~Fl_Help_Dialog()
{
    for(int n=0; n<10; n++) {
        if(prev_hist[n]) delete []prev_hist[n];
        if(next_hist[n]) delete []next_hist[n];
    }
}

void Fl_Help_Dialog::push_prev(const char *url)
{
    if(!url) return;
    if(prev_hist[0] && !strcmp(url, prev_hist[0])) return;

    if(prev_hist[9]) delete []prev_hist[9];
    int a;
    for(a=9; a>0; a--) {
        prev_hist[a] = prev_hist[a-1];
    }
    prev_hist[0] = strdup(url);

    back->activate();
}

char *Fl_Help_Dialog::pop_prev()
{
    char *url = prev_hist[0];
    if(!url) return 0;

    for(int a=1; a<10; a++) {
        prev_hist[a-1] = prev_hist[a];
    }
    prev_hist[9] = 0;

    if(!prev_hist[0]) back->deactivate();

    return url;
}

void Fl_Help_Dialog::push_next(const char *url)
{
	if(!url) return;
    if(next_hist[0] && !strcmp(url, next_hist[0])) return;

    if(next_hist[9]) delete []next_hist[9];
    int a;
    for(a=9; a>0; a--) {
        next_hist[a] = next_hist[a-1];
    }
    next_hist[0] = strdup(url);

	next->activate();
}

char *Fl_Help_Dialog::pop_next()
{
    char *url = next_hist[0];
    if(!url) return 0;

    for(int a=1; a<10; a++) {
        next_hist[a-1] = next_hist[a];
    }
    next_hist[9] = 0;

    if(!next_hist[0]) next->deactivate();

    return url;
}

void Fl_Help_Dialog::init()
{
    for(int n=0; n<10; n++) {
        prev_hist[n] = 0;
        next_hist[n] = 0;
    }
}

void Fl_Help_Dialog::make_group(int w, int h)
{
    menu()->begin();
    {
        Fl_Item_Group *g = new Fl_Item_Group(_("&File"));
        Fl_Item *i;

        i= new Fl_Item(_("Open"));
        i->shortcut(FL_CTRL+'o');
        i->callback((Fl_Callback*)cb_open, this);

        i = new Fl_Item(_("Close"));
        i->shortcut(FL_CTRL+'c');
        i->callback((Fl_Callback*)cb_close, this);
        g->end();
    }
    menu()->end();

    {
        toolbar()->begin();

        Fl_Button *b;

        b = new Fl_Highlight_Button(5, 2, 30, 25);
        b->image(Fl_Image::read_xpm(0, datas_open));
        //b->box(FL_HIGHLIGHT_UP_BOX);
        b->callback((Fl_Callback*)cb_open, this);
        b->tooltip(_("Open"));
        b->take_focus();


        b = back = new Fl_Highlight_Button(35, 2, 30, 25, "@<-");
        //b->box(FL_HIGHLIGHT_UP_BOX);
        b->label_type(FL_SYMBOL_LABEL);
        b->label_color(FL_DARK3);
        b->highlight_label_color(FL_GRAY);
        b->callback((Fl_Callback*)cb_back, this);
        b->tooltip(_("Back"));
        b->deactivate();

        b = next = new Fl_Highlight_Button(65, 2, 30, 25, "@->");
        //b->box(FL_HIGHLIGHT_UP_BOX);

        b->label_type(FL_SYMBOL_LABEL);
        b->label_color(FL_DARK3);
        b->highlight_label_color(FL_GRAY);
        b->callback((Fl_Callback*)cb_next, this);
        b->tooltip(_("Next"));
        b->deactivate();

        toolbar()->end();
    }

    htmlWidget = new Fl_Simple_Html(0, 50, w, h-50);
    htmlWidget->callback(cb_html_link, this);
    htmlWidget->end();

    view(htmlWidget);
}

void Fl_Help_Dialog::open_file()
{
    const char *f = fl_select_file(htmlWidget->filename(), _("Html files, *.{html|htm}, All files, *"), _("Open Help File"));
    load_file(f);
}

void Fl_Help_Dialog::load_file(const char *f)
{
    if(f) {
        //push_prev(htmlWidget->filename());
        htmlWidget->load(f);
        label(htmlWidget->title());
    }
}

void Fl_Help_Dialog::previous_url()
{
    char *url = pop_prev();
    if(url) {
        no_prevpush = true;
        push_next(htmlWidget->filename());

        htmlWidget->load(url);
        label(htmlWidget->title());
        delete []url;
        no_prevpush = false;
    }
}

void Fl_Help_Dialog::next_url()
{
    char *url = pop_next();
    if(url) {
        push_prev(htmlWidget->filename());

        htmlWidget->load(url);
        label(htmlWidget->title());
        delete []url;
    }
}

