#ifndef __FL_CHECK_BUTTONS_H_
#define __FL_CHECK_BUTTONS_H_

#include "Fl_Button_Group.h"

/**
 * Fl_Check_Buttons
 */

class FL_API Fl_Check_Buttons : public Fl_Button_Group
{
public:
    /** The traditional constructor creates the check buttons group using the position, size, and label. */
    Fl_Check_Buttons(int x, int y, int w, int h, const char *label = 0)
    : Fl_Button_Group(x,y,w,h,label) { type(CHECK_BUTTONS); }

    /** The new style constructor creates the check buttons group using the label, size, alignment, and label_width. */
    Fl_CCheck_Buttons(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100)
    : Fl_Button_Group(const char* l,int layout_size,Fl_Align layout_al,int label_w) { type(CHECK_BUTTONS); }
};

#endif
