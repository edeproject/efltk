#ifndef XMLTOKENIZER_H_
#define XMLTOKENIZER_H_

#include <stdio.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_String_Stack.h>

#include "Fl_XmlCtx.h"

#define BUF_SIZE 4096

/*
 * Base class for iterating through xml stream.
 * Tokenizes stream to tokens.
 * Used internally only.
 */
class Fl_XmlTokenizer
{
public:
    Fl_XmlTokenizer(Fl_XmlContext *ctx);
    virtual ~Fl_XmlTokenizer() { }

    // Set to true to ignore parsing whitespace and new-line characters
    void cdata_mode(bool val) { cdata_mode_ = val; }
    bool cdata_mode() { return cdata_mode_ || auto_cdata_; }

    // Dereference operator
    Fl_String &operator*() { return curtoken; }

    // Next token in stream
    Fl_XmlTokenizer &operator++()    { get_next(); return *this; }
    Fl_XmlTokenizer &operator++(int) { get_next(); return *this; }

    // Puts the token back into the stream
    void put_back(Fl_String &token) { putback_stack.push(token); }
    void put_back() { putback_stack.push(curtoken); }

    // Get next token, stores it to 'curtoken'
    void get_next();
    bool eos();

protected:
    // End of input stream
    virtual bool _eos() = 0;
    // Read to buffer
    virtual int _read(char *buf, int length) = 0;

    // Gets one character from internal buffer
    char _getchar();

    // Read buffer
    void fill_buffer();
    char read_buf[BUF_SIZE];
    int read_buf_len, read_buf_pos;

    // Write buffer
    char write_buf[BUF_SIZE];
    int write_buf_pos;

    // Current parsed token
    Fl_String curtoken;

    // Char which was put back internally
    char putback_char;

    // Stack for put_back()'ed tokens
    Fl_String_Stack putback_stack;

    // Internally used to recognize chars in the stream
    bool is_literal( char c );
    bool is_whitespace( char c );
    bool is_newline( char c );
    bool is_delimiter( char c ); // start-/endchar of a string

    // Cdata-mode doesn't care for whitespaces in strings
    // Auto cdata-mode turned on internally, doesnt add new-lines
    bool cdata_mode_, auto_cdata_;
    bool end_of_stream;

    // Context pointer
    Fl_XmlContext *ctxptr;
};

/*
 * Simple XML stream implementation.
 * Handles FILE or memory pointer.
 */
class Fl_XmlStreamIterator : public Fl_XmlTokenizer
{
public:
    // Contructor with inputbuffer
    Fl_XmlStreamIterator(Fl_XmlContext *ctx, const char *inputbuffer, long size=0);
    // Contructor with FILE pointer
    Fl_XmlStreamIterator(Fl_XmlContext *ctx, FILE *fp);

    virtual ~Fl_XmlStreamIterator();

protected:
    // Reads length bytes from stream, removed from stream
    int _read(char *buf, int length);
    // End of stream?
    bool _eos();

    void *io_ctx;
};

//////////////////////////////////

inline bool is_literal(Fl_String &str) {
    if(str.length()!=1) return false;
    switch(str[0]) {
    case '?': case '=': case '!':
    case '/': case '<': case '>':
        return true;
    }
    return false;
}

inline char literal(Fl_String &str) { return str[0]; }

#endif
