//
// "$Id$"
//
// _WIN32 font selection routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#include <efltk/Fl_Font.h>
#include <efltk/x.h>
#include <ctype.h>
#include <stdlib.h>
#include <efltk/math.h>

#if HAVE_XUTF8
# include <efltk/fl_utf8.h>
#endif

class Fl_FontSize {
public:
  Fl_FontSize *next;	// linked list for a single Fl_Font_
  Fl_FontSize *next_all;// linked list so we can destroy em all
  unsigned size;
  int charset;
#if HAVE_XUTF8
  int *width[64];
#else
  int width[255];
#endif
  HFONT font;
  TEXTMETRIC metr;
  Fl_FontSize(const char* fontname, int size, int charset);
  ~Fl_FontSize();
};

static Fl_FontSize* fl_fontsize;
static Fl_FontSize* all_fonts;

#include <stdio.h>

static DWORD str_to_charset(const char *str)
{
	if(!str || !*str) return DEFAULT_CHARSET;

#define EIF(s) else if(!strcmp(str, s)) return 
	
	if(strstr(str, "8859"))	return ANSI_CHARSET; //Return ANSI for ISO8859-* ?
	EIF("Ansi")				ANSI_CHARSET;
	EIF("Baltic")			BALTIC_CHARSET;
	EIF("Chinese Big5")		CHINESEBIG5_CHARSET;
	EIF("Eastern Europe")	EASTEUROPE_CHARSET;
	EIF("Gb2312")			GB2312_CHARSET;
	EIF("Greek")			GREEK_CHARSET;
	EIF("Hangul")			HANGUL_CHARSET;
	EIF("MAC")				MAC_CHARSET;
	EIF("OEM")				OEM_CHARSET;
	EIF("Russian")			RUSSIAN_CHARSET;
	EIF("Shift Jis")		SHIFTJIS_CHARSET;
	EIF("Symbol")			SYMBOL_CHARSET;
	EIF("Turkish")			TURKISH_CHARSET;
	EIF("Vietnamese")		VIETNAMESE_CHARSET;
	EIF("Johab")			JOHAB_CHARSET;
	EIF("Arabic")			ARABIC_CHARSET;
	EIF("Hebrew")			HEBREW_CHARSET;
	EIF("Thai")				THAI_CHARSET;

	return DEFAULT_CHARSET;	
}

Fl_FontSize::Fl_FontSize(const char* name, int size, int charset) 
{	
  fl_fontsize = this;

  int weight = FW_NORMAL;
  int italic = 0;

  // may be efficient, but this is non-obvious
  switch (*name++) {
  case 'I': italic = 1; break;
  case 'P': italic = 1;
  case 'B': weight = FW_BOLD; break;
  case ' ': break;
  default: name--;
  }

  HFONT font = CreateFont(
    -size,	    // use "char size"
    0,		    // logical average character width
    0,		    // angle of escapement
    0,		    // base-line orientation angle
    weight,
    italic,
    FALSE,		// underline attribute flag
    FALSE,		// strikeout attribute flag
    charset,		// character set identifier
    OUT_DEFAULT_PRECIS, // output precision
    CLIP_DEFAULT_PRECIS,// clipping precision
    DEFAULT_QUALITY,	// output quality
    DEFAULT_PITCH,	// pitch and family
    name		// pointer to typeface name string
  );

  HDC dc = fl_getDC();
  SelectObject(dc, font);
#ifdef HAVE_XUTF8
  for(int i = 0; i < 64; i++) width[i] = 0;
#else
  GetCharWidth(dc, 0, 255, width);
#endif
  GetTextMetrics(dc, &fl_fontsize->metr);
  
  this->font = font;
  this->size = size;
  this->charset = charset;
  next_all = all_fonts;
  all_fonts = this;  
}

Fl_FontSize::~Fl_FontSize() {
  if (this == fl_fontsize) fl_fontsize = 0;
  DeleteObject(font);
}

// Deallocate Win32 fonts on exit. Warning: it will crash if you try
// to do any fonts after this, because the pointers are not changed!
void fl_font_rid() {
  for (Fl_FontSize* fontsize = all_fonts; fontsize;) {
    Fl_FontSize* next = fontsize->next;
    delete fontsize;
    fontsize = next;
  }
}

Fl_Font fl_create_font(const char *system_name)
{
    Fl_Font_ *f = new Fl_Font_;
    f->name_ = system_name;
    f->bold_ = f;
    f->italic_ = f;
    f->first = 0;
	f->charsets_ = 0;
	f->sizes_ = 0;
    return f;
}

////////////////////////////////////////////////////////////////
// Public interface:

#define current_font (fl_fontsize->font)
HFONT fl_xfont() {return current_font;}
TEXTMETRIC* fl_textmetric() {return &(fl_fontsize->metr);}

// we need to decode the encoding somehow!
static int fl_charset = DEFAULT_CHARSET;

void fl_font(Fl_Font font, float psize) 
{
	fl_charset = str_to_charset(fl_encoding_);	

  // only integers supported right now, I think there is a newer
  // interface that takes arbitrary sizes, though...
  psize = float(int(psize+.5f));
  unsigned size = unsigned(psize);

  if (font == fl_font_ && psize == fl_size_ &&
      fl_fontsize->charset == fl_charset) return;
  fl_font_ = font; fl_size_ = psize;

  Fl_FontSize* f;
  // search the fontsizes we have generated already:
  for (f = font->first; f; f = f->next) {
	if (f->size == size && f->charset == fl_charset) break;
  }

  if (!f) {
		f = new Fl_FontSize(font->name_, size, fl_charset);
		f->next = font->first;
		((Fl_Font_*)font)->first = f;
  }
  
  fl_fontsize = f;
}

float fl_height()  { return float(fl_fontsize->metr.tmAscent + fl_fontsize->metr.tmDescent); }
float fl_descent() { return float(fl_fontsize->metr.tmDescent); }

// Unicode string buffer
static unsigned short *wstr = NULL;
static int wstr_len	= 0;
#define resize_buffer(len) \
if(len > wstr_len) { \
		if(wstr) wstr = (unsigned short*)realloc(wstr, sizeof(short) * len); \
		else wstr = (unsigned short*)malloc(sizeof(short) * len); \
		wstr_len = len; \
}

float fl_width(const char* c, int n) 
{
#if HAVE_XUTF8
  int i = 0;
  float w = 0;
  unsigned int ucs;
  while (i < n) {    
    int l = fl_utf2ucs((const unsigned char*)c + i, n - i, &ucs);
    if (l < 1) l = 1; 
    i += l;
    if (!fl_nonspacing(ucs)) {
      w += fl_width(ucs);
    }
  }
  return  w;
#else  		
	SIZE size;
	HDC dc = fl_getDC();
	SelectObject(dc, current_font);
	// I think win32 has a fractional version of this:
	GetTextExtentPoint(dc, c, n, &size);	
	return float(size.cx);
#endif
}

#if HAVE_XUTF8
float fl_width(unsigned int ucs) {
	unsigned int r = (ucs & 0xFC00)>>10;
	if(!fl_fontsize->width[r]) {
		SIZE s;
		HDC dc = fl_getDC();
		SelectObject(dc, current_font);
     	fl_fontsize->width[r] = new int[0x0400];        
		unsigned short i=0, ii = r * 0x400;
		for (; i < 0x400; i++) {
			GetTextExtentPoint32W(dc, &ii, 1, &s);
			fl_fontsize->width[r][i] = s.cx;
			ii++;
		}		
	}
	return float(fl_fontsize->width[r][ucs&0x03FF]);
}
#else
float fl_width(unsigned int c) {
	if(c>255) c=255;
    return float(fl_fontsize->width[c]);
}
#endif

void fl_transformed_draw(const char *str, int n, float x, float y) 
{
	SetTextColor(fl_gc, fl_colorref);
	SelectObject(fl_gc, current_font);
#if HAVE_XUTF8	
	int wn = 0;
	int i = 0;
	int lx = 0;
	while (i < n) {
		unsigned int u;
		unsigned short ucs;
		int l = fl_utf2ucs((const unsigned char*)str + i, n - i, &u);
		if (fl_nonspacing(u)) {
			x -= lx;
		} else {
	        lx = (int) fl_width(u);
		}
		ucs = u; 
		if (l < 1) l = 1;
		i += l;
		TextOutW(fl_gc, x, y, &ucs, 1);
		x += lx;
	}
#else
	TextOut(fl_gc, int(floorf(x+.5f)), int(floorf(y+.5f)), str, n);  
#endif
}

void fl_rtl_draw(const char *str, int n, float x, float y)
{
	int i = 0;
	int lx = 0;
#if HAVE_XUTF8
	resize_buffer(n);
	int wn = fl_utf2unicode((const unsigned char *)str, n, wstr);
	SetTextColor(fl_gc, fl_colorref);
	SelectObject(fl_gc, current_font);
	while (i < wn) {
	    lx = int(fl_width(wstr[i]));
		x -= lx;
		TextOutW(fl_gc, int(floorf(x+.5f)), int(floorf(y+.5f)),
				wstr + i, 1);
		if (fl_nonspacing(wstr[i])) {
			x += lx;
		}
		i++;
	}	
#else
	SetTextColor(fl_gc, fl_colorref);
	SelectObject(fl_gc, current_font);
	while(i < n) {
	    lx = int(fl_width(str[i]));
		x -= lx;
		TextOut(fl_gc, int(floorf(x+.5f)), int(floorf(y+.5f)), 
				str + i, 1);
		i++;
	}
#endif
}

// Change the encoding to use for the next font selection.
void fl_encoding(const char* f) {
  if (f != fl_encoding_) {
    fl_encoding_ = f;
    // charset = decode_the_encoding(f);
  }
}

////////////////////////////////////////////////////////////////

// The predefined fonts that fltk has:  bold:       italic:
Fl_Font_ fl_fonts[] = {
	{" Arial",				fl_fonts+1, fl_fonts+2,0,0},
	{"BArial", 				fl_fonts+1, fl_fonts+3,0,0},
	{"IArial",				fl_fonts+3, fl_fonts+2,0,0},
	{"PArial",				fl_fonts+3, fl_fonts+3,0,0},
	{" Courier New",		fl_fonts+5, fl_fonts+6,0,0},
	{"BCourier New",		fl_fonts+5, fl_fonts+7,0,0},
	{"ICourier New",		fl_fonts+7, fl_fonts+6,0,0},
	{"PCourier New",		fl_fonts+7, fl_fonts+7,0,0},
	{" Times New Roman",	fl_fonts+9, fl_fonts+10,0,0},
	{"BTimes New Roman",	fl_fonts+9, fl_fonts+11,0,0},
	{"ITimes New Roman",	fl_fonts+11,fl_fonts+10,0,0},
	{"PTimes New Roman",	fl_fonts+11,fl_fonts+11,0,0},
	{" Symbol",				fl_fonts+12,fl_fonts+12,0,0},
	{" Terminal",			fl_fonts+14,fl_fonts+14,0,0},
	{"BTerminal",			fl_fonts+14,fl_fonts+14,0,0},
	{" Wingdings",			fl_fonts+15,fl_fonts+15,0,0},
};

//
// End of "$Id$".
//
