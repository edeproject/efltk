#include <efltk/Fl_ListView.h>
#include <efltk/fl_draw.h>

#define SEL(w) (selection.index_of(w)!=-1)
#define SLIDER_WIDTH scrollbar_width()

static void revert(Fl_Style* s) {
    s->box = FL_DOWN_BOX;
    s->button_box = FL_NO_BOX;
    s->leading = 2;
}
static Fl_Named_Style style("ListView", revert, &Fl_ListView::default_style);
Fl_Named_Style* Fl_ListView::default_style = &::style;

Fl_ListView *Fl_ListView::current=0;


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

    calc_total_h = true;
    first_vis = -1;
    total_height = 0;
    item_      = 0;
    yposition_ = xposition_ = 0;
    scrolldy = scrolldx = 0;
    sort_type_ = SORT_ABSOLUTE;

    hscrollbar.type(Fl_Scrollbar::HORIZONTAL);
    hscrollbar.callback(hscrollbar_cb);
    vscrollbar.callback(vscrollbar_cb);

    find_def = true;
    draw_stripes_ = false;

    Fl_Group::remove(find(head));
    Fl_Group::remove(find(vscrollbar));
    Fl_Group::remove(find(hscrollbar));
    head.parent(this);
    hscrollbar.parent(this);
    vscrollbar.parent(this);

    Fl_Group::end();
    Fl_ListView::current = this;
}

Fl_ListView::~Fl_ListView() {
    clear();
}

void Fl_ListView::begin()
{
    Fl_ListView::current = this;
    Fl_Group::begin();
}

void Fl_ListView::end()
{
    Fl_ListView::current = 0;
    Fl_Group::end();
}

Fl_ListView_Item *Fl_ListView::find_userdata(void *data, uint start_index) const
{
    for(uint n=start_index; n<children(); n++) {
        if(items[n]->user_data()==data) 
            return items[n];
    }
    return 0;
}

Fl_ListView_Item *Fl_ListView::find_text(const char *text, uint column, uint start_index) const
{
    for(uint n=start_index; n<children(); n++) {
        const char *itext = items[n]->label(column);
        if(!strcmp(text, itext))			
            return items[n];
    }
    return 0;
}

static int scol=-1;
static int stype=-1;
static int fl_listview_sort(const void *w1, const void *w2) {
    Fl_ListView_Item *i1 = *(Fl_ListView_Item **)w1;
    Fl_ListView_Item *i2 = *(Fl_ListView_Item **)w2;
    return i1->compare(i2, scol, stype);    
}

// Returns sort type: ASC, DESC, ABSOLUTE
int Fl_ListView::sort(int column)
{
    if(scol!=column) sort_type_=SORT_ABSOLUTE;

    sort_type_++;
    if(sort_type_==SORT_LAST_TYPE)
        sort_type_=SORT_ABSOLUTE;

    scol = column;
    stype = sort_type_;
    items.sort(fl_listview_sort);

    calc_total_h = true;
    relayout();
    redraw();
    return sort_type_;
}

Fl_ListView_Item* Fl_ListView::top()
{
    if(!children()) return 0;
    return item(child(0));
}

Fl_ListView_Item* Fl_ListView::next()
{
    if(!item()) return 0;
    uint next_i = item()->index()+1;
    if(next_i >= children()) return 0;
    Fl_ListView_Item *w = child(next_i);
    item(w);
    return w;
}

Fl_ListView_Item* Fl_ListView::prev()
{
    if(!item() || item()->index()==0) return 0;
    int prev_i = item()->index()-1;
    if(prev_i < 0) return 0;
    Fl_ListView_Item *w = child(prev_i);
    item(w);
    return w;
}

bool Fl_ListView::show_item(Fl_ListView_Item *w)
{
    if(w->y() < yposition_) {
        yposition(w->y());
        redraw(FL_DAMAGE_CONTENTS);
        return true;
    } else if(w->y()+w->h() > yposition_+H) {
        yposition(w->y()+w->h()-H);
        redraw(FL_DAMAGE_CONTENTS);
        return true;
    }
    return false;
}

// set current item to one at or before Y pixels from top of browser
Fl_ListView_Item* Fl_ListView::item_at(int Y) const
{
    if(Y < 0) Y = 0;
    if(!children()) return 0;

    // move forward to the item:
    Fl_ListView_Item *w=0;
    for(uint a=find_safe_top(); a<children(); a++)
    {
        w=child(a);
        if(Y>=w->y() && Y<=w->y()+w->h())
            return w;
    }
    return 0;
}

void Fl_ListView::damage_item(Fl_ListView_Item *item)
{
    item->set_damage(FL_DAMAGE_ALL);
}

void Fl_ListView::draw_row(int x, int y, int w, int h, Fl_ListView_Item *widget, bool selected) const
{    
    if(selected) {

        fl_color(selection_color());
        fl_rectf(x, y, w, h);

    } else if(draw_stripes_) {

        Fl_Color c0 = color();
        Fl_Color c1 = button_color();        
        if(widget->index() & 1 && c1 != c0) {
            // draw odd-numbered items with a dark stripe, plus contrast-enhancing
            // pixel rows on top and bottom:
            fl_color(c1);
            fl_rectf(x, y, w, h);
            			
            fl_color(fl_lighter(button_color()));
            fl_line(x, y, w, y);			
            fl_line(x, y+h-1, w, y+h-1);
        } else {
            fl_color(c0);
            fl_rectf(x, y, w, h);
        }

    } else {

        fl_color(color());
        fl_rectf(x, y, w, h);
    }
}

void Fl_ListView::draw_item(Fl_ListView_Item *widget) const
{
    bool selected = SEL(widget);
    int y = widget->y() - yposition_+Y;

    int x = X-xposition_;

    draw_row(X, y, W, widget->h(), widget, selected);

    fl_push_matrix();
    fl_translate(x, y);

    int cellX=box()->dx();
    for(int a=0; a<columns(); a++) {
        widget->draw_cell(a, column_width(a), selected);
        cellX += column_width(a);
        fl_translate(column_width(a), 0);
    }

    fl_pop_matrix();
    widget->set_damage(0);
}

void Fl_ListView::draw_clip_cb(void* v,int X, int Y, int W, int H)
{
    ((Fl_ListView*)v)->draw_clip(X,Y,W,H);
}

void Fl_ListView::draw_clip(int x, int y, int w, int h) const
{
    if(!children()) {
        fl_color(color());
        fl_rectf(x,y,w,h);
        return;
    }

    fl_push_clip(x,y,w,h);

    int draw_all = damage() & (FL_DAMAGE_ALL|FL_DAMAGE_CONTENTS);
    int draw_scroll = damage() & (FL_DAMAGE_SCROLL);

    Fl_ListView_Item *widget = 0;
    for(uint n=find_safe_top(); n < children(); n++)
    {
        widget = child(n);

        if(widget->y()-yposition_ < -widget->h()) continue;
        if(widget->y()-yposition_ > y+h) break;

        if(draw_scroll || draw_all || (widget->damage() & FL_DAMAGE_ALL)) {
            draw_item(widget);
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
    fl_pop_clip();
}

void Fl_ListView::draw_header() const
{
    if(!(damage() & FL_DAMAGE_ALL) && !(_header->damage() & FL_DAMAGE_ALL))
        return;

    if(!_header->visible()) return;

    fl_push_clip(HX,HY,HW,HH);
    int xp = HX-xposition_;

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
    if((damage() & (FL_DAMAGE_ALL|FL_DAMAGE_CONTENTS))) {

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
            Fl_ListView_Item *widget = 0;
            for(uint n=find_safe_top(); n < children(); n++) {
                widget = child(n);

                if(widget->y()-yposition_ < -widget->h()) continue;
                if(widget->y()-yposition_ > Y+H) break;

                if(!clipped) {
                    fl_push_clip(X, Y, W, H);
                    clipped = true;
                }

                if((widget->damage() & (FL_DAMAGE_ALL|FL_DAMAGE_VALUE)))
                    draw_item(widget);
            }
            if(clipped) fl_pop_clip();
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
    if(children()>0) vscrollbar.linesize(child(0)->h());

    int hy = hscrollbar.flags()&FL_ALIGN_TOP ? box()->dy() : Y+H;
    hscrollbar.resize(X, hy, W, hscrollbar.h());
    hscrollbar.value(xposition_, W, 0, max_cols_w/*max_width*/);
    if(children()>0) hscrollbar.linesize(child(0)->h());
}

unsigned Fl_ListView::find_safe_top() const
{
    if(!children() || yposition_<=0) return 0;

	unsigned idx = 0;
	for(unsigned n=m_ypos_lookup.size()-1; n>=0; n--) {
		Fl_ListView_Item *i = child(m_ypos_lookup[n]);
		if(i->y() < yposition_) {
			idx = m_ypos_lookup[n];
			break;
		}
	}
	
	return idx;
}

void Fl_ListView::layout()
{
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

    if(children()>0 && calc_total_h) {
        
        int widgety=0;
        Fl_ListView_Item *widget = 0;

		m_ypos_lookup.clear();
		m_ypos_lookup.append(0);

        for(uint a=0; a < children(); a++)
        {
			if(a%1000 == 0) {				
				m_ypos_lookup.append(a);
			}
            widget = (Fl_ListView_Item *)child(a);
            widget->y(widgety);
            widget->layout();

            widgety+=widget->h();

            widget->index(a);
        }	

        total_height = widgety;
        calc_total_h = false;

        if(find_def) find_default_sizes();
    }

    layout_scrollbars();

    if(layout_damage() && _header->visible()) {
        _header->resize(HX, HY, HW, HH);
        _header->layout();
    }

    //Clear layout flag
    Fl_Widget::layout();
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
    ((Fl_Slider*)(&hscrollbar))->value(X);
    int dx = xposition_-X;
    if(dx) {
        xposition_ = X;
        scrolldx += dx;        
        _header->set_damage(FL_DAMAGE_ALL);
        redraw(FL_DAMAGE_SCROLL);
    }
}

void Fl_ListView::yposition(int Y)
{
    if(Y == yposition_) return;

    ((Fl_Slider*)(&vscrollbar))->value(Y);
    int dy = yposition_-Y;
    if(dy) {
        scrolldy += (yposition_-Y);
        yposition_ = Y;
        redraw(FL_DAMAGE_SCROLL);
    }
}

////////////////////////////////////////////////////////////////
// Event handling

// force current item to a state
int Fl_ListView::select(Fl_ListView_Item *w, int value)
{
    if(value) {
        if(SEL(w)) return 0;
        selection.append(w);        
    } else {        
        selection.remove(w);        
    }

    if(selection.size()>0 && move()) {
        sort_selection();
    }

    damage_item(w);
    return 1;
}

// Turn off all lines in the browser:
int Fl_ListView::unselect_all()
{
    for(uint n=0; n<selection.count(); n++)
        damage_item(selection[n]);
    selection.clear();
    return 1;
}

// Set both the single and multi-browser to only this item:
int Fl_ListView::select_only(Fl_ListView_Item *w)
{
    // Turn off all other items:
    unselect_all();    
    set_changed();
    selection.append(w);    
    damage_item(w);    

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
    static Fl_ListView_Item *sel_item=0;

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
                Fl_ListView_Item *i = item_at(my);
                if(!i) return 0;

                if(event == FL_DRAG)
                {
                    if(move())
                    {
                        if(sel_item)
                        {
                            if(selection.size() > 0) //Move many
                            {								
								int offset = i->h()-sel_item->h()/2;
                                if(my < sel_item->y()-offset) //UP
                                {
                                    int cnt = sel_item->index() - i->index();										
                                    if(selection.item(selection.size()-1)->index()-cnt >= 0) {										
                                        moveselection_up(cnt);                                        
                                        show_item(sel_item);
                                        redraw(FL_DAMAGE_CONTENTS);
                                    }
                                }
                                else if(my > sel_item->y()+sel_item->h()+offset) //DOWN
                                {
                                    int cnt = i->index() - sel_item->index();									
                                    if(selection.item(0)->index()+cnt < (int)children()) {
                                        moveselection_down(cnt);                                        
                                        show_item(sel_item);
                                        redraw(FL_DAMAGE_CONTENTS);
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
                            if(item()!=i) {
                                select_items(sel_item->index(), i->index());
                                item(i);
                                show_item(i);
                                redraw(FL_DAMAGE_CHILD);
                            }
                        }
                    //return 1;

                    } else { // end multi

                        select_only(i);
                        item(i);
                        show_item(i);
                        redraw(FL_DAMAGE_CHILD);
                    //return 1;

                    }

                    if(sel_item!=i) {
                        if(when() & FL_WHEN_CHANGED) do_callback();
                        else set_changed();
                    }
                    return 1;

                } // end if( event != FL_PUSH )
                else if(event == FL_PUSH) {

                // If different item, set clicks to 0
                    if(i != item())	Fl::event_clicks(0);

                    item(i);
                    damage_item(i);                
                    show_item(i);
                    int ret = 0;

                    if(Fl::event_button() == FL_LEFT_MOUSE && multi())
                    {
                    // Multiple selection button handling
                        if(Fl::event_state(FL_CTRL))
                        {
                        // start a new selection block without changing state
                            drag_type = !SEL(i);
                            select(i, drag_type);
                            sel_item = i;
                            show_item(i);
                            redraw(FL_DAMAGE_CHILD);
                            ret = 1;
                        }
                        else if(Fl::event_state(FL_SHIFT)) {
                        // We want to change the selection between
                        // the top most selected item and the just clicked item.
                        // start a new selection block without changing state
                            drag_type = !SEL(i);
                        //select(i, drag_type);
                            select_items(sel_item->index(), i->index());
                            sel_item  = i;
                            Fl::event_clicks(0);
                            show_item(i);
                            redraw(FL_DAMAGE_CHILD);
                            ret = 1;
                        } else {
                        //Normal push
                            select_only(i);
                            drag_type = 1;
                            sel_item  = i;
                            show_item(i);
                            redraw(FL_DAMAGE_CHILD);
                            ret = 1;
                        }

                    } else { // LEFT_MOUSE && multi()

                        select_only(i);
                        sel_item  = i;
                        show_item(i);
                        redraw(FL_DAMAGE_CHILD);
                        ret = 1;
                    }

                    if(when() & FL_WHEN_CHANGED)
                        do_callback();
                    else
                        set_changed();

                    return ret;
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
                            Fl_ListView_Item *i;
                            if(!item() && children()>0) i = child(children()-1);
                            else i = prev();
                            if(i) {
                                if(i->y() <= yposition_)
                                    scroll_up(i->h()+10);
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
                            Fl_ListView_Item *i;
                            if(!item() && children()>0) i = child(0);
                            else i = next();
                            if(i) {
                                if(i->y()+i->h() >= yposition_+H)
                                    scroll_down(i->h()+10);
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
                            if(Fl::event_key()==FL_Page_Up)
                                select_only(item_at(yposition_+10));
                            else if(Fl::event_key()==FL_Page_Down)
                                select_only(item_at(yposition_+H-10));
                            show_item(item());
                            redraw(FL_DAMAGE_CONTENTS);
                            return 1;
                        }
                        break;

                } // event_key
                break;
            } // FL_KEYBOARD
        case FL_MOUSEWHEEL:
            {
            /*if(vscrollbar.visible())
                return vscrollbar.send(event);
            else if(hscrollbar.visible())
                return hscrollbar.send(event);
            break;*/
                if(Fl::event_dy()>0) scroll_up(25);
                else scroll_down(25);
                return 1;
            }
        default:
            break;
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

static int cmp(const void *w1, const void *w2) {
    return (*(Fl_ListView_Item **)w2)->index() - (*(Fl_ListView_Item **)w1)->index();
}

void Fl_ListView::sort_selection() {
    selection.sort(cmp);
}

void Fl_ListView::moveselection_up(int dy)
{	
    uint n=selection.size();	
	Fl_ListView_Item *i;

    while(n--)
    {
		i = selection[n];
		items.remove(i->index());
		items.insert(i->index()-dy, i);
    }

	// Update Y positions and indexes for safe range, after move.
	// -10 and +10, only to be sure everything is correct
	int range_start = selection[selection.size()-1]->index()-10;
	int range_end	= selection[0]->index()+10;
	int y, idx;

	if(range_start<0) {
		range_start=0;
		y = 0; idx = 0;
	} else {
		y = child(range_start)->y();
		idx = child(range_start)->index();
	}
	if((unsigned)range_end>items.size()) range_end=items.size();
			
	for(n=range_start; n<(unsigned)range_end; n++) {		
		child(n)->y(y);
		child(n)->index(idx);
		y += child(n)->h();
		idx++;
	}
}

void Fl_ListView::moveselection_down(int dy)
{
	Fl_ListView_Item *i;
    for(uint n=0; n<selection.size(); n++)
    {		
		i = selection[n];
		items.remove(i->index());
		items.insert(i->index()+dy, i);
    }

	// Update Y positions and indexes for safe range, after move.
	// -10 and +10, only to be sure everything is correct
	int range_start = selection[selection.size()-1]->index()-10;
	int range_end	= selection[0]->index()+10;
	int y, idx;

	if(range_start<=0) {
		range_start=0;
		y = 0; idx = 0;
	} else {
		y = child(range_start)->y();
		idx = child(range_start)->index();
	}
	if((unsigned)range_end>items.size()) range_end=items.size();
		
	for(n=range_start; n<(unsigned)range_end; n++) {		
		child(n)->y(y);
		child(n)->index(idx);
		y += child(n)->h();
		idx++;
	}
}

void Fl_ListView::remove_selection()
{
    int a = 0;
    for(uint n=0; n<selection.size(); n++) {
        Fl_ListView_Item *item = selection.item(n);
        if(!a) a = item->index();
        delete item;
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
        end=to+1;
    }

    unselect_all();
    for(int n=start; n<end; n++) {
        selection.append(child(n));
        set_changed();
        damage_item(child(n));
    }

    if(selection.size()>0 && move()) {
        sort_selection();
    }
}

void Fl_ListView::clear()
{
    for(uint n=0; n<children(); n++) {
        Fl_ListView_Item *w = child(n);
        w->parent(0);
        delete w;
    }
    items.clear();
    selection.clear();

    first_vis = -1;
    scrolldy = scrolldx = 0;
    yposition_ = xposition_ = 0;
    item_ = 0;
    total_height = 0;
}

void Fl_ListView::remove(int index)
{
    if((uint)index >= children()) return;

    Fl_ListView_Item *w = child(index);
    if(w==item_) item_ = 0;

    w->parent(0);
    items.remove(index);

    calc_total_h = true;
}

void Fl_ListView::insert(Fl_ListView_Item  &o, uint index)
{
    if (o.parent()) {
        uint n = o.index();
        if (o.parent() == this) {
            if (index > n) index--;
            if (index == n) return;
        }
        o.parent()->remove(n);
    }
    o.parent(this);
    if(children() == 0) {
        // allocate for 1 child
        items.append(&o);
    } else {
        items.insert(index, &o);
    }

    calc_total_h = true;
    relayout();
}

void Fl_ListView::add(Fl_ListView_Item &w)
{
    insert(w, children());
}

void Fl_ListView::find_default_sizes()
{
    uint a;
    int i;
    Fl_Int_List max_col_w;

    bool do_find=false;
    for(i=0; i<columns(); i++) {
        max_col_w.append(0);
        if(column_width(i) < 0) do_find = true;
    }

    if(!do_find) return;

    for(a=0; a<children(); a++) {
        Fl_ListView_Item *widget = (Fl_ListView_Item *)child(a);
        for(i=0; i<columns(); i++) {
            if(column_width(i) > 0) continue;
            if(max_col_w[i] < widget->column_width(i)+20)
                max_col_w[i] = widget->column_width(i)+20;
        }
    }

    for(i=0; i<columns(); i++) {
        if(column_width(i) > 0) continue;
        column_width(i, max_col_w[i]);
    }

    find_def = false;
}

void Fl_ListView::fill(Fl_Data_Source &ds) 
{
    // Final version should replace the existing rows (truncate them,if necessary).
    clear();

    if (!ds.open()) return;

    // First version is very primitive.
    // Final version should replace the existing columns, if necessary.
    header()->clear();
    //header()->button_box(FL_VERT_SHADE_UP_BOX);

    unsigned columnCount = ds.field_count();
    if (!columnCount) return;
    for (unsigned col = 0; col < columnCount; col++) {
        Fl_Data_Field& df = ds.field(col);
        if (!df.visible) continue;
        int width = 100;
        if (df.width >= 0) {
            width = df.width * text_size() * 2 / 3;
        }
        add_column(df.name(),width);
        column_flags(col,df.flags);
    }

    begin();

    while (!ds.eof()) {
        Fl_ListView_ItemExt *item = new Fl_ListView_ItemExt();
        item->columns(columnCount);
        item->user_data(ds.user_data());
        for (int col = 0; col < (int)columnCount; col++) {
            Fl_Data_Field& df = ds.field(col);
            if (!df.visible) continue;
            item->flags(col, df.flags);
            if(df.type() == VAR_IMAGEPTR) item->image(col, (Fl_Image *)df.as_image());
            else item->label(col, ds.field(col).as_string());
        }
        ds.next();
    }
    ds.close();
    end();

    find_def = false;
}
