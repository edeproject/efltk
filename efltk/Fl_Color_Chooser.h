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

// The color chooser object and the color chooser popup.  The popup
// is just a window containing a single color chooser and some boxes
// to indicate the current and cancelled color.

#ifndef _FL_COLOR_CHOOSER_H_
#define _FL_COLOR_CHOOSER_H_

#include "Fl_Group.h"
#include "Fl_Box.h"
#include "Fl_Return_Button.h"
#include "Fl_Choice.h"
#include "Fl_Value_Input.h"

class FL_API Flcc_HueBox : public Fl_Widget {
public:
    Flcc_HueBox(int X, int Y, int W, int H);
    virtual ~Flcc_HueBox();

    virtual void layout();
    virtual void draw();
    virtual int handle(int);

private:
    void generate();
    Fl_Image *bg;
    int px, py;
};

class FL_API Flcc_ValueBox : public Fl_Widget {
public:
    Flcc_ValueBox(int X, int Y, int W, int H);
    ~Flcc_ValueBox();

    virtual void layout();
    virtual void draw();
    virtual int handle(int);
private:
    void generate();
    Fl_Image *bg;
    int py;
};

class FL_API Flcc_Value_Input : public Fl_Value_Input {
public:
    Flcc_Value_Input(int X, int Y, int W, int H) : Fl_Value_Input(X,Y,W,H) { }
    int format(char*);
};

/** Fl_Color_Chooser */
class FL_API Fl_Color_Chooser : public Fl_Group {
public:
    static Fl_Named_Style* default_style;

    /** The traditional constructor creates the color chooser widget using the position, size, and label. */
    Fl_Color_Chooser(int,int,int,int,const char* l= 0);

    /** The new style constructor creates the color chooser widget using the label, size, alignment, and label_width. */
    Fl_Color_Chooser(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    Fl_Color value() const;
    void value(Fl_Color);

    int mode() { return choice.value(); }
    float hue() const {return hue_;}
    float saturation() const {return saturation_;}
    float v() const {return value_;}
    float r() const {return r_;}
    float g() const {return g_;}
    float b() const {return b_;}
    int hsv(float,float,float);
    int rgb(float,float,float);

    static void hsv2rgb(float, float, float,float&,float&,float&);
    static void rgb2hsv(float, float, float,float&,float&,float&);

    void draw();

private:
    Flcc_HueBox huebox;
    Flcc_ValueBox valuebox;
    Fl_Group nrgroup; // no resize group
    Fl_Choice choice;
    Flcc_Value_Input rvalue;
    Flcc_Value_Input gvalue;
    Flcc_Value_Input bvalue;
    float hue_, saturation_, value_;
    float r_, g_, b_;

    void set_valuators();
    void ctor_init(int X, int Y, int W, int H);

    static void rgb_cb(Fl_Widget*, Fl_Color_Chooser*);
    static void mode_cb(Fl_Widget*, Fl_Color_Chooser*);
};

FL_API int fl_color_chooser(const char*name, float& r,float& g,float& b);
FL_API int fl_color_chooser(const char*name, uchar& r, uchar& g, uchar& b);
FL_API int fl_color_chooser(const char*name, Fl_Color& c);

#endif
