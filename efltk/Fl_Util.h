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

#ifndef _FL_UTIL_H_
#define _FL_UTIL_H_

#include "Enumerations.h"
#include "Fl_Flags.h"
#include "Fl_String.h"

#include "Fl_Rect.h"
#include "Fl_Point.h"
#include "Fl_Size.h"

// Include for compatibility
#include "filename.h"

/** removes leading spaces */
extern FL_API char *fl_trimleft(char *string);

/** removes trailing spaces */
extern FL_API char *fl_trimright(char *string);

/// Removes trailing and leading spaces
#define fl_trim(string) fl_trimright(fl_trimleft(string))

/** fl_tolower */
extern FL_API char *fl_tolower(char *string);

/** fl_toupper */
extern FL_API char *fl_toupper(char *string);

/** fl_strdup_printf */
extern FL_API char *fl_strdup_printf(char *s1, ...);

/** fl_split */
extern FL_API char** fl_split(const char *string, const char *delimiter, int max_tokens);

/** fl_start_child_process */
extern FL_API int fl_start_child_process(char *cmd);

/** fl_freev */
extern FL_API void fl_freev(char **str_array);

/** fl_cut_line */
extern FL_API const char *fl_cut_line(const char *str, int maxwidth);

/** fl_cut_multiline */
extern FL_API const char *fl_cut_multiline(const char *str, int maxwidth);

#endif
