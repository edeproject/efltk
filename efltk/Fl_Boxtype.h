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

#ifndef _FL_BOXTYPE_H_
#define _FL_BOXTYPE_H_

#include "Fl_Color.h"
#include "Fl_Flags.h"

// the abstract base class:
class FL_API Fl_Boxtype_
{
public:
    Fl_Boxtype_() : name(0) { }
    Fl_Boxtype_(const char* n) : name(n), next(first) { first = this; }

    int fills_rectangle() const { return fills_rectangle_; }
    int dx() const { return dx_; }
    int dy() const { return dy_; }
    int dw() const { return dw_; }
    int dh() const { return dh_; }
    void inset(int&X,int&Y,int&W,int&H) const { X+=dx_; Y+=dy_; W-=dw_; H-=dh_; }

    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const = 0;

    const Fl_Boxtype_ *next;
    static const Fl_Boxtype_ *first;
    static const Fl_Boxtype_ *find(const char* name);

    const char *name;

protected:
    int dx_, dy_, dw_, dh_;
    int fills_rectangle_;
};

typedef const Fl_Boxtype_* Fl_Boxtype;

// draw a pattern of lines around a box, pattern is from the data string
// in which 'A'=black, 'X'=white, other characters are gray levels
class FL_API Fl_Frame_Box : public Fl_Boxtype_
{
public:
    Fl_Frame_Box(const char* n, const char* c, const Fl_Frame_Box* d=0);

    const char* data() const { return data_; }
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;

protected:
    const char* data_;
    const Fl_Frame_Box* down;
};

extern FL_API const Fl_Frame_Box fl_up_box;
#define FL_UP_BOX (&fl_up_box)
#define FL_NORMAL_BOX (&fl_up_box)

extern FL_API const Fl_Frame_Box fl_down_box;
#define FL_DOWN_BOX (&fl_down_box)

extern FL_API const Fl_Frame_Box fl_thin_up_box;
#define FL_THIN_UP_BOX (&fl_thin_up_box)
#define FL_THIN_BOX (&fl_thin_up_box)

extern FL_API const Fl_Frame_Box fl_thin_down_box;
#define FL_THIN_DOWN_BOX (&fl_thin_down_box)

extern FL_API const Fl_Frame_Box fl_engraved_box;
#define FL_ENGRAVED_BOX (&fl_engraved_box)

extern FL_API const Fl_Frame_Box fl_embossed_box;
#define FL_EMBOSSED_BOX (&fl_embossed_box)

extern FL_API const Fl_Frame_Box fl_border_box;
#define FL_BORDER_BOX (&fl_border_box)

// no border, tiling pattern is in absolute coordinates:
class FL_API Fl_Flat_Box : public Fl_Boxtype_ {
public:
    Fl_Flat_Box(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};
extern FL_API const Fl_Flat_Box fl_flat_box;
#define FL_FLAT_BOX (&fl_flat_box)

// Combination of flat & any other boxtype when highlighted or pressed:
class FL_API Fl_Highlight_Box : public Fl_Flat_Box {
public:
    Fl_Highlight_Box(const char* n, const Fl_Boxtype_* d);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;

private:
    const Fl_Boxtype_* down;
};
extern FL_API const Fl_Highlight_Box fl_highlight_up_box;
#define FL_HIGHLIGHT_UP_BOX (&fl_highlight_up_box)
#define FL_FLAT_UP_BOX (&fl_highlight_up_box)
#define FL_HIGHLIGHT_BOX (&fl_highlight_up_box)

extern FL_API const Fl_Highlight_Box fl_highlight_down_box;
#define FL_HIGHLIGHT_DOWN_BOX (&fl_highlight_down_box)
#define FL_FLAT_DOWN_BOX (&fl_highlight_down_box)

// Circle with an edge pattern like Fl_Frame_Box:
class FL_API Fl_Round_Box : public Fl_Frame_Box {
public:
    Fl_Round_Box(const char* n, const char* c, const Fl_Frame_Box* d=0);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_Round_Box fl_round_up_box;
#define FL_ROUND_UP_BOX (&fl_round_up_box)
#define FL_ROUND_BOX (&fl_round_up_box)

extern FL_API const Fl_Round_Box fl_round_down_box;
#define FL_ROUND_DOWN_BOX (&fl_round_down_box)

// Diamond with an edge pattern like Fl_Frame_Box:
class FL_API Fl_Diamond_Box : public Fl_Frame_Box {
public:
    Fl_Diamond_Box(const char* n, const char* c, const Fl_Frame_Box* d=0);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_Diamond_Box fl_diamond_up_box;
#define FL_DIAMOND_UP_BOX (&fl_diamond_up_box)
#define FL_DIAMOND_BOX (&fl_diamond_up_box)

extern FL_API const Fl_Diamond_Box fl_diamond_down_box;
#define FL_DIAMOND_DOWN_BOX (&fl_diamond_down_box)

// Plastic/Aqua shading:
class FL_API Fl_Plastic_Box : public Fl_Frame_Box {
public:
    Fl_Plastic_Box(const char* n, const char* c, const Fl_Frame_Box* d=0);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_Plastic_Box fl_plastic_up_box;
#define FL_PLASTIC_UP_BOX (&fl_plastic_up_box)
#define FL_PLASTIC_BOX (&fl_plastic_up_box)

extern FL_API const Fl_Plastic_Box fl_plastic_down_box;
#define FL_PLASTIC_DOWN_BOX (&fl_plastic_down_box)

// a bunch of "one-of" types:
class FL_API Fl_No_Box : public Fl_Boxtype_ {
public:
    Fl_No_Box(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_No_Box fl_no_box;
#define FL_NO_BOX (&fl_no_box)

class FL_API Fl_Shadow_Box : public Fl_Boxtype_ {
public:
    Fl_Shadow_Box(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_Shadow_Box fl_shadow_box;
#define FL_SHADOW_BOX (&fl_shadow_box)

class FL_API Fl_Rounded_Box : public Fl_Boxtype_ {
public:
    Fl_Rounded_Box(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_Rounded_Box fl_rounded_box;
#define FL_ROUNDED_BOX (&fl_rounded_box)

class FL_API Fl_RShadow_Box : public Fl_Boxtype_ {
public:
    Fl_RShadow_Box(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_RShadow_Box fl_rshadow_box;
#define FL_RSHADOW_BOX (&fl_rshadow_box)

class FL_API Fl_RFlat_Box : public Fl_Boxtype_ {
public:
    Fl_RFlat_Box(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_RFlat_Box fl_rflat_box;
#define FL_RFLAT_BOX (&fl_rflat_box)

class FL_API Fl_Oval_Box : public Fl_Boxtype_ {
public:
    Fl_Oval_Box(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_Oval_Box fl_oval_box;
#define FL_OVAL_BOX (&fl_oval_box)

class FL_API Fl_Oval_Shadow_Box : public Fl_Boxtype_ {
public:
    Fl_Oval_Shadow_Box(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};
extern FL_API const Fl_Oval_Shadow_Box fl_oval_shadow_box;
#define FL_OSHADOW_BOX (&fl_oval_shadow_box)

class FL_API Fl_Oval_Flat_Box : public Fl_Boxtype_ {
public:
    Fl_Oval_Flat_Box(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_Oval_Flat_Box fl_oval_flat_box;
#define FL_OFLAT_BOX (&fl_oval_flat_box)

class FL_API Fl_Border_Frame : public Fl_Boxtype_ {
public:
    Fl_Border_Frame(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_Border_Frame fl_border_frame;
#define FL_BORDER_FRAME (&fl_border_frame)

class FL_API Fl_Dotted_Frame : public Fl_Boxtype_ {
public:
    Fl_Dotted_Frame(const char* n);
    virtual void draw(int,int,int,int, Fl_Color, Fl_Flags=0) const;
};

extern FL_API const Fl_Dotted_Frame fl_dotted_frame;
#define FL_DOTTED_FRAME (&fl_dotted_frame)

class Fl_Hor_Shade_Box : public Fl_Flat_Box {
public:
    Fl_Hor_Shade_Box(const char* n, const Fl_Boxtype_ *up, const Fl_Boxtype_ *down, Fl_Color end=0);
    virtual void draw(int x,int y,int w,int h, Fl_Color color, Fl_Flags f) const;

    Fl_Color end_color; //end of shaded color
protected:
    const Fl_Boxtype_ *up_, *down_;
};

class Fl_Vert_Shade_Box : public Fl_Hor_Shade_Box {
public:
    Fl_Vert_Shade_Box(const char* n, const Fl_Boxtype_ *up, const Fl_Boxtype_ *down, Fl_Color end=0) : Fl_Hor_Shade_Box(n,up,down,end) { }
    virtual void draw(int x,int y,int w,int h, Fl_Color color, Fl_Flags f) const;
};

extern FL_API const Fl_Vert_Shade_Box vert_up_shade_box;
extern FL_API const Fl_Hor_Shade_Box hor_up_shade_box;
#define FL_VERT_SHADE_UP_BOX (&vert_up_shade_box)
#define FL_HOR_SHADE_UP_BOX (&hor_up_shade_box)

extern FL_API const Fl_Vert_Shade_Box vert_flat_shade_box;
extern FL_API const Fl_Hor_Shade_Box hor_flat_shade_box;
#define FL_VERT_SHADE_FLAT_BOX (&vert_flat_shade_box)
#define FL_HOR_SHADE_FLAT_BOX (&hor_flat_shade_box)

// Used in MDI
extern FL_API const Fl_Frame_Box thick_up_box;
#define FL_THICK_UP_BOX (&thick_up_box)

#endif
