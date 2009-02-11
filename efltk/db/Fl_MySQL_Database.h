// Fl_MySQL_Database.h: interface for the Fl_MySQL_Database class.
//////////////////////////////////////////////////////////////////////

#ifndef _FL_MYSQL_DATABASE_H_
#define _FL_MYSQL_DATABASE_H_

#ifdef _WIN32
#include <winsock.h>
#endif

#include <efltk/db/Fl_Database.h>
#include <mysql.h>

class Fl_MySQL_Database : public Fl_Database
{
public:
    Fl_MySQL_Database(const Fl_String connString,bool threadSafe=false);
    virtual ~Fl_MySQL_Database();

    MYSQL *handle() const { return m_connection; }

protected:
    // Operations over query handle
    // These methods should be implemented in actual database class
    virtual void allocate_query(Fl_Query *);
    virtual void deallocate_query(Fl_Query *);
    virtual void prepare_query(Fl_Query *);
    virtual void open_query(Fl_Query *);
    virtual void fetch_query(Fl_Query *);
    virtual void close_query(Fl_Query *);

protected:
    // These methods should be implemented in actual database class
    virtual void open_connection();
    virtual void close_connection();

private:
    void parse_parameters(Fl_Query *query, Fl_String &real_sql);
    void get_param(const Fl_Params &params, unsigned param_num, Fl_String &ret);

    MYSQL *m_connection;
};

#endif // _FL_MYSQL_DATABASE_H_
