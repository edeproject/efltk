#include <efltk/Fl.h>
#include <efltk/Fl_Scroll.h>
#include <efltk/Fl_Round_Button.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Button_Group.h>
#include <efltk/db/Fl_Query.h>

#include <stdio.h>
#include <string.h>

static void default_button_callback(Fl_Widget *w, Fl_Button_Group *g) {    
	w->parent()->do_callback();
}

// Create a button in the group
Fl_Button *Fl_Button_Group::create_button(const char *the_label) 
{
	Fl_Button *btn = 0;
	const char *lbl = the_label;

	bool is_input_button = false;
	if (strcmp(the_label,"*") == 0 && !m_input_button) {
		is_input_button = true;
		lbl = "";
	}

	switch(type()) {

		case CHECK_BUTTONS: 
			btn = new Fl_Check_Button(0,0,0,0,lbl);
			break;

		case RADIO_BUTTONS: 
			btn = new Fl_Radio_Button(0,0,0,0,lbl);
			break;

		default:
		case NORMAL_BUTTONS:
			btn = new Fl_Button(0,0,0,0,lbl);
			break;

	};

	if (is_input_button) {
		m_input_button = btn;
		m_input = new Fl_Input(0,0,0,0);
	}

	btn->callback((Fl_Callback*)default_button_callback, this);

	return btn;
}

static void revert(Fl_Style* s)
{
	s->color = FL_GRAY;
	s->box = FL_ENGRAVED_BOX;
}


static Fl_Named_Style style("Button_Group", revert, &Fl_Button_Group::default_style);
Fl_Named_Style* Fl_Button_Group::default_style = &::style;

// Traditional ctor
Fl_Button_Group::Fl_Button_Group(int x,int y,int w,int h,const char *l)
: Fl_Group (x,y,w,h,l) 
{    
	style(default_style);
	layout_spacing(2);
	type(NORMAL_BUTTONS);

	m_input = 0;
	m_input_button = 0;

	end();
}

// New style ctor
Fl_Button_Group::Fl_Button_Group(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Group (l,layout_size,layout_al,label_w) 
{
	style(default_style);
	layout_spacing(2);
	type(NORMAL_BUTTONS);

	m_input = 0;
	m_input_button = 0;

	end();
}

// Define list of the buttons in the group
void Fl_Button_Group::buttons(const Fl_String_List& sl) 
{
	clear();
	m_input_button = NULL;
	m_input = NULL;

	begin();
	for (unsigned i = 0; i < sl.count(); i++) {
		const Fl_String& si = sl[i];
		create_button(si.c_str());
	}
	end();

	layout();
}

// Define list of the buttons in the group
void Fl_Button_Group::buttons(const Fl_Int_String_Map& sm) 
{
	clear();

	begin();

	Fl_Int_String_Iterator	 itor(sm);
	Fl_Int_String_Map::Pair	*pair;

	for (;;) {
		pair = *itor;
		if (!pair) break;
		Fl_Button *btn = create_button(pair->val.c_str());
		btn->argument(pair->id);
		itor.next();
	}

	end();

	layout();
}

void Fl_Button_Group::layout() 
{
	int X = 0, Y = 0;
	int W = w(), H = h();
	box()->inset(X,Y,W,H);
	X+=layout_spacing(); Y+=layout_spacing();
	W-=layout_spacing()*2; H+=layout_spacing()*2;

	for(int i = 0; i < children(); i++) 
	{
		Fl_Widget *btn = child(i);      
		if(btn==m_input) continue;

		int bw, bh=25;

		if (btn == m_input_button) {
			m_input->preferred_size(bw, bh);
			m_input_button->resize(X, Y, bh, bh);
			int x = m_input_button->x() + bh + 1;
			m_input->resize(x, Y, W-bh, bh);            
		} else {
			btn->preferred_size(bw, bh);            
			btn->resize(X, Y, W, bh);
		}

		Y += bh + layout_spacing();
	}    

	Fl_Widget::layout();
}

Fl_String Fl_Button_Group::value() const 
{
	Fl_String result;
	for (int i = 0; i < children(); i++) 
	{
		Fl_Widget *widget = child(i);        
		if(widget==m_input) continue;

		if (widget->value()) 
		{
			if(widget == m_input_button) {
				if (result.length() && m_input->size()) result += '|';
				result += m_input->value();
			} else {
				if (result.length()) result += '|';
				result += widget->label();            
			}
		}
	}
	return result;
}

void Fl_Button_Group::get_values(Fl_Int_String_Map& values) {
	values.clear();
	for (int i = 0; i < children(); i++) {
		Fl_Widget *widget = child(i);        
		if (widget==m_input) continue;

		if (widget->value()) {
			if (widget == m_input_button)
				values.insert(widget->argument(),m_input->value());
			else
				values.insert(widget->argument(),widget->label());
		}
	}
}

void Fl_Button_Group::deselect_all() 
{
	for (int i = 0; i < children(); i++) {
		Fl_Widget *widget = child(i);
		if(widget==m_input) continue;

		if(widget->value()) {
			widget->clear_value();
			widget->redraw();
		}
	}
}

int Fl_Button_Group::button_index(const char *label) 
{
	for (int i = 0; i < children(); i++) 
	{
		if(child(i)->label() == label)
			return i;
	}
	return -1;
}

static void set_button_value(Fl_Widget *w) {
	if(!w->value()) {
		w->set_value();
		w->redraw();
	}
}

void Fl_Button_Group::value(const char *s, const char *separator) {
	Fl_String_List sl(s, separator);
	value(sl);
}

void Fl_Button_Group::value(const Fl_String &s, const char *separator) {
	Fl_String_List sl(s, separator);
	value(sl);
}

void Fl_Button_Group::value(const Fl_String_List &sl) 
{
	if(!type()) return;

	deselect_all();

	for(unsigned i = 0; i < sl.count(); i++) {
		int ndx = button_index(sl[i].c_str());

		if (ndx > -1) {            
			set_button_value(child(ndx));
		} else {
			if (m_input_button) {
				set_button_value(m_input_button);
				m_input->value(sl[i].c_str());
			}
		}
		if(type()!=CHECK_BUTTONS) break;
	}

	do_callback();
}

void Fl_Button_Group::preferred_size(int& w,int& h) const
{
	h = box()->dy() + layout_spacing();    

	for(int i = 0; i < children(); i++) {
		Fl_Widget *widget = child(i);
		if(widget==m_input) continue;

		if(widget == m_input_button)
			h += m_input->h();
		else
			h += widget->h();

		h += layout_spacing();
	}

	h += box()->dh() - box()->dy();    
}
