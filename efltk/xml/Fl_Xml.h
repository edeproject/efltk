#ifndef _FL_XML_H_
#define _FL_XML_H_

#include "../Fl_Export.h"
#include "../Fl_Map.h"

#include "Fl_XmlDoc.h"
#include "Fl_XmlNode.h"
#include "Fl_XmlParser.h"
#include "Fl_XmlTokenizer.h"

/**
 * \defgroup XML eFLTK XML module
 */
/*@{*/

/**
 * EFLTK xml extension throws Fl_XmlException type exceptions.
 * You should catch always atleast these type of exceptions,
 * when processing XML.
 */
class FL_API Fl_XmlException
{
public:
	/**
	 * XML extension error codes enumeration.
	 */
	enum ErrorCodes {	
		NO_ERROR = 0,			/**< Operation success */
		UNKNOWN,				/**< Unspecified or unknown error */
		OPENTAG_EXPECTED,		/**< Expected an open tag literal '<' */
		OPENTAG_CDATA_EXPECTED, /**< Expected a '<' or cdata */
		CLOSETAG_EXPECTED,		/**< Expected a '>' closing tag literal */
		PI_DOCTYPE_EXPECTED,	/**< Expected a processing instruction or doctype tag */
		TAGNAME_EXPECTED,		/**< Expected a tag name after '<' or '</' */
		COMMENT_START_EXPECTED,	/**< Starting '--' of comment expected after '!' */
		COMMENT_END_MISSING,	/**< Ending '-->' missing */
		SLASH_EXPECTED,			/**< Expected a '/' after closing tag literal '<' */
		TAGNAME_MISMATCH,		/**< Tag name from start and end tag mismatch */
		EQUAL_EXPECTED,			/**< Expected '=' after attribute name */
		VALUE_EXPECTED			/**< Expected value after an '=' in attribute */
	};

	/**
	 * Constructs new exception
	 * @param error,	error code for error
	 * @param locator,	XML locator for stream
	 */
	Fl_XmlException(int error, Fl_XmlLocator *locator) : m_locator(locator), m_error(error) { }

	/**
	 * Returns human readable error string.
	 * @param short_version, return short version of error string
	 */
	Fl_String text(bool short_version=false) const;

    /** 
	 * Returns errorcode of last error happened.
	 */
    int error() const { return m_error; }

	/**
	 * Returns locator for error occured.
	 * NULL, if no locator specified in Fl_XmlParser
	 */
	Fl_XmlLocator *locator() const { return m_locator; }

	/**
	 * Return error string for given errorcode.
	 */
	static const char *error_string(int error);

private:
	Fl_XmlLocator *m_locator;
    int m_error;
};

#define FL_XML_NO_ERROR					Fl_XmlException::NO_ERROR
#define FL_XML_UNKNOWN					Fl_XmlException::UNKNOWN
#define FL_XMP_OPENTAG_EXPECTED			Fl_XmlException::OPENTAG_EXPECTED
#define FL_XML_OPENTAG_EXPECTED			Fl_XmlException::OPENTAG_EXPECTED
#define FL_XML_OPENTAG_CDATA_EXPECTED	Fl_XmlException::OPENTAG_CDATA_EXPECTED
#define FL_XML_CLOSETAG_EXPECTED		Fl_XmlException::CLOSETAG_EXPECTED
#define FL_XML_PI_DOCTYPE_EXPECTED		Fl_XmlException::PI_DOCTYPE_EXPECTED
#define FL_XML_TAGNAME_EXPECTED			Fl_XmlException::TAGNAME_EXPECTED
#define FL_XML_COMMENT_START_EXPECTED	Fl_XmlException::COMMENT_START_EXPECTED
#define FL_XML_COMMENT_END_MISSING		Fl_XmlException::COMMENT_END_MISSING
#define FL_XML_SLASH_EXPECTED			Fl_XmlException::SLASH_EXPECTED
#define FL_XML_TAGNAME_MISMATCH			Fl_XmlException::TAGNAME_MISMATCH
#define FL_XML_EQUAL_EXPECTED			Fl_XmlException::EQUAL_EXPECTED
#define FL_XML_VALUE_EXPECTED			Fl_XmlException::VALUE_EXPECTED

/*@}*/

#endif
