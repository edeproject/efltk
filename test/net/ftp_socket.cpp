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

    try {
        strcpy(server,"ftp.sunet.se");
        strcpy(userName,"anonymous");
        strcpy(password,"alex@alex.net");
        ftp.host(server);
        ftp.user(userName);
        ftp.password(password);
        ftp.open();
        const Fl_String_List& response = ftp.response();
        for (unsigned i = 0; i < response.count(); i++)
            cout << response[i].c_str() << endl;

        ftp.cmd_pwd();
        for (unsigned i = 0; i < response.count(); i++)
            cout << response[i].c_str() << endl;

        cout << endl << "File list in short format:" << endl;
        Fl_String_List files;
        ftp.cmd_nlst(files);
        for (unsigned i = 0; i < files.count(); i++)
            cout << files[i].c_str() << endl;

        cout << endl << "File list in long format:" << endl;
        ftp.cmd_list(files);
        for (unsigned j = 0; j < files.count(); j++)
            cout << files[j].c_str() << endl;

        cout << endl << "File to retrieve:";
        cin >> fileName;
        Fl_String fname(fileName);
        fname = fname.trim();
        if (fname.length()) {
            ftp.cmd_type('I');
            for (unsigned i = 0; i < response.count(); i++)
                cout << response[i].c_str() << endl;
            ftp.cmd_retr(fname);
            for (unsigned i = 0; i < response.count(); i++)
                cout << response[i].c_str() << endl;
        }

        ftp.cmd_quit();
        for (unsigned i = 0; i < response.count(); i++)
            cout << response[i].c_str() << endl;
    }
	catch(Fl_Exception &exception) {
		cout << exception.text().c_str();
	}
	return 0;
}
