#include <efltk/net/Fl_IMAP_Connect.h>
#include <stdio.h>

Fl_IMAP_Connect::Fl_IMAP_Connect() {
    m_port = 143;
    m_type = SOCK_STREAM;
    m_protocol = IPPROTO_TCP;
    m_ident = 0;
    m_loggedin = false;
}

Fl_IMAP_Connect::~Fl_IMAP_Connect() {
    close();
}

void Fl_IMAP_Connect::get_response(Fl_String ident) {
    char	readBuffer[255];

    m_response.clear();

    for (;;) {
        read_line(readBuffer,255);
        m_response.append(readBuffer);

        if (readBuffer[0] == '*')
            continue;
        if (strstr(readBuffer,ident.c_str()) == 0)
            break;
        fl_throw("Invalid command tag in the server response");
    }
}

void Fl_IMAP_Connect::command(Fl_String cmd) {
    Fl_String ident;
    ident.printf("A%05i ",m_ident++);
    if (!active())
        fl_throw("Socket isn't open");
    write((cmd + "\n").c_str(),cmd.length()+1);
    get_response(ident);
    for (unsigned i = 0; i < m_response.count(); i++)
        printf(m_response[i].c_str());
}

void Fl_IMAP_Connect::login(Fl_String user,Fl_String password) {
    if (m_loggedin) return;
    open();
    command("LOGIN "+user+" "+password);
    m_loggedin = true;
}

void Fl_IMAP_Connect::logoff() {
    if (!m_loggedin) return;
    command("LOGOUT");
    m_loggedin = false;
}
