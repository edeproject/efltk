/***************************************************************************
                                                    Fl_Directory_DS.cpp  -  description
                                                          -------------------
        begin                : Thu Nov 28 2002
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

#include <config.h>
#include "../core/fl_internal.h"

#include <efltk/filename.h>
#include <efltk/Fl_Directory_DS.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Pixmap.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#ifndef _WIN32
# include <unistd.h>
#endif

// REPLACE WITH XPM, now it's GIF
static const unsigned char exec_xpm[889] = {
    71,73,70,56,57,97,16,0,16,0,247,0,0,5,5,5,133,133,133,197,197,197,251,251,
    251,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,33,
    249,4,1,0,0,255,0,44,0,0,0,0,16,0,16,0,64,8,86,0,255,9,28,72,176,160,192,0,
    2,6,40,92,200,48,0,128,131,2,0,72,156,72,209,225,193,0,24,51,106,196,248,240,
    223,198,143,25,33,130,212,216,17,33,195,147,3,44,26,92,201,178,229,64,132,2,
    98,202,156,169,18,33,69,137,3,0,228,172,153,16,229,66,158,62,127,150,236,25,
    84,229,205,163,19,93,174,12,8,0,59};

static const char * document_xpm[] = {
    "16 16 4 1",
    " 	c None",
    ".	c #000000",
    "+	c #FFFFFF",
    "@	c #808080",
    "                ",
    "  ........      ",
    "  .+++++.@.     ",
    "  .+++++.+@.    ",
    "  .+++++.++@.   ",
    "  .+++++.....@  ",
    "  .++++++@@@.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  ...........@  ",
    "   @@@@@@@@@@@  ",
    "                "};

static const char * folder_xpm[] = {
    "16 16 5 1",
    " 	c None",
    ".	c #FFE79C",
    "+	c #C6864A",
    "@	c #FFC78C",
    "#	c #000000",
    "                ",
    "                ",
    "    ...+        ",
    "   @.@@@+       ",
    "  @@@@@@@@@@@@  ",
    " @@...........# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.+++++++++++# ",
    "  ############# ",
    "                ",
    "                "};

//static const Fl_Pixmap executablePixmap(exec_xpm);
static const Fl_Image executablePixmap(exec_xpm, sizeof(exec_xpm));
static const Fl_Pixmap folderPixmap(folder_xpm);
static const Fl_Pixmap documentPixmap(document_xpm);

#ifdef _WIN32

# include <windows.h>
# include <io.h>
# include <direct.h>

# define S_ISLNK(m)      (false)
# define S_ISEXEC(m)     (((m) & _S_IEXEC) == _S_IEXEC)
#if !defined(__GNUC__) && !defined(__BORLANDC__)
# define S_ISREG(m)      (((m) & _S_IFREG) == _S_IFREG)
# define S_ISDIR(m)      (((m) & _S_IFDIR) == _S_IFDIR)
# define S_ISBLK(m)      (((m) & _S_IFBLK) == _S_IFBLK)
#endif /* __GNUC__ */

# define lstat stat

#else /* _WIN32 */

# include <dirent.h>

#ifndef S_ISEXEC
# define S_ISEXEC(m)  (((m) & S_IEXEC) == S_IEXEC)
#endif
#ifndef S_ISREG
# define S_ISREG(m)   (((m) & S_IFMT) == S_IFREG)
#endif
#ifndef S_ISDIR
# define S_ISDIR(m)   (((m) & S_IFMT) == S_IFDIR)
#endif
#ifndef S_ISBLK
# define S_ISBLK(m)   (((m) & S_IFMT) == S_IFBLK)
#endif

#endif /* _WIN32 */

#define checkDSopen(ds) if (!ds) fl_throw("Dataset isn't open") 

      // access to the field by name
const Fl_Variant& Fl_Directory_DS::operator [] (const char *field_name) const {
    checkDSopen(m_current);
    return (*m_current)[field_name];
}

Fl_Variant& Fl_Directory_DS::operator [] (const char *field_name) {
    checkDSopen(m_current);
    return (*m_current)[field_name];
}

const Fl_Data_Field& Fl_Directory_DS::field (int field_index) const {
    checkDSopen(m_current);
    return m_current->field(field_index);
}

Fl_Data_Field& Fl_Directory_DS::field (int field_index) {
    checkDSopen(m_current);
    return m_current->field(field_index);
}

unsigned Fl_Directory_DS::record_count() const {
    checkDSopen(m_current);
    return m_list.count();
}

// how many fields do we have in the current record?
unsigned Fl_Directory_DS::field_count() const {
    checkDSopen(m_current);
    return m_current->count();
}

int Fl_Directory_DS::field_index(const char *field_name) const {
    checkDSopen(m_current);
    return m_current->field_index(field_name);
}

// access to the field by number, 0..field_count()-1
const Fl_Variant& Fl_Directory_DS::operator [] (int index) const {
    checkDSopen(m_current);
    return (*m_current)[index];
}

Fl_Variant& Fl_Directory_DS::operator [] (int index) {
    checkDSopen(m_current);
    return (*m_current)[index];
}

// read this field data into external value
bool Fl_Directory_DS::read_field(const char *fname,Fl_Variant& fvalue) {
    fl_try {
        fvalue = (*this)[fname];      
    }
    fl_catch(exc) {
        return false;
    }
    return true;
}

// write this field data from external value
bool Fl_Directory_DS::write_field(const char *fname, const Fl_Variant& fvalue) {
    fl_try {
        (*this)[fname] = fvalue;      
    }
     fl_catch(exc) {
    	  return false;
     }
     return true;
}

// Returns typename
Fl_String Fl_Directory_DS::get_file_type(const struct stat &st, const Fl_Image *&image) const {
    bool executable = S_ISEXEC(st.st_mode);
    image = &documentPixmap;
    
    Fl_String modeName;
    if(S_ISDIR(st.st_mode)) {
        modeName = _("Directory");
        executable = false;
        image = &folderPixmap;
    } 
    else if(S_ISREG(st.st_mode)) {
        if (executable) modeName = _("Executable");
        else modeName = _("File");
    }
    
    if(executable) image = &executablePixmap;
    
    return modeName;
}

// Define access mode constants if they aren't already defined.
#ifndef R_OK
# define R_OK 04
#endif

// dataset navigation

// read the directory() and move item into the first entry
bool Fl_Directory_DS::open() {
    clear();
    
    int dlen = m_directory.length()-1;
    if (dlen) {
        if (m_directory[dlen] != '\\' && m_directory[dlen] != '/')
            m_directory += slash;
    }
    
    dirent **files;
    int num_files = fl_filename_list(m_directory.c_str(), &files);
    
    if (num_files>0) {
        struct stat st;
        int again = 2;
        if(showpolicy() & NO_SORT || showpolicy() & HIDE_FILES) again--;
        do {
            for(int n=0; n < num_files; n++) {
                if(!files[n]) continue;
                
                if(!strcmp(files[n]->d_name, "..") || !strcmp(files[n]->d_name, ".")) continue;
                
                Fl_Data_Fields   *df = new Fl_Data_Fields;
                char		 *file = files[n]->d_name;
                bool is_link     = false;
                
                if((showpolicy()&HIDE_DOT_FILES) && file[0]=='.') continue;
                
                Fl_String        fullName = m_directory + file;
                
                lstat(fullName.c_str(), &st);
                
#ifndef _WIN32
                if ((st.st_mode & S_IFLNK) == S_IFLNK) {
                    is_link = true;
                    stat(fullName.c_str(), &st);
                }
#endif
                
                if(!S_ISDIR(st.st_mode) && !m_pattern.empty() && !fl_file_match(files[n]->d_name, m_pattern)) continue;
                if(!(showpolicy()&NO_SORT) && !S_ISDIR(st.st_mode) && again==2) continue;
                if((showpolicy()&HIDE_FILES) && !S_ISDIR(st.st_mode)) continue;
                if((showpolicy()&HIDE_DIRECTORIES) && S_ISDIR(st.st_mode)) continue;
                
                const Fl_Image *pixmapPtr = 0;
                Fl_String modeName = get_file_type(st, pixmapPtr);
                
                if(is_link) {
                    modeName += ' ';
                    modeName += _("link");
                }
                
                df->add("")				= pixmapPtr;
                df->add(N_("Name"))		= file;
                df->add(N_("Size"))		= (int)st.st_size;
                df->add(N_("Type"))		= modeName;
                df->add(N_("Modified"))	= Fl_Date_Time::convert(st.st_mtime);
                
                if(access(fullName, R_OK)!=0) {
                    df->field(0).flags = FL_INACTIVE | FL_ALIGN_LEFT;
                    df->field(1).flags = FL_INACTIVE | FL_ALIGN_LEFT;
                }
                
                m_list.append(df);
                
                free((struct dirent*)files[n]);
                files[n] = 0;
            }
        } while(--again);
        
        first();
        if(m_current) {
            field(0).flags = FL_ALIGN_LEFT;
            field(0).width = 3;
            field(1).flags = FL_ALIGN_LEFT;
            field(1).width = 30;
            field(2).flags = FL_ALIGN_LEFT;
            field(2).width = 10;
            field(3).flags = FL_ALIGN_LEFT;
            field(3).width = 10;
            field(4).flags = FL_ALIGN_LEFT;
            field(4).width = 16;
        }
        
        free((struct dirent**)files);
    }
    
    return (m_list.count()>0);
}

bool Fl_Directory_DS::close() {
    clear();
    return true;
}

bool Fl_Directory_DS::first() {
    if (m_list.count()) {
        m_currentIndex = 0;
        m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
        m_eof = false;
        return true;
    }
    m_eof = true;
    return false;
}

bool Fl_Directory_DS::last() {
    unsigned cnt = m_list.count();
    if (cnt) {
        m_currentIndex = cnt - 1;
        m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
        m_eof = false;
        return true;
    }
    m_eof = true;
    return false;
}

bool Fl_Directory_DS::next() {
    unsigned cnt = m_list.count();
    if (m_currentIndex + 1 < (int)cnt) {
        m_currentIndex++;
        m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
        m_eof = false;
        return true;
    }
    m_eof = true;
    return false;
}

bool Fl_Directory_DS::prior() {
    if (m_currentIndex > 0) {
        m_currentIndex--;
        m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
        m_eof = false;
        return true;
    }
    m_eof = true;
    return false;
}

bool Fl_Directory_DS::find(Fl_Variant position) {
    unsigned    cnt = m_list.count();
    Fl_String   name;
    unsigned i;
    switch (position.type()) {
        case VAR_INT:  if (position.get_int() < (int)cnt) {
                m_currentIndex = position.get_int();
                m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
                return true;
            }
            break;
        case VAR_STRING:
            name = position.get_string();
            for (i = 0; i < cnt; i++) {
                Fl_Data_Fields& entry = *(Fl_Data_Fields *)m_list[i];
                if (entry["name"] == name) {
                    m_currentIndex = i;
                    m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
                    return true;
                }
            }
            break;
        default:       break;
    }
    return false;
}

void Fl_Directory_DS::clear() {
    unsigned cnt = m_list.count();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Data_Fields *df = (Fl_Data_Fields *) m_list[i];
        delete df;
    }
    m_list.clear();
    m_current = 0L;
    m_currentIndex = -1;
    m_eof = true;
}
