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

// essai.cxx

// Demonstration of a plugin that replaces the boxes such that a pixmap
// is used to draw everything.

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
#include <efltk/Fl_Pixmap.h>

#include "bg.xpm"
#include "bg2.xpm"
#include "bg3.xpm"

class Fl_Image_Box : public Fl_Boxtype_ {
public:
    Fl_Image *normal_img;
    Fl_Image *down_img;
    Fl_Image *highlight_img;
    Fl_Image *inactive_img;
    Fl_Boxtype_ *normal_b;
    Fl_Boxtype_ *value_b;
    Fl_Boxtype_ *highlight_b;
    Fl_Boxtype_ *inactive_b;
    Fl_Flags mask;

    Fl_Image_Box(Fl_Image *normal,
                 Fl_Image *value,
                 Fl_Image *highlight,
                 Fl_Image *inactive,
                 Fl_Boxtype normal_b,
                 Fl_Boxtype value_b=0,
                 Fl_Boxtype highlight_b=0,
                 Fl_Boxtype inactive_b=0,
                 Fl_Flags m=0);
    void draw(const int,int,int,int, Fl_Color, Fl_Flags) const;
};

void Fl_Image_Box::draw(int x, int y, int w, int h,
                        Fl_Color color, Fl_Flags flags) const
{
    Fl_Image *img = 0;
    Fl_Boxtype_ *box = 0;

    if (flags&FL_HIGHLIGHT) { img = highlight_img; box = highlight_b; }
    else if(flags&FL_VALUE) { img = down_img; box = value_b; }
    else if (flags&FL_INACTIVE) { img = inactive_img; box = inactive_b; }

    if(!img) img = normal_img;
    if(!box) box = normal_b;

    box->draw(x,y,w,h,color,(flags|FL_INVISIBLE)&(~mask));

    if(flags&FL_INVISIBLE) return;

    box->inset(x,y,w,h);
    fl_push_clip(x,y,w,h);
    img->draw(x,y,w,h,FL_ALIGN_TILED);
    fl_pop_clip();
}

Fl_Image_Box::Fl_Image_Box(Fl_Image *normal,
                           Fl_Image *value,
                           Fl_Image *highlight,
                           Fl_Image *inactive,
                           Fl_Boxtype normal_b,
                           Fl_Boxtype value_b,
                           Fl_Boxtype highlight_b,
                           Fl_Boxtype inactive_b,
                           Fl_Flags m) :
Fl_Boxtype_(0), mask(m)
{
    this->normal_b = (Fl_Boxtype_ *)normal_b;
    this->value_b = (Fl_Boxtype_ *)value_b;
    this->highlight_b = (Fl_Boxtype_ *)highlight_b;
    this->inactive_b = (Fl_Boxtype_ *)inactive_b;

    dx_ = normal_b->dx();
    dy_ = normal_b->dy();
    dw_ = normal_b->dw();
    dh_ = normal_b->dh();
    fills_rectangle_ = 1;//normal_b->fills_rectangle();

    normal_img = normal;
    down_img = value;
    highlight_img = highlight;
    inactive_img = inactive;
}

extern "C" bool fltk_theme()
{
    Fl_Renderer::system_init();

    Fl_Pixmap gray((const char **)bg_xpm);
    Fl_Pixmap blue((const char **)bg2_xpm);
    Fl_Pixmap light((const char **)bg3_xpm);

    gray.state_effect(false);
    gray.mask_type(MASK_NONE);
    gray.system_convert();

    blue.state_effect(false);
    blue.mask_type(MASK_NONE);
    blue.system_convert();

    light.state_effect(false);
    light.mask_type(MASK_NONE);
    light.system_convert();


    //  fl_background(0xD0D0E000); // it would be nice to figure out color from image
    Fl_Boxtype up   = new Fl_Image_Box(&gray, 0, &light, 0 , FL_THIN_UP_BOX, FL_THIN_DOWN_BOX, FL_THIN_UP_BOX);
    Fl_Boxtype up_blue   = new Fl_Image_Box(&blue, 0, &light, 0 , FL_THIN_UP_BOX, FL_THIN_DOWN_BOX, FL_THIN_UP_BOX);
    Fl_Boxtype down = new Fl_Image_Box(&gray, &blue, &light, 0 , FL_THIN_DOWN_BOX);

    Fl_Boxtype border = new Fl_Image_Box(&blue, &light, &light, 0, FL_BORDER_BOX);
    Fl_Boxtype border_hl = new Fl_Image_Box(&gray, &gray, &gray, 0, FL_FLAT_BOX, FL_THIN_DOWN_BOX, FL_THIN_UP_BOX, 0, FL_VALUE);

    Fl_Boxtype hl = new Fl_Image_Box(&blue, &blue, &light, &blue, FL_FLAT_BOX, 0, FL_THIN_UP_BOX);

    Fl_Boxtype flat = new Fl_Image_Box(&gray, &blue, &light, 0, FL_FLAT_BOX);
    Fl_Boxtype flat_blue = new Fl_Image_Box(&blue, 0, 0, 0, FL_FLAT_BOX);

    Fl_Boxtype menu_up   = new Fl_Image_Box(&gray, &blue, &light, 0 , FL_UP_BOX);

    Fl_Style::scrollbar_width = 14;
    Fl_Widget::default_style->box = down;
    Fl_Widget::default_style->button_box = up;
    Fl_Widget::default_style->highlight_color = FL_LIGHT2;

    Fl_Style* s;
    if ((s = Fl_Style::find("window"))) {
        s->box = flat_blue;
    }
    if ((s = Fl_Style::find("group"))) {
        s->box = FL_NO_BOX;
    }
    if ((s = Fl_Style::find("menu"))) {
        s->leading=2;
        s->selection_text_color = fl_color_average(FL_BLUE, FL_BLACK, 0.5);
        s->box = menu_up;
        s->button_box = border;
    }
    if ((s = Fl_Style::find("menu bar"))) {
        s->leading=2;
        s->selection_text_color = fl_color_average(FL_BLUE, FL_BLACK, 0.5);
        s->highlight_label_color = fl_color_average(FL_BLUE, FL_BLACK, 0.5);
        s->highlight_color = FL_GRAY;
        s->box = flat;
        s->button_box = border_hl;
    }
    if ((s = Fl_Style::find("tool bar"))) {
        s->highlight_color = FL_GRAY;
        s->box = up_blue;
    }
    if ((s = Fl_Style::find("button"))) {
        s->selection_text_color = FL_BLACK;
        s->selection_color = FL_BLACK;
        s->box = up;
    }
    if((s = Fl_Style::find("browser"))) {
        s->box = FL_THIN_DOWN_BOX;
    }
    /*if ((s = Fl_Style::find("tabs"))) {
        s->box = up;
    }*/
    if ((s = Fl_Style::find("pack"))) {
        s->box = flat_blue;
    }
    if ((s = Fl_Style::find("slider"))) {
        s->box = FL_NO_BOX;
        s->button_box = up;
        s->focus_box = FL_NO_BOX;
    }
    if ((s = Fl_Style::find("value slider"))) {
        s->box = FL_NO_BOX;
        s->button_box = up;
        s->focus_box = FL_NO_BOX;
    }
    if ((s = Fl_Style::find("listheader"))) {
        s->button_box = up;
    }
    if ((s = Fl_Style::find("highlight button"))) {
        s->box = hl;
    }
    if ((s = Fl_Style::find("workspace"))) {
        s->box = FL_THIN_DOWN_BOX;;
    }
    if ((s = Fl_Style::find("mdi viewport"))) {
        s->box = flat;
    }
    if ((s = Fl_Style::find("panel"))) {
        s->box = up;
    }
    /*
    if ((s = Fl_Style::find("light button"))) {
        s->box = box3;
    } */

    return true;
}

//
// End of "$Id$".
//
