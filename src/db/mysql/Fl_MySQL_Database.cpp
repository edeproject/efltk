
#include <efltk/db/Fl_MySQL_Database.h>

#include <stdio.h>	
#include <stdlib.h>	

/////////////////////////////////////

/**
 * Driver-specific Fl_Data_Field extension. Contains all the information
 * we can get from the database about the field in 'select' query.
 * Driver TO DO: define native field information
 * (replace m_columnType,m_columnLength,m_columnScale)
 */
class Fl_MySQL_Field : public Fl_Data_Field {
public:
    Fl_MySQL_Field(const char *name, short type);
    short col_type;
};

/**
 * Field ctor
 * Driver TO DO: initialize the column information. Depending on native field type,
 * initialize Fl_Data_Field::value to one of the Fl_Variant types
 */
Fl_MySQL_Field::Fl_MySQL_Field(const char *name, short type) 
: Fl_Data_Field(name) 
{
    col_type = type;
    switch (col_type) 
	{
        case FIELD_TYPE_TINY:
		case FIELD_TYPE_SHORT:
		case FIELD_TYPE_LONG:
		case FIELD_TYPE_INT24:
		case FIELD_TYPE_LONGLONG:
            value.set_int(0);
            break;

        case FIELD_TYPE_DECIMAL:
		case FIELD_TYPE_FLOAT:
		case FIELD_TYPE_DOUBLE:
            value.set_float(0);
            break;

        case FIELD_TYPE_TIMESTAMP:
		case FIELD_TYPE_DATE:
		case FIELD_TYPE_TIME:
		case FIELD_TYPE_DATETIME:
		case FIELD_TYPE_YEAR:
            value.set_date(Fl_Date_Time(0.0));
            break;

		case FIELD_TYPE_NULL:
        case FIELD_TYPE_BLOB:
            value.set_buffer(NULL,0);
            break;

		default:
		case FIELD_TYPE_STRING:
            value.set_string("");
            value.resize_buffer(256);
            break;        
    }
}

Fl_Date_Time str_to_date(const char *date, short col_type)
{
	return Fl_Date_Time();
}

/////////////////////////////////////

/**
 * Constructor
 * Driver TO DO: put here your connection object initialization
 * w/o establishing a connection.
 */
Fl_MySQL_Database::Fl_MySQL_Database(const Fl_String connString,bool threadSafe)
: Fl_Database(connString, threadSafe)
{
	m_connection = 0;
}

/** 
 * Destructor
 * Driver TO DO: cleanup. close() and close_connection() are MUST.
 */
Fl_MySQL_Database::~Fl_MySQL_Database()
{
    close();
    close_connection();
}

void Fl_MySQL_Database::allocate_query(Fl_Query *query)
{

}

void Fl_MySQL_Database::deallocate_query(Fl_Query *query)
{

}

void Fl_MySQL_Database::prepare_query(Fl_Query *query)
{

}

/**
 * Execute query and fetch results, if any
 */
void Fl_MySQL_Database::open_query(Fl_Query *query)
{
	// Open the database if necessary
    if (!active()) open();

    if (query->active())
        fl_throw("Query is already opened");

	Fl_String real_sql;
	parse_parameters(query, real_sql);	

	if(mysql_real_query(m_connection, real_sql, real_sql.length()) != 0) {        
        fl_throw(mysql_error(m_connection));
    }

	MYSQL_RES *res = mysql_use_result(m_connection);
	if(!res) // mysql_store_result() returned nothing; should it have?
    {
        if(mysql_field_count(m_connection) == 0)
        {
            // query does not return data
            // (it was not a SELECT)
			close_query(query);
			return;
        }
        else // mysql_store_result() should have returned data
        {
            fl_throw(mysql_error(m_connection));
        }
    }

    query_active(query,true);

    Fl_Data_Fields& fields = query_fields(query);
    fields.clear();

	MYSQL_FIELD *field;
	while((field = mysql_fetch_field(res)))
	{
		Fl_Data_Field *data_field = new Fl_MySQL_Field(field->name, field->type);
	    query_fields(query).add(data_field);
	}

    query_eof(query, false);
    fetch_query(query);
}

void Fl_MySQL_Database::fetch_query(Fl_Query *query)
{
	if (!query->active())
        fl_throw("Dataset isn't open");

    Fl_Data_Fields& fields = query_fields(query); 
    unsigned    fieldCount = fields.count();

    if (!fieldCount) {
		return;
	}

    MYSQL_RES *res = (MYSQL_RES *)query_handle(query);

	MYSQL_ROW row = mysql_fetch_row(res);
	if(!row) {
		if(!mysql_error(m_connection)[0]) {
			query_eof(query, true);
            return;		
        } else {
			fl_throw(mysql_error(m_connection));
        }
	}
	unsigned long *lengths = mysql_fetch_lengths(res);

    for (unsigned column = 0; column < fieldCount; column++) 
	{
        Fl_MySQL_Field *field = (Fl_MySQL_Field *)&fields[column];
		Fl_Variant &value = field->value;

        switch(value.type()) 
		{
		case VAR_INT:
			value.set_int(strtol(row[column], 0, 10));
			break;

		case VAR_FLOAT:
			value.set_int(strtod(row[column], 0));
			break;
		
		case VAR_BUFFER:
			value.set_buffer(row[column], lengths[column]);
			break;

		case VAR_DATETIME:
			value.set_date(str_to_date(row[column], field->col_type));
			break;
		
		case VAR_STRING:			
		case VAR_TEXT:
		default:
			value.set_string(row[column], lengths[column]);
			((char*)value.data())[lengths[column]] = '\0';
			break;
        }
	}
}

/**
 * Closes query
 */
void Fl_MySQL_Database::close_query(Fl_Query *query)
{
    query_active(query, false);
    query_eof(query, true);

	MYSQL_RES *res = query_handle(query);
	if(res) mysql_free_result(res);

    Fl_Data_Fields& fields = query_fields(query);
    fields.clear();	
}

void Fl_MySQL_Database::bind_parameters(Fl_Query *query)
{

}

void Fl_MySQL_Database::open_connection()
{

}

void Fl_MySQL_Database::close_connection()
{

}

void Fl_MySQL_Database::parse_parameters(Fl_Query *query, Fl_String &real_sql)
{

}

void Fl_MySQL_Database::get_param(const Fl_Params &params, unsigned param_num, Fl_String &ret)
{

}
