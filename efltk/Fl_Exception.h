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

#ifndef _FL_EXCEPTION_H_
#define _FL_EXCEPTION_H_

/*
 *
 * fl_throw_(text, file, line):
 * Throw exception with given attributes
 *
 * fl_throw(text):
 * Same as before, file and line are appended automatically
 *
 * fl_rethrow:
 * Re-throw last exception, This should be called from catch statement
 * So next catch statement will receive same exception.
 *
 * fl_try:
 * Normal try statement begin.
 * NOTE: Do NOT return from try block, that will cause jump buffer stack size exceed!
 *       You are allowed to return after try/catch or from catch block.
 *
 * fl_catch(exception):
 * 'exception' is always Fl_Exception.
 *
 * void (*fl_exception_handler)(Fl_Exception &e):
 * This function is called for every unhandled exceptions.
 * Default handler terminates application run.
 *
 */

#include "Fl_String.h"
#include "Fl_Export.h"

class Fl_Exception {
public:
	Fl_Exception(Fl_String text="", const char *p="", int line=0);
	Fl_String text(bool shortVersion=false) const;

	Fl_Exception& operator = (Fl_Exception &src) { m_file=src.m_file; m_text=src.m_text; m_line=src.m_line; return *this; }
protected:
	Fl_String m_text;
	const char *m_file;
	int m_line;
};

#ifndef STD_EXCEPTIONS

/*
 * EFltk exception interface.
 * This behaves pretty much like std C++ exceptions.
 * with some limitations, though... :)
 *
 * Comparing to STD C++ exceptions, this seems to be much
 * faster! Looping 100k times loop, which throw's exception once 
 * and re-throws once, results: STD=780ms, EFLTK=20ms..
 * Without throws, STD=~20ms, EFLTK=~10ms
 *
 * Tested on VCPP6.0 under Win2000. Compiled release mode.
 */
#include <setjmp.h>

////////////////////////////////////////////
// BEGIN OF EFLTK EXCEPTIONS PRIVATE STUFF

class Fl_JmpBuf_Stack
{
	int items;
    jmp_buf *jumpbufs;
public:
	Fl_JmpBuf_Stack();
	~Fl_JmpBuf_Stack();
	jmp_buf &push();
	jmp_buf *peek();
	jmp_buf *pop();
};

extern FL_API void (*fl_exception_handler)(Fl_Exception &e);
extern FL_API Fl_Exception fl_last_throwed_exception;
extern FL_API bool fl_exception_was_throwed;
extern FL_API Fl_JmpBuf_Stack fl_jmpbuf_stack;

// END OF EFLTK EXCEPTIONS PRIVATE STUFF
//////////////////////////////////////////

#define fl_try fl_exception_was_throwed=false; if(!setjmp(fl_jmpbuf_stack.push()))
#define fl_catch(exception_variable) fl_jmpbuf_stack.pop(); Fl_Exception exception_variable=fl_last_throwed_exception; ((void)(exception_variable)); if(fl_exception_was_throwed)
#define fl_throw_exception(e) { fl_last_throwed_exception=e; fl_exception_was_throwed=true; jmp_buf *jmp=fl_jmpbuf_stack.peek(); if(jmp) longjmp(*jmp, 0); else fl_exception_handler(e); }
#define fl_rethrow fl_throw_exception(fl_last_throwed_exception)
#define fl_throw_(text, file, line) { Fl_Exception e(text, file, line); fl_throw_exception(e); }

#else /* STD_EXCEPTIONS */

/*
 * Std C++ exception interface
 */
#define fl_try try
#define fl_catch(exception_variable) catch(Fl_Exception& exception_variable)
#define fl_throw_(text, file, line) throw Fl_Exception(text, file, line);
#define fl_rethrow throw

#endif /* STD_EXCEPTIONS */

//Shortcut...
#define fl_throw(a) fl_throw_(a, __FILE__, __LINE__)

#endif
