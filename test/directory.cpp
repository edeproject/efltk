/***************************************************************************
                          directory.cpp  -  description
                             -------------------
    begin                : Thu Nov 28 13:42:29 PST 2002
    copyright            : (C) 2002 by Alexey Parshin
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Directory_DS.h>

int main(int argc, char *argv[]) {
	Fl_Directory_DS   dds;

	try {
#ifdef _WIN32
		dds.directory("C:\\");
#else
		dds.directory("/usr/lib");
#endif
		dds.open();
		while (!dds.eof()) {
			Fl_Date_Time d = dds["Modified"].get_date();
			printf("%20s %15s %10i %10s \n",
				dds["Name"].get_string(),
				dds["Type"].get_string(),
				dds["Size"].get_int(),
				(d.date_string() + " " + d.time_string()).c_str());
			dds.next();
		}
		dds.close();
	}
	catch (Fl_Exception &exception) {
		puts(exception.text().c_str());
	}

return EXIT_SUCCESS;
}
