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

#ifndef _FL_BROWSER_H_
#define _FL_BROWSER_H_

#include "Fl_Menu_.h"
#include "Fl_Scrollbar.h"

/** Fl_Browser */
class FL_API Fl_Browser : public Fl_Menu_ {
    Fl_End endgroup;
    void ctor_init();
public:

    static Fl_Named_Style* default_style;

    Fl_Browser(int X,int Y,int W,int H,const char*l=0);
    Fl_Browser(const char* l = 0,int layout_size=20,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);
    ~Fl_Browser();

    enum { // values for type()
        NORMAL = 0,
        MULTI = 1
    };
    bool multi() const { return (type()&MULTI); }

    virtual int handle(int);
    virtual void layout();
    virtual void draw();

    int max_width() const  { return max_width_; }
    int max_height() const { return max_height_; }

    int xposition() const { return xposition_; }
    void xposition(int);
    int yposition() const { return yposition_; }
    void yposition(int);

    bool indented() const { return indented_; }
    void indented(bool v) { indented_ = v; }

    Fl_Scrollbar scrollbar;
    Fl_Scrollbar hscrollbar;

    Fl_Widget* goto_top();
    Fl_Widget* goto_focus() {return goto_mark(FOCUS);}
    Fl_Widget* goto_position(int y);
    Fl_Widget* goto_index(const int* indexes, int level);
    Fl_Widget* goto_index(int);
    Fl_Widget* goto_index(int,int,int=-1,int=-1,int=-1);
    Fl_Widget* next();
    Fl_Widget* next_visible();
    Fl_Widget* previous_visible();
    bool item_is_visible() const;
    bool item_is_parent() const;

    bool set_focus();
    bool set_item_selected(bool value = true, Fl_Event_Type do_callback = FL_NO_EVENT);
    bool select_only_this(Fl_Event_Type do_callback = FL_NO_EVENT);
    bool deselect(Fl_Event_Type do_callback = FL_NO_EVENT);

    enum linepos { NOSCROLL, TOP, MIDDLE, BOTTOM };
    bool make_item_visible(linepos = NOSCROLL);
    void damage_item() { damage_item(HERE); }
    bool set_item_opened(bool);
    bool set_item_visible(bool);

    int current_level() const { return item_level[HERE]; }
    const int* current_index() const { return item_index[HERE]; }
    int current_position() const { return item_position[HERE]; }

    int focus_level() const { return item_level[FOCUS]; }
    const int* focus_index() const { return item_index[FOCUS]; }
    int focus_position() const { return item_position[FOCUS]; }
    void value(int v) { goto_index(v); set_focus(); }
    int value() const { return focus_index()[0]; }

    const int *column_widths() const { return column_widths_; }
    void column_widths(const int *pWidths)  { column_widths_ = pWidths; }

    // Convienence functions for flat browsers:
    bool select(int line, bool value = true);
    bool selected(int line);
    int topline() const {return item_index[FIRST_VISIBLE][0];}
    void topline(int line) {goto_index(line); make_item_visible(TOP);}
    void bottomline(int line) {goto_index(line); make_item_visible(BOTTOM);}
    void middleline(int line) {goto_index(line); make_item_visible();}
    bool displayed(int line);
    bool display(int line, bool value = true);

private:

    bool indented_;
    const int *column_widths_;
    int xposition_, yposition_;
    int max_width_, max_height_;
    int scrolldx, scrolldy;
    static void hscrollbar_cb(Fl_Widget*, void*);
    static void scrollbar_cb(Fl_Widget*, void*);
    void draw_item();
    void draw_clip(int,int,int,int);
    static void draw_clip_cb(void*,int,int,int,int);
    int X,Y,W,H; // bounding box area

    // Marks serve as "indexes" into the hierarchial browser. We probably
    // need to make some sort of public interface but I have not figured
    // it out completely.
    enum { // predefined marks
        HERE = 0, // current item, the one moved by all the calls
        FOCUS,
        FIRST_VISIBLE,
        REDRAW_0,
        REDRAW_1,
        TEMP,
        NUMMARKS
    };
    Fl_Widget* goto_mark(int mark); // set HERE to mark
    Fl_Widget* goto_visible_focus(); // set HERE to focus if visible
    void set_mark(int dest, int mark); // set dest to mark
    int compare_marks(int mark1, int mark2); // returns >0 if mark1 after mark2
    bool at_mark(int mark) { return !compare_marks(HERE,mark); }
    void unset_mark(int mark);  // makes mark have illegal value
    bool is_set(int mark);  // false if unset_mark was called
    void damage_item(int mark); // make this item redraw

    int siblings; // # of children of parent of HERE item

    // For each mark:
    unsigned char item_level[NUMMARKS]; // depth in hierarchy of the item
    unsigned char open_level[NUMMARKS]; // depth of highest closed parent
    int item_position[NUMMARKS]; // distance in pixels from top of browser
    int* item_index[NUMMARKS]; // indexes at each level of hierarchy
    int levels; // maximum depth of all items encountered so far
    void set_level(int); // increases levels by reallocating the arrays
};

#endif
