//
// "$Id$"
//
// Copyright 2001 Bill Spitzak and others.
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

// Draw fonts using Keith Packard's Xft and Xrender extension. Yow!
// Many thanks to Carl for making the original version of this.
//
// This code is included in efltk if it is compiled with -DUSE_XFT=1
// It should also be possible to compile this file as a seperate
// shared library, and by using LD_PRELOAD you can insert it between
// any efltk program and the efltk shared library.
//
// This plugin only requires libXft to work. Contrary to popular
// belief there is no need to have freetype, or the Xrender extension
// available to use this code. You will just get normal Xlib fonts
// (Xft calls them "core" fonts) The Xft algorithims for choosing
// these is about as good as the efltk ones (I hope to fix it so it is
// exactly as good...), plus it can cache it's results and share them
// between programs, so using this should be a win in all cases. Also
// it should be obvious by comparing this file and fl_font_x.cxx that
// it is a lot easier to program to Xft than to Xlib.
//
// To actually get antialiasing you need the following:
//
// 1. You have XFree86 4
// 2. You have the XRender extension
// 3. Your X device driver supports the render extension
// 4. You have libXft
// 5. Your libXft has freetype2 support compiled in
// 6. You have the freetype2 library
//
// Distributions that have XFree86 4.0.3 or later should have all of this...
//
// Unlike some other Xft packages, I tried to keep this simple and not
// to work around the current problems in Xft by making the "patterns"
// complicated. I belive doing this defeats our ability to improve Xft
// itself. You should edit the ~/.xftconfig file to "fix" things, there
// are several web pages of information on how to do this.

#include <efltk/Fl.h>
#include <efltk/Fl_Ptr_List.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl_Font.h>
#include <efltk/fl_draw.h>
#include <efltk/fl_utf8.h>
#include <efltk/x.h>

#include <X11/Xft/Xft.h>

// define some symbols missing from some Xft header files:
#ifndef XFT_MINSPACE
#define XFT_MINSPACE        "minspace"  /* Bool use minimum line spacing */
#endif
#ifndef XFT_MATRIX
#define XFT_MATRIX          "matrix"    /* XftMatrix */
typedef struct _XftMatrix {
    double xx, xy, yx, yy;
} XftMatrix;
#endif                                                        
#include <string.h>
#include <stdlib.h>

class Fl_FontSize {
public:
    Fl_FontSize *next;	   // linked list for this Fl_Fontdesc

    XftFont     *font;
    XFontStruct *core_font;

    float size;
    const char* encoding;

    Fl_FontSize(const char* xfontname);
    ~Fl_FontSize();
};

static Fl_FontSize *fl_fontsize;

#define current_font (fl_fontsize->font)

// Change the encoding to use for the next font selection.
void Fl_Device::encoding(const char* f) {
    fl_encoding_ = f;
}

void Fl_Device::font(Fl_Font font, float size)
{
    // Reduce the number of sizes by rounding to various multiples:
    size = rint(10*size)/10;

    if (font == fl_font_ && size == fl_size_ &&
        !strcasecmp(fl_fontsize->encoding, fl_encoding_))
        return;

    fl_font_ = font;
    fl_size_ = size;

    Fl_FontSize* f;
    // search the fontsizes we have generated already
    for (f = font->first; f; f = f->next) {
        if (f->size == size && !strcasecmp(f->encoding, fl_encoding_))
            break;
    }
    if (!f) {
        f = new Fl_FontSize(font->name_);
        f->next = font->first;
        ((Fl_Font_*)font)->first = f;
    }
    fl_fontsize = f;
}

static XftFont* fontopen(const char* name, bool core)
{
    fl_open_display();

    int slant = XFT_SLANT_ROMAN;
    int weight = XFT_WEIGHT_MEDIUM;
    // may be efficient, but this is non-obvious
    switch (*name++) {
    case 'I': slant  = XFT_SLANT_ITALIC; break;
    case 'P': slant  = XFT_SLANT_ITALIC;
    case 'B': weight = XFT_WEIGHT_BOLD; break;
    case ' ': break;
    default: name--;
    }

    // this call is extremely slow...
    return XftFontOpen(fl_display, fl_screen,
                       XFT_FAMILY, XftTypeString, name,
                       XFT_WEIGHT, XftTypeInteger, weight,
                       XFT_SLANT, XftTypeInteger, slant,
                       XFT_ENCODING, XftTypeString, fl_encoding_, // hmmm?
                       XFT_PIXEL_SIZE, XftTypeDouble, (double)fl_size_,
                       core ? XFT_CORE : 0, XftTypeBool, false,
                       XFT_ANTIALIAS, XftTypeBool, (fl_size_<12)?false:true,
                       //XFT_RENDER, XftTypeBool, false,
                       0);
}

Fl_FontSize::Fl_FontSize(const char* name)
{
    encoding = fl_encoding_;
    size = fl_size_;
    font = fontopen(name, true);
    core_font = 0;

    append_font(this);
}

Fl_FontSize::~Fl_FontSize() {
    if (this == fl_fontsize) fl_fontsize = 0;
    XftFontClose(fl_display, font);
    if(core_font)
        XFreeFont(fl_display, core_font);
}

XftFont* fl_xftfont()
{
    return current_font;
}

Fl_String get_xft_val(const char *t)
{
    XftValue val;
    if(XftPatternGet(current_font->pattern, t, 0, &val) == FcResultMatch)
    {
        switch(val.type) {
        case FcTypeInteger:
            return Fl_String(val.u.i);
        case FcTypeDouble:
            return Fl_String((int)val.u.d);
        case FcTypeString:
            return Fl_String((const char*)val.u.s);
        default:
            break;
        }
    }
    return "-";
}


// This call is used by opengl to get a bitmapped font. Xft actually does
// a pretty good job of selecting X fonts...
XFontStruct* fl_xfont()
{
    if(fl_fontsize->core_font) return fl_fontsize->core_font;

    Fl_String xlfd;
    xlfd += "-*-";
    xlfd += get_xft_val(XFT_FAMILY); //FamilyName
    xlfd += "-medium-";
    xlfd += "r-";
    xlfd += "normal-";
    xlfd += "*-";
    xlfd += Fl_String((int)fl_size_);
    xlfd += "-120-0-0-p-0-";
    xlfd += fl_encoding();

    //printf("XLFD (%s)\n", xlfd.c_str());
    fl_fontsize->core_font = XLoadQueryFont(fl_display, xlfd.c_str());

    if(!fl_fontsize->core_font) {
        static XFontStruct *fail_save=0;
        if(!fail_save) fail_save = XLoadQueryFont(fl_display, "variable");
        fl_fontsize->core_font = fail_save;
    }

    return fl_fontsize->core_font;
}

#if 1
// Some of the line spacings these return are insanely big!
//int fl_height() { return current_font->height; }
float Fl_Device::height() const { return current_font->ascent + current_font->descent; }
float Fl_Device::descent() const { return current_font->descent; }
#else
float Fl_Device::height() { return fl_size_;}
float Fl_Device::descent() { return fl_size_/4;}
#endif

float Fl_Device::width(const char *str, int n) const
{
    XGlyphInfo i;
#if HAVE_XUTF8
    XftChar16 buf[128];  // measure buffer
    int pos = 0;         // position in buffer
    int ulen;           // byte length of the UTF-8 char
    unsigned int ucs;    // Unicode value of the UTF-8 char
    unsigned int no_spc; // Spacing char equivalent of a non-spacing char
    float W=0;

    while(n > 0) {
        if(pos>120) {
            XftTextExtents16(fl_display, current_font, buf, pos, &i);
            W += i.xOff;
            pos = 0;
        }

        ulen = fl_fast_utf2ucs((unsigned char*)str, n, &ucs);
        if (ulen < 1) ulen = 1;
        no_spc = fl_nonspacing(ucs);
        if(no_spc) ucs = no_spc;

        if(!XftGlyphExists(fl_display, current_font, ucs)) {
            ucs = '?';
        }

        if(no_spc) {
            XftTextExtents16(fl_display, current_font, buf, pos, &i);
            W += i.xOff;
            pos = 0;
            *buf = (XftChar16)ucs;
            XftTextExtents16(fl_display, current_font, buf, 1, &i);
            W -= i.xOff;
        } else {
            *(buf+pos) = (XftChar16)ucs;
        }
        pos++;
        str += ulen;
        n-=ulen;
    }
    if(pos>0) {
        XftTextExtents16(fl_display, current_font, buf, pos, &i);
        W += i.xOff;
    }
    return W;
#else
    XftTextExtents8(fl_display, current_font, (XftChar8 *)str, n, &i);
#endif
    return i.xOff;
}

float Fl_Device::width(unsigned int c) const
{
#if HAVE_XUTF8
    unsigned int ucs;
    unsigned int ulen = fl_fast_utf2ucs((unsigned char*)&c, 1, &ucs);
    if (ulen < 1) ulen = 1;
    unsigned int no_spc = fl_nonspacing(ucs);
    if(no_spc) ucs = no_spc;

    if(!XftGlyphExists(fl_display, current_font, ucs)) {
        ucs = '?';
    }

    XGlyphInfo i;
    XftChar16 buf[2];
    buf[0] = (XftChar16)ucs;
    buf[1] = 0;
    XftTextExtents16(fl_display, current_font, buf, 1, &i);
    return i.xOff;
#else
    char ch[2] = { char(c), 0 };
    return width(ch, 1);
#endif
}

////////////////////////////////////////////////////////////////

#if USE_OVERLAY
// Currently Xft does not work with colormapped visuals, so this probably
// does not work unless you have a true-color overlay.
extern bool fl_overlay;
extern Colormap fl_overlay_colormap;
extern XVisualInfo* fl_overlay_visual;
#endif

extern int fl_clip_state_number;
static int clip_state_number = 0; // which clip we did last
static XftDraw* clipped_draw = 0;  // the XftDraw we did it to

void Fl_Device::transformed_draw(const char *str, int n, float x, float y)
{
    XftDraw* draw = fl_drawable->draw;

    if (!draw) {
#if USE_OVERLAY
        if (fl_overlay)
            draw = XftDrawCreate(fl_display, fl_drawable->xid, fl_overlay_visual->visual, fl_overlay_colormap);
        else
#endif
            draw = XftDrawCreate(fl_display, fl_drawable->xid, fl_visual->visual, fl_colormap);

        Region region = fl_clip_region();
        if (region) XftDrawSetClip(draw, region);
        clip_state_number = fl_clip_state_number;
        clipped_draw = fl_drawable->draw = draw;
    }
    else if (clip_state_number!=fl_clip_state_number || draw!=clipped_draw) {
        clip_state_number = fl_clip_state_number;
        clipped_draw = draw;
        XftDrawSetClip(draw, fl_clip_region());
    }

    // Use efltk's color allocator, copy the results to match what
    // XftCollorAllocValue returns:
    static Fl_Color flcolor;
    static XftColor color;
    if(flcolor != fl_color_) {
        color.pixel = fl_pixel;
        uchar r,g,b; fl_get_color(fl_color_, r,g,b);
        color.color.red   = r*0x101;
        color.color.green = g*0x101;
        color.color.blue  = b*0x101;
        color.color.alpha = 0xffff;
        flcolor = fl_color_;
    }

    int X = int(floor(x+.5f));
    int Y = int(floor(y+.5f));

#if HAVE_XUTF8
    XGlyphInfo i;
    XftChar16 buf[256];  // draw buffer
    int pos = 0;         // position in buffer
    int ulen;            // byte length of the UTF-8 char
    unsigned int ucs;    // Unicode value of the UTF-8 char
    unsigned int no_spc; // Spacing char equivalent of a non-spacing char

    while(n > 0) {

        if(pos>250) {
            XftDrawString16(draw, &color, current_font, X, Y, buf, pos);
            XftTextExtents16(fl_display, current_font, buf, pos, &i);
            X += i.xOff;
            pos = 0;
        }

        ulen = fl_fast_utf2ucs((unsigned char*)str, n, &ucs);
        if (ulen < 1) ulen = 1;
        no_spc = fl_nonspacing(ucs);
        if(no_spc) ucs = no_spc;

        if(!XftGlyphExists(fl_display, current_font, ucs)) {
            ucs = '?';
        }

        if(no_spc) {
            XftDrawString16(draw, &color, current_font, X, Y, buf, pos);
            XftTextExtents16(fl_display, current_font, buf, pos, &i);
            X += i.xOff;
            pos = 0;

            *buf = (XftChar16)ucs;
            XftTextExtents16(fl_display, current_font, buf, 1, &i);
            X -= i.xOff;
        } else {
            *(buf+pos) = (XftChar32)ucs;
        }

        pos++;
        str += ulen;
        n-=ulen;
    }
    if(pos>0)
        XftDrawString16(draw, &color, current_font, X, Y, buf, pos);
#else
    XftDrawString8(draw, &color, current_font, X, Y, (XftChar8 *)str, n);
#endif
}

void Fl_Device::rtl_draw(const char *str, int n, float x, float y) 
{
    transformed_draw(str, n, x, y);
}

void Fl_Drawable::free_gc()
{
    if (draw) {
        XftDrawDestroy(draw);
        draw = 0;
        clipped_draw = 0;
    }
}

Fl_Font fl_create_font(const char *system_name)                                 
{                                                                               
    Fl_Font_ *f = new Fl_Font_;
    f->name_ = strdup(system_name);
    //f->name_ = system_name;
    f->bold_ = f;
    f->italic_ = f;
    f->xlist_ = 0;
    f->first = 0;
    return f;
}

////////////////////////////////////////////////////////////////

// The predefined fonts that efltk has:  bold:       italic:
Fl_Font_
fl_fonts[] = {
{" helvetica",		fl_fonts+1, fl_fonts+2},
{"Bhelvetica",		fl_fonts+1, fl_fonts+3},
{"Ihelvetica",		fl_fonts+3, fl_fonts+2},
{"Phelvetica",		fl_fonts+3, fl_fonts+3},
{" courier",		fl_fonts+5, fl_fonts+6},
{"Bcourier",		fl_fonts+5, fl_fonts+7},
{"Icourier",		fl_fonts+7, fl_fonts+6},
{"Pcourier",		fl_fonts+7, fl_fonts+7},
{" times",		fl_fonts+9, fl_fonts+10},
{"Btimes",		fl_fonts+9, fl_fonts+11},
{"Itimes",		fl_fonts+11,fl_fonts+10},
{"Ptimes",		fl_fonts+11,fl_fonts+11},
{" symbol",		fl_fonts+12,fl_fonts+12},
{" mono",		fl_fonts+14,fl_fonts+14},
{"Bmono",		fl_fonts+14,fl_fonts+14},
{" dingbats",		fl_fonts+15,fl_fonts+15},
};

////////////////////////////////////////////////////////////////
// The rest of this is for listing fonts:

// turn a stored font name into a pretty name:
const char* Fl_Font_::name(int* ap) const
{
    int type;
    switch (name_[0]) {
    case 'B': type = FL_BOLD; break;
    case 'I': type = FL_ITALIC; break;
    case 'P': type = FL_BOLD | FL_ITALIC; break;
    default:  type = 0; break;
    }
    if (ap) { *ap = type; return name_+1; }
    if (!type) { return name_+1; }

    static char buffer[128];
    strcpy(buffer, name_+1);
    if (type & FL_BOLD) strcat(buffer, _(" bold"));
    if (type & FL_ITALIC) strcat(buffer, _(" italic"));
    return buffer;
}

extern "C" {
    static int sort_function(const void *aa, const void *bb) {
        const char* name_a = (*(Fl_Font_**)aa)->name_;
        const char* name_b = (*(Fl_Font_**)bb)->name_;
        int ret = strcasecmp(name_a+1, name_b+1); if (ret) return ret;
        return name_a[0]-name_b[0]; // sort by attribute
    }
}

static Fl_Font_* make_a_font(char attrib, const char* name)
{
    Fl_Font_* newfont = new Fl_Font_;
    char *n = new char[strlen(name)+2];
    n[0] = attrib;
    strcpy(n+1, name);
    newfont->name_ = n;
    newfont->bold_ = newfont;
    newfont->italic_ = newfont;
    newfont->first = 0;
    return newfont;
}

int fl_list_fonts(Fl_Font*& arrayp)
{
    static Fl_Font *font_array = 0;
    static int num_fonts = 0;

    if (font_array) { arrayp = font_array; return num_fonts; }

    fl_open_display();

    XftFontSet *fs = XftListFonts(fl_display, fl_screen, 0, XFT_FAMILY, 0);
    int nfonts = fs->nfont;
    font_array = (Fl_Font *)malloc(nfonts * sizeof(Fl_Font *));

    char *name;
    for (int i = 0; i < nfonts; i++) {
        if (XftPatternGetString(fs->fonts[i], XFT_FAMILY, 0, &name) == XftResultMatch) {
            Fl_Font_* base = make_a_font(' ', name);
            base->italic_ = make_a_font('I', name);
            //if (bNeedBold) {
            base->bold_ = make_a_font('B', name);
            base->italic_->bold_ = base->bold_->italic_ = make_a_font('P', name);
            //}
            font_array[num_fonts++] = base;
        }
    }

    qsort(font_array, num_fonts, sizeof(Fl_Font), sort_function);
    XftFontSetDestroy(fs);

    arrayp = font_array;
    return num_fonts;
}

extern "C" {
    static int int_sort(const void *aa, const void *bb) {
        return (*(int*)aa)-(*(int*)bb);
    }
}

////////////////////////////////////////////////////////////////

// Return all the point sizes supported by this font:
// Suprisingly enough Xft works exactly like efltk does and returns
// the same list. Except there is no way to tell if the font is scalable.
int Fl_Font_::sizes(int*& sizep) const
{
    fl_open_display();
    XftFontSet* fs = XftListFonts(fl_display, fl_screen,
                                  XFT_FAMILY, XftTypeString, name_+1, 0,
                                  XFT_PIXEL_SIZE, 0);
    static int* array = 0;
    static int array_size = 0;
    if (fs->nfont >= array_size) {
        delete[] array;
        array = new int[array_size = fs->nfont+1];
    }
    array[0] = 0; int j = 1; // claim all fonts are scalable by putting a 0 in
    for (int i = 0; i < fs->nfont; i++) {
        double v;
        if (XftPatternGetDouble(fs->fonts[i], XFT_PIXEL_SIZE, 0, &v)
            == XftResultMatch)
            array[j++] = int(v);
    }

    qsort(array+1, j-1, sizeof(int), int_sort);
    XftFontSetDestroy(fs);

    sizep = array;
    return j;
}

////////////////////////////////////////////////////////////////
// Return all the encodings for this font:

int Fl_Font_::encodings(const char**& arrayp) const
{
    fl_open_display();
    // we need to keep the previous return value around so the strings are
    // not destroyed.
    static XftFontSet *fs=0;
    if (fs) XftFontSetDestroy(fs);
    fs = XftListFonts(fl_display, fl_screen,
                      XFT_FAMILY, XftTypeString, name_+1, 0,
                      XFT_ENCODING, 0);

    static const char** array = 0;
    static int array_size = 0;
    if (fs->nfont > array_size) {
        array_size = fs->nfont;
        free(array);
        array = (const char**)malloc(array_size*sizeof(const char*));
    }

    int j = 0;
    for (int i = 0; i < fs->nfont; i++) {
        char *v;
        if (XftPatternGetString(fs->fonts[i], XFT_ENCODING, 0, &v) == XftResultMatch) {
            array[j++] = v;
        }
    }
    arrayp = array;
    return j;
}

//
// End of "$Id$"
//
