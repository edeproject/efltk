#include <efltk/Fl_MDI_Window.h>
#include <efltk/Fl_Image.h>

#include <string.h>

#ifndef _WIN32

# include <unistd.h>
# ifndef max
#  define max(a,b) (a) > (b) ? (a) : (b)
# endif

#else

# define usleep(x) Sleep(x/1000)
# define XSync(d, b) (void)d; (void)b

#endif

static void closeMdiWin(Fl_Widget *, void *d)
{
    ((Fl_MDI_Window*)d)->close_callback();	
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
#define CL_OF 0.6
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

#define MAX_OF 0.6
void draw_max(Fl_Color col)
{			
	fl_color(col);
	
	vv(-MAX_OF,-MAX_OF+0.2); 
	vv(MAX_OF,-MAX_OF+0.2); 
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

#define MIN_OF 0.6
#define MIN_OF2 0.5
void draw_min(Fl_Color col)
{			
	fl_color(col);
	
	vv(MIN_OF2, MIN_OF);
	vv(-MIN_OF2, MIN_OF);
	fl_stroke();
	fl_closepath();

	vv(MIN_OF2, MIN_OF-0.1);
	vv(-MIN_OF2, MIN_OF-0.1);
	fl_stroke();
	fl_closepath();
}

Fl_MDI_Titlebar::Fl_MDI_Titlebar(int x,int y,int w,int h,const char *l)
: Fl_Group(x,y,w,h,l),_close(0,0,0,0),_max(0,0,0,0),_min(0,0,0,0)
{
    _owner = (Fl_MDI_Window *)parent();

    fl_add_symbol("xx", draw_cl, 1);
    fl_add_symbol("mx", draw_max, 1);
    fl_add_symbol("mi", draw_min, 1);

    _close.label_type(FL_SYMBOL_LABEL);
    _close.label("@xx");
    _close.box(FL_THIN_UP_BOX);
    _close.callback(closeMdiWin, _owner);

    _max.label_type(FL_SYMBOL_LABEL);
    _max.label("@mx");
    _max.box(FL_THIN_UP_BOX);
    _max.callback(maxMdiWin, _owner);

    _min.label_type(FL_SYMBOL_LABEL);
    _min.label("@mi");
    _min.box(FL_THIN_UP_BOX);
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
    _close.resize(w()-X, mid, bh, bh);
    X+=bh+1;
    _max.resize(w()-X, mid, bh, bh);
    X+=bh+1;
    _min.resize(w()-X, mid, bh, bh);
}

void Fl_MDI_Titlebar::draw()
{
    if(!_owner->active())
        set_flag(FL_INACTIVE);

    int X = 7 + _close.w();
    if(_min.visible()) X+=_min.w();
    if(_max.visible()) X+=_max.w();
    if(image()) { int iw,ih; image()->measure(iw,ih); X+=iw+2; }

    fl_font(label_font(), label_size());

    char *txt = fl_cut_line(label(), w()-X);

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
    delete []txt;

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

Fl_MDI_Window::Fl_MDI_Window(int x, int y, int w, int h, const char *label)
: Fl_Window(x,y,w,h, _cap),
_titlebar(2,2,w,20, _cap)
{
    label_type(FL_NO_LABEL);
    box(FL_THICK_UP_BOX);

    size(w+box()->dw(), h+titlebar()->h()+box()->dh());

    memset(_cap, 0, 4096);
    caption(label);

    _anim_opaque = false;
    //_anim_opaque = true;

    _titlebar.align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    _titlebar.box(FL_HOR_SHADE_FLAT_BOX);
    _titlebar.label_color(FL_WHITE);
    _titlebar.label_font(FL_HELVETICA_BOLD);
    _titlebar.color(fl_rgb(0,0,200));
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

    _maximized = false;
    _animate   = false;
    _active    = false;

    _resize_where = NO_RESIZE;

    _ox = x;
    _oy = y;
    _oh = h;
    _ow = w;
    _minimized = false;
    old_title_h = _titlebar.h();
    old_title_fh = _titlebar.label_size();

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

    callback(closeMdiWin, this);
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

  delete prv;
  prv=0;

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

        draw_frame();

        if(prv->visible())
            draw_child(*prv);
        if(_titlebar.visible())
            draw_child(_titlebar);

        //fl_pop_clip();
    } else {
        if(prv->visible())
            update_child(*prv);
        if(_titlebar.visible())
            update_child(_titlebar);
    }
}

void Fl_MDI_Window::layout()
{
    if(!_toplevel && !_minimized) {
        if(w() < _minw) w(_minw);
        if(h() < _minh) h(_minh);
    }

#ifdef _WIN32
    unsigned int flags;
    if(layout_damage() & FL_LAYOUT_WH)
        flags = SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE;
    else if(layout_damage() & FL_LAYOUT_XY)
        flags = SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE;
    else
        flags = 0;
#else
    unsigned int flags = 1;
#endif

    if(!_toplevel) {
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

        if(!prv->resizable() && (_titlebar._max.visible() || _titlebar._min.visible())) {
            _titlebar._max.hide();
            _titlebar._min.hide();
        } else if(prv->resizable() && (!_titlebar._max.visible() || !_titlebar._min.visible())) {
            _titlebar._max.show();
            _titlebar._min.show();
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

    resize(x,y,w,h);
    layout_damage(FL_LAYOUT_DAMAGE|FL_LAYOUT_XYWH);
}

void Fl_MDI_Window::_position(int x, int y)
{
    if(!_toplevel) {
			check_move_boundary(x,y);
		}
		
		if(x==this->x()&&y==this->y())
			return;
		
    position(x,y);
    layout_damage(FL_LAYOUT_DAMAGE|FL_LAYOUT_XY);
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
    if(!prv->resizable() || _maximized || _minimized) return;

    if(_maximized) {
        _resize(0,0,_owner->w(), _owner->h());
        _maximized = false;
        return;
    }

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
    case FL_MOUSEWHEEL: {
        //send(event, *prv);
        prv->handle(FL_MOUSEWHEEL);
        break;
    }
    case FL_SHOW: {
        Fl_Window::handle(event);
        if(_toplevel) return 1;
        setTop();
        return 1;
    }
    case FL_HIDE: {
        //Donno why we need this...
        Fl_Window::handle(event);
        _active = false;
        return 1;
    }
    case FL_FOCUS: {
        return 0; // We do not need keyboard focus, for now...
    }
    case FL_PUSH: {
        if(_toplevel)
            return Fl_Window::handle(event);

        if(!_minimized) setTop();

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
            if(event != FL_ENTER && event != FL_MOVE && child->contains(Fl::belowmouse())) return false;
        }

        button = Fl::event_button();
        if(button == FL_LEFT_MOUSE && !_minimized) {
            if(prv->resizable() && !_maximized) {
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
        }

        return 0;
    }// Fl_PUSH
    case FL_LEAVE: {
        fl_cursor(FL_CURSOR_DEFAULT, 0, 255);
        break;
    }
    case FL_ENTER: {
        break;
    }
    case FL_MOVE: {
        if(_toplevel || _maximized || !prv->resizable() || _minimized) {
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

void Fl_MDI_Window::close_callback()
{
    if(!callback()) return;
    if(callback() == closeMdiWin) {
        _owner->remove(this);
        if(_owner->aot() == this)
            _owner->aot(0);
        if(_owner->maximum() == this)
            _owner->maximum(0);
        if(_owner->top() == this)
            _owner->_top=0;
        hide();
    } else {
        do_callback();
    }
}

void Fl_MDI_Window::detach()
{
    if(_toplevel || !parent()) return;

    if(_owner->aot() == this)
        _owner->aot(0);
    if(_owner->maximum() == this)
        _owner->maximum(0);

    _maximized=false;
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
        _w=_owner->w();
    }
    if(_h > _owner->h()) {
        _y=0;
        _h=_owner->h();
    }

    _titlebar.show();

    resize(_x, _y, _w, _h);
    setTop();
}

static int px,py,pw,ph;
#ifdef _WIN32
static int old_f;
#else
static GC invertGc=0;
#endif
void set_overlay_func() {
#ifdef _WIN32
    old_f = SetROP2(fl_gc, R2_NOT);
#else
    if(!invertGc) {
        XGCValues v;
        v.subwindow_mode = IncludeInferiors;
        v.function = GXinvert;
        v.line_width = 2;
        v.line_style = LineSolid;
        v.fill_style = FillSolid;
        v.join_style = JoinRound;
        int mask = GCSubwindowMode|GCFunction|GCLineWidth|GCLineWidth;
        //invertGc = XCreateGC(fl_display, RootWindow(fl_display, fl_screen), mask, &v);
        invertGc = XCreateGC(fl_display, fl_window, mask, &v);
    }
#endif
}
void set_def_func() {
#ifdef _WIN32
    SetROP2(fl_gc, old_f);
#endif
}
static void draw_current_rect() {
#ifdef _WIN32
    fl_rect(px, py, pw, ph);
#else
    XDrawRectangle(fl_display, fl_window, invertGc, px, py, pw, ph);
#endif
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

#define STEP_DIV 15
void Fl_MDI_Window::animate_max(int mx, int my, int mw, int mh)
{
    double steps = max((mw-w()),(mh-h())); steps/=STEP_DIV;
    double sx = max( ((double)(x()-mx)/steps), ((double)(mx-x())/steps));
    double sy = max( ((double)(y()-my)/steps), ((double)(my-y())/steps));
    double sw = (double)(mw-w())/steps;
    double sh = (double)(mh-h())/steps;

    int xinc = x() < mx ? 1 : -1;
    int yinc = y() < my ? 1 : -1;
    double rx=x(),ry=y(),rw=w(),rh=h();

    while(steps-- > 0) {
        rx+=(sx*xinc);
        ry+=(sy*yinc);
        rw+=sw;
        rh+=sh;

        if(_anim_opaque) {
            resize((int)rx, (int)ry, (int)rw, (int)rh);
            layout();
        } else {
            _owner->make_current();
            overlay_rect((int)rx, (int)ry, (int)rw, (int)rh);
            usleep(1000); //This is needed only in Linux... Otherwise seems to be too fast?!?!
        }
        XSync(fl_display, false);
        Fl::check();
    }
    if(!_anim_opaque) overlay_clear();
    resize(mx,my,mw,mh);
}

void Fl_MDI_Window::animate_min(int mx, int my, int mw, int mh)
{
    double steps = max((h()-mh),w()-mw); steps/=STEP_DIV;
    double sx = max( ((double)(x()-mx)/steps), ((double)(mx-x())/steps));
    double sy = max( ((double)(y()-my)/steps), ((double)(my-y())/steps));
    double sw = (double)(w()-mw)/steps;
    double sh = (double)(h()-mh)/steps;

    int xinc = x() > mx ? -1 : 1;
    int yinc = y() > my ? -1 : 1;
    double rx=x(),ry=y(),rw=w(),rh=h();
    while(steps-- > 0) {
        rx+=(sx*xinc);
        ry+=(sy*yinc);
        rw-=sw;
        rh-=sh;

        if(_anim_opaque) {
            resize((int)rx, (int)ry, (int)rw, (int)rh);
            layout();
        } else {
            _owner->make_current();
            overlay_rect((int)rx, (int)ry, (int)rw, (int)rh);
            usleep(1000); //This is needed only in Linux... Otherwise seems to be too fast?!?!
        }
        XSync(fl_display, false);
        Fl::check();
    }
    if(!_anim_opaque) overlay_clear();
    resize(mx,my,mw,mh);
}

void Fl_MDI_Window::minmax()
{	
    if(_maximized) {
        int _W,_H;
        _W=_owner->w(); _H=_owner->h();

        if(_animate)
            animate_max(0, 0, _W, _H);
        else
            resize(0, 0, _W, _H);
        _owner->maximum(this);
        old_title_h = _titlebar.h();
        old_title_fh = _titlebar.label_size();
        _titlebar.h(15);
        _titlebar.label_size(10);

    } else {
        if(_owner->maximum() == this)
            _owner->maximum(0);

        _titlebar.h(old_title_h);
        _titlebar.label_size(old_title_fh);
        _titlebar.show();

        check_size_boundary(_ow, _oh);
        if(_ox+_ow > _owner->w())
            _ox=_ox-((_ox+_ow)-_owner->w());
        if(_oy+_oh > _owner->h())
            _oy=_oy-((_oy+_oh)-_owner->h());
        if(_animate) {
            animate_min(_ox, _oy, _ow, _oh);
        } else
            resize(_ox, _oy, _ow, _oh);
    }

    layout();

    setTop();
    _minimized = false;
}

void Fl_MDI_Window::maximize(bool val)
{
    if(_toplevel) return;

    if(!_maximized && !_minimized)
    {
        oldpos(x(),y());
        oldsize(w(),h());
    }

    _maximized = val;
    minmax();

    _owner->redraw_all();
    _owner->relayout_all();
}

void Fl_MDI_Window::minimize(bool val)
{
    if(_toplevel) return;

	if(_maximized) {
		_maximized=false;
		_titlebar.h(old_title_h);
        _titlebar.label_size(old_title_fh);
	}
	if(_owner->_max==this) _owner->_max=0;

    if(!val && _minimized)
    {
        _minimized = false;
        _maximized = false;

        if(_animate) {
            animate_max(_hox, _hoy, _how, _hoh);
        } else
            resize(_hox,_hoy,_how,_hoh);

        take_focus();
        active(true);
        setTop();
    }
    else if(val && !_minimized)
    {
        h_oldsize(w(), h());
        h_oldpos(x(),y());

        if(_animate)
        {
            animate_min(0,_owner->h()-_titlebar.h()+4, 100, _titlebar.h()+4);
        } else
            resize(0,_owner->h()-_titlebar.h()+4, 100, _titlebar.h()+4);

        _maximized = false;
        _minimized = true;

        throw_focus();
        active(false);
    }

    _owner->redraw_all();
    _owner->relayout_all();
}

