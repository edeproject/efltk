/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_IMAGEFILTER_H_
#define _FL_IMAGEFILTER_H_

#include "Enumerations.h"
#include "Fl_Renderer.h"
#include "Fl_Util.h"

class Fl_Image;

/**
 * This file contains filters for Fl_Image.
 * You can apply modifier filter to image or to new Fl_Image.
 * functions takes value parameters from 0 to 3. Some of modifiers,
 * like DESATURATE doesnt take any values, but then again gamma modifier
 * will take 3, val1 as Red, val2 as Green, val3 as Blue, gamma correction values.
 */

// apply_to_[new|this](Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1, float val2, float val3)
// image - Fl_Image where to apply modifier
// rect - rectangle to apply or NULL for whole image
// filter - modifier filter (see end of this file)
// float val1-val3 modifier values, defined below

/**
 * Base Image_Filter class.
 */
class Fl_Image_Filter
{
public:
    static bool apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter);
    static bool apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1);
    static bool apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1, float val2);
    static bool apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1, float val2, float val3);

    static Fl_Image *apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter);
    static Fl_Image *apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1);
    static Fl_Image *apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1, float val2);
    static Fl_Image *apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1, float val2, float val3);

protected:
    virtual bool execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3) { return false; }
};

class FilterBrightness : public Fl_Image_Filter
{
public:
    // Takes 1 value, brightness correction
    virtual bool execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3);
};

class FilterContrast : public Fl_Image_Filter
{
public:
    // Takes 1-3 values (RGB), contrast correction
    virtual bool execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3);
};

class FilterGamma : public Fl_Image_Filter
{
public:
    // Takes 1-3 values (RGB), gamma correction
    virtual bool execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3);
};

class FilterDesaturate : public Fl_Image_Filter
{
public:
    // Takes 0 value, grayscales image
    virtual bool execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3);
};

extern FL_API FilterBrightness filter_brightness;
#define FILTER_BRIGHTNESS (&filter_brightness)

extern FL_API FilterContrast filter_contrast;
#define FILTER_CONTRAST (&filter_contrast)

extern FL_API FilterGamma filter_gamma;
#define FILTER_GAMMA (&filter_gamma)

extern FL_API FilterDesaturate filter_desaturate;
#define FILTER_DESATURATE (&filter_desaturate)

#endif
