#include <efltk/Fl_Buffer.h>
#include <efltk/Fl_Data_Source.h>
#include <efltk/Fl_Socket.h>
#include <efltk/net/Fl_FTP_Socket.h>

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
	void command(Fl_String cmd);

	const Fl_Buffer& response() const { return m_response; }

	bool active() const { return m_commandSocket.active(); }
};
