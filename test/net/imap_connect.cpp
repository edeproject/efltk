#include <efltk/net/Fl_IMAP_Connect.h>

int main(int argc,char *argv[]) {
    Fl_IMAP_Connect	imap;

    imap.host("mymailhost");
    imap.login("tmr04","tmr04");
}
