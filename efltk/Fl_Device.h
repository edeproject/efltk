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

#ifndef _FL_DEVICE_H_
#define _FL_DEVICE_H_

#include "Enumerations.h"
#include "Fl_Group.h"

extern FL_API Fl_Color    fl_color_;
extern FL_API Fl_Font 	  fl_font_;
extern FL_API float	  fl_size_; 
extern FL_API const char* fl_encoding_;

typedef void (*Fl_Draw_Image_Cb)(void*,int,int,int,uchar*);

class FL_API Fl_Device
{
public:
    virtual ~Fl_Device(){};

    virtual void color(Fl_Color color);
    virtual void color(uchar r, uchar g, uchar b) { color(fl_rgb(r,g,b)); }
    virtual Fl_Color color() { return fl_color_; }

    // Clipping:
    virtual void push_clip(int x, int y, int w, int h);
    virtual void clip_out(int x, int y, int w, int h);
    virtual void push_no_clip();
    virtual void pop_clip();
    virtual int  not_clipped(int x, int y, int w, int h);
    virtual int  clip_box(int _x, int _y, int _w, int _h, int& x, int& y, int& w, int& h);

    //  line style:
    virtual void line_style(int style, int width=0, char* dashes=0);

    //fl_vertex.cpp current transformation:
    virtual void push_matrix();
    virtual void pop_matrix();
    virtual void scale(float x, float y);
    virtual void scale(float x);
    virtual void translate(float x, float y);
    virtual void translate(int x, int y);
    virtual void rotate(float d);
    virtual void mult_matrix(float a, float b, float c, float d, float e, float f);
    virtual void load_identity();

    // get and use transformed positions:
    virtual void transform(float& x, float& y);
    virtual void transform(int& x, int& y);
    virtual void transform_distance(float& x, float& y);

    //Build the path:
    //fl_vertex.cpp
    virtual void newpath();
    virtual void vertex(float x, float y);
    virtual void vertex(int x, int y);
    virtual void vertices(int n, const float v[][2]);
    virtual void vertices(int n, const int v[][2]);
    virtual void transformed_vertices(int n, const float v[][2]);
    virtual void closepath();

    //fl_curve.cpp
    virtual void curve(float x0, float y0,
                       float x1, float y1,
                       float x2, float y2,
                       float x3, float x4);

    //fl_arc.cpp
    virtual void arc(float x, float y, float w, float h, float start, float end);

    //fl_vertex.cpp
    virtual void circle(float x, float y, float r);
    virtual void ellipse(float x, float y, float w, float h);

    // fl_vertex.cpp, draw the path:
    virtual void points();
    virtual void stroke();
    virtual void fill();
    virtual void fill_stroke(Fl_Color color);

    //fl_rect.cpp drawing that bypasses the path mechanism:
    virtual void rect(int x, int y, int w, int h);
    virtual void rectf(int x, int y, int w, int h, Fl_Color c);
    virtual void rectf(int x, int y, int w, int h);
    virtual void rectf(int x, int y, int w, int h, uchar r, uchar g, uchar b) { rectf(x,y,w,h, fl_rgb(r,g,b)); }
    virtual void point(int x, int y);
    virtual void line(int x1, int y1, int x2, int y2);

    virtual void pie(int x,int y,int w,int h,float a,float a2,int what);

    // current font+size:
    virtual void font(Fl_Font face, float size);

    virtual void font(const char* s, float size);
    virtual void font(const char* s, int attributes, float size);
    virtual const char* fontname(Fl_Font, int * = 0);

    virtual void 	encoding(const char*);
    virtual const char* encoding() { return fl_encoding_; }

    virtual Fl_Font font() { return fl_font_; }
    virtual float   size() { return fl_size_; }

    // measure things in the current font:
    virtual float width(unsigned int ucs);
    virtual float width(const char* s);
    virtual float width(const Fl_String& s);
    virtual float width(const char* s, int n);

    virtual float height();
    virtual float descent();

    // draw using current font:
    virtual void transformed_draw(const char* s, int n, float x, float y);
    virtual void rtl_draw(const char *s, int n, float x, float y);

    virtual void draw(const char* s, float x, float y);
    virtual void draw(const Fl_String & s, float x, float y);
    virtual void draw(const char* s, int n, float x, float y);

    // images:
    virtual void draw_image(const uchar* im, int x,int y,int w,int h, int delta=3, int ldelta=0);
    virtual void draw_image_mono(const uchar* im, int x,int y,int w,int h, int delta=1, int ld=0);
    virtual void draw_image(Fl_Draw_Image_Cb cb, void* im, int x,int y,int w,int h, int delta=3);
    virtual void draw_image_mono(Fl_Draw_Image_Cb cb, void* im, int x,int y,int w,int h, int delta=1);
};

extern FL_API Fl_Device fl_fltk_dev;
extern FL_API Fl_Device *fl_current_dev;

#endif
