#include <efltk/Fl_ListView.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_ListView_Header.h>

static void revert(Fl_Style* s) {
    //s->box = FL_DOWN_BOX;
    s->button_box = FL_NO_BOX;
    s->leading = 2;
}

static Fl_Named_Style style("ListView", revert, &Fl_ListView::default_style);
Fl_Named_Style* Fl_ListView::default_style = &::style;

Fl_ListView *Fl_ListView::current=0;

void Fl_ListView::ctor_init()
{
    accept_focus(true);
    when(FL_WHEN_CHANGED);
    //FL_WHEN_NOT_CHANGED|FL_DATA_CHANGE);
    style(default_style);

    m_header = new Fl_ListView_Header(this);
    m_type_in_mode = TYPE_IN_SELECT;
    //m_type_in_mode = TYPE_IN_HIDE;

    m_sort_type = Fl_ListView::SORT_NONE;
    m_sort_col = -1;

    cur_row = -1;

    default_row_height(0);

    // enable col header and resizing
    col_header(true);
    col_resize(true);

    m_needsetup = true;
    m_draw_stripes = false;

    begin();
}

Fl_ListView::Fl_ListView(const char *l, int layout_size, Fl_Align layout_al, int label_w)
: Fl_Table_Base(l, layout_size, layout_al, label_w)
{
    ctor_init();
}

Fl_ListView::Fl_ListView(int X, int Y, int W, int H, const char *l)
: Fl_Table_Base(X, Y, W, H, l)
{
    ctor_init();
}

Fl_ListView::~Fl_ListView()
{
    clear();
    clear_columns();
}

void Fl_ListView::clear()
{
    cur_row = -1;
    unselect_all();

    for(unsigned n=0; n < row_count(); n++) {
        Fl_ListView_Item *w = items[n];
        w->parent(0);
        delete w;
    }
    items.clear();
    row_count(0);

    relayout();
}

void Fl_ListView::draw_row(unsigned row, int w, int h) const
{
    if(selected_row(row)) {

        Fl_Color c = selection_color();
        // If not focused, make color grayed
        if(!focused()) c = fl_color_average(c, FL_GRAY, 0.40);

        fl_color(c);
        fl_rectf(0, 0, w, h);
        return;
    }

    if(draw_stripes()) {

        Fl_Color c1 = fl_lighter(button_color());
        if(row & 1) {
            // draw odd-numbered items with a dark stripe, plus contrast-enhancing
            // pixel rows on top and bottom:
            fl_color(c1);
            fl_rectf(0, 0, w, h);

            fl_color(fl_lighter(c1));
            fl_line(0, 0, w, 0);
            fl_line(0, h-1, w, h-1);
            return;
        }
    }

    fl_push_clip(0, 0, w, h);
    draw_group_box();
    fl_pop_clip();
    //fl_color(parent()->color());
    //fl_rectf(x, y, w, h);
}

void Fl_ListView::table_draw(TableContext context, unsigned R, unsigned C,
    int X, int Y, int W, int H)
{
    if(context==CONTEXT_NONE) return;

    static int drawing_row = -1;
    static bool drawed_header = false;
    bool damage_all = (damage() & ~FL_DAMAGE_CHILD)>0;

    if(drawed_header && context!=CONTEXT_COL_HEADER) {
        header()->set_damage(0);
        drawed_header = false;
    }

    if(context==CONTEXT_BEGIN) {
        drawing_row = -1;
        drawed_header = false;
    }
    else if(context==CONTEXT_END) {
        if(drawing_row>=0)
            child(drawing_row)->set_damage(0);
    }
    else if(context==CONTEXT_CELL) {
        fl_push_matrix();       
        fl_translate(X, Y);

        Fl_ListView_Item *item = items[R];              

        // Draw row
        if(C==leftcol && (damage_all || item->damage()&FL_DAMAGE_ALL)) {
            draw_row(R, table_w, row_height(R));
        }

        if(!damage_all) {
            if(item->damage())
                item->draw_cell(R, C, W, H);
        } else {            
            item->set_damage(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE);
            item->draw_cell(R, C, W, H);
        }

        if(drawing_row!=(int)R) {
            if(drawing_row>=0)
                child(drawing_row)->set_damage(0);
            drawing_row = R;
        }

        fl_pop_matrix();
    }
    else if(context==CONTEXT_COL_HEADER) {

        fl_push_matrix();
        fl_translate(X, Y);

        if(!damage_all) {
            if(header()->damage())
                header()->draw(C, W, H);
        } else {
            header()->set_damage(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE);
            header()->draw(C, W, H);
        }
        drawed_header = true;

        fl_pop_matrix();
    }
    else if(context==CONTEXT_ROW_HEADER) {
        fl_color(color());
        fl_rectf(X,Y,W,H);
    }
}

void Fl_ListView::layout()
{
    if(m_needsetup) {

        unsigned n;
        for(n=0; n < row_count(); n++) {
            //child(n)->index(n); //Set indexes also..
            if(row_height(n)==0) {
                items[n]->setup(n);
            }
        }

        // Find col width for -1 columns
        for(n=0; n<(unsigned)columns(); n++) {
            if(col_width(n)<0)
                col_width(n, preferred_col_width(n));
        }

        m_needsetup = false;
    }

    Fl_Table_Base::layout();
}

void Fl_ListView::resetup()
{
    for(unsigned n=0; n < row_count(); n++) {
        row_height(n, 0);
    }
    m_needsetup = true;
    relayout();
}

int Fl_ListView::handle(int event)
{
    return Fl_Table_Base::handle(event);
}

void Fl_ListView::table_layout(TableContext context, unsigned row, unsigned col)
{
    if(context==CONTEXT_COL_HEADER && width_changed_notify()) {
        bool need_relayout = false;
        for(unsigned n=0; n < row_count(); n++) {
            int oldh = row_height(n);
            items[n]->width_changed(n, col);
            if(row_height(n) != oldh) {
                need_relayout = true;
            }
        }
        if(need_relayout) {
            layout();
        }
    }
}

int Fl_ListView::table_handle(TableContext context, unsigned R, unsigned C, int event)
{
    static bool on_drag = false;

    static int sel_item = 0;
    static int last_dragged = 0;
    int current_item = 0;

    int ret = 0;
    if(!on_drag && (context==CONTEXT_COL_HEADER || header()->capture_events())) {
        ret = header()->handle(C, event);
        if(ret || header()->capture_events())
            return ret;
    }

    int shiftstate =
        (Fl::event_state() & FL_CTRL) ? FL_CTRL :
        (Fl::event_state() & FL_SHIFT) ? FL_SHIFT : 0;

    switch ( event )
    {
        case FL_FOCUS:
            reset_search();
        case FL_UNFOCUS:
            if(!selection.empty()) {
                for(unsigned n=0; n<selection.size(); n++) {
                    items[selection[n]]->set_damage(FL_DAMAGE_ALL);                 
                }   
                redraw();
            }
            return 1; //Keyboard focus

        case FL_MOVE:
        case FL_ENTER:
            Fl::belowmouse(this);
            ret = 1;
            break;

        case FL_PUSH:
            if(context==CONTEXT_CELL)
            {
                last_dragged = current_item = R;

                // Handle selection in table.
                // Select cell under cursor, and enable drag selection mode.

                cur_row = current_item;
                on_drag = true;

                if(Fl::event_button() == FL_LEFT_MOUSE && multi())
                {
                    switch(shiftstate) {
                        case FL_CTRL: {
                            // start a new selection block without changing state
                                select_row(current_item, 2);
                                sel_item = current_item;
                                show_row(current_item);
                                ret = 1;
                            }
                            break;

                        case FL_SHIFT: {
                            // We want to change the selection between
                            // the top most selected item and the just clicked item.
                            // start a new selection block without changing state
                                select_items(sel_item, current_item);
                                sel_item = current_item;
                                Fl::event_clicks(0);
                                show_row(current_item);
                                ret = 1;
                            }
                            break;

                        default: {
                                select_only_row(current_item);
                                sel_item = current_item;
                                show_row(current_item);
                                ret = 1;
                            }
                            break;
                    } //switch(shiftstate)

                } else { // LEFT_MOUSE && multi()

                    select_only_row(current_item);
                    sel_item = current_item;
                    show_row(current_item);
                    ret = 1;
                }

                if (when() & FL_WHEN_CHANGED) do_callback(FL_DATA_CHANGE);
                else set_changed();
            }
            break;

        case FL_DRAG: {
                if(!on_drag) break;

                if(context==CONTEXT_CELL) current_item = R;
                else                      current_item = row_at(yposition()+Fl::event_y()-tiy);
                if(current_item==-1) return 0;              

                if(multi())
                {                   
                    // Mark items selected
                    select_items(last_dragged, current_item);
                    show_row( (cur_row = current_item) );

                    if(sel_item!=current_item) {
                        if(when() & FL_WHEN_CHANGED) do_callback(FL_DATA_CHANGE);
                        else set_changed();
                    }

                } else { // end multi

                    if(!selected_row(current_item) || selected()>1) {
                        select_only_row(current_item, true);
                    }                    
                    show_row( (cur_row = current_item) );
                }
                last_dragged = current_item;
                return 1;
            }

        case FL_RELEASE:
            if(Fl::event_button() == 1) {
                on_drag = false;
                ret = 1;
            }

            if (when() & FL_WHEN_RELEASE && context==CONTEXT_CELL) {
                if (Fl::event_clicks()) {
                    do_callback(event);
                    Fl::event_clicks(0);
                    return 1;
                }
                do_callback(event);
            }
            break;

        case FL_KEY:
            ret = handle_key();

        default:
            break;
    }

    return ret;
}

int Fl_ListView::handle_key()
{
    if(!children()) return 0;

    Fl::event_clicks(0); // make program not think it is a double-click

    switch(Fl::event_key())
    {
        case FL_Home: {
                m_search_str.clear();
                yposition(0);
                item(child(0));
                select_only_row(0, true);
                return 1;
            }

        case FL_End: {
                m_search_str.clear();
                yposition(table_h - tih);
                item(child(children()-1));
                select_only_row(children()-1, true);
                return 1;
            }

        case FL_Up: {
                m_search_str.clear();
                int index;
                if(cur_row==-1) index = children()-1;
                else index = prev_row();
                if(index>=0) {
                    if(Fl::event_state(FL_SHIFT|FL_CTRL) && multi())
                        select_row(index, 1);
                    else
                        select_only_row(index, true);
                    show_row(index);
                    cur_row = index;
                }
                return 1;
            }

        case FL_Down: {
                m_search_str.clear();
                int index;
                if(cur_row==-1) index = 0;
                else index = next_row();
                if(index>=0 && index<int(children())) {
                    if(Fl::event_state(FL_SHIFT|FL_CTRL) && multi())
                        select_row(index, 1);
                    else
                        select_only_row(index, true);
                    show_row(index);
                    cur_row = index;
                }
                return 1;
            }

        case FL_Enter:
            if (!(when() & FL_WHEN_ENTER_KEY)) break;
            clear_changed();
            do_callback(FL_DATA_CHANGE);
            return 1;

        default: {
                int ret=0;
                ret = vscrollbar->send(FL_KEY);
                if(!ret) ret = hscrollbar->send(FL_KEY);

                if(ret)
                {
                    if(Fl::event_key()==FL_Page_Up)
                        select_only_row( row_at(yposition()), true );
                    else if(Fl::event_key()==FL_Page_Down)
                        select_only_row( row_at(yposition()+tih), true );

                    show_row(cur_row);
                    return 1;
                }
                else if(m_type_in_mode) {

            // Type-in search
                    bool bs = false;
                    switch (Fl::event_key())
                    {
                        case FL_BackSpace:
                            if(!m_search_str.empty()) {
                                m_search_str.sub_delete(m_search_str.length()-1);
                                bs = true;
                                break;
                            }
                            return 0;

                        case FL_Delete:
                        case FL_Escape:
                            reset_search();
                            return 1;

                        default:
                            break;
                    } //end switch (Fl::event_key())

                    int i;

            // insert any text:
                    if(Fl::compose(i) || bs)
                    {
                        if(!bs && !i && !Fl::event_length())
                            return 1;

                        Fl_String search_str = m_search_str;
                        if(!bs)
                            search_str.append(Fl::event_text(), Fl::event_length());

                        int index = find_text_row(search_str);
                //printf("Search str: (%s) / %d\n", search_str.c_str(), index);
                        if(index>-1) {
                            m_search_str = search_str;
                            if(type_in_mode()==TYPE_IN_SELECT) {

                                select_only_row(index, true);
                                show_row(index);

                            } else if(type_in_mode()==TYPE_IN_HIDE) {

                                unsigned col = (sort_col()>0) ? sort_col() : 0;
                                Fl_String search = search_str.lower_case();
                                for(unsigned n=0; n<row_count(); n++) {
                                    visible_row(n, match_text(search, items[n]->label(col)));
                                }
                                show_row(0);
                                redraw();
                            }
                            return 1;
                        }
                    } // end compose
                } // end if(m_type_in_mode)
                break;
            } // end default:

    } // event_key
    return 0;
}

void Fl_ListView::reset_search()
{
    if(!m_search_str.empty()) {
        m_search_str.clear();
    }

    if(type_in_mode()==TYPE_IN_HIDE) {
        bool need_redraw=false;
        for(unsigned n=0; n<row_count(); n++) {
            if(!visible_row(n)) {
                visible_row(n, true);
                need_redraw=true;
            }
        }
        if(need_redraw) {
            show_row(0);
            redraw();
        }
    }
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
    if(scol!=column) m_sort_type=SORT_NONE;

    m_sort_type++;
    if(m_sort_type==SORT_LAST_TYPE)
        m_sort_type=SORT_NONE;

    m_sort_col = scol = column;
    stype = m_sort_type;

    if(m_sort_type==SORT_NONE || m_columns[column]->type()==VAR_NONE)
        return SORT_NONE;

    unsigned n;
    Fl_ListItem_List list;
    Fl_Int_List flags;

    // We must preserve row flags, cause item indexes may change.
    // e.g. Selected items stays selected.
    for(n=0; n<row_count(); n++) {
        if(row_flags(n)) {
            list.append(items[n]);
            flags.append(row_flags(n));
            row_flags(n, 0);
        }
    }
    selection.clear();

    // Sort
    items.sort(fl_listview_sort);

    // Update row flags for new indexes
    for(n=0; n<list.size(); n++) {
        int new_index = items.index_of(list[n]);
        if(new_index>-1) {
            row_flags(new_index, flags[n]);
            if(selected_row(new_index)) {
                selection.append(new_index);
            }
        }
    }

    redraw();
    return m_sort_type;
}

Fl_ListItem_List &Fl_ListView::get_selection()
{
    stored_selection.clear();
    for(unsigned n=0; n<selection.size(); n++) {
        stored_selection.append(items[selection[n]]);
    }
    return stored_selection;
}

const Fl_ListItem_List &Fl_ListView::get_selection() const {
    return (const Fl_ListItem_List &)get_selection();
}

Fl_ListView_Item* Fl_ListView::next()
{
    if(cur_row==-1) return 0;
    unsigned next_i = cur_row+1;
    for(; next_i < row_count(); next_i++) {
        if(visible_row(next_i))
            break;
    }
    if(next_i >= row_count()) return 0;

    Fl_ListView_Item *w = items[next_i];
    return item(w);
}

Fl_ListView_Item* Fl_ListView::prev()
{
    if(cur_row<=0) return 0;
    int prev_i = cur_row-1;
    for(; prev_i>=0; prev_i--) {
        if(visible_row(prev_i))
            break;
    }
    if(prev_i < 0) return 0;

    Fl_ListView_Item *w = items[prev_i];
    return item(w);
}

int Fl_ListView::next_row()
{
    if(cur_row==-1) return -1;
    unsigned next_i = cur_row+1;
    for(; next_i < row_count(); next_i++) {
        if(visible_row(next_i))
            break;
    }
    if(next_i >= row_count()) return -1;
    cur_row = next_i;
    return next_i;
}

int Fl_ListView::prev_row()
{
    if(cur_row<=0) return -1;
    int prev_i = cur_row-1;
    for(; prev_i>=0; prev_i--) {
        if(visible_row(prev_i))
            break;
    }
    if(prev_i < 0) return 0;
    cur_row = prev_i;
    return prev_i;
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

int Fl_ListView::find_userdata_row(void *data, unsigned start_index, unsigned end_index) const
{
    if(row_count()<=0) return 0;

    if(start_index >= row_count())
        start_index = 0;
    if(end_index <= start_index || end_index >= row_count())
        end_index = row_count() - 1;

    for(unsigned n=start_index; n<=end_index; n++) {
        if(items[n]->user_data()==data)
            return n;
    }
    return -1;
}

Fl_ListView_Item *Fl_ListView::find_userdata(void *data, unsigned start_index, unsigned end_index) const
{
    if(row_count()<=0) return 0;

    if(start_index >= row_count())
        start_index = 0;
    if(end_index <= start_index || end_index >= row_count())        
        end_index = row_count() - 1;

    for(unsigned n=start_index; n<=end_index; n++) {        
        if(items[n]->user_data()==data)
            return items[n];
    }
    return 0;
}

bool Fl_ListView::match_text(const Fl_String &key, const char *text) const
{
    if(!text || !*text) return false;
    Fl_String tmp(text);
    return (strncmp(tmp.lower_case().c_str(), key.c_str(), key.length()) == 0);
}

int Fl_ListView::find_text_row(const char *text, int column, unsigned start_index, unsigned end_index) const
{
    if(row_count()<=0) return -1;
    if(!text || !*text) return -1;

    if(start_index >= row_count())
        start_index = 0;
    if(end_index <= start_index || end_index >= row_count())
        end_index = row_count() - 1;

    int col = (column<0) ? sort_col() : column;
    if(col<0) col = 0;

    Fl_String tmp(text);
    Fl_String search = tmp.lower_case();

    for(unsigned n=start_index; n<=end_index; n++) {
        if(match_text(search, items[n]->label(col)))
            return n;
    }
    return -1;
}

Fl_ListView_Item *Fl_ListView::find_text(const char *text, int column, unsigned start_index, unsigned end_index) const
{
    if(row_count()<=0) return 0;
    if(!text || !*text) return 0;

    if(start_index >= row_count())
        start_index = 0;
    if(end_index <= start_index || end_index >= row_count())
        end_index = row_count() - 1;

    int col = (column<0) ? sort_col() : column;
    if(col<0) col = 0;

    Fl_String tmp(text);
    Fl_String search = tmp.lower_case();    

    for(unsigned n=start_index; n<=end_index; n++) {
        if(match_text(search, items[n]->label(col)))
            return items[n];
    }
    return 0;
}

Fl_ListView_Item *Fl_ListView::item(Fl_ListView_Item *i)
{
    if(i && i->parent()!=this) return 0;

    if(i) {
        cur_row = items.index_of(i);
    } else {
        cur_row = -1;
    }
    return i;
}

// set current item to one at or before Y pixels from top of browser
int Fl_ListView::row_at(int Y) const
{
    if(!children()) return 0;
    if(Y < 0) return 0;
    if(Y > table_h) return items.size()-1;

    int R,C;
    position2rowcol(0, Y, R, C);
    return R;
}

// set current item to one at or before Y pixels from top of browser
Fl_ListView_Item* Fl_ListView::item_at(int Y) const
{
    if(!children()) return 0;
    if(Y < 0) return items[0];
    if(Y > table_h) return items[items.size()-1];

    int R,C;
    position2rowcol(0, Y, R, C);
    return items[R];
}

bool Fl_ListView::show_item(Fl_ListView_Item *w)
{
    if(!w || w->parent()!=this) return false;

    int index = items.index_of(w);
    if(index==-1) return false;

    int item_y  = row_scroll_position(index);
    int item_yh = item_y+row_height(index);

    if(item_y < yposition()) {
        yposition(item_y);
        return true;
    } else if(item_yh > yposition()+tih) {
        yposition(item_yh-tih);
        return true;
    }
    return false;
}

bool Fl_ListView::select_row(unsigned row, int value)
{
    if(set_select_flag(row, value)) {
        if(selected_row(row)) {
            selection.append(row);
        } else {
            selection.remove(row);
        }
        items[row]->redraw();
        return true;
    }
    return false;
}

bool Fl_ListView::select_only_row(unsigned row, bool do_callback)
{   
    unselect_all();
    if (set_select_flag(row, 1)) {
        selection.append(row);
        items[row]->redraw();
        cur_row = row;
        if(do_callback) {
            if(when()&(FL_WHEN_CHANGED)) Fl_Widget::do_callback(FL_DATA_CHANGE);
            else set_changed();
        }
    }
    cur_row = row;
    return true;
}

void Fl_ListView::select_items(unsigned from, unsigned to)
{
    int start=0, end=0;
    if(to < from) {
        start=to;
        end=from+1;
    } else {
        start=from;
        end=to+1;
    }

    for(int n=start; n<end; n++) {
        if(selection.index_of(n)==-1) {
            if(set_select_flag(n, 1))
                items[n]->redraw();
            selection.append(n);
        }
    }
    if (when() & FL_WHEN_CHANGED) do_callback(FL_DATA_CHANGE);
    else set_changed();
}

bool Fl_ListView::unselect_all()
{
    if(selection.empty()) return false;

    for(unsigned n=0; n<selection.count(); n++) {
        set_select_flag(selection[n], 0);
        items[selection[n]]->redraw();
    }
    selection.clear();
    return true;
}

bool Fl_ListView::set_select_flag(unsigned row, int flag)
{
    if(row >= row_count() ) { return 0; }

    bool oldval = selected_row(row);
    if(!selectable_row(row)) flag=0;

    if(flag==0) {
        row_flags(row, row_flags(row)&~SELECTED);
    } else if(flag==1) {
        row_flags(row, row_flags(row)|SELECTED);
    } else if(flag==2) {
        row_flags(row, row_flags(row)^SELECTED);
    }
    return (oldval!=selected_row(row));
}

void Fl_ListView::select_all_rows(int flag)
{
    for(unsigned row=0; row<row_count(); row++)
    {
        if(flag==0) {
            row_flags(row, row_flags(row)&~SELECTED);
        } else if(flag==1) {
            row_flags(row, row_flags(row)|SELECTED);
        } else if(flag==2) {
            row_flags(row, row_flags(row)^SELECTED);
        }
    }
    redraw();
}

void Fl_ListView::inactive_row(unsigned row, bool val)
{
    if(val) row_flags(row, row_flags(row)|INACTIVE);
    else    row_flags(row, row_flags(row)&~INACTIVE);
}

void Fl_ListView::selectable_row(unsigned row, bool val)
{
    if(val) row_flags(row, row_flags(row)&~NON_SELECTABLE);
    else    row_flags(row, row_flags(row)|NON_SELECTABLE);
}

int Fl_ListView::find(const Fl_ListView_Item *item) const
{
    if(!item) return children();
    // Search backwards so if children are deleted in backwards order
    // they are found quickly:
    for(int index = children(); index--;)
        if(child(index) == item)
            return index;
    return children();
}

void Fl_ListView::insert(Fl_ListView_Item &item, int pos)
{
    if(item.parent()) {
        int n = item.parent()->find(item);
        if(item.parent() == this) {
            if(pos > n) pos--;
            if(pos == n) return;
        }
        item.parent()->remove(n);
    }

    // Update parent and index
    item.parent(this);

    if(children() == 0) {
        // allocate for 1 child
        items.append(&item);
    } else {
        items.insert(pos, &item);
    }

    // Update row count in table
    if(items.size() != row_count())
        row_count(items.size());

    // Relayout
    m_needsetup = true;
    relayout();
}

void Fl_ListView::add(Fl_ListView_Item &item)
{
    insert(item, children());
}

void Fl_ListView::remove(int index)
{
    if(index >= int(children())) return;

    Fl_ListView_Item *w = child(index);
    if(cur_row==index) cur_row = -1;

    w->parent(0);
    items.remove(index);

    row_count(items.size());

    // Relayout
    m_needsetup = true;
    relayout();
}

///////////////////////////////
// Column functions

void Fl_ListView::columns(unsigned count)
{
    uint old_size = m_columns.size();
    uint new_size = count;

    if(old_size < new_size) {
        for(uint n=old_size; n<new_size; n++) {
            add_column("");
        }
    } else {
        for(uint n=new_size; n<old_size; n++) {
            delete m_columns[n];
        }
        m_columns.resize(new_size);        
    }

    col_count(new_size);
    // Relayout
    m_needsetup = true;
    relayout();
    redraw();
}

Fl_ListView_Column *Fl_ListView::add_column(const char *name, int width, Fl_Variant_Type column_type)
{
    Fl_ListView_Column *col = new Fl_ListView_Column();
    col->label(name);
    col->type(column_type);
    m_columns.append(col);
    col_count(m_columns.size());
    col_width(m_columns.size()-1, width);

    // Relayout
    m_needsetup = true;
    relayout();

    return col;
}

void Fl_ListView::remove_column(unsigned index)
{
    Fl_ListView_Column *col = m_columns[index];
    m_columns.remove(index);
    col_count(m_columns.size());

    // Relayout
    m_needsetup = true;
    relayout();

    delete col;
}

bool Fl_ListView::remove_column(const char *name)
{
    Fl_ListView_Column *col = 0;
    for(unsigned n=0; n<m_columns.size(); n++) {
        if(m_columns[n]->label() == name) {
            col = m_columns[n];
            m_columns.remove(n);
            break;
        }
    }
    if(col) {
        col_count(m_columns.size());
        delete col;

        // Relayout
        m_needsetup = true;
        relayout();

        return true;
    }
    return false;
}

void Fl_ListView::clear_columns()
{
    for(unsigned n=0; n<m_columns.size(); n++) {
        Fl_ListView_Column *col = m_columns[n];
        delete col;
    }

    m_columns.clear();
    col_count(0);

    // Relayout
    m_needsetup = true;
    relayout();
}

int Fl_ListView::preferred_col_width(int col)
{
    int max = 0;
    for(unsigned a=0; a < row_count(); a++) {
        Fl_ListView_Item *widget = items[a];
        int preferred_w = widget->preferred_width(col);
        if(max < preferred_w+20)
            max = preferred_w+20;
    }
    return max;
}

void Fl_ListView::find_default_sizes()
{
    unsigned a;
    unsigned i;
    Fl_Int_List max_col_w;

    bool do_find=false;
    for(i=0; i<columns(); i++) {
        max_col_w.append(0);
        if(col_width(i) < 0)
            do_find = true;
    }

    if(!do_find)
        return;

    for(a=0; a < row_count(); a++) {
        Fl_ListView_Item *widget = items[a];
        for(i=0; i<columns(); i++) {
            if(col_width(i) > 0) continue;
            int preferred_w = widget->preferred_width(i);
            if(max_col_w[i] < preferred_w+20)
                max_col_w[i] = preferred_w+20;
        }
    }

    for(i=0; i<columns(); i++) {
        if(col_width(i) > 0) continue;
        column_width(i, max_col_w[i]);
    }
}

void Fl_ListView::fill(Fl_Data_Source &ds, const char *user_data_column_name_)
{
    // Try to memorize the current selected row so we can restore it after fill.
    int selected_data = 0L;
    Fl_ListView_Item *selected_item = item();
    if (selected_item)
        selected_data = selected_item->argument();

    // Final version should replace the existing rows (truncate them,if necessary).
    clear();

    if (!ds.open()) return;

    Fl_String user_data_column_name(user_data_column_name_);

    // First version is very primitive.
    // Final version should replace the existing columns, if necessary.

    int user_data_column = -1;

    unsigned columnCount = ds.field_count();
    if (!columnCount) return;
    unsigned actualColumn = 0;
    for (unsigned col = 0; col < columnCount; col++) {
        Fl_Data_Field& df = ds.field(col);

        if (!df.visible) continue;
        if (!user_data_column_name.empty() && df.name() == user_data_column_name) {
            user_data_column = col;
            continue;
        }

        // Check if the column of that name/type exists already.
        // If exists, leave it intact. This way user may resize
        // columns and we won't destroy the user' column widths
        int width = 100;
        if (df.width >= 0) {
            width = df.width * text_size() * 2 / 3;
        }
        if (actualColumn < m_columns.size()) {
            Fl_ListView_Column *column = m_columns.item(actualColumn); 
            if (df.name() != column->label()) {
                column->label(df.name());
                col_width(actualColumn,width);
            }
            column->type(df.type());
        } else {
            add_column(df.name(),width,df.type());
        }

        m_columns[actualColumn]->flags(df.flags);
        actualColumn++;
    }
    columns(actualColumn);

    begin();

    while (!ds.eof()) {
        //Fl_ListView_ItemExt *item = new Fl_ListView_ItemExt();
        Fl_ListView_Item *item = new Fl_ListView_Item();
        item->columns(columnCount);
        item->user_data(ds.user_data());
        actualColumn = 0;
        for (int col = 0; col < (int)columnCount; col++) {
            Fl_Data_Field& df = ds.field(col);
            if (!df.visible) continue;
            if (int(col) == user_data_column) {
                item->argument(df.as_int());
            } else {
                //item->flags(col, df.flags);
                if (df.type() == VAR_IMAGEPTR) item->image(actualColumn, (Fl_Image *)df.as_image());
                else item->label(actualColumn, df.as_string());
                actualColumn++;
            }
        }
        ds.next();
    }
    ds.close();
    end();
    if (selected_data) {
        selected_item = find_userdata((void *)selected_data);
        if (selected_item)
            select_only(selected_item);
    }
}
