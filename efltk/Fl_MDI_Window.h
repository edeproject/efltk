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

    Fl_Button *close_button() { return &_close; }
    Fl_Button *min_button() { return &_min; }
    Fl_Button *max_button() { return &_max; }

protected:
    Fl_Button _close, _max, _min;
    Fl_MDI_Window *_owner;
};

class Fl_MDI_Window : public Fl_Window {
    friend class Fl_MDI_Viewport;
    friend class Fl_Workspace;
    friend class Fl_MDI_Titlebar;
public:
	enum {
		NORMAL = 0,
		MAXIMIZED,
		MINIMIZED
	};

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
    void caption(const char *cap);
    const char *caption() { return label(); }

    //void titlebar(Fl_Box *b) { _titlebar = b; }
    Fl_MDI_Titlebar* titlebar() {return &_titlebar;}

    bool toplevel() { return _toplevel; }

    void detach();
    void attach() { attach(_owner); }
    void attach(Fl_MDI_Viewport *ws);

    void owner(Fl_MDI_Viewport *ws) { _owner = ws; }
    Fl_MDI_Viewport *owner() { return _owner; }

    void setTop() { if(!_toplevel && _owner) _owner->top(this); else show(); }
    bool isTop() { return _toplevel==true ? 0 : (_owner->top()==this); }

	void state(int s);
	int state() { return state_; }
	
	void maximize(bool val) { state(val?MAXIMIZED:NORMAL); }
    bool maximized() { return (state_==MAXIMIZED); }
    void minimize(bool val) { state(val?MINIMIZED:NORMAL); }
    bool minimized() { return (state_==MINIMIZED); }

    static void animate_opaque(bool o) { anim_opaque_ = o; }
    static bool animate_opaque()       { return anim_opaque_; }
    static void animate(bool val)      { animate_ = val; }
    static bool animate()              { return animate_; }

    void boundary_check(bool val) { _boundaries = val; }
    bool boundary_check() { return _boundaries; }

    int minw() { return _minw; }
    int minh() { return _minh; }
    void minw(int w) { _minw = w+box()->dw(); }
    void minh(int h) { _minh = h+box()->dw()+titlebar()->h(); }

    virtual int handle(int ev);
    virtual void handle_resize(int where);
    virtual void draw();
    virtual void layout();

	static void default_callback(Fl_MDI_Window*, void* v);

private:
    void check_move_boundary(int &x, int &y);
    void check_size_boundary(int &w, int &h);

    void animate(int fx, int fy, int fw, int fh,
                 int tx, int ty, int tw, int th);

    void _resize(int x, int y, int w, int h);
    void _position(int x, int y);

    Fl_MDI_Viewport *_owner; //Workspace who own this window.
    Fl_Group *prv;
    Fl_MDI_Titlebar _titlebar;

    bool _toplevel;
	bool _active;

    int _ox, _oy, _oh, _ow;

    bool _boundaries;
	int state_;

    int _resize_where;

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

    static bool anim_opaque_;
    static bool animate_;

    short _minw, _minh;
    short _maxw, _maxh;

    void add_menu_buttons();
    void delete_menu_buttons();
};

#endif

