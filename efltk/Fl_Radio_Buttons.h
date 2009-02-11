#ifndef __FL_RADIO_BUTTONS_H_
#define __FL_RADIO_BUTTONS_H_

#include "Fl_Button_Group.h"

/**
 * Fl_Radio_Buttons
 */

class FL_API Fl_Radio_Buttons : public Fl_Button_Group
{
public:
    /** The traditional constructor creates the radio buttons group using the position, size, and label. */
    Fl_Radio_Buttons(int x, int y, int w, int h, const char *label = 0)
    : Fl_Button_Group(x,y,w,h,label) { type(RADIO_BUTTONS); }

    /** The new style constructor creates the radio buttons group using the label, size, alignment, and label_width. */
    Fl_Radio_Buttons(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100)
    : Fl_Button_Group(l,layout_size,layout_al,label_w) { type(RADIO_BUTTONS); }
};

#endif
