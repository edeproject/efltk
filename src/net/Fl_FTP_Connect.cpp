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

Fl_String Fl_FTP_Connect::cmd_quit() {
    command("QUIT");
    close();
    return m_commandSocket.response().data();
}

Fl_String Fl_FTP_Connect::cmd_type(char type) {
    Fl_String mode("TYPE I");
    mode[5] = type;
    command(mode);
    return m_commandSocket.response().data();
}

Fl_String Fl_FTP_Connect::cmd_cd(Fl_String dir) {
    command("CWD "+dir);
    return m_commandSocket.response().data();
}

Fl_String Fl_FTP_Connect::cmd_pwd() {
    command("PWD ");
    return m_commandSocket.response().data();
}

void Fl_FTP_Connect::get_list(Fl_String cmd,Fl_String_List& list) {
    Fl_Buffer	buffer(255);
    open_data_port();
    command(cmd);
    int         len;
    list.clear();
    do {
        len = m_dataSocket.read_line(buffer);
        char *p = strchr(buffer.data(),'\r');
        if (p) 
            *p = 0;
        else {
            p = strchr(buffer.data(),'\n');
            if (p) 
                *p = 0;
        }
        if (len > 1)
            list.append(buffer.data());
    } while (len > 1);
    m_dataSocket.close();
    m_commandSocket.get_response();
}

Fl_String_List Fl_FTP_Connect::Fl_FTP_Connect::cmd_list() {
    Fl_String_List	result;
    get_list("LIST",result);
    return result;
}

Fl_String_List Fl_FTP_Connect::cmd_nlst() {
    Fl_String_List	result;
    get_list("NLST",result);
    return result;
}

Fl_String Fl_FTP_Connect::cmd_retr(Fl_String fileName) {
    Fl_Buffer	buffer(2048);
    FILE *outfile = fopen(fileName.c_str(),"w+b");
    if (!outfile)
        fl_throw("Can't open file <" + fileName + "> for writing");
    open_data_port();
    command("RETR " + fileName);
    int len;
    do {
        len = m_dataSocket.read(buffer);
        if (len) {
            int bytes = fwrite(buffer.data(),1,len,outfile);
            if (bytes != len)
                fl_throw("Can't open file <" + fileName + "> for writing");
        }
    } while (len);
    m_dataSocket.close();
    fclose(outfile);
    m_commandSocket.get_response();
}

Fl_String Fl_FTP_Connect::cmd_store(Fl_String fileName) {
    Fl_Buffer	buffer(8192);
    FILE *infile = fopen(fileName.c_str(),"rb");
    if (!infile)
        fl_throw("Can't open file <" + fileName + "> for reading");
    open_data_port();
    command("STOR " + fileName);
    int len, bytes;
    while (!feof(infile)) {
        bytes = fread(buffer.data(),1,8192,infile);
        char *p = buffer.data();
        while (bytes) {
            len = m_dataSocket.write(p,bytes);
            if (len == 0) {
                fclose(infile);
                m_dataSocket.close();
                fl_throw("Can't send file <" + fileName + "> - transfer interrupted");
            }
            p += len;
            bytes -= len;
        }
        fflush(stdout);
    }
    m_dataSocket.write(NULL,0);
    m_dataSocket.close();
    fclose(infile);
}
