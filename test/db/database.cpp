#include <stdio.h>
#include <stdlib.h>

#include <efltk/Fl.h>
#include <efltk/fl_ask.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_ProgressBar.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_ListView.h>

#ifdef ODBC_DRIVER
#include <efltk/db/Fl_ODBC_Database.h>
#define DATABASE Fl_ODBC_Database		
#define CONSTR_TEMPLATE "DSN=odbc_dsn;UID=user;PWD=passwd"
#endif

#ifdef MYSQL_DRIVER
#include <efltk/db/Fl_MySQL_Database.h>
#define DATABASE Fl_MySQL_Database
#define CONSTR_TEMPLATE "HOST=hostname;UID=user;PWD=passwd;DB=db_name"
#endif

//#define USE_THREADS

#ifdef USE_THREADS

# include <efltk/Fl_Thread.h>
Fl_Thread thread;
# define lock() Fl::lock()
# define unlock() Fl::unlock()
# define awake() Fl::awake()

#else

# define lock()
# define unlock()
# define awake()

#endif

Fl_Database *db;
Fl_ListView *results;
Fl_Input *sql_input, *con_str;
Fl_Button *send_btn, *con_btn, *test_btn;
Fl_Query query;

int fetch_function(void* p)
{	
	sql_input->deactivate();
	send_btn->deactivate();

    results->clear();
    results->header()->clear();
	results->redraw();
	awake();	

	try {
		query.sql(sql_input->value());
		query.open();
	
		unsigned columnCount = query.field_count();
		if (!columnCount) return -1;
		lock();
		for (unsigned col = 0; col < columnCount; col++) {
			results->add_column(query.field(col).name());
		}
		unlock();

		results->begin();
		while (!query.eof()) 
		{			
			lock();
			
			Fl_ListView_ItemExt *item = new Fl_ListView_ItemExt();
			item->columns(columnCount);
			for (unsigned col = 0; col < columnCount; col++) {
				item->label(col, query.field(col).as_string());
			}
			query.fetch();

			unlock();
			//awake(); //Keeps screen up-to-date
		}		
		results->end();

		query.close();
   
	} catch(Fl_Exception &e) {
		Fl::warning("Error occured: %s\n", e.text().c_str());
	}

	sql_input->position(0, sql_input->size());//value("");
	sql_input->activate();
	send_btn->activate();

	results->recalc_totalheight();
	results->redraw();
	awake(); // Cause redraw ...

	return 0;
}

void send_cb(Fl_Widget *, void *)
{
#ifdef USE_THREADS
	thread.create(fetch_function);
#else
	fetch_function(0);
#endif
}

void connect_cb(Fl_Widget *, void *)
{	
	try {

	if(!db->active()) {
		db->open(con_str->value());
		con_btn->label("Disconnect");

		con_str->deactivate();
		test_btn->deactivate();
		results->activate();
		sql_input->activate();
		send_btn->activate();
	} else {
		db->connect_string("");
		db->close();
		con_btn->label("Connect");

		con_str->activate();
		test_btn->activate();
		results->deactivate();
		sql_input->deactivate();
		send_btn->deactivate();
	}

	con_btn->parent()->relayout();
	con_btn->parent()->redraw();

	} catch(Fl_Exception &e) {
		Fl::warning("Error occured: %s\n", e.text().c_str());
	}
}

//void printStepName(Fl_String str) 
#define printStepName(str) \
{ \
	bar.step(1); \
\
	Fl_ListView_Item *i = new Fl_ListView_Item(Fl_String((int)bar.value()), str); \
\
	lv.layout(); \
	lv.show_item(i); \
	lv.redraw(); \
	Fl::check(); \
}

void hide_cb(Fl_Widget *, void *d)
{
	((Fl_Window*)d)->hide();
}

void run_test(Fl_Widget *, void *)
{
	Fl_Query query(db);

	Fl_Window win(300, 300, "Running test");
	win.begin();
	
	Fl_ListView lv(0,0,300,280);
	lv.add_column("#", 20);
	lv.add_column("Test steps", 260);
	lv.end();

	Fl_ProgressBar bar(0,280,300,20);
	bar.range(0, 20);

	Fl_Button but(0,280,300,20, "Test completed. Close window.");
	but.callback(hide_cb, &win);
	but.hide();
	
	win.end();
	win.set_modal();
	win.show();

	lv.begin();	

    try
    {		
		printStepName ("Openning the database");
		db->open(con_str->value());
		printStepName ("Ok");

		printStepName ("Creating the temp table");		
		try {			
			//query.sql("CREATE TABLE _test_ (id int, name char(40))");
			query.sql("CREATE TABLE _test_ (id int, name char(40), modified datetime)");
			query.exec ();
			printStepName ("Ok");
		} catch(Fl_Exception &e) {
			Fl_String str("Failed!: " + e.text(true));
			printStepName (str);
		}

		printStepName ("Filling in the temp table");

		query.sql ("INSERT INTO _test_ (id,name,modified) VALUES (:var_id,:var_name,:var_date)");		
		query.param ("var_date") = Fl_Date_Time::Now();		

		for(int a=0;a<10;) {
			query.param ("var_id") = a++;
			query.param ("var_name") = "Alex";
			query.exec ();

			query.param ("var_id") = a++;
			query.param ("var_name") = "Dejan";
			query.exec ();

			query.param ("var_id") = a++;
			query.param ("var_name") = "Mikko";
			query.exec ();		
		}

		printStepName ("Ok");

		printStepName ("Openning the dataset");
		query.sql ("SELECT * FROM _test_");
		query.open ();
		printStepName ("Ok");

		printStepName ("Reading all the rows from the table\n");
		
		Fl_String cols("Row #\t");		
		for (unsigned i = 0; i < query.field_count(); i++) {
			cols += query.field(i).name() + "\t";
		}
		printStepName(cols);

		int rows = 0;
        while (!query.eof ()) {
			Fl_String row("Row ");
			row += Fl_String(rows) + ":\t";            
            for (unsigned i = 0; i < query.field_count(); i++) {
                row += query.field(i).as_string () + "\t";				
            }
			printStepName(row);
            query.fetch ();
            rows++;		
        }
        printStepName ("\nLooks good? Ok");

		printStepName ("Closing the dataset");
		query.close ();
		printStepName ("Ok");

		printStepName ("Removing temp table");
		query.sql ("DROP TABLE _test_");
		query.exec ();
		printStepName ("Ok");
    }
    catch (Fl_Exception &exception) {
		Fl::warning("Error occured!\n%s", exception.text ().c_str ());        
		printStepName (exception.text ());
    }

	try {
		printStepName ("Closing the database");
		db->close ();
		db->connect_string("");
		printStepName ("Ok");
	} catch (Fl_Exception &exception) {
		Fl::warning("Error occured!\n%s", exception.text ().c_str ());        
		printStepName (exception.text ());
    }

	bar.hide();
	but.show();

	while(win.visible()) Fl::wait();	
}

void build_window()
{
	results = new Fl_ListView(0,0,100,100);	
	results->layout_align(FL_ALIGN_CLIENT);
	results->end();	

	Fl_Group *g = new Fl_Group(0,0,100,30);
	g->begin();

		sql_input = new Fl_Input(0,0,60,30);
		sql_input->value("SELECT * FROM _test_");
		g->resizable(sql_input);
	
		send_btn = new Fl_Button(60,0,40,30,"SEND");
		send_btn->callback(send_cb);
	
	g->store_sizes(); //Remember initial sizes for resizing
	g->end();	
	g->layout_align(FL_ALIGN_BOTTOM);

	g = new Fl_Group(0,0,10,56);
	g->box(FL_BORDER_BOX);
	g->begin();

	Fl_Group *g2 = new Fl_Group(0,0,10,g->h()/2);
		
		Fl_Box *empty = new Fl_Box(0,0,90,23);
		empty->layout_align(FL_ALIGN_LEFT);
		
		con_str = new Fl_Input(90,10,300,23,"Connect String:");		
		con_str->value(CONSTR_TEMPLATE);
		con_str->layout_align(FL_ALIGN_CLIENT);

	g2->end();		
	g2->layout_align(FL_ALIGN_CLIENT);
		
	g2 = new Fl_Group(0,0,10,g->h()/2);
	g2->begin();
		
		con_btn = new Fl_Button(0,0,90,20,"Connect");
		con_btn->layout_align(FL_ALIGN_RIGHT);
		con_btn->callback(connect_cb);
		
		test_btn = new Fl_Button(0, 0, 90, 20, "Run test");	
		test_btn->layout_align(FL_ALIGN_RIGHT);
		test_btn->callback(run_test);

	g2->end();	
	g2->layout_spacing(3);
	g2->layout_align(FL_ALIGN_BOTTOM);

	g->end();		
	g->layout_align(FL_ALIGN_TOP);
}

void setup_styles()
{
	Fl_Style *s;
	if((s = Fl_Style::find("Button"))) {
		s->box = FL_THIN_UP_BOX;
		s->highlight_color = fl_lighter(FL_GRAY);
	}
	if((s = Fl_Style::find("Input"))) {
		s->box = FL_THIN_DOWN_BOX;
		s->selection_color = fl_lighter(FL_BLUE);
	}
	if((s = Fl_Style::find("Scrollbar"))) {
		s->button_box = FL_THIN_UP_BOX;
		Fl_Style::scrollbar_width = 14;
	}
	if((s = Fl_Style::find("ListView"))) {
		s->box = FL_THIN_DOWN_BOX;			
		s->selection_color = fl_lighter(FL_BLUE);
	}
	if((s = Fl_Style::find("ListView Header"))) {
		s->button_box = FL_THIN_UP_BOX;
	}	
}

int main (int argc, char *argv[])
{
	lock(); // you must do this before creating any threads!
	
	//setup_styles();

	Fl_Window win(400, 400, "Database test");	
	win.resizable(win);
	win.begin();
	
	build_window();
	
	win.end();	
	win.show();	

	results->deactivate();
	sql_input->deactivate();
	send_btn->deactivate();

	db = new DATABASE("");
	query.database(db);
	
	Fl::run();

	delete db;

    return 0;
}
