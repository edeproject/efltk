#ifndef FL_LISTVIEW_H_
#define FL_LISTVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fl.h"
#include "Fl_Group.h"
#include "Fl_Widget_List.h"
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
    ~Fl_ListHeader();

    virtual void clear();
	
	void columns(int count);
	uint columns();

    void add_column(const char *name, int w);
    int width(int col);
    void width(int col, int w);
    
    Fl_Flags column_flags(int col, int f);
    Fl_Flags column_flags(int col);
    Fl_Flags column_set_flag(int col, int f);
    Fl_Flags column_clear_flag(int col, int f);
    Fl_Flags column_invert_flag(int col, int f);

    const char *label();
    const char *label(int col);
    void label(int col, const char *text);
	void copy_label(int col, const char *txt);

    Fl_Font label_font(int col);
	int label_size(int col);
	void label_size(int col, int size);
    void label_font(int col, Fl_Font font);
    void label_color(int col, Fl_Color color);

    void image(int col, Fl_Image *im);
    void image(int col, Fl_Image &im);
    Fl_Image *image(int col);

    virtual void draw();
    virtual void layout();
    virtual int handle(int ev);

protected:
    int sort_type;
    int sort_col;
	Fl_Ptr_List attr_list;

	typedef struct {
		const char *label;
		Fl_Flags flags;
		int width;
		Fl_Font font;
		int font_size;
		Fl_Color color;
		Fl_Image *image;
	} attr;
	void add_attr(int col);	
};

class Fl_ListView : public Fl_Group {
public:
    static Fl_Named_Style* default_style;

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

    enum {
        SORT_ASC = 0,
        SORT_DESC,
        SORT_UNKNOWN
    };

    Fl_ListView(int X,int Y,int W,int H,const char*l=0);
    ~Fl_ListView();

    bool draw_stripes() { return draw_stripes_; }
    void draw_stripes(bool v) { draw_stripes_ = v; }

    Fl_ListHeader *header() { return _header; }
    void header(Fl_ListHeader *h) { _header = h; }

    void add_column(const char *name, int w=-1) { _header->add_column(name, w); if(w<0) find_def=true; }
    int columns() { return _header->columns(); }
    void columns(int cnt) { _header->columns(cnt); }

    int column_width(int c) { return _header->width(c); }
    void column_width(int c, int w) { _header->width(c, w); if(w<0) find_def=true; }

    const char *column_name(int c) { return _header->label(c); }
    void column_name(int c, const char *name) { _header->copy_label(c, name); }

    int column_flags(int c) { return _header->column_flags(c); }
    void column_flags(int c, int f) { _header->column_flags(c,f); }

    Fl_Image *column_image(int c) { return _header->image(c); }
    void column_image(int c, Fl_Image *im) { _header->image(c, im); }
    void column_image(int c, Fl_Image &im) { _header->image(c, im); }

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
    bool show_item(Fl_Widget *w);

    Fl_Widget* next();
    Fl_Widget* prev();

    void damage_item(Fl_Widget *i); // make this item redraw

    void scroll_up(int pixels = 20);
    void scroll_down(int pixels = 20);

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

    // Virtual functions
	virtual void add(Fl_Widget &);
    virtual void clear();
    virtual void remove(int index);
    void remove(Fl_Widget& o) { int w = Fl_Group::find(o);  remove(w);}
    void remove(Fl_Widget* o) { int w = Fl_Group::find(*o); remove(w);}

    virtual int handle(int ev);
    virtual void layout();
    virtual void layout_scrollbars();

    virtual void draw();
    virtual void draw_header();
    virtual void draw_row(int x, int y, int w, int h, Fl_Widget *widget, bool selected);

	// Finds default sizes for columns, which has width=-1
	virtual void find_default_sizes();

    // Returns sort mode: ASC,DESC,UNKNOWN
    virtual int sort(int column);
    int sort_type() { return sort_type_; }

    Fl_Widget_List &get_selection() { return selection; }
	
    Fl_Scrollbar vscrollbar;
    Fl_Scrollbar hscrollbar;

protected:
    static void hscrollbar_cb(Fl_Widget*, void*);
    static void vscrollbar_cb(Fl_Widget*, void*);

	void calc_index();

    Fl_ListHeader head; //Default header
    Fl_ListHeader *_header; //Pointer to current header

    Fl_Widget *item_;      // Current item

	bool calc_total_h;
	int first_vis;

    int total_height;
    int yposition_, xposition_;
    int scrolldy, scrolldx;

    void draw_item(Fl_Widget *);
    void draw_clip(int,int,int,int);
    static void draw_clip_cb(void*,int,int,int,int);

    Fl_Widget_List selection;

    int X,Y,W,H; //box
    int HX,HY,HW,HH; //header box

    bool draw_stripes_;
    bool find_def; // Set when needs to find default colmn sizes (called by layout)    

    int sort_type_;
};

#endif

