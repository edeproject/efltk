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
#include <efltk/fl_utf8.h>
#include <efltk/filename.h>
#include <windows.h>
#include <stdlib.h>

int fl_scandir(const char *dirname, struct dirent ***namelist,
               int (*select)(struct dirent *),
               int (*compar)(struct dirent **, struct dirent **))
{	
    int len;
    char *findIn;
    WIN32_FIND_DATAA find;
	WIN32_FIND_DATAW findw;
    HANDLE h;
    int nDir = 0, NDir = 0;
    struct dirent **dir = 0, *selectDir;
    unsigned long ret;	
	unsigned short *wbuf;

    len    = strlen(dirname);
    findIn = (char *)malloc(len+5);
    if (!findIn) return -1;

    memcpy(findIn, dirname, len);
	
	//Convert unix '/' to windows '\'
	for(char *d = findIn; *d; d++) if(*d=='/') *d='\\';

	if(len>0 && (findIn[len-1]!='\\')) {	
		findIn[len++] = '\\';
		findIn[len++] = '*';
	} 
	else if(len>0 && (findIn[len-1]=='\\')) { 
		findIn[len++] = '*';
	}
	else if(len==0) { 
		findIn[len++] = '.';
		findIn[len++] = '\\';
		findIn[len++] = '*';
	}
	findIn[len] = '\0';

#ifdef _WIN32_WCE
	wbuf = (unsigned short*)malloc(sizeof(short) *(len + 10));
	wbuf[fl_utf2unicode((const unsigned char*)findIn, len, wbuf)] = 0;
	h = FindFirstFileW((wchar_t *)wbuf, &findw);
	free((unsigned short*)wbuf);
#else
	if (fl_is_nt4()) {
		wbuf = (unsigned short*)malloc(sizeof(short) *(len + 10));
		wbuf[fl_utf2unicode((const unsigned char*)findIn, len, wbuf)] = 0;
		h = FindFirstFileW((wchar_t *)wbuf, &findw);
		free((unsigned short*)wbuf);
	} else {
		h=FindFirstFileA(fl_utf2mbcs(findIn), &find);
	}
#endif

    if(h==INVALID_HANDLE_VALUE) {
        free((char*)findIn);
        ret = GetLastError();
        if (ret != ERROR_NO_MORE_FILES) {
            /* TODO: return some error code */
        }
        *namelist = dir;
        return nDir;
    }
    do {
		int l;
		if(fl_is_nt4() || fl_is_ce()) {
			l = wcslen(findw.cFileName);
		} else {
			l = strlen(find.cFileName);
		}
        selectDir = (struct dirent*)malloc(sizeof(struct dirent)+(l*5)+1);
		if (fl_is_nt4() || fl_is_ce()) {
			l = fl_unicode2utf((unsigned short *)findw.cFileName, l, selectDir->d_name);
		} else {
			wbuf = (unsigned short*)malloc(sizeof(short) * (l+1));
			l = mbstowcs((wchar_t *)wbuf, find.cFileName, l);
			l = fl_unicode2utf(wbuf, l, selectDir->d_name);
			free((unsigned short*)wbuf);
		}
		selectDir->d_name[l] = 0;

        /*if(find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            ...
        }*/
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
            free(selectDir);
        }
    } 
#ifndef _WIN32_WCE
	while ( (fl_is_nt4() && FindNextFileW(h, &findw)) || 
			(!fl_is_nt4() && FindNextFileA(h, &find)));
#else
	while ( FindNextFileW(h, &findw));			
#endif

    ret = GetLastError();
    if (ret != ERROR_NO_MORE_FILES) {
        /* TODO: return some error code */
    }
    FindClose(h);

    free((char*)findIn);

    if(compar) qsort(dir, nDir, sizeof(*dir), (int(*)(const void*, const void*))compar);

    *namelist = dir;
    return nDir;
}
