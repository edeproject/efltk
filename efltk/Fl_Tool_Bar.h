#ifndef _FL_TOOLBAR_H_
#define _FL_TOOLBAR_H_

#include "Fl_Bar.h"
#include "Fl_Menu_Button.h"

class Fl_Tool_Bar : public Fl_Bar
{
public:
    static Fl_Named_Style* default_style;

    Fl_Tool_Bar(int x, int y, int w, int h, const char *label=0);
    ~Fl_Tool_Bar();

    static int button_w;
    static int button_h;
    Fl_Widget *add_button(const char *label, const char *tip, Fl_Image *image, Fl_Callback *cb);
    Fl_Widget *add_divider();

    void draw();
    void layout();
    int handle(int ev);

    static void button_glyph(const Fl_Widget* widget, int glyph, int x,int y,int w,int h, Fl_Flags flags);

    // Space between items
    int spacing() { return space_; }
    void spacing(int v) { space_ = v; }

private:
    int space_;

    Fl_Menu_ *menu_;
    Fl_Widget *menu_but, *right_;
    static void cb_menu(Fl_Widget *w, void *data);
};

#endif
