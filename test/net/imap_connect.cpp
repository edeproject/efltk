#include <efltk/Fl_Exception.h>
#include <efltk/net/Fl_IMAP_DS.h>

int main(int argc,char *argv[]) {
    Fl_IMAP_DS          imap;

    fl_try {
        imap.host("mymailhost");
        imap.user("tmr04");
        imap.password("tmr04");
        imap.folder("inbox");

        imap.open();

        if (imap.eof()) {
                // print the field names
            for (unsigned i = 0; i < imap.field_count(); i++) {
                Fl_Data_Field& fld = imap.field(i);
                printf("%15s",fld.name().c_str());
            }
        } else {
            puts("Mailbox is empty");
        }

        while (imap.eof()) {
            for (unsigned i = 0; i < imap.field_count(); i++) {
                Fl_Data_Field& fld = imap.field(i);
                printf("%15s",fld.as_string().sub_str(0,14).c_str());
            }
        }

        imap.close();
        /*        
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
        */
    } 
fl_catch(exception) { puts(exception.text().c_str()); }
}
