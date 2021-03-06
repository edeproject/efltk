//
// "$Id$"
//
// Font selection code for the Fast Light Tool Kit (FLTK).
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

#include <efltk/fl_math.h>
#include <config.h>

#include <efltk/Fl_Font.h>
#include <efltk/fl_draw.h>

// Static variables containing the currently selected font, size, encoding:
Fl_Font fl_font_;
float fl_size_;
const char *fl_encoding_ = "iso8859-1";

static Fl_Ptr_List *all_fonts=0;
#define append_font(f) if(!all_fonts) all_fonts=new Fl_Ptr_List(); all_fonts->append(f)

#ifdef _WIN32
# include "fl_font_win32.cpp"
#elif defined(__APPLE__)
# include "fl_font_mac.cpp"
#else
# if USE_XFT
#  include "fl_font_xft.cpp"
# else
#  include "fl_font_x.cpp"
# endif
#endif

void Fl_Device::draw(const char* str, float x, float y) {
    fl_draw(str, strlen(str), x, y);
}

void Fl_Device::draw(const Fl_String &str, float x, float y) {
    fl_draw(str.c_str(), str.length(), x, y);
}

void Fl_Device::draw(const char* str, int n, float x, float y) {
  fl_transform(x,y);
  fl_transformed_draw(str, n, x, y);
}

float Fl_Device::width(const char* str) const {
    return fl_width(str, strlen(str));
}

float Fl_Device::width(const Fl_String &str) const {
    return fl_width(str.c_str(), str.length());
}

// Deallocate fonts on exit. Warning: it will crash if you try
// to do any fonts after this, because the pointers are not changed!
void fl_font_rid()
{
    if(all_fonts) {
        for(unsigned n=0; n<all_fonts->size(); n++) {
            Fl_FontSize* fontsize = (Fl_FontSize*)(*all_fonts)[n];
            delete fontsize;
        }
        delete all_fonts;
    }
}


//
// End of "$Id$".
//
