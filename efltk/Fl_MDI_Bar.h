#ifndef _FL_MDI_BAR_H_
#define _FL_MDI_BAR_H_

#include <efltk/Fl_Group.h>
#include <efltk/Fl_MDI_Window.h>

class Fl_MDI_Bar : public Fl_Group
{
public:
	static Fl_Named_Style *default_style;

	Fl_MDI_Bar(int x, int y, int w, int h, const char *l=0);
	virtual ~Fl_MDI_Bar();
	
	virtual void layout();

	int spacing() { return spacing_; }
	void spacing(int val) { spacing_ = val; }

	int max_button_width() { return max_button_width_; }
	void max_button_width(int w) { max_button_width_ = w; }

	Fl_Widget *find_task(Fl_MDI_Window *win);

	// These are called by Fl_MDI_Viewport..
	void add_task(Fl_MDI_Window *win);
	void remove_task(Fl_MDI_Window *win);
	void update_task(Fl_MDI_Window *win);
	void update_tasks();

private:
	int max_button_width_;
	int spacing_;
};

#endif

