#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_String_List.h>
#include <efltk/net/Fl_FTP_DS.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    Fl_FTP_DS       ftp_ds;
    Fl_Buffer      result;
    char           server[80];
    char           userName[80];
    char           password[80];

    Fl_Window   window(600,400,"FTP DS test");
    Fl_ListView lview(10,10,580,380);
    window.end();
    window.show();

    fl_try {
        strcpy(server,"ftp.sunet.se");
        strcpy(userName,"anonymous");
        strcpy(password,"alex@alex.net");
        ftp_ds.host(server);
        ftp_ds.user(userName);
        ftp_ds.password(password);
        lview.fill(ftp_ds);
    }
    fl_catch(exception) {
        puts(exception.text().c_str());
    }

    Fl::run();

    return 0;
}
