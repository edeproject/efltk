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

#ifndef _FL_PIXMAP_H_
#define _FL_PIXMAP_H_

#include "Fl_Image.h"

/*
 * Fl_Pixmap is good for static XPM's
 * like built-in images, It parses image only
 * when it's needed. i.e. just before first draw.
 * This allows applications run w/o X11 running. (e.g. efluid -c)
 */

class FL_API Fl_Pixmap : public Fl_Image
{
public:
    Fl_Pixmap(char * const *d) : Fl_Image() { data = (const char **)d; measure(m_width, m_height); }
    Fl_Pixmap(uchar* const *d) : Fl_Image() { data = (const char **)d; measure(m_width, m_height); }
    Fl_Pixmap(const char * const *d) : Fl_Image() { data = (const char **)d; measure(m_width, m_height); }
    Fl_Pixmap(const uchar* const *d) : Fl_Image() { data = (const char **)d; measure(m_width, m_height); }
    virtual ~Fl_Pixmap() { }

    virtual void measure(int &w, int &h);

    const char * const * data; //XPM data
protected:
    virtual void _draw(int dx, int dy, int dw, int dh,
                       int sx, int sy, int sw, int sh,
                       Fl_Flags f);
};

#endif
