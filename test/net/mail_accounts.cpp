#include <efltk/Fl_ListView.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Secret_Input.h>
#include <efltk/Fl_Choice.h>
#include <efltk/Fl_Config.h>
#include <efltk/Fl_Return_Button.h>
#include <efltk/fl_ask.h>
#include "mail_accounts.h"

static Fl_Menu_Item serverMode[] = {
  {"IMAP",FL_ALT+'i'},
  {"POP3",FL_ALT+'p'},
  {"SMTP",FL_ALT+'s'},
  {0}
};

Fl_Mail_Accounts *mailAccounts;

static void get_string_ok_cb(Fl_Widget* w, void*) {
  w->window()->set_value();
  w->window()->hide();
}

static void get_string_cancel_cb(Fl_Widget* w, void*) {
    w->window()->hide();
}

int get_string(char *buffer) {
    Fl_Window window(320,75);
    Fl_Input input(60, 10, 250, 25, "Input:");
    input.value(buffer);
    input.when(0);
    Fl_Button cancel(60, 40, 80, 25, "cancel");
    cancel.callback(get_string_cancel_cb);
    Fl_Return_Button ok(150, 40, 80, 25, "OK");
    ok.callback(get_string_ok_cb);
    window.hotspot(&cancel); // you must position modal windows
    window.end();

    if (window.exec()) {
        strcpy(buffer,input.value());
        return 1;
    }
    return 0;
}

void add_account_cb(Fl_Widget *,void *) {
    char buffer[128];
    buffer[0] = 0;
    if (get_string(buffer))
        mailAccounts->add_account(buffer,"");
}

void account_data_change_cb(Fl_Widget *,void *) {
    mailAccounts->account_info_changed();
}

void account_clicked_cb(Fl_Widget *,void *) {
    mailAccounts->account_clicked();
}

void account_delete_cb(Fl_Widget *,void *) {
    if (fl_ask("Are you sure you want to delete this account?"))
        mailAccounts->account_remove();
}

Fl_Mail_Accounts::Fl_Mail_Accounts() : Fl_Dialog(500,350,"Mail Accounts") {
    ::mailAccounts = this;
    size_range(450,250);
    new_group("default");

    Fl_Group *group0 = new Fl_Group(100,100,285,100);

    m_serverTypeChoice = new Fl_Choice(80,10,120,22,"Server &Type");
    m_serverTypeChoice->menu(serverMode);
    m_serverTypeChoice->end();
    m_serverTypeChoice->hide();
    m_serverTypeChoice->callback(account_data_change_cb);

    m_serverNameInput = new Fl_Input(80,40,200,22,"&Server");
    m_serverNameInput->callback(account_data_change_cb);
    m_serverNameInput->hide();

    m_userNameInput = new Fl_Input(80,70,200,22,"&User Name");
    m_userNameInput->callback(account_data_change_cb);
    m_userNameInput->hide();

    m_passwordInput = new Fl_Secret_Input(80,100,200,22,"&Password");
    m_passwordInput->callback(account_data_change_cb);
    m_passwordInput->hide();

    group0->layout_align(FL_ALIGN_CLIENT);

    group0->end();
    group0->layout_align(FL_ALIGN_RIGHT);

    Fl_Group *group1 = new Fl_Group(10,10,150,100);
    group1->layout_align(FL_ALIGN_CLIENT);
    group1->color(FL_BLUE);

    m_accountListView = new Fl_ListView(10,10,150,100);
    m_accountListView->add_column("type",40);
    m_accountListView->add_column("account",200);
    m_accountListView->layout_align(FL_ALIGN_CLIENT);
    m_accountListView->callback(account_clicked_cb);

    Fl_Group *group2 = new Fl_Group(10,10,150,20);
    group2->layout_align(FL_ALIGN_BOTTOM);
    group1->color(FL_RED);

    Fl_Button *addButton = new Fl_Button(0,0,50,20,"New");
    addButton->layout_align(FL_ALIGN_LEFT);
    addButton->callback(add_account_cb);

    Fl_Button *editButton = new Fl_Button(0,0,50,20,"Edit");
    editButton->layout_align(FL_ALIGN_LEFT);

    Fl_Button *deleteButton = new Fl_Button(0,0,50,20,"Delete");
    deleteButton->layout_align(FL_ALIGN_LEFT);
    deleteButton->callback(account_delete_cb);

    group2->end();
    group1->end();

    end();
    resizable(this);
    buttons(FL_DLG_OK|FL_DLG_CANCEL|FL_DLG_HELP,FL_DLG_OK);
    relayout();

    m_config = new Fl_Config("EDE","edemail");
}

Fl_Mail_Accounts::~Fl_Mail_Accounts() {
    delete m_config;
}

bool Fl_Mail_Accounts::exec() {
    fl_try {
        m_config->clear();
        m_config->read_file();
        unsigned accountNumber = m_config->sections.count();
        for (unsigned account = 0; account < accountNumber; account++) {
            Section *section = (Section *)m_config->sections[account];
            if (section->name.pos("Account:") == 0) {
                m_config->set_section(section);
                Fl_String accountName,accountType,server,user,password;
                accountName = section->name.sub_str(8,32);
                m_config->read("Type",accountType,"IMAP");
                m_config->read("Server",server,"mail");
                m_config->read("User",user,"");
                m_config->read("Password",password,"");
                add_account(accountName,accountType,server,user,password);
            }
        }
    }
    fl_catch(exception) {
        fprintf(stderr,exception.text().c_str());
    }

    int rc = show_modal();
    if (rc != FL_DLG_OK)
        return false;

    fl_try {
        m_config->clear();
        unsigned accountNumber = m_accountListView->children();
        for (unsigned account = 0; account < accountNumber; account++) {
            Fl_ListView_Item *item = m_accountListView->child(account);
            Fl_String accountType = item->label(0);
            Fl_String accountName = item->label(1);
            Fl_String server = item->label(2);
            Fl_String user = item->label(3);
            Fl_String password = item->label(4);

            Section *section = m_config->create_section("Account:"+accountName);
            m_config->set_section(section);
            m_config->write("Type",accountType);
            m_config->write("Server",server);
            m_config->write("User",user);
            m_config->write("Password",password);
        }
        m_config->flush();
    }
    fl_catch(exception2) {
        fprintf(stderr,exception2.text().c_str());
        return false;
    }
    return true;
}

void Fl_Mail_Accounts::add_account(Fl_String accountName,Fl_String accountType,Fl_String server,Fl_String user,Fl_String password) {
    m_accountListView->begin();
    Fl_ListView_Item *item = new Fl_ListView_Item();
    item->columns(5);
    item->label(0,accountType);
    item->label(1,accountName);
    item->label(2,server);
    item->label(3,user);
    item->label(4,password);
    m_accountListView->end();
}

void Fl_Mail_Accounts::account_info_changed() {
    Fl_ListView_Item *item = m_accountListView->item();
    if (!item) return;
    if (Fl::focus() == (Fl_Widget *)item || Fl::focus() == (Fl_Widget *)m_accountListView) return;
    int serverIntType = m_serverTypeChoice->value();
    item->label(0,serverMode[serverIntType].text);
    item->label(2,m_serverNameInput->value());
    item->label(3,m_userNameInput->value());
    item->label(4,m_passwordInput->value());
    item->redraw();
}

void Fl_Mail_Accounts::account_clicked() {
    Fl_ListView_Item *item = m_accountListView->item();
    if (!item) return;
    Fl_String serverModeStr = item->label(0);
    for (int i = 0; serverMode[i].text; i++) {
        if (serverModeStr == serverMode[i].text) {
            m_serverTypeChoice->value(i);
        }
    }
    m_serverNameInput->value(item->label(2));
    m_userNameInput->value(item->label(3));
    m_passwordInput->value(item->label(4));
    m_serverTypeChoice->show();
    m_serverNameInput->show();
    m_userNameInput->show();
    m_passwordInput->show();
    //relayout();
}

void Fl_Mail_Accounts::account_remove() {
    Fl_ListView_Item *item = m_accountListView->item();
    m_accountListView->remove(item);
    m_serverTypeChoice->hide();
    m_serverNameInput->hide();
    m_userNameInput->hide();
    m_passwordInput->hide();
}
