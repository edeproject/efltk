#ifndef _FL_LISTVIEW_ITEM_H_
#define _FL_LISTVIEW_ITEM_H_

#include "Fl_Image.h"
#include "Fl_String.h"
#include "Fl_Packed_Strings.h"

class Fl_ListView;

class FL_API Fl_ListView_Item {
public:
	enum ItemTypes {
		NORMAL = 0,
		EXT = 1,
		CUSTOM = 1000
	};

    Fl_ListView_Item(const char *label1=0,
                     const char *label2=0,
                     const char *label3=0,
                     const char *label4=0,
                     const char *label5=0);
    virtual ~Fl_ListView_Item();

	virtual int type() { return NORMAL; }

    const char *label() const;
    const char *label(unsigned col) const;
    void label(unsigned col, const char *text);
    void label(unsigned col, const Fl_String &text);

    virtual void columns(unsigned count);
    virtual unsigned columns() const;

    // Layouting:
    virtual int preferred_width(int col) const;
    virtual void width_changed(unsigned row, int col);
    virtual void setup(unsigned row);

    virtual void draw_cell(unsigned row, unsigned col, int width, int height);

    void parent(Fl_ListView *p) { m_parent = p; }
    Fl_ListView *parent() const { return m_parent; }

    void *user_data()       { return m_user_data; }
    void user_data(void *d) { m_user_data = d; }
    long argument() const   { return (long)m_user_data; }
    void argument(long v)   { m_user_data = (void*)v; }

    uchar damage() const { return m_damage; }
    void set_damage(uchar c) { m_damage = c; }
    void redraw(uchar c);
    void redraw() { redraw(FL_DAMAGE_ALL); }

    void image(Fl_Image *im) { m_image = im; }
    void image(Fl_Image &im) { m_image = &im; }
    Fl_Image *image() { return m_image; }
    const Fl_Image *image() const { return m_image; }
    void image(unsigned col, Fl_Image &im) { image(im); }
    void image(unsigned col, Fl_Image *im) { image(im); }

    virtual int compare(Fl_ListView_Item *other, int column, int sort_type);

    ///////////////////////////////////////////////
    // Compatibility section:

    void copy_label(unsigned col, const char *text) { label(col, text); }

protected:
    Fl_Packed_Strings strings;

    void draw_row(unsigned row, int x, int y, int w, int h) const;

    int compare_strings(Fl_ListView_Item *other, int column, int sort_type) const;
    int compare_integers(Fl_ListView_Item *other, int column, int sort_type) const;
    int compare_floats(Fl_ListView_Item *other, int column, int sort_type) const;
    int compare_dates(Fl_ListView_Item *other, int column, int sort_type) const;
    int compare_datetimes(Fl_ListView_Item *other, int column, int sort_type) const;

private:
    Fl_ListView *m_parent;
    void *m_user_data;
    Fl_Image *m_image;
    //unsigned m_index;
    uchar m_damage;
};

class FL_API Fl_ListView_ItemExt : public Fl_ListView_Item {
public:
    Fl_ListView_ItemExt(const char *label1=0,
                        const char *label2=0,
                        const char *label3=0,
                        const char *label4=0,
                        const char *label5=0);
    virtual ~Fl_ListView_ItemExt();

	virtual int type() { return EXT; }

    virtual void columns(unsigned count);
    virtual unsigned columns() const { return Fl_ListView_Item::columns(); }

    // Layouting:
    virtual int preferred_width(int col) const;
    virtual void width_changed(unsigned row, int col);
    virtual void setup(unsigned row);

    virtual void draw_cell(unsigned row, unsigned col, int width, int height);

    int leading() const { return m_leading; }
    void leading(int l) { m_leading = l; }

    Fl_Flags flags(unsigned col, Fl_Flags f);
    Fl_Flags flags(unsigned col) const ;
    Fl_Flags set_flag(unsigned col, Fl_Flags f);
    Fl_Flags clear_flag(unsigned col, Fl_Flags f);
    Fl_Flags invert_flag(unsigned col, Fl_Flags f);

    int label_size(unsigned col) const;
    void label_size(unsigned col, int size);

    Fl_Font label_font(unsigned col) const;
    void label_font(unsigned col, Fl_Font font);

    Fl_Labeltype label_type(unsigned col) const;
    void label_type(unsigned col, Fl_Labeltype type);

    Fl_Color label_color(unsigned col) const;
    void label_color(unsigned col, Fl_Color color);

    void label_font(unsigned col, Fl_Font font, int size) { label_font(col, font); label_size(col, size); }

    void image(unsigned col, Fl_Image *im);
    void image(unsigned col, Fl_Image &im);
    Fl_Image *image(unsigned col);
    const Fl_Image *image(unsigned col) const;

protected:
    void draw_label(unsigned col, const char *label, int X, int Y, int W, int H, Fl_Flags flags);

private:
    int m_leading;
    Fl_Ptr_List col_attrs;
};

//////////////////////////////////////////
//////////////////////////////////////////

class Fl_ListItem_List : public Fl_Ptr_List {
public:
    Fl_ListItem_List() : Fl_Ptr_List() { }
    virtual ~Fl_ListItem_List() { clear(); }

    void append(Fl_ListView_Item *item) { Fl_Ptr_List::append((void *)item); }
    void prepend(Fl_ListView_Item *item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(uint pos, Fl_ListView_Item *item) { Fl_Ptr_List::insert(pos, (void *)item); }
    void replace(uint pos, Fl_ListView_Item *item) { Fl_Ptr_List::replace(pos, (void *)item); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(Fl_ListView_Item *item) { return Fl_Ptr_List::remove((void *)item); }
    int index_of(const Fl_ListView_Item *w) const { return Fl_Ptr_List::index_of((void*)w); }
    Fl_ListView_Item *item(uint index) const { return (Fl_ListView_Item*)Fl_Ptr_List::item(index); }
    Fl_ListView_Item **data() { return (Fl_ListView_Item**)items; }
    Fl_ListView_Item *operator [](uint ind) const { return (Fl_ListView_Item *)items[ind]; }
protected:
    void free_item(Fl_Ptr_List_Item item) { delete (Fl_ListView_Item*)(item); }
};

#endif
