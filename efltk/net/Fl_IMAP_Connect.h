#ifndef __FL_IMAP_CONNECT_H__
#define __FL_IMAP_CONNECT_H__

#include <efltk/Fl_Socket.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_String_List.h>

class Fl_IMAP_Connect : public Fl_Socket {
    Fl_String_List	m_response;
    int					m_ident;
    bool					m_loggedin;
protected:
    void get_response(Fl_String ident);
public:
    Fl_IMAP_Connect();
    ~Fl_IMAP_Connect();

    void command(Fl_String cmd);
    void login(Fl_String user,Fl_String password);
    void logoff();

    const Fl_String_List& response() const { return m_response; }
};

#endif
