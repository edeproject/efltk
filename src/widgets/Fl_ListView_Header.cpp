#include <efltk/Fl_ListView_Header.h>
#include <efltk/Fl_ListView.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Variant.h>

#include <stdlib.h>

#define LIST ((Fl_ListView *)parent())
#define DRAG_DIST 3 //Area to size header
#define TXT_SPACE 2 //Size between txt and img

class Fl_ListHeader_Attr
{
public:
    Fl_String       label;
    int             width;
    Fl_Variant_Type ctype;
    Fl_Flags        flags;
    Fl_Font         font;
    int             font_size;
    Fl_Color        color;
    Fl_Image       *image;
};

static void revert(Fl_Style* s) {
    s->button_box = FL_UP_BOX;
    s->button_color = FL_GRAY;
    s->color = FL_GRAY;
}
static Fl_Named_Style style("ListView_Header", revert, &Fl_ListView_Header::default_style);
Fl_Named_Style* Fl_ListView_Header::default_style = &::style;

Fl_ListView_Header::Fl_ListView_Header(int X,int Y,int W,int H,const char*l)
: Fl_Widget(X,Y,W,H,l)
{
    style(default_style);
    sort_type = Fl_ListView::SORT_ABSOLUTE;
    sort_col = 0;
}

Fl_ListView_Header::~Fl_ListView_Header()
{
    clear();
}

void Fl_ListView_Header::add_attr(int col)
{   
    Fl_ListHeader_Attr *a = new Fl_ListHeader_Attr;
    a->flags = FL_ALIGN_LEFT;
    a->width = 0;
    a->font = Fl_Widget::label_font();
    a->font_size = Fl_Widget::label_size();
    a->color = Fl_Widget::label_color();
    a->image = 0;
    attr_list[col] = a;
}

void Fl_ListView_Header::add_column(const char *name, int w, Fl_Variant_Type t)
{
    columns(columns()+1);
    column_label(columns()-1, name);
    column_width(columns()-1, w);
    column_type(columns()-1, t);
}

void Fl_ListView_Header::add_column(const Fl_String &name, int w, Fl_Variant_Type t)
{
    add_column(name.c_str(),w,t);
}

void Fl_ListView_Header::columns(int count)
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
            Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[n];
            delete a;
        }
        attr_list.resize(new_size);
    }
}

uint Fl_ListView_Header::columns()
{
    return attr_list.size();
}

void Fl_ListView_Header::column_width(int col, int w)
{
    if((uint)col>=attr_list.size()) return;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    a->width = w;
}

int Fl_ListView_Header::column_width(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->width;
}

void Fl_ListView_Header::column_type(int col, Fl_Variant_Type t)
{
    if((uint)col>=attr_list.size()) return;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    a->ctype = t;
}

Fl_Variant_Type Fl_ListView_Header::column_type(int col)
{
    if((uint)col>=attr_list.size()) return VAR_NONE;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->ctype;
}

Fl_Flags Fl_ListView_Header::column_flags(int col, int f)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->flags = f;
}

Fl_Flags Fl_ListView_Header::column_flags(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->flags;
}

Fl_Flags Fl_ListView_Header::column_set_flag(int col, int f)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->flags |= f;
}

Fl_Flags Fl_ListView_Header::column_clear_flag(int col, int f)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->flags &= ~f;
}

Fl_Flags Fl_ListView_Header::column_invert_flag(int col, int f)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->flags ^= f;
}

const Fl_String &Fl_ListView_Header::column_label() const
{
    if(attr_list.size()==0) return Fl_String::null_object;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[0];
    return a->label;
}

const Fl_String &Fl_ListView_Header::column_label(int col) const
{
    if(attr_list.size()==0) return Fl_String::null_object;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->label;
}

void Fl_ListView_Header::column_label(int col, const char *text)
{
    if((uint)col>=attr_list.size()) return;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    a->label = text;
}

void Fl_ListView_Header::column_label(int col, const Fl_String &text)
{
    if((uint)col>=attr_list.size()) return;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    a->label = text;
}

Fl_Font Fl_ListView_Header::column_label_font(int col) const
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->font;
}

int Fl_ListView_Header::column_label_size(int col) const
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->font_size;
}

void Fl_ListView_Header::column_label_font(int col, Fl_Font font)
{
    if((uint)col>=attr_list.size()) return;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    a->font = font;
}

void Fl_ListView_Header::column_label_size(int col, int size) const
{
    if((uint)col>=attr_list.size()) return;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    a->font_size = size;
}

void Fl_ListView_Header::column_label_color(int col, Fl_Color color)
{
    if((uint)col>=attr_list.size()) return;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    a->color = color;
}

void Fl_ListView_Header::column_image(int col, Fl_Image *im)
{
    if((uint)col>=attr_list.size()) return;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    a->image = im;
}

void Fl_ListView_Header::column_image(int col, Fl_Image &im)
{
    if((uint)col>=attr_list.size()) return;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    a->image = &im;
}

Fl_Image *Fl_ListView_Header::column_image(int col)
{
    if((uint)col>=attr_list.size()) return 0;
    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col];
    return a->image;
}

void Fl_ListView_Header::clear()
{
    for(uint n=0; n<attr_list.size(); n++) {
        Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[n];
        delete a;
    }
    attr_list.clear();
}

#define SORT_ARROW 8

void Fl_ListView_Header::draw()
{
    fl_push_matrix();
    int total_w=0;

    for(uint n=0; n<attr_list.size(); n++)
    {
        Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[n];

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

            if(sort_col==(int)n && sort_type>Fl_ListView::SORT_ABSOLUTE && sort_type<Fl_ListView::SORT_LAST_TYPE)
                W-=(SORT_ARROW+2);

            int tw=W-iw;
            if(tw>0) {
                fl_font(a->font, float(a->font_size));
                const char *pbuf = fl_cut_line(txt, W-iw-6);
                Fl_Widget::label(pbuf);
            } else {
                Fl_Widget::label("");
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

void Fl_ListView_Header::layout()
{
    Fl_Widget::layout();
    // No layout!
    // Header should be able to set any height user wants.
}

int Fl_ListView_Header::handle(int ev)
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
                Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[n];
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
                Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[inside];
                a->flags |= FL_VALUE;
                redraw(FL_DAMAGE_ALL);
                LIST->redraw(FL_DAMAGE_CHILD);
            }
            return 1;//dragging ? 1 : 0;

        case FL_RELEASE:
            if(inside >= 0 && (((Fl_ListHeader_Attr*)attr_list[inside])->flags & FL_VALUE) == FL_VALUE)
            {
                Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[inside];
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
            xp = LIST->xposition();
            mx = Fl::event_x()+xp;
            if(dragging) {
                Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[col_to_drag];
                a->width = mx-col_start;
                if(a->width < DRAG_DIST)
                    a->width = DRAG_DIST;
                set_damage(FL_DAMAGE_ALL);
                LIST->layout_scrollbars();
                LIST->redraw();
            }
            return 1;
        case FL_MOVE: {
                bool got_cursor = false;
                col_start=0;
                col_to_drag=0;
                xp = LIST->xposition();
                mx = Fl::event_x()+xp;
                for(n=0; n<attr_list.size(); n++) {
                    Fl_ListHeader_Attr *a = (Fl_ListHeader_Attr*)attr_list[n];
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
