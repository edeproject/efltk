#include <efltk/Fl_WM.h>
#include <config.h>

#ifndef _WIN32

#include <efltk/Fl.h>
#include <efltk/Fl_Util.h>
#include <efltk/Fl_Image.h>

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
Atom _XA_NET_WM_ICON_NAME;
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

#if HAVE_XUTF8
extern Atom fl_XaUtf8String;
#else
# define fl_XaUtf8String XA_STRING
#endif

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
    XEvent xev;
    memset(&xev, 0, sizeof(xev));
    xev.xclient.type = ClientMessage;
    xev.xclient.serial = 0;
    xev.xclient.send_event = True;
    xev.xclient.window = w;
    xev.xclient.display = fl_display;
    xev.xclient.message_type = a;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = x;
    xev.xclient.data.l[1] = CurrentTime;
    int ret = XSendEvent (fl_display, RootWindow(fl_display, fl_screen), False,
                          SubstructureRedirectMask | SubstructureNotifyMask,
                          &xev);
    XSync(fl_display, True);
    return ret;
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
        { &_XA_NET_SUPPORTING_WM_CHECK,"_NET_SUPPORTING_WM_CHECK" },

        // DESKTOP actions:
        { &_XA_NET_NUM_DESKTOPS,    "_NET_NUMBER_OF_DESKTOPS" },
        { &_XA_NET_DESKTOP_NAMES,   "_NET_DESKTOP_NAMES" },
        { &_XA_NET_CURRENT_DESKTOP, "_NET_CURRENT_DESKTOP" },
        { &_XA_NET_WORKAREA,        "_NET_WORKAREA" },
        { &_XA_NET_DESKTOP_GEOMETRY,"_NET_DESKTOP_GEOMETRY" },

        // WINDOW actions:
        { &_XA_NET_CLIENT_LIST,     "_NET_CLIENT_LIST" },
        { &_XA_NET_CLIENT_LIST_STACKING, "_NET_CLIENT_LIST_STACKING" },
        { &_XA_NET_ACTIVE_WINDOW,   "_NET_ACTIVE_WINDOW" },
        { &_XA_NET_WM_NAME,         "_NET_WM_NAME" },
        { &_XA_NET_WM_ICON_NAME,    "_NET_WM_ICON_NAME" },
        { &_XA_NET_WM_VISIBLE_NAME, "_NET_WM_VISIBLE_NAME" },
        { &_XA_NET_WM_DESKTOP,      "_NET_WM_DESKTOP" },

        { &_XA_NET_WM_WINDOW_TYPE,  "_NET_WM_WINDOW_TYPE" },
        { &_XA_NET_WM_WINDOW_TYPE_DESKTOP, "_NET_WM_WINDOW_TYPE_DESKTOP" },
        { &_XA_NET_WM_WINDOW_TYPE_DOCK,    "_NET_WM_WINDOW_TYPE_DOCK" },
        { &_XA_NET_WM_WINDOW_TYPE_TOOLBAR, "_NET_WM_WINDOW_TYPE_TOOLBAR" },
        { &_XA_NET_WM_WINDOW_TYPE_MENU,    "_NET_WM_WINDOW_TYPE_MENU" },
        { &_XA_NET_WM_WINDOW_TYPE_UTIL,    "_NET_WM_WINDOW_TYPE_UTILITY" },
        { &_XA_NET_WM_WINDOW_TYPE_SPLASH,  "_NET_WM_WINDOW_TYPE_SPLASH" },
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

Window fl_wmspec_check_window = None;
bool fl_netwm_supports(Atom &xproperty)
{
    static Atom *atoms = NULL;
    static int natoms = 0;

    Atom type;
    int format;
    ulong nitems;
    ulong bytes_after;
    Window *xwindow;

    if(fl_wmspec_check_window != None) {
        if(atoms == NULL)
            return false;
        for(int i=0; i<natoms; i++) {
            if (atoms[i] == xproperty)
                return true;
        }
        return false;
    }

    if(atoms) XFree(atoms);

    atoms = NULL;
    natoms = 0;

    /* This function is very slow on every call if you are not running a
     * spec-supporting WM. For now not optimized, because it isn't in
     * any critical code paths, but if you used it somewhere that had to
     * be fast you want to avoid "GTK is slow with old WMs" complaints.
     * Probably at that point the function should be changed to query
     * _NET_SUPPORTING_WM_CHECK only once every 10 seconds or something.
     */
    XGetWindowProperty (fl_display, RootWindow(fl_display, fl_screen),
                        _XA_NET_SUPPORTING_WM_CHECK, 0, ~0L,
                        False, XA_WINDOW, &type, &format, &nitems,
                        &bytes_after, (uchar **)&xwindow);

    if(type != XA_WINDOW)
        return false;

    // Find out if this WM goes away, so we can reset everything.
    XSelectInput(fl_display, *xwindow, StructureNotifyMask);
    XFlush(fl_display);

    XGetWindowProperty (fl_display, RootWindow(fl_display, fl_screen),
                        _XA_NET_SUPPORTED, 0, ~0L,
                        False, XA_ATOM, &type, &format, (ulong*)&natoms,
                        &bytes_after, (uchar **)&atoms);

    if(type != XA_ATOM)
        return false;

    fl_wmspec_check_window = *xwindow;
    XFree(xwindow);

    // since wmspec_check_window != None this isn't infinite. ;-)
    return fl_netwm_supports(xproperty);
}

bool Fl_WM::set_window_strut(Window xid, int left, int right, int top, int bottom)
{
    init_atoms();
    if(fl_netwm_supports(_XA_NET_WM_STRUT)) {
        CARD32 strut[4] = { left, right, top, bottom };
        XChangeProperty(fl_display, xid, _XA_NET_WM_STRUT, XA_CARDINAL, 32,
                        PropModeReplace, (unsigned char *)&strut, sizeof(CARD32)*4);
        return true;
    }
    return false;
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

    XChangeProperty(fl_display, xid, _XA_NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)&wintype, sizeof(Atom));
    return true;
}

bool Fl_WM::set_window_icon(Window xid, Fl_Image *icon)
{
    if(!icon->get_offscreen()) {
        bool oldval = icon->no_screen();
        icon->no_screen(true);
        icon->draw(0,0);
        icon->no_screen(oldval);
    }

    XWMHints hints;
    hints.icon_pixmap = (Pixmap)icon->get_offscreen();
    hints.flags       |= IconPixmapHint;
    XSetWMHints(fl_display, xid, &hints);

    return true;
}

#include <efltk/fl_utf8.h>
static char latin1buf[4096];

bool Fl_WM::set_window_title(Window xid, const char *title, int title_len)
{
    init_atoms();
    XChangeProperty(fl_display, xid, _XA_NET_WM_NAME, fl_XaUtf8String, 8, PropModeReplace, (uchar*)title, title_len);

    if(title_len>4096) title_len=4096;
    int latin1len = fl_utf2latin1((uchar *)title, title_len, latin1buf);
    XChangeProperty(fl_display, xid, XA_WM_NAME, XA_STRING, 8, 0, (uchar*)latin1buf, latin1len);

    return true;
}

bool Fl_WM::set_window_icontitle(Window xid, const char *title, int title_len)
{
    init_atoms();
    XChangeProperty (fl_display, xid, _XA_NET_WM_ICON_NAME, fl_XaUtf8String, 8, PropModeReplace, (uchar*)title, title_len);

    if(title_len>4096) title_len=4096;
    int latin1len = fl_utf2latin1((uchar *)title, title_len, latin1buf);
    XChangeProperty(fl_display, xid, XA_WM_ICON_NAME, XA_STRING, 8, 0, (uchar*)latin1buf, latin1len);

    return true;
}

bool Fl_WM::set_workspace_count(int count)
{
    init_atoms();
    if(fl_netwm_supports(_XA_NET_NUM_DESKTOPS)) {
        sendClientMessage(RootWindow(fl_display, fl_screen), _XA_NET_NUM_DESKTOPS, count);
        return true;
    }
    return false;
}

bool Fl_WM::set_workspace_names(const char **names, int count)
{
    init_atoms();

    if(fl_netwm_supports(_XA_NET_DESKTOP_NAMES)) {
        XTextProperty wnames;
#if HAVE_X11_UTF_TEXT_PROP
        if(Xutf8TextListToTextProperty(fl_display, (char**)names, count, XUTF8StringStyle, &wnames))
#else
        if(XStringListToTextProperty((char **)names, count, &wnames))
#endif
        {
            XSetTextProperty(fl_display, RootWindow(fl_display, fl_screen), &wnames, _XA_NET_DESKTOP_NAMES);
            XFree(wnames.value);
            return true;
        }
    }
    return false;
}

bool Fl_WM::set_current_workspace(int number)
{
    init_atoms();
    if(fl_netwm_supports(_XA_NET_CURRENT_DESKTOP)) {
        sendClientMessage(RootWindow(fl_display, fl_screen), _XA_NET_CURRENT_DESKTOP, number);
        return true;
    }
    return false;
}

bool Fl_WM::set_active_window(Window xid)
{
    init_atoms();
    if(fl_netwm_supports(_XA_NET_ACTIVE_WINDOW)) {
        sendClientMessage(xid, _XA_NET_ACTIVE_WINDOW, xid);
        return true;
    }
    return false;
}

/////////////////////////////////////////////

static uint8 *cvt1to32(XImage *xim, int ow, int oh)
{
    int pixel;
    int pitch = Fl_Renderer::calc_pitch(4, ow);
    uint8 *data = new uint8[oh*pitch];
    uint32 *ptr;
    int x,y;
    for(y = 0; y < oh; y++)
    {
        ptr = (uint32*) (data + (pitch*y));
        for(x = 0; x < ow; x++) {
            pixel = XGetPixel(xim, x, y);
            if(pixel) *ptr++ = 0x00000000;
            else *ptr++ = 0xFFFFFFFF;
        }
    }
    return data;
}

extern uint8 *ximage_to_data(XImage *im, Fl_PixelFormat *desired);
bool Fl_WM::get_window_icon(Window xid, Fl_Image *&icon, int w, int h)
{
    XWMHints *wm_hints = XGetWMHints(fl_display, xid);

    if(!wm_hints) return false;

    // Max size 128x128
    Fl_Rect r(0, 0, 128, 128);
    XImage *xim;

    Fl_Image *image=0;
    Pixmap mask_bitmap = 0;

    // ICON
    if(wm_hints && wm_hints->flags & IconPixmapHint && wm_hints->icon_pixmap)
    {
        xim = Fl_Renderer::ximage_from_pixmap(wm_hints->icon_pixmap, r);
        if(xim)
        {
            Fl_PixelFormat fmt;
            uint8 *data=0;
            if(xim->depth==1) {
                data = cvt1to32(xim, xim->width, xim->height);
                fmt.realloc(32,0,0,0,0);
            } else {
                data = ximage_to_data(xim, Fl_Renderer::system_format());
                fmt.copy(Fl_Renderer::system_format());
            }
            // Create Fl_Image, masks are calculated automaticly
            image = new Fl_Image(xim->width, xim->height, &fmt, data, true);
            image->mask_type(FL_MASK_NONE);
            XDestroyImage(xim);
        }
    }

    if(!image) {
        if(wm_hints) delete wm_hints;
        return false;
    }

    // MASK
    if(wm_hints && wm_hints->flags & IconMaskHint && wm_hints->icon_mask)
    {
        Fl_Image *mask=0;
        xim = Fl_Renderer::ximage_from_pixmap(wm_hints->icon_mask, r);
        if(xim) {
            uint8 *data = cvt1to32(xim, xim->width, xim->height);
            mask = new Fl_Image(xim->width, xim->height, 32, data, true);
            mask->no_screen(true);
            XDestroyImage(xim);
        }
        if(mask) {
            Fl_Image *smask = mask;
            if(mask->width()!=w || mask->height()!=h) {
                smask = mask->scale(w, h);
                delete mask;
            }
            smask->mask_type(MASK_COLORKEY);
            smask->colorkey(0xFFFFFFFF);
            mask_bitmap = smask->create_mask(w, h);
            delete smask;
        }
    }

    if(wm_hints) delete wm_hints;

    icon = image;
    if(image->width()!=w || image->height()!=h) {
        icon = image->scale(w,h);
        delete image;
    }

    if(mask_bitmap && icon) icon->set_mask(mask_bitmap, true);

    return (icon!=(Fl_Image*)0);
}

bool Fl_WM::get_window_title(Window xid, char *&title)
{
    XTextProperty xtp;
    title = 0;
    int ret=0;

    title = (char*)getProperty(xid, _XA_NET_WM_NAME, fl_XaUtf8String, 0, &ret);
    if(!title && XGetWMName(fl_display, xid, &xtp))
    {
        if(xtp.encoding == XA_STRING) {
            title = strdup((const char*)xtp.value);
        } else {
#if HAVE_X11_UTF_TEXT_PROP
            int items; char **list=0; Status s;
            s = Xutf8TextPropertyToTextList(fl_display, &xtp, &list, &items);
            if((s == Success) && (items > 0)) title = strdup((const char *)*list);
            else title = strdup((const char *)xtp.value);
            if(list) XFreeStringList(list);
#else
            title = strdup((const char*)xtp.value);
#endif
        }
        XFree(xtp.value);
    }
    return (title!=0);
}

bool Fl_WM::get_window_icontitle(Window xid, char *&title)
{
    XTextProperty xtp;
    title = 0;
    int ret=0;

    title = (char*)getProperty(xid, _XA_NET_WM_ICON_NAME, fl_XaUtf8String, 0, &ret);
    if(!title && XGetWMIconName(fl_display, xid, &xtp))
    {
        if(xtp.encoding == XA_STRING) {
            title = strdup((const char*)xtp.value);
        } else {
#if HAVE_X11_UTF_TEXT_PROP
            int items; char **list=0; Status s;
            s = Xutf8TextPropertyToTextList(fl_display, &xtp, &list, &items);
            if((s == Success) && (items > 0)) title = strdup((const char *)*list);
            else title = strdup((const char *)xtp.value);
            if(list) XFreeStringList(list);
#else
            title = strdup((const char*)xtp.value);
#endif
        }
        XFree(xtp.value);
    }
    return (title!=0);
}

bool Fl_WM::get_geometry(int &width, int &height)
{
    init_atoms();
    if(fl_netwm_supports(_XA_NET_DESKTOP_GEOMETRY)) {
        width = height = 0;
        unsigned long size = 0;
        int status;
        CARD32 *val = (CARD32 *)getProperty(RootWindow(fl_display, fl_screen), _XA_NET_DESKTOP_GEOMETRY, XA_CARDINAL, &size, &status);
        if(val) {
            width  = val[0];
            height = val[1];
            XFree((char*)val);
        }
        return true;
    }
    return false;
}

bool Fl_WM::get_workarea(int &x, int &y, int &width, int &height)
{
    init_atoms();
    if(fl_netwm_supports(_XA_NET_WORKAREA)) {
        x = y = width = height = 0;
        unsigned long size = 0;
        CARD32 *val = (CARD32 *)getProperty(RootWindow(fl_display, fl_screen), _XA_NET_WORKAREA, XA_CARDINAL, &size);
        if(val) {
            x      = val[0];
            y      = val[1];
            width  = val[2];
            height = val[3];
            XFree((char*)val);
        }
        return true;
    }
    return false;
}

int Fl_WM::get_windows_stacking(Window *&windows)
{
    init_atoms();
    if(fl_netwm_supports(_XA_NET_CLIENT_LIST_STACKING)) {
        unsigned long size = 0;
        windows = (Window *)getProperty(RootWindow(fl_display, fl_screen),
                                        _XA_NET_CLIENT_LIST_STACKING, XA_WINDOW, &size);
        if(!windows) return -1;
        return size;
    }
    return -1;
}

int Fl_WM::get_windows_mapping(Window *&windows)
{
    init_atoms();
    if(fl_netwm_supports(_XA_NET_CLIENT_LIST)) {
        unsigned long size = 0;
        windows = (Window *)getProperty(RootWindow(fl_display, fl_screen),
                                        _XA_NET_CLIENT_LIST, XA_WINDOW, &size);
        if(!windows) return -1;
        return size;
    }
    return -1;
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

Window Fl_WM::get_active_window()
{
    init_atoms();
    return getIntProperty(RootWindow(fl_display, fl_screen), _XA_NET_ACTIVE_WINDOW, XA_WINDOW, -1);
}

int Fl_WM::get_workspace_names(char **&names)
{
    init_atoms();
    if(!fl_netwm_supports(_XA_NET_DESKTOP_NAMES)) return -1;

    XTextProperty wnames;
    XGetTextProperty(fl_display, RootWindow(fl_display, fl_screen), &wnames, _XA_NET_DESKTOP_NAMES);

    int cnt=-1;
    names = new char*[32];
    char *buffer = (char*)wnames.value;
    int length = wnames.nitems;
    if(buffer) {
        char* c = buffer;
        for(cnt = 0; c < buffer+length; cnt++) {
            if(cnt>31) break;
            char* d = c;
            while(*d) d++;
            names[cnt] = strdup(c);
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
