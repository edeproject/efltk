#include <efltk/Fl.h>
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
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_ListView_Item.h>
#include <efltk/Fl_File_Dialog.h>

#include <stdio.h>

Fl_Menu_Item hugemenu[100];

Fl_Menu_Item menutable[] = {
  {"&File",0,0,0,FL_SUBMENU},
    {"&Open",	FL_ALT+'o', 0, 0, FL_MENU_INACTIVE},
    {"&Close",	0,	0},
    {"&Quit",	FL_ALT+'q', 0, 0, FL_MENU_DIVIDER},
    {"shortcut",'a'},
    {"shortcut",FL_SHIFT+'a'},
    {"shortcut",FL_CTRL+'a'},
    {"shortcut",FL_CTRL+FL_SHIFT+'a'},
    {"shortcut",FL_ALT+'a'},
    {"shortcut",FL_ALT+FL_SHIFT+'a'},
    {"shortcut",FL_ALT+FL_CTRL+'a'},
    {"shortcut",FL_ALT+FL_SHIFT+FL_CTRL+'a', 0,0, FL_MENU_DIVIDER},
  {"shortcut",'\r'/*FL_Enter*/},
    {"shortcut",FL_CTRL+FL_Enter, 0,0, FL_MENU_DIVIDER},
    {"shortcut",FL_F(1)},
    {"shortcut",FL_SHIFT+FL_F(1)},
    {"shortcut",FL_CTRL+FL_F(1)},
    {"shortcut",FL_SHIFT+FL_CTRL+FL_F(1)},
    {"shortcut",FL_ALT+FL_F(1)},
    {"shortcut",FL_ALT+FL_SHIFT+FL_F(1)},
    {"shortcut",FL_ALT+FL_CTRL+FL_F(1)},
    {"shortcut",FL_ALT+FL_SHIFT+FL_CTRL+FL_F(1), 0,0, FL_MENU_DIVIDER},
    {"&Submenus", FL_ALT+'S',	0, (void*)"Submenu1", FL_SUBMENU},
      {"A very long menu item"},
      {"&submenu",FL_CTRL+'S',	0, (void*)"submenu2", FL_SUBMENU},
	{"item 1"},
	{"item 2"},
	{"item 3"},
	{"item 4"},
	{0},
      {"after submenu"},
      {0},
    {0},
  {"&Edit",0,0,0,FL_SUBMENU},
    {"Undo",	FL_ALT+'z',	0},
    {"Redo",	FL_ALT+'r',	0, 0, FL_MENU_DIVIDER},
    {"Cut",	FL_ALT+'x',	0},
    {"Copy",	FL_ALT+'c',	0},
    {"Paste",	FL_ALT+'v',	0},
    {"Inactive",FL_ALT+'d',	0, 0, FL_MENU_INACTIVE},
    {"Clear",	0,	0, 0, FL_MENU_DIVIDER},
    {"Invisible",FL_ALT+'e',	0, 0, FL_MENU_INVISIBLE},
    {"Preferences",0,	0},
    {"Size",	0,	0},
    {0},
  {"&Checkbox",0,0,0,FL_SUBMENU},
    {"&Alpha",	0,	0, (void *)1, FL_MENU_TOGGLE|FL_MENU_VALUE},
    {"&Beta",	0,	0, (void *)2, FL_MENU_TOGGLE},
    {"&Gamma",	0,	0, (void *)3, FL_MENU_TOGGLE},
    {"&Delta",	0,	0, (void *)4, FL_MENU_TOGGLE|FL_MENU_VALUE},
    {"&Epsilon",0,	0, (void *)5, FL_MENU_TOGGLE},
    {"&Pi",	0,	0, (void *)6, FL_MENU_TOGGLE},
    {"&Mu",	0,	0, (void *)7, FL_MENU_TOGGLE|FL_MENU_DIVIDER},
    {"Red",	0,	0, (void *)1, FL_MENU_TOGGLE},
    {"Black",	0,	0, (void *)1, FL_MENU_TOGGLE|FL_MENU_DIVIDER},
    {"00",	0,	0, (void *)1, FL_MENU_TOGGLE},
    {"000",	0,	0, (void *)1, FL_MENU_TOGGLE},
    {0},
  {"&Radio",0,0,0,FL_SUBMENU},
    {"&Alpha",	0,	0, (void *)1, FL_MENU_RADIO},
    {"&Beta",	0,	0, (void *)2, FL_MENU_RADIO},
    {"&Gamma",	0,	0, (void *)3, FL_MENU_RADIO},
    {"&Delta",	0,	0, (void *)4, FL_MENU_RADIO|FL_MENU_VALUE},
    {"&Epsilon",0,	0, (void *)5, FL_MENU_RADIO},
    {"&Pi",	0,	0, (void *)6, FL_MENU_RADIO},
    {"&Mu",	0,	0, (void *)7, FL_MENU_RADIO|FL_MENU_DIVIDER},
    {"Red",	0,	0, (void *)1, FL_MENU_RADIO},
    {"Black",	0,	0, (void *)1, FL_MENU_RADIO|FL_MENU_DIVIDER},
    {"00",	0,	0, (void *)1, FL_MENU_RADIO},
    {"000",	0,	0, (void *)1, FL_MENU_RADIO},
    {0},
  {"&Font",0,0,0,FL_SUBMENU},
    {"Normal",	0, 0},
    {"Bold",	0, 0},
    {"Italic",	0, 0},
    {"BoldItalic",0,0},
    {"Small",	0, 0},
    {"Large",	0, 0},
    {"Emboss",	0, 0},
    {"Engrave",	0, 0},
    {"Shadow",	0, 0},
    {"@->",	0, 0},
    {0},
  {"E&mpty",0,0,0,FL_SUBMENU},
    {0},
  {"&Inactive", 0,	0, 0, FL_MENU_INACTIVE|FL_SUBMENU},
    {"A very long menu item"},
    {"A very long menu item"},
    {0},
  {"Invisible",0,	0, 0, FL_MENU_INVISIBLE|FL_SUBMENU},
    {"A very long menu item"},
    {"A very long menu item"},
    {0},
  {"&Huge", 0, 0, (void*)hugemenu, FL_SUBMENU_POINTER},
  {"button",0, 0, 0, FL_MENU_TOGGLE},
  {0}
};

void tool_cb(Fl_Widget* w, void*) {
    printf("Toolbar: %s\n", w->label());
}

void test_cb(Fl_Widget* w, void*) {
    Fl_Menu_* mw = (Fl_Menu_*)w;
    Fl_Widget* m = mw->item();
    if (!m)
        printf("Menu: NULL\n");
    else if (m->shortcut())
        printf("Menu: %s - %s\n", m->label(), Fl::key_name(m->shortcut()));
    else
        printf("Menu: %s\n", m->label());
    m->do_callback();
}

void cb_anim(Fl_Widget *w, void *data)
{
    if(w->value())
        Fl_MDI_Window::animate(true);
    else
        Fl_MDI_Window::animate(false);
}

void cb_opaq(Fl_Widget *w, void *data)
{
    if(w->value())
        Fl_MDI_Window::animate_opaque(true);
    else
        Fl_MDI_Window::animate_opaque(false);
}

void cb_detach(Fl_Widget *, void *data)
{
	Fl_MDI_Window *m = (Fl_MDI_Window *)data;
	if(!m->toplevel())
		m->detach();
}

void cb_attach(Fl_Widget *, void *data)
{
	Fl_MDI_Window *m = (Fl_MDI_Window *)data;
	if(m->toplevel())
		m->attach();
}

Fl_MDI_Window *add_win(Fl_MDI_Viewport *s, bool doublebuf, const char *n)
{
    s->begin();

    Fl_MDI_Window *w = new Fl_MDI_Window(10,10,150,250,n);
    w->show();

    if(doublebuf) {
        w->view()->end();
        Fl_Double_Window *win = new Fl_Double_Window(150,250);
        win->end();
        Fl_Group *g = w->view(win);
        delete g;
        win->show();
    }

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
    in->type(Fl_Input::WORDWRAP);
    in = new Fl_Input(10,220, 130, 20);

    w->view()->end();

    s->end();
    return w;
}

int main(int argc, char **argv)
{
    for (int i=0; i<99; i++) {
        char buf[100];
        sprintf(buf,"Item %d",i);
        hugemenu[i].text = strdup(buf);
    }

    //Fl_Window w(400,400,"MDI TEST");
    Fl_Main_Window mainwin(600,400, "MDI TEST");

    // Add menu and change fonts
    mainwin.menu()->menu(menutable);
    mainwin.menu()->tooltip("This is a menu bar");
    mainwin.menu()->callback(test_cb);
    Fl_Menu_Bar &menubar = *mainwin.menu();
    menubar.find("&Font/Normal")->label_font(FL_HELVETICA);
    menubar.find("&Font/Bold")->label_font(FL_HELVETICA_BOLD);
    menubar.find("&Font/Italic")->label_font(FL_HELVETICA_ITALIC);
    menubar.find("&Font/BoldItalic")->label_font(FL_HELVETICA_BOLD_ITALIC);
    menubar.find("&Font/Small")->label_size(10);
    menubar.find("&Font/Large")->label_size(24);
    menubar.find("&Font/Emboss")->label_type(FL_EMBOSSED_LABEL);
    menubar.find("&Font/Engrave")->label_type(FL_ENGRAVED_LABEL);
    menubar.find("&Font/Shadow")->label_type(FL_SHADOW_LABEL);
    menubar.find("&Font/@->")->label_type(FL_SYMBOL_LABEL);
    menubar.find("&Checkbox/Red")->label_color(FL_RED); // label text red
    menubar.find("&Checkbox/Red")->selection_text_color(FL_RED); // label text red when selected
    menubar.find("&Checkbox/Red")->text_color(FL_RED); // check mark red
    menubar.find("&Checkbox/Black")->label_color(FL_BLACK);
    menubar.find("&Checkbox/Black")->selection_text_color(FL_BLACK);
    menubar.find("&Checkbox/Black")->text_color(FL_BLACK);
    menubar.find("&Radio/Red")->label_color(FL_RED);
    menubar.find("&Radio/Red")->selection_text_color(FL_RED);
    menubar.find("&Radio/Red")->text_color(FL_RED);
    menubar.find("&Radio/Black")->label_color(FL_BLACK);
    menubar.find("&Radio/Black")->selection_text_color(FL_BLACK);
    menubar.find("&Radio/Black")->text_color(FL_BLACK);
    menubar.find("&Huge/Item 69")->deactivate();
    menubar.begin();
    menubar.right_layout( new Fl_Item("&Help") );
    menubar.end();


    // Set default button sizes, toolbar defaults is 24x24
    Fl_Tool_Bar::button_h = 32;
    Fl_Tool_Bar::button_w = 40;
    // Add some buttons, add_button(label, tooltip, image, callback)
    Fl_Tool_Bar *toolbar = mainwin.toolbar();
    toolbar->space(4);
    toolbar->add_button("This", "Toolbar button 1", 0, 0);
    toolbar->add_button("Is",   "Toolbar button 2", 0, 0);
    toolbar->add_button("Tool", "Toolbar button 3", 0, 0);
    toolbar->add_button("Bar",  "Toolbar button 4", 0, 0);
    toolbar->add_divider();
    toolbar->add_button("After",  "Toolbar button 5", 0, 0);
    toolbar->add_button("Divider","Toolbar button 6", 0, 0);

    // Workspace has scrollbars
    Fl_Workspace s(10,30,380,360);
    // Viewport doesnt...
    //Fl_MDI_Viewport s(10,30,380,360);

    s.viewport()->begin();

    Fl_Button *b;
    new Fl_Box(10,10,130,20,"Min / Max:");
    b = new Fl_Check_Button(10,30,130,20,"Animate");
    b->value(Fl_MDI_Window::animate());
    b->callback(cb_anim);
    b = new Fl_Check_Button(10,50,130,20,"Opaque");
    b->value(Fl_MDI_Window::animate_opaque());
    b->callback(cb_opaq);

    s.viewport()->end();

    // Set MDI workspace to mainwindow's central widget
    mainwin.view(&s);

    Fl_MDI_Window *c;
    c = add_win(s.viewport(), false,"non-resizable");
    c->titlebar()->h(15); //"Tool" Window :)
    s.relayout_all();
    c->position(200,10);
    //c->detach();

    c = add_win(s.viewport(), true, "Double Buffered");
    //c->animate(true);
    //c->animate_mode(true);
    c->resizable(c->view());
    c->minh(100);

    // Add statusbar and set text there
    mainwin.status()->label("This is status bar...");

    mainwin.end();

    //Read defaults, init locale and show the window
    mainwin.show(argc, argv);

    s.redraw_all();

    return Fl::run();
}

