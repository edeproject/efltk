#ifndef _FL_XMLPARSER_H_
#define _FL_XMLPARSER_H_

#include "Fl_Xml.h"
#include "Fl_XmlTokenizer.h"

class Fl_XmlNode;
class Fl_XmlDoc;
class Fl_XmlContext;

/*
 * XML parser class.
 * Used internally only.
 */
class Fl_XmlParser
{
public:
    Fl_XmlParser(Fl_XmlContext *ctx, Fl_XmlTokenizer &tok);

    // Parses DOCTYPE definenations
    bool parse_doctype(Fl_XmlDoc &doc);

    // Parses header, such as processing instructions, doctype etc.
    bool parse_header(Fl_XmlDoc &doc);

    // Parses the node as the document root
    bool parse_document(Fl_XmlDoc &doc);

    // Parses a node, without processing instructions. i.e. normal XML node
	// Return values: 0=failed, 1=success, 2=parsed parent node cdata
    int parse_node(Fl_XmlNode *node);

    // Parses an xml node attributes to list
    bool parse_attributes(AttrMap *attr);

    // Parses a <!-- --> comment
    bool parse_comment(Fl_XmlNode *node);

protected:
    void throw_error(int error);

    // Stream tokenizer
    Fl_XmlTokenizer &tokenizer;
    Fl_XmlContext *ctxptr;
};

#endif
