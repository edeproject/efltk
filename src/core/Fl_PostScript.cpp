#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <efltk/fl_math.h>
#include <efltk/Fl_PostScript.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl.h>

int my_fprintf(FILE *fp, const char *fmt, ...)
{
    char *locale = setlocale(LC_ALL, "");
    int ret=0;
    if(locale && locale[1]) {
        char *restore_locale = locale ? strdup(locale) : strdup("C");
        setlocale(LC_ALL, "C");
        va_list ap;
        va_start(ap, fmt);
        ret = vfprintf(fp,  fmt, ap);
        va_end(ap);

        setlocale(LC_ALL, restore_locale);
        free((char*)restore_locale);
    } else {
        va_list ap;
        va_start(ap, fmt);
        ret = vfprintf(fp,  fmt, ap);
        va_end(ap);
    }
    return ret;
}

struct Matrix1 {
    float a, b, c, d, x, y;
    int ix, iy; // x & y rounded to nearest integer
    bool trivial; // true if no rotation or scale
};

static Matrix1 m = {1, 0, 0, 1, 0, 0, 0, 0, true};

// ADDED COMPAT
double fl_transform_x(double x, double y)  { return x*m.a + y*m.c + m.x; }
double fl_transform_y(double x, double y)  { return x*m.b + y*m.d + m.y; }
double fl_transform_dx(double x, double y) { return x*m.a + y*m.c; }
double fl_transform_dy(double x, double y) { return x*m.b + y*m.d; }

inline void fl_matrix(double& a, double& b, double& c, double& d, double &x, double& y)
{
    a=fl_transform_dx(1,0);
    c=fl_transform_dx(0,1);
    b=fl_transform_dy(1,0);
    d=fl_transform_dy(0,1);
    x=fl_transform_x(0,0);
    y=fl_transform_y(0,0);
}

static char Dashes[5][7]={
    {0,0,0,0,0,0,0},
    {8,8,0,0,0,0,0},
    {1,8,0,0,0,0,0},
    {8,8,1,8,0,0,0},
    {8,8,1,8,1,8,0}
};

////////////////////// Prolog string ////////////////////////////////////////

static const char * prolog =
"%%%%BeginProlog\n"

"/L {\n"
"  /y2 exch def\n"
"  /x2 exch def\n"
"  /y1 exch def\n"
"  /x1 exch def\n"
"  newpath\n"
"  x1 y1 moveto\n"
"  x2 y2 lineto\n"
"  stroke\n"
"} bind def\n\n"

"/P {\n"
"  /y exch def\n"
"  /x exch def\n"
"  newpath\n"
"  x y moveto\n"
"  x y lineto\n"
"  stroke\n"
"} bind def\n\n"

"/R {\n"
"  /dy exch def\n"
"  /dx exch def\n"
"  /y exch def\n"
"  /x exch def\n"
"  newpath\n"
"  x y moveto\n"
"  dx 0 rlineto\n"
"  0 dy rlineto\n"
"  dx neg 0 rlineto\n"
"  closepath stroke\n"
"} bind def\n\n"

"/CL {\n"
"  /dy exch def\n"
"  /dx exch def\n"
"  /y exch def\n"
"  /x exch def\n"
"  newpath\n"
"  x y moveto\n"
"  dx 0 rlineto\n"
"  0 dy rlineto\n"
"  dx neg 0 rlineto\n"
"  closepath\n"
"  clip\n"
"} bind def\n\n"

"/FR {\n"
"  /dy exch def"
"  /dx exch def\n"
"  /y exch def\n"
"  /x exch def\n"
"  currentlinewidth 0 setlinewidth newpath\n"
"  x y moveto\n"
"  dx 0 rlineto\n"
"  0 dy rlineto\n"
"  dx neg 0 rlineto\n"
"  closepath fill setlinewidth\n"
"} bind def\n\n"

"/GS { gsave } bind  def\n"
"/GR { grestore } bind def\n"

"/SP { showpage } bind def\n"
"/LW { setlinewidth } bind def\n"
"/CF /Courier def\n"
"/SF { /CF exch def } bind def\n"
"/fsize 12 def\n"
"/FS { /fsize exch def fsize CF findfont exch scalefont setfont }def \n"

"/GL { setgray } bind def\n"
"/SRGB { setrgbcolor } bind def\n"

//////////////////// color images ////////////////////////

"/CI {\n"
"  GS /py exch def /px exch def /sy exch def /sx exch def\n"
"  translate \n"
"  sx sy scale px py 8 \n"
"  [ px 0 0 py neg 0 py ]\n"
"  currentfile /ASCIIHexDecode filter\n false 3"
"  colorimage GR\n"
"} bind def\n\n"

///////////////////  gray images //////////////////////////

"/GI {\n"
"  GS /py exch def /px exch def /sy exch def /sx exch def\n"
"  translate \n"
"  sx sy scale px py 8 \n"
"  [ px 0 0 py neg 0 py ]\n"
"  currentfile /ASCIIHexDecode filter\n"
"  image GR\n"
"} bind def\n\n"

////////////////// single-color bitmask ///////////////////

"/MI {\n"
"  GS /py exch def /px exch def /sy exch def /sx exch def \n"
"  translate \n"
"  sx sy scale px py false \n"
"  [ px 0 0 py neg 0 py ]\n"
"  currentfile /ASCIIHexDecode filter\n"
"  imagemask GR\n"
"} bind def\n\n"

////////////////   color image dict /////////////

"/CII {\n"
"  GS /inter exch def /py exch def /px exch def /sy exch def /sx exch def \n"
"  translate \n"
"  sx sy scale\n"
"  /DeviceRGB setcolorspace\n"
"  /IDD 8 dict def\n"
"  IDD begin\n"
"  /ImageType 1 def\n"
"  /Width px def\n"
"  /Height py def\n"
"  /BitsPerComponent 8 def\n"
"  /Interpolate inter def\n"
"  /DataSource currentfile /ASCIIHexDecode filter def\n"
"  /MultipleDataSources false def\n"
"  /ImageMatrix [ px 0 0 py neg 0 py ] def\n"
"  /Decode [ 0 1 0 1 0 1 ] def\n"
"  end\n"
"  IDD image GR\n"
"} bind def\n\n"

//////////////// gray image dict ///////////////////

"/GII {\n"
"  GS /inter exch def /py exch def /px exch def /sy exch def /sx exch def \n"
"  translate \n"
"  sx sy scale\n"
"  /DeviceGray setcolorspace\n"
"  /IDD 8 dict def\n"
"  IDD begin\n"
"  /ImageType 1 def\n"
"  /Width px def\n"
"  /Height py def\n"
"  /BitsPerComponent 8 def\n"
"  /Interpolate inter def\n"
"  /DataSource currentfile /ASCIIHexDecode filter def\n"
"  /MultipleDataSources false def\n"
"  /ImageMatrix [ px 0 0 py neg 0 py ] def\n"
"  /Decode [ 0 1 ] def\n"
"  end\n"
"  IDD image GR\n"
"} bind def\n\n"

///////////////////  masked color images   ///////

"/CIM {\n"
"  GS /inter exch def /my exch def /mx exch def /py exch def /px exch def /sy exch def /sx exch def \n"
"  translate \n"
"  sx sy scale\n"
"  /DeviceRGB setcolorspace\n"

"  /IDD 8 dict def\n"
"  IDD begin\n"
"  /ImageType 1 def\n"
"  /Width px def\n"
"  /Height py def\n"
"  /BitsPerComponent 8 def\n"
"  /Interpolate inter def\n"
"  /DataSource currentfile /ASCIIHexDecode filter def\n"
"  /MultipleDataSources false def\n"
"  /ImageMatrix [ px 0 0 py neg 0 py ] def\n"
"  /Decode [ 0 1 0 1 0 1 ] def\n"
"  end\n"

"  /IMD 8 dict def\n"
"  IMD begin\n"
"  /ImageType 1 def\n"
"  /Width mx def\n"
"  /Height my def\n"
"  /BitsPerComponent 1 def\n"
//"  /Interpolate inter def\n"
"  /ImageMatrix [ mx 0 0 my neg 0 my ] def\n"
"  /Decode [ 1 0 ] def\n"
"  end\n"

"  <<\n"
"  /ImageType 3\n"
"  /InterleaveType 2\n"
"  /MaskDict IMD\n"
"  /DataDict IDD\n"
"  >> image GR\n"
"} bind def\n\n"

///////////////////  masked gray images   ////////////////

"/GIM {\n"
"  GS /inter exch def /my exch def /mx exch def /py exch def /px exch def /sy exch def /sx exch def \n"
"  translate \n"
"  sx sy scale\n"
"  /DeviceGray setcolorspace\n"

"  /IDD 8 dict def\n"
"  IDD begin\n"
"  /ImageType 1 def\n"
"  /Width px def\n"
"  /Height py def\n"
"  /BitsPerComponent 8 def\n"
"  /Interpolate inter def\n"
"  /DataSource currentfile /ASCIIHexDecode filter def\n"
"  /MultipleDataSources false def\n"
"  /ImageMatrix [ px 0 0 py neg 0 py ] def\n"
"  /Decode [ 0 1 ] def\n"
"  end\n"

"  /IMD 8 dict def\n"
"  IMD begin\n"
"  /ImageType 1 def\n"
"  /Width mx def\n"
"  /Height my def\n"
"  /BitsPerComponent 1 def\n"
"  /ImageMatrix [ mx 0 0 my neg 0 my ] def\n"
"  /Decode [ 1 0 ] def\n"
"  end\n"

"  <<\n"
"  /ImageType 3\n"
"  /InterleaveType 2\n"
"  /MaskDict IMD\n"
"  /DataDict IDD\n"
"  >> image GR\n"
"} bind def\n\n"

///////////////////////////  path ////////////////////

"/BFP { newpath moveto } def\n"
"/BP { newpath } bind def \n"
"/PL { lineto } bind def \n"
"/PM { moveto } bind def \n"
"/MT { moveto } bind def \n"
"/LT { lineto } bind def \n"
"/EFP { closepath fill } bind def\n"	//was:stroke
"/ELP { stroke } bind def\n"
"/ECP { closepath stroke } bind def\n"	// Closed (loop)
"/LW { setlinewidth } bind def\n"

//////////////////////////// misc ////////////////

"/TR { translate } bind def\n"
"/CT { concat } bind def\n"
"/RCT { matrix invertmatrix concat} bind def\n"
"/SC { scale } bind def\n\n"
;

////////////////////// end prolog ////////////////////////

//////////////////////  fonts   ////////////////////////////////////

///////////////////////// Implementations : matrix ////////////////////////////////////////

void Fl_PostScript::concat(){
    double a,b,c,d,x,y;
    fl_matrix(a,b,c,d,x,y);
    my_fprintf(output,"[%g %g %g %g %g %g] CT\n", a , b , c , d , x , y);
}

void Fl_PostScript::reconcat(){
    double a,b,c,d,x,y;
    fl_matrix(a,b,c,d,x,y);
    my_fprintf(output, "[%g %g %g %g %g %g] RCT\n" , a , b , c , d , x , y);
}

//////////////// for language level <3 ///////////////////////

void Fl_PostScript::recover()
{
    if (colored_)
        color(cr_,cg_,cb_);
    if (line_styled_)
        line_style(linestyle_,linewidth_,linedash_);
    if (fonted_)
        font(font_, size_);

    colored_=line_styled_=fonted_=0;
}

void Fl_PostScript::reset()
{
    gap_=1;
    clip_=0;
    cr_=cg_=cb_=0;
    font_=FL_HELVETICA;
    size_=12;
    linewidth_=0;
    linestyle_=FL_SOLID;
    strcpy(linedash_, Dashes[FL_SOLID]);
    Clip *c=clip_;   //just not to have memory leaks for badly writen code (forgotten clip popping)
    while(c){
        clip_=clip_->prev;
        delete c;
        c=clip_;
    }

    colored_=1;
    line_styled_=1;
    fonted_=1;
}

void Fl_PostScript::draw(Fl_Widget * w)
{
    Fl_Device *t = fl_current_dev;
    Fl::flush();
    fl_current_dev = this;
    w->redraw();
    w->draw();
    fl_current_dev = t;
    //w->redraw();
}

///////////////// destructor, finishes postscript, closes FILE  ///////////////

Fl_PostScript::~Fl_PostScript()
{
    if(nPages){  // for eps nPages is 0 so it is fine ....
        my_fprintf(output, "CR\nGR\n GR\nSP\n restore\n");
        my_fprintf(output, "%%%%Trailer\n");
        my_fprintf(output, "%%%%Pages: %i\n" , nPages);
    }else
        my_fprintf(output, "GR\n restore\n");

    reset();
    fclose(output);

    while(clip_){
        Clip * c= clip_;
        clip_= clip_->prev;
        delete c;
    }
}

///////////////// PostScript constructors /////////////////////////////////////

Fl_PostScript::Fl_PostScript(FILE *o, int lang_level, double pw, double ph, int orientation):clip_(0),interpolate_(0)
{
    lang_level_=lang_level;
    clip_=0;
    output=o;
    mask = 0;
    orientation_=0;
    orientation_=orientation;
    lm_=rm_=bm_=tm_=72;
    pw_ =pw;
    ph_= ph;
    my_fprintf(output, "%%!PS-Adobe-3.0\n");
    if(lang_level_>1)
        my_fprintf(output, "%%%%LanguageLevel: %i\n" , lang_level_);
    my_fprintf(output, "%%%%Pages: (atend)\n");
    //	my_fprintf(output, "%%%%BoundingBox: 0 0 %i %i\n" , w , h);

    if(orientation)
        my_fprintf(output, "%%%%Orientation: %i\n" , orientation);

    my_fprintf(output, prolog);

    if(lang_level_>=3){
        my_fprintf(output, "/CS { clipsave } bind def\n");
        my_fprintf(output, "/CR { cliprestore } bind def\n");
    }else{
        my_fprintf(output, "/CS { GS } bind def\n");
        my_fprintf(output, "/CR { GR } bind def\n");
    }
    my_fprintf(output, "\n%%%%EndProlog\n");

    reset();
    nPages=0;
}

/////////////////////////////////////////////////////

Fl_PostScript::Fl_PostScript(FILE *o, int lang_level, int format, int orientation)
:clip_(0),interpolate_(0)
{
    lang_level_=lang_level;
    output=o;
    mask = 0;
    orientation_=orientation;
    lm_=rm_=bm_=tm_=72;
    bg_=FL_GRAY;
    if (orientation&1){
        ph_= Fl_Printer::page_formats[format][0];
        pw_= Fl_Printer::page_formats[format][1];
    }else{
        ph_= Fl_Printer::page_formats[format][1];
        pw_= Fl_Printer::page_formats[format][0];
    }
    my_fprintf(output, "%%!PS-Adobe-3.0\n");
    if(lang_level_>1)
        my_fprintf(output, "%%%%LanguageLevel: %i\n" , lang_level_);
    my_fprintf(output, "%%%%Pages: (atend)\n");

    if(orientation)
        my_fprintf(output, "%%%%Orientation: %i\n" , orientation);
    my_fprintf(output, prolog);
    if(lang_level_>=3){
        my_fprintf(output, "/CS { clipsave } bind def\n");
        my_fprintf(output, "/CR { cliprestore } bind def\n");
    }else{
        my_fprintf(output, "/CS { GS } bind def\n");
        my_fprintf(output, "/CR { GR } bind def\n");
    }
    my_fprintf(output, "\n%%%%EndProlog\n");

    reset();
    nPages=0;
}

///////////////////  eps constructor ////////////////////////////////////

Fl_PostScript::Fl_PostScript(FILE *o, int lang_level, double x, double y, double w, double h)
: clip_(0),interpolate_(0)
{
    output=o;
    mask = 0;
    lang_level_=lang_level;
    bg_=FL_GRAY;
    my_fprintf(output, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    if(lang_level_>1)
        my_fprintf(output, "%%%%LanguageLevel: %i\n" , lang_level_);
    my_fprintf(output, "%%%%BoundingBox: %i %i %i %i\n", (int)x , (int)y , (int)(x+w+.999) , (int)(y+h+.999));
    //my_fprintf(output, "%%%%Orientation: %i\n" , orientation);
    width_ = w;
    height_ = h;
    lm_=x;
    tm_=0;
    rm_=0;
    bm_=y;
    my_fprintf(output, prolog);
    if(lang_level_>=3){
        my_fprintf(output, "/CS { clipsave } bind def\n");
        my_fprintf(output, "/CR { cliprestore } bind def\n");
    }else{
        my_fprintf(output, "/CS { GS } bind def\n");
        my_fprintf(output, "/CR { GR } bind def\n");
    }
    my_fprintf(output, "\n%%%%EndProlog\n");
    my_fprintf(output, "save\n");
    my_fprintf(output, "GS\n");

    reset();
    my_fprintf(output, "%g %g TR\n", x , y+h);
    my_fprintf(output, "1 -1  SC\n");
    my_fprintf(output, "GS\nCS\n");

    nPages=0;  //must be 0 also for eps!
}

////////////////////// paging //////////////////////////////////////////

void Fl_PostScript::page(double pw, double ph, int orientation)
{
    if (nPages){
        my_fprintf(output, "CR\nGR\nGR\nSP\nrestore\n");
    }

    nPages++;
    my_fprintf(output, "%%%%Page: %i %i\n" , nPages , nPages);

    pw_=pw;
    ph_=ph;
    width_= pw_ - lm_ - rm_;
    height_= ph_ - tm_ - bm_;
    orientation_=orientation;

    if (orientation_){
        my_fprintf(output, "%%%%PageOrientation: %i\n", orientation);
    }
    reset();
    my_fprintf(output, "save\n");
    my_fprintf(output, "GS\n");
    my_fprintf(output, "%g %g TR\n", lm_ , ph_ - tm_);
    my_fprintf(output, "1 -1 SC\n");
    my_fprintf(output, "GS\nCS\n");
}

void Fl_PostScript::page(int format,int orientation)
{
    orientation_=orientation;
    if(orientation &1){
        ph_=Fl_Printer::page_formats[format][0];
        pw_=Fl_Printer::page_formats[format][1];
    }else{
        pw_=Fl_Printer::page_formats[format][0];
        ph_=Fl_Printer::page_formats[format][1];
    }

    page(pw_,ph_,orientation);
}

void Fl_PostScript::margins(double left, double top, double right, double bottom)
{
    lm_=left;
    tm_=top;
    rm_=right;
    bm_=bottom;
    width_= pw_ - lm_ - rm_;
    height_ =  ph_ - tm_ - bm_;
    if(nPages){
        my_fprintf(output, "CR\nGR\nGR\nGS\n");
        my_fprintf(output, "%g %g TR\n", lm_ , ph_ - tm_);
        my_fprintf(output, "1 -1 SC\n");
        my_fprintf(output, "GS\nCS\n");
    }
}

void Fl_PostScript::fit(double x, double y, double w, double h, int align)
{
    double dx=0;
    double s=double(width_)/w;
    double dy=(height_ - s*h)/2;
    if((height_/h)<s){
        s=height_/h;
        dy=0;
        dx=(width_- s*w)/2;
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

    my_fprintf(output, "CR\nGR\nGS\n");
    reset();
    my_fprintf(output, "%g %g TR\n", -x*s+dx , -y*s+dy);
    my_fprintf(output, "%g %g SC\nCS\n", s , s );
}

void Fl_PostScript::fit(double x, double y, double w, double h, double dpi, int align)
{
    double s = 72.0/dpi;

    double dy=(height_ - s*h)/2;
    double dx=(width_- s*w)/2;

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

    my_fprintf(output, "CR\nGR\nGS\n");
    reset();
    my_fprintf(output, "%g %g TR\n", -x*s+dx , -y*s+dy);
    my_fprintf(output, "%g %g SC\nCS\n", s , s );
}

void Fl_PostScript::place(double x, double y, double w, double h, double tx, double ty, double tw, double th,  int align)
{
    double s=tw/w;
    double dx=0;
    double dy=(th - s*h)/2;
    if(th/h<s){
        s=th/h;
        dy=0;
        dx=(tw- s*w)/2;
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

    my_fprintf(output, "CR\nGR\nGS\n");
    reset();
    my_fprintf(output, "%g %g TR\n", -x*s+tx+dx , -y*s+ty+dy);
    my_fprintf(output, "%g %g SC\nCS\n", s , s );
}

void Fl_PostScript::place(double x, double y, double w, double h, double tx, double ty, double tw, double th, double dpi, int align)
{
    double s=72/dpi;
    double dy=(th - s*h)/2;
    double dx=(tw- s*w)/2;
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

    my_fprintf(output, "CR\nGR\nGS\nCS\n");
    reset();
    my_fprintf(output, "%g %g TR\n", -x+tx+dx , -y+ty+dy);
    my_fprintf(output, "%g %g SC\n", s , s );
}

//////////////////////////////  setting background for alpha /////////////////////////////////

void Fl_PostScript::bg_color(Fl_Color bg) { bg_=bg; }

//////////////////////////////// Primitives: Colors  ////////////////////////////////////////////

void Fl_PostScript::color(Fl_Color c) {
    colored_=1;
    color_=c;
    fl_get_color(c, cr_, cg_, cb_);

    if (cr_==cg_ && cg_==cb_) {
        double gray = cr_/255.0;
        my_fprintf(output, "%g GL\n", gray);
    } else {
        double fr, fg, fb;
        fr = cr_/255.0;
        fg = cg_/255.0;
        fb = cb_/255.0;
        my_fprintf(output,"%g %g %g SRGB\n", fr , fg , fb);
    }
}

void Fl_PostScript::color(unsigned char r, unsigned char g, unsigned char b)
{
    colored_=1;
    cr_=r;cg_=g;cb_=b;
    if (r==g && g==b) {
        double gray = r/255.0;
        my_fprintf(output, "%g GL\n", gray);
    } else {
        double fr, fg, fb;
        fr = r/255.0;
        fg = g/255.0;
        fb = b/255.0;
        my_fprintf(output, "%g %g %g SRGB\n", fr , fg , fb);
    }
}

/////////////////////////////   Clipping /////////////////////////////////////////////

void Fl_PostScript::push_clip(int x, int y, int w, int h) 
{
    Clip * c=new Clip();
    clip_box(x,y,w,h,c->x,c->y,c->w,c->h);
    c->prev=clip_;
    clip_=c;
    my_fprintf(output, "CR\nCS\n");
    if(lang_level_<3)
        recover();
    my_fprintf(output, "%i %i %i %i CL\n", clip_->x , clip_->y , clip_->w  , clip_->h);
}

void Fl_PostScript::clip_out(int x, int y, int w, int h)
{

}

void Fl_PostScript::push_no_clip()
{
    Clip * c = new Clip();
    c->prev=clip_;
    clip_=c;
    clip_->x = clip_->y = clip_->w = clip_->h = -1;
    my_fprintf(output, "CR\nCS\n");
    if(lang_level_<3)
        recover();
}

void Fl_PostScript::pop_clip()
{
    if(!clip_) return;

    Clip * c=clip_;
    clip_=clip_->prev;
    delete c;
    my_fprintf(output, "CR\nCS\n");
    if(clip_ && clip_->w >0)
        my_fprintf(output, "%g %g %i %i CL\n", clip_->x - 0.5, clip_->y - 0.5, clip_->w  , clip_->h);
    // uh, -0.5 is to match screen clipping, for floats there should be something btter
    if(lang_level_<3)
        recover();
}

int Fl_PostScript::clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H)
{
    if(!clip_){
        X=x;Y=y;W=w;H=h;
        return 1;
    }
    if(clip_->w < 0){
        X=x;Y=y;W=w;H=h;
        return 1;
    }
    int ret=0;
    if (x > (X=clip_->x)) {X=x; ret=1;}
    if (y > (Y=clip_->y)) {Y=y; ret=1;}
    if ((x+w) < (clip_->x+clip_->w)) {
        W=x+w-X;
        ret=1;
    }else
        W = clip_->x + clip_->w - X;
    if(W<0){
        W=0;
        return 1;
    }
    if ((y+h) < (clip_->y+clip_->h)) {
        H=y+h-Y;
        ret=1;
    }else
        H = clip_->y + clip_->h - Y;
    if(H<0){
        W=0;
        H=0;
        return 1;
    }
    return ret;
}

int Fl_PostScript::not_clipped(int x, int y, int w, int h)
{
    if(!clip_) return 1;
    if(clip_->w < 0) return 1;
    int X, Y, W, H;
    clip_box(x, y, w, h, X, Y, W, H);
    if(W) return 1;
    return 0;
}

const char* Fl_PostScript::encoding()
{
    puts("Not implemented encoding.");
    return 0;
}

///////////////////////// misc ////////////////////////////////////////////

static const char *get_font_face(Fl_Font f)
{
    static const char *fontfaces[] = {
        "Helvetica",
        "Helvetica-Bold",
        "Helvetica-Oblique",
        "Helvetica-BoldOblique",
        "Courier",
        "Courier-Bold",
        "Courier-Oblique",
        "Courier-BoldOblique",
        "Times",
        "Times-Bold",
        "Times-Italic",
        "Times-BoldItalic",
        "Symbol",
        "Courier",
        "CourierBold",
        "ZapfDingbats"
    };

    int index = 0;
    if(f==FL_HELVETICA_BOLD) index = 1;
    else if(f==FL_HELVETICA_ITALIC) index = 2;
    else if(f==FL_HELVETICA_BOLD_ITALIC) index = 3;
    else if(f==FL_COURIER) index = 4;
    else if(f==FL_COURIER_BOLD) index = 5;
    else if(f==FL_COURIER_ITALIC) index = 6;
    else if(f==FL_COURIER_BOLD_ITALIC) index = 7;
    else if(f==FL_TIMES) index = 8;
    else if(f==FL_TIMES_BOLD) index = 9;
    else if(f==FL_TIMES_ITALIC) index = 10;
    else if(f==FL_TIMES_BOLD_ITALIC) index = 11;
    else if(f==FL_SYMBOL) index = 12;
    else if(f==FL_SCREEN) index = 13;
    else if(f==FL_SCREEN_BOLD) index = 14;
    else if(f==FL_ZAPF_DINGBATS) index = 15;

    return fontfaces[index];
}

void Fl_PostScript::font(Fl_Font f, float s) 
{
    fonted_=1;
    my_fprintf(output, "/%s SF\n" , get_font_face(f));
    my_fprintf(output,"%i FS\n", int(s));

    fl_fltk_dev.font(f, s); //Dirty hack for font measurement ;-(

    font_=f; size_=s;
}

void Fl_PostScript::font(const char* s, float size)
{
    Fl_Font f = fl_find_font(s);
    font(f, size);
}

void Fl_PostScript::font(const char* s, int attributes, float size)
{
    Fl_Font f = fl_find_font(s, attributes);
    font(f, size);
}

void  Fl_PostScript::encoding(const char*)
{
}

const char* Fl_PostScript::fontname(Fl_Font f, int *i)
{
    return get_font_face(f);
}


void Fl_PostScript::line_style(int style, int width, char* dashes){
    line_styled_=1;
    if(!width)
        width=1; //for screen drawing compatability
    linewidth_=width;
    linestyle_=style;
    my_fprintf(output, "%i setlinewidth\n", width);
    if(!dashes)
        dashes=Dashes[style&0xff];
    strcpy(linedash_,dashes);
    my_fprintf(output, "[");
    while(*dashes){
        my_fprintf(output, "%i ",(int)(*dashes));
        dashes++;
    }
    my_fprintf(output, "] 0 setdash\n");
    style>>=8;
    if(int i=style&0xf)
        my_fprintf(output,"%i setlinecap\n", i-1);
    else
        my_fprintf(output, "1 setlinecap\n"); //standard cap

    style>>=4;
    int i=style&0xf;
    if(i)
        my_fprintf(output, "%i setlinejoin\n", i-1) ;
    else
        my_fprintf(output, "1 setlinejoin\n");
};

float Fl_PostScript::width(const char* s)
{
    return fl_fltk_dev.width(s); //Dirty...
}

float Fl_PostScript::width(const Fl_String& s)
{
    return fl_fltk_dev.width(s);
}

float Fl_PostScript::width(unsigned int unc)
{
    return fl_fltk_dev.width(unc);
}

float Fl_PostScript::width(const char* s, int n)
{
    return fl_fltk_dev.width(s,n); //Very Dirty...
}

float Fl_PostScript::descent()
{
    return fl_fltk_dev.descent(); //A bit Dirty...
}

float Fl_PostScript::height()
{
    return fl_fltk_dev.height(); //Still Dirty...
}

void Fl_PostScript::rtl_draw(const char *s, int n, float x, float y)
{
    puts("rtl draw unimplemented.");
}

///////////////////////////////  text ////////////////////////////////////

void Fl_PostScript::transformed_draw(const char* str, int n, float x, float y){

    if (!n || !str || !*str) return;
    my_fprintf(output, "GS\n");
    my_fprintf(output,"%g %g moveto\n", x , y);
    my_fprintf(output, "[1 0 0 -1 0 0] concat\n");
    int i=1;
    my_fprintf(output, "\n(");
    for(int j=0;j<n;j++){
        if(i>240){
            my_fprintf(output, "\\\n");
            i=0;
        }
        i++;
        switch (*str) {
        case '(': case ')':
            my_fprintf(output, "\\%c" , *str);
            break;
        default:
            my_fprintf(output, "%c", *str);
        }
        str++;
    }
    my_fprintf(output, ") show\n");
    my_fprintf(output, "GR\n");
}

////////////////////////////      Images      /////////////////////////////////////

static inline uchar swap_byte(const uchar i)
{
    uchar b =0;
    if(i & 1) b |= 128;
    if(i & 2) b |= 64;
    if(i & 4) b |= 32;
    if(i & 8) b |= 16;
    if(i & 16) b |= 8;
    if(i & 32) b |= 4;
    if(i & 64) b |= 2;
    if(i & 128) b |= 1;
    return b;
}

//extern uchar **fl_mask_bitmap;

void Fl_PostScript::draw_scalled_image(const uchar *data, double x, double y, double w, double h, int iw, int ih, int D, int LD)
{
    if(D<3){ //mono
        draw_scalled_image(data, x, y, w, h, iw, ih, D, LD);
        return;
    }

    int i,j, k;

    my_fprintf(output,"save\n");

    char * interpol;
    if(lang_level_>1){
        if(interpolate_)
            interpol="true";
        else
            interpol="false";
        if(mask && lang_level_>2)
            my_fprintf(output, "%g %g %g %g %i %i %i %i %s CIM\n", x , y+h , w , -h , iw , ih, mx, my, interpol);
        else
            my_fprintf(output, "%g %g %g %g %i %i %s CII\n", x , y+h , w , -h , iw , ih, interpol);
    }else
        my_fprintf(output , "%g %g %g %g %i %i CI", x , y+h , w , -h , iw , ih);


    if(!LD) LD = iw*D;
    uchar *curmask=mask;
    uchar bg_r, bg_g, bg_b;
    fl_get_color(bg_, bg_r,bg_g,bg_b);
    for (j=0; j<ih;j++){
        if(mask){
            for(k=0;k<my/ih;k++){
                for (i=0; i<((mx+7)/8);i++){
                    if (!(i%80)) my_fprintf(output, "\n");
                    my_fprintf(output, "%.2x",swap_byte(*curmask));
                    curmask++;
                }
                my_fprintf(output,"\n");
            }
        }
        const uchar *curdata=data+j*LD;
        for(i=0 ; i<iw ; i++) {
            uchar r = curdata[0];
            uchar g =  curdata[1];
            uchar b =  curdata[2];
            if(lang_level_<3 && D>3) { //can do  mixing using bg_* colors)
                unsigned int a2 = curdata[3]; //must be int 
                unsigned int a = 255-a2;
                r = (a2 * r + bg_r * a)/255;
                g = (a2 * g + bg_g * a)/255;
                b = (a2 * b + bg_b * a)/255;
            }
            if (!(i%40)) my_fprintf(output, "\n");
            my_fprintf(output, "%.2x%.2x%.2x", r, g, b);
            curdata +=D;
        }
        my_fprintf(output,"\n");

    }

    my_fprintf(output," >\nrestore\n" );
};

void Fl_PostScript::draw_scalled_image(Fl_Draw_Image_Cb call, void *data, double x, double y, double w, double h, int iw, int ih, int D) 
{
    my_fprintf(output,"save\n");
    int i,j,k;
    char * interpol;
    if(lang_level_>1){
        if(interpolate_) interpol="true";
        else interpol="false";
        if(mask && lang_level_>2)
            my_fprintf(output, "%g %g %g %g %i %i %i %i %s CIM\n", x , y+h , w , -h , iw , ih, mx, my, interpol);
        else
            my_fprintf(output, "%g %g %g %g %i %i %s CII\n", x , y+h , w , -h , iw , ih, interpol);
    }else
        my_fprintf(output , "%g %g %g %g %i %i CI", x , y+h , w , -h , iw , ih);

    int LD=iw*D;
    uchar *rgbdata=new uchar[LD];
    uchar *curmask=mask;

    for (j=0; j<ih;j++){
        if(mask && lang_level_>2){  // InterleaveType 2 mask data
            for(k=0; k<my/ih;k++){ //for alpha pseudo-masking
                for (i=0; i<((mx+7)/8);i++){
                    if (!(i%40)) my_fprintf(output, "\n");
                    my_fprintf(output, "%.2x",swap_byte(*curmask));
                    curmask++;
                }
                my_fprintf(output,"\n");
            }
        }
        call(data,0,j,iw,rgbdata);
        uchar *curdata=rgbdata;
        for(i=0 ; i<iw ; i++) {
            uchar r = curdata[0];
            uchar g =  curdata[1];
            uchar b =  curdata[2];

            if (!(i%40)) my_fprintf(output, "\n");
            my_fprintf(output, "%.2x%.2x%.2x", r, g, b);

            curdata +=D;
        }
        my_fprintf(output,"\n");

    }
    my_fprintf(output,">\n");


    my_fprintf(output,"restore\n");
    delete[] rgbdata;
}

void Fl_PostScript::draw_scalled_image_mono(const uchar *data, double x, double y, double w, double h, int iw, int ih, int D, int LD) 
{
    my_fprintf(output,"save\n");

    int i,j, k;

    char * interpol;
    if(lang_level_>1){
        if(interpolate_)
            interpol="true";
        else
            interpol="false";
        if(mask && lang_level_>2)
            my_fprintf(output, "%g %g %g %g %i %i %i %i %s GIM\n", x , y+h , w , -h , iw , ih, mx, my, interpol);
        else
            my_fprintf(output, "%g %g %g %g %i %i %s GII\n", x , y+h , w , -h , iw , ih, interpol);
    }else
        my_fprintf(output , "%g %g %g %g %i %i GI", x , y+h , w , -h , iw , ih);


    if(!LD) LD = iw*D;

    uchar bg_r, bg_g, bg_b;
    fl_get_color(bg_, bg_r,bg_g,bg_b);
    int bg = (bg_r + bg_g + bg_b)/3;

    uchar *curmask=mask;
    for (j=0; j<ih;j++){
        if(mask){
            for(k=0;k<my/ih;k++){
                for (i=0; i<((mx+7)/8);i++){
                    if (!(i%80)) my_fprintf(output, "\n");
                    my_fprintf(output, "%.2x",swap_byte(*curmask));
                    curmask++;
                }
                my_fprintf(output,"\n");
            }
        }
        const uchar *curdata=data+j*LD;
        for(i=0 ; i<iw ; i++) {
            if (!(i%80)) my_fprintf(output, "\n");
            uchar r = curdata[0];
            if(lang_level_<3 && D>1) { //can do  mixing
                unsigned int a2 = curdata[1]; //must be int 
                unsigned int a = 255-a2;
                r = (a2 * r + bg * a)/255;
            }
            if (!(i%120)) my_fprintf(output, "\n");
            my_fprintf(output, "%.2x", r);
            curdata +=D;
        }
        my_fprintf(output,"\n");

    }

    my_fprintf(output," >\nrestore\n" );
};


void Fl_PostScript::draw_scalled_image_mono(Fl_Draw_Image_Cb call, void *data, double x, double y, double w, double h, int iw, int ih, int D) 
{
    my_fprintf(output,"save\n");
    int i,j,k;
    char * interpol;
    if(lang_level_>1){
        if(interpolate_) interpol="true";
        else interpol="false";
        if(mask && lang_level_>2)
            my_fprintf(output, "%g %g %g %g %i %i %i %i %s GIM\n", x , y+h , w , -h , iw , ih, mx, my, interpol);
        else
            my_fprintf(output, "%g %g %g %g %i %i %s GII\n", x , y+h , w , -h , iw , ih, interpol);
    }else
        my_fprintf(output , "%g %g %g %g %i %i GI", x , y+h , w , -h , iw , ih);

    int LD=iw*D;
    uchar *rgbdata=new uchar[LD];
    uchar *curmask=mask;
    for (j=0; j<ih;j++){
        if(mask && lang_level_>2){  // InterleaveType 2 mask data
            for(k=0; k<my/ih;k++){ //for alpha pseudo-masking
                for (i=0; i<((mx+7)/8);i++){
                    if (!(i%40)) my_fprintf(output, "\n");
                    my_fprintf(output, "%.2x",swap_byte(*curmask));
                    curmask++;
                }
                my_fprintf(output,"\n");
            }
        }
        call(data,0,j,iw,rgbdata);
        uchar *curdata=rgbdata;
        for(i=0 ; i<iw ; i++) {
            uchar r = curdata[0];
            if (!(i%120)) my_fprintf(output, "\n");
            my_fprintf(output, "%.2x", r);
            curdata +=D;
        }
        my_fprintf(output,"\n");
    }
    my_fprintf(output,">\n");
    my_fprintf(output,"restore\n");
    delete[] rgbdata;
}

///////////////
// Verticies //
///////////////

////////////////////////////////////////////////////////////////
// Path construction:

#include <efltk/fl_draw.h>
#include <efltk/x.h>
#include <stdlib.h>

// typedef what the x,y fields in a point are:
typedef int COORD_T;

// Storage of the current path:

// Points:
static XPoint *point_; // all the points
static int point_array_size;
static int points_; // number of points

// Loop:
static int loop_start; // point at start of current loop
static int* loop; // number of points in each loop
static int loops; // number of loops
static int loop_array_size;

static void add_n_points(int n)
{
    point_array_size = (point_array_size>0) ? 2*point_array_size : 16;
    if(points_+n >= point_array_size) point_array_size = n;
    point_ = (XPoint*)realloc((void*)point_, (point_array_size+1)*sizeof(XPoint));
}

void Fl_PostScript::vertex(float X, float Y)
{
    COORD_T x = COORD_T(floorf(X*m.a + Y*m.c + m.x + .5f));
    COORD_T y = COORD_T(floorf(X*m.b + Y*m.d + m.y + .5f));
    if (!points_ || x != point_[points_-1].x || y != point_[points_-1].y) {
        if (points_+1 >= point_array_size) add_n_points(1);
        point_[points_].x = x;
        point_[points_].y = y;
        points_++;
    }
}

void Fl_PostScript::vertex(int X, int Y)
{
    COORD_T x,y;
    if (m.trivial) {
        x = COORD_T(X+m.ix);
        y = COORD_T(Y+m.iy);
    } else {
        x = COORD_T(floorf(X*m.a + Y*m.c + m.x + .5f));
        y = COORD_T(floorf(X*m.b + Y*m.d + m.y + .5f));
    }
    if (!points_ || x != point_[points_-1].x || y != point_[points_-1].y) {
        if (points_+1 >= point_array_size) add_n_points(1);
        point_[points_].x = x;
        point_[points_].y = y;
        points_++;
    }
}

void Fl_PostScript::vertices(int n, const float array[][2])
{
    if (points_+n >= point_array_size) add_n_points(n);
    const float* a = array[0];
    const float* e = a+2*n;
    int pn = points_;
    if (m.trivial) {
        for (; a < e; a += 2) {
            COORD_T x = COORD_T(floorf(a[0] + m.x + .5f));
            COORD_T y = COORD_T(floorf(a[1] + m.y + .5f));
            if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
                point_[pn].x = x;
                point_[pn].y = y;
                pn++;
            }
        }
    } else {
        for (; a < e; a += 2) {
            COORD_T x = COORD_T(floorf(a[0]*m.a + a[1]*m.c + m.x + .5f));
            COORD_T y = COORD_T(floorf(a[0]*m.b + a[1]*m.d + m.y + .5f));
            if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
                point_[pn].x = x;
                point_[pn].y = y;
                pn++;
            }
        }
    }
    points_ = pn;
}

void Fl_PostScript::vertices(int n, const int array[][2])
{
    if (points_+n >= point_array_size) add_n_points(n);
    const int* a = array[0];
    const int* e = a+2*n;
    int pn = points_;
    if (m.trivial) {
        for (; a < e; a += 2) {
            COORD_T x = COORD_T(a[0]+m.ix);
            COORD_T y = COORD_T(a[1]+m.iy);
            if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
                point_[pn].x = x;
                point_[pn].y = y;
                pn++;
            }
        }
    } else {
        for (; a < e; a += 2) {
            COORD_T x = COORD_T(floorf(a[0]*m.a + a[1]*m.c + m.x + .5f));
            COORD_T y = COORD_T(floorf(a[0]*m.b + a[1]*m.d + m.y + .5f));
            if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
                point_[pn].x = x;
                point_[pn].y = y;
                pn++;
            }
        }
    }
    points_ = pn;
}

void Fl_PostScript::transformed_vertices(int n, const float array[][2])
{
    if (points_+n >= point_array_size) add_n_points(n);
    const float* a = array[0];
    const float* e = a+2*n;
    int pn = points_;
    for (; a < e; a += 2) {
        COORD_T x = COORD_T(floorf(a[0] + .5f));
        COORD_T y = COORD_T(floorf(a[1] + .5f));
        if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
            point_[pn].x = x;
            point_[pn].y = y;
            pn++;
        }
    }
    points_ = pn;
}

void Fl_PostScript::closepath()
{
    if (points_ > loop_start+2) {
        // close the shape by duplicating first point_:
        XPoint& q = point_[loop_start];
        // the array always has one extra point_ so we don't need to check
        XPoint& p = point_[points_-1];
        if (p.x != q.x || p.y != q.y) point_[points_++] = q;
        // remember the new loop:
        if (loops >= loop_array_size) {
            loop_array_size = loop_array_size ? 2*loop_array_size : 16;
            loop = (int*)realloc((void*)loop, loop_array_size*sizeof(int));
        }
        loop[loops++] = points_-loop_start;
        loop_start = points_;
    } else {
        points_ = loop_start;
    }
}

////////////////////////////////////////////////////////////////
// Enormous kludge to add arcs to a path but try to take advantage
// of primitive arc-drawing functions provided by the OS. This mess
// should not be needed on newer systems...
//
// We keep track of exactly one "nice" circle:

static int circle_x, circle_y, circle_w, circle_h;

// Add a circle to the path. It is always a circle, irregardless of
// the transform. Currently only one per path is supported, this uses
// commands on the server to draw a nicer circle than the path mechanism
// can make.
void Fl_PostScript::circle(float x, float y, float r)
{
    fl_transform(x,y);
    float rt = r * sqrtf(fabsf(m.a*m.d-m.b*m.c));
    circle_w = circle_h = int(rt*2 + .5);
    circle_x = int(floorf(x - circle_w*.5f + .5f));
    circle_y = int(floorf(y - circle_h*.5f + .5f));
}

// Add an ellipse to the path. On X/Win32 this only works for 90 degree
// rotations and only one ellipse (or cirlce) per path is supported.
void Fl_PostScript::ellipse(float x, float y, float w, float h)
{
    // This produces the correct image, but not as nice as using circles
    // produced by the server:
    fl_closepath();
    fl_arc(x, y, w, h, 0, 360);
    fl_closepath();
}

////////////////////////////////////////////////////////////////
// Draw the path:

static inline void inline_newpath() {
    points_ = loop_start = loops = circle_w = 0;
}
void Fl_PostScript::newpath() { inline_newpath(); }

void Fl_PostScript::points()
{
    my_fprintf(output, "GS\n");
    concat();
    my_fprintf(output, "BP\n");

    for(int i=0; i<points_; i++)
        my_fprintf(output,"%d %d MT\n", point_[i].x, point_[i].y);

    inline_newpath();
}

void Fl_PostScript::stroke()
{
    fl_closepath();
    inline_newpath();
    return;

    if (circle_w > 0)
        XDrawArc(fl_display, fl_window, fl_gc,
                 circle_x, circle_y, circle_w, circle_h, 0, 360*64);
    int loop_start = 0;
    for (int n = 0; n < loops; n++) {
        int loop_size = loop[n];
        XDrawLines(fl_display, fl_window, fl_gc, point_+loop_start, loop_size, 0);
        loop_start += loop_size;
    }
    int loop_size = points_-loop_start;
    if (loop_size > 1)
        XDrawLines(fl_display, fl_window, fl_gc, point_+loop_start, loop_size, 0);

    inline_newpath();
}

// Warning: result is different on X and Win32! Use fl_fill_stroke().
// There may be a way to tell Win32 to do what X does, perhaps by making
// the current pen invisible?
void Fl_PostScript::fill()
{
    fl_closepath();
    inline_newpath();

    return;
    my_fprintf(output, "GS\n");
    concat();

    if (circle_w > 0) {
        puts("DRAW CIRCLE");
    }
    if (loops) fl_closepath();
    if (points_ > 2) {
        if (loops > 2) {
            // back-trace the lines between each "disconnected" part so they
            // are actually connected:
            if (points_+loops-2 >= point_array_size) add_n_points(loops-2);
            int n = points_-1;
            for (int i = loops; --i > 1;) {
                n -= loop[i];
                point_[points_++] = point_[n];
            }
        }

        XFillPolygon(fl_display, fl_window, fl_gc, point_, points_, 0, 0);
    }

    reconcat();
    my_fprintf(output, "GR\n");

    inline_newpath();
}

// This seems to produce very similar results on X and Win32. Also
// should be faster than seperate fill & stroke on Win32 and on
// PostScript/PDF style systems.
void Fl_PostScript::fill_stroke(Fl_Color color)
{
    fl_closepath();
    return;

    if (circle_w > 0)
        XFillArc(fl_display, fl_window, fl_gc,
                 circle_x, circle_y, circle_w, circle_h, 0, 64*360);
    fl_closepath();
    if (points_ > 2) {
        int saved_points = points_;
        if (loops > 2) {
            // back-trace the lines between each "disconnected" part so they
            // are actually connected:
            if (points_+loops-2 >= point_array_size) add_n_points(loops-2);
            int n = saved_points-1;
            for (int i = loops; --i > 1;) {
                n -= loop[i];
                point_[points_++] = point_[n];
            }
        }
        XFillPolygon(fl_display, fl_window, fl_gc, point_, points_, 0, 0);
        points_ = saved_points; // throw away the extra points
    }
    Fl_Color saved = fl_color();
    fl_color(color);
    fl_stroke();
    fl_color(saved);
}

//////////////////////////

void Fl_PostScript::arc(float l, float b, float w, float h, float start, float end)
{
    return;
}
void Fl_PostScript::pie(int x,int y,int w,int h,float a1,float a2)
{
    return;
}
void Fl_PostScript::curve(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
    return;
}

void Fl_PostScript::rect(int x, int y, int w, int h)
{
    fprintf(output, "GS\n");
    fprintf(output, "%i, %i, %i, %i R\n", x , y , w, h);
    fprintf(output, "GR\n");
}

void Fl_PostScript::rectf(int x, int y, int w, int h)
{
    fprintf(output, "%i %i %i %i FR\n", x, y, w, h);
}
void Fl_PostScript::rectf(int x, int y, int w, int h, uchar r,  uchar g, uchar b)
{
    fprintf(output, "GS\n");
    double fr = r/255.0;
    double fg = g/255.0;
    double fb = b/255.0;
    fprintf(output, "%g %g %g SRGB\n",fr , fg , fb);
    fprintf(output, "%i %i %i %i FR\n", x , y , w  , h );
    fprintf(output, "GR\n");
}

void Fl_PostScript::line(int x, int y, int x1, int y1)
{
    fprintf(output, "GS\n");
    fprintf(output, "%i %i %i %i L\n", x , y, x1 ,y1);
    fprintf(output, "GR\n");
}

void Fl_PostScript::point(int x, int y)
{
    fprintf(output, "GS\n");
    fprintf(output, "%i %i P\n", x , y);
    fprintf(output, "GR\n");
}
