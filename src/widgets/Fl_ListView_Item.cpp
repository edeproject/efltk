#include <efltk/Fl_ListView_Item.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Fl_ListView_Item::Fl_ListView_Item(const char *label1,
                                   const char *label2,
                                   const char *label3,
                                   const char *label4,
                                   const char *label5)
: Fl_Widget(0,0,0,0,0)
{
	attr_list.auto_delete(true);
	int cols = 0;
	if(label5) cols=5;
	else if(label4) cols=4;
	else if(label3) cols=3;
	else if(label2) cols=2;
	else if(label1) cols=1;

	columns(cols);
    label(0, label1);
	label(1, label2);
	label(2, label3);
	label(3, label4);
	label(4, label5);
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
			attr *a = (attr*)attr_list[n];
			if(a->flags & FL_COPIED_LABEL) if(a->label) free((void *)a->label);
		}
		attr_list.resize(new_size);
	}
}

void Fl_ListView_Item::add_attr(int col)
{	
	attr *a = new attr;
	a->label = 0;
	a->flags = FL_ALIGN_LEFT;
	a->width = 0;
	a->font = Fl_Widget::label_font();
	a->font_size = Fl_Widget::label_size();
	a->color = Fl_Widget::label_color();
	a->image = 0;	
	attr_list[col] = a;
}

Fl_ListView_Item::~Fl_ListView_Item()
{
    for(uint n=0; n<attr_list.size(); n++) {
		attr *a = (attr*)attr_list[n];
        if(a->flags & FL_COPIED_LABEL)
            if(a->label) 
				free((void *)a->label);
    }
}

void Fl_ListView_Item::copy_label(int col, const char *txt)
{
	attr *a = (attr*)attr_list[col];
    if(a->flags&FL_COPIED_LABEL) free((void*)a->label);
    if(txt) {
        a->label = strdup(txt);
        a->flags |= FL_COPIED_LABEL;
    } else {
        a->label = 0;
        a->flags &= ~FL_COPIED_LABEL;
    }
}

void Fl_ListView_Item::draw()
{
    int X=2;
    for(int a=0; a<listview()->columns(); a++) {
        draw_cell(X,y(), listview()->column_width(a), h(),a);
        X+=listview()->column_width(a);
    }
}

void Fl_ListView_Item::draw_cell(int x, int y, int w, int h, int col)
{
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
    const char *txt = a->label;
    const char *saved_label = Fl_Widget::label();

    if(txt) {
        fl_font(a->font, float(a->font_size));
        fl_color(a->color);

        int iw=0,ih=0;
        if(a->image) {
            a->image->measure(iw,ih);
        }

        char *cutted_label=0;
        int textw = int(fl_width(txt));
        int colw = listview()->column_width(col)-iw-6;
        if(textw>colw) {
            if(strchr(txt, '\n')) cutted_label = fl_cut_multiline(txt, colw);
            else cutted_label = fl_cut_line(txt, colw);
            Fl_Widget::label(cutted_label);
        } else {
            Fl_Widget::label(txt);
        }		

        //Clear CLIP flag if set, cause we clip anyway =)
        if(align() & FL_ALIGN_CLIP) Fl_Widget::clear_flag(FL_ALIGN_CLIP);

		Fl_Widget::label_color(a->color);
        Fl_Widget::label_size(a->font_size);
		Fl_Widget::label_font(a->font);
        Fl_Image *si = Fl_Widget::image();
        Fl_Widget::image(a->image);

        if(a->flags&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {x += 3; w -= 6;}

        fl_push_clip(x,y,w,h);
        draw_label(x, y, w, h, a->flags|(flags()&(FL_SELECTED|FL_INACTIVE)));
        fl_pop_clip();

        Fl_Widget::image(si);        
    }
    Fl_Widget::label(saved_label);
}

// Measure the space the draw() will take:
void Fl_ListView_Item::layout()
{
    if(w() && h()) return;

    int H = 0;
    int W = 0;

    for(uint n=0; n<attr_list.size(); n++)
    {
		attr *a = (attr*)attr_list[n];
        const char *txt = a->label;
        if(txt) {
            int w,h;
            fl_font(a->font , float(a->font_size));
            fl_measure(txt, w, h, a->flags);
            a->width = w+leading();
            W+=w;
            if(h>H) H=h;
        }

        Fl_Image *im = a->image;
        if(im) {
            int w,h;
            im->measure(w,h);
            a->width += w;
            W+=w;
            if(h>H) H=h;
        }
    }

    w(W);
    h(H);

    Fl_Widget::layout();
}

int Fl_ListView_Item::width(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->width;
}

Fl_Flags Fl_ListView_Item::column_flags(int col, int f)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags = f; 
}

Fl_Flags Fl_ListView_Item::column_flags(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags; 
}

Fl_Flags Fl_ListView_Item::column_set_flag(int col, int f)
{
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags |= f;
}

Fl_Flags Fl_ListView_Item::column_clear_flag(int col, int f)
{
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags &= ~f;
}

Fl_Flags Fl_ListView_Item::column_invert_flag(int col, int f)
{
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->flags ^= f;
}

const char *Fl_ListView_Item::label()
{ 
	if(attr_list.size()==0) return 0;
	attr *a = (attr*)attr_list[0];
	return a->label; 
}

const char *Fl_ListView_Item::label(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->label;
}

void Fl_ListView_Item::label(int col, const char *text)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->label = text; 
}

Fl_Font Fl_ListView_Item::label_font(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->font; 
}

int Fl_ListView_Item::label_size(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->font_size; 	
}

void Fl_ListView_Item::label_font(int col, Fl_Font font)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->font = font; 	
}

void Fl_ListView_Item::label_size(int col, int size)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->font_size = size; 	
}

void Fl_ListView_Item::label_color(int col, Fl_Color color)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->color = color; 
}

void Fl_ListView_Item::image(int col, Fl_Image *im)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->image = im; 
}

void Fl_ListView_Item::image(int col, Fl_Image &im)
{ 
	if((uint)col>=attr_list.size()) return;
	attr *a = (attr*)attr_list[col];
	a->image = &im; 
}

Fl_Image *Fl_ListView_Item::image(int col)
{ 
	if((uint)col>=attr_list.size()) return 0;
	attr *a = (attr*)attr_list[col];
	return a->image; 
}
