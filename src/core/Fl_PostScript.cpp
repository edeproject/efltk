#include <stdio.h>
#include <math.h>

#include <efltk/Fl_PostScript.h>
#include <efltk/Fl.h>

struct Matrix1 {
    float a, b, c, d, x, y;
    int ix, iy; // x & y rounded to nearest integer
    bool trivial; // true if no rotation or scale
};

static Matrix1 m = {1, 0, 0, 1, 0, 0, 0, 0, true};

// ADDED COMPAT
double fl_transform_x(double x, double y) {return x*m.a + y*m.c + m.x;}
double fl_transform_y(double x, double y) {return x*m.b + y*m.d + m.y;}
double fl_transform_dx(double x, double y) {return x*m.a + y*m.c;}
double fl_transform_dy(double x, double y) {return x*m.b + y*m.d;}

inline void fl_matrix(double& a, double& b, double& c, double& d, double &x, double& y)
{
    a=fl_transform_dx(1,0);	c=fl_transform_dx(0,1);	b=fl_transform_dy(1,0);	d=fl_transform_dy(0,1);	x=fl_transform_x(0,0);	y=fl_transform_y(0,0);
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
    "/L { /y2 exch def\n"
    "/x2 exch def\n"
    "/y1 exch def\n"
    "/x1 exch def\n"
    "newpath   x1 y1 moveto x2 y2 lineto\n"
    "stroke}\n"
    "bind def\n"


    "/R { /dy exch def\n"
    "/dx exch def\n"
    "/y exch def\n"
    "/x exch def\n"
    "newpath\n"
    "x y moveto\n"
    "dx 0 rlineto\n"
    "0 dy rlineto\n"
    "dx neg 0 rlineto\n"
    "closepath stroke\n"
    "} bind def\n"

    "/CL {\n"
    "/dy exch def\n"
    "/dx exch def\n"
    "/y exch def\n"
    "/x exch def\n"
    "newpath\n"
    "x y moveto\n"
    "dx 0 rlineto\n"
    "0 dy rlineto\n"
    "dx neg 0 rlineto\n"
    "closepath\n"
    "clip\n"
    "} bind def\n"

    "/FR { /dy exch def\n"
    "/dx exch def\n"
    "/y exch def\n"
    "/x exch def\n"
    "currentlinewidth 0 setlinewidth newpath\n"
    "x y moveto\n"
    "dx 0 rlineto\n"
    "0 dy rlineto\n"
    "dx neg 0 rlineto\n"
    "closepath fill setlinewidth\n"
    "} bind def\n"

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

    "/CI { GS /py exch def /px exch def /sy exch def /sx exch def\n"
    "translate \n"
    "sx sy scale px py 8 \n"
    "[ px 0 0 py neg 0 py ]\n"
    "currentfile /ASCIIHexDecode filter\n false 3"
    " colorimage GR\n"
    "} bind def\n"

///////////////////  gray images //////////////////////////

    "/GI { GS /py exch def /px exch def /sy exch def /sx exch def \n"
    "translate \n"
    "sx sy scale px py 8 \n"
    "[ px 0 0 py neg 0 py ]\n"
    "currentfile /ASCIIHexDecode filter\n"
    "image GR\n"
    "} bind def\n"

////////////////// single-color bitmask ///////////////////

    "/MI { GS /py exch def /px exch def /sy exch def /sx exch def \n"
    "translate \n"
    "sx sy scale px py false \n"
    "[ px 0 0 py neg 0 py ]\n"
    "currentfile /ASCIIHexDecode filter\n"
    "imagemask GR\n"
    "} bind def\n"

////////////////   color image dict /////////////

    "/CII {GS /inter exch def /py exch def /px exch def /sy exch def /sx exch def \n"
    "translate \n"
    "sx sy scale\n"
    "/DeviceRGB setcolorspace\n"
    "/IDD 8 dict def\n"
    "IDD begin\n"
    "/ImageType 1 def\n"
    "/Width px def\n"
    "/Height py def\n"
    "/BitsPerComponent 8 def\n"
    "/Interpolate inter def\n"
    "/DataSource currentfile /ASCIIHexDecode filter def\n"
    "/MultipleDataSources false def\n"
    "/ImageMatrix [ px 0 0 py neg 0 py ] def\n"
    "/Decode [ 0 1 0 1 0 1 ] def\n"
    "end\n"
    "IDD image GR} bind def\n"

//////////////// gray image dict ///////////////////

    "/GII {GS /inter exch def /py exch def /px exch def /sy exch def /sx exch def \n"
    "translate \n"
    "sx sy scale\n"
    "/DeviceGray setcolorspace\n"
    "/IDD 8 dict def\n"
    "IDD begin\n"
    "/ImageType 1 def\n"
    "/Width px def\n"
    "/Height py def\n"
    "/BitsPerComponent 8 def\n"
    "/Interpolate inter def\n"
    "/DataSource currentfile /ASCIIHexDecode filter def\n"
    "/MultipleDataSources false def\n"
    "/ImageMatrix [ px 0 0 py neg 0 py ] def\n"
    "/Decode [ 0 1 ] def\n"
    "end\n"
    "IDD image GR} bind def\n"


///////////////////  masked color images   ///////
    "/CIM {GS /inter exch def /my exch def /mx exch def /py exch def /px exch def /sy exch def /sx exch def \n"
    "translate \n"
    "sx sy scale\n"
    "/DeviceRGB setcolorspace\n"



    "/IDD 8 dict def\n"
    "IDD begin\n"
    "/ImageType 1 def\n"
    "/Width px def\n"
    "/Height py def\n"
    "/BitsPerComponent 8 def\n"
    "/Interpolate inter def\n"
    "/DataSource currentfile /ASCIIHexDecode filter def\n"
    "/MultipleDataSources false def\n"
    "/ImageMatrix [ px 0 0 py neg 0 py ] def\n"
    "/Decode [ 0 1 0 1 0 1 ] def\n"
    "end\n"

    "/IMD 8 dict def\n"
    "IMD begin\n"
    "/ImageType 1 def\n"
    "/Width mx def\n"           
    "/Height my def\n"
    "/BitsPerComponent 1 def\n"
//	"/Interpolate inter def\n"
    "/ImageMatrix [ mx 0 0 my neg 0 my ] def\n"
    "/Decode [ 1 0 ] def\n"
    "end\n"

    "<<\n"
    "/ImageType 3\n"
    "/InterleaveType 2\n"
    "/MaskDict IMD\n"
    "/DataDict IDD\n"
    ">> image GR\n"
    "} bind def\n"



///////////////////  masked gray images   ////////////////


    "/GIM {GS /inter exch def /my exch def /mx exch def /py exch def /px exch def /sy exch def /sx exch def \n"
    "translate \n"
    "sx sy scale\n"
    "/DeviceGray setcolorspace\n"



    "/IDD 8 dict def\n"
    "IDD begin\n"
    "/ImageType 1 def\n"
    "/Width px def\n"
    "/Height py def\n"
    "/BitsPerComponent 8 def\n"
    "/Interpolate inter def\n"
    "/DataSource currentfile /ASCIIHexDecode filter def\n"
    "/MultipleDataSources false def\n"
    "/ImageMatrix [ px 0 0 py neg 0 py ] def\n"
    "/Decode [ 0 1 ] def\n"
    "end\n"

    "/IMD 8 dict def\n"
    "IMD begin\n"
    "/ImageType 1 def\n"
    "/Width mx def\n"           
    "/Height my def\n"
    "/BitsPerComponent 1 def\n"
    "/ImageMatrix [ mx 0 0 my neg 0 my ] def\n"
    "/Decode [ 1 0 ] def\n"
    "end\n"

    "<<\n"
    "/ImageType 3\n"
    "/InterleaveType 2\n"
    "/MaskDict IMD\n"
    "/DataDict IDD\n"
    ">> image GR\n"
    "} bind def\n"


    "\n"
///////////////////////////  path ////////////////////
    "/BFP { newpath moveto }  def\n"
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
    "/SC { scale } bind def\n"
;


////////////////////// end prolog ////////////////////////

//////////////////////  fonts   ////////////////////////////////////

/*
static const char *_fontNames[] = {
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
*/


///////////////////////// Implementations : matrix ////////////////////////////////////////

void Fl_PostScript::concat(){
    double a,b,c,d,x,y;
    fl_matrix(a,b,c,d,x,y);
    fprintf(output,"[%g %g %g %g %g %g] CT\n", a , b , c , d , x , y);
}

void Fl_PostScript::reconcat(){
    double a,b,c,d,x,y;
    fl_matrix(a,b,c,d,x,y);
    fprintf(output, "[%g %g %g %g %g %g] RCT\n" , a , b , c , d , x , y);
}

//////////////// for language level <3 ///////////////////////

void Fl_PostScript::recover(){
    //if (colored_) 
    color(cr_,cg_,cb_);
    //if (line_styled_) 
    line_style(linestyle_,linewidth_,linedash_);
    //if (fonted_) 
    font(font_, size_);
    //colored_=line_styled_=fonted_=0;
};

void Fl_PostScript::reset(){
    gap_=1;
    clip_=0;
    cr_=cg_=cb_=0;
    font_=FL_HELVETICA;
    size_=12;
    linewidth_=0;
    linestyle_=FL_SOLID;
    strcpy(linedash_,Dashes[FL_SOLID]);
    Clip *c=clip_;   ////just not to have memory leaks for badly writen code (forgotten clip popping)
    while(c){
        clip_=clip_->prev;
        delete c;
        c=clip_;
    }
    //colored_=1;
    //line_styled_=1;
    //fonted_=1;
};

FL_API void Fl_PostScript::draw(Fl_Widget * w)
{
    Fl_Device *t = fl_current_dev;
    Fl::flush();
    fl_current_dev = this;
    w->redraw();
    w->draw();
    fl_current_dev = t;
    //w->redraw();
};

///////////////// destructor, finishes postscript, closes FILE  ///////////////

Fl_PostScript::~Fl_PostScript() {
    if(nPages){  // for eps nPages is 0 so it is fine ....
        fprintf(output, "CR\nGR\n GR\nSP\n restore\n");
        fprintf(output, "%%%%Trailer\n");
        fprintf(output, "%%%%Pages: %i\n" , nPages);
    }else
        fprintf(output, "GR\n restore\n");
    reset();
    fclose(output);

    while(clip_){
        Clip * c= clip_;
        clip_= clip_->prev;
        delete c;
    }

}


///////////////// PostScript constructors /////////////////////////////////////


Fl_PostScript::Fl_PostScript(FILE *o, int lang_level, double pw, double ph, int orientation):clip_(0),interpolate_(0){

    lang_level_=lang_level;
    clip_=0;
    output=o;
    mask = 0;
    orientation_=0;
    orientation_=orientation;
    lm_=rm_=bm_=tm_=72;
    pw_ =pw;
    ph_= ph;
    fprintf(output, "%%!PS-Adobe-3.0\n");
    if(lang_level_>1)
        fprintf(output, "%%%%LanguageLevel: %i\n" , lang_level_);
    fprintf(output, "%%%%Pages: (atend)\n");
//	fprintf(output, "%%%%BoundingBox: 0 0 %i %i\n" , w , h);

    if(orientation)
        fprintf(output, "%%%%Orientation: %i\n" , orientation);
    fprintf(output, prolog);
    if(lang_level_>=3){
        fprintf(output, "/CS { clipsave } bind def\n");
        fprintf(output, "/CR { cliprestore } bind def\n");
    }else{
        fprintf(output, "/CS { GS } bind def\n");
        fprintf(output, "/CR { GR } bind def\n");
    }
    fprintf(output, "%%%%EndProlog\n");

    reset();
    nPages=0;

};

/////////////////////////////////////////////////////

Fl_PostScript::Fl_PostScript(FILE *o, int lang_level, int format, int orientation)
:clip_(0),interpolate_(0)
{
    lang_level_=lang_level;
    output=o;
    mask = 0;
    //clip_=0;
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
    fprintf(output, "%%!PS-Adobe-3.0\n");
    if(lang_level_>1)
        fprintf(output, "%%%%LanguageLevel: %i\n" , lang_level_);
    fprintf(output, "%%%%Pages: (atend)\n");

    if(orientation)
        fprintf(output, "%%%%Orientation: %i\n" , orientation);
    fprintf(output, prolog);
    if(lang_level_>=3){
        fprintf(output, "/CS { clipsave } bind def\n");
        fprintf(output, "/CR { cliprestore } bind def\n");
    }else{
        fprintf(output, "/CS { GS } bind def\n");
        fprintf(output, "/CR { GR } bind def\n");
    }
    fprintf(output, "%%%%EndProlog\n");

    reset();
    nPages=0;

};



///////////////////  eps constructor ////////////////////////////////////

Fl_PostScript::Fl_PostScript(FILE *o, int lang_level, double x, double y, double w, double h)
:clip_(0),interpolate_(0)
{
    output=o;
    mask = 0;
    //clip_=0;
    lang_level_=lang_level;
    bg_=FL_GRAY;
    fprintf(output, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    if(lang_level_>1)
        fprintf(output, "%%%%LanguageLevel: %i\n" , lang_level_);
    fprintf(output, "%%%%BoundingBox: %i %i %i %i\n", (int)x , (int)y , (int)(x+w+.999) , (int)(y+h+.999));
    //fprintf(output, "%%%%Orientation: %i\n" , orientation);
    width_ = w;
    height_ = h;
    lm_=x;
    tm_=0;
    rm_=0;
    bm_=y;
    fprintf(output, prolog);
    if(lang_level_>=3){
        fprintf(output, "/CS { clipsave } bind def\n");
        fprintf(output, "/CR { cliprestore } bind def\n");
    }else{
        fprintf(output, "/CS { GS } bind def\n");
        fprintf(output, "/CR { GR } bind def\n");
    }
    fprintf(output, "%%%%EndProlog\n");
    fprintf(output, "save\n");
    fprintf(output, "GS\n");

    reset();
    fprintf(output, "%g %g TR\n", x , y+h);
    fprintf(output, "1 -1  SC\n");
    fprintf(output, "GS\nCS\n");

    nPages=0;  //must be 0 also for eps!

};


////////////////////// paging //////////////////////////////////////////



void Fl_PostScript::page(double pw, double ph, int orientation) {

    if (nPages){
        fprintf(output, "CR\nGR\nGR\nSP\nrestore\n");
    }

    ++nPages;
    fprintf(output, "%%%%Page: %i %i\n" , nPages , nPages);


    pw_=pw;
    ph_=ph;
    width_= pw_ - lm_ - rm_;
    height_= ph_ - tm_ - bm_;
    orientation_=orientation;

    if (orientation_){ 
        fprintf(output, "%%%%PageOrientation: %i\n", orientation);
    }
    reset();
    fprintf(output, "save\n");
    fprintf(output, "GS\n");
    fprintf(output, "%g %g TR\n", lm_ , ph_ - tm_);
    fprintf(output, "1 -1 SC\n");
    fprintf(output, "GS\nCS\n");

};

void Fl_PostScript::page(int format,int orientation){

    orientation_=orientation;
    if(orientation &1){
        ph_=Fl_Printer::page_formats[format][0];
        pw_=Fl_Printer::page_formats[format][1];
    }else{
        pw_=Fl_Printer::page_formats[format][0];
        ph_=Fl_Printer::page_formats[format][1];
    }

    page(pw_,ph_,orientation);
};

void Fl_PostScript::margins(double left, double top, double right, double bottom){
    lm_=left;
    tm_=top;
    rm_=right;
    bm_=bottom;
    width_= pw_ - lm_ - rm_;
    height_ =  ph_ - tm_ - bm_;
    if(nPages){
        fprintf(output, "CR\nGR\nGR\nGS\n");
        fprintf(output, "%g %g TR\n", lm_ , ph_ - tm_);
        fprintf(output, "1 -1 SC\n");
        fprintf(output, "GS\nCS\n");
    }
};


void Fl_PostScript::fit(double x, double y, double w, double h, int align){
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

    fprintf(output, "CR\nGR\nGS\n");
    reset();
    fprintf(output, "%g %g TR\n", -x*s+dx , -y*s+dy);
    fprintf(output, "%g %g SC\nCS\n", s , s );


};


void Fl_PostScript::fit(double x, double y, double w, double h, double dpi, int align){

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

    fprintf(output, "CR\nGR\nGS\n");
    reset();
    fprintf(output, "%g %g TR\n", -x*s+dx , -y*s+dy);
    fprintf(output, "%g %g SC\nCS\n", s , s );
};

void Fl_PostScript::place(double x, double y, double w, double h, double tx, double ty, double tw, double th,  int align){

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

    fprintf(output, "CR\nGR\nGS\n");
    reset();
    fprintf(output, "%g %g TR\n", -x*s+tx+dx , -y*s+ty+dy);
    fprintf(output, "%g %g SC\nCS\n", s , s );
};



void Fl_PostScript::place(double x, double y, double w, double h, double tx, double ty, double tw, double th, double dpi, int align){

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

    fprintf(output, "CR\nGR\nGS\nCS\n");
    reset();
    fprintf(output, "%g %g TR\n", -x+tx+dx , -y+ty+dy);
    fprintf(output, "%g %g SC\n", s , s );
};








//////////////////////////////  setting background for alpha /////////////////////////////////

void Fl_PostScript::bg_color(Fl_Color bg){bg_=bg;};

//////////////////////////////// Primitives: Colors  ////////////////////////////////////////////

void Fl_PostScript::color(Fl_Color c) {
    //colored_=1;
    color_=c;
    //Fl::get_color(c, cr_, cg_, cb_);
    fl_get_color(c, cr_, cg_, cb_);

    if (cr_==cg_ && cg_==cb_) {
        double gray = cr_/255.0;
        fprintf(output, "%g GL\n", gray);
    } else {
        double fr, fg, fb;
        fr = cr_/255.0;
        fg = cg_/255.0;
        fb = cb_/255.0;
        fprintf(output,"%g %g %g SRGB\n", fr , fg , fb);
    }
}

void Fl_PostScript::color(unsigned char r, unsigned char g, unsigned char b) {

    //colored_=1;
    cr_=r;cg_=g;cb_=b;
    if (r==g && g==b) {
        double gray = r/255.0;
        fprintf(output, "%g GL\n", gray);
    } else {
        double fr, fg, fb;
        fr = r/255.0;
        fg = g/255.0;
        fb = b/255.0;
        fprintf(output, "%g %g %g SRGB\n", fr , fg , fb);
    }
}

/////////////////////////////   Clipping /////////////////////////////////////////////

void Fl_PostScript::push_clip(int x, int y, int w, int h) 
{
    Clip * c=new Clip();
    clip_box(x,y,w,h,c->x,c->y,c->w,c->h);
    c->prev=clip_;
    clip_=c;
    fprintf(output, "CR\nCS\n");
    if(lang_level_<3)
        recover();
    fprintf(output, "%i %i %i %i CL\n", clip_->x , clip_->y , clip_->w  , clip_->h);
}

void Fl_PostScript::push_no_clip() {
    Clip * c = new Clip();
    c->prev=clip_;
    clip_=c;
    clip_->x = clip_->y = clip_->w = clip_->h = -1;
    fprintf(output, "CR\nCS\n");
    if(lang_level_<3)
        recover();
}

void Fl_PostScript::pop_clip() {
    if(!clip_)return;
    Clip * c=clip_;
    clip_=clip_->prev;
    delete c;
    fprintf(output, "CR\nCS\n");
    if(clip_ && clip_->w >0) 
        fprintf(output, "%g %g %i %i CL\n", clip_->x - 0.5, clip_->y - 0.5, clip_->w  , clip_->h);
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
};

int Fl_PostScript::not_clipped(int x, int y, int w, int h)
{
    if(!clip_) return 1;
    if(clip_->w < 0) return 1;
    int X, Y, W, H;
    clip_box(x, y, w, h, X, Y, W, H);
    if(W) return 1;
    return 0;
};

void Fl_PostScript::clip_out(int x, int y, int w, int h)
{
    puts("Not implemented clip out.");
}

const char* Fl_PostScript::encoding()
{
    puts("Not implemented encoding.");
    return 0;
}

void Fl_PostScript::point(int, int)
{
    puts("Not implemented point.");
}

void Fl_PostScript::rtl_draw(char const*, int, float, float)
{
    puts("Not implemented rtl draw.");
}




/*
int Fl_PostScript::clip_box(int x, int y, int w, int h, int& X, int& Y, int& W, int& H){
    double _x, _y, _w, _h;
    int ret = clip_box(x, y, w, h, _x, _y, _w, _h);
    X=(int)(_x+.5);
    Y=(int)(_y+.5);
    W=(int)(_w+.5);
    H=(int)(_h+.5);
    return ret;
};
*/
///////////////////////////////// rect  /////////////////////////////////////////

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

void Fl_PostScript::rectf(int x, int y, int w, int h, uchar r, uchar g, uchar b) 
{
    fprintf(output, "GS\n");
    double fr = r/255.0;
    double fg = g/255.0;
    double fb = b/255.0;
    fprintf(output, "%g %g %g SRGB\n",fr , fg , fb);
    fprintf(output, "%i %i %i %i FR\n", x , y , w  , h );
    fprintf(output, "GR\n");
}

///////////////////////////////// lines  /////////////////////////////////////////

void Fl_PostScript::line(int x1, int y1, int x2, int y2) 
{
    fprintf(output, "GS\n");
    fprintf(output, "%i %i %i %i L\n", x1 , y1, x2 ,y2);
    fprintf(output, "GR\n");
}

/*
void Fl_PostScript::line(int x0, int y0, int x1, int y1, int x2, int y2) {
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x0 , y0);
    fprintf(output, "%i %i LT\n", x1 , y1);
    fprintf(output, "%i %i LT\n", x2 , y2);
    fprintf(output, "ELP\n");
    fprintf(output, "GR\n");
}

void Fl_PostScript::loop(int x0, int y0, int x1, int y1, int x2, int y2) {
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x0 , y0);
    fprintf(output, "%i %i LT\n", x1 , y1);
    fprintf(output, "%i %i LT\n", x2 , y2);
    fprintf(output, "ECP\n");
    fprintf(output, "GR\n");
}

void Fl_PostScript::loop(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x0 , y0);
    fprintf(output, "%i %i LT\n", x1 , y1);
    fprintf(output, "%i %i LT\n", x2 , y2);
    fprintf(output, "%i %i LT\n", x3 , y3);
    fprintf(output, "ECP\n");
    fprintf(output, "GR\n");
}

void Fl_PostScript::polygon(int x0, int y0, int x1, int y1, int x2, int y2) {
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x0 , y0);
    fprintf(output,"%i %i LT\n", x1 , y1);
    fprintf(output, "%i %i LT\n", x2 , y2);
    fprintf(output, "EFP\n");
    fprintf(output, "GR\n");
}

void Fl_PostScript::polygon(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x0 , y0 );
    fprintf(output, "%i %i LT\n", x1 , y1 );
    fprintf(output, "%i %i LT\n", x2 , y2 );
    fprintf(output, "%i %i LT\n", x3 , y3 );
    fprintf(output, "EFP\n");
    fprintf(output, "GR\n");
}

void Fl_PostScript::xyline(int x, int y, int x1, int y2, int x3){
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x , y );
    fprintf(output, "%i %i LT\n", x1 , y );
    fprintf(output, "%i %i LT\n", x1 , y2);
    fprintf(output,"%i %i LT\n", x3 , y2);
    fprintf(output, "ELP\n");
    fprintf(output, "GR\n");
};

void Fl_PostScript::xyline(int x, int y, int x1, int y2){
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x , y);
    fprintf(output,"%i %i LT\n", x1 , y);
    fprintf(output, "%i %i LT\n", x1 , y2 );
    fprintf(output, "ELP\n");
    fprintf(output, "GR\n");
};

void Fl_PostScript::xyline(int x, int y, int x1){
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x , y);
    fprintf(output, "%i %i LT\n", x1 , y );
    fprintf(output, "ELP\n");
    fprintf(output, "GR\n");
};

void Fl_PostScript::yxline(int x, int y, int y1, int x2, int y3){
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output,"%i %i MT\n", x , y);
    fprintf(output, "%i %i LT\n", x , y1 );
    fprintf(output, "%i %i LT\n", x2 , y1 );
    fprintf(output , "%i %i LT\n", x2 , y3);
    fprintf(output, "ELP\n");
    fprintf(output, "GR\n");
};

void Fl_PostScript::yxline(int x, int y, int y1, int x2){
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x , y);
    fprintf(output, "%i %i LT\n", x , y1);
    fprintf(output, "%i %i LT\n", x2 , y1);
    fprintf(output, "ELP\n");
    fprintf(output, "GR\n");
};

void Fl_PostScript::yxline(int x, int y, int y1){
    fprintf(output, "GS\n");
    fprintf(output,"BP\n");
    fprintf(output, "%i %i MT\n", x , y);
    fprintf(output, "%i %i LT\n", x , y1);
    fprintf(output, "ELP\n");
    fprintf(output, "GR\n");
};

*/


void Fl_PostScript::arc(float x, float y, float w, float h, float a1, float a2) 
{
    fprintf(output, "GS\n");
    fprintf(output, "BP\n");
    fprintf(output, "%g %g TR\n", x + w/2.0 , y + h/2.0);
    fprintf(output, "%g %g SC\n", w/2.0 , h/2.0 );
    fprintf(output, "0 0 1 %g %g arcn\n" , -a1 , -a2);
    fprintf(output, "%g setlinewidth\n",  2/sqrt(w*h));
    fprintf(output, "ELP\n");
//	fprintf(output, 2.0/w , 2.0/w , " SC\n";
//	fprintf(output, (-x - w/2.0) , (-y - h/2)  , " TR\n";
    fprintf(output, "GR\n");
}

void Fl_PostScript::pie(int x, int y, int w, int h, float a1, float a2) {

    fprintf(output, "GS\n");
    fprintf(output, "%g %g TR\n", x + w/2.0 , y + h/2.0);
    fprintf(output, "%g %g SC\n", w/2.0 , h/2.0 );
#ifndef __BORLANDC__
#warning begin polygon	and arc todo
#endif
//	begin_polygon();
//	arc(0.0, 0.0, 1, a1, a2);
//	end_polygon();
    fprintf(output, "GR\n");

}

void Fl_PostScript::ellipse(float x, float y, float w, float h)
{
    puts("Not implemented Fl_PostScript::ellipse.");
}

void Fl_PostScript::points()
{
    puts("Not implemented Fl_PostScript::points");
}

void Fl_PostScript::stroke()
{
    puts("Not implemented Fl_PostScript::stroke.");
}

void Fl_PostScript::fill()
{
    puts("Not implemented Fl_PostScript::fill.");
}

void Fl_PostScript::fill_stroke(Fl_Color)
{
    puts("Not implemented Fl_PostScript::fill_stroke.");
}

void Fl_PostScript::newpath()
{
    puts("Not implemented Fl_PostScript::newpath.");
}

void Fl_PostScript::vertex(float x, float y)
{
    puts("Not implemented Fl_PostScript::vertex.");
}

void Fl_PostScript::vertex(int x, int y)
{
    puts("Not implemented Fl_PostScript::vertex.");
}

void Fl_PostScript::vertices(int n, const float v[][2])
{
    puts("Not implemented Fl_PostScript::vertices.");
}

void Fl_PostScript::vertices(int n, const int v[][2])
{
    puts("Not implemented Fl_PostScript::vertices.");
}

void Fl_PostScript::transformed_vertices(int n, const float v[][2])
{
    puts("Not implemented Fl_PostScript::transformed_vertices.");
}

void Fl_PostScript::closepath()
{
    puts("Not implemented Fl_PostScript::closepath.");
}

/////////////////  transformed (double) drawings ////////////////////////////////


/*
void Fl_PostScript::begin_points(){
    fprintf(output, "GS\n");
    concat();
    fprintf(output, "BP\n");
    gap_=1;
    shape_=POINTS;
};

void Fl_PostScript::begin_line(){
    fprintf(output, "GS\n");
    concat();
    fprintf(output, "BP\n");
    gap_=1;
    shape_=LINE;
};

void Fl_PostScript::begin_loop(){
    fprintf(output, "GS\n");
    concat();
    fprintf(output, "BP\n");
    gap_=1;
    shape_=LOOP;
};

void Fl_PostScript::begin_polygon(){
    fprintf(output, "GS\n");
    concat();
    fprintf(output, "BP\n");
    gap_=1;
    shape_=POLYGON;
};

void Fl_PostScript::vertex(double x, double y){
    if(shape_==POINTS){
        fprintf(output,"%g %g MT\n", x , y);
        gap_=1;
        return;
    }
    if(gap_){
        fprintf(output,"%g %g MT\n", x , y);
        gap_=0;
    }else
        fprintf(output, "%g %g LT\n", x , y);
};

*/

void Fl_PostScript::curve(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3)
{
    if(shape_==NONE) return;
    if(gap_)
        fprintf(output,"%g %g MT\n", x , y);
    else
        fprintf(output, "%g %g LT\n", x , y);
    gap_=0;

    fprintf(output, "%g %g %g %g %g %g curveto \n", x1 , y1 , x2 , y2 , x3 , y3);
};


void Fl_PostScript::circle(float x, float y, float r)
{
    if(shape_==NONE){
        fprintf(output, "GS\n");
        concat();
//		fprintf(output, "BP\n");
        fprintf(output,"%g %g %g 0 360 arc\n", x , y , r);
        reconcat();
//		fprintf(output, "ELP\n");
        fprintf(output, "GR\n");
    }else

        fprintf(output, "%g %g %g 0 360 arc\n", x , y , r);

};



/*
void Fl_PostScript::arc(double x, double y, double r, double start, double a){
    if(shape_==NONE) return;
    gap_=0;
    fprintf(output, "%g %g %g %g %g arc\n", x , y , r , -start , -a);

};

void Fl_PostScript::end_points(){
    gap_=1;
    reconcat();
    fprintf(output, "ELP\n"); //??
    fprintf(output, "GR\n");
    shape_=NONE;
}

void Fl_PostScript::end_line(){
    gap_=1;
    reconcat();
    fprintf(output, "ELP\n");
    fprintf(output, "GR\n");
    shape_=NONE;
}
void Fl_PostScript::end_loop(){
    gap_=1;
    reconcat();
    fprintf(output, "ECP\n");
    fprintf(output, "GR\n");
    shape_=NONE;
}

void Fl_PostScript::end_polygon(){
    gap_=1;
    reconcat();
    fprintf(output, "EFP\n");
    fprintf(output, "GR\n");
    shape_=NONE;
}

void Fl_PostScript::transformed_vertex(double x, double y){
    reconcat();
    if(gap_){
        fprintf(output, "%g %g MT\n", x , y);
        gap_=0;
    }else
        fprintf(output, "%g %g LT\n", x , y);
    concat();
};

*/

///////////////////////// misc ////////////////////////////////////////////

void Fl_PostScript::font(Fl_Font f, float s) 
{

    //fonted_=1;
    //if (f >= FL_FREE_FONT)
    //	f = FL_COURIER;
    //fprintf(output, "/%s SF\n" , _fontNames[f]);
    fprintf(output, "/%s SF\n" , f->name());
    fprintf(output,"%i FS\n", int(s));
    fl_fltk_dev.font(f, s); //Dirty hack for font measurement ;-(
    font_=f; size_=s;
};

void Fl_PostScript::font(const char* s, float size)
{
}

void Fl_PostScript::font(const char* s, int attributes, float size)
{
}

void  Fl_PostScript::encoding(const char*)
{
}

const char* Fl_PostScript::fontname(Fl_Font, int *i)
{
    return 0;
}


void Fl_PostScript::line_style(int style, int width, char* dashes){
    //line_styled_=1;
    if(!width)
        width=1; //for screen drawing compatability
    linewidth_=width;
    linestyle_=style;
    fprintf(output, "%i setlinewidth\n", width);
    if(!dashes)
        dashes=Dashes[style&0xff];
    strcpy(linedash_,dashes);
    fprintf(output, "[");
    while(*dashes){
        fprintf(output, "%i ",(int)(*dashes));
        dashes++;
    }
    fprintf(output, "] 0 setdash\n");
    style>>=8;
    if(int i=style&0xf)
        fprintf(output,"%i setlinecap\n", i-1);
    else
        fprintf(output, "1 setlinecap\n"); //standard cap

    style>>=4;
    if(int i=style&0xf)
        fprintf(output, "%i setlinejoin\n", style&0xf-1) ;
    else
        fprintf(output, "1 setlinejoin\n");
};

float Fl_PostScript::width(const char* s)
{
    return fl_fltk_dev.width(s); //Dirty...
}

float Fl_PostScript::width(const Fl_String& s)
{
    return fl_fltk_dev.width(s.c_str());
}

float Fl_PostScript::width(unsigned int unc)
{
    puts("Not implemented");
    return fl_fltk_dev.width(unc); 
}


/*float Fl_PostScript::width(uchar c)
{
    return fl_fltk_dev.width(c); //Dirty...
}
*/

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

void rtl_draw(const char *s, int n, float x, float y)
{
    puts("rtl draw unimplemented.");
}

///////////////////////////////  text ////////////////////////////////////

void Fl_PostScript::transformed_draw(const char* str, int n, float x, float y){

    if (!n||!str||!*str)return;
    fprintf(output, "GS\n");
    fprintf(output,"%g %g moveto\n", x , y);
    fprintf(output, "[1 0 0 -1 0 0] concat\n");
    int i=1;
    fprintf(output, "\n(");
    for(int j=0;j<n;j++){
        if(i>240){
            fprintf(output, "\\\n");
            i=0;
        }
        i++;
        switch (*str) {
            case '(': case ')':
                fprintf(output, "\\%c" , *str);
                break;
            default:
                fprintf(output, "%c", *str);
        }
        str++;
    }
    fprintf(output, ") show\n");
    fprintf(output, "GR\n");
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

    fprintf(output,"save\n");

    char * interpol;
    if(lang_level_>1){
        if(interpolate_)
            interpol="true";
        else
            interpol="false";
        if(mask && lang_level_>2)
            fprintf(output, "%g %g %g %g %i %i %i %i %s CIM\n", x , y+h , w , -h , iw , ih, mx, my, interpol);
        else
            fprintf(output, "%g %g %g %g %i %i %s CII\n", x , y+h , w , -h , iw , ih, interpol);
    }else
        fprintf(output , "%g %g %g %g %i %i CI", x , y+h , w , -h , iw , ih);


    if(!LD) LD = iw*D;
    uchar *curmask=mask;
    uchar bg_r, bg_g, bg_b;
    fl_get_color(bg_, bg_r,bg_g,bg_b);
    for (j=0; j<ih;j++){
        if(mask){
            for(k=0;k<my/ih;k++){
                for (i=0; i<((mx+7)/8);i++){
                    if (!(i%80)) fprintf(output, "\n");
                    fprintf(output, "%.2x",swap_byte(*curmask));
                    curmask++;
                }
                fprintf(output,"\n");
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
            if (!(i%40)) fprintf(output, "\n");
            fprintf(output, "%.2x%.2x%.2x", r, g, b);
            curdata +=D;
        }
        fprintf(output,"\n");

    }

    fprintf(output," >\nrestore\n" );
};

void Fl_PostScript::draw_scalled_image(Fl_Draw_Image_Cb call, void *data, double x, double y, double w, double h, int iw, int ih, int D) 
{
    fprintf(output,"save\n");
    int i,j,k;
    char * interpol;
    if(lang_level_>1){
        if(interpolate_) interpol="true";
        else interpol="false";
        if(mask && lang_level_>2)
            fprintf(output, "%g %g %g %g %i %i %i %i %s CIM\n", x , y+h , w , -h , iw , ih, mx, my, interpol);
        else
            fprintf(output, "%g %g %g %g %i %i %s CII\n", x , y+h , w , -h , iw , ih, interpol);
    }else
        fprintf(output , "%g %g %g %g %i %i CI", x , y+h , w , -h , iw , ih);

    int LD=iw*D;
    uchar *rgbdata=new uchar[LD];
    uchar *curmask=mask;

    for (j=0; j<ih;j++){
        if(mask && lang_level_>2){  // InterleaveType 2 mask data
            for(k=0; k<my/ih;k++){ //for alpha pseudo-masking
                for (i=0; i<((mx+7)/8);i++){
                    if (!(i%40)) fprintf(output, "\n");
                    fprintf(output, "%.2x",swap_byte(*curmask));
                    curmask++;
                }
                fprintf(output,"\n");
            }
        }
        call(data,0,j,iw,rgbdata);
        uchar *curdata=rgbdata;
        for(i=0 ; i<iw ; i++) {
            uchar r = curdata[0];
            uchar g =  curdata[1];
            uchar b =  curdata[2];

            if (!(i%40)) fprintf(output, "\n");
            fprintf(output, "%.2x%.2x%.2x", r, g, b);

            curdata +=D;
        }
        fprintf(output,"\n");

    }
    fprintf(output,">\n");


    fprintf(output,"restore\n");
    delete[] rgbdata;
}

void Fl_PostScript::draw_scalled_image_mono(const uchar *data, double x, double y, double w, double h, int iw, int ih, int D, int LD) 
{
    fprintf(output,"save\n");

    int i,j, k;

    char * interpol;
    if(lang_level_>1){
        if(interpolate_)
            interpol="true";
        else
            interpol="false";
        if(mask && lang_level_>2)
            fprintf(output, "%g %g %g %g %i %i %i %i %s GIM\n", x , y+h , w , -h , iw , ih, mx, my, interpol);
        else
            fprintf(output, "%g %g %g %g %i %i %s GII\n", x , y+h , w , -h , iw , ih, interpol);
    }else
        fprintf(output , "%g %g %g %g %i %i GI", x , y+h , w , -h , iw , ih);


    if(!LD) LD = iw*D;

    uchar bg_r, bg_g, bg_b;
    fl_get_color(bg_, bg_r,bg_g,bg_b);
    int bg = (bg_r + bg_g + bg_b)/3;

    uchar *curmask=mask;
    for (j=0; j<ih;j++){
        if(mask){
            for(k=0;k<my/ih;k++){
                for (i=0; i<((mx+7)/8);i++){
                    if (!(i%80)) fprintf(output, "\n");
                    fprintf(output, "%.2x",swap_byte(*curmask));
                    curmask++;
                }
                fprintf(output,"\n");
            }
        }
        const uchar *curdata=data+j*LD;
        for(i=0 ; i<iw ; i++) {
            if (!(i%80)) fprintf(output, "\n");
            uchar r = curdata[0];
            if(lang_level_<3 && D>1) { //can do  mixing
                unsigned int a2 = curdata[1]; //must be int 
                unsigned int a = 255-a2;
                r = (a2 * r + bg * a)/255;
            }
            if (!(i%120)) fprintf(output, "\n");
            fprintf(output, "%.2x", r);
            curdata +=D;
        }
        fprintf(output,"\n");

    }

    fprintf(output," >\nrestore\n" );
};


void Fl_PostScript::draw_scalled_image_mono(Fl_Draw_Image_Cb call, void *data, double x, double y, double w, double h, int iw, int ih, int D) 
{
    fprintf(output,"save\n");
    int i,j,k;
    char * interpol;
    if(lang_level_>1){
        if(interpolate_) interpol="true";
        else interpol="false";
        if(mask && lang_level_>2)
            fprintf(output, "%g %g %g %g %i %i %i %i %s GIM\n", x , y+h , w , -h , iw , ih, mx, my, interpol);
        else
            fprintf(output, "%g %g %g %g %i %i %s GII\n", x , y+h , w , -h , iw , ih, interpol);
    }else
        fprintf(output , "%g %g %g %g %i %i GI", x , y+h , w , -h , iw , ih);

    int LD=iw*D;
    uchar *rgbdata=new uchar[LD];
    uchar *curmask=mask;
    for (j=0; j<ih;j++){
        if(mask && lang_level_>2){  // InterleaveType 2 mask data
            for(k=0; k<my/ih;k++){ //for alpha pseudo-masking
                for (i=0; i<((mx+7)/8);i++){
                    if (!(i%40)) fprintf(output, "\n");
                    fprintf(output, "%.2x",swap_byte(*curmask));
                    curmask++;
                }
                fprintf(output,"\n");
            }
        }
        call(data,0,j,iw,rgbdata);
        uchar *curdata=rgbdata;
        for(i=0 ; i<iw ; i++) {
            uchar r = curdata[0];
            if (!(i%120)) fprintf(output, "\n");
            fprintf(output, "%.2x", r);
            curdata +=D;
        }
        fprintf(output,"\n");
    }
    fprintf(output,">\n");
    fprintf(output,"restore\n");
    delete[] rgbdata;
}


////////////////////////////// Image classes //////////////////////

/*
int Fl_PostScript::alpha_mask(const uchar * data, int w, int h, int D, int LD){
    mask = 0;
    if((D/2)*2 != D){ //no mask info
        return 0;
    }
    int xx;
    int i,j, k, l; 
    LD += w*D;
    int V255=0;
    int V0 =0;
    int V_=0;
//	uchar d;
    for(j=0;j<h;j++){
        for(i=0;i<w;i++)
            switch(data[j*LD+D*i+D-1]){
                case 255: V255 = 1; break;
                case 0: V0 = 1; break;
                default: V_= 1;
            }
        if(V_) break;
    };
    if(!V_){
        if(V0)
            if(V255){// not true alpha, only masking
                xx = (w+7)/8;
                mask = new uchar[h * xx];
                for(i=0;i<h * xx;i++) mask[i]=0;
                for(j=0;j<h;j++)
                    for(i=0;i<w;i++)
                        if(data[j*LD+D*i+D-1])
                            mask[j*xx+i/8] |= 1 << (i % 8);
                mx = w;
                my = h; //mask imensions
                return 0;
            }else{
                mask=0;
                return 1; //everything masked
            }
        else
            return 0;
    }



    /////   Alpha dither, generating (4*w) * 4 mask area       /////
    /////         with Floyd-Steinberg error diffusion         /////

    mask = new uchar[((w+1)/2) * h * 4];

    for(i=0;i<((w+1)/2) * h * 4; i++) mask[i] = 0; //cleaning


    mx= w*4;
    my=h*4; // mask dimensions

    xx = (w+1)/2;                //  mask line width in bytes

    short * errors1 = new short [w*4+2]; //  two rows of dither errors
    short * errors2 = new short [w*4+2]; //  two rows of dither errors

    for(i=0;i<w*4+2;i++) errors2[i] = 0; // cleaning,after first swap will become current
    for(i=0;i<w*4+2;i++) errors1[i] = 0; // cleaning,after first swap will become current

    short * current = errors1;
    short * next = errors2;
    short * swap;

    for(j=0;j<h;j++){
        for(l=0;l<4;){           // generating 4 rows of mask lines for 1 RGB line
            int jj = j*4+l;	

            /// mask row index
            swap = next;
            next = current;
            current = swap;
            *(next+1) = 0;          // must clean the first cell, next are overriden by *1
            for(i=0;i<w;i++){
                for(k=0;k<4;k++){   // generating 4 x-pixels for 1 RGB
                    short error, o1, o2, o3;
                    int ii = i*4+k;   // mask cell index
                    short val = data[j*LD+D*i+D-1] + current[1+ii];
                    if (val>127){
                        mask[jj*xx+ii/8]  |= 1 << (ii % 8); //set mask bit
                        error =  val-255;
                    }else
                        error = val;

                    ////// error spreading /////
                    if(error >0){
                        next[ii] +=  o1 = (error * 3 + 8)/16;
                        current[ii+2] += o2 = (error * 7 + 8)/16;
                        next[ii+2] = o3 =(error + 8)/16;  // *1 - ok replacing (cleaning)
                    }else{
                        next[ii] += o1 = (error * 3 - 8)/16;
                        current[ii+2] += o2 = (error * 7 - 8)/16;
                        next[ii+2] = o3 = (error - 8)/16; 
                    }
                    next[1+ii] += error - o1 - o2 - o3;
                }
            }
            l++;

            ////// backward

            jj = j*4+l;	
            swap = next;
            next = current;
            current = swap;
            *(next+1) = 0;          // must clean the first cell, next are overriden by *1
            for(i=w-1;i>=0;i--){
                for(k=3;k>=0;k--){   // generating 4 x-pixels for 1 RGB
                    short error, o1, o2, o3;
                    int ii = i*4+k;   // mask cell index
                    short val = data[j*LD+D*i+D-1] + current[1+ii];
                    if (val>127){
                        mask[jj*xx+ii/8]  |= 1 << (ii % 8); //set mask bit
                        error =  val-255;
                    }else
                        error = val;

                    ////// error spreading /////
                    if(error >0){
                        next[ii+2] +=  o1 = (error * 3 + 8)/16;
                        current[ii] += o2 = (error * 7 + 8)/16;
                        next[ii] = o3 =(error + 8)/16;  // *1 - ok replacing (cleaning)
                    }else{
                        next[ii+2] += o1 = (error * 3 - 8)/16;
                        current[ii] += o2 = (error * 7 - 8)/16;
                        next[ii] = o3 = (error - 8)/16; 
                    }
                    next[1+ii] += error - o1 - o2 - o3;
                }
            }
            l++;
        }
    }
    delete[] errors1;
    delete[] errors2;
    return 0;
}

*/


//void Fl_PostScript::draw_Pixmap(Fl_Pixmap * pxm,int XP, int YP, int WP, int HP, int cx, int cy){
    //const char * const * di = pxm->data();
/*	const char * const * di = pxm->data;
    int w,h;
    if (!fl_measure_pixmap(di, w, h)) return;
    mask=0;
    fl_mask_bitmap=&mask;
    mx = WP;
    my = HP;
    push_clip(XP, YP, WP, HP);
    fl_draw_pixmap(di,XP -cx, YP -cy, bg_); //yes, it is dirty, but fl is dispatched, so it works!
    pop_clip();
    delete[] mask;
    mask=0;
    fl_mask_bitmap=0;
*/
//};

/*
void Fl_PostScript::draw_RGB(Fl_RGB_Image * rgb,int XP, int YP, int WP, int HP, int cx, int cy){
    const uchar  * di = rgb->array;
    int w = rgb->w();
    int h = rgb->h();
    mask=0;
    if(lang_level_>2) //when not true, not making alphamask, mixing colors instead...
        if (alpha_mask(di, w, h, rgb->d(),rgb->ld())) return; //everthing masked, no need for painting!
    push_clip(XP, YP, WP, HP);
    draw_scalled_image(di, XP + cx, YP + cy, w, h,  w,  h, rgb->d(), rgb->ld()); 
    pop_clip();
    delete[]mask;
    mask=0;
};
*/

//void Fl_PostScript::draw_Bitmap(Fl_Bitmap * bitmap,int XP, int YP, int WP, int HP, int cx, int cy){
/*	const uchar  * di = bitmap->array;
    int w,h;
    int LD=(bitmap->w()+7)/8;
    int xx;

    if (WP> bitmap->w() - cx){// to assure that it does not go out of bounds;
         w = bitmap->w() - cx;
         xx = (bitmap->w()+7)/8 - cx/8;
    }else{
        w =WP;
        xx = (w+7)/8 - cx/8;
    }
    if( HP > bitmap->h()-cy)
        h = bitmap->h() - cy;
    else
        h = HP;

    di += cy*LD + cx/8;
    int si = cx % 8; // small shift to be clipped

    int i,j;
    push_clip(XP, YP, WP, HP);
    fprintf(output , "%i %i %i %i %i %i MI", XP - si, YP + HP , WP , -HP , w , h);

    for (j=0; j<HP; j++){
        for (i=0; i<xx; i++){
            if (!(i%80)) fprintf(output, "\n");
            fprintf(output, "%.2x",swap_byte(~(*di)));
            di++;
        }
        fprintf(output,"\n");
    }
    fprintf(output,">\n");
    pop_clip();
*/
//};



