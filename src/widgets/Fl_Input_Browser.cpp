#include <efltk/Fl_Input_Browser.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Browser.h>
#include <efltk/fl_draw.h>
#include <efltk/x.h>
#include <efltk/Fl_Util.h>

#define SIZE_GRIP 6

//////////////////////////////////////////////
//////////////////////////////////////////////

class ComboWindow : public Fl_Menu_Window {
public:
    int handle(int);
    void draw();
    ComboWindow(int x, int y, int w, int h) : Fl_Menu_Window(x, y, w, h) {
        combo=0;
    }

    Fl_Input_Browser *combo;
};


// CET - FIXME - this doesn't seem to be working
// Use this to copy all the items out of one group into another:
class Share_List : public Fl_List {
public:
    Fl_Menu_* other;
    int children(const Fl_Menu_*, const int* indexes, int level) {
        return other->children(indexes, level);
    }
    Fl_Widget* child(const Fl_Menu_*, const int* indexes, int level) {
        return other->child(indexes, level);
    }
    void flags_changed(const Fl_Menu_*, Fl_Widget* widget) {
        other->list()->flags_changed(other,widget);
    }
} share_list; // only one instance of this.

//////////////////////////////////////////////
//////////////////////////////////////////////

class ComboBrowser : public Fl_Browser {
public:
    ComboBrowser(int x, int y, int w, int h) : Fl_Browser(x, y, w, h, 0) {
        combo=0;
        when(FL_WHEN_RELEASE);
    }

    int handle(int);
    static void browser_cb(Fl_Widget *w, void *data);

    Fl_Input_Browser *combo;
};

int ComboBrowser::handle(int event)
{
    // Work-around...
    if(Fl::event_key()==FL_Down && (!item() || children()==1)) {
        item(child(0));
        Fl_Group::focus(item());
    }   

    if((event==FL_SHORTCUT||event==FL_KEY) && !(combo->type()&Fl_Input_Browser::NONEDITABLE)) {
        if( (Fl::event_key()!=FL_Escape) &&
                (Fl::event_key()!=FL_Up) &&
                (Fl::event_key()!=FL_Down) &&
                !(Fl::event_key()==FL_Enter && item()) )
            return combo->input()->handle(FL_KEY);
    }

    static bool was_wheel=false;
    if(was_wheel) {
        was_wheel=false;
        return 1;
    }

    switch (event) {
        case FL_MOUSEWHEEL: {
                was_wheel=true;
                break;
            }

        case FL_KEY:
        case FL_SHORTCUT:
            if(Fl::event_key() == FL_Escape) {
                combo->hide_popup();
                return 1;
            }
            break;

        case FL_PUSH: {
                Fl_Rect size_grip(w()-SIZE_GRIP, h(), SIZE_GRIP, SIZE_GRIP);
                if(size_grip.posInRect(Fl::event_x(), Fl::event_y())) return 1;

                if(Fl::event_x() > w() || Fl::event_x() < x() ||
                        Fl::event_y() > h() || Fl::event_y() < y() ) {
                    combo->hide_popup();
                    if(Fl::event_y() < y()-combo->h()) combo->send(FL_PUSH);
                    return 1;
                }
                break;
            }

        case FL_MOVE:
            event = FL_DRAG;

        case FL_RELEASE:
        case FL_DRAG:
        // this causes a drag-in to the widget to work:
            if (Fl::event_inside(0, 0, w(), h()))
                Fl::pushed(this);
            else {
                Fl::pushed(0);
                return 0;
            }

        default:
            break;
    }

    return Fl_Browser::handle(event);
}

void ComboBrowser::browser_cb(Fl_Widget *w, void *data)
{
    // we get callbacks for all keys?
    if(Fl::event_key() != FL_Enter && Fl::event_key() != ' ')
        return;

    ComboBrowser *br = (ComboBrowser *)w;
    Fl_Input_Browser *combo = (Fl_Input_Browser *)data;
    Fl_Widget *item = br->item();

    if(!item) return;
    if (item->is_group()) return; // can't select a group!

    combo->item(item);
    combo->value(item->label().c_str());
    combo->redraw(FL_DAMAGE_VALUE);
    combo->hide_popup();

    combo->do_callback();
}

//////////////////////////////////////////////
//////////////////////////////////////////////

int ComboWindow::handle(int event)
{
    static bool resizing = false;

    switch (event) {
        case FL_PUSH: {
                Fl_Rect size_grip(w()-SIZE_GRIP, h()-SIZE_GRIP, SIZE_GRIP, SIZE_GRIP);
                if(size_grip.posInRect(Fl::event_x(), Fl::event_y())) {
                    resizing = true;            
                    return 1;
                }       
                break;
            }

        case FL_DRAG:
            if(resizing) {
                int W=Fl::event_x(), H=Fl::event_y();
                if(W < combo->w()) W = combo->w();
                if(H < combo->h()) H = combo->h();
                size(W, H);
                combo->list->Fl_Group::size(W-box()->dw(), H-SIZE_GRIP-box()->dh());
                return 1;
            }
            break;

        case FL_RELEASE:
            if(resizing) {
                resizing=false;
                return 1;
            }
            break;

        case FL_KEY:
        case FL_MOVE:
            if(combo->list) combo->list->handle(event);
            return 1;

        default:
            break;
    }
    return Fl_Menu_Window::handle(event);
}

void ComboWindow::draw()
{
    Fl_Menu_Window::draw();

    for(int a=2; a<SIZE_GRIP+2; a++) {
        if(a%2) fl_color(FL_GRAY);
        else fl_color(FL_DARK3);
        fl_line(w()-a, h()-box()->dh(), w()-box()->dw(), h()-a);
    }
}

//////////////////////////////////////////////
//////////////////////////////////////////////

static Fl_Named_Style style("Input_Browser", 0, &Fl_Input_Browser::default_style);
Fl_Named_Style* Fl_Input_Browser::default_style = &::style;

void Fl_Input_Browser::input_cb(Fl_Input *in, Fl_Input_Browser *data) {
    data->do_callback();
}

#define popup_minw 100
#define popup_minh 40
#define popup_maxw 600
#define popup_maxh 400

// ctor initializer - used in both ctors
void Fl_Input_Browser::ctor_init() {
    callback(Fl_Widget::default_callback);
    align(FL_ALIGN_LEFT);
    style(default_style);

    if (input()->parent()) input()->parent()->remove(input());
    input()->parent(this);
    input()->when(FL_WHEN_CHANGED | FL_WHEN_ENTER_KEY_ALWAYS);
    input()->callback((Fl_Callback *)input_cb, this);

    over_now = 0; over_last = 1;

    win = 0; list = 0;
}

// Traditional ctor
Fl_Input_Browser::Fl_Input_Browser(int x, int y, int w, int h, const char *l)
: Fl_Menu_(x, y, w, h, l), m_input(x,y,w,h)
{
    ctor_init();
}

// New Style ctor
Fl_Input_Browser::Fl_Input_Browser(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Menu_(l,layout_size,layout_al,label_w), m_input(0,0,10,10)
{
    m_input.resize(x(),y(),w(),h());
    ctor_init();
}

// Destructor
Fl_Input_Browser::~Fl_Input_Browser()
{
    input()->parent(0);    
    if(win) delete win;
}

int Fl_Input_Browser::handle(int e)
{
    int TX, TY = 0, TW, TH = h();
    if(type()&NONEDITABLE) {
        TX = 0;
        TW = w();
    } else {
        TX = input()->x()+input()->w();
        TW = w()-(input()->x()+input()->w());
    }
    if (Fl::event_inside(TX, TY, TW, TH))
        over_now = 1;
    else
        over_now = 0;
    if((over_now != over_last) && highlight_color())
        redraw(FL_DAMAGE_HIGHLIGHT);

    if(e == FL_FOCUS) Fl::focus(input());

    if((Fl::event_inside(input()->x(), input()->y(), input()->w(), input()->h()) || e == FL_KEY) && !(type()&NONEDITABLE) && Fl::pushed() != this)
    {
        if(e == FL_PUSH) {
            Fl::pushed(input());
            Fl::focus(input());
        }
        return input()->send(e);//handle(e);
    }

    switch (e) {
        case FL_PUSH: {
                if(!win || !win->visible())
                    popup();
                return 1;
            }

        case FL_FOCUS:
        case FL_UNFOCUS:
            if (type()&NONEDITABLE) break;
            return input()->handle(e);

        case FL_ENTER: case FL_MOVE: return 1;
    }
    return 0;
}

void Fl_Input_Browser::draw()
{
    Fl_Flags f = flags();
    if (!active_r()) f.set(FL_INACTIVE);
    //minw_ = w();
    if (damage()&FL_DAMAGE_ALL) draw_frame();
    int X = 0, Y = 0, W = w(), H = h(); box()->inset(X, Y, W, H);
    int W1 = H*4/5;
    if (damage()&(FL_DAMAGE_ALL|FL_DAMAGE_CHILD)) {
        input()->resize(X, Y, W-W1, H);
        input()->set_damage(FL_DAMAGE_ALL);
        input()->copy_style(style()); // force it to use this style
        input()->box(FL_FLAT_BOX);

        // fix for relative coordinates
        fl_push_matrix();
        fl_translate(X,Y);

        input()->draw();

        fl_pop_matrix();
        input()->set_damage(0);
    }
    if(damage()&(FL_DAMAGE_ALL|FL_DAMAGE_VALUE|FL_DAMAGE_HIGHLIGHT))
    {
        if(over_now) f.set(FL_HIGHLIGHT);
        X += W-W1;
        W = W1;
	button_box(FL_DIV_UP_BOX);
        // draw the little mark at the right:
        draw_glyph(FL_GLYPH_DOWN_BUTTON, X, Y, W, H, f);
        over_last = over_now;
    }
}

void Fl_Input_Browser::hide_popup()
{
    if(win && win->visible()) {
        Fl::exit_modal();
    }
}

void Fl_Input_Browser::popup()
{
    bool resize_only = false;

    if(!win || !win->visible()) 
    {
        Fl_Group::current(0);

        if(!win) {
            win = new ComboWindow(0,0,0,0);
            win->set_override();

            win->begin();
            list = new ComboBrowser(0,0,0,0);
            list->box(FL_FLAT_BOX);
            list->callback(ComboBrowser::browser_cb, this);
            list->when(FL_WHEN_CHANGED | FL_WHEN_RELEASE_ALWAYS | FL_WHEN_ENTER_KEY_ALWAYS);        
            list->end();

            win->end();
            win->box(FL_BORDER_BOX);

            win->combo = this;
            list->combo = this;
        }        

        share_list.other = this;
        list->list(&share_list);

        list->indented((type()&INDENTED) != 0);
        win->color(list->color());

    } else
        resize_only = true;

    list->layout();
    int W = list->max_width() + list->scrollbar.w() + list->box()->dw();
    int H = list->max_height() + box()->dh() + SIZE_GRIP;
    if(W > popup_maxw) W = popup_maxw;
    if(H > popup_maxh) H = popup_maxh;
    if(W < popup_minw) W = popup_minw;
    if(W < width()) W = width();
    if(H < popup_minh) H = popup_minh;

    int X = x(); int Y = y()+h();
    for (Fl_Widget *o = parent(); o; o = o->parent()) {
        X += o->x(); Y += o->y();
    }

    int down = Fl::h() - Y;
    int up = Y-h();
    if(H > down) {
        if(up > down) {
            Y = up-H;
            if (Y < 0) {
                Y = 0;
                H = up;
            }
        } else {
            H = down;
        }
    }
    if (X + W > Fl::w()) {
        X = Fl::w() - W;
        if (X < 0) {
            X = 0;
            W = Fl::w();
        }
    }

    win->resize(X,Y,W,H);
    win->layout();
    //int winW=W, winH=H;
    X=0,Y=0;
    win->box()->inset(X,Y,W,H);
    list->resize(X,Y,W,H-SIZE_GRIP);

    if(resize_only) return;

    set_value();
    redraw(FL_DAMAGE_VALUE);

    win->exec(0, true);
    win->hide();

    if(type()&NONEDITABLE) throw_focus();
    else Fl::focus(input());

    clear_value();
    redraw(FL_DAMAGE_VALUE);
}

void Fl_Input_Browser::preferred_size(int& w, int& h) const
{
    fl_font(text_font(), float(text_size()));
    h = int(fl_height()+fl_descent()) + box()->dh() + 2;
    if(m_input.maximum_size()>0) {
        int ms = m_input.maximum_size() + 1;
        if (ms > 50) ms = 50;
        w = ms * (int)fl_width((unsigned int)'W') + h;
    }
}
