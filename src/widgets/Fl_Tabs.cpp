/***************************************************************************
                          Fl_Tabs.cpp  -  description
                             -------------------
    begin                : Tue Feb 26 2002
    version              : 0.98, Jun 1 2002
    copyright            : (C) 2002 by Alexey S.Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   under LGPL
 *                                                                         *
 ***************************************************************************/

#include <efltk/fl_math.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Tabs.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Scroll.h>
#include <efltk/Fl_Image.h>
#include <string.h>
#include <stdio.h>

#define BORDER 10
#define TABSLOPE 5
#define EXTRASPACE 2

class Fl_Tab_Info {
public:
    int       m_x, m_y, m_width, m_height;
    int       m_id;
    Fl_Widget *m_widget;
public:
    Fl_Tab_Info(int x,int y,int width,int height,int id,Fl_Widget *widget);
    Fl_Tab_Info(const Fl_Tab_Info& );
    bool includes_coord(int x,int y);
    Fl_Widget *widget() { return m_widget; }
};

class Fl_Tabs_List {
    friend class Fl_Tabs_Matrix;
    friend class Fl_Tabs;
private:
    Fl_Tab_Info   *m_list[32];
    unsigned       m_count;
    int            m_active;
protected:
    void      sety(int ycoord);
    Fl_Tab_Info *tab_at(int x,int y) const;
    Fl_Tab_Info *tab_for(Fl_Widget *group) const;
    void      extend(int width);
public:
    Fl_Tabs_List();
    ~Fl_Tabs_List() { clear(); }
    void     add(Fl_Tab_Info *ti);
    void     clear();
    unsigned count()                          { return m_count; }
    Fl_Tab_Info * operator [] (unsigned index)   { return m_list[index]; }
    int       active()                        { return m_active; }
    void      active(int activeIndex)         { m_active = activeIndex; }
    Fl_Tab_Info *active_tab();
    int       index_of(Fl_Tab_Info *ti);
};

class Fl_Tabs_Matrix {
    friend class Fl_Tabs;
private:
    unsigned            m_count;
    Fl_Tabs_List *m_list[16];
    Fl_Tabs      *m_multiTabs;
protected:
    Fl_Tab_Info        *m_activeTab;

    Fl_Tab_Info *tab_at(int x,int y) const;
    Fl_Tab_Info *tab_for(Fl_Widget *group) const;
public:
    Fl_Tabs_Matrix(Fl_Tabs * multiTabs) { m_count = 0; m_activeTab = 0L; m_multiTabs = multiTabs; }
    ~Fl_Tabs_Matrix() { clear(); }
    void     add(Fl_Tabs_List *tl);
    void     clear();
    unsigned count() { return m_count; }
    Fl_Tabs_List * operator [] (unsigned index) { return (Fl_Tabs_List *)m_list[index]; }

    void     activate(int rowIndex,int tabIndex,Fl_Align tmode);
    void     activate(Fl_Tab_Info *,Fl_Align tmode);
};

Fl_Tab_Info::Fl_Tab_Info(int tx,int ty,int twidth,int theight,int tid,Fl_Widget *twidget) {
    m_x = tx;
    m_y = ty;
    m_width = twidth;
    m_height = theight;
    m_id = tid;
    m_widget = twidget;
}

Fl_Tab_Info::Fl_Tab_Info(const Fl_Tab_Info& ti) {
    m_x = ti.m_x;
    m_y = ti.m_y;
    m_width = ti.m_width;
    m_height = ti.m_height;
    m_id = ti.m_id;
    m_widget = ti.m_widget;
}

bool Fl_Tab_Info::includes_coord(int xx,int yy) {
    return ( xx > m_x && xx < m_x + m_width && yy > m_y && yy < m_y + m_height );
}

Fl_Tabs_List::Fl_Tabs_List()  {
    m_active = -1;
    m_count = 0;
}

void Fl_Tabs_List::extend(int width) {
    if (!m_count) return;
    Fl_Tab_Info *ti = m_list[m_count-1];
    int totalWidth = ti->m_x + ti->m_width;
    int extendX = (width - totalWidth) / (int)m_count;
    for (unsigned t=0; t < m_count; t++) {
        Fl_Tab_Info *ti = m_list[t];
        ti->m_x += int(t) * extendX;
        ti->m_width += int( extendX );
    }
   // step 2 - finalizing
    totalWidth = ti->m_x + ti->m_width;

    extendX = width - totalWidth;
    ti->m_width += extendX;
}

Fl_Tab_Info * Fl_Tabs_List::tab_for(Fl_Widget *widget) const {
    for (unsigned i=0; i < m_count; i++) {
        Fl_Tab_Info *ti = m_list[i];
        if (ti->m_widget == widget) return ti;
    }
    return 0L;
}

void Fl_Tabs_List::add(Fl_Tab_Info *ti) {
    if (m_count >= 32) return;
    m_list[m_count] = ti;
    m_count++;
}

void Fl_Tabs_List::clear() {
    for (unsigned i=0; i < m_count; i++) {
        delete m_list[i];
    }
    m_count = 0;
}

Fl_Tab_Info *Fl_Tabs_List::active_tab() {
    if (m_active == -1) return 0;
    return m_list[m_active];
}

void Fl_Tabs_List::sety(int ycoord) {
    for (unsigned i=0; i < m_count; i++) {
        m_list[i]->m_y = ycoord;
    }
}

Fl_Tab_Info *Fl_Tabs_List::tab_at(int x,int y) const {
    for (unsigned i=0; i < m_count; i++) {
        Fl_Tab_Info * tab = m_list[i];
        if (tab->includes_coord(x,y))
            return tab;
    }
    return 0;
}

int Fl_Tabs_List::index_of(Fl_Tab_Info *ti) {
    for (unsigned i=0; i < m_count; i++) {
        Fl_Tab_Info * tab = m_list[i];
        if (tab == ti)
            return i;
    }
    return -1;
}

void Fl_Tabs_Matrix::add(Fl_Tabs_List *tl) {
    if (m_count >= 8) return;
    m_list[m_count] = tl;
    m_count++;
}

void Fl_Tabs_Matrix::clear() {
    for (unsigned i=0; i < m_count; i++) {
        delete m_list[i];
    }
    m_count = 0;
}

Fl_Tab_Info * Fl_Tabs_Matrix::tab_for(Fl_Widget *group) const {
    for (unsigned i=0; i < m_count; i++) {
        Fl_Tab_Info *ti = m_list[i]->tab_for(group);
        if (ti)
            return ti;
    }
    return 0L;
}

void Fl_Tabs_Matrix::activate(int rowIndex,int tabIndex,Fl_Align tmode) {
   // find currently active row
    if (!m_count) return;

    unsigned activeRowIndex = 0;
    if (tmode != FL_ALIGN_BOTTOM)
        activeRowIndex = m_count - 1;

    Fl_Tabs_List *activeRow = (Fl_Tabs_List *)m_list[activeRowIndex];
    Fl_Tabs_List *row = (Fl_Tabs_List *)m_list[rowIndex];
    int ycoordActiveRow = (*activeRow)[0]->m_y;
    int ycoordRow = (*row)[0]->m_y;

    if (m_count > 1)
        row->sety(ycoordActiveRow);
    row->active(tabIndex);
    if ((int)activeRowIndex != rowIndex) {
      // move row coordinates for the currently active row
        if (m_count > 1)
            activeRow->sety(ycoordRow);
        activeRow->active(-1);
      // swap the rows visually
        m_list[rowIndex] = activeRow;
        m_list[activeRowIndex] = row;
    }
    m_activeTab = row->active_tab();
}

void Fl_Tabs_Matrix::activate(Fl_Tab_Info *ti,Fl_Align tmode) {
   // find tab's row
    for (unsigned i=0; i < m_count; i++) {
        int tabIndex = m_list[i]->index_of(ti);
        if (tabIndex > -1) {
            activate(i,tabIndex,tmode);
            break;
        }
    }
}

Fl_Tab_Info *Fl_Tabs_Matrix::tab_at(int x,int y) const {
    for (unsigned i=0; i < m_count; i++) {
        Fl_Tab_Info *tab = m_list[i]->tab_at(x,y);
        if (tab)
            return tab;
    }
    return 0;
}

inline
int sign(int v) {
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

struct Point {
    int x;
    int y;
};

void draw3Dshape(int pointsCount,Point *points,Fl_Color fillColor,Fl_Boxtype boxType) {
    int i;
    Point *p = points;

    fl_color(fillColor);
    fl_newpath();
    for (i = 0; i < pointsCount; i++) {
        fl_vertex(p->x,p->y);
        p++;
    }
    fl_closepath();
    fl_fill();

    int  border = boxType->dx();

    Fl_Color upColor = FL_BLACK;
    Fl_Color upColor2 = fillColor;
    Fl_Color downColor2 = fillColor;
    Fl_Color downColor =  FL_BLACK;

    if ( boxType == FL_THIN_UP_BOX || boxType == FL_UP_BOX ) {
        upColor = fl_lighter(fillColor);
        upColor2 = fl_lighter(fl_lighter(upColor));
        downColor2 = fl_darker(fillColor);
        downColor =  fl_darker(fl_darker(downColor2));
    } else
        if ( boxType == FL_THIN_DOWN_BOX || boxType == FL_DOWN_BOX ) {
            downColor = fl_lighter(fillColor);
            downColor2 = fl_lighter(fl_lighter(downColor));
            upColor2 = fl_darker(fillColor);
            upColor =  fl_darker(fl_darker(upColor2));
        }

    if (border < 2) {
        downColor = downColor2;
        upColor = upColor2;
    }

    Point *p1 = points;
    Point *p2 = points + 1;
    int    lastx = 0, lasty = 0;
    for (i = 1; i < pointsCount; i++) {
        int dx = p2->x - p1->x;
        int dy = p2->y - p1->y;
        int x1 = p1->x;
        int y1 = p1->y;
        int x2 = p2->x;
        int y2 = p2->y;

        Fl_Color clr;
        if ( (dx >= 0 && fabs(dy) <= dx) || (dy <= 0 && fabs(dx) <= -dy) )
            clr = upColor;
        else  clr = downColor;

        fl_color(clr);
        fl_line(x1,y1,x2,y2);

        if (border > 1) {
            if (clr == upColor)
                fl_color(upColor2);
            else  fl_color(downColor2);

            switch (sign(dx)) {
                case 1:  // dx > 0
                    switch (sign(dy)) {
                        case  1: // dy > 0
                            y1++;
                            x2--;
                            break;
                        case -1: // dy < 0
                            x1++;
                            y2++;
                            break;
                        default: // dy == 0
                            y1++;
                            y2++;
                            x1++;
                            x2--;
                            break;
                    }
                    break;
                case -1:  // dx < 0
                    switch (sign(dy)) {
                        case  1: // dy > 0
                            x1--;
                            y2--;
                            break;
                        case -1: // dy < 0
                            y1--;
                            x2++;
                            break;
                        default: // dy == 0
                            y1--;
                            y2--;
                            x1--;
                            x2++;
                            break;
                    }
                    break;
                case 0:  // dx == 0
                    switch (sign(dy)) {
                        case  1: // dy > 0
                            x1--;
                            x2--;
                            y1++;
                            y2--;
                            break;
                        case -1: // dy < 0
                            x1++;
                            x2++;
                            break;
                    }
                    break;
            }
            if (i > 1 && lastx != x1 && lasty != y1)
                fl_line(lastx,lasty,x1,y1);
            fl_line(x1,y1,x2,y2);
            lastx = x2;
            lasty = y2;
        }
        p1++;
        p2++;
    }
}

#define CORNER TABSLOPE-1

#define FL_TAB_BOX_UP         0x01000000
#define FL_TAB_BOX_DOWN       0x02000000
#define FL_TAB_BOX_THICK      0x04000000

#define C(c) fl_color(c + (FL_GRAY_RAMP-'A'));

class MultiTabBox : public Fl_Flat_Box {
public:
    MultiTabBox() : Fl_Flat_Box(0) { dx_=dy_=2; dw_=dh_=4;}
    void draw(int x1,int y1,int w,int h, Fl_Color color, Fl_Flags f) const {
        fl_color(color);
        int x2 = x1 + w - 1;
        int y2 = y1 + h - 1;
        Fl_Boxtype tab_box_type = FL_FLAT_BOX;
        if (f&FL_TAB_BOX_UP) {
            if (f&FL_TAB_BOX_THICK)
                tab_box_type = FL_UP_BOX;
            else  tab_box_type = FL_THIN_UP_BOX;
        } else {
            if (f&FL_TAB_BOX_THICK)
                tab_box_type = FL_DOWN_BOX;
            else  tab_box_type = FL_THIN_DOWN_BOX;
        }

        if (f&FL_ALIGN_TOP) {
            if (f&FL_SELECTED)
                fl_rectf(x1+3,y2,w-4,dy()+1);

            fl_push_clip(x1,y1,w,h-1);
            Point points[] = {
                { x1+2, y2 + 4 },
                { x1+2, y1+TABSLOPE },
                { x1+2+TABSLOPE, y1 },
                { x1+w-1, y1 },
                { x2, y2 + 4 }
            };
            draw3Dshape(5,points,color,tab_box_type);
            fl_pop_clip();
        }
        else if (f&FL_ALIGN_BOTTOM) {
            int extra_h = 0;
            if (f&FL_SELECTED) {
                fl_rectf(x1+3,y1-dy(),w-5,dy());
                extra_h = 1;
            }

            fl_push_clip(x1,y1,w,h);
            Point points[] = {
                { x2-1, y1-2 },
                { x2-1, y2 },
                { x1+2+TABSLOPE, y2 },
                { x1+2, y2-TABSLOPE },
                { x1+2, y1-2 }
            };
            draw3Dshape(5,points,color,tab_box_type);
            fl_pop_clip();
        }
        else if (f&FL_ALIGN_RIGHT) {
            if (f & FL_SELECTED)
                fl_rectf(x1-dx(),y1+dy()/2,dx(),h-dy());

            fl_push_clip(x1,y1,w,h);
            Point points[] = {
                { x1-2, y1 },
                { x2, y1 },
                { x2, y2-TABSLOPE },
                { x2-TABSLOPE, y2 },
                { x1-2, y2 }
            };
            draw3Dshape(5,points,color,tab_box_type);
            fl_pop_clip();
        }
        else {
            if (f & FL_SELECTED)
                fl_rectf(x2,y1+dy()/2,dh(),h-dy());
            fl_push_clip(x1,y1,w,h);
            Point points[] = {
                { x2+3, y2 },
                { x1+TABSLOPE, y2 },
                { x1, y2-TABSLOPE },
                { x1, y1 },
                { x2+3, y1 }
            };
            draw3Dshape(5,points,color,tab_box_type);
            fl_pop_clip();
        }
    }
};
MultiTabBox multitab_box;

class MultiTabFocusBox : public Fl_Flat_Box {
public:
    MultiTabFocusBox() : Fl_Flat_Box(0) { }
    void draw(int x1,int y1,int w,int h, Fl_Color color, Fl_Flags f) const    {
        int x2 = x1 + w - 1;
        int y2 = y1 + h - 1;
        fl_line_style(FL_DOT);
        fl_color(color);
        if (f&FL_ALIGN_TOP) {
            int cX=x1+CORNER;
            int cY=y1+CORNER;
            fl_line(x1, y2, x1, cY);
            fl_line(x1, cY, cX, y1);
            fl_line(cX, y1, x2, y1);
            fl_line(x2, y1, x2, y2);
            fl_line(x2, y2, x1, y2);
        }
        else if (f&(FL_ALIGN_BOTTOM|FL_ALIGN_LEFT)) {
            int cX=x1+CORNER;
            int cY=y2-CORNER+2;
            fl_line(x1, y1, x1, cY);
            fl_line(x1, cY, cX, y2);
            fl_line(cX, y2, x2, y2);
            fl_line(x2, y2, x2, y1);
            fl_line(x1, y1, x2, y1);
        } else {
            int cX=x2-CORNER;
            int cY=y2-CORNER;
            fl_line(x1, y1, x2, y1);
            fl_line(x2, y1, x2, cY);
            fl_line(x2, cY, cX, y2);
            fl_line(cX, y2, x1, y2);
            fl_line(x1, y2, x1, y1);
        }
        fl_line_style(0);
    }
};
MultiTabFocusBox multitab_focusbox;

static void revert(Fl_Style* s)
{
    s->box = FL_THIN_UP_BOX;
    s->button_box = &multitab_box;
    s->focus_box = &multitab_focusbox;
    s->color = FL_GRAY;
    s->selection_color = FL_GRAY;
}

static Fl_Named_Style style("Tabs", revert, &Fl_Tabs::default_style);
Fl_Named_Style* Fl_Tabs::default_style = &::style;

// ctor initializer - used in both ctors
void Fl_Tabs::ctor_init() {
    m_tabsMatrix = new Fl_Tabs_Matrix(this);
    push_ = 0;
    m_showTabs = true;
    m_autoColorIndex = 0;
    m_tabsMode = FL_ALIGN_TOP;
    m_tabsWidth = m_tabsHeight = 0;
    m_rowHeight = 0;
    style(default_style);
}

// Traditional ctor
Fl_Tabs::Fl_Tabs(int X,int Y,int W, int H,const char *l)
: Fl_Group(X,Y,W,H,l) {
    ctor_init();
}

// New style ctor
Fl_Tabs::Fl_Tabs(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Group(l,layout_size,layout_al,label_w) {
    ctor_init();
}

// dtor
Fl_Tabs::~Fl_Tabs() {
    delete m_tabsMatrix;
}

// this is used by fluid to pick tabs:
Fl_Widget *Fl_Tabs::which(int event_x, int event_y) {
    Fl_Tab_Info *tab = m_tabsMatrix->tab_at(event_x-x(),event_y-y());
    if (tab) {
        m_tabsMatrix->activate(tab,m_tabsMode);
        return tab->m_widget;
    }
    return 0;
}

int focusFirstAvailableChild(Fl_Group *g) {
    for (int i = 0; i < g->children(); i++) {
        Fl_Widget *w = g->child(i);
        if (w->visible() && w->take_focus()) {
            g->redraw();
            return 1;
        }
    }
    return 0;
}

int focusLastAvailableChild(Fl_Group *g) {
    for (int i = g->children()-1; i >= 0; i--) {
        Fl_Widget *w = g->child(i);
        if (w->visible() && w->take_focus()) {
            g->redraw();
            return 1;
        }
    }
    return 0;
}

int Fl_Tabs::handle(int event) {
    int            i;
    Fl_Tab_Info   *tab;

    int ex = Fl::event_x();
    int ey = Fl::event_y();
    Fl_Group *selected = (Fl_Group *)this->value();

    switch (event) {

        case FL_PUSH:
            switch (m_tabsMode) {
                case FL_ALIGN_TOP:  if (ey > m_tabsHeight) goto DEFAULT;
                    break;
                case FL_ALIGN_LEFT: if (ex > m_tabsWidth) goto DEFAULT;
                    break;
                case FL_ALIGN_RIGHT: if (ex < w()-m_tabsWidth) goto DEFAULT;
                    break;
                case FL_ALIGN_BOTTOM: if (ey < h() - m_tabsHeight) goto DEFAULT;
                    break;
                default:
                    break;
            }

      //if (Fl::visible_focus()) 
            Fl::focus(this);
            tab = m_tabsMatrix->tab_at(ex,ey);
            if (tab)
                value(tab->m_widget);
            return 1;

        case FL_FOCUS:
        case FL_UNFOCUS:
            redraw();
            return 1;

        case FL_KEYBOARD:
            switch (Fl::event_key()) {
                case FL_Right:
                case FL_Down:
                    return focusFirstAvailableChild(selected);
                case FL_Left:
                case FL_Up:
                    return focusLastAvailableChild(selected);
                default:
                    Fl_Group::handle(event);
            }
            return Fl_Group::handle(event);

        case FL_SHORTCUT:
            if (Fl::event_key()==FL_Tab && Fl::event_state(FL_CTRL)) {
                bool backwards = Fl::event_state(FL_SHIFT);
                for (i = children()-1; i>0; i--) if (child(i)->visible()) break;
                if (backwards) {
                    i = i ? i-1 : children()-1;
                } else {
                    i++; if (i >= children()) i = 0;
                }
                value(child(i)); do_callback(event);
                return 1;
            }
            if (!selected) return 0;
            if (selected->send(event)) return 1;
            if (!contains(Fl::focus())) return 0;
            switch (navigation_key()) {
                case FL_Right:
                case FL_Down:
                    if (focus() < 0 && selected) return selected->take_focus();
                    else return 0;
                case FL_Left:
                case FL_Up:
                    if (focus() >= 0) {Fl::focus(this); return 1;}
                    else return 0;
                default:
                    return 0;
            }
        default:
        DEFAULT:
            return Fl_Group::handle(event);
    }
}

int Fl_Tabs::push(Fl_Widget *o) {
    if (push_ == o) return 0;
    if (push_ && !push_->visible() || o && !o->visible())
        redraw(FL_DAMAGE_EXPOSE);
    push_ = o;
    return 1;
}

Fl_Widget* Fl_Tabs::value() {
    Fl_Widget* v = 0;
    for (int i = 0; i < children(); i++) {
        Fl_Widget* o = child(i);
        if (o->visible()) {
            v = o;
            color(v->color());
        }
    }
    return v;
}

// Setting the value hides all other children, and makes this one
// visible, iff it is really a child:
int Fl_Tabs::value(Fl_Widget *newvalue) {
    int ret = 0;
    for (int i = 0; i < children(); i++) {
        Fl_Widget* o = child(i);
        if (o == newvalue) {
            if (!o->visible()) ret = 1;
            o->show();
        } else {
            o->hide();
        }
    }
    relayout();
    return ret;
}

enum {LEFT, RIGHT, SELECTED};

void Fl_Tabs::draw() {
    Fl_Widget *v = value();
    if (damage() & FL_DAMAGE_ALL) { // redraw the entire thing:
        fl_push_clip(0,0,this->w(),this->h());
        if (v) draw_child(*v);
        parent()->draw_group_box();
        switch (m_tabsMode) {
            case FL_ALIGN_BOTTOM:
                box()->draw(0, 0, this->w() - m_tabsWidth, this->h() - m_tabsHeight, v ? v->color() : color(), FL_INVISIBLE);
                break;
            case FL_ALIGN_LEFT:
                box()->draw(m_tabsWidth, 0, this->w() - m_tabsWidth, this->h() - m_tabsHeight, v ? v->color() : color(), FL_INVISIBLE);
                break;
            default:
                box()->draw(0, m_tabsHeight, this->w() - m_tabsWidth, this->h() - m_tabsHeight, v ? v->color() : color(), FL_INVISIBLE);
                break;
        }
        fl_pop_clip();
    }                            // redraw the child
    else {
        if (v) update_child(*v);
    }

    Fl_Flags button_box_flags = m_tabsMode;
    Fl_Flags tab_flags = 0L;
    if ( box() == FL_THIN_UP_BOX || box() == FL_UP_BOX ) {
        button_box_flags |= FL_TAB_BOX_UP;
        if (box() == FL_UP_BOX)
            button_box_flags |= FL_TAB_BOX_THICK;
    } else
        if ( box() == FL_THIN_DOWN_BOX || box() == FL_DOWN_BOX ) {
            button_box_flags |= FL_TAB_BOX_DOWN;
            if (box() == FL_DOWN_BOX)
                button_box_flags |= FL_TAB_BOX_THICK;
        }

    if (damage() & (FL_DAMAGE_EXPOSE|FL_DAMAGE_ALL)) {
        unsigned rowCount = m_tabsMatrix->count();
        if (m_tabsMode==FL_ALIGN_BOTTOM) {
            for (int r = rowCount - 1; r >= 0; r--) {
                Fl_Tabs_List& row = *(*m_tabsMatrix)[r];
                int rowTabCount = row.count();
                for (int t = 0; t < rowTabCount; t++) {
                    Fl_Tab_Info *tab = row[t];
                    tab_flags = button_box_flags;
                    if (row.active()==t)
                        tab_flags |= FL_SELECTED;
                    draw_tab(tab,tab_flags);
                }
            }
        } else {
            for (unsigned r = 0; r < rowCount; r++) {
                Fl_Tabs_List& row = *(*m_tabsMatrix)[r];
                int rowTabCount = row.count();
                for (int t = 0; t < rowTabCount; t++) {
                    Fl_Tab_Info *tab = row[t];
                    tab_flags = button_box_flags;
                    if (row.active()==t)
                        tab_flags |= FL_SELECTED;
                    draw_tab(tab,tab_flags);
                }
            }
        }
    }
}

void Fl_Tabs::draw_tab(Fl_Tab_Info *tab,Fl_Flags flags) {
    if (!m_showTabs) return;

    Fl_Color widgetColor = tab->m_widget->color()==FL_INVALID_COLOR ? parent()->color() : tab->m_widget->color();
    Fl_Color tabColor = ! (flags & FL_SELECTED) ? fl_color_average(widgetColor, FL_BLACK, 0.85f) : widgetColor;

    // Draw the background of the tab
    int x1 = tab->m_x;
    int y1 = tab->m_y;
    int y2 = m_tabsHeight;
    int s_offset = 0;
    if (flags & FL_SELECTED)
        s_offset = 1;

    switch (m_tabsMode) {
        case FL_ALIGN_TOP:
            button_box()->draw(tab->m_x,tab->m_y,tab->m_width,m_tabsHeight-tab->m_y,tabColor,flags);
            break;

        case FL_ALIGN_BOTTOM:
            y1 = h() - m_tabsHeight - s_offset;
            y2 = tab->m_y + tab->m_height;
            button_box()->draw(tab->m_x,y1,tab->m_width,y2-y1+1,tabColor,flags);
            break;

        case FL_ALIGN_RIGHT:
        case FL_ALIGN_LEFT:
            button_box()->draw(tab->m_x,y1,tab->m_width,tab->m_height,tabColor,flags);
            break;

        default:
            break;
    }

    Fl_Align labelAlign = FL_ALIGN_CENTER;
    int      labelLeft = 0;

    int wt = 0, ht = 0;
    int focus_dx = box()->dx();
    int focus_dw = box()->dw() + 2;
    int focus_dy = box()->dy();
    int focus_dh = box()->dh() + 2;

    fl_font(label_font(),label_size());
    tab->m_widget->measure_label(wt,ht);

    switch (m_tabsMode) {
        case FL_ALIGN_TOP:
            labelLeft = x1 + 4 + (tab->m_width-6) / 2 - wt / 2;
            focus_dx += 2;
            focus_dw += 1;
            focus_dh -= box()->dw();
            break;

        case FL_ALIGN_BOTTOM:
            labelLeft = x1 + 4 + (tab->m_width-6) / 2 - wt / 2;
            focus_dx += 2;
            focus_dw += 1;
            focus_dy -= box()->dy();
            focus_dh -= box()->dh();
            break;

        case FL_ALIGN_RIGHT:
            labelAlign = FL_ALIGN_LEFT;
            labelLeft = x1 + box()->dx();
            focus_dh -= box()->dy();
            focus_dx -= box()->dx();
            focus_dw -= box()->dw();
            break;

        case FL_ALIGN_LEFT:
            labelAlign = FL_ALIGN_LEFT;
            labelLeft = x1 + 4 + box()->dx();
            focus_dw -= box()->dw();
            focus_dh -= box()->dy();
            break;

        default:
            break;
    }
    Fl_Widget *widget = tab->m_widget;
    Fl_Image *image = widget->image();
    if (image) {
        labelLeft = x1 + 7;

        int imw = image->width();
        int imh = image->height();
        image->draw(labelLeft,tab->m_y+tab->m_height/2-imh/2,imw,imh);
        labelLeft += imw + 3;
    }
    int yt = tab->m_y + tab->m_height / 2 - ht / 2;
    widget->label_type()->draw(widget->label().c_str(), labelLeft, yt, wt, ht, widget->label_color(), 0);
    if (Fl::focus() == this && (flags & FL_SELECTED))
        focus_box()->draw(tab->m_x+focus_dx,tab->m_y+focus_dy,tab->m_width-focus_dw,tab->m_height-focus_dh,0,m_tabsMode | FL_INVISIBLE);
}

void Fl_Tabs::layout()
{
    int wt = 0;
    int i;
    unsigned r;
    int group_x = box()->dx(), group_y = box()->dy();
    int group_w = w() - box()->dw(), group_h = h() - box()->dh();
    int voffset = 0, hoffset = 0;

    Fl_Tab_Info *activeTab = 0L;
    Fl_Widget *activeWidget = 0L;

    if(!(layout_damage() & FL_LAYOUT_WH) || !m_showTabs && value()) {
        if((layout_damage() & FL_LAYOUT_XY)) value()->layout_damage(value()->layout_damage()|FL_LAYOUT_XY);       
        value()->resize(group_x, group_y, group_w, group_h);
        if(value()->layout_damage()) value()->layout();
    }

    Fl_Tabs_Matrix *old_tabsMatrix = m_tabsMatrix;
    m_tabsMatrix = new Fl_Tabs_Matrix(this);

    Fl_Tabs_List *row = new Fl_Tabs_List;
    m_tabsMatrix->add(row);

    fl_font(label_font(),label_size());
    m_tabsWidth = 0;
    int max_wt = 0;
    int max_ht = int(fl_height()+4);
    for (i=0; i<children(); i++) {
        Fl_Widget * group = child(i);
        Fl_Tab_Info *tab = old_tabsMatrix->tab_for(group);
        Fl_Image *glyph = 0L;
        if (tab && tab->m_widget)
            glyph = tab->m_widget->image();
        wt = 0;
        if(!group->label().empty()) {
            wt = int(fl_width(group->label()));
            wt += box()->dw() + 4;
            if (glyph)
                wt += glyph->width();
        }
        if (wt > max_wt) max_wt = wt;
        if (glyph && glyph->height() + 2 > max_ht)
            max_ht = glyph->height() + 2;
    }

    int xpos = 0;
    int ypos = 0;
    int ystep = 0;
    if (m_showTabs) { 
        ystep = max_ht + 4;
        m_rowHeight = ystep;
    }

    switch (m_tabsMode) {
        case FL_ALIGN_BOTTOM:
        case FL_ALIGN_TOP:
            m_tabsWidth = 0;
            m_tabsHeight = 0; // to be determined
            break;

        case FL_ALIGN_RIGHT:
        case FL_ALIGN_LEFT:
            ystep += box()->dh()+3;
            m_rowHeight += box()->dh();
            m_tabsWidth  = max_wt + 6;
            m_tabsHeight = 0;
            ypos = 3;
            if (m_tabsMode == FL_ALIGN_RIGHT)
                xpos = w() - m_tabsWidth;
            break;

        default:
            break;
    }

    for (i=0; i<children(); i++) {
        Fl_Widget *group = child(i);
        wt = 0;

        Fl_Tab_Info *tab = old_tabsMatrix->tab_for(group);
        Fl_Image *glyph = 0L;

        if (tab && tab->m_widget)
            glyph = tab->m_widget->image();

        switch (m_tabsMode) {
            case FL_ALIGN_TOP:
            case FL_ALIGN_BOTTOM:
                if(!group->label().empty())
                    wt = int(fl_width(group->label()));
                wt += 10;
                if (glyph)
                    wt += glyph->width() + 4;
                if (xpos + wt > w()) {
                    if (row->count() > 0) {
                        xpos = 0;
                        ypos += ystep;
                        row = new Fl_Tabs_List;
                        m_tabsMatrix->add(row);
                    } else {
                        wt = w() - xpos;
                    }
                }
                tab  = new Fl_Tab_Info(xpos,ypos,wt,m_rowHeight,i, group);
                row->add(tab);
                if (group->visible())
                    m_tabsMatrix->m_activeTab = tab;
                xpos += wt;
                break;
            case FL_ALIGN_LEFT:
            case FL_ALIGN_RIGHT:
                if (ypos + ystep < h()) {
                    tab  = new Fl_Tab_Info(xpos,ypos,m_tabsWidth,m_rowHeight,i, group);
                    row->add(tab);
                }
                ypos += ystep;
                break;

            default:
                break;
        }

        if (!tab) break;

        if (group->visible()) {
            activeTab = tab;
            activeWidget = group;
        }

    }
    delete old_tabsMatrix;

    switch (m_tabsMode) {
        case FL_ALIGN_TOP:
            m_tabsHeight = ypos + ystep;
            m_tabsMatrix->activate(activeTab,m_tabsMode);
            extend_tabs();
            group_y = m_tabsHeight + box()->dy();
            break;
        case FL_ALIGN_BOTTOM:
            m_tabsHeight = ypos + ystep;
            voffset = h() - m_tabsHeight;
            for (r = 0; r < m_tabsMatrix->count(); r++) {
                Fl_Tabs_List *row = (*m_tabsMatrix)[r];
                for (unsigned t = 0; t < row->count(); t++) {
                    Fl_Tab_Info *tab = (*row)[t];
                    tab->m_y += voffset;
                    tab->m_height--;
                }
            }
            m_tabsMatrix->activate(activeTab,m_tabsMode);
            extend_tabs();
            group_y = box()->dy();
            voffset = 0;
            break;
        case FL_ALIGN_RIGHT:
            m_tabsMatrix->activate(activeTab,m_tabsMode);
            break;
        case FL_ALIGN_LEFT:
            hoffset = m_tabsWidth;
            m_tabsMatrix->activate(activeTab,m_tabsMode);
            break;

        default:
            break;
    }

    group_w -= m_tabsWidth;
    group_h -= m_tabsHeight;

   // Only need to resize visible tab.
    if(activeWidget) {
        if((layout_damage() & FL_LAYOUT_XY)) activeWidget->layout_damage(activeWidget->layout_damage()|FL_LAYOUT_XY);       
        activeWidget->resize(group_x+hoffset, group_y+voffset, group_w, group_h);
        if(activeWidget->layout_damage()) activeWidget->layout();
    }

    Fl_Widget::layout();
}

void Fl_Tabs::extend_tabs() {
    unsigned cnt = m_tabsMatrix->count();
    if (cnt > 1)
        for (unsigned r = 0; r < cnt; r++) {
            (*m_tabsMatrix)[r]->extend(w()-2);
        }
}

const Fl_Color Fl_Tabs::auto_color_table[16] = {
    fl_rgb(0xB0,0xD0,0xD0),
    fl_rgb(0xC0,0xC0,0xE0),
    fl_rgb(192,176,160),
    fl_rgb(0xD0,0xD0,0xB0),
    fl_rgb(240,190,190),
    fl_rgb(0xC0,0xB0,0xC0),
    fl_rgb(0xC0,0xA0,0x90),
    fl_rgb(0xD0,0xD0,0xE8),
    fl_rgb(0xE8,0xC0,0xC0),
    fl_rgb(0xC0,0xE8,0xC0),
    fl_rgb(0xE8,0xC0,0xE8),
    fl_rgb(0xE0,0xE0,0xC0),
    fl_rgb(0xC0,0xE0,0xE0),
    fl_rgb(0xE0,0xC0,0xE0),
    fl_rgb(0xA0,0xB8,0xA0),
    fl_rgb(0xB8,0xC0,0xE8)
};

Fl_Scroll* Fl_Tabs::create_new_scroll(const char *label) 
{
    begin();
    Fl_Scroll *scroll = new Fl_Scroll(0,0,w(),h(),label);
	scroll->color(color());
    end();
    return scroll;
}

Fl_Group* Fl_Tabs::create_new_group(const char *label) 
{
    begin();
    Fl_Group *group = new Fl_Group(0,0,w(),h(),label);
	group->color(color());
    end();
    return group;
}

Fl_Scroll* Fl_Tabs::new_scroll(const char *label,bool autoColor) 
{
    Fl_Scroll* group = create_new_scroll(label);
    group->box(FL_FLAT_BOX);

    if(children() > 1)
        group->hide();

    if (autoColor) {
        Fl_Color clr = auto_color_table[m_autoColorIndex&0xF];
        group->color( clr );
        m_autoColorIndex++;
    }

    int rowNumber = m_tabsMatrix->count()-1;
    Fl_Tabs_List *row = 0L;
    if (rowNumber < 0) {
        row = new Fl_Tabs_List();
        m_tabsMatrix->add(row);
    } else {
        row = (*m_tabsMatrix)[rowNumber];
    }
    row->add(new Fl_Tab_Info(0,0,0,0,0,group));

    group->begin();
    return group;
}

Fl_Group* Fl_Tabs::new_group(const char *label,bool autoColor) 
{
    Fl_Group* group = create_new_group(label);
    group->box(FL_FLAT_BOX);

    if(children() > 1)
        group->hide();

    if (autoColor) {
        Fl_Color clr = auto_color_table[m_autoColorIndex&0xF];
        group->color( clr );
        m_autoColorIndex++;
    }

    int rowNumber = m_tabsMatrix->count()-1;
    Fl_Tabs_List *row = 0L;
    if (rowNumber < 0) {
        row = new Fl_Tabs_List();
        m_tabsMatrix->add(row);
    } else {
        row = (*m_tabsMatrix)[rowNumber];
    }
    row->add(new Fl_Tab_Info(0,0,0,0,0,group));

    group->begin();
    return group;
}

Fl_Group* Fl_Tabs::last_tab() {
   // find the last children
    int n = children() - 1;
    if (n < 0)
        return 0L;
    else  return (Fl_Group*) child(n);
}

void Fl_Tabs::show_tabs(bool st) {
    if (m_showTabs != st) {
        m_showTabs = st;
        if (parent())
            parent()->redraw(FL_DAMAGE_ALL);
    }
}

void Fl_Tabs::tabs_mode(Fl_Align tm) {
    if (m_tabsMode != tm) {
        m_tabsMode = tm;
        relayout();
        if (parent())
            parent()->redraw(FL_DAMAGE_ALL);
    }
}
