#include <efltk/net/Fl_FTP_Connect.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char *argv[]) {
    Fl_FTP_Connect  ftp;
    Fl_Buffer       result;
    char            server[80];
    char            userName[80];
    char            password[80];

    strcpy(server,"ftp");
    strcpy(userName,"tmr04");
    strcpy(password,"tmr04");

    fl_try {
        cout << "ftp server: ";
       //cin >> server;
        cout << "user: ";
       //cin >> userName;
        cout << "password: ";
       //cin >> password;
        ftp.host(server);
        ftp.user(userName);
        ftp.password(password);
        ftp.open();
        cout << ftp.response().data();

        ftp.command("pwd");
        cout << ftp.response().data();

        ftp.command("nlst");
        cout << ftp.response().data();

        ftp.command("quit");
        cout << ftp.response().data();
        ftp.close();
    }
fl_catch(exception) {
    cout << exception.text().c_str();
}
return 0;
}
