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

#ifndef _FL_PROGRESSBAR_H_
#define _FL_PROGRESSBAR_H_

#include "Fl_Widget.h"
#include "Fl.h"
#include "fl_draw.h"

/** Fl_ProgressBar */
class FL_API Fl_ProgressBar : public Fl_Widget
{
public:
    static Fl_Named_Style* default_style;

    Fl_ProgressBar(int x, int y, int w, int h, const char *lbl = 0);

    void range(float min, float max, float step = 1)  { mMin = min; mMax = max; mStep = step; };

    float minimum()	{ return mMin; }
    float maximum()	{ return mMax; }
    void minimum(float nm) { mMin = nm; };
    void maximum(float nm) { mMax = nm; };

    void step(float step) { mPresent += step; redraw(); };
    float step()	  { return mStep; }

    void  value(float v) { mPresent = v; redraw(); }
    float value() const  { return mPresent; }

    void showtext(bool st) { mShowPct = st; }
    bool showtext()	   { return mShowPct; }

    virtual void draw();

protected:
    float mMin, mMax;
    float mPresent, mStep;
    bool mShowPct;
};

#endif
