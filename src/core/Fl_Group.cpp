//
// "$Id$"
//
// Group widget for the Fast Light Tool Kit (FLTK).
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

// Fl_Window itself is a subclass of this, and most of the event
// handling is designed so windows themselves work correctly.

#include <efltk/Fl.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Window.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Tooltip.h>

#include <stdlib.h>

////////////////////////////////////////////////////////////////

FL_API Fl_Group* Fl_Group::m_current;

static void revert(Fl_Style* s)
{
    s->color = FL_INVALID_COLOR;//FL_GRAY;
    s->box = FL_NO_BOX;
}

// This style is unnamed since there is no reason for themes to change it:
extern Fl_Named_Style* group_style;
static Fl_Named_Style the_style(0, revert, &group_style);
Fl_Named_Style* group_style = &the_style;

Fl_Group::Fl_Group(int X,int Y,int W,int H,const char *l)
: Fl_Widget(X,Y,W,H,l), m_layout_spacing(1), m_focus(-1), m_resizable(0), m_data_source(0)
{

    widget_type(GROUP_TYPE);
    style(::group_style);
    align(FL_ALIGN_TOP);
    // Subclasses may want to construct child objects as part of their
    // constructor, so make sure they are add()'d to this object.
    // But you must end() the object!
    begin();
}

void Fl_Group::clear()
{
    init_sizes();
    if(children()) {
        Fl_Widget*const* a = array().data();
        Fl_Widget*const* e = a+children();
        // clear everything now, in case fl_fix_focus recursively calls us:
        m_focus = -1;
        if(resizable()) resizable(this);
        // okay, now it is safe to destroy the children:
        while (e > a) {
            Fl_Widget* o = *--e;
            o->parent(0);        // stops it from calling remove()
            delete o;
        }
        array().clear();
    }
}

Fl_Group::~Fl_Group() { 
    clear(); 
    if(Fl_Group::current()==this)
        Fl_Group::current(parent());
}

void Fl_Group::insert(Fl_Widget &o, int index)
{
    if (o.parent()) {
        int n = o.parent()->find(o);
        if (o.parent() == this) {
            if (index > n) index--;
            if (index == n) return;         
        }
        o.parent()->remove(n);
    }
    o.parent(this);
    if(children() == 0) {
        // allocate for 1 child
        array().append(&o);
    } else {
        array().insert(index, &o);
    }
    init_sizes();
}

void Fl_Group::remove(int index)
{
    if(index >= children()) return;
    Fl_Widget* o = child(index);
    o->parent(0);
    array().remove(index);
    init_sizes();
}

void Fl_Group::replace(int index, Fl_Widget& o)
{
    if(index >= children()) {
        add(o);
        return;
    }
    o.parent(this);
    array()[index]->parent(0);
    array().replace(index, &o);
    init_sizes();
}

int Fl_Group::find(const Fl_Widget* o) const
{
    for (;;) {
        if (!o) return children();
        if(o->parent() == this) break;
        o = o->parent();
    }

    // Search backwards so if children are deleted in backwards order
    // they are found quickly:
    for (int index = children(); index--;)
        if(child(index) == o)
            return index;

    return children();
}


////////////////////////////////////////////////////////////////
// Handle

// Turn FL_Tab into FL_Right or FL_Left for keyboard navigation
int Fl_Group::navigation_key()
{
    switch (Fl::event_key())
    {
        case FL_Tab:
            if (Fl::event_state(FL_CTRL)) return 0;
            return Fl::event_state(FL_SHIFT) ? FL_Left : FL_Right;
        case FL_Up:
        case FL_Down:
        case FL_Left:
        case FL_Right:
            return Fl::event_key();
        default:
            return 0;
    }
}


int Fl_Group::handle(int event)
{
    const int numchildren = children();
    int i;

    switch (event)
    {
        case FL_FOCUS:
            if (contains(Fl::focus()))
            {
            // The focus is being changed to some widget inside this.
                m_focus = find(Fl::focus());
                return true;
            }
        // otherwise it indicates an attempt to give this widget focus:
            switch (navigation_key())
            {
                default:
                    {
                // try to give it to whatever child had focus last:
                        if (m_focus >= 0 && m_focus < numchildren)
                            if (child(m_focus)->take_focus()) return true;
                // otherwise search for the widget that needs the focus, but
                // prefer a widget that returns 2:
                        Fl_Widget* f1 = 0; int ret = 0;
                        for (i = 0; i < numchildren; ++i)
                        {
                            Fl_Widget* w = child(i);
                            int n = w->handle(FL_FOCUS);
                            if (n) {ret = n; f1 = w; if (n & 2) break;}
                        }
                        if (f1 && !f1->contains(Fl::focus())) Fl::focus(f1);
                        return ret;
                    }
                case FL_Right:
                case FL_Down:
                    for (i=0; i < numchildren; ++i)
                        if (child(i)->take_focus()) return true;
                    return false;
                case FL_Left:
                case FL_Up:
                    for (i = numchildren; i--;)
                        if (child(i)->take_focus()) return true;
                    return false;
            }

        case FL_DRAG:
        case FL_RELEASE:
        case FL_LEAVE:
        case FL_DND_LEAVE:
        // Ignore these. We handle them if the belowmouse of pushed widget
        // has been set to this. Subclasses may do something with these.
        // Definately do not pass them to child widgets!
            break;

        case FL_KEY: {
        // keyboard navigation
                if (!numchildren) break;
                int key = navigation_key();
                if (!key) break;        

                int previous = m_focus;     
                if (previous < 0 || previous >= numchildren) previous = 0;      
                for (i = previous;;)
                {
                    if (key == FL_Left || key == FL_Up) {
                        if (i) --i;
                        else
                        {
                            if (parent()) return false;
                            i = numchildren-1;
                        }
                    } else {
                        ++i;
                        if (i >= numchildren) {
                            if (parent()) return false;
                            i = 0;
                        }
                    }

                    if (i == previous) {                
                        break;
                    }

                    if (key == FL_Down || key == FL_Up)
                    {
                // for up/down, the widgets have to overlap horizontally:
                        Fl_Widget* o = child(i);
                        Fl_Widget* p = child(previous);
                        if (o->x() >= p->x()+p->w() || o->x()+o->w() <= p->x()) continue;
                    }

                    if (child(i)->take_focus()) {                   
                        return true;
                    }           
                }
            }

        case FL_PUSH:
        case FL_ENTER:
        case FL_MOVE:
        case FL_DND_ENTER:
        case FL_DND_DRAG:
        // search the children in backwards (top to bottom) order:
            for (i = numchildren; i--;) {
                Fl_Widget* child = this->child(i);
            // ignore widgets we are not pointing at:
                if (Fl::event_x() < child->x()) continue;
                if (Fl::event_x() >= child->x()+child->w()) continue;
                if (Fl::event_y() < child->y()) continue;
                if (Fl::event_y() >= child->y()+child->h()) continue;
            // see if it wants the event:
                if (child->send(event)) return true;
            // quit when we reach a widget that claims mouse points at it,
            // so we don't pass the events to widgets "hidden" behind that one.
                if (event != FL_ENTER && event != FL_MOVE &&
                        child->contains(Fl::belowmouse())) return false;
            }
            return Fl_Widget::handle(event);

        default: {
        // Try to give all other events to every child, starting at focus:
                if (!numchildren) break;
                int previous = m_focus;
                if (previous < 0 || previous >= numchildren) previous = 0;
                for (i = previous;;) {
                    if (child(i)->send(event)) return true;
                    if (++i >= numchildren) i = 0;
                    if (i == previous) break;

                }
                break;
            }
    }

    return Fl_Widget::handle(event);
}


    ////////////////////////////////////////////////////////////////
// Layout

// So that resizing a window and then returing it to it's original
// size results in the original layout, the initial size and position
// of all children are stored in the sizes() array.
//
// Though this makes sense it often results in unexpected behavior
// when a program wants to rearrange the child widgets or change the
// size of a group to surround a new arrangement of child widgets.
//
// The solution fltk provides is the init_sizes() method, which resets
// thins so that the current state is considered the
// "initial" state the next time layout() is called. Because resize()
// does not directly call layout() you can use resize() on the group
// and all children to get exactly the layout you want, and then call
// init_sizes() to indicate that nothing should move when layout is
// called.
//
// The sizes() array stores the initial positions of widgets as
// left,right,top,bottom quads.  The first quad is the group, the
// second is the resizable (clipped to the group), and the
// rest are the children.  This is a convienent order for the
// algorithim.  If you change this be sure to fix Fl_Tile which
// also uses this array!
//
// Calling init_sizes() "resets" the sizes array to the current group
// and children positions.  Actually it just deletes the sizes array,
// and it is not recreated until the next time layout is called. This
// allows arbitrary layout changes to be made by the program until the
// moment that the group is displayed to the user. This appears to be
// the desired behavior.

void Fl_Group::init_sizes()
{
    m_sizes.clear();
    relayout();
}


int* Fl_Group::sizes()
{
    if(m_sizes.size()<=0) {
        // first thing in sizes array is the group's size:
        m_sizes.append(x());
        m_sizes.append(w());
        m_sizes.append(y());
        m_sizes.append(h());
        // next is the resizable's size:
        m_sizes.append(0);                // init to the group's size
        m_sizes.append(w());
        m_sizes.append(0);
        m_sizes.append(h());

        Fl_Widget* r = resizable();
        if (r && r != this)      // then clip the resizable to it
        {
            int t;
            t = r->x(); if (t > 0) m_sizes[4] = t;
            t +=r->w(); if (t < m_sizes[1]) m_sizes[5] = t;
            t = r->y(); if (t > 0) m_sizes[6] = t;
            t +=r->h(); if (t < m_sizes[3]) m_sizes[7] = t;
        }
        // next is all the children's sizes:

        for(uint n=0; n<array().size(); n++) {
            Fl_Widget *widget = array()[n];
            if(!widget->layout_align()) {
                m_sizes.append(widget->x());
                m_sizes.append(widget->x()+widget->w());
                m_sizes.append(widget->y());
                m_sizes.append(widget->y()+widget->h());
            }
        }
    }
    return (int*)m_sizes.data();
}

static int max(int a,int b) {
    if (a>b) return a;
    return b;
}

static int widget_total_width(Fl_Widget *w,int pref_w) {
    int label_w = w->label_width();
    if (label_w < 0) label_w = 0;
    if (w->align() & (FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) 
        return max(label_w,pref_w);
    return pref_w + label_w;
}

static int widget_total_height(Fl_Widget *w,int pref_h) {
    if (w->align() & (FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) 
        return w->label_height() + pref_h;
    return max(w->label_height(),pref_h);
}

static void widget_position(Fl_Widget *w,int x,int y,int& wx,int& wy) {
    int label_w = w->label_width();
    if (label_w < 0) label_w = 0;
    if (w->align() & (FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) {
        wx = x;
        wy = y;
        if (w->align() & FL_ALIGN_TOP)
            wy = y + w->label_height();
    } else {
        wx = x;
        wy = y;
        if (w->align() & FL_ALIGN_LEFT)
            wx = x + label_w;
    }
}

void Fl_Group::layout()
{
    // Save the layout damage and then clear it. This is so layout() of a
    // child can turn it back on and subclasses like Fl_Pack can detect that:
    int layout_damage = this->layout_damage();
    int pref_x, pref_y;
    int pref_w, pref_h;
    int total_w, total_h;
    int label_w=0;
    Fl_Widget::layout();

    int* p = 0;
    if (resizable() && children() > 0) {
        p = sizes(); // initialize the size array
    }

    if(children() > 0 && layout_damage&(FL_LAYOUT_DAMAGE|FL_LAYOUT_WH))
    {
        Fl_Widget *client = NULL;
        int dw=0, dh=0, IX=0, IR=0, IY=0, IB=0;
        if(p) {
            // get changes in size from the initial size:
            dw = w()-p[1];
            dh = h()-p[3];
            p+=4;

            // Calculate a new size & position for every child widget:
            // get initial size of resizable():
            IX = *p++; IR = *p++; IY = *p++; IB = *p++;
        }
        int xx = 0, yy = 0;
        int ww = w(), hh = h();
        box()->inset(xx,yy,ww,hh);

        int offset = m_layout_spacing;
        xx+=offset; yy+=offset;
        ww-=offset*2; hh-=offset*2;

        Fl_Widget*const* a = array().data();
        Fl_Widget*const* e = a+children();

        while (a < e)
        {
            Fl_Widget *o = *a++;
            switch (o->layout_align()) {
                case 0: {
                        if(!p || !resizable()) break;

                        int X = p[0];
                        if (X >= IR) X += dw;
                        else if (X > IX) X = X + dw * (X-IX)/(IR-IX);
                        int R = p[1];
                        if (R >= IR) R += dw;
                        else if (R > IX) R = R + dw * (R-IX)/(IR-IX);

                        int Y = p[2];
                        if (Y >= IB) Y += dh;
                        else if (Y > IY) Y = Y + dh*(Y-IY)/(IB-IY);
                        int B = p[3];
                        if (B >= IB) B += dh;
                        else if (B > IY) B = B + dh*(B-IY)/(IB-IY);

                        o->resize(X, Y, R-X, B-Y);
                        p += 4;
                    }
                    break;

                case FL_ALIGN_LEFT:
                    if (!o->visible()) break;

                    pref_w = o->w();
                    pref_h = hh;
                    o->preferred_size(pref_w,pref_h);

                    total_w = widget_total_width(o,pref_w);

                    widget_position(o,xx,yy,pref_x,pref_y);

                    o->resize(pref_x,pref_y,pref_w,pref_h);
                    xx += total_w + offset * 2;
                    ww -= total_w + offset * 2;
                    break;

                case FL_ALIGN_RIGHT:
                    if(!o->visible()) break;

                    pref_w = o->w();
                    pref_h = hh;
                    o->preferred_size(pref_w,pref_h);

                    total_w = widget_total_width(o,pref_w);

                    widget_position(o,xx+ww-total_w,yy,pref_x,pref_y);

                    o->resize(pref_x,pref_y,pref_w,pref_h);

                    ww -= total_w + offset * 2;
                    break;

                case FL_ALIGN_TOP:
                    if (!o->visible()) break;

                    pref_w = ww;
                    pref_h = o->h();

                    if (!(o->align() & (FL_ALIGN_TOP|FL_ALIGN_BOTTOM))) {
                        label_w = o->label_width();
                        if (label_w < 0) label_w = 0;
                        pref_w -= label_w;
                    }

                    o->preferred_size(pref_w,pref_h);

                    widget_position(o,xx,yy,pref_x,pref_y);

                    o->resize(pref_x,pref_y,pref_w,pref_h);

                    total_h = widget_total_height(o,pref_h);

                    yy += total_h + offset * 2;
                    hh -= total_h + offset * 2;
                    break;

                case FL_ALIGN_BOTTOM:
                    if(!o->visible()) break;

                    pref_w = ww;
                    pref_h = o->h();
                    if (!(o->align() & (FL_ALIGN_TOP|FL_ALIGN_BOTTOM))) {
                        label_w = o->label_width();
                        if (label_w < 0) label_w = 0;
                        pref_w -= label_w;
                    }

                    o->preferred_size(pref_w,pref_h);

                    total_h = widget_total_height(o,pref_h);

                    widget_position(o,xx,yy+hh-total_h,pref_x,pref_y);

                    o->resize(pref_x,pref_y,pref_w,pref_h);

                    hh -= total_h + offset * 2;
                    break;

                case FL_ALIGN_CLIENT:
                    if(!o->visible()) break;
                    client = o;
                    break;
            }
        }
        // use the remaining space for the only client-size widget, if any
        if(client) {
            pref_w = ww;
            pref_h = hh;
            if (client->align() & (FL_ALIGN_TOP|FL_ALIGN_BOTTOM)) {
                pref_h -= client->label_height();
            } else {
                label_w = client->label_width();
                if (label_w < 0) label_w = 0;
                pref_w -= label_w;
            }
            client->preferred_size(pref_w,pref_h);

            // Center the widget in the client area, if it's preferred
            // size is smaller than client area
            total_h = widget_total_height(client,pref_h);
            total_w = widget_total_width(client,pref_w);
            widget_position(client,xx+ww/2-total_w/2,yy+hh/2-total_h/2,pref_x,pref_y);
            client->resize(pref_x,pref_y,pref_w,pref_h);
        }
    }

    Fl_Widget*const* a = array().data();
    Fl_Widget*const* e = a+children();
    if ((layout_damage & (FL_LAYOUT_DAMAGE|FL_LAYOUT_XY)) && !is_window())
    {
        // If this is not an Fl_Window and the xy position is changed, we must
        // call layout() on every child. This is necessary so that child
        // Fl_Windows will move to their new positions.
        while (a < e)
        {
            Fl_Widget* widget = *a++;
            widget->layout_damage(widget->layout_damage()|FL_LAYOUT_XY);
            widget->layout();
        }
    }
    else
    {
        // Otherwise we only need to call layout on children with the
        // layout bit set:
        while (a < e)
        {
            Fl_Widget* widget = *a++;
            if (widget->layout_damage()) widget->layout();
        }
    }

    if (layout_damage & FL_LAYOUT_WH) redraw();
}

////////////////////////////////////////////////////////////////
// Draw
void Fl_Group::draw()
{
    int numchildren = children();
    if (damage() & ~FL_DAMAGE_CHILD)
    {
        int n; 
        if(!(fl_current_dev->capabilities() & Fl_Device::CAN_CLIPOUT)) {
            // blinky-draw:
            draw_box();
            draw_inside_label();
            for (n = 0; n < numchildren; n++)
            {
                Fl_Widget& w = *child(n);
                w.set_damage(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE);
                update_child(w);
            }
        } else {
            // Non-blinky draw, draw the inside widgets first, clip their areas
            // out, and then draw the background:
            fl_push_clip(0, 0, w(), h());
            for (n = numchildren; n--;) draw_child(*child(n));
            draw_box();
            draw_inside_label();
            fl_pop_clip();
        }

        // labels are drawn without the clip for back compatability so they
        // can draw atop sibling widgets:
        for (n = 0; n < numchildren; n++) draw_outside_label(*child(n));
    }
    else
    {
        // only some child widget has been damaged, draw them without
        // doing any clipping.  This is for maximum speed, even though
        // this may result in different output if this widget overlaps
        // another widget or a label.
        for (int n = 0; n < numchildren; n++)
        {
            Fl_Widget& w = *child(n);
            if (w.damage() & FL_DAMAGE_CHILD_LABEL)
            {
                draw_outside_label(w);
                w.set_damage(w.damage() & ~FL_DAMAGE_CHILD_LABEL);
            }
            update_child(w);
        }
    }
}


// Pieces of draw() that subclasses may want to use:

// Draw the background. If FL_DAMAGE_EXPOSE is on, widgets are expected
// to completely fill their rectangle. To allow non-rectangular widgets
// to appear to work, a widget can call this (with the clip region set)
// to draw the area of it's parent that is visible behind it.
void Fl_Group::draw_group_box() const
{
    // So that this may be called from any child's draw context, I need to
    // figure out the correct origin:
    fl_push_matrix();
#if 1
    fl_load_identity();
    int x = 0;
    int y = 0;
    const Fl_Group* group = this;
    while (!group->is_window())
    {
        x += group->x();
        y += group->y();
        group = group->parent();
    }
    fl_translate(x,y);
#else
    // this does not work because it resets the clip region:
    make_current();
#endif
    if (!box()->fills_rectangle())
    {
        if (parent()) {
            parent()->draw_group_box();
        } else {
            fl_color(color());
            fl_rectf(0, 0, w(), h());
        }
    }
    draw_box();
    draw_inside_label();
    fl_pop_matrix();
}

// Widgets that want to outwit the clip-out can set this when they are
// drawn to indicate that they did the clip-out. Only Fl_Tabs really uses
// this (and I'm not certain it has to), plus a bunch of back-compatability
// widgets that want to be "invisible" (they turn this on but don't draw
// anything). This is a pointer so if it is left on by a child widget
// it does not fool this into thinking the clipping is done.
Fl_Widget *fl_did_clipping=0;
Fl_Widget *current_drawchild=0;

// Force a child to redraw and remove the rectangle it used from the clip
// region.
void Fl_Group::draw_child(Fl_Widget& w) const
{
    if (w.visible() && !w.is_window())
    {
        if (!fl_not_clipped(w.x(), w.y(), w.w(), w.h())) return;
        fl_push_matrix();
        fl_translate(w.x(), w.y());
        fl_did_clipping = 0;
        current_drawchild = &w;
        w.set_damage(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE);
        w.draw();
        w.set_damage(0);
        if(fl_did_clipping != &w && fl_current_dev->capabilities() & Fl_Device::CAN_CLIPOUT) {
            fl_clip_out(0,0,w.w(),w.h());
        }
        fl_pop_matrix();
        current_drawchild = 0;
    }
}


// Redraw a single child in response to it's damage:
void Fl_Group::update_child(Fl_Widget& w) const
{
    if (w.damage() && w.visible() && !w.is_window())
    {
        if (!fl_not_clipped(w.x(), w.y(), w.w(), w.h())) return;
        fl_push_matrix();
        fl_translate(w.x(), w.y());
        w.draw();
        w.set_damage(0);
        fl_pop_matrix();
    }
}

// Parents normally call this to draw outside labels:
void Fl_Group::draw_outside_label(Fl_Widget& w) const
{
    if (!w.visible()) return;
    // skip any labels that are inside the widget:
    if (!(w.flags()&15) || (w.flags() & FL_ALIGN_INSIDE)) return;
    // invent a box that is outside the widget:
    unsigned align = w.flags();
    int X = w.x();
    int Y = w.y();
    int W = w.w();
    int H = w.h();

    if (align & FL_ALIGN_TOP)
    {
        align ^= (FL_ALIGN_BOTTOM|FL_ALIGN_TOP);
        Y = 0;
        H = w.y();
    }
    else if (align & FL_ALIGN_BOTTOM)
    {
        align ^= (FL_ALIGN_BOTTOM|FL_ALIGN_TOP);
        Y = Y+H;
        H = h()-Y;
    }
    else if (align & FL_ALIGN_LEFT)
    {
        align ^= (FL_ALIGN_LEFT|FL_ALIGN_RIGHT);
        X = 0;
        W = w.x()-3;
    }
    else if (align & FL_ALIGN_RIGHT)
    {
        align ^= (FL_ALIGN_LEFT|FL_ALIGN_RIGHT);
        X = X+W+3;
        W = this->w()-X;
    }

    w.draw_label(X,Y,W,H,(Fl_Flags)align);
}

// data source support methods
void Fl_Group::data_source(Fl_Data_Source *ds)
{
    if (m_data_source)
        m_data_source->parent_ = NULL;
    m_data_source = ds; 
    m_data_source->parent_ = this;
}

bool Fl_Group::load_data(Fl_Data_Source *ds) {
    if (!ds)
        ds = m_data_source;
    if (!ds)
        return false;

    unsigned cnt = children();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Widget   *widget = child(i);
        widget->load_data(ds);
    }
    return true;
}

bool Fl_Group::save_data(Fl_Data_Source *ds) const {
    if (!ds)
        ds = m_data_source;
    if (!ds)
        return false;
    unsigned cnt = children();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Widget   *widget = child(i);
        widget->save_data(ds);
    }
    return true;
}

//
// End of "$Id$".
//
