#ifndef _FL_BUTTON_GROUP_H_
#define _FL_BUTTON_GROUP_H_

#include "Fl_Group.h"
#include "Fl_Input.h"
#include "Fl_Button.h"
#include "Fl_String_List.h"

/**
 * Fl_Button_Group
 */
class FL_API Fl_Button_Group : public Fl_Group {
public:
	static Fl_Named_Style* default_style;

	// Values for type()
	enum {
		NORMAL_BUTTONS = 0,
		CHECK_BUTTONS,
		RADIO_BUTTONS		
	};

    Fl_Button_Group(int x, int y, int w, int h, const char *label = 0);

    void buttons(const Fl_String_List& sl);

    Fl_String value() const;
    
	void value(const char *s, const char *separator="|");
	void value(const Fl_String &s, const char *separator="|");
	void value(const Fl_String_List &sl);

    virtual void layout();
    virtual void preferred_size(int& x,int& y) const;

protected:
    Fl_Button     *m_input_button;	// Button for input field
    Fl_Input      *m_input;			// Input field

	int button_index(const char *label);
	void deselect_all();
    virtual Fl_Button *create_button(const char *label);
};

class Fl_Check_Buttons : public Fl_Button_Group
{
public:
	Fl_Check_Buttons(int x, int y, int w, int h, const char *label = 0) : Fl_Button_Group(x,y,w,h,label) { type(CHECK_BUTTONS); }
};

class Fl_Radio_Buttons : public Fl_Button_Group
{
public:
	Fl_Radio_Buttons(int x, int y, int w, int h, const char *label = 0) : Fl_Button_Group(x,y,w,h,label) { type(RADIO_BUTTONS); }
};

#endif