//
// "$Id$"
//
// Font selection code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2001 by Bill Spitzak and others.
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

#include <config.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Font.h>
#include <efltk/x.h>
#include <efltk/fl_draw.h>
#include <efltk/math.h>

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#if HAVE_XUTF8
#include "fl_utf8_x.h"
#endif


class Fl_FontSize {
public:
  Fl_FontSize* next;	// linked list for a single Fl_Font_
  
#if HAVE_XUTF8
  XUtf8FontStruct* font; // X UTF-8 font information
#else
  XFontStruct* font;
#endif  
  const char* encoding;
  Fl_FontSize(const char* xfontname);
  unsigned minsize;	// smallest point size that should use this
  unsigned maxsize;	// largest point size that should use this
  //  ~Fl_FontSize();
};

static Fl_FontSize *fl_fontsize;

static GC font_gc; // which gc the font was set in last time

static void
set_current_fontsize(Fl_FontSize* f) {
  if (f != fl_fontsize) {
    fl_fontsize = f;
    font_gc = 0;
  }
}

#define current_font (fl_fontsize->font)
#if HAVE_XUTF8
XUtf8FontStruct* fl_xfont() {return current_font;}
#else
XFontStruct* fl_xfont() {return current_font;}
#endif

Fl_FontSize::Fl_FontSize(const char* name) {
#  if HAVE_XUTF8
  font = XCreateUtf8FontStruct(fl_display, name);
#  else
  font = XLoadQueryFont(fl_display, name);
# endif  
  if (!font) {
    Fl::warning("bad font: %s", name);
#  if HAVE_XUTF8
    font = XCreateUtf8FontStruct(fl_display, "fixed"); 
#  else
    font = XLoadQueryFont(fl_display, "fixed"); // if fixed fails we crash
#  endif    
  }
  encoding = 0;
}

#if 0 // this is never called!
Fl_FontSize::~Fl_FontSize() {
  if (this == fl_fontsize) fl_fontsize = 0;
#  if HAVE_XUTF8
  XFreeUtf8FontStruct(fl_display, font);
#  else
  XFreeFont(fl_display, font);
#  endif  
}
#endif

////////////////////////////////////////////////////////////////
// Things you can do once the font+size has been selected:

// Placeholder function, Xft version needs to free something:
void Fl_Drawable::free_gc() {draw = 0;}

void fl_transformed_draw(const char *str, int n, float x, float y) {
  if (font_gc != fl_gc) {
    // I removed this, the user MUST set the font before drawing: (was)
    // if (!fl_fontsize) fl_font(FL_HELVETICA, FL_NORMAL_SIZE);
    font_gc = fl_gc;
#if !HAVE_XUTF8    
    XSetFont(fl_display, fl_gc, current_font->fid);
#endif    
  }
#if HAVE_XUTF8
  XUtf8DrawString(fl_display, fl_window, current_font, fl_gc, int(floorf(x+.5f)),
							      int(floorf(y+.5f)), str, n);
#else
  XDrawString(fl_display, fl_window, fl_gc,
	      int(floorf(x+.5f)),
	      int(floorf(y+.5f)), str, n);
#endif	      
}


void fl_rtl_draw(const char *str, int n, float x, float y) {
    if (font_gc != fl_gc) {
        font_gc = fl_gc;
#if !HAVE_XUTF8
        XSetFont(fl_display, fl_gc, fl_xfont()->fid);
#endif
    }
#if HAVE_XUTF8
    XUtf8DrawRtlString(fl_display, fl_window, current_font, fl_gc,
                       int(floorf(x+.5f)), int(floorf(y+.5f)), str, n);
#else
    XDrawString(fl_display, fl_window, fl_gc,
                int(floorf(x+.5f)),
                int(floorf(y+.5f)), str, n);
#endif
}


float fl_height() {
  return (current_font->ascent + current_font->descent);
}

float fl_descent() { return current_font->descent; }

float fl_width(const char *c, int n) {
#if HAVE_XUTF8
    return (float) XUtf8TextWidth(current_font, c, n);
#else
    return XTextWidth(current_font, c, n);
#endif    
}

float fl_width(uchar c) {
#if HAVE_XUTF8
  return (float) XUtf8UcsWidth(current_font, c);
#else
    XCharStruct* p = current_font->per_char;
    if (p) {
        int a = current_font->min_char_or_byte2;
        int b = current_font->max_char_or_byte2 - a;
        int x = c-a;
        if (x >= 0 && x <= b) return p[x].width;
    }
    return current_font->min_bounds.width;
#endif    
}


////////////////////////////////////////////////////////////////
// The rest of this file is the enormous amount of crap you have to
// do to get a font & size out of X.  To select a font+size, all
// matchine X fonts are listed with XListFonts, and then the first
// of the following is found and used:
//
//	pixelsize == size
//	pixelsize == 0 (which indicates a scalable font)
//	the largest pixelsize < size
//	the smallest pixelsize > size
//
// If any fonts match the fl_encoding() then the search is limited
// to those matching fonts. Otherwise all fonts are searched and thus
// a random encoding is chosen.
//
// I have not been able to find any other method than a search
// that will reliably return a bitmap version of the font if one is
// available at the correct size.  This is because X will not use a
// bitmap font unless all the extra fields are filled in correctly.
//
// Fltk uses pixelsize, not "pointsize".  This is what everybody wants!

// return dash number N, or pointer to ending null if none:
static const char *
font_word(const char* p, int n) {
  while (*p) {if (*p=='-') {if (!--n) break;} p++;}
  return p;
}

void fl_font(Fl_Font font, float psize) {
  Fl_FontSize* f = fl_fontsize;

  // only integers supported right now (this can be improved):
  psize = int(psize+.5);
  unsigned size = unsigned(psize);

  // See if the current font is correct:
  if (fl_font_ && font==fl_font_ &&
      psize == fl_size_)
      //&& (f->encoding==fl_encoding_ || !strcmp(f->encoding, fl_encoding_))) //this doesnt work, if you change the encoding...
      return;

  fl_font_ = font; fl_size_ = psize;

  // search the FontSize we have generated already:
  for (f = font->first; f; f = f->next)
    if (f->minsize <= size && f->maxsize >= size
        && (f->encoding==fl_encoding_ ||
	    !f->encoding || !strcmp(f->encoding, fl_encoding_))) {
      set_current_fontsize(f); return;
    }

  // now search the XListFonts results:
  if (!font->xlist) {
    fl_open_display();
    Fl_Font_* t = (Fl_Font_*)font; // cast away const
    t->xlist = XListFonts(fl_display, t->name_, 100, &(t->n));
    if (!t->xlist || t->n<=0) {	// use variable if no matching font...
      t->first = f = new Fl_FontSize("variable");
      f->minsize = 0;
      f->maxsize = 32767;
      set_current_fontsize(f); return;
    }
  }

  char* name = font->xlist[0];
  unsigned ptsize = 0;	// best one found so far
  char namebuffer[1024];	// holds scalable font name
  bool found_encoding = false;
  int m = font->n; if (m<0) m = -m;

  for (int n=0; n < m; n++) {

    char* thisname = font->xlist[n];
    // get the encoding field:
    const char* this_encoding = font_word(thisname, 13);
    if (*this_encoding++ && !strcmp(this_encoding, fl_encoding_)) {
      // forget any wrong encodings when we find a correct one:
      if (!found_encoding) ptsize = 0;
      found_encoding = true;
    } else {
      // ignore later wrong encodings after we find a correct one:
      if (found_encoding) continue;
    }
    // get the pixelsize field:
    const char* c = font_word(thisname,7);
    unsigned thissize = *c ? atoi(++c) : 32767;
    if (thissize == size) {
      // Use an exact match:
      name = thisname;
      ptsize = size;
      if (found_encoding) break;
    } else if (!thissize && ptsize!=size) {
      // Use a scalable font if no exact match found:
      int l = c-thisname;
      memcpy(namebuffer,thisname,l);
      // print the pointsize into it:
      if (size>=100) namebuffer[l++] = size/100+'0';
      if (size>=10) namebuffer[l++] = (size/10)%10+'0';
      namebuffer[l++] = (size%10)+'0';
      while (*c == '0') c++;
      strcpy(namebuffer+l,c);
      name = namebuffer;
      ptsize = size;
    } else if (!ptsize ||	// no fonts yet
               thissize < ptsize && ptsize > size || // current font too big
               thissize > ptsize && thissize <= size // current too small
      ) {
      // Use the nearest fixed size font:
      name = thisname;
      ptsize = thissize;
    }
  }

  // If we didn't find an exact match, search the list to see if we already
  // found this font:
  if (ptsize != size || !found_encoding) {
    for (f = font->first; f; f = f->next) {
      if (f->minsize <= ptsize && f->maxsize >= ptsize &&
	  (!found_encoding || !strcmp(f->encoding, fl_encoding_))) {
	if (f->minsize > size) f->minsize = size;
	if (f->maxsize < size) f->maxsize = size;
	set_current_fontsize(f); return;
      }
    }
  }

  // okay, we definately have some name, make the font:
  f = new Fl_FontSize(name);
  // we pretend it has the current encoding even if it does not, so that
  // it is quickly matched when searching for it again with the same
  // encoding:
  f->encoding = fl_encoding_;
  if (ptsize < size) {f->minsize = ptsize; f->maxsize = size;}
  else {f->minsize = size; f->maxsize = ptsize;}
  f->next = font->first;
  ((Fl_Font_*)font)->first = f;
  set_current_fontsize(f);

}

// Change the encoding to use for the next font selection.
void fl_encoding(const char* f) {
  fl_encoding_ = f;
}

////////////////////////////////////////////////////////////////

// The predefined fonts that fltk has:  bold:       italic:
Fl_Font_
fl_fonts[] = {
{"-*-helvetica-medium-r-normal--*",	fl_fonts+1, fl_fonts+2},
{"-*-helvetica-bold-r-normal--*", 	fl_fonts+1, fl_fonts+3},
{"-*-helvetica-medium-o-normal--*",	fl_fonts+3, fl_fonts+2},
{"-*-helvetica-bold-o-normal--*",	fl_fonts+3, fl_fonts+3},
{"-*-courier-medium-r-normal--*",	fl_fonts+5, fl_fonts+6},
{"-*-courier-bold-r-normal--*",		fl_fonts+5, fl_fonts+7},
{"-*-courier-medium-o-normal--*",	fl_fonts+7, fl_fonts+6},
{"-*-courier-bold-o-normal--*",		fl_fonts+7, fl_fonts+7},
{"-*-times-medium-r-normal--*",		fl_fonts+9, fl_fonts+10},
{"-*-times-bold-r-normal--*",		fl_fonts+9, fl_fonts+11},
{"-*-times-medium-i-normal--*",		fl_fonts+11,fl_fonts+10},
{"-*-times-bold-i-normal--*",		fl_fonts+11,fl_fonts+11},
{"-*-symbol-*",				fl_fonts+12,fl_fonts+12},
{"-*-lucidatypewriter-medium-r-normal-sans-*", fl_fonts+14,fl_fonts+14},
{"-*-lucidatypewriter-bold-r-normal-sans-*", fl_fonts+14,fl_fonts+14},
{"-*-*zapf dingbats-*",			fl_fonts+15,fl_fonts+15},
};

//
// End of "$Id$"
//
