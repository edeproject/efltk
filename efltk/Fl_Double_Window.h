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

#ifndef _FL_DOUBLE_WINDOW_H_
#define _FL_DOUBLE_WINDOW_H_

#include "Fl_Window.h"

class FL_API Fl_Double_Window : public Fl_Window {
public:
    Fl_Double_Window(int W, int H, const char *l = 0);
    Fl_Double_Window(int X, int Y, int W, int H, const char *l = 0);
    ~Fl_Double_Window();

    virtual void layout();

protected:
    virtual void create();
    virtual void flush();
    void flush(bool eraseoverlay);
    virtual void destroy();

private:
    void free_backbuffer();
};

#endif
