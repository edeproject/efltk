#include <efltk/xml/Fl_Xml.h>
#include <efltk/xml/Fl_XmlTokenizer.h>

Fl_XmlTokenizer::Fl_XmlTokenizer(Fl_XmlContext *ctx)
{
    ctxptr = ctx;
    putback_char = -1;
    cdata_mode_ = auto_cdata_ = false;
}

void Fl_XmlTokenizer::get_next()
{
    if(!putback_stack.empty()) {
        curtoken = putback_stack.pop();
        return;
    }

    //bool ws_added=false; //Is whitespace added already? HTML?
    bool finished = false;
    Fl_String generic;

    // get next char
    char c;
    do {
        if (putback_char == -1 ) {
            c = getchar();
            ctxptr->pos_++;
        } else {
            c = putback_char;
            putback_char = -1;
            ctxptr->pos_++;
        }

        // do we have an eof?
        if(eos()) {
            if(generic.length()!=0) {
                curtoken = c;
                return;
            } else
                break;
        }

        // is it a literal?
        if(is_literal(c)) {
            if(!cdata_mode_) auto_cdata_ = false;
            if(generic.length()==0) {
                curtoken = c;
                // quick fix for removing set_cdata_mode() functionality
                if(c=='>')
                    if(!cdata_mode_) auto_cdata_ = true;
                return;
            }
            putback_char = c;
            ctxptr->pos_--;
            break;
        }

        if(cdata_mode_) {
            //Fixed CDATA and comments...
            generic += c;
            continue;
        }

        // string delimiter and not in cdata mode?
        if(is_delimiter(c) && !cdata_mode()) {
            generic = c;
            char delim = c;
            do {
                c = getchar();
                ctxptr->pos_++;
                if(eos()) break;
                generic += c;
            } while(c != delim);
            break;
        }

        // Do not add tabs in HTML mode?!
        //if(c=='\t' && cdata_mode /*&& htmlmode_*/) continue;

        // a whitespace?
        if(is_whitespace(c)) {
            if(generic.length()==0)
                continue;
            else if(!cdata_mode()) {
                break;
            }

            //if(ws_added) continue;
            //else ws_added=true;
        }
        //else ws_added=false;

        // a newline char?
        if (is_newline(c)) {
            if(cdata_mode() && generic.length()!=0)
                ;//c = ' '; //HTML mode?!
            else
                continue;
        }
        // add to generic Fl_String
        generic += c;

    } while (!finished);

    //Trim! HTML?!
    if( !cdata_mode() && (generic[0]==' ' || generic[generic.length()-1]==' ') )
        generic = generic.trim();

    // set the generic string
    curtoken = generic;
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

bool Fl_XmlStreamIterator::eos()
{
    return ((Fl_IO*)io_ctx)->eos();
}

Fl_String Fl_XmlStreamIterator::peek(int length)
{
    if(!eos()) {
        int pos = ((Fl_IO*)io_ctx)->tell();
        char *tmp = new char[length];
        int readed = ((Fl_IO*)io_ctx)->read(tmp, length);
        ((Fl_IO*)io_ctx)->seek(pos);
        if(readed==length) {
            tmp[length] = '\0';
            return Fl_String(tmp, length, true);
        } else
            delete []tmp;
    }
    return Fl_String((char)EOF);
}

Fl_String Fl_XmlStreamIterator::read(int length)
{
    if(!eos()) {
        char *tmp = new char[length+1];
        int readed = ((Fl_IO*)io_ctx)->read(tmp, length);
        if(readed==length) {
            tmp[length] = '\0';
            return Fl_String(tmp, length, true);
        } else
            delete []tmp;
    }
    return Fl_String((char)EOF);
}

char Fl_XmlStreamIterator::getchar()
{
    if(!eos()) {
        char c;
        int readed = ((Fl_IO*)io_ctx)->read(&c, 1);
        if(readed==1)
            return c;
    }
    return EOF;
}


