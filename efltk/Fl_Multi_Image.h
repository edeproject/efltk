//
// "$Id$"
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

#ifndef Fl_Multi_Image_H
#define Fl_Multi_Image_H

#include "Fl_Image.h"

class Fl_Multi_Image : public Fl_Image
{
  enum {MAXIMAGES = 8};
  Fl_Image* images[MAXIMAGES];
  Fl_Flags flags[MAXIMAGES];
public:
  Fl_Multi_Image(Fl_Image& image0,
                 Fl_Flags flags1, Fl_Image& image1) {
      images[0] = &image0;
      flags[1] = flags1; images[1] = &image1;
      images[2] = 0;
  }
  Fl_Multi_Image(Fl_Image& image0,
                 Fl_Flags flags1, Fl_Image& image1,
                 Fl_Flags flags2, Fl_Image& image2) {
      images[0] = &image0;
      flags[1] = flags1; images[1] = &image1;
      flags[2] = flags2; images[2] = &image2;
      images[3] = 0;
  }
  Fl_Multi_Image(Fl_Image& image0,
                 Fl_Flags flags1, Fl_Image& image1,
                 Fl_Flags flags2, Fl_Image& image2,
                 Fl_Flags flags3, Fl_Image& image3) {
      images[0] = &image0;
      flags[1] = flags1; images[1] = &image1;
      flags[2] = flags2; images[2] = &image2;
      flags[3] = flags3; images[3] = &image3;
      images[4] = 0;
  }
  Fl_Multi_Image(Fl_Image& image0,
                 Fl_Flags flags1, Fl_Image& image1,
                 Fl_Flags flags2, Fl_Image& image2,
                 Fl_Flags flags3, Fl_Image& image3,
                 Fl_Flags flags4, Fl_Image& image4) {
      images[0] = &image0;
      flags[1] = flags1; images[1] = &image1;
      flags[2] = flags2; images[2] = &image2;
      flags[3] = flags3; images[3] = &image3;
      flags[4] = flags4; images[4] = &image4;
      images[5] = 0;
  }
  Fl_Multi_Image(Fl_Image& image0,
		Fl_Flags flags1, Fl_Image& image1,
		Fl_Flags flags2, Fl_Image& image2,
		Fl_Flags flags3, Fl_Image& image3,
		Fl_Flags flags4, Fl_Image& image4,
		Fl_Flags flags5, Fl_Image& image5) {
    images[0] = &image0;
    flags[1] = flags1; images[1] = &image1;
    flags[2] = flags2; images[2] = &image2;
    flags[3] = flags3; images[3] = &image3;
    flags[4] = flags4; images[4] = &image4;
    flags[5] = flags5; images[5] = &image5;
    images[6] = 0;
  }
  Fl_Multi_Image(Fl_Image& image0,
		Fl_Flags flags1, Fl_Image& image1,
		Fl_Flags flags2, Fl_Image& image2,
		Fl_Flags flags3, Fl_Image& image3,
		Fl_Flags flags4, Fl_Image& image4,
		Fl_Flags flags5, Fl_Image& image5,
		Fl_Flags flags6, Fl_Image& image6) {
    images[0] = &image0;
    flags[1] = flags1; images[1] = &image1;
    flags[2] = flags2; images[2] = &image2;
    flags[3] = flags3; images[3] = &image3;
    flags[4] = flags4; images[4] = &image4;
    flags[5] = flags5; images[5] = &image5;
    flags[6] = flags6; images[6] = &image6;
    images[7] = 0;
  }
  Fl_Multi_Image(Fl_Image& image0,
		Fl_Flags flags1, Fl_Image& image1,
		Fl_Flags flags2, Fl_Image& image2,
		Fl_Flags flags3, Fl_Image& image3,
		Fl_Flags flags4, Fl_Image& image4,
		Fl_Flags flags5, Fl_Image& image5,
		Fl_Flags flags6, Fl_Image& image6,
		Fl_Flags flags7, Fl_Image& image7) {
    images[0] = &image0;
    flags[1] = flags1; images[1] = &image1;
    flags[2] = flags2; images[2] = &image2;
    flags[3] = flags3; images[3] = &image3;
    flags[4] = flags4; images[4] = &image4;
    flags[5] = flags5; images[5] = &image5;
    flags[6] = flags6; images[6] = &image6;
    flags[7] = flags7; images[7] = &image7;
  }

  virtual void measure(int&,int&);

protected:
    virtual void _draw(int dx, int dy, int dw, int dh,
                      int sx, int sy, int sw, int sh,
                      Fl_Flags f);
};

#endif

//
// End of "$Id$".
//
