#ifndef _FL_XML_H_
#define _FL_XML_H_

#include <efltk/Fl_Map.h>
#include <efltk/xml/Fl_XmlCtx.h>
#include <efltk/xml/Fl_XmlDoc.h>
#include <efltk/xml/Fl_XmlNode.h>
#include <efltk/xml/Fl_XmlParser.h>
#include <efltk/xml/Fl_XmlTokenizer.h>

//XML parsing error codes enumeration
enum {
    FL_XML_NO_ERROR = 0,
    //unspecified or unknown error
    FL_XML_UNKNOWN,
    //expected an open tag literal '<'
    FL_XMP_OPENTAG_EXPECTED,
    //expected a '<' or cdata
    FL_XML_OPENTAG_CDATA_EXPECTED,
    //expected a '>' closing tag literal
    FL_XML_CLOSETAG_EXPECTED,
    //expected a processing instruction or doctype tag
    FL_XML_PI_DOCTYPE_EXPECTED,
    //expected a tag name after '<' or '</'
    FL_XML_TAGNAME_EXPECTED,
    //starting "--" of comment expected after !
    FL_XML_COMMENT_START_EXPECTED,
    //ending "-->" missing
    FL_XML_COMMENT_END_MISSING,
    //expected a '/' after closing tag literal '<'
    FL_XML_SLASH_EXPECTED,
    //tag name from start and end tag mismatch
    FL_XML_TAGNAME_MISMATCH,
    //expected '=' after attribute name
    FL_XML_EQUAL_EXPECTED,
    //expected value after an '=' in attribute
    FL_XML_VALUE_EXPECTED,
    //requested name not found
    FL_XML_NAME_NOT_FOUND
};

#endif

