#ifndef _FL_MAINWIN_H_
#define _FL_MAINWIN_H_

#include "Fl_Double_Window.h"
#include "Fl_Button.h"
#include "Fl_Box.h"
#include "Fl_Widget.h"
#include "Fl_Pack.h"
#include "Fl_Bar.h"
#include "Fl.h"
#include "Fl_Menu_Bar.h"
#include "Fl_Tool_Bar.h"

class Fl_Main_Window : public Fl_Double_Window
{
public:
    Fl_Main_Window(int w, int h, const char *l=0);
    ~Fl_Main_Window();

    void menu(Fl_Menu_Bar *w);
    Fl_Menu_Bar *menu();

    void toolbar(Fl_Tool_Bar *w);
    Fl_Tool_Bar *toolbar();

    void view(Fl_Group *w);
    Fl_Group *view();

    void status(Fl_Group *w);
    Fl_Group *status();

protected:
    // If you inherit this class, you get access to pack,
    // where you can add e.g. second toolbar
    Fl_Pack *pack() { return pack_; }

private:
    Fl_Pack   *pack_;
    Fl_Menu_Bar  *menu_;
    Fl_Tool_Bar  *toolbar_;
    Fl_Group  *view_;
    Fl_Group  *status_;
};

#endif

