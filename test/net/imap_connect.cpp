#include <efltk/Fl_Exception.h>
#include <efltk/net/Fl_IMAP_DS.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Secret_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_ProgressBar.h>
#include <efltk/Fl_Config.h>
#include <efltk/Fl_Choice.h>
#include <efltk/Fl_Browser.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Text_Editor.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Item_Group.h>
#include <efltk/Fl_Menu_Item.h>
#include <efltk/Fl_Menu_Bar.h>

#include "folder_small.xpm"
#include "file_small.xpm"
#include "mail_accounts.h"

Fl_Image *folderSmall = Fl_Image::read_xpm(0, folder_small);
Fl_Image *fileSmall   = Fl_Image::read_xpm(0, file_small);

Fl_Input *server, *user, *password;
Fl_ListView *list_view;
Fl_ProgressBar *progress;
Fl_Config *config;
Fl_Browser *browser;
Fl_Text_Buffer *messageBuffer;

void quit_cb(Fl_Widget *,void *) {
    exit(0);
}

void accounts_cb(Fl_Widget *,void *) {
    Fl_Mail_Accounts    mailAccounts;
    mailAccounts.exec();
}

Fl_Menu_Item menutable[] = {
    {"&File",0,0,0,FL_SUBMENU},
    {"&Quit",   FL_ALT+'q', quit_cb},
    {0},
    {"&Settings",0,0,0,FL_SUBMENU},
    {"&Accounts",FL_SHIFT+'a',accounts_cb},
    {0},
    {0}
};

class Fl_Tree_Item {
    Fl_Ptr_List m_list;
    Fl_String   m_name;
    Fl_Tree_Item *find(const Fl_String& name);
public:
    Fl_Tree_Item(Fl_String name) { m_name = name; }
    ~Fl_Tree_Item() { clear(); }
    void append(Fl_String full_name);
    const Fl_String& operator [] (unsigned i) { return ((Fl_Tree_Item *)m_list[i])->m_name; }
    unsigned count() const { return m_list.count(); }
    const Fl_String& name() const { return m_name; }
    void clear();

    void create_folders(Fl_Group *parent);
};

Fl_Tree_Item *Fl_Tree_Item::find(const Fl_String& the_name) {
    unsigned cnt = m_list.count();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Tree_Item *item = (Fl_Tree_Item *) m_list[i];
        if (item->m_name == the_name)
            return item;
    }
    return 0L;
}

void Fl_Tree_Item::clear() {
    unsigned cnt = m_list.count();
    for (unsigned i = 0; i < cnt; i++) {
        delete (Fl_Tree_Item *) m_list[i];
    }
    m_list.clear();
}

void Fl_Tree_Item::append(Fl_String full_name) {
    int p = full_name.pos("/");
    if (p < 0) {
        m_list.append(new Fl_Tree_Item(full_name));
    } else {
        Fl_String folder_name = full_name.sub_str(0,p);
        Fl_String remains = full_name.sub_str(p+1,1024);
        Fl_Tree_Item *folder = find(folder_name);
        if (!folder) {
            folder = new Fl_Tree_Item(folder_name);
            m_list.append(folder);
        }
        folder->append(remains);
    }
}

static Fl_Group* add_folder(Fl_Group* parent,const Fl_String& name) {
    parent->begin();
    Fl_Item_Group *o = new Fl_Item_Group(name.c_str());
    o->value(1);
    o->image(folderSmall);
    return o;
}

static Fl_Widget* add_item(Fl_Group* parent,const Fl_String& name) {
    parent->begin();
    Fl_Item *o = new Fl_Item(name.c_str());
    o->image(folderSmall);
    return o;
}

void Fl_Tree_Item::create_folders(Fl_Group *parent) {
    unsigned cnt = m_list.count();
    if (!cnt) {
        add_item(parent,m_name);
        return;
    }
    if (m_name != "")
        parent = add_folder(parent,m_name);
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Tree_Item *child = (Fl_Tree_Item *) m_list[i];
        child->create_folders(parent);
    }
}

void cb_progress(int total,int pr) {
    progress->range(0,total);
    progress->value(pr);
    Fl::check();
}

Fl_String currentFolder;

void cb_browser(Fl_Widget *browser,void *) {
    Fl_Widget   *item = ((Fl_Browser*)browser)->item();
    Fl_String   mailbox = item->label();
    // Build the full folder name
    for (;;) {
        item = item->parent();
        if (!item) break;
        if (item == browser) break;
        mailbox = item->label() + Fl_String("/") + mailbox;
    };
    currentFolder = mailbox;
    // Retrive the message list
    Fl_IMAP_DS  imap_ds;
    fl_try {
        // Filling the list of messages
        imap_ds.callback(cb_progress);
        imap_ds.host(server->value());
        imap_ds.user(user->value());
        imap_ds.password(password->value());
        imap_ds.folder(mailbox);
        list_view->fill(imap_ds);
        list_view->redraw();
    }
fl_catch(exception) { puts(exception.text().c_str()); }
}

void cb_lview(Fl_Widget *sender,void *) {
    // Use the mailbox defined by prior click
    // on the folder name in the browser
    Fl_String   mailbox = currentFolder;
    if (!currentFolder.length()) return;

    // Get the active line in the message list,
    // obtain the message id
    Fl_ListView *l = (Fl_ListView *)sender;
    Fl_ListView_Item *i = (Fl_ListView_Item *)l->item();
    if (!i) return;
    int msgid = (int) i->user_data();

    // Retrive the highlighted message
    Fl_IMAP_DS  imap_ds;
    fl_try {
        // Filling the list of messages
        imap_ds.host(server->value());
        imap_ds.user(user->value());
        imap_ds.password(password->value());
        imap_ds.folder(mailbox);
        imap_ds.message(msgid);
        imap_ds.fetch_body(true);
        imap_ds.open();
        Fl_String body = imap_ds["body"].get_string();
        messageBuffer->text(body.c_str());
        imap_ds.close();
    }
fl_catch(exception) { puts(exception.text().c_str()); }
}

void cb_read(Fl_Widget *,void *) {
    Fl_IMAP_Connect     imap_connect;
    Fl_String_List      imap_folders;
    Fl_Tree_Item        tree("");

    browser->clear();

    fl_try {
        // Obtain the list of the folders
        imap_connect.host(server->value());
        imap_connect.cmd_login(user->value(),password->value());
        imap_connect.cmd_list("*",true);
        const Fl_String_List& imap_folders = imap_connect.response();
        for (unsigned i = 0; i < imap_folders.count(); i++) {
            tree.append(imap_folders[i]);
        }
        tree.create_folders(browser);
        browser->end();
        imap_connect.cmd_logout();
        imap_connect.close();
        config->write("server",server->value());
        config->write("user",user->value());
        config->write("password",password->value());
    }
fl_catch(exception) { puts(exception.text().c_str()); }
}

Fl_Menu_Item default_mboxes[] = {
    { "inbox", 0 },
    { 0 }
};

int main(int argc,char *argv[]) {
    Fl_Window   window(600,400,"IMAP test");
    Fl_Config   conf("imap_connect.ini");
    Fl_String   conf_value;
    config = &conf;

    Section *sect = config->find_section("Connection");
    if (!sect)
        sect = config->create_section("Connection");
    config->set_section(sect);

    Fl_Menu_Bar menubar(0,0,20,20);
    menubar.menu(menutable);
    menubar.layout_align(FL_ALIGN_TOP);

    Fl_Group    centerGroup(10,10,150,10);

    Fl_Browser  br(10,10,150,100);
    br.layout_align(FL_ALIGN_LEFT);
    br.indented(1);
    br.callback(cb_browser);
    browser = &br;

    Fl_ListView lview(10,10,480,150);
    lview.layout_align(FL_ALIGN_TOP);
    lview.callback(cb_lview);
    list_view = &lview;

    Fl_Text_Buffer textBuf;

    Fl_Text_Editor messageText(10,10,480,30);
    messageText.layout_align(FL_ALIGN_CLIENT);

    messageText.buffer(&textBuf);

    messageBuffer = &textBuf;

    centerGroup.end();
    centerGroup.layout_align(FL_ALIGN_CLIENT);

    Fl_Group        group1(10,10,100,23);
    group1.layout_align(FL_ALIGN_TOP);

    Fl_Box          label1(10,10,80,10,"server name");
    label1.layout_align(FL_ALIGN_LEFT);
    label1.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

    Fl_Input        input1(10,10,70,10);
    input1.layout_align(FL_ALIGN_LEFT);
    server = &input1;
    conf.read("server",conf_value,"");
    server->value(conf_value);

    Fl_Box          label2(10,10,40,10,"user");
    label2.layout_align(FL_ALIGN_LEFT);
    label2.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

    Fl_Input        input2(10,10,50,10);
    input2.layout_align(FL_ALIGN_LEFT);
    user = &input2;
    conf.read("user",conf_value,"");
    user->value(conf_value);

    Fl_Box          label3(10,10,60,10,"password");
    label3.layout_align(FL_ALIGN_LEFT);
    label3.align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);

    Fl_Secret_Input input3(10,10,50,10);
    input3.layout_align(FL_ALIGN_LEFT);
    password = &input3;
    conf.read("password",conf_value,"");
    password->value(conf_value);

    Fl_Button       button1(10,10,50,10,"Connect!");
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
