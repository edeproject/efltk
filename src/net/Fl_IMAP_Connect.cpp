#include <efltk/net/Fl_IMAP_Connect.h>
#include <stdio.h>
#include <stdlib.h>

// Implementation is based on
// http://www.course.molina.com.br/RFC/Orig/rfc2060.txt

Fl_IMAP_Connect::Fl_IMAP_Connect() {
   m_port = 143;
   m_ident = 1;
}

Fl_IMAP_Connect::~Fl_IMAP_Connect() {
   close();
}

#define RSP_BLOCK_SIZE 1024
bool Fl_IMAP_Connect::get_response(Fl_String ident) {
   char    readBuffer[RSP_BLOCK_SIZE+1];

   for (;;) {
      int len = read_line(readBuffer,RSP_BLOCK_SIZE);
        Fl_String longLine = readBuffer;
        if (len == RSP_BLOCK_SIZE && readBuffer[RSP_BLOCK_SIZE]!='\n') {
            do {
                len = read_line(readBuffer,RSP_BLOCK_SIZE);
                longLine += readBuffer;
            } while(len == RSP_BLOCK_SIZE);
        }
        m_response.append(longLine);
        if (ident[0] == 0) return true;

        if (longLine[0] == '*')
            continue;
        if (longLine[0] == '+')
            return true;
        if (longLine.pos(ident)==0) {
            int p = ident.length();
            while (longLine[p] == ' ') p++;
            switch (longLine[p]) {
                case 'O': // OK
                    return true;
                case 'N': // NO
                    return false;
                case 'B': // BAD
                    return false;
            }
        }
    }
    return false;
}

const Fl_String Fl_IMAP_Connect::empty_quotes;

static Fl_String quotes(Fl_String st) {
	return "\"" + st + "\"";
}

Fl_String Fl_IMAP_Connect::send_command(Fl_String cmd) {
	Fl_String ident;
	ident.printf("a%03i",m_ident++);
	ident += " ";
	cmd = ident + cmd + "\n";
	if (!active())
		fl_throw("Socket isn't open");
	write(cmd.c_str(),cmd.length());
	return ident;
}

void Fl_IMAP_Connect::command(Fl_String cmd,const Fl_String& arg1,const Fl_String& arg2) {
	if (arg1.length() || &arg1 == &empty_quotes)
		cmd += " " + quotes(arg1);
	if (arg2.length() || &arg2 == &empty_quotes)
		cmd += " " + quotes(arg2);
	m_response.clear();
	Fl_String ident = send_command(cmd);
    //m_response.append(ident + cmd + "\n");
	get_response(ident);
}

void Fl_IMAP_Connect::cmd_login(Fl_String user,Fl_String password) {
    close();
    open();
    m_response.clear();
    get_response("");
    command("login "+user+" "+password);
}
/*
void Fl_IMAP_Connect::cmd_append(Fl_String mail_box,const Fl_String_List& message) {
    Fl_String cmd = "append " + mail_box + " (\\Seen) {310}";
    Fl_String ident = send_command(cmd);
    m_response.clear();
    m_response.append(ident+cmd+"\n");
    get_response("");
    for (unsigned i = 0; i < message.count(); i++) {
        Fl_String row = message[i] + "\n";
        write(row.c_str(),row.length());
    }
    write(NULL,0);
    get_response(ident);
}
*/

void Fl_IMAP_Connect::cmd_select(Fl_String mail_box,int& total_msgs) {
	command("select",mail_box);
	for (unsigned i = 0; i < m_response.count(); i++) {
		Fl_String& st = m_response[i];
		if (st[0] == '*') {
			int p = st.pos("EXISTS");
			if (p > 0) {
				total_msgs = st.sub_str(2,p - 2).to_int();
				break;
			}
		}
	}
}

void Fl_IMAP_Connect::parse_search(Fl_String& result) {
	result = "";
	for (unsigned i = 0; i < m_response.count(); i++) {
		Fl_String& st = m_response[i];
		if (st.pos("* SEARCH") == 0)
			result += st.sub_str(8,st.length());
	}
}

void Fl_IMAP_Connect::cmd_search_all(Fl_String& result) {
	command("search all");
	parse_search(result);
}

void Fl_IMAP_Connect::cmd_search_new(Fl_String& result) {
	command("search unseen");
	parse_search(result);
}

static const char *required_headers[] = {
	"Date",
	"From",
	"Subject",
	"To",
	"CC",
	"Content-Type",
	"Reply-To",
	"Return-Path",
	NULL
};

static void parse_header(const Fl_String& header,Fl_String& header_name,Fl_String& header_value) {
	if (header[0] == ' ') 
		return;

	int p = header.pos(" ");
	if (p < 1) 
		return;
	if (header[p-1] == ':') {
		header_name = header.sub_str(0,p-1);
		header_value = header.sub_str(p+1,header.length());
	}
}

static Fl_Date_Time decode_date(const Fl_String& dt) {
	char    temp[40];
	strcpy(temp,dt.c_str()+5);
    // 1. get the day of the month
	char *p1 = temp;
	char *p2 = strchr(p1,' ');
	if (!p2) return Fl_Date_Time(0.0);
	*p2 = 0;
	int mday = atoi(p1);
    // 2. get the month
	p1 = p2 + 1;
	int month = 1;
	switch (*p1) {
		case 'A':
			if (*(p1+1) == 'p') {
				month = 4; // Apr
				break;
			}
			month = 8; // Aug
			break;
		case 'D':
			month = 12; // Dec
			break;
		case 'F':
			month = 2; // Feb
			break;
		case 'J':   
			if (*(p1+1) == 'a') {
				month = 1; // Jan
				break;
			} 
			if (*(p1+2) == 'n') {
				month = 6; // Jun
				break;
			}
			month = 7; // Jul
			break;
		case 'M':
			if (*(p1+2) == 'r') {
				month = 3; // Mar
				break;
			}
			month = 5; // May
			break;
		case 'N':
			month = 11; // Oct
			break;
		case 'O':
			month = 10; // Oct
			break;
		case 'S':
			month = 9; // Sep
			break;
	}
    // 2. get the year
	p1 += 4;
	p2 = p1 + 4;
	*p2 = 0;
	int year = atoi(p1);
	p1 = p2 + 1;
	p2 = strchr(p1,' ');
	if (p2) *p2 = 0;
	Fl_Date_Time    time(p1);
	Fl_Date_Time    date(year,month,mday);
	return double(date) + double(time);
}

void Fl_IMAP_Connect::parse_message(Fl_Data_Fields& results,bool headers_only) {
	results.clear();
	unsigned i;
	for (i = 0; required_headers[i]; i++) {
		Fl_Data_Field *fld = new Fl_Data_Field(required_headers[i]);
		switch (i) {
			case 0: fld->width = 16; break;
			default: fld->width = 32; break;
		}
		results.add(fld);
	}
    // parse headers
	i = 1;
	for (; i < m_response.count() - 1; i++) {
		Fl_String& st = m_response[i];
		Fl_String header_name, header_value;
		parse_header(st,header_name,header_value);
		if (header_name.length()) {
			int field_index = results.field_index(header_name.c_str());
			if (field_index >= 0) {
				if (header_name == "Date")
					results[field_index].set_date(decode_date(header_value));
				else    
					results[field_index].set_string(header_value);
			}
		}
	}
	if (headers_only) return;
	Fl_String   body;
	for (; i < m_response.count() - 1; i++) {
		body += m_response[i];
	}
	Fl_Data_Field& bodyField = results.add(new Fl_Data_Field("Body"));
	bodyField = body;
}

void Fl_IMAP_Connect::cmd_fetch_headers(int msg_id,Fl_Data_Fields& result) {
	command("FETCH "+Fl_String(msg_id)+" (BODY[HEADER])");
	parse_message(result,true);
}

void Fl_IMAP_Connect::cmd_fetch_message(int msg_id,Fl_Data_Fields& result) {
	command("FETCH "+Fl_String(msg_id)+" (BODY[])");
	parse_message(result,false);
}

static Fl_String strip_framing_quotes(Fl_String st) {
	if (st[0] == '\"')
		return st.sub_str(1,st.length()-2);
	else return st;
}

void Fl_IMAP_Connect::parse_folder_list() {
	Fl_String_List	folder_names;
	Fl_String prefix = "* LIST ";
	for (unsigned i = 0; i < m_response.count(); i++) {
		Fl_String& st = m_response[i];
		if (st.pos(prefix) == 0) {
			// passing the attribute(s)
			const char *p = strstr(st.c_str() + prefix.length(),") ");
			if (!p) continue;
			// passing the reference
			p = strchr(p + 2,' ');
			if (!p) continue;
            p++;
			// Ok, we found the path
			folder_names.append(strip_framing_quotes(p));
		}
	}
	m_response = folder_names;
}

void Fl_IMAP_Connect::cmd_list(Fl_String mail_box_mask,bool decode)  { 
	command("list",empty_quotes,mail_box_mask);
	if (decode)
		parse_folder_list();
}
