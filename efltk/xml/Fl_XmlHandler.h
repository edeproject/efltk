#ifndef _FL_XMLHANDLER_H_
#define _FL_XMLHANDLER_H_

#include "Fl_XmlDoc.h"
#include "../Fl_String.h"

/**
 * \defgroup XML eFLTK XML module
 */
/*@{*/

/**
 * XML parser event handler (SAX).
 * re-implement this class and set to
 * context event handler before loading file
 */
class Fl_XmlHandler
{
public:
    Fl_XmlHandler() { }
    virtual ~Fl_XmlHandler() { }

	/**
	 * The reader calls this function before it starts parsing the document. 
	 * The argument locator is a pointer to a Fl_XmlLocator which allows the application 
	 * to get the parsing position within the document. 
	 */
	virtual void set_locator(Fl_XmlLocator **locator) { }

	/**
	 * The reader calls this function when it starts parsing the document. 
	 * The reader calls this function only once.
	 */
    virtual void start_document() { }

	/**
	 * The reader calls this function after it has finished parsing. 
	 * It is called only once, and is the last handler function called. 
	 * It is called after the reader has read all input. 
	 */
    virtual void end_document() { }

	/**
	 * The reader calls this function when it has parsed a processing instruction. 
	 * @param target is the target name of the processing instruction.
	 * @param data is the data in the processing instruction. 
	 */
	virtual void processing_instruction(const Fl_String &target, const Fl_String &data) { }

	/**
	 * The reader calls this function when it has parsed a start element tag.
	 * There is a corresponding end_node() call when the corresponding end element tag is read. 
	 * start_node() and end_node() calls are always nested correctly. 
	 * Empty element tags (e.g. <mytag/>) cause a start_node() call immediately followed by an end_node() call. 
	 * @param name, name of parsed start tag
	 * @param attrs, attribute list that contains attributes of node.
	 */
    virtual void start_node(const Fl_String &name, const Fl_XmlAttributes &attrs) { }

	/**
	 * The reader calls this function when it has parsed an end element (e.g. </mytag>) tag.
	 * @param name, name of parsed end tag.
	 */
	virtual void end_node(const Fl_String &name) { }

	/**
	 * The reader calls this function, when it has parsed a character data.
	 * Entities are converted to their actual values before calling this.
	 * @param cdata, parsed character data
	 */
    virtual void cdata(const Fl_String &cdata) { }

	/**
	 * The parser calls this function, when it has parsed comment
	 * @param comment, content of comment
	 */
    virtual void comment(const Fl_String &comment) { }

	/**
	 * Returns document type for parsed document. 
	 * Entities are stored here.
	 */
	Fl_XmlDocType &doctype() { return m_doctype; }

private:
	Fl_XmlDocType m_doctype;
};

/*@}*/

#endif
