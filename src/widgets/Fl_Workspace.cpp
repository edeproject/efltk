#include <efltk/Fl_Workspace.h>
#include <efltk/Fl_MDI_Window.h>

static void cb_none(Fl_Widget *, void *) { }

#define SLIDER_WIDTH scrollbar_width()

static void revert(Fl_Style* s) {
    s->color = FL_GRAY;
    s->box = FL_FLAT_BOX;
}
static Fl_Named_Style style("MDI_Viewport", revert, &Fl_MDI_Viewport::default_style);
Fl_Named_Style* Fl_MDI_Viewport::default_style = &::style;

Fl_MDI_Viewport::Fl_MDI_Viewport(int x, int y, int w, int h, const char *label)
    : Fl_ViewportType(x,y,w,h, label)
{
    style(default_style);

    callback(cb_none);

    _aot = 0;
    _max = 0;
    _top = 0;

    _scrolldx = _scrolldy = 0;
}

void Fl_MDI_Viewport::top(Fl_MDI_Window *w)
{
    if(w && w!=_top) {

        // Insert new top to last of the stack
        insert(*w, children());

        //Just in case... :)
        w->take_focus();
        w->show();

        if(w->shown()) {
#ifndef _WIN32
            XRaiseWindow(fl_display, fl_xid(w));
#else
            BringWindowToTop(fl_xid(w));
#endif
        }
        if(_top) {
            // set to inactive and redraw old _top
            _top->active(false);
            _top->redraw();
        }

        // Set new top, and redraw it
        _top = w;
        _top->active(true);
        _top->redraw();

        do_callback();
    }
}

void Fl_MDI_Viewport::maximum(Fl_MDI_Window *w)
{
    top(w);
    if(_aot)
        insert(*w,_aot);
    _max = w;
    relayout();
}

int Fl_MDI_Viewport::handle(int ev)
{
    switch(ev) {
    case FL_SHOW:
        Fl_ViewportType::handle(ev);
        relayout_all();
        redraw_all();
        return 1;
    case FL_FOCUS: return 1; //Grab keyboard focus

    case FL_KEYUP: {
        if(Fl::event_state(FL_CTRL))
            if(Fl::event_key()==FL_Tab)
                cycle_windows();
    }
    };

    return Fl_ViewportType::handle(ev);
}

int Fl_MDI_Viewport::cnt_windows()
{
    int c=0;
    for(int n=children(); n--;)
        if(((child(n)->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW))
        {
            Fl_MDI_Window *win = (Fl_MDI_Window *)child(n);
            if(!win->minimized())
                c++;
        }

    return c;
}

void Fl_MDI_Viewport::attach(Fl_MDI_Window *w)
{
    if(w->owner() != this)
        return;

    if(w->toplevel())
        w->attach(this);
}

void Fl_MDI_Viewport::detach(Fl_MDI_Window *w)
{
    if(w->owner() != this)
        return;

    w->detach();
}

void Fl_MDI_Viewport::close_all()
{
    for(int n = children(); n--;)
    {
        Fl_Widget* o = child(n);
        if(((o->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW))
        {
            Fl_MDI_Window *win = (Fl_MDI_Window *)o;
            win->close_callback();
        }
    }
}

void Fl_MDI_Viewport::cb_draw_clip(void* v,int X, int Y, int W, int H)
{
    ((Fl_MDI_Viewport *)v)->draw_clip(X,Y,W,H);
}

void Fl_MDI_Viewport::draw_clip(int X, int Y, int W, int H)
{
    fl_push_clip(X,Y,W,H);

    // draw all the children, clipping them out of the region:
    int numchildren = children();
    int i;
    for(i = numchildren; i--;)
    {
        Fl_Widget& w = *child(i);
        if(w.visible() && w.is_window()) { w.show(); continue; }

        // Partial-clipped children with their own damage will still need
        // to be redrawn before the scroll is finished drawing.  Don't clear
        // their damage in this case:
        uchar save = 0;
        if(!(damage()&FL_DAMAGE_ALL)) {
            if(w.x() < X || w.y() < Y || w.x()+w.w() > X+W || w.y()+w.h() > Y+H)
                save = w.damage();
        }
        draw_child(w);
        w.set_damage(save);
    }

    // fill the rest of the region with color:
    // fl_color(color()); fl_rectf(X,Y,W,H);
    draw_box(); //Keeps bg picture up-to-date

    fl_pop_clip();
}

void Fl_MDI_Viewport::draw()
{
    if(_max) {
        if(damage() & ~FL_DAMAGE_CHILD) {
            fl_push_matrix();
            fl_translate(_max->x(), _max->y());
            _max->set_damage(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE);
            _max->draw();
            _max->set_damage(0);
            fl_pop_matrix();
        }
        else
            update_child(*_max);
        return;
    }

    int X=0,Y=0,W=w(),H=h();
    box()->inset(X,Y,W,H);

    //uchar d = damage();
    //if(d & FL_DAMAGE_ALL)
    {
        draw_frame();
        draw_clip(X, Y, W, H);
    }
    // This is not possible, if viewport has some other widgets than MDI windows...
    /*else {
        if(_scrolldx || _scrolldy) {
            fl_scroll(X, Y, W, H, _scrolldx, _scrolldy, cb_draw_clip, this);
        }
        if (d & FL_DAMAGE_CHILD) { // draw damaged children
            fl_push_clip(X, Y, W, H);
            //draw_box();
            for(int i = children(); i--;) {
                Fl_Widget& w = *child(i);
                if(w.visible() && w.is_window()) { w.show(); continue; }
                if(w.damage() & FL_DAMAGE_CHILD_LABEL) {
                    draw_outside_label(w);
                    w.set_damage(w.damage() & ~FL_DAMAGE_CHILD_LABEL);
                }
                update_child(w);
            }
            fl_pop_clip();
        }
    }   */
    _scrolldx = _scrolldy = 0;
}

void Fl_MDI_Viewport::redraw_all()
{
    for(int n = children(); n--;)
    {
        Fl_Widget* o = child(n);
        if(((o->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW))
        {
            Fl_MDI_Window *win = (Fl_MDI_Window *)o;
            if(win!=_top) win->active(false);
            if(win->visible()) win->show();
            win->redraw();
        }
    }
    redraw();
}

void Fl_MDI_Viewport::relayout_all()
{
    for(int n = children(); n--;) {
        Fl_Widget* o = child(n);
        if(((o->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW))
        {
            Fl_MDI_Window *win = (Fl_MDI_Window *)o;
            win->relayout();
        }
    }
    relayout();
}

Fl_MDI_Window *Fl_MDI_Viewport::find(const char *caption)
{
    for(int n = children(); n--;) {
        Fl_Widget* o = child(n);
        if(((o->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW)) {
            Fl_MDI_Window *win = (Fl_MDI_Window *)o;
            if(strcmp(caption, win->caption()) == 0)
                return win;
        }
    }
    return 0;
}

void Fl_MDI_Viewport::layout()
{
    Fl_ViewportType::layout();

    //For minimized windows
    int min=0;
    int row=1;

    for(int n = children(); n--;) {
        Fl_Widget* o = child(n);

        if(((o->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW)) {
            Fl_MDI_Window *win = (Fl_MDI_Window *)o;
            if(!win->visible() && win->toplevel())
                continue;

            if(win==_max) {
                win->resize(-win->box()->dx(), -win->box()->dy(), w()+win->box()->dw(), h()+win->box()->dh() );
                win->layout();
                if(_aot) insert(*win,_aot);
            }

            if(win == _aot) {
#ifndef _WIN32
                XRaiseWindow(fl_display, fl_xid(win));
#else
                BringWindowToTop(fl_xid(win));
#endif
                if(win != child(children()-1)) add(*win);
                _top = win;
            }

            if(win->minimized()) {
                int X=win->w()*min;
                if(X+win->w()>w()) { X=0; min=0; row++; }
                int Y=h()-(win->h()*row)-1;
                win->position(X,Y);
                win->layout();

                min++;
            }
        }
    }
}

void Fl_MDI_Viewport::cycle_windows()
{
    for(int n=0; n<children(); n++) {
        Fl_Widget *o = child(n);
        if(((o->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW) && o->visible()) {
            top((Fl_MDI_Window *)o);
            break;
        }
    }
}


//////////////////////////////////

void cb_show(Fl_Widget *w, void *d)
{
    ((Fl_Workspace *)d)->show_window();
}

static void ws_revert(Fl_Style* s) {
    s->box = FL_DOWN_BOX;
}
static Fl_Named_Style ws_style("Workspace", ws_revert, &Fl_Workspace::default_style);
Fl_Named_Style* Fl_Workspace::default_style = &::ws_style;

Fl_Workspace::Fl_Workspace(int x, int y, int w, int h, const char *label)
: Fl_WorkType(x,y,w,h, label)
{
    style(default_style);

    xposition_ = yposition_ = 0;
    layoutdx = layoutdy = 0;
    move_pos = false;

    type(BOTH);

    vscrollbar = new Fl_Scrollbar(x+w-SLIDER_WIDTH, y, SLIDER_WIDTH, h-SLIDER_WIDTH);
    hscrollbar = new Fl_Scrollbar(x, y+h-SLIDER_WIDTH, w-SLIDER_WIDTH, SLIDER_WIDTH);

    hscrollbar->parent(this);
    hscrollbar->type(Fl_Slider::HORIZONTAL);
    hscrollbar->callback(cb_hscrollbar, this);
    hscrollbar->linesize(10);

    vscrollbar->parent(this);
    vscrollbar->callback(cb_vscrollbar, this);
    vscrollbar->linesize(10);

    _viewport = new Fl_MDI_Viewport(box()->dy(), box()->dx(), w-box()->dw(), h-box()->dh());
    _viewport->end();

    Fl_Group::current(this);
}

Fl_Workspace::~Fl_Workspace()
{
}

void Fl_Workspace::focus_moves_pos(bool val)
{
    if(val)
        viewport()->callback(cb_show, this);
    else
        viewport()->callback(cb_none, this);

    move_pos = val;
}


void Fl_Workspace::show_window(Fl_MDI_Window *w)
{
    if(!w) return;

    int X,Y,W,H; bbox(X,Y,W,H);

    bool lay=false;
    int wx=w->x(), wy=w->y(), ww=w->w(), wh=w->h();
    int newx = xposition(), newy = yposition();
    if(wx<0) { newx=0; lay=true; }
    if(wy<0) { newy=0; lay=true; }
    if(wx+ww>W) { newx=ww-(W-ww); lay=true; }
    if(wy+wh>H) { newy=wy-(H-wh); lay=true; }

    if(lay) {
        position(newx, newy);
    }
}

void Fl_Workspace::cb_vscrollbar(Fl_Widget *o, void *d) 
{
	Fl_Workspace *s = (Fl_Workspace*)d;
	s->position(s->xposition(), int(((Fl_Scrollbar*)o)->value()));
}

void Fl_Workspace::cb_hscrollbar(Fl_Widget *o, void *d) 
{
	Fl_Workspace *s = (Fl_Workspace*)d;	
	s->position(int(((Fl_Scrollbar*)o)->value()), s->yposition());
}

void Fl_Workspace::position(int X, int Y) 
{
	int dx = xposition_-X;
	int dy = yposition_-Y;
	if (!dx && !dy) return;
	
	xposition_ = X;
	yposition_ = Y;
	
	layoutdx += dx;
	layoutdy += dy;
	
	relayout();		
}

int Fl_Workspace::handle(int ev)
{
    if(Fl::event_inside(vscrollbar->x(), vscrollbar->y(), vscrollbar->w(), vscrollbar->h()))
        if(vscrollbar->send(ev)) return 1;

    if(Fl::event_inside(hscrollbar->x(), hscrollbar->y(), hscrollbar->w(), hscrollbar->h()))
        if(hscrollbar->send(ev)) return 1;

    return Fl_WorkType::handle(ev);
}

void Fl_Workspace::draw()
{
    viewport()->redraw();
    draw_frame();

    // draw the scrollbars:
    if(damage() & FL_DAMAGE_ALL) {
        vscrollbar->set_damage(FL_DAMAGE_ALL);
        hscrollbar->set_damage(FL_DAMAGE_ALL);
        if(vscrollbar->visible() && hscrollbar->visible()) {
            // fill in the little box in the corner
            fl_color(button_color());
            fl_rectf(vscrollbar->x(),hscrollbar->y(),vscrollbar->w(),hscrollbar->h());
        }
    }
    update_child(*vscrollbar);
    update_child(*hscrollbar);
}

void Fl_Workspace::layout()
{
    Fl_Widget::layout();
    if(viewport()->maximum()) {
        vscrollbar->clear_visible(); hscrollbar->clear_visible();
        viewport()->resize(0, 0, w(), h());
        viewport()->layout();
        return;
    }

    const int sw = scrollbar_width();

    int X=0; int Y=0; int W=w(); int H=h();

    int dx = layoutdx;
    int dy = layoutdy;
    viewport()->scrolldx(dx);
    viewport()->scrolldy(dy);
    layoutdx = layoutdy = 0;

    int mL = 0;	//Left most pos
    int mR = w()-box()->dw();//Right most pos
    int mT = 0;	//Top most pos
    int mB = h()-box()->dh();//Bottom most pos

    if(vscrollbar->visible()) { mR-=sw; }
    if(hscrollbar->visible()) { mB-=sw; }

    // Viewport box
    int viewW = w()-box()->dw(), viewH = h()-box()->dh();

    for(int n = viewport()->children(); n--;) {
        Fl_Widget* o = viewport()->child(n);
        if(!o->visible()) continue;

        o->position(o->x()+dx, o->y()+dy);
        o->layout();
        if(o->x() < mL) mL = o->x();
        if(o->y() < mT) mT = o->y();
        if(o->x()+o->w() > mR) mR = o->x()+o->w();
        if(o->y()+o->h() > mB) mB = o->y()+o->h();
    }

    // See if children would fit if we had no scrollbars...
    X=0, Y=0, W=w(), H=h();

    if(vscrollbar->visible()) { viewW-=sw; }
    if(hscrollbar->visible()) { viewH-=sw; }

    int vneeded = 0;
    int hneeded = 0;
    if(type() & VERTICAL) {
        if((type() & ALWAYS_ON) || mT < 0 || mB > viewH) {
            vneeded = 1;
            W -= sw;
            if(scrollbar_align() & FL_ALIGN_LEFT) {
                X += sw;
            }
        }
    }

    if(type() & HORIZONTAL) {
        if((type() & ALWAYS_ON) || mL < 0 || mR > viewW) {
            hneeded = 1;
            H -= sw;
            if(scrollbar_align() & FL_ALIGN_TOP)
                Y += sw;
            // recheck vertical since we added a horizontal scrollbar
            if (!vneeded && (type() & VERTICAL)) {
                if(mT < 0 || mB > viewH) {
                    vneeded = 1;
                    W -= sw;
                    if(scrollbar_align() & FL_ALIGN_LEFT)
                        X += sw;
                }
            }
        }
    }

    // Now that we know what's needed, make it so.
    if (vneeded) {
        if(!vscrollbar->visible()) {
            vscrollbar->set_visible();
            redraw(FL_DAMAGE_ALL);
        }
    } else {
        if(vscrollbar->visible()) {
            vscrollbar->clear_visible();
            redraw(FL_DAMAGE_ALL);
        }
    }

    if (hneeded) {
        if(!hscrollbar->visible()) {
            hscrollbar->set_visible();
            redraw(FL_DAMAGE_ALL);
        }
    } else {
        if(hscrollbar->visible()) {
            hscrollbar->clear_visible();
            redraw(FL_DAMAGE_ALL);
        }
    }

    box()->inset(X,Y,W,H);
    vscrollbar->resize(scrollbar_align()&FL_ALIGN_LEFT ? X-sw : X+W, Y, sw, H);
    vscrollbar->value(yposition_ = (0-mT), viewH, 0, mB-mT);
    hscrollbar->resize(X, scrollbar_align()&FL_ALIGN_TOP ? Y-sw : Y+H, W, sw);
    hscrollbar->value(xposition_ = (0-mL), viewW, 0, mR-mL);

    _viewport->resize(X, Y, viewW, viewH);
    _viewport->layout();

    viewport()->redraw(FL_DAMAGE_SCROLL);
}

void Fl_Workspace::bbox(int& X, int& Y, int& W, int& H)
{
    X = 0; Y = 0; W = w(); H = h(); box()->inset(X,Y,W,H);
    if(vscrollbar->visible()) {
        W -= vscrollbar->w();
        if(scrollbar_align() & FL_ALIGN_LEFT)
            X += vscrollbar->w();
    }
    if(hscrollbar->visible()) {
        H -= hscrollbar->h();
        if(scrollbar_align() & FL_ALIGN_TOP)
            Y += hscrollbar->h();
    }
}

void Fl_Workspace::tileH()
{
    int count = viewport()->cnt_windows();
    if( !count )
        return;

    int i=0;
    int m_height = height() / count;
    int m_width = width() -1;
    int f_x = 0;
    int f_y = 0;

    Fl_Widget *widget;
    while( i<viewport()->children() )
    {
        widget = viewport()->child(i);
        if(((widget->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW) && widget->visible())
        {
            Fl_MDI_Window *w = (Fl_MDI_Window *)widget;
            if(!w->minimized() && w->visible())
            {
                w->resize(f_x,f_y,m_width,m_height);
                f_y += m_height;
                w->_maximized = false;
                w->relayout();
            }
        }
        i++;
    }
	viewport()->maximum(0);
}

void Fl_Workspace::tileV()
{
    int count = viewport()->cnt_windows();
    if( !count )
        return;

    int i=0;
    int m_height = height();
    int m_width = width() / count;
    int f_x = 0;
    int f_y = 0;

    Fl_Widget *widget;
    while( i<viewport()->children() )
    {
        widget = viewport()->child(i);
        if(((widget->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW) && widget->visible())
        {
            Fl_MDI_Window *w = (Fl_MDI_Window *)widget;
            if(!w->minimized() && w->visible())
            {
                w->resize(f_x,f_y,m_width,m_height);
                f_x += m_width;
                w->_maximized = false;
                w->relayout();
            }
        }
        i++;
    }
    viewport()->maximum(0);
}

void Fl_Workspace::cascade()
{
    int count = viewport()->cnt_windows();
    if( !count )
        return;

    int i=0;
	int f_x=0, f_y=0;
    Fl_Widget *widget;
    while(i<viewport()->children())
    {
        widget = viewport()->child(i);
        if(((widget->flags() & FL_MDI_WINDOW) == FL_MDI_WINDOW) && widget->visible())
        {
            Fl_MDI_Window *w = (Fl_MDI_Window *)widget;
            if(!w->minimized() && w->visible())
            {
                w->resize(f_x, f_y, width()-(width()/4), height()-(height()/4));
                f_x += w->titlebar()->h()+1;
				f_y += w->titlebar()->h()+1;

                w->_maximized = false;
                w->relayout();
            }
        }
        i++;
    }
	viewport()->maximum(0);
}

