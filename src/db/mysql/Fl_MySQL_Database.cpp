
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

        case FIELD_TYPE_BLOB:			
            value.set_buffer(NULL,0);			
            break;

		default:
		case FIELD_TYPE_STRING:			
            value.set_string("");            
            break;        
    }
}

Fl_Date_Time timestamp_to_date(const char *date)
{
	short year=0, mon=0, day=0;
	short hour=0, min=0, sec=0;

	int len = strlen(date);

	switch(len) {
		case 14:
			if(sscanf(date, "%04d%02d%02d%02d%02d%02d", &year, &mon, &day, &hour, &min, &sec) != 6) 
				return Fl_Date_Time();
			break;
		case 12:
			if(sscanf(date, "%02d%02d%02d%02d%02d%02d", &year, &mon, &day, &hour, &min, &sec) != 6) 
				return Fl_Date_Time();
			break;
		case 10:
			if(sscanf(date, "%02d%02d%02d%02d%02d", &year, &mon, &day, &hour, &min) != 5) 
				return Fl_Date_Time();
			break;
		case 8:
			if(sscanf(date, "%02d%02d%02d%02d", &year, &mon, &day, &hour) != 4) 
				return Fl_Date_Time();
			break;
		case 6:
			if(sscanf(date, "%02d%02d%02d", &year, &mon, &day) != 3) 
				return Fl_Date_Time();
			break;
		case 4:
			if(sscanf(date, "%02d%02d", &year, &mon) != 2) 
				return Fl_Date_Time();
			break;
		case 2:
			if(sscanf(date, "%02d", &year) != 1) 
				return Fl_Date_Time();
			break;
	}

	if(year < 100) {
		if(year<40)		year += 2000;
		else			year += 1900;
	}
	
	double encoded_date, encoded_time;
	Fl_Date_Time::encode_date(encoded_date, year, mon, day);
	Fl_Date_Time::encode_time(encoded_time, hour, min, sec);

	return Fl_Date_Time(encoded_date + encoded_time);
}

Fl_Date_Time str_to_date(const char *date, short col_type)
{
	short year=0, mon=0, day=0;
	short hour=0, min=0, sec=0;

	switch(col_type) {
	    case FIELD_TYPE_TIMESTAMP:
			return timestamp_to_date(date);

		case FIELD_TYPE_DATETIME:
			if(sscanf(date, "%04d-%02d-%02d %02d:%02d:%02d", &year, &mon, &day, &hour, &min, &sec) != 6) 
				return Fl_Date_Time();
			break;

		case FIELD_TYPE_DATE:
			if(sscanf(date, "%04d-%02d-%02d", &year, &mon, &day) != 3) 
				return Fl_Date_Time();
			break;

		case FIELD_TYPE_TIME:
			if(sscanf(date, "%02d:%02d:%02d", &hour, &min, &sec) != 3) 
				return Fl_Date_Time();
			break;

		case FIELD_TYPE_YEAR:
			year = strtol(date, 0, 10);
			break;

		default:
			return Fl_Date_Time();
	}
	
	double encoded_date, encoded_time;
	Fl_Date_Time::encode_date(encoded_date, year, mon, day);
	Fl_Date_Time::encode_time(encoded_time, hour, min, sec);

	return Fl_Date_Time(encoded_date + encoded_time);
}

// MySQL retrieves and displays DATETIME values in 'YYYY-MM-DD HH:MM:SS' format.
// The supported range is '1000-01-01 00:00:00' to '9999-12-31 23:59:59'. 
Fl_String date_to_string(Fl_Date_Time date)
{
	short year, mon, day;
	short hour, min, sec;
	short ms;

	Fl_Date_Time::decode_date((double)date, year, mon, day);
	Fl_Date_Time::decode_time((double)date, hour, min, sec, ms);

	char tmp[32];
	sprintf(tmp, "%04d-%02d-%02d %02d:%02d:%02d", 
		year, mon, day,
		hour, min, sec);

	return Fl_String(tmp);
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
	while (m_queryList.count()) {
		Fl_Query *q = (Fl_Query *)m_queryList[0];
        q->database(NULL);
    }    
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

	query_handle(query, res);
    query_active(query, true);

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
    unsigned fieldCount = fields.count();
    if(!fieldCount) {
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
		
		case VAR_DATETIME:
			value.set_date(str_to_date(row[column], field->col_type));
			break;
		
		case VAR_BUFFER:
			value.set_buffer(row[column], lengths[column]);
			((char*)value.data())[lengths[column]] = '\0';
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
	if(!query_active(query)) return;

	MYSQL_RES *res = (MYSQL_RES *)query_handle(query);
	if(res) mysql_free_result(res);		
	
    query_active(query, false);
    query_eof(query, true);
	query_handle(query, 0);

    query_fields(query).clear();    
}

void Fl_MySQL_Database::bind_parameters(Fl_Query *query)
{

}

Fl_String get_value(const char *key, const Fl_String &buf)
{
	int pos = buf.pos(key);
	if(pos==-1) return Fl_String::null_object;
	int pos2 = buf.pos('=', pos);
	pos2++;
	int pos3 = buf.pos(';', pos2);
	if(pos3==-1) pos3 = buf.length();

	return buf.sub_str(pos2, pos3-pos2);
}

void Fl_MySQL_Database::open_connection()
{
	const Fl_String &buf = this->m_connString;

	// Check parameters
	if(!buf.length())
		fl_throw("Can't connect: connection string is empty");

	// If we are  already connected, disconnect
	if(m_connection) close_connection();

	m_connection = mysql_init(m_connection);
	if(!m_connection) {
		fl_throw(mysql_error(m_connection));
	}
	
	Fl_String host	= get_value("HOST", buf);
	Fl_String user	= get_value("UID", buf);
	Fl_String pass	= get_value("PWD", buf);
	Fl_String db	= get_value("DB", buf);
	int port		= get_value("PORT", buf).to_int();

	if(host.empty()) host = "localhost";

	if(!mysql_real_connect(m_connection, 
		host.c_str(), 
		user.empty()	? NULL : user.c_str(), 
		pass.empty()	? NULL : pass.c_str(), 
		db.empty()		? NULL : db.c_str(), 
		port, 
		0, //unix_socket, 
		0  //client_flag
		))
	{
		fl_throw(mysql_error(m_connection));
	}
}

void Fl_MySQL_Database::close_connection()
{
	if(m_connection) {
		mysql_close(m_connection);
		m_connection = 0;
	}
}

void Fl_MySQL_Database::parse_parameters(Fl_Query *query, Fl_String &real_sql)
{
	const Fl_String &sql = query->sql();
	const Fl_Params &params = query->params();

	int param_num = 0;
	for(int n=0; n<sql.length(); n++) {
		if(sql[n] == '?') {
			Fl_String param;
			get_param(params, param_num++, param);
			real_sql += param;
		} else
			real_sql += sql[n];
	}
}

static Fl_Param *find_param(const Fl_Params &params, unsigned param_num)
{
	Fl_Param *param = 0;
    for(unsigned i = 0; i < params.count(); i++) {
        Fl_Param *param = &params[i];
        for (unsigned j = 0; j < param->bind_count(); j++) {
			if(param->bind_index(j) == param_num)
				return param;
		}
	}
	return 0;
}

void Fl_MySQL_Database::get_param(const Fl_Params &params, unsigned param_num, Fl_String &ret)
{
	Fl_Param *param = find_param(params, param_num);
	if(!param) {
		fl_throw("Parameter at index (" + Fl_String(param_num) + ") not found.");
	}
	switch(param->type()) 
	{
	case VAR_INT:
		ret = Fl_String(param->get_int());
		break;

	case VAR_FLOAT: {
		char tmp[32];
		sprintf(tmp, "%g", param->get_float());
		ret = tmp;
		}
		break;		
		
	case VAR_DATETIME:
		ret = '\'';
		ret += date_to_string(param->get_date());
		ret += '\'';
		break;
		
	case VAR_BUFFER: {
		ret = '\'';

		char *to = (char*)malloc((param->size()*2+1) * sizeof(char));
		unsigned long to_len = mysql_real_escape_string(m_connection, to, (const char *)param->get_buffer(), param->size()); 
		ret.append(to, to_len);
		free((char*)to);

		ret += '\'';
		}
		break;

	case VAR_STRING:			
	case VAR_TEXT:
	default:
		ret = '\'';

		char *to = (char*)malloc((param->size()*2+1) * sizeof(char));
		unsigned long to_len = mysql_real_escape_string(m_connection, to, param->get_string(), param->size()); 
		ret.append(to, to_len);
		free((char*)to);

		ret += '\'';		
		break;
    }
}

