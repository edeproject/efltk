#ifndef FL_LISTVIEW_H_
#define FL_LISTVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fl.h"
#include "Fl_Group.h"
#include "Fl_PtrList.h"
#include "Fl_Image.h"
#include "Fl_Slider.h"
#include "Fl_Scrollbar.h"
#include "fl_draw.h"
#include "x.h"

#define MAX_COLUMNS 32

class Fl_ListHeader : public Fl_Widget
{
public:
    static Fl_Named_Style* default_style;

    Fl_ListHeader(int X,int Y,int W,int H,const char*l=0);

    void add_column(const char *name, int w) {
        ++cols;
        colw[cols-1] = w;
        coln[cols-1] = strdup(name);
    }
    int columns() { return cols; }

    int column_width(int c) { return colw[c]; }
    void column_width(int c, int w) { colw[c] = w; }

    const char *column_name(int c) { return coln[c]; }
    void column_name(int c, const char *name) { if(coln[c]) delete []coln[c]; coln[c] = strdup(name); redraw(); }

    int column_flags(int c) { return colf[c]; }
    void column_flags(int c, int f) { colf[c] = f; }

    Fl_Image *column_image(int c) { return coli[c]; }
    void column_image(int c, Fl_Image *im) { coli[c] = im; }

    void draw();
    void layout();
    int handle(int ev);

private:
    int cols;
    int colw[MAX_COLUMNS]; //widths
    int colf[MAX_COLUMNS]; //drawing flags
    char *coln[MAX_COLUMNS]; //labels
    Fl_Image *coli[MAX_COLUMNS]; //images
};

class Fl_ListView : public Fl_Group {
public:
    Fl_ListView(int X,int Y,int W,int H,const char*l=0);
    ~Fl_ListView();

    bool draw_stripes() { return draw_stripes_; }
    void draw_stripes(bool v) { draw_stripes_ = v; }

    Fl_ListHeader *header() { return _header; }
    void header(Fl_ListHeader *h) { _header = h; }

    void add_column(const char *name, int w=-1) { _header->add_column(name, w); if(w<0) find_def=true; }
    int columns() { return _header->columns(); }

    int column_width(int c) { return _header->column_width(c); }
    void column_width(int c, int w) { _header->column_width(c, w); if(w<0) find_def=true; }

    const char *column_name(int c) { return _header->column_name(c); }
    void column_name(int c, const char *name) { _header->column_name(c, name); }

    int column_flags(int c) { return _header->column_flags(c); }
    void column_flags(int c, int f) { _header->column_flags(c,f); }

    Fl_Image *column_image(int c) { return _header->column_image(c); }
    void column_image(int c, Fl_Image *im) { _header->column_image(c,im); }

    bool move()  { return ((type() & MOVE_SELECTION)==MOVE_SELECTION);  }
    bool multi() { return ((type() & MULTI_SELECTION)==MULTI_SELECTION); }
    bool single(){ return !(type() & MULTI_SELECTION);}

    int totalheight() { return total_height; }

    int	yposition() const {return yposition_;}
    void yposition(int Y);
    int	xposition() const {return xposition_;}
    void xposition(int X);

    Fl_Widget* top(); 						// move to top and set first item to current
    Fl_Widget* item_at(int Y);    // Return item at Y

    Fl_Widget *item(Fl_Widget *i) { return (item_ = i); }
    Fl_Widget *item() { return item_; }
    void show_item(Fl_Widget *w);

    Fl_Widget* next();
    Fl_Widget* prev();

    void damage_item(Fl_Widget *i); // make this item redraw

    void scroll_up(int pixels = 20);
    void scroll_down(int pixels = 20);

    void clear();
    void remove(int index);
    void remove(Fl_Widget& o) { int w = Fl_Group::find(o);  remove(w);}
    void remove(Fl_Widget* o) { int w = Fl_Group::find(*o); remove(w);}

    void sort_selection(); //Call this always before when new multiselection
    void moveselection_up(int dy);
    void moveselection_down(int dy);

    void clear_selection();
    void remove_selection();

    int select(Fl_Widget *w, int value = 1);
    int select_only(Fl_Widget *w);
    void select_items(int from, int to);

    int unselect_all();
    int selected() { return selection.count(); }

    enum { // values for type()
        HORIZONTAL = 1,
        VERTICAL = 2,
        BOTH = 3,
        ALWAYS_ON = 4,
        HORIZONTAL_ALWAYS = 5,
        VERTICAL_ALWAYS = 6,
        BOTH_ALWAYS = 7,

        MULTI_SELECTION = 8,
        MOVE_SELECTION  = 16
    };

    // Virtual functions
    virtual int handle(int ev);
    virtual void layout();
    virtual void layout_scrollbars();

    virtual void draw();
    virtual void draw_header();
    virtual void draw_row(int x, int y, int w, int h, Fl_Widget *widget);

    Fl_Image *bg_image() { return image_; }
    void bg_image(Fl_Image *i) { image_ = i; }

    Fl_PtrList<Fl_Widget> &get_selection() { return selection; }

    Fl_Scrollbar vscrollbar;
    Fl_Scrollbar hscrollbar;

    static Fl_Named_Style* default_style;

private:
    static void hscrollbar_cb(Fl_Widget*, void*);
    static void vscrollbar_cb(Fl_Widget*, void*);

    Fl_Image *image_, *scaled;
    bool draw_stripes_;
    bool find_def; // Set when needs to find default colmn sizes (called by layout)
    void find_def_sizes();

    Fl_ListHeader head; //Default header
    Fl_ListHeader *_header; //Pointer to current header

    Fl_Widget *item_;      // Current item

    int total_height;
    int yposition_, xposition_;
    int scrolldy, scrolldx;

    void draw_item(Fl_Widget *);
    void draw_clip(int,int,int,int);
    static void draw_clip_cb(void*,int,int,int,int);

    Fl_PtrList<Fl_Widget> selection;
    bool on_selection(int Y);

    // number of first visible item
    int first_vis;

    int X,Y,W,H; //box
    int HX,HY,HW,HH; //header box
};

#endif

