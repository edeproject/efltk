#include <efltk/Fl_ListView_Item.h>
#include <efltk/Fl_ListView.h>
#include <efltk/fl_draw.h>

#include <stdlib.h>

Fl_ListView_Item::Fl_ListView_Item(const char *label1,
                                   const char *label2,
                                   const char *label3,
                                   const char *label4,
                                   const char *label5)
{
    m_parent = 0;
    m_user_data = 0;
    m_image = 0;
    m_damage = FL_DAMAGE_ALL;

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
    if(parent()) parent()->remove(this);
}

void Fl_ListView_Item::redraw(uchar c)
{
    m_damage = c;
    if(parent()) parent()->redraw(FL_DAMAGE_CHILD);
}

const char *Fl_ListView_Item::label() const
{
    if(!columns()) return "";
    return strings[0];
}

const char *Fl_ListView_Item::label(unsigned col) const
{
    if(col>=columns()) return "";
    return strings[col];
}

void Fl_ListView_Item::label(unsigned col, const char *text)
{
    if(col>=columns()) {
        columns(col+1);
    }
    strings.set(col, text);
}

void Fl_ListView_Item::label(unsigned col, const Fl_String &text)
{
    if(col>=columns()) {
        columns(col+1);
    }
    strings.set(col, text);
}

unsigned Fl_ListView_Item::columns() const
{
    return strings.count();
}

void Fl_ListView_Item::columns(unsigned count)
{
    strings.resize(count);
}

int Fl_ListView_Item::preferred_width(unsigned col) const
{
	if(col>=columns()) return 1;

    int w=parent()->col_width(col), h=0;
    if(w<0) w=300;
    fl_font(parent()->text_font(), parent()->text_size());
    fl_measure(label(col), w, h, parent()->column(col)->flags());
    if(col==0 && m_image)
        w += m_image->width();
    return w;
}

void Fl_ListView_Item::width_changed(unsigned row, unsigned col)
{
	if(col>=columns()) return;

    Fl_Flags a = parent()->column(col)->flags() & FL_ALIGN_MASK;
    if(a & FL_ALIGN_WRAP) {
        int w=parent()->col_width(col), h=0;
        if(w<0) w=300;
        w-=parent()->button_box()->dw();
        fl_font(parent()->text_font(), parent()->text_size());
        fl_measure(label(col), w, h, parent()->column(col)->flags());
        h += (int)fl_descent();
        if(col==0 && m_image) {
            if(h < m_image->height())
                h = m_image->height();
        }
        h += parent()->button_box()->dh() + parent()->leading();

        parent()->row_height(row, h);
    }
}

void Fl_ListView_Item::setup(unsigned row)
{
    int H = 0;
    fl_font(parent()->text_font() , parent()->text_size());
    H = int(fl_height() + fl_descent());

    for(unsigned n=0; n<columns(); n++)
    {
        const char *col_label = label(n);
        if(!col_label || !*col_label) continue;

        Fl_Flags a = parent()->column(n)->flags() & FL_ALIGN_MASK;
        int h=0;

        if(a & FL_ALIGN_WRAP) {
            // Wrap is on.
            int w=parent()->col_width(n);
            if(w<0) w=300;
            fl_measure(col_label, w, h, parent()->column(n)->flags());
        } else {
            // No wrap, check for multi line
            char *ptr = (char *)strchr(col_label, '\n');
            if(ptr) {
                // Multi line, calc lines
                h = (int)fl_height();
                while((ptr=strchr(ptr+1, '\n'))) {
                    h += (int)fl_height();
                }
                h += int(fl_height() + fl_descent());
            }
        }
        if(h>H) H=h;
    }

    if(m_image) {
        if(m_image->height()>H)
            H=m_image->height();
    }

    H += parent()->button_box()->dh() + parent()->leading();
    parent()->row_height(row, H);
}

void Fl_ListView_Item::draw_cell(unsigned row, unsigned col, int width, int height)
{
    if(!(damage() & FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE))
        return;    

    Fl_Flags f = 0;
    if(parent()->selected_row(row)) f |= FL_SELECTED;
    if(parent()->inactive_row(row) || !parent()->active()) f |= FL_INACTIVE;

    int X=0, Y=0, W=width, H=height;
    // Draw user defined border
    Fl_Boxtype box = parent()->button_box();
    box->draw(0, 0, W, H, fl_inactive(parent()->button_color(), f), FL_INVISIBLE);
    box->inset(X,Y,W,H);

    if(col==0 && m_image) {
        m_image->draw(X, H/2-m_image->height()/2, m_image->width(), m_image->height(), f);
        W -= m_image->width()+2;
        X += m_image->width()+2;
    }

    const char *str = label(col);
    if(str && *str) {
		fl_push_clip(0, 0, width, height);
        
		fl_font(parent()->text_font(), parent()->text_size());
        Fl_Color color = (f&FL_SELECTED) ? parent()->selection_text_color() : parent()->text_color();

		fl_color(fl_inactive(color, f));
		fl_draw(str, X, Y, W, H, parent()->column(col)->flags()|f);

		fl_pop_clip();
    }    
}

/////////////////////////////////////////////

int Fl_ListView_Item::compare_strings(Fl_ListView_Item *other, int column, int sort_type) const
{
    const char *txt = label(column);
    const char *other_txt = other->label(column);

    if(sort_type==Fl_ListView::SORT_ASC)
        return strcmp(txt, other_txt);

    return strcmp(other_txt, txt);
}

int Fl_ListView_Item::compare_integers(Fl_ListView_Item *other, int column, int sort_type) const
{
    const char *txt = label(column);
    const char *other_txt = other->label(column);

    if(sort_type==Fl_ListView::SORT_ASC)
        return strtol(txt,0,10) > strtol(other_txt,0,10);

    return strtol(txt,0,10) < strtol(other_txt,0,10);
}

int Fl_ListView_Item::compare_floats(Fl_ListView_Item *other, int column, int sort_type) const
{
    const char *txt = label(column);
    const char *other_txt = other->label(column);

    if(sort_type==Fl_ListView::SORT_ASC)
        return strtod(txt,0) > strtod(other_txt,0);

    return strtod(txt,0) < strtod(other_txt, 0);
}

int Fl_ListView_Item::compare_dates(Fl_ListView_Item *other, int column, int sort_type) const
{
    const char *txt = label(column);
    const char *other_txt = other->label(column);

    if(sort_type==Fl_ListView::SORT_ASC)
        return Fl_Date_Time(txt) > Fl_Date_Time(other_txt);

    return Fl_Date_Time(txt) < Fl_Date_Time(other_txt);
}

int Fl_ListView_Item::compare_datetimes(Fl_ListView_Item *other, int column, int sort_type) const
{
    const char *txt = label(column);
    const char *other_txt = other->label(column);

    if(sort_type==Fl_ListView::SORT_ASC)
        return Fl_Date_Time(txt) > Fl_Date_Time(other_txt);

    return Fl_Date_Time(txt) < Fl_Date_Time(other_txt);
}

int Fl_ListView_Item::compare(Fl_ListView_Item *other, int column, int sort_type)
{
    switch (parent()->column(column)->type()) {
    case VAR_INT:
        return compare_integers(other, column, sort_type);
    case VAR_FLOAT:
        return compare_floats(other, column, sort_type);
    case VAR_DATE:
        return compare_dates(other, column, sort_type);
    case VAR_DATETIME:
        return compare_datetimes(other, column, sort_type);
    default:
        break;
    }
    return compare_strings(other, column, sort_type);
}
