#ifndef XMLTOKENIZER_H_
#define XMLTOKENIZER_H_

#include "../Fl_String.h"
#include "../Fl_String_Stack.h"
#include "../Fl_Export.h"

#include <stdio.h> //For FILE

#define BUF_SIZE 4096

/**
 * Fl_XmlLocator class provides the XML handler with information about 
 * the position in a file. 
 */
class FL_API Fl_XmlLocator
{
	friend class Fl_XmlTokenizer;
public:
	Fl_XmlLocator() { m_line=m_col=1; }
	    
	/**
	 * Returns line number, where error happened.
	 */
	int line() const { return m_line; }
    
	/**
	 * Returns column in line, where error happened.
	 */
    int col() const { return m_col; }

    /**
	 * Returns line in file, where error happened.
	 */
    static Fl_String error_line(const char *filename, const Fl_XmlLocator &locator);

private:
	int m_line, m_col;    
};

/**
 * Base class for tokenizing through XML stream.
 */
class Fl_XmlTokenizer
{
	friend class Fl_XmlParser;
public:
    Fl_XmlTokenizer();
    virtual ~Fl_XmlTokenizer() { }

	/**
	 * Returns current stream locator.
	 */
	Fl_XmlLocator *locator() const { return m_locator; }

	/**
	 * Set current stream locator.
	 * @param locator to set
	 */
	void locator(Fl_XmlLocator *locator) { m_locator = locator; }

protected:
    /**
	 * Derived tokenizers override this function.
	 * Returns true, if END-OF-STREAM
	 */
    virtual bool stream_eos() const = 0;
    
    /**
	 * Derived tokenizers override this function.
	 * Tries to 'length' data from stream to 'buf' buffer.
	 * Returns bytes readed.
	 * @param buf buffer to read
	 * @param length to read from stream to buffer
	 */
    virtual int stream_read(char *buf, int length) = 0;

private:
    bool eos() const { return stream_eos() && read_buf_len<=0; }
    
	// Set to true to ignore parsing whitespaces and new-line characters
    void cdata_mode(bool val) { cdata_mode_ = val; }
    bool cdata_mode() const { return cdata_mode_ || auto_cdata_; } 
	
	// Set to true when parsing prolog
    void prolog_mode(bool val) { prolog_mode_ = val; }
    bool prolog_mode() const { return prolog_mode_; }

	// Set to true when parsing prolog
    void attr_mode(bool val) { attr_mode_ = val; }
    bool attr_mode() const { return attr_mode_; }

	// Set to true when parsing preformatted text
    void pre_mode(bool val) { pre_mode_ = val; }
    bool pre_mode() const { return pre_mode_; }

    // Dereference operator
    const Fl_String &operator*() const { return curtoken; }

    // Next token in stream
    Fl_XmlTokenizer &operator++()    { read_next(); return *this; }
    Fl_XmlTokenizer &operator++(int) { read_next(); return *this; }

    // Puts the token back into the stream
    void put_back(const Fl_String &token) { putback_stack.push(token); }
    void put_back(const char *token) { putback_stack.push(token); }
    void put_back() { put_back(curtoken); }

    // Gets one character from internal buffer
    char read_char();
    // Get next token, stores it to 'curtoken'
    void read_next();

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
    bool is_literal( char c ) const;
    bool is_whitespace( char c ) const;
    bool is_newline( char c ) const;
    bool is_delimiter( char c ) const; // start-/endchar of a string

    // Cdata-mode doesn't care for whitespaces in strings
    // Auto cdata-mode turned on internally, doesnt add new-lines
    bool cdata_mode_, auto_cdata_;
	bool prolog_mode_, attr_mode_;
	bool pre_mode_;

	Fl_XmlLocator *m_locator;
};

/**
 * DefaultTokenizer class.
 * Simple XML tokenizer implementation.
 * Handles FILE and memory buffer tokenizing.
 */
class Fl_XmlDefaultTokenizer : public Fl_XmlTokenizer
{
public:
    /** 
	 * Contructor with inputbuffer 
	 * @param buffer pointer XML data
	 * @param buffer_len length of data
	 */
    Fl_XmlDefaultTokenizer(const char *buffer, long buffer_len);
    
	/** 
	 * Contructor with FILE pointer. fp MUST be opened and closed by user.
	 * @param fp pointer to FILE
	 */
    Fl_XmlDefaultTokenizer(FILE *fp);

    virtual ~Fl_XmlDefaultTokenizer();

protected:
    /** Reads length bytes from stream, removed from stream */
    virtual int stream_read(char *buf, int length);
    /** End of stream? */
    virtual bool stream_eos() const;

private:
    void *io_ctx;
};

//////////////////////////////////

inline bool is_literal(const Fl_String &str, bool cdata=false) {
    if(str.length()!=1) return false;
    switch(str[0]) {
    case '/': case '?': 
	case '=': case '!':
	case '>':
        if(cdata) return false;
    case '<':
        return true;
    }
    return false;
}

inline char literal(const Fl_String &str) { return str[0]; }

#endif
