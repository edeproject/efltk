#ifndef _FL_XMLPARSER_H_
#define _FL_XMLPARSER_H_

#include "Fl_Xml.h"
#include "Fl_XmlTokenizer.h"

class Fl_XmlNode;
class Fl_XmlDoc;
class Fl_XmlContext;

//xml parser implementation class
class Fl_XmlParser
{
public:
    Fl_XmlParser(Fl_XmlTokenizer &tok);

    bool parse_doctype( Fl_XmlDoc &doc, Fl_XmlContext *ctxptr);

    //parses the node as the document root
    bool parse_document( Fl_XmlDoc &doc, Fl_XmlContext *ctxptr );

    //parses a node, without processing instructions
    bool parse_node( Fl_XmlNode &node, Fl_XmlContext *ctxptr );

    //parses xml header, such as processing instructions, doctype etc.
    bool parse_header( Fl_XmlDoc &doc, Fl_XmlContext *ctxptr );

    //parses an xml tag attribute list
    bool parse_attributes( AttrMap *attr, Fl_XmlContext *ctxptr );

    //parses a <!-- --> comment
    bool parse_comment( Fl_XmlNode &node, Fl_XmlContext *ctxptr );

protected:
    //stream tokenizer
    Fl_XmlTokenizer &tokenizer;
};

#endif
