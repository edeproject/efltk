#ifndef __FL_BUTTON_GROUP_H__
#define __FL_BUTTON_GROUP_H__

#include <efltk/Fl_Group.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_String_List.h>

class Fl_Query;

class FL_API Fl_Button_Group : public Fl_Group {
protected:
    bool           m_singleSelection;
    Fl_String      m_lastValue;
    Fl_String_List m_buttonLabels;
    Fl_Button     *m_otherButton;
    Fl_Input      *m_otherInput;
    int  buttonIndex(const char *buttonLabel);
    void deselectAllButtons();
    void selectButton(int choice);
    virtual Fl_Button *createButton(const char *) = 0L;
public:

    Fl_Button_Group(int,int,int,int,const char * = 0);
    void buttons(const Fl_String_List& sl);

    virtual void clearButtons();

    virtual Fl_String value() const;
    virtual void value(const Fl_String s);

    void layout();
    void preferred_size(int& x,int& y);

    virtual void load(Fl_Query *);
    virtual void save(Fl_Query *);
};

#endif
