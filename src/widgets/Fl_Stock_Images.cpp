#include <efltk/Fl_Stock_Images.h>
#include <efltk/Fl_Pixmap.h>

#include "images/stock_cancel.xpm"
#include "images/stock_delete.xpm"
#include "images/stock_edit.xpm"
#include "images/stock_help.xpm"
#include "images/stock_insert.xpm"
#include "images/stock_left.xpm"
#include "images/stock_new.xpm"
#include "images/stock_no.xpm"
#include "images/stock_ok.xpm"
#include "images/stock_open.xpm"
#include "images/stock_print.xpm"
#include "images/stock_printer.xpm"
#include "images/stock_right.xpm"
#include "images/stock_save.xpm"

#include "images/stock_next.xpm"
#include "images/stock_prior.xpm"
#include "images/stock_refresh.xpm"
#include "images/stock_search.xpm"
#include "images/stock_send.xpm"
#include "images/stock_stepleft.xpm"
#include "images/stock_stepright.xpm"
#include "images/stock_calendar.xpm"

static Fl_Pixmap cancel_pixmap(stock_cancel_xpm);
static Fl_Pixmap delete_pixmap(stock_delete_xpm);
static Fl_Pixmap edit_pixmap(stock_edit_xpm);
static Fl_Pixmap help_pixmap(stock_help_xpm);
static Fl_Pixmap insert_pixmap(stock_insert_xpm);
static Fl_Pixmap left_pixmap(stock_left_xpm);
static Fl_Pixmap new_pixmap(stock_new_xpm);
static Fl_Pixmap no_pixmap(stock_no_xpm);
static Fl_Pixmap ok_pixmap(stock_ok_xpm);
static Fl_Pixmap open_pixmap(stock_open_xpm);
static Fl_Pixmap print_pixmap(stock_print_xpm);
static Fl_Pixmap printer_pixmap(stock_printer_xpm);
static Fl_Pixmap right_pixmap(stock_right_xpm);
static Fl_Pixmap save_pixmap(stock_save_xpm);

static Fl_Pixmap next_pixmap(stock_next_xpm);
static Fl_Pixmap prior_pixmap(stock_prior_xpm);
static Fl_Pixmap refresh_pixmap(stock_refresh_xpm);
static Fl_Pixmap search_pixmap(stock_search_xpm);
static Fl_Pixmap send_pixmap(stock_send_xpm);
static Fl_Pixmap stepleft_pixmap(stock_stepleft_xpm);
static Fl_Pixmap stepright_pixmap(stock_stepright_xpm);
static Fl_Pixmap calendar_pixmap(stock_calendar_xpm);

class Fl_Stock_Image : public Fl_Image
{
public:

    Fl_Image *image() const { return other_image ? other_image : default_image; }

    virtual void _draw(int dx, int dy, int dw, int dh,
                       int sx, int sy, int sw, int sh,
                       Fl_Flags f)
    {
        Fl_Image *im = image();
        im->measure(m_width, m_height);
        im->draw(dx,dy,dw,dh, sx,sy,sw,sh, f);
    }

    void set_default(Fl_Image *i) { default_image = i; i->measure(m_width, m_height); }
    void set_other(Fl_Image *i)   {
        other_image = i;
        if(i) {
            i->measure(m_width, m_height);
        } else {
            default_image->measure(m_width, m_height);
        }
    }

private:
    Fl_Image *default_image;
    Fl_Image *other_image;
};

static Fl_Stock_Image fl_stock_images[Fl_Stock_Images::LAST_STOCK_TYPE];

static void fl_init_stock_images()
{
    static bool been_here = false;
    if(been_here) return;
    been_here = true;

    fl_stock_images[Fl_Stock_Images::SI_OK].set_default(&ok_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_CANCEL].set_default(&cancel_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_NO].set_default(&no_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_OPEN].set_default(&open_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_SAVE].set_default(&save_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_BROWSE].set_default(&help_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_HELP].set_default(&help_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_NEXT].set_default(&next_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_PREV].set_default(&prior_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_LEFT].set_default(&left_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_RIGHT].set_default(&right_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_ADD].set_default(&insert_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_DELETE].set_default(&delete_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_EDIT].set_default(&edit_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_REFRESH].set_default(&refresh_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_CALENDAR].set_default(&calendar_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_PRINT].set_default(&print_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_PRINTER].set_default(&printer_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_INSERT].set_default(&insert_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_NEW].set_default(&new_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_SEARCH].set_default(&search_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_SEND].set_default(&send_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_STEPLEFT].set_default(&stepleft_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_STEPRIGHT].set_default(&stepright_pixmap);
    fl_stock_images[Fl_Stock_Images::SI_VIEW].set_default(&new_pixmap);
}

Fl_Image *Fl_Stock_Images::get_image(SI_Type type)
{
    fl_init_stock_images();
    return fl_stock_images[type].image();
}

void Fl_Stock_Images::set_image(SI_Type type, Fl_Image *image)
{
    fl_stock_images[type].set_other(image);
}
