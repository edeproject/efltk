#ifndef _FL_XMLDOC_H_
#define _FL_XMLDOC_H_

#include "Fl_XmlNode.h"
#include <stdio.h> //For FILE

class Fl_XmlDoc: public Fl_XmlNode
{
    friend class Fl_XmlParser;
public:
    Fl_XmlDoc();
    Fl_XmlDoc(Fl_XmlContext *pctx);
    virtual void clear();

    virtual void add_child(Fl_XmlNode *node, bool prepend=false);
    virtual Fl_XmlNode *add_child(Fl_String name, bool prepend=false);

    //returns a list of processing instruction nodes
    NodeList &pi_list() { return procinstructions_; }

    Fl_String &dtd_type() { return dtds[0]; }
    Fl_String &dtd_location() { return dtds[1]; }
    Fl_String &doc_uri() { return dtds[2]; }

    void dtd_type(Fl_String s) { dtds[0] = s; }
    void dtd_location(Fl_String s) { dtds[1] = s; }
    void dtd_uri(Fl_String s) { dtds[2] = s; }

    Fl_XmlNode *root_node();

    //loads xml node from input stream
    bool load(const char *ptr, int len=0);

    //loads xml node from input file
    bool load(FILE *fp);

    //saves xml document to string
    void save(Fl_String &str);

protected:
    //node list of parsed processing instructions
    NodeList procinstructions_;

    // Dtd's, 0=type, 1=location, 2=uri
    Fl_String dtds[3];
};

#endif

