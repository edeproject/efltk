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

#ifndef _FL_LABELTYPE_H_
#define _FL_LABELTYPE_H_

#include "Fl_Color.h"
#include "Fl_Flags.h"

// the abstract base class:
class FL_API Fl_Labeltype_ {
public:
    Fl_Labeltype_(const char* n) : name(n), next(first) { first = this; }

    virtual void draw(const char*, int,int,int,int, Fl_Color, Fl_Flags) const;

    const char* name;
    const Fl_Labeltype_* next;
    static const Fl_Labeltype_* first;
    static const Fl_Labeltype_* find(const char* name);
};

typedef const Fl_Labeltype_* Fl_Labeltype;

extern FL_API Fl_Labeltype_ fl_normal_label;
#define FL_NORMAL_LABEL (&fl_normal_label)

class FL_API Fl_No_Label : public Fl_Labeltype_ {
public:
    Fl_No_Label(const char * n) : Fl_Labeltype_(n) {}
    virtual void draw(const char*, int,int,int,int, Fl_Color, Fl_Flags) const;
};
extern FL_API Fl_No_Label fl_no_label;
#define FL_NO_LABEL (&fl_no_label)

class FL_API Fl_Symbol_Label : public Fl_Labeltype_ {
public:
    Fl_Symbol_Label(const char * n) : Fl_Labeltype_(n) {}
    virtual void draw(const char*, int,int,int,int, Fl_Color, Fl_Flags) const;
};
extern FL_API const Fl_Symbol_Label fl_symbol_label;
#define FL_SYMBOL_LABEL (&fl_symbol_label)

class FL_API Fl_Engraved_Label : public Fl_Labeltype_ {
    const int* data;
public:
    Fl_Engraved_Label(const char * n, const int p[][3]) : Fl_Labeltype_(n), data((const int*)p) { }
    virtual void draw(const char*, int,int,int,int, Fl_Color, Fl_Flags) const;
};
extern FL_API const Fl_Engraved_Label fl_shadow_label;
#define FL_SHADOW_LABEL (&fl_shadow_label)
extern FL_API const Fl_Engraved_Label fl_engraved_label;
#define FL_ENGRAVED_LABEL (&fl_engraved_label)
extern FL_API const Fl_Engraved_Label fl_embossed_label;
#define FL_EMBOSSED_LABEL (&fl_embossed_label)

#endif
