#include <efltk/fl_math.h>
#include <efltk/Fl_Tool_Bar.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Button.h>

class ToolMenuButton : public Fl_Widget
{
public:
    ToolMenuButton() : Fl_Widget(0,0,0,0,0) {
        box(FL_FLAT_BOX);
    }
    void draw() {
        draw_box();
        int X=0, Y=0, W=w(), H=h();
        box()->inset(X,Y,W,H);
        draw_glyph(FL_GLYPH_RIGHT_BUTTON, X,Y,W,H,flags());
    }
    int handle(int ev) {
        if(ev==FL_PUSH && Fl::event_is_click()) {
            if(Fl::event_button()==FL_LEFT_MOUSE) {
                set_selected();
                redraw();
                menu->anim_flags(Fl_Menu_::LEFT_TO_RIGHT);
                menu->Fl_Group::focus(-1);
                menu->popup(w(), 0);
                clear_selected();
                redraw();
                return 1;
            }
        }
        return Fl_Widget::handle(ev);
    }
    Fl_Menu_ *menu;
};

void Fl_Tool_Bar::cb_menu(Fl_Widget *w, void *data)
{
    Fl_Menu_Button *m = (Fl_Menu_Button *)w;
    Fl_Widget *item = m->item();
    if (item && item->user_data()) {
        Fl_Widget *toolw = (Fl_Widget *)item->user_data();
        if(item->value()) toolw->set_value();
        else toolw->clear_value();
        toolw->do_callback(FL_MENU_ITEM);
    }
}

void Fl_Tool_Bar::default_callback(Fl_Widget *button, void *arg)
{
    Fl_Tool_Bar *b = (Fl_Tool_Bar *)button->parent();
    b->item(button);
    b->do_callback(FL_RELEASE);
}

int Fl_Tool_Bar::m_icon_sizes[2][2] = { { 20, 20 }, { 32, 32 } };
Fl_Tool_Bar::TbSize Fl_Tool_Bar::m_tb_def_size = TB_SIZE_SMALL;

static void revert(Fl_Style* s)
{
    s->button_box = FL_UP_BOX;
    s->button_color = FL_BLACK;
    s->glyph = Fl_Tool_Bar::button_glyph;
    s->color = FL_GRAY;
}

static Fl_Named_Style style("Tool_Bar", revert, &Fl_Tool_Bar::default_style);
Fl_Named_Style* Fl_Tool_Bar::default_style = &::style;

// ctor initializer - used in both ctors
void Fl_Tool_Bar::ctor_init()
{
    style(default_style);

    m_menu = new Fl_Menu_();
    m_menu->callback(cb_menu, this);

    m_menubut = new ToolMenuButton();
    m_menubut->hide();
    ((ToolMenuButton*)m_menubut)->menu = m_menu;
    if(m_menubut->parent())
        m_menubut->parent()->remove(m_menubut);

    layout_spacing(3);

    m_tb_size = TB_SIZE_DEFAULT;
}

// Traditional ctor
Fl_Tool_Bar::Fl_Tool_Bar(int x, int y, int w, int h, const char *label)
: Fl_Bar(x,y,w,h)
{
    ctor_init();
}

// New style ctor
Fl_Tool_Bar::Fl_Tool_Bar(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Bar(l,layout_size,layout_al,label_w)
{
    ctor_init();
}

// dtor
Fl_Tool_Bar::~Fl_Tool_Bar()
{
    delete m_menubut;
}

void Fl_Tool_Bar::layout()
{
    if(!opened()) {
        Fl_Widget::layout();
        return;
    }

    int X=0,Y=0,W=w(),H=h();
    box()->inset(X,Y,W,H);
    X+=glyph_size()+layout_spacing();

    H=0;
    int hoff = layout_spacing()*2 + box()->dh();

    int out=-1;

    for(int n=0; n<children(); n++)
    {
        Fl_Widget *w = child(n);
        if(w==m_menu || w==m_menubut || w==m_right) continue;

        w->show();

        int ww = w->w();
        int wh = h()-hoff;

        w->preferred_size(ww, wh);

        w->resize(X, box()->dy()+layout_spacing(), ww, wh);
        w->layout();

        if(H < w->h()+hoff)
            H = w->h()+hoff;

        X += w->w()+layout_spacing();

        if(X>W - (m_menubut->visible()?15:0) ) {
            out=n;
            //w->hide();
            break;
        }

    }

    if(m_menu->children())
        m_menu->clear();

    if(out>=0)
    {
        m_menubut->resize(W-15, Y+2, 14, H-box()->dh()-4);
        m_menu->resize(W-15, Y, 15, H-box()->dh());
        m_menubut->show();

        m_menu->begin();
        for(int n=out; n<children(); n++) {
            Fl_Widget *w = child(n);
            if(w==m_menu || w==m_menubut || w==m_right) continue;

            if(n>out) w->hide();
            if(w->is_group()) continue;

            if(w->type()==Fl_Divider::VERTICAL) {
                // Create divider, only if not first in menu
                if(n>out)
                    new Fl_Divider(1, 5);

            } else {

                Fl_Item *i = new Fl_Item();
                // Tooltip as a label, if theres one
                i->label(w->tooltip().empty() ? w->label() : w->tooltip());
                i->image(w->image());
                i->user_data(w);
                i->activate(w->active());
                i->type(w->type());
                if(w->value()) i->set_value();
                else i->clear_value();
            }
        }
        m_menu->end();

    } else {
        m_menubut->hide();
    }

    if(h() != H) {
        h(H);
    }
    Fl_Widget::layout();
}

void Fl_Tool_Bar::preferred_size(int &w, int &h) const
{
    if(opened()) {
        int H=0;
        for(int n=0; n<children(); n++)
        {
            Fl_Widget *w = child(n);
            if(w==m_menu || w==m_menubut || w==m_right) continue;
            int ww = w->w();
            int wh = 0;
            w->preferred_size(ww, wh);
            if(wh > H) H = wh;
        }
        H += layout_spacing()*2 + box()->dh();
        h = H;
    } else {
        h = glyph_size();
    }
}

void Fl_Tool_Bar::draw()
{
    int n;

    if(opened())
    {
        // make it not draw the inside label:
        int saved = flags(); align(FL_ALIGN_TOP);

        if(damage() & ~FL_DAMAGE_CHILD) {
            draw_frame();
            fl_push_clip(box()->dx(), box()->dy(), w()-box()->dw()-(m_menubut->visible()?20:0), h()-box()->dh());
            for (n = children(); n--;) draw_child(*child(n));
            draw_box();
            draw_inside_label();
            fl_pop_clip();

            if(m_menubut->visible()) {
                fl_push_clip(w()-box()->dw()-(m_menubut->visible()?20:0), box()->dy(), 30, h()-box()->dh());
                draw_child(*m_menubut);
                draw_box();
                fl_pop_clip();
            }

            for (n = 0; n < children(); n++) draw_outside_label(*child(n));
        } else {
            fl_push_clip(box()->dx(), box()->dy(), w()-box()->dw()-(m_menubut->visible()?20:0), h()-box()->dh());

            for(n = 0; n < children(); n++) {
                Fl_Widget& w = *child(n);
                if (w.damage() & FL_DAMAGE_CHILD_LABEL) {
                    draw_outside_label(w);
                    w.set_damage(w.damage() & ~FL_DAMAGE_CHILD_LABEL);
                }
                update_child(w);
            }

            fl_pop_clip();
        }

        flags(saved);

        if (damage() & (FL_DAMAGE_EXPOSE|FL_DAMAGE_HIGHLIGHT|FL_DAMAGE_ALL))
        {
            Fl_Flags f = 0;
            if (pushed) f.set(FL_VALUE);
            if (highlighted) f.set(FL_HIGHLIGHT);
            draw_glyph(0, 0, 0, glyph_size(), h(), f);
        }

    } else
        Fl_Bar::draw();
}

int Fl_Tool_Bar::handle(int ev)
{
    if(m_menubut->visible() && Fl::event_inside(m_menubut->x(), m_menubut->y(), m_menubut->w(), m_menubut->h())) {
        int ret = m_menubut->handle(ev);
        return ret;
    }
    return Fl_Bar::handle(ev);
}

void Fl_Tool_Bar::button_glyph(const Fl_Widget* widget, int glyph, int x,int y,int w,int h, Fl_Flags flags)
{
    int X=0, Y=0, W=w, H=h;
    widget->box()->inset(X,Y,W,H);

    if(h>w) {
        int c = int(floor((w/2)+.5));
        widget->button_box()->draw(c-2, Y+2, 2, H-4, widget->button_color(), flags);
        widget->button_box()->draw(c+1, Y+2, 2, H-4, widget->button_color(), flags);

    } else {
        int c = int((floor((h/2)+.5)));
        widget->button_box()->draw(X+2, c-2, W, 2, widget->button_color(), flags);
        widget->button_box()->draw(X+2, c+1, W, 2, widget->button_color(), flags);
    }
}

Fl_Tool_Button *Fl_Tool_Bar::add_toggle(Fl_Image *image, long id, const char *label, const char *tip)
{
    Fl_Tool_Button *b = Fl_Tool_Button::create(this, image, label, tip, id);
    b->type(Fl_Button::TOGGLE);
    return b;
}

Fl_Tool_Button *Fl_Tool_Bar::add_button(Fl_Image *image, long id, const char *label, const char *tip)
{
    return Fl_Tool_Button::create(this, image, label, tip, id);
}

Fl_Tool_Button *Fl_Tool_Bar::add_toggle(const char *label, const char *tip, Fl_Image *image, Fl_Callback *cb, void *data)
{
    Fl_Tool_Button *b = Fl_Tool_Button::create(this, image, label, tip, cb, data);
    b->type(Fl_Button::TOGGLE);
    return b;
}

Fl_Tool_Button *Fl_Tool_Bar::add_button(const char *label, const char *tip, Fl_Image *image, Fl_Callback *cb, void *data)
{
    return Fl_Tool_Button::create(this, image, label, tip, cb, data);
}

Fl_Divider *Fl_Tool_Bar::add_divider()
{
    begin();

    int dw, dh;
    get_icon_size(tb_size(), dw, dh);

    Fl_VertDivider *l = new Fl_VertDivider(5, dh);

    end();
    return l;
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

Fl_Tool_Button::TbShowMode Fl_Tool_Button::m_def_showmode = Fl_Tool_Button::SHOW_AUTO;
Fl_Tool_Button::TbTextPos Fl_Tool_Button::m_def_textpos = Fl_Tool_Button::POS_BOTTOM;

static void button_revert(Fl_Style* s)
{
    s->label_size = 11;
    s->box = FL_UP_BOX;
    s->color = FL_GRAY;
}

static Fl_Named_Style but_style("Tool_Button", button_revert, &Fl_Tool_Bar::default_style);
Fl_Named_Style* Fl_Tool_Button::default_style = &::but_style;

Fl_Tool_Button::Fl_Tool_Button(Fl_Tool_Bar *bar)
    : Fl_Button(0,0,0,0), m_bar(bar)
{
    accept_focus(false);
    style(Fl_Tool_Button::default_style);

    m_showmode = SHOW_DEFAULT;
    m_textpos  = POS_DEFAULT;

    small = big = 0;
}

Fl_Tool_Button::~Fl_Tool_Button()
{
    if(small && small!=image()) {
        delete small;
    }
    if(big && big!=image()) {
        delete big;
    }
}

Fl_Tool_Button *Fl_Tool_Button::create(Fl_Tool_Bar *bar, Fl_Image *image, const char *label, const char *tooltip, long id)
{
    return create(bar, image, label, tooltip, 0, (void*)id);
}

Fl_Tool_Button *Fl_Tool_Button::create(Fl_Tool_Bar *bar, Fl_Image *image, const char *label, const char *tooltip, Fl_Callback *cb, void *data)
{
    Fl_Group *saved = Fl_Group::current();
    Fl_Group::current(bar);

    Fl_Tool_Button *b = new Fl_Tool_Button(bar);
    if(image) b->image(image);
    if(label) b->label(label);
    if(tooltip) b->tooltip(tooltip);
    if(cb) b->callback(cb); else b->callback(Fl_Tool_Bar::default_callback);
    if(data) b->user_data(data);

    Fl_Group::current(saved);

    return b;
}

void Fl_Tool_Button::draw()
{
    Fl_String saved_l;
    Fl_Image *saved_im = image();

    TbShowMode sm = showmode();
    if(sm==SHOW_DEFAULT) sm = default_showmode();

    if(sm==SHOW_AUTO) {
        if(image()) sm = SHOW_IMAGE;
        else        sm = SHOW_TEXT;
    }

    if(!(sm&SHOW_IMAGE))
        image(0);
    else {
        if(m_bar->tb_size() == Fl_Tool_Bar::TB_SIZE_SMALL && small) {
            image(small);
        } else if(m_bar->tb_size() == Fl_Tool_Bar::TB_SIZE_BIG && big) {
            image(big);
        }
    }
    if(!(sm&SHOW_TEXT)) {
        saved_l = label();
        label("");
    }

    Fl_Button::draw();

    image(saved_im);
    if(!saved_l.empty()) {
        label(saved_l);
    }
}

void Fl_Tool_Button::preferred_size(int &w, int &h) const
{
    TbTextPos tp = textpos();
    if(tp==POS_DEFAULT) tp = default_textpos();

    TbShowMode sm = showmode();
    if(sm==SHOW_DEFAULT) sm = default_showmode();

    if(sm==SHOW_AUTO) {
        if(image()) sm = SHOW_IMAGE;
        else        sm = SHOW_TEXT;
    }

    int H=0, W=0;
    if(sm&SHOW_TEXT) {
        measure_label(W, H);
    }

    if(sm&SHOW_IMAGE) {
        int bw, bh;
        m_bar->get_icon_size(m_bar->tb_size(), bw, bh);

        if(tp == POS_RIGHT) W += bw;
        else                H += bh;

        if(W < bw) W = bw;
        if(H < bh) H = bh;
    }

    W += box()->dw() + 4;
    H += box()->dh() + 4;

    if(W < H) W = H;

    w = W;
    h = H;
}

void Fl_Tool_Button::layout()
{
    TbShowMode sm = showmode();
    if(sm==SHOW_DEFAULT) sm = default_showmode();

    if(sm==SHOW_AUTO) {
        if(image()) sm = SHOW_IMAGE;
        else        sm = SHOW_TEXT;
    }

    int bw, bh;
    m_bar->get_icon_size(m_bar->tb_size(), bw, bh);

    // Create/free big and small images
    if(image() && sm&SHOW_IMAGE)
    {
        if(m_bar->tb_size() == Fl_Tool_Bar::TB_SIZE_SMALL)
        {
            if(small && (small->width()!=bw || small->height()!=bh)) {
                if(small!=image()) delete small;
                small = 0;
            }
            if(!small) {
                if(image()->width()==bw && image()->height()==bh)
                    small = image();
                else
                    small = image()->scale(bw, bh);
            }
        } else {
            if(big && (big->width()!=bw || big->height()!=bh)) {
                if(big!=image()) delete big;
                big = 0;
            }
            if(!big) {
                if(image()->width()==bw && image()->height()==bh)
                    big = image();
                else
                    big = image()->scale(bw, bh);
            }
        }
    }

    Fl_Button::layout();
}
