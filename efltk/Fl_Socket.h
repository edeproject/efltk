#ifndef _FL_SOCKET_H_
#define _FL_SOCKET_H_

#ifndef _WIN32
# include <sys/types.h>
# include <sys/socket.h>
# include <stdio.h>
# include <sys/un.h>
# include <sys/unistd.h>
typedef int SOCKET;
# define INVALID_SOCKET -1
#else
# include <winsock2.h>
#endif

#include <efltk/Fl_String.h>
#include <efltk/Fl_Buffer.h>

class Fl_Socket {
	SOCKET		m_sockfd;
	int			m_domain;
	int			m_type;
	int 	   	m_protocol;
	Fl_String	m_host;
	int			m_port;
	fd_set		inputs,outputs;

protected:
	static int	m_socketCount;
	static bool m_inited;

	static void init();
	static void cleanup();
public:
    // Constructor & destructor
	Fl_Socket(int domain=AF_INET, int type=SOCK_STREAM, int protocol=0);
	~Fl_Socket();

    // Settings
	int  handle() const { return m_sockfd; }

	void host(Fl_String hostName);
	const char *host() const { return m_host; }

	void port(int portNumber);
	int port() const { return m_port; }

    // Connect & disconnect
	void open(Fl_String hostName="", int port=0);
	void close();
	bool active() const { return m_sockfd != INVALID_SOCKET; }

	int  control(int flag, unsigned long *check);
	int  set_option(int level,int option,int  value);
	int  get_option(int level,int option,int& value);

    // Read & write
	int read(char *buffer,int size);
	int read(Fl_Buffer& buffer);
	int write(const char *buffer,int size);
	int write(const Fl_Buffer& buffer);

	bool ready_to_read(int waitmsec);
	bool ready_to_write();
};

#endif
