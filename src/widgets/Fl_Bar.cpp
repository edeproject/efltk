//
// "$Id$"
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

// Based on Fl_Frametab V2 contributed by Curtis Edwards (curt1@trilec.com)

#include <efltk/Fl.h>
#include <efltk/Fl_Bar.h>

static void revert(Fl_Style *s)
{
    s->box = FL_FLAT_BOX;
    s->button_box = FL_UP_BOX;
    s->button_color = FL_BLACK;
    s->color = FL_GRAY;
    s->label_size = 10;
}


static Fl_Named_Style style("Bar", revert, &Fl_Bar::default_style);
Fl_Named_Style* Fl_Bar::default_style = &::style;

Fl_Bar::Fl_Bar(int x, int y, int w, int h, const char* l)
: Fl_Group(x, y, w, h, l)
{
    ctor_init(h);
}

Fl_Bar::Fl_Bar(const char* l,Fl_Align layout_al,int layout_size,int label_w) 
: Fl_Group(l,layout_size,layout_al,label_w)
{
    ctor_init(h());
}

void Fl_Bar::ctor_init(int hh) 
{
    style(default_style);

    type(HORIZONTAL);
    open_ = true;
    highlighted = false;
    pushed = false;
    glyph_size_ = 12;
    saved_size = hh;
    align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
}

void Fl_Bar::glyph_box(int& x, int& y, int& w, int& h)
{
    //box()->inset(x,y,w,h);
    x = y = 0; w = this->w(); h = this->h();
    if (type() & 1)              // horizontal
    {
        w = open_ ? glyph_size_ : saved_size;
    }
    else
    {
        h = open_ ? glyph_size_ : saved_size;
    }
}


#include <stdio.h>
int Fl_Bar::handle(int event)
{
    int x,y,w,h;
    switch (event)
    {
        case FL_ENTER:
        case FL_MOVE:
        case FL_LEAVE:
            if (highlight_color() && takesevents())
            {
                glyph_box(x,y,w,h);
                bool hl = Fl::event_inside(x,y,w,h);
                if (hl != highlighted)
                {
                    highlighted = hl;
                    redraw(FL_DAMAGE_HIGHLIGHT);
                }
            }
            break;
        case FL_PUSH:
            glyph_box(x,y,w,h);
            if (Fl::event_inside(x,y,w,h))
            {
                pushed = highlighted = true;
                redraw(FL_DAMAGE_HIGHLIGHT);
                return true;
            }
            break;
        case FL_DRAG:
            glyph_box(x,y,w,h);
            if (Fl::event_inside(x,y,w,h))
            {
                if (!pushed)
                {
                    pushed = highlighted = true;
                    redraw(FL_DAMAGE_HIGHLIGHT);
                }
            }
            else
            {
                if (pushed)
                {
                    pushed = false;
                    redraw(FL_DAMAGE_HIGHLIGHT);
                }
            }
            return true;
        case FL_RELEASE:
            if (pushed)
            {
                opened(!open_);
                pushed = false;
                highlighted = true;
                redraw(FL_DAMAGE_HIGHLIGHT);
            }
            else if (highlighted)
            {
                highlighted = false;
                redraw(FL_DAMAGE_HIGHLIGHT);
            }
            return true;
    }
    if (open_) return Fl_Group::handle(event);
    else return 0;
}


void Fl_Bar::draw()
{
    if (open_)
    {
        if (damage() & ~FL_DAMAGE_HIGHLIGHT)
        {
            // make it not draw the inside label:
            int saved = flags(); align(FL_ALIGN_TOP);
            Fl_Group::draw();
            flags(saved);
        }
    }
    else if (damage() & ~(FL_DAMAGE_CHILD|FL_DAMAGE_HIGHLIGHT))
    {
        draw_box();
        int x = 0,y = 0,w = this->w(),h = this->h(); box()->inset(x,y,w,h);
        if (type() & 1)          // horizontal
            draw_inside_label(saved_size, y, w-saved_size, h, 0);
        else
            draw_inside_label(x, saved_size, w, h-saved_size, 0);
    }
    if (damage() & (FL_DAMAGE_EXPOSE|FL_DAMAGE_HIGHLIGHT))
    {
        Fl_Flags f = 0;
        if (pushed) f |= FL_VALUE;
        if (highlighted) f |= FL_HIGHLIGHT;
        int x,y,w,h; glyph_box(x,y,w,h);
        draw_glyph(0, x, y, w, h, f);
    }
}

bool Fl_Bar::opened(bool v)
{
    if (open_)
    {
        if (v) return false;
        open_ = false;
        if (type() & 1)          // horizontal
        {
            saved_size = h();
            resize(x(), y(), w(), glyph_size_);
        }
        else
        {
            saved_size = w();
            resize(x(), y(), glyph_size_, h());
        }
    }
    else
    {
        if (!v) return false;
        open_ = true;
        if (type() & 1)          // horizontal
            resize(x(), y(), w(), saved_size);
        else
            resize(x(), y(), saved_size, h());
    }
    relayout();
    redraw();
    if(parent()) {
        parent()->redraw();
        parent()->relayout();
    }
    return true;
}


// Don't move widgets around while we are closed!
void Fl_Bar::layout()
{
    if (open_) Fl_Group::layout();
    else Fl_Widget::layout();
}
