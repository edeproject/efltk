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

#ifndef _FL_LISTVIEW_H_
#define _FL_LISTVIEW_H_

#include "Fl_ListView_Header.h"
#include "Fl_ListView_Item.h"
#include "Fl_Group.h"
#include "Fl_Scrollbar.h"

/** Fl_ListView */
class Fl_ListView : public Fl_Group {
public:
    static Fl_Named_Style* default_style;
    static Fl_ListView *current;

    enum { // values for type()
        HORIZONTAL          = 1,
        VERTICAL            = 2,
        BOTH                = 3,
        ALWAYS_ON           = 4,
        HORIZONTAL_ALWAYS   = 5,
        VERTICAL_ALWAYS     = 6,
        BOTH_ALWAYS         = 7,
        MULTI_SELECTION     = 8,
        MOVE_SELECTION      = 16
    };

    enum {
        SORT_ABSOLUTE = 0,
        SORT_ASC,
        SORT_DESC,
        SORT_LAST_TYPE //number of last type
    };

    /** Creates new list view widget using the given position, size, and label string. */
    Fl_ListView(int X,int Y,int W,int H,const char*l=0);

    /** Creates list view box widget using the label, size, alignment, and label_width. */
    Fl_ListView(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    /** destructor */
    virtual ~Fl_ListView();

    virtual void begin();
    virtual void end();

    Fl_ListItem_List &array() { return items; }

    Fl_ListView_Item *find_userdata(void *data, uint start_index=0) const;
    Fl_ListView_Item *find_text(const char *text, uint column, uint start_index=0) const;

    Fl_ListView_Item *child(uint index) const { return items.item(index); }
    uint children() const { return items.size(); }
    virtual void clear();

    bool draw_stripes() const { return draw_stripes_; }
    void draw_stripes(bool v) { draw_stripes_ = v; }

    Fl_ListView_Header *header() const { return _header; }
    void header(Fl_ListView_Header *h) { _header = h; }

    void add_column(const char *name, int w=-1,int ctype=VAR_STRING) { _header->add_column(name, w, ctype); if(w<0) find_def=true; }
    int columns() const { return _header->columns(); }
    void columns(int cnt) { _header->columns(cnt); }

    int column_width(int c) const { return _header->column_width(c); }
    void column_width(int c, int w) { _header->column_width(c, w); if(w<0) find_def=true; }

    int column_type(int c) const { return _header->column_type(c); }
    void column_type(int c, int t) { _header->column_type(c, t); }

    const char *column_name(int c) const { return _header->column_label(c); }
    void column_name(int c, const char *name) { _header->column_copy_label(c, name); }

    int column_flags(int c) const { return _header->column_flags(c); }
    void column_flags(int c, int f) { _header->column_flags(c,f); }

    const Fl_Image *column_image(int c) const { return _header->column_image(c); }
    Fl_Image *column_image(int c) { return _header->column_image(c); }
    void column_image(int c, Fl_Image *im) { _header->column_image(c, im); }
    void column_image(int c, Fl_Image &im) { _header->column_image(c, im); }

    bool multi() const { return ((type() & MULTI_SELECTION)==MULTI_SELECTION); }
    void multi(bool val) { if(val) type(type()|MULTI_SELECTION); else type(type()&~MULTI_SELECTION); }

    bool move() const { return ((type() & MOVE_SELECTION)==MOVE_SELECTION); }
    void move(bool val) { if(val) type(type()|MOVE_SELECTION); else type(type()&~MOVE_SELECTION); }

    void recalc_totalheight() { calc_total_h = true; relayout(); }
    int totalheight() const { return total_height; }

    int yposition() const {return yposition_;}
    void yposition(int Y);
    int xposition() const {return xposition_;}
    void xposition(int X);

    Fl_ListView_Item* top();             // move to top and set first item to current
    Fl_ListView_Item* item_at(int Y) const;    // Return item at Y

    Fl_ListView_Item *item(Fl_ListView_Item *i) { return (item_ = i); }
    Fl_ListView_Item *item() const { return item_; }
    bool show_item(Fl_ListView_Item *w);

    Fl_ListView_Item* next();
    Fl_ListView_Item* prev();

    void damage_item(Fl_ListView_Item *i); // make this item redraw

    void scroll_up(int pixels = 20);
    void scroll_down(int pixels = 20);

    void sort_selection(); //Call this always before when new multiselection
    void moveselection_up(int dy);
    void moveselection_down(int dy);

    void clear_selection();
    void remove_selection();

    int select(Fl_ListView_Item *w, int value = 1);
    int select_only(Fl_ListView_Item *w);
    void select_items(int from, int to);

    int unselect_all();
    int selected() const { return selection.count(); }

    // Virtual functions
    virtual void insert(Fl_ListView_Item &, uint pos);
    virtual void add(Fl_ListView_Item &);
    virtual void fill(Fl_Data_Source &ds,Fl_String user_data_column_name="");
    virtual void remove(int index);
    void remove(Fl_ListView_Item& o) { int w = items.index_of(&o); remove(w);}
    void remove(Fl_ListView_Item* o) { int w = items.index_of(o); remove(w);}

    virtual int handle(int ev);
    virtual void layout();
    virtual void layout_scrollbars();

    virtual void draw();

    // Finds default sizes for columns, which has width=-1
    virtual void find_default_sizes();

    // Returns sort mode: ASC,DESC,UNKNOWN
    virtual int sort(int column);
    int sort_type() const { return sort_type_; }

    Fl_ListItem_List &get_selection() { return selection; }

    Fl_Scrollbar vscrollbar;
    Fl_Scrollbar hscrollbar;

protected:

    /** ctor initializer */
    void ctor_init();

    static void hscrollbar_cb(Fl_Widget*, void*);
    static void vscrollbar_cb(Fl_Widget*, void*);

    Fl_ListItem_List items;
    Fl_ListItem_List selection;

    Fl_ListView_Header head; //Default header
    Fl_ListView_Header *_header; //Pointer to current header

    Fl_ListView_Item *item_;      // Current item

    bool calc_total_h;
    int first_vis;

    int total_height;
    int yposition_, xposition_;
    int scrolldy, scrolldx;

    virtual void draw_header() const;
    virtual void draw_row(int x, int y, int w, int h, Fl_ListView_Item *widget, bool selected) const;
    void draw_item(Fl_ListView_Item *) const;
    void draw_clip(int,int,int,int) const;
    static void draw_clip_cb(void*,int,int,int,int);

    int X,Y,W,H; //box
    int HX,HY,HW,HH; //header box

    bool draw_stripes_;
    bool find_def; // Set when needs to find default colmn sizes (called by layout)

    int sort_type_;

    uint find_safe_top() const;
    Fl_Int_List m_ypos_lookup;
};

#endif
