#ifndef FL_INPUT_BROWSER_H_
#define FL_INPUT_BROWSER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Fl_Input.h"
#include "Fl_Menu_.h"
#include "Fl_Menu_Window.h"

class ComboBrowser;
class ComboWindow;

class Fl_Input_Browser : public Fl_Menu_ {
public:

    enum { // values for type()
        NORMAL = 0,
        NONEDITABLE = 1,
        INDENTED = 2,
        NONEDITABLE_INDENTED = 3
    };
    static Fl_Named_Style* default_style;

    Fl_Input_Browser(int,int,int,int,const char * = 0);
    virtual ~Fl_Input_Browser();

    void popup();
    void hide_popup();

    virtual int handle(int);

    void maxw(int i) { maxw_ = i; }
    void maxh(int i) { maxh_ = i; }
    int maxw() { return maxw_; }
    int maxh() { return maxh_; }

    int minw() { return minw_; }
    int minh() { return minh_; }

    void clear() { Fl_Menu_::clear(); item(0); }

    void value(const char *v) { input_->value(v); }
    const char *value() { return input_->value(); }

    Fl_Input *input() { return input_; }

protected:
    virtual void draw();

    friend class ComboWindow;
    friend class ComboBrowser;

    ComboWindow *win;
    ComboBrowser *list;

    Fl_Input *input_;
    int minw_, minh_, maxw_, maxh_;
    int over_now, over_last;

    static void input_cb(Fl_Input *in, void *d);
};

#endif
