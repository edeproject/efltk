#ifndef _FL_SOCKET_H_
#define _FL_SOCKET_H_

#ifndef _WIN32
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/un.h>
# include <unistd.h>
typedef int SOCKET;
# define INVALID_SOCKET -1
#else 
# include <winsock2.h>
#endif

#include <efltk/Fl_Exception.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_Buffer.h>

class Fl_Socket_Reader : protected Fl_Buffer {
   int m_socket;
   int m_readOffset;
   int buffered_read(char *dest,int sz,bool read_line);
   int read_available(char *dest,int sz,bool read_line);
public:
   Fl_Socket_Reader(int buffer_size=16384);
   void open(int socket);
   void close() { m_socket = 0; }
   int  read(char *dest,int sz,bool read_line=false);
};

class FL_API Fl_Socket {
protected:
	SOCKET		        m_sockfd;
	int			        m_domain;
	int			        m_type;
	int 	   	        m_protocol;
	Fl_String	        m_host;
	int			        m_port;
	fd_set		        m_inputs,m_outputs;
    Fl_Socket_Reader    m_reader;

protected:
	static int	m_socketCount;
	static bool m_inited;

	static void init();
	static void cleanup();

	char get_char();

public:
   // Constructor & destructor
	Fl_Socket(int domain=AF_INET, int type=SOCK_STREAM, int protocol=0);
	virtual ~Fl_Socket();

	int  handle() const { return m_sockfd; }

	void host(Fl_String hostName);
	const char *host() const { return m_host; }

	void port(int portNumber);
	int port() const { return m_port; }

   // Connect & disconnect
	virtual void open(Fl_String hostName="", int port=0);
	void open_addr(struct sockaddr_in& addr);
	virtual void close();

	bool active() const { return m_sockfd != INVALID_SOCKET; }

   // Settings
	int  control(int flag, unsigned long *check);
	int  set_option(int level,int option,int  value);
	int  get_option(int level,int option,int& value);

    // Read & write
	int read_line(char *buffer,int size);
	int read_line(Fl_Buffer& buffer);
	int read(char *buffer,int size);
	int read(Fl_Buffer& buffer);
	int write(const char *buffer,int size);
	int write(const Fl_Buffer& buffer);

	bool ready_to_read(int waitmsec);
	bool ready_to_write();
};

#endif
