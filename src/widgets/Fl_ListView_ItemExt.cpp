#include <efltk/Fl_ListView_Item.h>
#include <efltk/Fl_ListView.h>
#include <efltk/fl_draw.h>

typedef struct {
    Fl_Flags flags;
    Fl_Font font;
    int font_size;
    Fl_Color color;
    Fl_Image *image;
    Fl_Labeltype label_type;
} ColAttr;

ColAttr *create_attr(Fl_ListView_ItemExt *item, unsigned col)
{
    Fl_ListView *parent = item->parent();

    ColAttr *a = new ColAttr;
    a->image = 0;
    a->flags        = parent ? parent->column_flags(col)    : FL_ALIGN_LEFT;
    a->font         = parent ? parent->text_font()          : Fl_Widget::default_style->text_font;
    a->font_size    = parent ? parent->text_size()          : Fl_Widget::default_style->text_size;
    a->color        = parent ? parent->text_color()         : Fl_Widget::default_style->text_color;
    a->label_type   = parent ? parent->label_type()         : Fl_Widget::default_style->label_type;
    return a;
}

Fl_ListView_ItemExt::Fl_ListView_ItemExt(const char *label1,
                                         const char *label2,
                                         const char *label3,
                                         const char *label4,
                                         const char *label5)
    : Fl_ListView_Item(0,0,0,0,0)
{
    if(parent())
        m_leading = parent()->leading();
    else
        m_leading = 1;

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
    columns(0);
}

void Fl_ListView_ItemExt::columns(unsigned count)
{
    Fl_ListView_Item::columns(count);

    uint old_size = col_attrs.size();
    uint new_size = count;

    if(old_size < new_size) {
        col_attrs.resize(new_size);
        for(uint n=old_size; n<new_size; n++) {
            col_attrs[n] = create_attr(this, n);
        }
    } else {
        for(uint n=new_size; n<old_size; n++) {
            ColAttr *a = (ColAttr*)col_attrs[n];
            delete a;
        }
        col_attrs.resize(new_size);
    }
}

int Fl_ListView_ItemExt::preferred_width(unsigned col) const
{
	if(col>=columns()) return 1;

    int w=parent()->col_width(col), h=0;
    if(w<0) w=300;
    fl_font(label_font(col), label_size(col));
    fl_measure(label(col), w, h, flags(col));
    if(image(col))
        w += image(col)->width();
    return w;
}

void Fl_ListView_ItemExt::width_changed(unsigned row, unsigned col)
{
	if(col>=columns()) return;

    Fl_Flags a = flags(col) & FL_ALIGN_MASK;
    if(a & FL_ALIGN_WRAP) {
        int w=parent()->col_width(col), h=0;
        if(w<0) w=300;
        w -= parent()->button_box()->dw();
        fl_font(label_font(col), label_size(col));
        fl_measure(label(col), w, h, flags(col));
        h += (int)fl_descent();
        if(image(col)) {
            if(h < image(col)->height())
                h = image(col)->height();
        }
        h += parent()->button_box()->dh() + leading() + 2;
        parent()->row_height(row, h);
    }
}

void Fl_ListView_ItemExt::setup(unsigned row)
{
    int H = 0;
    fl_font(label_font(0), label_size(0));
    H = int(fl_height() + fl_descent());

    for(unsigned n=0; n<columns(); n++)
    {
        const char *col_label = label(n);
        if(!col_label || !*col_label) continue;

        Fl_Flags a = flags(n) & FL_ALIGN_MASK;
        int h=0;

        fl_font(label_font(n), label_size(n));
        if(a & FL_ALIGN_WRAP) {
            // Wrap is on.
            int w=parent()->col_width(n);
            if(w<0) w=300;
            fl_measure(col_label, w, h, a);
        } else {
            // No wrap, check for multi line
            const char *ptr = strchr(col_label, '\n');
            if(ptr) {
                // Multi line, calc lines
                h = 0;
                while(ptr) {
                    h += (int)fl_height();
                    ptr = strchr(ptr+1, '\n');
                }
                h += int(fl_height() + fl_descent());
            }
        }

        if(image(n)) {
            if(image(n)->height() > h)
                h = image(n)->height();
        }

        if(h>H) H=h;
    }

    H += parent()->button_box()->dh() + leading() + 2;
    parent()->row_height(row, H);
}

void Fl_ListView_ItemExt::draw_cell(unsigned row, unsigned col, int width, int height)
{
    if(!(damage() & FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE))
        return;    

    Fl_Flags f = (col>=columns()) ? Fl_Flags(0) : flags(col);
    if(parent()->selected_row(row)) f.set(FL_SELECTED);
    if(parent()->inactive_row(row) || !parent()->active()) f.set(FL_INACTIVE);

    int X=0, Y=0, W=width, H=height;
    // Draw user defined border
    Fl_Boxtype box = parent()->button_box();
	box->draw(0, 0, W, H, fl_inactive(parent()->button_color(), f), FL_INVISIBLE);
	box->inset(X,Y,W,H);

	const char *str = label(col);
    if(str && *str) {
		fl_push_clip(0, 0, width, height);

		if(f&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {
			X += 3; W -= 6;
		}
		draw_label(col, str, X, Y, W, H, f);

		fl_pop_clip();
	}    
}

void Fl_ListView_ItemExt::draw_label(unsigned col, const char *label, int X, int Y, int W, int H, Fl_Flags flags)
{
	if(col>=columns()) return;

    fl_font(label_font(col), label_size(col));

    Fl_Color color;
    // yes, inside label is affected by selection or highlight:
    if(flags&FL_SELECTED)
        color = parent()->selection_text_color();
    else if (flags&FL_HIGHLIGHT && parent()->highlight_label_color())
        color = parent()->highlight_label_color();
    else
        color = label_color(col);

    Fl_Image *image = this->image(col);
    if(image) {
        fl_color(fl_inactive(color, flags));

        if(flags & FL_ALIGN_TILED || flags & FL_ALIGN_SCALE) {
            image->draw(X, Y, W, H, flags);
        } else {
            int w = W;
            int h = H;
            image->measure(w, h);

            // If all the flags are off, draw the image and label centered "nicely"
            // by measuring their total size and centering that rectangle:
            if (!(flags & (FL_ALIGN_LEFT|FL_ALIGN_RIGHT|FL_ALIGN_TOP|FL_ALIGN_BOTTOM|
                           FL_ALIGN_INSIDE)) && label)
            {
                int d = (H-int(h+fl_height()))>>1;
                if (d >= 0)
                {
                    // put the image atop the text
                    Y += d;
                    H -= d;
                    flags.set(FL_ALIGN_TOP);
                }
                else
                {
                    // put image to left
                    int text_w = W; int text_h = H;
                    fl_measure(label, text_w, text_h, flags);
                    int d = (W-(h+text_w))>>1;
                    if (d > 0) {X += d; W -= d;}
                    flags.set(FL_ALIGN_LEFT);
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

            image->draw(X-cx, Y-cy, W, H, 0,0,0,0,flags);

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
        label_type(col)->draw(label, X, Y, W, H, color, flags);
    }
}

Fl_Font Fl_ListView_ItemExt::label_font(unsigned col) const
{
    if(col>=col_attrs.size()) return 0;
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->font;
}

int Fl_ListView_ItemExt::label_size(unsigned col) const
{
    if(col>=col_attrs.size()) return 0;
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->font_size;
}

void Fl_ListView_ItemExt::label_font(unsigned col, Fl_Font font)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    a->font = font;
}

void Fl_ListView_ItemExt::label_size(unsigned col, int size)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    a->font_size = size;
}

void Fl_ListView_ItemExt::label_color(unsigned col, Fl_Color color)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    a->color = color;
}

Fl_Color Fl_ListView_ItemExt::label_color(unsigned col) const
{
    if(col>=col_attrs.size()) return 0;
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->color;
}

void Fl_ListView_ItemExt::label_type(unsigned col, Fl_Labeltype type)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    a->label_type = type;
}

Fl_Labeltype Fl_ListView_ItemExt::label_type(unsigned col) const
{
    if(col>=col_attrs.size()) return 0;
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->label_type;
}

void Fl_ListView_ItemExt::image(unsigned col, Fl_Image *im)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    a->image = im;
}

void Fl_ListView_ItemExt::image(unsigned col, Fl_Image &im)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    a->image = &im;
}

const Fl_Image *Fl_ListView_ItemExt::image(unsigned col) const
{
    if(col>=col_attrs.size()) return 0;
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->image;
}

Fl_Image *Fl_ListView_ItemExt::image(unsigned col)
{
    if(col>=col_attrs.size()) return 0;
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->image;
}

Fl_Flags Fl_ListView_ItemExt::flags(unsigned col) const
{
    if(col>=col_attrs.size()) return 0;
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->flags;
}

Fl_Flags Fl_ListView_ItemExt::flags(unsigned col, Fl_Flags f)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->flags = f;
}

Fl_Flags Fl_ListView_ItemExt::set_flag(unsigned col, Fl_Flags f)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->flags.set(f);
}

Fl_Flags Fl_ListView_ItemExt::clear_flag(unsigned col, Fl_Flags f)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->flags.clear(f);
}

Fl_Flags Fl_ListView_ItemExt::invert_flag(unsigned col, Fl_Flags f)
{
    if(col>=columns()) columns(col+1);
    ColAttr *a = (ColAttr*)col_attrs[col];
    return a->flags.invert(f);
}
