#include <config.h>

#include <efltk/Fl_Window.h>
#include <efltk/x.h>

#include <efltk/Fl_WM.h>

#ifndef _WIN32

#include <efltk/Fl.h>
#include <efltk/Fl_Util.h>
#include <efltk/Fl_Image.h>

#include <X11/Xproto.h> //For CARD32

#include <stdlib.h>
#include <string.h>

Atom _XA_NET_SUPPORTED = 0;
Atom _XA_NET_SUPPORTING_WM_CHECK = 0;

// DESKTOP actions:
Atom _XA_NET_NUM_DESKTOPS = 0;
Atom _XA_NET_DESKTOP_NAMES = 0;
Atom _XA_NET_CURRENT_DESKTOP = 0;
Atom _XA_NET_WORKAREA = 0;

// WINDOW actions:
Atom _XA_NET_CLIENT_LIST = 0;
Atom _XA_NET_CLIENT_LIST_STACKING = 0;
Atom _XA_NET_ACTIVE_WINDOW = 0;
Atom _XA_NET_WM_NAME = 0;
Atom _XA_NET_WM_ICON_NAME = 0;
Atom _XA_NET_WM_VISIBLE_NAME = 0;
Atom _XA_NET_WM_VISIBLE_ICON_NAME = 0;
Atom _XA_NET_WM_DESKTOP = 0;

Atom _XA_NET_DESKTOP_GEOMETRY = 0;

Atom _XA_NET_WM_WINDOW_TYPE = 0;
Atom _XA_NET_WM_WINDOW_TYPE_DESKTOP = 0;
Atom _XA_NET_WM_WINDOW_TYPE_DOCK = 0;
Atom _XA_NET_WM_WINDOW_TYPE_TOOLBAR = 0;
Atom _XA_NET_WM_WINDOW_TYPE_MENU = 0;
Atom _XA_NET_WM_WINDOW_TYPE_UTIL = 0;
Atom _XA_NET_WM_WINDOW_TYPE_SPLASH = 0;
Atom _XA_NET_WM_WINDOW_TYPE_DIALOG = 0;
Atom _XA_NET_WM_WINDOW_TYPE_NORMAL = 0;

Atom _XA_NET_WM_STRUT = 0;

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

int getIntProperty(Window w, Atom a, Atom type, int deflt, int *ret=0) {
    void* prop = getProperty(w, a, type, 0, ret);
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

static struct {
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
    { &_XA_NET_WM_VISIBLE_ICON_NAME, "_NET_WM_VISIBLE_ICON_NAME" },
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
static bool all_inited = false;

static void init_atoms()
{
    fl_open_display();

    for(uint i = 0; i < CNT(atom_info); i++) {
        if(*(atom_info[i].atom)==0) *(atom_info[i].atom) = XInternAtom(fl_display, atom_info[i].name, False);
    }
    all_inited = true;
}

static void init_atom(Atom *atom)
{
    if(all_inited) return;
    fl_open_display();

    for(uint i = 0; i < CNT(atom_info); i++) {
        if(atom_info[i].atom == atom) {
            if(*(atom_info[i].atom)==0) *(atom_info[i].atom) = XInternAtom(fl_display, atom_info[i].name, False);
            return;
        }
    }
}

Window fl_wmspec_check_window = None;
bool fl_netwm_supports(Atom &xproperty)
{
    init_atom(&_XA_NET_SUPPORTING_WM_CHECK);
    init_atom(&_XA_NET_SUPPORTED);

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
    init_atom(&_XA_NET_WM_STRUT);
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
    Atom *wintype;
    switch(type) {
    case DIALOG:
        wintype = &_XA_NET_WM_WINDOW_TYPE_DIALOG;
        break;
    case UTIL:
        wintype = &_XA_NET_WM_WINDOW_TYPE_UTIL;
        break;
    case TOOLBAR:
        wintype = &_XA_NET_WM_WINDOW_TYPE_TOOLBAR;
        break;
    case DOCK:
        wintype = &_XA_NET_WM_WINDOW_TYPE_DOCK;
        break;
    case SPLASH:
        wintype = &_XA_NET_WM_WINDOW_TYPE_SPLASH;
        break;
    case MENU:
        wintype = &_XA_NET_WM_WINDOW_TYPE_MENU;
        break;
    case DESKTOP:
        wintype = &_XA_NET_WM_WINDOW_TYPE_DESKTOP;
        break;
    case NORMAL:
    default:
        wintype = &_XA_NET_WM_WINDOW_TYPE_NORMAL;
    };
    init_atom(wintype);
    init_atom(&_XA_NET_WM_WINDOW_TYPE);

    XChangeProperty(fl_display, xid, _XA_NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)wintype, sizeof(Atom));
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
    init_atom(&_XA_NET_WM_NAME);
    XChangeProperty(fl_display, xid, _XA_NET_WM_NAME, fl_XaUtf8String, 8, PropModeReplace, (uchar*)title, title_len);

    if(title_len>4096) title_len=4096;
    int latin1len = fl_utf2latin1((uchar *)title, title_len, latin1buf);
    latin1buf[latin1len]='\0';
    XChangeProperty(fl_display, xid, XA_WM_NAME, XA_STRING, 8, 0, (uchar*)latin1buf, latin1len);

    return true;
}

bool Fl_WM::set_window_icontitle(Window xid, const char *title, int title_len)
{
    init_atom(&_XA_NET_WM_ICON_NAME);
    XChangeProperty (fl_display, xid, _XA_NET_WM_ICON_NAME, fl_XaUtf8String, 8, PropModeReplace, (uchar*)title, title_len);

    if(title_len>4096) title_len=4096;
    int latin1len = fl_utf2latin1((uchar *)title, title_len, latin1buf);
    latin1buf[latin1len]='\0';
    XChangeProperty(fl_display, xid, XA_WM_ICON_NAME, XA_STRING, 8, 0, (uchar*)latin1buf, latin1len);

    return true;
}

bool Fl_WM::set_workspace_count(int count)
{
    init_atom(&_XA_NET_NUM_DESKTOPS);
    if(fl_netwm_supports(_XA_NET_NUM_DESKTOPS)) {
        sendClientMessage(RootWindow(fl_display, fl_screen), _XA_NET_NUM_DESKTOPS, count);
        return true;
    }
    return false;
}

bool Fl_WM::set_workspace_names(const char **names, int count)
{
    init_atom(&_XA_NET_DESKTOP_NAMES);

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
    init_atom(&_XA_NET_CURRENT_DESKTOP);
    if(fl_netwm_supports(_XA_NET_CURRENT_DESKTOP)) {
        sendClientMessage(RootWindow(fl_display, fl_screen), _XA_NET_CURRENT_DESKTOP, number);
        return true;
    }
    return false;
}

bool Fl_WM::set_active_window(Window xid)
{
    init_atom(&_XA_NET_ACTIVE_WINDOW);
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
    init_atom(&_XA_NET_WM_NAME);

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
    init_atom(&_XA_NET_WM_ICON_NAME);

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

// Returns: -2=ERROR, -1=STICKY, Otherwise desktop
int Fl_WM::get_window_desktop(Window xid)
{
    init_atom(&_XA_NET_WM_DESKTOP);
    if(fl_netwm_supports(_XA_NET_WM_DESKTOP)) {
        int status=0;
        unsigned long desk;
        desk = getIntProperty(xid, _XA_NET_WM_DESKTOP, XA_CARDINAL, 100000, &status);
        if(status!=Success || desk==100000) {
            return -2;
        }
        if(desk==0xFFFFFFFF || desk==0xFFFFFFFE) {
            return -1;
        }
        return desk;
    }
    return -2;
}

bool Fl_WM::get_geometry(int &width, int &height)
{
    init_atom(&_XA_NET_DESKTOP_GEOMETRY);
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
    init_atom(&_XA_NET_WORKAREA);
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
    init_atom(&_XA_NET_CLIENT_LIST_STACKING);
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
    init_atom(&_XA_NET_CLIENT_LIST);
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
    init_atom(&_XA_NET_NUM_DESKTOPS);
    return getIntProperty(RootWindow(fl_display, fl_screen), _XA_NET_NUM_DESKTOPS, XA_CARDINAL, -1);
}

int Fl_WM::get_current_workspace()
{
    init_atom(&_XA_NET_CURRENT_DESKTOP);
    return getIntProperty(RootWindow(fl_display, fl_screen), _XA_NET_CURRENT_DESKTOP, XA_CARDINAL, -1);
}

Window Fl_WM::get_active_window()
{
    init_atom(&_XA_NET_ACTIVE_WINDOW);
    return getIntProperty(RootWindow(fl_display, fl_screen), _XA_NET_ACTIVE_WINDOW, XA_WINDOW, -1);
}

int Fl_WM::get_workspace_names(char **&names)
{
    init_atom(&_XA_NET_DESKTOP_NAMES);
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

#include <efltk/Fl_Callback_List.h>

static Window action_window=0;
static int action=0;

static Fl_Int_List handled;
static Fl_Int_List action_masks;
static Fl_Callback_List callbacks;

void Fl_WM::clear_handled() {
    handled.clear();
}

bool Fl_WM::is_handled(Window w) {
    return (handled.index_of(w)>-1);
}

void Fl_WM::unhandle_window(Window w) {
    handled.remove(w);
}

void Fl_WM::handle_window(Window w) {
    if(handled.index_of(w)>-1)
        return;

    if ( !fl_find( w ) )
        XSelectInput( fl_display, w, PropertyChangeMask | StructureNotifyMask );

    handled.append(w);
}

static void do_callback(int mask)
{
    for(uint n=0; n<action_masks.size(); n++) {
        if(action_masks[n]&action) {
            CallbackData *d = callbacks[n];
            if(d->cb) d->cb(0, d->arg);
        }
    }
}

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

        // Active window changed
        else if(fl_xevent.xproperty.atom==_XA_NET_ACTIVE_WINDOW) {
            action = Fl_WM::WINDOW_ACTIVE;
        }

        // Window name
        else if(fl_xevent.xproperty.atom==_XA_NET_WM_NAME || fl_xevent.xproperty.atom==XA_WM_NAME)
            action = Fl_WM::WINDOW_NAME;
        else if(fl_xevent.xproperty.atom==_XA_NET_WM_VISIBLE_NAME)
            action = Fl_WM::WINDOW_NAME_VIS;

        // Icon name
        else if(fl_xevent.xproperty.atom==_XA_NET_WM_ICON_NAME || fl_xevent.xproperty.atom==XA_WM_ICON_NAME)
            action = Fl_WM::WINDOW_ICONNAME;
        else if(fl_xevent.xproperty.atom==_XA_NET_WM_VISIBLE_ICON_NAME)
            action = Fl_WM::WINDOW_ICONNAME_VIS;

        else if(fl_xevent.xproperty.atom==_XA_NET_WM_DESKTOP)
            action = Fl_WM::WINDOW_DESKTOP;

        if(action>0) {
            do_callback(action);
            // Reset after callback
            action=0;
            action_window=0;
            return 1;
        }
        action=0;
        action_window=0;
    }

    return 0;
}

void Fl_WM::add_callback(Fl_Callback *cb, void *user_data, int mask)
{
    init_atoms();
    static bool inited=false;
    if(!inited) {
        XSelectInput( fl_display, RootWindow(fl_display, fl_screen), PropertyChangeMask | StructureNotifyMask );
        Fl::add_handler(wm_event_handler);
        inited=true;
    }
    action_masks.append(mask);
    callbacks.append(cb, user_data);
}

void Fl_WM::remove_callback(Fl_Callback *cb, void *user_data)
{
    int index = callbacks.index_of(cb, user_data);
    if(index>=0) {
        callbacks.remove(index);
        action_masks.remove(index);
    }
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

void Fl_WM::add_callback(Fl_Callback *cb, void *user_data, int mask) { }

void Fl_WM::remove_callback(Fl_Callback *cb, void *user_data) { }

int Fl_WM::action() { return 0; }
Window Fl_WM::window() { return 0; }


#endif /* _WIN32 */
