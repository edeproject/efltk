#ifndef XMLTOKENIZER_H_
#define XMLTOKENIZER_H_

#include <stdio.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_String_Stack.h>

#include "Fl_XmlCtx.h"

/*base class for iterating through xmltoken */
class Fl_XmlTokenizer
{
public:
    Fl_XmlTokenizer(Fl_XmlContext *ctx);
    virtual ~Fl_XmlTokenizer() { }

    //set to true to ignore parsing whitespace
    void cdata_mode(bool val) { cdata_mode_ = val; }
    bool  cdata_mode() { return cdata_mode_ || auto_cdata_; }

    //dereference operator
    Fl_String &operator*() { return curtoken; }

    //advances in the xml stream
    Fl_XmlTokenizer &operator++()    { get_next(); return *this; }
    Fl_XmlTokenizer &operator++(int) { get_next(); return *this; }

    //puts the token back into the stream
    void put_back(Fl_String &token) { putback_stack.push(token); }
    void put_back() { putback_stack.push(curtoken); }

    void get_next();

    // End of input stream
    virtual bool eos() = 0;

    // Stream access
    virtual Fl_String peek(int length) = 0;
    virtual Fl_String read(int length) = 0;
    virtual char getchar() = 0;

protected:

    Fl_String curtoken;

    //char which was put back internally
    char putback_char;

    //stack for put_back()'ed tokens
    Fl_String_Stack putback_stack;

    // internally used to recognize chars in the stream
    bool is_literal( char c );
    bool is_whitespace( char c );
    bool is_newline( char c );
    bool is_delimiter( char c ); // start-/endchar of a Fl_String

    //cdata-mode doesn't care for whitespaces in generic strings
    bool cdata_mode_, auto_cdata_;

    Fl_XmlContext *ctxptr;
};

// Iterator through all xmltoken contained in the xml input stream
class Fl_XmlStreamIterator : public Fl_XmlTokenizer
{
public:
    // ctor with inputstream
    Fl_XmlStreamIterator(Fl_XmlContext *ctx, const char *inputbuffer, long size=0);
    // ctor with inputstream
    Fl_XmlStreamIterator(Fl_XmlContext *ctx, FILE *fp);
    virtual ~Fl_XmlStreamIterator();

    bool eos();

    Fl_String peek(int length);
    Fl_String read(int length);
    char getchar();

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