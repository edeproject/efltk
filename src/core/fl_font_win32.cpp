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
#include <efltk/fl_utf8.h>

#ifdef _WIN32_WCE
#include <wince.h>
#endif

class Fl_FontSize {
public:
  Fl_FontSize *next;	// linked list for a single Fl_Font_
  unsigned size;
  int charset;
  int *width[64];
  HFONT font;
  TEXTMETRIC metr;
  Fl_FontSize(const char* fontname, int size, int charset);
  ~Fl_FontSize();
};

static Fl_FontSize* fl_fontsize;

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
#ifndef _WIN32_WCE
	EIF("Hangul")			HANGUL_CHARSET;
#endif
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

extern char *fl_utf82locale(const char *s, UINT codepage = 0);

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

  HFONT font;
  LOGFONT lFont;

  lFont.lfHeight         = -size; // use "char size"
  lFont.lfWidth          = 0L;
  lFont.lfEscapement     = 0L;
  lFont.lfOrientation    = 0L;
  lFont.lfWeight         = weight;
  lFont.lfItalic         = italic;
  lFont.lfUnderline      = FALSE;
  lFont.lfStrikeOut      = FALSE;
  lFont.lfCharSet        = charset;
  lFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
  lFont.lfPitchAndFamily = DEFAULT_PITCH & FF_DONTCARE;

#ifdef _WIN32_WCE
  lFont.lfOutPrecision   = OUT_DEFAULT_PRECIS;
  lFont.lfQuality        = DEFAULT_QUALITY;
#else
  lFont.lfOutPrecision   = OUT_DEVICE_PRECIS;   // CE doesn't understand
  lFont.lfQuality        = PROOF_QUALITY;       // CE doesn't understand
#endif

  TCHAR *family_name;
#ifdef UNICODE
  int len = fl_utf_nb_char((unsigned char*)name, strlen(name));
  family_name = (TCHAR*)malloc((len + 1) * sizeof(TCHAR));
  fl_utf2unicode((unsigned char*)name, len, (unsigned short*)family_name);
  family_name[len] = 0;
  wcsncpy(lFont.lfFaceName, family_name, LF_FACESIZE);
#else
  family_name = fl_utf82locale(name);
  strncpy(lFont.lfFaceName, family_name, LF_FACESIZE);
#endif  

  font = ::CreateFontIndirect( &lFont );

  HDC dc = fl_getDC();
  SelectObject(dc, font);

  for(int i = 0; i < 64; i++) width[i] = 0;
  GetTextMetrics(dc, &fl_fontsize->metr);
  
  this->font = font;
  this->size = size;
  this->charset = charset;

  append_font(this);
}

Fl_FontSize::~Fl_FontSize() {
  if (this == fl_fontsize) fl_fontsize = 0;
  DeleteObject(font);
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
HFONT fl_xfont() { return current_font; }
TEXTMETRIC *fl_textmetric() { return &(fl_fontsize->metr); }

// we need to decode the encoding somehow!
static int fl_charset = DEFAULT_CHARSET;

void Fl_Device::font(Fl_Font font, float psize) 
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

float Fl_Device::height()  const { return float(fl_fontsize->metr.tmAscent + fl_fontsize->metr.tmDescent); }
float Fl_Device::descent() const { return float(fl_fontsize->metr.tmDescent); }

// Unicode string buffer
static unsigned short *wstr = NULL;
static int wstr_len	= 0;
#define resize_buffer(len) \
if(len > wstr_len) { \
		if(wstr) wstr = (unsigned short*)realloc(wstr, sizeof(short) * len); \
		else wstr = (unsigned short*)malloc(sizeof(short) * len); \
		wstr_len = len; \
}

float Fl_Device::width(const char* c, int n) const
{
  int i = 0;
  float w = 0;
  unsigned int ucs;
  while (i < n) {    
    int l = fl_fast_utf2ucs((const unsigned char*)c + i, n - i, &ucs);
    if (l < 1) l = 1; 
    i += l;
    if (!fl_nonspacing(ucs)) {
      w += fl_width(ucs);
    }
  }
  return w;
}

float Fl_Device::width(unsigned int ucs) const
{
	unsigned int r = (ucs & 0xFC00)>>10;
	if(!fl_fontsize->width[r]) 
	{
		SIZE s;
		HDC dc = fl_getDC();
		SelectObject(dc, current_font);
     	fl_fontsize->width[r] = new int[0x0400];        
		unsigned short i=0, ii = r * 0x400;
		for (; i < 0x400; i++) {
			GetTextExtentPoint32W(dc, (const WCHAR*)&ii, 1, &s);
			fl_fontsize->width[r][i] = s.cx;
			ii++;
		}		
	}
	return float(fl_fontsize->width[r][ucs&0x03FF]);
}

static inline int wchar_width(WCHAR *wc, int len) {
	float W=0;
	for(int n=0; n<len; n++) W += fl_width(wc[n]);
	return int(W);

}

void Fl_Device::transformed_draw(const char *str, int n, float x, float y) 
{
	SetTextColor(fl_gc, fl_colorref);
	SelectObject(fl_gc, current_font);
	
#ifdef _WIN32_WCE
	RECT rect = { int(floor(x+.5f)), int(floor(y+.5f)), 0, 0 };	
#else
    int X = int(floor(x+.5f));
    int Y = int(floor(y+.5f));
#endif

	unsigned ucs;
	unsigned no_spc;
    WCHAR buf[128];		// drawing buffer
    int pos = 0;		// position in buffer

	while(n > 0) {

        if(pos>120) {
#ifdef _WIN32_WCE			
			DrawText(fl_gc, buf, pos, &rect, DT_SINGLELINE | DT_TOP | DT_LEFT | DT_NOCLIP);	
			rect.left += wchar_width(buf, pos);
#else
			TextOutW(fl_gc, X, Y, buf, pos);
			X += wchar_width(buf, pos);
#endif
			pos = 0;
        }

        int ulen = fl_fast_utf2ucs((unsigned char*)str, n, &ucs);
        if (ulen < 1) ulen = 1;
        no_spc = fl_nonspacing(ucs);
        if(no_spc) ucs = no_spc;
		buf[pos] = ucs;

        if(no_spc) {
#ifdef _WIN32_WCE
			DrawText(fl_gc, buf, pos, &rect, DT_SINGLELINE | DT_TOP | DT_LEFT | DT_NOCLIP);	
			rect.left += wchar_width(buf, pos);
			rect.left -= fl_width(buf[pos]);
#else
			TextOutW(fl_gc, X, Y, buf, pos);
			X += wchar_width(buf, pos);
			X -= fl_width(buf[pos]);
#endif
            buf[0] = ucs;
			pos = 0;
        }

        pos++;
        str += ulen;
        n-=ulen;
    }
    if(pos>0)
#ifdef _WIN32_WCE			
		DrawText(fl_gc, buf, pos, &rect, DT_SINGLELINE | DT_TOP | DT_LEFT | DT_NOCLIP);	
#else
		TextOutW(fl_gc, X, Y, buf, pos);
#endif
}

void Fl_Device::rtl_draw(const char *str, int n, float x, float y)
{
	// USE BUFFER HERE ALSO
	SetTextColor(fl_gc, fl_colorref);
	SelectObject(fl_gc, current_font);

	int i = 0;
	int lx = 0;
	const WCHAR *skod;
	resize_buffer(n);
	int wn = fl_utf2unicode((const unsigned char *)str, n, wstr);

	while (i < wn) {
	    lx = int(fl_width(wstr[i]));
		x -= lx;
		skod = (const WCHAR*)wstr + i;
#ifndef _WIN32_WCE
		TextOutW(fl_gc, int(floor(x+.5f)), int(floor(y+.5f)), skod, 1);
#else
		RECT rect = {int(floor(x+.5f)),int(floor(y+.5f)), 0,0};
		DrawText(fl_gc, skod, 1, &rect, DT_SINGLELINE | DT_TOP | DT_LEFT | DT_NOCLIP);	
#endif
		if (fl_nonspacing(wstr[i])) {
			x += lx;
		}
		i++;
	}	
}

// Change the encoding to use for the next font selection.
void Fl_Device::encoding(const char* f) {
    fl_encoding_ = f;
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
