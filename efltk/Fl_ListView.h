#ifndef _FL_LISTVIEW_H_
#define _FL_LISTVIEW_H_

#include "Fl_Table_Base.h"
#include "Fl_ListView_Item.h"
#include "Fl_ListView_Header.h"
#include "Fl_ListView_Column.h"

/**
 * Fl_ListView.. Docos to do..
 */
class Fl_ListView : public Fl_Table_Base {
public:
    // This must not overlap values in Fl_Table_Base::Flags
    // Now it's next available bit mask (after RESIZABLE)
    enum ListViewFlags {
        SELECTED       = 4,
        NON_SELECTABLE = 8,
        INACTIVE       = 16
    };

    enum TypeInModes {
        TYPE_IN_NONE = 0, // No type-in-search
        TYPE_IN_SELECT,   // Select first match
        TYPE_IN_HIDE      // Hide unmatch
    };

    enum SortTypes {
        SORT_NONE = 0,
        SORT_ASC,
        SORT_DESC,
        SORT_LAST_TYPE //number of last type
    };

    static Fl_Named_Style* default_style;
    static Fl_ListView *current;

    // values for type()
    enum TypeValues {
        MULTI_SELECTION = 16,
        WIDTH_CHANGED_NOTIFY = 32
    };

    /**
     * Creates new list view widget using the given position, size, and label string.
     */
    Fl_ListView(int X, int Y, int W, int H, const char *l=0);

    /**
     * Creates new list view widget using the label, size, alignment, and label width.
     */
    Fl_ListView(const char *l = 0, int layout_size=30, Fl_Align layout_al=FL_ALIGN_TOP, int label_w=100);

    /** Destructor */
    virtual ~Fl_ListView();

    void clear();

    virtual void layout();
    virtual int handle(int event);

    virtual void begin();
    virtual void end();

    virtual void fill(Fl_Data_Source &ds, const char *user_data_column_name="");

    int find(const Fl_ListView_Item *item) const;
    int find(const Fl_ListView_Item &item) const { return find(&item); }

    void insert(Fl_ListView_Item &item, int pos);
    void add(Fl_ListView_Item &item);
    void remove(int index);
    void remove(Fl_ListView_Item &item) { remove(find(&item)); }
    void remove(Fl_ListView_Item *item) { remove(find(item)); }

    unsigned children() const { return items.size(); }
    Fl_ListView_Item* child(unsigned n) const { return items.item(n); }
    Fl_ListItem_List &array() { return items; }

    Fl_ListView_Header *header() { return m_header; }
    const Fl_ListView_Header *header() const { return m_header; }

    bool multi() const { return ((type() & MULTI_SELECTION)==MULTI_SELECTION); }
    void multi(bool val) { if(val) type(type()|MULTI_SELECTION); else type(type()&~MULTI_SELECTION); }

    bool draw_stripes() const { return m_draw_stripes; }
    void draw_stripes(bool v) { m_draw_stripes = v; }

    void damage_item(Fl_ListView_Item *i) { i->redraw(); }
    void damage_row(unsigned row) { items[row]->redraw(); }

    // Selections:
    // 0 = unselect, 1 = select, 2 = toggle

    void select_all_rows(int value=1);
    bool unselect_all();

    void inactive_row(unsigned row, bool val);
    bool inactive_row(unsigned row) const { return (row_flags(row)&INACTIVE)==INACTIVE; }
    bool inactive(Fl_ListView_Item *w) const { return inactive_row(find(w)); }

    void selectable_row(unsigned row, bool val);
    bool selectable_row(unsigned row) const { return !(row_flags(row)&NON_SELECTABLE); }
    bool selectable(Fl_ListView_Item *w) const { return selectable_row(find(w)); }

    bool selected_row(unsigned row) const { return (row_flags(row) & SELECTED)==SELECTED; }
    bool selected(Fl_ListView_Item *w) const { return selected_row(find(w)); }

    bool select_row(unsigned row, int value=1);
    bool select(Fl_ListView_Item *w, int value=1) { return select_row(find(w), value); }

    bool select_only_row(unsigned row);
    bool select_only(Fl_ListView_Item *w) { return select_only_row(find(w)); }

    void select_items(unsigned from, unsigned to);

    int selected() const { return selection.count(); }
    Fl_ListItem_List &get_selection();
    const Fl_ListItem_List &get_selection() const;

    void current_row(unsigned row) { cur_row = row; }
    unsigned current_row() const   { return cur_row; }

    Fl_ListView_Item *item(Fl_ListView_Item *i);
    Fl_ListView_Item *item() const { return items.item(cur_row); }

    Fl_ListView_Item *item_at(int Y) const;
    int row_at(int Y) const;

    bool show_item(Fl_ListView_Item *w);

    Fl_ListView_Item* prev();
    Fl_ListView_Item* next();

    int prev_row();
    int next_row();

    //Sort:
    // Returns sort mode: ASC, DESC, UNKNOWN
    virtual int sort(int column);

    int sort_col() const { return m_sort_col; }
    void sort_col(int col) { m_sort_col = col; }

    int sort_type() const { return m_sort_type; }
    void sort_type(int t) { m_sort_type = t; }

    // Search:
    Fl_ListView_Item *find_userdata(void *data, unsigned start_index=0, unsigned end_index=0) const;
    Fl_ListView_Item *find_text(const char *text, int column=-1, unsigned start_index=0, unsigned end_index=0) const;

    int find_userdata_row(void *data, unsigned start_index=0, unsigned end_index=0) const;
    int find_text_row(const char *text, int column=-1, unsigned start_index=0, unsigned end_index=0) const;

    int type_in_mode() const { return (int)m_type_in_mode; }
    void type_in_mode(int v) { m_type_in_mode = (uchar)v; }

    void reset_search();
    const Fl_String &search_str() const { return m_search_str; }

    // Columns:
    Fl_ListView_Column *add_column(const char *name, int width=-1, Fl_Variant_Type column_type=VAR_STRING);
    bool remove_column(const char *name);
    void remove_column(unsigned index);
    void clear_columns();

    Fl_ListView_Column *column(unsigned c) { return m_columns.item(c); }
    const Fl_ListView_Column *column(unsigned c) const { return m_columns.item(c); }
    unsigned columns() const { return m_columns.size(); }
    void columns(unsigned count);

    // Finds default sizes for columns, which has width=-1
    void find_default_sizes();
    int preferred_col_width(int col);

    bool width_changed_notify() const { return ((type() & WIDTH_CHANGED_NOTIFY)==WIDTH_CHANGED_NOTIFY); }
    void width_changed_notify(bool v) { if(v) type(type()|WIDTH_CHANGED_NOTIFY); else type(type()&~WIDTH_CHANGED_NOTIFY); }

    void resetup();

    /////////////////////////////////////
    // Compatibility section

    Fl_ListView_Item *top() { return items.item(0); }

    void clear_selection() { unselect_all(); }

    void recalc_totalheight() { resetup(); }

    void scroll_up(int pixels = 20) { int newy = yposition()-20; yposition((newy>0) ? newy : 0); }
    void scroll_down(int pixels = 20) { int newy = yposition()+20; yposition(newy); }

    int column_width(int c) const { return col_width(c); }
    void column_width(int c, int w) { col_width(c, w); }

    Fl_Variant_Type column_type(int c) const { return column(c)->type(); }
    void column_type(int c, Fl_Variant_Type t) { column(c)->type(t); }

    const char *column_name(int c) const { return column(c)->label(); }
    void column_name(int c, const char *name) { column(c)->label(name); }

    int column_flags(int c) const { return column(c)->flags(); }
    void column_flags(int c, int f) { column(c)->flags(f); }

    const Fl_Image *column_image(int c) const { return column(c)->image(); }
    Fl_Image *column_image(int c) { return column(c)->image(); }
    void column_image(int c, Fl_Image *im) { column(c)->image(im); }
    void column_image(int c, Fl_Image &im) { column(c)->image(im); }

protected:

    virtual void table_draw(TableContext context, unsigned R=0, unsigned C=0,
                            int X=0, int Y=0, int W=0, int H=0);
    virtual void table_layout(TableContext context, unsigned row, unsigned col);
    virtual int  table_handle(TableContext context, unsigned row, unsigned col, int event);

	virtual void draw_row(unsigned row, int w, int h) const;

    virtual int handle_key();

    // returns true, if key matches somehow text.
    // Default implementation checks, if first key.length() characters are same in text.
    virtual bool match_text(const Fl_String &key, const char *text) const;

private:
    int cur_row;

    Fl_ListColumn_List m_columns;

    bool m_needsetup;
    bool m_draw_stripes;

    int m_sort_type;
    int m_sort_col;

    Fl_ListItem_List items;
    Fl_Int_List selection;

    // For get_selection...
    Fl_ListItem_List stored_selection;

    Fl_ListView_Header *m_header;

    Fl_String m_search_str;
    uchar m_type_in_mode;

    bool set_select_flag(unsigned row, int flag);
    void ctor_init();
};

#endif
