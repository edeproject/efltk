
#include <efltk/db/Fl_MySQL_Database.h>

#include <stdio.h>	
#include <stdlib.h>	

Fl_MySQL_Database(const Fl_String connString,bool threadSafe)
: Fl_Database(connString, threadSafe)
{
	m_connection = 0;
}

Fl_MySQL_Database::~Fl_MySQL_Database()
{

}

void Fl_MySQL_Database::allocate_query(Fl_Query *);
{

}

void Fl_MySQL_Database::deallocate_query(Fl_Query *);
{

}

void Fl_MySQL_Database::prepare_query(Fl_Query *);
{

}

void Fl_MySQL_Database::open_query(Fl_Query *);
{

}

void Fl_MySQL_Database::fetch_query(Fl_Query *);
{

}

void Fl_MySQL_Database::close_query(Fl_Query *);
{

}

void Fl_MySQL_Database::bind_parameters(Fl_Query *);
{

}

void Fl_MySQL_Database::open_connection();
{

}

void Fl_MySQL_Database::close_connection();
{

}

unsigned Fl_MySQL_Database::query_count_cols(Fl_Query *query) const;
{

}

void Fl_MySQL_Database::parse_parameters(Fl_Query *query, Fl_String &real_sql);
{

}

void Fl_MySQL_Database::get_param(const Fl_Params &params, unsigned param_num, Fl_String &ret);
{

}
