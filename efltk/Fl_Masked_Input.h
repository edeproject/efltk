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
 * Author : Alexey Parshin
 * Email  : alexey@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_MASKED_INPUT_H_
#define _FL_MASKED_INPUT_H_

#include "Fl_Input.h"
#include "Fl_String.h"

/** Fl_Masked_Input */
class FL_API Fl_Masked_Input : public Fl_Input {
public:

    /** Creates new masked input widget using the given position, size, and label string. */
    Fl_Masked_Input(int x,int y,int w,int h,const char *l = 0)
    : Fl_Input(x, y, w, h, l) {}

    /** Creates new masked input widget using the label, size, alignment, and label_width. */
    Fl_Masked_Input(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100)
    : Fl_Input(l,layout_size,layout_al,label_w) {}

    void mask(const char *m);
    const char *mask() const  { return m_mask.c_str(); }

    virtual int handle(int event);

private:
    Fl_String   m_mask;
    Fl_String   m_inputMask;
    Fl_String   m_backgroundMask;

    bool        checkCharacterAtPos(int pos,char& key);
    bool        checkCharacter(int pos,char& key);
};

#endif 
