#include <efltk/Fl.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Window.h>

#include <efltk/Fl_Split.h>

int main(int argc, char *argv[])
{
    // First window demonstrates the use of Fl_Split with
    // the new layout style
	Fl_Window *window = new Fl_Window(300,300,"Fl_Split and new style layout");
	Fl_Group *group = new Fl_Group(5,5,290,290);
	window->resizable(group);
	group->layout_align(FL_ALIGN_CLIENT);

	group->begin();

	Fl_ListView   *listView1 = new Fl_ListView("Left",40,FL_ALIGN_LEFT);
	listView1->end();
	listView1->add_column("column 1");
	Fl_Split *split1  = new Fl_Split(listView1);

	Fl_ListView   *listView2 = new Fl_ListView("Right",40,FL_ALIGN_RIGHT);
	listView2->end();
	listView2->add_column("column 1");
	Fl_Split *split2  = new Fl_Split(listView2);

	Fl_ListView   *listView3 = new Fl_ListView("Top",10,FL_ALIGN_TOP);
	listView3->end();
	Fl_Split *split3  = new Fl_Split(listView3);
	listView3->add_column("column 1");

	Fl_ListView   *listView4 = new Fl_ListView("Bottom",40,FL_ALIGN_BOTTOM);
	listView4->end();
	Fl_Split *split4  = new Fl_Split(listView4);
	listView4->add_column("column 1");

	Fl_ListView   *listView5 = new Fl_ListView("Client",40,FL_ALIGN_CLIENT);
	listView5->end();
	listView5->add_column("column 1");

	Fl_ListView   *listView6 = new Fl_ListView("Left\nat\nthe\nend",40,FL_ALIGN_LEFT);
	listView6->end();
	listView6->add_column("column 1");

	group->end();
	window->end();
	window->show();

    // Second window demonstrates the use of Fl_Split with the
    // old style layouting (eg. X Y W H give)
	window = new Fl_Window(300,300,"Fl_Split and old style positioning");
	group = new Fl_Group(5,5,290,290);
	group->layout_align(FL_ALIGN_CLIENT);    

	group->begin();

	Fl_Box *button1 = new Fl_Box(5, 5, 40, 290,"Left");

	Fl_Box *button2 = new Fl_Box(255,5,40,290,"Right");

	Fl_Box *button3 = new Fl_Box(50,5,200,20,"Top");

	Fl_Box *button4 = new Fl_Box(50,255,200,40,"Bottom");

	Fl_Box *button5 = new Fl_Box(50,30,200,220,"Client");

    // Because the list of the neighbouring widgets is made
    // in the constructor, the splitters has to be added at the end
	split3  = new Fl_Split(50,25,200,5);
	split4  = new Fl_Split(50,250,200,5);
    // because split1 and split2 resizes split3 & 4, they must be added later
	split1  = new Fl_Split(45, 5, 5, 290);
	split2  = new Fl_Split(250,5,5,290);

    // In some cases you may add other widgets to your window
    // after Fl_Split. In this case you should call the
    // find_neighbours() method, like this:
    // split1->find_neighbours();

	button1->box(FL_THIN_UP_BOX);
	button2->box(FL_THIN_UP_BOX);
	button3->box(FL_THIN_UP_BOX);
	button4->box(FL_THIN_UP_BOX);
	button5->box(FL_THIN_UP_BOX);

	window->resizable(group);
	group->resizable(button5);

	group->end();
	window->end();
	window->show();


	return Fl::run();
}
