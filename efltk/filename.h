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

 struct dirent { char d_name[1]; };

#endif

// File list sort function type
typedef int (Fl_File_Sort_F)(struct dirent **, struct dirent **);
// Pre-defined sort functions
extern FL_API int fl_alphasort(struct dirent **, struct dirent **);
extern FL_API int fl_casealphasort(struct dirent **, struct dirent **);

// Portable "scandir" function.  Ugly but necessary...
extern FL_API int fl_filename_list(const char *dir, struct dirent ***list, Fl_File_Sort_F *sort = fl_alphasort);


// Returns pointer to .ext or NULL if no extension
extern FL_API const char *fl_file_getext(const char *filename);
// Returns extension ".ext" of file as Fl_String.
extern FL_API Fl_String fl_file_getext(const Fl_String &filename);

// Change / Add extension, returns pointer to filename
extern FL_API char *fl_file_setext(char *filename, const char *ext);
// Change / Add extension, returns new Fl_String with changed extension
extern FL_API Fl_String fl_file_setext(const Fl_String &, const char *ext);

// Strip path from absolute path filename. Returns pointer to filename
extern FL_API const char *fl_file_filename(const char *filename);
// Strip path from absolute path filename. Returns Fl_String
extern FL_API Fl_String fl_file_filename(const Fl_String &);

// Expand filename, Convert $x and ~x to strings. Returns true, if anything converted
extern FL_API bool fl_file_expand(char *buf, int buf_len, const char *from);
// Expand filename, Convert $x and ~x to strings. Returns converted Fl_String
extern FL_API Fl_String fl_file_expand(const Fl_String &from);

// prepend getcwd()
extern FL_API bool fl_file_absolute(char *buf, int buf_len, const char *from);
// prepend getcwd()
extern FL_API Fl_String fl_file_absolute(const Fl_String &from);

// glob match
extern FL_API bool fl_file_match(const char *, const char *pattern); 

// Returns homepath in WIN32 and Linux
extern FL_API char *fl_get_homedir();
extern FL_API const Fl_String &fl_homedir();

// Check if given file exists on disk
extern FL_API bool fl_file_exists(const char *name);

// Check if given name is dir
extern FL_API bool fl_is_dir(const char *path);

class FL_API Fl_FileAttr
{
public:
	Fl_FileAttr() { size=0; flags=0; }

	enum {
		DIR       = 1, //Directory
		FILE      = 2, //Regular file
		LINK   = 4, //Sym link (ignored on WIN32)
		DEVICE = 8  //Logical disk (ignored on Linux)
	};
	bool parse(const char *filename);
	
	ulong size; // size of file
	ulong modified; // time modified
	char time[128]; // time modified str
	Fl_Flags flags; // type flags

#ifdef _WIN32
	uint64 free; //Free space
	uint64 capacity; //total capacity space
#endif
};

extern FL_API Fl_FileAttr *fl_file_attr(const char *name);

// Backward compatibility..
inline bool fl_file_absolute(char *buf, const char *from) { return fl_file_absolute(buf, FL_PATH_MAX, from); }

#define FL_DIR	  Fl_FileAttr::DIR
#define FL_FILE   Fl_FileAttr::FILE
#define FL_LINK   Fl_FileAttr::LINK
#define FL_DEVICE Fl_FileAttr::DEVICE

#endif
