/***************************************************************************
                          main.cpp  -  description
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

#include <stdlib.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_Directory_DS.h>

int main(int argc, char *argv[])
{
   Fl_Directory_DS   dds;

   dds.directory("/usr/lib");

   Fl_Window *window = new Fl_Window(400,300);
   Fl_ListView *lv = new Fl_ListView(10,10,380,280);
   lv->fill(dds);
   window->end();
   window->show(argc, argv);

   Fl::run();

   return EXIT_SUCCESS;
}
