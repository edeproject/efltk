//
// "$Id$"
//
// Copyright Mark Edel.  Permission to distribute under the LGPL for
// the FLTK library granted by Mark Edel.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//
#include <config.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Text_Editor.h>
#include <efltk/Fl_Style.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <efltk/Fl_Menu_Button.h>

static Fl_Text_Editor *menu_widget=0;
static Fl_Menu_ menu;
static Fl_Menu_ *menu_ = &menu;

#define CUT   1
#define COPY  2
#define PASTE 3

static void cb_menu(Fl_Widget *w, void *d)
{
    if(!menu_widget) return;
    char *selection = 0;
    switch((int)d) {
    case COPY:
        selection = (char *)menu_widget->buffer()->selection_text();
        if(*selection) {
            Fl::copy(selection, strlen(selection), true);
        }
        delete []selection;
        break;
    case CUT:
        selection = (char *)menu_widget->buffer()->selection_text();
        if(*selection) {
            Fl::copy(selection, strlen(selection), true);
            menu_widget->buffer()->remove_selection();
        }
        delete []selection;
        break;
    case PASTE:
        Fl::paste(*menu_widget, true);
        break;
    default:
        break;
    };
}

static void revert(Fl_Style *s) {
	s->text_font = FL_COURIER;
    s->box = FL_DOWN_BOX;
    s->color = FL_WHITE;
    s->button_box = FL_BORDER_BOX;
    s->button_color = FL_GRAY;  
}

static Fl_Named_Style style("Text_Editor", revert, &Fl_Text_Editor::default_style);
Fl_Named_Style* Fl_Text_Editor::default_style = &::style;

Fl_Text_Editor::Fl_Text_Editor(int X, int Y, int W, int H,  const char* l)
: Fl_Text_Display(X, Y, W, H, l)
{
    static bool menuinit=false;
    if(!menuinit) {
        if(menu_->parent()) menu_->parent()->remove(menu_);
        menu_->type(Fl_Menu_Button::POPUP3); //HACK! :)
        menu_->add("Cut", 0, cb_menu, (void *)CUT);
        menu_->add("Copy", 0, cb_menu, (void *)COPY);
        menu_->add("Paste", 0, cb_menu, (void *)PASTE);
        menuinit=true;
    }

    style(default_style);
    mCursorOn = 1;
    insert_mode_ = 1;
    key_bindings = 0;

    // handle the default key bindings
    add_default_key_bindings(&key_bindings);

    // handle everything else
    default_key_function(kf_default);
}


Fl_Text_Editor::Key_Binding* Fl_Text_Editor::global_key_bindings = 0;

static int ctrl_a(int, Fl_Text_Editor* e);

// These are the default key bindings every widget should start with
static struct
{
    int key;
    int state;
    Fl_Text_Editor::Key_Func func;
}

default_key_bindings[] =
{
    //{ FL_Escape,    FL_TEXT_EDITOR_ANY_STATE, Fl_Text_Editor::kf_ignore     },
    { FL_Enter,     FL_TEXT_EDITOR_ANY_STATE, Fl_Text_Editor::kf_enter      },
    { FL_KP_Enter,  FL_TEXT_EDITOR_ANY_STATE, Fl_Text_Editor::kf_enter      },
    { FL_BackSpace, FL_TEXT_EDITOR_ANY_STATE, Fl_Text_Editor::kf_backspace  },
    { FL_Insert,    0, Fl_Text_Editor::kf_insert     },
    { FL_Delete,    0, Fl_Text_Editor::kf_delete     },
    { FL_Home,      0,                        Fl_Text_Editor::kf_move       },
    { FL_End,       0,                        Fl_Text_Editor::kf_move       },
    { FL_Left,      0,                        Fl_Text_Editor::kf_move       },
    { FL_Up,        0,                        Fl_Text_Editor::kf_move       },
    { FL_Right,     0,                        Fl_Text_Editor::kf_move       },
    { FL_Down,      0,                        Fl_Text_Editor::kf_move       },
    { FL_Page_Up,   0,                        Fl_Text_Editor::kf_move       },
    { FL_Page_Down, 0,                        Fl_Text_Editor::kf_move       },
    { FL_Home,      FL_SHIFT,                 Fl_Text_Editor::kf_shift_move },
    { FL_End,       FL_SHIFT,                 Fl_Text_Editor::kf_shift_move },
    { FL_Left,      FL_SHIFT,                 Fl_Text_Editor::kf_shift_move },
    { FL_Up,        FL_SHIFT,                 Fl_Text_Editor::kf_shift_move },
    { FL_Right,     FL_SHIFT,                 Fl_Text_Editor::kf_shift_move },
    { FL_Down,      FL_SHIFT,                 Fl_Text_Editor::kf_shift_move },
    { FL_Page_Up,   FL_SHIFT,                 Fl_Text_Editor::kf_shift_move },
    { FL_Page_Down, FL_SHIFT,                 Fl_Text_Editor::kf_shift_move },
    { FL_Home,      FL_CTRL,                  Fl_Text_Editor::kf_ctrl_move  },
    { FL_End,       FL_CTRL,                  Fl_Text_Editor::kf_ctrl_move  },
    { FL_Left,      FL_CTRL,                  Fl_Text_Editor::kf_ctrl_move  },
    { FL_Up,        FL_CTRL,                  Fl_Text_Editor::kf_ctrl_move  },
    { FL_Right,     FL_CTRL,                  Fl_Text_Editor::kf_ctrl_move  },
    { FL_Down,      FL_CTRL,                  Fl_Text_Editor::kf_ctrl_move  },
    { FL_Page_Up,   FL_CTRL,                  Fl_Text_Editor::kf_ctrl_move  },
    { FL_Page_Down, FL_CTRL,                  Fl_Text_Editor::kf_ctrl_move  },
    { FL_Home,      FL_CTRL|FL_SHIFT,         Fl_Text_Editor::kf_c_s_move   },
    { FL_End,       FL_CTRL|FL_SHIFT,         Fl_Text_Editor::kf_c_s_move   },
    { FL_Left,      FL_CTRL|FL_SHIFT,         Fl_Text_Editor::kf_c_s_move   },
    { FL_Up,        FL_CTRL|FL_SHIFT,         Fl_Text_Editor::kf_c_s_move   },
    { FL_Right,     FL_CTRL|FL_SHIFT,         Fl_Text_Editor::kf_c_s_move   },
    { FL_Down,      FL_CTRL|FL_SHIFT,         Fl_Text_Editor::kf_c_s_move   },
    { FL_Page_Up,   FL_CTRL|FL_SHIFT,         Fl_Text_Editor::kf_c_s_move   },
    { FL_Page_Down, FL_CTRL|FL_SHIFT,         Fl_Text_Editor::kf_c_s_move   },
    { 'a',          FL_CTRL,                  ctrl_a                        },
    //{ 'z',          FL_CTRL,                  Fl_Text_Editor::undo	  },
    { FL_Insert,    FL_SHIFT,                 Fl_Text_Editor::kf_paste      },
    { FL_Delete,    FL_SHIFT,                 Fl_Text_Editor::kf_cut        },
    { 'z',          FL_CTRL,                  Fl_Text_Editor::kf_undo        },
    { 'x',          FL_CTRL,                  Fl_Text_Editor::kf_cut        },
    { 'c',          FL_CTRL,                  Fl_Text_Editor::kf_copy       },
	{ FL_Insert,    FL_CTRL,                  Fl_Text_Editor::kf_copy       },
    { 'v',          FL_CTRL,                  Fl_Text_Editor::kf_paste      },	
    { 0,            0,                        0                             }
};

#if HAVE_XUTF8
static int utf_len(char c)
{
  if (!(c & 0x80)) return 1;
  if (c & 0x40) {
    if (c & 0x20) {
      if (c & 0x10) {
        if (c & 0x08) {
          if (c & 0x04) {
            return 6;
          }
          return 5;
        }
        return 4;
      }
      return 3;
    }
    return 2;
  }
  return 0;
}
#endif

void Fl_Text_Editor::add_default_key_bindings(Key_Binding** list)
{
    for (int i = 0; default_key_bindings[i].key; i++)
    {
        add_key_binding(default_key_bindings[i].key,
            default_key_bindings[i].state,
            default_key_bindings[i].func,
            list);
    }
}

void Fl_Text_Editor::insert(const char* text)
{
    int textLen = strlen( text );
    int startPos = insert_position();
    buffer()->add_undo(text, startPos, textLen, true, false);

    Fl_Text_Display::insert(text);
}

void Fl_Text_Editor::overstrike(const char* text)
{
    int textLen = strlen( text );
    int startPos = insert_position();
    char *txt = (char*)buffer()->text_range(startPos, startPos+textLen);
    buffer()->add_undo(txt, startPos, textLen, false, true);
    delete []txt;

    Fl_Text_Display::overstrike(text);
}

static void kill_selection(Fl_Text_Editor* e)
{
    if (e->buffer()->selected())
    {
        e->insert_position(e->buffer()->primary_selection()->start());

        char *text = (char*)e->buffer()->selection_text();
        int textLen = strlen( text );
        int startPos = e->insert_position();
        e->buffer()->add_undo(text, startPos, textLen, false, false);
        delete []text;

        e->buffer()->remove_selection();
    }
}


// Any keys not in above table go to this:

int Fl_Text_Editor::kf_default(int c, Fl_Text_Editor* e)
{

    // See if the key is a shortcut assigned to some other widget or menu item:
    static bool recursion;
    if (!recursion)
    {
        recursion = true;
        bool ret = Fl::handle(FL_SHORTCUT, e->window()) != 0;
        recursion = false;
        if (ret) return 1;
    }

    // Emulate Emacs for a lot of keys:
    int key = 0;
    switch (c)
    {
        case 'b': key = FL_Left; goto MOVE;
        case 'f': key = FL_Right; goto MOVE;
        case 'p': key = FL_Up; goto MOVE;
        case 'n': key = FL_Down; goto MOVE;
        case 'e': key = FL_End; goto MOVE;
        MOVE:
        if (Fl::event_state(FL_ALT))
        {
            if (Fl::event_state(FL_SHIFT))
                return Fl_Text_Editor::kf_c_s_move(key,e);
            else
                return Fl_Text_Editor::kf_ctrl_move(key,e);
        }
        else
        {
            if (Fl::event_state(FL_SHIFT))
                return Fl_Text_Editor::kf_shift_move(key,e);
            else
                return Fl_Text_Editor::kf_move(key,e);
        }
        case 'd':
            return Fl_Text_Editor::kf_delete(c,e);
        case 'h':
            return Fl_Text_Editor::kf_backspace(c,e);
            //case 'k':
            //  return Fl_Text_Editor::delete_to_eol(c,e);
            //case 'o':
            //  return Fl_Text_Editor::open_line(c,e);
            //case 'q':
            //  return Fl_Text_Editor::quote_next(c,e);
            //case 'r':
            //  return Fl_Text_Editor::reverse_search(c,e);
            //case 's':
            //  return Fl_Text_Editor::search(c,e);
            //case 't':
            //  return Fl_Text_Editor::transpose_chars(c,e);
            //case 'u':
            //  return Fl_Text_Editor::repeat prefix(c,e);
        case 'w':
            return Fl_Text_Editor::kf_cut(c,e);
        case 'y':
            return Fl_Text_Editor::kf_paste(c,e);
            //case '/':
            //  return Fl_Text_Editor::undo(c,e);
    }

    // insert other control characters into the text:
    if (Fl::event_length())
    {
        kill_selection(e);
        if (e->insert_mode()) e->insert(Fl::event_text());
        else e->overstrike(Fl::event_text());
        e->show_insert_position();
        return 1;
    }
    return 0;
}


Fl_Text_Editor::Key_Func
Fl_Text_Editor::bound_key_function(int key, int state, Key_Binding* list)
{
    Key_Binding* current;
    for (current = list; current; current = current->next)
        if (current->key == key)
            if (current->state == FL_TEXT_EDITOR_ANY_STATE || current->state == state)
                break;
    if (!current) return 0;
    return current->function;
}


void
Fl_Text_Editor::remove_all_key_bindings(Key_Binding** list)
{
    Key_Binding *current, *next;
    for (current = *list; current; current = next)
    {
        next = current->next;
        delete current;
    }
    *list = 0;
}


void
Fl_Text_Editor::remove_key_binding(int key, int state, Key_Binding** list)
{
    Key_Binding *current, *last = 0;
    for (current = *list; current; last = current, current = current->next)
        if (current->key == key && current->state == state) break;
    if (!current) return;
    if (last) last->next = current->next;
    else *list = current->next;
    delete current;
}


void
Fl_Text_Editor::add_key_binding(int key, int state, Key_Func function,
Key_Binding** list)
{
    Key_Binding* kb = new Key_Binding;
    kb->key = key;
    kb->state = state;
    kb->function = function;
    kb->next = *list;
    *list = kb;
}


////////////////////////////////////////////////////////////////

#define NORMAL_INPUT_MOVE 0

int Fl_Text_Editor::kf_ignore(int, Fl_Text_Editor*)
{
    return 0;                    // don't handle
}


int Fl_Text_Editor::kf_backspace(int, Fl_Text_Editor* e)
{
    if (!e->buffer()->selected() && e->move_left()) {
#if HAVE_XUTF8    
	int l = 1;
        char c = e->buffer()->character(e->insert_position());
        if (c & 0x80 && c & 0x40) {
    	    l = utf_len(c);
	} 
	e->buffer()->select(e->insert_position(), e->insert_position()+l);
#else
        e->buffer()->select(e->insert_position(), e->insert_position()+1);
#endif	
    }	
    kill_selection(e);
    e->show_insert_position();
    return 1;
}


int Fl_Text_Editor::kf_enter(int, Fl_Text_Editor* e)
{
    if (e->when() & FL_WHEN_ENTER_KEY) {
        e->do_callback();
	
    }

    kill_selection(e);
    e->insert("\n");
    e->show_insert_position();
    return 1;
}


extern void fl_text_drag_me(int pos, Fl_Text_Display* d);

int Fl_Text_Editor::kf_move(int c, Fl_Text_Editor* e)
{
    int vis_lines = e->mNVisibleLines-1;
    int selected = e->buffer()->selected();
    if (!selected)
        e->dragPos = e->insert_position();
    e->buffer()->unselect();

    switch (c)
    {
        case FL_Home:
            e->insert_position(e->line_start(e->insert_position()));
            break;
        case FL_End:
            e->insert_position(e->line_end(e->insert_position(), false));
            break;
        case FL_Left:
            e->move_left();
            break;
        case FL_Right:
            e->move_right();
            break;
        case FL_Up:
            e->move_up();
            break;
        case FL_Down:
            e->move_down();
            break;
        case FL_Page_Up:
            e->move_up(vis_lines);
            break;
        case FL_Page_Down:
            e->move_down(vis_lines);
            break;
    }
    e->show_insert_position();
    return 1;
}


int Fl_Text_Editor::kf_shift_move(int c, Fl_Text_Editor* e)
{
    kf_move(c, e);
    fl_text_drag_me(e->insert_position(), e);
    return 1;
}


int Fl_Text_Editor::kf_ctrl_move(int c, Fl_Text_Editor* e)
{
    if (!e->buffer()->selected())
        e->dragPos = e->insert_position();
    if (c != FL_Up && c != FL_Down)
    {
        e->buffer()->unselect();
        e->show_insert_position();
    }
    switch (c)
    {
        case FL_Home:
            e->insert_position(0);
            break;
        case FL_End:
            e->insert_position(e->buffer()->length());
            break;
        case FL_Left:
            e->previous_word();
            break;
        case FL_Right:
            e->next_word();
            break;
        case FL_Up:
            e->scroll(e->mTopLineNum-1, e->mHorizOffset);
            break;
        case FL_Down:
            e->scroll(e->mTopLineNum+1, e->mHorizOffset);
            break;
        case FL_Page_Up:
            e->insert_position(e->mLineStarts[0]);
            break;
        case FL_Page_Down:
            e->insert_position(e->mLineStarts[e->mNVisibleLines-2]);
            break;
    }
    return 1;
}


int Fl_Text_Editor::kf_c_s_move(int c, Fl_Text_Editor* e)
{
    kf_ctrl_move(c, e);
    fl_text_drag_me(e->insert_position(), e);
    return 1;
}


static int ctrl_a(int, Fl_Text_Editor* e)
{
    // make 2+ ^A's in a row toggle select-all:
    int i = e->buffer()->line_start(e->insert_position());
    if (i != e->insert_position())
        return Fl_Text_Editor::kf_move(FL_Home, e);
    else
    {
        if (e->buffer()->selected())
            e->buffer()->unselect();
        else
            Fl_Text_Editor::kf_select_all(0, e);
    }
    return 1;
}


int Fl_Text_Editor::kf_home(int, Fl_Text_Editor* e)
{
    return kf_move(FL_Home, e);
}


int Fl_Text_Editor::kf_end(int, Fl_Text_Editor* e)
{
    return kf_move(FL_End, e);
}


int Fl_Text_Editor::kf_left(int, Fl_Text_Editor* e)
{
    return kf_move(FL_Left, e);
}


int Fl_Text_Editor::kf_up(int, Fl_Text_Editor* e)
{
    return kf_move(FL_Up, e);
}


int Fl_Text_Editor::kf_right(int, Fl_Text_Editor* e)
{
    return kf_move(FL_Right, e);
}


int Fl_Text_Editor::kf_down(int, Fl_Text_Editor* e)
{
    return kf_move(FL_Down, e);
}


int Fl_Text_Editor::kf_page_up(int, Fl_Text_Editor* e)
{
    return kf_move(FL_Page_Up, e);
}


int Fl_Text_Editor::kf_page_down(int, Fl_Text_Editor* e)
{
    return kf_move(FL_Page_Down, e);
}


int Fl_Text_Editor::kf_insert(int, Fl_Text_Editor* e)
{
    e->insert_mode(e->insert_mode() ? 0 : 1);
    return 1;
}


int Fl_Text_Editor::kf_delete(int, Fl_Text_Editor* e)
{
    if (!e->buffer()->selected()) {
#if HAVE_XUTF8    
        int l = 1;
	char c = e->buffer()->character(e->insert_position());
        if (c & 0x80 && c & 0x40) {
	    l = utf_len(c);
	} 
	e->buffer()->select(e->insert_position(), e->insert_position()+l);
#else
        e->buffer()->select(e->insert_position(), e->insert_position()+1);
#endif	
    }	
    kill_selection(e);
    e->show_insert_position();
    return 1;
}


int Fl_Text_Editor::kf_copy(int, Fl_Text_Editor* e)
{
    if (!e->buffer()->selected()) return 1;
    char *copy = (char *)e->buffer()->selection_text();
    if (*copy) Fl::copy(copy, strlen(copy), true);
    delete []copy;
    e->show_insert_position();
    return 1;
}


int Fl_Text_Editor::kf_cut(int c, Fl_Text_Editor* e)
{
    kf_copy(c, e);
    kill_selection(e);
    return 1;
}

int Fl_Text_Editor::kf_undo(int c, Fl_Text_Editor* e)
{
    int pos = e->buffer()->undo();
    if(pos>-1) {
        e->insert_position(pos);
        e->show_insert_position();
        if(e->when()&FL_WHEN_CHANGED) e->do_callback(); else e->set_changed();
    }
    return 1;
}

int Fl_Text_Editor::kf_paste(int, Fl_Text_Editor* e)
{
    kill_selection(e);
    Fl::paste(*e,true);
    e->show_insert_position();
    return 1;
}


int Fl_Text_Editor::kf_select_all(int, Fl_Text_Editor* e)
{
    e->buffer()->select(0, e->buffer()->length());
    return 1;
}

int Fl_Text_Editor::handle_key()
{
    if(when()&FL_WHEN_CHANGED) do_callback(); else set_changed();

    // Call fltk's rules to try to turn this into a printing character.
    // This uses the right-hand ctrl key as a "compose prefix" and returns
    // the changes that should be made to the text, as a number of
    // bytes to delete and a string to insert:
    int del;
    int key = Fl::event_key();
    if (Fl::compose(del) && key < FL_BackSpace)
    {
        if (del) buffer()->select(insert_position()-del, insert_position());
        kill_selection(this);
        if (Fl::event_length())
        {
            if (insert_mode()) insert(Fl::event_text());
            else overstrike(Fl::event_text());
        }
        show_insert_position();
        return 1;
    }

    if (key >= FL_Shift_L && key <= FL_Meta_R) {
       //puts ("Modifier pressed");
       return false;
    }

    int state = Fl::event_state() & (FL_SHIFT|FL_CTRL|FL_ALT|FL_WIN);
    Key_Func f = bound_key_function(key, state, global_key_bindings);
    if (!f) f = bound_key_function(key, state, key_bindings);
    if (!f) f = default_key_function_;
    if (!f) f = kf_default;
    return f(key, this);
}


int Fl_Text_Editor::handle(int event)
{
    if (!buffer()) return 0;

    if (Fl_Text_Display::handle(event))
    {
        switch (event)
        {
        case FL_PUSH:
            if (Fl::event_button() == 2)
            {
                dragType = -1;
                Fl::paste(*this,false);
            } else if(Fl::event_button()==3) {
                char *selection = (char *)buffer()->selection_text();
                if(!*selection) {
                    menu_->find("Cut")->deactivate();
                    menu_->find("Copy")->deactivate();
                } else {
                    menu_->find("Cut")->activate();
                    menu_->find("Copy")->activate();
                }
                delete []selection;
                menu_widget = this;
                menu_->popup(Fl::event_x(), Fl::event_y());
                menu_widget = 0;
            }
            return 1;

        case FL_FOCUS:
            return 3;        // indicate that this widget should get initial focus

        case FL_UNFOCUS:
	    if (when() & FL_WHEN_RELEASE) do_callback();
            return 1;

        default:
            return 1;
        }
    }
    else
    {
        switch (event)
        {
        case FL_HIDE:
            if (when() & FL_WHEN_RELEASE) do_callback();
	    
            return 1;

        case FL_KEY:
            return handle_key();

        case FL_PASTE:
            if(!Fl::event_length() || !Fl::event_text()) return 0;

            if(when()&FL_WHEN_CHANGED) do_callback(); else set_changed();

            buffer()->remove_selection();
            if (insert_mode()) insert(Fl::event_text());
            else overstrike(Fl::event_text());
            show_insert_position();
            return 1;

            // CET - FIXME - this will clobber the window's current cursor state!
            //    case FL_ENTER:
            //    case FL_MOVE:
            //    case FL_LEAVE:
            //      if (Fl::event_inside(text_area)) fl_cursor(FL_CURSOR_INSERT);
            //      else fl_cursor(FL_CURSOR_DEFAULT);
        }
        return 0;
    }
}


//
// End of "$Id$".
//
