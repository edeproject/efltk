/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_TEXT_EDITOR_H_
#define _FL_TEXT_EDITOR_H_

#include "Fl_Text_Display.h"

// key will match in any state
#define FL_TEXT_EDITOR_ANY_STATE  (-1L)

/** Fl_Text_Editor */
class FL_API Fl_Text_Editor : public Fl_Text_Display {
public:
    typedef int (*Key_Func)(int key, Fl_Text_Editor* editor);

    struct FL_API Key_Binding {
        int          key;
        int          state;
        Key_Func     function;
        Key_Binding* next;
    };

    /** Creates new text editor widget using the given position, size, and label string. */
    Fl_Text_Editor(int X, int Y, int W, int H, const char* l = 0);

    /** Creates new input widget using the label, size, alignment, and label width. */
    Fl_Text_Editor(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=-1);

    /** Destructor */
    ~Fl_Text_Editor() { remove_all_key_bindings(); }

    static Fl_Named_Style* default_style;
    virtual int handle(int e);
    void insert_mode(int b) { insert_mode_ = b; }
    int insert_mode() { return insert_mode_; }

    void add_key_binding(int key, int state, Key_Func f, Key_Binding** list);
    void add_key_binding(int key, int state, Key_Func f)
    { add_key_binding(key, state, f, &key_bindings); }
    void remove_key_binding(int key, int state, Key_Binding** list);
    void remove_key_binding(int key, int state)
    { remove_key_binding(key, state, &key_bindings); }
    void remove_all_key_bindings(Key_Binding** list);
    void remove_all_key_bindings() { remove_all_key_bindings(&key_bindings); }
    void add_default_key_bindings(Key_Binding** list);
    Key_Func bound_key_function(int key, int state, Key_Binding* list);
    Key_Func bound_key_function(int key, int state)
    { return bound_key_function(key, state, key_bindings); }
    void default_key_function(Key_Func f) { default_key_function_ = f; }

    // functions for the built in default bindings
    static int kf_default(int c, Fl_Text_Editor* e);
    static int kf_ignore(int c, Fl_Text_Editor* e);
    static int kf_backspace(int c, Fl_Text_Editor* e);
    static int kf_enter(int c, Fl_Text_Editor* e);
    static int kf_move(int c, Fl_Text_Editor* e);
    static int kf_shift_move(int c, Fl_Text_Editor* e);
    static int kf_ctrl_move(int c, Fl_Text_Editor* e);
    static int kf_c_s_move(int c, Fl_Text_Editor* e);
    static int kf_home(int, Fl_Text_Editor* e);
    static int kf_end(int c, Fl_Text_Editor* e);
    static int kf_left(int c, Fl_Text_Editor* e);
    static int kf_up(int c, Fl_Text_Editor* e);
    static int kf_right(int c, Fl_Text_Editor* e);
    static int kf_down(int c, Fl_Text_Editor* e);
    static int kf_page_up(int c, Fl_Text_Editor* e);
    static int kf_page_down(int c, Fl_Text_Editor* e);
    static int kf_insert(int c, Fl_Text_Editor* e);
    static int kf_delete(int c, Fl_Text_Editor* e);
    static int kf_copy(int c, Fl_Text_Editor* e);
    static int kf_cut(int c, Fl_Text_Editor* e);
    static int kf_undo(int c, Fl_Text_Editor* e);
    static int kf_paste(int c, Fl_Text_Editor* e);
    static int kf_select_all(int c, Fl_Text_Editor* e);

    void insert(const char* text);
    void overstrike(const char* text);

protected:
    int handle_key();
    int insert_mode_;
    Key_Binding* key_bindings;
    static Key_Binding* global_key_bindings;
    Key_Func default_key_function_;
private:
    void ctor_init();
};

#endif
