#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Popup_Window.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Pixmap.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Combo_Box.h>

static char * add_small_xpm[] = {
    "15 15 6 1",
    "   c None",
    ".  c #008080",
    "+  c #000000",
    "@  c #FFFF00",
    "#  c #00FFFF",
    "$  c #808000",
    "               ",
    "        ++++   ",
    "        +##+   ",
    "        +##+   ",
    "     ++++##++++",
    "  ++++########+",
    " +$$$+########+",
    " +$$$++++##++++",
    " +$$$$$$+##+   ",
    " +$$++++++++++ ",
    " +$+@@@@@@@@@+ ",
    " ++@@@@@@@@@+  ",
    " +@@@@@@@@@+   ",
    " ++++++++++    ",
    "               "};

static char * browse_small_xpm[] = {
    "15 15 5 1",
    "   c None",
    ".  c #008080",
    "+  c #000000",
    "@  c #FFFF00",
    "#  c #808000",
    "               ",
    "       +++     ",
    "      +   + +  ",
    "           ++  ",
    "          +++  ",
    "  +++          ",
    " +###++++++    ",
    " +########+    ",
    " +###++++++++++",
    " +##+@@@@@@@@@+",
    " +#+@@@@@@@@@+ ",
    " ++@@@@@@@@@+  ",
    " +@@@@@@@@@+   ",
    " ++++++++++    ",
    "               "};

static char * delete_small_xpm[] = {
    "15 15 6 1",
    "   c None",
    ".  c #008080",
    "+  c #000000",
    "@  c #FFFF00",
    "#  c #808000",
    "$  c #FF0000",
    "               ",
    "               ",
    "               ",
    "     ++++++++++",
    "  ++++$$$$$$$$+",
    " +###+$$$$$$$$+",
    " +###++++++++++",
    " +#########+   ",
    " +##++++++++++ ",
    " +#+@@@@@@@@@+ ",
    " ++@@@@@@@@@+  ",
    " +@@@@@@@@@+   ",
    " ++++++++++    ",
    "               ",
    "               "};

static char * edit_small_xpm[] = {
    "15 15 10 1",
    "   c None",
    ".  c #000000",
    "+  c #800080",
    "@  c #FFFFFF",
    "#  c #C0C0C0",
    "$  c #000080",
    "%  c #808080",
    "&  c #FFFF00",
    "*  c #808000",
    "=  c #00FFFF",
    "         .&@@&&",
    "        .&@@&&$",
    "       .&@@&&$*",
    " ........@&&$*.",
    " .===%.##.&$*..",
    " .....#@@#.*..%",
    " .@@%.@@@#...% ",
    " .$$.#@@#..#.% ",
    " .@%..#..%##.% ",
    " .$....%#$$#.% ",
    " .@..%#.####.% ",
    " .$$$$@.@$$@.% ",
    " .@@@@@.@@@@.% ",
    " ............  ",
    "               "};

static char * refresh_small_xpm[] = {
    "15 15 5 1",
    "   c None",
    ".  c #008080",
    "+  c #000000",
    "@  c #808000",
    "#  c #FFFF00",
    "               ",
    "     ++++++    ",
    "    +@+####+   ",
    "    +@@+###+   ",
    "   +@@@@+###+  ",
    "   +@@@++###++ ",
    "   +@@@+#####+ ",
    "   +@@@++###+  ",
    "   +@@@+ +#+   ",
    "   +@@@+       ",
    "   +@@@+++++   ",
    "   +@@@+###+   ",
    "    +@@+###+   ",
    "    +@+###+    ",
    "     +++++     "};

static Fl_Pixmap   add_pixmap(add_small_xpm);
static Fl_Pixmap   browse_pixmap(browse_small_xpm);
static Fl_Pixmap   delete_pixmap(delete_small_xpm);
static Fl_Pixmap   edit_pixmap(edit_small_xpm);
static Fl_Pixmap   refresh_pixmap(refresh_small_xpm);

class Fl_Popup_ListView : public Fl_Popup_Window {
    Fl_ListView *m_listView;
    Fl_Widget   *m_editControl;
public:
    Fl_Popup_ListView(Fl_Widget *editControl=NULL);

    Fl_ListView *listview() { return m_listView; }

    void clicked() { set_value(); }
    void layout();
    void draw();
    int  handle(int);

    static void cb_clicked(Fl_Widget *w, void *d);

    bool popup();
    // Popup list view, relative to widget
    bool popup(Fl_Widget *editControl, int X, int Y, int W=0, int H=0);
};

void Fl_Popup_ListView::cb_clicked(Fl_Widget *w, void *d) {
    Fl_Window *win = w->window();
    if(win && Fl::event_button()<=3) {
        win->set_value();
        win->hide();
    }
}

Fl_Popup_ListView::Fl_Popup_ListView(Fl_Widget *editControl)
: Fl_Popup_Window(150,150,"ListView") {
    m_editControl = editControl;
    m_listView = new Fl_ListView(0,0,w(),h());
    m_listView->callback(Fl_Popup_ListView::cb_clicked);
    m_listView->box(FL_NO_BOX);

    end();
}

void Fl_Popup_ListView::draw() {
    Fl_Popup_Window::draw();
}

void Fl_Popup_ListView::layout() {
    m_listView->resize(box()->dx(),box()->dy(),w()-box()->dw(),h()-box()->dh());
    m_listView->layout();
    Fl_Popup_Window::layout();
}

bool Fl_Popup_ListView::popup() {
    if (m_editControl) {
        int width = m_editControl->w();
        if (width < 175) width = 175;
        int X=0, Y=0;
        for(Fl_Widget* w = m_editControl; w; w = w->parent()) {
            X += w->x();
            Y += w->y();
        }
        int height = 160;
        m_listView->size(width,height);
        resize(X, Y+m_editControl->h(), width+box()->dw(), height+box()->dh());
    }
    int rc = Fl_Popup_Window::show_popup();
    if (m_editControl)
        m_editControl->redraw();
    return rc;
}

bool Fl_Popup_ListView::popup(Fl_Widget *editControl, int X, int Y, int W, int H) {
    if (editControl) {
        m_editControl = editControl;
        int width = (W>0) ? W : editControl->w();
        if (width < 175) width = 175;
        int height = (H>0) ? H : 175;
        if (height < 175) height = 175;
        for(Fl_Widget* w = editControl; w; w = w->parent()) {
            X += w->x();
            Y += w->y();
        }
        resize(X, Y, width, height);
        layout(); // Make sure window moves
    }
    int rc = Fl_Popup_Window::show_popup();
    if (editControl)
        editControl->redraw();
    return rc;
}

int Fl_Popup_ListView::handle(int event) {
    int rc = Fl_Popup_Window::handle(event);
    if (rc) return rc;
    rc = m_listView->handle(event);
    return rc;
}

class Fl_Combo_Box_Panel : public Fl_Box {
    Fl_ListView *m_listView;
    void draw();
public:
    Fl_Combo_Box_Panel(Fl_ListView *lv);

    int handle(int);
};

Fl_Combo_Box_Panel::Fl_Combo_Box_Panel(Fl_ListView *lv)
: Fl_Box(0,0,10,10) {
    m_listView = lv;
    align(FL_ALIGN_LEFT);
    box(FL_FLAT_BOX);
}

void Fl_Combo_Box_Panel::draw() {
    int focused = -1;
    if (Fl::focus() == this) focused = 1;

    Fl_Color clr = fl_lighter(fl_lighter(parent()->color()));
    box()->draw(0, 0, w(), h(), clr);

    int dd = 2;
    int xx = 0;
    int yy = dd * 2;
    int hh = h()- dd * 3;

    Fl_ListView_Item    *item = (Fl_ListView_ItemExt *)m_listView->item();
    if (!item) return;

    Fl_ListView_ItemExt *item_ext = dynamic_cast<Fl_ListView_ItemExt *>(item);

    if (!item_ext) {
        fl_font(text_font(),text_size());
        fl_color(text_color());
    }

    for (unsigned c = 0; c < item->columns(); c++) {
        int ww = m_listView->column_width(c);
        fl_push_clip(xx+dd,yy,ww-dd,hh);
        if (item_ext) {
            fl_font(item_ext->label_font(c),item_ext->label_size(c));
            fl_color(item_ext->label_color(c));
        }
        fl_draw(item->label(c),xx+dd,yy,ww-dd,hh,FL_ALIGN_LEFT);

        fl_pop_clip();

        fl_line(xx + ww,0,xx + ww,h());

        xx += ww;
    }
}

int Fl_Combo_Box_Panel::handle(int event) {
    color( parent()->color() );
    switch (event) {
        case FL_FOCUS:
        case FL_UNFOCUS:
            redraw();
            return 1;
        case FL_PUSH:
            if (contains(Fl::focus())) return 1;
            Fl::focus(this);
            return 1;
        case FL_KEYBOARD: {
                unsigned ch = Fl::event_key();
                if (ch == FL_Tab) break;
                int rc = m_listView->handle(event);
                redraw();
                return rc;
            }
    }
    if (Fl_Box::handle(event)) return 1;

    return 0;
}
//-------------------------------------------------------------------
int button_to_event(int argument) {
    switch (argument) {
        case FL_CBB_INSERT:     return FL_UC_INSERT;
        case FL_CBB_EDIT:       return FL_UC_EDIT;
        case FL_CBB_DELETE:     return FL_UC_DELETE;
        case FL_CBB_REFRESH:    return FL_UC_REFRESH;
    }
    return FL_NO_EVENT;
}

Fl_Combo_Box::Fl_Combo_Box(int x,int y,int w,int h,const char *label)
: Fl_Group(x,y,w,h,label) {
    align(FL_ALIGN_LEFT);
    box(FL_THIN_DOWN_BOX);
    layout_spacing(0);
    end();

    m_popup = new Fl_Popup_ListView;

    begin();

    for (int i = 0; i < 5; i++) {
        Fl_Button *b = new Fl_Button(10,10,20,16,"");
        m_buttons[i] = b;
        b->layout_align(FL_ALIGN_RIGHT);
        b->callback(cb_button);
        b->argument(1 << i);
        switch (i) {
            case 0: 
                b->image(browse_pixmap); 
                b->callback(cb_browse);
                break;
            case 1: 
                b->image(refresh_pixmap); 
                break;
            case 2: 
                b->image(add_pixmap); 
                break;
            case 3: 
                b->image(delete_pixmap); 
                break;
            case 4: 
                b->image(edit_pixmap); 
                break;
        }
        if (i == 0) 
            b->show();
        else b->hide();
    }

    m_panel = new Fl_Combo_Box_Panel(listview());
    m_panel->layout_align(FL_ALIGN_CLIENT);

    end();
}

Fl_ListView *Fl_Combo_Box::listview() const { 
    return m_popup->listview(); 
}

void Fl_Combo_Box::cb_browse(Fl_Widget *w, void *) {
    Fl_Combo_Box *cb = (Fl_Combo_Box *) w->parent();
    Fl_Popup_ListView *popup = cb->m_popup;
    int saveValue = cb->value();
    if (popup->popup(w->parent(),0,w->parent()->h())) {
        // Call the callback function if the value has changed
        if (cb->value() != saveValue) 
            cb->do_callback(FL_DATA_CHANGE);
    } else {
        // Restore original value
        cb->value(saveValue);
    }
}

void Fl_Combo_Box::cb_button(Fl_Widget *w, void *) {
    Fl_Combo_Box *cb = (Fl_Combo_Box *) w->parent();
    int event = button_to_event(w->argument());
    cb->do_callback(event);
}

int Fl_Combo_Box::value() const {
    Fl_ListView_Item *item = listview()->item();
    if (!item) return 0;
    return (int) item->user_data();
}

void Fl_Combo_Box::value(int v) const {
    Fl_ListView_Item *item = listview()->find_userdata((void *)v);
    if (!item) return;
    listview()->select_only(item);
    listview()->show_item(item);
}

Fl_String Fl_Combo_Box::text(int column) const {
    Fl_ListView_Item *item = listview()->item();
    if (!item) return "";
    return item->label(column);
}

void Fl_Combo_Box::buttons(int buttons_set) {
    // Browse button is always shown
    for (int i = 1; i < 5; i++) {
        Fl_Button *b = m_buttons[i];
        if (buttons_set & b->argument())
            b->show();
        else b->hide();
    }
    relayout();
}
