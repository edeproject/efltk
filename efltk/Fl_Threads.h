// Inline classes to provide portable support for threads and mutexes.
//
// Fltk does not use this (it has an internal mutex implementation
// that is used if Fl::lock() is called). This header file's only
// purpose is so we can write portable demo programs. It may be useful
// or an inspiration to people who want to try writing multithreaded
// programs themselves.
//
// Fltk has no multithreaded support unless the main thread calls Fl::lock().
// This main thread is the only thread allowed to call Fl::run or Fl::wait.
// From then on fltk will be locked except when the main thread is actually
// waiting for events from the user. Other threads must call Fl::lock() and
// Fl::unlock() to surround calls to fltk (such as to change widgets or
// redraw them).

#ifndef Fl_Threads_H
#define Fl_Threads_H

#include "Fl_Thread.h"

#endif
