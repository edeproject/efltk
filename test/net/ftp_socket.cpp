#include <efltk/net/Fl_FTP_Socket.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	Fl_FTP_Socket	ftp;

	puts("Connecting");
	ftp.open("ftp.tts-sf.com");
	puts("Connected");
	ftp.command("user xxx");

	return 0;
}
