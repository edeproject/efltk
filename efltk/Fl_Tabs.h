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
 * Author : Alexey Parshin
 * Email  : alexey@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _Fl_Tabs_H_
#define _Fl_Tabs_H_

#include "Fl_Group.h"

class Fl_Scroll;
class Fl_Tabs_Matrix;
class Fl_Tab_Info;

/** Fl_Tabs */
class FL_API Fl_Tabs : public Fl_Group {
    friend class Fl_Tabs_Matrix;
public:
    static Fl_Named_Style* default_style;

    /** Creates new tabs widget using the given position, size, and label string. */
    Fl_Tabs(int x,int y,int w,int h,const char *label = 0);

    /** Creates new tabs widget using the label, size, alignment, and label width. */
    Fl_Tabs(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=-1);

    /** Destructor */
    virtual ~Fl_Tabs();

    Fl_Group* new_group(const char *label);
    Fl_Scroll* new_scroll(const char *label);
    Fl_Group* new_page(const char *label) { return (Fl_Group*)new_scroll(label); }

    Fl_Widget *value();
    int value(Fl_Widget *);

    Fl_Widget *push() const {return push_;}
    int push(Fl_Widget *);

    Fl_Widget *which(int event_x, int event_y);

    void show_tabs(bool st);
    bool show_tabs() { return m_showTabs; }

    void tabs_mode(Fl_Align tm);
    Fl_Align tabs_mode() { return m_tabsMode; }

    virtual void draw();
    virtual void layout();
    virtual int handle(int);

protected:
    bool m_showTabs;
    int  m_tabsWidth;
    int  m_tabsHeight;
    int  m_rowHeight;
    void draw_tab(Fl_Tab_Info *tab, Fl_Flags flags);
    Fl_Group* last_tab();

    void resize_tabs();
    void extend_tabs();

    Fl_Scroll*	create_new_scroll(const char *label);
    Fl_Group*	create_new_group(const char *label);

private:    
    void ctor_init();

    Fl_Widget        *value_;
    Fl_Widget        *push_;
    Fl_Tabs_Matrix   *m_tabsMatrix;
    int               m_autoColorIndex;
    Fl_Align          m_tabsMode;
};

#endif
