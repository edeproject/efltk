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

#ifndef _FL_MULTI_IMAGE_H_
#define _FL_MULTI_IMAGE_H_

#include "Fl_Image.h"

/** Fl_Multi_Image */
class FL_API Fl_Multi_Image : public Fl_Image
{
    enum {MAXIMAGES = 8};
    Fl_Image* images[MAXIMAGES];
    Fl_Flags flags[MAXIMAGES];
public:
    Fl_Multi_Image(Fl_Image& image0,
                   Fl_Flags flags1, Fl_Image& image1) {
        images[0] = &image0;
        flags[1] = flags1; images[1] = &image1;
        images[2] = 0;
    }
    Fl_Multi_Image(Fl_Image& image0,
                   Fl_Flags flags1, Fl_Image& image1,
                   Fl_Flags flags2, Fl_Image& image2) {
        images[0] = &image0;
        flags[1] = flags1; images[1] = &image1;
        flags[2] = flags2; images[2] = &image2;
        images[3] = 0;
    }
    Fl_Multi_Image(Fl_Image& image0,
                   Fl_Flags flags1, Fl_Image& image1,
                   Fl_Flags flags2, Fl_Image& image2,
                   Fl_Flags flags3, Fl_Image& image3) {
        images[0] = &image0;
        flags[1] = flags1; images[1] = &image1;
        flags[2] = flags2; images[2] = &image2;
        flags[3] = flags3; images[3] = &image3;
        images[4] = 0;
    }
    Fl_Multi_Image(Fl_Image& image0,
                   Fl_Flags flags1, Fl_Image& image1,
                   Fl_Flags flags2, Fl_Image& image2,
                   Fl_Flags flags3, Fl_Image& image3,
                   Fl_Flags flags4, Fl_Image& image4) {
        images[0] = &image0;
        flags[1] = flags1; images[1] = &image1;
        flags[2] = flags2; images[2] = &image2;
        flags[3] = flags3; images[3] = &image3;
        flags[4] = flags4; images[4] = &image4;
        images[5] = 0;
    }
    Fl_Multi_Image(Fl_Image& image0,
                   Fl_Flags flags1, Fl_Image& image1,
                   Fl_Flags flags2, Fl_Image& image2,
                   Fl_Flags flags3, Fl_Image& image3,
                   Fl_Flags flags4, Fl_Image& image4,
                   Fl_Flags flags5, Fl_Image& image5) {
        images[0] = &image0;
        flags[1] = flags1; images[1] = &image1;
        flags[2] = flags2; images[2] = &image2;
        flags[3] = flags3; images[3] = &image3;
        flags[4] = flags4; images[4] = &image4;
        flags[5] = flags5; images[5] = &image5;
        images[6] = 0;
    }
    Fl_Multi_Image(Fl_Image& image0,
                   Fl_Flags flags1, Fl_Image& image1,
                   Fl_Flags flags2, Fl_Image& image2,
                   Fl_Flags flags3, Fl_Image& image3,
                   Fl_Flags flags4, Fl_Image& image4,
                   Fl_Flags flags5, Fl_Image& image5,
                   Fl_Flags flags6, Fl_Image& image6) {
        images[0] = &image0;
        flags[1] = flags1; images[1] = &image1;
        flags[2] = flags2; images[2] = &image2;
        flags[3] = flags3; images[3] = &image3;
        flags[4] = flags4; images[4] = &image4;
        flags[5] = flags5; images[5] = &image5;
        flags[6] = flags6; images[6] = &image6;
        images[7] = 0;
    }
    Fl_Multi_Image(Fl_Image& image0,
                   Fl_Flags flags1, Fl_Image& image1,
                   Fl_Flags flags2, Fl_Image& image2,
                   Fl_Flags flags3, Fl_Image& image3,
                   Fl_Flags flags4, Fl_Image& image4,
                   Fl_Flags flags5, Fl_Image& image5,
                   Fl_Flags flags6, Fl_Image& image6,
                   Fl_Flags flags7, Fl_Image& image7) {
        images[0] = &image0;
        flags[1] = flags1; images[1] = &image1;
        flags[2] = flags2; images[2] = &image2;
        flags[3] = flags3; images[3] = &image3;
        flags[4] = flags4; images[4] = &image4;
        flags[5] = flags5; images[5] = &image5;
        flags[6] = flags6; images[6] = &image6;
        flags[7] = flags7; images[7] = &image7;
    }

    virtual void measure(int&,int&);

protected:
    virtual void _draw(int dx, int dy, int dw, int dh,
                       int sx, int sy, int sw, int sh,
                       Fl_Flags f);
};

#endif
