#ifndef FL_WM_H_
#define FL_WM_H_

#include "x.h"

class Fl_WM
{
    Fl_WM() {}
public:
    ///////////////
    // Set functions:

    static bool set_window_strut(Window xid, int left, int right, int top, int bottom);

    // Types for set_window_type function
    enum {
        NORMAL=1,
        DIALOG,
        UTIL,
        TOOLBAR,
        DOCK,
        SPLASH,
        MENU,
        DESKTOP
    };
    static bool set_window_type(Window xid, int type);

    ////////////////
    // Get functions:

    static bool get_geometry(int &width, int &height);
    static bool get_workarea(int &x, int &y, int &width, int &height);

};

#endif
