#include <efltk/Fl_ListView.h>
#include <efltk/Fl_ListView_Item.h>

#define DRAG_DIST 3 //Area to size header
#define TXT_SPACE 2 //Size between txt and img

#define SEL(w) (selection.index_of(w)!=-1)
//((w->flags() & FL_SELECTED) == FL_SELECTED)

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
	attr_list.auto_delete(true);
    style(default_style);
    sort_type = Fl_ListView::SORT_UNKNOWN;
    sort_col = 0;
}

Fl_ListHeader::~Fl_ListHeader()
{
    clear();
}

void Fl_ListHeader::add_attr(int col)
{	
	attr *a = new attr;
	a->label = 0;
	a->flags = FL_ALIGN_LEFT;
	a->width = 0;
	a->font = Fl_Widget::label_font();
	a->font_size = Fl_Widget::label_size();
	a->color = Fl_Widget::label_color();
	a->image = 0;
	attr_list[col] = a;
}

void Fl_ListHeader::add_column(const char *name, int w)
{	
	columns(columns()+1);
	label(columns()-1, name);
	width(columns()-1, w);
}

void Fl_ListHeader::columns(int count)
{
	uint old_size = attr_list.size();
	uint new_size = count;

	if(old_size < new_size) {
		attr_list.resize(new_size);
		for(uint n=old_size; n<new_size; n++) {
			add_attr(n);
		}
	} else {
		for(uint n=new_size; n<old_size; n++) {
			attr *a = (attr*)attr_list[n];
			if(a->flags & FL_COPIED_LABEL) if(a->label) free((void *)a->label);
		}
		attr_list.resize(new_size);
	}
}

uint Fl_ListHeader::columns()
{
	return attr_list.size();
}

void Fl_ListHeader::width(int col, int w)
{
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->width = w;
}

int Fl_ListHeader::width(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->width;
}

Fl_Flags Fl_ListHeader::column_flags(int col, int f)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags = f; 
}

Fl_Flags Fl_ListHeader::column_flags(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags; 
}

Fl_Flags Fl_ListHeader::column_set_flag(int col, int f)
{
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags |= f;
}

Fl_Flags Fl_ListHeader::column_clear_flag(int col, int f)
{
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags &= ~f;
}

Fl_Flags Fl_ListHeader::column_invert_flag(int col, int f)
{
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags ^= f;
}

const char *Fl_ListHeader::label()
{ 
	if(attr_list.size()==0) return 0;
	attr *a = (attr*)attr_list[0];
	return a->label; 
}

const char *Fl_ListHeader::label(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->label;
}

void Fl_ListHeader::copy_label(int col, const char *txt)
{
	attr *a = (attr*)attr_list[col];
    if(a->flags&FL_COPIED_LABEL) free((void*)a->label);
    if(txt) {
        a->label = strdup(txt);
        a->flags |= FL_COPIED_LABEL;
    } else {
        a->label = 0;
        a->flags &= ~FL_COPIED_LABEL;
    }
}

void Fl_ListHeader::label(int col, const char *text)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->label = text; 
}

Fl_Font Fl_ListHeader::label_font(int col)
{
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->font;
}

int Fl_ListHeader::label_size(int col)
{
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->font_size;
}


void Fl_ListHeader::label_font(int col, Fl_Font font)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->font = font; 
}

void Fl_ListHeader::label_size(int col, int size)
{
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->font_size = size; 
}

void Fl_ListHeader::label_color(int col, Fl_Color color)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->color = color; 
}

void Fl_ListHeader::image(int col, Fl_Image *im)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->image = im; 
}

void Fl_ListHeader::image(int col, Fl_Image &im)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->image = &im; 
}

Fl_Image *Fl_ListHeader::image(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->image; 
}

void Fl_ListHeader::clear()
{
    for(uint n=0; n<attr_list.size(); n++) {
		attr *a = (attr*)attr_list[n];
        if(a->flags & FL_COPIED_LABEL)
            if(a->label) 
				free((void *)a->label);
    }
}

#define SORT_ARROW 8

void Fl_ListHeader::draw()
{    
	fl_push_matrix();
    int total_w=0;

    for(uint n=0; n<attr_list.size(); n++)
    {		
		attr *a = (attr*)attr_list[n];		

        Fl_Flags f = a->flags;
        Fl_Color c = button_color();
        button_box()->draw(0, 0, a->width, h(), c, f);

        const char *txt = a->label;
        if(txt) {
            int iw=0, ih=0;
            if(a->image) {
                a->image->measure(iw,ih);
            }

            int X=0,Y=0,W=a->width,H=h();
            if(f&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {X += 3; W -= 6;}

            if(sort_col==(int)n && sort_type>=0 && sort_type<Fl_ListView::SORT_UNKNOWN)
                W-=(SORT_ARROW+2);
			
			int tw=W-iw;
			if(tw>0) {
				fl_font(a->font, float(a->font_size));
				char *pbuf = fl_cut_line(txt, W-iw);
				Fl_Widget::label(pbuf);
			}

            //Clear CLIP flag if set, cause we clip anyway =)
            if(align() & FL_ALIGN_CLIP) Fl_Widget::clear_flag(FL_ALIGN_CLIP);

			fl_push_clip(0, 0, a->width-DRAG_DIST, h());
			
			Fl_Widget::label_color(a->color);
			Fl_Widget::label_font(a->font);
			Fl_Widget::label_size(a->font_size);
            Fl_Image *si = Fl_Widget::image();
            Fl_Widget::image(a->image);
            draw_label(X, Y, W, H, f|(flags()&(FL_SELECTED|FL_INACTIVE)));
            Fl_Widget::image(si);

            if(sort_col==(int)n) {
                switch(sort_type) {
                case Fl_ListView::SORT_ASC:
                    draw_glyph(FL_GLYPH_UP, a->width-DRAG_DIST-SORT_ARROW, h()/2-SORT_ARROW/2, SORT_ARROW, SORT_ARROW, f|(flags()&(FL_SELECTED|FL_INACTIVE)));
                    break;
                case Fl_ListView::SORT_DESC:
                    draw_glyph(FL_GLYPH_DOWN, a->width-DRAG_DIST-SORT_ARROW, h()/2-SORT_ARROW/2, SORT_ARROW, SORT_ARROW, f|(flags()&(FL_SELECTED|FL_INACTIVE)));
                    break;
                default:
                    break;
                }
            }
            fl_pop_clip();
        }
        
		fl_translate(a->width, 0);
        total_w+=a->width;		
    }

    // Fill space after last column
    int xf = LIST->xposition()+LIST->w()-total_w;
    if(xf>0) { fl_color(Fl_Widget::color()); fl_rectf(0, 0, xf, h()); }    

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
    uint n, xp;

    switch(ev)
    {
    case FL_PUSH:
        inside=-1;
        col_start=0;
        col_to_drag=0;
        xp = LIST->xposition();
        mx = Fl::event_x()+xp;
        for(n=0; n<attr_list.size(); n++) {
			attr *a = (attr*)attr_list[n];
            col_to_drag=n;
            if(mx > a->width + col_start-DRAG_DIST && mx < a->width + col_start+DRAG_DIST) {
                dragging=true;
                break;
            }
            if(mx > col_start && mx < col_start+a->width)
                inside=n;
            col_start+=a->width;
        }

        if(!dragging && inside >= 0) {
			attr *a = (attr*)attr_list[inside];
            a->flags |= FL_VALUE;
            redraw(FL_DAMAGE_ALL);
            LIST->redraw(FL_DAMAGE_CHILD);
        }
        return 1;//dragging ? 1 : 0;

    case FL_RELEASE:		
        if(inside >= 0 && (((attr*)attr_list[inside])->flags & FL_VALUE) == FL_VALUE)
        {
			attr *a = (attr*)attr_list[inside];
			a->flags &= ~FL_VALUE;
            redraw(FL_DAMAGE_ALL);
            LIST->redraw(FL_DAMAGE_CHILD);

            sort_col = inside;
            sort_type = LIST->sort(inside);
        }
        dragging=false;
        col_start=0;
        return 0;

    case FL_DRAG:
        xp = ((Fl_ListView *)parent())->xposition();
        mx = Fl::event_x()+xp;
        if(dragging) {
			attr *a = (attr*)attr_list[col_to_drag];			
            a->width = mx-col_start;
            if(a->width-col_start-1/*-DRAG_DIST*/ < -col_start)
                a->width = 1;//DRAG_DIST;
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
        for(n=0; n<attr_list.size(); n++) {
			attr *a = (attr*)attr_list[n];
            if(mx > a->width + col_start-DRAG_DIST && mx < a->width + col_start+DRAG_DIST) {
                got_cursor = true;
                fl_cursor(FL_CURSOR_WE);
                break;
            }
            col_start+=a->width;
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

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

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

	calc_total_h = true;
	first_vis = -1;
	total_height = 0;
    item_      = 0;    
    yposition_ = xposition_ = 0;
    scrolldy = scrolldx = 0;
    sort_type_ = SORT_UNKNOWN;

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

	Fl_Group::current(this);
}

Fl_ListView::~Fl_ListView() {
}

static int scol=-1;
static int col_sort_asc(const void *w1, const void *w2) {
    Fl_ListView_Item *i1 = ITEM(*(Fl_ListView_Item **)w1);
    Fl_ListView_Item *i2 = ITEM(*(Fl_ListView_Item **)w2);
    return strcmp(i1->label(scol)?i1->label(scol):"", i2->label(scol)?i2->label(scol):"");
}
static int col_sort_desc(const void *w1, const void *w2) {
    Fl_ListView_Item *i1 = ITEM(*(Fl_ListView_Item **)w1);
    Fl_ListView_Item *i2 = ITEM(*(Fl_ListView_Item **)w2);
    return strcmp(i2->label(scol)?i2->label(scol):"", i1->label(scol)?i1->label(scol):"");
}

// Returns sort mode: ASC,DESC,UNKNOWN
int Fl_ListView::sort(int column)
{
	if(scol!=column) sort_type_=SORT_UNKNOWN;

    scol = column;
    sort_type_++;
    if(sort_type_>SORT_UNKNOWN)
        sort_type_=SORT_ASC;

    switch(sort_type_) {
    case SORT_ASC:
        array().sort(col_sort_asc);
        break;
    case SORT_DESC:
        array().sort(col_sort_desc);
        break;
    default:
        break;
    }

	calc_total_h = true;
    relayout();
    redraw();
    return sort_type_;
}

Fl_Widget* Fl_ListView::top()
{
    if(!children()) return 0;
    return item(child(0));
}

Fl_Widget* Fl_ListView::next()
{
	if(!item()) return 0;
    int next_i = find(item())+1;
    if(next_i >= children()) return 0;
    Fl_Widget *w = child(next_i);
    item(w);
    return w;
}

Fl_Widget* Fl_ListView::prev()
{
	if(!item()) return 0;
    int prev_i = find(item())-1;
    if(prev_i < 0) return 0;
    Fl_Widget *w = child(prev_i);
    item(w);
    return w;
}

bool Fl_ListView::show_item(Fl_Widget *w)
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
Fl_Widget* Fl_ListView::item_at(int Y)
{
    if(Y < 0) Y = 0;
	if(!children()) return 0;

	// THIS IS LAME!!! :)
	int avg_h = int(total_height/children());
	int n = yposition_/avg_h-100;
	if(n<0) n=0;
	int start = ITEM(child(n))->num;

    // move forward to the item:
    Fl_Widget *w=0;
    for(int a=start; a<children(); a++)
    {
        w=child(a);
		if(Y>w->y() && Y<w->y()+w->h())
			return w;
    }    
    return 0;
}

void Fl_ListView::damage_item(Fl_Widget *item)
{
    item->set_damage(FL_DAMAGE_ALL);    
}

void Fl_ListView::draw_row(int x, int y, int w, int h, Fl_Widget *widget, bool selected)
{    
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

void Fl_ListView::draw_item(Fl_Widget *widget)
{
	bool selected = SEL(widget);
    int y = widget->y() - yposition_+Y;

    int x = X-xposition_;
    int h = widget->h();

	Fl_Flags saved = widget->flags();
	widget->flags(widget->flags()|(selected?FL_SELECTED:0));	

    draw_row(X, y, W, h, widget, selected);

    y+=(leading()+1)/2-1;

    int save_y = widget->y();

    fl_push_matrix();
    fl_translate(x, 0);
	
    widget->w(W);
    widget->y(y);

    widget->draw();

    widget->y(save_y);

    fl_pop_matrix();

	widget->flags(saved);
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
	for(int n=0; n < children(); n++)
    {
		widget = child(n);
		if(widget->y()-yposition_ < -widget->height()) continue;       
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
    } else {
		fl_color(color());
		fl_rectf(x, y, w, h);
	}

    fl_pop_clip();
}

void Fl_ListView::draw_header()
{
    if(!(damage() & FL_DAMAGE_ALL) && !(_header->damage() & FL_DAMAGE_ALL))
        return;

	if(!_header->visible()) return;

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
            Fl_Widget *widget = 0;
            for(int n=0; n < children(); n++) {
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
	if(children()>0) vscrollbar.linesize(child(0)->height());

    int hy = hscrollbar.flags()&FL_ALIGN_TOP ? box()->dy() : Y+H;
    hscrollbar.resize(X, hy, W, hscrollbar.h());
    hscrollbar.value(xposition_, W, 0, max_cols_w/*max_width*/);
	if(children()>0) hscrollbar.linesize(child(0)->height());
}

void Fl_ListView::calc_index()
{
    int a; int wy=0;
    Fl_ListView_Item *widget = 0;
    for(a=0; a < children(); a++) {
		widget = (Fl_ListView_Item *)child(a);
		widget->num = a;		
		widget->y(wy);
		wy+=widget->h();
    }
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

    // count all the items scrolled off the top:
    int a;
	int widgety=0;
    Fl_ListView_Item *widget = 0;
    for(a=0; a < children(); a++)
    {
        widget = (Fl_ListView_Item *)child(a);        
        widget->y(widgety);
        widget->layout();

		widgety+=widget->h();

		if(calc_total_h) widget->num = a;
		if(!calc_total_h && widgety>Y+H+yposition_) break;
    }
	
	if(calc_total_h) total_height = widgety;
	calc_total_h = false;

    if(find_def) find_default_sizes();

    layout_scrollbars();

    if((layout_damage() & FL_LAYOUT_XYWH) && _header->visible()) {
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
int Fl_ListView::select(Fl_Widget *w, int value)
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
int Fl_ListView::select_only(Fl_Widget *w)
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
            Fl_ListView_Item *i = (Fl_ListView_Item *)item_at(my);
            if(!i) return 0;

            if(event == FL_DRAG)
            {
                if(move())
                {
                    if(sel_item)
                    {
                        if(selection.size() == 1) //Move one
                        {
							int oldy = sel_item->y();
                            int place = ITEM(i)->num;
                            if(my < sel_item->y()-2) { //Up
                                place--;
                                if(place>=-1) {
									i->num++;
                                    sel_item->num--;
									ITEM(sel_item)->y(i->y());
									i->y(oldy);
                                    insert(*sel_item, place+1);
									show_item(sel_item);
									redraw(FL_DAMAGE_CONTENTS);
                                }
                            }
                            else if(my > sel_item->y()+sel_item->h()+2) //Down
                            {				
                                place++;
                                if(place<=children()) {																		
									i->num--;
                                    sel_item->num++;
									ITEM(sel_item)->y(i->y());
									i->y(oldy);
                                    insert(*sel_item, place);
									show_item(sel_item);
									redraw(FL_DAMAGE_CONTENTS);
                                }
                            }							                            

                        } else if(selection.size() > 1) //Move many
                        {
                            if(my < sel_item->y()-2) //UP
                            {
                                int cnt = ITEM(sel_item)->num - ITEM(i)->num;
                                if(ITEM(selection.item(selection.size()-1))->num-cnt >= 0) {
                                    moveselection_up(cnt);     
									calc_index();
                                    show_item(sel_item);
									redraw(FL_DAMAGE_CONTENTS);
                                }
                            }
                            else if(my > sel_item->y()+sel_item->h()+2) //DOWN
                            {
                                int cnt = ITEM(i)->num - ITEM(sel_item)->num;
                                if(ITEM(selection.item(0))->num+cnt < children()) {
                                    moveselection_down(cnt);   
									calc_index();
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
							select_items(sel_item->num, i->num);
							item(i);
							show_item(i);						
							redraw(FL_DAMAGE_CHILD);
						}
                    }
                    return 1;

                } else { // end multi

                    select_only(i);
                    item(i);
					show_item(i);						
					redraw(FL_DAMAGE_CHILD);
                    return 1;

                }
            } // end if( event != FL_PUSH )
            else if(event == FL_PUSH) {

                // If different item, set clicks to 0
                if(i != item())	Fl::event_clicks(0);

				item(i);
                damage_item(i);                
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
						show_item(i);						
						redraw(FL_DAMAGE_CHILD);
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
						show_item(i);						
						redraw(FL_DAMAGE_CHILD);
                        return 1;
                    } else {
                        //Normal push
                        select_only(i);
                        drag_type = 1;
                        sel_item  = i;
						show_item(i);						
						redraw(FL_DAMAGE_CHILD);
                        return 1;
                    }

                } else { // LEFT_MOUSE && multi()

                    select_only(i);
                    sel_item  = i;
					show_item(i);						
					redraw(FL_DAMAGE_CHILD);
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
					printf("SET ITEM!\n");
                    //Set item to first visible
                    //layout();
                    //item(child(first_vis));
                    return 1;
                }
                break;

            } // event_key
            break;
        } // FL_KEYBOARD
    case FL_MOUSEWHEEL:
        {
			if(vscrollbar.visible())
				return vscrollbar.send(event);
			else if(hscrollbar.visible())
				return hscrollbar.send(event);
			break;
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
    return ITEM(*(Fl_ListView_Item **)w2)->num - ITEM(*(Fl_ListView_Item **)w1)->num;
}

void Fl_ListView::sort_selection() {
    selection.sort(cmp);
}

void Fl_ListView::moveselection_up(int dy)
{	
    uint n=selection.size();
    while(n--) 
	{
		Fl_ListView_Item *i = (Fl_ListView_Item *)selection.item(n);
		Fl_ListView_Item *oldi = (Fl_ListView_Item *)child(i->num-dy);		
		insert(*i, i->num-dy);
    }    
}

void Fl_ListView::moveselection_down(int dy)
{	
    for(uint n=0; n<selection.size(); n++) 
	{        
		Fl_ListView_Item *i = (Fl_ListView_Item *)selection.item(n);
		Fl_ListView_Item *oldi = (Fl_ListView_Item *)child(i->num+dy);
		insert(*i, i->num+dy+1);
    }
}

void Fl_ListView::remove_selection()
{
    int a = 0;
    for(uint n=0; n<selection.size(); n++) {
        Fl_Widget *item = selection.item(n);
        if(!a) a = find(item);
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
    item_ = 0;
    total_height = 0;
	selection.clear();
	Fl_Group::clear();
}

void Fl_ListView::remove(int index)
{
    Fl_Widget *w = child(index);
	if(w) {		
		if(w==item_) item_ = 0;		
	}
	calc_total_h = true;
	Fl_Group::remove(index);
}

void Fl_ListView::add(Fl_Widget &w)
{	
	calc_total_h = true;	
	Fl_Group::add(w);
}

void Fl_ListView::find_default_sizes()
{
	int a, i;
	Fl_Int_List max_col_w;	

	bool do_find=false;
	for(a=0; a<columns(); a++) {
		max_col_w.append(0);
		if(column_width(a) < 0) do_find = true;
	}

	if(!do_find) return;

    for(a=0; a<children(); a++) {
        Fl_ListView_Item *widget = (Fl_ListView_Item *)child(a);
        for(i=0; i<columns(); i++) {
            if(column_width(i) > 0) continue;
            if(max_col_w[i] < widget->width(i)+20)
                max_col_w[i] = widget->width(i)+20;
        }
    }

    for(i=0; i<columns(); i++) {
        if(column_width(i) > 0) continue;
        column_width(i, max_col_w[i]);
    }

    find_def = false;
}

