#ifndef _FL_LISTVIEW_H_
#define _FL_LISTVIEW_H_

#include "Fl_ListView_Header.h"
#include "Fl_ListView_Item.h"
#include "Fl_Group.h"
#include "Fl_Scrollbar.h"

class Fl_ListView : public Fl_Group {
public:
    static Fl_Named_Style* default_style;
    static Fl_ListView *current;

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
        SORT_ABSOLUTE = 0,
        SORT_ASC,
        SORT_DESC,
        SORT_LAST_TYPE //number of last type
    };

    Fl_ListView(int X,int Y,int W,int H,const char*l=0);
    virtual ~Fl_ListView();

    void begin();
    void end();

	Fl_ListItem_List &array() { return items; }

    Fl_ListView_Item *find_userdata(void *data, uint start_index=0);
    Fl_ListView_Item *find_text(const char *text, uint column, uint start_index=0);

    Fl_ListView_Item *child(uint index) { return items.item(index); }
    uint children() { return items.size(); }
    virtual void clear();

    bool draw_stripes() { return draw_stripes_; }
    void draw_stripes(bool v) { draw_stripes_ = v; }

    Fl_ListView_Header *header() { return _header; }
    void header(Fl_ListView_Header *h) { _header = h; }

    void add_column(const char *name, int w=-1) { _header->add_column(name, w); if(w<0) find_def=true; }
    int columns() { return _header->columns(); }
    void columns(int cnt) { _header->columns(cnt); }

    int column_width(int c) { return _header->column_width(c); }
    void column_width(int c, int w) { _header->column_width(c, w); if(w<0) find_def=true; }

    const char *column_name(int c) { return _header->column_label(c); }
    void column_name(int c, const char *name) { _header->column_copy_label(c, name); }

    int column_flags(int c) { return _header->column_flags(c); }
    void column_flags(int c, int f) { _header->column_flags(c,f); }

    Fl_Image *column_image(int c) { return _header->column_image(c); }
    void column_image(int c, Fl_Image *im) { _header->column_image(c, im); }
    void column_image(int c, Fl_Image &im) { _header->column_image(c, im); }

    bool move()  { return ((type() & MOVE_SELECTION)==MOVE_SELECTION);  }
    bool multi() { return ((type() & MULTI_SELECTION)==MULTI_SELECTION); }
    bool single(){ return !(type() & MULTI_SELECTION);}

	void calc_totalheight() { calc_total_h = true; }
    int totalheight() { return total_height; }

    int	yposition() const {return yposition_;}
    void yposition(int Y);
    int	xposition() const {return xposition_;}
    void xposition(int X);

    Fl_ListView_Item* top();             // move to top and set first item to current
    Fl_ListView_Item* item_at(int Y);    // Return item at Y

    Fl_ListView_Item *item(Fl_ListView_Item *i) { return (item_ = i); }
    Fl_ListView_Item *item() { return item_; }
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
    int selected() { return selection.count(); }

    // Virtual functions
    virtual void insert(Fl_ListView_Item &, uint pos);
    virtual void add(Fl_ListView_Item &);
    virtual void fill(Fl_Data_Source &ds);
    virtual void remove(int index);
    void remove(Fl_ListView_Item& o) { int w = items.index_of(&o);  remove(w);}
    void remove(Fl_ListView_Item* o) { int w = items.index_of(o); remove(w);}

    virtual int handle(int ev);
    virtual void layout();
    virtual void layout_scrollbars();

    virtual void draw();
    virtual void draw_header();
    virtual void draw_row(int x, int y, int w, int h, Fl_ListView_Item *widget, bool selected);

    // Finds default sizes for columns, which has width=-1
    virtual void find_default_sizes();

    // Returns sort mode: ASC,DESC,UNKNOWN
    virtual int sort(int column);
    int sort_type() { return sort_type_; }

    Fl_ListItem_List &get_selection() { return selection; }

    Fl_Scrollbar vscrollbar;
    Fl_Scrollbar hscrollbar;

protected:

    static void hscrollbar_cb(Fl_Widget*, void*);
    static void vscrollbar_cb(Fl_Widget*, void*);

    void calc_index();
    uint find_safe_top();

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

    void draw_item(Fl_ListView_Item *);
    void draw_clip(int,int,int,int);
    static void draw_clip_cb(void*,int,int,int,int);

    int X,Y,W,H; //box
    int HX,HY,HW,HH; //header box

    bool draw_stripes_;
    bool find_def; // Set when needs to find default colmn sizes (called by layout)

    int sort_type_;
};

#endif
