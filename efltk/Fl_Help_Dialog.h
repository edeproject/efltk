#ifndef FL_HELP_DIALOG_H_
#define FL_HELP_DIALOG_H_

#include "Fl.h"
#include "Fl_Double_Window.h"
#include "Fl_Menu_Bar.h"
#include "Fl_Item_Group.h"
#include "Fl_Item.h"
#include "Fl_Group.h"
#include "Fl_Button.h"
#include "Fl_File_Dialog.h"
#include "Fl_Simple_Html.h"

class Fl_Help_Dialog : public Fl_Double_Window
{
public:
    Fl_Help_Dialog(int x, int y, int w, int h, const char *l);
    Fl_Help_Dialog(int w, int h, const char *l);
    virtual ~Fl_Help_Dialog();

    void init();
    void make_group(int w, int h);

    void load(const char *f) { load_file(f); }
    void load_file(const char *f);
    void previous_url();
    void next_url();
    void open_file();

    // Method add/remove from history
    void push_prev(const char *url);
    char *pop_prev();

    void push_next(const char *url);
    char *pop_next();

private:
    Fl_Simple_Html *htmlWidget;

    static void cb_close(Fl_Widget*, void*);
    static void cb_back(Fl_Button*, void*);
    static void cb_next(Fl_Button*, void*);
    static void cb_open(Fl_Button*, void*);
    static void cb_html_link(Fl_Widget *w, void *d);

    char *prev_hist[10];
    char *next_hist[10];

    Fl_Button *back, *next;

    Fl_Menu_Bar *menubar_;
};

#endif
