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

#ifndef _FL_WM_H_
#define _FL_WM_H_

#include "Fl_Widget.h"
#include "x.h"

/**
 * The window manager module for eFLTK.
 * You can set and get information from WM with this class.
 * Currently only X11 is supported. NOTE: many of features are supported only NET-WM window managers.
 * Known NET-WM window managers: KDE 2>, GNOME 2>, EDE
 */
class Fl_WM
{
public:
    /**
     * Types for set_window_type function.
     */
    enum WindowTypes {
        NORMAL=1,
        DIALOG,
        UTIL,
        TOOLBAR,
        DOCK,
        SPLASH,
        MENU,
        DESKTOP
    };

    /**
     * Set type of window.
     * Returns true on success.
     * @see enum WindowTypes
     */
    static bool set_window_type(Window xid, int type);

    /**
     * Set application icon for window. This does use X11 standard WMHints, so most of window managers will support this.
     * Returns true on success.
     */
    static bool set_window_icon(Window xid, Fl_Image *icon);

    /**
     * Set window title text. The one shown in titlebar.
     * Returns true on success.
     */
    static bool set_window_title(Window xid, const char *title, int title_len);

    /**
     * Set window icon title text. The one shown in taskbar.
     * Returns true on success.
     */
    static bool set_window_icontitle(Window xid, const char *title, int title_len);

    /**
     * Set number of workspaces, in NET-WM compliant WM.
     * Returns true on success.
     * @param count number of workspaces.
     */
    static bool set_workspace_count(int count);

    /**
     * Set names to workspaces.
     * Returns true on success.
     * @param names list of names to set
     * @param count number of names in list
     */
    static bool set_workspace_names(const char **names, int count);

    /**
     * Set current active workspace.
     * Returns true on success.
     */
    static bool set_current_workspace(int number);

    /**
     * Set current active window. NET-WM only.
     * Returns true on success.
     */
    static bool set_active_window(Window xid);

    /**
     * Set window strut, i.e. reserve some space from workspace, so e.g. maximized windows doesn't overlap it.
     * Returns true on success.
     * Used commonly in taskbars (panels). NET-WM only.
     */
    static bool set_window_strut(Window xid, int left, int right, int top, int bottom);

    /**
     * Get icon for window. icon is allocated by eFLTK and MUST be freed with delete operator.
     * Returns true on success.
     * @param icon is stored to this.
     * @param w,h preferred size of icon, use -1 for default iconsize.
     */
    static bool get_window_icon(Window xid, Fl_Image *&icon, int w=-1, int h=-1);

    /**
     * Get title text for window. title is allocated by eFLTK and must be freed with free() function.
     * Returns true on success.
     */
    static bool get_window_title(Window xid, char *&title);

    /**
     * Get icon title text for window. title is allocated by eFLTK and must be freed with free() function.
     * Returns true on success.
     */
    static bool get_window_icontitle(Window xid, char *&title);

    /**
     * Get desktop where window is placed on.
     * Returns: -2=ERROR, -1=STICKY, 0> number of desktop. NET-WM only
     */
    static int get_window_desktop(Window xid);

    /**
     * Get width and height of workspace.
     * Returns true on success. NET-WM only
     */
    static bool get_geometry(int &width, int &height);

    /**
     * Get area of workspace, window struts are subtracted from this.
     * Returns true on success. NET-WM only
     */
    static bool get_workarea(int &x, int &y, int &width, int &height);

    /**
     * Get WM windows in stacking order. windows is allocated by eFLTK and MUST be freed with free() function.
     * This is used mostly by pagers or taskbars.
     * Returns number windows stored in list 'windows'. NET-WM only
     */
    static int get_windows_stacking(Window *&windows);

    /**
     * Get WM windows in mapping order. windows is allocated by eFLTK and MUST be freed with free() function.
     * This is used mostly by pagers or taskbars.
     * Returns number windows stored in list 'windows'. NET-WM only
     */
    static int get_windows_mapping(Window *&windows);

    /**
     * Returns number of workspaces. NET-WM only
     */
    static int get_workspace_count();

    /**
     * Get workspace names. names are stored in variable 'names'. names is allocated by eFLTK and MUST be freef with free() function.
     * Returns number of names in list 'names'. NET-WM only.
     */
    static int get_workspace_names(char **&names);

    /**
     * Returns current number of workspace. NET-WM only.
     */
    static int get_current_workspace();

    /**
     * Returns current active window in WM. NET-WM only.
     */
    static Window get_active_window();

    /**
     * Types of callback actions.
     * @see add_callback(Fl_Callback *cb, void *user_data, int action_mask)
     */
    enum ActionTypes {
        NONE = 0,
        DESKTOP_COUNT    = 1<<0,
        DESKTOP_NAMES    = 1<<1,
        DESKTOP_CHANGED  = 1<<2,
        DESKTOP_WORKAREA = 1<<3,

        WINDOW_LIST          = 1<<10,
        WINDOW_LIST_STACKING = 1<<11,
        WINDOW_ACTIVE        = 1<<12,
        WINDOW_NAME          = 1<<13,
        WINDOW_NAME_VIS      = 1<<14,
        WINDOW_ICONNAME      = 1<<15,
        WINDOW_ICONNAME_VIS  = 1<<16,
        WINDOW_DESKTOP       = 1<<17
    };

    /**
     * Clear list of handled windows.
     */
    static void clear_handled();

    /**
     * Returns true, if window 'w' is handled.
     */
    static bool is_handled(Window w);

    /**
     * Handle window 'w'. NOTE: You must call this, in order to receive events from window.
     */
    static void handle_window(Window w);

    /**
     * Remove handled window 'w'
     */
    static void unhandle_window(Window w);

    /*
     * Set callback function and action mask.
     * Callback is only done, when received event defined in action mask.
     * user_data is passed to callback function.
     */
    static void add_callback(Fl_Callback *cb, void *user_data, int action_mask);

    /**
     * Remove callback function from list.
     */
    static void remove_callback(Fl_Callback *cb, void *user_data);

    /**
     * Returns last action (event) happened.
     */
    static int action();

    /**
     * Returns window where last event received.
     */
    static Window window();

    /**
     * compatibility
     * @see add_callback(Fl_Callback *cb, void *user_data, int action_mask)
     */
    static void callback(Fl_Callback *cb, void *user_data, int action_mask) {
        add_callback(cb, user_data, action_mask);
    }
};

#endif
