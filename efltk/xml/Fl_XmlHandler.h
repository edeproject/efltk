#ifndef _FL_XMLHANDLER_H_
#define _FL_XMLHANDLER_H_

#include <efltk/Fl_String.h>
#include "Fl_Xml.h"
#include "Fl_XmlNode.h"

//xml parsing event handler (SAX)
class Fl_XmlHandler
{
public:
    Fl_XmlHandler() { }
    virtual ~Fl_XmlHandler() { }

    //called when parsing of an xml document starts
    virtual void start_document() { }

    //called when ended parsing a document
    virtual void end_document() { }

    //called when parsing a processing instruction
    virtual void processing_instruction( Fl_XmlNode &/*pinode*/ ) { }

    //called when start parsing a node
    virtual void start_node( Fl_String &/*nodename*/ ) { }

    //called when an attribute list was parsed
    virtual void parsed_attributes( Fl_String &/*nodename*/, AttrMap &/*attr*/ ) { }

    //called when parsing of a node was finished
    virtual void end_node( Fl_String &/*nodename*/ ) { }

    //called when a cdata section ended
    virtual void cdata( Fl_String &/*cdata*/ ) { }
};

#endif
