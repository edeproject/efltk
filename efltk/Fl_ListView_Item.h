#ifndef FL_LISTITEM_H_
#define FL_LISTITEM_H_

#include "Fl_ListView.h"
#include "Fl.h"
#include "Fl_Widget.h"
#include "fl_draw.h"
#include "Fl_Image.h"
#include "Fl_Image_List.h"
#include "Fl_Int_List.h"
#include "Fl_String_List.h"

class Fl_ListView_Item : public Fl_Widget {
public:
    Fl_ListView_Item(const char *label1=0,
                 const char *label2=0,
                 const char *label3=0,
                 const char *label4=0,
                 const char *label5=0);
    virtual ~Fl_ListView_Item();
	
	Fl_ListView *listview() { return (Fl_ListView *)parent(); }

	void columns(uint count);
	uint columns();
    
    virtual void draw();
    virtual void draw_cell(int x, int y, int w, int h, int col);
    virtual void layout();

    int width(int col);

    void copy_label(int col, const char *txt);

    Fl_Flags column_flags(int col, int f);
    Fl_Flags column_flags(int col);
    Fl_Flags column_set_flag(int col, int f);
    Fl_Flags column_clear_flag(int col, int f);
    Fl_Flags column_invert_flag(int col, int f);

    const char *label();
    const char *label(int col);
    void label(int col, const char *text);

    Fl_Font label_font(int col);
	int label_size(int col);
	void label_size(int col, int size);
    void label_font(int col, Fl_Font font);
    void label_color(int col, Fl_Color color);

    void image(int col, Fl_Image *im);
    void image(int col, Fl_Image &im);
    Fl_Image *image(int col);

    static char *get_multiline(const char *buf, int maxwidth);

    int num;

protected:
	typedef struct {
		const char *label;
		Fl_Flags flags;
		int width;
		Fl_Font font;
		int font_size;
		Fl_Color color;
		Fl_Image *image;
	} attr;
	void add_attr(int col);

private:
	Fl_Ptr_List attr_list;
};

#endif
