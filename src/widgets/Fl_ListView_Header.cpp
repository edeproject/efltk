#include <efltk/Fl_ListView_Header.h>
#include <efltk/Fl_ListView.h>
#include <efltk/fl_draw.h>

#define SORT_ARROW 8
#define DRAG_DIST 3 //Area to size header

Fl_ListView_Column::Fl_ListView_Column()
{
    m_color = Fl_Widget::default_style->label_color;
    m_font  = Fl_Widget::default_style->label_font;
    m_font_size = Fl_Widget::default_style->label_size;

    m_type = VAR_STRING;
    m_flags = FL_ALIGN_LEFT;
    m_image = 0;
}

//////////////////////////////

static void revert(Fl_Style* s) {
}

static Fl_Named_Style style("ListView Header", revert, &Fl_ListView_Header::default_style);
Fl_Named_Style* Fl_ListView_Header::default_style = &::style;

Fl_ListView_Header::Fl_ListView_Header(Fl_ListView *parent)
    : Fl_Widget(0,0,0,0,0)
{
	style(default_style);
    m_capture = -1;
}

Fl_ListView_Header::~Fl_ListView_Header()
{
}

void Fl_ListView_Header::draw(int c, int width, int height)
{
    Fl_ListView_Column *col = parent()->column(c);
    if(!col) return;

    fl_push_clip(0,0,width,height);

    Fl_Flags f = col->flags();
    Fl_Color color = button_color();
    button_box()->draw(0, 0, width, height, color, f);

    int X=0, Y=0, W=width, H=height;
    button_box()->inset(X,Y,W,H);

    if(!col->label().empty()) {
        /*int iw=0, ih=0;
        if(col->image()) {
            col->image()->measure(iw,ih);
        }*/

        if(f&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) { X += 3; W -= 6; }

        if(parent()->sort_col()==c && parent()->sort_type()>Fl_ListView::SORT_NONE && parent()->sort_type()<Fl_ListView::SORT_LAST_TYPE)
            W -= (SORT_ARROW+2);

        Fl_Widget::label(col->label());
        Fl_Widget::label_color(col->label_color());
        Fl_Widget::label_font(col->label_font());
        Fl_Widget::label_size(col->label_size());
        Fl_Widget::image(col->image());
        draw_label(X, Y, W-X, H, f|(flags()&(FL_SELECTED|FL_INACTIVE)));
        Fl_Widget::image(0);

        //fl_font(parent()->text_font(), parent()->text_size());
        //fl_color(parent()->text_color());
        //fl_draw(col->label(), iw, 0, tw, height, f);

        if(parent()->sort_col()==c) {
            switch(parent()->sort_type()) {
            case Fl_ListView::SORT_DESC:
                glyph()(this, FL_GLYPH_UP, width-DRAG_DIST-SORT_ARROW, H/2-SORT_ARROW/2, SORT_ARROW, SORT_ARROW, f|(parent()->flags()&(FL_SELECTED|FL_INACTIVE)));
                break;
            case Fl_ListView::SORT_ASC:
                glyph()(this, FL_GLYPH_DOWN, width-DRAG_DIST-SORT_ARROW, H/2-SORT_ARROW/2, SORT_ARROW, SORT_ARROW, f|(parent()->flags()&(FL_SELECTED|FL_INACTIVE)));
                break;
            default:
                break;
            }
        }
    }
    fl_pop_clip();
}

int Fl_ListView_Header::handle(int col, int ev)
{
    if(capture_events())
        col = get_capture();

    Fl_ListView_Column *c = parent()->column(col);
    int X, Y, W, H;

    switch(ev)
    {
    case FL_PUSH:
        set_capture(col);
        c->flags(c->flags() | FL_VALUE);
        redraw(FL_DAMAGE_VALUE);
        return 1;

    case FL_RELEASE:
        if(parent()->find_cell(Fl_Table_Base::CONTEXT_COL_HEADER, 0, col, X, Y, W, H)) {
            if(Fl::event_inside(X,Y,W,H)) {
                parent()->sort(col);
            }
        }
        set_capture(-1);
        c->flags(c->flags() & ~FL_VALUE);
        redraw(FL_DAMAGE_VALUE);
        return 1;

    case FL_DRAG:
        if(parent()->find_cell(Fl_Table_Base::CONTEXT_COL_HEADER, 0, col, X, Y, W, H)) {
            if(!Fl::event_inside(X,Y,W,H)) {
                c->flags(c->flags() & ~FL_VALUE);
            } else {
                c->flags(c->flags() | FL_VALUE);
            }
            redraw(FL_DAMAGE_VALUE);
        }

    default:
        break;
    }
    return 0;
}

void Fl_ListView_Header::show()
{
    parent()->col_header(true);
    redraw();
}

void Fl_ListView_Header::hide()
{
    parent()->col_header(false);
    redraw();
}

///////////////////////////////
// Compatibility section

void Fl_ListView_Header::clear() {
    parent()->clear_columns();
}

void Fl_ListView_Header::add_column(const char *name, int w, Fl_Variant_Type column_type) {
    parent()->add_column(name, w, column_type);
}

void Fl_ListView_Header::add_column(const Fl_String &name, int w, Fl_Variant_Type column_type) {
    parent()->add_column(name, w, column_type);
}

void Fl_ListView_Header::columns(int count) { parent()->columns(count); }
unsigned Fl_ListView_Header::columns() const { return parent()->columns(); }

int Fl_ListView_Header::column_width(int col) const { return parent()->col_width(col); }
void Fl_ListView_Header::column_width(int col, int w) { parent()->col_width(col, w); }

Fl_Variant_Type Fl_ListView_Header::column_type(int col) const { return parent()->column(col)->type(); }
void Fl_ListView_Header::column_type(int col, Fl_Variant_Type w) { parent()->column(col)->type(w); }

Fl_Flags Fl_ListView_Header::column_flags(int col, int f)       { return parent()->column(col)->flags(f); }
Fl_Flags Fl_ListView_Header::column_flags(int col) const        { return parent()->column(col)->flags(); }
Fl_Flags Fl_ListView_Header::column_set_flag(int col, int f)    { return parent()->column(col)->set_flag(f); }
Fl_Flags Fl_ListView_Header::column_clear_flag(int col, int f)  { return parent()->column(col)->clear_flag(f); }
Fl_Flags Fl_ListView_Header::column_invert_flag(int col, int f) { return parent()->column(col)->invert_flag(f); }

const Fl_String &Fl_ListView_Header::column_label() const        { return parent()->column(0)->label(); }
const Fl_String &Fl_ListView_Header::column_label(int col) const { return parent()->column(col)->label(); }

void Fl_ListView_Header::column_label(int col, const char *text)      { parent()->column(col)->label(text); }
void Fl_ListView_Header::column_label(int col, const Fl_String &text) { parent()->column(col)->label(text); }
void Fl_ListView_Header::column_copy_label(int col, const char *txt)  { column_label(col, txt); }

Fl_Font Fl_ListView_Header::column_label_font(int col) const { return parent()->column(col)->label_font(); }
int Fl_ListView_Header::column_label_size(int col) const     { return parent()->column(col)->label_size(); }
Fl_Color Fl_ListView_Header::column_label_color(int col) const { return parent()->column(col)->label_color(); }

void Fl_ListView_Header::column_label_size(int col, int size)        { parent()->column(col)->label_size(size); }
void Fl_ListView_Header::column_label_font(int col, Fl_Font font)    { parent()->column(col)->label_font(font); }
void Fl_ListView_Header::column_label_color(int col, Fl_Color color) { parent()->column(col)->label_color(color); }

void Fl_ListView_Header::column_image(int col, Fl_Image *im) { parent()->column(col)->image(im); }
void Fl_ListView_Header::column_image(int col, Fl_Image &im) { parent()->column(col)->image(im); }
Fl_Image *Fl_ListView_Header::column_image(int col) { return parent()->column(col)->image(); }
const Fl_Image *Fl_ListView_Header::column_image(int col) const { return parent()->column(col)->image(); }
