/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_WORKSPACE_H_
#define _FL_WORKSPACE_H_

#include "Fl_Window.h"
#include "Fl_Scrollbar.h"
#include "Fl_Menu_Bar.h"
#include "fl_draw.h"
#include "Fl.h"
#include "x.h"

class FL_API Fl_MDI_Bar;
class FL_API Fl_MDI_Window;
class FL_API Fl_Workspace;

#define FL_MDI_WINDOW 0x01000000

typedef Fl_Group Fl_WorkType;
typedef Fl_Window Fl_ViewportType;

 /*! 
   *  Viewport is MDI window container. It handles most common MDI needs like:
   *    - Redrawing all in once
   *	- Relayouting all in once
   *	- Attach / Detach window
   *	- Always on top window
   *	- Maximum window
   *	
   *  Viewport can be "scrolled", using scrolld* functions. These will only move all childrens in layout, according dx and dy.
   *  See FLE_WorkSpace for information about that.
   *
   *  Basically Viewport is only used, if you dont want nothing special in mdi container, like scrollbars.
   *  For more container advanced See FLE_WorkSpace
   */
class Fl_MDI_Viewport : public Fl_ViewportType
{	
public:
    static Fl_Named_Style* default_style;

    /*!
     Constructs widget with given coordinates.
     */
    Fl_MDI_Viewport(int x, int y, int w, int h, const char *label = 0);

    /*!
     Deletes widget and all its children.
     */
    virtual ~Fl_MDI_Viewport() { }

    /*!
     Force to redraw all MDI windows
     */
    void redraw_all();
    /*!
     Force to relayout all MDI windows
     */
    void relayout_all();

	/*!	
	*/
	void taskbar(Fl_MDI_Bar *bar);
	Fl_MDI_Bar *taskbar();

    /*!
     @param caption As a string to match with window caption.
     Finds MDI window by titlebar caption.

     Returns pointer to window if found, otherwise 0.
     */
    Fl_MDI_Window *find(const char *caption);

    /*!
     @param win As window to attach.
     Attachs MDI window.
     */
    void attach(Fl_MDI_Window *win);
    /*!
     @param win As window to detach.
     Detachs MDI window. (makes it toplevel)
     */
    void detach(Fl_MDI_Window *w);

    /*!
     Closes all MDI windows.
     */
    void close_all();

    /*!
     Returns "Always On Top" MDI window.
     @see aot(Fl_MDI_Window *win)
     */
    Fl_MDI_Window *aot() { return _aot; }
    /*!
     @param win As MDI window to set.
     Sets "Always On Top" MDI window. And relayouts viewport.
     @see aot()
     */
    void aot(Fl_MDI_Window *win) { _aot = win; relayout(); }

    /*!
     Returns "Maximum" MDI window, if there is one.

     Otherwise returns 0
     @see maximum(Fl_MDI_Window *w)
     */
    Fl_MDI_Window *maximum() { return _max; }
    /*!
     @param win As MDI window to set.
     Sets "Maximum" MDI window.
     @see maximum()
     */
    void maximum(Fl_MDI_Window *win);

    /*!
     @param win As a MDI window to set.
     Activate and set MDI window to top of the window stack.
     @see top()
     */
    void top(Fl_MDI_Window *win);
    /*!
     Returns current active window.
     @see top(Fl_MDI_Window *win)
     */
    Fl_MDI_Window *top() { return _top; }

    /*!
     Returns number of all visible MDI windows.
     */
    int cnt_windows();

    /*!
     Cycles windows, sets next window to active.
     @see top(Fl_MDI_Window *win)
     */
    void cycle_windows();

    /*!
     @param dy As a +/- pixels to move all children
     This will move childrens vertically by dy, when layout gets called next time.
     Please, DO NOT use this, unless you are knowing what yuo are doing.
     @see scrolldx(int dx)
     */
    void scrolldy(int dy) { _scrolldy+=dy; }
    /*!
     @param dx As a +/- pixels to move all children
     This will move childrens horizontally by dx, when layout gets called next time.
     Please, DO NOT use this, unless you are knowing what yuo are doing.
     @see scrolldy(int dy)
     */
    void scrolldx(int dx) { _scrolldx+=dx; }

    /*!
     This is called, when widget changes its size or relayout called by user.
     This makes sure that aot window is actually always on top. And layouts minimized windows
     to left-bottom corner of viewport. If you override this, you should call this at the beginning
     of function.
     */
    virtual void layout();
    /*!
     @param ev As a FLTK event number passed to function
     This handles only keyboard clicks. If you override this and want ALT+TAB cycles windows
     you should call this also.
     */
    virtual int handle(int ev);
    /*!
     Draws all MDI windows and other childrens.
     */
    virtual void draw();

    /*!
     Set or get menubar, where min/max/close buttons are located when maximized
    */
    void menu(Fl_Menu_Bar *menu) { _menu = menu; }
    Fl_Menu_Bar *menu() { return _menu; }

private:
    friend class Fl_MDI_Window;

    Fl_Menu_Bar *_menu;
	Fl_MDI_Bar *_bar;

    Fl_MDI_Window *_aot; //Always On Top
    Fl_MDI_Window *_max; //Maximized
    Fl_MDI_Window *_top; //Top most, active

    // For scrolling:
    static void cb_draw_clip(void*,int,int,int,int);
    void draw_clip(int,int,int,int);
    int _scrolldx, _scrolldy;
};

/*!
 *  Workspace is advanced MDI window container. It handles some special MDI needs like:
 *    - Tiling (V/H)
 *    - Cascade
 *    - Scrollbars if window(s) outside of viewport
 *
 *  Workspace normally used in every program as a MDI container, not Fl_MDI_Viewport.
 *  This can handle larger workareas very easily, e.g. viewport is only 640x480, can
 *  whole workspace be 2048x1024.
 *
 *  Workspace wraps most of viewports functions, so this can be used like a viewport.
 *  It also provides backward compatibility.
 */
class Fl_Workspace : public Fl_WorkType  {
public:
    static Fl_Named_Style* default_style;

    /*!
     Constructs widget with given coordinates.
     */
    Fl_Workspace(int x, int y, int w, int h, const char *label = 0);
    /*!
     Deletes widget and all its children.
     */
    virtual ~Fl_Workspace();

    //@{
    /*!
     Wraps viewport functionality. And provides backward compatibility.
     @see Fl_MDI_Viewport
     */
    void begin() { viewport()->begin(); }
    void end()   { viewport()->end(); }

    void redraw_all()   { viewport()->redraw_all(); }
    void relayout_all() { viewport()->relayout_all(); }

    Fl_MDI_Window *find(const char *caption) { return viewport()->find(caption); }

    void attach(Fl_MDI_Window *win) { viewport()->attach(win); }
    void detach(Fl_MDI_Window *win) { viewport()->detach(win); }

    void close_all() { _viewport->close_all(); }

    Fl_MDI_Window *aot() { return viewport()->aot(); }
    void aot(Fl_MDI_Window *win) { viewport()->aot(win); }

    Fl_MDI_Window *maximum() { return viewport()->maximum(); }
    void maximum(Fl_MDI_Window *win) { viewport()->maximum(win); }

    void top(Fl_MDI_Window *win) { viewport()->top(win); }
    Fl_MDI_Window *top() { return viewport()->top(); }

    void menu(Fl_Menu_Bar *menu) { viewport()->menu(menu); }
    Fl_Menu_Bar *menu() { return viewport()->menu(); }

    //@}

    /*!
     Cascade layout all visible MDI windows.
     */
    void cascade();

    /*!
     Vertical tile layout all visible MDI windows.
     */
    void tileV();
    /*!
     Horizontal tile layout all visible MDI windows.
     */
    void tileH();
    /*!
     Wraps horizontal tile layout.
     @see tileH()
     */
    void tile() { tileH();}

    /*!
     @param val Is either True or False.

     Moves viewport position, if focused window is outside of viewport visible area.
     @see focus_moves_pos()
     */
    void focus_moves_pos(bool val);
    /*!
     Returns value setted by focus_moves_pos(bool val).
     @see focus_moves_pos(bool val)
     */
    bool focus_moves_pos() { return move_pos; }

    Fl_MDI_Viewport *viewport() { return _viewport; }

    /*!
     values for type()
     */
    enum {
        HORIZONTAL = 1,			/**< Show horizontal scrollbar, if needed */
        VERTICAL = 2,			/**< Show vertical scrollbar, if needed */
        BOTH = 3,				/**< Show both scrollbars, if needed */
        ALWAYS_ON = 4,
        HORIZONTAL_ALWAYS = 5,	/**< Horizontal scrollbar always visible */
        VERTICAL_ALWAYS = 6,	/**< Vertical scrollbar always visible */
        BOTH_ALWAYS = 7			/**< Both scrollbars always visible  */
    };

    /*!
     Moves viewport to show active window, if outside of workarea.
     @see show_window(Fl_MDI_Window *win)
     */
    void show_window() { show_window(viewport()->top()); }
    /*!
     @param win As a MDI window to show
     Moves viewport to show window, if outside of workarea.
     @see show_window()
     */
    void show_window(Fl_MDI_Window *win);

    /*!
     Returns X position of viewport
     @see yposition() and position(int x, int y)
     */
    int xposition() const {return xposition_;}
    /*!
     Returns Y position of viewport
     @see xposition() and position(int x, int y)
     */
    int yposition() const {return yposition_;}
    /*!
     Sets X and Y position of viewport and moves it to that position straight away.
     @see yposition() and xposition()
     */
    void position(int x, int y);

    /*!
     This is called, when widget changes its size or relayout called by user.
     Keeps track of visibility of scrollbars. Calculates viewport size.
     */
    virtual void layout();
    /*!
     Redirect events to scrollbars, if needed.
     */
    virtual int handle(int ev);
    /*!
     Draws scrollbars and call Fl_MDI_Viewport to draw MDI windows
     */
    virtual void draw();

private:
    static void cb_hscrollbar(Fl_Widget *o, void *d);
    static void cb_vscrollbar(Fl_Widget *o, void *d);

    void bbox(int&,int&,int&,int&);

    Fl_MDI_Viewport *_viewport;

    int xposition_, yposition_;
    int layoutdx, layoutdy;

    Fl_Scrollbar *vscrollbar;
    Fl_Scrollbar *hscrollbar;

    bool move_pos;
};

#endif
