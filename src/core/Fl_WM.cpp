#include <efltk/Fl_WM.h>

#include <X11/Xproto.h> //For CARD32

uchar* getProperty(Window w, Atom a, Atom type, unsigned long *np, int *ret=0)
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

Atom _XA_NET_SUPPORTED; 
Atom _XA_NET_SUPPORTING_WM_CHECK;

Atom _XA_NET_DESKTOP_GEOMETRY;
Atom _XA_NET_WORKAREA;

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

static bool atoms_inited = false;

static void init_atoms()
{
    if(atoms_inited) return;

    struct {
        Atom *atom;
        const char *name;
    } atom_info[] = {
        { &_XA_NET_SUPPORTED,       "_NET_SUPPORTED" },
        { &_XA_NET_DESKTOP_GEOMETRY,"_NET_DESKTOP_GEOMETRY" },
        { &_XA_NET_WORKAREA,        "_NET_WORKAREA" },
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

