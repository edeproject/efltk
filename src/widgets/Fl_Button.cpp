//
// "$Id$"
//
// Button widget for the Fast Light Tool Kit (FLTK).
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
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Group.h>

bool Fl_Button::set()
{
    clear_changed();
    if (!value()) {set_value(); redraw(); return true;}
    return false;
}

bool Fl_Button::clear()
{
    clear_changed();
    if (value()) {clear_value(); redraw(); return true;}
    return false;
}

bool Fl_Button::value(bool v)
{
    return v ? set() : clear();
}

void Fl_Button::setonly()        // set this radio button on, turn others off
{
    set();
    for (int i = parent()->children(); i--;)
    {
        Fl_Widget* o = parent()->child(i);
        if (o != this && o->type() == RADIO)
            ((Fl_Button*)o)->clear();
    }
}

static Fl_Button* held_down;

int Fl_Button::handle(int event)
{
    static bool oldval;
    static bool already_pushed=false;
    bool newval;

    switch (event)
    {
        case FL_LEAVE:
        case FL_ENTER:
            if (highlight_color() && takesevents())
                redraw(FL_DAMAGE_HIGHLIGHT);

        case FL_MOVE:
            return 1;

        case FL_PUSH:
            if(!already_pushed) oldval = value();
            already_pushed = true;

        case FL_DRAG:
            if (Fl::event_inside(0,0,w(),h()))
            {
                held_down = this;
                if (type() == RADIO) newval = true;
                else newval = !oldval;
            }
            else
            {
                held_down = 0;
                newval = oldval;
            }
            if (value(newval) && when()&FL_WHEN_CHANGED)
                do_callback();
            return 1;

        case FL_RELEASE:
            redraw(FL_DAMAGE_VALUE);
            held_down = 0;
            already_pushed = false;
            if (value() == oldval) return 1;
            if (type() == RADIO)
                setonly();
            else if (type())     // TOGGLE
            ;                // leave it as set
            else
            {
                value(oldval);
                if (when() & FL_WHEN_CHANGED)
                    do_callback();
            }
            if (when() & FL_WHEN_RELEASE)
                do_callback();
            else
                set_changed();
            return 1;

        case FL_UNFOCUS:
        case FL_FOCUS:
            redraw(FL_DAMAGE_HIGHLIGHT);
        // grab initial focus if we are an Fl_Return_Button:
            return shortcut()=='\r' ? 2 : 1;

        case FL_SHORTCUT:
        case FL_KEY:
            if(event==FL_SHORTCUT && !test_shortcut())
                return 0;

            if(event==FL_KEY && Fl::event_key() != ' ' && Fl::event_key() != FL_Enter )
                return 0;

            if (type() == RADIO/* && !value()*/)
            {
                setonly();
                if (when() & FL_WHEN_CHANGED) do_callback();
            }                    // TOGGLE
            else if (type())
            {
                value(!value());
                if (when() & FL_WHEN_CHANGED) do_callback();
            }
            if (when() & FL_WHEN_RELEASE)
                do_callback();
            else
                set_changed();
            return 1;

        default:
            break;
    }
    return Fl_Widget::handle(event);
}

////////////////////////////////////////////////////////////////

#include <efltk/Fl_Image.h>
#include <efltk/fl_draw.h>

extern Fl_Widget* fl_did_clipping;

// Draw button-like widgets with an optional glyph. The glyph is given
// a size (negative to put it on the right)
void Fl_Button::draw(int glyph, int glyph_width) const
{
    // Figure out the colors to use. The flags are used by the label and
    // glyph functions to figure out their colors:
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
    Fl_Flags glyph_flags = flags;
    if (glyph_width)
    {
        if (this == held_down) flags.set(FL_VALUE);
        if (value()) glyph_flags.set(FL_VALUE);
    }
    else if (value())
    {
        flags.set(FL_VALUE);
        // Use the pushed-in color if the user has explicitly set it
        // on this widget:
        if (style()->selection_color)
        {
            color = style()->selection_color;
            flags.set(FL_SELECTED); // this makes label use selected_text_color()
        }
    }

    bool draw_label = true;
    int x = 0, y = 0, w = this->w(), h = this->h();

    if (box() == FL_NO_BOX)
    {
        // If the box is FL_NO_BOX we need to avoid drawing the label so
        // that it does not blink and does not draw multiple times (which
        // will make it look bold if antialiasing is on).
        /* if (!label()) {
          // don't do anything if no label, so buttons that are an image
          // only will redraw correctly and with minimum blinking.
                                       } else */
        if ((damage()&FL_DAMAGE_EXPOSE) ||
            (damage()&FL_DAMAGE_HIGHLIGHT) && !focused())
        {
            // erase the background behind where the label will draw:
            fl_push_clip(0, 0, w, h);
            parent()->draw_group_box();
            fl_pop_clip();
        }
        else
        {
            // Don't draw the label unnecessarily:
            draw_label = false;
        }
    }
    else
    {
        bool drawed = false;
        if(image() && !image()->get_mask()) {
            if((align()&FL_ALIGN_TILED || align()&FL_ALIGN_SCALE) &&
                ( !(align()&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT|FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) || (align()&FL_ALIGN_INSIDE) )
                ) {
                // We can draw only frame, if drawing image tiled or scale
                // And no mask defined to image...
                draw_frame();
                drawed = true;
            }
        }

        if(!drawed) {
            if (damage()&FL_DAMAGE_EXPOSE && !box()->fills_rectangle()) {
                fl_push_clip(0, 0, w, h);
                parent()->draw_group_box();
                fl_pop_clip();
            }
            // Draw the box:
            box()->draw(0, 0, w, h, color, flags);
        }

        box()->inset(x,y,w,h);
    }

    if (glyph_width < 0) {
        int g = -glyph_width;
        draw_glyph(glyph, x+w-g-3, y+((h-g)>>1), g, g, glyph_flags);
        if (draw_label) draw_inside_label(x, y, w-g-3, h, flags);
    }
    else if (glyph_width > 0)
    {
        int g = glyph_width;
        draw_glyph(glyph, x+3, y+((h-g)>>1), g, g, glyph_flags);
        if (draw_label) draw_inside_label(x+g+3, y, w-g-3, h, flags);
    }
    else
    {
        if (draw_label) draw_inside_label(x, y, w, h, flags);
    }

    if (focused())
    {
        focus_box()->draw(x+1, y+1, w-2, h-2,
            flags&FL_SELECTED ? selection_text_color():label_color(),
            FL_INVISIBLE);
    }
}


void Fl_Button::draw()
{
    if (type() == HIDDEN)
    {
        fl_did_clipping = this;
        return;
    }
    draw(0,0);
}

void Fl_Button::preferred_size(int& w, int& h) const
{
    measure_label(w, h);

    if (image()) {
        w += image()->width();
        if (h < image()->height())
            h = image()->height();
        w += 4;
    }

    w += box()->dw() + 4;
    h += box()->dh() + 4;
}

////////////////////////////////////////////////////////////////

static void revert(Fl_Style* s)
{
    s->color = FL_GRAY;
    s->box = FL_UP_BOX;
}


static Fl_Named_Style style("Button", revert, &Fl_Button::default_style);
Fl_Named_Style* Fl_Button::default_style = &::style;

// Traditional ctor
Fl_Button::Fl_Button(int x,int y,int w,int h, const char *l) 
: Fl_Widget(x,y,w,h,l)
{
    style(default_style);
}

// New style ctor
Fl_Button::Fl_Button(const char* l,int layout_size,Fl_Align layout_al)
: Fl_Widget(l,layout_size,layout_al,-1)
{
    style(default_style);
}

//
// End of "$Id$".
//
