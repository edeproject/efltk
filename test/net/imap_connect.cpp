#include <efltk/Fl_Exception.h>
#include <efltk/net/Fl_IMAP_DS.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_ListView.h>

int main(int argc,char *argv[]) {
    Fl_IMAP_DS          imap;

    Fl_Window   window(500,400,"IMAP test");
    Fl_ListView lview(10,10,480,380);
    fl_try {
        imap.host("mymailhost");
        imap.user("tmr04");
        imap.password("tmr04");
        imap.folder("inbox");
        lview.fill(imap);
    }
fl_catch(exception) {
    puts(exception.text().c_str());
}

window.end();
window.show();

Fl::run();
}
