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

#ifndef _FL_BUTTON_H_
#define _FL_BUTTON_H_

#include "Fl_Widget.h"

/**
 * Buttons generate callbacks when they are clicked by the user. 
 * You control exactly when and how by changing the values for type() and when().
 *
 * Buttons can also generate callbacks in response to FL_SHORTCUT events. 
 * The button can either have an explicit shortcut() value or a letter shortcut can be indicated in the label() with an '&' character before it. 
 * For the label shortcut it does not matter if Alt is held down, but if you have an input field in the same window, the user will have to hold down the Alt key so that the input field does not eat the event first as an FL_KEY event.
 */
class FL_API Fl_Button : public Fl_Widget {
public:
    static Fl_Named_Style* default_style;

	/** The constructor creates the button using the position, size, and label. */
    Fl_Button(int x, int y, int w, int h,const char *l=0);

    /** values for type(int), which can be one of: */
    enum {
        NORMAL = 0, /**< The value is unchanged. */
        TOGGLE = 1, /**< The value is inverted. */
        RADIO  = 2, /**< The value is set to 1, and all other buttons in the current group with type() == FL_RADIO_BUTTON are set to zero. */
        HIDDEN = 3  /**< The hidden button */
    };

    bool value() const { return Fl_Widget::value(); }
    bool value(bool);

	/** Same as value(true). */
    bool set();

	/** Same as value(false). */
    bool clear();

	/** Turns on this button and turns off all other radio buttons in the group (calling value(true) or set() does not do this). */
    void setonly();

    virtual void draw();
    virtual int handle(int event);
	virtual void preferred_size(int& w, int& h) const;

protected:
    void draw(int glyph, int glyph_width) const;
};

#endif
