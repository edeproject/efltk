#include <efltk/net/Fl_FTP_Connect.h>
#include <stdio.h>

Fl_FTP_Connect::Fl_FTP_Connect() 
: m_commandSocket(), m_dataSocket(), m_response(m_commandSocket.response()) {
	m_passive = true;
}

Fl_FTP_Connect::~Fl_FTP_Connect() {
	close();
}

void Fl_FTP_Connect::host(Fl_String hostName,int portNumber) {
	close();
	m_port = portNumber;
	m_host = hostName;
}

void Fl_FTP_Connect::open() {
	m_commandSocket.open(m_host,m_port);
	m_commandSocket.login(m_user,m_password);
	open_data_port();
}

void Fl_FTP_Connect::close() {
	if (!active()) return;
	m_commandSocket.close();
	m_dataSocket.close();
}

void Fl_FTP_Connect::command(Fl_String cmd) {
	if (!active())
		fl_throw("Connection doesn't exist yet");
	m_commandSocket.command(cmd);
}

void Fl_FTP_Connect::open_data_port() {
	union {
		struct sockaddr sa;
		struct sockaddr_in in;
	} sin;
	unsigned l = sizeof(sin);
	unsigned int v[6];
	struct linger lng = { 0, 0 };

	if (m_passive) {
		command("PASV");
		if (m_response.data()[0] != '2')
			fl_throw(m_response.data());

		memset(&sin, 0, l);
		sin.in.sin_family = AF_INET;
		char *cp = strchr(m_response.data(),'(');
		if (cp == NULL)
			fl_throw(m_response.data());
		cp++;
		sscanf(cp,"%u,%u,%u,%u,%u,%u",&v[2],&v[3],&v[4],&v[5],&v[0],&v[1]);
		sin.sa.sa_data[2] = v[2];
		sin.sa.sa_data[3] = v[3];
		sin.sa.sa_data[4] = v[4];
		sin.sa.sa_data[5] = v[5];
		sin.sa.sa_data[0] = v[0];
		sin.sa.sa_data[1] = v[1];
	}
	if (m_passive) {
		m_dataSocket.open_addr(sin.in);
		setsockopt(m_dataSocket.handle(),SOL_SOCKET,SO_LINGER,(char *)&lng,sizeof(lng));
	}
}
