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

#ifndef _FL_PACK_H_
#define _FL_PACK_H_

#include "Fl_Group.h"

/**
 * This grouping widget arranges and resizes all of it's children so they are all packed close together 
 * and completely fill the widget. This is similar to layout widgets used by TK and some other toolkits. 
 * 
 * Each child widget is stretched (ie one of it's dimensions is changed and the other left alone) to completely fill the remaining space on one edge of the pack and placed against all the previous widgets on that edge.
 *
 * Any widget with the FL_PACK_VERTICAL bit (8) set in the flags() are placed against the left or right edge, otherwise against the top or bottom edge. (If type() of the pack is set to Fl_Pack::HORIZONTAL then it will "pack horzontally" which means that all widgets are packed against the left or right edges, whether or not they have FL_PACK_VERTICAL turned on)
 *
 * All widgets before the resizable() widget are placed against the top and left edge, all widgets after the resizable() widget are placed against the bottom and right edge in backwards order. If the resizable() is not set, all widgets are placed against the top and left edge, and the pack itself resizes to surround them. Such a pack must be imbedded in another pack or be the only child of a window so that this resizing can be used to layout the parent widget.
 *
 * If any child changes size the pack automatically re-layouts and possibly changes it's own size to accomodate it. If you add, move, remove, hide, or show a child widget, or change the FL_PACK_VERTICAL flag, you should call relayout() on the pack yourself.
 *
 * The default box is FL_FLAT_BOX. If you set it to something else the border of the box is drawn and the widgets are packed against the inside of this border.
 */
class FL_API Fl_Pack : public Fl_Group {
public:
    static Fl_Named_Style* default_style;

	/**
	 * Creates a new empty Fl_Pack. 
	 */
    Fl_Pack(int x,int y,int w ,int h,const char *label=0);

	/** values for type(int) */
    enum Types {
        NORMAL	    = GROUP_TYPE,   /**< Pack widgets vertically */
        VERTICAL    = NORMAL,		/**< For back compatability */
        HORIZONTAL  = GROUP_TYPE+1  /**< Pack widgets horizontally */
    };

    virtual void layout();

	/** 
	 * Get the number of extra pixels of blank space that are added between each child widgets.
	 */
    int spacing() const { return layout_spacing(); }
	
	/**
	 * Set the number of extra pixels of blank space that are added between each child widgets.
	 * @param i pixels
	 */
    void spacing(int i) { layout_spacing(i); }
};

#endif
