#include <efltk/Fl_String.h>
#include <efltk/Fl_String_List.h>
#include <efltk/Fl_Buffer.h>
#include <efltk/Fl_Data_Source.h>
#include <efltk/Fl_Socket.h>

class Fl_FTP_Socket : public Fl_Socket {
    Fl_Buffer	m_buffer;
public:
    Fl_FTP_Socket();
    ~Fl_FTP_Socket();

   // Connect & disconnect
    virtual void open(Fl_String hostName="", int port=0);

    const Fl_Buffer& response() { return m_buffer; }
    const Fl_Buffer& login(Fl_String user,Fl_String password);
    const Fl_Buffer& command(Fl_String cmd);

    const Fl_Buffer& get_response();
};

class FL_API Fl_FTP_Connect {
protected:
    Fl_FTP_Socket		m_commandSocket;
    Fl_FTP_Socket		m_dataSocket;
    Fl_String			m_user;
    Fl_String			m_password;
    Fl_String			m_host;
    int					m_port;
    const Fl_Buffer&	m_response;
    bool					m_passive;
protected:
    void open_data_port();
    void command(Fl_String cmd);
    void get_list(Fl_String cmd,Fl_String_List& list);
public:
    Fl_FTP_Connect();
    ~Fl_FTP_Connect();

    void passive(bool p) { m_passive = p; }
    bool passive() const { return m_passive; }

    void user(Fl_String u) { m_user = u; }
    Fl_String user() const { return m_user; }

    void password(Fl_String p) { m_password = p; }
    Fl_String password() const { return m_password; }

    void host(Fl_String hostName,int portNumber=21);

    void open();
    void close();

    const Fl_Buffer& response() const { return m_response; }

    bool active() const { return m_commandSocket.active(); }

    // FTP commands
    Fl_String cmd_quit();
    Fl_String cmd_type(char type);
    Fl_String cmd_cd(Fl_String dir);
    Fl_String cmd_pwd();

    Fl_String_List cmd_list();
    Fl_String_List cmd_nlst();

    Fl_String cmd_retr(Fl_String fileName);
    Fl_String cmd_store(Fl_String fileName);
};
