#include <efltk/Fl_Main_Window.h>

Fl_Main_Window::Fl_Main_Window(int x, int y, int w, int h, const char *l)
    : Fl_Main_WindowType(x,y,w,h,l)
{
    m_menu = 0;
    m_toolbar = 0;
    m_view = 0;
    m_status = 0;
    resizable(this);
}

Fl_Main_Window::Fl_Main_Window(int w, int h, const char *l)
    : Fl_Main_WindowType(w,h,l)
{
    m_menu = 0;
    m_toolbar = 0;
    m_view = 0;
    m_status = 0;
    resizable(this);
}

Fl_Main_Window::~Fl_Main_Window()
{
}

void Fl_Main_Window::menu(Fl_Menu_Bar *w)
{
    if(m_menu) remove(m_menu);

    m_menu = w;
    insert(*m_menu, 0);
    m_menu->layout_align(FL_ALIGN_TOP);
}

Fl_Menu_Bar *Fl_Main_Window::menu()
{
    if(!m_menu) {
        Fl_Menu_Bar *m = new Fl_Menu_Bar();
        m->end();
        menu(m);
    }
    return m_menu;
}

void Fl_Main_Window::toolbar(Fl_Tool_Bar *w)
{
    if(m_toolbar) remove(m_toolbar);

    m_toolbar = w;

    int index=0;
    if(m_menu) index++;

    insert(*m_toolbar, index);
    m_toolbar->layout_align(FL_ALIGN_TOP);
}

Fl_Tool_Bar *Fl_Main_Window::toolbar()
{
    if(!m_toolbar) {
        Fl_Tool_Bar *b = new Fl_Tool_Bar();
        b->end();
        toolbar(b);
    }
    return m_toolbar;
}

void Fl_Main_Window::view(Fl_Group *w)
{
    if(m_view) remove(m_view);

    m_view = w;

    int index=0;
    if(m_menu) index++;
    if(m_toolbar) index++;

    insert(*m_view, index);
    m_view->layout_align(FL_ALIGN_CLIENT);
}

Fl_Group *Fl_Main_Window::view()
{
    if(!m_view) {
        Fl_Group *g = new Fl_Group();
        g->end();
        view(g);
    }
    return m_view;
}

void Fl_Main_Window::status(Fl_Widget *w)
{
    if(m_status) remove(m_status);

    m_status = w;
    add(*m_status);
    m_status->layout_align(FL_ALIGN_BOTTOM);
}

Fl_Widget* Fl_Main_Window::status()
{
    if(!m_status) {
        Fl_Box *b = new Fl_Box();
        b->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
        status(b);
    }
    return m_status;
}

