//
// "$Id$"
//
// Fonts used by FLTK styles and drawing code
//
// Copyright 1998-1999 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#ifndef Fl_Font_h
#define Fl_Font_h

#include "Enumerations.h" // for FL_API
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

#ifndef _WIN32
    // XWindows cache stuff:
    bool xlist_cached_; //Are all XListFonts cached
    Fl_CString_List xlist_; //Cached xlist
    Fl_Int_List xlist_offsets_; // Offsets of different fonts in xlists
    Fl_Int_List xlist_sizes_;   // Sizes of different font lists in xlists

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
#define FL_HELVETICA		(fl_fonts+0)
#define FL_HELVETICA_BOLD	(fl_fonts+1)
#define FL_HELVETICA_ITALIC	(fl_fonts+2)
#define FL_HELVETICA_BOLD_ITALIC (fl_fonts+3)
#define FL_COURIER		(fl_fonts+4)
#define FL_COURIER_BOLD		(fl_fonts+5)
#define FL_COURIER_ITALIC	(fl_fonts+6)
#define FL_COURIER_BOLD_ITALIC	(fl_fonts+7)
#define FL_TIMES		(fl_fonts+8)
#define FL_TIMES_BOLD		(fl_fonts+9)
#define FL_TIMES_ITALIC		(fl_fonts+10)
#define FL_TIMES_BOLD_ITALIC	(fl_fonts+11)
#define FL_SYMBOL		(fl_fonts+12)
#define FL_SCREEN		(fl_fonts+13)
#define FL_SCREEN_BOLD		(fl_fonts+14)
#define FL_ZAPF_DINGBATS	(fl_fonts+15)

// Find a font by name + attributes:
FL_API Fl_Font fl_create_font(const char *system_name);

// Find a font by name + attributes:
FL_API Fl_Font fl_find_font(const char* name, int attrib = 0);

// Find and return every font on the system.
FL_API int fl_list_fonts(Fl_Font*& arrayp);

#ifndef FLTK_2
#define FL_NORMAL_SIZE	12
#endif

#endif
