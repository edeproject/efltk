#ifndef FL_WM_H_
#define FL_WM_H_

#include "Fl_Widget.h"
#include "x.h"

class Fl_WM
{
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
    static bool set_window_icon(Window xid, Fl_Image *icon);
    static bool set_window_title(Window xid, char *title, int title_len);
    static bool set_window_icontitle(Window xid, char *title, int title_len);

    static bool set_workspace_count(int count);
    static bool set_workspace_names(const char **names, int count);
    static bool set_current_workspace(int number);
    static bool set_active_window(Window xid);

    ////////////////
    // Get functions:

    static bool get_window_icon(Window xid, Fl_Image *&icon, int w, int h);
    static bool get_window_title(Window xid, char *&title);
    static bool get_window_icontitle(Window xid, char *&title);

    static bool get_geometry(int &width, int &height);
    static bool get_workarea(int &x, int &y, int &width, int &height);

    static int get_windows_stacking(Window *&windows);
    static int get_windows_mapping(Window *&windows);
    static int get_workspace_count();
    static int get_workspace_names(char **&names);
    static int get_current_workspace();
    static Window get_active_window();

    ////////////////
    // Callback:

    //Actions:
    enum {
        NONE=0,
        DESKTOP_COUNT    = 0x0000001,
        DESKTOP_NAMES    = 0x0000002,
        DESKTOP_CHANGED  = 0x0000004,
        DESKTOP_WORKAREA = 0x0000008,

        WINDOW_LIST          = 0x0001000,
        WINDOW_LIST_STACKING = 0x0002000,
        WINDOW_ACTIVE        = 0x0004000,
        WINDOW_NAME          = 0x0008000,
        WINDOW_NAME_VISIBLE  = 0x0010000,
        WINDOW_DESKTOP       = 0x0020000
    };
    // Set callback and action mask, callback is only done, when receiving action defined in mask.
    static void callback(Fl_Callback *cb, void *user_data, int action_mask);
    static int action();
    static Window window();
};

#endif
