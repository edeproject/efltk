#ifndef __FL_RADIO_BUTTONS_H__
#define __FL_RADIO_BUTTONS_H__

#include <efltk/Fl_Button_Group.h>

class FL_API Fl_Radio_Buttons : public Fl_Button_Group {
    static void radioButtonsCallback(Fl_Widget *,void *);
protected:
    virtual Fl_Button *createButton(const char *label);
public:
    Fl_Radio_Buttons(int,int,int,int,const char * = 0);

    //virtual CString className() const { return "Fl_Radio_Button"; }
};

#endif
