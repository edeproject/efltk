#include <efltk/Fl_Table_Base.h>
#include <efltk/fl_draw.h>

#include <stdio.h>
#include <stdlib.h>

void Fl_Table_Base::ctor_init()
{
    box(FL_DOWN_BOX);
    type(TRANSPARENT_RESIZE | BOTH);

    // Private members
    m_scrolled = false;
    m_row_cols_changed = true;

    m_rows = m_cols = 0;
    m_row_header_w = 50;
    m_default_col_w = 70;
    m_col_header_h = 20;
    m_default_row_h = 20;
    m_row_header = m_col_header = 0;
    m_row_resize = m_col_resize = 0;
    m_row_resize_min = m_col_resize_min = 1;
    m_last_cursor = FL_CURSOR_DEFAULT;
    m_row_lookup.blocksize(1024);

    m_rowflags_size = 1;
    m_rowflags = (uchar*)malloc(1);
    m_rowflags[0] = NONE;

    m_colflags_size = 1;
    m_colflags = (uchar*)malloc(1);
    m_colflags[0] = NONE;

    // Protected members
    table_w = table_h = 0;
    toprow = leftcol  = 0;
    toprow_y = leftcol_x = 0;
    tix = tiy = tiw = tih = 0;
    wix = wiy = wiw = wih = 0;

    vscrollbar = new Fl_Scrollbar(w()-scrollbar_width(), 0, scrollbar_width(), h()-scrollbar_width());
    vscrollbar->linesize(10);
    vscrollbar->type(Fl_Slider::VERTICAL);
    vscrollbar->callback((Fl_Callback*)cb_vscrollbar, (void*)this);

    hscrollbar = new Fl_Scrollbar(0, h()-scrollbar_width(), w(), scrollbar_width());
    hscrollbar->linesize(10);
    hscrollbar->type(Fl_Slider::HORIZONTAL);
    hscrollbar->callback((Fl_Callback*)cb_hscrollbar, (void*)this);

    Fl_Group::remove(vscrollbar);
    Fl_Group::remove(hscrollbar);
    hscrollbar->parent(this);
    vscrollbar->parent(this);

    begin();
}

Fl_Table_Base::Fl_Table_Base(const char *l, int layout_size, Fl_Align layout_al, int label_w)
    : Fl_Group(l, layout_size, layout_al, label_w)
{
    ctor_init();
}

// Ctor
Fl_Table_Base::Fl_Table_Base(int X, int Y, int W, int H, const char *l) : Fl_Group(X,Y,W,H,l)
{
    ctor_init();
}

// Dtor
Fl_Table_Base::~Fl_Table_Base()
{
    delete hscrollbar;
    delete vscrollbar;

    free(m_rowflags);
    free(m_colflags);
}

bool Fl_Table_Base::show_row(unsigned row)
{
    int item_y  = row_scroll_position(row);
    int item_yh = item_y+row_height(row);
    int newtop = -1;

    bool need_move = false;

    if(item_y < yposition()) {
        newtop = item_y;
        need_move = true;
    } else if(item_yh > yposition()+tih) {
        newtop = item_yh-tih;
        need_move = true;
    }

    if(!need_move) return false;

    if(newtop<0) newtop = 0;
    else if(newtop > table_h-tih) newtop = table_h-tih;

    yposition(newtop);
    return true;
}

bool Fl_Table_Base::show_col(unsigned col)
{
    int item_x  = col_scroll_position(col);
    int item_xw = item_x+col_width(col);
    int newleft = -1;

    bool need_move = false;

    if(item_x < xposition()) {
        newleft = item_x;
        need_move = true;
    } else if(item_xw > xposition()+tiw) {
        newleft = item_xw-tiw;
        need_move = true;
    }

    if(!need_move) return false;

    if(newleft<0) newleft = 0;
    else if(newleft > table_w-tiw) newleft = table_w-tiw;

    xposition(newleft);
    return true;
}

// Scroll display so 'row' is at top
void Fl_Table_Base::top_row(unsigned row)
{
    if ( row >= row_count() ) row = row_count() - 1;
    if ( table_h <= tih )
        return;	// don't scroll if table smaller than window

    int newtop = row_scroll_position(row);
    if(newtop > table_h-tih) newtop = table_h-tih;

    yposition(newtop);
}

// Scroll display so 'col' is at left
void Fl_Table_Base::left_col(unsigned col)
{
    if ( col >= col_count() ) col = col_count() - 1;
    if ( table_w <= tiw )
        return;	// don't scroll if table smaller than window

    int newleft = col_scroll_position(col);
    if ( newleft > table_w-tiw ) {
        newleft = table_w-tiw;
    }
    xposition(newleft);
}

// Find scroll position of a row (in pixels)
int Fl_Table_Base::row_scroll_position(unsigned row)
{
    int y = 0;
    unsigned r = find_safe_top(yposition(), y);
    if(r >= row) {
        y = 0;
        r = find_safe_top(0, y); // Happends sometimes.. (very rarely)
    }
    for (; r < row; r++ ) {
        if(!visible_row(r)) continue;
        y += row_height(r);
    }
    return y;
}

// Find scroll position of a column (in pixels)
int Fl_Table_Base::col_scroll_position(unsigned col)
{
    int x = 0;
    for(unsigned t=0; t<col; t++ ) {
        if(!visible_col(t)) continue;
        x += col_width(t);
    }
    return x;
}

// Set height of a row
void Fl_Table_Base::row_height(unsigned row, int height)
{
    if(row >= row_count()) return;
    m_rowheights[row] = height;

    m_row_cols_changed = true;
    recalc_row_lookup();
}

// Set width of a column
void Fl_Table_Base::col_width(unsigned col, int width)
{
    if(col >= m_cols) return;
    m_colwidths[col] = width;

    m_row_cols_changed = true;
    relayout();
}

void Fl_Table_Base::row_height_all(int height)
{
    for( unsigned r=0; r<m_rowheights.size(); r++ )
        m_rowheights[r] = height;

    m_row_cols_changed = true;
    recalc_row_lookup();
}

void Fl_Table_Base::col_width_all(int width)
{
    for( unsigned c=0; c<m_colwidths.size(); c++ )
        m_colwidths[c] = width;

    m_row_cols_changed = true;
    relayout();
}

// Return row/col clamped to reality
bool Fl_Table_Base::row_col_clamp(unsigned &R, unsigned &C)
{
    bool clamped = false;

    if(R >= row_count()) { R = row_count()-1; clamped = true; }
    if(C >= col_count()) { C = col_count()-1; clamped = true; }

    return clamped;
}

// Return row/col clamped to reality
bool Fl_Table_Base::row_col_clamp(int &R, int &C)
{
    bool clamped = false;

    if(R < 0) { R = 0; clamped = true; }
    else if((unsigned)R >= row_count()) { R = row_count()-1; clamped = true; }

    if(C < 0) { C = 0; clamped = true; }
    else if((unsigned)C >= col_count()) { C = col_count()-1; clamped = true; }

    return clamped;
}

// Return bounding region for given context
void Fl_Table_Base::get_bounds(TableContext context, int &X, int &Y, int &W, int &H)
{
    switch ( context )
    {
    case CONTEXT_COL_HEADER:

        // Column header clipping.
        X = tix;
        Y = tiy - col_header_height();
        W = tiw;
        H = col_header_height();
        return;

    case CONTEXT_ROW_HEADER:

        // Row header clipping.
        X = tix - row_header_width();
        Y = tiy;
        W = row_header_width();
        H = tih;
        return;

    case CONTEXT_TABLE:

        // Table inner dimensions
        X = tix; Y = tiy; W = tiw; H = tih;
        return;

        // TODO: Add other contexts..
    default:
        fprintf(stderr, "get_bounds(): context %d unimplemented\n", (int)context);
        return;
    }
    //NOTREACHED
}

// Find row/col beneath cursor
//
//    Returns R/C and context.
//    Also returns resizeflag, if mouse is hovered over a resize boundary.
//
#define event_inside2(widget) Fl::event_inside(widget->x(), widget->y(), widget->w(), widget->h())
Fl_Table_Base::TableContext Fl_Table_Base::cursor2rowcol(unsigned &R, unsigned &C, ResizeFlag &resizeflag)
{
    int max_y = yposition() + tih;
    int max_x = xposition() + tiw;

    // return values
    R = C = 0;
    resizeflag = RESIZE_NONE;

    // Event in scrollbar?
    // Then event is not in table context.
    if(( vscrollbar->visible() && event_inside2(vscrollbar) ) ||
       ( hscrollbar->visible() && event_inside2(hscrollbar) ) )
    {
        return CONTEXT_NONE;
    }

    int X, Y, W, H;

    // Row header?
    if(row_header())
    {
        get_bounds(CONTEXT_ROW_HEADER, X, Y, W, H);

        // Inside a row heading?
        if ( Fl::event_inside(X, Y, W, H) )
        {
            Y = toprow_y;
            // Scan visible rows until found
            for(R=toprow; R < row_count(); R++ )
            {
                if(!visible_row(R)) continue;
                H = row_height(R);
                if(Y > max_y) break;

                int ey = Y-yposition()+tiy;
                if( Fl::event_y() >= ey && Fl::event_y() < (ey+H) )
		{
		    // Found row?
		    //     If cursor over resize boundary, and resize enabled,
		    //     enable the appropriate resize flag.
		    //
		    if ( row_resize() )
                    {
                        if ( Fl::event_y() <= (ey+3-0) ) { resizeflag = RESIZE_ROW_ABOVE; }
                        if ( Fl::event_y() >= (ey+H-3) ) { resizeflag = RESIZE_ROW_BELOW; }
                    }
		    return CONTEXT_ROW_HEADER;
                }
                Y += H;
	    }
	    // Must be in row header dead zone
            return CONTEXT_NONE;
	}
    }

    // Column header?
    if(col_header())
    {
        get_bounds(CONTEXT_COL_HEADER, X, Y, W, H);

        // Inside a column heading?
        if ( Fl::event_inside(X, Y, W, H) )
        {
            // Scan visible columns until found
            X = leftcol_x;
            for(C = leftcol; C < col_count(); C++ )
            {
                if(!visible_col(C)) continue;
                W = col_width(C);
                if(X > max_x) break;

                int ex = X-xposition()+tix;
                if ( Fl::event_x() >= ex && Fl::event_x() < (ex+W) )
                {
                    // Found column?
		    //     If cursor over resize boundary, and resize enabled,
		    //     enable the appropriate resize flag.
		    //
		    if ( col_resize() )
		    {
                        if ( Fl::event_x() <= (ex+3-0) ) { resizeflag = RESIZE_COL_LEFT; }
                        if ( Fl::event_x() >= (ex+W-3) ) { resizeflag = RESIZE_COL_RIGHT; }
		    }
		    return CONTEXT_COL_HEADER;
                }
                X += W;
	    }

	    // Must be in column header dead zone
	    return CONTEXT_NONE;
	}
    }

    // Mouse somewhere in table?
    //     Scan visible r/c's until we find it.
    //
    if ( Fl::event_inside(tix, tiy, tiw, tih) )
    {
        // DO NOT CALL find_cell(), causes huge overheat.
        Y = toprow_y;
        for(R=toprow; R < row_count(); R++)
        {
            if(!visible_row(R)) continue;
            H = row_height(R);
            if(Y > max_y) break;

            X=leftcol_x;
            for(C = leftcol; C < col_count(); C++)
            {
                if(!visible_col(C)) continue;
                W = col_width(C);
                if(X > max_x) break;
                if(Fl::event_inside(X-xposition()+tix, Y-yposition()+tiy, W, H))
                    return CONTEXT_CELL;
                X += W;
            }
            Y += H;
        }

    }

    // Somewhere else
    return CONTEXT_NONE;
}

void Fl_Table_Base::position2rowcol(int x, int y, int &R, int &C) const
{
    // return values
    R = C = -1;
    int X, Y;

    if(y>=0 && y<table_h) {
        Y = 0;
        unsigned r = find_safe_top(y, Y);
        for(; r < row_count(); r++)
        {
            if(!visible_row(r)) continue;
            if(y>=Y && y<=Y+row_height(r)) {
                R = r;
                break;
            }
            Y += row_height(r);
        }
    }

    if(x>=0 && x<table_w) {
        X=0;
        for(unsigned c = 0; c < col_count(); c++)
        {
            if(!visible_col(c)) continue;
            if(x>=X && x<=X+col_width(c)) {
                C = c;
                break;
            }
            X += col_width(C);
        }
    }
}

// Find X/Y/W/H for cell at R/C
//  with X/Y/W/H set to zero.
//  return false if not found
//
bool Fl_Table_Base::find_cell(TableContext context, unsigned R, unsigned C, int &X, int &Y, int &W, int &H)
{
    if(row_col_clamp(R, C)) {
        X=Y=W=H=0;
        return false;
    }

    X = col_scroll_position(C) - xposition() + tix;
    Y = row_scroll_position(R) - yposition() + tiy;
    W = col_width(C);
    H = row_height(R);

    switch( context )
    {
    case CONTEXT_COL_HEADER:
        Y = wiy;
        H = col_header_height();
        break;

    case CONTEXT_ROW_HEADER:
        X = wix;
        W = row_header_width();
        break;

    case CONTEXT_CELL:
    case CONTEXT_TABLE:
        break;

        // TODO -- HANDLE OTHER CONTEXTS
    default:
        Fl::warning("Fl_Table_Base::find_cell(): unknown context %d\n", (int)context);
        return false;
    }

    return true;
}

void Fl_Table_Base::xposition(int X)
{
    /*
    int R,C;
    position2rowcol(X, 0, R,C);
    int newx = col_scroll_position(C);
    // Do not let last col partially visible.
    if(newx+tiw < table_w-col_width(col_count()-1)) {
        X = newx;
    }*/

    ((Fl_Slider*)hscrollbar)->value(X);
    m_scrolled = true;
    relayout();
    redraw(FL_DAMAGE_SCROLL);
}

void Fl_Table_Base::yposition(int Y)
{
    /*
    int R,C;
    position2rowcol(0, Y, R,C);
    int newy = row_scroll_position(R);
    // Do not let last row partially visible.
    if(newy+tih < table_h-row_height(row_count()-1)) {
        Y = newy;
    }*/

    ((Fl_Slider*)vscrollbar)->value(Y);
    m_scrolled = true;
    relayout();
    redraw(FL_DAMAGE_SCROLL);
}

void Fl_Table_Base::visible_row(int row, bool val)
{
    int old = m_rowflags[row];
    if(val) m_rowflags[row] &= ~INVISIBLE;
    else    m_rowflags[row] |= INVISIBLE;

    if(old!=m_rowflags[row]) {
        m_row_cols_changed = true;
        recalc_row_lookup();
    }
}

void Fl_Table_Base::visible_col(int col, bool val)
{
    if(val) m_colflags[col] &= ~INVISIBLE;
    else    m_colflags[col] |= INVISIBLE;
}

void Fl_Table_Base::resizable_row(int row, bool val)
{
    if(val) m_rowflags[row] &= ~NON_RESIZABLE;
    else    m_rowflags[row] |= NON_RESIZABLE;
}

void Fl_Table_Base::resizable_col(int col, bool val)
{
    if(val) m_colflags[col] &= ~NON_RESIZABLE;
    else    m_colflags[col] |= NON_RESIZABLE;
}

// Set number of rows
void Fl_Table_Base::row_count(unsigned val)
{
    {
        if(val > m_rowheights.size()) {
            // enlarge
            while( val > m_rowheights.size() )
                m_rowheights.append(default_row_height());
        } else {
            // shrink
            m_rowheights.resize(val);
        }
    }

    // Keep row flags in sync
    {
        int size = val;
        unsigned newcap = (size * 9 / 64 + 1) * 8;
        if(newcap!=m_rowflags_size) {
            m_rowflags = (uchar*)realloc(m_rowflags, newcap);
            if(newcap > m_rowflags_size)
                memset(m_rowflags+m_rowflags_size, NONE, newcap-m_rowflags_size);
            m_rowflags_size = newcap;
        }
    }

    m_rows = val;
    m_row_cols_changed = true;
    recalc_row_lookup();
}

// Set number of cols
void Fl_Table_Base::col_count(unsigned val)
{
    {
        if(val > m_colwidths.size()) {
            // enlarge
            while ( val > m_colwidths.size() )
                m_colwidths.append(default_col_width());
        } else {
            // shrink
            m_colwidths.resize(val);
        }
    }

    // Keep col flags in sync
    {
        int size = val;
        unsigned newcap = (size * 9 / 64 + 1) * 8;
        if(newcap!=m_colflags_size) {
            m_colflags = (uchar*)realloc(m_colflags, newcap);
            if(newcap > m_colflags_size)
                memset(m_colflags+m_colflags_size, NONE, newcap-m_colflags_size);
            m_colflags_size = newcap;
        }
    }

    m_cols = val;
    m_row_cols_changed = true;
    relayout();
}

// Change mouse cursor to different type
void Fl_Table_Base::change_cursor(Fl_Cursor newcursor)
{
    if ( newcursor != m_last_cursor )
    {
        fl_cursor(newcursor);//, FL_BLACK, FL_WHITE);
        m_last_cursor = newcursor;
    }
}


unsigned Fl_Table_Base::find_safe_top(int ypos, int &y) const
{
    if(!row_count() || ypos<=0 || m_row_lookup.size()==0) return 0;

    // Check this!
    for (int n=m_row_lookup.size()-1; n>=0; n--) {
        if (ypos >= m_row_lookup[n]) {
            y = m_row_lookup[n];
            return (n*1000);
        }
    }
    y=0;
    return 0;
}

void Fl_Table_Base::calc_row_lookup()
{
    m_row_lookup.clear();
    m_row_lookup.append(0);

    int Y=0;
    for(unsigned n=0; n<row_count(); n++) {
        if(!visible_row(n)) continue;
        if(n>1 && n%1000 == 0) {
            m_row_lookup.append(Y);
        }
        Y += m_rowheights[n];
    }
}

// Recalculate the window dimensions
void Fl_Table_Base::recalc_dimensions()
{
    // Recal to* (Table Outer), ti* (Table Inner), wi* ( Widget Inner)
    tix = wix = box()->dx();
    tiy = wiy = box()->dy();

    tiw = wiw = w() - box()->dw();
    tih = wih = h() - box()->dh();

    // Trim window if headers enabled
    if ( col_header() ) {
        tiy += col_header_height();
        tih -= col_header_height();
    }

    if ( row_header() ) {
        tix += row_header_width();
        tiw -= row_header_width();
    }

    // Make scroll bars disappear if window large enough
    {
        // First pass: can hide via window size?
        int hidev = table_h < tih;
        int hideh = table_w < tiw;

        int vsize = vscrollbar->visible() ? vscrollbar->w() : 0;
        int hsize = hscrollbar->visible() ? hscrollbar->h() : 0;

        // Second pass: Check for interference
        if ( !hideh & hidev ) {
            hidev = ( ( table_h - tih + hsize ) < 0 );
        }
        if ( !hidev & hideh ) {
            hideh = ( ( table_w - tiw + vsize ) < 0 );
        }

        if(type()&VERTICAL) {
            if(type()&ALWAYS_ON)
                hidev = 0;
        } else
            hidev = 1;

        if(type()&HORIZONTAL) {
            if(type()&ALWAYS_ON)
                hideh = 0;
        } else
            hideh = 1;

        // Determine scrollbar visibility, trim ti[xywh]
        if ( hidev ) {
            vscrollbar->hide();
        } else {
            vscrollbar->show();
            if(scrollbar_align()&FL_ALIGN_LEFT) {
                tix += vscrollbar->w();
            }
            tiw -= vscrollbar->w();
        }
        if ( hideh ) {
            hscrollbar->hide();
        } else {
            hscrollbar->show();
            if(scrollbar_align()&FL_ALIGN_TOP)
                tiy += hscrollbar->h();
            tih -= hscrollbar->h();
        }
        
		if(!m_scrolled) {
			// Clamp vertical scrollbar
			if(vscrollbar->value() > table_h-tih && table_h>tih) vscrollbar->Fl_Slider::value(table_h-tih);
			else if(vscrollbar->value()<0 || table_h<tih) vscrollbar->Fl_Slider::value(0);

			// Clamp horizontal scrollbar
			if(hscrollbar->value() > table_w-tiw && table_w>tiw) hscrollbar->Fl_Slider::value(table_w-tiw);
			else if(hscrollbar->value()<0 || table_w<tiw) hscrollbar->Fl_Slider::value(0);
		}

        // Recalc scrollbar sizes:

        int hor_y = wiy+wih-hscrollbar->h();
        int hor_x = wix;

        int ver_y = wiy;
        int ver_x = wix+wiw-vscrollbar->w();

        if(scrollbar_align()&FL_ALIGN_LEFT && vscrollbar->visible()) {
            ver_x = wix;
            hor_x += vscrollbar->w();
        }
        if(scrollbar_align()&FL_ALIGN_TOP && hscrollbar->visible()) {
            hor_y = wiy;
            ver_y += hscrollbar->h();
        }

        vscrollbar->resize(ver_x, ver_y,
                           vscrollbar->w(), wih - (hscrollbar->visible()?hscrollbar->h():0));
        vscrollbar->value(yposition(), tih, 0, table_h);

        // Horizontal
        hscrollbar->resize(hor_x, hor_y,
                           wiw - (vscrollbar->visible()?vscrollbar->w():0), hscrollbar->h());
        hscrollbar->value(xposition(), tiw, 0, table_w);

    }
}

// Resize FLTK override
//     Handle resize events if user resizes parent window.
//
// Table resized: recalc internal data
//    Call this whenever the window is resized.
//    Recalculates the scrollbar sizes.
//    Makes no assumptions about any pre-initialized data.
//
void Fl_Table_Base::layout()
{
    //printf("void Fl_Table_Base::layout(%x)\n", layout_damage());

    if(m_recalc_row_lookup) {
        calc_row_lookup();
        m_recalc_row_lookup = false;
    }

    if(m_row_cols_changed) {
        table_h = row_scroll_position(row_count());
        table_w = col_scroll_position(col_count());
        m_row_cols_changed = false;
    }

    recalc_dimensions();

    {
        // Top row
        int y = 0;
        unsigned row = find_safe_top(yposition(), y);
        int voff = yposition();
        for (; row < m_rows; row++ ) {
            if(!visible_row(row)) continue;
            y += row_height(row);
            if ( y >= voff ) { y -= row_height(row); break; }
        }
        toprow = row;
        toprow_y = y;

        // Left column
        unsigned col;
        int x, hoff = xposition();
        for( col=x=0; col < col_count(); col++ ) {
            if(!visible_col(col)) continue;
            x += col_width(col);
            if ( x >= hoff ) { x -= col_width(col); break; }
        }
        leftcol = col;
        leftcol_x = x;
    }

    if(!m_scrolled) {
        table_layout(CONTEXT_TABLE, row_count(), col_count());
    } else {
        table_layout(CONTEXT_SCROLLED, toprow, leftcol);
        m_scrolled = false;
    }

    // Call Fl_Group layout to make normal widgets layout correctly
    if(children()>0) {
        Fl_Group::layout();
    } else {
        Fl_Widget::layout();
    }
}

static int resizing_col = -1; // Column being dragged
static int resizing_row = -1; // Row being dragged
static int min_col_x    = -1;    // Minimum X for dragged column
static int min_row_y    = -1;    // Minimum Y for dragged row

#define fill_rect(xx,yy,ww,hh) \
	fl_push_clip( (xx), (yy), (ww), (hh) ); \
	draw_group_box(); \
	fl_pop_clip()

// Draw the entire Fl_Table_Base
//    Override the draw() routine to draw the table.
//    Then tell the group to draw over us.
//
void Fl_Table_Base::draw()
{
    // Handle overlay drawing only
    if(transparent_resize()) {
        if(resizing_col!=-1) {
            fl_overlay_rect(min_col_x+col_width(resizing_col), wiy, 2, wiy+wih);
            return;
        }
        else if(resizing_row!=-1) {
            fl_overlay_rect(wix, min_row_y+row_height(resizing_row), wix+wiw, 2);
            return;
        }
    }

    int X,Y,W,H;

    int max_y = yposition() + tih;
    int max_x = xposition() + tiw;

    // let user's drawing routine prepare for new page
    table_draw(CONTEXT_BEGIN,0,0,tix,tiy,tiw,tih);

    bool damage_all = (damage() & ~FL_DAMAGE_CHILD)>0;
    if(damage_all) {
        draw_frame();
    }

    //printf("void Fl_Table_Base::draw(%x) %d\n", damage(), damage_all);

    // Draw row headers, if any
    if(row_header())
    {
        get_bounds(CONTEXT_ROW_HEADER, X, Y, W, H);
        fl_push_clip(X,Y,W,H);
        Y=toprow_y;
        for(unsigned r = toprow; r < row_count(); r++ )
        {
            if(!visible_row(r)) continue;
            H = row_height(r);
            if(Y > max_y) break;
            table_draw(CONTEXT_ROW_HEADER, r, 0, X, Y-yposition()+tiy, W, H);
            Y += H;
        }
        fl_pop_clip();
    }

    // Draw column headers, if any
    if(col_header())
    {
        get_bounds(CONTEXT_COL_HEADER, X, Y, W, H);
        fl_push_clip(X,Y,W,H);
        X=leftcol_x;
        for(unsigned c = leftcol; c < col_count(); c++ )
        {
            if(!visible_col(c)) continue;
            W = col_width(c);
            if(X > max_x) break;
            table_draw(CONTEXT_COL_HEADER, 0, c, X-xposition()+tix, Y, W, H);
            X += W;
        }
        fl_pop_clip();
    }

    fl_push_clip(tix,tiy,tiw,tih);

    // Let fltk widgets draw themselves first
    // Do this after table_draw(CONTEXT_BEGIN), in case user moved widgets around.
    if(children()>0) {
        if(damage_all) {
            int n;
            //draw_inside_label();
            for(n = 0; n < children(); n++)
            {
                Fl_Widget& w = *child(n);
                w.set_damage(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE);
                update_child(w);
            }
            // labels are drawn without the clip for back compatability so they
            // can draw atop sibling widgets:
            for(n = 0; n < children(); n++) draw_outside_label(*child(n));
        }
        else
        {
            // only some child widget has been damaged, draw them without
            // doing any clipping.  This is for maximum speed, even though
            // this may result in different output if this widget overlaps
            // another widget or a label.
            for (int n = 0; n < children(); n++)
            {
                Fl_Widget& w = *child(n);
                if (w.damage() & FL_DAMAGE_CHILD_LABEL) {
                    draw_outside_label(w);
                    w.set_damage(w.damage() & ~FL_DAMAGE_CHILD_LABEL);
                }
                update_child(w);
            }
        }
    }

    // Draw all cells.
    {
        Y = toprow_y;
        for(unsigned r=toprow; r < row_count(); r++ )
        {
            if(!visible_row(r)) continue;

            H = row_height(r);
            if(Y > max_y) break;

            X=leftcol_x;
            for(unsigned c = leftcol; c < col_count(); c++ )
            {
                if(!visible_col(c)) continue;
                W = col_width(c);
                if(X > max_x) break;
                table_draw(CONTEXT_CELL, r, c, X-xposition()+tix, Y-yposition()+tiy, W, H);
                X += W;
            }
            Y += H;
        }
    }

    fl_pop_clip();

    table_draw(CONTEXT_END,0,0,tix,tiy,tiw,tih);

    // Draw little rectangle in corner of headers
    if(row_header() && col_header()) {
        //fl_color(button_color());
        //fl_rectf(tix-row_header_width(), tiy-col_header_height(), row_header_width(), col_header_height());
		fill_rect(tix-row_header_width(), tiy-col_header_height(), row_header_width(), col_header_height());
    }

    // Set drawing color for rest of method
    // fl_color(color());

    // Table width smaller than window? Fill remainder with rectangle
    if ( table_w < tiw )
    {
		//fl_rectf(tix+table_w, tiy, tiw-table_w, tih);
		fill_rect(tix+table_w, tiy, tiw-table_w, tih);        
		
		// Col header? fill that too
		if ( col_header() )
		{

			/*fl_rectf(tix + table_w, 
				wiy, 
				// get that corner just right..
                (tiw - table_w),
				col_header_height());*/
			fill_rect(tix + table_w, 
				wiy, 
				// get that corner just right..
                (tiw - table_w),
				col_header_height());
		}
    }

    // Table height smaller than window? Fill remainder with rectangle
    if ( table_h < tih )
    {
		//fl_rectf(tix, tiy + table_h, tiw, tih - table_h);
		fill_rect(tix, tiy + table_h, tiw, tih - table_h);

		if ( row_header() )
		{
            // NOTE:
            //     Careful with that lower corner; don't use tih; when eg.
            //     table->box(FL_THIN_UPFRAME) and hscrollbar hidden,
            //     leaves a row of dead pixels.
            //
			/*
            fl_rectf(wix,
                     tiy + table_h,
                     row_header_width(),
                     (wiy+wih)-(tiy+table_h)-(hscrollbar->visible() ? hscrollbar->h():0));
			*/
			fill_rect(wix,
                     tiy + table_h,
                     row_header_width(),
                     (wiy+wih)-(tiy+table_h)-(hscrollbar->visible() ? hscrollbar->h():0));
        }
    }

    // draw the scrollbars:
    if(damage() & (FL_DAMAGE_ALL|FL_DAMAGE_CONTENTS)) {
        vscrollbar->set_damage(FL_DAMAGE_ALL);
        hscrollbar->set_damage(FL_DAMAGE_ALL);
        if(vscrollbar->visible() && hscrollbar->visible()) {
            // fill in the little box in the corner
            //fl_color(button_color());
            //fl_rectf(vscrollbar->x(), hscrollbar->y(), vscrollbar->w(), hscrollbar->h());
			fill_rect(vscrollbar->x(), hscrollbar->y(), vscrollbar->w(), hscrollbar->h());
        }
    }
    update_child(*vscrollbar);
    update_child(*hscrollbar);
}

int Fl_Table_Base::handle(int event)
{
    // Check for scrollbar events

    // These are handled by eFLTK (belowmouse())
    if(event!=FL_DRAG && event!=FL_RELEASE && event!=FL_LEAVE && event!=FL_DND_LEAVE)
    {
        if(vscrollbar->visible()) {
            if(event_inside2(vscrollbar)) {
                change_cursor(FL_CURSOR_DEFAULT);
                return vscrollbar->send(event);
            }
        }
        if(hscrollbar->visible()) {
            if(event_inside2(hscrollbar)) {
                change_cursor(FL_CURSOR_DEFAULT);
                return hscrollbar->send(event);
            }
        }
    }

    static int dragging_x = -1,   // Starting x position for horiz drag
               dragging_y = -1;   // Starting y position for vert drag

    static TableContext push_context = CONTEXT_NONE;	// FL_PUSH context

    // let FLTK group handle events first
    int ret = Fl_Group::handle(event);

    // Which row/column are we over?
    unsigned R, C;
    // which resizing area are we over? (0=none)
    ResizeFlag resizeflag;
    TableContext context = cursor2rowcol(R, C, resizeflag);

    switch ( event )
    {
    case FL_FOCUS:
    case FL_UNFOCUS:
        ret = 1;
        break;

    case FL_PUSH:
        // Save these for later when button released.
        //  Do this for all mouse push buttons.
        //
        push_context = context;

        if ( context == CONTEXT_COL_HEADER && Fl::event_button() == 1 && resizeflag )
        {
            // Start resize if left mouse clicked on column border.
            //
            //    "ret = 1" ensures we get drag events from now on.
            //    (C-1) is used if mouse is over the left hand side of the cell,
            //    so that we resize the next column over to the left.
            //
            resizing_col = ( resizeflag & RESIZE_COL_LEFT ) ? C-1 : C;
            if(resizing_col<0) { resizing_col=-1; return 0; }
            if(!resizable_col(resizing_col)) { resizing_col=-1; return 0; }
            min_col_x = col_scroll_position(resizing_col) - xposition() + tix;
            resizing_row = -1;
            dragging_x = Fl::event_x();
        }
        else if ( context == CONTEXT_ROW_HEADER && Fl::event_button() == 1 && resizeflag )
        {
            // Start resize if left mouse clicked on row border.
            //
            //    "ret = 1" ensures we get drag events from now on.
            //    (R-1) is used if mouse is over the top of the cell,
            //    so that we resize the row above.
            //
            resizing_row = ( resizeflag & RESIZE_ROW_ABOVE ) ? R-1 : R;
            if(resizing_row<0) { resizing_row=-1; return 0; }
            if(!resizable_row(resizing_row)) { resizing_row=-1; return 0; }
            min_row_y = row_scroll_position(resizing_row) - yposition() + tiy;
            resizing_col = -1;
            dragging_y = Fl::event_y();
        }

        ret = 1;
        break;

    case FL_DRAG:

        if ( resizing_col > -1)
        {
            // Dragging column?
            //
            //    Let user drag even /outside/ the row/col widget.
            //    Don't allow column width smaller than 1.
            //    Continue to show FL_CURSOR_WE at all times during drag.
            //
            int offset = dragging_x - Fl::event_x();
            int new_w = col_width(resizing_col) - offset;
            if ( new_w < m_col_resize_min ) new_w = m_col_resize_min;

            dragging_x = Fl::event_x();
            if(dragging_x < min_col_x) dragging_x = min_col_x;

            if(!transparent_resize()) {
                col_width(resizing_col, new_w);
                table_layout(CONTEXT_COL_HEADER, 0, resizing_col);
            } else {
                m_colwidths[resizing_col] = new_w;
            }

            redraw();
            change_cursor(FL_CURSOR_WE);
            ret = 1;
        }
        else if ( resizing_row > -1 )
        {
            // Dragging row?
            //
            //    Let user drag even /outside/ the row/col widget.
            //    Don't allow row width smaller than 1.
            //    Continue to show FL_CURSOR_NS at all times during drag.
            //
            int offset = dragging_y - Fl::event_y();
            int new_h = row_height(resizing_row) - offset;
            if ( new_h < m_row_resize_min ) new_h = m_row_resize_min;

            dragging_y = Fl::event_y();
            if(dragging_y < min_row_y) dragging_y = min_row_y;

            if(!transparent_resize()) {
                row_height(resizing_row, new_h);
                table_layout(CONTEXT_ROW_HEADER, resizing_row, 0);
            } else {
                m_rowheights[resizing_row] = new_h;
            }

            redraw();
            change_cursor(FL_CURSOR_NS);
            ret = 1;
        }
        break;

    case FL_RELEASE:

        if ( Fl::event_button() == 1 && (resizing_col!=-1 || resizing_row!=-1))
        {
            change_cursor(FL_CURSOR_DEFAULT);

            if(transparent_resize()) {
                if(resizing_col!=-1)
                    table_layout(CONTEXT_COL_HEADER, 0, resizing_col);
                else
                    table_layout(CONTEXT_ROW_HEADER, resizing_row, 0);

                fl_overlay_clear();

                m_row_cols_changed = true;
                relayout();
                redraw();
            }
            resizing_col = -1;
            resizing_row = -1;
            return 1;
        }
        break;

    case FL_MOVE:

        // in column header? and resize enabled + near resize boundary?
        if ( context == CONTEXT_COL_HEADER && resizeflag )
        {
            change_cursor(FL_CURSOR_WE); // show resize cursor
        }
        // in row header? and resize enabled + near resize boundary?
        else if ( context == CONTEXT_ROW_HEADER && resizeflag )
        {
            change_cursor(FL_CURSOR_NS); // show resize cursor
        }
        else
        {
            change_cursor(FL_CURSOR_DEFAULT); // normal cursor
        }

        ret = 1;
        break;

    default:
        change_cursor(FL_CURSOR_DEFAULT);
        break;
    }

    // It's safe to virtual table_handle now.
    if(resizing_col==-1 && resizing_row==-1) {
        // We reach here, if cursor is on row/col header and not resizing.
        if(table_handle(context, R, C, event))
            ret = 1;
    }

    // Handle mousewheel after Fl_Group handle
    if(event == FL_MOUSEWHEEL && !ret) {
        ret = vscrollbar->send(event);
        if(!ret) ret = hscrollbar->send(event);
    }

    return ret;
}
