//
// "$Id$"
//
// Menu bar widget for the Fast Light Tool Kit (FLTK).
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
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Util.h>
#include <efltk/Fl_Menu_Bar.h>
#include <efltk/fl_draw.h>
#include <config.h>

static void revert_menubar(Fl_Style* s) {
    s->leading = 5;
    s->color = FL_GRAY;
	s->selection_color = FL_LIGHT1;
	s->selection_text_color = FL_BLACK;
    s->box = FL_FLAT_BOX;
#if 0
    // NT 4.0 style
    s->button_box = FL_FLAT_BOX;
#else
    // Windows98 style:
    s->button_box = FL_HIGHLIGHT_BOX;
#endif
}

static Fl_Named_Style style_menubar("Menu_Bar", revert_menubar, &Fl_Menu_Bar::default_style);
Fl_Named_Style* Fl_Menu_Bar::default_style = &::style_menubar;

Fl_Menu_Bar::Fl_Menu_Bar(int x,int y,int w,int h,const char *l)
    : Fl_Menu_(x,y,w,h,l)
{
    style(default_style);
    shortcut(FL_Alt_L);
    lines=1;

    highlight_ = last_highlight_ = -1;
    selected_ = last_selected_ = -1;

    right_=0;
    do_layout=true;
    key_event = false;

    value(-1);

	anim_flags_ = TOP_TO_BOTTOM;
}

void Fl_Menu_Bar::draw()
{
    if(damage()&(~FL_DAMAGE_HIGHLIGHT))
        draw_box();

    if(!children()) { last_highlight_ = last_selected_ = -1; return; }

    //if(highlight_>=0) child(highlight_)->set_damage(FL_DAMAGE_HIGHLIGHT);
    //if(last_highlight_>=0) child(last_highlight_)->set_damage(FL_DAMAGE_HIGHLIGHT);

    int X=0, Y=0, W=w(), H=h();
    box()->inset(X,Y,W,H);
    fl_push_clip(X,Y,W,H);

    for (int i = 0; i < children(); i++)
    {
        Fl_Widget* widget = child(i);
        if (!widget->visible()) continue;

        Fl_Flags f=widget->flags();

        if(i==selected_) f|=FL_VALUE|FL_SELECTED;
        else if(i==highlight_) f|=FL_HIGHLIGHT;

        if( (damage()&(~FL_DAMAGE_HIGHLIGHT)) ||
           (selected_==i || last_selected_==i) ||
           (highlight_==i || last_highlight_==i) )
        {
            Fl_Color save_color = widget->highlight_label_color();
            widget->highlight_label_color(highlight_label_color());
            Fl_Color save_scolor = widget->selection_text_color();
            widget->selection_text_color(selection_text_color());
			int save_flags = widget->flags();
			widget->flags(f);

			Fl_Color c = (selected_==i)?selection_color():button_color();
            button_box()->draw(widget->x(), widget->y(), widget->w(), widget->h(), c, f);
            //update_child(*widget);
            fl_push_matrix();
            fl_translate(widget->x(), widget->y());
            widget->draw();
            fl_pop_matrix();

			widget->flags(save_flags);
            widget->highlight_label_color(save_color);
			widget->selection_text_color(save_scolor);
        }
    }

    fl_pop_clip();

    last_highlight_ = highlight_;
    last_selected_ = selected_;
}

void Fl_Menu_Bar::layout()
{
    if (!layout_damage()) return;

    // we only need to do something special if the group is resized:
    if (!(layout_damage() & (FL_LAYOUT_WH|FL_LAYOUT_DAMAGE)) || !children())
    {
        Fl_Group::layout();
        if (!(layout_damage() & FL_LAYOUT_DAMAGE)) return;
    }

    lines=1;
    if(do_layout) h(0);
    int X=box()->dx()+leading()/2;
    int Y=box()->dy()+leading()/2;
    int W = w()-box()->dw();
    int H = h()-box()->dh();

    for(int i = 0; i < children(); i++) {
        Fl_Widget *w = child(i);

        if(!w->visible()) continue;
        if(w==right_) continue;

        w->w(0); w->layout(); //Get original size
        w->w(w->w()+leading());
        w->h(w->h()+leading());

        if(w->w()+X > W && do_layout) {
            Y+=w->h()+leading()/2;
            X=box()->dx()+leading()/2;
            lines++;
        }

        if(Y+w->h() > H && do_layout) {
            h(Y+w->h()+leading()/2);
            H = h();
        }

        w->position(X,Y);
        X += w->w();
    }

    if(right_) {
        Fl_Widget *w = right_;

        w->w(0); w->layout(); //Get original size
        w->w(w->w()+leading());
        w->h(w->h()+leading());

        if(w->w()+X > W && do_layout) {
            Y+=w->h()+leading()/2;
            X=box()->dx()+leading()/2;
            lines++;
        }

        if(Y+w->h() > H && do_layout) {
            h(Y+w->h()+leading()/2);
            H=h();
        }

        if(lines==1)
            X=W-w->w();

        w->position(X,Y);
    }

	if(do_layout)
		Fl_Widget::size(W,H);
    Fl_Widget::layout();
}

int Fl_Menu_Bar::handle(int event)
{
    static bool menu_up=false;
    switch(event) {
	case FL_FOCUS: return 1;

    case FL_LEAVE:
        if(menu_up) return 0;
        highlight_ = selected_ = -1;
        redraw(FL_DAMAGE_HIGHLIGHT);
        return 1;

    case FL_PUSH: {
        value(-1);
        key_event = false;
        Fl_Widget *w = (highlight_>=0) ? child(highlight_) : 0;
        if(w && w->type()!=Fl_Item::NO_EXECUTE) {
            menu_up=true;
            popup(0,0,0,0);
            menu_up=false;
            return 1;
        }
        break;
    }
    case FL_ENTER:
    case FL_MOVE: {
        int index = -1;
        for(int i = 0; i < children(); i++) {
            Fl_Widget *widget = child(i);
            if(!widget->visible()) continue;
            if(Fl::event_inside(widget->x(), widget->y(), widget->w(), widget->h())) {
                index = i;
                break;
            }
        }
        if(index!=last_highlight_) {
            highlight_ = index;
            redraw(FL_DAMAGE_HIGHLIGHT);
        }
        break;
    }

	case FL_KEY:
    case FL_SHORTCUT: {
		if(!Fl::event_state(FL_ALT)) break;
		if(!focused()) {
			take_focus();
			key_event = true;
		}
        for(int i = 0; i < children(); i++) {
            Fl_Widget* w = child(i);
            if(w->is_group() && w->active() && w->test_shortcut()) {				
                value(i);
				menu_up=true;
                popup(0,0,0,0);
				menu_up=false;				
                return 1;
            }
        }
        if(handle_shortcut()) return 1;
        break;
    }

    default:
        break;

    }

    return Fl_Menu_::handle(event);
}

//
// End of "$Id$".
//
