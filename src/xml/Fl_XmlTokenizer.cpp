#include <efltk/xml/Fl_Xml.h>
#include <efltk/xml/Fl_XmlTokenizer.h>

Fl_String Fl_XmlLocator::error_line(const char *filename, const Fl_XmlLocator &locator)
{
    FILE *fp = fopen(filename, "r");
    if(!fp) return "";

	int line = locator.line();
	int col  = locator.col();

    char linebuffer[1024];
    for(int i=0; i<line-1 && !feof(fp);) {
        int c = fgetc(fp);
        if(c=='\n') i++;
    }
    fread(linebuffer, 1, 1024, fp);
    fclose(fp);

    Fl_String line_str(linebuffer);
    if(line_str.pos('\n')>0)
        line_str = line_str.sub_str(0, line_str.pos('\n'));
    
	if(line_str.length()>=79)
        line_str.sub_delete(79, line_str.length()-79);

    line_str += "\n";
    for(int j=2; j<col; j++)
        line_str += "-";
    line_str += "^";

    return line_str;
}

//////////////////////////////

Fl_XmlTokenizer::Fl_XmlTokenizer()
{
	m_locator = 0;

    putback_char = -1;
    cdata_mode_ = auto_cdata_ = false;
	prolog_mode_ = false;
	attr_mode_ = false;
	pre_mode_ = false;

    read_buf_pos = 0;
    read_buf_len = -1;
}

void Fl_XmlTokenizer::fill_buffer()
{
    if(read_buf_pos>=read_buf_len) {
        read_buf_len = stream_read(read_buf, BUF_SIZE);
        read_buf_pos = 0;
    }
}

char Fl_XmlTokenizer::read_char()
{
	if(locator()) locator()->m_col++;
    read_buf_pos++;
    fill_buffer();
    return read_buf[read_buf_pos];
}

void Fl_XmlTokenizer::read_next()
{	
    if(!putback_stack.empty()) {
        curtoken = putback_stack.pop();		
        return;
    }

    bool ws_added = false;
    write_buf_pos = 0;
    curtoken.clear();

    char c;
    while(!eos())
    {		
        if(write_buf_pos>=BUF_SIZE) {
            // Flush buffer!
            curtoken.append(write_buf, write_buf_pos);
            write_buf_pos = 0;
        }

        if(putback_char == -1) {
            c = read_char();	            
        } else {
            c = putback_char;
            putback_char = -1;            
        }

		if(is_newline(c)) {
			if(locator()) locator()->m_line++;
			if(locator()) locator()->m_col = 1;
		}

        // Is it a literal?
        if(is_literal(c)) {
            if(!cdata_mode_) auto_cdata_ = false;
            if(write_buf_pos==0) {
                curtoken = c;
                if(c=='>')
                    if(!cdata_mode_) auto_cdata_ = true;
                return;
            }					
            putback_char = c;            
            break;
        }

        if(cdata_mode_ || (pre_mode() && cdata_mode())) {
            // Fixed CDATA, comments and preformatted text.
            // Add straight to write buffer
            write_buf[write_buf_pos++] = c;
            continue;
        }

        // String delimiter ("/') and in attribute mode?
        if(is_delimiter(c) && attr_mode()) 
		{
            write_buf_pos = 0;
            char delim = c;
			c = read_char();

			while(c!=delim) {
				if(eos()) break;
				write_buf[write_buf_pos++] = c;
				c = read_char();                
            }

            break;
        }

        // Newline char?
        if(is_newline(c)) c=' ';
        
        // Whitespace?
        if(is_whitespace(c)) 
		{
            if(write_buf_pos==0)
				continue;
            else if(!cdata_mode() || attr_mode())
                break;

			if(ws_added)	continue;
			else			ws_added=true;
        }
		else ws_added=false;		

        // Add to write buffer
        write_buf[write_buf_pos++] = c;

        // Do we have an eos?
        if(eos()) break;
	}

    curtoken.append(write_buf, write_buf_pos);
}

// returns if we have a literal char
bool Fl_XmlTokenizer::is_literal( char c ) const
{
    switch(c)
    {
    case '?':
		if(prolog_mode()) return true;
    case '/':		
    case '=':		
    case '!':
        if(attr_mode() || cdata_mode()) return false;
	case '>':		
	case '<':
        return true;
    }

    return false;
}

// returns if we have a white space char
bool Fl_XmlTokenizer::is_whitespace( char c ) const
{
    switch(c)
    {
    case ' ':
    case '\t':
        return true;
    }

    return false;
}

// returns if we have a newline
bool Fl_XmlTokenizer::is_newline( char c ) const
{
    switch(c)
    {
    case '\n':
    case '\r':
        return true;
    }

    return false;
}

// returns if we have a Fl_String delimiter (separating " and ')
bool Fl_XmlTokenizer::is_delimiter( char c ) const
{
    switch(c)
    {
    case '\"':
    case '\'':
        return true;
    }

    return false;
}

//////////////////////////////////

// FOR IO
#include "../core/fl_internal.h"

Fl_XmlDefaultTokenizer::Fl_XmlDefaultTokenizer(const char *inputbuffer, long size)
: Fl_XmlTokenizer()
{
    if(!size) size = strlen(inputbuffer);

    Fl_IO *io = new Fl_IO;
    io->init_io(0, (uint8*)inputbuffer, size);
    io_ctx = io;
}

Fl_XmlDefaultTokenizer::Fl_XmlDefaultTokenizer(FILE *fp)
: Fl_XmlTokenizer()
{
    Fl_IO *io = new Fl_IO;
    io->init_io(fp, 0, 0);
    io_ctx = io;
}

Fl_XmlDefaultTokenizer::~Fl_XmlDefaultTokenizer()
{
    delete (Fl_IO*)io_ctx;
}

bool Fl_XmlDefaultTokenizer::stream_eos() const
{
    return ((Fl_IO*)io_ctx)->eos();
}

int Fl_XmlDefaultTokenizer::stream_read(char *buf, int length)
{
    if(!stream_eos()) {
        int readed = ((Fl_IO*)io_ctx)->read(buf, length);
        if(readed>0) return readed;
    }
    return -1;
}

