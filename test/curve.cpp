//
// "$Id$"
//
// Curve test program for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Hor_Value_Slider.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Toggle_Button.h>

float args[10] = {
  20,20, 50,200, 100,20, 200,200, 0, 1
};

const char* name[10] = {
  "X0", "Y0", "X1", "Y1", "X2", "Y2", "X3", "Y3", "rotate", "scale"
};

bool points = false;

class Drawing : public Fl_Widget {
	void draw() 
	{
		int X=0, Y=0, W=w(), H=h();
    
		fl_push_clip(X,Y,W,H);
		fl_color(FL_DARK3);
		fl_rectf(X,Y,W,H);
		fl_push_matrix();

		if(args[9]!=1.0) {
			// Scale
			fl_scale(args[9]);
		}

		if (args[8]) {
			// Rotate
			H = W = 280;
			fl_translate(H/2.0f, H/2.0f); //Translate to center
			fl_rotate(args[8]);
			fl_translate(-W/2.0f, -H/2.0f); // And back to corner
		}

		fl_color(FL_BLACK);
		fl_vertex(args[0],args[1]);
		fl_vertex(args[2],args[3]);
		fl_vertex(args[4],args[5]);
		fl_vertex(args[6],args[7]);
		fl_stroke();

		fl_curve(args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7]);
		
		fl_color(FL_WHITE);
		if(points)	fl_points();
		else		fl_fill_stroke(FL_RED);
	    
		fl_pop_matrix();
		fl_pop_clip();
	}
public:
	Drawing(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H) { }
};

Drawing *d;

void points_cb(Fl_Button *o, void*) 
{
	points = o->value();
	d->redraw();
}

void slider_cb(Fl_Slider *s, long v) 
{
	args[v] = s->value();
	d->redraw();
}

int main(int argc, char** argv) 
{
	//Fl_Double_Window window(300,555, "Curve test");
	Fl_Window window(300,600, "Curve test");
	
	Drawing drawing(10,10,280,280);
	d = &drawing;

	Fl_Group g(0, 300, 300, 300);
	g.layout_spacing(2);

	for (int n = 0; n<10; n++) {
		Fl_Slider* s = new Fl_Value_Slider(name[n], 22, FL_ALIGN_TOP, 50);
		s->align(FL_ALIGN_LEFT);
		s->type(Fl_Slider::HORIZONTAL | Fl_Slider::TICK_ABOVE);
		s->step(1);
		s->value(args[n]);
		s->callback((Fl_Callback1*)slider_cb, n);
		s->minimum(0); s->maximum(280);

		if (n == 8) {
			s->maximum(360);
		} else if (n == 9) {
			s->maximum(2);
			s->step(0.01);
		}
	}
	Fl_Toggle_Button but("points");
	but.callback((Fl_Callback*)points_cb);

	window.end();
	window.resizable(d);
	window.show(argc,argv);
  
	return Fl::run();
}

//
// End of "$Id$".
//
