/***************************************************************************
                          Fl_Exception.cpp  -  description
                             -------------------
    begin                : Thu Apr 27 2000
    copyright            : (C) 2000 by Alexey S.Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl.h>

#include <stdlib.h>
#include <exception>

static void fl_terminate_handler() {	
    Fl::warning("Exception termination handler called.\n"
				"This is due to unhandled exception in application,\n"
				"that often means application has crashed.\n" 
				"It is highly recommended to contact application vendor for bug report."
				);
	abort();
}

static void fl_unexpected_handler() {
    Fl::warning("Unexpected exception handler called.\n"
				"It is highly recommended to contact application vendor for bug report."
				);
	abort();
}

class ExceptionInitializer {
public:
	ExceptionInitializer() {		
		::set_terminate(fl_terminate_handler);
		::set_unexpected(fl_unexpected_handler);		
	}	
};
static ExceptionInitializer initializer;

Fl_Exception::Fl_Exception(const char *text, const char *file, int line) {	
    m_file = file;
    m_text = text;
    m_line = line;
}

Fl_String Fl_Exception::text(bool short_version) const {
    if(!short_version && m_line) {
        Fl_String ret;
        return ret.printf(_("Error in file \'%s\' [%d]: %s"), m_file, m_line, m_text.c_str());
    }
    return m_text;
}
