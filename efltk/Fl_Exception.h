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

#ifndef _FL_EXCEPTION_H_
#define _FL_EXCEPTION_H_

#include "Fl_String.h"
#include "Fl_Export.h"

/**
 * General exception class for EFltk.
 * Only this type of exception is throwed by EFltk.
 */
class FL_API Fl_Exception {
public:
	Fl_Exception(const char *text="", const char *file="", int line=0);

	/**
	 * Returns descriptive text of exception happened,
	 * including file name and line in file.
	 *
	 * If short_version is true, only text is returned.
	 */
	Fl_String text(bool short_version=false) const;

protected:
	Fl_String m_text;
	const char *m_file;
	int m_line;
};

// Shortcut for easier throwing
#define fl_throw(text) throw Fl_Exception(text, __FILE__, __LINE__)

/*
 * Backward compatibility..
 * Emulate std C++ exception interface
 */
#define fl_try try
#define fl_catch(exception_variable) catch(Fl_Exception& exception_variable)
#define fl_throw_(text, file, line) throw Fl_Exception(text, file, line);
#define fl_rethrow throw

#endif
