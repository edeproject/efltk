#include <efltk/Fl.h>
#include <efltk/Fl_Socket.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_ProgressBar.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Text_Editor.h>
#include <efltk/Fl_Simple_Html.h>
#include <efltk/fl_ask.h>

#include <string.h>

// Buffer size for read buffer
// The smaller it is, more responsible interface will be.
// Though, you may loose in speed lil bit.
//#define BUFFER_SIZE 16384
//#define BUFFER_SIZE 4096
#define BUFFER_SIZE 1024

Fl_Socket		*sock;
Fl_Input		*input;
Fl_Text_Buffer	*textbuf;
Fl_Text_Editor	*textdisp;

Fl_ProgressBar	*p_bar;
Fl_Box			*p_text;

Fl_String header;
unsigned content_len = 0;

void parse_header(Fl_Buffer &buf)
{
	if(!header.empty()) return;

	char *ptr = buf.data();
	char *header_end = strstr(ptr, "\r\n\r\n");
	if(header_end) {
		header = Fl_String(ptr, header_end-ptr);		
		int hlen = header.length()+4;
		buf.set(buf.data()+hlen, buf.bytes()-hlen);

		printf("HEADER (%s)\n", header.c_str());
		int pos = header.pos("Content-Length");
		if(pos>-1) {
			pos += 15;
			int pos2 = header.pos("\r\n", pos);
			content_len = header.sub_str(pos, pos2-pos).to_int();	
			p_bar->range(0, content_len);
		}		
	}
}

void socket_cb(int fd, void *arg)
{
	Fl_Socket *socket = (Fl_Socket *)arg;

	// Create buffer for reading.
	Fl_Buffer read_buffer;
	read_buffer.check_size(BUFFER_SIZE);

	try {
		// Try to read from socket
		int bytes = socket->read(read_buffer);

		if(bytes<=0) {
			// No more data!
			// We now safely remove FD from eFLTK socket lookup list.
			Fl::remove_fd(socket->handle(), FL_READ);
			// And close it.
			socket->close();
		
		} else {

			parse_header(read_buffer);

			// Got some data!
			// Print out some info:
			printf("Read %i bytes, read_buffer: %i\n", bytes, read_buffer.bytes());
			// Set terminating NULL. This is needed, if you use data as string
			read_buffer.data()[read_buffer.bytes()] = 0; //terminating NULL
			// Append to text display
			textbuf->append(read_buffer.data());
			textdisp->redraw();

			if(content_len>0) {
				p_bar->step(read_buffer.bytes());
				char tmp[128]; sprintf(tmp, "%d of %d Bytes", (int)p_bar->value(), content_len);
				p_text->label(tmp);
			} else {
				p_bar->step(read_buffer.bytes());
				char tmp[128]; sprintf(tmp, "%d of ? Bytes", (int)p_bar->value());
				p_text->label(tmp);
			}			
		}
		p_text->parent()->redraw();

	} catch(Fl_Exception &e) {
		Fl::warning(e.text());
	}
}

void go_callback(Fl_Widget *,void *) 
{    
	header.clear();
	content_len = 0;

	p_bar->range(0,1);
	p_bar->value(0);
	p_text->label("...");

	textbuf->text("");    
	textdisp->redraw();
	
    Fl_String	host_name = input->value();
    Fl_String	page_name = "/index.html";	

	if(!strncmp(host_name, "http://", 7) || !strncmp(host_name, "HTTP://", 7)) {
		host_name.sub_delete(0, 7);
	}

    int pos = host_name.pos("/");
    if (pos > 0) {
        page_name = host_name.sub_str(pos,255);
        host_name.set_length(pos);
    }

    try {
        sock->open(host_name,80);

        char host_header[256];
        int len = sprintf(host_header,"GET %s HTTP/1.0\nHost: %s:80\n\n",page_name.c_str(),host_name.c_str());
        sock->write(host_header, len);

		// Add socket to eFLTK socket lookup list
		Fl::add_fd(sock->handle(), FL_READ, socket_cb, sock);
    }
    catch(Fl_Exception &exception) 
	{
		Fl::warning(exception.text());
		return;
	}
}

int main(int argc,char *argv[]) 
{
	Fl_Socket socket;
	sock = &socket;

    Fl_Window main_window(600,400,"Socket test");

	Fl_Group top_group(0,0,200,25);
	top_group.layout_align(FL_ALIGN_TOP);

	Fl_Box progress_text(0,0,150,25);
	p_text = &progress_text;

	Fl_ProgressBar progress_bar(150,0,50,25);
	p_bar = &progress_bar;

	top_group.resizable(p_bar);
	top_group.store_sizes();
	top_group.end();

	Fl_Text_Buffer buf;
    Fl_Text_Editor	editor(10,10,200,100);

    editor.layout_align(FL_ALIGN_CLIENT);
    editor.buffer(buf);

	textbuf = &buf;
	textdisp = &editor;

    Fl_Group status_line(0,0,200,25);
    status_line.layout_align(FL_ALIGN_BOTTOM);

    Fl_Input url_input(50, 0, 100, 25, "http://");
	url_input.value("www.fltk.org/index.php");

    Fl_Button go_button(150, 0, 50, 25, "Go!");
    go_button.callback(go_callback);
    
	status_line.resizable(url_input);
	status_line.store_sizes();
	status_line.end();

    input = &url_input;

    main_window.end();
    main_window.resizable(main_window);
    main_window.show(argc,argv);

    return Fl::run();
}
