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

void Fl_Date_Input::input_callback(Fl_Widget *di,void *) {
    Fl_Group *parent = (Fl_Group *) di->parent();
    if (parent)
        parent->do_callback(FL_DATA_CHANGE);
}

void Fl_Date_Input::button_callback(Fl_Widget *button,void *) {
    Fl_Date_Input *dateInput = (Fl_Date_Input *) button->parent();
    Fl_Popup_Calendar calendar(dateInput);
    calendar.date(dateInput->date_value());
    if (calendar.popup())
        dateInput->date_value(calendar.date());
}

static Fl_Pixmap buttonPixmap(calendar_xpm);

static void date_revert(Fl_Style* s)
{
    s->box = FL_DOWN_BOX;
    s->color = FL_WHITE;
}

static Fl_Named_Style date_style("Date_Input", date_revert, &Fl_Date_Input::default_style);
Fl_Named_Style* Fl_Date_Input::default_style = &::date_style;

Fl_Date_Input::Fl_Date_Input(int xx,int yy,int ww,int hh,const char *lbl)
: Fl_Group(xx,yy,ww,hh,lbl)
{
    style(date_style);
    layout_spacing(0);

    m_input = new Fl_Masked_Input(0,0,10,10);
    m_input->box(FL_FLAT_BOX);
    m_input->callback(Fl_Date_Input::input_callback);
    m_input->mask(Fl_Date_Time::dateInputFormat);
    m_input->layout_align(FL_ALIGN_CLIENT);

    m_button = new Fl_Button(0,0,10,10);
    m_button->box(FL_UP_BOX);
    m_button->callback(Fl_Date_Input::button_callback);
    m_button->image(&buttonPixmap);
    m_button->layout_align(FL_ALIGN_RIGHT);
    end();
}

int Fl_Date_Input::dateInputWidth(bool set_font) const {
    if (set_font)
        fl_font(text_font(), float(text_size()));
    return (int) fl_width(" 00/00/0000 ") + 2;
}

void Fl_Date_Input::preferred_size(int& w,int &h) const {
    w = dateInputWidth(true) + m_button->w() + box()->dw();
    h = int(fl_height()+fl_descent()) + box()->dh() + 2;
}

void Fl_Date_Input::draw()
{
    //Set style. NOTE:  this part MUST be in draw()
    m_input->copy_style(style());
    m_input->box(FL_FLAT_BOX);
    m_input->button_color(FL_BLACK);

    m_button->color(button_color());
    m_button->box(button_box());

    Fl_Group::draw();
}

void Fl_Date_Input::layout()
{
    int X=0, Y=0, W=w(), H=h();
    box()->inset(X,Y,W,H);
    W-=H;

    m_input->resize(X, Y, W, H);
    m_button->resize(W+box()->dx(), Y, H, H);

    Fl_Widget::layout();
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

Fl_Date_Time Fl_Date_Input::date_value() {
    return Fl_Date_Time(m_input->value());
}

//-------------------------------------------------------------------------------

static void datetime_revert(Fl_Style* s)
{
    s->box = FL_DOWN_BOX;
    s->color = FL_WHITE;
}

static Fl_Named_Style datetime_style("Date_Time_Input", datetime_revert, &Fl_Date_Input::default_style);
Fl_Named_Style* Fl_Date_Time_Input::default_style = &::datetime_style;

Fl_Date_Time_Input::Fl_Date_Time_Input(int xx,int yy,int ww,int hh,const char *lbl)
    : Fl_Date_Input(xx,yy,ww,hh,lbl)
{
    style(datetime_style);

    Fl_Group::current(0);

    m_timeInput = new Fl_Masked_Input(0,0,10,10,"");
    m_timeInput->callback(Fl_Date_Input::input_callback);
    m_timeInput->mask(Fl_Date_Time::timeInputFormat);
    m_timeInput->label_width(10);
    m_timeInput->align(FL_ALIGN_LEFT);
    m_timeInput->layout_align(FL_ALIGN_LEFT);

    // Insert to correct index, so TAB works
    insert(*m_timeInput, 1);

    end();
}

void Fl_Date_Time_Input::draw()
{
    // Set style
    m_timeInput->copy_style(style());
    m_timeInput->box(FL_FLAT_BOX);
    m_timeInput->button_color(FL_BLACK);

    Fl_Date_Input::draw();
}

void Fl_Date_Time_Input::layout()
{
    int X=0, Y=0, W=w(), H=h();
    box()->inset(X,Y,W,H);
    W-=H;

    m_button->resize(W+box()->dx(), Y, H, H);
    int iw = dateInputWidth(true);
    m_input->resize(X, Y, iw, H);
    m_timeInput->resize(iw+X+m_timeInput->label_width(), Y, W-iw-m_timeInput->label_width(), H);

    Fl_Widget::layout();
}

int Fl_Date_Time_Input::timeInputWidth(bool set_font) const {
    if (set_font)
        fl_font(text_font(), float(text_size()));
    return (int) fl_width(" 00:00 ") + 2;
}

void Fl_Date_Time_Input::preferred_size(int& w,int &h) const {
    w = dateInputWidth(true) + timeInputWidth(false) + m_button->w() + box()->dw() + m_timeInput->label_width();
    h = int(fl_height()+fl_descent()) + box()->dh() + 2;
}

void Fl_Date_Time_Input::value(const char *v) {
    m_input->value(v);
}

const char *Fl_Date_Time_Input::value() {
    return m_input->value();
}

void Fl_Date_Time_Input::date_value(Fl_Date_Time dt) {
    m_input->value(dt.date_string().c_str());
}

Fl_Date_Time Fl_Date_Time_Input::date_value() {
    return Fl_Date_Time(m_input->value());
}
