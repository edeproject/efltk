#include <efltk/Fl_Exception.h>
#include <efltk/net/Fl_IMAP_DS.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_ProgressBar.h>

Fl_Input *server, *user, *password, *mailbox;
Fl_ListView *list_view;
Fl_ProgressBar *progress;

void cb_progress(int total,int pr) {
    progress->range(0,total);
    progress->value(pr);
    Fl::check();
}

void cb_read(Fl_Widget *,void *) {
    Fl_IMAP_DS          imap;

    fl_try {
        imap.callback(cb_progress);
        imap.host(server->value());
        imap.user(user->value());
        imap.password(password->value());
        imap.folder(mailbox->value());
        list_view->fill(imap);
    }
fl_catch(exception) { puts(exception.text().c_str()); }

}

int main(int argc,char *argv[]) {
    Fl_Window       window(600,400,"IMAP test");

    Fl_ListView lview(10,10,480,380);
    lview.layout_align(FL_ALIGN_CLIENT);
    list_view = &lview;

    Fl_Group        group1(10,10,100,23);
    group1.layout_align(FL_ALIGN_TOP);

    Fl_Box          label1(10,10,80,10,"server name");
    label1.layout_align(FL_ALIGN_LEFT);
    label1.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

    Fl_Input        input1(10,10,70,10);
    input1.layout_align(FL_ALIGN_LEFT);
    server = &input1;

    Fl_Box          label2(10,10,40,10,"user");
    label2.layout_align(FL_ALIGN_LEFT);
    label2.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

    Fl_Input        input2(10,10,50,10);
    input2.layout_align(FL_ALIGN_LEFT);
    user = &input2;

    Fl_Box          label3(10,10,60,10,"password");
    label3.layout_align(FL_ALIGN_LEFT);
    label3.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

    Fl_Input        input3(10,10,50,10);
    input3.layout_align(FL_ALIGN_LEFT);
    password = &input3;

    Fl_Box          label4(10,10,60,10,"mailbox");
    label4.layout_align(FL_ALIGN_LEFT);
    label4.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

    Fl_Input        input4(10,10,50,10);
    input4.layout_align(FL_ALIGN_LEFT);
    input4.value("inbox");
    mailbox = &input4;

    Fl_Button       button1(10,10,50,10,"Read it!");
    button1.layout_align(FL_ALIGN_LEFT);
    button1.callback(cb_read);

    group1.end();

    Fl_Group        group2(10,10,100,18);
    group2.layout_align(FL_ALIGN_BOTTOM);

    Fl_ProgressBar  pbar(10,10,100,10);
    pbar.layout_align(FL_ALIGN_RIGHT);
    progress = &pbar;

    group2.end();


    window.resizable(window);
    window.end();
    window.show();

    Fl::run();
}
