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

#ifndef _FL_PRINTER_H_
#define _FL_PRINTER_H_

#include "fl_draw.h"
#include "Enumerations.h"

const double FL_POINT = 1;
const double FL_INCH = 72;
const double FL_MM = 2.835;
const double FL_CM = 28.35;
const double FL_PICA = 12;

const int NO_PAGE_FORMATS=30;

/** Fl_Printer */
class FL_API Fl_Printer : public Fl_Device {
public:
    enum PAGE_FORMAT{
        USER, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9,
        B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10,
        C5E, DLE, EXECUTIVE, FOLIO, LEDGER, LEGAL,
        LETTER, TABLOID, ENVELOPE, NON_DEFINED = -1
    };
    enum PAGE_LAYOUT { PORTRAIT=0, LANDSCAPE=1 };

    static const int page_formats[NO_PAGE_FORMATS+1][2];
    virtual void page(double pw, double ph, int orientation) = 0;
    virtual void page(int format, int orientation) = 0;
    double page_width() const { return pw_; }
    double page_height() const { return ph_; }
    virtual void page() = 0;
    virtual void margins(double left, double top, double right, double bottom) = 0;

    virtual void fit(double x, double y, double w, double h, int align) = 0;
    virtual void fit(double x, double y, double w, double h, double dpi, int align) = 0;
    void fit(Fl_Widget * w, int align);
    void fit(Fl_Widget * w, double dpi, int align);

    virtual void place(double x, double y, double w, double h, double tx, double ty, double tw, double th, int align) = 0;
    virtual void place(double x, double y, double w, double h, double tx, double ty, double tw, double th, double dpi, int align) = 0;
    void place(Fl_Widget * w, double tx, double ty, double tw, double th, int align) { place(w->x(),w->y(),w->w(),w->h(), tx, ty, tw, th, align); }
    void place(Fl_Widget * w, double tx, double ty, double tw, double th, double dpi, int align) { place(w->x(),w->y(),w->w(),w->h(), tx, ty, tw, th, dpi, align); }

    Fl_Printer() : lm_(72),tm_(72),rm_(72),bm_(72),orientation_(0) { }
    virtual ~Fl_Printer() { }

    virtual void draw(Fl_Widget * w) = 0;

    virtual void draw(const char* s, float x, float y) { Fl_Device::draw(s, x, y); }
    virtual void draw(const Fl_String & s, float x, float y) { Fl_Device::draw(s, x, y); }
    virtual void draw(const char* s, int n, float x, float y) { Fl_Device::draw(s, n, x, y); }

protected:

    int nPages;
    double lm_,tm_,rm_,bm_;
    double pw_, ph_;
    int orientation_;
};

#ifdef _WIN32

#include "Fl_Gdi.h"
#ifndef FL_PRINTER
#define FL_GDI_PRINTER
#define FL_PRINTER FL_GDI_PRINTER
typedef Fl_Gdi_Settings Fl_Printer_Settings;
inline Fl_Printer * fl_printer_chooser(Fl_Printer_Settings * s=0) {
    return fl_gdi_printer_chooser(s);
}
#endif

#endif //_WIN32

#endif // _FL_DEVICE_H_
