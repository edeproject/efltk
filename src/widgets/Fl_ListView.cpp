#include <efltk/Fl_ListView.h>
#include <efltk/Fl_ListView_Item.h>
//#include "FLE_MdiWindow.h"

#define DRAG_DIST 3 //Area to size header
#define TXT_SPACE 2 //Size between txt and img

#define CHECK_WIDGET(w) (w && (w->flags() & FL_LISTVIEW_ITEM) == FL_LISTVIEW_ITEM)
#define SKIP_WIDGET(w) if(!CHECK_WIDGET(w)) continue 

#define SEL(w) ((w->flags() & FL_SELECTED) == FL_SELECTED)

#define LIST ((Fl_ListView *)parent())
#define ITEM(i) ((Fl_ListView_Item *)i)

static void h_revert(Fl_Style* s) {
    s->button_box = FL_UP_BOX;
    s->button_color = FL_GRAY;
    s->color = FL_GRAY;
    //s->button_color = FL_GRAY;
    //s->glyph = ::glyph;
}
static Fl_Named_Style h_style("ListHeader", h_revert, &Fl_ListHeader::default_style);
Fl_Named_Style* Fl_ListHeader::default_style = &::h_style;

Fl_ListHeader::Fl_ListHeader(int X,int Y,int W,int H,const char*l)
    : Fl_Widget(X,Y,W,H,l)
{
    style(default_style);

    cols=0;
    for(int a=0;a<10;a++) { colw[a]=0; colf[a]=FL_ALIGN_LEFT; coli[a]=0;}
}

void Fl_ListHeader::draw()
{
    fl_push_matrix();
    int total_w=0;

    for(int a=0; a<cols; a++)
    {
        button_box()->draw(0, 0, colw[a], h(),button_color(), colf[a]);

        char *txt = coln[a];
        if(txt) {
            int iw=0, ih=0;
            if(coli[a]) {
                coli[a]->measure(iw,ih);
            }

            int X=0,Y=0,W=colw[a],H=h();
            if(colf[a]&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {X += 3; W -= 6;}

            fl_font(label_font(), float(label_size()));
            char *pbuf = fl_cut_line(txt, colw[a]-iw-X);

            //Clear CLIP flag if set, cause we clip anyway =)
            if(align() & FL_ALIGN_CLIP) Fl_Widget::clear_flag(FL_ALIGN_CLIP);

            fl_push_clip(0,0,colw[a]-DRAG_DIST,h());

            label(pbuf);
            Fl_Image *si = Fl_Widget::image();
            Fl_Widget::image(coli[a]);
            draw_label(X, Y, W, H, colf[a]|(flags()&(FL_SELECTED|FL_INACTIVE)));
            Fl_Widget::image(si);

            fl_pop_clip();
        }
        fl_translate(colw[a], 0);
        total_w+=colw[a];
    }

    // Fill space after last column
    int xf = LIST->xposition()+LIST->w()-total_w;
    if(xf>0) { fl_color(color()); fl_rectf(0, 0, xf, h()); }

    fl_pop_matrix();
}

void Fl_ListHeader::layout()
{
    Fl_Widget::layout();
    // No layout!
    // Header should be able to set any height user wants.
}

int Fl_ListHeader::handle(int ev)
{
    static bool dragging = false;
    static int col_start=0;
    static int col_to_drag=0;
    static int inside=-1;
    static int mx;
    int a, xp;

    switch(ev)
    {
    case FL_PUSH:
        inside=-1;
        col_start=0;
        col_to_drag=0;
        xp = LIST->xposition();
        mx = Fl::event_x()+xp;
        for(a=0; a<cols; a++) {
            col_to_drag=a;
            if(mx > colw[a] + col_start-DRAG_DIST && mx < colw[a] + col_start+DRAG_DIST) {
                dragging=true;
                break;
            }
            if(mx > col_start && mx < col_start+colw[a])
                inside=a;
            col_start+=colw[a];
        }

        if(!dragging && inside >= 0) {
            colf[inside] |= FL_VALUE;
            redraw(FL_DAMAGE_ALL);
            LIST->redraw(FL_DAMAGE_CHILD);
        }
        return 1;//dragging ? 1 : 0;

    case FL_RELEASE:
        if(inside >= 0 && (colf[inside] & FL_VALUE) == FL_VALUE)
        {
            colf[inside] &= ~FL_VALUE;
            redraw(FL_DAMAGE_ALL);
            LIST->redraw(FL_DAMAGE_CHILD);
            //Do some callback for sorting!?
        }
        dragging=false;
        col_start=0;
        return 0;

    case FL_DRAG:
        xp = ((Fl_ListView *)parent())->xposition();
        mx = Fl::event_x()+xp;
        if(dragging) {
            colw[col_to_drag] = mx-col_start;
            if(colw[col_to_drag]-col_start-1/*-DRAG_DIST*/ < -col_start)
                colw[col_to_drag] = 1;//DRAG_DIST;
            redraw(FL_DAMAGE_ALL);
            LIST->redraw();
            LIST->layout();
        }
        return 1;
    case FL_MOVE: {
        bool got_cursor = false;
        col_start=0;
        col_to_drag=0;
        xp = LIST->xposition();
        mx = Fl::event_x()+xp;
        for(a=0; a<cols; a++) {
            if(mx > colw[a] + col_start-DRAG_DIST && mx < colw[a] + col_start+DRAG_DIST) {
                got_cursor = true;
                fl_cursor(FL_CURSOR_WE);
                break;
            }
            col_start+=colw[a];
        }
        if(!got_cursor) fl_cursor(FL_CURSOR_DEFAULT);
    }
    return 1;
    case FL_LEAVE:
        fl_cursor(FL_CURSOR_DEFAULT);
        break;
    }
    return Fl_Widget::handle(ev);
}

static void revert(Fl_Style* s) {
    s->box = FL_DOWN_BOX;
    //s->color = FL_WHITE;
    //s->button_color = FL_GRAY;
    //s->glyph = ::glyph;
}
static Fl_Named_Style style("ListView", revert, &Fl_ListView::default_style);
Fl_Named_Style* Fl_ListView::default_style = &::style;

#define SLIDER_WIDTH scrollbar_width()

Fl_ListView::Fl_ListView(int X,int Y,int W,int H,const char* L)
    : Fl_Group(X,Y,W,H,L),
    vscrollbar(X+W-SLIDER_WIDTH,Y,SLIDER_WIDTH,H-SLIDER_WIDTH),
    hscrollbar(X,Y+H-SLIDER_WIDTH,W-SLIDER_WIDTH,SLIDER_WIDTH),
    head(0,0,W,20)
{
    style(default_style);
    set_click_to_focus();

    _header = &head;

    type(BOTH);

    item_      = 0;
    first_vis  = -1;
    yposition_ = xposition_ = 0;
    scrolldy = scrolldx = 0;

    hscrollbar.type(Fl_Scrollbar::HORIZONTAL);
    hscrollbar.callback(hscrollbar_cb);
    vscrollbar.callback(vscrollbar_cb);

    find_def = true;
    draw_stripes_ = false;

    remove(head);
    remove(vscrollbar);
    remove(hscrollbar);
    head.parent(this);
    hscrollbar.parent(this);
    vscrollbar.parent(this);

    image_ = scaled = 0;
}

Fl_ListView::~Fl_ListView()
{
    if(scaled) delete scaled;
}

Fl_Widget* Fl_ListView::top()
{
    if(!children() || !child(0))
        return 0;
    return item(child(0));
}

Fl_Widget* Fl_ListView::next()
{
    int next_i = find(item())+1;
    if(next_i >= children() || !child(next_i))
        return 0;

    Fl_Widget *w = child(next_i);
    item(w);
    return w;
}

Fl_Widget* Fl_ListView::prev()
{
    int prev_i = find(item())-1;
    if(prev_i < 0 || !child(prev_i))
        return 0;

    Fl_Widget *w = child(prev_i);
    item(w);
    return w;
}

void Fl_ListView::show_item(Fl_Widget *w)
{
    if(!CHECK_WIDGET(w)) return;

    Fl_ListView_Item *i=ITEM(w);

    if(i->y() < yposition_) {
        yposition(i->y());
        redraw(FL_DAMAGE_CONTENTS);
    } else if(i->y()+i->h() > yposition_+H) {
        yposition(i->y()+i->h()-H);
        redraw(FL_DAMAGE_CONTENTS);
    }
}

// set current item to one at or before Y pixels from top of browser
Fl_Widget* Fl_ListView::item_at(int Y)
{
    if(Y < 0)
        Y = 0;

    // move forward to the item:
    Fl_Widget *w=0;
    for(int a=0; a<children(); a++)
    {
        w=child(a);
        if(!w)
            return 0;

        if(w->y()+w->h() > Y)
            break;
    }

    //printf("item at %d is %s\n", Y, item()->label());
    return w;
}

void Fl_ListView::damage_item(Fl_Widget *item)
{
    if(!CHECK_WIDGET(item)) return;

    item->redraw(FL_DAMAGE_ALL);
    redraw(FL_DAMAGE_SCROLL);
}

void Fl_ListView::draw_row(int x, int y, int w, int h, Fl_Widget *widget)
{
    bool selected = SEL(widget);
    if(bg_image()) {

        if(!scaled) return;

        if(selected) {
#if 0
            // Draws alpheblended selection box,
            // This should optional, since its not usable in big multiselection
            // list, cause its too slow. IMHO those lists should not even use image as a bg
            // BUGGY!!

            FLE_Image sel(w, h);

            uint8 *dst = sel.data();
            FLE_Rect dst_r(0,0,w,h);

            uint8 *src = scaled->data();
            FLE_Rect src_r(0, y-HH, w, h);

            FLE_Renderer::blit(src, &src_r, scaled->format(), scaled->pitch(),
                               dst, &dst_r, sel.format(), sel.pitch(), 0);

            sel.alpha(128);

            FLE_Image *blended = sel.fore_blend(selection_color());
            blended->draw(x,y,w,h);
            delete blended;
#else

            fl_color(selection_color());
            fl_rectf(x, y, w, h);

#endif

        } else {

            if(!scaled->get_offscreen()) scaled->draw(0,0,scaled->width(), scaled->height());

            int y1=y;
            fl_transform(x,y);
            int y2=y-y1;
            y-=y2;

            if(y+h-HH > scaled->height() ) {
                h = scaled->height() - y + HH;
            }

            if(h>0) {
                int Y=y-HH;
                if(Y<0) { Y=0; h-=(HH-y); y+=(HH-y); }
                fl_copy_offscreen(x, y+y2, w, h, scaled->get_offscreen(), 0, Y);
            }
        }

    } else {

        if(selected) {

            fl_color(selection_color());
            fl_rectf(x, y, w, h);

        } else if(draw_stripes_) {

            Fl_Color c0 = color();
            Fl_Color c1 = button_color();
            int XX=1;
            int widget_n = Fl_Group::find(widget);
            for (int j=0; j<=widget_n; j++) XX ^= widget_n+1;
            if (XX & 1 && c1 != c0) {
                // draw odd-numbered items with a dark stripe, plus contrast-enhancing
                // pixel rows on top and bottom:
                fl_color(c1);
                fl_rectf(x, y, w, h);
                fl_color(c0 <= FL_LIGHT1 ? c1 : Fl_Color(FL_LIGHT1));
                //fl_color(fl_color_average(c1, c0, 1.9));
                fl_line(x, y, w, y);
                fl_line(x, h-1, w, h-1);
            } else {
                fl_color(c0);
                fl_rectf(x, y, w, h);
            }

        } else {

            fl_color(color());
            fl_rectf(x, y, w, h);
        }
    }
}

void Fl_ListView::draw_item(Fl_Widget *widget)
{
    if(!CHECK_WIDGET(widget)) return;

    int y = widget->y() - yposition_+Y;

    int x = X-xposition_;
    int h = widget->h();

    draw_row(X, y, W, h, widget);

    y+=(leading()+1)/2-1;

    int save_y = widget->y();

    fl_push_matrix();
    fl_translate(x, 0);

    widget->w(W);
    widget->y(y);

    widget->draw();

    widget->y(save_y);

    fl_pop_matrix();

    widget->set_damage(0);
}

void Fl_ListView::draw_clip_cb(void* v,int X, int Y, int W, int H)
{
    ((Fl_ListView*)v)->draw_clip(X,Y,W,H);
}

void Fl_ListView::draw_clip(int x, int y, int w, int h)
{
    fl_push_clip(x,y,w,h);

    int draw_all = damage() & (FL_DAMAGE_ALL|FL_DAMAGE_CONTENTS);
    int draw_scroll = damage() & (FL_DAMAGE_SCROLL);

    Fl_Widget *widget = 0;
    if(first_vis>=0) {
        for(int a = first_vis; a < children(); a++)
        {
            widget = child(a);

            SKIP_WIDGET(widget);

            int item_y = widget->y() - yposition_;
            if(item_y >= y+h) break;

            if(draw_scroll || draw_all || (widget->damage() & FL_DAMAGE_ALL))
            {
                draw_item(widget);
            }
        }
    }

    // erase the area below the last item:
    if(widget) {
        int bottom_y = widget->y()+widget->h()-yposition_+Y;
        if(bottom_y < y+h) {
            fl_color(color());
            fl_rectf(x, bottom_y, w, y+h-bottom_y);
        }
    }

    if(!children()) {
        fl_color(color());
        fl_rectf(x, y, w, h);
    }

    fl_pop_clip();
}

void Fl_ListView::draw_header()
{
    if(!(damage() & FL_DAMAGE_ALL) && !(_header->damage() & FL_DAMAGE_ALL))
        return;

    fl_push_clip(HX,HY,HW,HH);
    int xp = HX-xposition_;

    //correct position with FLTK internal positions
    fl_push_matrix();
    fl_translate(xp, HY);

    _header->draw();

    fl_pop_matrix();

    fl_pop_clip();

    _header->set_damage(0);
}

void Fl_ListView::draw()
{
    if(totalheight() < H)
        yposition_ = 0;
    else if((total_height < yposition_+H) && totalheight() > H)
        yposition_ = total_height-H;

    draw_header();

    // redraw contents
    if((damage() & (FL_DAMAGE_ALL|FL_DAMAGE_CONTENTS)) || bg_image() ) {

        //printf("contents %d %d %d %d\n", X,Y,W,H);
        draw_frame();
        draw_clip(X, Y, W, H);

    } else {

        // minimal update
        //printf("minimal redraw damage %x\n", damage());
        if(scrolldy || scrolldx) {

            fl_scroll(X, Y, W, H, scrolldx, scrolldy, draw_clip_cb, this);

        } else {

            bool clipped = false;
            Fl_Widget *widget = 0;
            if(first_vis>=0) {
                for(int a = first_vis; a < children(); a++) {
                    widget = child(a);

                    SKIP_WIDGET(widget);

                    if(!widget) break;

                    int item_y = widget->y() - yposition_;
                    if(item_y >= Y+H) break; //Out off screen

                    if(!clipped) {
                        fl_push_clip(X, Y, W, H);
                        clipped = true;
                    }

                    if((widget->damage() & (FL_DAMAGE_ALL|FL_DAMAGE_VALUE)))
                        draw_item(widget);
                }

                if(clipped)
                    fl_pop_clip();
            }
        }
    }

    scrolldy = scrolldx = 0;

    // draw the scrollbars:
    if(damage() & (FL_DAMAGE_ALL|FL_DAMAGE_CONTENTS)) {
        vscrollbar.set_damage(FL_DAMAGE_ALL);
        hscrollbar.set_damage(FL_DAMAGE_ALL);
        if(vscrollbar.visible() && hscrollbar.visible()) {
            // fill in the little box in the corner
            fl_color(parent()->color());
            fl_rectf(vscrollbar.x(), hscrollbar.y(), vscrollbar.w(), hscrollbar.h());
        }
    }
    update_child(vscrollbar);
    update_child(hscrollbar);
}

////////////////////////////////////////////////////////////////
// Scrolling and layout:
void Fl_ListView::layout_scrollbars()
{
    int max_cols_w = 0;
    for(int a=0; a<columns(); a++)
        max_cols_w += column_width(a);

    if((type()&VERTICAL) && (type()&ALWAYS_ON || total_height > H || yposition_))
    {
        if(!vscrollbar.visible()) {
            vscrollbar.set_visible();
            W -= vscrollbar.w();
            HW-= vscrollbar.w();
            redraw(FL_DAMAGE_ALL);
        }
    } else {
        if(vscrollbar.visible()) {
            vscrollbar.clear_visible();
            W += vscrollbar.w();
            HW+= vscrollbar.w();
            redraw(FL_DAMAGE_ALL);
        }
    }

    if((type()&HORIZONTAL) && (type()&ALWAYS_ON || max_cols_w > W || xposition_)) {
        if (!hscrollbar.visible()) {
            hscrollbar.set_visible();
            H -= hscrollbar.h();
            //HH-= hscrollbar.h();
            redraw(FL_DAMAGE_ALL);
        }
    } else {
        if(hscrollbar.visible()) {
            hscrollbar.clear_visible();
            H += hscrollbar.h();
            //HH+= hscrollbar.h();
            redraw(FL_DAMAGE_ALL);
        }
    }

    int vx = vscrollbar.flags()&FL_ALIGN_LEFT ? X-vscrollbar.w() : X+W;
    int vy = Y-(_header->visible() ? _header->h() : 0);
    int vh = H+(_header->visible() ? _header->h() : 0);
    vscrollbar.resize(vx, vy, vscrollbar.w(), vh);
    vscrollbar.value(yposition_, H, 0, total_height);
	vscrollbar.linesize(fl_height());

    int hy = hscrollbar.flags()&FL_ALIGN_TOP ? box()->dy() : Y+H;
    hscrollbar.resize(X, hy, W, hscrollbar.h());
    hscrollbar.value(xposition_, W, 0, max_cols_w/*max_width*/);
    hscrollbar.linesize(fl_height());
}

void Fl_ListView::layout()
{
    //Clear layout flag
    Fl_Widget::layout();

    X = 0; Y = 0;
    W = w(); H = h();
    box()->inset(X,Y,W,H);

    HX=X; HY=Y;
    HH = _header->visible() ? _header->h() : 0;
    HW = W;

    H-=HH;
    Y+=HH;

    if(vscrollbar.visible()) {
        W -= vscrollbar.w();
        HW-= vscrollbar.w();
        if(vscrollbar.flags() & FL_ALIGN_LEFT) {
            X += vscrollbar.w();
            HX+= vscrollbar.w();
        }
    }
    if(hscrollbar.visible()) {
        H -= hscrollbar.h();
        if(hscrollbar.flags() & FL_ALIGN_TOP) {
            Y += hscrollbar.h();
            HY+= hscrollbar.h();
        }
    }

    if(bg_image()) {
        if(!scaled) scaled = bg_image()->scale(W, H+box()->dy());
        if(scaled && (scaled->width()!=W || scaled->height()!=H+box()->dy()) ) {
            delete scaled;
            scaled = bg_image()->scale(W, H+box()->dy());
        }
        scaled->no_screen(true);
    }

    //if(!children())  return;

    // count all the items scrolled off the top:
    total_height=0;
    int a;
    bool first_found=false;
    Fl_Widget *widget = 0;
    for(a=0; a < children(); a++)
    {
        widget = child(a);

        SKIP_WIDGET(widget);

        ITEM(widget)->num = a;
        //if(!widget) break;
        widget->layout();
        widget->y(total_height);

        if((total_height+widget->height() > yposition_) && !first_found) {
            first_vis = find(widget);
            first_found=true;
        }
        total_height += widget->h();
    }

    if(find_def) find_def_sizes();

    layout_scrollbars();

    if((layout_damage() & FL_LAYOUT_XYWH) && _header->visible()) {
        _header->resize(HX, HY, HW, HH);
        _header->layout();
    }
}

void Fl_ListView::hscrollbar_cb(Fl_Widget* o, void*) {
    ((Fl_ListView *)(o->parent()))->xposition(int(((Fl_Scrollbar*)o)->value()));
}

void Fl_ListView::vscrollbar_cb(Fl_Widget* o, void*) {
    ((Fl_ListView *)(o->parent()))->yposition(int(((Fl_Scrollbar*)o)->value()));
}

void Fl_ListView::xposition(int X)
{
    if(X == xposition_) return;

    int dx = xposition_-X;
    if(dx) {
        xposition_ = X;
        scrolldx += dx;
        relayout();
        _header->set_damage(FL_DAMAGE_ALL);

        redraw(FL_DAMAGE_SCROLL);
    }
}

void Fl_ListView::yposition(int Y)
{
    if(Y == yposition_) return;

    ((Fl_Slider*)(&vscrollbar))->value(Y);

    Fl_Widget *i = item_at(Y);
    if(i) first_vis = find(item());

    scrolldy += (yposition_-Y);
    yposition_ = Y;

    relayout();

    redraw(FL_DAMAGE_SCROLL);
}

////////////////////////////////////////////////////////////////
// Event handling

// force current item to a state
int Fl_ListView::select(Fl_Widget *w, int value)
{
    if(!CHECK_WIDGET(w)) return 0;

    if(value) {
        if(SEL(w)) return 0;
        selection.append(w);
        w->set_flag(FL_SELECTED);
    } else {
        if(!SEL(w)) return 0;
        selection.remove(w);
        w->clear_flag(FL_SELECTED);
    }

    if(selection.count()>0 && move()) {
        sort_selection();
    }

    damage_item(w);

    return 1;
}

// Turn off all lines in the browser:
int Fl_ListView::unselect_all()
{
    selection.clear();
    for(int a=0; a < children(); a++)
    {
        if(SEL(child(a))) {
            child(a)->clear_flag(FL_SELECTED);
            child(a)->redraw(FL_DAMAGE_VALUE);
        }
    }

    return 1;
}

// Set both the single and multi-browser to only this item:
int Fl_ListView::select_only(Fl_Widget *w)
{
    if(!CHECK_WIDGET(w)) return 0;

    // Turn off all other items:
    selection.clear();
    for(int a=0; a < children(); a++)
    {
        if(SEL(child(a))) {
            child(a)->clear_flag(FL_SELECTED);
            child(a)->redraw(FL_DAMAGE_VALUE);
        }
    }

    set_changed();
    selection.append(w);
    w->set_flag(FL_SELECTED);
    w->redraw(FL_DAMAGE_VALUE);

    item(w);

    return 1;
}

#define HANDLE_HEADER_PUSH if(Fl::event_inside(HX,HY,HW,HH) && _header->visible()) { header_pushed=true; return head.send(event); }
#define HANDLE_HEADER if(Fl::event_inside(HX,HY,HW,HH) && _header->visible()) { return head.send(event); }

int Fl_ListView::handle(int event)
{
    static bool header_pushed=false;
    static char drag_type=0; // for multibrowser

    // for moving and selecting
    static Fl_Widget *sel_item=0;

    switch(event)
    {
    case FL_FOCUS:
    case FL_UNFOCUS:
        return 1;

    case FL_PUSH:
        HANDLE_HEADER_PUSH;
    case FL_MOVE:
        HANDLE_HEADER;
    case FL_ENTER:
        if(vscrollbar.align()&FL_ALIGN_LEFT ? (Fl::event_x() < vscrollbar.x()+vscrollbar.w()) : (Fl::event_x() >= vscrollbar.x()))
            if(vscrollbar.send(event))
                return 1;
        if(hscrollbar.align()&FL_ALIGN_TOP ? (Fl::event_y() < hscrollbar.y()+hscrollbar.h()) : (Fl::event_y() >= hscrollbar.y()))
            if(hscrollbar.send(event))
                return 1;

        if(event != FL_PUSH)
        {
            Fl::belowmouse(this);
            return 1;
        }

        take_focus();
    case FL_DRAG:
        {
            if(header_pushed)
                HANDLE_HEADER;
            int my = Fl::event_y()+yposition_-Y;
            Fl_Widget *i = item_at(my);
            if(!i) return 0;

            if(event == FL_DRAG)
            {
                if(move())
                {
                    if(sel_item)
                    {
                        if(selection.count() == 1) //Move one
                        {
                            int place = ITEM(i)->num;
                            if(my < sel_item->y()-2) { //Up
                                place--;
                                if(place>=-1) {
                                    ITEM(i)->num = place;
                                    insert(*sel_item, place+1);
                                    redraw(FL_DAMAGE_CONTENTS);
                                }
                            }
                            else if(my > sel_item->y()+sel_item->h()+2) //Down
                            {
                                place++;
                                if(place<=children()) {
                                    ITEM(i)->num = place;
                                    insert(*sel_item, place);
                                    redraw(FL_DAMAGE_CONTENTS);
                                }
                            }
                            show_item(sel_item);

                        } else if(selection.count() > 1) //Move many
                        {
                            if(my < sel_item->y()-2) //UP
                            {
                                int cnt = ITEM(sel_item)->num - ITEM(i)->num;
                                if(ITEM(selection.first())->num-cnt >= 0) {
                                    moveselection_up(cnt);
                                    //show_item(selection.first());
                                    show_item(sel_item);
                                }
                            }
                            else if(my > sel_item->y()+sel_item->h()+2) //DOWN
                            {
                                int cnt = ITEM(i)->num - ITEM(sel_item)->num;
                                if(ITEM(selection.last())->num+cnt < children()) {
                                    moveselection_down(cnt);
                                    //show_item(selection.last());
                                    show_item(sel_item);
                                }
                            }
                        }
                    } //sel_item

                } else if(multi()) // end move
                {
                    if(sel_item) {
                        // If not movable, then dragging selects
                        //drag_type = !SEL(i);
                        //select(i, drag_type);
                        select_items(ITEM(sel_item)->num, ITEM(i)->num);
                        item(i);
                        show_item(i);
                        redraw(FL_DAMAGE_SCROLL);
                    }
                    return 1;

                } else { // end multi

                    select_only(i);
                    item(i);
                    show_item(i);
                    redraw(FL_DAMAGE_SCROLL);
                    return 1;

                }
            } // end if( event != FL_PUSH )
            else if(event == FL_PUSH) {

                // If different item, set clicks to 0
                if(i != item())	Fl::event_clicks(0);

                damage_item(i);
                item(i);
                show_item(i);

                if(when() & FL_WHEN_CHANGED)
                    do_callback();

                if(Fl::event_button() == FL_LEFT_MOUSE && multi())
                {
                    // Multiple selection button handling
                    if(Fl::event_state(FL_CTRL))
                    {
                        // start a new selection block without changing state
                        drag_type = !SEL(i);
                        select(i, drag_type);
                        sel_item = i;
                        return 1;
                    }
                    else if(Fl::event_state(FL_SHIFT)) {
                        // We want to change the selection between
                        // the top most selected item and the just clicked item.
                        // start a new selection block without changing state
                        drag_type = !SEL(i);
                        //select(i, drag_type);
                        select_items(ITEM(sel_item)->num, ITEM(i)->num);
                        sel_item  = i;
                        Fl::event_clicks(0);
                        return 1;
                    } else {
                        //Normal push
                        select_only(i);
                        drag_type = 1;
                        sel_item  = i;
                        return 1;
                    }

                } else { // LEFT_MOUSE && multi()

                    select_only(i);
                    sel_item  = i;
                    return 1;

                }
            }
        }  // end case FL_PUSH / FL_DRAG
        return 1;

    case FL_RELEASE:
        {
            HANDLE_HEADER;
            header_pushed=false;

            if(when() & FL_WHEN_RELEASE) {
                if(Fl::event_clicks()) {
                    do_callback();
                    Fl::event_clicks(0);
                    return 1;
                }
                do_callback();
            }
        }
        return 1;

    case FL_KEY:
        {
            Fl::event_clicks(0); // make program not think it is a double-click
            switch(Fl::event_key())
            {
            case FL_Delete:
                return 1;
            case FL_Home:
                yposition(0);
                item(child(0));
                select_only(child(0));
                return 1;

            case FL_End:
                yposition(totalheight()-h());
                item(child(children()-1));
                select_only(child(children()-1));
                redraw(FL_DAMAGE_CONTENTS);
                return 1;

            case FL_Up:
                {
                    Fl_Widget *i;
                    if(!item() && children()>0) i = child(children()-1);
                    else i = prev();
                    if(i) {
                        if(i->y() <= yposition_)
                            scroll_up(i->height()+10);
                        if(Fl::event_state(FL_SHIFT|FL_CTRL) && multi())
                            select(i, 1);
                        else
                            select_only(i);

                        show_item(i);
                        redraw(FL_DAMAGE_CONTENTS);
                    }
                    if((when()&FL_WHEN_RELEASE) && (changed() || (when()&FL_WHEN_NOT_CHANGED))) {
                        clear_changed();
                        do_callback();
                    }
                    return 1;
                }

            case FL_Down:
                {
                    Fl_Widget *i;
                    if(!item() && children()>0) i = child(0);
                    else i = next();
                    if(i) {
                        if(i->y()+i->h() >= yposition_+H)
                            scroll_down(i->height()+10);
                        if(Fl::event_state(FL_SHIFT|FL_CTRL) && multi())
                            select(i, 1);
                        else
                            select_only(i);

                        show_item(i);
                        redraw(FL_DAMAGE_CONTENTS);
                    }
                    if((when()&FL_WHEN_RELEASE) && (changed() || (when()&FL_WHEN_NOT_CHANGED))) {
                        clear_changed();
                        do_callback();
                    }
                    return 1;
                }

            case FL_Enter:
                if (!(when() & FL_WHEN_ENTER_KEY)) break;
                clear_changed();
                do_callback();
                return 1;

            default:
                int ret=0;
                ret = vscrollbar.send(event);
                if(!ret) ret = hscrollbar.send(event);
                if(ret) {
                    //Set item to first visible
                    layout();
                    item(child(first_vis));
                    return 1;
                }
                break;

            } // event_key
            break;
        } // FL_KEYBOARD
    case FL_MOUSEWHEEL:
        {
            return vscrollbar.send(event);
        }
    } // event

    return 0;
}

void Fl_ListView::scroll_down(int pixels)
{
    if(children() && totalheight() > H)
    {
        if(yposition_ > (totalheight() - H)) {
            yposition(totalheight() - H);
            return;
        }

        int yp = yposition_+pixels;
        if(yp > (totalheight() - H)) yp = totalheight()-H;

        yposition(yp);
    }
}

void Fl_ListView::scroll_up(int pixels)
{
    if(children())
    {
        if(yposition_-pixels <= 0)
        {
            if(yposition_ > 0)
                yposition(0);
            return;
        }
        yposition(yposition_-pixels);
    }
}

static int cmp(const void *w1, const void *w2)
{
    return ITEM(*(Fl_ListView_Item **)w2)->num - ITEM(*(Fl_ListView_Item **)w1)->num;
}

void Fl_ListView::sort_selection()
{
    Fl_Widget *item;
    Fl_ListView_Item **l = (Fl_ListView_Item **)malloc(sizeof(Fl_ListView_Item *)*selection.count());
    int a=0;
    for(item = selection.first(); item != 0; item = selection.next()) {
        l[a] = (Fl_ListView_Item *)item;
        a++;
    }
    qsort(l, selection.count(), sizeof(Fl_ListView_Item *), cmp);
    selection.clear();
    while(a--) {
        selection.append(l[a]);
    }
    free(l);
}

void Fl_ListView::moveselection_up(int dy)
{
    Fl_Widget *item;
    for(item = selection.first(); item != 0; item = selection.next()) {

        insert(*item, ITEM(item)->num-dy);
        ITEM(item)->num -= dy;
    }
    redraw(FL_DAMAGE_CONTENTS);
}

void Fl_ListView::moveselection_down(int dy)
{
    Fl_Widget *item;
    for(item = selection.last(); item != 0; item = selection.prev()) {
        insert(*item, ITEM(item)->num+dy+1);
        ITEM(item)->num += dy+1;
    }
    redraw(FL_DAMAGE_CONTENTS);
}

bool Fl_ListView::on_selection(int Y)
{
    Fl_Widget *item = item_at(Y);
    if(!item) return false;
    int it_pos = find(item);
    int f_pos  = find(selection.first());
    int l_pos  = find(selection.last());
    if(it_pos < l_pos && it_pos > f_pos)
        return true;

    return false;
}

void Fl_ListView::remove_selection()
{
    int a = 0;
    for(Fl_Widget *item = selection.first(); item != 0; item = selection.next())
    {
        a = find(item);
        remove(item);
    }
    selection.clear();
    select_only(child(a));
}

void Fl_ListView::clear_selection()
{
    selection.clear();
}

void Fl_ListView::select_items(int from, int to)
{
    int start=0, end=0;
    if(to < from) {
        start=to;
        end=from;
    } else {
        start=from;
        end=to;
    }

    selection.clear();
    Fl_Widget *it;
    for(int n=0; n<children(); n++) {
        it = child(n);

        if(n>=start && n<=end) {
            if(!SEL(it)) {
                set_changed();
                it->set_flag(FL_SELECTED);
                it->redraw(FL_DAMAGE_VALUE);
            }
            selection.append(it);

        } else {

            if(SEL(it)) {
                set_changed();
                it->clear_flag(FL_SELECTED);
                it->redraw(FL_DAMAGE_VALUE);
            }

        }
    }

    if(selection.count()>0 && move()) {
        sort_selection();
    }
}

void Fl_ListView::clear()
{
    Fl_Group::clear();
    first_vis    = -1;
    item_ 	 = 0;
    total_height = 0;
    redraw(FL_DAMAGE_ALL);
}

void Fl_ListView::remove(int index)
{
    Fl_Widget *w = child(index);
    if(!w) return;
    if(w==item_) item_ = 0;
    Fl_Group::remove(index);

    relayout();
}

void Fl_ListView::find_def_sizes()
{
    int max_col_w[MAX_COLUMNS] = {0};

    for(int a=0; a<children(); a++)
    {
        Fl_Widget *widget = child(a);

        SKIP_WIDGET(widget);

        for(int i=0; i<columns(); i++) {
            if(column_width(i) > 0) continue;
            if(max_col_w[i] < ITEM(widget)->width(i)+20)
                max_col_w[i] = ITEM(widget)->width(i)+20;
        }
    }

    for(int i=0; i<columns(); i++) {
        if(column_width(i) > 0) continue;
        column_width(i, max_col_w[i]);
    }

    find_def = false;
}

