#include <efltk/Fl.h>
#include <efltk/Fl_Socket.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Text_Editor.h>
#include <efltk/Fl_Simple_Html.h>
#include <efltk/fl_ask.h>

Fl_Input			*input;
Fl_Simple_Html	*view;
Fl_Text_Buffer	*textbuf;

void go_callback(Fl_Widget *,void *) {
	Fl_Socket	s;
	Fl_Buffer	read_buffer, page_buffer;
	Fl_String	host_name = input->value();
	Fl_String	page_name = "/index.html";

	int pos = host_name.pos("/");
	if (pos > 0) {
		page_name = host_name.sub_str(pos,255);
		host_name.set_length(pos);
	}

	fl_try {
		s.open(host_name,80);

		read_buffer.check_size(32*1024);

		char host_header[256];
		sprintf(host_header,"GET %s HTTP/1.0\nHost: %s:80\n\n",page_name.c_str(),host_name.c_str());
		s.write(host_header,strlen(host_header)+1);

		int bytes = -1;
		int total = 0;
		while (bytes) {
			if (s.ready_to_read(1000)) {
				bytes = s.read(read_buffer);
				total += bytes;
				page_buffer.append(read_buffer);
				//printf("read %i bytes, read_buffer: %i, page_buffer: %i\n",bytes,read_buffer.bytes(),page_buffer.bytes());
				puts("-----------------------------------------------");
				puts(page_buffer.data());
				if (strstr(read_buffer.data(),"</html>"))
					break;
				if (strstr(read_buffer.data(),"</HTML>"))
					break;
			} else {
				puts("Timeout!");
			}
		}
		s.close();
	}
	fl_catch(exception) 
{
	fl_alert(exception.text().c_str());
	return;
}
//view->value(buffer.data());
textbuf->text(page_buffer.data());
}

int main(int argc,char *argv[]) {

	Fl_Window		main_window(600,400,"Socket test");

   /*
   Fl_Simple_Html	html_view(10,10,200,100);
   html_view.layout_align(FL_ALIGN_CLIENT);
   view = &html_view;
   */
	textbuf = new Fl_Text_Buffer;
	Fl_Text_Editor	editor(10,10,200,100);
	editor.layout_align(FL_ALIGN_CLIENT);
	editor.buffer(textbuf);

	Fl_Group			status_line(10,10,200,30);
	status_line.layout_align(FL_ALIGN_BOTTOM);

	Fl_Button		go_button(10,10,50,30,"Go!");
	go_button.callback(go_callback);
	go_button.layout_align(FL_ALIGN_RIGHT);

	Fl_Box			label(10,10,70,30,"http://");
	label.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
	label.layout_align(FL_ALIGN_LEFT);

	Fl_Input			url_input(10,10,70,30);
	url_input.value("www.fltk.org/index.php");
	url_input.layout_align(FL_ALIGN_CLIENT);

	input = &url_input;

	main_window.end();

	main_window.resizable(main_window);

	main_window.show(argc,argv);

	Fl::run();

	return 0;
}
