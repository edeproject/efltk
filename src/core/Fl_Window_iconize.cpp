//
// "$Id$"
//
// Window minification code for the Fast Light Tool Kit (FLTK).
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

#include <config.h>

#include <efltk/Fl_Window.h>
#include <efltk/x.h>

extern bool fl_show_iconic;      // in Fl_x.C/Fl_win32.C

void Fl_Window::iconize()
{
    if (!i) {
        fl_show_iconic = true;
        show();
    } else {
#ifdef _WIN32
# ifndef _WIN32_WCE
		ShowWindow(i->xid, SW_SHOWMINNOACTIVE);
# endif
#else
        XIconifyWindow(fl_display, i->xid, fl_screen);
        i->wait_for_expose = true;
#endif
        set_visible();
    }
}


//
// End of "$Id$".
//
