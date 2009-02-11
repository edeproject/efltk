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

#ifndef _FL_TRANSLATOR_H_
#define _FL_TRANSLATOR_H_

#include "Fl_Export.h"
#include "Fl_String_List.h"
#include "Fl_Ptr_List.h"

/** Fl_Translator */
class FL_API Fl_Translator
{
public:
    static char *tr(const char *string);
    static char *dtr(const char *domain, const char *string);

    static const char *load_translation_file(const char *desired_domain, const char *path);
    static const char *load_translation(const char *domainname);

    static bool has_search_path(const char *path);
    static void add_search_path(const char *path);
    static void remove_search_path(const char *path);

    // GNU gettext compatibility layer
    static char *bindtextdomain(const char *domainname, const char *dirname);
    static char *textdomain(const char *domainname);

    Fl_Translator();
    ~Fl_Translator();

private:
    static Fl_CString_List search_paths_;
    static Fl_Ptr_List catalogs_;
    static Fl_Translator translator;
};

#endif
