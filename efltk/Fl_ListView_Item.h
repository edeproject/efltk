#ifndef FL_LISTITEM_H_
#define FL_LISTITEM_H_

#include "Fl.h"
#include "Fl_Widget.h"
#include "fl_draw.h"
#include "Fl_Image.h"
#include "Fl_ListView.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FL_LISTVIEW_ITEM 0x11000000

class Fl_ListView_Item : public Fl_Widget {
public:
    Fl_ListView_Item();
    Fl_ListView_Item(const char *label1,
                 const char *label2=0,
                 const char *label3=0,
                 const char *label4=0,
                 const char *label5=0);
    ~Fl_ListView_Item();

    Fl_ListView *listview() { return list; }
    void draw();
    void draw_cell(int x, int y, int w, int h, int col);
    void layout();

    int width(int col) { return widths[col]; }

    void copy_label(int col, const char *txt);

    Fl_Flags column_flags(int col, int f) { return colflags[col] = f; }
    Fl_Flags column_flags(int col) { return colflags[col]; }
    Fl_Flags column_set_flag(int col, int f)	{return colflags[col] |= f;}
    Fl_Flags column_clear_flag(int col, int f)	{return colflags[col] &= ~f;}
    Fl_Flags column_invert_flag(int col, int f)	{return colflags[col] ^= f;}

    const char *label() { return label(0); }
    const char *label(int col) { return labels[col]; }
    void label(int col, const char *text) { labels[col] = text; }

    Fl_Font font(int col, int *size) { if(size) *size = font_sizes[col]; return fonts[col]; }
    void font(int col, Fl_Font font, int size) { fonts[col] = font; font_sizes[col] = size; }
    void color(int col, Fl_Color color) { colors[col] = color; }

    void image(int col, Fl_Image *im) { images[col] = im; }
    Fl_Image *image(int col) { return images[col]; }

    static char *get_multiline(const char *buf, int maxwidth);

    int num;

private:
    Fl_ListView *list;

    const char *labels[MAX_COLUMNS];
    int widths[MAX_COLUMNS];

    Fl_Font fonts[MAX_COLUMNS];
    int font_sizes[MAX_COLUMNS];

    int colflags[MAX_COLUMNS];

    Fl_Color colors[MAX_COLUMNS];

    Fl_Image *images[MAX_COLUMNS];
};

#endif
