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

#ifndef _FL_LISTVIEW_ITEM_H_
#define _FL_LISTVIEW_ITEM_H_

#include "Fl.h"
#include "Fl_Font.h"
#include "Fl_Style.h"
#include "Fl_Image.h"
#include "Fl_Image_List.h"
#include "Fl_Int_List.h"
#include "Fl_String_List.h"
#include "Fl_Ptr_List.h"

class Fl_ListView;

// ListView_Item attributes for each column
class Fl_ListItem_Attr
{
public:
    Fl_String       col_label;
    int16           col_width;
};

/** Fl_ListView_Item */
class FL_API Fl_ListView_Item {
public:
    Fl_ListView_Item(const char *label1=0,
        const char *label2=0,
        const char *label3=0,
        const char *label4=0,
        const char *label5=0);
    virtual ~Fl_ListView_Item();

    bool selected() const;

    void *user_data() const { return user_data_; }
    void user_data(void* v) { user_data_ = v; }
    long argument() const   { return (long)user_data_; }
    void argument(long v)   { user_data_ = (void*)v; }

    uchar damage() const { return damage_; }
    void set_damage(uchar c) { damage_ = c; }
    void redraw(uchar c);
    void redraw() { redraw(FL_DAMAGE_ALL); }

    Fl_ListView *parent() const { return parent_; }
    void parent(Fl_ListView *l) { parent_ = l; }

    int column_width(int col) const;

    void check_columns(uint count);
    void columns(uint count);
    uint columns() const;

    virtual void draw_cell(int col, int width, bool selected);
    virtual void layout();

    const Fl_String &label() const;
    const Fl_String &label(int col) const;
    void label(int col, const char *text);
    void label(int col, const Fl_String &text);
    void copy_label(int col, const char *txt) { label(col, txt); }

    void image(Fl_Image *im) { image_ = im; }
    void image(Fl_Image &im) { image_ = &im; }
    Fl_Image *image() { return image_; }
    const Fl_Image *image() const { return image_; }
    void image(int col, Fl_Image &im) { image(im); }
    void image(int col, Fl_Image *im) { image(im); }

    int y() const { return y_; }
    void y(int Y) { y_ = Y; }
    int h() const { return h_; }
    void h(int H) { h_ = H; }

    // Current index on the list
    void index(int i) { index_ = i; }
    int index() const { return index_; }

    virtual int compare(Fl_ListView_Item *other, int column, int sort_type);

protected:
    Fl_Ptr_List attr_list;

    // Creates and intializes attr class,
    // extended listitems with more column specific attributes must override this
    virtual Fl_ListItem_Attr *create_attr(int col);

private:
    int y_, h_;

    unsigned index_;
    uchar damage_;
    Fl_Image *image_;
    void *user_data_;
    Fl_ListView *parent_;
    void add_attr(int col);
};

//////////////////////////////////////////
//////////////////////////////////////////

// ListView_ItemExt attributes for each column
class Fl_ListItem_AttrExt : public Fl_ListItem_Attr
{
public:
    Fl_Flags col_flags;
    Fl_Font col_font;
    int col_font_size;
    Fl_Color col_color;
    Fl_Image *col_image;
    Fl_Labeltype col_label_type;
};

/** Fl_ListView_ItemExt */
class FL_API Fl_ListView_ItemExt : public Fl_ListView_Item {
public:
    Fl_ListView_ItemExt(const char *label1=0,
        const char *label2=0,
        const char *label3=0,
        const char *label4=0,
        const char *label5=0);
    virtual ~Fl_ListView_ItemExt();

    virtual void draw_cell(int col, int width, bool selected);
    virtual void layout();

    int leading() const { return leading_; }
    void leading(int l) { leading_ = l; }

    Fl_Flags flags(int col, int f);
    Fl_Flags flags(int col) const ;
    Fl_Flags set_flag(int col, int f);
    Fl_Flags clear_flag(int col, int f);
    Fl_Flags invert_flag(int col, int f);

    Fl_Font label_font(int col) const;
    Fl_Labeltype label_type(int col) const;
    int label_size(int col) const;
    Fl_Color label_color(int col) const;

    void label_size(int col, int size);
    void label_font(int col, Fl_Font font);
    void label_color(int col, Fl_Color color);
    void label_type(int col, Fl_Labeltype type);

    void label_font(int col, Fl_Font font, int size) { label_font(col, font); label_size(col, size); }

    void image(int col, Fl_Image *im);
    void image(int col, Fl_Image &im);
    Fl_Image *image(int col);
    const Fl_Image *image(int col) const;

protected:
    int leading_;
    virtual Fl_ListItem_Attr *create_attr(int col);
private:
    void draw_label(const char *label, int X, int Y, int W, int H, Fl_Flags flags, void *a);
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
