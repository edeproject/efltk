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

#ifndef _FL_LISTVIEW_HEADER_H_
#define _FL_LISTVIEW_HEADER_H_

#include "Fl_Widget.h"
#include "Fl_Image.h"
#include "Fl_Ptr_List.h"

/** Fl_ListView_Header */
class Fl_ListView_Header : public Fl_Widget
{
public:
    static Fl_Named_Style* default_style;

    Fl_ListView_Header(int X,int Y,int W,int H,const char*l=0);
    ~Fl_ListView_Header();

    void add_column(const char *name, int w, Fl_Variant_Type column_type=VAR_STRING);
    void add_column(const Fl_String &name, int w, Fl_Variant_Type column_type=VAR_STRING);

    virtual void clear();

    void columns(int count);
    uint columns();

    int column_width(int col);
    void column_width(int col, int w);

    Fl_Variant_Type column_type(int col);
    void column_type(int col, Fl_Variant_Type w);

    Fl_Flags column_flags(int col, int f);
    Fl_Flags column_flags(int col);
    Fl_Flags column_set_flag(int col, int f);
    Fl_Flags column_clear_flag(int col, int f);
    Fl_Flags column_invert_flag(int col, int f);

    const Fl_String &column_label() const;
    const Fl_String &column_label(int col) const;

    void column_label(int col, const char *text);
    void column_label(int col, const Fl_String &text);
    void column_copy_label(int col, const char *txt) { column_label(col, txt); }

    Fl_Font column_label_font(int col) const;
    int column_label_size(int col) const;
    void column_label_size(int col, int size) const;
    void column_label_font(int col, Fl_Font font);
    void column_label_color(int col, Fl_Color color);

    void column_image(int col, Fl_Image *im);
    void column_image(int col, Fl_Image &im);
    Fl_Image *column_image(int col);
    const Fl_Image *column_image(int col) const;

    virtual void draw();
    virtual void layout();
    virtual int handle(int ev);

protected:
    int sort_type;
    int sort_col;
    Fl_Ptr_List attr_list;

    virtual void add_attr(int col);
};

#endif
