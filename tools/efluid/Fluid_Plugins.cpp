//
// "$Id$"
//
// Plugins code for the Fast Light Tool Kit (FLTK).
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <efltk/Fl.h>
#include "Fluid_Plugins.h"
#include <efltk/Fl_Menu_Item.h>
#include <efltk/fl_load_plugin.h>
#include <config.h> // for strcasecmp

Fluid_Plugin* plugins[MAXPLUGINS];
int nbplugins;
Fl_Menu_Item Plugins_Options_Menu[MAXPLUGINS+1];
Fl_Menu_Item Plugins_New_Menu[MAXPLUGINS+1];

#if HAVE_DLOPEN

#include <efltk/filename.h>
static int nboptions;
static int nbnew;

static void ReadPlugin(char* s, const char* location)
{
  if(nbplugins >= MAXPLUGINS) return;

  if(!strcmp(s+strlen(s)-sizeof(PLUGINS_EXTENSION)+1, PLUGINS_EXTENSION)) {
    char s2[256];

    sprintf(s2, "%s%s", location, s);

    Fluid_Plugin* d = (Fluid_Plugin*)fl_load_plugin(s2, "fluid_plugin");

    if (d) {
      s[strlen(s)-sizeof(PLUGINS_EXTENSION)+1] = 0;

      int i;
      for(i=0; i<nbplugins; i++) if(!strcmp(d->name, plugins[i]->name)) break;
      if(i<nbplugins) 
	fprintf(stderr, "Duplicate FLUID plugin, only the first one will be loaded ...\n");
      else {
	fprintf(stderr, "Found FLUID plugin '%s' ...\n", s);
	if(d->options_menu) {
	  Plugins_Options_Menu[nboptions].text = d->name;
	  Plugins_Options_Menu[nboptions].user_data_ = d->options_menu;
	  Plugins_Options_Menu[nboptions].flags = FL_SUBMENU_POINTER;
	  nboptions++;
	}
	if(d->new_menu) {
	  Plugins_New_Menu[nbnew].text = d->name;
	  Plugins_New_Menu[nbnew].user_data_ = d->new_menu;
	  Plugins_New_Menu[nbnew].flags = FL_SUBMENU_POINTER;
	  fill_in_New_Menu(d->new_menu);
	  nbnew++;
	}
	plugins[nbplugins++] = d;
      }
    }
  }
}

static void ReadPlugins(const char* location)
{
  dirent **d = 0;
  int n = fl_filename_list(location, &d);

  if (n <= 0)
    return;

//  printf("ReadPlugins: n = %d\n", n);

  for (int i = 0; i < n; i ++) 
  {
    ReadPlugin(d[i]->d_name, location);
//    free((void*)(d[i]));
  }
  free((void*)d);
}

// Here, we create some useless object just to be sure that the whole 
// FLTK library will be linked in fluid.
// This function even do not need to be called ...
//#include <efltk/Fl_Pixmap.h>
void link_whole_fltk()
{
    //new Fl_Pixmap((char**)0);
  // add some more if you get problems when reading your plugins ...
}

void read_plugins()
{
  // Priority order in case of duplicate plugin name is from the most local to the most global
  ReadPlugins("plugins/");
  ReadPlugins("./");
#ifndef _WIN32
  char s[256];
  sprintf(s, "%s/.fluid/plugins/", getenv("HOME"));
  ReadPlugins(s);
  ReadPlugins("/usr/local/lib/efltk/fluid/");
#endif
}

#else

void read_plugins() {}

#endif

//
// End of "$Id$"
//
