#ifndef __FL_IMAP_CONNECT_H__
#define __FL_IMAP_CONNECT_H__

#include <efltk/Fl_Socket.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_String_List.h>
#include <efltk/Fl_Data_Fields.h>

class Fl_IMAP_Connect : public Fl_Socket {
	Fl_String_List  m_response;
	int             m_ident;
	static const Fl_String  empty_quotes;
protected:
	Fl_String send_command(Fl_String cmd);
	bool get_response(Fl_String ident);
	void parse_search(Fl_String& result);
	void parse_message(Fl_Data_Fields& result,bool headers_only);
	void parse_folder_list();
public:
	Fl_IMAP_Connect();
	~Fl_IMAP_Connect();

	void command(Fl_String cmd,const Fl_String& arg1="",const Fl_String& arg2="");
	const Fl_String_List& response() const          { return m_response; }

    // IMAPv4 commands - any state
	void cmd_capability()                          { command("capability"); }
	void cmd_noop()                                { command("noop"); }
	void cmd_logout()                              { command("logout"); }

    // IMAPv4 commands - not logged in
	void cmd_login(Fl_String user,Fl_String password);

    // IMAPv4 commands - logged in,
    // mailbox-operations
	void cmd_select(Fl_String mail_box,int& total_msgs);
	void cmd_examine(Fl_String mail_box)            { command("examine",mail_box); }
	void cmd_subscribe(Fl_String mail_box)          { command("subscribe",mail_box); }
	void cmd_unsubscribe(Fl_String mail_box)        { command("unsubscribe",mail_box); }
	void cmd_create(Fl_String mail_box)             { command("create",mail_box); }
	void cmd_delete(Fl_String mail_box)             { command("delete",mail_box); }
	void cmd_rename(Fl_String mail_box,Fl_String new_name)  { command("rename ",mail_box,new_name); }
	void cmd_list(Fl_String mail_box_mask,bool decode=false);
    //void cmd_append(Fl_String mail_box,const Fl_String_List& message);

    // IMAPv4 commands - logged in,
    // selected mailbox-operations
	void cmd_close()                                { command("close"); }
	void cmd_expunge()                              { command("expunge"); }
	void cmd_search_all(Fl_String& result);
	void cmd_search_new(Fl_String& result);
	void cmd_fetch_headers(int msg_id,Fl_Data_Fields& result);
	void cmd_fetch_message(int msg_id,Fl_Data_Fields& result);
};

#endif
