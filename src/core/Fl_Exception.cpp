/***************************************************************************
                          Fl_Exception.cpp  -  description
                             -------------------
    begin                : Thu Apr 27 2000
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

#include <efltk/Fl_Exception.h>
#include <efltk/Fl.h>

static void default_exception_handler(Fl_Exception &e) {
	Fl::fatal("Unhandled exception:\n%s", e.text());
}

void (*fl_exception_handler)(Fl_Exception &e) = default_exception_handler;

/////////////////////////////
// Jump Buf Stack

#define JUMPSTACK_SIZE 1024

Fl_JmpBuf_Stack::Fl_JmpBuf_Stack() {
	items = 0;
	jumpbufs = (jmp_buf*)malloc(sizeof(jmp_buf)*JUMPSTACK_SIZE);
}

Fl_JmpBuf_Stack::~Fl_JmpBuf_Stack() {
	free((jmp_buf*)jumpbufs);
}

jmp_buf &Fl_JmpBuf_Stack::push() {
	int index = items++;
	if(index>JUMPSTACK_SIZE) Fl::fatal("EFltk exceptions jumpstack size exceed!\n");
	if(index<0) index=0;
	return jumpbufs[index];
}

jmp_buf *Fl_JmpBuf_Stack::pop() {
	int index = --items;
	if(index<0) { items=0; return 0; }
	return &jumpbufs[index];
}

jmp_buf *Fl_JmpBuf_Stack::peek() {
	int index = items-1;
	if(index<0) { items=0; return 0; }
	return &jumpbufs[index];
}

/////////////////////////////

Fl_JmpBuf_Stack fl_jmpbuf_stack;
Fl_Exception fl_last_throwed_exception;
bool fl_exception_was_throwed;

Fl_Exception::Fl_Exception(const char *text, const char *file, int line) {
   m_file = file;
   m_text = text;
   m_line = line;
}

Fl_String Fl_Exception::text(bool shortVersion) const {	
	if(!shortVersion && m_line) {
		Fl_String ret;
		return ret.printf("Error in file \'%s\' [%d]: %s", m_file, m_line, m_text);
	}
	return Fl_String(m_text);
}
