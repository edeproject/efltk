#ifndef _FL_XMLPARSER_H_
#define _FL_XMLPARSER_H_

#include "Fl_Xml.h"
#include "Fl_XmlHandler.h"
#include "Fl_XmlTokenizer.h"

class Fl_XmlNode;
class Fl_XmlDoc;

/*
 * The XML parser class.
 * The parser is non-validating parser. It cannot handle external DTD's at all.
 * Internal DTD's are partially handled, i.e. custom entities are parsed, though
 * parameter entities are not supported. 
 * Parser expands entitied during parsing, so entity reference nodes are not supported either.
 * I.e. cdata/attributes stored to node or send to SAX handler, are already expanded.
 */
class Fl_XmlParser
{
	friend class Fl_XmlTokenizer;

public:
	/**
	 * Parse new XML/HTML document from stream. throws Fl_XmlException on error and returns NULL.
	 * Caller is supposed to free returned Fl_XmlDoc with 'delete' operator.
	 * You can set own tokenizer, e.g. which reads data from net.
	 * @param tokenizer, stream for document data to parse.
	 * @param locator for tokenizer. If error occurs, you can get position from here.
	 * @param html_mode, document is parsed in HTML mode, for XML this should be always false.
	 */
	static Fl_XmlDoc *create_dom(Fl_XmlTokenizer &tokenizer, Fl_XmlLocator *locator=0, bool html_mode=false);
	
	/**
	 * Parse new XML/HTML document from stream. throws Fl_XmlException on error and returns NULL.
	 * Caller is supposed to free returned Fl_XmlDoc with 'delete' operator.
	 * @param buffer, pointer to data for parse.
	 * @param buffer_len, length of data on buffer
	 * @param locator for tokenizer. If error occurs, you can get position from here.
	 * @param html_mode, document is parsed in HTML mode, for XML this should be always false.
	 */
	static Fl_XmlDoc *create_dom(const char *buffer, int buffer_len, Fl_XmlLocator *locator=0, bool html_mode=false);
	
	/**
	 * Parse new XML/HTML document from stream. throws Fl_XmlException on error and returns NULL.
	 * Caller is supposed to free returned Fl_XmlDoc with 'delete' operator.
	 * You can set own tokenizer, e.g. which reads data from net.
	 * @param fp, FILE * to parse. fp MUST be opened and closed by caller.
	 * @param locator for tokenizer. If error occurs, you can get position from here.
	 * @param html_mode, document is parsed in HTML mode, for XML this should be always false.
	 */
	static Fl_XmlDoc *create_dom(FILE *fp, Fl_XmlLocator *locator=0, bool html_mode=false);

	/**
	 * Parse XML/HTML document in SAX mode. 
	 * This is good for large XML documents, where keeping nodes in memory
	 * would take too much memory. While parsing document, handler methods are called.
	 * @param handler, SAX handler to use catch events.
	 * @param tokenizer, stream for document data to parse.
	 * @param html_mode, document is parsed in HTML mode, for XML this should be always false.
	 * @see Fl_XmlHandler
	 */
	static bool create_sax(Fl_XmlHandler &handler, Fl_XmlTokenizer &tokenizer, bool html_mode=false);

	/**
	 * Parse XML/HTML document in SAX mode. 
	 * This is good for large XML documents, where keeping nodes in memory
	 * would take too much memory. While parsing document, handler methods are called.
	 * @param handler, SAX handler to use catch events.
	 * @param buffer, pointer to data for parse.
	 * @param buffer_len, length of data on buffer
	 * @param html_mode, document is parsed in HTML mode, for XML this should be always false.
	 * @see Fl_XmlHandler
	 */
	static bool create_sax(Fl_XmlHandler &handler, const char *buffer, int buffer_len, bool html_mode=false);

	/**
	 * Parse XML/HTML document in SAX mode. 
	 * This is good for large XML documents, where keeping nodes in memory
	 * would take too much memory. While parsing document, handler methods are called.
	 * @param handler, SAX handler to use catch events.
	 * @param fp, FILE * to parse. fp MUST be opened and closed by caller.
	 * @param html_mode, document is parsed in HTML mode, for XML this should be always false.
	 * @see Fl_XmlHandler
	 */
	static bool create_sax(Fl_XmlHandler &handler, FILE *fp, bool html_mode=false);

	/**
	 * Sets the SAX event handler. If handler is NULL, SAX events are ignored
	 * and nodes are stored to DOM tree.
     * @param handler, event handler to set
	 */
    void handler(Fl_XmlHandler *handler) { m_eventhandler = handler; }

    /**
	 * Returns current SAX event handler, NULL if none specific.
	 */
    Fl_XmlHandler *handler() const { return m_eventhandler; }

protected:
	/**
	 * Create new parser.
	 * @param tokenizer is used as stream tokenizer.
	 */
    Fl_XmlParser(Fl_XmlTokenizer &tokenizer);

    /** Parse subnodes until end-of-stream */
    bool parse_document(Fl_XmlDoc *doc);

    /** Parse doctype declaration */
    bool parse_doctype(Fl_XmlDocType *doc);

    /** Parse a node and its subnodes */
    bool parse_node(Fl_XmlDoc *doc, Fl_XmlNode *node);

    /** Parse an XML node attributes to attr */ 
    bool parse_attributes(Fl_XmlDoc *doc, Fl_XmlAttributes *attr);

    /** Parse a comment (<!-- -->) */
    bool parse_comment(Fl_XmlNode *node);

    /** Turn HTML mode on/off */
    void html_mode(bool val) { m_html_mode = val; }
	/** Return current mode of parser */
    bool html_mode() const { return m_html_mode; }

private:
    // Stream tokenizer
    Fl_XmlTokenizer &tokenizer;    
    
    // Event handler pointer
    Fl_XmlHandler *m_eventhandler;

	//Needed Html mode parsing.
    bool m_html_mode;	
	bool tag_end;
	int force_ret;
	Fl_String last_block;
	Fl_String parent_name;
};

#endif
