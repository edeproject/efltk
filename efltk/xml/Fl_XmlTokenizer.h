#ifndef XMLTOKENIZER_H_
#define XMLTOKENIZER_H_

#include <stdio.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_String_Stack.h>

#include "Fl_XmlCtx.h"

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

    // End of input stream
    virtual bool eos() = 0;

    // Stream access
    virtual Fl_String peek(int length) = 0;
    virtual Fl_String read(int length) = 0;
    virtual char _getchar() = 0;

protected:

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

    // End of stream?
    bool eos();

    // Peeks stream, not removes from stream
    Fl_String peek(int length);
    // Reads length bytes from stream, removed from stream
    Fl_String read(int length);
    // Gets one character from stream, removed from stream
    char _getchar();

protected:
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
