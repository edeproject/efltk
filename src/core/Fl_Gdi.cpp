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
#include <config.h>
#ifdef _WIN32

#include <stdlib.h>
#include <math.h>
#include <efltk/Fl.h>
#include <windows.h>
#include <wingdi.h>

#include <efltk/Fl_Printer.h>
#include <commdlg.h>
#include <efltk/x.h>
//#include <CDERR.H >

//static HANDLE hDevMode, hDevNames;




Fl_Gdi::~Fl_Gdi()
{
	if(nPages)
			EndPage(gc_);
	EndDoc(gc_);
	DeleteDC(gc_);
	if(delete_mode_) GlobalFree(mode_); 
}

//extern Fl_Ext * fl_ext;
void Fl_Gdi::draw(Fl_Widget * w)
{
	Fl_Device *t = fl_current_dev;
	fl_current_dev = this;
	Fl::flush(); // cleaning ...
	HDC o = fl_gc;
	fl_gc = gc_;
	SelectClipRgn(fl_gc, 0);
	fl_push_no_clip(); //i am not sure why, but it is required...
	w->redraw(); // making dirty
	w->draw();
	fl_pop_clip();
	fl_gc = o;
	fl_current_dev = t;
}



Fl_Gdi * fl_gdi_printer_chooser(Fl_Gdi_Settings * settings)
{

	PRINTDLG pd;
	pd.Flags       = PD_RETURNDC;
	PrintDlg(&pd);
	ZeroMemory(&pd, sizeof(pd));

	pd.lStructSize = sizeof(pd);

	pd.Flags       = PD_RETURNDC  | PD_ALLPAGES | PD_NOSELECTION | PD_NOPAGENUMS;
	pd.nCopies     = 1;
	pd.nMinPage =1;
	pd.nMaxPage =1;
	pd.nFromPage =1;
	pd.nToPage = 1;
	if(settings){
		pd.hDevMode    = settings->mode;
		pd.hDevNames    = settings->names;
		pd.nCopies     = settings->copies();
		pd.nFromPage = settings->first_page();
		if(settings->max_page()){
			pd.Flags &= ~PD_NOPAGENUMS ;
			pd.nMaxPage = settings->max_page();
			pd.nFromPage = settings->first_page();
			if(!settings->last_page())
				pd.nToPage = settings->max_page();
			else
				pd.nToPage = settings->last_page();
		}
	}

	

	if (PrintDlg(&pd)!=TRUE || !pd.hDC || !pd.hDevMode){
		//int rrr =CommDlgExtendedError();
		return 0;
	};
	
	Fl_Gdi * gdi = new Fl_Gdi(pd.hDC, (DEVMODE *)pd.hDevMode);
	
	if(settings){
		if(pd.Flags & PD_PAGENUMS){
			settings->first_page(pd.nFromPage);
			settings->last_page(pd.nToPage);
			settings->mode = (DEVMODE *)pd.hDevMode;
			settings->names = (DEVNAMES *)pd.hDevNames;
		}
	}else
		gdi->delete_mode(1);
	return gdi;
}



void Fl_Gdi_Settings::init()
{
	if(mode || names) return; //do not need to initialize
	PRINTDLG pd;
	ZeroMemory(&pd, sizeof(PRINTDLG));
	pd.lStructSize = sizeof(PRINTDLG);
	pd.hwndOwner   = 0;
	pd.hDevMode    = NULL;
	pd.hDevNames    = NULL;
	pd.Flags       = PD_USEDEVMODECOPIESANDCOLLATE | PD_ALLPAGES | PD_RETURNDEFAULT | PD_NOSELECTION;
	PrintDlg(&pd);
	mode = (DEVMODE *)pd.hDevMode;
	names = (DEVNAMES *)pd.hDevNames;
}

void Fl_Gdi_Settings::reset()
{
	if(mode) GlobalFree(mode); 
	if(names) GlobalFree(names);
	mode = 0;
	names = 0;
	last_page_ = max_page_=0;
	first_page_=1;
};

////////////// gets the paper size from DEVMODE /////////////////////

static int gdipaper(DEVMODE  *mod)
{
	if(!(mod->dmFields & DM_PAPERSIZE)) return 0;
	
	int paper;
	switch (mod->dmPaperSize){
		case DMPAPER_A3:
			paper = Fl_Printer::A3; break;
		case DMPAPER_A4:
			paper = Fl_Printer::A4; break;
		case DMPAPER_A5:
			paper = Fl_Printer::A5; break;
		//case DMPAPER_A6: paper = FL_A6; break;
		case DMPAPER_B4:
			paper = Fl_Printer::B4; break;
		case DMPAPER_B5: paper = Fl_Printer::B5; break;
		//case DMPAPER_B6: paper = FL_B6; break;
		case DMPAPER_EXECUTIVE:
			paper = Fl_Printer::EXECUTIVE; break;
		case DMPAPER_FOLIO:
			paper = Fl_Printer::FOLIO; break;
		case DMPAPER_LEDGER:
			paper = Fl_Printer::LEDGER; break;
		case DMPAPER_LEGAL:
			paper = Fl_Printer::LEGAL; break;
		case DMPAPER_LETTER:
			paper = Fl_Printer::LETTER; break;
		case DMPAPER_TABLOID:
			paper = Fl_Printer::TABLOID; break;
		case DMPAPER_ENV_10:
			paper = Fl_Printer::ENVELOPE; break;
		default:
			paper = Fl_Printer::A4;
	}
	return paper;
}

////////////// sets the paper size in DEVMODE /////////////////////

static void gdipaper(DEVMODE  *mode, int format)
{
	switch(format){
		case Fl_Printer::A3: mode->dmPaperSize = DMPAPER_A3; break;
		case Fl_Printer::A4: mode->dmPaperSize = DMPAPER_A4; break;
		case Fl_Printer::A5: mode->dmPaperSize = DMPAPER_A5; break;

		case Fl_Printer::B4: mode->dmPaperSize = DMPAPER_B4; break;
		case Fl_Printer::B5: mode->dmPaperSize = DMPAPER_B5; break;
		
		case Fl_Printer::EXECUTIVE: mode->dmPaperSize = DMPAPER_EXECUTIVE; break;
		case Fl_Printer::FOLIO: mode->dmPaperSize = DMPAPER_FOLIO; break;
		case Fl_Printer::LEDGER: mode->dmPaperSize = DMPAPER_LEDGER; break;
		case Fl_Printer::LEGAL: mode->dmPaperSize = DMPAPER_LEGAL; break;
		case Fl_Printer::LETTER: mode->dmPaperSize = DMPAPER_LETTER; break;
		case Fl_Printer::TABLOID: mode->dmPaperSize = DMPAPER_TABLOID; break;
		case Fl_Printer::ENVELOPE: mode->dmPaperSize = DMPAPER_ENV_9; break;
	
	}
}

int Fl_Gdi_Settings::format()
{
	int ret = -1;
	if(!mode) return -1;
	DEVMODE  *mod  = (DEVMODE *)GlobalLock(mode);
	ret = gdipaper(mod);
	GlobalUnlock(mode);
	return ret;
}

void Fl_Gdi_Settings::format(int f)
{
	init();
	DEVMODE  *mod  = (DEVMODE *)GlobalLock(mode);
	gdipaper(mod,f);
	GlobalUnlock(mode);
}

int Fl_Gdi_Settings::orientation()
{
	if(!mode) return -1;
	int orientation=0;
	DEVMODE  *mod  = (DEVMODE *)GlobalLock(mode);
	if (mod->dmOrientation == DMORIENT_LANDSCAPE)
		orientation=1;
	GlobalUnlock(mode);
	return orientation;
}

void Fl_Gdi_Settings::orientation(int o)
{
	init();
	DEVMODE  *mod  = (DEVMODE *)GlobalLock(mode);
	if(o)
		mod->dmOrientation = DMORIENT_LANDSCAPE;
	GlobalUnlock(mode);
}



//////////////////////////////////////////////////////////////////////////////////////////////

Fl_Gdi::Fl_Gdi(HDC gc, DEVMODE * mode):Fl_Printer(),gc_(gc),mode_(mode),delete_mode_(0)
{
	static DOCINFO DocInfo = { sizeof(DOCINFO), "FLTK Document", NULL,0 };// declare DocInfo for use and set the name of the print job as 'Name Of Document'
	DEVMODE  *mod  = (DEVMODE *)GlobalLock(mode_);
	int orientation_ = 0; 
	if(mod->dmOrientation==DMORIENT_LANDSCAPE)
		orientation_ = 1;
	int paper;
	if(mod->dmFields & DM_PAPERSIZE){
		paper = gdipaper(mod);
		
		if(mod->dmOrientation == DMORIENT_PORTRAIT){
			pw_ = Fl_Printer::page_formats[paper][0];
			ph_ = Fl_Printer::page_formats[paper][1];
		}else{
			pw_ = Fl_Printer::page_formats[paper][1];
			ph_ = Fl_Printer::page_formats[paper][0];
		}
	}
	
	
	
	ResetDC(gc_,mod);
	GlobalUnlock(mode_);
	SetMapMode(gc_, MM_ANISOTROPIC);
	SetTextAlign(gc_, TA_BASELINE|TA_LEFT);
	SetBkMode(gc_, TRANSPARENT);
	StartDoc(gc_, &DocInfo);
	ix = GetDeviceCaps(gc_, LOGPIXELSX);
	iy = GetDeviceCaps(gc_, LOGPIXELSY);
	ox = GetDeviceCaps(gc_, PHYSICALOFFSETX);
	oy = GetDeviceCaps(gc_, PHYSICALOFFSETY);

	nPages=0;
}


/////////////////////////////////   paging   //////////////////////////////////////


void Fl_Gdi::set_page(int page)
{
	DEVMODE * mode = (DEVMODE *) GlobalLock(mode_);
	if(page){
		ResetDC(gc_,mode);
		SetMapMode(gc_, MM_ANISOTROPIC);
		SetTextAlign(gc_, TA_BASELINE|TA_LEFT);
		SetBkMode(gc_, TRANSPARENT);
		StartPage(gc_);
		ix = GetDeviceCaps(gc_, LOGPIXELSX);
		iy = GetDeviceCaps(gc_, LOGPIXELSY);
		ox = GetDeviceCaps(gc_, PHYSICALOFFSETX);
		oy = GetDeviceCaps(gc_, PHYSICALOFFSETY);
	}
	GlobalUnlock(mode_);
	
	SetViewportOrgEx(gc_,VOx = (int)(ix * lm_ /72 - ox), VOy =(int)( iy *tm_ /72 - oy),0); //setting origin to the upper left corner inside margins
	SetViewportExtEx(gc_, VEx = (int)(ix * pw_ / 72),  (int)(VEy = iy * ph_ / 72),0);
	SetWindowExtEx(gc_, WEx = (int) pw_,  WEy = (int)ph_,0); //72 pixels per inch mapping
	SetWindowOrgEx(gc_, WOx = 0, WOy = 0,0);
}



void Fl_Gdi::page()
{
	if(nPages)
		EndPage(gc_);
	nPages++;
	set_page(1);
}

void Fl_Gdi::page(double pw, double ph, int orientation)
{
	if(nPages)
		EndPage(gc_);
	nPages++;
	pw_=pw;
	ph_=ph;
	orientation_ = orientation;
	DEVMODE * mode = (DEVMODE *)GlobalLock(mode_);
	if(orientation)
		mode->dmOrientation = DMORIENT_PORTRAIT;
	else
		mode->dmOrientation = DMORIENT_LANDSCAPE;
	mode->dmPaperWidth = (int) (pw*254/72);
	mode->dmPaperLength = (int) (ph*254/72);
	mode->dmFields |= DM_PAPERLENGTH | DM_PAPERWIDTH;
	mode->dmFields &= ~DM_PAPERSIZE;
	GlobalUnlock(mode_);
	set_page(1);
};
	

void Fl_Gdi::page(int format, int orientation)
{
	DEVMODE * mode = (DEVMODE *)GlobalLock(mode_);
	if(orientation){
		mode->dmOrientation = DMORIENT_LANDSCAPE;
		pw_ = Fl_Printer::page_formats[format][1];
		ph_ = Fl_Printer::page_formats[format][0];
	}else{
		mode->dmOrientation = DMORIENT_PORTRAIT;
		pw_ = Fl_Printer::page_formats[format][0];
		ph_ = Fl_Printer::page_formats[format][1];
	}
	if(format)
		gdipaper(mode, format);
	else{
		GlobalUnlock(mode_);
		page(pw_,ph_,orientation);
		return;
	}
	mode_->dmFields &= ~DM_PAPERLENGTH & ~DM_PAPERWIDTH;
	mode_->dmFields |= DM_PAPERSIZE;
	GlobalUnlock(mode_);
	set_page(1);
};

////////////////////////  margins and placing of drawinds on the page ///////////////////////////

void Fl_Gdi::margins(double left, double top, double right ,double bottom)
{
	lm_=left;
	tm_=top;
	rm_=right;
	bm_=bottom;
	if(nPages)
		set_page(0);
};


void Fl_Gdi::fit(double x, double y, double w, double h, int align)
{
	
	
	double dx, dy;
	double pwp = pw_ - lm_ - rm_;
	double php = ph_ - tm_ - bm_;

	double s = pwp/w;
	if(s<(php/h)){
		dx = 0;
		dy = (php - s * h)*iy/144;
	}else{
		s=php/h;
		dy =0;
		dx = (pwp - s * w)*ix/144;
	}

	if(align & 3)
		if(align & FL_ALIGN_TOP)
			dy=0;
		else
			dy *=2;
	if(align & 12)
		if(align & FL_ALIGN_LEFT)
			dx=0;
		else
			dx *=2;

	SetViewportOrgEx(gc_, VOx = (int)(ix * lm_ /72 - ox + dx), VOy = (int)( iy *tm_ /72 - oy + dy),0); //setting origin to the upper left corner inside margins
	SetWindowOrgEx(gc_, WOx = (int)x, WOy = (int)y,0);
	SetViewportExtEx(gc_,  VEx =(int) (ix*s),  VEy =(int) (iy*s), 0);
	SetWindowExtEx(gc_, WEx = 72,  WEy = 72,0);
};


void Fl_Gdi::place(double x, double y, double w, double h, double tx, double ty, double tw, double th,int align)
{
	
	
	double dx, dy;
	double s = tw/w;
	if(s<(th/h)){
		dx = 0;
		dy = (th - s * h)*iy/144;
	}else{
		s=th/h;
		dy =0;
		dx = (tw - s * w)*ix/144;
	}

	if(align & 3)
		if(align & FL_ALIGN_TOP)
			dy=0;
		else
			dy *=2;
	if(align & 12)
		if(align & FL_ALIGN_LEFT)
			dx=0;
		else
			dx *=2;
	
	SetViewportOrgEx(gc_, VOx = (int)(ix * (lm_+tx) /72 - ox + dx), VOy = (int)( iy *(tm_+th) /72 - oy + dy),0); //setting origin to the upper left corner inside margins
	SetWindowOrgEx(gc_, WOx = (int)x,  WOy = (int)y,0);
	SetViewportExtEx(gc_,  VEx =(int)(ix*s),  VEy =(int)(iy*s), 0);
	SetWindowExtEx(gc_, WEx = 72, WEy = 72,0); 
	
};


void Fl_Gdi::fit(double x, double y, double w, double h, double dpi, int align)
{
	double s = 72/dpi;
	double pwp = pw_ - lm_ - rm_;
	double php = ph_ - tm_ - bm_;
	double dy = (php - s * h)*iy/144;
	double dx = (pwp - s * w)*ix/144;

	if(align & 3)
		if(align & FL_ALIGN_TOP)
			dy=0;
		else
			dy *=2;
	if(align & 12)
		if(align & FL_ALIGN_LEFT)
			dx=0;
		else
			dx *=2;

	SetViewportOrgEx(gc_, VOx = (int)(ix * lm_ /72 - ox + dx), VOy = (int)( iy *tm_ /72 - oy + dy),0); //setting origin to the upper left corner inside margins
	SetWindowOrgEx(gc_, WOx = (int)x, WOy = (int)y,0);
	SetViewportExtEx(gc_,  VEx = (int)(ix*s),  VEy = (int)(iy*s), 0);
	SetWindowExtEx(gc_, WEx = 72, WEy = 72,0);
};

void Fl_Gdi::place(double x, double y, double w, double h, double tx, double ty, double tw, double th, double dpi, int align)
{
	double s = 72/dpi;
	double dy = (th - s * h)*iy/144;
	double dx = (tw - s * w)*ix/144;

	if(align & 3)
		if(align & FL_ALIGN_TOP)
			dy=0;
		else
			dy *=2;
	if(align & 12)
		if(align & FL_ALIGN_LEFT)
			dx=0;
		else
			dx *=2;

	SetViewportOrgEx(gc_, VOx = (int)(ix * (lm_+tx) /72 - ox + dx), VOy = (int)( iy *(tm_+ty) /72 - oy + dy),0); 
	SetWindowOrgEx(gc_, WOx = (int)x,  WOy = (int)y,0);
	SetViewportExtEx(gc_,  VEx = (int)(ix*s),  VEy = (int)(iy*s), 0);
	SetWindowExtEx(gc_, WEx = 72,  WEy = 72,0); 
};


////////  clipping, need to be re-implemented as orig. win32 functions are in device coordinates  ///////////

FL_API void Fl_Gdi::push_clip(int x, int y, int w, int h)
{
	Fl_Device::push_clip((x - WOx) * VEx / WEx + VOx,  (y - WOy) * VEy / WEy + VOy, w * VEx / WEx, h * VEy / WEy);
}

extern Fl_Region * fl_clip_stack;
extern int * fl_clip_stack_pointer;

FL_API int Fl_Gdi::not_clipped(int x, int y, int w, int h)
{
	Fl_Region r = fl_clip_stack[* fl_clip_stack_pointer];
	if (!r) return 1;
	RECT rect;
	rect.left = (x - WOx) * VEx / WEx + VOx;
	rect.top = (y - WOy) * VEy / WEy + VOy;
	rect.right  = (x + w - WOx) * VEx / WEx + VOx;
	rect.bottom  = (y + h - WOy) * VEy / WEy + VOy;
	return RectInRegion(r,&rect);
}

FL_API int Fl_Gdi::clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H)
{
	int ret = Fl_Device::clip_box((x - WOx) * VEx / WEx + VOx,  (y - WOy) * VEy / WEy + VOy, w * VEx / WEx, h * VEy / WEy, X, Y, W, H);
	X = (X - VOx ) * WEx / VEx + WOx;
	Y = (Y - VOy ) * WEy / VEy + WOy;
	W = W * WEx / VEx;
	H = H * WEy / VEy;
	return ret;
} 

//////////////////////// images (need to be uncached) /////////////////////////////////

/*FL_API void Fl_Gdi::draw_Pixmap(Fl_Pixmap * pxm,int XP, int YP, int WP, int HP, int cx, int cy)
{
	pxm->uncache();
	Fl_Device::draw_Pixmap(pxm, XP, YP, WP, HP, cx, cy);
	pxm->uncache();
}

FL_API void Fl_Gdi::draw_RGB(Fl_RGB_Image * rgb,int XP, int YP, int WP, int HP, int cx, int cy){
	rgb->uncache();
	Fl_Device::draw_RGB(rgb, XP, YP, WP, HP, cx, cy);
	rgb->uncache();
}

FL_API void Fl_Gdi::draw_Bitmap(Fl_Bitmap * bmp,int XP, int YP, int WP, int HP, int cx, int cy){
	bmp->uncache();
	Fl_Device::draw_Bitmap(bmp, XP, YP, WP, HP, cx, cy);
	bmp->uncache();
}
*/
#endif

