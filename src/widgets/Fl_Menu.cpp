//
// "$Id$"
//
// Implementation of popup menus.  These are called by using the
// Fl_Menu_::popup and Fl_Menu_::pulldown methods.  See also the
// Fl_Menu_ base class in Fl_Menu_.cxx.  Warning: this code is
// quite a mess!  Also, the classes defined here are private and
// may change in the future!
//
// Copyright 1998-2000 by Bill Spitzak and others.
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
#include <efltk/fl_math.h>
#include <config.h>

#include <efltk/Fl_Menu_.h>
#include <efltk/Fl_Menu_Bar.h>
#include <efltk/Fl_Choice.h>
#include <efltk/Fl_Util.h>
#include <efltk/Fl.h>
#include <efltk/x.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Item.h> // for TOGGLE, RADIO
#include <efltk/Fl_Tooltip.h>
#include <efltk/Fl_Image.h>

#define checkmark(item) (item->type()>=Fl_Item::TOGGLE && item->type()<=Fl_Item::RADIO)

#include <stdlib.h>
#include <stdio.h>

#if defined(_WIN32) && !defined(__GNUC__)
# define isnan(x) false
#endif

class MenuWindow;

enum {
    INITIAL_STATE = 0,// no mouse up or down since popup() called
    PUSH_STATE,	// mouse has been pushed on a normal item
    DONE_STATE	// execute the selected item
};

typedef struct menustate_
{
  int level;	// which level of nesting current item is in
  int indexes[MAX_LEVELS]; // index in each level of selected item  
  bool menubar; // if true menus[0] is a menubar
  int state; // one of the enumeration below

  // timeout stuff:
  MenuWindow *open_window, *close_window;
  Fl_Widget *open_widget;
  int open_index;

} MenuState;

///////////////////////
// MENU WINDOW CLASS //
///////////////////////

class MenuWindow : public Fl_Menu_Window {
public:
    static Fl_Named_Style* default_style;

    MenuWindow(MenuWindow *parent, Fl_Widget *widget, int widget_index, Fl_Menu_ *menu, int *indexes, int level, int Wp=0, int Hp=0);
    ~MenuWindow();

    int autoscroll(int i);
    Fl_Widget* get_widget(int index);
    int is_parent(int index);

    Fl_Widget *find_widget(int x, int y, int *index=0);
    int ypos(int index);

    int backward(int menu);
    int forward(int menu);
    void set_item(int level, int index);

    void relayout(int *indexes, int level);
    void layout();
    void draw();
    int handle(int event);

    Fl_Widget* current_widget() {
        if(!indexes_) return 0;
        return menu_->child(indexes_, level_);
    }
    // return the widget at a given level:
    Fl_Widget* current_widget(int level) {
        if(!indexes_ || level<0) return 0;
        return menu_->child(indexes_, level);
    }

    void open_childwin(Fl_Widget *widget, int index);
    void close_childwin();

    void show();
    void show(Fl_Window *w);

    void fix_indexes();

    void set_selected(int index) {
        if(index!=selected_) {
            selected_ = index;
            redraw(FL_DAMAGE_CHILD);
        }
    }

//private:
    friend class Fl_Menu_;
    friend class Fl_Menu_Bar;
    friend class Fl_Choice;

    MenuWindow *child_win;
    Fl_Menu_ *menu_;

    Fl_Widget *widget_;
    int widget_index_;

    int selected_, last_selected_;

    int *indexes_;
    int level_;
    bool add_items;
    bool empty;

    int ox,oy,ow,oh;
    int Wp, Hp;

    int effect;
    int anim_flags;

    MenuWindow *parent;

    static bool key_event;
};

bool MenuWindow::key_event = false;

static MenuState *state = 0;

static MenuWindow *first_menu = 0; //First popped up menuwindow
static MenuWindow *current_menu = 0; //Current subwindow

#define TXT_OFFSET  3
#define TXT_OFFSET2 6

static void revert_menuwin(Fl_Style *s) {
    s->color = FL_GRAY;
    s->box = FL_UP_BOX;
    s->button_box = FL_FLAT_BOX;
    s->leading = 4;
}
static Fl_Named_Style style_menuwin("Menu", revert_menuwin, &MenuWindow::default_style);
Fl_Named_Style* MenuWindow::default_style = &::style_menuwin;

MenuWindow::MenuWindow(MenuWindow *parent, Fl_Widget *widget, int widget_index, Fl_Menu_ *menu, int *indexes, int level, int Wp, int Hp)
    : Fl_Menu_Window(0,0,0)
{
    effect = Fl_Menu_::default_effect_type();
    current_menu = this;

    end();
    style(default_style);
    set_override();

    anim_flags = 0;

    ox=oy=ow=oh=-1;

    child_win = 0;
    add_items = false;
    widget_ = widget;
    widget_index_ = widget_index;
    menu_ = menu;
    empty = true;

    this->parent = parent;

    this->Wp=Wp;
    this->Hp=Hp;

    relayout(indexes, level);
}

void timeout_open_childwin(void *arg);
void timeout_close_childwin(void *arg);

MenuWindow::~MenuWindow()
{
    animating = false;

    if(child_win) {
        close_childwin();
    }

    if(state->open_window==this) {
        state->open_widget = 0;
        state->open_index = -1;
        state->open_window = 0;
    }

    current_menu = parent;
}

void MenuWindow::relayout(int *indexes, int level)
{
    indexes_ = indexes;
    level_ = level;

    selected_ = last_selected_ = -1;
    child_win = 0;

    animating = false;

    empty = true;
    add_items = true;

    Fl_Menu_ *menu = (Fl_Menu_*)widget_;
    if(menu && menu->is_group() && menu->about_to_show) {
        menu->about_to_show(menu, menu->user_data());
    }

    layout();
    redraw();
}

void MenuWindow::layout()
{
    int W=0,H=0;

    if(indexes_ && add_items) {

        int hotKeysW = 0;

        for (int i = 0;; i++) {
            Fl_Widget* widget = get_widget(i);
            if (!widget) break;
            if (!widget->visible()) continue;

            int itemw = widget->width();
            int itemh = widget->height();

            if(W<itemw) W=itemw;
            H+=itemh+leading();

            if(is_parent(i)) {
                if (16 > hotKeysW) hotKeysW = 16;
            } else if (widget->shortcut()) {
                int w1 = int(fl_width(Fl::key_name(widget->shortcut())) + 8.5);
                if (w1 > hotKeysW) hotKeysW = w1;
            }

            widget->set_damage(FL_DAMAGE_ALL);
            empty = false;
        }

        W += hotKeysW + box()->dw() + TXT_OFFSET2;
        H += box()->dh();

        if(Wp>W) W=Wp;

        size(W,H);

        ow = W;
        oh = H;
        add_items = false;

        if(parent) {
            if(Fl_Menu_::subwindow_effect()) {
                anim_flags = Fl_Menu_::LEFT_TO_RIGHT;
            }
        }
    }

    if(!indexes_ || empty) {
        //shows littlebox empty box on empty menus
        //W=widget_->width();
        //H=box()->dh();
        ow = W; oh = H;
        size(W,H);
    }

	Fl_Menu_Window::layout();
}

void MenuWindow::draw()
{
    if(!indexes_ || empty || animating) {
        //box()->draw(0, 0, w(), h(), color(), 0); //Comment out, if little empty box is showed on empty menus
        return;
    }

    if( damage() != FL_DAMAGE_CHILD ) {
        box()->draw(0, 0, w(), h(), color(), 0);
    }

    int x=1; int y=0;
    int w=this->w()-2; int h=0;
    box()->inset(x,y,w,h);

    for (int i = 0; ; i++) {
        Fl_Widget* widget = get_widget(i);
        if (!widget) break;
        if (!widget->visible()) continue;

        int itemh = widget->height()+leading();

        // Minimal update if FL_DAMAGE_CHILD is set on
        if (damage() != FL_DAMAGE_CHILD || i==selected_ || i==last_selected_)
        {
            Fl_Flags flags = widget->flags();

            if(selected_==i && !(flags & (FL_OUTPUT|FL_INACTIVE)) )
            {
                flags |= FL_SELECTED;
                if (Fl::event_state(FL_BUTTONS) && widget->takesevents())
                    Fl::pushed_ = widget;
                button_box()->draw(x,y,w,itemh,selection_color(),flags);

            } else {

                flags &= ~FL_SELECTED;
                if (damage() == FL_DAMAGE_CHILD) {
                    fl_push_clip(x,y,w,itemh);
                    box()->draw(0, 0, this->w(), this->h(), color(), 0);
                    fl_pop_clip();
                }
            }

            fl_push_matrix();
            fl_translate(x+TXT_OFFSET, y+leading()/2);
            int save_w = widget->w();
            widget->w(w-TXT_OFFSET2);
            int save_flags = widget->flags();
            Fl_Color save_scolor = widget->selection_text_color();
            widget->selection_text_color(selection_text_color());
            widget->flags(flags);
            widget->draw();
            widget->flags(save_flags);
            widget->selection_text_color(save_scolor);
            widget->w(save_w);
            Fl::pushed_ = 0;
            fl_pop_matrix();

            flags &= ~(FL_VALUE|FL_ALIGN_MASK);

            if (is_parent(i)) {

                // Use the item's fontsize for the size of the arrow, rather than h:
                int nh = widget->text_size();
                draw_glyph(FL_GLYPH_RIGHT, x+w-nh, y+((itemh-nh)>>1), nh, nh, flags);

            } else if (widget->shortcut()) {

                fl_font(widget->label_font(), float(widget->label_size()));
                int lx = int(fl_width(widget->label()));

                fl_font(widget->text_font(), float(widget->text_size()));

                int W = ow-box()->dw()-TXT_OFFSET2;
                fl_push_clip(lx+leading(), y, W-lx, itemh);
                widget->label_type()->draw(Fl::key_name(widget->shortcut()),
                                           x, y, W, itemh,
                                           (flags&FL_SELECTED) ? selection_text_color() : widget->label_color(),
                                           flags|FL_ALIGN_RIGHT);
                fl_pop_clip();
            }
        }
        y += itemh;
    }

    last_selected_ = selected_;
}

void MenuWindow::fix_indexes()
{
    if(!indexes_) return;

    MenuWindow *win=parent;
    int sel = widget_index_;
    while(win) {
        win->set_selected(sel);
        sel = win->widget_index_;
        win=win->parent;
    }

    win = this;
    while(win) {
        if(win->level_<=0) break;
        state->indexes[win->level_-1] = win->widget_index_;
        win = win->parent;
    }
}

Fl_Widget *MenuWindow::find_widget(int x, int y, int *index)
{
    if(!indexes_) return 0;

    Fl_Widget *widget=0;
    int Y=box()->dy();
    int X=box()->dx();
    int i=0;
    for(; ; i++) {
        widget = get_widget(i);
        if(!widget) {
            if(index) *index=-1;
            return 0;
        }
        if (!widget->visible()) continue;

        int itemh = widget->height()+leading();

        if(y>=Y&&y<Y+itemh && x>=X&&x<X+width())
            break;

        Y+=itemh;
    }
    if(index) *index=i;
    return widget;
}

// scroll so item i is visible on screen, return true if it moves
int MenuWindow::autoscroll(int i)
{
    if(i < 0) return 0;
    int Y = y()+ypos(i);
    if (Y <= Fl::y()) {
        Y = Fl::y()-Y+10;
    } else {
        Fl_Widget* widget = get_widget(i);
        if(widget) {
            Y = Y+widget->height()+leading()-Fl::h()-Fl::y();
            if (Y < 0) return 0;
            Y = -Y-10;
        } else return 0;
    }
    Fl_Window::position(x(), y()+Y);
    // y(y()+Y); // don't wait for response from X
    return 1;
}

static void autoscroll_timeout(void*) {
    // this will call MenuWindow::handle(FL_MOVE) but also set Fl::event()
    // so that the timeout gets repeated.
    Fl::handle(FL_MOVE, 0);
}

void MenuWindow::set_item(int level, int index)
{
    if(!indexes_) return;

    if(state->indexes[level] == index) return;

    indexes_[level] = index;
    indexes_[level+1] = -1;

    state->level = level;
    //state->indexes[level] = index;
    //state->indexes[level+1] = -1;

    // If we scroll to show this item and the user dragged to it, we should
    // continue scrolling after a timeout:
    Fl::remove_timeout(autoscroll_timeout, this);
    if(autoscroll(index)) {
        Fl::repeat_timeout(.05f, autoscroll_timeout, this);
    }
}

Fl_Widget *MenuWindow::get_widget(int index)
{
    if(!indexes_) return 0;

    int saved = indexes_[level_];
    indexes_[level_] = index;
    Fl_Widget* w = current_widget(level_);
    indexes_[level_] = saved;
    return w;
}

// return true if item is a parent of a submenu:
int MenuWindow::is_parent(int index)
{
    if(!indexes_) return 0;

    int saved = indexes_[level_];
    indexes_[level_] = index;
    int n = menu_->children(indexes_, level_+1);
    indexes_[level_] = saved;
    return (n >= 0);
}

// return the top edge of item:
int MenuWindow::ypos(int index)
{
    int y=0;
    y+=box()->dy();
    for (int i = 0; i < index; i++)
    {
        Fl_Widget* widget = get_widget(i);
        if (!widget->visible()) continue;
        y += widget->height()+leading();
    }
    return y;
}

int MenuWindow::backward(int menu)
{
    for (int item = state->indexes[menu]-1; item >= 0; item--)
    {
        Fl_Widget* widget = get_widget(item);
        if(!widget) return 0;
        if(widget->takesevents()) {
            set_item(menu, item);
            if(selected_!=item) {
                selected_=item;
                redraw(FL_DAMAGE_CHILD);
            }
            return 1;
        }
    }
    return 0;
}

int MenuWindow::forward(int menu)
{
    for(int item = state->indexes[menu]+1;;item++)
    {
        Fl_Widget* widget = get_widget(item);
        if (!widget) break;
        if (widget->takesevents()) {
            set_item(menu, item);
            if(selected_!=item) {
                selected_=item;
                redraw(FL_DAMAGE_CHILD);
            }
            return 1;
        }
    }
    return 0;
}

void MenuWindow::close_childwin()
{
    if(child_win) {
        child_win->animating = false;

        if(child_win->widget_ && child_win->widget_->is_group()) {
            Fl_Menu_ *menu = (Fl_Menu_*)child_win->widget_;
            if(menu && menu->about_to_hide) {
                menu->about_to_hide(menu, menu->user_data());
            }
        }

        child_win->hide();
        delete child_win;
        child_win=0;
    }
}

void MenuWindow::open_childwin(Fl_Widget *widget, int index)
{
    if(child_win && child_win->widget_!=widget) {

        close_childwin();
        child_win = new MenuWindow(this, widget, index, menu_, state->indexes, level_+1);
        child_win->effect = effect;

    }
    else if(!child_win) {

        child_win = new MenuWindow(this, widget, index, menu_, state->indexes, level_+1);
        child_win->effect = effect;

    } else
        return;

    int nX = x() + w() - 3;
    int nY = y() + ypos(index) - ypos(0);

    // Force menu on screen
    if(nX+child_win->ow > Fl::w()) {
        // X position to right side of current menu
        nX = x()-child_win->ow+3;//Fl::w()-child_win->ow;
        child_win->anim_flags = Fl_Menu_::RIGHT_TO_LEFT;
    }
    if(nY+child_win->oh > Fl::h()) {
        nY = Fl::h()-child_win->oh;
        if(nY<0) nY=0;
    }

    child_win->ox = nX;
    child_win->oy = nY;
    child_win->position(nX, nY);

    if(!child_win->visible()) {        
        child_win->show(first_menu);
    }

    //If key event, select first item
    if(key_event) child_win->forward(level_+1);
}

void timeout_open_childwin(void *arg)
{
    if(state->open_window && state->open_widget && state->open_index>=0) {
        state->open_window->open_childwin(state->open_widget, state->open_index);
    }
    state->open_widget = 0;
    state->open_index = -1;
    state->open_window = 0;
}

void timeout_close_childwin(void *arg)
{
    if(state->close_window) {
        state->close_window->close_childwin();
    }
    state->close_window = 0;
}

void timeout_initial(void *) {
    state->state = PUSH_STATE;
}

int MenuWindow::handle(int event)
{
    Fl_Rect rect;

    if(animating && (event==FL_PUSH||event==FL_MOVE||event==FL_DRAG||event==FL_KEY)) {
        // Stop animating if moving or dragging...
        animating = false;
        return 0;
    }

    // Redirect mouse events to child_win if needed
    if(first_menu == this && indexes_ && child_win
       && ( (event==FL_PUSH || event==FL_DRAG || event==FL_MOVE || event==FL_RELEASE) )
      ) {

        // Check if mouse pointer is pointing to any of parent menus
        MenuWindow *win=current_menu;//?current_menu->parent:0;
        while(win) {
            rect.set(win->x(), win->y(), win->w(), win->h());
            if(rect.posInRect(Fl::event_x_root(), Fl::event_y_root())) {
                break;
            }
            win=win->parent;
        }
        // If not in parent menus, send all events to current sub-menu
        if(!win) win = current_menu;

        // Redirect events:
        if(win && win!=this) {
            int sx = Fl::e_x; int sy = Fl::e_y;
            Fl::e_x = Fl::event_x_root()-win->x();
            Fl::e_y = Fl::event_y_root()-win->y();
            win->handle(event);
            Fl::e_x = sx;
            Fl::e_y = sy;
            return 1;
        }
    }

    int index=0;
    Fl_Widget *widget=0;

    switch(event)
    {
    case FL_KEY:
    case FL_SHORTCUT: {
        // Redirect key events to children
        if(child_win) {
            int ret = child_win->handle(event);
            if(ret) return 1;
            close_childwin();
            return 1;
        }

        key_event = true;
        Fl_Menu_::key_event = true;
        switch (Fl::event_key()) {
        case FL_Up:
            if(backward(level_));
            else set_item(0, indexes_[0]);
            return 1;
        case FL_Down:
            forward(level_);
            return 1;
        case FL_Right:
            if(indexes_ && is_parent(indexes_[state->level])) {
                index = indexes_[state->level];
                widget = current_widget();
                goto JUMP_OPEN;
            }
            else if( (level_==1||level_==-1) ) {
                int i=1;
                while(menu_->value()+i < menu_->children()) {
                    if( menu_->child(menu_->value()+i)->active() ) {
                        menu_->value(menu_->value()+i);
                        return 1;
                    }
                    i++;
                }
                if(menu_->value()+i >= menu_->children()) {
                    menu_->value(0);
                }
            }
            return 1;
        case FL_Left:
            if(level_>1 || !state->menubar) {
                return 0;
            }
            else if( (level_==1||level_==-1) ) {
                int i=menu_->value()-1;
                while(i >= 0) {
                    if( menu_->child(i)->active() ) {
                        menu_->value(i);
                        return 1;
                    }
                    i--;
                }
                if(i < 0) {
                    menu_->value(menu_->children()-1);
                }
            }
            return 1;
        
		case ' ':
        case FL_Enter:
            goto EXECUTE;
		
        case FL_Escape:
			//menu_picked=false;
            Fl::exit_modal();
            return 1;
        }
		return 0;
    }

    //case FL_ENTER:
    //case FL_LEAVE:
    case FL_DRAG:
    case FL_MOVE:
    case FL_PUSH:
        {
        fix_indexes();
        Fl_Menu_::key_event = false;
        key_event = false;

        rect.set(x(), y(), w(), h());
        if(!rect.posInRect(Fl::event_x_root(), Fl::event_y_root())) {
            //pointer not inside the window, set none selected
            if(selected_) {
                tooltip(0);
                Fl_Tooltip::exit();
                selected_=-1;
                redraw(FL_DAMAGE_CHILD);
            }
            state->open_widget = 0;
            state->open_index = -1;
            state->open_window = 0;
            state->close_window = 0;
            Fl::remove_timeout(timeout_open_childwin, state);
            Fl::remove_timeout(timeout_close_childwin, state);
            return 1;
        }

        index=-1;
        widget = find_widget(Fl::event_x(), Fl::event_y(), &index);
        if( (index!=selected_ && index!=-1) || (is_parent(index)&&index!=selected_) ) {
            tooltip(0);
            Fl_Tooltip::exit();
            selected_=index;
            redraw(FL_DAMAGE_CHILD);
        }

        if(widget) {
            tooltip(widget->tooltip());
            Fl_Tooltip::enter(this);

            // Send events widgets, so sub-classed items can get them.
            // FIXME: Fl::e_x and Fl::e_y is WRONG!
            if(widget->takesevents())
                if(widget->send(event)) {
                    return 1;
                }
        }
    JUMP_OPEN:
        if(widget) set_item(level_, index);

        if(state->open_window && widget && state->open_widget!=widget) {
            state->open_widget = 0;
            state->open_index = -1;
            state->open_window = 0;
            Fl::remove_timeout(timeout_open_childwin, state);
        }

        if(child_win && child_win->widget_==widget && state->close_window==this) {
            Fl::remove_timeout(timeout_close_childwin, state);
            state->close_window = 0;
        }

        float delay = (menu_->delay()==-1)?Fl_Menu_::default_delay():menu_->delay();

        //if(indexes_ && is_parent(index)) {
        if(indexes_ && widget && widget->is_group() )
        {
            if(child_win && child_win->widget_==widget) return 1;

            if(widget && !widget->takesevents() && !widget->active()) {
                // inactive item...
                goto CLOSE_JUMP;
            }

            if(delay>0 && state->open_widget!=widget) {
                // Add only, if not already added to this widget timeout
                state->open_widget = widget;
                state->open_index = index;
                state->open_window = this;
                Fl::add_timeout(delay, timeout_open_childwin, state);
            } else if(delay<=0) {
                // Open with NO timeout
                open_childwin(widget, index);
            }
            return 1;
        }

    CLOSE_JUMP:
        if(widget) {

            if(child_win) {
                if(delay>0) {
                    if(state->close_window!=this) {
                        if(state->close_window) Fl::remove_timeout(timeout_close_childwin, state);
                        state->close_window = this;
                        Fl::add_timeout(delay, timeout_close_childwin, state);
                    }
                } else {
                    close_childwin();
                }
            }
        }

        if (event == FL_PUSH) {
            state->state = PUSH_STATE;
            // redraw checkboxes so they preview the state they will be in:
            Fl_Widget* widget = get_widget(index);
            if(widget && checkmark(widget)) redraw(FL_DAMAGE_CHILD);
        }

        return 1;
        }

    case FL_RELEASE: {
        Fl::pushed_ = 0;

    EXECUTE: // execute the item pointed to by w and current item				
        // If clicked check button in menubar...
        if(state->menubar && widget_ && checkmark(widget_)) {			
            state->state = DONE_STATE;
            state->level=0;
            Fl::exit_modal();
            return 1;
        }
		
        // Allow menus to be "clicked-up".  Without this a single click will
        // pick whatever item the mouse is pointing at in a pop-up menu:
        if(state->state==INITIAL_STATE && Fl::event_is_click()) {			
			state->state=PUSH_STATE;
            return 1;
        }

        Fl_Widget *widget = 0;
        if(!key_event) {
            widget = find_widget(Fl::event_x(), Fl::event_y());
        } else {
            widget = current_widget();
        }

        // Open child window on RELEASE, if we are still waiting timeout
        if(widget && state->open_window==this) {
            Fl::remove_timeout(timeout_open_childwin, state);
            open_childwin(state->open_widget, state->open_index);
		    state->open_widget = 0;
		    state->open_index = -1;
			state->open_window = 0;
            return 1;
        }

        if(!widget && state->menubar) {
            // Check for button in menubar
            int WX = widget_->x(); int WY = widget_->y();
            for (Fl_Widget *o = widget_->parent(); o; o = o->parent()) {
                WX += o->x(); WY += o->y();
            }
            rect.set(WX, WY, widget_->w(), widget_->h());
            if(rect.posInRect(Fl::event_x_root(), Fl::event_y_root())) {
                widget = widget_;
                state->level = 0;
            }
        }

        if(!widget) {
            Fl::exit_modal(); return 1;
        }
        if(!widget->takesevents()) return 1;

        if(widget && widget->takesevents()) {
            // Send FL_RELEASE to item
            if(widget->send(event)) {
                return 1;
            }
        }

        state->state = DONE_STATE;
        Fl::exit_modal();
        return 1;
    }
	case FL_UNFOCUS:		
		//menu_picked=false;
        Fl::exit_modal();
        return 1;

    default:
        break;
    }

    return Fl_Menu_Window::handle(event);
}

void MenuWindow::show()
{
    if(!indexes_ || empty) {
        resize(-1,-1,1,1);
        Fl_Menu_Window::layout();
        Fl_Menu_Window::show();
        return;
    }

    if(!Fl_Menu_::effects() || (!Fl_Menu_::subwindow_effect()&&parent)) {
        Fl_Menu_Window::show();
        return;
    }

	// If shown, no effect..
    if(shown()) {
		Fl_Menu_Window::show();
		return;
	} 
		
	create(); //We need system handle for window (xid)!

    int X=x(), Y=y(), W=ow, H=oh;

    int ty=y(), tx=x();
    int tw=ow , th=oh;
    if(ty+th > Fl::h()) {
        H = th = Fl::h()-ty;
    }

    switch(effect)
    {
    case FL_EFFECT_FADE:
        fade(tx,ty,tw,th);
        break;

    case FL_EFFECT_ANIM:
        {
        if(anim_flags&Fl_Menu_::TOP_TO_BOTTOM) {
            Y=y();
            H=1;
        }
        else if(anim_flags&Fl_Menu_::BOTTOM_TO_TOP) {
            Y=y()+h();
            H=1;
        }
        if(anim_flags&Fl_Menu_::LEFT_TO_RIGHT) {
            X=x();
            W=1;
        }
        else if(anim_flags&Fl_Menu_::RIGHT_TO_LEFT) {
            X=x()+w();
            W=1;
        }

        if(W!=tw || H!=th)
            Fl_Menu_Window::animate(X,Y,W,H, tx,ty,tw,th);
        else
            Fl_Menu_Window::show();
    }

    case FL_EFFECT_NONE:
    default:
        Fl_Menu_Window::show();
        break;
    }

    resize(tx, ty, ow, oh);
    Fl_Menu_Window::layout();
}

void MenuWindow::show(Fl_Window *w)
{
    child_of(w);
    show();
}

//#define DEBUG_MENUS

#ifdef DEBUG_MENUS
# define MODAL false
#else
# define MODAL true
#endif

int Fl_Menu_::popup(int X, int Y, int W, int H)
{
    MenuState *saved_state = state;
    MenuWindow *saved_first = first_menu;
    MenuWindow *saved_current = current_menu;

    MenuState menustate;
    // reset sub-window delay stuff...
    menustate.open_widget = 0;
    menustate.open_index = -1;
    menustate.open_window = 0;
    menustate.close_window = 0;
    menustate.state = INITIAL_STATE;
    menustate.level=0;
    menustate.indexes[0] = value();
    menustate.indexes[1] = -1;
    menustate.menubar = false;
    state = &menustate;

    // fix possible programmer error...
    Fl_Group::current(0);

    // Lame hack to detect if user meant to popup in absolute position (many does this)
    if(X!=Fl::event_x_root() || Y!=Fl::event_y_root())
    {
        // figure out where to pop up in screen coordinates:
        if(parent()) {
            for (Fl_Widget* w = this; w; w = w->parent()) {
                X += w->x();
                Y += w->y();
            }
        } else {
            X += Fl::event_x_root()-Fl::event_x();
            Y += Fl::event_y_root()-Fl::event_y();
        }
    }
    Y+=H;

    if(color()!=FL_INVALID_COLOR)
        MenuWindow::default_style->color = color();

    float speed = (anim_speed()==-1||isnan(anim_speed()))?Fl_Menu_::default_anim_speed():anim_speed();
    int effect = (effect_type()==-1)?Fl_Menu_::default_effect_type():effect_type();

    first_menu = new MenuWindow(0, 0, value(), this, menustate.indexes, menustate.level, W, H);
    first_menu->child_of(Fl::first_window());
    first_menu->effect = effect;
    first_menu->anim_flags = anim_flags_;
    first_menu->anim_speed(speed);
    first_menu->widget_ = this;

    first_menu->relayout(menustate.indexes, menustate.level);

    // Force menu X/Y on screen
    if(Y+first_menu->oh > Fl::h()) {
        if(first_menu->oh>Fl::h()) Y = 0;
        else Y = Fl::h()-first_menu->oh;
    }
    if(X+first_menu->ow > Fl::w()) {
        X = Fl::w()-first_menu->ow;
    }

    first_menu->ox = X; first_menu->oy = Y;
    first_menu->position(X, Y);

    Fl_Widget* saved_modal = Fl::modal();
    bool saved_grab = Fl::grab();

    for(Fl::modal(first_menu, MODAL); !Fl::exit_modal_flag(); Fl::wait())
    {
        //Show window, after entered MODAL loop, so window can events while animating
        if(!first_menu->shown()) {
            first_menu->show(Fl::first_window());
            Fl::add_timeout(0.5f, timeout_initial);
        }
    }

    delete first_menu;

    Fl::modal(saved_modal, saved_grab);
    Fl::remove_timeout(timeout_open_childwin, state);
    Fl::remove_timeout(timeout_close_childwin, state);
    Fl::remove_timeout(timeout_initial);

    state = saved_state;
    first_menu = saved_first;
    current_menu = saved_current;

    if(menustate.state != DONE_STATE) return false;

    // Execute whatever item the user picked:
    focus(menustate.indexes, menustate.level);
    execute(item());

    return true;
}

int Fl_Menu_Bar::popup(int X, int Y, int W, int H)
{
    MenuState *saved_state = state;
    MenuWindow *saved_first = first_menu;
    MenuWindow *saved_current = current_menu;

    MenuState menustate;
    // reset sub-window delay stuff...
    menustate.open_widget = 0;
    menustate.open_index = -1;
    menustate.open_window = 0;
    menustate.close_window = 0;
    menustate.state = INITIAL_STATE;
    menustate.level=-1;
    menustate.indexes[0] = -1;
    menustate.menubar = true;
    state = &menustate;

    int WX = x(); int WY = y();
    for (Fl_Widget *o = parent(); o; o = o->parent()) {
        WX += o->x(); WY += o->y();
    }

    // fix possible programmer error...
    Fl_Group::current(0);

    if(color()!=FL_INVALID_COLOR)
        MenuWindow::default_style->color = color();

    float speed = (anim_speed()==-1||isnan(anim_speed()))?Fl_Menu_::default_anim_speed():anim_speed();
    int effect = (effect_type()==-1)?Fl_Menu_::default_effect_type():effect_type();

    first_menu = new MenuWindow(0, this, value(), this, 0, -1);
    first_menu->effect = effect;
    first_menu->anim_flags = anim_flags_;
    first_menu->anim_speed(speed);    
    first_menu->child_of(Fl::first_window());

    Fl_Widget* saved_modal = Fl::modal();
    bool saved_grab = Fl::grab();
    int cur_index = -1;

    for(Fl::modal(first_menu, MODAL); !Fl::exit_modal_flag(); Fl::wait())
    {
        Fl_Widget *inside=0;
        int index = -1;

        if(!key_event) {
            bool changed = true;

            MenuWindow *win = first_menu;
            while(win) {
                Fl_Rect r(win->x(), win->y(), win->w(), win->h());
                if(r.posInRect(Fl::event_x_root(), Fl::event_y_root())) {
                    changed = false;
                    break;
                }
                win = win->child_win;
            }

            if(!changed) continue;

            for(int i = 0; i < children(); i++) {
                Fl_Widget *widget = child(i);
                if(!widget->visible()) continue;
                Fl_Rect r(widget->x()+WX, widget->y()+WY, widget->w(), widget->h());
                if(r.posInRect(Fl::event_x_root(), Fl::event_y_root())) {
                    index = i;
                    inside = widget;
                    break;
                }
            }

        } else { //!key_event
            index = value();
            inside = child(index);
        }

        if(index>=0 && index!=cur_index)
        {
            if(index!=last_selected_) {
                highlight_ = selected_ = index;
                redraw(FL_DAMAGE_HIGHLIGHT);
            }
            value(index);
            menustate.level=1;
            menustate.indexes[0] = value();
            menustate.indexes[1] = 0;

            first_menu->widget_ = inside;
            if(first_menu->child_win) {
                first_menu->close_childwin();
            }

            int nX = inside->x()+WX;
            int nY = inside->y()+inside->h()+WY;

            int *tmp_indexes=0;
            int tmp_level = -1;

            if(inside->takesevents() && inside->active() && child(menustate.indexes, menustate.level))
            {
                // Force menu X on screen
                if(nX+first_menu->ow > Fl::w()) {
                    nX = Fl::w()-first_menu->ow;
                }

                menustate.indexes[1] = -1;
                tmp_indexes = menustate.indexes;
                tmp_level = menustate.level;
                first_menu->widget_index_ = value();

            } else {
                nX=nY=0;
            }

            first_menu->ox = nX; first_menu->oy = nY;
            first_menu->position(nX, nY);
            first_menu->relayout(tmp_indexes, tmp_level);

            cur_index = index;
            if(!first_menu->shown()) {
                first_menu->show();
                Fl::add_timeout(0.5f, timeout_initial);
            } else
                first_menu->show();
        }
    }

    delete first_menu;

    Fl::modal(saved_modal, saved_grab);
    Fl::remove_timeout(timeout_open_childwin, state);
    Fl::remove_timeout(timeout_close_childwin, state);
    Fl::remove_timeout(timeout_initial);

    state = saved_state;
    first_menu = saved_first;
    current_menu = saved_current;

    selected_ = -1;
    if(menustate.level>0) highlight_ = -1;
    redraw(FL_DAMAGE_HIGHLIGHT);

    if(menustate.state != DONE_STATE) return false;

    // Execute whatever item the user picked:
    focus(menustate.indexes, menustate.level);
    execute(item());

    return true;
}

//////////////////////////////
// FL_CHOICE

int Fl_Choice::popup(int X, int Y, int W, int H)
{
    MenuState *saved_state = state;
    MenuWindow *saved_first = first_menu;
    MenuWindow *saved_current = current_menu;

    MenuState menustate;
    // reset sub-window delay stuff...
    menustate.open_widget = 0;
    menustate.open_index = -1;
    menustate.open_window = 0;
    menustate.close_window = 0;
    menustate.state = INITIAL_STATE;
    menustate.level=0;
    menustate.indexes[0] = value();
    menustate.indexes[1] = -1;
    menustate.menubar = false;
    state = &menustate;

    // fix possible programmer error...
    Fl_Group::current(0);

    // figure out where to pop up in screen coordinates:
    if (parent()) {
        for (Fl_Widget* w = this; w; w = w->parent()) {
            X += w->x();
            Y += w->y();
        }
    } else {
        X += Fl::event_x_root()-Fl::event_x();
        Y += Fl::event_y_root()-Fl::event_y();
    }

    if(color()!=FL_INVALID_COLOR)
        MenuWindow::default_style->color = color();

    float speed = (anim_speed()==-1||isnan(anim_speed()))?Fl_Menu_::default_anim_speed():anim_speed();
    int effect = (effect_type()==-1)?Fl_Menu_::default_effect_type():effect_type();
    if(effect==FL_EFFECT_ANIM) effect = FL_EFFECT_NONE;

    first_menu = new MenuWindow(0, this, value(), this, menustate.indexes, menustate.level, W, H);
    first_menu->child_of(Fl::first_window());
    first_menu->effect = effect;
    first_menu->anim_flags = anim_flags_;
    first_menu->anim_speed(speed);
    first_menu->widget_ = this;
    MenuWindow *win = first_menu;

    int oY = Y-win->ypos(state->indexes[menustate.level])+win->ypos(0);
    first_menu->ox = X; first_menu->oy = oY;
    win->position(X, oY);
    win->selected_ = menustate.indexes[menustate.level];

    // create submenus until we locate the one with selected item
    // in it, positioning them so that one is selected:
    for (;;) {

        if(state->indexes[menustate.level] < 0) break;
        Fl_Widget* widget = win->current_widget();
        if(!widget->takesevents()) break;
        if(!widget->is_group()) break;
        int item = ((Fl_Group*)widget)->focus();
        if(item < 0) break;

        int nX = win->x() + win->w();
        int nY = win->y() + win->ypos(menustate.indexes[menustate.level]) - win->ypos(0);

        menustate.level++;
        menustate.indexes[menustate.level] = item;
        menustate.indexes[menustate.level+1] = -1;

        MenuWindow *sub_win = new MenuWindow(win, widget, item, this, menustate.indexes, menustate.level);
        sub_win->position(X, Y-sub_win->ypos(menustate.indexes[menustate.level])+sub_win->ypos(0));
        sub_win->selected_ = menustate.indexes[menustate.level];

        // move all earlier menus to line up with this new one:
        int dy = sub_win->y()-nY;
        int dx = sub_win->x()-nX;
        for(MenuWindow *t=first_menu; t!=0; t=t->child_win) {
            int nx = t->x()+dx; if(nx < 0) {nx = 0; dx = -t->x();}
            int ny = t->y()+dy; if(ny < 0) {ny = 0; dy = -t->y();}
            t->position(nx, ny);
        }

        win->child_win = sub_win;
        win = sub_win;
    }

    Fl_Widget* saved_modal = Fl::modal();
    bool saved_grab = Fl::grab();

    for(Fl::modal(first_menu, MODAL); !Fl::exit_modal_flag(); Fl::wait())
    {
        //Show window, after entered MODAL loop, so window can events while animating
        if(!first_menu->shown()) {
            MenuWindow *t=first_menu;
            while(t->child_win) {
                // No effects for already up menus
                t->effect = FL_EFFECT_NONE;
                t->show();
                t = t->child_win;
            }
            t->show(Fl::first_window());
            Fl::add_timeout(0.5f, timeout_initial);
        }
    }

    delete first_menu;

    Fl::modal(saved_modal, saved_grab);
    Fl::remove_timeout(timeout_open_childwin, state);
    Fl::remove_timeout(timeout_close_childwin, state);
    Fl::remove_timeout(timeout_initial);

    state = saved_state;
    first_menu = saved_first;
    current_menu = saved_current;

    if(menustate.state != DONE_STATE) return false;

    // Execute whatever item the user picked:
    focus(menustate.indexes, menustate.level);
    execute(item());

    return true;
}

//
// End of "$Id$".
//
