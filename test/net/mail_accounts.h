#ifndef __MAIL_ACCOUNTS_H__
#define __MAIL_ACCOUNTS_H__

#include <efltk/Fl_Dialog.h>

class Fl_ListView;
class Fl_Choice;
class Fl_Input;
class Fl_Secret_Input;
class Fl_Config;

class Fl_Mail_Accounts : public Fl_Dialog {
    Fl_ListView     *m_accountListView;
    Fl_Choice       *m_serverTypeChoice;
    Fl_Input        *m_serverNameInput;
    Fl_Input        *m_userNameInput;
    Fl_Secret_Input *m_passwordInput;
    Fl_Config       *m_config;
public:
    Fl_Mail_Accounts();
    ~Fl_Mail_Accounts();

    bool exec();
    void add_account(Fl_String accountName,Fl_String accountType="",Fl_String server="",Fl_String user="",Fl_String password="");
    void account_info_changed();
    void account_clicked();
    void account_remove();
};

#endif
