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

#include <sys/types.h>
#include <sys/stat.h>
#include <efltk/filename.h>
#include <efltk/Fl_Directory_DS.h>

#ifndef _WIN32

# include <dirent.h>

#else

# include <windows.h>
# include <io.h>
# include <direct.h>

# define S_ISLNK(m)      (false)
# define S_ISEXEC(m)     (((m) & _S_IFMT) == _S_IEXEC)
#ifndef __GNUC__
# define S_ISREG(m)      (((m) & _S_IFMT) == _S_IFREG)
# define S_ISDIR(m)      (((m) & _S_IFMT) == _S_IFDIR)
# define S_ISBLK(m)      (((m) & _S_IFMT) == _S_IFBLK)
#endif /* __GNUC__ */

# define lstat stat

#endif

#if defined(__linux) && defined(__GNUC__)
# define S_ISEXEC(m)	  (((m) & S_IFMT) == S_IEXEC)
# define S_ISREG(m) 	 (((m) & S_IFMT) == S_IFREG) 
# define S_ISDIR(m) 	 (((m) & S_IFMT) == S_IFDIR) 
# define S_ISBLK(m) 	 (((m) & S_IFMT) == S_IFBLK)
#endif

#ifdef __sun  
# define S_ISEXEC(m)	  (((m) & S_IFMT) == S_IEXEC)
//# define S_ISREG(m) 	 (((m) & S_IFMT) == S_IFREG) 
//# define S_ISDIR(m) 	 (((m) & S_IFMT) == S_IFDIR) 
//# define S_ISBLK(m) 	 (((m) & S_IFMT) == S_IFBLK)
#endif

static Fl_Variant    notFound;
static Fl_Data_Field fieldNotFound("not_found");

   // access to the field by name
const Fl_Variant& Fl_Directory_DS::operator [] (const char *field_name) const {
   if (m_current)
         return (*m_current)[field_name];
   else  return notFound;
}

Fl_Variant& Fl_Directory_DS::operator [] (const char *field_name) {
   if (m_current)
         return (*m_current)[field_name];
   else  return notFound;
}

const Fl_Data_Field& Fl_Directory_DS::field (int field_index) const {
   if (m_current)
         return m_current->field(field_index);
   else  return fieldNotFound;
}

Fl_Data_Field& Fl_Directory_DS::field (int field_index) {
   if (m_current)
         return m_current->field(field_index);
   else  return fieldNotFound;
}

// how many fields do we have in the current record?
unsigned Fl_Directory_DS::field_count() const {
   if (m_current)
         return m_current->count();
   else  return 0;
}

int Fl_Directory_DS::field_index(const char *field_name) const {
   if (m_current)
         return m_current->field_index(field_name);
   else  return -1;
}

// access to the field by number, 0..field_count()-1
const Fl_Variant& Fl_Directory_DS::operator [] (int index) const {
   if (m_current)
         return (*m_current)[index];
   else  return notFound;
}

Fl_Variant& Fl_Directory_DS::operator [] (int index) {
   if (m_current)
         return (*m_current)[index];
   else  return notFound;
}

// read this field data into external value
bool Fl_Directory_DS::read_field(const char *fname,Fl_Variant& fvalue) {
   fvalue = (*this)[fname];
   return &fvalue != &notFound;
}

// write this field data from external value
bool Fl_Directory_DS::write_field(const char *fname,const Fl_Variant& fvalue) {
   (*this)[fname] = fvalue;
   return &fvalue != &notFound;
}

// dataset navigation
#include <stdio.h>

// read the directory() and move item into the first entry
bool Fl_Directory_DS::open() {

   clear();

   int dlen = m_directory.length();
   if (dlen) {
      dlen--;
      if (m_directory[dlen] != '\\' && m_directory[dlen] != '/') {
#ifdef _WIN32
         m_directory += "\\";
#else
         m_directory += "/";
#endif
      }
   }

   unsigned num_files = 0;

   dirent **files;
   num_files = fl_filename_list(m_directory.c_str(), &files);

   struct stat st;
   if(num_files) {
      for (unsigned n = 0; n < num_files; n ++) {
         Fl_Data_Fields&  df = *(new Fl_Data_Fields);
         dirent          *file = files[n];
         Fl_String        fullName = m_directory + file->d_name;
         lstat(fullName.c_str(),&st);

         df["name"] = file->d_name;
         df["size"] = (int) st.st_size;
         df["modified"] = Fl_Date_Time::convert(st.st_mtime);

         bool executable = S_ISEXEC(st.st_mode);

         Fl_String modeName;
         if(S_ISDIR(st.st_mode)) {
            modeName = "directory";
            executable = false;
         }
         if(S_ISREG(st.st_mode))
            modeName = "file";
#ifndef _WIN32
         if ((st.st_mode & S_IFLNK) == S_IFLNK) {
            stat(fullName.c_str(),&st);
            if ((st.st_mode & S_IFDIR) == S_IFDIR) {
               modeName = "directory";
               executable = false;
            }
            if ((st.st_mode & S_IFREG) == S_IFREG)
               modeName = "file";
            modeName += " link";
         }
#endif

         if (executable)
               df["executable"] = "*";
         else  df["executable"] = " ";

         df["type"] = modeName.c_str();

         if (n==0) {
            m_current = &df;
            field(0).align = FL_ALIGN_LEFT;
            field(0).width = 30;
            field(1).align = FL_ALIGN_RIGHT;
            field(1).width = 10;
            field(2).align = FL_ALIGN_LEFT;
            field(2).width = 16;
            field(3).align = FL_ALIGN_LEFT;
            field(3).width = 2;
            field(4).align = FL_ALIGN_LEFT;
            field(4).width = 15;
         }

         m_list.append(&df);

         free(file);
      }
   }

   free(files);
   first();

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
