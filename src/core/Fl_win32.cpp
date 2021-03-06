//
// "$Id$"
//
// _WIN32-specific code for the Fast Light Tool Kit (FLTK).
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

// This file contains win32-specific code for fltk which is always linked
// in.	Search other files for "_WIN32" or filenames ending in _win32.C
// for other system-specific code.

#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Style.h>
#include <efltk/fl_utf8.h>
#include <efltk/win32.h>

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include <sys/types.h>
#include <limits.h>
#include <time.h>
#include <winsock.h>

// The following include files require GCC 3.x or a non-GNU compiler...
#if !defined(__GNUC__) || __GNUC__ >= 3
# include <ole2.h>
# include <ShellApi.h>
# include <imm.h>
# include "aimm.h"
#endif // !__GNUC__ || __GNUC__ >= 3

//
// USE_ASYNC_SELECT - define it if you have WSAAsyncSelect()...
//

//#define USE_ASYNC_SELECT

#ifndef _WIN32_WCE 
 #undef USE_ASYNC_SELECT
#endif
//
// USE_TRACK_MOUSE - define it if you have TrackMouseEvent()...
//
// Apparently, at least some versions of Cygwin/MingW don't provide
// the TrackMouseEvent() function.  You can define this by hand
// if you have it - this is only needed to support subwindow
// enter/leave notification under Windows.
//

//#define USE_TRACK_MOUSE

//
// WM_SYNCPAINT is an "undocumented" message, which is finally defined in
// VC++ 6.0.
//
#ifndef WM_SYNCPAINT
#  define WM_SYNCPAINT 0x0088
#endif

#ifndef WM_MOUSELEAVE
#  define WM_MOUSELEAVE 0x02a3
#endif

#ifndef WM_MOUSEWHEEL
#  define WM_MOUSEWHEEL 0x020a
#endif

#ifndef WHEEL_DELTA
#  define WHEEL_DELTA 120        // according to MSDN.
#endif

#ifndef ENUM_CURRENT_SETTINGS
#  define ENUM_CURRENT_SETTINGS       ((DWORD)-1)
#endif

//
// WM_FLSELECT is the user-defined message that we get when one of
// the sockets has pending data, etc.
//

#define WM_FLSELECT (WM_USER+0x0400)

static bool ticks_started=false;
static DWORD start;
#define TIME_WRAP_VALUE	(~(DWORD)0)

void fl_start_ticks() {
	if(ticks_started) return;

    /* Set first ticks value */
    start = GetTickCount();
	ticks_started = true;
}

uint32 Fl::ticks()
{
	if(!ticks_started) fl_start_ticks();

    DWORD now, ticks;
    now = GetTickCount();
    if ( now < start ) ticks = (TIME_WRAP_VALUE-start) + now;
    else ticks = (now - start);
    return ticks;
}

void Fl::sleep(int ms) {
    Sleep(ms);
}

void fl_open_display()
{
    static bool been_here=false;
    if(been_here) return;

    fl_start_ticks();

    extern void fl_private_init();
    fl_private_init(); //Fl_init.cpp

    been_here=true;
}

////////////////////////////////////////////////////////////////
// interface to poll/select call:

// fd's are only implemented for sockets.  Microsoft Windows does not
// have a unified IO system, so it doesn't support select() on files,
// devices, or pipes...
//
// Microsoft provides the Berkeley select() call and an asynchronous
// select function that sends a _WIN32 message when the select condition
// exists...

#ifndef USE_ASYNC_SELECT
static fd_set fdsets[3];
#endif                           // !USE_ASYNC_SELECT

#define POLLIN 1
#define POLLOUT 4
#define POLLERR 8

struct FD {
    int fd;
    short events;
    void (*cb)(int, void*);
    void *arg;
#ifdef USE_ASYNC_SELECT
	HWND window;
#endif
};

static Fl_Ptr_List fd;

void Fl::add_fd(int n, int events, void (*cb)(int, void*), void *v)
{
#ifdef USE_ASYNC_SELECT
	if(!Fl::first_window() || !Fl::first_window()->shown()) {
		Fl::warning("Cannot register fd (%d). No window created yet.", n);	
		return;
	}
#endif

    remove_fd(n,events);

	struct FD *f = new struct FD;
    f->fd = n;
    f->events = events;
    f->cb = cb;
    f->arg = v;

	fd.append(f);

#ifdef USE_ASYNC_SELECT
    int mask = 0;
    if (events & POLLIN) mask |= FD_READ;
    if (events & POLLOUT) mask |= FD_WRITE;
    if (events & POLLERR) mask |= FD_CLOSE;
	
	HWND hwdn = fl_xid(Fl::first_window());
    f->window = hwnd;
	
    if(WSAAsyncSelect(n, hwnd, WM_FLSELECT, mask) != 0) {
		remove_fd(n,events);		
	}
#else
    if (events & POLLIN) FD_SET(n, &fdsets[0]);
    if (events & POLLOUT) FD_SET(n, &fdsets[1]);
    if (events & POLLERR) FD_SET(n, &fdsets[2]);
#endif                       // USE_ASYNC_SELECT
}


void Fl::add_fd(int fd, void (*cb)(int, void*), void* v)
{
    Fl::add_fd(fd, POLLIN, cb, v);
}

void Fl::remove_fd(int n, int events)
{
    for(unsigned i=0; i<fd.size(); i++)
    {
		struct FD *f = (struct FD *)fd[i];
        if(f->fd == n) {
#ifdef USE_ASYNC_SELECT
		    WSAAsyncSelect(n, f->window, 0, 0);
#endif
			fd.remove(i);
			delete f;
			break;
        }
    }

#ifndef USE_ASYNC_SELECT
    if (events & POLLIN)  FD_CLR((unsigned)n, &fdsets[0]);
    if (events & POLLOUT) FD_CLR((unsigned)n, &fdsets[1]);
    if (events & POLLERR) FD_CLR((unsigned)n, &fdsets[2]);
#endif                       // USE_ASYNC_SELECT
}


// these pointers are set by the Fl::lock() function:
static void nothing() {}
void (*fl_lock_function)() = nothing;
void (*fl_unlock_function)() = nothing;

static void* thread_message_;
void* Fl::thread_message()
{
    void* r = thread_message_;
    thread_message_ = 0;
    return r;
}


MSG fl_msg;
IActiveIMMApp *fl_aimm = NULL;

// Wait up to the given time for any events or sockets to become ready,
// do the callbacks for the events and sockets.
// It *should* return negative on error, 0 if nothing happens before
// timeout, and >0 if any callbacks were done.	This version only
// returns zero if nothing happens during a 0.0 timeout, otherwise
// it returns 1.
static inline int fl_wait(double time_to_wait)
{
    int have_message = 0;
    int timerid;

#ifndef USE_ASYNC_SELECT
    if (fd.size())
    {
        // For _WIN32 we need to poll for socket input FIRST, since
        // the event queue is not something we can select() on...
        timeval t;
        t.tv_sec = 0;
        t.tv_usec = 0;

        fd_set fdt[3];
        fdt[0] = fdsets[0];
        fdt[1] = fdsets[1];
        fdt[2] = fdsets[2];

		int rc = ::select(0, &fdt[0], &fdt[1], &fdt[2], &t);
        if(rc>0)
        {
            // We got something - do the callback!
			for (unsigned i = 0; i < fd.size(); i ++)
            {
				struct FD *f = (struct FD*)fd[i];
                int sock = f->fd;
                
				short revents = 0;
                if (FD_ISSET(sock, &fdt[0])) revents |= POLLIN;
                if (FD_ISSET(sock, &fdt[1])) revents |= POLLOUT;
                if (FD_ISSET(sock, &fdt[2])) revents |= POLLERR;

                if (f->events & revents) f->cb(sock, f->arg);
            }
            time_to_wait = 0.0;  // just peek for any messages
        }
#ifndef __CYGWIN__
		else {
			// we need to check them periodically, so set a short timeout (100ms):
			if (time_to_wait > .1) time_to_wait = .1;
		}
#endif

    }
#endif                       // USE_ASYNC_SELECT

    fl_unlock_function();

    if (time_to_wait < 2147483.648) {
        have_message = PeekMessage(&fl_msg, NULL, 0, 0, PM_REMOVE);
        if(!have_message)
        {
            int t = (int)(time_to_wait * 1000.0 + .5);			
            if(t > 0) {
				// Got some time to wait
		        timerid = SetTimer(NULL, 0, t, NULL);
				have_message = GetMessage(&fl_msg, NULL, 0, 0);
				KillTimer(NULL, timerid);
				if(fl_msg.message == WM_TIMER) have_message = 0; // TIMEOUT!
			}
        }
    } else {
        have_message = GetMessage(&fl_msg, NULL, 0, 0);
    }

    fl_lock_function();

	if(!have_message) {
		// No messages in given time (if not infinite),
		// Return 0 to notify that timeout exceed.
		return 0;
	}

    // Execute the message we got, and all other pending messages:
    while (have_message)
    {
        if (fl_msg.message == WM_USER)
        {
            // This is used by Fl::awake() and by WndProc() in an attempt
            // to get Fl::wait() to return. That does not always work
            // unfortunately, as Windoze calls WndProc directly sometimes.
            // If that happens it gives up and calls Fl::flush()
            if (fl_msg.wParam) thread_message_ = (void*)fl_msg.wParam;
        }
        else
        {
            TranslateMessage(&fl_msg);
            DispatchMessage(&fl_msg);
        }
        have_message = PeekMessage(&fl_msg, NULL, 0, 0, PM_REMOVE);
		if(fl_msg.hwnd && !fl_find(fl_msg.hwnd)) {
			// This is not for us, send it back and return immediately!
			// Only case I have seen this happend is DND operations, 
			// more specific IDropTarger::DragEnter
			SendMessage(fl_msg.hwnd, fl_msg.message, fl_msg.wParam, fl_msg.lParam);
			break;
		}		
    }

    // Return 1, since there's some events we have handled.
    return 1;
}


// fl_ready() is just like fl_wait(0.0) except no callbacks are done:
static inline int fl_ready()
{
    if (PeekMessage(&fl_msg, NULL, 0, 0, PM_NOREMOVE)) return 1;
#ifdef USE_ASYNC_SELECT
    return 0;
#else
    timeval t;
    t.tv_sec = 0;
    t.tv_usec = 0;
    fd_set fdt[3];
    fdt[0] = fdsets[0];
    fdt[1] = fdsets[1];
    fdt[2] = fdsets[2];
    return ::select(0,&fdt[0],&fdt[1],&fdt[2],&t);
#endif                       // USE_ASYNC_SELECT
}


////////////////////////////////////////////////////////////////

static bool reload_info = true;

const Fl_Screen_Info& Fl::info()
{
    static Fl_Screen_Info info;
    if (reload_info)
    {
        reload_info = false;

        RECT r;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
        info.x = r.left;
        info.y = r.top;
        info.w = r.right - r.left;
        info.h = r.bottom - r.top;

        DEVMODE mode;
        EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode);
        info.width = mode.dmPelsWidth;
        info.height = mode.dmPelsHeight;
        info.depth = mode.dmBitsPerPel;

        HDC screen = GetDC(0);
        info.width_mm = GetDeviceCaps(screen, HORZSIZE);
        info.height_mm = GetDeviceCaps(screen, VERTSIZE);
        //info.dpi_x = GetDeviceCaps(screen, LOGPIXELSX);
        //info.dpi_y = GetDeviceCaps(screen, LOGPIXELSY);
    }
    return info;
}


void Fl::get_mouse(int &x, int &y)
{
    POINT p;
    GetCursorPos(&p);
    x = p.x;
    y = p.y;
}


////////////////////////////////////////////////////////////////
// code used for selections:

char *fl_selection_buffer[2];
int fl_selection_length[2];
int fl_selection_buffer_length[2];
char fl_i_own_selection[2];
UINT fl_codepage = 0;
static char *buf = NULL;
static int buf_len = 0;
static unsigned short *wbuf = NULL;
char *fl_utf82locale(const char *s, UINT codepage = 0)
{
	if (!s) return "";
	int len, l = 0;
	len = strlen(s);
	if (buf_len < len * 2 + 1) {
		buf_len = len * 2 + 1;
		buf = (char*) realloc(buf, buf_len);
		wbuf = (unsigned short*) realloc(wbuf, buf_len * sizeof(short));
	}
	if (codepage < 1) codepage = fl_codepage;
	l = fl_utf2unicode((const unsigned char *)s, len, wbuf);
	buf[l] = 0;
	l = WideCharToMultiByte(codepage, 0, (WCHAR*)wbuf, l, buf, 
		buf_len, NULL, NULL);
	if (l < 0) l = 0;
	buf[l] = 0;
	return buf;	
}

char *fl_locale2utf8(const char *s, UINT codepage = 0)
{
	if (!s) return "";
	int len, l = 0;
	len = strlen(s);
	if (buf_len < len * 5 + 1) {
		buf_len = len * 5 + 1;
		buf = (char*) realloc(buf, buf_len);
		wbuf = (unsigned short*) realloc(wbuf, buf_len * sizeof(short));
	}
	if (codepage < 1) codepage = fl_codepage;
	buf[l] = 0;
	
	l = MultiByteToWideChar(codepage, 0, s, len, (WCHAR*)wbuf, buf_len);
	if (l < 0) l = 0;
	wbuf[l] = 0;
	l = fl_unicode2utf(wbuf, l, buf);
	buf[l] = 0;
	return buf;	
}

int fl_atol(TCHAR *buf)
{
#ifdef UNICODE
	CHAR strTmp[256];
    int len = wcslen(buf);
    if(len>sizeof(strTmp)) len=sizeof(strTmp);
	len = wcstombs(strTmp, (const wchar_t *)buf, len);
    if(len < 0) return 0;
    strTmp[len] = '\0';
	return strtol(strTmp, NULL, 10);
#else
	return atoi(buf);
#endif
}

UINT fl_get_lcid_codepage(LCID id)
{
	TCHAR buf[8];
	buf[GetLocaleInfo(id, LOCALE_IDEFAULTANSICODEPAGE, buf, 8)] = 0;
	
	return fl_atol(buf);
}

// call this when you create a selection:
void Fl::copy(const char *stuff, int len, bool clipboard) 
{
	if (!stuff || len<0) return;
	if (len+1 > fl_selection_buffer_length[clipboard]) {
		delete[] fl_selection_buffer[clipboard];
		fl_selection_buffer[clipboard] = new char[len+100];
		fl_selection_buffer_length[clipboard] = len+100;
	}
	memcpy(fl_selection_buffer[clipboard], stuff, len);
	fl_selection_buffer[clipboard][len] = 0; // needed for direct paste
	fl_selection_length[clipboard] = len;
	if (clipboard) {
		// set up for "delayed rendering":
		if (OpenClipboard(fl_xid(Fl::first_window()))) {
			EmptyClipboard();
			/*if (fl_is_nt4()) {
				SetClipboardData(CF_UNICODETEXT, NULL);
			} else */{
				SetClipboardData(CF_TEXT, NULL);
			}
			CloseClipboard();
		}
		fl_i_own_selection[clipboard] = 1;
	}
}

// Call this when a "paste" operation happens:
void Fl::paste(Fl_Widget &receiver, bool clipboard) 
{
	static char *selection_buffer=0;
	if (!clipboard || fl_i_own_selection[clipboard]) {
		// We already have it, do it quickly without window server.
		// Notice that the text is clobbered if set_selection is
		// called in response to FL_PASTE!
		Fl::e_text = fl_selection_buffer[clipboard];
		Fl::e_length = fl_selection_length[clipboard];
		receiver.handle(FL_PASTE);
	} else {
		if (!OpenClipboard(NULL)) return;
		HANDLE hh = GetClipboardData(CF_LOCALE);
		UINT *i = (UINT*)GlobalLock(hh);
		UINT id = *i;
		GlobalUnlock(hh);
		HANDLE h;
		/*if (fl_is_nt4()) {
			h = GetClipboardData(CF_UNICODETEXT);
		} else */{
			h = GetClipboardData(CF_TEXT);
		}
		if (h) {
			void *g = GlobalLock(h);
			if (!g) {
				CloseClipboard();
				return;
			}	
			if (fl_is_nt4()) {
				int l = wcslen((wchar_t*)g);
				if(selection_buffer) free((char*)selection_buffer);
				selection_buffer = (char*) malloc(l * 5 + 1);
				selection_buffer[fl_unicode2utf((unsigned short *)g, l, selection_buffer)] = 0;
				Fl::e_text = selection_buffer;
			} else {	  
				Fl::e_text = fl_locale2utf8((char *)g, fl_get_lcid_codepage(id));
			}
			LPSTR a,b;
			a = b = Fl::e_text;
			while (*a) { // strip the CRLF pairs ($%$#@^)
				if (*a == '\r' && a[1] == '\n') a++;
				else *b++ = *a++;
			}
			*b = 0;
			Fl::e_length = b - Fl::e_text;
			receiver.handle(FL_PASTE);
			GlobalUnlock(h);
		}
		CloseClipboard();
	}
}


// Communicating data to Win32 requires it to be in "global memory", this
// copies the given selection to such a block and returns it. It appears
// this block is usually handed to Windows and Windows deletes it.
HANDLE fl_global_selection(int clipboard)
{
	HANDLE h;
    /*if (fl_is_nt4()) {
		int l = fl_utf_nb_char((unsigned char*)fl_selection_buffer[1], fl_selection_length[1]);	
		h = GlobalAlloc(GHND, (l+1) * sizeof(short));
        if (h) {
			unsigned short *g = (unsigned short*) GlobalLock(h);
			fl_utf2unicode((unsigned char *)fl_selection_buffer[1], fl_selection_length[1], g);
			g[l] = 0; 
			GlobalUnlock(h);
			SetClipboardData(CF_UNICODETEXT, h);
        }
	} else */{
		h = GlobalAlloc(GHND, fl_selection_length[1]+1);
		if (h) {
			LPSTR p = (LPSTR)GlobalLock(h);
			fl_selection_buffer[1][fl_selection_length[1]] = 0;	
			char *s = fl_utf82locale(fl_selection_buffer[1]);
			memcpy(p, s, strlen(s));
			p[fl_selection_length[1]] = 0;
			GlobalUnlock(h);
			SetClipboardData(CF_TEXT, h);
		}
    }
    return h;
}

bool fl_is_ime = false;
void fl_get_codepage()
{
	HKL hkl = GetKeyboardLayout(0);
	TCHAR ld[8];
	
	GetLocaleInfo(LOWORD(hkl), LOCALE_IDEFAULTANSICODEPAGE, ld, 6);
	DWORD ccp = fl_atol(ld);
	fl_is_ime = false;
	
	fl_codepage = ccp;
	if (fl_aimm) {
		fl_aimm->GetCodePageA(GetKeyboardLayout(0), &fl_codepage);
	} else if (ImmIsIME(hkl)) {
		fl_is_ime = true;
	}
}

////////////////////////////////////////////////////////////////

// Drag-n-drop requires GCC 3.x or a non-GNU compiler...
#if !defined(__GNUC__) || __GNUC__ >= 3

// I believe this was written by Matthias Melcher, correct?

#include <ole2.h>
#include <ShellApi.h>

static Fl_Window *fl_dnd_target_window = 0;

/**
 * subclass the IDropTarget to receive data from DnD operations
 */
class FLDropTarget : public IDropTarget
{
    DWORD m_cRefCount;
    DWORD lastEffect;
    int px, py;
    public:
                                 // initialize
        FLDropTarget() : m_cRefCount(0)
        {
        }
        HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, LPVOID *ppvObject )
        {
            if (IID_IUnknown==riid || IID_IDropTarget==riid)
            {
                *ppvObject=this;
                ((LPUNKNOWN)*ppvObject)->AddRef();
                return S_OK;
            }
            *ppvObject = NULL;
            return E_NOINTERFACE;
        }
        ULONG STDMETHODCALLTYPE AddRef() { return ++m_cRefCount; }
        ULONG STDMETHODCALLTYPE Release()
        {
            long nTemp;
            nTemp = --m_cRefCount;
            if(nTemp==0)
                delete this;
            return nTemp;
        }
        HRESULT STDMETHODCALLTYPE DragEnter( IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
        {
            if( !pDataObj ) return E_INVALIDARG;
            // set e_modifiers here from grfKeyState, set e_x and e_root_x
            // check if FLTK handles this drag and return if it can't (i.e. BMP drag without filename)
            POINT ppt;
            Fl::e_x_root = ppt.x = pt.x;
            Fl::e_y_root = ppt.y = pt.y;
            HWND hWnd = WindowFromPoint( ppt );
            Fl_Window *target = fl_find( hWnd );
            if (target)
            {
                Fl::e_x = Fl::e_x_root-target->x();
                Fl::e_y = Fl::e_y_root-target->y();
            }
            fl_dnd_target_window = target;
            px = pt.x; py = pt.y;
            // FLTK has no mechanism yet for the different drop effects, so we allow move and copy
            if ( target && Fl::handle( FL_DND_ENTER, target ) )
                                 //|DROPEFFECT_LINK;
                *pdwEffect = DROPEFFECT_MOVE|DROPEFFECT_COPY;
            else
                *pdwEffect = DROPEFFECT_NONE;
            lastEffect = *pdwEffect;
            Fl::flush();         // get the display to update for local drags
            return S_OK;
        }
        HRESULT STDMETHODCALLTYPE DragOver( DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
        {
            if ( px==pt.x && py==pt.y )
            {
                *pdwEffect = lastEffect;
                return S_OK;
            }
            if ( !fl_dnd_target_window )
            {
                *pdwEffect = lastEffect = DROPEFFECT_NONE;
                return S_OK;
            }
            // set e_modifiers here from grfKeyState, set e_x and e_root_x
            Fl::e_x_root = pt.x;
            Fl::e_y_root = pt.y;
            if (fl_dnd_target_window)
            {
                Fl::e_x = Fl::e_x_root-fl_dnd_target_window->x();
                Fl::e_y = Fl::e_y_root-fl_dnd_target_window->y();
            }
            // Fl_Group will change DND_DRAG into DND_ENTER and DND_LEAVE if needed
            if ( Fl::handle( FL_DND_DRAG, fl_dnd_target_window ) )
                                 //|DROPEFFECT_LINK;
                *pdwEffect = DROPEFFECT_MOVE|DROPEFFECT_COPY;
            else
                *pdwEffect = DROPEFFECT_NONE;
            px = pt.x; py = pt.y;
            lastEffect = *pdwEffect;
            Fl::flush();         // get the display to update for local drags
            return S_OK;
        }
        HRESULT STDMETHODCALLTYPE DragLeave()
        {
            if ( fl_dnd_target_window )
            {
                Fl::handle( FL_DND_LEAVE, fl_dnd_target_window );
                Fl::flush();     // get the display to update for local drags
                fl_dnd_target_window = 0;
            }
            return S_OK;
        }
        HRESULT STDMETHODCALLTYPE Drop( IDataObject *data, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
        {
            if ( !fl_dnd_target_window )
                return S_OK;
            Fl_Window *target_window = fl_dnd_target_window;
            fl_dnd_target_window = 0;
            Fl::e_x_root = pt.x;
            Fl::e_y_root = pt.y;
            if (target_window)
            {
                Fl::e_x = Fl::e_x_root-target_window->x();
                Fl::e_y = Fl::e_y_root-target_window->y();
            }
            // tell FLTK that the user released an object on this widget
            if ( !Fl::handle( FL_DND_RELEASE, target_window ) )
                return S_OK;

            Fl_Widget* target = Fl::belowmouse();
            if (!target) return S_OK;
            Fl_Widget *w = target;
            while (w->parent()) w = w->window();
            HWND hwnd = fl_xid( (Fl_Window*)w );

		    FORMATETC fmt;
			
            STGMEDIUM medium;
            fmt.tymed = TYMED_HGLOBAL;
            fmt.dwAspect = DVASPECT_CONTENT;
            fmt.lindex = -1;
            fmt.cfFormat = CF_TEXT;
			fmt.ptd = 0;
            // if it is ASCII text, send an FL_PASTE with that text
            if ( data->GetData( &fmt, &medium )==S_OK )
            {
                void *stuff = GlobalLock( medium.hGlobal );
                //long len = GlobalSize( medium.hGlobal );
                                 // min(strlen, len)
                Fl::e_length = strlen( (char*)stuff );
                Fl::e_text = (char*)stuff;
                                 // e_text will be invalid after this call
                target->handle(FL_PASTE);
                GlobalUnlock( medium.hGlobal );
                ReleaseStgMedium( &medium );
                SetForegroundWindow( hwnd );
                return S_OK;
            }
            fmt.tymed = TYMED_HGLOBAL;
            fmt.dwAspect = DVASPECT_CONTENT;
            fmt.lindex = -1;
            fmt.cfFormat = CF_HDROP;
            // if it is a pathname list, send an FL_PASTE with a \n seperated list of filepaths
            if ( data->GetData( &fmt, &medium )==S_OK )
            {
                HDROP hdrop = (HDROP)medium.hGlobal;
                int i, n, nn = 0, nf = DragQueryFile( hdrop, (UINT)-1, 0, 0 );
                for ( i=0; i<nf; i++ ) nn += DragQueryFile( hdrop, i, 0, 0 );
                nn += nf;
                Fl::e_length = nn-1;
                WCHAR *dst = (WCHAR*)malloc((nn+1)*sizeof(WCHAR));
                for ( i=0; i<nf; i++ )
                {					
                    n = DragQueryFileW( hdrop, i, dst, nn );
                    dst += n;
                    if ( i<nf-1 ) {
						uchar tmp[2] = { '\n', '\0' };
						fl_utf2ucs(tmp, 1, (unsigned int*)dst);
						dst++;
					}
                }
                *dst = 0;
				Fl::e_text = (char*)malloc((nn+1)*4);
				Fl::e_text[fl_unicode2utf((unsigned short*)dst, nn, Fl::e_text)] = '\0';
				
                target->handle(FL_PASTE);
                free( Fl::e_text );
                ReleaseStgMedium( &medium );
                SetForegroundWindow( hwnd );
                return S_OK;
            }
            return S_OK;
        }
} flDropTarget;
#endif

////////////////////////////////////////////////////////////////

#ifndef TME_LEAVE
#define TME_LEAVE 2
#endif

typedef struct _tagTRACKMOUSEEVENT
{
    DWORD cbSize;
    DWORD dwFlags;
    HWND  hwndTrack;
    DWORD dwHoverTime;
} _TRACKMOUSEEVENT, *_LPTRACKMOUSEEVENT;

/* This code lifted from SDL, also under the LGPL - CET

   Special code to handle mouse leave events - this sucks...
   http://support.microsoft.com/support/kb/articles/q183/1/07.asp

   TrackMouseEvent() is only available on Win98 and WinNT.
   _TrackMouseEvent() is available on Win95, but isn't yet in the mingw32
   development environment, and only works on systems that have had IE 3.0
   or newer installed on them (which is not the case with the base Win95).
   Therefore, we implement our own version of _TrackMouseEvent() which
   uses our own implementation if TrackMouseEvent() is not available.
*/
static BOOL (WINAPI *_TrackMouseEvent)(_TRACKMOUSEEVENT *ptme) = NULL;

static VOID CALLBACK
TrackMouseTimerProc(HWND hWnd, UINT, UINT idEvent, DWORD)
{
    RECT rect;
    POINT pt;

    GetClientRect(hWnd, &rect);
    MapWindowPoints(hWnd, NULL, (LPPOINT)&rect, 2);
    GetCursorPos(&pt);
    if (!PtInRect(&rect, pt) || (WindowFromPoint(pt) != hWnd))
    {
        if ( !KillTimer(hWnd, idEvent) )
        {
            /* Error killing the timer! */
        }
        PostMessage(hWnd, WM_MOUSELEAVE, 0, 0);
    }
}


static BOOL WINAPI
WIN_TrackMouseEvent(_TRACKMOUSEEVENT *ptme)
{
    if (ptme->dwFlags == TME_LEAVE)
        return SetTimer(ptme->hwndTrack, ptme->dwFlags, 100,
            (TIMERPROC)TrackMouseTimerProc);
    return FALSE;
}


static _TRACKMOUSEEVENT mouseevent =
{
    sizeof(_TRACKMOUSEEVENT),
    TME_LEAVE,
	0, 0
};

////////////////////////////////////////////////////////////////

static bool mouse_event(Fl_Window *window, int what, int button,
WPARAM wParam, LPARAM lParam)
{
    xmousewin = window;
    if (!window) return false;
    static int px, py, pmx, pmy;
    POINT pt;
    Fl::e_x = pt.x = (signed short)LOWORD(lParam);
    Fl::e_y = pt.y = (signed short)HIWORD(lParam);
    ClientToScreen(fl_xid(window), &pt);
    Fl::e_x_root = pt.x;
    Fl::e_y_root = pt.y;
    //xmousewin = window;
    while (window->parent())
    {
        Fl::e_x += window->x();
        Fl::e_y += window->y();
        window = window->window();
    }

                                 // keep shift key states
    ulong state = Fl::e_state & 0xff0000;
    #if 0
    // mouse event reports some shift flags, perhaps save them?
    if (wParam & MK_SHIFT) state |= FL_SHIFT;
    if (wParam & MK_CONTROL) state |= FL_CTRL;
    #endif
    if (wParam & MK_LBUTTON) state |= FL_BUTTON1;
    if (wParam & MK_MBUTTON) state |= FL_BUTTON2;
    if (wParam & MK_RBUTTON) state |= FL_BUTTON3;
    Fl::e_state = state;

    switch (what)
    {
        case 1:                  // double-click
            // This is not detecting triple-clicks, does anybody know how to fix?
            if (Fl::e_is_click) {Fl::e_clicks++; goto J1;}
        case 0:                  // single-click
            Fl::e_clicks = 0;
            J1:
            if (!Fl::grab_) SetCapture(fl_xid(window));
            Fl::e_keysym = FL_Button(button);
            Fl::e_is_click = 1;
            px = pmx = Fl::e_x_root; py = pmy = Fl::e_y_root;
            if (Fl::handle(FL_PUSH, window)) return true;
            // If modal is on and 0 is returned, we should turn off modal and
            // pass the event on to other widgets. The pass-on part is nyi!
            if (Fl::grab_)       /* NYI */
            {
                Fl::exit_modal();
            }
            return false;

        case 2:                  // release:
            // WAS: this should turn off Fl::e_is_click if more than .2 second passed
            // since the push event!
            if (!Fl::grab_) ReleaseCapture();
            Fl::e_keysym = FL_Button(button);
            return Fl::handle(FL_RELEASE,window);

        case 3:                  // move:
        default:                 // avoid compiler warning
            // MSWindows produces extra events even if mouse does not move, ignore em:
            if (Fl::e_x_root == pmx && Fl::e_y_root == pmy) return true;
            pmx = Fl::e_x_root; pmy = Fl::e_y_root;
            if (abs(Fl::e_x_root-px)>5 || abs(Fl::e_y_root-py)>5) Fl::e_is_click = 0;

            // look for mouse leave events
            if (!_TrackMouseEvent)
            {
                /* Get the version of TrackMouseEvent() we use */
                HMODULE handle = GetModuleHandle(TEXT("USER32.DLL"));
                if (handle) _TrackMouseEvent =
                        (BOOL(WINAPI*)(_TRACKMOUSEEVENT*))GetProcAddress(handle, "TrackMouseEvent");
                if (!_TrackMouseEvent) _TrackMouseEvent = WIN_TrackMouseEvent;
            }
            mouseevent.hwndTrack = fl_xid(window);
            _TrackMouseEvent(&mouseevent);

            return Fl::handle(FL_MOVE,window);
    }
}


// convert a MSWindows VK_x to an Fltk (X) Keysym:
// See also the inverse converter in Fl_get_key_win32.C
// This table is in numeric order by VK:
static const struct {
    unsigned short vk, fltk, extended;
} vktab[] =
{
    {VK_BACK, FL_BackSpace, 0},
    {VK_TAB,  FL_Tab, 0},
    {VK_CLEAR,    FL_KP('5'), FL_Clear},
    {VK_RETURN,   FL_Enter,   FL_KP_Enter},
    {VK_SHIFT,    FL_Shift_L, FL_Shift_R},
    {VK_CONTROL,  FL_Control_L,   FL_Control_R},
    {VK_MENU, FL_Alt_L,   FL_Alt_R},
    {VK_PAUSE,    FL_Pause, 0},
    {VK_CAPITAL,  FL_Caps_Lock, 0},
    {VK_ESCAPE,   FL_Escape, 0},
    {VK_SPACE,    ' ', 0},
    {VK_PRIOR,    FL_KP('9'), FL_Page_Up},
    {VK_NEXT, FL_KP('3'), FL_Page_Down},
    {VK_END,  FL_KP('1'), FL_End},
    {VK_HOME, FL_KP('7'), FL_Home},
    {VK_LEFT, FL_KP('4'), FL_Left},
    {VK_UP,   FL_KP('8'), FL_Up},
    {VK_RIGHT,    FL_KP('6'), FL_Right},
    {VK_DOWN, FL_KP('2'), FL_Down},
    {VK_SNAPSHOT, FL_Print, 0}, // does not work on NT
    {VK_INSERT,   FL_KP('0'), FL_Insert},
    {VK_DELETE,   FL_KP('.'), FL_Delete},
    {VK_LWIN, FL_Win_L, 0},
    {VK_RWIN, FL_Win_R, 0},
    {VK_APPS, FL_Menu, 0},
    {VK_MULTIPLY, FL_KP('*'), 0},
    {VK_ADD,  FL_KP('+'), 0},
    {VK_SUBTRACT, FL_KP('-'), 0},
    {VK_DECIMAL,  FL_KP('.'), 0},
    {VK_DIVIDE,   FL_KP('/'), 0},
    {VK_NUMLOCK,  FL_Num_Lock, 0},
    {VK_SCROLL,   FL_Scroll_Lock, 0},
    {0xba,    ';', 0},
    {0xbb,    '=', 0},
    {0xbc,    ',', 0},
    {0xbd,    '-', 0},
    {0xbe,    '.', 0},
    {0xbf,    '/', 0},
    {0xc0,    '`', 0},
    {0xdb,    '[', 0},
    {0xdc,    '\\', 0},
    {0xdd,    ']', 0},
    {0xde,    '\'', 0}
};
static int ms2fltk(int vk, int extended)
{
    static unsigned short vklut[256];
    static unsigned short extendedlut[256];
    if (!vklut[1])               // init the table
    {
        unsigned int i;
        for (i = 0; i < 256; i++) vklut[i] = tolower(i);
        for (i=VK_F1; i<=VK_F16; i++) vklut[i] = i+(FL_F(0)-(VK_F1-1));
        for (i=VK_NUMPAD0; i<=VK_NUMPAD9; i++) vklut[i] = i+(FL_KP('0')-VK_NUMPAD0);
        for (i = 0; i < sizeof(vktab)/sizeof(*vktab); i++)
        {
            vklut[vktab[i].vk] = vktab[i].fltk;
            extendedlut[vktab[i].vk] = vktab[i].extended;
        }
        for (i = 0; i < 256; i++) if (!extendedlut[i]) extendedlut[i] = vklut[i];
    }
    return extended ? extendedlut[vk] : vklut[vk];
}


#if USE_COLORMAP
                                 // in fl_color_win32.C
extern HPALETTE fl_select_palette(void);
#endif

static Fl_Window* resize_from_system;
//  static Fl_Window* in_wm_paint;
//  static PAINTSTRUCT paint;

#define MakeWaitReturn() PostMessage(hWnd, WM_USER, 0, 0)

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Copy the message to fl_msg so add_handler code can see it, it is
    // already there if this is called by DispatchMessage, but not if
    // Windows calls this directly.
    fl_msg.hwnd = hWnd;
    fl_msg.message = uMsg;
    fl_msg.wParam = wParam;
    fl_msg.lParam = lParam;
    //fl_msg.time = ???
    //fl_msg.pt = ???
    //fl_msg.lPrivate = ???

	static unsigned short wbuf[200];
	static long wlen = 0;
    Fl_Window *window = fl_find(hWnd);

    switch (uMsg)
    {

        case WM_SYNCPAINT :
        case WM_NCPAINT :
        case WM_ERASEBKGND :
            // Andreas Weitl - WM_SYNCPAINT needs to be passed to DefWindowProc
            // so that Windows can generate the proper paint messages...
            // Similarly, WM_NCPAINT and WM_ERASEBKGND need this, too...
            break;

        case WM_CAPTURECHANGED:
            if (Fl::grab_)
            {
                Fl::exit_modal();
                // Make Fl::wait() return so that the function that called modal()
                // can continue executing:
                MakeWaitReturn();
            }
            break;

        #if 0
        case WM_NCACTIVATE:
            // This prevents the title bar highlighting from turning off while a
            // modal window is running. This is certainly necessary for menus
            // but they do the grab which seems to make this not happen.
            if (Fl::modal_) wParam = 1;
            break;
        #endif

        case WM_QUIT:            // this should not happen?
            Fl::fatal("WM_QUIT message");

        case WM_CLOSE:           // user clicked close box
            if (!window) break;
            //if (!Fl::modal_ || window == Fl::modal_)
            if (!Fl::grab() && !(Fl::modal() && window != Fl::modal()))
                window->do_callback();
            return 1;

        case WM_PAINT:
        {
            if (!window) break;
            Fl_X *i = Fl_X::i(window);
            i->wait_for_expose = false;
            #if 1
            // Merge the region into whatever is accumulated by fltk. I do this
            // by invalidating the fltk region and reading the resulting region
            // back:
            if (i->region) InvalidateRgn(hWnd, i->region, FALSE);
            else i->region = CreateRectRgn(0,0,0,0);
            GetUpdateRgn(hWnd, i->region, 0);
            // This convinces MSWindows we have painted whatever they wanted
            // us to paint, and stops it from sending WM_PAINT messages:
            ValidateRgn(hWnd, i->region);
            // This makes Fl::flush() do something:
            Fl::damage(FL_DAMAGE_EXPOSE);
            // Originally it called Fl::flush() directly here, but it appears to
            // be better to get Fl::wait() to return by posting a message. This
            // merges the damage together and waits for idle. Windows appears to
            // sometimes send WM_PAINT while we are painting the previous contents
            // and this minimizes the chances that will mess it up:
            MakeWaitReturn();
            //Fl::flush();
            #else
            // This version was an attempt to fool fltk into doing what Windows
            // wants, which is to draw immediately in response to the WM_PAINT
            // event. This did not work as well as the above simpler version,
            // and also appeared to be no faster.
            // Since we can't merge or otherwise change the clip region, we
            // must first get rid of any other damage before doing the drawing:
            if (window->damage() || i->region)
            {
                window->flush();
                window->set_damage(0);
                if (i->region) {XDestroyRegion(i->region); i->region = 0;}
            }
            // Now get the damage region, so fltk has some idea what area it
            // needs to draw:
            i->region = CreateRectRgn(0,0,0,0);
            GetUpdateRgn(hWnd, i->region, 0);
            // Now draw it using Windows' gc and clip region:
            BeginPaint(i->xid, &paint);
            in_wm_paint = window;// makes it use the hdc from the paint struct
            window->flush();
            window->set_damage(0);
            if (i->region) {XDestroyRegion(i->region); i->region = 0;}
            EndPaint(i->xid, &paint);
            in_wm_paint = 0;
            #endif
        } break;

        case WM_LBUTTONDOWN:  mouse_event(window, 0, 1, wParam, lParam); return 0;
        case WM_LBUTTONDBLCLK:mouse_event(window, 1, 1, wParam, lParam); return 0;
        case WM_LBUTTONUP:    mouse_event(window, 2, 1, wParam, lParam); return 0;
        case WM_MBUTTONDOWN:  mouse_event(window, 0, 2, wParam, lParam); return 0;
        case WM_MBUTTONDBLCLK:mouse_event(window, 1, 2, wParam, lParam); return 0;
        case WM_MBUTTONUP:    mouse_event(window, 2, 2, wParam, lParam); return 0;
        case WM_RBUTTONDOWN:  mouse_event(window, 0, 3, wParam, lParam); return 0;
        case WM_RBUTTONDBLCLK:mouse_event(window, 1, 3, wParam, lParam); return 0;
        case WM_RBUTTONUP:    mouse_event(window, 2, 3, wParam, lParam); return 0;

        case WM_MOUSEMOVE:
        #ifdef USE_TRACK_MOUSE
            if (Fl::belowmouse() != window)
            {
                TRACKMOUSEEVENT tme;
                tme.cbSize    = sizeof(TRACKMOUSEEVENT);
                tme.dwFlags   = TME_LEAVE;
                tme.hwndTrack = hWnd;
                _TrackMouseEvent(&tme);
            }
        #endif                   // USE_TRACK_MOUSE
            mouse_event(window, 3, 0, wParam, lParam);
            return 0;

        case WM_MOUSELEAVE:
            // In fltk2 we should only call Fl::handle(FL_LEAVE) if the mouse is
            // not pointing at a window belonging to the application. This seems
            // to work, probably because the enter event has already been done
            // and has changed xmousewin to some other window:
            if (window == xmousewin) {xmousewin = 0; Fl::handle(FL_LEAVE, window);}
            break;

        case WM_KILLFOCUS:
            window = 0;
        case WM_SETFOCUS:
            if (xfocus != window)
            {
                xfocus = window;
                fl_fix_focus();
                MakeWaitReturn();
            }
            break;

		case WM_INPUTLANGCHANGE:
			fl_get_codepage();
			break;
		case WM_IME_COMPOSITION:
			if (!fl_is_nt4() && lParam & GCS_RESULTCLAUSE) {
				HIMC himc = ImmGetContext(hWnd);
				wlen = ImmGetCompositionStringW(himc, GCS_RESULTSTR, wbuf, sizeof(wbuf)) / sizeof(short);
				if (wlen < 0) wlen = 0;
				wbuf[wlen] = 0;
				ImmReleaseContext(hWnd, himc);
			}
			break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            // save the keysym until we figure out the characters:
            Fl::e_keysym = ms2fltk(wParam,lParam&(1<<24));
            // See if TranslateMessage turned it into a WM_*CHAR message:
            if (PeekMessage(&fl_msg, hWnd, WM_CHAR, WM_SYSDEADCHAR, 1))
            {
                uMsg = fl_msg.message;
                wParam = fl_msg.wParam;
                lParam = fl_msg.lParam;
            }
            // fall through to the character case:
        case WM_DEADCHAR:
        case WM_SYSDEADCHAR:
        case WM_CHAR:
        case WM_SYSCHAR:
        {
			UINT cp = fl_codepage;
			static char buffer[1024];
			static unsigned char lead[4] = {0, 0, 0, 0};
			if (!fl_is_nt4() && uMsg == WM_CHAR) {
				if (!lead[0] && IsDBCSLeadByteEx(cp, (unsigned char)wParam)) 
				{
					lead[0] = (unsigned char)wParam;
					return 0;
				}
			}

            static int lastkeysym;
            // keep the mouse button state
            ulong state = Fl::e_state & 0xff000000;
            // if GetKeyState is expensive we might want to comment some of these out:
            if (GetKeyState(VK_SHIFT)&~1) state |= FL_SHIFT;
            if (GetKeyState(VK_CAPITAL)) state |= FL_CAPS_LOCK;
            if (GetKeyState(VK_CONTROL)&~1) state |= FL_CTRL;
            // Alt gets reported for the Alt-GR switch on foreign keyboards.
            // so we need to check the event as well to get it right:
            if ((lParam&(1<<29)) //same as GetKeyState(VK_MENU)
                && uMsg != WM_CHAR) state |= FL_ALT;
            if (GetKeyState(VK_NUMLOCK)) state |= FL_NUM_LOCK;
            if (GetKeyState(VK_LWIN)&~1 || GetKeyState(VK_RWIN)&~1)
            {
                // _WIN32 bug?  GetKeyState returns garbage if the user hit the
                // Windows key to pop up start menu.  Sigh.
                if ((GetAsyncKeyState(VK_LWIN)|GetAsyncKeyState(VK_RWIN))&~1)
                    state |= FL_WIN;
            }
            if (GetKeyState(VK_SCROLL)) state |= FL_SCROLL_LOCK;
            Fl::e_state = state;
            if (lParam & (1<<31))// key up events.
            {
                Fl::e_is_click = (Fl::e_keysym == lastkeysym);
                lastkeysym = 0;
                if (Fl::handle(FL_KEYUP, window)) return 0;
                break;
            }
            // if same as last key, increment repeat count:			
            if (lParam & (1<<30)) {
                Fl::e_clicks++;
                Fl::e_is_click = 0;
            } else {
                Fl::e_clicks = 0;
                Fl::e_is_click = 1;
            }
            lastkeysym = Fl::e_keysym;
            // translate to text:
			if (uMsg == WM_CHAR || uMsg == WM_SYSCHAR) {
				int i = 0;
				unsigned short ucs[10];
				int ulen = 0;
				int len;
				int l = 1;
				if (fl_is_nt4()) {
					unsigned short u = (unsigned short) wParam;
					Fl::e_length = fl_unicode2utf(&u, 1, buffer);
					buffer[Fl::e_length] = 0;
				} else if (!fl_is_ime) {
      				if (lead[0]) {
	 					lead[1] = (unsigned char) wParam;
	 					l = 2;
      				} else {
     					lead[0] = (unsigned char) wParam;
      				}
      				len = MultiByteToWideChar(fl_codepage, MB_PRECOMPOSED, (char*)lead, l, (wchar_t*)ucs, 10);
      				len = 1;
      				lead[0] = 0;
      				lead[1] = 0;
      				while (i < len) { 
        				int l = fl_ucs2utf(ucs[i], buffer + ulen);
        				if (l > 0) ulen += l;
        				i++;
      				}
      				buffer[ulen] = '\0';
      				Fl::e_length = ulen;
				} else {
					int l = fl_unicode2utf(wbuf, wlen, buffer);
					if (l < 0) l = 0;
					buffer[l] = 0;
      				Fl::e_length = l;
					wlen = 0;
				}
			} else if (Fl::e_keysym >= FL_KP(0) && Fl::e_keysym <= FL_KP_Last)
            {
                buffer[0] = Fl::e_keysym-FL_KP(0);
                Fl::e_length = 1;
            }
            else
            {
                buffer[0] = 0;
                Fl::e_length = 0;
            }
            Fl::e_text = buffer;
            // for (int i = lParam&0xff; i--;)
            if (window) while (window->parent()) window = window->window();
            if (Fl::handle(FL_KEY,window)) return 0;
            break;
        }

        case WM_MOUSEWHEEL:
        {
            static int delta = 0;// running total of all motion
            delta += (SHORT)(HIWORD(wParam));
            Fl::e_dy = delta / WHEEL_DELTA;
            if (Fl::e_dy) {
                delta -= Fl::e_dy * WHEEL_DELTA;
                Fl::handle(FL_MOUSEWHEEL, window);
            }
            return 0;
        }

        case WM_GETMINMAXINFO:
            if (window) Fl_X::i(window)->set_minmax((LPMINMAXINFO)lParam);
            break;

        case WM_SHOWWINDOW:
            if (!window) break;
            if (wParam) { // Map event            
				// ignore child windows                                 
                if (window->parent()) break;

                // figure out where OS really put window
                RECT wr; GetClientRect(fl_xid(window), &wr);
                POINT wul = { 0, 0 };
                ClientToScreen(fl_xid(window), &wul);

                // tell Fl_Window about it
                if (window->resize(wul.x, wul.y, wr.right, wr.bottom))
                    resize_from_system = window;

			} else { // Unmap event                        
                Fl_X::i(window)->wait_for_expose = true;
            }
            MakeWaitReturn();
            break;

        case WM_SIZE:
            if (window && !window->parent())
            {
                                 // iconize
                if (wParam == SIZE_MINIMIZED || wParam == SIZE_MAXHIDE)
                {
                    Fl_X::i(window)->wait_for_expose = true;
                }                // resize, deiconize
                else
                {
                    // supposedly a Paint event will come in turn off iconize indicator
                    if (window->resize(window->x(), window->y(),
                        LOWORD(lParam), HIWORD(lParam)))
                        resize_from_system = window;
                }
            }
            MakeWaitReturn();
            break;

        case WM_USER:
            // This will be called if MakeWaitReturn fails because Stoopid Windows
            // called the WndProc directly. Instead do the best we can, which is
            // to flush the display.
            // record the awake() argument:
            if (fl_msg.wParam) thread_message_ = (void*)fl_msg.wParam;
            Fl::flush();
            break;

        case WM_MOVE:
                                 // ignore child windows
            if (!window || window->parent()) break;
        #if 1
            if (window->resize((signed short)LOWORD(lParam),
                (signed short)HIWORD(lParam),
                window->w(), window->h()))
                resize_from_system = window;
            MakeWaitReturn();
        #else
            // Don't bother having dragging windows call resize or layout, just
            // set the coordinates directly. This should be faster but I can't
            // see too much difference. This should also be copied to X version.
            window->x((signed short)LOWORD(lParam));
            window->y((signed short)HIWORD(lParam));
        #endif
            break;

        case WM_SETCURSOR:
            if (window && LOWORD(lParam) == HTCLIENT)
            {
                while (window->parent()) window = window->window();
                SetCursor(Fl_X::i(window)->cursor);
                return 0;
            }
            break;

        #if USE_COLORMAP
        case WM_QUERYNEWPALETTE :
            window->make_current();
            if (fl_select_palette()) InvalidateRect(hWnd, NULL, FALSE);
            break;

        case WM_PALETTECHANGED:
            if ((HWND)wParam != hWnd)
            {
                window->make_current();
                if (fl_select_palette()) UpdateColors(fl_gc);
            }
            break;

        #if 0
            // This seems to be called directly by CreateWindowEx so I can't
            // have stored the windowid yet and thus cannot find the Fl_Window!
        case WM_CREATE :
            window->make_current();
            fl_select_palette();
            break;
        #endif
        #endif

        case WM_DISPLAYCHANGE:
        case WM_SETTINGCHANGE:
            reload_info = true;
			Fl::read_defaults();
			// Need to reload also system image format information
			// And invalidate all images..
        case WM_SYSCOLORCHANGE:			
            Fl_Style::reload_theme();
            break;

        case WM_DESTROYCLIPBOARD:
			fl_i_own_selection[1] = 0;
			return 1;

        case WM_RENDERALLFORMATS:
			fl_i_own_selection[1] = 0;            
            // Windoze seems unhappy unless I do these two steps. Documentation
            // seems to vary on whether opening the clipboard is necessary or
            // is in fact wrong:
            CloseClipboard();
            OpenClipboard(NULL);
            // fall through...
        case WM_RENDERFORMAT:
            SetClipboardData(CF_TEXT, fl_global_selection(1));
            // Windoze also seems unhappy if I don't do this. Documentation very
            // unclear on what is correct:
            if (fl_msg.message == WM_RENDERALLFORMATS) CloseClipboard();
            return 1;

        default:
            if (Fl::handle(0,0)) return 0;
            break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


////////////////////////////////////////////////////////////////
// Sets the 4 return values to the thickness of the window border, so
// that window positions can be adjusted to match the X method of
// placing the contents at an absolute position.  The return value
// is also the value to put in the window style.

int Fl_X::borders(const Fl_Window* window, int& dx,int& dy,int& dw,int& dh)
{
    if (!window->border() || window->override() || window->parent())
    {
        dx = dy = dw = dh = 0;
        return WS_POPUP;
    }                            // resizable
    else if (window->m_maxw != window->m_minw || window->m_maxh != window->m_minh)
    {
        dx = GetSystemMetrics(SM_CXSIZEFRAME);
        dw = 2*dx;
        int bt = GetSystemMetrics(SM_CYCAPTION);
        int by = GetSystemMetrics(SM_CYSIZEFRAME);
        dy = bt+by;
        dh = bt+2*by;
        return WS_THICKFRAME | WS_MAXIMIZEBOX | WS_CAPTION;
    }
    else
    {
        dx = GetSystemMetrics(SM_CXFIXEDFRAME);
        dw = 2*dx;
        int bt = GetSystemMetrics(SM_CYCAPTION);
        int by = GetSystemMetrics(SM_CYFIXEDFRAME);
        dy = bt+by;
        dh = bt+2*by;
        return WS_DLGFRAME | WS_CAPTION;
    }
}


////////////////////////////////////////////////////////////////

void Fl_Window::layout()
{
    UINT flags;
    if (layout_damage() & FL_LAYOUT_WH)
        flags = SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE;
    else if (layout_damage() & FL_LAYOUT_XY)
        flags = SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE;
    else
        flags = 0;
    Fl_Group::layout();
    if (this == resize_from_system)
    {
        resize_from_system = 0;
    }
    else if (i && flags)
    {
        int real_x = this->x(); int real_y = this->y();
        // this should not treat x,y differently from any other widget
        for (Fl_Widget* p = parent(); p && !p->is_window(); p = p->parent())
        {
            real_x += p->x(); real_y += p->y();
        }
        int dx, dy, dw, dh; Fl_X::borders(this, dx, dy, dw, dh);
        SetWindowPos(i->xid, 0, real_x-dx, real_y-dy, w()+dw, h()+dh, flags);
                                 /*i->wait_for_expose = true;*/
        if (!(flags & SWP_NOSIZE))
        {
            redraw();
        }
    }
}


////////////////////////////////////////////////////////////////
// Innards of Fl_Window::create():

// set by show_inside()
const Fl_Window* fl_mdi_window = 0;
HCURSOR fl_default_cursor;

void Fl_X::create(Fl_Window* window)
{
	static TCHAR class_name[1024];
    static bool registered = false;
	int len;

    if (!registered)
    {
        registered = true;

#ifdef UNICODE
		len = fl_utf2unicode((const uchar*)Fl_Window::xclass().c_str(), Fl_Window::xclass().length(), (unsigned short*)class_name);
#else
		len = strlen(Fl_Window::xclass());
		strncpy(class_name, Fl_Window::xclass(), len);
#endif
		class_name[len] = 0;

		if (!fl_default_cursor) fl_default_cursor = LoadCursor(NULL, IDC_ARROW);
		static WNDCLASSEX wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
		wc.lpfnWndProc = (WNDPROC)WndProc;
		wc.cbClsExtra = wc.cbWndExtra = 0;
		wc.hInstance = fl_display;
		if(!window->icon()) window->icon((void *)LoadIcon(NULL, IDI_APPLICATION));
		wc.hIcon = wc.hIconSm = (HICON)window->icon();			
		wc.hCursor = fl_default_cursor;
		//uchar r,g,b; fl_get_color(FL_GRAY,r,g,b);
		//wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(r,g,b));
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = class_name;
		wc.cbSize = sizeof(WNDCLASSEX);
		RegisterClassEx(&wc);
	}

    HWND parent;
    DWORD style;
    DWORD styleEx;

    int xp = window->x();
    int yp = window->y();

    int dx, dy, dw, dh;

    if (window->parent())
    {
        for (Fl_Widget* p=window->parent(); p && !p->is_window(); p=p->parent())
        {
            xp += p->x(); yp += p->y();
        }
        style = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CHILD;
        styleEx = WS_EX_LEFT | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;
        parent = fl_xid(window->window());
        dx=dy=dw=dh=0;
    }
    else
    {
        style = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | borders(window, dx,dy,dw,dh);
        styleEx = WS_EX_LEFT | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;
        // we don't want an entry in the task list for menuwindows or tooltips!
        // This seems to have no effect on NT, maybe for Win2K?
        if (window->override())
        {
            styleEx |= WS_EX_TOOLWINDOW;
        }
        else if (!window->contains(Fl::modal()))
        {
            style |= WS_SYSMENU | WS_MINIMIZEBOX;
        }

        xp = window->x(); if (xp != FL_USEDEFAULT) xp -= dx;
        yp = window->y(); if (yp != FL_USEDEFAULT) yp -= dy;

        if (window->child_of() && window->child_of()->shown())
        {
            parent = window->child_of()->i->xid;
        }
        else if (fl_mdi_window)
        {
            parent = fl_mdi_window->i->xid;
        }
        else
        {
            parent = 0;
        }
    }

    Fl_X* x = new Fl_X;
	window->i = x;
    x->backbuffer.xid = 0;
    x->backbuffer.dc = 0;
    x->window = window; 	
    x->region = 0;
    x->cursor = fl_default_cursor;
    if (!fl_codepage) fl_get_codepage();
	
	/*if (fl_is_nt4()) {		
		WCHAR *lab = NULL;
		if(window->label()) {
			int l = fl_utf_nb_char((unsigned char*)window->label(), strlen(window->label()));
			lab = (WCHAR*)malloc((l + 1) * sizeof(WCHAR));
			fl_utf2unicode((unsigned char*)window->label(), l, (unsigned short*)lab);
			lab[l] = 0;			
		}
		x->xid = CreateWindowExW(
			styleEx,
			class_namew, lab, style,
			xp, yp, window->w()+dw, window->h()+dh,
			parent,
			NULL, // menu
			fl_display,
			NULL // creation parameters
		);
		if (lab) free(lab);
	} else 
	*/{
		TCHAR *label = NULL;
#ifdef UNICODE
		if(!window->label().empty()) {
			len = fl_utf_nb_char((unsigned char*)window->label().c_str(), window->label().length());
			label = (TCHAR*)malloc((len + 1) * sizeof(TCHAR));
			fl_utf2unicode((unsigned char*)window->label().c_str(), len, (unsigned short*)label);
			label[len] = 0;			
		}
#else
		label = fl_utf82locale(window->label());
#endif
		x->xid = CreateWindowEx(
			styleEx,
			class_name, label, style,
			xp, yp, window->w()+dw, window->h()+dh,
			parent,
			NULL, // menu
			fl_display,
			NULL // creation parameters
		);
#ifdef UNICODE
		if(label) free(label);
#endif
	}	
	
    x->dc = GetDC(x->xid);
    SetTextAlign(x->dc, TA_BASELINE|TA_LEFT);
    SetBkMode(x->dc, TRANSPARENT);

#if 0                        // WAS: Doing this completely breaks NT, the title bar loses highlight:
    if (window->override())
    {
        UINT posflags = SWP_NOMOVE|SWP_NOSIZE|SWP_NOSENDCHANGING;
        if(style & WS_POPUP)
            posflags |= SWP_NOACTIVATE;
        SetWindowPos(x->xid, HWND_TOPMOST, 0, 0, 0, 0, posflags);
    }
#endif

    x->wait_for_expose = true;
    x->next = Fl_X::first;
    Fl_X::first = x;

    // Drag-n-drop requires GCC 3.x or a non-GNU compiler...
#if !defined(__GNUC__) || __GNUC__ >= 3
    // Register all windows for potential drag'n'drop operations
    static bool oleInitialized = false;
    if (!oleInitialized) {oleInitialized = true; OleInitialize(0L);}
    RegisterDragDrop(x->xid, &flDropTarget);
#endif
}


////////////////////////////////////////////////////////////////

HINSTANCE fl_display = GetModuleHandle(NULL);

void Fl_Window::size_range_()
{
    m_size_range = true;
}

void Fl_X::set_minmax(LPMINMAXINFO minmax)
{
    int dx, dy, dw, dh; borders(window, dx, dy, dw, dh);

    minmax->ptMinTrackSize.x = window->m_minw + dw;
    minmax->ptMinTrackSize.y = window->m_minh + dh;
    if (window->m_maxw)
    {
        minmax->ptMaxTrackSize.x = window->m_maxw + dw;
        minmax->ptMaxSize.x = window->m_maxw + dw;
    }
    if (window->m_maxh)
    {
        minmax->ptMaxTrackSize.y = window->m_maxh + dw;
        minmax->ptMaxSize.y = window->m_maxh + dw;
    }
}


bool Fl_Window::iconic() const
{
    return i && IsIconic(i->xid);
}


////////////////////////////////////////////////////////////////

#include <efltk/filename.h>       // need so FL_API filename_name works
// returns pointer to the filename, or null if name ends with '/'
const char *fl_file_filename(const char *name)
{
    const char *p,*q;
    q = name;
    // skip leading drive letter
    if (q[0] && q[1]==':') q += 2;
    for (p = q; *p; p++) if (*p == '/' || *p == '\\') q = p+1;
    return q;
}

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
		TCHAR *text;
#ifdef UNICODE
        int len = fl_utf_nb_char((unsigned char*)l.c_str(), l.length());
        text = (TCHAR*)malloc((len + 1) * sizeof(TCHAR));
        fl_utf2unicode((unsigned char*)l.c_str(), len, (unsigned short*)text);
		text[len] = 0;
#else
		text = fl_utf82locale(l.c_str());
#endif
        SetWindowText(i->xid, text);
#ifdef UNICODE
        free(text);
#endif
    }
}
////////////////////////////////////////////////////////////////
// Drawing context

const Fl_Window *Fl_Window::current_;
HDC fl_gc;                       // the current context

// make X drawing go into this window (called by subclass flush() impl.)
void Fl_Window::make_current() const
{
    //    if (this == in_wm_paint)
    //      fl_gc = paint.hdc;
    //    else
    i->make_current();
    #if USE_COLORMAP
    // Windows maintains a hardware and software color palette; the
    // SelectPalette() call updates the current soft->hard mapping
    // for all drawing calls, so we must select it here before any
    // code does any drawing...
    fl_select_palette();
    #endif                       // USE_COLORMAP
    current_ = this;
}


// Code used to switch output to an off-screen window.  See macros in
// win32.h which save the old state in local variables.

HDC fl_makeDC(HBITMAP bitmap)
{
    HDC new_gc = CreateCompatibleDC(fl_gc);
    SetTextAlign(new_gc, TA_BASELINE|TA_LEFT);
    SetBkMode(new_gc, TRANSPARENT);
    #if USE_COLORMAP
    if (fl_palette) SelectPalette(new_gc, fl_palette, FALSE);
    #endif
    SelectObject(new_gc, bitmap);
    return new_gc;
}


void fl_copy_offscreen(int x,int y,int w,int h,HBITMAP bitmap,int srcx,int srcy)
{
    HDC new_gc = CreateCompatibleDC(fl_gc);
    SelectObject(new_gc, bitmap);
    BitBlt(fl_gc, x, y, w, h, new_gc, srcx, srcy, SRCCOPY);
    DeleteDC(new_gc);
}


////////////////////////////////////////////////////////////////

#ifndef SPI_GETWHEELSCROLLLINES
#define SPI_GETWHEELSCROLLLINES   104
#endif

#ifndef WHEEL_PAGESCROLL
                                 /* Scroll one page */
#define WHEEL_PAGESCROLL    (UINT_MAX)
#endif

static Fl_Color win_color(int wincol)
{
    int R = wincol&0xff;
    int G = (wincol >> 8)&0xff;
    int B = (wincol >> 16)&0xff;
    Fl_Color col = fl_rgb(R, G, B);
    if (col) return col;
    return FL_BLACK;
}


static int win_fontsize(int winsize)
{
                                 // -charsize: which is what FLTK uses
    if (winsize < 0) return -winsize;
    if (winsize == 0) return 12; // pick any good size.  12 is good!
    return winsize*3/4;          // cellsize: convert to charsize
}

const char *font_name(TCHAR *name)
{	
#ifdef UNICODE
	static char text[1024*2];
	int len = wcslen(name);
	if(len>1024) len = 1024;	
	text[fl_unicode2utf((unsigned short*)name, len, text)] = 0;
	return text;
#else
	return fl_locale2utf8(name);
#endif
}

bool fl_get_system_colors()
{

    Fl_Color background = win_color(GetSysColor(COLOR_BTNFACE));
    Fl_Color foreground = win_color(GetSysColor(COLOR_BTNTEXT));
    Fl_Color select_background = win_color(GetSysColor(COLOR_HIGHLIGHT));
    Fl_Color select_foreground = win_color(GetSysColor(COLOR_HIGHLIGHTTEXT));
    Fl_Color text_background = win_color(GetSysColor(COLOR_WINDOW));
    Fl_Color text_foreground = win_color(GetSysColor(COLOR_WINDOWTEXT));
    Fl_Color menuitem_background = win_color(GetSysColor(COLOR_MENU));
    Fl_Color menuitem_foreground = win_color(GetSysColor(COLOR_MENUTEXT));
    Fl_Color tooltip_background = win_color(GetSysColor(COLOR_INFOBK));
    Fl_Color tooltip_foreground = win_color(GetSysColor(COLOR_INFOTEXT));
    // Windows doesn't seem to honor this one
    // Fl_Color slider_background = win_color(GetSysColor(COLOR_SCROLLBAR));

    fl_background(background);
    Fl_Widget::default_style->label_color = foreground;
    Fl_Widget::default_style->highlight_label_color = foreground;
    Fl_Widget::default_style->color = text_background;
    Fl_Widget::default_style->text_color = text_foreground;
    Fl_Widget::default_style->selection_color = select_background;
    Fl_Widget::default_style->selection_text_color = select_foreground;

    Fl_Style* style = Fl_Style::find("scrollbar");

    if (style) {
        //    style->color = fl_color_average(slider_background, text_background, .5);
        style->color = fl_color_average(background, text_background, .5);
    }

    style = Fl_Style::find("item");
    if (style) {
        style->color = menuitem_background;
        style->label_color = menuitem_foreground;
        style->selection_color = select_background;
        style->selection_text_color = select_foreground;
    }

    /* This is the same as the defaults:
      if ((style = Fl_Style::find("menu title"))) {
        style->highlight_color = FL_GRAY;
        style->highlight_label_color = foreground;
        style->selection_color = FL_GRAY;
        style->selection_text_color = foreground;
      }
    */
    style = Fl_Style::find("menu bar");
    if (style) {
		// enable title highlightig
        style->highlight_color = FL_GRAY;
    }

    style = Fl_Style::find("tooltip");
    if (style) {
        style->color = tooltip_background;
        style->label_color = tooltip_foreground;
    }

    /*
       Windows font stuff

       It looks Windows has just three separate fonts that it actually
       uses for stuff replaced by FLTK.  But the "Display Properties"
       dialog has a lot more fonts that you can set?  Wrong, look again.
       Some of the fonts are duplicates and another doesn't do anything!
       It has fonts for the titlebar and icons which we don't have to worry
       about, a menu font which is used for menubars and menu items, a
       status font which is for status bars and tooltips, and a message
       box font which is used for everything else.  Except that it's not
       used by everything else;  almost all non-menu widgets in every
       application I tested did not respond to font changes.  The fonts
       are apparently hard coded by the applications which seems to me to
       bad programming considering that Windows has an adequate system for
       allowing the user to specify font preferences.  This is especially
       true of Microsoft applications and Windows itself!  We will allow
       FLTK applications to automatically use the fonts specified by the
       user.

       CET
    */

    NONCLIENTMETRICS ncm;
    int sncm = sizeof(ncm);
    ncm.cbSize = sncm;
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sncm, &ncm, SPIF_SENDCHANGE);

    Fl_Font font=0; 
	int size=0;
    // get font info for regular widgets from LOGFONT structure


    font = fl_find_font(font_name(ncm.lfMessageFont.lfFaceName));

	if(!font) font = FL_HELVETICA; //Just to be sure!

    if (ncm.lfMessageFont.lfWeight >= FW_SEMIBOLD) font = font->bold();
    if (ncm.lfMessageFont.lfItalic) font = font->italic();
    size = win_fontsize(ncm.lfMessageFont.lfHeight);

    Fl_Widget::default_style->label_font = font;
    Fl_Widget::default_style->text_font = font;
    Fl_Widget::default_style->label_size = size;
    Fl_Widget::default_style->text_size = size;

    style = Fl_Style::find("item");
    if (style)
    {
        // get font info for menu items from LOGFONT structure
        font = fl_find_font(font_name(ncm.lfMenuFont.lfFaceName));
        if (ncm.lfMenuFont.lfWeight >= FW_SEMIBOLD) font = font->bold();
        if (ncm.lfMenuFont.lfItalic) font = font->italic();
        size = win_fontsize(ncm.lfMenuFont.lfHeight);

        style->label_font = style->text_font = font;
        style->label_size = style->text_size = size;

        style = Fl_Style::find("menu bar");
        if (style)
        {
            style->label_font = style->text_font = font;
            style->label_size = style->text_size = size;
        }

        style = Fl_Style::find("menu title");
        if (style)
        {
            style->label_font = style->text_font = font;
            style->label_size = style->text_size = size;
        }
    }

    style = Fl_Style::find("tooltip");
    if (style)
    {
        // get font info for tooltips from LOGFONT structure
        font = fl_find_font(font_name(ncm.lfStatusFont.lfFaceName));
        if (ncm.lfStatusFont.lfWeight >= FW_SEMIBOLD) font = font->bold();
        if (ncm.lfStatusFont.lfItalic) font = font->italic();
        size = win_fontsize(ncm.lfStatusFont.lfHeight);

        style->label_font = style->text_font = font;
        style->label_size = style->text_size = size;
    }

    // grab mousewheel stuff from Windows
    UINT delta;
    SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, (PVOID)&delta, 0);
    if (delta == WHEEL_PAGESCROLL) Fl_Style::wheel_scroll_lines = 10000;
    else Fl_Style::wheel_scroll_lines = (int)delta;

    // CET - FIXME - do encoding stuff
    return true;
}


//
// End of "$Id$".
//
