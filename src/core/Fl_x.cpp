//
// "$Id$"
//
// X specific code for the Fast Light Tool Kit (FLTK).
// This file is #included by Fl.cxx
//
// Copyright 1998-1999 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#define CONSOLIDATE_MOTION 0     // this was 1 in fltk 1.0

#include <config.h>

#include <efltk/Fl_WM.h>
#include <efltk/fl_utf8.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Style.h>

#include <exception>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>

using namespace std;

/* The first ticks value of the application */
static struct timeval start;
static bool ticks_started=false;

void fl_start_ticks() {
    if(ticks_started) return;
    /* Set first ticks value */
    gettimeofday(&start, NULL);
    ticks_started = true;
}

uint32 Fl::ticks()
{
    if(!ticks_started) fl_start_ticks();
    struct timeval now;
    gettimeofday(&now, NULL);
    return ((now.tv_sec-start.tv_sec)*1000+(now.tv_usec-start.tv_usec)/1000);
}

void Fl::sleep(int ms) {
    timeval t;
    t.tv_sec = int(ms/1000);
    t.tv_usec = 1000*ms;
    ::select(1,0,0,0,&t);
}

extern unsigned int KeySymToUcs4(KeySym keysym);
#define XKeysymToUcs(ks) KeySymToUcs4(ks)

int XConvertEucToUtf8(const char*   locale,
    char*       buffer_return,
    int     len,
    int     bytes_buffer)
{
    char *buf = (char*) malloc(len);
    memcpy(buf, buffer_return, len);

    int cvt = fl_convert2utf(locale,
            (const uchar*)buf, len,
            buffer_return, len);

    free(buf);
    return cvt;
}

#if HAVE_XUTF8
int XUtf8LookupString(XIC                 ic,
    XKeyPressedEvent*   event,
    char*               buffer_return,
    int                 bytes_buffer,
    KeySym*             keysym,
    Status*             status_return)
{
    long ucs = -1;
    int len;
    len = XmbLookupString(ic, event, buffer_return, bytes_buffer / 2,
            keysym, status_return);
    if (*keysym > 0 && *keysym < 0x100) {
        ucs = (unsigned char)buffer_return[0];
        //ucs = *keysym;
    } else  if (((*keysym >= 0x100 && *keysym <= 0xf000) ||
                (*keysym & 0xff000000U) == 0x01000000))
    {
        ucs = XKeysymToUcs(*keysym);
    } else {
        ucs = -2;
    }
    //if (ucs == -1) len = 0;
    if (ucs > 0) {
        len = fl_ucs2utf(ucs, (char *)buffer_return);
    } else if (len > 0) {
        len = XConvertEucToUtf8(XLocaleOfIM(XIMOfIC(ic)), buffer_return, len, bytes_buffer);
    }
    return len;
}
#endif

////////////////////////////////////////////////////////////////
// interface to poll/select call:

#if USE_POLL

#include <poll.h>
static pollfd *pollfds = 0;

#else

#if HAVE_SYS_SELECT_H
#  include <sys/select.h>
#endif                           /* HAVE_SYS_SELECT_H */

// The following #define is only needed for HP-UX 9.x and earlier:
//#define select(a,b,c,d,e) select((a),(int *)(b),(int *)(c),(int *)(d),(e))

static fd_set fdsets[3];
static int maxfd;
#define POLLIN 1
#define POLLOUT 4
#define POLLERR 8
#endif                           /* USE_POLL */

static int nfds = 0;
static int fd_array_size = 0;
static struct FD
{
#if !USE_POLL
    int fd;
    short events;
#endif
    void (*cb)(int, void*);
    void* arg;
} *fd = 0;

void Fl::add_fd(int n, int events, void (*cb)(int, void*), void *v)
{
    remove_fd(n,events);
    int i = nfds++;
    if (i >= fd_array_size)
    {
        fd_array_size = 2*fd_array_size+1;
        fd = (FD*)realloc(fd, fd_array_size*sizeof(FD));
#if USE_POLL
        pollfds = (pollfd*)realloc(pollfds, fd_array_size*sizeof(pollfd));
#endif
    }
    fd[i].cb = cb;
    fd[i].arg = v;
#if USE_POLL
    pollfds[i].fd = n;
    pollfds[i].events = events;
#else
    fd[i].fd = n;
    fd[i].events = events;
    if (events & POLLIN) FD_SET(n, &fdsets[0]);
    if (events & POLLOUT) FD_SET(n, &fdsets[1]);
    if (events & POLLERR) FD_SET(n, &fdsets[2]);
    if (n > maxfd) maxfd = n;
#endif
}


void Fl::add_fd(int fd, void (*cb)(int, void*), void* v)
{
    Fl::add_fd(fd, POLLIN, cb, v);
}


void Fl::remove_fd(int n, int events)
{
    int i,j;
    for (i=j=0; i<nfds; i++)
    {
#if USE_POLL
        if (pollfds[i].fd == n)
        {
            int e = pollfds[i].events & ~events;
            if (!e) continue;    // if no events left, delete this fd
            pollfds[j].events = e;
        }
#else
        if (fd[i].fd == n)
        {
            int e = fd[i].events & ~events;
            if (!e) continue;    // if no events left, delete this fd
            fd[i].events = e;
        }
#endif
        // move it down in the array if necessary:
        if (j<i)
        {
            fd[j] = fd[i];
#if USE_POLL
            pollfds[j] = pollfds[i];
#endif
        }
        j++;
    }
    nfds = j;
#if !USE_POLL
    if (events & POLLIN) FD_CLR(n, &fdsets[0]);
    if (events & POLLOUT) FD_CLR(n, &fdsets[1]);
    if (events & POLLERR) FD_CLR(n, &fdsets[2]);
    if (n == maxfd) maxfd--;
#endif
}


#if CONSOLIDATE_MOTION
static Fl_Window* send_motion;
#endif
static bool in_a_window; // true if in any of our windows, even destroyed ones

static void do_queued_events(int, void*)
{
    in_a_window = true;

    while (!Fl::exit_modal_ && XEventsQueued(fl_display,QueuedAfterReading))
    {
        XNextEvent(fl_display, &fl_xevent);
        fl_handle();
    }
    // we send FL_LEAVE only if the mouse did not enter some other window:
    if (!in_a_window) Fl::handle(FL_LEAVE, 0);
    //if (!xmousewin) Fl::handle(FL_LEAVE, 0);
#if CONSOLIDATE_MOTION
    else if (send_motion == xmousewin)
    {
        send_motion = 0;
        Fl::handle(FL_MOVE, xmousewin);
    }
#endif
}


// these pointers are set by the Fl::lock() function:
static void nothing() {}
void (*fl_lock_function)() = nothing;
void (*fl_unlock_function)() = nothing;

// Wait up to the given time for any events or sockets to become ready,
// do the callbacks for the events and sockets:
static inline int fl_wait(float time_to_wait)
{

    // OpenGL and other broken libraries call XEventsQueued()
    // and thus cause the file descriptor to not be ready,
    // so we must check for already-read events:
    if (fl_display && XQLength(fl_display)) {do_queued_events(0,0); return 1;}

#if !USE_POLL
    fd_set fdt[3];
    fdt[0] = fdsets[0];
    fdt[1] = fdsets[1];
    fdt[2] = fdsets[2];
#endif

    fl_unlock_function();
#if USE_POLL
    int n = ::poll(pollfds, nfds,
            (time_to_wait<2147483.648f) ? int(time_to_wait*1000+.5f) : -1);
#else
    int n;
    if (time_to_wait < 2147483.648f) {
        timeval t;
        t.tv_sec = int(time_to_wait);
        t.tv_usec = int(1000000 * (time_to_wait-t.tv_sec));
        n = ::select(maxfd+1,&fdt[0],&fdt[1],&fdt[2],&t);
    } else {
        n = ::select(maxfd+1,&fdt[0],&fdt[1],&fdt[2],0);
    }
#endif
    fl_lock_function();

    if (n > 0)
    {
        for (int i=0; i<nfds; i++)
        {
#if USE_POLL
            if (pollfds[i].revents) fd[i].cb(pollfds[i].fd, fd[i].arg);
#else
            int f = fd[i].fd;
            short revents = 0;
            if (FD_ISSET(f,&fdt[0])) revents |= POLLIN;
            if (FD_ISSET(f,&fdt[1])) revents |= POLLOUT;
            if (FD_ISSET(f,&fdt[2])) revents |= POLLERR;
            if (fd[i].events & revents) fd[i].cb(f, fd[i].arg);
#endif
        }
    }
    return n;
}


// fl_ready() is just like fl_wait(0.0) except no callbacks are done:
static inline int fl_ready()
{
    if (XQLength(fl_display)) return 1;
#if USE_POLL
    return ::poll(pollfds, nfds, 0);
#else
    timeval t;
    t.tv_sec = 0;
    t.tv_usec = 0;
    fd_set fdt[3];
    fdt[0] = fdsets[0];
    fdt[1] = fdsets[1];
    fdt[2] = fdsets[2];
    return ::select(maxfd+1,&fdt[0],&fdt[1],&fdt[2],&t);
#endif
}


////////////////////////////////////////////////////////////////

Display *fl_display = 0;
Window fl_message_window;
int fl_screen;
XVisualInfo *fl_visual;
Colormap fl_colormap;

Atom FLTKChangeScheme;
Atom FLTKChangeSettings;

Atom WM_DELETE_WINDOW;
Atom WM_PROTOCOLS;
Atom fl_MOTIF_WM_HINTS;
Atom TARGETS;
Atom CLIPBOARD;
Atom fl_XdndAware;
Atom fl_XdndSelection;
Atom fl_XdndEnter;
Atom fl_XdndTypeList;
Atom fl_XdndPosition;
Atom fl_XdndLeave;
Atom fl_XdndDrop;
Atom fl_XdndStatus;
Atom fl_XdndActionCopy;
Atom fl_XdndFinished;
Atom fl_textplain;
Atom fl_texturilist;
//Atom fl_XdndProxy;
#if HAVE_XUTF8
Atom fl_XaUtf8String;
#endif
extern "C"
{
    static int io_error_handler(Display*) {Fl::fatal("X I/O error"); return 0;}

    static int xerror_handler(Display* d, XErrorEvent* e)
    {
        char buf1[128], buf2[128];
        sprintf(buf1, "XRequest.%d", e->request_code);
        XGetErrorDatabaseText(d,"",buf1,buf1,buf2,128);
        XGetErrorText(d, e->error_code, buf1, 128);
        Fl::warning("%s: %s 0x%lx", buf2, buf1, e->resourceid);
        return 0;
    }
}

#if HAVE_XUTF8
XIM fl_xim_im;
XIC fl_xim_ic;
char fl_ping_xim = 0;

void fl_init_xim()
{
    static bool print_once=false;

    XIMStyles* xim_styles;
    if (!fl_display) return;
    if (fl_xim_im) return;

    fl_xim_im = XOpenIM(fl_display, NULL, NULL, NULL);
    xim_styles = NULL;
    fl_xim_ic = NULL;

    if (fl_xim_im) {
        XGetIMValues (fl_xim_im, XNQueryInputStyle,
            &xim_styles, NULL, NULL);
    } else {
        if(!print_once) { Fl::warning("XOpenIM() failed\n"); print_once=true; }
        return;
    }
    if (xim_styles && xim_styles->count_styles) {
        fl_xim_ic = XCreateIC(fl_xim_im,
                XNInputStyle, (XIMPreeditNothing | XIMStatusNothing),
                NULL);
    } else {
        if(!print_once) { Fl::warning("No XIM style found\n"); print_once=true; }
        XCloseIM(fl_xim_im);
        fl_xim_im = NULL;
        return;
    }
    if (!fl_xim_ic) {
        if(!print_once) { Fl::warning("XCreateIC() failed\n"); print_once=true; }
        XCloseIM(fl_xim_im);
        XFree(xim_styles);
        fl_xim_im = NULL;
    }
}
#endif

void fl_open_display()
{
    if (fl_display) return;

    XSetIOErrorHandler(io_error_handler);
    XSetErrorHandler(xerror_handler);

    Display *d = XOpenDisplay(0);
    if (!d) Fl::fatal("Can't open display \"%s\"",XDisplayName(0));

    fl_open_display(d);
}

void fl_open_display(Display* d)
{
    fl_display = d;
    Fl::add_fd(ConnectionNumber(d), POLLIN, do_queued_events);

    fl_start_ticks();

    extern void fl_private_init();
    fl_private_init(); //Fl_init.cpp

    WM_DELETE_WINDOW      = XInternAtom(d, "WM_DELETE_WINDOW",    0);
    WM_PROTOCOLS          = XInternAtom(d, "WM_PROTOCOLS",    0);
    fl_MOTIF_WM_HINTS     = XInternAtom(d, "_MOTIF_WM_HINTS", 0);
    FLTKChangeScheme      = XInternAtom(d, "FLTKChangeScheme",    0);
    FLTKChangeSettings    = XInternAtom(d, "FLTKChangeSettings",  0);
    TARGETS               = XInternAtom(d, "TARGETS",     0);
    CLIPBOARD     = XInternAtom(d, "CLIPBOARD",       0);
    fl_XdndAware          = XInternAtom(d, "XdndAware",       0);
    fl_XdndSelection      = XInternAtom(d, "XdndSelection",   0);
    fl_XdndEnter          = XInternAtom(d, "XdndEnter",       0);
    fl_XdndTypeList       = XInternAtom(d, "XdndTypeList",    0);
    fl_XdndPosition       = XInternAtom(d, "XdndPosition",    0);
    fl_XdndLeave          = XInternAtom(d, "XdndLeave",       0);
    fl_XdndDrop           = XInternAtom(d, "XdndDrop",        0);
    fl_XdndStatus         = XInternAtom(d, "XdndStatus",      0);
    fl_XdndActionCopy     = XInternAtom(d, "XdndActionCopy",  0);
    fl_XdndFinished       = XInternAtom(d, "XdndFinished",    0);
    fl_textplain          = XInternAtom(d, "text/plain",      0);
    fl_texturilist        = XInternAtom(d, "text/uri-list",   0);
    //fl_XdndProxy        = XInternAtom(d, "XdndProxy",     0);
#if HAVE_XUTF8
    fl_XaUtf8String = XInternAtom(d, "UTF8_STRING",     0);
#endif

    fl_screen = DefaultScreen(d);

    // Carl inserted something much like the KDE plugin does to register
    // a style client message.  I would prefer to either leave this up
    // to the plugin, or use the SAME atoms as KDE (to avoid even more
    // namespace pollution).  See the kde plugin for sample code.

    // I don't think an X window with the name "FLTK_STYLE_WINDOW" pollutes
    // the namespace very badly.  We could use the same atoms as KDE, but then
    // FLTK windows would redraw every time we changed the KDE scheme, and
    // KDE windows would redraw every time we changed the FLTK scheme which
    // to me would be unacceptable.  Moreover, this would make FLTK dependant
    // on a particular KDE version; different versions of KDE (currently just
    // v1 & v2) handle this in different ways.  We would need put logic in
    // FLTK to figure out which version of KDE is running and do it in that
    // way, and that would break again if the KDE folks changed methods again.
    // It doesn't hurt anything and saves code needed for KDE compatibility
    // to just do it our own way.  Finally, it just doesn't seem "right" for
    // FLTK applications to advertise themselves as KDE applications when in
    // fact they are not.  That could potentially break KDE as it waits for
    // a FLTK application to do some KDE thing that it doesn't know how to
    // respond to.  That's what the KDE theme is for!
    //
    // CET

    // WAS: ok.  I made it public so the window id can be used for grab, etc.
    // We may want the atom to be FLTK_MESSAGE_WINDOW, and change the message
    // to be FLTKChangeStyle so that the names match kde more closely.

    fl_message_window =
        XCreateSimpleWindow(d, RootWindow(d,fl_screen), 0,0,1,1,0, 0, 0);
    Atom style_atom = XInternAtom(d, "FLTK_STYLE_WINDOW", False);
    long data = 1;
    XChangeProperty(d, fl_message_window, style_atom, style_atom, 32,
        PropModeReplace, (unsigned char *)&data, 1);

    // construct an XVisualInfo that matches the default Visual:
    XVisualInfo templt; int num;
    templt.visualid = XVisualIDFromVisual(DefaultVisual(d, fl_screen));
    fl_visual = XGetVisualInfo(d, VisualIDMask, &templt, &num);
    fl_colormap = DefaultColormap(d, fl_screen);

#  if HAVE_XUTF8
    fl_init_xim();
#  endif

#if !USE_COLORMAP
    Fl::visual(FL_RGB);
#endif
}


void fl_close_display()
{
    Fl::remove_fd(ConnectionNumber(fl_display));
    XCloseDisplay(fl_display);
}


static bool reload_info = true;

const Fl_Screen_Info& Fl::info()
{
    static Fl_Screen_Info info;
    if (reload_info)
    {
        reload_info = false;
        fl_open_display();

        // WAS: this should do something on multihead systems to match Windoze!
        // I don't have multihead versions of either X or Windows to test...
        info.x = 0;
        info.y = 0;
        info.width = DisplayWidth(fl_display,fl_screen);
        info.height = DisplayHeight(fl_display,fl_screen);
        info.w = info.width;
        info.h = info.height;

        // do any screens really return 0 for MM?
        info.width_mm = DisplayWidthMM(fl_display, fl_screen);
        if (!info.width_mm) info.width_mm = int(info.width*25.4/75);
        //info.dpi_x = info.width*25.4/info.width_mm;
        info.height_mm = DisplayHeightMM(fl_display, fl_screen);
        if (!info.height_mm) info.height_mm = int(info.height*25.4/75);
        // info.dpi_y = info.height*25.4/info.height_mm;
    }
    return info;
}


void Fl::get_mouse(int &x, int &y)
{
    fl_open_display();
    Window root = RootWindow(fl_display, fl_screen);
    Window c; int mx,my,cx,cy; unsigned int mask;
    XQueryPointer(fl_display,root,&root,&c,&mx,&my,&cx,&cy,&mask);
    x = mx;
    y = my;
}


////////////////////////////////////////////////////////////////
// Code used for paste and DnD into the program:

static Fl_Widget *fl_selection_requestor;
static char *selection_buffer[2];
static int selection_length[2];
static int selection_buffer_length[2];
bool fl_i_own_selection[2];

// Call this when a "paste" operation happens:
void Fl::paste(Fl_Widget &receiver, bool clipboard)
{
    if (fl_i_own_selection[clipboard])
    {
        // We already have it, do it quickly without window server.
        // Notice that the text is clobbered if set_selection is
        // called in response to FL_PASTE!
        Fl::e_text = selection_buffer[clipboard];
        Fl::e_length = selection_length[clipboard];
        receiver.handle(FL_PASTE);
        return;
    }
    // otherwise get the window server to return it:
    fl_selection_requestor = &receiver;
    Atom property = clipboard ? CLIPBOARD : XA_PRIMARY;
    XConvertSelection(fl_display, property, XA_STRING, property,
        fl_xid(Fl::first_window()), fl_event_time);
#if HAVE_XUTF8
    XConvertSelection(fl_display, property, fl_XaUtf8String, property,
        fl_xid(Fl::first_window()), fl_event_time);
#endif
}


Window fl_dnd_source_window;
Atom *fl_dnd_source_types;       // null-terminated list of data types being supplied
Atom *fl_incoming_dnd_source_types;
Atom fl_dnd_type;
Atom fl_dnd_source_action;
Atom fl_dnd_action;

void fl_sendClientMessage(Window window, Atom message,
    unsigned long d0,
    unsigned long d1=0,
    unsigned long d2=0,
    unsigned long d3=0,
    unsigned long d4=0)
{
    XEvent e;
    e.xany.type = ClientMessage;
    e.xany.window = window;
    e.xclient.message_type = message;
    e.xclient.format = 32;
    e.xclient.data.l[0] = (long)d0;
    e.xclient.data.l[1] = (long)d1;
    e.xclient.data.l[2] = (long)d2;
    e.xclient.data.l[3] = (long)d3;
    e.xclient.data.l[4] = (long)d4;
    XSendEvent(fl_display, window, 0, 0, &e);
}


////////////////////////////////////////////////////////////////
// Code for copying to clipboard and DnD out of the program:

void Fl::copy(const char *stuff, int len, bool clipboard)
{
    if (!stuff || len<0) return;
    if (len+1 > selection_buffer_length[clipboard])
    {
        delete[] selection_buffer[clipboard];
        selection_buffer[clipboard] = new char[len+100];
        selection_buffer_length[clipboard] = len+100;
    }
    memcpy(selection_buffer[clipboard], stuff, len);
                                 // needed for direct paste
    selection_buffer[clipboard][len] = 0;
    selection_length[clipboard] = len;
    fl_i_own_selection[clipboard] = true;
    Atom property = clipboard ? CLIPBOARD : XA_PRIMARY;
    XSetSelectionOwner(fl_display, property, fl_message_window, fl_event_time);
}


////////////////////////////////////////////////////////////////

XEvent fl_xevent;                // the current x event
ulong fl_event_time;             // the last timestamp from an x event

char fl_key_vector[32];          // used by Fl::get_key()

// Record event mouse position and state from an XEvent:

static void set_event_xy(bool push)
{
#if CONSOLIDATE_MOTION
    send_motion = 0;
#endif
    Fl::e_x_root = fl_xevent.xbutton.x_root;
    Fl::e_x = fl_xevent.xbutton.x;
    Fl::e_y_root = fl_xevent.xbutton.y_root;
    Fl::e_y = fl_xevent.xbutton.y;
    Fl::e_state = fl_xevent.xbutton.state << 16;
    fl_event_time = fl_xevent.xbutton.time;
#ifdef __sgi
    // get the Win key off PC keyboards:
    if (fl_key_vector[18]&0x18) Fl::e_state |= FL_WIN;
#endif
    // turn off is_click if enough time or mouse movement has passed:
    static int px, py;
    static ulong ptime;
    if (abs(Fl::e_x_root-px)+abs(Fl::e_y_root-py) > 3
            || fl_event_time >= ptime+(push?1000:200))
        Fl::e_is_click = 0;
    if (push)
    {
        px = Fl::e_x_root;
        py = Fl::e_y_root;
        ptime = fl_event_time;
    }
}


////////////////////////////////////////////////////////////////

static Fl_Window* resize_from_system;

static unsigned wheel_up_button = 4;
static unsigned wheel_down_button = 5;

extern "C"
{
    static Bool fake_keyup_test(Display*, XEvent* event, char* previous)
    {
        return
        event->type == KeyPress &&
            event->xkey.keycode == ((XKeyEvent*)previous)->keycode &&
            event->xkey.time == ((XKeyEvent*)previous)->time;
    }
}

extern Window fl_wmspec_check_window;
bool fl_handle()
{
    Fl_Window* window = fl_find(fl_xevent.xany.window);
    int event = 0;

    try {

#if HAVE_XUTF8
        int filtered = 0;
    /*
    // According to Martin's report, this slows down window destroying..
    // And it seems that no other toolkit does this.. Is this necessary??
    if(fl_xevent.type == DestroyNotify) {
        XIM xim_im;
        xim_im = XOpenIM(fl_display, NULL, NULL, NULL);
        if (!xim_im) {
            //  XIM server has crashed
            XSetLocaleModifiers("@im=");
            fl_xim_im = NULL;
            fl_init_xim();
        } else {
            XCloseIM(xim_im);
        }
    }*/

        filtered = XFilterEvent((XEvent *)&fl_xevent, fl_xevent.xany.window);
        if (fl_xim_ic  && fl_ping_xim && (fl_xevent.type == KeyPress ||
                    fl_xevent.type == FocusIn || fl_xevent.type == KeyRelease))
        {
        // ping the xim server !!!
            static XVaNestedList list = NULL;
            static XIC xic = NULL;
            if (!list || xic != fl_xim_ic) {
                static unsigned int c;
                xic = fl_xim_ic;
                if (list) XFree(list);
                list = XVaCreateNestedList(0, XNForeground, c, NULL);
                XGetICValues(fl_xim_ic, XNPreeditAttributes, &list, NULL);
            }
            XSetICValues(fl_xim_ic, XNPreeditAttributes, list, NULL);
            if (filtered) return 1;
        }
#endif

        if(fl_wmspec_check_window != None &&
                fl_xevent.xany.window == fl_wmspec_check_window &&
                fl_xevent.type == DestroyNotify)
        {
            fl_wmspec_check_window = None;
            return Fl::handle(event, window);
        }

        switch (fl_xevent.type)
        {
            case KeymapNotify:
                memcpy(fl_key_vector, fl_xevent.xkeymap.key_vector, 32);
                break;

            case MappingNotify:
                XRefreshKeyboardMapping((XMappingEvent*)&fl_xevent.xmapping);
                break;

            case ClientMessage:
                {
                    Atom message = fl_xevent.xclient.message_type;
                    const long* data = fl_xevent.xclient.data.l;

                    if (window && (Atom)(data[0]) == WM_DELETE_WINDOW)
                    {
                        if (!Fl::grab() && !(Fl::modal() && window != Fl::modal()))
                            window->do_callback(FL_WND_DESTROY);
                        return true;

                    }
                    else if (message == FLTKChangeSettings)
                    {
                        Fl::read_defaults();
                        break;
                    }
                    else if (message == FLTKChangeScheme)
                    {
                        Fl_Style::reload_theme();
                        break;
                    }
                    else if (message == fl_XdndEnter)
                    {
                        xmousewin = window;
                        in_a_window = true;

                        fl_dnd_source_window = data[0];
                // version number is data[1]>>24
                        if (data[1]&1)
                        {
                    // get list of data types:
                            Atom actual; int format; unsigned long count, remaining;
                            unsigned char *buffer = 0;
                            XGetWindowProperty(fl_display, fl_dnd_source_window, fl_XdndTypeList,
                                0, 0x8000000L, False, XA_ATOM, &actual, &format,
                                &count, &remaining, &buffer);
                            if (actual != XA_ATOM || format != 32 || count<4 || !buffer)
                                goto FAILED;
                            delete [] fl_incoming_dnd_source_types;
                            fl_incoming_dnd_source_types = new Atom[count+1];
                            fl_dnd_source_types = fl_incoming_dnd_source_types;
                            for (unsigned i = 0; i < count; i++)
                                fl_dnd_source_types[i] = ((Atom*)buffer)[i];
                            fl_dnd_source_types[count] = 0;
                        }
                        else
                        {
                        FAILED:
                    // less than four data types, or if the above messes up:
                            if (!fl_incoming_dnd_source_types)
                                fl_incoming_dnd_source_types = new Atom[4];
                            fl_dnd_source_types = fl_incoming_dnd_source_types;
                            fl_dnd_source_types[0] = data[2];
                            fl_dnd_source_types[1] = data[3];
                            fl_dnd_source_types[2] = data[4];
                            fl_dnd_source_types[3] = 0;
                        }
                // This should return one of the fl_dnd_source_types. Unfortunately
                // no way to just force it to cough up whatever data is "most text-like"
                // instead I have to select from a list of known types. We may need
                // to add to this list in the future, turn on the #if to print the
                // types if you get a drop that you think should work.
                                 // try this if no matches, it may work
                        fl_dnd_type = fl_textplain;
                        for (int i = 0; ; i++)
                        {
                            Atom type = fl_dnd_source_types[i]; if (!type) break;
#if 0        // print what types are being pasted:
                            char* x = XGetAtomName(fl_display, type);
                            printf("source type of %s\n",x);
                            XFree(x);
#else
                                 // our favorite
                            if (type == fl_textplain)
                            {
                                fl_dnd_type = type; break;
                            }
                                 // ok
                            if (type == fl_texturilist) fl_dnd_type = type;
#endif
                        }
                        event = FL_DND_ENTER;
                        break;

                    }
                    else if (message == fl_XdndPosition)
                    {
                        xmousewin = window;
                        fl_dnd_source_window = data[0];
                        Fl::e_x_root = data[2]>>16;
                        Fl::e_y_root = data[2]&0xFFFF;
                        if (window)
                        {
                            Fl::e_x = Fl::e_x_root-window->x();
                            Fl::e_y = Fl::e_y_root-window->y();
                        }
                        fl_event_time = data[3];
                        fl_dnd_source_action = data[4];
                        fl_dnd_action = fl_XdndActionCopy;
                        int accept = Fl::handle(FL_DND_DRAG, window);
                        fl_sendClientMessage(data[0], fl_XdndStatus,
                            fl_xevent.xclient.window,
                            accept ? 1 : 0,
                            0,           // used for xy rectangle to not send position inside
                            0,           // used for width+height of rectangle
                            accept ? fl_dnd_action : None);
                        return true;

                    }
                    else if (message == fl_XdndLeave)
                    {
                                 // don't send a finished message to it
                        fl_dnd_source_window = 0;
                        event = FL_DND_LEAVE;
                        break;

                    }
                    else if (message == fl_XdndDrop)
                    {
                        in_a_window = true;
                        xmousewin = window;

                        fl_dnd_source_window = data[0];
                        fl_event_time = data[2];
                        Window to_window = fl_xevent.xclient.window;
                        if (Fl::handle(FL_DND_RELEASE, window))
                        {
                            fl_selection_requestor = Fl::belowmouse();
                            XConvertSelection(fl_display, fl_XdndSelection,
                                fl_dnd_type, XA_SECONDARY,
                                to_window, fl_event_time);
                        }
                        else
                        {
                    // Send the finished message if I refuse the drop.
                    // It is not clear whether I can just send finished always,
                    // or if I have to wait for the SelectionNotify event as the
                    // code is currently doing.
                            fl_sendClientMessage(fl_dnd_source_window, fl_XdndFinished, to_window);
                            fl_dnd_source_window = 0;
                        }
                        return true;

                    }
                    break;
                }

        // We cannot rely on the x,y position in the configure notify event.
        // I now think this is an unavoidable problem with X: it is impossible
        // for a window manager to prevent the "real" notify event from being
        // sent when it resizes the contents, even though it can send an
        // artificial event with the correct position afterwards (and some
        // window managers do not send this fake event anyway)
        // So anyway, do a round trip to find the correct x,y:
        // WAS: Actually, TWO round trips! Is X stoopid or what?
            case MapNotify:
            //event = FL_SHOW;
            case ConfigureNotify:
                {
                    window = fl_find(fl_xevent.xmapping.window);
                    if (!window) break;

            // ignore child windows
                    if (window->parent()) break;

            // figure out where OS really put window
                    XWindowAttributes actual;
                    XGetWindowAttributes(fl_display, fl_xid(window), &actual);
                    Window cr; int X, Y, W = actual.width, H = actual.height;
                    XTranslateCoordinates(fl_display, fl_xid(window), actual.root,
                        0, 0, &X, &Y, &cr);
#if 0
            // Faster version that does not bother with calling resize as the
            // user drags the window around. This was what most Win32 versions
            // of fltk did. This breaks programs that want to track the current
            // position to figure out what corner is being resized when layout
            // is called.
                    if (W == window->w() && H == window->h())
                    {
                        window->x(X);
                        window->y(Y);
                        break;
                    }
#endif
            // tell Fl_Window about it and set flag to prevent echoing:
                    if (window->resize(X, Y, W, H)) resize_from_system = window;
                    break;               // allow add_handler to do something too
                }

            case UnmapNotify:
                window = fl_find(fl_xevent.xmapping.window);
                if (!window) break;
            // ignore child windows
                if (window->parent()) break;
            // turning this flag makes iconic() return true:
                Fl_X::i(window)->wait_for_expose = true;
            //event = FL_HIDE;
                break;               // allow add_handler to do something too

            case Expose:
            case GraphicsExpose:
                if (!window) break;
            // If this window completely fills it's parent, parent will not get
            // an expose event and the wait flag will not turn off. So force this:
                if (Fl_X::i(window)->wait_for_expose)
                {
                    for (Fl_Window* w = window;;)
                    {
                        Fl_X::i(w)->wait_for_expose = false;
                        w = w->window();
                        if (!w) break;
                    }
                }
                Fl_X::i(window)->expose(fl_xevent.xexpose.x, fl_xevent.xexpose.y,
                    fl_xevent.xexpose.width, fl_xevent.xexpose.height);
                return true;

            case ButtonPress:
                {
                    unsigned n = fl_xevent.xbutton.button;
                    Fl::e_keysym = FL_Button(n);
                    set_event_xy(true);
            // turn off is_click if enough time or mouse movement has passed:
                    if (Fl::e_is_click == Fl::e_keysym)
                    {
                        Fl::e_clicks++;
                    } else {
                        Fl::e_clicks = 0;
                        Fl::e_is_click = Fl::e_keysym;
                    }
                    if (n == wheel_up_button) {
                        Fl::e_dy = +1;
                        event = FL_MOUSEWHEEL;
                    }
                    else if (n == wheel_down_button) {
                        Fl::e_dy = -1;
                        event = FL_MOUSEWHEEL;
                    } else {
                        Fl::e_state |= (FL_BUTTON1 << (n-1));
                        event = FL_PUSH;
                    }
                }
                goto J1;

            case MotionNotify:
                set_event_xy(false);
#if CONSOLIDATE_MOTION
                send_motion = window;
                return false;
#else
                event = FL_MOVE;
                goto J1;
#endif

            case ButtonRelease:
                {
                    unsigned n = fl_xevent.xbutton.button;
                    Fl::e_keysym = FL_Button(n);
                    set_event_xy(false);
            //if (n == wheel_up_button || n == wheel_down_button) break;
                    Fl::e_state &= ~(FL_BUTTON1 << (n-1));
                    event = FL_RELEASE;
                }
                goto J1;

            case EnterNotify:
                set_event_xy(false);
                Fl::e_state = fl_xevent.xcrossing.state << 16;
                if (fl_xevent.xcrossing.detail == NotifyInferior) break;
            //      printf("EnterNotify window %s, xmousewin %s\n",
            //         window ? window->label() : "NULL",
            //         xmousewin ? xmousewin->label() : "NULL");
            // XInstallColormap(fl_display, Fl_X::i(window)->colormap);
                event = FL_ENTER;
            J1:
                xmousewin = window;
            // send a mouse event, with cruft so the grab around modal things works:
                if (Fl::grab_)
                {
                    int ret = Fl::handle(event, window);
                    if (Fl::grab_ && !Fl::exit_modal_)
                        XAllowEvents(fl_display, SyncPointer, CurrentTime);

                // If modal is on and 0 is returned, we should turn off modal and
                // pass the event on to other widgets. The pass-on part is nyi!
                    if(event==FL_PUSH && !ret && Fl::grab_) {
                        Fl::exit_modal();
                    }
                    return true;
                }
                break;

            case LeaveNotify:
                if (fl_xevent.xcrossing.detail == NotifyInferior) break;
                set_event_xy(false);
                Fl::e_state = fl_xevent.xcrossing.state << 16;
                if (fl_xevent.xcrossing.detail == NotifyInferior) break;
            //      printf("LeaveNotify window %s, xmousewin %s\n",
            //         window ? window->label() : "NULL",
            //         xmousewin ? xmousewin->label() : "NULL");
                in_a_window = false;
                xmousewin = 0;
                break;

            case FocusIn:
#if HAVE_XUTF8
                if (fl_xim_ic) XSetICFocus(fl_xim_ic);
#endif
                xfocus = window;
                if (window) {fl_fix_focus(); return true;}
                break;

            case FocusOut:
#if HAVE_XUTF8
                if (fl_xim_ic) XUnsetICFocus(fl_xim_ic);
#endif
                if (window && window == xfocus) {xfocus = 0; fl_fix_focus(); return true;}
                break;

            case KeyPress:
            case KeyRelease:
                {
                KEYPRESS:
            //if (Fl::grab_) XAllowEvents(fl_display, SyncKeyboard, CurrentTime);
                    int keycode = fl_xevent.xkey.keycode;
                    static int lastkeycode;

                    static char buffer[255];
                    KeySym keysym;

                    if (fl_xevent.type == KeyPress)
                    {
                        event = FL_KEY;
                        int len=0;
                        fl_key_vector[keycode/8] |= (1 << (keycode%8));

                // Make repeating keys increment the click counter:
                        if (keycode == lastkeycode) {
                            Fl::e_clicks++;
                            Fl::e_is_click = 0;

                        } else {

                            Fl::e_clicks = 0;
                            Fl::e_is_click = 1;
                            lastkeycode = keycode;
                        }
#if HAVE_XUTF8
                        if (fl_xim_ic) {
                            static Window xim_win = 0;
                            if (xim_win != fl_xid(window))
                            {
                                XDestroyIC(fl_xim_ic);
                                xim_win = fl_xid(window);
                                fl_xim_ic = XCreateIC(fl_xim_im,
                                        XNInputStyle, (XIMPreeditNothing | XIMStatusNothing),
                                        XNClientWindow, xim_win,
                                        XNFocusWindow, xim_win,
                                        NULL);
                            }
                            if (!filtered) {
                                Status status;
                                len = XUtf8LookupString(fl_xim_ic, (XKeyPressedEvent *)&fl_xevent.xkey,
                                                        buffer, 255, &keysym, &status);
                                if(buffer[0] && len < 1) len = 1;

                            } else {
                                keysym = XKeycodeToKeysym(fl_display, keycode, 0);
                            }

                        } else
#endif
                        {
                            len = XLookupString((XKeyEvent*)&(fl_xevent.xkey), buffer, 20, &keysym, 0);
                            if (keysym && keysym < 0x400) { // a character in latin-1,2,3,4 sets
                        // force it to type a character (not sure if this ever is needed):
                        // if (!len) {buffer[0] = char(keysym); len = 1;}
#if HAVE_XUTF8
                                len = fl_ucs2utf(XKeysymToUcs(keysym), buffer);
#else
                                len = 1;
                                buffer[0] = (char)(keysym&0xFF);
#endif
                                if (len < 1) len = 1;
                        // ignore all effects of shift on the keysyms, which makes it a lot
                        // easier to program shortcuts and is Windoze-compatable:
                                keysym = XKeycodeToKeysym(fl_display, keycode, 0);
                            }
                        }
                        if (Fl::event_state(FL_CTRL) && keysym == '-') buffer[0] = 0x1f; // ^_

                // Any keys producing foreign letters produces the bottom 8 bits:
                // if (!len && keysym < 0xf00) {buffer[0]=(char)keysym; len = 1;}

                        buffer[len] = 0;
                        Fl::e_text = buffer;
                        Fl::e_length = len;

                    } else {

                // Stupid X sends fake key-up events when a repeating key is held
                // down, probably due to some back compatability problem. Fortunatley
                // we can detect this because the repeating KeyPress event is in
                // the queue, get it and execute it instead:
                        XEvent temp;
                        if (XCheckIfEvent(fl_display,&temp,fake_keyup_test,(char*)(&fl_xevent)))
                        {
                            fl_xevent = temp;
                            goto KEYPRESS;
                        }
                        event = FL_KEYUP;
                        fl_key_vector[keycode/8] &= ~(1 << (keycode%8));
                // event_is_click is left on if they press & release the key quickly:
                        Fl::e_is_click = (keycode == lastkeycode);
                // make next keypress not be a repeating one:
                        lastkeycode = 0;
                        keysym = XKeycodeToKeysym(fl_display, keycode, 0);
                    }

            // Use the unshifted keysym! This matches the symbols that the Win32
            // version produces. However this will defeat older keyboard layouts
            // that use shifted values for function keys.
            // keysym = XKeycodeToKeysym(fl_display, keycode, 0);

            // XK_KP_*
                    if (keysym >= 0xff95 && keysym <= 0xff9f)
                    {
                // Make all keypad keys act like NumLock is on all the time. This
                // is nicer (imho), but more importantly this gets rid of a range of
                // keysyms that the Win32 version cannot produce. This strange
                // table translates XK_KP_Home to '7', etc:
                        keysym = FL_KP("7486293150."[keysym-0xff95]);
                        Fl::e_text[0] = char(keysym) & 0x7F;
                        Fl::e_text[1] = 0;
                        Fl::e_length = 1;
                    }                    // XK_Meta_L
                    else if (keysym == 0xffe7)
                    {
                // old versions of XFree86 used XK_Meta for the "windows" key
                        keysym = FL_Win_L;
                    }                    // XK_Meta_R
                    else if (keysym == 0xffe8)
                    {
                        keysym = FL_Win_R;
                    }                    // X did not map this key
                    else if (!keysym)
                    {
                        keysym = keycode|0x8000;
#ifdef __sgi
                // You can plug a microsoft keyboard into an Irix box but these
                // keys are not translated.  Make them translate like XFree86 does:
                        switch (keycode)
                        {
                            case 147: keysym = FL_Win_L; break;
                            case 148: keysym = FL_Win_R; break;
                            case 149: keysym = FL_Menu; break;
                        }
#endif
                    }
                    Fl::e_keysym = int(keysym);
                    set_event_xy(true);
                    break;
                }
            case SelectionNotify:
                {
                    if (!fl_selection_requestor) return false;
                    static unsigned char* buffer;
                    if (buffer) {XFree(buffer); buffer = 0;}
                    long read = 0;
                    if (fl_xevent.xselection.property) for (;;)
                        {
                // The Xdnd code pastes 64K chunks together, possibly to avoid
                // bugs in X servers, or maybe to avoid an extra round-trip to
                // get the property length.  I copy this here:
                            Atom actual; int format; unsigned long count, remaining;
                            unsigned char* portion;
                            if (XGetWindowProperty(fl_display,
                                        fl_xevent.xselection.requestor,
                                        fl_xevent.xselection.property,
                                        read/4, 65536, 1, 0,
                                        &actual, &format, &count, &remaining,
                                 // quit on error
                                        &portion)) break;
                            if (read)        // append to the accumulated buffer
                            {
                                buffer = (unsigned char*)realloc(buffer, read+count*format/8+remaining);
                                memcpy(buffer+read, portion, count*format/8);
                                XFree(portion);
                            }                // Use the first section without moving the memory:
                            else
                            {
                                buffer = portion;
                            }
                            read += count*format/8;
                            if (!remaining) break;
                        }
                    Fl::e_text = (char*)buffer;
                    Fl::e_length = read;
                    fl_selection_requestor->handle(FL_PASTE);
            // Detect if this paste is due to Xdnd by the property name (I use
            // XA_SECONDARY for that) and send an XdndFinished message. It is not
            // clear if this has to be delayed until now or if it can be done
            // immediatly after calling XConvertSelection.
                    if (fl_xevent.xselection.property == XA_SECONDARY &&
                            fl_dnd_source_window)
                    {
                        fl_sendClientMessage(fl_dnd_source_window, fl_XdndFinished,
                            fl_xevent.xselection.requestor);
                                 // don't send a second time
                        fl_dnd_source_window = 0;
                    }
                    return true;
                }

            case SelectionClear:
                {
                    bool clipboard = fl_xevent.xselectionclear.selection == CLIPBOARD;
                    fl_i_own_selection[clipboard] = false;
                    return true;
                }

            case SelectionRequest:
                {
                    XSelectionEvent e;
                    e.type = SelectionNotify;
                    e.requestor = fl_xevent.xselectionrequest.requestor;
                    e.selection = fl_xevent.xselectionrequest.selection;
                    bool clipboard = e.selection == CLIPBOARD;
                    e.target = fl_xevent.xselectionrequest.target;
                    e.time = fl_xevent.xselectionrequest.time;
                    e.property = fl_xevent.xselectionrequest.property;
                    if (e.target == TARGETS) {
#if HAVE_XUTF8
                        Atom a = fl_XaUtf8String; //XA_STRING;
#else
                        Atom a = XA_STRING;
#endif
                        XChangeProperty(fl_display, e.requestor, e.property,
                            XA_ATOM, sizeof(Atom)*8, 0, (unsigned char*)&a,
                            sizeof(Atom));
                    }
                    else if(/*e.target == XA_STRING &&*/selection_length[clipboard]) {
                        XChangeProperty(fl_display, e.requestor, e.property,
                            e.target, 8, 0,
                            (unsigned char *)selection_buffer[clipboard],
                            selection_length[clipboard]);
                    } else {
                //    char* x = XGetAtomName(fl_display,e.target);
                //    fprintf(stderr,"selection request of %s\n",x);
                //    XFree(x);
                        e.property = 0;
                    }
                    XSendEvent(fl_display, e.requestor, 0, 0, (XEvent *)&e);
                }
                return true;

        }

    } catch(...) {
        terminate();
    }

    return Fl::handle(event, window);
}


////////////////////////////////////////////////////////////////

void Fl_Window::layout()
{
    if (this == resize_from_system)
    {
        // prevent echoing changes back to the server
        resize_from_system = 0;
    }
    else if ((layout_damage()&FL_LAYOUT_XYWH) && i) // only for shown windows
    {
        // figure out where the window should be in it's parent:
        int x = this->x(); int y = this->y();
        for (Fl_Widget* p = parent(); p && !p->is_window(); p = p->parent())
        {
            x += p->x(); y += p->y();
        }
        if (layout_damage() & FL_LAYOUT_WH)
        {
            // Some window managers refuse to allow resizes unless the resize
            // information allows it:
            if(!parent() && (minw() == maxw() && minh() == maxh())) size_range(w(), h(), w(), h());
            XMoveResizeWindow(fl_display, i->xid, x, y,
                w()>0 ? w() : 1, h()>0 ? h() : 1);
            // Wait for echo (relies on window having StaticGravity!!!)
            i->wait_for_expose = true;
        }
        else
        {
            XMoveWindow(fl_display, i->xid, x, y);
        }
    }
    Fl_Group::layout();
}

// returns pointer to the filename, or null if name ends with '/'
const char *fl_file_filename(const char *name)
{
    const char *p,*q;
    for (p=q=name; *p;) if (*p++ == '/') q = p;
    return q;
}


////////////////////////////////////////////////////////////////
// Innards of Fl_Window::create()

extern bool fl_show_iconic;      // In Fl_Window.cxx, set by iconize() or -i switch

void Fl_X::create(Fl_Window* window,
    XVisualInfo *visual, Colormap colormap,
    int background)
{
    XSetWindowAttributes attr;
    attr.border_pixel = 0;
    attr.colormap = colormap;
    attr.bit_gravity = 0;        // StaticGravity;
    int mask = CWBorderPixel|CWColormap|CWEventMask|CWBitGravity;

    int W = window->w();
    if (W <= 0) W = 1;           // X don't like zero...
    int H = window->h();
    if (H <= 0) H = 1;           // X don't like zero...
    int X = window->x();
    int Y = window->y();

    ulong root;

    if (window->parent())
    {
        // locate the surrounding window and adjust window position for
        // any intermediate group widgets:
        for (Fl_Widget *o = window->parent(); ; o = o->parent())
        {
            if (o->is_window()) {root = ((Fl_Window*)o)->i->xid; break;}
            X += o->x();
            Y += o->y();
        }
        attr.event_mask = ExposureMask;
    }
    else
    {
        if (X == FL_USEDEFAULT) X = (DisplayWidth(fl_display,fl_screen)-W)/2;
        if (Y == FL_USEDEFAULT) Y = (DisplayHeight(fl_display,fl_screen)-H)/2;
        root = RootWindow(fl_display, fl_screen);
        attr.event_mask =
            ExposureMask | StructureNotifyMask
            | KeyPressMask | KeyReleaseMask | KeymapStateMask | FocusChangeMask
            | ButtonPressMask | ButtonReleaseMask
            | EnterWindowMask | LeaveWindowMask
            | PointerMotionMask;
        if (window->override())
        {
            Fl::flush();         // make sure save_under does not undo any drawing!
            attr.override_redirect = 1;
            attr.save_under = 1;
            mask |= CWOverrideRedirect | CWSaveUnder;
        }
    }

    if (background >= 0)
    {
        attr.background_pixel = background;
        mask |= CWBackPixel;
    }

    Fl_X* x = new Fl_X;
    x->xid = XCreateWindow(fl_display,
            root,
            X, Y, W, H,
            0,                       // borderwidth
            visual->depth,
            InputOutput,
            visual->visual,
            mask, &attr);

    x->backbuffer.xid = 0;
    x->window = window; window->i = x;
    x->region = 0;
    x->wait_for_expose = true;
    x->next = Fl_X::first;
    Fl_X::first = x;

    // send junk to X window manager:
    if (!window->parent() && !window->override())
    {
        // Setting this allows the window manager to use the window's class
        // to look up things like border colors and icons in the xrdb database:
        XChangeProperty(fl_display, x->xid, XA_WM_CLASS, XA_STRING, 8, 0,
            (unsigned char *)Fl_Window::xclass().c_str(), Fl_Window::xclass().length()+1);

        // Set the labels
        Fl_WM::set_window_title(x->xid, window->label().c_str(), window->label().length());
        if(!window->iconlabel().empty())
            Fl_WM::set_window_icontitle(x->xid, window->iconlabel().c_str(), window->iconlabel().length());
        else {
            Fl_String iname(fl_file_filename(window->label().c_str()));
            Fl_WM::set_window_icontitle(x->xid, iname.c_str(), iname.length());
        }

        // Makes the close button produce an event:
        XChangeProperty(fl_display, x->xid, WM_PROTOCOLS,
            XA_ATOM, 32, 0, (uchar*)&WM_DELETE_WINDOW, 1);

        // Make it receptive to DnD:
        int version = 4;
        XChangeProperty(fl_display, x->xid, fl_XdndAware,
            XA_ATOM, sizeof(int)*8, 0, (unsigned char*)&version, 1);

        // Send child window information:
        if (window->child_of() && window->child_of()->shown())
            XSetTransientForHint(fl_display, x->xid, window->child_of()->i->xid);

        // Set up the icon and initial icon state:
        XWMHints hints;
        hints.input = True;      // some window managers require this to be sent?
        hints.flags = InputHint;
        if (fl_show_iconic)
        {
            hints.flags |= StateHint;
            hints.initial_state = IconicState;
            fl_show_iconic = false;
        }
        if (window->icon())
        {
            hints.icon_pixmap = (Pixmap)window->icon();
            hints.flags       |= IconPixmapHint;
        }
        XSetWMHints(fl_display, x->xid, &hints);

        // send size limits and border:
        x->sendxjunk();
    }
}


////////////////////////////////////////////////////////////////
// Send X window stuff that can be changed over time:

void Fl_X::sendxjunk()
{
    // it's not a window manager window!
    if (window->parent() || window->override()) return;

    XSizeHints hints;
    // memset(&hints, 0, sizeof(hints)); jreiser suggestion to fix purify?
    hints.min_width = window->minw();
    hints.min_height = window->minh();
    hints.max_width = window->maxw();
    hints.max_height = window->maxh();
    hints.width_inc = window->dw();
    hints.height_inc = window->dh();
    hints.win_gravity = StaticGravity;

    // see the file /usr/include/X11/Xm/MwmUtil.h:
    // fill all fields to avoid bugs in kwm and perhaps other window managers:
    // 0, MWM_FUNC_ALL, MWM_DECOR_ALL
    long prop[5] = {0, 1, 1, 0, 0};

    if (hints.min_width != hints.max_width ||
            hints.min_height != hints.max_height)
    {
        // resizable
        hints.flags = PMinSize|PWinGravity;
        if (hints.max_width >= hints.min_width || hints.max_height >= hints.min_height)
        {
            hints.flags = PMinSize|PMaxSize|PWinGravity;
            // unfortunately we can't set just one maximum size.  Guess a
            // value for the other one.  Some window managers will make the
            // window fit on screen when maximized, others will put it off screen:
            if (hints.max_width < hints.min_width)
                hints.max_width = DisplayWidth(fl_display,fl_screen);
            if (hints.max_height < hints.min_height)
                hints.max_height = DisplayHeight(fl_display,fl_screen);
        }
        if (hints.width_inc && hints.height_inc) hints.flags |= PResizeInc;
        //     if (window->aspect) {
        //       hints.min_aspect.x = hints.max_aspect.x = hints.min_width;
        //       hints.min_aspect.y = hints.max_aspect.y = hints.min_height;
        //       hints.flags |= PAspect;
        //     }
    }                            // not resizable:
    else
    {
        hints.flags = PMinSize|PMaxSize|PWinGravity;
        prop[0] = 1;             // MWM_HINTS_FUNCTIONS
        prop[1] = 1|2|16;        // MWM_FUNC_ALL | MWM_FUNC_RESIZE | MWM_FUNC_MAXIMIZE
    }

    if (window->x() != FL_USEDEFAULT || window->y() != FL_USEDEFAULT)
    {
        hints.flags |= USPosition;
        hints.x = window->x();
        hints.y = window->y();
    }

    if (!window->border())
    {
        prop[0] |= 2;            // MWM_HINTS_DECORATIONS
        prop[2] = 0;             // no decorations
    }

    XSetWMNormalHints(fl_display, xid, &hints);
    XChangeProperty(fl_display, xid,
        fl_MOTIF_WM_HINTS, fl_MOTIF_WM_HINTS,
        32, 0, (unsigned char *)prop, 5);
}


void Fl_Window::size_range_()
{
    m_size_range = true;
    if (i) i->sendxjunk();
}


bool Fl_Window::iconic() const
{
    return (i && visible() && i->wait_for_expose);
}


////////////////////////////////////////////////////////////////

void Fl_Window::label(const char *l, const char *il)
{
    Fl_String label(l), ilabel(il);
    this->label(label, ilabel);
}

void Fl_Window::label(const Fl_String &l, const Fl_String &il)
{
    Fl_Widget::label(l);
    iconlabel_ = il;

    if(i && !parent()) {
        // Label:
        if(l.empty()) {
            Fl_WM::set_window_title(i->xid, "", 0);
        } else {
            Fl_WM::set_window_title(i->xid, l.c_str(), l.length());
        }

        // Icon label:
        if(iconlabel_.empty()) {
            Fl_String ilabel = fl_file_filename(l.c_str());
            Fl_WM::set_window_icontitle(i->xid, ilabel.c_str(), ilabel.length());
        } else {
            Fl_WM::set_window_icontitle(i->xid, iconlabel_.c_str(), iconlabel_.length());
        }
    }
}

////////////////////////////////////////////////////////////////
// Drawing context

Fl_Drawable* fl_drawable;
Window fl_window;
const Fl_Window *Fl_Window::current_;
GC fl_gc;

void Fl_Window::make_current() const
{
    current_ = this;
    i->make_current();
    static GC gc;                // the GC used by all X windows with fl_visual
    if (!gc) gc = XCreateGC(fl_display, i->xid, 0, 0);
    fl_gc = gc;
}


////////////////////////////////////////////////////////////////
// Get the KDE colors that it writes to the xrdb database:

// Set this to 1 to get my attempt to improve XGetDefault:
#define MY_GET_DEFAULT 0

#if MY_GET_DEFAULT

// Simplified resource search that understands periods in the names.
// Matches class.a:, class*a:, *.a:, *a:, and a:
// Ignores case on everything.
// Strips whitespace from both sides of the value
// An empty value returns null.
// Also understands = instead of :
// Comments start with ! or ;
// No quoting of any kind on the values!

// case independent compare, r advanced to point after match:
static int match(char* & rr, const char* a)
{
    for (char* r = rr; ; a++, r++)
    {
        if (!*a) {rr = r; return 1;}
        if (tolower(*r) != tolower(*a)) return 0;
    }
}


// return true if this character is the end of line:
static int iseol(char c) {return !c || c=='\n' || c=='!' ||c==';';}

// like strtok, this mangles the string temporarily using these:
static char* resourcestring;
static char* clobbered;
static char clobbered_value;

static const char* get_default(const char* a)
{
    if (clobbered) {*clobbered = clobbered_value; clobbered = 0;}
    if (!resourcestring) resourcestring = XResourceManagerString(fl_display);
    char* r = resourcestring;
    char* found = 0;
    for (;;)                     // for each line in r
    {
        // skip leading whitespace (and also all blank lines):
        while (isspace(*r)) r++;
        if (!*r) break;
        // exact is true if the program name is matched:
        int exact = 0;
        if (*r == '*')
        {
            // checked for * or *.:
            r++;
            if (*r == '.') r++;
        }
        else if (match(r, Fl_Window::xclass()) && (*r == '.' || *r == '*'))
        {
            // matched the program name:
            r++;
            exact = 1;
        }                        // otherwise try just 'a':
        if (match(r, a))
        {
            while (*r != '\n' && isspace(*r)) r++;
            if (*r == ':' || *r == '=')
            {
                r++;
                while (*r != '\n' && isspace(*r)) r++;
                if (iseol(*r))   // blank attribute
                {
                    if (exact) return 0;
                    goto SKIP;
                }
                // find the end of the word (point to first whitespace at eol or \n):
                char* e = r; while (!iseol(*e)) e++;
                while (e > r && isspace(*(e-1))) e--;
                // remove anything for previous find
                if (clobbered) *clobbered = clobbered_value;
                // replace the end with a null, which we will put back later:
                clobbered = e;
                clobbered_value = *e;
                *e = 0;
                if (exact || !clobbered_value) return r;
                found = r; r = e+1;
            }
            else
            {
                // check for blank attribute name with no : or = sign:
                if (exact && iseol(*r)) return 0;
            }
        }
    SKIP:
         // go to next line
        while (*r && *r++ != '\n');
    }
    return found;
}


#else

static inline const char* get_default(const char* a)
{
    return XGetDefault(fl_display, Fl_Window::xclass().c_str(), a);
}

static inline const char* get_default(const char* a, const char* b)
{
    return XGetDefault(fl_display, a, b);
}

#endif

static Fl_Color to_color(const char* p)
{
    return p ? fl_rgb(p) : 0;
}


bool fl_get_system_colors()
{
    fl_open_display();

    Fl_Color color;

    color = to_color(get_default("background"));
    if (color) fl_background(color);

    color = to_color(get_default("foreground"));
    if (color)
    {
        Fl_Widget::default_style->label_color = color;
        Fl_Widget::default_style->highlight_label_color = color;
    }

#if MY_GET_DEFAULT
    color = to_color(get_default("Text.background"));
    if (color) Fl_Widget::default_style->color = color;

    color = to_color(get_default("Text.foreground"));
    if (color) Fl_Widget::default_style->text_color = color;

    color = to_color(get_default("Text.selectBackground"));
    if (color) Fl_Widget::default_style->selection_color = color;

    color = to_color(get_default("Text.selectForeground"));
    if (color) Fl_Widget::default_style->selection_text_color = color;
#else
    color = to_color(get_default("Text","background"));
    if (color) Fl_Widget::default_style->color = color;

    color = to_color(get_default("Text","foreground"));
    if (color) Fl_Widget::default_style->text_color = color;

    color = to_color(get_default("Text","selectBackground"));
    if (color) Fl_Widget::default_style->selection_color = color;

    color = to_color(get_default("Text","selectForeground"));
    if (color) Fl_Widget::default_style->selection_text_color = color;
#endif

    // also Scrollbar,width
    // does not appear to be anything there for setting the tooltips...
    // Maybe I should just add Tooltip,back/foreground.

    // Mousewheel stuff is read from the XDefaults database but there
    // are no standards for these. We should change these to match any
    // standards that arise:

    const char* w = get_default("wheel_scroll_lines");
    if (w) Fl_Style::wheel_scroll_lines = atoi(w);

    w = get_default("wheel_up_button");
    if (w) wheel_up_button = atoi(w);

    w = get_default("wheel_down_button");
    if (w) wheel_down_button = atoi(w);

#if MY_GET_DEFAULT
    // undo my mangling of the x resource string:
    if (clobbered) {*clobbered = clobbered_value; clobbered = 0;}
#endif

    return true;
}


//
// End of "$Id$".
//
