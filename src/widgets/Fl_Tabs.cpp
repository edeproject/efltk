//
// "$Id$"
//
// Tab widget for the Fast Light Tool Kit (FLTK).
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

// This is the "file card tabs" interface to allow you to put lots and lots
// of buttons and switches in a panel, as popularized by many toolkits.

// Each child widget is a card, and it's label() is printed on the card tab.
// Clicking the tab makes that card visible.

#include <efltk/Fl.h>
#include <efltk/Fl_Tabs.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Tooltip.h>

#define TABSLOPE 5
#define EXTRASPACE 5+button_box()->dw()

// return the left edges of each tab (plus a fake left edge for a tab
// past the right-hand one).  These position are actually of the left
// edge of the slope.  They are either seperated by the correct distance
// or by TABSLOPE or by zero.
// Return value is the index of the selected item.

int Fl_Tabs::tab_positions(int* p, int* w)
{
    int selected = -1;
    int i;
    p[0] = 0;
    int numchildren = children();
    for (i=0; i<numchildren; i++)
    {
        Fl_Widget* o = child(i);
        if(o->visible()) selected = i;
        if(!o->label().empty())
        {
            int wt = 0; int ht = 0; o->measure_label(wt,ht);
            w[i] = wt+TABSLOPE+EXTRASPACE;
            //if (2*TABSLOPE > w[i]) w[i] = 2*TABSLOPE;
        } else
        w[i] = 2*TABSLOPE;
        p[i+1] = p[i]+w[i]+1;
    }
    int r = this->w()-TABSLOPE-1;
    if (p[i] <= r) return selected;
    // uh oh, they are too big:
    // pack them against right edge:
    p[i] = r;
    for (i = children(); i--;)
    {
        int l = r-w[i];
        if (p[i+1]-TABSLOPE < l) l = p[i+1]-TABSLOPE;
        if (p[i] <= l) break;
        p[i] = l;
        r -= TABSLOPE;
    }
    // pack them against left edge and truncate width if they still don't fit:
    for (i = 0; i<children(); i++)
    {
        if (p[i] >= i*TABSLOPE) break;
        p[i] = i*TABSLOPE;
        int W = this->w()-1-TABSLOPE*(children()-i) - p[i];
        if (w[i] > W) w[i] = W;
    }
    // adjust edges according to visiblity:
    for (i = children(); i > selected; i--)
    {
        p[i] = p[i-1]+w[i-1]+1;
    }
    return selected;
}


// return space needed for tabs.  Negative to put them on the bottom:
int Fl_Tabs::tab_height()
{
    int H = h();
    int H2 = 0;
    int numchildren = children();
    for (int i=0; i < numchildren; i++)
    {
        Fl_Widget* o = child(i);
        if (o->y() < H) H = o->y();
        if (o->y()+o->h() > H2) H2 = o->y()+o->h();
    }
    H2 = h()-H2;
    int dx=0; int dy=0; int dw=0; int dh=0; box()->inset(dx,dy,dw,dh);
    if (H2 > H)
    {
        H = H2-dy;
        return (H <= 0) ? 0 : -H-1;
    }
    else
    {
        H = H-dy;
        return (H <= 0) ? 0 : H;
    }
}


// this is used by fluid to pick tabs:
Fl_Widget *Fl_Tabs::which(int event_x, int event_y)
{
    int H = tab_height();
    if (H < 0)
    {
        if (event_y > h() || event_y < h()+H) return 0;
    }
    else
    {
        if (event_y > H || event_y < 0) return 0;
    }
    if (event_x < 0) return 0;
    int p[128], w[128];
    int selected = tab_positions(p, w);
    int d = (event_y-(H>=0?0:h()))*TABSLOPE/(H==0?1:H);
    for (int i=0; i<children(); i++)
    {
        if (event_x < p[i+1]+(i<selected ? TABSLOPE-d : d)) return child(i);
    }
    return 0;
}


int Fl_Tabs::handle(int event)
{

    Fl_Widget *selected = this->value();
    int i;
    int backwards = 0;

    switch (event)
    {

        case FL_FOCUS:
            if (contains(Fl::focus()))
            {
                // this is called to indicate that some child got the focus
                                 /*if (Fl::focus() == this || focus() < 0)*/
                redraw(FL_DAMAGE_VALUE);
                focus(Fl::focus() == this ? -1 : 0);
                return true;
            }
            // otherwise this indicates that somebody is trying to give focus to this
            switch (navigation_key())
            {
            case FL_Left:
            case FL_Up:
                if (tab_height() < 0) goto GOTO_TABS; else goto GOTO_CONTENTS;
            case FL_Right:
            case FL_Down:
                if (tab_height() < 0) goto GOTO_CONTENTS; else goto GOTO_TABS;
            default:
            GOTO_CONTENTS:
                // Try to give the contents the focus. Also preserve a return value
                // of 2 (which indicates the contents have a text field):
                if (selected)
                {
                    int n = selected->handle(FL_FOCUS);
                    if (n)
                    {
                        if (!selected->contains(Fl::focus())) Fl::focus(selected);
                        return n;
                    }
                }
            GOTO_TABS:
                focus(-1);
                // moving right moves focus to the tabs.
                return true;
            }

        case FL_UNFOCUS:
            if (focus() < 0) redraw(FL_DAMAGE_VALUE);
            return 1;

            // handle mouse events in the tabs:
        case FL_PUSH:
        {
            int H = tab_height();
            if (H >= 0)
            {
                if (Fl::event_y() > H) break;
            }
            else
            {
                if (Fl::event_y() < h()+H) break;
            }
        }
        case FL_DRAG:
        case FL_RELEASE:
            selected = which(Fl::event_x(), Fl::event_y());
            if (event == FL_RELEASE && !Fl::pushed())
            {
                push(0);
                if (selected && value(selected)) do_callback();
            }
            else
            {
                push(selected);
            }
            return 1;

            // handle pointing at the tabs to bring up tooltip:
        case FL_ENTER:
        case FL_MOVE:
        {
            int H = tab_height();
            if (H >= 0)
            {
                if (Fl::event_y() > H) break;
            }
            else
            {
                if (Fl::event_y() < h()+H) break;
            }
            Fl_Widget* item = which(Fl::event_x(), Fl::event_y());
            //Fl::belowmouse(this);
            if (item) Fl_Tooltip::enter(this, 0, H<0?h()+H:0, w(), H<0?-H:H, item->tooltip().c_str());
            return 1;
        }

        case FL_KEY:
            switch (Fl::event_key())
            {
                case ' ':
                case FL_Right:
                    break;
                case FL_BackSpace:
                case FL_Left:
                    backwards = 1;
                    break;
                default:
                    return 0;
            }
            MOVE:
            for (i = children()-1; i>0; i--) if (child(i)->visible()) break;
            if (backwards) {i = i ? i-1 : children()-1;}
            else {i++; if (i >= children()) i = 0;}
            value(child(i)); do_callback();
            return 1;

        case FL_SHORTCUT:
            if (Fl::event_key()==FL_Tab && Fl::event_state(FL_CTRL))
            {
                backwards = Fl::event_state(FL_SHIFT);
                goto MOVE;
            }
            if (!selected) return 0;
            if (selected->send(event)) return 1;
            if (!contains(Fl::focus())) return 0;
            switch (navigation_key())
            {
                case FL_Right:
                case FL_Down:
                    if (focus() < 0 && selected) return selected->take_focus();
                    else return 0;
                case FL_Left:
                case FL_Up:
                    if (focus() >= 0) {Fl::focus(this); return 1;}
                    else return 0;
                default:
                    return 0;
            }
    }

    if (selected) return selected->send(event);
    return 0;
}


int Fl_Tabs::push(Fl_Widget *o)
{
    if (push_ == o) return 0;
    if (push_ && !push_->visible() || o && !o->visible())
        redraw(FL_DAMAGE_VALUE);
    push_ = o;
    return 1;
}


// The value() is the first visible child (or the last child if none
// are visible) and this also hides any other children.
// This allows the tabs to be deleted, moved to other groups, and
// show()/hide() called without it screwing up.
Fl_Widget* Fl_Tabs::value()
{
    Fl_Widget* v = 0;
    int numchildren = children();
    for (int i=0; i < numchildren; i++)
    {
        Fl_Widget* o = child(i);
        if (v) o->hide();
        else if (o->visible()) v = o;
        else if (i==numchildren-1) {o->show(); v = o;}
    }
    return v;
}


// Setting the value hides all other children, and makes this one
// visible, iff it is really a child:
int Fl_Tabs::value(Fl_Widget *newvalue)
{
    int setfocus = !focused() && contains(Fl::focus());
    int numchildren = children();
    for (int i=0; i < numchildren; i++)
    {
        Fl_Widget* o = child(i);
        if (o == newvalue)
        {
            // no change
            if (o->visible()) return 0;
            o->show();
            if (setfocus) o->take_focus();
        }
        else
        {
            o->hide();
        }
    }
    return 1;
}


enum {LEFT, RIGHT, SELECTED};

extern Fl_Widget* fl_did_clipping;

static int p[128];
void Fl_Tabs::draw()
{
    Fl_Widget *v = value();
    int selected=-1;
    int i;
    int w[128];

    tabH = tab_height();
    if (damage() & FL_DAMAGE_ALL)// redraw the entire thing:
    {
        fl_push_clip(0,0,this->w(),this->h());
        if (v) draw_child(*v);
        parent()->draw_group_box();
        box()->draw(0, (tabH>=0?tabH:0), this->w(), this->h()-(tabH>=0?tabH:-tabH)+1, v ? v->color() : color(), FL_INVISIBLE);
        fl_pop_clip();
    }                            // redraw the child
    else
    {
        if (v) update_child(*v);
    }

    if(!(fl_current_dev->capabilities() & Fl_Device::CAN_CLIPOUT)) {
        set_damage(FL_DAMAGE_ALL);
    }

    // draw the tabs if needed:
    if (damage() & (FL_DAMAGE_VALUE|FL_DAMAGE_ALL))
    {		        
        selected = tab_positions(p,w);        

        for(i=0; i<selected; i++)
            draw_tab(p[i], p[i+1], w[i], tabH, child(i), LEFT);
        for(i=children()-1; i > selected; i--)
            draw_tab(p[i], p[i+1], w[i], tabH, child(i), RIGHT);
        if(v) {
            i = selected;
            draw_tab(p[i], p[i+1], w[i], tabH, child(i), SELECTED);
        }
    }

    if (damage() & FL_DAMAGE_EXPOSE) {
        fl_clip_out(0, tabH>=0 ? 0 : h()+tabH, p[children()]+TABSLOPE, (tabH>=0?tabH:-tabH));
        fl_clip_out(0, tabH>0 ? tabH : 0, this->w(), h()-(tabH>=0?tabH:-tabH-1));
        fl_did_clipping = this;
    }
}


void Fl_Tabs::draw_tab(int x1, int x2, int W, int H, Fl_Widget* o, int what)
{	
  bool sel = (what == SELECTED);

  if ((x2 < x1+W) && what == RIGHT) x1 = x2 - W;
  
  Fl_Color c = (!sel && o==push_) ? fl_color_average(selection_color(), o->selection_color(), 0.8) : o->color();
  Fl_Flags f=sel?FL_SELECTED:0;

  if (H >= 0) {
      H--;
      int adjust = (sel?box()->dy()+1:0);
      button_box()->draw(x1, 0, W, H+adjust, c, f|FL_ALIGN_TOP);
      o->draw_label(x1, button_box()->dy(), W, H, FL_ALIGN_CENTER);
      if (focused() && o->visible())
          focus_box()->draw(x1+button_box()->dx(),
                            button_box()->dy(),
                            W-button_box()->dw(),
                            H-button_box()->dh()+adjust,
                            FL_BLACK, FL_INVISIBLE|FL_ALIGN_TOP|f);
  } else {
      H = -H;
      int adjust = (sel?(box()->dh()-box()->dy()):0);
      button_box()->draw(x1, h()-H-adjust+1, W, H+adjust-2, c, f|FL_ALIGN_BOTTOM);
      o->draw_label(x1, h()-H, W, H-1, FL_ALIGN_CENTER);
      if(focused() && o->visible())
          focus_box()->draw(x1+button_box()->dx(),
                            h()-H+button_box()->dy()-adjust,
                            W-button_box()->dw(),
                            H-button_box()->dh()+adjust-1,
                            FL_BLACK, FL_INVISIBLE|FL_ALIGN_BOTTOM|f);
  }
}

#define CORNER 5

#define C(c) fl_color(c + (FL_GRAY_RAMP-'A'));
//#define C(c) fl_color(fl_gray_ramp(c))

class TabBox : public Fl_Flat_Box {
public:
    TabBox() : Fl_Flat_Box(0) { dx_=dy_=2; dw_=dh_=4;}
    void draw(int x,int y,int w,int h, Fl_Color color, Fl_Flags f) const
    {
        if(f&FL_ALIGN_TOP) {            
            int cX=x+CORNER;
            int cY=y+CORNER;
            C('W');
            fl_line(x, y+h-1, x, cY);
            fl_line(x, cY, cX, y);
            fl_line(cX, y, x+w, y);
            C('A');
            fl_line(x+w, y, x+w, y+h-1);

            x++; y++; w-=2;
            C('T');
            fl_line(x, y+h-1, x, cY);
            fl_line(x, cY, cX, y);
            fl_line(cX, y, x+w, y);
            C('M');
            fl_line(x+w, y, x+w, y+h-1);
			
            x++; y++; w--; h--;
            fl_color(color);
            fl_newpath();
            fl_vertex(x, y+h-1);   fl_vertex(x, cY);
            fl_vertex(cX, y);    fl_vertex(x+w, y);
            fl_vertex(x+w, y+h-1); fl_vertex(x, y+h-1);
            fl_closepath();
            fl_fill();

        } else {
						
            int cX=x+CORNER;
            int cY=y+h-CORNER;
            C('W');
            fl_line(x, y, x, cY);       // '|'
            fl_line(x, cY, cX, y+h);    // '\'
            C('A');
            fl_line(cX, y+h, x+w, y+h); // '_'
            fl_line(x+w, y+h, x+w, y);  // '|'

            x++; w-=2; h--;
            C('T');
            fl_line(x, y, x, cY);
            fl_line(x, cY, cX, y+h);
            C('M');
            fl_line(cX, y+h, x+w, y+h);
            fl_line(x+w, y+h, x+w, y);

            x++; w--;
            fl_color(color);
            fl_newpath();
            fl_vertex(x, y);    fl_vertex(x, cY);
            fl_vertex(cX, y+h); fl_vertex(x+w, y+h);
            fl_vertex(x+w, y);  fl_vertex(x, y);
            fl_closepath();
            fl_fill();
        }
    }
};
TabBox tabbox;

class TabFocusBox : public Fl_Flat_Box {
public:
    TabFocusBox() : Fl_Flat_Box(0) { }
    void draw(int x,int y,int w,int h, Fl_Color color, Fl_Flags f) const
    {
        fl_line_style(FL_DOT);
        fl_color(color);
        if(f&FL_ALIGN_TOP) {
            int cX=x+CORNER;
            int cY=y+CORNER;
            fl_line(x, y+h, x, cY+1);
            fl_line(x, cY, cX, y);
            fl_line(cX+1, y, x+w, y);
            fl_line(x+w, y, x+w, y+h);
            fl_line(x+w, y+h, x, y+h);
        } else {
            int cX=x+CORNER;
            int cY=y+h-CORNER;
            fl_line(x, y, x, cY-1);
            fl_line(x, cY, cX, y+h);
            fl_line(cX+1, y+h, x+w, y+h);
            fl_line(x+w, y+h, x+w, y);
            fl_line(x, y, x+w, y);
        }
        fl_line_style(0);
    }
};
TabFocusBox tabfocusbox;

static void revert(Fl_Style* s)
{
    s->box = FL_UP_BOX;
    s->button_box = &tabbox;
    s->focus_box = &tabfocusbox;
	//s->focus_box = FL_NO_BOX;
    s->color = FL_GRAY;
    s->selection_color = FL_GRAY;
}


static Fl_Named_Style style("Tabs", revert, &Fl_Tabs::default_style);
Fl_Named_Style* Fl_Tabs::default_style = &::style;

Fl_Tabs::Fl_Tabs(int X,int Y,int W, int H, const char *l)
: Fl_Group(X,Y,W,H,l)
{
    style(default_style);
    push_ = 0;
	tabH = 0;
}


//
// End of "$Id$".
//
