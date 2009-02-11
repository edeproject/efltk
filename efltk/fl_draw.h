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

#ifndef _FL_DRAW_H_
#define _FL_DRAW_H_

#include "Fl_Flags.h" // for alignment values
#include "Fl_Color.h"
#include "Fl_Font.h"
#include "Fl_Device.h"

inline void fl_load_identity() { fl_current_dev->load_identity(); }

//fl_vertex.cpp current transformation:
inline void fl_push_matrix() { fl_current_dev->push_matrix(); }
inline void fl_pop_matrix()  { fl_current_dev->pop_matrix();  }
inline void fl_scale(float x, float y) { fl_current_dev->scale(x, y); }
inline void fl_scale(float x) { fl_current_dev->scale(x); }
inline void fl_translate(float x, float y) { fl_current_dev->translate(x,y); }
inline void fl_translate(int x, int y) { fl_current_dev->translate(x,y); }
inline void fl_rotate(float d) { fl_current_dev->rotate(d); }
inline void fl_mult_matrix(float a, float b, float c, float d, float e, float f) { fl_current_dev->mult_matrix(a,b,c,d,e,f); }

// get and use transformed positions:
inline void fl_transform(float& x, float& y) { fl_current_dev->transform(x,y); }
inline void fl_transform(int& x, int& y) { fl_current_dev->transform(x,y); }
inline void fl_transform_distance(float& x, float& y) { fl_current_dev->transform_distance(x,y); }

// fl_clip.cpp: 
inline void fl_push_clip(int x, int y, int w, int h)   { fl_current_dev->push_clip(x,y,w,h); }
inline void fl_clip_out(int x, int y, int w, int h)    { fl_current_dev->clip_out(x,y,w,h); }
inline void fl_push_no_clip()			       { fl_current_dev->push_no_clip(); }
inline void fl_pop_clip()			       { fl_current_dev->pop_clip(); }
inline int  fl_not_clipped(int x, int y, int w, int h) { return fl_current_dev->not_clipped(x,y,w,h); }
inline int  fl_clip_box(int _x, int _y, int _w, int _h,
                        int& x, int& y, int& w, int& h) { return fl_current_dev->clip_box(_x, _y, _w, _h, x, y, w, h); }

// fl_color.cpp Colors: 
extern FL_API   Fl_Color fl_color_;

inline void     fl_color(Fl_Color c)  			   {fl_current_dev->color(c);}; // select indexed color
inline void     fl_color(uchar r, uchar g, uchar b) 	   {fl_current_dev->color(r,g,b);}; // select actual color
inline Fl_Color fl_color() 			           {return fl_current_dev->color();}

//  line type:
inline void fl_line_style(int style, int width=0, char* dashes=0)
		 {fl_current_dev->line_style(style,width,dashes);}
enum {
  FL_SOLID	= 0,
  FL_DASH	= 1,
  FL_DOT	= 2,
  FL_DASHDOT	= 3,
  FL_DASHDOTDOT	= 4,

  FL_CAP_FLAT	= 0x100,
  FL_CAP_ROUND	= 0x200,
  FL_CAP_SQUARE	= 0x300,

  FL_JOIN_MITER	= 0x1000,
  FL_JOIN_ROUND	= 0x2000,
  FL_JOIN_BEVEL	= 0x3000
};

//Build the path:
//fl_vertex.cpp
inline void fl_newpath() { fl_current_dev->newpath(); }
inline void fl_vertex(float x, float y) { fl_current_dev->vertex(x, y); }
inline void fl_vertex(int x, int y) { fl_current_dev->vertex(x, y); }
inline void fl_vertices(int n, const float v[][2]) { fl_current_dev->vertices(n, v); }
inline void fl_vertices(int n, const int v[][2])   { fl_current_dev->vertices(n, v); }
inline void fl_transformed_vertices(int n, const float v[][2]) { fl_current_dev->transformed_vertices(n, v); }
inline void fl_closepath() { fl_current_dev->closepath(); }

//fl_curve.cpp
inline void fl_curve(float a,float b,float c,float d,float e,float f,float g,float h) { fl_current_dev->curve(a,b,c,d,e,f,g,h); }
//fl_arc.cpp
inline void fl_arc(float x,float y,float w,float h, float a1, float a2) { fl_current_dev->arc(x, y, w,h, a1,a2); }
//fl_vertex.cpp
inline void fl_circle(float x, float y, float r) { fl_current_dev->circle(x, y, r); }
inline void fl_ellipse(float x, float y, float w, float h) { fl_current_dev->ellipse(x, y, w, h); }

// fl_vertex.cpp, draw the path:
inline void fl_points() { fl_current_dev->points(); }
inline void fl_stroke() { fl_current_dev->stroke(); }
inline void fl_fill()   { fl_current_dev->fill(); }
inline void fl_fill_stroke(Fl_Color c) { fl_current_dev->fill_stroke(c); }

//fl_rect.cpp drawing that bypasses the path mechanism:
inline void fl_rect(int x, int y, int w, int h)		{ fl_current_dev->rect(x,y,w,h); }
inline void fl_rectf(int x, int y, int w, int h)	{ fl_current_dev->rectf(x,y,w,h); }
inline void fl_point(int x, int y)			{ fl_current_dev->point(x,y); }
inline void fl_line(int x1, int y1, int x2, int y2)	{ fl_current_dev->line(x1, y1, x2, y2); }

// fl_arci.cpp
enum { FL_PIE, FL_CHORD, FL_ARC };
inline void fl_pie(int x,int y,int w,int h,float a1,float a2,int what=FL_PIE) { fl_current_dev->pie(x,y,w,h,a1,a2,what); }

// current font+size:
inline void fl_font(Fl_Font face, float size)  { fl_current_dev->font(face,size); }
inline void fl_font(const char* s, float size) { fl_current_dev->font(s,size); }
inline void fl_font(const char* s, int attributes, float size) { fl_current_dev->font(s, attributes, size); }

inline const char* fl_encoding() { return fl_current_dev->encoding(); }
inline void 	   fl_encoding(const char* s) { fl_current_dev->encoding(s); }

// information you can get about the current font+size+encoding:
extern FL_API Fl_Font 	fl_font_;
extern FL_API float	fl_size_; // should be 2x2 transformation matrix

inline Fl_Font 		fl_font() { return fl_current_dev->font(); }
inline float 		fl_size() { return fl_current_dev->size(); }
inline const char*	fl_fontname(Fl_Font f, int *i = 0) { return fl_current_dev->fontname(f, i); }


// measure things in the current font:
inline float fl_width(unsigned int ucs)  	{ return fl_current_dev->width(ucs); } //Unicode char
inline float fl_width(const char* s)		{ return fl_current_dev->width(s);   }
inline float fl_width(const Fl_String& s) 	{ return fl_current_dev->width(s);   }
inline float fl_width(const char* s, int n) 	{ return fl_current_dev->width(s,n); }

inline float fl_height()			{ return fl_current_dev->height();  }
inline float fl_descent()			{ return fl_current_dev->descent(); }

// draw using current font:
inline void fl_transformed_draw(const char* s, int n, float x, float y) { fl_current_dev->transformed_draw(s,n,x,y); }
inline void fl_rtl_draw(const char *s, int n, float x, float y)		{ fl_current_dev->rtl_draw(s,n,x,y); }

inline void fl_draw(const char* s, float x, float y)		{ fl_current_dev->draw(s,x,y);   }
inline void fl_draw(const Fl_String & s, float x, float y) 	{ fl_current_dev->draw(s,x,y);   }
inline void fl_draw(const char* s, int n, float x, float y) 	{ fl_current_dev->draw(s,n,x,y); }

// the "fancy" text formatter:
FL_API void fl_measure(const char*d, int& w, int& h, Fl_Flags f); 
FL_API void fl_draw(const char*d, int x,int y,int w,int h, Fl_Flags f);
FL_API void fl_measure(const Fl_String &s, int& w, int& h, Fl_Flags f);
FL_API void fl_draw(const Fl_String &s, int x,int y,int w,int h, Fl_Flags f);

extern FL_API const int* fl_column_widths_;
inline const int* 	 fl_column_widths() {return fl_column_widths_;}
inline void 		 fl_column_widths(const int* i) {fl_column_widths_ = i;}

// images:
inline void fl_draw_image(const uchar* im, int x,int y,int w,int h, int delta=3, int ldelta=0){fl_current_dev->draw_image(im,x,y,w,h,delta,ldelta);};
inline void fl_draw_image_mono(const uchar* im, int x,int y,int w,int h, int delta=1, int ld=0){fl_current_dev->draw_image_mono(im,x,y,w,h,delta,ld);};
typedef void (*Fl_Draw_Image_Cb)(void*,int,int,int,uchar*);
inline void fl_draw_image(Fl_Draw_Image_Cb cb, void* im, int x,int y,int w,int h, int delta=3){fl_current_dev->draw_image(cb, im, x,y,w,h,delta);};
inline void fl_draw_image_mono(Fl_Draw_Image_Cb cb, void* im, int x,int y,int w,int h, int delta=1){fl_current_dev->draw_image(cb, im, x,y,w,h,delta);};

inline void fl_rectf(int x, int y, int w, int h, Fl_Color c){fl_current_dev->rectf(x,y,w,h,c);};
inline void fl_rectf(int x, int y, int w, int h, uchar r, uchar g, uchar b) { fl_rectf(x,y,w,h,fl_rgb(r,g,b)); }

// XPM interpreter (probably should be part of Fl_Pixmap):
FL_API int  fl_draw_pixmap(const char*const* data, int x,int y,Fl_Color c=FL_GRAY);
FL_API int  fl_measure_pixmap(const char*const* data, int &w, int &h);
FL_API void fl_set_mask_bitmap(uchar **ppBitmap);


// depreciated:
extern FL_API void fl_scroll(int X, int Y, int W, int H, int dx, int dy,
			     void (*draw_area)(void*, int,int,int,int), void*);
FL_API void fl_overlay_rect(int,int,int,int);
FL_API void fl_overlay_clear();
FL_API void fl_cursor(Fl_Cursor, Fl_Color=FL_BLACK, Fl_Color=FL_WHITE);

// XForms symbols (should not be here...)
FL_API int fl_draw_symbol(const char* label,int x,int y,int w,int h, Fl_Color);
FL_API int fl_add_symbol(const char* name, void (*drawit)(Fl_Color), int scalable);

#endif

