#include <efltk/Fl_MDI_Bar.h>
#include <efltk/Fl_MDI_Window.h>
#include <efltk/Fl_Button.h>

static void revert(Fl_Style* s) {
    s->color = FL_GRAY;
    s->button_color = FL_GRAY;
    s->box = FL_FLAT_BOX;
}

static Fl_Named_Style style("MDI_Bar", revert, &Fl_MDI_Bar::default_style);
Fl_Named_Style* Fl_MDI_Bar::default_style = &::style;

Fl_MDI_Bar::Fl_MDI_Bar(int x, int y, int w, int h, const char *l)
: Fl_Group(x,y,w,h,l)
{
	style(default_style);
	max_button_width_ = 100;
	spacing_ = 1;
}

Fl_MDI_Bar::~Fl_MDI_Bar()
{

}

static void fl_mdi_bar_button_cb(Fl_Button *button, Fl_MDI_Window *win)
{
	win->setTop();
	win->owner()->taskbar()->update_tasks();
}

void Fl_MDI_Bar::add_task(Fl_MDI_Window *win)
{
	begin();

	Fl_Button *b = new Fl_Button(0, 0, 0, 0, win->caption());
	b->callback((Fl_Callback*)fl_mdi_bar_button_cb, win);
	b->clear_click_to_focus();
	b->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT|FL_ALIGN_CLIP);
	b->color(button_color());

	end();

	redraw();
	relayout();	
}

Fl_Widget *Fl_MDI_Bar::find_task(Fl_MDI_Window *win)
{
	for(int n=0; n<children(); n++) {
		Fl_Widget *w = child(n);
		if(w->user_data()==win) {
			return w;
		}		
	}
	return 0;
}

void Fl_MDI_Bar::remove_task(Fl_MDI_Window *win)
{
	for(int n=0; n<children(); n++) {
		Fl_Widget *w = child(n);
		if(w->user_data()==win) {
			delete w;
			redraw();
			relayout();	
			return;
		}		
	}
}

void Fl_MDI_Bar::update_task(Fl_MDI_Window *win)
{
	for(int n=0; n<children(); n++) {
		Fl_Widget *w = child(n);
		if(w->user_data()==win) {
			w->label(win->caption());
			redraw();			
			return;
		}		
	}
}

void Fl_MDI_Bar::update_tasks()
{
	for(int n=0; n<children(); n++) {
		Fl_Widget *w = child(n);
		Fl_MDI_Window *win = (Fl_MDI_Window *)child(n)->user_data();
	
		if(!win->visible()) {
			w->hide();
			continue;
		} else
			w->show();

		if(win->isTop()) {
			w->color(fl_lighter(button_color()));
		} else
		if(win->minimized()) {
			w->color(fl_darker(button_color()));
		} else {
			w->color(button_color());
		}
	}
	relayout();
	redraw();
}

void Fl_MDI_Bar::layout()
{
	if(!children()) {
		Fl_Group::layout();
		return;
	}

	int X=0, Y=0, W=w(), H=h();
	box()->inset(X,Y,W,H);

	X+=2; Y+=2;	
	W-=4; H-=4;		

	W -= spacing_*children();
	int bW = W/children();	
	if(bW>max_button_width_) bW=max_button_width_;

	int bX = X;
	for(int n=0; n<children(); n++) {
		Fl_Widget *w = child(n);
		if(w->visible()) {
			int tW=bW, tH=H;
			fl_measure(w->label(), tW, tH, w->align());
                        if(tW>=bW-6) w->tooltip(w->label());
			else w->tooltip(0);			

			w->resize(bX, Y, bW, H);
			w->layout();
			bX += bW+spacing_;
		}
	}

	Fl_Widget::layout();
}
