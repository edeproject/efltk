//
// "$Id$"
//
// Menu button widget for the Fast Light Tool Kit (FLTK).
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
#include <efltk/Fl_Menu_Button.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Item.h>

extern Fl_Widget* fl_did_clipping;

void Fl_Menu_Button::draw()
{
    if (type()&7)                // draw nothing for the popup types
    {
        fl_did_clipping = this;
        return;
    }
    Fl_Boxtype box = this->box();
    // We need to erase the focus rectangle on FL_DAMAGE_HIGHTLIGHT for
    // FL_NO_BOX buttons such as checkmarks:
    if (damage()&FL_DAMAGE_EXPOSE && !box->fills_rectangle()
        || box == FL_NO_BOX && damage()&FL_DAMAGE_HIGHLIGHT && !focused())
    {
        fl_push_clip(0, 0, this->w(), this->h());
        parent()->draw_group_box();
        fl_pop_clip();
    }
    Fl_Flags flags;
    Fl_Color color;
    if (!active_r())
    {
        flags = FL_INACTIVE;
        color = this->color();
    }
    else if (belowmouse())
    {
        flags = FL_HIGHLIGHT;
        color = highlight_color();
        if (!color) color = this->color();
    }
    else
    {
        flags = 0;
        color = this->color();
    }
    box->draw(0, 0, this->w(), this->h(), color, flags);
    int x,y,w,h;
    x = y = 0; w = this->w(); h = this->h(); box->inset(x,y,w,h);
    draw_inside_label(x,y,w,h,flags);
    if (focused())
    {
        focus_box()->draw(x+1, y+1, w-2, h-2, text_color(), FL_INVISIBLE);
    }
    // draw the little mark at the right:
    int w1 = text_size();
    draw_glyph(FL_GLYPH_DOWN, x+w-w1, y, w1, h, flags);
}

int Fl_Menu_Button::popup(int X, int Y, int W, int H)
{
    return Fl_Menu_::popup(X,Y,W,H);
}

int Fl_Menu_Button::popup()
{
    // back compatibility hack
    if (box() == FL_NO_BOX) type(POPUP3);
    if (type()&7)
    {
        /*if (label())
        {
            Fl_Item title(label());
            return Fl_Menu_::popup(Fl::event_x(), Fl::event_y(), 0,0);
        }
        else*/
        {
            if(anim_flags_==TOP_TO_BOTTOM) anim_flags_ = TOP_TO_BOTTOM|LEFT_TO_RIGHT;
            return popup(Fl::event_x(), Fl::event_y());
        }
    }
    else
    {
        return popup(0, 0, w(), h());
    }
}


int Fl_Menu_Button::handle(int e)
{
    switch (e)
    {

        case FL_FOCUS:
        case FL_UNFOCUS:
            if (type()&7) return 0;
            redraw(FL_DAMAGE_HIGHLIGHT);
            return 1;

        case FL_ENTER:
        case FL_LEAVE:
            if (type()&7) return 0;
            if (highlight_color() && takesevents()) redraw(FL_DAMAGE_HIGHLIGHT);
        case FL_MOVE:
            return 1;

        case FL_PUSH:
            // If you uncomment this line (or make a subclass that does this) then
            // a mouse click picks the current item, and the menu goes away.  The
            // user must drag the mouse to select a different item.  Depending on
            // the size and usage of the menu, this may be more user-friendly:
            // Fl::event_is_click(0);
            if (type()&7)
            {
                if (!(type() & (1 << (Fl::event_button()-1)))) return 0;
            }
            else
            {
                if (click_to_focus()) take_focus();
            }
            EXECUTE:
            //if (!(type()&7)) value(-1); // make it pull down below the button...
            popup();
            return 1;

        case FL_SHORTCUT:
            if (test_shortcut()) goto EXECUTE;
            return handle_shortcut();

        case FL_KEY:
            if (Fl::event_key() == FL_Enter || Fl::event_key() == ' ') goto EXECUTE;
            return 0;

        default:
            return 0;
    }
}


static void revert(Fl_Style* s)
{
    s->color = FL_GRAY;
    s->box = FL_UP_BOX;
}


static Fl_Named_Style style("Menu_Button", revert, &Fl_Menu_Button::default_style);
Fl_Named_Style* Fl_Menu_Button::default_style = &::style;

Fl_Menu_Button::Fl_Menu_Button(int X,int Y,int W,int H,const char *l)
: Fl_Menu_(X,Y,W,H,l)
{
    style(default_style);
    align(FL_ALIGN_CENTER);
    //set_click_to_focus();

    anim_flags_ = TOP_TO_BOTTOM;
}


//
// End of "$Id$".
//
