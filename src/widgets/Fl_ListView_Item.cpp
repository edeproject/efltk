#include <efltk/Fl_ListView_Item.h>

Fl_ListView_Item::Fl_ListView_Item(const char *label1,
                                   const char *label2,
                                   const char *label3,
                                   const char *label4,
                                   const char *label5)
: Fl_Widget(0,0,0,0,0)
{
    list = (Fl_ListView *)parent();

    Fl_Widget::set_flag(FL_LISTVIEW_ITEM);

    for(int a=0; a<MAX_COLUMNS; a++) {
        colflags[a] = FL_ALIGN_LEFT;
        images[a] = 0;
        labels[a] = 0;
        widths[a] = 0;
        fonts[a] = label_font();
        font_sizes[a] = label_size();
        colors[a] = label_color();
    }

    if(label1) labels[0]=label1;
    if(label2) labels[1]=label2;
    if(label3) labels[2]=label3;
    if(label4) labels[3]=label4;
    if(label5) labels[4]=label5;
}

Fl_ListView_Item::~Fl_ListView_Item()
{
    for(int a=0; a<MAX_COLUMNS; a++) {
        if(colflags[a] & FL_COPIED_LABEL)
            if(labels[a])
                free((void *)labels[a]);
    }
}

void Fl_ListView_Item::copy_label(int col, const char *txt)
{
    if(colflags[col]&FL_COPIED_LABEL) free((void*)labels[col]);
    if(txt) {
        labels[col] = strdup(txt);
        colflags[col] |= FL_COPIED_LABEL;
    } else {
        labels[col] = 0;
        colflags[col] &= ~FL_COPIED_LABEL;
    }
}

void Fl_ListView_Item::draw()
{
    int X=2;
    for(int a=0; a<list->columns(); a++) {
        draw_cell(X,y(),list->column_width(a), h(),a);
        X+=list->column_width(a);
    }
}

void Fl_ListView_Item::draw_cell(int x, int y, int w, int h, int col)
{
    const char *txt = labels[col];
    const char *saved_label = Fl_Widget::label();

    if(txt) {
        fl_font(fonts[col], font_sizes[col]);
        fl_color(colors[col]);

        int iw=0,ih=0;
        if(images[col]) {
            images[col]->measure(iw,ih);
        }

        char *cutted_label=0;
        int textw = int(fl_width(txt));
        if(textw<list->column_width(col)) {
            if(strchr(txt, '\n')) cutted_label = fl_cut_multiline(txt, list->column_width(col)-leading()-iw);
            else cutted_label = fl_cut_line(txt, list->column_width(col)-leading()-iw);
            Fl_Widget::label(cutted_label); 
        } else {
            Fl_Widget::label(txt);
        }

        //Clear CLIP flag if set, cause we clip anyway =)
        if(align() & FL_ALIGN_CLIP) Fl_Widget::clear_flag(FL_ALIGN_CLIP);

        label_color(colors[col]);
        label_size(font_sizes[col]); label_font(fonts[col]);
        Fl_Image *si = Fl_Widget::image();
        Fl_Widget::image(images[col]);

        if(colflags[col]&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {x += 3; w -= 6;}

        fl_push_clip(x,y,w,h);
        draw_label(x, y, w, h, colflags[col]|(flags()&(FL_SELECTED|FL_INACTIVE)));
        fl_pop_clip();

        Fl_Widget::image(si);
        if(cutted_label) delete []cutted_label;
    }
    Fl_Widget::label(saved_label);
}

// Measure the space the draw() will take:
void Fl_ListView_Item::layout()
{
    if(w() && h()) return;

    int H = 0;
    int W = 0;

    for(int a=0; a<list->columns(); a++)
    {
        const char *txt = label(a);
        if(txt) {
            int w,h;
            fl_font(fonts[a] , font_sizes[a]);
            fl_measure(txt, w, h, colflags[a]);
            widths[a] = w+leading();
            W+=w;
            if(h>H) H=h;
        }

        Fl_Image *im = image(a);
        if(im) {
            int w,h;
            im->measure(w,h);
            widths[a] += w;
            W+=w;
            if(h>H) H=h;
        }
    }

    w(W);
    h(H);

    Fl_Widget::layout();
}
