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

#ifndef _FL_FONT_H_
#define _FL_FONT_H_

#include "Fl_Export.h" // for FL_API
#include "Fl_String_List.h"
#include "Fl_Int_List.h"

class FL_API Fl_FontSize;

struct FL_API Fl_Font_;
typedef const Fl_Font_* Fl_Font;

// This is a struct so I can init a table with constants:
struct FL_API Fl_Font_ {
// PRIVATE:
    const char* name_;
    Fl_Font_* bold_;
    Fl_Font_* italic_;

    // list of sizes (used by X and Win32 GDI):
    Fl_FontSize *first;

#ifdef _WIN32
    Fl_CString_List *charsets_;
    Fl_Int_List *sizes_;
#else
    // XWindows cache stuff:
    char **xlist_;
    int xlist_n_;

    uint cache_xlist();
    Fl_FontSize *load_font(float size);
#endif
// PUBLIC:

    // return the system-specific name, different for each fontset:
    const char *system_name() const { return name_; }

    // return the "nice" name, and the attributes:
    const char *name(int *attr = 0) const;

    // return array of sizes:
    int sizes(int*&) const;

    // return array of encodings:
    int encodings(const char**&) const;

    Fl_Font bold() const { return bold_; }
    Fl_Font italic() const { return italic_; }

    // "measurement" is considered a drawing function, see fl_draw.h
};

// values for attributes:
enum {
    FL_BOLD = 1,
    FL_ITALIC = 2,
    FL_BOLD_ITALIC = 3
};

// Built-in fonts:
extern FL_API Fl_Font_ fl_fonts[16];

#define FL_HELVETICA			(fl_fonts+0)
#define FL_HELVETICA_BOLD		(fl_fonts+1)
#define FL_HELVETICA_ITALIC		(fl_fonts+2)
#define FL_HELVETICA_BOLD_ITALIC (fl_fonts+3)
#define FL_COURIER				(fl_fonts+4)
#define FL_COURIER_BOLD			(fl_fonts+5)
#define FL_COURIER_ITALIC		(fl_fonts+6)
#define FL_COURIER_BOLD_ITALIC	(fl_fonts+7)
#define FL_TIMES				(fl_fonts+8)
#define FL_TIMES_BOLD			(fl_fonts+9)
#define FL_TIMES_ITALIC			(fl_fonts+10)
#define FL_TIMES_BOLD_ITALIC	(fl_fonts+11)
#define FL_SYMBOL				(fl_fonts+12)
#define FL_SCREEN				(fl_fonts+13)
#define FL_SCREEN_BOLD			(fl_fonts+14)
#define FL_ZAPF_DINGBATS		(fl_fonts+15)

// XWin: Create a fontset, XLFD's separated with comma
// WIN32: Create single font
extern FL_API Fl_Font fl_create_font(const char *system_name);

/** Find a font by name + attributes */
extern FL_API Fl_Font fl_find_font(const char* name, int attrib = 0);

/** Find and return every font on the system. */
extern FL_API int fl_list_fonts(Fl_Font*& arrayp);

#endif
