#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Button_Group.h>

#include <efltk/Fl_Check_Buttons.h>
#include <efltk/Fl_Radio_Buttons.h>

Fl_Input            *i;
Fl_Button_Group     *cb;
Fl_Box              *bx;

void button_cb(Fl_Widget *b,void *) 
{	
    if (b->label() == "Get Choices")
        i->value(cb->value());
    else  
		cb->value(i->value());
}

void group_cb(Fl_Button_Group *b,void *) 
{	
	cb = b;
}

int main(int argc, char *argv[]) 
{
    Fl_Window w(400, 450, "Button Groups");	
    w.layout_spacing(4);

    Fl_Button_Group  *cbl1	= new Fl_Button_Group(10,20,390,100,"Fl_Button_Group:");
    Fl_Check_Buttons *cbl2	= new Fl_Check_Buttons(10,20,390,100,"Fl_Check_Buttons:");
    Fl_Radio_Buttons *cbl3	= new Fl_Radio_Buttons(10,20,390,100,"Fl_Radio_Buttons:");
    
	Fl_String_List buttons("first,second,third,*", ",");
	cbl1->callback((Fl_Callback*)group_cb); cbl1->buttons(buttons); cbl1->layout_align(FL_ALIGN_TOP);
	cbl2->callback((Fl_Callback*)group_cb); cbl2->buttons(buttons); cbl2->layout_align(FL_ALIGN_TOP);
	cbl3->callback((Fl_Callback*)group_cb); cbl3->buttons(buttons); cbl3->layout_align(FL_ALIGN_TOP);	

	//int W,H; 
	//cbl1->preferred_size(W,H); cbl1->h(H);
	//cbl2->preferred_size(W,H); cbl2->h(H);
	//cbl3->preferred_size(W,H); cbl3->h(H);

        cb = cbl3;

	//Fl_Group main_group(10, 10, 100, 100);		
	//main_group.layout_align(FL_ALIGN_CLIENT);

	//Fl_Box empty1(0,0,0,20); empty1.layout_align(FL_ALIGN_CLIENT);
	//main_group.add(cbl1);

	//Fl_Box empty2(0,0,0,20); empty2.layout_align(FL_ALIGN_TOP);
	//main_group.add(cbl2);

	//Fl_Box empty3(0,0,0,20); empty3.layout_align(FL_ALIGN_TOP);
	//main_group.add(cbl3);
	
	//main_group.end();

	Fl_Group g(0, 250, 400, 50);
	g.layout_align(FL_ALIGN_BOTTOM);
		
		Fl_Input input(100,120,200,24,"Test");		
		i = &input;
		input.layout_align(FL_ALIGN_TOP);

		Fl_Button   btn1(120,160,100,30,"Get Choices");
		btn1.callback(button_cb);
		btn1.layout_align(FL_ALIGN_LEFT);

		Fl_Button   btn2(230,160,100,30,"Set Choices");
		btn2.callback(button_cb);
		btn2.layout_align(FL_ALIGN_LEFT);

	g.end();

    w.end();
	//w.resizable(w);
    w.show(argc,argv);	
    
	return Fl::run();
}
