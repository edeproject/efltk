#include <efltk/Fl_ListView_Item.h>
#include <efltk/Fl_ListView.h>
#include <efltk/fl_draw.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Fl_ListView_Item::Fl_ListView_Item(const char *label1,
    const char *label2,
    const char *label3,
    const char *label4,
    const char *label5)
{
    user_data_ = 0;
    image_  = 0;
    y_ = h_ = 0;
    damage_ = 0;
    parent_ = 0;

    int cols = 0;
    if(label5) cols=5;
    else if(label4) cols=4;
    else if(label3) cols=3;
    else if(label2) cols=2;
    else if(label1) cols=1;

    columns(cols);
    if(cols>0) label(0, label1);
    if(cols>1) label(1, label2);
    if(cols>2) label(2, label3);
    if(cols>3) label(3, label4);
    if(cols>4) label(4, label5);

    if(Fl_ListView::current)
        Fl_ListView::current->add(*this);
}

Fl_ListView_Item::~Fl_ListView_Item()
{
    for(uint n=0; n<attr_list.size(); n++) {
        delete (Fl_ListItem_Attr *)attr_list[n];
    }
}

void Fl_ListView_Item::redraw(uchar c) 
{ 
    damage_ = c;
    if(parent()) parent()->redraw(FL_DAMAGE_CHILD);
}

Fl_ListItem_Attr *Fl_ListView_Item::create_attr(int col)
{
    Fl_ListItem_Attr *a = new Fl_ListItem_Attr;
    a->col_width = 0;
    return a;
}

void Fl_ListView_Item::add_attr(int col)
{
    attr_list[col] = create_attr(col);
}

int Fl_ListView_Item::compare_strings(Fl_ListView_Item *other, int column, int sort_type)
{
    const Fl_String &txt = label(column);
    const Fl_String &other_txt = other->label(column);

    switch(sort_type) {
        case Fl_ListView::SORT_ASC:
            return strcmp(txt.c_str(), other_txt.c_str());
        case Fl_ListView::SORT_DESC:
            return strcmp(other_txt.c_str(), txt.c_str());
        default:
            break;
    }
    return index()-other->index();
}

int Fl_ListView_Item::compare_integers(Fl_ListView_Item *other, int column, int sort_type)
{
    const Fl_String &txt = label(column);
    const Fl_String &other_txt = other->label(column);

    switch(sort_type) {
        case Fl_ListView::SORT_ASC:
            return atoi(txt.c_str()) > atoi(other_txt.c_str());
        case Fl_ListView::SORT_DESC:
            return atoi(txt.c_str()) < atoi(other_txt.c_str());
        default:
            break;
    }
    return index()-other->index();
}

int Fl_ListView_Item::compare_floats(Fl_ListView_Item *other, int column, int sort_type)
{
    const Fl_String &txt = label(column);
    const Fl_String &other_txt = other->label(column);

    switch(sort_type) {
        case Fl_ListView::SORT_ASC:
            return atof(txt.c_str()) > atof(other_txt.c_str());
        case Fl_ListView::SORT_DESC:
            return atof(txt.c_str()) < atof(other_txt.c_str());
        default:
            break;
    }
    return index()-other->index();
}

int Fl_ListView_Item::compare_dates(Fl_ListView_Item *other, int column, int sort_type)
{
    const Fl_String &txt = label(column);
    const Fl_String &other_txt = other->label(column);

    switch(sort_type) {
        case Fl_ListView::SORT_ASC:
            return Fl_Date_Time(txt.c_str()) > Fl_Date_Time(other_txt.c_str());
        case Fl_ListView::SORT_DESC:
            return Fl_Date_Time(txt.c_str()) < Fl_Date_Time(other_txt.c_str());
        default:
            break;
    }
    return index()-other->index();
}

int Fl_ListView_Item::compare_datetimes(Fl_ListView_Item *other, int column, int sort_type)
{
    const Fl_String &txt = label(column);
    const Fl_String &other_txt = other->label(column);

    switch(sort_type) {
        case Fl_ListView::SORT_ASC:
            return Fl_Date_Time(txt.c_str()) > Fl_Date_Time(other_txt.c_str());
        case Fl_ListView::SORT_DESC:
            return Fl_Date_Time(txt.c_str()) < Fl_Date_Time(other_txt.c_str());
        default:
            break;
    }
    return index()-other->index();
}

bool Fl_ListView_Item::selected() const
{
    return (parent()->get_selection().index_of(this)>-1);
}

uint Fl_ListView_Item::columns() const
{
    return attr_list.size();
}

void Fl_ListView_Item::columns(uint count)
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
            Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[n];
            delete (Fl_ListItem_Attr*)a;
        }
        attr_list.resize(new_size);
    }
}

void Fl_ListView_Item::check_columns(uint count) {
    if(count+1>columns()) columns(count+1);
}

void Fl_ListView_Item::draw_cell(int col, int w, bool sel)
{
    if((uint)col>=attr_list.size()) return;

    Fl_Flags f = parent()->column_flags(col) | (parent()->flags()&FL_INACTIVE);

    int X=0, Y=0, W=w, H=h();
    // Draw user defined border
    Fl_Boxtype box = parent()->button_box();
    box->draw(0, 0, W, H, fl_inactive(parent()->button_color(), f), FL_INVISIBLE);

    box->inset(X, Y, W, H);
    fl_push_clip(X, Y, W, H);

    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    const char *txt = a->col_label;
    if(txt) {
        int iw=0;
        int y = h()/2;

        if(col==0 && image_) {
            image_->draw(X, y-image_->height()/2, image_->width(), image_->height(), f|(sel?FL_SELECTED:0));
            iw = image_->width()+2;
            X+=iw;
        }

        fl_font(parent()->text_font(), parent()->text_size());
        fl_color(fl_inactive(sel?parent()->selection_text_color():parent()->text_color(), f));

        //HMM... cutting should be optional
        //if(strchr(txt, '\n')) txt = fl_cut_multiline(txt, w-iw-6);
        //else txt = fl_cut_line(txt, w-iw-6);

        fl_draw(txt, X, 0, W-X, H, (f & FL_ALIGN_MASK) );
    }
    fl_pop_clip();
}

// Measure the space the draw() will take:
void Fl_ListView_Item::layout()
{
    int H = 0;
    fl_font(parent()->text_font() , parent()->text_size());
    for(uint n=0; n<attr_list.size(); n++) {
        Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[n];
        if(!a->col_label.empty()) {
            int w=300,h=0;
            fl_measure(a->col_label, w, h, FL_ALIGN_LEFT);
            if(h>H) H=h;
            a->col_width = w;
        }

        if(image_ && n==0) {
            int w,h;
            image_->measure(w,h);
            a->col_width += w;
            if(h>H) H=h;
        }
    }
    H += parent()->button_box()->dh();
    h(int(H+parent()->leading()));
}

int Fl_ListView_Item::column_width(int col) const
{
    if((uint)col>=attr_list.size()) return -1;
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    return a->col_width;
}

const Fl_String &Fl_ListView_Item::label() const
{
    if(attr_list.size()==0) return Fl_String::null_object;
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[0];
    return a->col_label;
}

const Fl_String &Fl_ListView_Item::label(int col) const
{
    if((uint)col>=attr_list.size()) return Fl_String::null_object;
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    return a->col_label;
}

void Fl_ListView_Item::label(int col, const char *text)
{
    check_columns(col);
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    a->col_label = text;
}

void Fl_ListView_Item::label(int col, const Fl_String &text)
{
    check_columns(col);
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    a->col_label = text;
}

///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////

Fl_ListView_ItemExt::Fl_ListView_ItemExt(const char *label1,
    const char *label2,
    const char *label3,
    const char *label4,
    const char *label5)
: Fl_ListView_Item(0,0,0,0,0)
{
    if(parent())
        leading_ = parent()->leading();
    else
        leading_ = 1;

    int cols = 0;
    if(label5) cols=5;
    else if(label4) cols=4;
    else if(label3) cols=3;
    else if(label2) cols=2;
    else if(label1) cols=1;

    columns(cols);
    if(cols>0) label(0, label1);
    if(cols>1) label(1, label2);
    if(cols>2) label(2, label3);
    if(cols>3) label(3, label4);
    if(cols>4) label(4, label5);
}

Fl_ListView_ItemExt::~Fl_ListView_ItemExt()
{

}

Fl_ListItem_Attr *Fl_ListView_ItemExt::create_attr(int col)
{
    Fl_ListItem_AttrExt *a = new Fl_ListItem_AttrExt;
    a->col_label = 0;
    a->col_width = 0;
    a->col_image = 0;
    a->col_flags        = parent() ? parent()->column_flags(col)    : FL_ALIGN_LEFT;
    a->col_font         = parent() ? parent()->text_font()          : Fl_Widget::default_style->text_font;
    a->col_font_size    = parent() ? parent()->text_size()          : Fl_Widget::default_style->text_size;
    a->col_color        = parent() ? parent()->text_color()         : Fl_Widget::default_style->text_color;
    a->col_label_type   = parent() ? parent()->label_type()         : Fl_Widget::default_style->label_type;
    return a;
}

Fl_Font Fl_ListView_ItemExt::label_font(int col) const
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_font;
}

int Fl_ListView_ItemExt::label_size(int col) const
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_font_size;
}

void Fl_ListView_ItemExt::label_font(int col, Fl_Font font)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->col_font = font;
}

void Fl_ListView_ItemExt::label_size(int col, int size)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->col_font_size = size;
}

void Fl_ListView_ItemExt::label_color(int col, Fl_Color color)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->col_color = color;
}

Fl_Color Fl_ListView_ItemExt::label_color(int col) const
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_color;
}

void Fl_ListView_ItemExt::label_type(int col, Fl_Labeltype type)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->col_label_type = type;
}

Fl_Labeltype Fl_ListView_ItemExt::label_type(int col) const
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_label_type;
}

void Fl_ListView_ItemExt::image(int col, Fl_Image *im)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->col_image = im;
}

void Fl_ListView_ItemExt::image(int col, Fl_Image &im)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->col_image = &im;
}

const Fl_Image *Fl_ListView_ItemExt::image(int col) const
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_image;
}

Fl_Image *Fl_ListView_ItemExt::image(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_image;
}

Fl_Flags Fl_ListView_ItemExt::flags(int col) const
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_flags;
}

Fl_Flags Fl_ListView_ItemExt::flags(int col, int f)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_flags = f;
}

Fl_Flags Fl_ListView_ItemExt::set_flag(int col, int f)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_flags |= f;
}

Fl_Flags Fl_ListView_ItemExt::clear_flag(int col, int f)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_flags &= ~f;
}

Fl_Flags Fl_ListView_ItemExt::invert_flag(int col, int f)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->col_flags ^= f;
}

void Fl_ListView_ItemExt::draw_cell(int col, int w, bool sel)
{
    if((uint)col>=attr_list.size()) return;

    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];

    Fl_Flags f = parent()->flags();
    Fl_Flags item_f = a->col_flags | (f&FL_INACTIVE) | (sel?FL_SELECTED:0);

    int X=0, Y=0, W=w, H=h();
    // Draw user defined border
    Fl_Boxtype box = parent()->button_box();
    box->draw(0, 0, W, H, fl_inactive(parent()->button_color(), f), FL_INVISIBLE);
    box->inset(X,Y,W,H);

    fl_push_clip(X, Y, W, H);

    const char *txt = a->col_label;
    Fl_Image *im = a->col_image;
    if(txt) {

        int iw=0;
        if(im) {
            iw = im->width()+2;
        }

        //fl_font(a->col_font, a->col_font_size);
        //HMM... cutting should be optional
        //if(strchr(txt, '\n')) txt = fl_cut_multiline(txt, w-iw-6);
        //else txt = fl_cut_line(txt, w-iw-6);

        if(item_f&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) { X += 3; W -= 6; }

        draw_label(txt, X, 0, W, H, item_f, a);
    }
    fl_pop_clip();
}

// Measure the space the draw() will take:
void Fl_ListView_ItemExt::layout()
{
    int H = 0;
    for(uint n=0; n<attr_list.size(); n++) {
        Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[n];
        if(!a->col_label.empty()) {
            int w=300,h=0;
            fl_font(a->col_font , a->col_font_size);
            fl_measure(a->col_label, w, h, a->col_flags);
            if(h>H) H=h;
            a->col_width = w;
        }
        if(a->col_image) {
            int w,h;
            a->col_image->measure(w,h);
            a->col_width += w;
            if(h>H) H=h;
        }
    }
    H += parent()->button_box()->dh();
    h(int(H+leading_));
}

// Anybody can call this to force the label to draw anywhere, this is
// used by Fl_Group and Fl_Tabs to draw outside labels:
void Fl_ListView_ItemExt::draw_label(const char *label, int X, int Y, int W, int H, Fl_Flags flags, void *attr)
{
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr;
    fl_font(a->col_font, a->col_font_size);

    Fl_Color color;
    // yes, inside label is affected by selection or highlight:
    if (flags&FL_SELECTED)
        color = parent()->selection_text_color();
    else if (flags&FL_HIGHLIGHT && (color = parent()->highlight_label_color()))
    ;
    else
        color = a->col_color;

    if(a->col_image) {
        fl_color(fl_inactive(color, flags));

        if(flags & FL_ALIGN_TILED || flags & FL_ALIGN_SCALE) {
            a->col_image->draw(X, Y, W, H, flags);
        } else {
            int w = W;
            int h = H;
            a->col_image->measure(w, h);

            // If all the flags are off, draw the image and label centered "nicely"
            // by measuring their total size and centering that rectangle:
            if (!(flags & (FL_ALIGN_LEFT|FL_ALIGN_RIGHT|FL_ALIGN_TOP|FL_ALIGN_BOTTOM|
                            FL_ALIGN_INSIDE)) && label)
            {
                int d = (H-int(h+fl_height()))>>1;
                if (d >= 0)
                {
                    // put the image atop the text
                    Y += d; H -= d; flags |= FL_ALIGN_TOP;
                }
                else
                {
                    // put image to left
                    int text_w = W; int text_h = H;
                    fl_measure(label, text_w, text_h, flags);
                    int d = (W-(h+text_w))>>1;
                    if (d > 0) {X += d; W -= d;}
                    flags |= FL_ALIGN_LEFT;
                }
            }

            int cx,cy;               // point in image to put at X,Y
            if (flags & FL_ALIGN_RIGHT)
            {
                cx = w-W;
                if (flags & FL_ALIGN_LEFT && cx < 0) cx = 0;
            }
            else if (flags & FL_ALIGN_LEFT) cx = 0;
            else cx = w/2-W/2;
            if (flags & FL_ALIGN_BOTTOM)
            {
                cy = h-H;
                if (flags & FL_ALIGN_TOP && cy < 0) cy = 0;
            }
            else if (flags & FL_ALIGN_TOP) cy = 0;
            else cy = h/2-H/2;

            a->col_image->draw(X-cx, Y-cy, W, H, 0,0,0,0,flags);

            // figure out the rectangle that remains for text:
            if (flags & FL_ALIGN_LEFT) { X += (w+2); W -= (w+4); }
            else if (flags & FL_ALIGN_RIGHT) W -= (w+4);
            else if (flags & FL_ALIGN_TOP) {Y += h; H -= h;}
            else if (flags & FL_ALIGN_BOTTOM) H -= h;
            else                     /*flags |= FL_ALIGN_TOP;*/
            {
                Y += (h-cy); H -= (h-cy);
            }
        }
    }

    if(label && *label) {
        a->col_label_type->draw(label, X, Y, W, H, color, flags);
    }
}
