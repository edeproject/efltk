#ifndef _FL_LISTVIEW_BASE_H_
#define _FL_LISTVIEW_BASE_H_

#include <efltk/Fl.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Scrollbar.h>

/**
 * Fl_Table_Base.. Docos to do..
 */
class Fl_Table_Base : public Fl_Group
{
public:
    // Bit mask for row/col flags. MAX 8 bytes!
    enum RowColFlags {
        NONE = 0,
        INVISIBLE = 1,
        NON_RESIZABLE = 2
    };

    // Context for table_layout and table_draw
    enum TableContext
    {
        CONTEXT_NONE = 0,
        CONTEXT_BEGIN,      // before a page is redrawn
        CONTEXT_END,        // after a page is redrawn
        CONTEXT_ROW_HEADER, // in the row header
        CONTEXT_COL_HEADER, // in the col header
        CONTEXT_CELL,       // in one of the cells
        CONTEXT_TABLE,      // in the table
        CONTEXT_SCROLLED    // Scrolled
    };

    // values for type()
    enum TypeValues {
        HORIZONTAL          = 1,
        VERTICAL            = 2,
        BOTH                = 3,
        ALWAYS_ON           = 4,
        HORIZONTAL_ALWAYS   = 5,
        VERTICAL_ALWAYS     = 6,
        BOTH_ALWAYS         = 7,
        TRANSPARENT_RESIZE  = 8
    };

    // Resize flags for row/col resize
    enum ResizeFlag {
        RESIZE_NONE      = 0,
        RESIZE_COL_LEFT  = 1,
        RESIZE_COL_RIGHT = 2,
        RESIZE_ROW_ABOVE = 3,
        RESIZE_ROW_BELOW = 4
    };

    Fl_Table_Base(int X, int Y, int W, int H, const char *l=0);
    Fl_Table_Base(const char *l = 0, int layout_size=30, Fl_Align layout_al=FL_ALIGN_TOP, int label_w=-1);
    virtual ~Fl_Table_Base();

    virtual int handle(int e);
    virtual void layout();
    virtual void draw();

    // Set transparent resize for columns and rows. Default is ON.
    bool transparent_resize() const { return ((type() & TRANSPARENT_RESIZE)==TRANSPARENT_RESIZE); }
    void transparent_resize(bool v) { if(v) type(type()|TRANSPARENT_RESIZE); else type(type()&~TRANSPARENT_RESIZE); }

    // Return x/y/w/h bounds for context.
    void get_bounds(TableContext context, int &X, int &Y, int &W, int &H);

    // Find row/col for current x/y event
    TableContext cursor2rowcol(unsigned &R, unsigned &C, ResizeFlag &resizeflag);

    // Find cell's on screen x/y/w/h for given row/col
    bool find_cell(TableContext context, unsigned R, unsigned C, int &X, int &Y, int &W, int &H);

    // Clamp r/c to known universe. Returns true, if clamped
    bool row_col_clamp(unsigned &R, unsigned &C);
    bool row_col_clamp(int &R, int &C);

    // Find scroll position of row (in pixels from top)
    int row_scroll_position(unsigned row);

    // Find scroll position of col (in pixels from left)
    int col_scroll_position(unsigned col);

    // Find row/col for x/y in somewhere table.
    // x/y must be in totalheight/totalwidth.
    // If row or col not found, variable is set to -1
    void position2rowcol(int x, int y, int &R, int &C) const;

    // Enable row resizing
    void row_resize(bool flag) { m_row_resize = flag; }
    bool row_resize() const { return m_row_resize; }

    // Enable col resizing
    void col_resize(bool flag) { m_col_resize = flag; }
    bool col_resize() const { return m_col_resize; }

    // Column minimum resizing width
    void col_resize_min(unsigned val) { m_col_resize_min = (int)val; }
    int col_resize_min() const { return m_col_resize_min; }

    // Column minimum resizing width
    void row_resize_min(unsigned val) { m_row_resize_min = (int)val; }
    int row_resize_min() const { return m_row_resize_min; }

    // set/get row header enable flag
    void row_header(bool flag) { m_row_header = flag; redraw(); relayout(); }
    bool row_header() const { return m_row_header; }

    // set/get col header enable flag
    void col_header(bool flag) { m_col_header = flag; redraw(); relayout(); }
    bool col_header() const { return m_col_header; }

    // set/get col header height
    void col_header_height(int height) { m_col_header_h = height; redraw(); relayout(); }
    int col_header_height() const { return m_col_header_h; }

    // set/get row header width
    void row_header_width(int width) { m_row_header_w = width; redraw(); relayout(); }
    int row_header_width() const { return m_row_header_w; }

    // set/get row height
    void row_height(unsigned row, int height);
    int row_height(unsigned row) const { return m_rowheights[row]; }

    // set/get a column's width
    void col_width(unsigned col, int width);
    int col_width(unsigned col) const { return m_colwidths[col]; }

    // set all row/col heights
    void row_height_all(int height);
    void col_width_all(int width);

    // Set new top row
    void top_row(unsigned row);

    // Set new left col
    void left_col(unsigned col);

    // Show row, returns true if scrolled
    bool show_row(unsigned row);

    // Show col, returns true if scrolled
    bool show_col(unsigned col);

    // Set/get Y scroll position
    void yposition(int Y);
    int yposition() const { return (int)vscrollbar->value(); }

    // Set/get X scroll position
    void xposition(int X);
    int xposition() const { return (int)hscrollbar->value(); }

    // Returns virtual height of table
    int totalheight() const { return table_h; }

    // Returns virtual width of table
    int totalwidth()  const { return table_w; }

    //////////////////
    // Flags handling for row/col
    void row_flags(int row, uchar flags) { m_rowflags[row] = flags; }
    uchar row_flags(int row) const { return m_rowflags[row]; }

    void col_flags(int row, uchar flags) { m_colflags[row] = flags; }
    uchar col_flags(int row) const { return m_colflags[row]; }

    // Set/get visibilty for row
    bool visible_row(int row) const { return !(m_rowflags[row]&INVISIBLE); }
    void visible_row(int row, bool val);

    // Set/get visibilty for col
    bool visible_col(int col) const { return !(m_colflags[col]&INVISIBLE); }
    void visible_col(int col, bool val);

    // Set/get resizable for individual row
    bool resizable_row(int row) const { return !(m_rowflags[row]&NON_RESIZABLE); }
    void resizable_row(int row, bool val);

    // Set/get resizable for individual col
    bool resizable_col(int col) const { return !(m_colflags[col]&NON_RESIZABLE); }
    void resizable_col(int col, bool val);

protected:

    // set/get number of rows
    virtual void row_count(unsigned count);
    unsigned row_count() const { return m_rows; }

    // set/get number of columns
    virtual void col_count(unsigned count);
    unsigned col_count() const { return m_cols; }

    // Default width for created columns
    int default_col_width() const { return m_default_col_w; }
    void default_col_width(int w) { m_default_col_w = w; }

    // Default height for created rows
    int default_row_height() const { return m_default_row_h; }
    void default_row_height(int h) { m_default_row_h = h; }

    // Called to draw cells
    // overridden by deriving class
    virtual void table_draw(TableContext context, unsigned R, unsigned C, int X, int Y, int W, int H) = 0;

    // Called when ever table gets resized or scrolled.
    // In CONTEXT_SCROLLED, row/col is set to top/left.
    virtual void table_layout(TableContext context, unsigned row, unsigned col) { }

    // You should use this to handle events.
    virtual int table_handle(TableContext context, unsigned row, unsigned col, int event) { return 0; }

    // table's virtual size (in pixels)
    int table_w, table_h;

    // top/left corners of viewable table
    unsigned toprow, leftcol;     //Row/col positions
    unsigned toprow_y, leftcol_x; //Scroll positions

    // Dimensions:
    // data table dimension xywh: E.G. tix = wix+(row_header()?row_header_width():0;
    int tix, tiy, tiw, tih;
    // widget inner dimension xywh: E.G. wih = h()-box()->dh()
    int wix, wiy, wiw, wih;

    // vertical scrollbar
    Fl_Scrollbar *vscrollbar;
    // horizontal scrollbar
    Fl_Scrollbar *hscrollbar;

    // Recalculate row lookup, this is needed when some row has changed
    // it's height. Or row count changed.
    void recalc_row_lookup() { m_recalc_row_lookup=true; relayout(); }

    // Returns cached row and set y to cached position.
    unsigned find_safe_top(int ypos, int &y) const;

    // Class maintenance. shows/hides scrollbar.
    void recalc_dimensions();

    // change mouse cursor to some other shape
    void change_cursor(Fl_Cursor newcursor);

    static void cb_vscrollbar(Fl_Scrollbar *s, Fl_Table_Base *d) { d->yposition((int)s->value()); }
    static void cb_hscrollbar(Fl_Scrollbar *s, Fl_Table_Base *d) { d->xposition((int)s->value()); }

private:
    unsigned m_rows;    // Total rows
    unsigned m_cols;	// Total cols

    int m_default_row_h; // Default row height for new rows
    int m_default_col_w; // Default col width for new cols

    int m_row_header_w;	// width of row header
    int m_col_header_h;	// height of column header

    bool m_row_header;  // row header enabled?
    bool m_row_resize;  // row resizing enabled?

    bool m_col_header;	// col header enabled?
    bool m_col_resize;	// col resizing enabled?

    int m_row_resize_min; // row minimum resizing height (default=1)
    int m_col_resize_min; // col minimum resizing width (default=1)

    Fl_Int_List m_colwidths;  // column widths in pixels
    Fl_Int_List m_rowheights; // row heights in pixels

    bool m_scrolled; //True after scroll, turned off by layout()
    bool m_row_cols_changed;

    // Y position / row lookup, this makes HUGE tables usable also.
    // yposition stored for each 1000 rows.
    Fl_Int_List m_row_lookup;
    bool m_recalc_row_lookup;
    void calc_row_lookup();

    // last mouse cursor before changed to 'resize' cursor
    Fl_Cursor m_last_cursor;

    // Flags for rows
    unsigned m_rowflags_size; // Size of allocated space in m_rowflags
    uchar *m_rowflags;        // Pointer to hold flags

    // Flags for cols
    unsigned m_colflags_size; // Size of allocated space in m_rowflags
    uchar *m_colflags;        // Pointer to hold flags

    void ctor_init();
};

#endif
