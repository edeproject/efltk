//
// "$Id$"
//
// Image drawing routines for the Fast Light Tool Kit (FLTK).
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

#include <efltk/Fl.h>
#include <efltk/fl_draw.h>
#include <efltk/x.h>

#include <efltk/Fl_Util.h>
#include <efltk/Fl_Renderer.h>


// Include platform depend files.
// Files with _2 at end provides FLTK2 original
// drawing functions. They are provided for backward
// compatibility and cause they are nice in some purposes :)
#ifdef _WIN32
# include "fl_draw_image_win32.cpp"
# include "fl_draw_image_win32_2.cpp"
#else
# include "fl_draw_image_x.cpp"
# include "fl_draw_image_x_2.cpp"
#endif

void fl_draw_image(const uchar* buf, int x, int y, int w, int h, int d, int l){
    innards(buf,x,y,w,h,d,l,(d<3&&d>-3),0,0);
}
void fl_draw_image(Fl_Draw_Image_Cb cb, void* data, int x, int y, int w, int h,int d) {
    innards(0,x,y,w,h,d,0,(d<3&&d>-3),cb,data);
}
void fl_draw_image_mono(const uchar* buf, int x, int y, int w, int h, int d, int l){
    innards(buf,x,y,w,h,d,l,1,0,0);
}
void fl_draw_image_mono(Fl_Draw_Image_Cb cb, void* data, int x, int y, int w, int h,int d) {
    innards(0,x,y,w,h,d,0,1,cb,data);
}

//
// End of "$Id$".
//
