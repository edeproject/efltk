/***************************************************************************
                          Fl_Buffer.h  -  description
                             -------------------
    begin                : Sun Feb 2 2003
    copyright            : (C) 2000 by Alexey S.Parshin
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

#ifndef __FL_BUFFER_H__
#define __FL_BUFFER_H__

#include <efltk/Fl_Export.h>

class FL_API Fl_Buffer {
protected:
   unsigned m_size;
   unsigned m_bytes;
   char *   m_buffer;
public:
   Fl_Buffer(unsigned sz=16);
   ~Fl_Buffer();
   char *data() const { return m_buffer; }
   bool check_size(unsigned sz);
   void set(const char *data,unsigned sz);
   bool append(const char *data,unsigned sz);
   void reset(unsigned sz=0);
   void fill(char c);

   unsigned size()  const { return m_size; }
   unsigned bytes() const { return m_bytes; }
   void bytes(unsigned b) { set(NULL,b); }
};

class FL_API Fl_String_Buffer {
public:
   Fl_String_Buffer(unsigned sz=16) : Fl_Buffer(sz) {}
   char& operator [] (int ndx) { return mbuffer[ndx]; }
};

#endif
