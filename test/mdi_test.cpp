#include <efltk/Fl.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Radio_Button.h>
#include <efltk/Fl_Browser.h>
#include <efltk/Fl_Menu_Bar.h>
#include <efltk/Fl_Main_Window.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Workspace.h>
#include <efltk/Fl_MDI_Window.h>
#include <efltk/Fl_MDI_Bar.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_ListView_Item.h>
#include <efltk/Fl_File_Dialog.h>

#include <stdio.h>

void cb_cascade(Fl_Widget* w, void*);
void cb_tile_h(Fl_Widget* w, void*);
void cb_tile_v(Fl_Widget* w, void*);

Fl_Menu_Item menutable[] = {
  {"&File",0,0,0,FL_SUBMENU},
    {"&Open",	FL_ALT+'o', 0, 0, FL_MENU_INACTIVE},
    {"&Close",	0,	0, 0, FL_MENU_DIVIDER},
    {"&Quit",	FL_ALT+'q', 0, 0, 0},
    {0},
  {"&Actions",0,0,0,FL_SUBMENU},
    {"Cascade",	0, cb_cascade},
	{"Tile Hor", 0, cb_tile_h},
	{"Tile Ver", 0, cb_tile_v},
    {0},
  {"Windows",0,0,0,FL_SUBMENU},    
    {0},
  {"Help",0, 0, 0, FL_MENU_RIGHTLAYOUT|FL_SUBMENU},
    {0},

  {0}
};

Fl_Workspace *workspace;
Fl_Menu_Bar *menu;

void cb_cascade(Fl_Widget* w, void*) {
	workspace->cascade();
}
void cb_tile_h(Fl_Widget* w, void*) {
	workspace->tileH();
}
void cb_tile_v(Fl_Widget* w, void*) {
	workspace->tileV();
}

void tool_cb(Fl_Widget* w, void*) {
    printf("Toolbar: %s\n", w->label().c_str());
}

void test_cb(Fl_Widget* w, void*) {
    Fl_Menu_* mw = (Fl_Menu_*)w;
    Fl_Widget* m = mw->item();
    if (!m)
        printf("Menu: NULL\n");
    else if (m->shortcut())
        printf("Menu: %s - %s\n", m->label().c_str(), Fl::key_name(m->shortcut()));
    else
        printf("Menu: %s\n", m->label().c_str());
    m->do_callback();
}

void cb_anim(Fl_Widget *w, void *data) {
	if(w->value()) Fl_MDI_Window::animate(true);
	else Fl_MDI_Window::animate(false);
}
void cb_opaq(Fl_Widget *w, void *data) {
	if(w->value()) Fl_MDI_Window::animate_opaque(true);
	else Fl_MDI_Window::animate_opaque(false);
}
void cb_detach(Fl_Widget *, void *data) {
	Fl_MDI_Window *m = (Fl_MDI_Window *)data;
	if(!m->toplevel()) m->detach();
}
void cb_attach(Fl_Widget *, void *data) {
	Fl_MDI_Window *m = (Fl_MDI_Window *)data;
	if(m->toplevel()) m->attach();
}
void cb_top_window(Fl_Widget *, void *data) {
	Fl_MDI_Window *m = (Fl_MDI_Window *)data;
	m->setTop();
}

void close_mdi(Fl_Widget *w, void *)
{	
	Fl_MDI_Window *win = (Fl_MDI_Window *)w;
	win->hide();
	char item[64]; 
	sprintf(item, "Windows/%s", win->label().c_str());
	Fl_Widget *i = menu->find(item);
	if(i) delete i; //Delete item	
	delete win; //Delete window	

}

Fl_MDI_Window *add_win(Fl_MDI_Viewport *s, bool doublebuf, const char *n)
{
    s->begin();

    Fl_MDI_Window *w = new Fl_MDI_Window(10,10,150,250,n);    

    if(doublebuf) {
        w->view()->end();
        Fl_Double_Window *win = new Fl_Double_Window(150,250);
        win->end();
        Fl_Group *g = w->view(win);
        delete g;
        win->show();
    }
	w->resizable(w->view());	

    // Set "view" to current group
    // View is Fl_Group inside MDI window frames	
    w->view()->begin();

    Fl_Button *b;

    //b = new Fl_Button(10,10,130,20,"Attach");
    b = new Fl_Button(0,10,w->view()->w(),20,"Attach");
    b->tooltip("Attach window!");
    b->callback(cb_attach, w);

    b = new Fl_Button(10,40,130,20,"Detach");
    b->tooltip("Detach window!");
    b->callback(cb_detach, w);

    Fl_Input *in = new Fl_Input(10,150, 130, 60);
    in->tooltip("Click right mouse button!");
    in->type(Fl_Input::MULTILINE);
	in->wordwrap(1);
    in = new Fl_Input(10,220, 130, 20);
	in->value("This is readonly");
	in->readonly(1);

    w->view()->end();

    s->end();
	
	Fl_Menu_ *m = (Fl_Menu_ *)menu->find("Windows");
	m->add(w->label(), w)->callback(cb_top_window, w);
	
	w->callback(close_mdi);

	w->show();	
    return w;
}

void cb_add_window(Fl_Widget *w, void *)
{	
	add_win(workspace->viewport(), false, "Added");
}

int main(int argc, char **argv)
{
    //Fl_Window w(400,400,"MDI TEST");
    Fl_Main_Window *mainwin = new Fl_Main_Window(600,400, "MDI TEST");

    // Add menu and change fonts
	menu = mainwin->menu();
    mainwin->menu()->menu(menutable);
    mainwin->menu()->tooltip("This is a menu bar");
    mainwin->menu()->callback(test_cb);

    // Add some buttons, add_button(label, tooltip, image, callback)
    Fl_Tool_Bar *toolbar = mainwin->toolbar();
    toolbar->tb_size(Fl_Tool_Bar::TB_SIZE_BIG);
    toolbar->spacing(4);
    toolbar->add_button("This", "Toolbar button 1", 0, 0);
    toolbar->add_button("Is",   "Toolbar button 2", 0, 0);
    toolbar->add_button("Tool", "Toolbar button 3", 0, 0);
    toolbar->add_button("Bar",  "Toolbar button 4", 0, 0);
    toolbar->add_divider();
    toolbar->add_button("After",  "Toolbar button 5", 0, 0);
    toolbar->add_button("Divider","Toolbar button 6", 0, 0);

    // Workspace has scrollbars
    workspace = new Fl_Workspace(10,30,380,360);
    // Viewport doesnt...
    //Fl_MDI_Viewport s(10,30,380,360);

    workspace->viewport()->menu(mainwin->menu());

    workspace->viewport()->begin();

    Fl_Button *b;
    new Fl_Box(10,10,130,20,"Min / Max:");
    b = new Fl_Check_Button(10,30,130,20,"Animate");
    b->value(Fl_MDI_Window::animate());
    b->callback(cb_anim);

    b = new Fl_Check_Button(10,50,130,20,"Opaque");
    b->value(Fl_MDI_Window::animate_opaque());
    b->callback(cb_opaq);

	b = new Fl_Button(10,100,130,20,"Add new");
	b->callback(cb_add_window);

    workspace->viewport()->end();

    // Set MDI workspace to mainwindow's central widget
    mainwin->view(workspace);

    Fl_MDI_Window *c;
    c = add_win(workspace->viewport(), false,"non-resizable");
	c->resizable(0);
    c->titlebar()->h(15); //"Tool" Window :)    
    c->position(200,10);
    //c->detach();	

    c = add_win(workspace->viewport(), true, "Double Buffered");
    //c->animate(true);
    //c->animate_mode(true);    
    c->minh(100);	

	workspace->relayout_all();

    // Add statusbar and set text there
	Fl_MDI_Bar *tasks = new Fl_MDI_Bar(0,10,600,25);
	tasks->spacing(5);
	workspace->viewport()->taskbar(tasks);
    mainwin->status(tasks);//->label("This is status bar...");

    mainwin->end();

    //Read defaults, init locale and show the window
    mainwin->show(argc, argv);

	Fl::run();
	delete mainwin;
    return 0;
}

