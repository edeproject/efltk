#include <efltk/Fl_Exception.h>
#include <efltk/net/Fl_IMAP_Connect.h>

int main(int argc,char *argv[]) {
    Fl_IMAP_Connect imap;

    fl_try {
        imap.host("mymailhost");
        imap.cmd_login("tmr04","tmr04");
        imap.response().print();

        imap.cmd_capability();
        imap.response().print();

        puts("Here is the list of mail boxes:");
        imap.cmd_list("*");
        imap.response().print();

        puts("Selecting inbox:");
        int total_messages;
        imap.cmd_select("inbox",total_messages);
        imap.response().print();
        printf("There are %i messages\n",total_messages);

        Fl_Data_Fields  df;
        imap.cmd_fetch_headers(1,df);
        imap.response().print();
        for (unsigned i = 0; i < df.count(); i++) {
            Fl_Data_Field& fld = df.field(i);
            printf("%-15s: %s",fld.name().c_str(),fld.as_string().c_str());
        }

        imap.cmd_logout();
        imap.response().print();
    } 
fl_catch(exception) { puts(exception.text().c_str()); }
}
