/***************************************************************************
                          Fl_Date_Time_Input.cpp  -  description
                             -------------------
    begin                : Mon Nov 11 2002
    copyright            : (C) 2002 by Alexey Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

// LGPL !!!

#include <efltk/Fl_Date_Time_Input.h>
#include <efltk/Fl_Masked_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Pixmap.h>
#include <efltk/Fl_Calendar.h>
#include <efltk/fl_draw.h>

static const char * calendar_xpm[] = {
    "15 15 7 1",
    "   c None",
    ".  c #000000",
    "+  c #FFFFFF",
    "@  c #C0C0C0",
    "#  c #008080",
    "$  c #0000FF",
    "%  c #800000",
    " ..........    ",
    " .$$$$$$$$.    ",
    " ..............",
    " .+@+.$$$$$$$$.",
    " .@%%..........",
    " .+%+.+@+@+@+@.",
    " .@%%.@%%%%%@+.",
    " .+%+.+@+@%%+@.",
    " .@%%.@+@%%+@+.",
    " .+@+.+@%%+@+@.",
    " .@$$.@+%%@+@+.",
    " .+@+.+@+@+@+@.",
    " .....@$$$$$$$.",
    "     .+@+@+@+@.",
    "     .........."};

class Fl_Calendar_Button : public Fl_Button {
    Fl_Input *m_input;
public:
    Fl_Calendar_Button(Fl_Input *input=NULL) : Fl_Button(0,0,18,18) {m_input = input;}
    virtual void preferred_size(int& w,int& h) const { 
        w = 15+box()->dw(); 
        fl_font(parent()->text_font(),parent()->text_size());
        h = int(fl_height()+fl_descent()) + 2;
    }
    int handle(int event) { // button should never take focus
        if (event == FL_FOCUS)
            return false;
        return Fl_Button::handle(event);
    }

    Fl_Input *input() { return m_input; }
    void input(Fl_Input *inp) { m_input = inp; }
};

class Fl_Calendar_Input : public Fl_Masked_Input {
public:
    Fl_Calendar_Input() : Fl_Masked_Input(0,0,10,10) {}

    virtual void preferred_size(int& w,int& h) const {
        w = preferred_width(true);
        h = int(fl_height()+fl_descent()) + 2;
    }

    int preferred_width(bool set_font) const {
        if (set_font)
            fl_font(text_font(), float(text_size()));
        return (int) fl_width("00/00/0000W");
    }
};

class Fl_Calendar_Time_Input : public Fl_Masked_Input {
public:
    Fl_Calendar_Time_Input() : Fl_Masked_Input(0,0,10,10) {}
    virtual void preferred_size(int& w,int& h) const {
        w = preferred_width(true);
        h = int(fl_height()+fl_descent()) + 2;
    }

    int preferred_width(bool set_font) const {
        if (set_font)
            fl_font(text_font(), float(text_size()));
        if (Fl_Date_Time::time24Mode)
            return (int) fl_width("00:00W");
        else return (int) fl_width("00:00AMW");
    }
};

void Fl_Date_Input::input_callback(Fl_Widget *di,void *) {
    di->parent()->do_callback();
}

void Fl_Date_Input::button_callback(Fl_Widget *button,void *) {
    Fl_Date_Input *dateInput = (Fl_Date_Input *) button->parent();
    Fl_Popup_Calendar calendar(dateInput);
    calendar.date(dateInput->date_value());
    if (calendar.popup()) {
        Fl_Calendar_Button *btn = (Fl_Calendar_Button *)button;
        Fl_Input *inp = btn->input();
        if (!inp) return;
        Fl_Date_Time dt = calendar.date();
        if (inp->value() != dt.date_string()) {
            inp->value(dt.date_string());
            dateInput->do_callback();
        }
    }
}

static Fl_Pixmap buttonPixmap(calendar_xpm);

static void date_revert(Fl_Style* s)
{
    s->color = FL_WHITE;
}

static Fl_Named_Style date_style("Date_Input", date_revert, &Fl_Date_Input::default_style);
Fl_Named_Style* Fl_Date_Input::default_style = &::date_style;

// ctor initializer - used in both ctors
void Fl_Date_Input::ctor_init() {
    style(date_style);
    layout_spacing(0);
    align(FL_ALIGN_LEFT);

    m_input = new Fl_Calendar_Input();
    m_input->callback(Fl_Date_Input::input_callback);
    m_input->mask(Fl_Date_Time::dateInputFormat);
    m_input->layout_align(FL_ALIGN_LEFT);

    m_button = new Fl_Calendar_Button(m_input);    
    m_button->callback(Fl_Date_Input::button_callback);
    m_button->image(&buttonPixmap);
    m_button->layout_align(FL_ALIGN_RIGHT);
    end();
}

// Traditional ctor
Fl_Date_Input::Fl_Date_Input(int xx,int yy,int ww,int hh,const char *lbl)
: Fl_Group(xx,yy,ww,hh,lbl)
{
    ctor_init();
}

// New style ctor
Fl_Date_Input::Fl_Date_Input(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Group(l,layout_size,layout_al,label_w)
{
    ctor_init();
}

void Fl_Date_Input::preferred_size(int& w,int &h) const {
    m_input->preferred_size(w,h);
    h += box()->dh();
    w += m_button->w() + box()->dw();
}

// Data source support
// loading data from DS
bool Fl_Date_Input::load_data(Fl_Data_Source *ds)
{
    if(field_name().empty())
        return false;

    Fl_Variant fld_value;
    if (ds->read_field(field_name().c_str(), fld_value)) {
        date_value(fld_value.as_date());
        return true;
    }
    return false;
}

// saving data to DS
bool Fl_Date_Input::save_data(Fl_Data_Source *ds) 
{
    if(field_name().empty())
        return false;

    Fl_Variant  fld_value;
    fld_value.set_date(date_value());
    return ds->write_field(field_name().c_str(), fld_value);
}

void Fl_Date_Input::draw()
{
    //Set style. NOTE:  this part MUST be in draw()
    m_input->copy_style(style());
    m_input->box(FL_NO_BOX); // Draw bg using parent parent()->draw_group_box() 
    m_input->button_color(FL_BLACK); //Black cursor

    m_button->color(button_color());
    m_button->box(button_box());

    Fl_Group::draw();
}

void Fl_Date_Input::value(const char *v) {
    m_input->value(v);
}

const char *Fl_Date_Input::value() {
    return m_input->value();
}

void Fl_Date_Input::date_value(Fl_Date_Time dt) {
    m_input->value(dt.date_string().c_str());
}

Fl_Date_Time Fl_Date_Input::date_value() const {
    return Fl_Date_Time(m_input->value());
}

//-------------------------------------------------------------------------------

static void datetime_revert(Fl_Style* s)
{
    s->color = FL_WHITE;
}

static Fl_Named_Style datetime_style("Date_Time_Input", datetime_revert, &Fl_Date_Input::default_style);
Fl_Named_Style* Fl_Date_Time_Input::default_style = &::datetime_style;

// ctor initializer - used in both ctors
void Fl_Date_Time_Input::ctor_init() {
    style(datetime_style);
    begin();
    m_timeInput = new Fl_Calendar_Time_Input();
    m_timeInput->callback(Fl_Date_Input::input_callback);
    m_timeInput->mask(Fl_Date_Time::timeInputFormat);
    m_timeInput->layout_align(FL_ALIGN_RIGHT);
    end();
}

// Traditional ctor
Fl_Date_Time_Input::Fl_Date_Time_Input(int xx,int yy,int ww,int hh,const char *lbl)
: Fl_Date_Input(xx,yy,ww,hh,lbl)
{
    ctor_init();
}

// New style ctor
Fl_Date_Time_Input::Fl_Date_Time_Input(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Date_Input(l,layout_size,layout_al,label_w)
{
    ctor_init();
}

// Data source support
// loading data from DS
bool Fl_Date_Time_Input::load_data(Fl_Data_Source *ds)
{
    if(field_name().empty())
        return false;

    Fl_Variant fld_value;
    if (ds->read_field(field_name().c_str(), fld_value)) {
        date_time_value(fld_value.as_datetime());
        return true;
    }
    return false;
}

// saving data to DS
bool Fl_Date_Time_Input::save_data(Fl_Data_Source *ds) 
{
    if(field_name().empty())
        return false;

    Fl_Variant  fld_value;
    fld_value.set_datetime(date_time_value());
    return ds->write_field(field_name().c_str(), fld_value);
}

void Fl_Date_Time_Input::draw()
{
    // Set style
    m_timeInput->copy_style(style());
    m_timeInput->box(FL_NO_BOX); // Draw bg using parent parent()->draw_group_box() 
    m_timeInput->button_color(FL_BLACK); //Black cursor

    Fl_Date_Input::draw();
}

void Fl_Date_Time_Input::preferred_size(int& w,int &h) const {
    m_input->preferred_size(w,h);
    h += box()->dh();
    w += m_button->w() + box()->dw() + ((Fl_Calendar_Time_Input *)m_timeInput)->preferred_width(false);
}

void Fl_Date_Time_Input::value(const char *v) {
    Fl_Date_Time dt(v);
    date_value(dt);
}

const char *Fl_Date_Time_Input::value() {
    sprintf(m_buffer,"%s %s",m_input->value(),m_timeInput->value());
    return m_buffer;
}

void Fl_Date_Time_Input::date_time_value(Fl_Date_Time dt) {
    m_input->value(dt.date_string().c_str());
    m_timeInput->value(dt.time_string());
}

Fl_Date_Time Fl_Date_Time_Input::date_time_value() const {
    double d = Fl_Date_Time(m_input->value());
    double t = Fl_Date_Time(m_timeInput->value());
    return d + t;
}

//-----------------------------------------------------------------------------------------------

// ctor initializer - used in both ctors
void Fl_Date_Interval_Input::ctor_init() {
    style(datetime_style);

    m_button->layout_align(FL_ALIGN_LEFT);

    begin();
    m_button2 = new Fl_Calendar_Button();
    m_button2->box(FL_UP_BOX);
    m_button2->callback(Fl_Date_Input::button_callback);
    m_button2->image(&buttonPixmap);
    m_button2->layout_align(FL_ALIGN_RIGHT);

    m_input2 = new Fl_Calendar_Input();
    m_input2->box(FL_FLAT_BOX);
    m_input2->callback(Fl_Date_Input::input_callback);
    m_input2->mask(Fl_Date_Time::dateInputFormat);
    m_input2->layout_align(FL_ALIGN_RIGHT);

    end();

    m_button2->input(m_input2);
}

// Traditional ctor
Fl_Date_Interval_Input::Fl_Date_Interval_Input(int xx,int yy,int ww,int hh,const char *lbl)
: Fl_Date_Input(xx,yy,ww,hh,lbl)
{
    ctor_init();
}

// New style ctor
Fl_Date_Interval_Input::Fl_Date_Interval_Input(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Date_Input(l,layout_size,layout_al,label_w)
{
    ctor_init();
}

// Data source support
// loading data from DS
bool Fl_Date_Interval_Input::load_data(Fl_Data_Source *ds)
{
    Fl_Variant fld_value;

    if (!field_name().empty()) {
        if (ds->read_field(field_name().c_str(), fld_value))
            date_value(fld_value.as_datetime());
        else return false;
    }

    if (!field_name2().empty()) {
        if (ds->read_field(field_name2().c_str(), fld_value))
            date_value2(fld_value.as_datetime());
        else return false;
    }

    return true;
}

// saving data to DS
bool Fl_Date_Interval_Input::save_data(Fl_Data_Source *ds)
{
    Fl_Variant fld_value;

    if (!field_name().empty()) {
        Fl_Variant  fld_value;
        fld_value.set_datetime(date_value());
        if (!ds->write_field(field_name().c_str(), fld_value))
            return false;
    }

    if (!field_name2().empty()) {
        Fl_Variant  fld_value;
        fld_value.set_datetime(date_value2());
        if (!ds->write_field(field_name2().c_str(), fld_value))
            return false;
    }
    return true;
}

void Fl_Date_Interval_Input::draw()
{
    // Set style
    m_input2->copy_style(style());
    m_input2->box(FL_NO_BOX); // Draw bg using parent parent()->draw_group_box() 
    m_input2->button_color(FL_BLACK); // Black cursor

    Fl_Date_Input::draw();
}

void Fl_Date_Interval_Input::preferred_size(int& w,int &h) const {
    m_input->preferred_size(w,h);
    h += box()->dh();
    w += m_button->w();
    w = w + w + box()->dw()*2;
}

void Fl_Date_Interval_Input::value2(const char *v) {
    m_input2->value(v);
}

const char *Fl_Date_Interval_Input::value2() {
    return m_input2->value();
}

void Fl_Date_Interval_Input::date_value2(Fl_Date_Time dt) {
    m_input2->value(dt.date_string());
}

Fl_Date_Time Fl_Date_Interval_Input::date_value2() const {
    return Fl_Date_Time(m_input2->value());
}

//------------------------------------------------------------------------------------------------
