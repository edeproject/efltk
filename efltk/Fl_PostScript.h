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


#ifndef Fl_PostScript_H
#define Fl_PostScript_H

#include "Fl_String.h"
#include "fl_draw.h"
#include "Fl_Printer.h"
#include "Enumerations.h"
#include <stdio.h>

class FL_API Fl_PostScript: public Fl_Printer { 

	enum SHAPE{NONE=0, LINE, LOOP, POLYGON, POINTS};

	class Clip{
	public:
		int x, y, w, h;
		Clip *prev;
	};
	Clip * clip_;

	
	int lang_level_;
	Fl_Font font_;
	float size_;
	Fl_Color color_;
	FILE *output;
	//int nPages;
	int gap_;

	double width_;
	double height_;
	//double g_pw_, g_ph_, 
	//double lm_, tm_, rm_, bm_;
	//int g_orientation_,

	int shape_;
	int linewidth_;// need for clipping, lang level 1-2
	int linestyle_;//
	int interpolate_; //interpolation of images
	unsigned char cr_,cg_,cb_;
	char  linedash_[256];//should be enought
	void concat();  // transform ror scalable dradings...
	void reconcat(); //invert
	void recover(); //recovers the state afrer grestore 
	void reset();

	//double c_x_, c_y_, c_w_, c_h_; //no_clip clipping (to margins)
	//int colored_, line_styled_, fonted_;
		//these are flags if graphical state (color, painting, font)should be recovered
		// for language level 1-2: it has no clipsace/cliprestore, so gsave / grestore is used

	

	uchar * mask;
	int mx; // width of mask;
	int my; // mask lines
	Fl_Color bg_;

protected:
	  int alpha_mask(const uchar * data, int w, int h, int D, int LD=0);
	
	  void transformed_draw(const char* s, int n, float x, float y); //precise text placing
	  void transformed_draw(const char* s, float x, float y){transformed_draw(s,strlen(s),x,y);};
	
	  void draw_scalled_image(const uchar *data, double x, double y, double w, double h, int iw, int ih, int D=3, int LD=0);
	  void draw_scalled_image_mono(const uchar *data, double x, double y, double w, double h, int iw, int ih, int D=3, int LD=0);
	  void draw_scalled_image(Fl_Draw_Image_Cb call, void *data, double x, double y, double w, double h, int iw, int ih, int D);
	  void draw_scalled_image_mono(Fl_Draw_Image_Cb call, void *data, double x, double y, double w, double h, int iw, int ih, int D);
		

public:
	  void draw(Fl_Widget * w);

	  Fl_PostScript(FILE *o, int lang_level, int format = A4, int orientation = PORTRAIT); // ps (aslo multi-page) constructor
	  Fl_PostScript(FILE *o, int lang_level, double x, double y, double w, double h); //eps constructor
	  virtual ~Fl_PostScript();
	  void interpolate(int i){interpolate_=i;};
	  int interpolate(){return interpolate_;}

	  void page(double pw, double ph, int orientation);
	  void page(int format, int orientation);
	  void page(){page(pw_,ph_,orientation_);};
	  void margins(double left, double top, double right, double bottom);

	  void fit(double x, double y, double w, double h, int align=FL_ALIGN_CENTER);
	  void fit(double x, double y, double w, double h, double dpi, int align=FL_ALIGN_CENTER);
	  void place(double x, double y, double w, double h, double tx, double ty, double tw, double th, int align);
	  void place(double x, double y, double w, double h, double tx, double ty, double tw, double th, double dpi, int align);
//////////////////////////////////////////////////////

	  void color(Fl_Color c);
	  void bg_color(Fl_Color bg);
	  void color(uchar r, uchar g, uchar b);
	  Fl_Color color(){return color_;};
	
	  void push_clip(int x, int y, int w, int h);
	  void clip_out(int x, int y, int w, int h);
//
	  void push_no_clip();
	  void pop_clip();
	  int not_clipped(int x, int y, int w, int h);
	  int clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H);

	  void line_style(int style, int width, char* dashes);
	  
/*	  void line(int x1, int y1, int x2, int y2, int x3, int y3);

	  void loop(int x1, int y1, int x2 ,int y2, int x3, int y3);
	  void loop(int x1, int y1, int x2 ,int y2, int x3, int y3, int x4, int y4);

	  void polygon(int x1, int y1, int x2 ,int y2, int x3, int y3);
	  void polygon(int x1 ,int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	  void xyline(int x, int y, int x1);
	  void xyline(int x, int y, int x1, int y2);
	  void xyline(int x, int y, int x1, int y2, int x3);

	  void yxline(int x, int y, int y1);
	  void yxline(int x, int y, int y1, int x2);
	  void yxline(int x, int y, int y1, int x2, int y3);
*/

	  void curve(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3);
//	  void arc(double x, double y, double r, double start, double a);
	  void arc(float x, float y, float w, float h, float a1, float a2);
	  
	  void circle(float x, float y, float r);
	  void ellipse(float x, float y, float w, float h);
 //

	  void rect(int x, int y, int w, int h);
	  void rectf(int x, int y, int w, int h);
	  void point(int x, int y);
	  void line(int x1, int y1, int x2, int y2);

	  void pie(int x, int y, int w, int h, float a1, float a2);

	 void points(); //
	 void stroke();//
	 void fill();//
	void fill_stroke(Fl_Color);//


	 void newpath(); //
	void vertex(float x, float y); //
	 void vertex(int x, int y);//
	 void vertices(int n, const float v[][2]);
	 void vertices(int n, const int v[][2]);//
	void transformed_vertices(int n, const float v[][2]);//
	 void closepath();//


/*	  void begin_points();
	  void begin_line();
	  void begin_loop();
	  void begin_polygon();
	  void vertex(double x, double y);
	  void end_points();
	  void end_line();
	  void end_loop();
	  void end_polygon();
	void begin_complex_polygon(){begin_polygon();};
	void gap(){gap_=1;};
	void end_complex_polygon(){end_polygon();};
	  void transformed_vertex(double x, double y);
*/


	void font(Fl_Font face, float size);
	void font(const char* s, float size); //
	void font(const char* s, int attributes, float size); //
	
	Fl_Font font(){return font_;};
	float size(){return size_;};
	
	void  encoding(const char*); //
	const char* encoding();//
	
	const char* fontname(Fl_Font, int * = 0);//

	
	  //float width(uchar c);
	  float width(unsigned int ucs);
//
	  float width(const char* s);
	  float width(const Fl_String& s);
//
	  float width(const char* s, int n);

	  float height();
	  float descent();


//	void transformed_draw(const char* s, int n, float x, float y);
	void rtl_draw(const char *s, int n, float x, float y);//

	void draw(const char* s, int n, float x, float y){transformed_draw(s,n,x,y);}
	void draw(const Fl_String &s, float x, float y){draw(s.c_str(), s.length(), x, y);}
		
	void draw(const char* s, float x, float y){draw(s,strlen(s),x,y);};


	  void draw_image(const uchar* d, int x,int y,int w,int h, int delta=3, int ldelta=0){draw_scalled_image(d,x,y,w,h,w,h,delta,ldelta);}
	  void draw_image_mono(const uchar* d, int x,int y,int w,int h, int delta=1, int ld=0){draw_scalled_image_mono(d,x,y,w,h,w,h,delta,ld);}
	  void draw_image(Fl_Draw_Image_Cb call, void* data, int x,int y, int w, int h, int delta=3){draw_scalled_image(call,data, x, y, w, h, w, h, delta);}
	  void draw_image_mono(Fl_Draw_Image_Cb call, void* data, int x,int y, int w, int h, int delta=1){draw_scalled_image_mono(call, data, x, y, w, h, w, h, delta);}
	
	  void rectf(int x, int y, int w, int h, uchar r,  uchar g, uchar b);
    	  void rectf(int x, int y, int w, int h, Fl_Color c)
	  {
	    uchar r, g, b;
	    fl_get_color(c, r, g, b);
	    rectf(x, y, w, h, r, g, b);
	    
	    
}



/////////////////////////////////////////////////

	  Fl_PostScript(FILE *o, int lang_level, double pw, double ph, int orientation); // ps (aslo multi-page) constructor
	
	

	
//	  void draw_Pixmap(Fl_Pixmap * pxm,int XP, int YP, int WP, int HP, int cx, int cy);
//	  void draw_RGB(Fl_RGB_Image * rgb,int XP, int YP, int WP, int HP, int cx, int cy);
//	  void draw_Bitmap(Fl_Bitmap * bitmap,int XP, int YP, int WP, int HP, int cx, int cy);
};


//Fl_PostScript * fl_psfile_chooser(Fl_PsFile_Settings * s=0, int * begin = 0, int * end = 0);

#endif

