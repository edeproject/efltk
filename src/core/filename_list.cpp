
//
// "$Id$"
//
// Filename list routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2002 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

// Wrapper for scandir with const-correct function prototypes.

#include <config.h>

#ifdef _WIN32_WCE
#include <wince.h>
#endif

#include <efltk/filename.h>
#include <efltk/Fl_String.h>

#if defined(__linux__)

# define __USE_LARGEFILE64
# define __USE_GNU
# include <sys/types.h>
# include <dirent.h>
# define dirent dirent64
# define scandir scandir64

#endif


#if !HAVE_SCANDIR
  extern int fl_scandir(const char *dir, dirent ***namelist,
						int (*select)(dirent *),
						int (*compar)(dirent **, dirent **));
#endif

int fl_filename_list(const char *dir, dirent ***list, Fl_File_Sort_F *sort) 
{
#if defined(__hpux)
    // HP-UX defines the comparison function like this:
    return scandir(dir, list, 0, (int(*)(const dirent **, const dirent **))sort);
#elif defined(__osf__)
    // OSF, DU 4.0x
    return scandir(dir, list, 0, (int(*)(dirent **, dirent **))sort);
#elif defined(_AIX)
    // AIX is almost standard...
    return scandir(dir, list, 0, (int(*)(void*, void*))sort);
#elif HAVE_SCANDIR && !defined(__sgi)
    // The vast majority of Unix systems want the sort function to have this
    // prototype, most likely so that it can be passed to qsort without any
    // changes:
    return scandir(dir, list, 0, (int(*)(const void*,const void*))sort);
#else
    // This version is when we define our own scandir (WIN32 and perhaps
    // some Unix systems) and apparently on Irix:
    return fl_scandir(dir, list, 0, sort);
#endif
}

//
// End of "$Id$".
//
