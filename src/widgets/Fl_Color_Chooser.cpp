//
// "$Id$"
//
// Color chooser for the Fast Light Tool Kit (FLTK).
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

#include <efltk/fl_math.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Color_Chooser.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Image.h>

//#include <stdio.h>

// For NLS stuff
#include "../core/fl_internal.h"

// Besides being a useful object on it's own, the Fl_Color_Chooser was
// an attempt to make a complex composite object that could be easily
// imbedded into a user interface.  If you wish to make complex objects
// of your own, be sure to read this code.

// The function fl_color_chooser() creates a window containing a color
// chooser and a few buttons and current-color indicators.  It is an
// easier interface for simple programs that just need a color.

// The "hue box" can be a circle or rectilinear.
// You get a circle by defining this:
#define CIRCLE 1
// And the "hue box" can auto-update when the value changes
// you get this by defining this:
//#define UPDATE_HUE_BOX 1

void Fl_Color_Chooser::hsv2rgb(float H, float S, float V, float& r, float& g, float& b)
{
    if (S < 5.0e-6) {
        r = g = b = V;
    } else {
        int i = (int)H;  
        float f = H - (float)i;
        float p1 = V*(1.0f-S);
        float p2 = V*(1.0f-S*f);
        float p3 = V*(1.0f-S*(1.0f-f));
        switch (i) {
            case 0: r = V;   g = p3;  b = p1;  break;
            case 1: r = p2;  g = V;   b = p1;  break;
            case 2: r = p1;  g = V;   b = p3;  break;
            case 3: r = p1;  g = p2;  b = V;   break;
            case 4: r = p3;  g = p1;  b = V;   break;
            case 5: r = V;   g = p1;  b = p2;  break;
        }
    }
}

void Fl_Color_Chooser::rgb2hsv(float r, float g, float b, float& H, float& S, float& V)
{
    float maxv = r > g ? r : g; if (b > maxv) maxv = b;
    V = maxv;
    if (maxv>0) {
        float minv = r < g ? r : g; if (b < minv) minv = b;
        S = 1.0f - float(minv)/maxv;
        if (maxv > minv) {
            if (maxv == r) {H = (g-b)/float(maxv-minv); if (H<0) H += 6.0f;}
            else if (maxv == g) H = 2.0f+(b-r)/float(maxv-minv);
            else H = 4.0f+(r-g)/float(maxv-minv);
        }
    }
}

enum {M_RGB, M_BYTE, M_HEX, M_HSV}; // modes

int Flcc_Value_Input::format(char* buf) {
    Fl_Color_Chooser* c = (Fl_Color_Chooser*)parent()->parent();
    if (c->mode() == M_HEX) return sprintf(buf,"0x%02X", int(value()));
    else return Fl_Valuator::format(buf);
}

void Fl_Color_Chooser::set_valuators() {
    switch (mode()) {
        case M_RGB:
            rvalue.range(0,1); rvalue.step(.001); rvalue.value(r_);
            gvalue.range(0,1); gvalue.step(.001); gvalue.value(g_);
            bvalue.range(0,1); bvalue.step(.001); bvalue.value(b_);
            break;
        case M_BYTE:
        case M_HEX:
            rvalue.range(0,255); rvalue.step(1); rvalue.value(int(255*r_+.5f));
            gvalue.range(0,255); gvalue.step(1); gvalue.value(int(255*g_+.5f));
            bvalue.range(0,255); bvalue.step(1); bvalue.value(int(255*b_+.5f));
            break;
        case M_HSV:
            rvalue.range(0,6); rvalue.step(.001); rvalue.value(hue_);
            gvalue.range(0,1); gvalue.step(.001); gvalue.value(saturation_);
            bvalue.range(0,1); bvalue.step(.001); bvalue.value(value_);
            break;
    }
}

int Fl_Color_Chooser::rgb(float r, float g, float b)
{
    if (r == r_ && g == g_ && b == b_) return 0;
    r_ = r; g_ = g; b_ = b;
    float ph = hue_;
    float ps = saturation_;
    float pv = value_;
    rgb2hsv(r,g,b,hue_,saturation_,value_);
    set_valuators();
    if (value_ != pv) {
#ifdef UPDATE_HUE_BOX
        huebox.redraw(FL_DAMAGE_ALL);
#endif
        valuebox.redraw(FL_DAMAGE_VALUE);       
    }
    if (hue_ != ph || saturation_ != ps) {
        huebox.redraw(FL_DAMAGE_VALUE);
        valuebox.redraw(FL_DAMAGE_ALL);     
    }
    return 1;
}

int Fl_Color_Chooser::hsv(float h, float s, float v)
{
    h = fmod(h,6.0f); if (h < 0) h += 6.0f;
    if (s < 0) s = 0; else if (s > 1) s = 1;
    if (v < 0) v = 0; else if (v > 1) v = 1;
    if (h == hue_ && s == saturation_ && v == value_) return 0;
    float ph = hue_;
    float ps = saturation_;
    float pv = value_;
    hue_ = h; saturation_ = s; value_ = v;
    if (value_ != pv) {
#ifdef UPDATE_HUE_BOX
        huebox.redraw(FL_DAMAGE_ALL);
#endif
        valuebox.redraw(FL_DAMAGE_VALUE);
    }
    if (hue_ != ph || saturation_ != ps) {
        huebox.redraw(FL_DAMAGE_VALUE);
        valuebox.redraw(FL_DAMAGE_ALL);
    }
    hsv2rgb(h,s,v,r_,g_,b_);
    set_valuators();
    return 1;
}

////////////////////////////////////////////////////////////////

static void tohs(float x, float y, float& h, float& s) {
#ifdef CIRCLE
    x = 2*x-1;
    y = 1-2*y;
    s = sqrt(x*x+y*y); if (s > 1) s = 1;
    h = float(3.0/M_PI)*atan2(y,x);
    if (h<0) h += 6;
#else
    h = fmod(6*x,6.0f); if (h < 0) h += 6;
    s = 1-y; if (s < 0) s = 0; else if (s > 1) s = 1;
#endif
}

Flcc_HueBox::Flcc_HueBox(int X, int Y, int W, int H)
: Fl_Widget(X,Y,W,H)
{
    bg = 0;
    px = py = 0;
}

Flcc_HueBox::~Flcc_HueBox()
{
    if(bg) delete bg;
}

int Flcc_HueBox::handle(int e)
{
    static float is;
    Fl_Color_Chooser* c = (Fl_Color_Chooser*)parent();
    switch (e) {
        case FL_PUSH:
            is = c->saturation();
        case FL_DRAG: {
                float Xf, Yf, H, S;
                int ix = 0; int iy = 0; int iw = w(); int ih = h();
                box()->inset(ix, iy, iw, ih);
                Xf = (Fl::event_x()-ix)/float(iw);
                Yf = (Fl::event_y()-iy)/float(ih);
                tohs(Xf, Yf, H, S);
                if (fabs(H-ih) < 3*6.0f/w()) H = float(ih);
                if (fabs(S-is) < 3*1.0f/h()) S = is;
                if (Fl::event_state(FL_CTRL)) H = float(ih);
                if (c->hsv(H, S, c->v())) c->do_callback(FL_DATA_CHANGE);
            }
            return 1;

        default:
            return 0;
    }
}

void Flcc_HueBox::layout()
{
    if(layout_damage() & FL_LAYOUT_WH) {
        generate();
    }

    Fl_Widget::layout();
}

void Flcc_HueBox::generate()
{
    int X = 0, Y = 0, W = w(), H = h();
    box()->inset(X,Y,W,H);

#ifdef UPDATE_HUE_BOX
    const float V = ((Fl_Color_Chooser*)(parent()))->v();
#else
    const float V = 1.0f;
#endif

    Fl_Image *im = new Fl_Image(W, H, 32);

    uint32 *dst = (uint32 *)im->data();
    int skip = (im->pitch() - W * im->bytespp()) >> 2;
    register float r,g,b;

    for(int y = 0; y < H; y++) {

        float Yf = (float)y / H;

        for (int x = 0; x < W; x++)
        {
            float Xf = (float)x / W;
            float H,S; tohs(Xf, Yf, H, S);
            Fl_Color_Chooser::hsv2rgb(H,S,V,r,g,b);
            fl_rgb888_from_rgb(*dst++, uchar(255*r+.5f), uchar(255*g+.5f), uchar(255*b+.5f));
        }
        dst += skip;
    }

    if(bg) delete bg;
    bg = im;
}

#define BUTTON_SIZE 8
void Flcc_HueBox::draw()
{
    if (damage() & FL_DAMAGE_ALL) {
        draw_frame();
    }

    int x1 = 0; int y1 = 0; int w1 = w(); int h1 = h();
    box()->inset(x1,y1,w1,h1);

    if (damage() == FL_DAMAGE_VALUE) fl_push_clip(x1+px,y1+py,BUTTON_SIZE,BUTTON_SIZE);
    if(bg) bg->draw(x1,y1,w1,h1);
    if (damage() == FL_DAMAGE_VALUE) fl_pop_clip();

    Fl_Color_Chooser* c = (Fl_Color_Chooser*)parent();

#ifdef CIRCLE
    int X = int(.5f*(cos(c->hue()*float(M_PI/3.0))*c->saturation()+1) * (w1-BUTTON_SIZE));
    int Y = int(.5f*(1-sin(c->hue()*float(M_PI/3.0))*c->saturation()) * (h1-BUTTON_SIZE));
#else
    int X = int(c->hue()/6.0f*(w1-BUTTON_SIZE));
    int Y = int((1-c->saturation())*(h1-BUTTON_SIZE));
#endif

    if (X < 0) X = 0; else if (X > w1-BUTTON_SIZE) X = w1-BUTTON_SIZE;
    if (Y < 0) Y = 0; else if (Y > h1-BUTTON_SIZE) Y = h1-BUTTON_SIZE;

    button_box()->draw(x1+X, y1+Y, BUTTON_SIZE, BUTTON_SIZE, button_color(), 0);
    px = X;
    py = Y;
}

////////////////////////////////////////////////////////////////

int Flcc_ValueBox::handle(int e)
{
    static float iv;
    Fl_Color_Chooser* c = (Fl_Color_Chooser*)parent();
    switch (e) {
        case FL_PUSH:
            iv = c->v();
        case FL_DRAG: {
                float Yf;
                int x1 = 0; int y1 = 0; int w1 = w(); int h1 = h();
                box()->inset(x1,y1,w1,h1);
                Yf = 1-(Fl::event_y()-y1)/float(h1);
                if (fabs(Yf-iv)<(3*1.0f/h())) Yf = iv;
                if (c->hsv(c->h(),c->saturation(),Yf)) c->do_callback(FL_DATA_CHANGE);
            }
            return 1;
        default:
            return 0;
    }
}

Flcc_ValueBox::Flcc_ValueBox(int X, int Y, int W, int H)
: Fl_Widget(X,Y,W,H)
{
    py = 0;
    bg = 0;
}

Flcc_ValueBox::~Flcc_ValueBox()
{
    if(bg) delete bg;
}

void Flcc_ValueBox::layout()
{
    if(layout_damage() & FL_LAYOUT_WH) {
        generate();
    }

    Fl_Widget::layout();
}

static float tr, tg, tb;
void Flcc_ValueBox::generate()
{
    int X = 0, Y = 0, W = w(), H = h();
    box()->inset(X,Y,W,H);

    Fl_Image *im = new Fl_Image(W, H, 32);

    uint32 *dst = (uint32*)im->data();
    uint32 rgb;
    int skip = (im->pitch() - W * im->bytespp()) >> 2;

    for(int y = 0; y < H; y++) {

        float Yf = 255*(1.0-float(y)/H);
        fl_rgb888_from_rgb(rgb, uchar(tr*Yf+.5f), uchar(tg*Yf+.5f), uchar(tb*Yf+.5f));

        for(int x = 0; x < W; x++) {
            *dst++ = rgb;
        }

        dst += skip;
    }
    if(bg) delete bg;
    bg = im;
}

void Flcc_ValueBox::draw()
{
    int d = damage();
    int x1 = 0; int y1 = 0; int w1 = w(); int h1 = h();

    box()->inset(x1,y1,w1,h1);

    Fl_Color_Chooser* c = (Fl_Color_Chooser*)parent();
    c->hsv2rgb(c->hue(), c->saturation(), 1.0f, tr, tg, tb);

    if(d & FL_DAMAGE_ALL) {
        draw_frame();
        generate();     
    }

    if (d == FL_DAMAGE_VALUE) fl_push_clip(x1,y1+py,w1,6);
    bg->draw(x1,y1,w1,h1);
    if (d == FL_DAMAGE_VALUE) fl_pop_clip();

    int Y = int((1-c->v()) * (h1-6));
    if (Y < 0) Y = 0; else if (Y > h1-6) Y = h1-6;
    button_box()->draw(x1, y1+Y, w1, 6, color(), 0);

    py = Y;
}

////////////////////////////////////////////////////////////////

void Fl_Color_Chooser::rgb_cb(Fl_Widget* o, Fl_Color_Chooser *c)
{
    float r = c->rvalue.value();
    float g = c->gvalue.value();
    float b = c->bvalue.value();
    if (c->mode() == M_HSV) {
        if (c->hsv(r,g,b)) c->do_callback(FL_DATA_CHANGE);
        return;
    }
    if (c->mode() != M_RGB) {
        r = r/255;
        g = g/255;
        b = b/255;
    }
    if (c->rgb(r,g,b)) c->do_callback(FL_DATA_CHANGE);
}

void Fl_Color_Chooser::mode_cb(Fl_Widget* o, Fl_Color_Chooser *c)
{
    // force them to redraw even if value is the same:
    c->rvalue.value(-1);
    c->gvalue.value(-1);
    c->bvalue.value(-1);
    c->set_valuators();
}

////////////////////////////////////////////////////////////////

void Fl_Color_Chooser::draw()
{
    huebox.box(box());
    huebox.button_box(button_box());

    valuebox.box(box());

    Fl_Boxtype saved = box();
    box(FL_NO_BOX);
    Fl_Group::draw();
    box(saved);
}

static void revert(Fl_Style* s) {
    s->color = FL_GRAY;
    s->button_box = FL_ROUND_UP_BOX;
}

static Fl_Named_Style style("Color_Chooser", revert, &Fl_Color_Chooser::default_style);
Fl_Named_Style* Fl_Color_Chooser::default_style = &::style;

// ctor initializer - used in both ctors
void Fl_Color_Chooser::ctor_init(int X, int Y, int W, int H) {
    style(Fl_Color_Chooser::default_style);

    nrgroup.end();
    choice.begin();
    new Fl_Item("rgb");
    new Fl_Item("byte");
    new Fl_Item("hex");
    new Fl_Item("hsv");
    choice.end();
    end();
    resizable(huebox);
    sizes();
    resize(X,Y,W,H);
    r_ = g_ = b_ = 0;
    hue_ = 0.0;
    saturation_ = 0.0;
    value_ = 0.0;
    set_valuators();

    rvalue.callback((Fl_Callback*)rgb_cb, this);
    gvalue.callback((Fl_Callback*)rgb_cb, this);
    bvalue.callback((Fl_Callback*)rgb_cb, this);
    choice.callback((Fl_Callback*)mode_cb, this);

    rvalue.step(0.01);
    gvalue.step(0.01);
    bvalue.step(0.01);
}

// Traditional ctor
Fl_Color_Chooser::Fl_Color_Chooser(int X, int Y, int W, int H, const char* L)
: Fl_Group(0,0,180,100,L),
huebox(0,0,100,100),
valuebox(100,0,20,100),
nrgroup(120,0, 60, 100),
choice(0,0,60,21),
rvalue(0,22,60,21),
gvalue(0,44,60,21),
bvalue(0,66,60,21)
{
    ctor_init(X, Y, W, H);
}

// New style ctor
Fl_Color_Chooser::Fl_Color_Chooser(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Group(l,layout_size,layout_al,label_w),
huebox(0,0,100,100),
valuebox(100,0,20,100),
nrgroup(120,0, 60, 100),
choice(0,0,60,21),
rvalue(0,22,60,21),
gvalue(0,44,60,21),
bvalue(0,66,60,21)
{
    ctor_init(0, 0, w(), h());
}

Fl_Color Fl_Color_Chooser::value() const {
    Fl_Color ret = fl_rgb(uchar(255*r()+.5f), uchar(255*g()+.5f), uchar(255*b()+.5f));
    return (ret ? ret : (Fl_Color)FL_BLACK);
}

void Fl_Color_Chooser::value(Fl_Color c) {
    c = fl_get_color(c);
    rgb(uchar(c>>24)/255.0f, uchar(c>>16)/255.0f, uchar(c>>8)/255.0f);
}

////////////////////////////////////////////////////////////////
// fl_color_chooser():

#include <efltk/Fl_Window.h>
#include <efltk/Fl_Return_Button.h>

static Fl_Window* window;
static Fl_Color_Chooser* chooser;
static Fl_Box* ok_color;
static Fl_Button* ok_button;
static Fl_Box* cancel_color;
static Fl_Button* cancel_button;

// this location is used to preserve index Fl_Color values:
static Fl_Color picked_color;

static void chooser_cb(Fl_Widget*, void*) {
    ok_color->color(picked_color = chooser->value());
    ok_color->redraw();
}

#define ROWS 4
#define COLS 16

class CellBox : public Fl_Widget {
public:
    CellBox(int X, int Y, int W, int H) : Fl_Widget(X,Y,W,H) {}

    void draw();
    int handle(int);

    void set(Fl_Color *cp, int r, int c) {
        colors = cp;
        rows = r; cols = c;
    }

    Fl_Color *colors;
    int rows, cols;
};

void CellBox::draw() {
    for (int Y = 0; Y < rows; Y++) {
        int yy = Y*h()/rows;
        int hh = (Y+1)*h()/rows - yy;
        for (int X = 0; X < cols; X++) {
            int xx = X*w()/cols;
            int ww = (X+1)*w()/cols - xx;
            FL_THIN_DOWN_BOX->draw(xx,yy,ww,hh,colors[Y*cols+X]);
        }
    }
}

int CellBox::handle(int e) {
    switch (e) {
        case FL_PUSH: return 1;
        case FL_DRAG: return 1;
        case FL_RELEASE: {
                int X = Fl::event_x()*cols/w();
                if (X < 0 || X >= cols) return 1;
                int Y = Fl::event_y()*rows/h();
                if (Y < 0 || Y >= rows) return 1;
                X = X+Y*cols;
                if(Fl::event_button() > 1) {
                    colors[X] = picked_color;
                    redraw();
                } else {
                    chooser->value(picked_color = colors[X]);
                    ok_color->color(picked_color);
                    ok_color->redraw();
                }
                return 1;}
    }
    return Fl_Widget::handle(e);
}

FL_API Fl_Color fl_color_cells[ROWS*COLS] = {
    // first the 16 assignable fltk color indexes:
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
    16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
    // then the closest gray ramps to 0,1/4,1/3,1/2,2/3,3/4,1:
    32,32,32,37,37,39,39,43,43,47,47,49,49,55,55,55,
    32,32,32,37,37,39,39,43,43,47,47,49,49,55,55,55
};

static void ok_cb(Fl_Widget* w, void*) {
    w->window()->set_value();
    w->window()->hide();
}

static void cancel_cb(Fl_Widget* w, void*) {
    w->window()->hide();
}

static void make_it()
{
    int W=280;
    int H=290;

    if (window) return;
    window = new Fl_Window(W, H);
    window->size_range(W,H);
    chooser = new Fl_Color_Chooser(5, 5, W-10, H-130);
    chooser->callback(chooser_cb);

    CellBox *colors = new CellBox(5, H-120, W-10, 60);
    colors->set(fl_color_cells, ROWS, COLS);

    ok_color = new Fl_Box(5, H-55, W/2-10, 21);
    ok_color->box(FL_ENGRAVED_BOX);
    cancel_color = new Fl_Box(W/2+5, H-55, W/2-10, 21);
    cancel_color->box(FL_ENGRAVED_BOX);

    ok_button = new Fl_Return_Button(5, H-30, W/2-10, 21, _("&OK"));
    ok_button->callback(ok_cb);
    cancel_button = new Fl_Button(W/2+5, H-30, W/2-10, 21, _("&Cancel"));
    cancel_button->callback(cancel_cb);

    window->resizable(chooser);
    window->end();
}

static int run_it(const char* name) {
    window->label(name);
    ok_color->color(chooser->value());
    cancel_color->color(chooser->value());
    window->hotspot(window);
    return window->exec();
}

int fl_color_chooser(const char* name, float& r, float& g, float& b) {
    make_it();
    chooser->rgb(r,g,b);
    if (!run_it(name)) return 0;
    r = chooser->r();
    g = chooser->g();
    b = chooser->b();
    return 1;
}

int fl_color_chooser(const char* name, uchar& r, uchar& g, uchar& b) {
    make_it();
    chooser->rgb(r/255.0f, g/255.0f, b/255.0f);
    if (!run_it(name)) return 0;
    r = uchar(255*chooser->r()+.5f);
    g = uchar(255*chooser->g()+.5f);
    b = uchar(255*chooser->b()+.5f);
    return 1;
}

int fl_color_chooser(const char* name, Fl_Color& c) {
    make_it();
    chooser->value(c);
    picked_color = c;
    if (!run_it(name)) return 0;
    c = picked_color;
    return 1;
}

//
// End of "$Id$".
//
