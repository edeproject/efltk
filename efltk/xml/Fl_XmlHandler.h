#ifndef _FL_XMLHANDLER_H_
#define _FL_XMLHANDLER_H_

#include <efltk/Fl_String.h>
#include "Fl_XmlNode.h"

/*
 * XML parser event handler (SAX).
 * re-implement this class and set to
 * context event handler before loading file
 */
class Fl_XmlHandler
{
public:
    Fl_XmlHandler() { }
    virtual ~Fl_XmlHandler() { }

    // Called after header of document parsed
    virtual void start_document(Fl_String &/*dtd_type*/,
                                Fl_String &/*dtd_location*/,
                                Fl_String &/*dtd_uri*/) { }

    // Called when parsing a document finished
    virtual void end_document() { }

    // Called when parsing a processing instruction
    virtual void processing_instruction(Fl_XmlNode &/*pinode*/) { }

    // Called when start parsing a node
    virtual void start_node(Fl_String &/*nodename*/) { }

    // Called when an attribute list was parsed
    virtual void parsed_attributes(Fl_String &/*nodename*/, AttrMap &/*attr*/) { }

    // Called when parsing of a node was finished
    virtual void end_node(Fl_String &/*nodename*/) { }

    // Called when a cdata section ended
    virtual void cdata(Fl_String &/*cdata*/) { }

    // Called when a comment section ended
    virtual void comment(Fl_String &/*comment*/) { }
};

#endif
