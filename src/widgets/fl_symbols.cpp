//
// "$Id$"
//
// Symbol drawing code for the Fast Light Tool Kit (FLTK).
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

// These are small graphics drawn by the normal label-drawing
// code when the string starts with an '@' sign.

// Adapted from original code written by:

// Written by Mark Overmars
// Version 2.1 a
// Date: Oct  2, 1992

#include <efltk/Fl_Style.h>
#include <efltk/fl_draw.h>
#include <string.h>

typedef struct
{
    const char *name;
    void (*drawit)(Fl_Color);
    char scalable;
    char notempty;
} SYMBOL;

#define MAXSYMBOL       211
/* Maximal number of symbols in table. Only half of them are
   used. Should be prime. */

static SYMBOL symbols[MAXSYMBOL];/* The symbols */
static int symbnumb = -1;        /* Their number */

static int find(const char *name)
{
    // returns hash entry if it exists, or first empty slot:
    int pos = name[0] ? (
        name[1] ? (
        name[2] ? 71*name[0]+31*name[1]+name[2] : 31*name[0]+name[1]
        ) :
    name[0]
        ) : 0;
    pos %= MAXSYMBOL;
    int hh2 = name[0] ? (
        (name[1]) ? 51*name[0]+3*name[1] : 3*name[0]
        ) : 1;
    hh2 %= MAXSYMBOL; if (!hh2) hh2 = 1;
    for (;;)
    {
        if (!symbols[pos].notempty) return pos;
        if (!strcmp(symbols[pos].name,name)) return pos;
        pos = (pos + hh2) % MAXSYMBOL;
    }
}


static void fl_init_symbols(void);

/**************** The routines seen by the user *************************/

int fl_add_symbol(const char *name, void (*drawit)(Fl_Color), int scalable)
/* Adds a symbol to the system. Returns whether correct. */
{
    fl_init_symbols();
    int pos;
                                 // table is full
    if (symbnumb > MAXSYMBOL / 2) return 0;
    pos = find(name);
    symbols[pos].name = name;
    symbols[pos].drawit = drawit;
    symbols[pos].notempty = 1;
    symbols[pos].scalable = scalable;
    symbnumb++;
    return 1;
}


// this function is in Fl_Return_Button.cxx:
void fl_glyph_return(const Fl_Widget*, int,
int x,int y,int w,int h, Fl_Flags);

// provided for back compatability:
int fl_draw_symbol(const char *label,int x,int y,int w,int h,Fl_Color col)
{
    const char *p = label;
    if (*p++ != '@') return 0;
    fl_init_symbols();
    bool equalscale = false;
    if (*p == '#')
    {
        equalscale = true;
        p++;
    }
    else
    {
        // if it is nearly square, make it square:
        if (w < h) {if (w*3 > h*2) equalscale = true;}
        else {if (h*3 > w*2) equalscale = true;}
    }
    if (*p == '-' && p[1]>='1' && p[1]<='9')
    {
        int n = p[1]-'0';
        x += n; y += n; w -= 2*n; h -= 2*n;
        p += 2;
    }
    else if (*p == '+' && p[1]>='1' && p[1]<='9')
    {
        int n = p[1]-'0';
        x -= n; y -= n; w += 2*n; h += 2*n;
        p += 2;
    }
    if (w < 10) {x -= (10-w)/2; w = 10;}
    if (h < 10) {y -= (10-h)/2; h = 10;}
    w = (w-1)|1; h = (h-1)|1;    // odd sizes so arrow points are centered
    int rotangle;
    switch (*p++)
    {
        case '0':
            rotangle = 1000*(p[1]-'0') + 100*(p[2]-'0') + 10*(p[3]-'0');
            p += 4;
            break;
        case '1': rotangle = 2250; break;
        case '2': rotangle = 2700; break;
        case '3': rotangle = 3150; break;
        case '4': rotangle = 1800; break;
        case '5':
        case '6': rotangle = 0; break;
        case '7': rotangle = 1350; break;
        case '8': rotangle =  900; break;
        case '9': rotangle =  450; break;
        default: rotangle = 0; p--; break;
    }
    int pos = find(p);
    if (!symbols[pos].notempty) return 0;
                                 // kludge to detect return arrow
    if (symbols[pos].scalable == 3)
    {
        fl_glyph_return(0,0, x,y,w,h, 0);
        return 1;
    }
    fl_push_matrix();
    fl_translate(x+w/2,y+h/2);
    if (symbols[pos].scalable)
    {
        if (equalscale) {if (w<h) h = w; else w = h;}
        fl_scale(0.5*w, 0.5*h);
        fl_rotate(rotangle/10.0);
    }
    (symbols[pos].drawit)(col);
    fl_pop_matrix();
    return 1;
}


/******************** THE DEFAULT SYMBOLS ****************************/

/* Some help stuff */

#define BP
#define EP fl_fill()
#define BL
#define EL fl_stroke()
#define BC
#define EC fl_closepath(); fl_color(FL_BLACK); fl_stroke()
#define EF(c) fl_fill_stroke(FL_BLACK)
#define vv(x,y) fl_vertex(x,y)

static void rectangle(float x,float y,float x2,float y2,Fl_Color col)
{
    fl_color(col);
    BP; vv(x,y); vv(x2,y); vv(x2,y2); vv(x,y2); EF(col);
}


/* The drawing routines */

static void draw_arrow1(Fl_Color col)
{
    fl_color(col);
    BP; vv(-0.8f,-0.4f); vv(-0.8f,0.4f); vv(0.0f,0.4f); vv(0.0f,-0.4f); EP;
    BP; vv(0.0f,0.8f); vv(0.8f,0.0f); vv(0.0f,-0.8f); vv(0.0f,-0.4f); vv(0.0f,0.4f); EP;
    BC; vv(-0.8f,-0.4f); vv(-0.8f,0.4f); vv(0.0f,0.4f); vv(0.0f,0.8f); vv(0.8f,0.0f);
    vv(0.0f,-0.8f); vv(0.0f,-0.4f); EC;
}

static void draw_arrow2(Fl_Color col)
{
    fl_color(col);
    BP; vv(-0.3f,0.8f); vv(0.50f,0.0f); vv(-0.3f,-0.8f); EF(col);
}

static void draw_arrow3(Fl_Color col)
{
    fl_color(col);
    BP; vv(0.1f,0.8f); vv(0.9f,0.0f); vv(0.1f,-0.8f); EF(col);
    BP; vv(-0.7f,0.8f); vv(0.1f,0.0f); vv(-0.7f,-0.8f); EF(col);
}

static void draw_arrowbar(Fl_Color col)
{
    fl_color(col);
    BP; vv(0.2f,0.8f); vv(0.6f,0.8f); vv(0.6f,-0.8f); vv(0.2f,-0.8f); EF(col);
    BP; vv(-0.6f,0.8f); vv(0.2f,0.0f); vv(-0.6f,-0.8f); EF(col);
}

static void draw_arrowbox(Fl_Color col)
{
    fl_color(col);
    BP; vv(-0.6f,0.8f); vv(0.2f,0.0f); vv(-0.6f,-0.8f); EF(col);
    BC; vv(0.2f,0.8f); vv(0.6f,0.8f); vv(0.6f,-0.8f); vv(0.2f,-0.8f); EC;
}

static void draw_bararrow(Fl_Color col)
{
    fl_color(col);
    BP; vv(0.1f,0.8f); vv(0.9f,0.0f); vv(0.1f,-0.8f); EF(col);
    BP; vv(-0.5f,0.8f); vv(-0.1f,0.8f); vv(-0.1f,-0.8f); vv(-0.5f,-0.8f); EF(col);
}

static void draw_doublebar(Fl_Color col)
{
    rectangle(-0.6f,-0.8f,-.1f,.8f,col);
    rectangle(.1f,-0.8f,.6f,.8f,col);
}

static void draw_arrow01(Fl_Color col)
{ fl_rotate(180); draw_arrow1(col); }

static void draw_arrow02(Fl_Color col)
{ fl_rotate(180); draw_arrow2(col); }

static void draw_arrow03(Fl_Color col)
{ fl_rotate(180); draw_arrow3(col); }

static void draw_0arrowbar(Fl_Color col)
{ fl_rotate(180); draw_arrowbar(col); }

static void draw_0arrowbox(Fl_Color col)
{ fl_rotate(180); draw_arrowbox(col); }

static void draw_0bararrow(Fl_Color col)
{ fl_rotate(180); draw_bararrow(col); }

static void draw_square(Fl_Color col)
{ rectangle(-1,-1,1,1,col); }

static void draw_uparrow(Fl_Color)
{
    fl_color(FL_LIGHT3);
    BL; vv(-.8f,.8f); vv(-.8f,-.8f); vv(.8f,0.0f); EL;
    fl_color(FL_DARK3);
    BL; vv(-.8f,.8f); vv(.8f, 0.0f); EL;
}

static void draw_downarrow(Fl_Color)
{
    fl_color(FL_DARK3);
    BL; vv(-.8f,.8f); vv(-.8f,-.8f); vv(.8f,0.0f); EL;
    fl_color(FL_LIGHT3);
    BL; vv(-.8f,.8f); vv(.8f, 0.0f); EL;
}

static void draw_arrow1bar(Fl_Color col)
{
    draw_arrow1(col);
    rectangle(.6f,-.8f,.9f,.8f, col);
}

static void draw_doublearrow(Fl_Color col)
{
  fl_color(col);
  BP; vv(-0.35f,-0.4f); vv(-0.35f,0.4f); vv(0.35f,0.4f); vv(0.35f,-0.4f); EP;
  BP; vv(0.15f,0.8f); vv(0.95f,0.0f); vv(0.15f,-0.8f); EP;
  BP; vv(-0.15f,0.8f); vv(-0.95f,0.0f); vv(-0.15f,-0.8f); EP;

  BC; vv(-0.15f,0.4f); vv(0.15f,0.4f); vv(0.15f,0.8f); vv(0.95f,0.0f);
  vv(0.15f,-0.8f); vv(0.15f,-0.4f); vv(-0.15f,-0.4f); vv(-0.15f,-0.8f);
  vv(-0.95f,0.0f); vv(-0.15f,0.8f); EC;
}

static void draw_arrow(Fl_Color col)
{
    fl_color(col);
    BP; vv(0.65f,0.1f); vv(1.0f,0.0f); vv(0.65f,-0.1f); EF(col);
    BL; vv(-1.0f,0.0f); vv(0.65f,0.0f); EL;
}

static void draw_circle(Fl_Color col)
{
    fl_color(col); BP; fl_ellipse(-1,-1,2,2); EF(col);
}

static void draw_line(Fl_Color col)
{
    fl_color(col); BL; vv(-1.0f,0.0f); vv(1.0f,0.0f); EL;
}

static void draw_plus(Fl_Color col)
{
    fl_color(col);
    BP; vv(-0.9f,-0.15f); vv(-0.9f,0.15f); vv(0.9f,0.15f); vv(0.9f,-0.15f); EP;
    BP; vv(-0.15f,-0.9f); vv(-0.15f,0.9f); vv(0.15f,0.9f); vv(0.15f,-0.9f); EP;

    BC;
    vv(-0.9f,-0.15f); vv(-0.9f,0.15f); vv(-0.15f,0.15f); vv(-0.15f,0.9f);
    vv(0.15f,0.9f); vv(0.15f,0.15f); vv(0.9f,0.15f); vv(0.9f,-0.15f);
    vv(0.15f,-0.15f); vv(0.15f,-0.9f); vv(-0.15f,-0.9f); vv(-0.15f,-0.15f);
    EC;
}

static void draw_menu(Fl_Color col)
{
    rectangle(-0.65f, 0.85f, 0.65f, -0.25f, col);
    rectangle(-0.65f, -0.6f, 0.65f, -1.0f, col);
}

static void fl_init_symbols(void)
{
    static char beenhere;
    if (beenhere) return;
    beenhere = 1;
    symbnumb = 0;

    fl_add_symbol("",     draw_arrow1,        1);
    fl_add_symbol("->",       draw_arrow1,        1);
    fl_add_symbol(">",        draw_arrow2,        1);
    fl_add_symbol(">>",       draw_arrow3,        1);
    fl_add_symbol(">|",       draw_arrowbar,      1);
    fl_add_symbol(">[]",      draw_arrowbox,      1);
    fl_add_symbol("|>",       draw_bararrow,      1);
    fl_add_symbol("<-",       draw_arrow01,       1);
    fl_add_symbol("<",        draw_arrow02,       1);
    fl_add_symbol("<<",       draw_arrow03,       1);
    fl_add_symbol("|<",       draw_0arrowbar,     1);
    fl_add_symbol("[]<",      draw_0arrowbox,     1);
    fl_add_symbol("<|",       draw_0bararrow,     1);
    fl_add_symbol("<->",      draw_doublearrow,   1);
    fl_add_symbol("-->",      draw_arrow,     1);
    fl_add_symbol("+",        draw_plus,      1);
    fl_add_symbol("->|",      draw_arrow1bar,     1);
    fl_add_symbol("arrow",    draw_arrow,     1);
    fl_add_symbol("returnarrow",  0,          3);
    fl_add_symbol("square",   draw_square,        1);
    fl_add_symbol("circle",   draw_circle,        1);
    fl_add_symbol("line",     draw_line,      1);
    fl_add_symbol("plus",     draw_plus,      1);
    fl_add_symbol("menu",     draw_menu,      1);
    fl_add_symbol("UpArrow",  draw_uparrow,       1);
    fl_add_symbol("DnArrow",  draw_downarrow,     1);
    fl_add_symbol("||",       draw_doublebar,     1);
}


////////////////////////////////////////////////////////////////

#include <efltk/Fl_Labeltype.h>

void Fl_Symbol_Label::draw(const char* label,
int X, int Y, int W, int H,
Fl_Color fill, Fl_Flags align) const
{
    fill = fl_inactive(fill, align);
    int x1 = X;
    int y1 = Y;
    int w1 = W;
    int h1 = H;
    if (align & 15)
    {
        if (w1 < h1) h1 = w1; else w1 = h1;
        if (align & FL_ALIGN_LEFT) ;
        else if (align & FL_ALIGN_RIGHT) x1 = X+W-w1;
        else x1 = X+((W-w1)>>1);
        if (align & FL_ALIGN_TOP) ;
        else if (align & FL_ALIGN_BOTTOM) y1 = Y+H-h1;
        else y1 = Y+((H-h1)>>1);
    }
    if (!fl_draw_symbol(label, x1, y1, w1, h1, fill))
    {
        fl_color(fill);
        fl_draw(label, X, Y, W, H, align);
    }
}


const Fl_Symbol_Label fl_symbol_label("symbol");

#include <efltk/Fl.h>
#include <efltk/Fl_Widget.h>

#ifndef FLTK_2
void Fl::enable_symbols()
{
    Fl_Widget::default_style->label_type = FL_SYMBOL_LABEL;
}
#endif

//
// End of "$Id$".
//
