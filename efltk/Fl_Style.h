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

#ifndef _FL_STYLE_H_
#define _FL_STYLE_H_

#include "Enumerations.h"
#include "Fl_Boxtype.h"
#include "Fl_Labeltype.h"
#include "Fl_Font.h"

class FL_API Fl_Widget;

typedef void (*Fl_Glyph)(const Fl_Widget*, int type,
                         int,int,int,int,
                         Fl_Flags);

extern "C" { typedef bool (*Fl_Theme)(); }

/** Fl_Style */
struct FL_API Fl_Style {
    const Fl_Style* parent;
    void  (*revertfunc)(Fl_Style*);

    Fl_Boxtype    box;
    Fl_Boxtype    button_box;
    Fl_Boxtype	  focus_box;
    Fl_Glyph      glyph;
    Fl_Font       label_font;
    Fl_Font       text_font;
    Fl_Labeltype  label_type;
    Fl_Color      color;
    Fl_Color      button_color;
    Fl_Color      label_color;
    Fl_Color      selection_color;
    Fl_Color      selection_text_color;
    Fl_Color      highlight_color;
    Fl_Color      highlight_label_color;
    Fl_Color      text_color;
    unsigned      label_size;
    unsigned      text_size;
    unsigned      leading;

    // global settings:
    static bool   draw_boxes_inactive;
    static unsigned scrollbar_width;
    static Fl_Flags scrollbar_align;
    static int	wheel_scroll_lines;

    Fl_Style(); // creates a dynamic() style
    bool dynamic() const {return !revertfunc;}

    static Fl_Style* find(const char* name);
    static void revert();
    static Fl_Theme theme() {return theme_;}
    static void theme(Fl_Theme f) {theme_ = f;}
    static Fl_Theme load_theme(const char*);
    static void load_theme();
    static void reload_theme();
    static const char* scheme() {return scheme_;}
    static void scheme(const char* f) {scheme_ = f;}

private:
    static Fl_Theme theme_;
    static const char* scheme_;
};

/** Fl_Named_Style */
struct FL_API Fl_Named_Style : public Fl_Style {
    Fl_Named_Style(const char* name, void (*revert)(Fl_Style*), Fl_Named_Style**);

    const char* name;
    Fl_Named_Style* next;
    static Fl_Named_Style* first;
    Fl_Named_Style** back_pointer; // used by Fl_Style_Set
};

/** Fl_Glyphtype */
enum Fl_Glyphtype {	// glyph types understood by Fl_Widget::default_glyph()
    // the numbers 0-99 are reserved for private glyph functions
    FL_GLYPH_BOX = 100,
    FL_GLYPH_UP,
    FL_GLYPH_DOWN,
    FL_GLYPH_LEFT,
    FL_GLYPH_RIGHT,
    FL_GLYPH_UP_BUTTON,
    FL_GLYPH_DOWN_BUTTON,
    FL_GLYPH_LEFT_BUTTON,
    FL_GLYPH_RIGHT_BUTTON
};

extern "C" FL_API bool fltk_theme();

/** fl_get_system_colors */
FL_API bool fl_get_system_colors();
FL_API const char* fl_find_config_file(char* out, int size, const char* name);

#endif
