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

#include <efltk/Fl.h>
#include <efltk/Fl_Font.h>
#include <efltk/x.h>
#include <efltk/fl_draw.h>
#include <efltk/math.h>
#include <efltk/Fl_Util.h>
#include <efltk/Fl_String.h>

#include <ctype.h>
#include <stdio.h>
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
    //return fl_width((const char*)&(c), 1);
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

Fl_Font fl_create_font(const char *system_name)
{
    Fl_Font_ *f = new Fl_Font_;
    f->name_ = system_name;
    f->bold_ = f;
    f->italic_ = f;
    f->xlist_cached_ = false;
    f->first = 0;
    return f;
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

// return a pointer to a number we think is "point size":
char* fl_find_fontsize(char* name)
{
    char* c = name;
    // for standard x font names, try after 7th dash:
    if (*c == '-') {
        c = (char*)font_word(c,7);
        if (*c++ && isdigit(*c)) return c;
        return 0; // malformed x font name?
    }
    char* r = 0;
    // find last set of digits:
    for (c++;* c; c++)
        if (isdigit(*c) && !isdigit(*(c-1))) r = c;
    return r;
}

// return true if this matches fl_encoding:
int fl_correct_encoding(const char* name) {
  if (*name != '-') return 0;
  const char* c = font_word(name,13);
  return (*c++ && !strcmp(c, fl_encoding_));
}

#define MAXSIZE 32767

static char *find_best_font(Fl_Font_ *f, const char *fname, int size, int index)
{
    char **list = NULL;
    int cnt, offset;

    cnt = (int)f->xlist_sizes_[index];
    offset = (int)f->xlist_offsets_[index];
    list = (char**)f->xlist_.data();

    if(!list || cnt<=0) return "fixed";

    // search for largest <= font size:
    char* name = list[offset];
    int ptsize = 0; // best one found so far
    int matchedlength = 32767;
    static char namebuffer[1024]; // holds scalable font name
    bool found_encoding = false;

    for(int n=offset; n < offset+cnt; n++)
    {
        char* thisname = list[n];

        if (fl_correct_encoding(thisname)) {
            if (!found_encoding) ptsize = 0; // force it to choose this
            found_encoding = true;
        } else {
            if (found_encoding) continue;
        }
        char* c = (char*)fl_find_fontsize(thisname);
        int thissize = c ? atoi(c) : MAXSIZE;
        int thislength = strlen(thisname);
        if (thissize == size && thislength < matchedlength) {
            // exact match, use it:
            name = thisname;
            ptsize = size;
            matchedlength = thislength;
        } else if (!thissize && ptsize!=size) {
            // whoa!  A scalable font!  Use unless exact match found:
            int l = c-thisname;
            memcpy(namebuffer,thisname,l);
            l += sprintf(namebuffer+l,"%d",size);
            while (*c == '0') c++;
            strcpy(namebuffer+l,c);
            name = namebuffer;
            ptsize = size;
        } else if (!ptsize ||       // no fonts yet
                   thissize < ptsize && ptsize > size || // current font too big
                   thissize > ptsize && thissize <= size // current too small
                  ) {
            /*
            if (size > 24) {
                int l = c-thisname;
                memcpy(namebuffer,thisname,l);
                l += sprintf(namebuffer+l,"%d",size);
                while (*c != '-') c++;
                strcpy(namebuffer+l,c);
                name = namebuffer;
                ptsize = size;
            } else {
            */
                name = thisname;
                ptsize = thissize;
            //}
            matchedlength = thislength;
        }
    }
    return name;
}

static char *put_font_size(Fl_Font_ *font, int size)
{
    int i = 0;
    char *buf;
    const char *ptr;
    char *f;
    char *name;
    int nbf = 1;

    name = strdup(font->name_);
    while (name[i]) {
        if (name[i] == ',') {nbf++; name[i] = '\0';}
        i++;
    }

    buf = (char*) malloc(nbf * 256);
    buf[0] = '\0';
    ptr = name;
    i = 0;
    int cnt=0;
    while (ptr && nbf > 0) {
        f = find_best_font(font, ptr, size, cnt);
        while (*f) {
            buf[i] = *f;
            f++; i++;
        }
        nbf--; cnt++;
        while (*ptr) ptr++;
        if (nbf) {
            ptr++;
            buf[i] = ',';
            i++;
        }
        while(isspace(*ptr)) ptr++;
    }

    buf[i] = '\0';
    free(name);
    return buf;
}

uint Fl_Font_::cache_xlist()
{
    fl_open_display();
    if(xlist_cached_) return xlist_.size();

    char **names = fl_split(name_, ",", 255);
    if(!names) return 0;

    for(int n=0; names[n]; n++) {
        int cnt;
        char **xlist = XListFonts(fl_display, names[n], 255, &cnt);

        xlist_offsets_.append(xlist_.size());
        xlist_sizes_.append(cnt);
        for(int a=0; a<cnt; a++) {
            // Add all matching fonts to cache list
            xlist_.append(xlist[a]);
        }
    }

    fl_freev(names);
    xlist_cached_ = true;

    return xlist_.size();
}

Fl_FontSize *Fl_Font_::load_font(float psize)
{
    if(cache_xlist()==0) return 0;

    unsigned size = unsigned(psize);
    char *name = put_font_size(this, size);

    // okay, make the font:
    Fl_FontSize* f = new Fl_FontSize(name);

    // we pretend it has the current encoding even if it does not, so that
    // it is quickly matched when searching for it again with the same
    // encoding:
    f->encoding = fl_encoding_;

    f->minsize = size;
    f->maxsize = size;

    f->next = first;
    first = f;
    delete []name;

    return f;
}

void fl_font(Fl_Font font, float psize)
{
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
  for (f = font->first; f; f = f->next) {
      if (f->minsize <= size && f->maxsize >= size
          && (f->encoding==fl_encoding_ ||
              !f->encoding || !strcmp(f->encoding, fl_encoding_))
         )
      {
          set_current_fontsize(f);
          return;
      }
  }


  Fl_Font_ *t = (Fl_Font_*)font; // cast away const
  f = t->load_font(size);
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
