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

/**
 * @file Fl_Font.h
 */

#include "Fl_Export.h" // for FL_API
#include "Fl_String_List.h"
#include "Fl_Int_List.h"

class FL_API Fl_FontSize;

struct FL_API Fl_Font_;
typedef const Fl_Font_* Fl_Font;

// This is a struct so I can init a table with constants:

/**
 * The Fl_Font_ struct. 
 */
struct FL_API Fl_Font_ {
// PRIVATE:
    const char* name_;
    Fl_Font_* bold_;
    Fl_Font_* italic_;

    // list of sizes (used by X and Win32 GDI):
    Fl_FontSize *first;

#ifdef _WIN32
	// WIN32 cache stuff:
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

    /** 
	 * Return the system-specific name, different for each font.
	 * Using this function is not portable!
	 */
    const char *system_name() const { return name_; }

    /**
	 * Return the "nice" name, and the attributes.
	 * @param attr Font attributes are stored to this, if not NULL
	 */
    const char *name(int *attr = 0) const;

    /** 
	 * Get array of font sizes for this font.
	 * Returns number of sizes stored in array.
	 * @param parray Array pointer for storing sizes, caller MUST NOT free array.
	 */
    int sizes(int *&parray) const;

    /** 
	 * Get array of font encoding for this font.
	 * Returns number of encodings stored in array.
	 * @note XFT does not return any encoding, since fonts are UNICODE mapped.
	 * @note WIN32 returns charsets, not encodings.
	 *
	 * @param parray Array pointer for storing encodings, caller MUST NOT free array.
	 */
    int encodings(const char **&parray) const;

	/**
	 * Return pointer to bold version of this font.
	 * If returned pointer points to this font, bold font cannot be found.
	 */
    Fl_Font bold() const { return bold_; }
	/**
	 * Return pointer to italic version of this font.
	 * If returned pointer points to this font, italic font cannot be found.
	 */
    Fl_Font italic() const { return italic_; }
};

/**
 * Values for font attributes.
 */
enum {
    FL_BOLD			= 1, ///< Bold font
    FL_ITALIC		= 2, ///< Italic font
    FL_BOLD_ITALIC	= 3  ///< Bold+italic font
};

// Buildin font defines:
#define FL_HELVETICA			 (fl_fonts+0)
#define FL_HELVETICA_BOLD		 (fl_fonts+1)
#define FL_HELVETICA_ITALIC		 (fl_fonts+2)
#define FL_HELVETICA_BOLD_ITALIC (fl_fonts+3)
#define FL_COURIER				 (fl_fonts+4)
#define FL_COURIER_BOLD			 (fl_fonts+5)
#define FL_COURIER_ITALIC		 (fl_fonts+6)
#define FL_COURIER_BOLD_ITALIC	 (fl_fonts+7)
#define FL_TIMES				 (fl_fonts+8)
#define FL_TIMES_BOLD			 (fl_fonts+9)
#define FL_TIMES_ITALIC			 (fl_fonts+10)
#define FL_TIMES_BOLD_ITALIC	 (fl_fonts+11)
#define FL_SYMBOL				 (fl_fonts+12)
#define FL_SCREEN				 (fl_fonts+13)
#define FL_SCREEN_BOLD			 (fl_fonts+14)
#define FL_ZAPF_DINGBATS		 (fl_fonts+15)

/**
 * Array of build-in fonts. See defined macros FL_*(_BOLD)(_ITALIC).
 */
extern FL_API Fl_Font_ fl_fonts[16];

/**
 * Create new font, this function is system depend and should not be used!
 * Under X11 it takes XLFD and under WIN32 it's font name
 */
extern FL_API Fl_Font fl_create_font(const char *system_name);

/** 
 * Find a font by name + attributes 
 */
extern FL_API Fl_Font fl_find_font(const char* name, int attrib = 0);

/** 
 * Find and return every font on the system. 
 * Returns number of fonts found.
 * @param arrayp Fonts are stored to this array pointer, caller MUST NOT free pointer!
 */
extern FL_API int fl_list_fonts(Fl_Font*& arrayp);

#endif
