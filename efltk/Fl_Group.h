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

#ifndef _FL_GROUP_H_
#define _FL_GROUP_H_

#include "Fl_Widget.h"
#include "Fl_Data_Source.h"
#include "Fl_Widget_List.h"
#include "Fl_Int_List.h"

/**
 * The Fl_Group class is the EFLTK container widget. 
 * It maintains an array of child widgets. These children can themselves be any widget including Fl_Group, nesting groups allows much more control over layout and resize behavior. 
 * Nested groups are also necessary to group radio buttons together. 
 *
 * By default Fl_Group preserves the positions and sizes of all it's children, 
 * they do not move no matter what sizes or other children are added or removed.
 *
 * Setting resizable() will change the layout behavior so that it responds to resizing by moving or resizing the children to fit. See below for details.
 *
 * You may want to use an Fl_Pack or a Fl_Scroll to get other common layout behavior that can respond to changes in the sizes of child widgets.
 * 
 * The most-used subclass of Fl_Group is Fl_Window, all the rules about resizing apply to windows. Setting resizable() on a window will allow the user to resize it. 
 * If you want different behavior (such as from Fl_Pack) for your window you should make the window have that as a single resizable child that fills it.
 *
 * Fl_Menu_ is a subclass and thus all menus and browsers are groups and the items in them are widgets.
 *
 * EFLTK have also addiotinal layout_align() functions, which allows you set automatic widget resizing.
 * @see layout_align(Fl_Align)
 */
class FL_API Fl_Group : public Fl_Widget {
public:

    /** Creates new group widget using the given position, size, and label string. */
    Fl_Group(int x, int y, int w, int h, const char *l=0);

    /** Creates new group widget using the label, size, alignment, and label width. */
    Fl_Group(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=-1);

    /**
     * The destructor also deletes all the children. 
     * This allows a whole tree to be deleted at once, without having to keep a pointer to all the children in the user code. 
     * A kludge has been done so the Fl_Group and all of it's children can be automatic (local) variables, 
     * but you must declare the Fl_Group first, so that it is destroyed last. 
     */
    virtual ~Fl_Group();

    /** Returns how many child widgets the group has. */
    int children() const { return m_array.size(); }

    /** Returns a child, n >= 0 &n < children(). <i>No range checking is done!</i> */
    Fl_Widget* child(int n) const { return m_array[n]; }

    /** Returns Fl_Widget_List of group */
    Fl_Widget_List &array() { return m_array; }

    /** 
     * Draw the background. If FL_DAMAGE_EXPOSE is on, widgets are expected
     * to completely fill their rectangle. To allow non-rectangular widgets
     * to appear to work, a widget can call this (with the clip region set)
     * to draw the area of it's parent that is visible behind it.
     */
    void draw_group_box() const;

    virtual void preferred_size(int &w, int &h) const { }
    virtual void draw();
    virtual void layout();
    virtual int handle(int);

    /**
     * begin() sets the current group so you can build the widget tree by just constructing the widgets. 
     * begin() is automatically called by the constructor for Fl_Group (and thus for Fl_Window as well). begin() is exactly the same as current(this). 
     * <i>Don't forget to end() the group or window!</i>
     */
    virtual void begin() { Fl_Group::m_current = this; }

    /**
     * end() is exactly the same as current(this->parent()). Any new widgets added to the widget tree will be added to the parent of the group. 
     */
    virtual void end()   { Fl_Group::m_current = (Fl_Group*)parent(); }

    /*
     * current() returns the currently active group. 
     * @see current(Fl_Group *g)
     */
    static Fl_Group *current() { return Fl_Group::m_current; }

    /** 
     * current() returns the currently active group. 
     * The Fl_Widget constructor automatically does current()->add(widget) if this is not null. 
     * To prevent new widgets from being added to a group, call Fl_Group::current(0). 
     */
    static void current(Fl_Group *g) { Fl_Group::m_current = g; }

    /** Searches the children for w, returns the index of w or of a parent of w that is a child of this. Returns children() if the widget is NULL or not found.  */
    int find(const Fl_Widget *w) const;

    /** Searches the children for w, returns the index of w or of a parent of w that is a child of this. Returns children() if the widget is NULL or not found.  */
    int find(const Fl_Widget &w) const { return find(&w); }

    virtual void clear();

    void insert(Fl_Widget& o, Fl_Widget* before) { insert(o,find(before)); }
    void insert(Fl_Widget&, int index);

    void remove(Fl_Widget& o) { remove(find(o)); }
    void remove(Fl_Widget* o) { remove(find(*o)); }
    void remove(int index);

    void replace(int index, Fl_Widget&);
    void replace(Fl_Widget& old, Fl_Widget& o) { replace(find(old),o); };    

    void add(Fl_Widget& o) { insert(o, children()); }
    void add(Fl_Widget* o) { add(*o); }    

    void resizable(Fl_Widget& o) { m_resizable = &o; }
    void resizable(Fl_Widget* o) { m_resizable = o; }
    Fl_Widget* resizable() const { return m_resizable; }
    void add_resizable(Fl_Widget& o) { m_resizable = &o; add(o); }
    void init_sizes();

    void focus(int i) { m_focus = i; }
    void focus(Fl_Widget* w) { focus(find(w)); }
    int focus() const { return m_focus; }
    static int navigation_key();

    // data source support methods
    void data_source(Fl_Data_Source *ds);
    Fl_Data_Source* data_source() const { return m_data_source; }
    virtual bool load_data(Fl_Data_Source *ds);
    virtual bool save_data(Fl_Data_Source *ds) const;

    uchar layout_spacing() const { return m_layout_spacing; }
    void layout_spacing(const uchar offset) { m_layout_spacing = offset; }

protected:
    void draw_child(Fl_Widget&) const;
    void update_child(Fl_Widget&) const;
    void draw_outside_label(Fl_Widget&) const;
    int* sizes();

private:
    uchar m_layout_spacing;
    int m_focus;

    Fl_Widget_List m_array;
    Fl_Int_List m_sizes; // remembered initial sizes of children

    Fl_Widget *m_resizable;
    Fl_Data_Source *m_data_source;

    static Fl_Group *m_current;
};

// This dummy class can be used in constructors to set the parent
// group to any desired value before creating child widget instances.
class FL_API Fl_End {
public:
    Fl_End() {Fl_Group::current()->end();}
    Fl_End(Fl_Group* g) {Fl_Group::current(g);}
};

#endif
