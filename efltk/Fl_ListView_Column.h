#ifndef _FL_LISTVIEW_COLUMN_H_
#define _FL_LISTVIEW_COLUMN_H_

#include <efltk/Fl_String.h>

class Fl_ListView_Column
{
public:
    Fl_ListView_Column();

    void label(const char *text) { m_label = text; }
    void label(const Fl_String &text) { m_label = text; }
    const Fl_String &label() const { return m_label; }

    void type(Fl_Variant_Type t) { m_type = t; }
    Fl_Variant_Type type() const { return m_type; }

    Fl_Flags flags(Fl_Flags f)  { return (m_flags = f); }
    Fl_Flags flags() const      { return m_flags; }
    Fl_Flags set_flag(int f)    { return (m_flags |= f); }
    Fl_Flags clear_flag(int f)  { return (m_flags &= ~f); }
    Fl_Flags invert_flag(int f) { return (m_flags ^= f); }

    int label_size() const { return m_font_size; }
    void label_size(int size) { m_font_size = size; }

    Fl_Font label_font() const { return m_font; }
    void label_font(Fl_Font font) { m_font = font; }

    Fl_Color label_color() const { return m_color; }
    void label_color(Fl_Color color) { m_color = color; }

    void image(Fl_Image *i) { m_image = i; }
    void image(Fl_Image &i) { m_image = &i; }
    const Fl_Image *image() const { return m_image; }
    Fl_Image *image() { return m_image; }

private:
    Fl_String       m_label;
    Fl_Color        m_color;
    Fl_Font         m_font;
    int             m_font_size;
    Fl_Variant_Type m_type;
    Fl_Flags        m_flags;
    Fl_Image       *m_image;
};

//////////////////////////////////////////
//////////////////////////////////////////

class Fl_ListColumn_List : public Fl_Ptr_List {
public:
    Fl_ListColumn_List() : Fl_Ptr_List() { }
    virtual ~Fl_ListColumn_List() { clear(); }

    void append(Fl_ListView_Column *item) { Fl_Ptr_List::append((void *)item); }
    void prepend(Fl_ListView_Column *item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(uint pos, Fl_ListView_Column *item) { Fl_Ptr_List::insert(pos, (void *)item); }
    void replace(uint pos, Fl_ListView_Column *item) { Fl_Ptr_List::replace(pos, (void *)item); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(Fl_ListView_Column *item) { return Fl_Ptr_List::remove((void *)item); }
    int index_of(const Fl_ListView_Column *w) const { return Fl_Ptr_List::index_of((void*)w); }
    Fl_ListView_Column *item(uint index) const { return (Fl_ListView_Column*)Fl_Ptr_List::item(index); }
    Fl_ListView_Column **data() { return (Fl_ListView_Column**)items; }

    Fl_ListView_Column *operator [](unsigned ind) { return (Fl_ListView_Column *)items[ind]; }
    const Fl_ListView_Column *operator [](uint ind) const { return (Fl_ListView_Column *)items[ind]; }

protected:
    void free_item(Fl_Ptr_List_Item item) { delete (Fl_ListView_Column*)(item); }
};


#endif
