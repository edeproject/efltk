//
// "$Id$"
//
// Arc functions for the Fast Light Tool Kit (FLTK).
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

// Utility for drawing arcs and circles.  They are added to
// the current fl_begin/fl_vertex/fl_end path.

// Based on code donated by Jim Wilson

#include <efltk/fl_draw.h>
#include <efltk/math.h>

void fl_arc(double l, double b, double w, double h, double start, double end)
{

    const double x = l+w/2;
    const double y = b+h/2;
    double angle = start*(M_PI/180);

    // draw start point accurately:
    double X = w/2*cos(angle);
    double Y = -h/2*sin(angle);

    #define MAXPOINTS 100
    float points[MAXPOINTS][2];
    float* p = points[0];
    *p++ = float(x+X); *p++ = float(y+Y);

    // Maximum arc length to approximate with chord with error <= 0.125

    double epsilon;
    {
        // calculate area of parallelogram defined by diameters
        double dx1,dy1; dx1=w; dy1=0; fl_transform_distance(dx1,dy1);
        double dx2,dy2; dx2=0; dy2=h; fl_transform_distance(dx2,dy2);
        double r = fabs(dx1*dy2 - dx2*dy1);
        r = .5*sqrt(r);          // approximate radius
        // I don't understand this part:
        r = 1.0 - 0.125/r;       // r2 = cos(epsilon/2)
        if (r < 0.5) r = 0.5;    // minimum 3 chords/circle
        epsilon = /*2**/acos(r);       // Maximum arc angle
    }
                                 // Displacement angle (radians)
    angle = end*(M_PI/180) - angle;
                                 // Segments in approximation
    int i = int(ceil(fabs(angle)/epsilon));
    if (i > MAXPOINTS-1) i = MAXPOINTS-1;

    if (i)
    {
        epsilon = angle/i;       // Arc length for equal-size steps
        // calculate transformation matrix that does rotation by epsilon in
        // a scaled by w,h coordinate system. We could in fact figure out a
        // transformation for the actual current fl_transform and calculate
        // real pixel positions, have not figured this out yet:
        const double m00 = cos(epsilon);
        const double m11 = m00;
        const double sin_e = sin(epsilon);
        const double m01 = sin_e*w/h;
        const double m10 = -sin_e*h/w;
        do
        {
            double Xnew = m00*X + m01*Y;
            Y = m10*X + m11*Y;
            X = Xnew;
            *p++ = float(x + X);
            *p++ = float(y + Y);
        } while (--i);
    }
    fl_vertices((p-points[0])/2, points);
}


#if 0                            // portable version.  X-specific one in fl_vertex.C
void fl_circle(double x,double y,double r)
{
    _fl_arc(x, y, r, r, 0, 360);
}
#endif

//
// End of "$Id$".
//
