#include <efltk/Fl_String_List.h>
#include <efltk/net/Fl_FTP_Connect.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char *argv[]) {
    Fl_FTP_Connect  ftp;
    Fl_Buffer       result;
    char            server[80];
    char            userName[80];
    char            password[80];
    char            fileName[80];

    fl_try {
        cout << "ftp server: ";
        cin >> server;
        cout << "user: ";
        cin >> userName;
        cout << "password: ";
        cin >> password;
        ftp.host(server);
        ftp.user(userName);
        ftp.password(password);
        ftp.open();
        cout << ftp.response().data();

        ftp.cmd_pwd();
        cout << ftp.response().data();

        cout << endl << "File list in short format:" << endl;
        Fl_String_List files = ftp.cmd_nlst();
        for (unsigned i = 0; i < files.count(); i++)
            cout << files[i].c_str() << endl;

        cout << endl << "File list in long format:" << endl;
        files = ftp.cmd_list();
        for (unsigned j = 0; j < files.count(); j++)
            cout << files[j].c_str() << endl;

        cout << endl << "File to retrieve:";
        cin >> fileName;
        Fl_String fname(fileName);
        fname = fname.trim();
        if (fname.length()) {
            cout << ftp.cmd_type('I').c_str() << endl;
            cout << ftp.cmd_retr(fname).c_str() << endl;
        }

        cout << ftp.cmd_quit().c_str() << endl;
    }
    fl_catch(exception) {
        cout << exception.text().c_str();
    }
    return 0;
}
