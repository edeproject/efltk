#ifndef _FL_MDIWINDOW_H
#define _FL_MDIWINDOW_H

#include "Fl_Workspace.h"
#include "Fl_Util.h"
#include "Fl_Group.h"
#include "Fl_Window.h"
#include "Fl_Box.h"
#include "Fl_Button.h"
#include "Fl.h"

#include <string.h>

#define NO_RESIZE   -1
#define TOP	    0
#define BOTTOM	    1
#define RIGHT	    2
#define LEFT	    3
#define RIGHTTOP    4
#define RIGHTBOTTOM 5
#define LEFTTOP     6
#define LEFTBOTTOM  7

class Fl_MDI_Window;

class Fl_MDI_Titlebar : public Fl_Group {
    friend class Fl_MDI_Window;
public:
    static Fl_Named_Style* default_style;

    Fl_MDI_Titlebar(int x,int y,int w,int h,const char *l=0);

    virtual void draw();
    virtual int handle(int event);
    virtual void layout();

    static int ex,ey;
    static int old_rx,old_ry;

    Fl_Button *close() { return &_close; }
    Fl_Button *min() { return &_min; }
    Fl_Button *max() { return &_max; }

protected:
    Fl_Button _close, _max, _min;
    Fl_MDI_Window *_owner;
};

class Fl_MDI_Window : public Fl_Window {
    friend class Fl_MDI_Viewport;
    friend class Fl_Workspace;
    friend class Fl_MDI_Titlebar;
public:
    static Fl_Named_Style* default_style;

    Fl_MDI_Window(int x, int y, int w, int h, const char *label);
    virtual ~Fl_MDI_Window();

    bool active() { return _active; }
    void active(bool a) { _active = a; }
		
    // Set/get view
    Fl_Group *view(Fl_Group *v); //returns old view
    Fl_Group *view() { return prv; }

    void resizable(Fl_Widget *w) { prv->resizable(w); }
    void resizable(Fl_Widget &w) { prv->resizable(w); }
    Fl_Widget *resizable()       { return prv->resizable(); }

    // Caption functions
    void caption(const char *cap) { if(cap) strncpy(_cap, cap, 4096); else _cap[0]='\0'; _titlebar.redraw(); }
    void label(const char *_label) { caption(_label); }
    const char *caption() { return _cap; }
    const char *label() { return caption(); }

    //void titlebar(Fl_Box *b) { _titlebar = b; }
    Fl_MDI_Titlebar* titlebar() {return &_titlebar;}

    bool toplevel() { return _toplevel; }

    void detach();
    void attach() { attach(_owner); }
    void attach(Fl_MDI_Viewport *ws);

    void owner(Fl_MDI_Viewport *ws) { _owner = ws; }
    Fl_MDI_Viewport *owner() { return _owner; }

    void close_callback();
    void minimize(bool val);

    bool minimized() { return _minimized; }

    void setTop() { if(!_toplevel && _owner) _owner->top(this); else show(); }
    bool isTop() { return _toplevel==true ? 0 : (_owner->top()==this); }

    void maximize(bool val);
    bool maximized() { return _maximized; }

    void animate_mode(bool o) { _anim_opaque = o; }
    bool animate_mode() { return _anim_opaque; }
    void animate(bool val) { _animate = val; }
    bool animate() { return _animate; }

    void boundary_check(bool val) { _boundaries = val; }
    bool boundary_check() { return _boundaries; }

    int minw() { return _minw; }
    int minh() { return _minh; }
    void minw(int w) { _minw = w+box()->dw(); }
    void minh(int h) { _minh = h+box()->dw()+titlebar()->h(); }

protected:
    virtual int handle(int ev);
    virtual void handle_resize(int where);
    virtual void draw();
    virtual void layout();

private:
    void check_move_boundary(int &x, int &y);
    void check_size_boundary(int &w, int &h);

    void animate(int fx, int fy, int fw, int fh,
                 int tx, int ty, int tw, int th);

    //void animate_min(int mx, int my, int mw, int mh);
    //void animate_max(int mx, int my, int mw, int mh);

    void _resize(int x, int y, int w, int h);
    void _position(int x, int y);
    void minmax();

    Fl_MDI_Viewport *_owner; //Workspace who own this window.
    Fl_Group *prv;
    Fl_MDI_Titlebar _titlebar;

    char _cap[4096];

    bool _toplevel;
	bool _active;

    void h_oldsize(int w, int h) { _how = w; _hoh = h; }
    void h_oldpos(int x, int y)  { _hox = x; _hoy = y; }
    int _hox, _hoy, _how, _hoh;

    void oldsize(int w, int h) { _ow = w; _oh = h; }
    void oldpos(int x, int y)  { _ox = x; _oy = y; }
    int _ox, _oy, _oh, _ow;

    bool _boundaries;
    bool _animate;
    bool _maximized;
    bool _minimized;

    int _resize_where;

    int old_title_h, old_title_fh;

    int tx,ty,tw,th; //Box for titlebar
    int px,py,pw,ph; //Box for view

    Fl_Rect bot;
    Fl_Rect top;
    Fl_Rect left;
    Fl_Rect right;

    Fl_Rect ltcorn;
    Fl_Rect rtcorn;
    Fl_Rect lbcorn;
    Fl_Rect rbcorn;

    bool _anim_opaque;

    short _minw, _minh;
    short _maxw, _maxh;
};

#endif

