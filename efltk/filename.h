//
// "$Id$"
//
// Filename header file for the Fast Light Tool Kit (FLTK).
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

#ifndef FL_FILENAME_H
#define FL_FILENAME_H

#include "Enumerations.h" // for FL_API
#include "Fl_Util.h"

#define FL_PATH_MAX 1024 // all buffers are assummed to be at least this long

#if defined(_WIN32) && !defined(__CYGWIN__)

struct dirent {char d_name[1];};

#elif defined(__linux_)

#define __USE_LARGEFILE64
#define __USE_GNU
#include <sys/types.h>
#include <dirent.h>
#define dirent dirent64
#define scandir scandir64

#else

#include <sys/types.h>
#include <dirent.h>
// warning: on some systems (very few nowadays?) <dirent.h> may not exist.
// The correct information is in one of these files:
//#include <sys/ndir.h>
//#include <sys/dir.h>
//#include <ndir.h>
// plus you must do the following #define:
//#define dirent direct
// It would be best to create a <dirent.h> file that does this...

#endif

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

FL_API int fl_alphasort(struct dirent **, struct dirent **);
FL_API int fl_casealphasort(struct dirent **, struct dirent **);
FL_API int fl_casenumericsort(struct dirent **, struct dirent **);
FL_API int fl_numericsort(struct dirent **, struct dirent **);

typedef int (Fl_File_Sort_F)(struct dirent **, struct dirent **);

// Portable "scandir" function.  Ugly but necessary...
FL_API int fl_filename_list(const char *d, struct dirent ***l,
                            Fl_File_Sort_F *s = fl_numericsort);

#  ifdef __cplusplus
}
#endif

#endif

//
// End of "$Id$".
//
