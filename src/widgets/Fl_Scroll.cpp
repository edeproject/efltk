//
// "$Id$"
//
// Scroll widget for the Fast Light Tool Kit (FLTK).
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
#include <efltk/Fl_Scroll.h>
#include <efltk/fl_draw.h>

void Fl_Scroll::draw_clip(void* v,int X, int Y, int W, int H)
{
    fl_push_clip(X,Y,W,H);
    Fl_Scroll* s = (Fl_Scroll*)v;
    // draw all the children, clipping them out of the region:
    int numchildren = s->children(); int i;
    for (i = numchildren; i--;)
    {
        Fl_Widget& w = *s->child(i);
        // Partial-clipped children with their own damage will still need
        // to be redrawn before the scroll is finished drawing.  Don't clear
        // their damage in this case:
        uchar save = 0;
        if (!(s->damage()&FL_DAMAGE_ALL)) {
            if (w.x() < X || w.y() < Y ||
                w.x()+w.w() > X+W || w.y()+w.h() > Y+H)
                save = w.damage();
        }
        s->draw_child(w);
        w.set_damage(save);
    }
    // fill the rest of the region with color:
    fl_color(s->color()); fl_rectf(X,Y,W,H);
    // draw the outside labels:
    for (i = numchildren; i--;)
        s->draw_outside_label(*s->child(i));
    fl_pop_clip();
}

void Fl_Scroll::bbox(int& X, int& Y, int& W, int& H)
{
    X = 0; Y = 0; W = w(); H = h(); box()->inset(X,Y,W,H);
    if (scrollbar.visible()) {
        W -= scrollbar.w();
        if (scrollbar_align() & FL_ALIGN_LEFT) X += scrollbar.w();
    }
    if (hscrollbar.visible()) {
        H -= hscrollbar.h();
        if (scrollbar_align() & FL_ALIGN_TOP) Y += hscrollbar.h();
    }
}

void Fl_Scroll::draw()
{
    int X,Y,W,H; bbox(X,Y,W,H);

    uchar d = damage();
    if (d & FL_DAMAGE_ALL)       // full redraw
    {
        draw_frame();
        draw_clip(this, X, Y, W, H);
    }
    else
    {
        if (scrolldx || scrolldy) {
            fl_scroll(X, Y, W, H, scrolldx, scrolldy, draw_clip, this);
        }
        // draw damaged children
        if (d & FL_DAMAGE_CHILD) {
            fl_push_clip(X, Y, W, H);
            for (int i = children(); i--;) {
                Fl_Widget& w = *child(i);
                if (w.damage() & FL_DAMAGE_CHILD_LABEL) {
                    draw_outside_label(w);
                    w.set_damage(w.damage() & ~FL_DAMAGE_CHILD_LABEL);
                }
                update_child(w);
            }
            fl_pop_clip();
        }
    }
    scrolldx = scrolldy = 0;

    // draw the scrollbars:
    if (d & FL_DAMAGE_ALL)
    {
        scrollbar.set_damage(FL_DAMAGE_ALL);
        hscrollbar.set_damage(FL_DAMAGE_ALL);
        if (scrollbar.visible() && hscrollbar.visible())
        {
            // fill in the little box in the corner
            fl_color(button_color());
            fl_rectf(scrollbar.x(),hscrollbar.y(),scrollbar.w(),hscrollbar.h());
        }
    }
    update_child(scrollbar);
    update_child(hscrollbar);
}

// Calculates extra size needed for widgets outside label
void calc_outside_label(Fl_Widget& widget, int &x, int &y, int &w, int &h)
{
    if(!widget.visible() || !widget.label() || !*widget.label()) return;
    // skip any labels that are inside the widget:
    if(!(widget.flags()&15) || (widget.flags() & FL_ALIGN_INSIDE)) return;
    // invent a box that is outside the widget:
    unsigned align = widget.flags();

    fl_font(widget.label_font(), widget.label_size());
    int TW=widget.w(), TH=widget.h(); // rather arbitrary choice for maximum wrap width
    fl_measure(widget.label(), TW, TH, widget.flags());
    TW+=5;
    TH+=5;

    if (align & FL_ALIGN_TOP) {
        y-=TH;
        h+=TH;
    }
    else if (align & FL_ALIGN_BOTTOM) {
        h+=TH;
    }
    else if (align & FL_ALIGN_LEFT) {
        x-=TW;
        w+=TW;
    }
    else if (align & FL_ALIGN_RIGHT) {
        w+=TW;
    }
}

void Fl_Scroll::layout()
{
    int X,Y,W,H;
    // move all the children and accumulate their bounding boxes:
    int dx = layoutdx;
    int dy = layoutdy;
    layoutdx = layoutdy = 0;
    scrolldx += dx;
    scrolldy += dy;
    int l = w();
    int r = 0;
    int t = h();
    int b = 0;
    int numchildren = children();
    for (int i=0; i < numchildren; i++)
    {
        Fl_Widget* o = child(i);
        o->position(o->x()+dx, o->y()+dy);
        o->layout();

        int ox=o->x(),oy=o->y(),ow=o->w(),oh=o->h();
        calc_outside_label(*o, ox, oy, ow, oh);

        if (ox < l) l = ox;
        if (oy < t) t = oy;
        if (ox+ow > r) r = ox+ow;
        if (oy+oh > b) b = oy+oh;
    }

    // Add offset:
    if(edge_offset_>0) {
        l-=edge_offset_;
        r+=edge_offset_;
        t-=edge_offset_;
        b+=edge_offset_;
    }

    const int sw = scrollbar_width();

    bool need_pos=false;
    int total_w = xposition_+r;
    int total_h = yposition_+b;
    int xp = xposition_, yp=yposition_;

    // See if children would fit if we had no scrollbars...
    X=0; Y=0; W=w(); H=h(); box()->inset(X,Y,W,H);
    bool vneeded = false;
    bool hneeded = false;

    if (type() & VERTICAL) {
        if ((type() & ALWAYS_ON) || total_h > H || yposition_) {
            vneeded = true;
            W -= sw;
            if (scrollbar_align() & FL_ALIGN_LEFT) X += sw;
        }
    }

    if (type() & HORIZONTAL) {
        if ((type() & ALWAYS_ON) || total_w > W || xposition_) {
            hneeded = true;
            H -= sw;
            if (scrollbar_align() & FL_ALIGN_TOP) Y += sw;
            // recheck vertical since we added a horizontal scrollbar
            if (!vneeded && (type() & VERTICAL)) {
                if(total_h > H || yposition_) {
                    vneeded = true;
                    W -= sw;
                    if (scrollbar_align() & FL_ALIGN_LEFT) X += sw;
                }
            }
        }
    }
    // Now that we know what's needed, make it so.
    if (vneeded) {
        if (!scrollbar.visible()) {
            scrollbar.set_visible();
            redraw(FL_DAMAGE_ALL);
        }
    } else {
        if (scrollbar.visible()) {
            scrollbar.clear_visible();
            redraw(FL_DAMAGE_ALL);
        }
    }
    if (hneeded) {
        if (!hscrollbar.visible()) {
            hscrollbar.set_visible();
            redraw(FL_DAMAGE_ALL);
        }
    } else {
        if (hscrollbar.visible()) {
            hscrollbar.clear_visible();
            redraw(FL_DAMAGE_ALL);
        }
    }

    //Adjust Y pos
    yposition_ = (Y-t);
    if(total_h < H) { yp = 0; need_pos = true; }
    else if(H>b && total_h>H) { yp = total_h-H; need_pos=true; yposition_ = (Y-t);}

    // Adjust X pos
    xposition_ = (X-l);
    if(total_w < W) { xp = 0; need_pos = true; }
    else if(W>r && total_w>W) { xp = total_w-W; need_pos=true; xposition_ = (X-l); }

    scrollbar.resize(scrollbar_align()&FL_ALIGN_LEFT ? X-sw : X+W, Y, sw, H);
    scrollbar.value(yposition_, H, 0, total_h);
    hscrollbar.resize(X, scrollbar_align()&FL_ALIGN_TOP ? Y-sw : Y+H, W, sw);
    hscrollbar.value(xposition_, W, 0, total_w);

    Fl_Widget::layout();

    if(need_pos) position(xp, yp);
    redraw(FL_DAMAGE_SCROLL);
}

void Fl_Scroll::position(int X, int Y)
{
    int dx = xposition_-X;
    int dy = yposition_-Y;
    if (!dx && !dy) return;
    xposition_ = X;
    yposition_ = Y;
    layoutdx += dx;
    layoutdy += dy;

    relayout();
}

void Fl_Scroll::hscrollbar_cb(Fl_Widget* o, void*)
{
    Fl_Scroll* s = (Fl_Scroll*)(o->parent());
    s->position(int(((Fl_Scrollbar*)o)->value()), s->yposition());
}


void Fl_Scroll::scrollbar_cb(Fl_Widget* o, void*)
{
    Fl_Scroll* s = (Fl_Scroll*)(o->parent());
    s->position(s->xposition(), int(((Fl_Scrollbar*)o)->value()));
}

#define SLIDER_WIDTH scrollbar_width()

Fl_Scroll::Fl_Scroll(int X,int Y,int W,int H,const char* L)
: Fl_Group(X,Y,W,H,L), endgroup(0),
scrollbar(X+W-SLIDER_WIDTH,Y,SLIDER_WIDTH,H-SLIDER_WIDTH),
hscrollbar(X,Y+H-SLIDER_WIDTH,W-SLIDER_WIDTH,SLIDER_WIDTH)
{
    type(BOTH);
    xposition_ = 0;
    yposition_ = 0;
    scrolldx = scrolldy = layoutdx = layoutdy = 0;
    edge_offset_ = 3;

    //hscrollbar.resize();
    hscrollbar.parent(this);
    hscrollbar.type(Fl_Slider::HORIZONTAL);
    hscrollbar.callback(hscrollbar_cb);
    hscrollbar.linesize(12);

    scrollbar.parent(this);
    scrollbar.callback(scrollbar_cb);
    scrollbar.linesize(12);

    Fl_Group::current(this);
}

int Fl_Scroll::handle(int event)
{
    switch (event)
    {

    case FL_FOCUS:
        if (contains(Fl::focus())) {
            // The event indicates that the focus changed to a different child,
            // auto-scroll to show it:
            Fl_Widget* w = Fl::focus();
            int x = w->x();
            int y = w->y();
            for (Fl_Group* p = w->parent(); p != this; p = p->parent()) {
                // if (!p) return 0; // this should never happen
                x += p->x();
                y += p->y();
            }
            int X,Y,R,B; bbox(X,Y,R,B); R += X; B += Y;
            int r = x+w->w();
            int dx = 0;
            if (x < X) {
                dx = X-x;
                if (r+dx > R) {
                    dx = R-r; if (dx < 0) dx = 0;
                }
            }
            else if (r > R) {
                dx = R-r;
                if (x+dx < X) {
                    dx = X-x; if (dx > 0) dx = 0;
                }
            }
            int b = y+w->h();
            int dy = 0;
            if (y < Y) {
                dy = Y-y;
                if (b+dy > B) {
                    dy = B-b; if (dy < 0) dy = 0;
                }
            }
            else if (b > B) {
                dy = B-b;
                if (y+dy < Y) {
                    dy = Y-y; if (dy > 0) dy = 0;
                }
            }
            position(xposition_-dx, yposition_-dy);
            layout();
        }
        break;

    case FL_PUSH:
    case FL_ENTER:
    case FL_MOVE:
    case FL_DND_ENTER:
    case FL_DND_DRAG:
        // For all mouse events check to see if we are in the scrollbar
        // areas and send to them:
        if (scrollbar.visible() &&
            (scrollbar_align()&FL_ALIGN_LEFT ?
             (Fl::event_x() < scrollbar.x()+scrollbar.w()) :
             (Fl::event_x() >= scrollbar.x())))
            return scrollbar.send(event);
        if (hscrollbar.visible() &&
            (scrollbar_align()&FL_ALIGN_TOP ?
             (Fl::event_y() < hscrollbar.y()+hscrollbar.h()) :
             (Fl::event_y() >= hscrollbar.y())))
            return hscrollbar.send(event);
        break;

    case FL_MOUSEWHEEL:
        return scrollbar.send(event);

    case FL_KEY:
        if (scrollbar.send(event)) return 1;
        if (hscrollbar.send(event)) return 1;
        break;
    }

    return Fl_Group::handle(event);
}


//
// End of "$Id$".
//
