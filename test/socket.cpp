#include <efltk/Fl.h>
#include <efltk/Fl_Socket.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Simple_Html.h>
#include <efltk/fl_ask.h>

Fl_Input			*input;
Fl_Simple_Html	*view;

void go_callback(Fl_Widget *,void *) {
	Fl_Socket	s;
	Fl_Buffer	buffer;
	Fl_String	host_name = input->value();

	fl_try {
		s.open(host_name,80);

		buffer.check_size(128*1024);

		char host_header[256];
		sprintf(host_header,"GET /index.html HTTP/1.1\nHost: %s:80\n\n",host_name.c_str());
		buffer.set(host_header,strlen(host_header)+1);

		s.write(buffer);

		if (s.ready_to_read(1000)) {
			int bytes = s.read(buffer);
			buffer.data()[bytes] = 0;
			printf("Read %i bytes\n\n",bytes);
			puts(buffer.data());
		} else {
			puts("Timeout!");
		}

		s.close();
	}
	fl_catch(exception) 
{
	fl_alert(exception.text().c_str());
	return;
}
view->value(buffer.data());
}

int main(int argc,char *argv[]) {

	Fl_Window		main_window(600,400,"Socket test");

	Fl_Simple_Html	html_view(10,10,200,100);
	html_view.layout_align(FL_ALIGN_CLIENT);
	view = &html_view;

	Fl_Group			status_line(10,10,200,30);
	status_line.layout_align(FL_ALIGN_BOTTOM);

	Fl_Button		go_button(10,10,50,30,"Go!");
	go_button.callback(go_callback);
	go_button.layout_align(FL_ALIGN_RIGHT);

	Fl_Box			label(10,10,70,30,"http://");
	label.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
	label.layout_align(FL_ALIGN_LEFT);

	Fl_Input			url_input(10,10,70,30);
	url_input.value("www.google.com");
	url_input.layout_align(FL_ALIGN_CLIENT);

	input = &url_input;

	html_view.end();
	main_window.end();

	main_window.resizable(main_window);

	main_window.show(argc,argv);

	Fl::run();
}
