#ifndef __FL_COMBO_BOX_H__
#define __FL_COMBO_BOX_H__

#include <efltk/Fl_Group.h>
#include <efltk/Fl_ListView.h>

enum Fl_Combo_Box_Buttons {
    FL_CBB_BROWSE  = 1,
    FL_CBB_INSERT  = 2,
    FL_CBB_EDIT    = 4,
    FL_CBB_DELETE  = 8,
    FL_CBB_REFRESH = 16
};

class Fl_Combo_Box_Panel;
class Fl_Popup_ListView;
class Fl_Button;

class Fl_Combo_Box : public Fl_Group {
    Fl_Combo_Box_Panel  *m_panel;
    Fl_Popup_ListView   *m_popup;
    Fl_Button           *m_buttons[5];

    void ctor_init();
protected:
    static void Fl_Combo_Box::cb_browse(Fl_Widget *w, void *data);
    static void Fl_Combo_Box::cb_button(Fl_Widget *w, void *data);
public:
    /** Creates a new combo box widget using the given position, size, and label string. */
    Fl_Combo_Box(int x,int y,int w,int h,const char *label=0);

    /** Creates the combo box widget using the label, size, alignment, and label_width. */
    Fl_Combo_Box(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    Fl_ListView *listview() const;

    void buttons(int buttons_set=FL_CBB_BROWSE);

    void fill(Fl_Data_Source& ds,int user_data_column=-1) { listview()->fill(ds,user_data_column); }

    // Get the active item user_data, or set item by user_data
    int value() const;
    void value(int) const;

    virtual void preferred_size(int& w,int &h) const;

    // Get text from the active item by column
    Fl_String text(int column) const;
};

#endif
