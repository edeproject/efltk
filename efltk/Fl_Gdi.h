//
// "$Id$"
//
// WIN32 GDI printing device for the Fast Light Tool Kit (FLTK).
//
// Copyright (c) 2002  O'ksi'D
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "oksid@bluewin.ch".
//

#ifdef WIN32
#ifndef Fl_Gdi_H
#define Fl_Gdi_H
//#include "Fl_Printer.H"
#include <windows.h>
#include <commdlg.h>


extern FL_API Fl_Color fl_color_;
extern FL_API float    fl_size_;
extern FL_API Fl_font  fl_font_;
extern FL_API HDC      fl_gc;
/*
struct Fl_Ext{
		int WOx, VEx, WEx, VOx;
		int WOy, VEy, WEy, VOy;
};
*/

class FL_API Fl_Gdi_Settings{
	void init();
	bool * pages_;
	int copies_;
	int max_page_;
	int first_page_;
	int last_page_;
	


public:
	DEVMODE * mode;
	DEVNAMES * names;
	void reset();
	int first_page(){return first_page_;};
	void first_page(int i){first_page_=i;};
	int last_page(){return last_page_;};
	void last_page(int i){last_page_=i;};
	void pages(int first, int last){first_page_=first; last_page_=last;};
	int max_page(){return max_page_;};
	void max_page(int p){max_page_=p;};
	int format();
	void format(int f);
	int orientation();
	void orientation(int o);
	void copies(int i){copies_=i;};
	int copies(){return copies_;};

	Fl_Gdi_Settings():pages_(0),copies_(1),max_page_(0),first_page_(1),last_page_(0),mode(0),names(0){};
	~Fl_Gdi_Settings(){
		if(mode) GlobalFree(mode); 
		if(names) GlobalFree(names);
	};
};

class FL_API Fl_Gdi: public Fl_Printer{
	HDC gc_;
	DEVMODE *  mode_;
	int delete_mode_;
	int ix, iy, ox, oy;
	int WOx, VEx, WEx, VOx;
	int WOy, VEy, WEy, VOy;


 
protected:
	void set_page(int page);
public:
	  void delete_mode(int i){delete_mode_=i;};

	  void draw(Fl_Widget * w);
	  void page(double pw, double ph, int orientation);
	  void page(int format, int orientation);
	  void page();


	//// Some clipping primitives must be re-implemented as used gdi functions work in device-coordinates, not "logical" (in MS terminology)
	  void push_clip(int x, int y, int w, int h);
	  int not_clipped(int x, int y, int w, int h);
	  int clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H);

	  void margins(double left, double top, double right, double bottom);


	  void fit(double x, double y, double w, double h, int align);
	  void fit(double x, double y, double w, double h, double dpi, int align);
	  void place(double x, double y, double w, double h, double tx, double ty, double tw, double th, int align);
	  void place(double x, double y, double w, double h, double tx, double ty, double tw, double th, double dpi, int align);

	// Those need to be refined  -  need to be uncached for offscreen cteation 
	// note: masking do not seems to work directly
//	  void draw_Pixmap(Fl_Pixmap * pxm,int XP, int YP, int WP, int HP, int cx, int cy);
//	  void draw_RGB(Fl_RGB_Image * rgb,int XP, int YP, int WP, int HP, int cx, int cy);
//	  void draw_Bitmap(Fl_Bitmap * bmp,int XP, int YP, int WP, int HP, int cx, int cy);

	Fl_Gdi(HDC gc, DEVMODE * mode);
	  ~Fl_Gdi();
};

Fl_Gdi * fl_gdi_printer_chooser(Fl_Gdi_Settings * settings=0);

#endif
#endif