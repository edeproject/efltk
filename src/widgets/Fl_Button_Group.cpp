#include <efltk/Fl.h>
#include <efltk/Fl_Scroll.h>
#include <efltk/Fl_Round_Button.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Button_Group.h>
#include <efltk/db/Fl_Query.h>

#include <stdio.h>
#include <string.h>

Fl_Button_Group::Fl_Button_Group(int x,int y,int w,int h,const char *l)
: Fl_Group (x,y,w,h,l) {
    end();
    clearButtons();
    m_singleSelection = false;
}

void Fl_Button_Group::clearButtons() {
    clear();
    m_buttonLabels.clear();
    m_otherInput = 0L;
    m_otherButton = 0L;
}

void Fl_Button_Group::buttons(const Fl_String_List& sl) {
    clearButtons();
    m_buttonLabels = sl;
    unsigned buttonsCount = m_buttonLabels.count();
    begin();
    for (unsigned i = 0; i < buttonsCount; i++) {
        Fl_String& si = m_buttonLabels[i];
        Fl_Button *btn = createButton(si.c_str());
        if (si == "*" && !m_otherButton) {  // Only one free entry is allowed
            btn->label("");
            m_otherButton = btn;
            m_otherInput = new Fl_Input(10,10,50,22);
        }
    }
    end();
    relayout();
}

void Fl_Button_Group::layout() {
    Fl_Group::layout();
    unsigned    cnt = children();
    int x = box()->dx() + 2;
    int y = box()->dy() + 2;
    int h = text_size() * 3 / 2;
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Button *btn = dynamic_cast<Fl_Button *>(child(i));
        if (!btn) continue;
        int ww = w() - box()->dx() * 2 - 4;
        if (btn == m_otherButton)
            ww = h + 2;
        btn->resize(x,y,ww,h);
        y += h + 2;
    }
    if (m_otherInput) {
        int h = 22;
        int y = m_otherButton->y() + m_otherButton->h()/2 - h/2;
        int x = m_otherButton->x() + m_otherButton->w() + 1;
        int w = this->w() - x - 4;
        m_otherInput->resize(x,y,w,h);
    }
}

Fl_String Fl_Button_Group::value() const {
    Fl_String     result;
    unsigned    cnt = children();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Button *b = dynamic_cast<Fl_Button *>(child(i));
        if (!b) continue;
        if (b->value()) {
            if (result.length())
                result += "|";
            if (b == m_otherButton) 
                result += m_otherInput->value();
            else result += b->label();
            if (m_singleSelection)
                break;
        }
    }
    return result;
}

int Fl_Button_Group::buttonIndex(const char *buttonLabel) {
    unsigned    cnt = children();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Button *b = dynamic_cast<Fl_Button *>(child(i));
        if (!b) continue;
        if (strcmp(b->label(),buttonLabel) == 0)
            return i;
    }
    return -1;
}

void Fl_Button_Group::deselectAllButtons() {
    unsigned    cnt = children();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Button *b = dynamic_cast<Fl_Button *>(child(i));
        if (!b) continue;
        b->value(0);
    }
}

void Fl_Button_Group::value(const Fl_String s) {
    deselectAllButtons();
    Fl_String_List sl(s,"|");
    unsigned cnt = sl.count();
    for (unsigned i = 0; i < cnt; i++) {
        int ndx = buttonIndex(sl[i].c_str());
        if (ndx > -1) {
            Fl_Button *b = (Fl_Button *)child(ndx);
            b->value(1);
        } else {
            if (m_otherButton) {
                m_otherButton->value(1);
                m_otherInput->value(sl[i].c_str());
            }
        }
        if (m_singleSelection)
            break;
    }

    do_callback(FL_DATA_CHANGE);
}

void Fl_Button_Group::preferred_size(int& w,int& h) {
    h = 0;
    unsigned cnt = children();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Button *b = dynamic_cast<Fl_Button *>(child(i));
        if (!b) continue;
        h += b->h();
    }
    w = this->w();
}

void Fl_Button_Group::load(Fl_Query *loadQuery) {
    if (!field_name().length()) return;
    value((*loadQuery)[field_name().c_str()].get_string());
}

void Fl_Button_Group::save(Fl_Query *updateQuery) {
    if (!field_name().length()) return;
    Fl_Param& param = updateQuery->param(field_name().c_str());
    param.set_string( value().c_str() );
}
