//
// $Id$
//
// Demo program for eFLTK
//

#include <efltk/Fl_Main_Window.h>
#include <efltk/Fl_Stock_Images.h>
#include <efltk/Fl_Radio_Buttons.h>
#include <efltk/Fl_Box.h>
#include <efltk/fl_ask.h>

Fl_Main_Window *mainwin;

enum {
    QUIT = 1,
    ABOUT
};

void handle_action(long id)
{
    switch(id) {
    case QUIT:
        mainwin->hide();
        break;

    case ABOUT:
        fl_message("eFLTK demo app!\n(c) EDE-Team 2003");
        break;
    }
}

void cb_toolbar(Fl_Tool_Bar *bar, void *arg)
{
    if(!bar->item()) return;
    handle_action(bar->item()->argument());
}

void cb_menubar(Fl_Menu_Bar *bar, void *arg)
{
    if(!bar->item()) return;
    handle_action(bar->item()->argument());
}

void cb_size(Fl_Button_Group *g, void *arg)
{
    if(!g->visible_r()) return;
    int id = g->find(Fl::focus());
    Fl_Tool_Bar::default_tb_size((Fl_Tool_Bar::TbSize)id);

    mainwin->toolbar()->relayout();
    mainwin->toolbar()->redraw();
    mainwin->relayout();
    mainwin->redraw();
}

void cb_pos_mode(Fl_Button_Group *g, void *arg)
{
    if(!g->visible_r()) return;
    int id = g->find(Fl::focus()) + 1;
    Fl_Tool_Button::default_textpos((Fl_Tool_Button::TbTextPos)id);

    mainwin->toolbar()->relayout();
    mainwin->toolbar()->redraw();
    mainwin->relayout();
    mainwin->redraw();
}

void cb_show_mode(Fl_Button_Group *g, void *arg)
{
    if(!g->visible_r()) return;
    int id = g->find(Fl::focus()) + 1;
    Fl_Tool_Button::default_showmode((Fl_Tool_Button::TbShowMode)id);

    mainwin->toolbar()->relayout();
    mainwin->toolbar()->redraw();
    mainwin->relayout();
    mainwin->redraw();
}

int main(int argc, char **argv)
{
    Fl_Main_Window window(300,360,"eFLTK main window test");
    mainwin = &window;
    window.size_range(150, 360);

    // Menu bar
    window.menu()->callback((Fl_Callback*)cb_menubar);
    window.menu()->add("&File/&Quit", FL_ALT+'q', 0, (void*)QUIT);
    window.menu()->add("&Help/&About", FL_ALT+'a', 0, (void*)ABOUT);

    // Tool bar
    window.toolbar()->callback((Fl_Callback*)cb_toolbar);

    window.toolbar()->add_button(Fl_Stock_Images::get_image(Fl_Stock_Images::SI_CANCEL), (int)QUIT, "Quit", "Quit App..");
    window.toolbar()->add_button(Fl_Stock_Images::get_image(Fl_Stock_Images::SI_HELP), (int)ABOUT, "About", "About..");
    window.toolbar()->add_divider();
    window.toolbar()->add_button(Fl_Stock_Images::get_image(Fl_Stock_Images::SI_PREV), 0, "Prev", "Previous..");
    window.toolbar()->add_button(Fl_Stock_Images::get_image(Fl_Stock_Images::SI_NEXT), 0, "Next", "Next..");
    window.toolbar()->add_divider();
    window.toolbar()->add_button(Fl_Stock_Images::get_image(Fl_Stock_Images::SI_CANCEL), 0, "1. Useless", "Useless button number 1");
    window.toolbar()->add_button(Fl_Stock_Images::get_image(Fl_Stock_Images::SI_NEW), 0, "2. Useless", "Useless button number 2");
    window.toolbar()->add_button(Fl_Stock_Images::get_image(Fl_Stock_Images::SI_OK), 0, "3. Useless", "Useless button number 3");
    window.toolbar()->add_button(Fl_Stock_Images::get_image(Fl_Stock_Images::SI_NO), 0, "4. Useless", "Useless button number 4");

    // View
    window.view()->begin();
    Fl_String_List strlist;

    strlist.from_string("Small|Big", "|");
    Fl_Radio_Buttons size_group("Sizes:");
    size_group.callback((Fl_Callback*)cb_size);
    size_group.buttons(strlist);
    size_group.value("Small");

    strlist.from_string("Bottom|Right", "|");
    Fl_Radio_Buttons pos_group("Position Modes:");
    pos_group.callback((Fl_Callback*)cb_pos_mode);
    pos_group.buttons(strlist);
    pos_group.value("Bottom");

    strlist.from_string("Text|Image|Both|Auto", "|");
    Fl_Radio_Buttons show_group("Show Modes:");
    show_group.callback((Fl_Callback*)cb_show_mode);
    show_group.buttons(strlist);
    show_group.value("Auto");

    window.view()->end();

    // Status bar
    window.status()->label("Ready..");

    // Show it!
    window.show(argc, argv);
    return Fl::run();
}
