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

#include <efltk/Fl_String_Hash.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Font.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Util.h>
#include <efltk/Fl_String.h>
#include <efltk/x.h>
#include <efltk/fl_utf8.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const int fl_encoding_number(const char *enc);
extern const int fl_ucs2fontmap(char *s, unsigned int ucs, int enc);

class Fl_FontSize {
public:
    Fl_FontSize* next;	// linked list for a single Fl_Font_

    Fl_FontSize(const char* xfontname);

    XFontStruct* font;
    const char* encoding;
    int encoding_num;

    unsigned minsize;	// smallest point size that should use this
    unsigned maxsize;	// largest point size that should use this
    //  ~Fl_FontSize();
};

static Fl_FontSize *fl_fontsize;
static GC font_gc; // which gc the font was set in last time

static void set_current_fontsize(Fl_FontSize* f)
{
    if (f != fl_fontsize) {
        fl_fontsize = f;
        font_gc = 0;
    }
}

#define current_font (fl_fontsize->font)
XFontStruct* fl_xfont() { return current_font; }

Fl_FontSize::Fl_FontSize(const char* name)
{
    font = XLoadQueryFont(fl_display, name);
    if(!font) {
        Fl::warning("bad font: %s", name);
        // if fixed fails we crash
        font = XLoadQueryFont(fl_display, "fixed");
    }
    encoding = 0;
    encoding_num = -1;
}

#if 0 // this is never called!
Fl_FontSize::~Fl_FontSize()
{
    if (this == fl_fontsize) fl_fontsize = 0;
    XFreeFont(fl_display, font);
}
#endif

////////////////////////////////////////////////////////////////
// Things you can do once the font+size has been selected:

// Placeholder function, Xft version needs to free something:
void Fl_Drawable::free_gc() { draw = 0; }

void Fl_Device::transformed_draw(const char *str, int n, float x, float y)
{
    if (font_gc != fl_gc) {
        font_gc = fl_gc;
        XSetFont(fl_display, fl_gc, current_font->fid);
    }

    int X = int(floor(x+.5f));
    int Y = int(floor(y+.5f));

#if HAVE_XUTF8
    char glyph[2];       // byte1 and byte2 value of the UTF-8 char
    XChar2b buf[128];    // drawing buffer
    int pos = 0;         // position in buffer
    int  ulen;           // byte length of the UTF-8 char
    unsigned int ucs;    // Unicode value of the UTF-8 char
    unsigned int no_spc; // Spacing char equivalent of a non-spacing char

    while(n > 0) {

        if(pos>120) {
            XDrawString16(fl_display, fl_window, fl_gc, X, Y, buf, pos);
            X += XTextWidth16(current_font, buf, pos);
            pos = 0;
        }

        ulen = fl_fast_utf2ucs((unsigned char*)str, n, &ucs);
        if (ulen < 1) ulen = 1;
        no_spc = fl_nonspacing(ucs);
        if(no_spc) ucs = no_spc;

        if(fl_ucs2fontmap(glyph, ucs, fl_fontsize->encoding_num) < 0) {
            // the char is not valid in this encoding
            fl_ucs2fontmap(glyph, '?', fl_fontsize->encoding_num);
        }

        if(no_spc) {
            XDrawString16(fl_display, fl_window, fl_gc, X, Y, buf, pos);
            X += XTextWidth16(current_font, buf, pos);
            pos = 0;
            (*buf).byte1 = glyph[1];
            (*buf).byte2 = glyph[0];
            X -= XTextWidth16(current_font, buf, 1);
        } else {
            (*(buf + pos)).byte1 = glyph[1];
            (*(buf + pos)).byte2 = glyph[0];
        }

        pos++;
        str += ulen;
        n-=ulen;
    }
    if(pos>0)
        XDrawString16(fl_display, fl_window, fl_gc, X, Y, buf, pos);
#else
    XDrawString(fl_display, fl_window, fl_gc, X, Y, str, n);
#endif
}

void Fl_Device::rtl_draw(const char *str, int n, float x, float y) {
    if (font_gc != fl_gc) {
        font_gc = fl_gc;
        XSetFont(fl_display, fl_gc, ((XFontStruct*)fl_xfont())->fid);
    }
    ///
    ///
}

float Fl_Device::height() const { return (current_font->ascent + current_font->descent); }
float Fl_Device::descent() const { return current_font->descent; }

float Fl_Device::width(const char *str, int n) const
{
#if HAVE_XUTF8
    char glyph[2];       // byte1 and byte2 value of the UTF-8 char
    XChar2b buf[128];    // measure buffer
    int pos = 0;         // position in buffer
    int  ulen;           // byte length of the UTF-8 char
    unsigned int ucs;    // Unicode value of the UTF-8 char
    unsigned int no_spc; // Spacing char equivalent of a non-spacing char
    float W=0;

    while(n > 0) {
        if(pos>120) {
            W += XTextWidth16(current_font, buf, pos);
            pos = 0;
        }

        ulen = fl_fast_utf2ucs((unsigned char*)str, n, &ucs);
        if (ulen < 1) ulen = 1;
        no_spc = fl_nonspacing(ucs);
        if(no_spc) ucs = no_spc;

        if(fl_ucs2fontmap(glyph, ucs, fl_fontsize->encoding_num) < 0) {
            // the char is not valid in this encoding
            fl_ucs2fontmap(glyph, '?', fl_fontsize->encoding_num);
        }

        if(no_spc) {
            W += XTextWidth16(current_font, buf, pos);
            pos = 0;
            (*buf).byte1 = glyph[1];
            (*buf).byte2 = glyph[0];
            W -= XTextWidth16(current_font, buf, 1);
        } else {
            (*(buf + pos)).byte1 = glyph[1];
            (*(buf + pos)).byte2 = glyph[0];
        }

        pos++;
        str += ulen;
        n-=ulen;
    }
    if(pos>0)
        W += XTextWidth16(current_font, buf, pos);
    return W;
#else
    return XTextWidth(current_font, str, n);
#endif
}

float Fl_Device::width(unsigned int c) const
{
#if HAVE_XUTF8
    unsigned int ucs;
    unsigned int ulen = fl_fast_utf2ucs((unsigned char*)&c, 1, &ucs);
    if (ulen < 1) ulen = 1;
    unsigned int no_spc = fl_nonspacing(ucs);
    if(no_spc) ucs = no_spc;

    char glyph[2];
    if(fl_ucs2fontmap(glyph, ucs, fl_fontsize->encoding_num) < 0) {
        // the char is not valid in this encoding
        fl_ucs2fontmap(glyph, '?', fl_fontsize->encoding_num);
    }

    XChar2b char2[2];
    char2[0].byte1 = glyph[1];
    char2[0].byte2 = glyph[0];
    char2[1].byte1 = char2[1].byte2 = 0;
    return XTextWidth16(current_font, char2, 1);
#else
    char ch=char(c);
    return width(&ch,1);
#endif    
}

Fl_Font fl_create_font(const char *system_name)
{
    Fl_Font_ *f = new Fl_Font_;
    f->name_ = system_name;
    f->bold_ = f;
    f->italic_ = f;
    f->xlist_ = 0;
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
const char *font_word(const char* p, int n)
{
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
  return (*c++ && !strcasecmp(c, fl_encoding_));
}

#define MAXSIZE 32767

static char *find_best_font(Fl_Font_ *f, const char *fname, int size)
{
    char **list = f->xlist_;
    int cnt = f->xlist_n_;

    if(!list) return "fixed";
    if(cnt<0) cnt = -cnt;

    // search for largest <= font size:
    char* name = list[0];
    int ptsize = 0; // best one found so far
    static char namebuffer[1024]; // holds scalable font name
    bool found_encoding = false;

    for(int n=0; n < cnt; n++)
    {
        char* thisname = list[n];
        if (fl_correct_encoding(thisname)) {
            if (!found_encoding) ptsize = 0; // force it to choose this
            found_encoding = true;
        } else {
            if (found_encoding) continue;
        }

        char *c = (char*)fl_find_fontsize(thisname);
        int thissize = c ? strtol(c,NULL,10) : MAXSIZE;

        if (thissize == size) {

            // exact match, use it:
            name = thisname;
            ptsize = size;
            break;

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
            break;

        } else if (!ptsize ||       // no fonts yet
                   thissize < ptsize && ptsize > size || // current font too big
                   thissize > ptsize && thissize <= size // current too small
                  ) {
            name = thisname;
            ptsize = thissize;
        }
    }
    return name;
}

uint Fl_Font_::cache_xlist()
{
    fl_open_display();
    if(xlist_) return xlist_n_;

    xlist_ = XListFonts(fl_display, name_, 255, &xlist_n_);
    return xlist_n_;
}

Fl_FontSize *Fl_Font_::load_font(float psize)
{
    Fl_FontSize *f;
    if(cache_xlist()==0) {
        // use variable if no matching font...
        f = new Fl_FontSize("variable");
        f->minsize = 0;
        f->maxsize = 32767;
    } else {
        unsigned size = unsigned(psize);
        char *name = find_best_font(this, name_, size);
        // okay, make the font:
        f = new Fl_FontSize(name);
        const char *enc = font_word(name, 13);
        if(enc && *enc++) {
            f->encoding_num = fl_encoding_number(enc);
        }
        f->minsize = size;
        f->maxsize = size;
    }

    if(f->encoding_num==-1)
        f->encoding_num = 1; //ISO8859-1

    f->encoding = fl_encoding_;

    f->next = first;
    first = f;
    return f;
}

void Fl_Device::font(Fl_Font font, float psize)
{
    Fl_FontSize* f = fl_fontsize;

    // only integers supported right now (this can be improved):
    psize = int(psize+.5);
    unsigned size = unsigned(psize);

    // See if the current font is correct:
    if(font == fl_font_ && psize == fl_size_ &&
       (f->encoding==fl_encoding_ || !strcmp(f->encoding, fl_encoding_)))
        return;

    fl_font_ = font;
    fl_size_ = psize;

    // search the FontSize we have generated already:
    for(f = font->first; f; f = f->next) {
        if (f->minsize <= size && f->maxsize >= size
            && (f->encoding==fl_encoding_ ||
                !f->encoding || !strcmp(f->encoding, fl_encoding_)))
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
void Fl_Device::encoding(const char* f) {
    fl_encoding_ = f;
}

////////////////////////////////////////////////////////////////

// The predefined fonts that fltk has:  bold:       italic:
Fl_Font_ fl_fonts[] = {
{"-*-helvetica-medium-r-normal--*",	fl_fonts+1, fl_fonts+2,0},
{"-*-helvetica-bold-r-normal--*", 	fl_fonts+1, fl_fonts+3,0},
{"-*-helvetica-medium-o-normal--*",	fl_fonts+3, fl_fonts+2,0},
{"-*-helvetica-bold-o-normal--*",	fl_fonts+3, fl_fonts+3,0},
{"-*-courier-medium-r-normal--*",	fl_fonts+5, fl_fonts+6,0},
{"-*-courier-bold-r-normal--*",		fl_fonts+5, fl_fonts+7,0},
{"-*-courier-medium-o-normal--*",	fl_fonts+7, fl_fonts+6,0},
{"-*-courier-bold-o-normal--*",		fl_fonts+7, fl_fonts+7,0},
{"-*-times-medium-r-normal--*",		fl_fonts+9, fl_fonts+10,0},
{"-*-times-bold-r-normal--*",		fl_fonts+9, fl_fonts+11,0},
{"-*-times-medium-i-normal--*",		fl_fonts+11,fl_fonts+10,0},
{"-*-times-bold-i-normal--*",		fl_fonts+11,fl_fonts+11,0},
{"-*-symbol-*",				fl_fonts+12,fl_fonts+12,0},
{"-*-lucidatypewriter-medium-r-normal-sans-*", fl_fonts+14,fl_fonts+14,0},
{"-*-lucidatypewriter-bold-r-normal-sans-*", fl_fonts+14,fl_fonts+14,0},
{"-*-*zapf dingbats-*",			fl_fonts+15,fl_fonts+15,0}
};

//
// End of "$Id$"
//
