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
#include <stdio.h>
#include <stdlib.h>
#include <efltk/Fl_Buffer.h>
#include <efltk/Fl_Exception.h>

Fl_Buffer::Fl_Buffer(unsigned sz) {
    m_buffer = (char *)calloc(1,sz);
    if (m_buffer) {
        m_size = sz; 
    } else {
        m_size = 0;
    }
    m_bytes = 0;
}

Fl_Buffer::~Fl_Buffer() {
    free(m_buffer);
    m_buffer = NULL;
}

bool Fl_Buffer::check_size(unsigned sz) {
    if (sz >= m_size) {
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
    check_size(sz);
    if (data)
        memcpy(m_buffer,data,sz);
    m_bytes = sz;
}

void Fl_Buffer::set(const Fl_Buffer& buffer) {
    check_size(buffer.bytes());
    memcpy(m_buffer,buffer.data(),buffer.bytes());
    m_bytes = buffer.bytes();
}

void Fl_Buffer::set(const Fl_String& str) {
    set(str.c_str(), str.length());
}

void Fl_Buffer::append(char ch) {
    check_size(m_bytes + 1);
    m_buffer[m_bytes] = ch;
    m_bytes++;
}

void Fl_Buffer::append(const char *data,unsigned sz) {
    check_size(m_bytes + sz);
    if (data)
        memcpy(m_buffer+m_bytes,data,sz);
    m_bytes += sz;
}

void Fl_Buffer::append(const Fl_Buffer& buffer) {
    check_size(m_bytes + buffer.bytes());
    memcpy(m_buffer+m_bytes,buffer.data(),buffer.bytes());
    m_bytes += buffer.bytes();
}

void Fl_Buffer::append(const Fl_String& str) {
    append(str.c_str(), str.length());
}

void Fl_Buffer::fill(char c) {
    memset(m_buffer, c,m_size);
}

void Fl_Buffer::reset() {
    unsigned m_size = 16;
    m_buffer = (char *)realloc(m_buffer,m_size);
    m_bytes = 0;
}

void Fl_Buffer::read_file(const char *fileName) 
{
    FILE *f = fopen(fileName, "rb");
    if (!f) {
        fl_throw("Can't open file <" + Fl_String(fileName) + "> for reading");
		return;
	}
    fseek(f,0,SEEK_END);
    unsigned fileLength = ftell(f);
    fseek(f,0,SEEK_SET);
    bytes(fileLength);
    char *ptr = m_buffer;
    unsigned p=0;
    while(p < fileLength) {
        p += fread( (ptr+p), 1, 1024, f);
    }
    fclose(f);
}

void Fl_Buffer::save_file(const char *fileName) 
{
    FILE *f = fopen(fileName, "w+b");
    if (!f) {
        fl_throw("Can't open file <" + Fl_String(fileName) + "> for writing");
        return;
    }

    char *ptr = m_buffer;
    unsigned p = 0;
    while(p < m_bytes)
    {
        int bytes = m_bytes - p;
        if (bytes > 1024)
            bytes = 1024;
        p += fwrite( (ptr+p) ,1, bytes, f);
    }
    fclose(f);
}
