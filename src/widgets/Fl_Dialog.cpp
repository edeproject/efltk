/***************************************************************************
                          Fl_Dialog.cpp  -  description
                             -------------------
    begin                : Tue Nov 12 2002
    copyright            : (C) 2002 by Alexey Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "../core/fl_internal.h"

#include <efltk/Fl.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Tabs.h>
#include <efltk/Fl_Stock_Images.h>
#include <efltk/fl_ask.h>
#include <efltk/fl_draw.h>

#include <efltk/Fl_Dialog.h>

struct Fl_Dialog_Button_Template {
    int         id;
    const char *label;
    Fl_Stock_Images::SI_Type type;
};

static const Fl_Dialog_Button_Template buttonTemplates[] = {
    { Fl_Dialog::BTN_OK,     N_("Ok"),      Fl_Stock_Images::SI_OK },
    { Fl_Dialog::BTN_CANCEL, N_("Cancel"),  Fl_Stock_Images::SI_CANCEL },
    { Fl_Dialog::BTN_YES,    N_("Yes"),     Fl_Stock_Images::SI_OK },
    { Fl_Dialog::BTN_NO,     N_("No"),      Fl_Stock_Images::SI_NO },
    { Fl_Dialog::BTN_RETRY,  N_("Retry"),   Fl_Stock_Images::SI_REFRESH },
    { Fl_Dialog::BTN_REFRESH,N_("Refresh"), Fl_Stock_Images::SI_REFRESH },
    { Fl_Dialog::BTN_CONFIRM,N_("Confirm"), Fl_Stock_Images::SI_OK },
    { Fl_Dialog::BTN_IGNORE, N_("Ignore"),  Fl_Stock_Images::SI_NO },
    { Fl_Dialog::BTN_HELP,   N_("Help"),    Fl_Stock_Images::SI_HELP },
    { 0,             "",       Fl_Stock_Images::SI_HELP }
};

class Fl_Dialog_Button : public Fl_Group {
    Fl_Button *m_button;
    bool            m_default;
protected:
    static void dialog_button_cb(Fl_Widget *w,void *);
public:
    Fl_Dialog_Button(const char* l, Fl_Image *i, int id);

    virtual void preferred_size(int& w,int& h) const;
    virtual void layout();

    void default_button(bool d);
    bool default_button() const { return m_default; }
};

void Fl_Dialog_Button::dialog_button_cb(Fl_Widget *w,void *) {
    Fl_Group *frame = w->parent();
    frame->do_callback(FL_DIALOG_BTN);
}

Fl_Dialog_Button::Fl_Dialog_Button(const char* l, Fl_Image *i, int id)
: Fl_Group("",30,FL_ALIGN_RIGHT) {
    m_button = new Fl_Button(0,0,10,10,l);
    m_button->image(i);
    m_button->callback(Fl_Dialog_Button::dialog_button_cb,(void *)id);
    end();
}

void Fl_Dialog_Button::preferred_size(int& w,int& h) const {
    int bw = w;
    int bh = h - 6;

    if (m_default) bw -= 6;

    m_button->preferred_size(bw,bh);

    w = bw;

    if (bh + 6 > h)
        h = bh + 6;

    if (m_default) w += 6;
}

void Fl_Dialog_Button::layout() {
    Fl_Group::layout();
    int bx = 0;
    int bw = w();
    int bh = h() - 6;
    if (m_default) {
        bx = 3;
        bw -= 6;
    }
    m_button->resize(bx,3,bw,bh);
}


void Fl_Dialog_Button::default_button(bool d) {
    if (d) {
        box(FL_THIN_DOWN_BOX);
        color(FL_BLACK);
    } else {
        box(FL_NO_BOX);
    }
    m_default = d;
}

void Fl_Dialog::escape_callback(Fl_Dialog *dialog, void *) {
    if (dialog->m_buttons & Fl_Dialog::BTN_CANCEL) {
        Fl::exit_modal();
        dialog->m_modalResult = Fl_Dialog::BTN_CANCEL;
    }
}

void Fl_Dialog::buttons_callback(Fl_Button *btn, long id)
{
    Fl_Dialog *dialog = (Fl_Dialog *)btn->window();

    if (id & (BTN_OK|BTN_YES)) {
        try {
            if (!dialog->save_data())
                return;
        }
        catch (Fl_Exception& e) {
            Fl::warning("Can't save data. " + e.text());
            return;
        }
    }

    if (id & (BTN_OK|BTN_CANCEL|BTN_YES|BTN_NO|BTN_RETRY|BTN_CONFIRM|BTN_IGNORE)) {
        Fl::exit_modal();
        dialog->m_modalResult = (int)id;
    } else {
        // this requires event_argument!
        dialog->do_callback(btn,btn->argument(),FL_DIALOG_BTN);
    }
}

Fl_Dialog::Fl_Dialog(int ww, int hh, const char *label, Fl_Data_Source *ds) 
: Fl_Window(ww,hh,label) 
{
    m_defaultButton = 0;

    m_buttonPanel = new Fl_Group("",30,FL_ALIGN_BOTTOM);
    //Fl_Box *resize = new Fl_Box(0,-1,10,1);
    //resize->hide();
    m_buttonPanel->layout_spacing(2);
    m_buttonPanel->end();

    m_tabs = new Fl_Tabs(0,0,10,10);
    m_tabs->show_tabs(false);
    m_tabs->layout_align(FL_ALIGN_CLIENT);
    m_modalResult = 0;
    m_externalDataSource = (ds != NULL);

    if (ds) m_dataSource = ds;
    else    m_dataSource = new Fl_Dialog_DS();

    m_dataSource->parent(m_tabs);

    callback((Fl_Callback*)escape_callback);
}

Fl_Dialog::~Fl_Dialog() {
    if (!m_externalDataSource)
        delete m_dataSource;
    clear_buttons();
}

void Fl_Dialog::enable_button(int button_mask,bool enabled)
{
    for (unsigned i = 0; i < m_buttonList.size(); i++) {
        Fl_Widget *btn = m_buttonList[i];
        if (button_mask & btn->argument()) {
            if (enabled)
                btn->activate();
            else btn->deactivate();          
        }
    }
}

void Fl_Dialog::submit(int button_id)
{
    for (unsigned i = 0; i < m_buttonList.size(); i++) {
        Fl_Widget *btn = m_buttonList[i];
        if(button_id == btn->argument()) {
            btn->do_callback(btn->argument());
            return; // Only one allowed
        }
    }
}

Fl_Widget *Fl_Dialog::find_widget(const char *field_name) const 
{
    unsigned n_pages = m_tabs->children();
    for (unsigned i = 0; i < n_pages; i++) {
        Fl_Widget *widget = m_tabs->child(i);
        if(widget->is_group()) {
            Fl_Group *page = (Fl_Group *)widget;
            unsigned  n_widgets = page->children();
            for (unsigned j = 0; j < n_widgets; j++) {
                widget = page->child(j);
                if(widget->field_name()==field_name)
                    return widget;
            }
        } else {
            if(widget->field_name()==field_name)
                return widget;
        }
    }
    return (Fl_Widget*)0;
}

const Fl_Variant& Fl_Dialog::operator [] (const char *field_name) const {
    return (*m_dataSource)[field_name];
}

Fl_Variant& Fl_Dialog::operator [] (const char *field_name) {
    return (*m_dataSource)[field_name];
}

void Fl_Dialog::clear_buttons() 
{
    unsigned cnt = m_buttonList.count();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Widget *btn = m_buttonList[i];
        m_buttonPanel->remove(btn);
        delete btn;
    }
    m_buttonList.clear();
    m_defaultButton = 0L;
}

void Fl_Dialog::buttons(int buttons_mask,int default_button) 
{
    Fl_Group *saved = Fl_Group::current();

    Fl_Dialog_Button *btn;
    unsigned i;
    m_buttons = buttons_mask;
    clear_buttons();

    int maxh = 25;

    m_buttonPanel->begin();
    for(i = 0; buttonTemplates[i].id; i++) 
    {
        const Fl_Dialog_Button_Template& buttonTemplate = buttonTemplates[i];
        long id = buttonTemplate.id;
        if (buttons_mask & id) 
        {
            btn = new Fl_Dialog_Button(_(buttonTemplate.label), Fl_Stock_Images::get_image(buttonTemplate.type), id);
            if (id == default_button) {
                btn->default_button(true);
                m_defaultButton = btn;
            }
            btn->callback((Fl_Callback1*)Fl_Dialog::buttons_callback, id);

            m_buttonList.append(btn);

            // Check the maximum button height
            int bw = 100;
            int bh = 25;
            btn->preferred_size(bw,bh);
            if (bh > maxh) maxh = bh;
        }
    }
    m_buttonPanel->end();

    // resize buttons
    /*
    int bx = (w()-layout_spacing()*2) + 3;
    for (i = 0; i < m_buttonList.size(); i++) 
    {
        Fl_Widget *btn = m_buttonList[i];
        fl_font(btn->label_font(), btn->label_size());
        int ww = int(fl_width(btn->label()));

        if (btn->image())
            ww += btn->image()->width() + 3;
        ww += btn->box()->dw() * 2 + 4;
        bx -= ww + 6;
        if (btn == m_defaultButton) {
            Fl_Widget *default_box = btn->parent();
            default_box->resize(bx-2,3,ww+4,maxh+4);
            btn->resize(2,2,ww,maxh);
        } else {
            btn->resize(bx,5,ww,maxh);
        }
    }
    */
    // resize button panel
    m_buttonPanel->h(maxh + m_buttonPanel->layout_spacing() * 2);

    relayout();
    Fl_Group::current(saved);
}

int Fl_Dialog::handle(int event) 
{
    int rc = inherited::handle(event);
    if (rc)
        return rc;
    if (event == FL_KEY) {
        switch(Fl::event_key()) {
            case FL_Escape:
                clear_value();
                m_modalResult = (int)Fl_Dialog::BTN_CANCEL;
                Fl::exit_modal();
                return 1;
            case FL_Enter:
                if (m_defaultButton) {
                    m_defaultButton->do_callback(FL_DIALOG_BTN);
                    return 1;
                }
        }
    }
    return 0;
}

int Fl_Dialog::show_modal() {
    load_data();
    exec(0,false);
    return m_modalResult;
}

Fl_Scroll *Fl_Dialog::new_scroll(const char *lbl,bool autoColor) 
{
    if(!m_tabs) return 0;
    if (!m_tabs->children()) {
        m_tabs->show_tabs(false);
    } else {
        m_tabs->show_tabs(true);
    }
    return m_tabs->new_scroll(lbl, autoColor);
}

Fl_Group *Fl_Dialog::new_group(const char *lbl,bool autoColor) 
{
    if(!m_tabs) return 0;
    if (!m_tabs->children()) {
        m_tabs->show_tabs(false);
    } else {
        m_tabs->show_tabs(true);
    }
    return m_tabs->new_group(lbl, autoColor);
}

bool Fl_Dialog::load_data(Fl_Data_Source *ds) 
{
    try {
        if (!ds) ds = m_dataSource;

        // Clean the widgets data before loading. 
        // Useful if we have incomplete information in datasource
        m_tabs->reset();

        return ds->load();
    }
    catch (Fl_Exception& e) {
        fl_alert("Can't open "+label()+".\n"+e.text());
        return false;
    }
}

bool Fl_Dialog::save_data(Fl_Data_Source *ds) {
    try {
        if (!ds) ds = m_dataSource;
        return ds->save();
    }
    catch (Fl_Exception& e) {
        fl_alert("Can't open "+label()+".\n"+e.text());
        return false;
    }
}

void Fl_Dialog::user_button(int button_id, Fl_String label, Fl_Pixmap *pixmap) {
    // Checking the button_id
    if (button_id <= BTN_HELP)
        fl_throw("Invalid button id");

    for (unsigned i = 0; i < m_buttonList.size(); i++) {
        Fl_Button *btn = (Fl_Button*)m_buttonList[i];
        if (button_id == btn->argument()) 
            fl_throw("Duplicated button id");
    }

    if (pixmap) {
        if (pixmap->width() > 20 || pixmap->height() > 20) {
            fl_throw("Button pixmap has size > 20");
        }
    }

    m_buttonPanel->begin();
    Fl_Dialog_Button *btn = new Fl_Dialog_Button(_(label.c_str()), pixmap, button_id);
    btn->callback((Fl_Callback1*)Fl_Dialog::buttons_callback,button_id);
    if (pixmap)
        btn->image(pixmap);
    m_buttonList.append(btn);
    m_buttonPanel->end();
}
