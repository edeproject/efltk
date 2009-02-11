#ifndef _FL_LISTVIEW_HEADER_H_
#define _FL_LISTVIEW_HEADER_H_

#include "Fl_Image.h"
#include "Fl_Ptr_List.h"

class Fl_ListView;

/**
 * Fl_ListView_Header
 */
class Fl_ListView_Header : public Fl_Widget
{
public:
    static Fl_Named_Style* default_style;

    Fl_ListView_Header(Fl_ListView *parent);
    virtual ~Fl_ListView_Header();

    void show();
    void hide();

    virtual void draw(int col, int width, int height);
    virtual void draw() { Fl_Widget::draw(); }
    virtual int handle(int col, int event);
    virtual int handle(int event) { return Fl_Widget::handle(event); }

    bool capture_events() const { return (m_capture>=0); }

    void parent(Fl_ListView *p) { Fl_Widget::parent((Fl_Group*)p); }
    Fl_ListView *parent() const { return (Fl_ListView *)Fl_Widget::parent(); }

    ///////////////////////////////
    // Compatibility section

    void clear();

    void add_column(const char *name, int w=-1, Fl_Variant_Type column_type=VAR_STRING);
    void add_column(const Fl_String &name, int w=-1, Fl_Variant_Type column_type=VAR_STRING);

    void columns(int count);
    unsigned columns() const;

    int column_width(int col) const;
    void column_width(int col, int w);

    Fl_Variant_Type column_type(int col) const;
    void column_type(int col, Fl_Variant_Type w);

    Fl_Flags column_flags(int col, int f);
    Fl_Flags column_flags(int col) const;
    Fl_Flags column_set_flag(int col, int f);
    Fl_Flags column_clear_flag(int col, int f);
    Fl_Flags column_invert_flag(int col, int f);

    const Fl_String &column_label() const;
    const Fl_String &column_label(int col) const;

    void column_label(int col, const char *text);
    void column_label(int col, const Fl_String &text);
    void column_copy_label(int col, const char *txt);

    Fl_Font column_label_font(int col) const;
    int column_label_size(int col) const;
    Fl_Color column_label_color(int col) const;

    void column_label_size(int col, int size);
    void column_label_font(int col, Fl_Font font);
    void column_label_color(int col, Fl_Color color);

    void column_image(int col, Fl_Image *im);
    void column_image(int col, Fl_Image &im);
    Fl_Image *column_image(int col);
    const Fl_Image *column_image(int col) const;

protected:
    void set_capture(int col) { m_capture = col; }
    int get_capture() const { return m_capture; }

private:
    int m_capture;
};

#endif
