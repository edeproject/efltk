#include <efltk/Fl_MDI_Window.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Item.h>

#include <string.h>

#ifndef _WIN32

# include <unistd.h>
# ifndef max
#  define max(a,b) (a) > (b) ? (a) : (b)
# endif

#else

# include <windows.h>
# include <winsock.h>
// DOOH! Is this lame or what? :) Trying to avoid windows draw too fast...
# define XFlush(a) Sleep(1)

#endif

static int px,py,pw,ph;
#ifdef _WIN32
 static int old_f;
#else
 static GC invertGc=0, saved;
#endif

void set_overlay_func() {
#ifdef _WIN32
	old_f = SetROP2(fl_gc, R2_NOT);
#else
    if(!invertGc) {
        XGCValues v;
        v.subwindow_mode = IncludeInferiors;
        v.foreground = 0xffffffff;
        v.function = GXxor;
        v.line_width = 2;
        v.graphics_exposures = False;
        int mask = GCForeground|GCSubwindowMode|GCFunction|GCLineWidth|GCGraphicsExposures;
        invertGc = XCreateGC(fl_display, RootWindow(fl_display, fl_screen), mask, &v);
    }
    saved=fl_gc;
    fl_gc=invertGc;
#endif
}
void set_def_func() {
#ifdef _WIN32
    SetROP2(fl_gc, old_f);
#else
    fl_gc=saved;
#endif
}
static void draw_current_rect() {
    fl_rect(px, py, pw, ph);
}
void overlay_clear() { if (pw > 0) { draw_current_rect(); pw = 0; } }
void overlay_rect(int x, int y, int w, int h) {
    set_overlay_func();
    fl_transform(x,y);
    if (w < 0) {x += w; w = -w;} else if (!w) w = 1;
    if (h < 0) {y += h; h = -h;} else if (!h) h = 1;
    if (pw > 0) {
        if (x==px && y==py && w==pw && h==ph) return;
        draw_current_rect();
    }
    px = x; py = y; pw = w; ph = h;
    draw_current_rect();
    set_def_func();
}

static void closeMdiWin(Fl_Widget *, void *d) {
	((Fl_MDI_Window*)d)->do_callback();	
}

static void maxMdiWin(Fl_Widget *, void *d)
{
    Fl_MDI_Window *w = (Fl_MDI_Window*)d;
    if(w->maximized())
        w->maximize(false);
    else
        w->maximize(true);
}

static void minMdiWin(Fl_Widget *, void *d)
{
    Fl_MDI_Window *w = (Fl_MDI_Window*)d;
    if(w->minimized())
        w->minimize(false);
    else
        w->minimize(true);
}

// Min/Max/Close button symbols drawing stuff:
extern int fl_add_symbol(const char *name, void (*drawit)(Fl_Color), int scalable);
#define vv(x,y) fl_vertex(x,y)
#define CL_OF .6f
void draw_cl(Fl_Color col)
{			
	fl_color(col);
	
	fl_vertex(-CL_OF,-CL_OF);
	fl_vertex(CL_OF, CL_OF);
	fl_stroke();
	fl_closepath();

	fl_vertex(CL_OF,-CL_OF);
	fl_vertex(-CL_OF, CL_OF);
	fl_stroke();
	fl_closepath();	
}

#define MAX_OF .6f
void draw_max(Fl_Color col)
{			
	fl_color(col);
	
	vv(-MAX_OF,-MAX_OF+0.2f); 
	vv(MAX_OF,-MAX_OF+0.2f); 
	fl_stroke();
	fl_closepath();
	
	vv(-MAX_OF, -MAX_OF); 
	vv(MAX_OF, -MAX_OF); 
	fl_stroke();
	fl_closepath();

	
	vv(MAX_OF,-MAX_OF); 
	vv(MAX_OF,MAX_OF); 
	vv(-MAX_OF,MAX_OF); 
	vv(-MAX_OF,-MAX_OF); 
	fl_stroke();
	fl_closepath();
}

#define MIN_OF .6f
#define MIN_OF2 .5f
void draw_min(Fl_Color col)
{			
	fl_color(col);
	
	vv(MIN_OF2, MIN_OF);
	vv(-MIN_OF2, MIN_OF);
	fl_stroke();
	fl_closepath();

	vv(MIN_OF2, MIN_OF-0.1f);
	vv(-MIN_OF2, MIN_OF-0.1f);
	fl_stroke();
	fl_closepath();
}

static void title_revert(Fl_Style* s) {
    s->box = FL_HOR_SHADE_FLAT_BOX;
    s->button_box  = FL_THIN_UP_BOX;
    s->label_color = FL_WHITE;
    s->label_font  = FL_HELVETICA_BOLD;
    s->color       = fl_rgb(0,0,200);
}
static Fl_Named_Style title_style("MDI_Titlebar", title_revert, &Fl_MDI_Titlebar::default_style);
Fl_Named_Style* Fl_MDI_Titlebar::default_style = &::title_style;

Fl_MDI_Titlebar::Fl_MDI_Titlebar(int x,int y,int w,int h,const char *l)
    : Fl_Group(x,y,w,h,l),_close(0,0,0,0),_max(0,0,0,0),_min(0,0,0,0)
{
    style(default_style);

    _owner = (Fl_MDI_Window *)parent();

    fl_add_symbol("xx", draw_cl, 1);
    fl_add_symbol("mx", draw_max, 1);
    fl_add_symbol("mi", draw_min, 1);

    _close.label_type(FL_SYMBOL_LABEL);
    _close.label("@xx");
    _close.box(button_box());
    _close.callback(closeMdiWin, _owner);
	//_close.connect(_owner, &Fl_Widget::do_callback, (void*)0);

    _max.label_type(FL_SYMBOL_LABEL);
    _max.label("@mx");
    _max.box(button_box());
    _max.callback(maxMdiWin, _owner);

    _min.label_type(FL_SYMBOL_LABEL);
    _min.label("@mi");
    _min.box(button_box());
    _min.callback(minMdiWin, _owner);

    _close.show();
    _min.show();
    _max.show();

    _close.clear_click_to_focus();
    _min.clear_click_to_focus();
    _max.clear_click_to_focus();

    end();

    align(FL_ALIGN_LEFT|FL_ALIGN_RIGHT);
}

void Fl_MDI_Titlebar::layout()
{
    int bh = h()-box()->dh()-4;

    int mid = h()/2-(bh/2);
    int X=bh+2;
	if(_close.visible()) {
		_close.resize(w()-X, mid, bh, bh);
		X+=bh+1;
	}
	if(_max.visible()) {
		_max.resize(w()-X, mid, bh, bh);
		X+=bh+1;
	}
    _min.resize(w()-X, mid, bh, bh);
}

void Fl_MDI_Titlebar::draw()
{
    if(!_owner->active())
        set_flag(FL_INACTIVE);

	label(_owner->label());

    int X = 7 + _close.w();
    if(_min.visible()) X+=_min.w();
    if(_max.visible()) X+=_max.w();
    if(image()) { int iw,ih; image()->measure(iw,ih); X+=iw+2; }

    fl_font(label_font(), float(label_size()));

    const char *txt = fl_cut_line(label(), w()-X);

    const char *saved_label = label();
    label(txt);

    bool dbuffer=true;
    if(damage()&FL_DAMAGE_CHILD) {
        dbuffer=false;
    }
#ifndef _WIN32
    if(dbuffer) {
        Pixmap i = fl_create_offscreen(w(),h());
        fl_begin_offscreen(i);

        Fl_Group::draw();

        fl_end_offscreen();
        fl_copy_offscreen(x(),y(),w(),h(),i,0,0);
        fl_delete_offscreen(i);
    } else
#endif
    {
        Fl_Group::draw();
    }

    label(saved_label);
    clear_flag(FL_INACTIVE);
}

int Fl_MDI_Titlebar::ex=0;
int Fl_MDI_Titlebar::ey=0;
int Fl_MDI_Titlebar::old_rx=0;
int Fl_MDI_Titlebar::old_ry=0;

int Fl_MDI_Titlebar::handle(int event)
{
    static int xx,yy,rx,ry;
    static bool moving=false;

    rx = Fl::event_x_root();
    ry = Fl::event_y_root();

    switch(event)
    {
    case FL_PUSH: {
        if(Fl::event_button()>1) return 1;

        // Send event to widgets...
        for(int i = children(); i--;) {
            Fl_Widget* child = this->child(i);
            // ignore widgets we are not pointing at:
            if (Fl::event_x() < child->x()) continue;
            if (Fl::event_x() >= child->x()+child->w()) continue;
            if (Fl::event_y() < child->y()) continue;
            if (Fl::event_y() >= child->y()+child->h()) continue;
            // see if it wants the event:
            if (child->send(event)) return true;
            // quit when we reach a widget that claims mouse points at it,
            // so we don't pass the events to widgets "hidden" behind that one.
            if(event != FL_ENTER && event != FL_MOVE && child->contains(Fl::belowmouse())) return false;
        }

        if(_owner->minimized()) return 0;

        fl_cursor(FL_CURSOR_MOVE);
        old_rx = rx - window()->x();
        old_ry = ry - window()->y();
        ex = Fl::event_x();
        ey = Fl::event_y();

        moving=true;
        return 1;
    }

    case FL_RELEASE: {
        if(when()&FL_WHEN_CHANGED || when()&FL_WHEN_RELEASE) do_callback();
        fl_cursor(FL_CURSOR_DEFAULT);
        moving=false;
        return 1;
    }

    case FL_DRAG: {
        if(!moving) return 1;
        if ((rx != old_rx) || (ry != old_ry)) {
            xx =  rx - old_rx;
            yy =  ry - old_ry;
            _owner->_position(xx,yy);
        }
        return 1;
    }
    /*    case FL_MOVE: {
     return 0;
     }
     case FL_ENTER: {
     return 0;
     }*/

    case FL_LEAVE: {
        fl_cursor(FL_CURSOR_DEFAULT);
        return 1;
    }
    default :
        return 0;
    }
}

bool Fl_MDI_Window::animate_ = true;
bool Fl_MDI_Window::anim_opaque_ = false;

void Fl_MDI_Window::default_callback(Fl_MDI_Window *win, void* v)
{
	win->hide();
}

static void revert(Fl_Style* s) {
    s->box = FL_THICK_UP_BOX;
}
static Fl_Named_Style style("MDI_Window", revert, &Fl_MDI_Window::default_style);
Fl_Named_Style* Fl_MDI_Window::default_style = &::style;

Fl_MDI_Window::Fl_MDI_Window(int x, int y, int w, int h, const char *label)
    : Fl_Window(x,y,w,h,0),
    _titlebar(2,2,w,18,0)
{
	Fl_Widget::copy_label(label);

    style(default_style);

    label_type(FL_NO_LABEL);
    box();

    size(w+box()->dw(), h+titlebar()->h()+box()->dh());

    _titlebar.align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    _titlebar.parent(this);

    // Set flag to identify our window
    set_flag(FL_MDI_WINDOW);

    bot.set(10,h-3,w-20,3);
    top.set(10,0,w-20,3);
    left.set(0,10,3,h-20);
    right.set(w-3,10,3,h-20);

    ltcorn.set(0,0,10,10);
    rtcorn.set(w-10,0,10,10);
    lbcorn.set(0,h-10,10,10);
    rbcorn.set(w-13,h-13,13,13);

    prv = new Fl_Group(box()->dx(), titlebar()->h()+box()->dy(), w, h);
    prv->box(FL_FLAT_BOX);
    prv->label_type(FL_NO_LABEL);
    prv->parent(this);

    h+=titlebar()->h();
    w+=box()->dw();

	state_ = NORMAL;
    _active    = false;

    _resize_where = NO_RESIZE;

    _ox = x;
    _oy = y;
    _oh = h;
    _ow = w;

    minw(100);
    minh(0);

    if(parent()) {
        _owner = (Fl_MDI_Viewport *)parent();
        _toplevel = false;
        Fl_Window::resizable(prv);
    } else {
        Fl_Window::resizable(0);
        _owner = 0;
        _toplevel = true;
    }

	//connect(&Fl_Widget::hide, (void*)0);
    callback((Fl_Callback*)default_callback, this);
    
	//_titlebar.activate(0);

    _boundaries=true;

    view()->begin();
}

Fl_MDI_Window::~Fl_MDI_Window()
{
    _owner->remove(this);
    if(_owner->aot() == this)
        _owner->aot(0);

    if(_owner->maximum() == this)
        _owner->maximum(0);

    if(_owner->_top == this)
        _owner->_top = 0;

    if(prv) {
        delete prv;
        prv=0;
    }

    destroy();
}

Fl_Group *Fl_MDI_Window::view(Fl_Group *v)
{
    Fl_Group *old = prv;
    remove(prv);
    v->parent(this);
    v->box(FL_FLAT_BOX);
    v->label_type(FL_NO_LABEL);
    insert(*v,0);
    prv = v;
    return old;
}

void Fl_MDI_Window::draw()
{
    if(damage() & ~FL_DAMAGE_CHILD) {

        fl_push_clip(0,0,w(),h());

        draw_frame();

        if(prv->visible())
            draw_child(*prv);
        if(_titlebar.visible())
            draw_child(_titlebar);

        fl_pop_clip();
    } else {
        if(prv->visible())
            update_child(*prv);
        if(_titlebar.visible())
            update_child(_titlebar);
    }
}

void Fl_MDI_Window::layout()
{
    if(!_toplevel && state_==NORMAL) {
        if(w() < _minw) w(_minw);
        if(h() < _minh) h(_minh);
    }

#ifdef _WIN32

    
	unsigned int flags;
    if(layout_damage() & FL_LAYOUT_WH)
#ifndef _WIN32_WCE
        flags = SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE;
    else if(layout_damage() & FL_LAYOUT_XY)
        flags = SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE;
#else
        flags = SWP_NOZORDER | SWP_NOACTIVATE;
    else if(layout_damage() & FL_LAYOUT_XY)
        flags = SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE;
#endif
    else
        flags = 0;


#else
    unsigned int flags = 1;
#endif

    if(!_toplevel) {

        if(!_titlebar.visible()) {
            tx=ty=tw=th=0;
            px=py=0;
            pw=w(); ph=h();

            prv->resize(px,py,pw,ph);
            prv->layout_damage(layout_damage());
            prv->layout();

        } else {

            tx=0,ty=0,tw=w(),th=_titlebar.height();
            tx+=box()->dx();
            ty+=box()->dy();
            tw-=box()->dw();

            px=0,py=_titlebar.height(),pw=w(),ph=h()-_titlebar.height();
            px+=box()->dx();
            py+=box()->dy();
            pw-=box()->dw();
            ph-=box()->dh();

            prv->resize(px,py,pw,ph);
            _titlebar.resize(tx,ty,tw,th);
            prv->layout_damage(layout_damage());
            prv->layout();
            _titlebar.layout();

            bot.set(10,h()-3,w()-20,3);
            top.set(10,0,w()-20,3);
            left.set(0,10,3,h()-20);
            right.set(w()-3,10,3,h()-20);

            ltcorn.set(0,0,8,8);
            rtcorn.set(w()-8,0,8,8);
            lbcorn.set(0,h()-8,8,8);
            rbcorn.set(w()-8,h()-8,8,8);

            //if(_maximized && _owner->maximum() != this)
            //	maximize(false);

            if(!prv->resizable()) {
                _titlebar._max.hide();
                //_titlebar._min.hide();
            } else if(prv->resizable()) {
                _titlebar._max.show();
                //_titlebar._min.show();
            }
        }
    } else {
        prv->resize(0,0,w(),h());
        prv->layout();
    }

    // Clear layout flags
    Fl_Widget::layout();

    // Do resizing
    if(shown() && flags) {
#ifdef _WIN32
        if(_toplevel) {
            int dx=0, dy=0, dw=0, dh=0;
            Fl_X::borders(this, dx, dy, dw, dh);
            SetWindowPos(fl_xid(this), 0, x()-dx, y()-dy, w()+dw, h()+dh, flags);
        } else
            SetWindowPos(fl_xid(this), 0, x(), y(), w(), h(), flags);
        if(!(flags & SWP_NOSIZE)) redraw();
#else
        XMoveResizeWindow(fl_display, fl_xid(this), x(), y(), w(), h());
#endif
    }
}

void Fl_MDI_Window::_resize(int x, int y, int w, int h)
{
    if(!_toplevel) {
        if(x<0) x=0;
        if(y<0) y=0;
        if(w<_minw) w=_minw;
        if(h<_minh) h=_minh;
        check_size_boundary(w,h);
    }

    if(x==this->x()&&y==this->y()&&w==this->w()&&h==this->h())
        return;

    //resize(x,y,w,h);
    this->x(x); this->y(y);
    this->w(w); this->h(h);

    resize(x,y,w,h);
    layout_damage(FL_LAYOUT_DAMAGE|FL_LAYOUT_XYWH);
	layout();
}

void Fl_MDI_Window::_position(int x, int y)
{
    if(!_toplevel) {
        check_move_boundary(x,y);
    }

    if(x==this->x()&&y==this->y())
        return;

    position(x,y);
}

void Fl_MDI_Window::check_size_boundary(int &w, int &h)
{
    if(w < _minw)
        w = _minw;

    if(h < _minh)
        h = _minh;

    if(_boundaries)
    {
        if(x()+w > _owner->w())
            w = _owner->w()-x();

        if(y()+h > _owner->h())
            h = _owner->h()-y();
    }
}

void Fl_MDI_Window::check_move_boundary(int &x, int &y)
{
	if(_boundaries)
  {
#if 0 //Window totally inside
    int OW=_owner->w();
    int OH=_owner->h();
    int TX=x+w();
    int TY=y+h();

    if(TX > OW)
        x = x-(TX-OW);

    if(TY > OH)
        y = y-(TY-OH);

    if(x < 0)
        x=0;

    if(y < 0)
    y=0;
#else
    int X=Fl::event_x_root()-Fl_MDI_Titlebar::old_rx+Fl_MDI_Titlebar::ex;
    int Y=Fl::event_y_root()-Fl_MDI_Titlebar::old_ry+Fl_MDI_Titlebar::ey;

    if(X < 0)
        x=-Fl_MDI_Titlebar::ex;
    if(Y < 0)
        y=-Fl_MDI_Titlebar::ey;
    if(X > _owner->w())
        x=_owner->w()-Fl_MDI_Titlebar::ex;
    if(Y > _owner->h())
        y=_owner->h()-Fl_MDI_Titlebar::ey;
#endif
	}
}

void Fl_MDI_Window::handle_resize(int where)
{
    if(!prv->resizable() || state_!=NORMAL) return;

    switch(where)
    {
    case RIGHTBOTTOM:
        {
            _resize(x(),y(),Fl::event_x(), Fl::event_y());
            break;
        }
    case LEFTBOTTOM:
        {
            int W=x()+w();
            int X=x()+Fl::event_x();
            // check boundaries...
            if(x()+Fl::event_x() > 0 || !_boundaries)
                W=W-(x()+Fl::event_x());
            if(W < _minw) {
                W=_minw;
                X=x()+w()-W;
            }
            _resize(X, y(), W, Fl::event_y());
            break;
        }
    case LEFTTOP:
        {
            int X=x()+Fl::event_x();
            int Y=y()+Fl::event_y();
            int W=x()+w();
            int H=y()+h();
			
            if(x()+Fl::event_x() > 0 || !_boundaries)
                W=W-(x()+Fl::event_x());
            if(y()+Fl::event_y() > 0 || !_boundaries) //boundary...
                H=H-(y()+Fl::event_y());

            if(H < _minh) {
                H=_minh;
                Y=y()+h()-H;
            }
            if(W < _minw) {
                W=_minw;
                X=x()+w()-W;
            }
            _resize(X, Y, W, H);
            break;
        }
    case RIGHTTOP:
        {
            int H=y()+h();
            int Y=y()+Fl::event_y();

            if(y()+Fl::event_y() > 0 || !_boundaries) //boundary...
                H=H-(y()+Fl::event_y());
            if(H < _minh) {
                H=_minh;
                Y=y()+h()-H;
            }
            _resize(x(), Y, Fl::event_x(), H);
            break;
        }
    case LEFT:
        {
            int W=x()+w();
            int X=x()+Fl::event_x();
            // check boundaries...
            if(x()+Fl::event_x() > 0 || !_boundaries)
                W=W-(x()+Fl::event_x());
            if(W < _minw) {
                W=_minw;
                X=x()+w()-W;
            }
            _resize(X, y(), W, h());
            break;
        }
    case RIGHT:
        {
            _resize(x(),y(),w()+(Fl::event_x()-w()),h());
            break;
        }
    case TOP:
        {
            int H=y()+h();
            int Y=y()+Fl::event_y();

            if(y()+Fl::event_y() > 0 || !_boundaries) //boundary...
                H=H-(y()+Fl::event_y());

            if(H < _minh) {
                H=_minh;
                Y=y()+h()-H;
            }
            _resize(x(), Y, w(), H);
            break;
        }
    case BOTTOM:
        {
            _resize(x(),y(),w(),h()+(Fl::event_y()-h()));
            break;
        }
    }
}

int Fl_MDI_Window::handle(int event)
{
    static int button = 0;

    switch(event)
    {
    /*case FL_MOUSEWHEEL: {		
        prv->send(event);
        break;
    }*/
    case FL_SHOW: {
        Fl_Window::handle(event);
        if(_toplevel) return 1;		
		setTop();
		_owner->relayout();
		Fl::flush();
        return 1;
    }
    case FL_HIDE: {
        delete_menu_buttons();
        Fl_Window::handle(event);

        if(_owner->aot() == this) _owner->aot(0);
        if(_owner->maximum() == this) _owner->maximum(0);					
        if(_owner->top() == this) _owner->_top=0;
		state_ = NORMAL;        
        throw_focus();

        _active = false;
		_owner->relayout();
		Fl::flush();
        return 1;
    }
    /*case FL_FOCUS: {
		prv->take_focus();
        return 0; // We do not need keyboard focus, for now...
    }*/
    case FL_PUSH: {		
		//Fl::pushed(this);
        if(_toplevel)
            return Fl_Window::handle(event);

        if(!minimized()) setTop();				

        // Send event to widgets...
        for(int i = children(); i--;) {
            Fl_Widget* child = this->child(i);
            // ignore widgets we are not pointing at:
            if(Fl::event_x() < child->x()) continue;
            if(Fl::event_x() >= child->x()+child->w()) continue;
            if(Fl::event_y() < child->y()) continue;
            if(Fl::event_y() >= child->y()+child->h()) continue;
            // see if it wants the event:
            if(child->send(event)) return true;
            // quit when we reach a widget that claims mouse points at it,
            // so we don't pass the events to widgets "hidden" behind that one.
            //if(event != FL_ENTER && event != FL_MOVE && child->contains(Fl::belowmouse())) return false;
        }		

        button = Fl::event_button();
        if(button == FL_LEFT_MOUSE && state_==NORMAL && prv->resizable() ) {
			if( rbcorn.posInRect(Fl::event_x(), Fl::event_y()) ) {
				fl_cursor(FL_CURSOR_NWSE, 0, 255);
				_resize_where = RIGHTBOTTOM;
				return 1;
			}
			else if( lbcorn.posInRect(Fl::event_x(), Fl::event_y()) ) {
				fl_cursor(FL_CURSOR_NESW, 0, 255);
				_resize_where = LEFTBOTTOM;
				return 1;
			}
			else if(ltcorn.posInRect(Fl::event_x(),Fl::event_y()) ) {
				fl_cursor(FL_CURSOR_NWSE, 0, 255);
				_resize_where = LEFTTOP;
				return 1;
			}
			else if( rtcorn.posInRect(Fl::event_x(),Fl::event_y()) ) {
				fl_cursor(FL_CURSOR_NESW, 0, 255);
				_resize_where = RIGHTTOP;
				return 1;
			}
			else if( left.posInRect(Fl::event_x(),Fl::event_y()) ) {
				fl_cursor(FL_CURSOR_WE, 0, 255);
				_resize_where = LEFT;
				return 1;
			}
			else if(right.posInRect(Fl::event_x(),Fl::event_y()) ) {
				fl_cursor(FL_CURSOR_WE, 0, 255);
				_resize_where = RIGHT;
				return 1;
			}
			else if(top.posInRect(Fl::event_x(),Fl::event_y()) ) {
				fl_cursor(FL_CURSOR_NS, 0, 255);
				_resize_where = TOP;
				return 1;
			}
			else if(  bot.posInRect(Fl::event_x(),Fl::event_y()) ) {
				fl_cursor(FL_CURSOR_NS, 0, 255);
				_resize_where = BOTTOM;
				return 1;
			}
        }

		break;
        //return 0;
    }// Fl_PUSH

    case FL_LEAVE:
        fl_cursor(FL_CURSOR_DEFAULT, 0, 255);
		break;

    case FL_ENTER:
    case FL_MOVE: {
        if(_toplevel || !prv->resizable() || state_!=NORMAL) {
            return prv->send(event);
        }
        // Left or right side
        if( left.posInRect(Fl::event_x(),Fl::event_y()) || right.posInRect(Fl::event_x(),Fl::event_y()) ) {
            fl_cursor(FL_CURSOR_WE, 0, 255);
            return 1;
        }
        // Top or bottom side
        if( top.posInRect(Fl::event_x(),Fl::event_y()) || bot.posInRect(Fl::event_x(),Fl::event_y()) ) {
            fl_cursor(FL_CURSOR_NS, 0, 255);
            return 1;
        }
        // Left top corner
        if( ltcorn.posInRect(Fl::event_x(),Fl::event_y()) ) {
            fl_cursor(FL_CURSOR_NWSE, 0, 255);
            return 1;
        }
        // Right top corner
        if( rtcorn.posInRect(Fl::event_x(),Fl::event_y()) ) {
            fl_cursor(FL_CURSOR_NESW, 0, 255);
            return 1;
        }
        // Right bottom corner
        if(rbcorn.posInRect(Fl::event_x(),Fl::event_y()) ) {
            fl_cursor(FL_CURSOR_NWSE, 0, 255);
            return 1;
        }
        // Left bottom corner		
        if( lbcorn.posInRect(Fl::event_x(),Fl::event_y()) ) {
            fl_cursor(FL_CURSOR_NESW, 0, 255);
            return 1;
        }
        fl_cursor(FL_CURSOR_DEFAULT, 0, 255);
        break;
    } // FL_MOVE
    case FL_DRAG: {
        if(_toplevel)
            return Fl_Window::handle(event);

        if(button == FL_LEFT_MOUSE) {
            handle_resize(_resize_where);
        }
        return 1;
    }
    case FL_RELEASE: {
        _resize_where = NO_RESIZE;
        fl_cursor(FL_CURSOR_DEFAULT, 0, 255);
    }

    } //switch

    return Fl_Group::handle(event);
}

void Fl_MDI_Window::detach()
{
    if(_toplevel || !parent()) return;

    delete_menu_buttons();

    if(_owner->aot() == this)
        _owner->_aot = 0;
    if(_owner->maximum() == this)
        _owner->_max = 0;
    if(_owner->top() == this)
        _owner->_top = 0;


	state_ = NORMAL;
    _titlebar.hide();

    _toplevel = true;
    parent()->remove(this);
    parent(0);
    box(FL_FLAT_BOX);

    if(resizable()) {
        size_range(_minw-4, _minh-27);
    } else {
        size_range(view()->w(), view()->h(), view()->w(), view()->h());
        //size_range(-1,-1,-1,-1);
    }
    Fl_Window::resizable(0);

    int WX = x(); int WY = y();
    for (Fl_Widget *o = _owner->parent(); o; o = o->parent()) {
        WX += o->x(); WY += o->y();
        if (o->is_window()) break;
    }

    int _x=WX;
    int _y=WY+_titlebar.h();
    int _w=view()->w(), _h=view()->h();

    // Popup in same place
    resize(_x, _y, _w, _h);

    destroy();
    show();

    if(prv->is_window()) {
        ((Fl_Window *)prv)->show(this);
    }
}

void Fl_MDI_Window::attach(Fl_MDI_Viewport *ws)
{
    if(!_toplevel || !ws) return;

    _toplevel = false;

    ws->add(*this);
    parent(ws);
    box(FL_THICK_UP_BOX);
    Fl_Window::resizable(prv);

    destroy();
    show();

    if(prv->is_window()) {
        ((Fl_Window *)prv)->show(this);
    }

    int WX = 0; int WY = 0;
    for (Fl_Widget *o = _owner->parent(); o; o = o->parent()) {
        WX += o->x(); WY += o->y();
        if (o->is_window()) break;
    }

    int _x=x()-WX;
    int _y=y()-WY-_titlebar.h();
    int _w=w()+4, _h=h()+_titlebar.h()+4;
	
    if(_x<0) _x=0;
    if(_y<0) _y=0;
    if(_x+_w>_owner->w()) _x=_owner->w()-_w;
    if(_y+_h>_owner->h()) _y=_owner->h()-_h;
	
    if(_w > _owner->w()) {
        _x=0;
        //_w=_owner->w();
    }
    if(_h > _owner->h()) {
        _y=0;
        //_h=_owner->h();
    }

    _titlebar.show();

    resize(_x, _y, _w, _h);
    setTop();
}

class Fl_MDI_MenuButtons : public Fl_Widget
{
public:
    Fl_MDI_MenuButtons() : Fl_Widget(0,0,0,0) {
        type(Fl_Item::NO_EXECUTE);
        index = -1;
        box(FL_THIN_UP_BOX);        
    }
    ~Fl_MDI_MenuButtons() {        
    }
	void set_control(Fl_MDI_Window *w, Fl_Menu_Bar *b)
	{
		index = -1;
		win = w;
        bar = b;
		if(!bar->contains(this)) {
			bar->add(this);
	        stored_rlayout = bar->right_layout();
		    bar->right_layout(this);
		}
	}
	void release_control()
	{
		if(bar) {
			bar->remove(this);
			bar->right_layout(stored_rlayout);
		}
		bar=0;
		stored_rlayout=0;
		win=0;
		bar=0;
	}

    void draw() {
        int size = h()-4;

        for(int n=0; n<3; n++) {
            buttons[n].set(2+(n*size)+(n*2),2,size,size);
            box()->draw(buttons[n].x(), buttons[n].y(), buttons[n].w(), buttons[n].w(),
                        button_color(), n==index?FL_VALUE:0);

            label_type(FL_SYMBOL_LABEL);

            int X = buttons[n].x();
            int Y = buttons[n].y();
            int W = buttons[n].w();
            int H = buttons[n].h();
            box()->inset(X,Y,W,H);
            switch(n) {
            case 0:
                label_type()->draw("@mi", X,Y,W,H, FL_BLACK, 0);
                break;
            case 1:
                label_type()->draw("@mx", X,Y,W,H, FL_BLACK, 0);
                break;
            case 2:
                label_type()->draw("@xx", X,Y,W,H, FL_BLACK, 0);
                break;
            default:
                break;
            }
        }

    }
    void layout() {
        if(w() && h()) return;
        h(bar->text_size());
        w((h()*3)+6);
        Fl_Widget::layout();
    }
    int handle(int e)
    {
        switch(e) {
        case FL_RELEASE: {
            if(index!=-1) {                
                if(Fl::event_inside(buttons[index].x(),buttons[index].y(),buttons[index].w(),buttons[index].h()))
                    action(index);				
				return 1;
            }
            break;
        }
        case FL_PUSH: {
            for(int n=0; n<3; n++)
            {
                // ignore widgets we are not pointing at:
                if (Fl::event_x() < buttons[n].x()) continue;
                if (Fl::event_x() >= buttons[n].x()+buttons[n].w()) continue;
                if (Fl::event_y() < buttons[n].y()) continue;
                if (Fl::event_y() >= buttons[n].y()+buttons[n].h()) continue;

                index = n;
                bar->redraw();
                return 1;
            }
        }
        default:
            break;
        }

        return Fl_Widget::handle(e);
    }
    void action(int button) {
        switch(button) {
        case 0: //MIN
            win->minimize(true);
            break;
        case 1: //MAX
            win->maximize(false);
            break;
        case 2: //CLOSE
            win->do_callback();
            break;
        default:
            break;
        }
    }

    Fl_Widget *stored_rlayout;
    Fl_MDI_Window *win;
    Fl_Menu_Bar *bar;
    int index;
    Fl_Rect buttons[3];
};

Fl_MDI_MenuButtons *menubuttons = 0;

void Fl_MDI_Window::add_menu_buttons()
{
    Fl_Menu_Bar *menu = owner()->menu();
    if(menu) {
		if(!menubuttons) {
			Fl_Group::current(0); 
			menubuttons = new Fl_MDI_MenuButtons();
		}
        menu->begin();
        menubuttons->set_control(this, menu);
        menu->end();

        menu->relayout();
        menu->redraw();
    }
}

void Fl_MDI_Window::delete_menu_buttons()
{
    if(menubuttons) {
        menubuttons->release_control();

        Fl_Menu_Bar *menu = owner()->menu();
        if(menu) {
            menu->relayout();
            menu->redraw();
        }
    }
}

#define STEP_DIV 15
void Fl_MDI_Window::animate(int fx, int fy, int fw, int fh,
                            int tx, int ty, int tw, int th)
{	
# undef max
# define max(a,b) (a) > (b) ? (a) : (b)
    float max_steps = max( float(tw-fw), float(th-fh) );
    float min_steps = max( float(fw-tw), float(fh-th) );
    float steps = max(max_steps, min_steps);
    steps/=STEP_DIV;

    float sx = max( ((float)(fx-tx)/steps), ((float)(tx-fx)/steps) );
    float sy = max( ((float)(fy-ty)/steps), ((float)(ty-fy)/steps) );
    float sw = max( ((float)(fw-tw)/steps), ((float)(tw-fw)/steps) );
    float sh = max( ((float)(fh-th)/steps), ((float)(th-fh)/steps) );

    int xinc = fx < tx ? 1 : -1;
    int yinc = fy < ty ? 1 : -1;
    int winc = fw < tw ? 1 : -1;
    int hinc = fh < th ? 1 : -1;
    float rx=float(fx), ry=float(fy),
		rw=float(fw), rh=float(fh);	

#ifdef _WIN32
	if(!_owner->shown()) return;
	HDC saved = fl_gc, new_gc;
	fl_gc = new_gc = GetDCEx(fl_xid(_owner), NULL, DCX_LOCKWINDOWUPDATE); //Draws top of child windows...
#endif
    
    while(steps-- > 0) {

        rx+=(sx*xinc);
        ry+=(sy*yinc);
        rw+=(sw*winc);
        rh+=(sh*hinc);

        if(anim_opaque_) {
            resize((int)rx, (int)ry, (int)rw, (int)rh);
            layout();
        } else {
#ifndef _WIN32
            _owner->make_current();
#else
            fl_gc = new_gc;
#endif
            overlay_rect((int)rx, (int)ry, (int)rw, (int)rh);			
        }

        XFlush(fl_display);
        Fl::check();
    }
#ifdef _WIN32
	ReleaseDC(fl_xid(_owner), new_gc);
	fl_gc = saved;
#endif

    if(!anim_opaque_) overlay_clear();
    resize(tx,ty,tw,th);
}

void Fl_MDI_Window::state(int s)
{
    int X, Y, W, H;
	switch(s)
	{
	case NORMAL:
		if(state_>NORMAL) {
	        if(_owner->maximum()==this) _owner->_max=0;
	        if(animate()) animate(x(), y(), w(), h(), _ox, _oy, _ow, _oh);
			else resize(_ox, _oy, _ow, _oh);
	        _titlebar.show();
	        delete_menu_buttons();
			setTop();
			active(true);
			layout();
			redraw();					
		}		
		break;

	case MAXIMIZED:
		_ox=x(); _oy=y(); _ow=w(); _oh=h();
		X=Y=0; W=_owner->w(); H=_owner->h();

		if(!resizable()) {			
			state(NORMAL);
			return;
		}

		if(animate()) animate(x(), y(), w(), h(), X, Y, W, H);
        else resize(X, Y, W, H);

        _owner->maximum(this);
	    if(_owner->menu()) _titlebar.hide();
		add_menu_buttons();
		take_focus();
		active(true);
		
		layout();		
		redraw();		
		break;

	case MINIMIZED:
		_ox=x(); _oy=y(); _ow=w(); _oh=h();      
		X=0; Y=_owner->h()-_titlebar.h()+4; W=100; H=_titlebar.h()+4;
		
        if(animate()) animate(x(), y(), w(), h(), X, Y, W, H);
        else resize(X, Y, W, H);

		if(state_==MAXIMIZED) {
			_owner->maximum(0);
			_titlebar.show();
			delete_menu_buttons();
		}
		throw_focus();
		active(false);
		
		redraw();
		break;

	default:
		return;
	}

	state_ = s;
    _owner->redraw_all();
    _owner->relayout_all();
}

