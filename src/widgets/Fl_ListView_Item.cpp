#include <efltk/Fl_ListView_Item.h>
#include <efltk/Fl_ListView.h>
#include <efltk/fl_draw.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class Fl_ListItem_Attr
{
public:
    const char *label;
    bool copied;
    int16 width;
};

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

bool Fl_ListView_Item::selected()
{
    return (parent()->get_selection().index_of(this)>-1);
}

uint Fl_ListView_Item::columns()
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
            if(a->label && a->copied) free((void *)a->label);
            delete (Fl_ListItem_Attr*)a;
        }
        attr_list.resize(new_size);
    }
}

void Fl_ListView_Item::add_attr(int col)
{
    Fl_ListItem_Attr *a = new Fl_ListItem_Attr;
    a->label = 0;
    a->copied = false;
    a->width = 0;
    attr_list[col] = a;
}

Fl_ListView_Item::~Fl_ListView_Item()
{
    for(uint n=0; n<attr_list.size(); n++) {
        Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[n];
        if(a->label && a->copied)
            free((void *)a->label);
    }
}

void Fl_ListView_Item::check_columns(uint count) {
    if(count+1>columns()) columns(count+1);
}

void Fl_ListView_Item::copy_label(int col, const char *txt)
{
    check_columns(col);
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    if(a->copied) free((void*)a->label);
    if(txt) {
        a->label = strdup(txt);
        a->copied = true;
    } else {
        a->label = 0;
        a->copied = false;
    }
}

void Fl_ListView_Item::draw_cell(int col, int w, bool sel)
{
    if((uint)col>=attr_list.size()) return;

    Fl_Flags f = parent()->column_flags(col) | (parent()->flags()&FL_INACTIVE);

    fl_push_clip(0, 0, w, h());

    // Draw user defined border
    Fl_Boxtype box = parent()->button_box();
    box->draw(0, 0, w, h(), fl_inactive(parent()->button_color(), f), FL_INVISIBLE);
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    const char *txt = a->label;
    if(txt) {
        fl_font(parent()->text_font(), parent()->text_size());
        fl_color(fl_inactive(sel?parent()->selection_text_color():parent()->text_color(), f));

        int x=2;
        int iw=0;

        if(col==0 && image_) {
            image_->draw(x, h()/2-image_->height()/2, image_->width(), image_->height(), f|(sel?FL_SELECTED:0));
            iw = image_->width()+2;
            x+=iw;
        }

        //HMM... cutting should be optional
        if(strchr(txt, '\n')) txt = fl_cut_multiline(txt, w-iw-6);
        else txt = fl_cut_line(txt, w-iw-6);

        fl_draw(txt, x, int(fl_descent()/2), w-x, h(), f&FL_ALIGN_MASK);
    }
    fl_pop_clip();
}

// Measure the space the draw() will take:
void Fl_ListView_Item::layout()
{
    if(h()) return;

    int H = 0;
    fl_font(parent()->text_font() , parent()->text_size());
    for(uint n=0; n<attr_list.size(); n++) {
        Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[n];
        if(a->label) {
            int w=300,h=0;
            fl_measure(a->label, w, h, FL_ALIGN_LEFT);
            if(h>H) H=h;
            a->width = w;
        }
    }
    h(int(H+fl_descent()));
}

int Fl_ListView_Item::column_width(int col)
{
    if((uint)col>=attr_list.size()) return -1;
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    return a->width;
}

const char *Fl_ListView_Item::label()
{
    if(attr_list.size()==0) return 0;
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[0];
    return a->label;
}

const char *Fl_ListView_Item::label(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    return a->label;
}

void Fl_ListView_Item::label(int col, const char *text)
{
    check_columns(col);
    Fl_ListItem_Attr *a = (Fl_ListItem_Attr*)attr_list[col];
    if(a->label && a->copied) free((void*)a->label);
    a->copied = false;
    a->label = text;
}

///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////

class Fl_ListItem_AttrExt : public Fl_ListItem_Attr
{
public:
    Fl_Flags flags;
    Fl_Font font;
    int font_size;
    Fl_Color color;
    Fl_Image *image;
    Fl_Labeltype label_type;
};

Fl_ListView_ItemExt::Fl_ListView_ItemExt(const char *label1,
                                         const char *label2,
                                         const char *label3,
                                         const char *label4,
                                         const char *label5)
: Fl_ListView_Item(0,0,0,0,0)
{
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

void Fl_ListView_ItemExt::add_attr(int col)
{
    Fl_ListItem_AttrExt *a = new Fl_ListItem_AttrExt;
    a->label = 0;
    a->copied = false;
    a->width = 0;
    a->image = 0;
    a->flags = parent()->column_flags(col);
    a->font = parent()->text_font();
    a->font_size = parent()->text_size();
    a->color = parent()->text_color();
    a->label_type = parent()->label_type();
    attr_list[col] = a;
}

Fl_Font Fl_ListView_ItemExt::label_font(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->font;
}

int Fl_ListView_ItemExt::label_size(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->font_size;
}

void Fl_ListView_ItemExt::label_font(int col, Fl_Font font)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->font = font;
}

void Fl_ListView_ItemExt::label_size(int col, int size)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->font_size = size;
}

void Fl_ListView_ItemExt::label_color(int col, Fl_Color color)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->color = color;
}

Fl_Color Fl_ListView_ItemExt::label_color(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->color;
}

void Fl_ListView_ItemExt::label_type(int col, Fl_Labeltype type)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->label_type = type;
}

Fl_Labeltype Fl_ListView_ItemExt::label_type(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->label_type;
}

void Fl_ListView_ItemExt::image(int col, Fl_Image *im)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->image = im;
}

void Fl_ListView_ItemExt::image(int col, Fl_Image &im)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    a->image = &im;
}

Fl_Image *Fl_ListView_ItemExt::image(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->image;
}

Fl_Flags Fl_ListView_ItemExt::flags(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->flags;
}

Fl_Flags Fl_ListView_ItemExt::flags(int col, int f)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->flags = f;
}

Fl_Flags Fl_ListView_ItemExt::set_flag(int col, int f)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->flags |= f;
}

Fl_Flags Fl_ListView_ItemExt::clear_flag(int col, int f)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->flags &= ~f;
}

Fl_Flags Fl_ListView_ItemExt::invert_flag(int col, int f)
{
    check_columns(col);
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];
    return a->flags ^= f;
}

void Fl_ListView_ItemExt::draw_cell(int col, int w, bool sel)
{
    if((uint)col>=attr_list.size()) return;

    fl_push_clip(0, 0, w, h());

    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[col];

    Fl_Flags f = parent()->flags();
    Fl_Flags item_f = a->flags | (f&FL_INACTIVE) | (sel?FL_SELECTED:0);

    // Draw user defined border
    Fl_Boxtype box = parent()->button_box();
    box->draw(0, 0, w, h(), fl_inactive(parent()->button_color(), f), FL_INVISIBLE);

    const char *txt = a->label;
    Fl_Image *im = a->image;
    if(txt) {

        int iw=0;
        if(im) {
            iw = im->width()+2;
        }

        fl_font(a->font, a->font_size);
        int x=2;
        //HMM... cutting should be optional
        if(strchr(txt, '\n')) txt = fl_cut_multiline(txt, w-iw-6);
        else txt = fl_cut_line(txt, w-iw-6);

        if(item_f&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {x += 3; w -= 6;}

        fl_push_clip(x,0, w, h());
        draw_label(txt, x, 0, w, h(), item_f, a);
        fl_pop_clip();
    }
    fl_pop_clip();
}

// Measure the space the draw() will take:
void Fl_ListView_ItemExt::layout()
{
    if(h()) return;

    int H = 0;
    for(uint n=0; n<attr_list.size(); n++) {
        Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr_list[n];
        if(a->label) {
            int w=300,h=0;
            fl_font(a->font , a->font_size);
            fl_measure(a->label, w, h, a->flags);
            if(h>H) H=h;
            a->width = w;
        }
        if(a->image) {
            int w,h;
            a->image->measure(w,h);
            a->width += w;
            if(h>H) H=h;
        }
    }
    h(int(H+fl_descent()));
}

// Anybody can call this to force the label to draw anywhere, this is
// used by Fl_Group and Fl_Tabs to draw outside labels:
void Fl_ListView_ItemExt::draw_label(const char *label, int X, int Y, int W, int H, Fl_Flags flags, void *attr)
{
    Fl_ListItem_AttrExt *a = (Fl_ListItem_AttrExt*)attr;
    fl_font(a->font, a->font_size);

    Fl_Color color;
    // yes, inside label is affected by selection or highlight:
    if (flags&FL_SELECTED)
        color = parent()->selection_text_color();
    else if (flags&FL_HIGHLIGHT && (color = parent()->highlight_label_color()))
        ;
    else
        color = a->color;

    if(a->image) {
        fl_color(fl_inactive(color, flags));

        if(flags & FL_ALIGN_TILED || flags & FL_ALIGN_SCALE) {
            a->image->draw(X, Y, W, H, flags);
        } else {
            int w = W;
            int h = H;
            a->image->measure(w, h);

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

            a->image->draw(X-cx, Y-cy, W, H, 0,0,0,0,flags);

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
        a->label_type->draw(label, X, Y, W, H, color, flags);
    }
}
