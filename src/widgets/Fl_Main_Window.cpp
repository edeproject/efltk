#include <efltk/Fl_Main_Window.h>

Fl_Main_Window::Fl_Main_Window(int x, int y, int w, int h, const char *l)
    : Fl_Main_WindowType(x,y,w,h,l)
{
    pack_ = new Fl_Pack(0,0,w,h);
    pack_->end();

    menu_ = 0;
    toolbar_ = 0;
    view_ = 0;
    status_ = 0;

    resizable(pack_);
}

Fl_Main_Window::Fl_Main_Window(int w, int h, const char *l)
    : Fl_Main_WindowType(w,h,l)
{
    pack_ = new Fl_Pack(0,0,w,h);
    pack_->end();

    menu_ = 0;
    toolbar_ = 0;
    view_ = 0;
    status_ = 0;

    resizable(pack_);
}

Fl_Main_Window::~Fl_Main_Window()
{

}

void Fl_Main_Window::menu(Fl_Menu_Bar *w)
{
    if(menu_) pack_->remove(menu_);

    menu_ = w;
    pack_->insert(*menu_,0);
}

Fl_Menu_Bar *Fl_Main_Window::menu()
{
    if(!menu_) {
        Fl_Menu_Bar *m = new Fl_Menu_Bar(0,0,0,23);
        //m->box(FL_THIN_UP_BOX);
        m->end();
        menu(m);
    }
    return menu_;
}

void Fl_Main_Window::toolbar(Fl_Tool_Bar *w)
{
    if(toolbar_) pack_->remove(toolbar_);

    toolbar_ = w;

    int index=0;
    if(menu_) index++;

    pack_->insert(*toolbar_, index);
}

Fl_Tool_Bar *Fl_Main_Window::toolbar()
{
    if(!toolbar_) {
        Fl_Tool_Bar *b = new Fl_Tool_Bar(0,0,0,10);
        //b->box(FL_THIN_UP_BOX);
        b->end();
        toolbar(b);
    }
    return toolbar_;
}

void Fl_Main_Window::view(Fl_Group *w)
{
    if(view_) pack_->remove(view_);

    view_ = w;

    int index=0;
    if(menu_) index++;
    if(toolbar_) index++;

    pack_->insert(*view_, index);
    pack_->resizable(view_);
}

Fl_Group *Fl_Main_Window::view()
{
    if(!view_) {
        Fl_Group *g = new Fl_Group(0,0,w(),h());
        //g->box(FL_THIN_DOWN_BOX);
        g->end();
        view(g);
    }
    return view_;
}

void Fl_Main_Window::status(Fl_Group *w)
{
    if(status_) pack_->remove(status_);

    status_ = w;
    pack_->add(*status_);
}

Fl_Group *Fl_Main_Window::status()
{
    if(!status_) {
        Fl_Group *g = new Fl_Group(0,0,0,23);
        //g->box(FL_THIN_UP_BOX);
        g->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
        status(g);
    }
    return status_;
}

