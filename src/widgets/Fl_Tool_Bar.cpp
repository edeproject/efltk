#include <efltk/fl_math.h>
#include <efltk/Fl_Tool_Bar.h>
#include <efltk/Fl_Divider.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Item.h>
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
    if(item && item->user_data()) {
        Fl_Widget *toolw = (Fl_Widget *)item->user_data();
        if(item->value()) toolw->set_value();
        else toolw->clear_value();
        toolw->do_callback();
    }
}

int Fl_Tool_Bar::button_w = 24;
int Fl_Tool_Bar::button_h = 24;

static void revert(Fl_Style* s)
{
    s->button_box = FL_UP_BOX;
    s->button_color = FL_BLACK;
    s->glyph = Fl_Tool_Bar::button_glyph;
    s->color = FL_GRAY;
}

static Fl_Named_Style style("Tool_Bar", revert, &Fl_Tool_Bar::default_style);
Fl_Named_Style* Fl_Tool_Bar::default_style = &::style;


Fl_Tool_Bar::Fl_Tool_Bar(int x, int y, int w, int h, const char *label)
    : Fl_Bar(x,y,w,h)
{
    style(default_style);

    menu_ = new Fl_Menu_();
    menu_->callback(cb_menu, this);

    menu_but = new ToolMenuButton();
    menu_but->hide();
    ((ToolMenuButton*)menu_but)->menu = menu_;
    if(menu_but->parent()) menu_but->parent()->remove(menu_but);

    space_ = 2;
}

Fl_Tool_Bar::~Fl_Tool_Bar()
{
    delete menu_but;
}

void Fl_Tool_Bar::layout()
{
    if(!opened()) {
        Fl_Widget::layout();
        return;
    }

    int X=0,Y=0,W=w(),H=h();
    box()->inset(X,Y,W,H);
    X+=glyph_size()+space_;

    H=0;

    int out=-1;

    for(int n=0; n<children(); n++) {
        Fl_Widget *w=child(n);
        if(w==menu_||w==menu_but) continue;
        if(w==right_) continue;

        w->layout();
        w->position(X, box()->dh()+space_/2);

        if(H < (w->h()+space_+box()->dh()*2) ) H = w->h()+space_+box()->dh()*2;
        X+=w->w()+space_;

        if(X>W - (menu_but->visible()?15:0) ) {
            out=n;
            //w->hide();
            break;
        } else
            ;//w->show();
    }

    if(menu_->children()) menu_->clear();
    if(out>=0) {
        menu_but->resize(W-15, Y+2, 14, H-box()->dh()-4);
        menu_->resize(W-15, Y, 15, H-box()->dh());
        menu_but->show();

        menu_->begin();
        for(int n=out; n<children(); n++) {
            Fl_Widget *w = child(n);

            if(w->type()==Fl_Divider::VERTICAL) {
                // Create divider, only if not first in menu
                if(n>out)
                    new Fl_Divider(1, 5);

            } else {

                Fl_Item *i = new Fl_Item();
                // Tooltip as a label, if theres one
                i->copy_label(w->tooltip().empty() ? w->label() : w->tooltip());
                i->image(w->image());
                i->user_data(w);
                i->activate(w->active());
                i->type(w->type());
                if(w->value()) i->set_value();
                else i->clear_value();
            }
        }
        menu_->end();

    } else {
        menu_but->hide();
    }

    h(H);
    Fl_Widget::layout();
}

void Fl_Tool_Bar::draw()
{
    if(opened())
    {
        // make it not draw the inside label:
        int saved = flags(); align(FL_ALIGN_TOP);

        if(damage() & ~FL_DAMAGE_CHILD) {
            draw_frame();
            fl_push_clip(box()->dx(), box()->dy(), w()-box()->dw()-(menu_but->visible()?20:0), h()-box()->dh());
            int n; for (n = children(); n--;) draw_child(*child(n));
            draw_box();
            draw_inside_label();
            fl_pop_clip();

            if(menu_but->visible()) {
                fl_push_clip(w()-box()->dw()-(menu_but->visible()?20:0), box()->dy(), 30, h()-box()->dh());
                draw_child(*menu_but);
                draw_box();
                fl_pop_clip();
            }

            for (n = 0; n < children(); n++) draw_outside_label(*child(n));
        } else {
            fl_push_clip(box()->dx(), box()->dy(), w()-box()->dw()-(menu_but->visible()?20:0), h()-box()->dh());

            for (int n = 0; n < children(); n++) {
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

        if (damage() & (FL_DAMAGE_EXPOSE|FL_DAMAGE_HIGHLIGHT))
        {
            Fl_Flags f = 0;
            if (pushed) f |= FL_VALUE;
            if (highlighted) f |= FL_HIGHLIGHT;
            draw_glyph(0, 0, 0, glyph_size(), h(), f);
        }

    } else
        Fl_Bar::draw();
}

int Fl_Tool_Bar::handle(int ev)
{
	if(menu_but->visible() && Fl::event_inside(menu_but->x(), menu_but->y(), menu_but->w(), menu_but->h())) {
		int ret = menu_but->handle(ev);
		return ret;
	}
	return Fl_Bar::handle(ev);
}

void Fl_Tool_Bar::button_glyph(const Fl_Widget* widget, int glyph,
                               int x,int y,int w,int h, Fl_Flags flags)
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

Fl_Widget *Fl_Tool_Bar::add_button(const char *label, const char *tip, Fl_Image *image, Fl_Callback *cb)
{
    begin();
    Fl_Button *b = new Fl_Button(0, 0, button_w, button_h, label);
    b->tooltip(tip);
    b->image(image);
    b->callback(cb ? cb : Fl_Widget::default_callback);
    //b->box(FL_THIN_UP_BOX);
    end();
    return b;
}

Fl_Widget *Fl_Tool_Bar::add_divider()
{
    begin();
    Fl_VertDivider *l = new Fl_VertDivider(10, button_h);
    end();
    return l;
}



