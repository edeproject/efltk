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

#ifndef _FL_BITMAP_H_
#define _FL_BITMAP_H_

#include "Fl_Image.h"

/** Fl_Bitmap */
class FL_API Fl_Bitmap : public Fl_Image {
public:
    Fl_Bitmap(const uint8 *bits, int W, int H, bool allow_free=false) : Fl_Image(W, H, 1, (uint8*)bits, allow_free) { }
    Fl_Bitmap(const char  *bits, int W, int H, bool allow_free=false) : Fl_Image(W, H, 1, (uint8*)bits, allow_free) { }

protected:
    virtual void _draw(int dx, int dy, int dw, int dh,
                       int sx, int sy, int sw, int sh,
                       Fl_Flags f);
};

#endif
