#include <efltk/xml/Fl_Xml.h>
#include <efltk/xml/Fl_XmlTokenizer.h>

Fl_XmlTokenizer::Fl_XmlTokenizer(Fl_XmlContext *ctx)
{
    ctxptr = ctx;
    putback_char = -1;
    cdata_mode_ = auto_cdata_ = false;

    read_buf_pos = 0;
    read_buf_len = -1;
    end_of_stream = true;
}

bool Fl_XmlTokenizer::eos()
{
    return end_of_stream;
}

void Fl_XmlTokenizer::fill_buffer()
{
    if(read_buf_pos>=read_buf_len) {
        end_of_stream = _eos();
        read_buf_len = _read(read_buf, BUF_SIZE);
        if(read_buf_len<=0) end_of_stream = true;
        read_buf_pos = 0;
    }
}

char Fl_XmlTokenizer::_getchar()
{
    read_buf_pos++;
    fill_buffer();
    return read_buf[read_buf_pos];
}

void Fl_XmlTokenizer::get_next()
{
    if(!putback_stack.empty()) {
        curtoken = putback_stack.pop();
        return;
    }

    //bool ws_added=false; //Is whitespace added already? HTML?
    write_buf_pos = 0;
    curtoken.clear();

    char c;
    while(true)
    {
        if(write_buf_pos>=BUF_SIZE) {
            // Flush buffer!
            curtoken.append(write_buf, write_buf_pos);
            write_buf_pos = 0;
        }

        if(putback_char == -1) {
            c = _getchar();
            ctxptr->pos_++;
        } else {
            c = putback_char;
            putback_char = -1;
            ctxptr->pos_++;
        }

        // Do we have an eof?
        if(eos()) {
            if(write_buf_pos>0) {
                curtoken = c;
                return;
            } else
                break;
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
            ctxptr->pos_--;
            break;
        }

        if(cdata_mode_) {
            // Fixed CDATA and comments...
            // Add to write buffer
            write_buf[write_buf_pos++] = c;
            continue;
        }

        // String delimiter and not in cdata mode?
        if(is_delimiter(c) && !cdata_mode()) {
            write_buf_pos = 0;
            write_buf[write_buf_pos++] = c;
            char delim = c;
            do {
                c = _getchar();
                ctxptr->pos_++;
                if(eos()) break;
                write_buf[write_buf_pos++] = c;
            } while(c != delim);
            break;
        }

        // Do not add tabs in HTML mode?!
        //if(c=='\t' && cdata_mode /*&& htmlmode_*/) continue;

        // Whitespace?
        if(is_whitespace(c)) {
            if(write_buf_pos==0)
                continue;
            else if(!cdata_mode()) {
                break;
            }
            //if(ws_added) continue;
            //else ws_added=true;
        }
        //else ws_added=false;

        // Newline char?
        if (is_newline(c)) {
            if(cdata_mode() && write_buf_pos>0)
                ;//c = ' '; //HTML mode?!
            else
                continue;
        }

        // Add to write buffer
        write_buf[write_buf_pos++] = c;
    }

    curtoken.append(write_buf, write_buf_pos);

    //Trim! HTML?!
    if( !cdata_mode() && (curtoken[0]==' ' || curtoken[curtoken.length()-1]==' ') )
        curtoken = curtoken.trim();
}

// returns if we have a literal char
bool Fl_XmlTokenizer::is_literal( char c )
{
    switch(c)
    {
    case '?':
    case '=':
    case '!':
    case '/':
        if(cdata_mode())
            return false;
    case '<':
    case '>':
        return true;
    }

    return false;
}

// returns if we have a white space char
bool Fl_XmlTokenizer::is_whitespace( char c )
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
bool Fl_XmlTokenizer::is_newline( char c )
{
    switch(c)
    {
    case '\n':
        ctxptr->line_++;
        ctxptr->pos_ = 1;
    case '\r':
        return true;
    }

    return false;
}

// returns if we have a Fl_String delimiter (separating " and ')
bool Fl_XmlTokenizer::is_delimiter( char c )
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

Fl_XmlStreamIterator::Fl_XmlStreamIterator(Fl_XmlContext *ctx, const char *inputbuffer, long size)
: Fl_XmlTokenizer(ctx)
{
    if(!size) size = strlen(inputbuffer);

    Fl_IO *io = new Fl_IO;
    io->init_io(0, (uint8*)inputbuffer, size);
    io_ctx = io;
}

Fl_XmlStreamIterator::Fl_XmlStreamIterator(Fl_XmlContext *ctx, FILE *fp)
: Fl_XmlTokenizer(ctx)
{
    Fl_IO *io = new Fl_IO;
    io->init_io(fp, 0, 0);
    io_ctx = io;
}

Fl_XmlStreamIterator::~Fl_XmlStreamIterator()
{
    delete (Fl_IO*)io_ctx;
}

bool Fl_XmlStreamIterator::_eos()
{
    return ((Fl_IO*)io_ctx)->eos();
}

int Fl_XmlStreamIterator::_read(char *buf, int length)
{
    if(!eos()) {
        int readed = ((Fl_IO*)io_ctx)->read(buf, length);
        if(readed>0) return readed;
    }
    return -1;
}

