#include <efltk/Fl_Exception.h>
#include <efltk/net/Fl_IMAP_DS.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Secret_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_ProgressBar.h>
#include <efltk/Fl_Config.h>
#include <efltk/Fl_Choice.h>

Fl_Input *server, *user, *password;
Fl_Choice *mailbox;
Fl_ListView *list_view;
Fl_ProgressBar *progress;
Fl_Config *config;

void cb_progress(int total,int pr) {
	progress->range(0,total);
	progress->value(pr);
	Fl::check();
}

void cb_read(Fl_Widget *,void *) {
	Fl_IMAP_Connect		imap_connect;
	Fl_IMAP_DS 				imap_ds;
	Fl_String_List			imap_folders;

	fl_try {
		// Obtain the list of the folders
		imap_connect.host(server->value());
		imap_connect.cmd_login(user->value(),password->value());
		imap_connect.cmd_list("*",true);
		imap_folders = imap_connect.response();
		imap_folders.print();
		imap_connect.cmd_logout();
		//imap_connect.close();

		// Filling the list of messages
		imap_ds.callback(cb_progress);
		imap_ds.host(server->value());
		imap_ds.user(user->value());
		imap_ds.password(password->value());
		imap_ds.folder(mailbox->value());
		list_view->fill(imap_ds);
		config->write("server",server->value());
		config->write("user",user->value());
		config->write("password",password->value());
	}
fl_catch(exception) { 
	puts(exception.text().c_str()); 
}
}

Fl_Menu_Item default_mboxes[] = {
	{ "inbox", 0 },
	{ 0 }
};

int main(int argc,char *argv[]) {
	Fl_Window      window(600,400,"IMAP test");
	Fl_Config		conf("imap_connect.ini");
	Fl_String		conf_value;
	config = &conf;

	Section *sect = config->find_section("Connection");
	if (!sect)
		sect = config->create_section("Connection");
	config->set_section(sect);

	Fl_ListView lview(10,10,480,380);
	lview.layout_align(FL_ALIGN_CLIENT);
	list_view = &lview;

	Fl_Group        group1(10,10,100,23);
	group1.layout_align(FL_ALIGN_TOP);

	Fl_Box          label1(10,10,80,10,"server name");
	label1.layout_align(FL_ALIGN_LEFT);
	label1.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

	Fl_Input        input1(10,10,70,10);
	input1.layout_align(FL_ALIGN_LEFT);
	server = &input1;
	conf.read("server",conf_value,"");
	server->value(conf_value);

	Fl_Box          label2(10,10,40,10,"user");
	label2.layout_align(FL_ALIGN_LEFT);
	label2.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

	Fl_Input        input2(10,10,50,10);
	input2.layout_align(FL_ALIGN_LEFT);
	user = &input2;
	conf.read("user",conf_value,"");
	user->value(conf_value);

	Fl_Box          label3(10,10,60,10,"password");
	label3.layout_align(FL_ALIGN_LEFT);
	label3.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

	Fl_Secret_Input input3(10,10,50,10);
	input3.layout_align(FL_ALIGN_LEFT);
	password = &input3;
	conf.read("password",conf_value,"");
	password->value(conf_value);

	Fl_Box          label4(10,10,60,10,"mailbox");
	label4.layout_align(FL_ALIGN_LEFT);
	label4.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

	Fl_Choice       choice1(10,10,50,10);
	choice1.layout_align(FL_ALIGN_LEFT);
	choice1.menu(default_mboxes);
	choice1.add("GGU",NULL);
	choice1.value(0);
	choice1.end();
	mailbox = &choice1;

	Fl_Button       button1(10,10,50,10,"Connect!");
	button1.layout_align(FL_ALIGN_LEFT);
	button1.callback(cb_read);

	group1.end();

	Fl_Group        group2(10,10,100,18);
	group2.layout_align(FL_ALIGN_BOTTOM);

	Fl_ProgressBar  pbar(10,10,100,10);
	pbar.layout_align(FL_ALIGN_RIGHT);
	progress = &pbar;

	group2.end();


	window.resizable(window);
	window.end();
	window.show();

	Fl::run();
}
