#ifndef __FL_CHECK_BUTTONS_H__
#define __FL_CHECK_BUTTONS_H__

#include <efltk/Fl_Button_Group.h>

class FL_API Fl_Check_Buttons : public Fl_Button_Group {
    static void checkButtonsCallback(Fl_Widget *,void *);
protected:
    virtual Fl_Button *createButton(const char *label);
public:
    Fl_Check_Buttons(int,int,int,int,const char * = 0);
    //virtual Fl_String className() const { return "Fl_Check_Buttons"; }
};

#endif
