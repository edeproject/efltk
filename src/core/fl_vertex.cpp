//
// "$Id$"
//
// Path construction and filling. I think this file is always linked
// into any fltk program, so try to keep it reasonably small.
// Also see fl_arc.cxx and fl_curve.cxx
//
// Copyright 2001 by Bill Spitzak and others.
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

#include <efltk/fl_draw.h>
#include <efltk/x.h>

#include <stdlib.h>

////////////////////////////////////////////////////////////////
// Transformation:

struct Matrix {
  float a, b, c, d, x, y;
  int ix, iy; // x & y rounded to nearest integer
  bool trivial; // true if no rotation or scale
};

static Matrix m = {1, 0, 0, 1, 0, 0, 0, 0, true};
static Matrix stack[64];
static int sptr = 0;

void Fl_Device::push_matrix() {
    stack[sptr++] = m;
}

void Fl_Device::pop_matrix() {
    m = stack[--sptr];
}

void Fl_Device::mult_matrix(float a, float b, float c, float d, float x, float y) {
  if (m.trivial) {
    m.a = a; m.b = b; m.c = c; m.d = d;
    m.x += x; m.ix = int(floor(m.x+.5f));
    m.y += y; m.iy = int(floor(m.y+.5f));
    m.trivial = false;
  } else {
    Matrix o;
    o.a = a*m.a + b*m.c;
    o.b = a*m.b + b*m.d;
    o.c = c*m.a + d*m.c;
    o.d = c*m.b + d*m.d;
    o.x = x*m.a + y*m.c + m.x; o.ix = int(floor(o.x+.5f));
    o.y = x*m.b + y*m.d + m.y; o.iy = int(floor(o.y+.5f));
    o.trivial = false;
    m = o;
  }
}

void Fl_Device::scale(float x,float y) {
  if (x != 1.0 && y != 1.0) fl_mult_matrix(x,0,0,y,0,0);
}

void Fl_Device::scale(float x) {
    if (x != 1.0) fl_mult_matrix(x,0,0,x,0,0);
}

void Fl_Device::translate(float x,float y) {
  if (m.trivial) {
    m.x += x; m.ix = int(floor(m.x+.5f));
    m.y += y; m.iy = int(floor(m.y+.5f));
    m.trivial = m.ix==m.x && m.iy==m.y;
  } else {
    fl_mult_matrix(1,0,0,1,x,y);
  }
}

void Fl_Device::translate(int x, int y) {
  if (m.trivial) {
    m.ix += x; m.x = float(m.ix);
    m.iy += y; m.y = float(m.iy);
  } else {
    fl_mult_matrix(1,0,0,1, float(x), float(y));
  }
}

void Fl_Device::rotate(float d) {
  if (d) {
    float s, c;
    if (d == 0) {s = 0; c = 1;}
    else if (d == 90) {s = 1; c = 0;}
    else if (d == 180) {s = 0; c = -1;}
    else if (d == 270 || d == -90) {s = -1; c = 0;}
    else {s = sinf(d*float(M_PI/180)); c = cosf(d*float(M_PI/180));}
    fl_mult_matrix(c,-s,s,c,0,0);
  }
}

void Fl_Device::load_identity() {
  m.a = 1; m.b = 0; m.c = 0; m.d = 1;
  m.x = 0; m.y = 0;
  m.ix = 0; m.iy = 0;
  m.trivial = true;
}

////////////////////////////////////////////////////////////////
// Return the transformation of points:

void Fl_Device::transform(float& x, float& y) {
  if (!m.trivial) {
    float t = x*m.a + y*m.c + m.x;
    y = x*m.b + y*m.d + m.y;
    x = t;
  } else {
    x += m.x;
    y += m.y;
  }
}

void Fl_Device::transform_distance(float& x, float& y) {
  if (!m.trivial) {
    float t = x*m.a + y*m.c;
    y = x*m.b + y*m.d;
    x = t;
  }
}

void Fl_Device::transform(int& x, int& y) {
  if (!m.trivial) {
    int t = int(floor(x*m.a + y*m.c + m.x + .5f));
    y = int(floor(x*m.b + y*m.d + m.y + .5f));
    x = t;
  } else {
    x += m.ix;
    y += m.iy;
  }
}

////////////////////////////////////////////////////////////////
// Path construction:

// typedef what the x,y fields in a point are:
#ifdef _WIN32
typedef int COORD_T;
#else
typedef short COORD_T;
#endif

// Storage of the current path:

// Points:
static XPoint *point_; // all the points
static int point_array_size;
static int points_; // number of points

// Loop:
static int loop_start; // point at start of current loop
static int* loop; // number of points in each loop
static int loops; // number of loops
static int loop_array_size;

static void add_n_points(int n)
{
    point_array_size = (point_array_size>0) ? 2*point_array_size : 16;
    if(points_+n >= point_array_size) point_array_size = n;
    point_ = (XPoint*)realloc((void*)point_, (point_array_size+1)*sizeof(XPoint));
}

void Fl_Device::vertex(float X, float Y)
{
    COORD_T x = COORD_T(floor(X*m.a + Y*m.c + m.x + .5f));
    COORD_T y = COORD_T(floor(X*m.b + Y*m.d + m.y + .5f));
    if (!points_ || x != point_[points_-1].x || y != point_[points_-1].y) {
        if (points_+1 >= point_array_size) add_n_points(1);
        point_[points_].x = x;
        point_[points_].y = y;
        points_++;
    }
}

void Fl_Device::vertex(int X, int Y)
{
    COORD_T x,y;
    if (m.trivial) {
        x = COORD_T(X+m.ix);
        y = COORD_T(Y+m.iy);
    } else {
        x = COORD_T(floor(X*m.a + Y*m.c + m.x + .5f));
        y = COORD_T(floor(X*m.b + Y*m.d + m.y + .5f));
    }
    if (!points_ || x != point_[points_-1].x || y != point_[points_-1].y) {
        if (points_+1 >= point_array_size) add_n_points(1);
        point_[points_].x = x;
        point_[points_].y = y;
        points_++;
    }
}

void Fl_Device::vertices(int n, const float array[][2])
{
    if (points_+n >= point_array_size) add_n_points(n);
    const float* a = array[0];
    const float* e = a+2*n;
    int pn = points_;
    if (m.trivial) {
        for (; a < e; a += 2) {
            COORD_T x = COORD_T(floor(a[0] + m.x + .5f));
            COORD_T y = COORD_T(floor(a[1] + m.y + .5f));
            if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
                point_[pn].x = x;
                point_[pn].y = y;
                pn++;
            }
        }
    } else {
        for (; a < e; a += 2) {
            COORD_T x = COORD_T(floor(a[0]*m.a + a[1]*m.c + m.x + .5f));
            COORD_T y = COORD_T(floor(a[0]*m.b + a[1]*m.d + m.y + .5f));
            if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
                point_[pn].x = x;
                point_[pn].y = y;
                pn++;
            }
        }
    }
    points_ = pn;
}

void Fl_Device::vertices(int n, const int array[][2])
{
    if (points_+n >= point_array_size) add_n_points(n);
    const int* a = array[0];
    const int* e = a+2*n;
    int pn = points_;
    if (m.trivial) {
        for (; a < e; a += 2) {
            COORD_T x = COORD_T(a[0]+m.ix);
            COORD_T y = COORD_T(a[1]+m.iy);
            if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
                point_[pn].x = x;
                point_[pn].y = y;
                pn++;
            }
        }
    } else {
        for (; a < e; a += 2) {
            COORD_T x = COORD_T(floor(a[0]*m.a + a[1]*m.c + m.x + .5f));
            COORD_T y = COORD_T(floor(a[0]*m.b + a[1]*m.d + m.y + .5f));
            if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
                point_[pn].x = x;
                point_[pn].y = y;
                pn++;
            }
        }
    }
    points_ = pn;
}

void Fl_Device::transformed_vertices(int n, const float array[][2])
{
    if (points_+n >= point_array_size) add_n_points(n);
    const float* a = array[0];
    const float* e = a+2*n;
    int pn = points_;
    for (; a < e; a += 2) {
        COORD_T x = COORD_T(floor(a[0] + .5f));
        COORD_T y = COORD_T(floor(a[1] + .5f));
        if (!pn || x != point_[pn-1].x || y != point_[pn-1].y) {
            point_[pn].x = x;
            point_[pn].y = y;
            pn++;
        }
    }
    points_ = pn;
}

void Fl_Device::closepath()
{
    if (points_ > loop_start+2) {
        // close the shape by duplicating first point_:
        XPoint& q = point_[loop_start];
        // the array always has one extra point_ so we don't need to check
        XPoint& p = point_[points_-1];
        if (p.x != q.x || p.y != q.y) point_[points_++] = q;
        // remember the new loop:
        if (loops >= loop_array_size) {
            loop_array_size = loop_array_size ? 2*loop_array_size : 16;
            loop = (int*)realloc((void*)loop, loop_array_size*sizeof(int));
        }
        loop[loops++] = points_-loop_start;
        loop_start = points_;
    } else {
        points_ = loop_start;
    }
}

////////////////////////////////////////////////////////////////
// Enormous kludge to add arcs to a path but try to take advantage
// of primitive arc-drawing functions provided by the OS. This mess
// should not be needed on newer systems...
//
// We keep track of exactly one "nice" circle:

static int circle_x, circle_y, circle_w, circle_h;

// Add a circle to the path. It is always a circle, irregardless of
// the transform. Currently only one per path is supported, this uses
// commands on the server to draw a nicer circle than the path mechanism
// can make.
void Fl_Device::circle(float x, float y, float r) {
  fl_transform(x,y);
  float rt = r * sqrt(fabs(m.a*m.d-m.b*m.c));
  circle_w = circle_h = int(rt*2 + .5);
  circle_x = int(floor(x - circle_w*.5f + .5f));
  circle_y = int(floor(y - circle_h*.5f + .5f));
}

// Add an ellipse to the path. On X/Win32 this only works for 90 degree
// rotations and only one ellipse (or cirlce) per path is supported.
void Fl_Device::ellipse(float x, float y, float w, float h) {
#if 1
  // Use X/Win32 drawing functions as best we can. Only works for 90
  // degree rotations:
  x += w/2;
  y += h/2;
  fl_transform(x,y);
  float d1x,d1y; d1x = w; d1y = 0; fl_transform_distance(d1x, d1y);
  float d2x,d2y; d2x = 0; d2y = h; fl_transform_distance(d2x, d2y);
  float rx = sqrt(d1x*d1x+d2x*d2x)/2;
  float ry = sqrt(d1y*d1y+d2y*d2y)/2;
  circle_w = int(rx*2 + .5f);
  circle_x = int(floor(x - circle_w*.5f + .5f));
  circle_h = int(ry*2 + .5f);
  circle_y = int(floor(y - circle_h*.5f + .5f));
#else
  // This produces the correct image, but not as nice as using circles
  // produced by the server:
  fl_closepath();
  fl_arc(x, y, w, h, 0, 360);
  fl_closepath();
#endif
}

////////////////////////////////////////////////////////////////
// Draw the path:

static inline void inline_newpath() {
  points_ = loop_start = loops = circle_w = 0;
}
void Fl_Device::newpath() {inline_newpath();}

void Fl_Device::points() {
#ifdef _WIN32
  for (int i=0; i<points_; i++)
    SetPixel(fl_gc, point_[i].x, point_[i].y, fl_colorref);
#else
  if (points_ > 0) XDrawPoints(fl_display, fl_window, fl_gc, point_, points_, 0);
#endif
  inline_newpath();
}

void Fl_Device::stroke() {
#ifdef _WIN32
  if (circle_w > 0)
    Arc(fl_gc, circle_x, circle_y, circle_x+circle_w+1, circle_y+circle_h+1,
	0,0, 0,0);
  int loop_start = 0;
  for (int n = 0; n < loops; n++) {
    int loop_size = loop[n];
    Polyline(fl_gc, point_+loop_start, loop_size);
    loop_start += loop_size;
  }
  int loop_size = points_-loop_start;
  if (loop_size > 1)
    Polyline(fl_gc, point_+loop_start, loop_size);
#else
  if (circle_w > 0)
    XDrawArc(fl_display, fl_window, fl_gc,
	     circle_x, circle_y, circle_w, circle_h, 0, 360*64);
  int loop_start = 0;
  for (int n = 0; n < loops; n++) {
    int loop_size = loop[n];
    XDrawLines(fl_display, fl_window, fl_gc, point_+loop_start, loop_size, 0);
    loop_start += loop_size;
  }
  int loop_size = points_-loop_start;
  if (loop_size > 1)
    XDrawLines(fl_display, fl_window, fl_gc, point_+loop_start, loop_size, 0);
#endif
  inline_newpath();
}

// Warning: result is different on X and Win32! Use fl_fill_stroke().
// There may be a way to tell Win32 to do what X does, perhaps by making
// the current pen invisible?
void Fl_Device::fill() {
#ifdef _WIN32
  if (circle_w > 0)
    Chord(fl_gc, circle_x, circle_y, circle_x+circle_w+1, circle_y+circle_h+1,
	  0,0, 0,0);
#ifndef _WIN32_WCE
  if (loops) {
    fl_closepath();
    PolyPolygon(fl_gc, point_, loop, loops);
  } else 
#endif
	  if (points_ > 2) {
    Polygon(fl_gc, point_, points_);
  }
#else
  if (circle_w > 0)
    XFillArc(fl_display, fl_window, fl_gc,
	     circle_x, circle_y, circle_w, circle_h, 0, 64*360);
  if (loops) fl_closepath();
  if (points_ > 2) {
    if (loops > 2) {
      // back-trace the lines between each "disconnected" part so they
      // are actually connected:
      if (points_+loops-2 >= point_array_size) add_n_points(loops-2);
      int n = points_-1;
      for (int i = loops; --i > 1;) {
	n -= loop[i];
	point_[points_++] = point_[n];
      }
    }
    XFillPolygon(fl_display, fl_window, fl_gc, point_, points_, 0, 0);
  }
#endif
  inline_newpath();
}

// This seems to produce very similar results on X and Win32. Also
// should be faster than seperate fill & stroke on Win32 and on
// PostScript/PDF style systems.
void Fl_Device::fill_stroke(Fl_Color color) {
#ifdef _WIN32
  COLORREF saved = fl_colorref;
  fl_colorref = fl_wincolor(color);
  HPEN newpen = fl_create_pen();
  fl_colorref = saved;
  HPEN oldpen = (HPEN)SelectObject(fl_gc, newpen);
  if (circle_w > 0)
    Chord(fl_gc, circle_x, circle_y, circle_x+circle_w+1, circle_y+circle_h+1,
	  0,0, 0,0);
#ifndef _WIN32_WCE
  if (loops) {
    fl_closepath();
    PolyPolygon(fl_gc, point_, loop, loops);
  } else 
#endif
	  if (points_ > 2) {
    Polygon(fl_gc, point_, points_);
  }
  SelectObject(fl_gc, oldpen);
  DeleteObject(newpen);
  inline_newpath();
#else
  if (circle_w > 0)
    XFillArc(fl_display, fl_window, fl_gc,
	     circle_x, circle_y, circle_w, circle_h, 0, 64*360);
  fl_closepath();
  if (points_ > 2) {
    int saved_points = points_;
    if (loops > 2) {
      // back-trace the lines between each "disconnected" part so they
      // are actually connected:
      if (points_+loops-2 >= point_array_size) add_n_points(loops-2);
      int n = saved_points-1;
      for (int i = loops; --i > 1;) {
	n -= loop[i];
	point_[points_++] = point_[n];
      }
    }
    XFillPolygon(fl_display, fl_window, fl_gc, point_, points_, 0, 0);
    points_ = saved_points; // throw away the extra points
  }
  Fl_Color saved = fl_color();
  fl_color(color); fl_stroke();
  fl_color(saved);
#endif
}

//
// End of "$Id$".
//
