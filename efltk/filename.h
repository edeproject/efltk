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

#ifndef _FL_FILENAME_H_
#define _FL_FILENAME_H_

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
