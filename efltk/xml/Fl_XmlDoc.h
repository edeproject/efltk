#ifndef _FL_XMLDOC_H_
#define _FL_XMLDOC_H_

#include "Fl_XmlNode.h"
#include <stdio.h> //For FILE

/*
 * XML document class.
 * can load whole document from FILE pointer or
 * memory pointer.
 */
class Fl_XmlDoc: public Fl_XmlNode
{
    friend class Fl_XmlParser;
public:
    // Allocates new context automatically
    Fl_XmlDoc();
    // Context passed as argument
    Fl_XmlDoc(Fl_XmlContext *pctx);

    // Clears document
    virtual void clear();

    // Adds child as "root node".
    // If comment type "root node" is not replaced.
    virtual void add_node(Fl_XmlNode *node, bool prepend=false);
    // Adds new root node, returns pointer to it
    virtual Fl_XmlNode *add_node(Fl_String name, bool prepend=false);

    // Returns a list of processing instruction nodes
    NodeList &pi_list() { return procinstructions_; }

    // DTD values of document:
    // Type of document
    Fl_String &dtd_type() { return dtds[0]; }
    void dtd_type(Fl_String s) { dtds[0] = s; }

    // Location of DTD. PUBLIC or SYSTEM
    Fl_String &dtd_location() { return dtds[1]; }
    void dtd_location(Fl_String s) { dtds[1] = s; }

    // URI where dtd file is found
    Fl_String &dtd_uri() { return dtds[2]; }
    void dtd_uri(Fl_String s) { dtds[2] = s; }

    // Returns pointer to root node
    Fl_XmlNode *root_node();

    // Loads XML document from memory pointer.
    bool load(const char *ptr, int len=0);

    // Loads XML document from FILE pointer.
    bool load(FILE *fp);

    // Saves XML document to string 'str'
    void save(Fl_String &str);

protected:
    // Node list of parsed processing instructions
    NodeList procinstructions_;

    // Dtd's, 0=type, 1=location, 2=uri
    Fl_String dtds[3];
};

#endif

