/***************************************************************************
                          Fl_Buffer.cpp  -  description
                             -------------------
    begin                : Sun Feb 2 2003
    copyright            : (C) 2003 by Alexey S.Parshin
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

#include <string.h>
#include <stdlib.h>
#include <efltk/Fl_Buffer.h>
#include <efltk/Fl_Exception.h>

Fl_Buffer::Fl_Buffer(unsigned sz) {
   m_buffer = (char *)calloc(1,sz);
   if (m_buffer) {
      m_size = sz; 
   } else { m_size = 0;
      m_bytes = 0;
   }
}

Fl_Buffer::~Fl_Buffer() {
   free(m_buffer);
   m_buffer = NULL;
}

bool Fl_Buffer::check_size(unsigned sz) {
   if (sz > m_size) {
      unsigned newSize = sz * 5 / 4 + 1;
      char *p = (char *)realloc(m_buffer,newSize + 1);
      if (!p)
         fl_throw ("Can't reallocate a buffer");
      m_buffer = p;
      m_size = newSize;
   }
   return true;
}

void Fl_Buffer::set(const char *data,unsigned sz) {
   if ( check_size(sz) ) {
      if (data)
         memcpy(m_buffer,data,sz);
      m_bytes = sz;
   }
}

bool Fl_Buffer::append(const char *data,unsigned sz) {
   if ( check_size(sz) ) {
      if (data)
         memcpy(m_buffer+m_bytes,data,sz);
      m_bytes += sz;
      return true;
   }
   return false;
}

void Fl_Buffer::fill(char c) {
   memset(m_buffer,c,m_size);
}

void Fl_Buffer::reset(unsigned sz) {
   if (sz) {
      char *p = (char *)realloc(m_buffer,sz + 1);
      if (!p)
         fl_throw("Can't reallocate a buffer");
      m_buffer = p;
      m_size = sz;
   }
   m_bytes = 0;
}
