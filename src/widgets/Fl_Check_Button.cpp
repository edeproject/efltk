//
// "$Id$"
//
// Check button widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#include <efltk/Fl.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Group.h>

static void default_glyph(const Fl_Widget* widget, int glyph,
    int x,int y,int w,int h, Fl_Flags flags)
{
    Fl_Boxtype box = widget->button_box();
    box->draw(x, y, w, h, widget->button_color(), flags);
    box->inset(x, y, w, h);
    if (flags & FL_VALUE)
    {
        Fl_Color color = (box == FL_NO_BOX && (flags&FL_SELECTED)) ?
            widget->selection_text_color() : widget->text_color();
        fl_color(fl_inactive(color, flags));
        x += 1;
        w = h - 2;
        int d1 = w/3;
        int d2 = w-d1;
        y += (h+d2)/2-d1-2;
        for (int n = 0; n < 3; n++, y++)
        {
            fl_line(x, y, x+d1, y+d1);
            fl_line(x+d1, y+d1, x+w-1, y+d1-d2+1);
        }
    }
}

void Fl_Check_Button::preferred_size(int& w, int& h) const
{   
    Fl_Button::preferred_size(w,h);
    w += text_size()+8;
    h += 2;
}

void Fl_Check_Button::draw()
{
    Fl_Button::draw(0, text_size()+2);
}


static void revert(Fl_Style* s)
{
    s->box = FL_NO_BOX;
    s->color = FL_GRAY;
    s->button_box = FL_DOWN_BOX;
    s->button_color = FL_WHITE;
    s->glyph = ::default_glyph;
}


static Fl_Named_Style style("Check_Button", revert, &Fl_Check_Button::default_style);
Fl_Named_Style* Fl_Check_Button::default_style = &::style;

// Traditional ctor
Fl_Check_Button::Fl_Check_Button(int x, int y, int w, int h, const char *l)
: Fl_Button(x, y, w, h, l)
{
    style(default_style);
    type(TOGGLE);
    set_flag(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
}

// New style ctor
Fl_Check_Button::Fl_Check_Button(const char* l,int layout_size,Fl_Align layout_al)
: Fl_Button(l,layout_size,layout_al)
{
    style(default_style);
    type(TOGGLE);
    set_flag(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
}

// Data source support
// loading data from DS
bool Fl_Check_Button::load_data(Fl_Data_Source *ds)
{
    if (field_name().empty())
        return false;

    Fl_Variant fld_value;
    if (ds->read_field(field_name().c_str(), fld_value)) {
        Fl_String v = fld_value.as_string();
        if (strchr("YyTt1",v[0]))
            value(1);
        else value(0);
        return true;
    }
    return false;
}

// saving data to DS
bool Fl_Check_Button::save_data(Fl_Data_Source *ds)
{
    if(field_name().empty())
        return false;

    Fl_Variant  fld_value;
    if (value())
        fld_value.set_string("Y");
    else fld_value.set_string("N");
    return ds->write_field(field_name().c_str(), fld_value);
}

// Dialog support
void Fl_Check_Button::reset() { 
    value(0); 
}
