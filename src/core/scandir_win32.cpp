/*
 * $Id$
 *
 * WIN32 scandir function for the Fast Light Tool Kit (FLTK).
 *
 * Copyright 1998-2002 by Bill Spitzak and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems to "fltk-bugs@fltk.org".
 */

/* Emulation of posix scandir() call */
#include <config.h>
#include <efltk/fl_utf8.h>
#include <efltk/Fl_Exception.h>
#include <efltk/filename.h>
#include <windows.h>
#include <stdlib.h>

int fl_scandir(const char *dirname, struct dirent ***namelist,
               int (*select)(struct dirent *),
               int (*compar)(struct dirent **, struct dirent **))
{	
    WIN32_FIND_DATA find;
    HANDLE h;
    int nDir = 0, NDir = 0;
    struct dirent **dir = 0, *selectDir;
    unsigned long ret;	
	unsigned short *wbuf;

    Fl_String findIn(dirname);
	
	//Convert unix '/' to windows '\'
	for(int n=0; n<findIn.length(); n++) if(findIn[n]=='/') findIn[n]='\\';

	if(findIn.empty()) { 
		findIn = ".\\*";
	}
	else if(findIn[findIn.length()-1] != '\\') {	
		findIn += "\\*";
	} 
	else if(findIn[findIn.length()-1] == '\\') { 
		findIn += '*';
	}

#ifdef UNICODE
	findIn.to_unicode(wbuf);
	h = FindFirstFile((wchar_t *)wbuf, &find);
	free((unsigned short*)wbuf);
#else
	h = FindFirstFile(fl_utf2mbcs(findIn.c_str()), &find);
#endif

    if(h==INVALID_HANDLE_VALUE) {
        ret = GetLastError();
        if (ret != ERROR_NO_MORE_FILES) {
			TCHAR msgbuf[1024];
#ifdef UNICODE
			int msgbuf_len = 
#endif
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                ret,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&msgbuf,
                sizeof(msgbuf),
                NULL);
#ifdef UNICODE
			fl_throw(Fl_String::from_unicode(msgbuf, msgbuf_len)); 
#else
			fl_throw(msgbuf);      
#endif
        }
        *namelist = dir;
        return nDir;
    }
    do {
#ifdef UNICODE
		int l = wcslen(find.cFileName);
#else
		int l = strlen(find.cFileName);
#endif
        selectDir = (struct dirent*)malloc(sizeof(struct dirent)+(l*5)+1);
#ifdef UNICODE
		l = fl_unicode2utf((unsigned short *)find.cFileName, l, selectDir->d_name);
#else
		wbuf = (unsigned short*)malloc(sizeof(short) * (l+1));
		l = mbstowcs((wchar_t *)wbuf, find.cFileName, l);
		l = fl_unicode2utf(wbuf, l, selectDir->d_name);
		free((unsigned short*)wbuf);
#endif
		selectDir->d_name[l] = 0;

        if(find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            selectDir->d_type = DT_DIR;
        } else
			selectDir->d_type = DT_REG;

        if(!select || (*select)(selectDir)) {
            if(nDir==NDir) {
				if(!dir) dir = (dirent **)malloc(sizeof(struct dirent*) * 33);
				else dir = (dirent **)realloc(dir, sizeof(struct dirent*) * (NDir+33));                
				NDir += 32;
            }
            dir[nDir] = selectDir;
            nDir++;
            dir[nDir] = 0;
        } else {
            free((struct dirent*)selectDir);
        }
    } 
	while(FindNextFile(h, &find));			

    ret = GetLastError();
    if (ret != ERROR_NO_MORE_FILES) {
			TCHAR msgbuf[1024];
#ifdef UNICODE
			int msgbuf_len = 
#endif
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				ret,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&msgbuf,
				sizeof(msgbuf),
				NULL);
			FindClose(h);
#ifdef UNICODE
			fl_throw(Fl_String::from_unicode(msgbuf, msgbuf_len)); 
#else
			fl_throw(msgbuf);
#endif
    } else
		FindClose(h);

    if(compar) qsort(dir, nDir, sizeof(*dir), (int(*)(const void*, const void*))compar);

    *namelist = dir;
    return nDir;
}
