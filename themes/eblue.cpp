//
// "$Id$"
//
// Theme plugin file for FLTK
//
// Copyright 1999 Bill Spitzak and others.
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

// eblue.cpp

#include <efltk/Fl.h>
#include <efltk/Fl_Widget.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Scrollbar.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Output.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Style.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <efltk/Fl_Boxtype.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Image_Filter.h>
#include <efltk/Fl_Renderer.h>

class Fl_Shaded_Box : public Fl_Boxtype_ {
public:
    bool vertical;
    Fl_Boxtype frame;

    Fl_Shaded_Box(Fl_Boxtype fr, bool vert) {
        frame = fr;
        vertical = vert;
        dx_ = fr->dx();
        dy_ = fr->dy();
        dw_ = fr->dw();
        dh_ = fr->dh();
    }
    void draw(const int,int,int,int, Fl_Color, Fl_Flags) const;
};

void Fl_Shaded_Box::draw(int x, int y, int w, int h,
                        Fl_Color color, Fl_Flags flags) const
{
    frame->draw(x,y,w,h,color, FL_INVISIBLE|flags);

    if(flags&FL_INVISIBLE) return;

    Fl_Boxtype box;
    if((frame==FL_HIGHLIGHT_BOX && flags&FL_HIGHLIGHT) //hack :)
       || frame!=FL_HIGHLIGHT_BOX)
        frame->inset(x,y,w,h);
    fl_push_clip(x,y,w,h);
    if(vertical) box = FL_VERT_SHADE_FLAT_BOX;
    else box = FL_HOR_SHADE_FLAT_BOX;
    box->draw(x,y,w,h,color,flags);
    fl_pop_clip();
}

extern "C" bool fltk_theme()
{
    Fl_Boxtype vertup   = new Fl_Shaded_Box(FL_THIN_UP_BOX, true);
    Fl_Boxtype vertdown = new Fl_Shaded_Box(FL_THIN_DOWN_BOX, true);
    Fl_Boxtype vertfr   = new Fl_Shaded_Box(FL_BORDER_BOX, true);
    Fl_Boxtype vertflat = new Fl_Shaded_Box(FL_FLAT_BOX, true);
    Fl_Boxtype verthl = new Fl_Shaded_Box(FL_HIGHLIGHT_BOX, true);

    Fl_Boxtype horup   = new Fl_Shaded_Box(FL_THIN_UP_BOX, false);
    Fl_Boxtype hordown = new Fl_Shaded_Box(FL_THIN_DOWN_BOX, false);
    //Fl_Boxtype horfr   = new Fl_Shaded_Box(FL_BORDER_BOX, false);
    Fl_Boxtype horflat = new Fl_Shaded_Box(FL_FLAT_BOX, false);

    Fl_Color bc = fl_rgb(180,210,230);

    Fl_Style::scrollbar_width = 15;
    Fl_Widget::default_style->box = vertdown;
    //Fl_Widget::default_style->button_box = vertup;
    Fl_Widget::default_style->color = bc;
    //Fl_Widget::default_style->highlight_color = FL_LIGHT2;

    Fl_Style* s;
    if ((s = Fl_Style::find("window"))) {
        s->box = FL_FLAT_BOX;//vertflat;
        s->color = fl_rgb(180,200,215);
    }
    if ((s = Fl_Style::find("group"))) {
        s->box = FL_NO_BOX;
        s->color = bc;
    }
    if ((s = Fl_Style::find("menu"))) {
        s->selection_text_color = fl_darker(FL_BLUE);
        s->selection_color = bc;
        s->box = vertfr;
        s->color = fl_lighter(FL_BLUE);
        s->button_box = vertfr;
    }
    if ((s = Fl_Style::find("menu bar"))) {
        s->color = bc;
        s->highlight_label_color = fl_darker(FL_BLUE);
        s->selection_text_color = fl_darker(FL_BLUE);
        s->highlight_color = FL_GRAY;
        s->box = vertflat;
        s->button_box = FL_NO_BOX;
    }
    if ((s = Fl_Style::find("choice"))) {
        s->box = FL_THIN_DOWN_BOX;
        s->button_color = bc;
    }
    if ((s = Fl_Style::find("button"))) {
        s->selection_color = fl_darker(bc);
        s->color = bc;
        s->box = vertup;
    }
    if ((s = Fl_Style::find("scrollbar"))) {
        s->color = bc;
        s->button_color = bc;
        s->button_box = vertup;
    }
    if ((s = Fl_Style::find("menu button"))) {
        s->color = bc;
        s->box = vertup;
    }
    if((s = Fl_Style::find("browser"))) {
        s->box = FL_THIN_DOWN_BOX;
        s->color = fl_rgb(235,245,255);
    }
    if((s = Fl_Style::find("input browser"))) {
        s->box = FL_THIN_DOWN_BOX;
        s->button_color = bc;
        s->color = fl_rgb(235,245,255);
    }
    if((s = Fl_Style::find("input"))) {
        s->box = hordown;
    }
    if ((s = Fl_Style::find("listview header"))) {
        s->button_box = vertup;
        s->button_color = bc;
    }
    if ((s = Fl_Style::find("listview"))) {
        s->button_color = fl_lighter(bc);
    }
    if ((s = Fl_Style::find("slider"))) {
        s->box = hordown;
        s->button_box = horup;
        s->color = bc;
        s->button_color = fl_darker(bc);
        s->focus_box = FL_NO_BOX;
    }
    if ((s = Fl_Style::find("value slider"))) {
        s->box = hordown;
        s->button_box = horup;
        s->color = bc;
        s->button_color = fl_darker(bc);
        s->focus_box = FL_NO_BOX;
    }
    if ((s = Fl_Style::find("highlight button"))) {
        s->box = verthl;
        s->color = bc;
        s->highlight_color = fl_lighter(bc);
    }
    if ((s = Fl_Style::find("tool bar"))) {
        //s->highlight_color = FL_GRAY;
        s->box = vertup;
    }
    if ((s = Fl_Style::find("tabs"))) {
        s->box = vertup;
    }
    if ((s = Fl_Style::find("pack"))) {
        s->box = horflat;
    }
    if ((s = Fl_Style::find("workspace"))) {
        s->box = FL_THIN_DOWN_BOX;;
    }
    if ((s = Fl_Style::find("mdi viewport"))) {
        s->box = FL_FLAT_BOX;//vertflat;
        s->color = fl_rgb(180,200,215);
    }
    if ((s = Fl_Style::find("panel"))) {
        s->box = horup;
        s->color = bc;
    }
    if ((s = Fl_Style::find("light button"))) {
        s->selection_color = fl_lighter(FL_BLUE);
    }

    return true;
}

//
// End of "$Id$".
//
