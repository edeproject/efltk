#include <efltk/Fl_WM.h>

#ifndef _WIN32

#include <efltk/Fl.h>

#include <X11/Xproto.h> //For CARD32

#include <stdlib.h>
#include <string.h>

Atom _XA_NET_SUPPORTED; 
Atom _XA_NET_SUPPORTING_WM_CHECK;

// DESKTOP actions:
Atom _XA_NET_NUM_DESKTOPS;
Atom _XA_NET_DESKTOP_NAMES;
Atom _XA_NET_CURRENT_DESKTOP;
Atom _XA_NET_WORKAREA;

// WINDOW actions:
Atom _XA_NET_CLIENT_LIST;
Atom _XA_NET_CLIENT_LIST_STACKING;
Atom _XA_NET_ACTIVE_WINDOW;
Atom _XA_NET_WM_NAME;
Atom _XA_NET_WM_VISIBLE_NAME;
Atom _XA_NET_WM_DESKTOP;

Atom _XA_NET_DESKTOP_GEOMETRY;

Atom _XA_NET_WM_WINDOW_TYPE;
Atom _XA_NET_WM_WINDOW_TYPE_DESKTOP;
Atom _XA_NET_WM_WINDOW_TYPE_DOCK;
Atom _XA_NET_WM_WINDOW_TYPE_TOOLBAR;
Atom _XA_NET_WM_WINDOW_TYPE_MENU;
Atom _XA_NET_WM_WINDOW_TYPE_UTIL;
Atom _XA_NET_WM_WINDOW_TYPE_SPLASH;
Atom _XA_NET_WM_WINDOW_TYPE_DIALOG;
Atom _XA_NET_WM_WINDOW_TYPE_NORMAL;

Atom _XA_NET_WM_STRUT;

uchar* getProperty(Window w, Atom a, Atom type, unsigned long *np=0, int *ret=0)
{
    Atom realType;
    int format;
    unsigned long n, extra;
    int status;
    uchar *prop;
    status = XGetWindowProperty(fl_display, w, a, 0L, 0x7fffffff,
                                False, type, &realType,
                                &format, &n, &extra, (uchar**)&prop);
    if(ret) *ret = status;
    if (status != Success) return 0;
    if (!prop) { return 0; }
    if (!n) { XFree(prop); return 0; }
    if (np) *np = n;
    return prop;
}

int getIntProperty(Window w, Atom a, Atom type, int deflt) {
    void* prop = getProperty(w, a, type);
    if(!prop) return deflt;
    int r = int(*(long*)prop);
    XFree(prop);
    return r;
}

int sendClientMessage(Window w, Atom a, long x)
{
    XEvent ev;
    long mask;
    memset(&ev, 0, sizeof(ev));
    ev.xclient.type = ClientMessage;
    ev.xclient.window = w;
    ev.xclient.message_type = a;
    ev.xclient.format = 32;
    ev.xclient.data.l[0] = x;
    ev.xclient.data.l[1] = CurrentTime;
    mask = 0L;
    if(w == RootWindow(fl_display, fl_screen)) mask = SubstructureRedirectMask;
    return XSendEvent(fl_display, RootWindow(fl_display, fl_screen), False, mask, &ev);
}

static void init_atoms()
{
    static bool atoms_inited = false;
    if(atoms_inited) return;
    fl_open_display();

    struct {
        Atom *atom;
        const char *name;
    } atom_info[] = {
        { &_XA_NET_SUPPORTED,       "_NET_SUPPORTED" },

        { &_XA_NET_DESKTOP_GEOMETRY,"_NET_DESKTOP_GEOMETRY" },

        // DESKTOP actions:
        { &_XA_NET_NUM_DESKTOPS,    "_NET_NUMBER_OF_DESKTOPS" },
        { &_XA_NET_DESKTOP_NAMES,   "_NET_DESKTOP_NAMES" },
        { &_XA_NET_CURRENT_DESKTOP, "_NET_CURRENT_DESKTOP" },
        { &_XA_NET_WORKAREA,        "_NET_WORKAREA" },

        // WINDOW actions:
        { &_XA_NET_CLIENT_LIST,     "_NET_CLIENT_LIST" },
        { &_XA_NET_CLIENT_LIST_STACKING, "_NET_CLIENT_LIST_STACKING" },
        { &_XA_NET_ACTIVE_WINDOW,   "_NET_ACTIVE_WINDOW" },
        { &_XA_NET_WM_NAME,         "_NET_WM_NAME" },
        { &_XA_NET_WM_VISIBLE_NAME, "_NET_WM_VISIBLE_NAME" },
        { &_XA_NET_WM_DESKTOP,      "_NET_WM_DESKTOP" },


        { &_XA_NET_WM_WINDOW_TYPE,  "_NET_WM_WINDOW_TYPE" },
        { &_XA_NET_WM_WINDOW_TYPE_DESKTOP, "_NET_WM_WINDOW_TYPE_DESKTOP" },
        { &_XA_NET_WM_WINDOW_TYPE_DOCK,    "_NET_WM_WINDOW_TYPE_DOCK" },
        { &_XA_NET_WM_WINDOW_TYPE_TOOLBAR, "_NET_WM_WINDOW_TYPE_TOOLBAR" },
        { &_XA_NET_WM_WINDOW_TYPE_MENU,    "_NET_WM_WINDOW_TYPE_MENU" },
        { &_XA_NET_WM_WINDOW_TYPE_UTIL,    "_NET_WM_WINDOW_TYPE_UTILITY" },
        { &_XA_NET_WM_WINDOW_TYPE_SPLASH,    "_NET_WM_WINDOW_TYPE_SPLASH" },
        { &_XA_NET_WM_WINDOW_TYPE_DIALOG,  "_NET_WM_WINDOW_TYPE_DIALOG" },
        { &_XA_NET_WM_WINDOW_TYPE_NORMAL,  "_NET_WM_WINDOW_TYPE_NORMAL" },
        { &_XA_NET_WM_STRUT,       "_NET_WM_STRUT" }
    };

#define CNT(x) (sizeof(x)/sizeof(x[0]))
    unsigned int i;
    for(i = 0; i < CNT(atom_info); i++) {
        *(atom_info[i].atom) = XInternAtom(fl_display, atom_info[i].name, False);
    }

    atoms_inited = true;
}

bool Fl_WM::set_window_strut(Window xid, int left, int right, int top, int bottom)
{
    init_atoms();

    CARD32 strut[4] = { left, right, top, bottom };
    int status = XChangeProperty(fl_display, xid, _XA_NET_WM_STRUT, XA_CARDINAL, 32,
                                 PropModeReplace, (unsigned char *)&strut, sizeof(CARD32)*4);
    return (status==Success);
}

bool Fl_WM::set_window_type(Window xid, int type)
{
    init_atoms();

    Atom wintype[1];
    switch(type) {
    case DIALOG:
        wintype[0] = _XA_NET_WM_WINDOW_TYPE_DIALOG;
        break;
    case UTIL:
        wintype[0] = _XA_NET_WM_WINDOW_TYPE_UTIL;
        break;
    case TOOLBAR:
        wintype[0] = _XA_NET_WM_WINDOW_TYPE_TOOLBAR;
        break;
    case DOCK:
        wintype[0] = _XA_NET_WM_WINDOW_TYPE_DOCK;
        break;
    case SPLASH:
        wintype[0] = _XA_NET_WM_WINDOW_TYPE_SPLASH;
        break;
    case MENU:
        wintype[0] = _XA_NET_WM_WINDOW_TYPE_MENU;
        break;
    case DESKTOP:
        wintype[0] = _XA_NET_WM_WINDOW_TYPE_DESKTOP;
        break;
    case NORMAL:
    default:
        wintype[0] = _XA_NET_WM_WINDOW_TYPE_NORMAL;
    };

    int status = XChangeProperty(fl_display, xid, _XA_NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                                 PropModeReplace, (unsigned char *)&wintype, sizeof(Atom));
    return (status==Success);
}

bool Fl_WM::set_workspace_count(int count)
{
    init_atoms();
    int status = sendClientMessage(RootWindow(fl_display, fl_screen), _XA_NET_NUM_DESKTOPS, count);
    return (status==Success);
}

bool Fl_WM::set_workspace_names(const char **names, int count)
{
    init_atoms();
    XTextProperty wnames;
    if(XStringListToTextProperty((char **)names, count, &wnames)) {
        XSetTextProperty(fl_display, RootWindow(fl_display, fl_screen), &wnames, _XA_NET_DESKTOP_NAMES);
        XFree(wnames.value);
        return true;
    }
    return false;
}

bool Fl_WM::set_current_workspace(int number)
{
    init_atoms();
    int status = sendClientMessage(RootWindow(fl_display, fl_screen), _XA_NET_CURRENT_DESKTOP, number);
    return (status==Success);
}

/////////////////////////////////////////////

bool Fl_WM::get_geometry(int &width, int &height)
{
    init_atoms();
    unsigned long size = 0;
    int status;
    CARD32 *val;
    val = (CARD32 *)getProperty(RootWindow(fl_display, fl_screen),
                                _XA_NET_DESKTOP_GEOMETRY, XA_CARDINAL, &size, &status);
    if(status==Success && val) {
        width  = val[0];
        height = val[1];
        XFree((char*)val);
    }
    return (status==Success);
}

bool Fl_WM::get_workarea(int &x, int &y, int &width, int &height)
{
    init_atoms();

    unsigned long size = 0;
    int status;
    CARD32 *val;
    val = (CARD32 *)getProperty(RootWindow(fl_display, fl_screen),
                                _XA_NET_WORKAREA, XA_CARDINAL, &size, &status);
    if(status==Success && val) {
        x      = val[0];
        y      = val[1];
        width  = val[2];
        height = val[3];
        XFree((char*)val);
    }
    return (status==Success);
}

int Fl_WM::get_windows_stacking(Window *&windows)
{
    init_atoms();
    unsigned long size = 0;
    int status;
    windows = (Window *)getProperty(RootWindow(fl_display, fl_screen),
                                    _XA_NET_CLIENT_LIST_STACKING, XA_WINDOW, &size, &status);
    if(status!=Success || !windows) return -1;
    return size;
}

int Fl_WM::get_windows_mapping(Window *&windows)
{
    init_atoms();
    unsigned long size = 0;
    int status;
    windows = (Window *)getProperty(RootWindow(fl_display, fl_screen),
                                    _XA_NET_CLIENT_LIST_STACKING, XA_WINDOW, &size, &status);
    if(status!=Success || !windows) return -1;
    return size;
}

int Fl_WM::get_workspace_count()
{
    init_atoms();
    return getIntProperty(RootWindow(fl_display, fl_screen), _XA_NET_NUM_DESKTOPS, XA_CARDINAL, -1);
}

int Fl_WM::get_current_workspace()
{
    init_atoms();
    return getIntProperty(RootWindow(fl_display, fl_screen), _XA_NET_CURRENT_DESKTOP, XA_CARDINAL, -1);
}

int Fl_WM::get_workspace_names(char **&names)
{
    init_atoms();

    XTextProperty wnames;
    // Try to get NET desktop names
    XGetTextProperty(fl_display, RootWindow(fl_display, fl_screen), &wnames, _XA_NET_DESKTOP_NAMES);
    char *buffer = (char *)wnames.value;
    int length = wnames.nitems;
    int cnt=0;

    if(buffer) {
        names = new char*[1];

        char* c = buffer;
        for (int i = 1; c < buffer+length; i++) {
            char* d = c;
            while(*d) d++;
            if(strcmp(c, "")) {
                names[cnt++] = strdup(c);
                names = (char **)realloc(names, sizeof(char*)*(cnt+1));
            }
            c = d+1;
        }
        XFree(wnames.value);
    }
    return cnt;
}

///////////////////////////////////////////////

static Window action_window=0;
static int action=0, action_mask=0;
static Fl_Callback *callback=0;
static void *user_data=0;

static int wm_event_handler(int e)
{
    action=0;
    action_window=0;

    if(fl_xevent.type==PropertyNotify)
    {
        action_window = fl_xevent.xproperty.window;
        if(fl_xevent.xproperty.atom==_XA_NET_NUM_DESKTOPS)
            action = Fl_WM::DESKTOP_COUNT;
        else if(fl_xevent.xproperty.atom==_XA_NET_DESKTOP_NAMES)
            action = Fl_WM::DESKTOP_NAMES;
        else if(fl_xevent.xproperty.atom==_XA_NET_CURRENT_DESKTOP)
            action = Fl_WM::DESKTOP_CHANGED;
        else if(fl_xevent.xproperty.atom==_XA_NET_WORKAREA)
            action = Fl_WM::DESKTOP_WORKAREA;

        else if(fl_xevent.xproperty.atom==_XA_NET_CLIENT_LIST_STACKING)
            action = Fl_WM::WINDOW_LIST_STACKING;
        else if(fl_xevent.xproperty.atom==_XA_NET_CLIENT_LIST)
            action = Fl_WM::WINDOW_LIST;
        else if(fl_xevent.xproperty.atom==_XA_NET_ACTIVE_WINDOW)
            action = Fl_WM::WINDOW_ACTIVE;
        else if(fl_xevent.xproperty.atom==_XA_NET_WM_NAME)
            action = Fl_WM::WINDOW_NAME;
        else if(fl_xevent.xproperty.atom==_XA_NET_WM_VISIBLE_NAME)
            action = Fl_WM::WINDOW_NAME_VISIBLE;
        else if(fl_xevent.xproperty.atom==_XA_NET_WM_DESKTOP)
            action = Fl_WM::WINDOW_DESKTOP;

        if(action_mask&action)
            callback(0, user_data);

        // Reset after callback
        action=0;
        action_window=0;
    }
    return 0;
}

void Fl_WM::callback(Fl_Callback *cb, void *user_data, int mask)
{
    static bool inited=false;
    if(!inited) {
        init_atoms();
        XSelectInput(fl_display, RootWindow(fl_display, fl_screen), PropertyChangeMask);
        Fl::add_handler(wm_event_handler);
        inited=true;
    }
    ::callback = cb;
    ::user_data = user_data;
    ::action_mask = mask;
}

int Fl_WM::action() {
    return ::action;
}
Window Fl_WM::window() {
    return ::action_window;
}

#else

bool Fl_WM::set_window_strut(Window xid, int left, int right, int top, int bottom) { return false; }

bool Fl_WM::set_window_type(Window xid, int type) { return false; }

bool Fl_WM::set_workspace_count(int count) { return false; }

bool Fl_WM::set_workspace_names(const char **names, int count) { return false; }

bool Fl_WM::set_current_workspace(int number) { return false; }

bool Fl_WM::get_geometry(int &width, int &height) { return false; }

bool Fl_WM::get_workarea(int &x, int &y, int &width, int &height) { return false; }

int Fl_WM::get_windows_stacking(Window *&windows) { return -1; }

int Fl_WM::get_windows_mapping(Window *&windows) { return -1; }

int Fl_WM::get_workspace_count() { return -1; }

int Fl_WM::get_current_workspace() { return -1; }

int Fl_WM::get_workspace_names(char **&names) { return -1; }

void Fl_WM::callback(Fl_Callback *cb, void *user_data, int mask) { }
int Fl_WM::action() { return 0; }
Window Fl_WM::window() { return 0; }


#endif /* _WIN32 */
