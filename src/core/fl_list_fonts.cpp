//
// "$Id$"
//
// Copyright 1998-2000 by Bill Spitzak and others.
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
#include <efltk/fl_draw.h>
#include <string.h>

#ifdef _WIN32
# include "fl_list_fonts_win32.cpp"
#elif defined(__APPLE__)
# include "fl_list_fonts_mac.cpp"
#else
# if USE_XFT
// the code is included by fl_font.cpp
# else
#  include "fl_list_fonts_x.cpp"
# endif
#endif

// For Xlib the only way to reliably get a font is to enumerate them all
// and then search. For Xft and Win32 we should be able to program a more
// direct call, as long as we accumulate all the names we searched for
// into an array and fl_list_fonts can add all the missing ones to the
// array. This is sufficiently painful that I have not done this yet.

Fl_Font fl_find_font(const char* name, int attributes )
{
    if (!name || !*name) return 0;
    // find out if the " bold" or " italic" are on the end:
    int length = strlen(name);
    if (length > 7 && !strncasecmp(name+length-7, " italic", 7))
    {
        length -= 7; attributes |= FL_ITALIC;
    }
    if (length > 5 && !strncasecmp(name+length-5, " bold", 5))
    {
        length -= 5; attributes |= FL_BOLD;
    }
    Fl_Font font = 0;
    // always try the built-in fonts first, becasue fl_list_fonts is *slow*...
    int i; for (i = 0; i < 16; i += (i < 12 ? 4 : 1)) {
        font = fl_fonts+i;
        const char* fontname = font->name();
        if (!strncasecmp(name, fontname, length) && !fontname[length]) goto GOTIT;
    }
    // now try all the fonts on the server, using a binary search:
    font = 0;
    {
        Fl_Font* list; int b = fl_list_fonts(list); int a = 0;
        while (a < b)
        {
            int c = (a+b)/2;
            Fl_Font testfont = list[c];
            const char* fontname = testfont->name();
			int d = strncasecmp(name, fontname, length);
            if (!d)
            {				
                // If we match a prefix of the font return it unless a better match found
                font = testfont;
                if (!fontname[length]) goto GOTIT;
            }
            if (d > 0) a = c+1;
            else b = c;
        }
    }
    if (!font) return 0;
    GOTIT:
    if (attributes & FL_BOLD) font = font->bold_;
    if (attributes & FL_ITALIC) font = font->italic_;
    return font;
}


//
// End of "$Id$".
//
