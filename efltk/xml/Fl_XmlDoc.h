#ifndef _FL_XMLDOC_H_
#define _FL_XMLDOC_H_

#include "Fl_XmlNode.h"
#include "Fl_XmlTokenizer.h"

#include "../Fl_Buffer.h"

/**
 * \defgroup XML eFLTK XML module
 */
/*@{*/

/** 
 * Maps an entity string to a presentation string.
 */
class Fl_XmlEntities : public Fl_String_String_Map {
public:
    typedef Fl_String_String_Iterator Iterator;

    Fl_XmlEntities() { }

    /**
     * Remove named entity.
     * Returns true, if operation success
     * @param name entity name to remove
     */
    bool remove_entity(const char *name) { return remove(name); }

    /**
     * Add entity to map, If entity named 'name' exists already in map,
     * it's value is replaced with 'replacement'
     * @param name, entity to add/change
     * @param replacement, value that represents entity
     */
    void set_entity(const char *name, const char *replacement) { set_value(name, replacement); }
};

/**
 * The Fl_XmlDocType represents tag <DOCTYPE ...> in XML document.
 * It can return a map of all entities(). 
 * This class provides the name(), public_id() and system_id() functions. 
 */
class Fl_XmlDocType {
    friend class Fl_XmlParser;
public:

    Fl_XmlDocType() { m_html = false; }
    Fl_XmlDocType(const char *name, const char *public_id=0, const char *system_id=0);

    /**
     * Returns the name of the document type as specified in the <!DOCTYPE name> tag.
     */
    const Fl_String &name() const { return m_name; }

    /**
     * Returns the public identifier of the external DTD subset.
     * Returns empty string if there is no public identifier.
     */
    const Fl_String &public_id() const { return m_public_id; }

    /**
     * Returns the system identifier of the external DTD subset.
     * Returns empty string if there is no system identifier.
     */
    const Fl_String &system_id() const { return m_system_id; }

    /**
     * Returns a map of all entities described in the DTD.
     * NOTE: Map doesn't hold default entities.
     */
    Fl_XmlEntities &entities() { return m_entities;  }
    const Fl_XmlEntities &entities() const { return m_entities;  }

    /**
     * Encodes string to XML representation.
     * I.e. Converts "<test>" to "&lt;test&gt;"
     * Returns true, any entities replaced.
     * @param str string to convert
     * @param ret converted string is stored to this.
     */
    bool encode_entities(const char *str, Fl_String &ret);

    /**
     * Decodes entities in string to their actual values.
     * I.e. Converts "&lt;test&gt;" to "<test>"
     * Returns true, any entities expanded.
     * @param str string to convert
     * @param ret converted string is stored to this.
     */
    bool decode_entities(const char *str, Fl_String &ret);

    /**
     * Search for entity with given name
     * Returns true, if attribute is found.
     * @param name entity to search
     */
    bool has_entity(const char *name) const;

    /**
     * Remove named entity from entity map.
     * Returns true, if entity removed.
     * @param name entity to remove
     */
    bool remove_entity(const char *name) { return m_entities.remove_entity(name); }

    /**
     * Return replacement value for named entity.
     * If entity is not found, empty string is returned.
     * @param name entity name
     */
    Fl_String get_replacement(const char *name) const;

    /**
     * Add entity to map, If entity named 'name' exists already in map,
     * it's value is replaced with 'replacement'
     * @param name entity to add/change
     * @param replacement value that represents entity
     */
    void set_entity(const char *name, const char *replacement) { m_entities.set_entity(name, replacement); }

private:
    Fl_XmlEntities m_entities;

    Fl_String m_name;
    Fl_String m_public_id;
    Fl_String m_system_id;

    bool m_html;
};

/**
 * The Fl_XmlDoc class represents the entire XML document.
 * It provides access to document root node, which includes all nodes in XML document tree.
 * 
 * Since elements, text nodes, comments, processing instructions, etc...
 * cannot exist outside the context of a document, the document class also contains 
 * the factory functions needed to create these objects. 
 *
 * The node objects created have an document() function which returns document which is used to create it.
 * Creation of elements, text nodes, etc... Is done using the various factory functions provided in this class.  
 */
class Fl_XmlDoc: public Fl_XmlNode
{
    friend class Fl_XmlParser;
public:
    /**
     * Constructs an empty document, without doctype.
     */
    Fl_XmlDoc();
    /**
     * Constructs an empty document, with doctype.
     * @param name of document.
     * @param public_id of document, placed on DOCTYPE declaration
     * @param system_id of document, placed on DOCTYPE declaration
     */
    Fl_XmlDoc(const char *name, const char *public_id=0, const char *system_id=0);

    /**
     * Destroys object and free's all resources
     */
    virtual ~Fl_XmlDoc() { clear(); }

    /**
     * Destroys all nodes in document
     */
    virtual void clear();

    /**
     * Creates new named node of type Fl_XmlNode::DOM_ELEMENT.
     * It can be added to document DOM tree.
     * @param tagname name of element
     * @see Fl_XmlNode
     */
    Fl_XmlNode *create_element(const char *tagname);

    /**
     * Creates new named node of type Fl_XmlNode::DOM_TEXT.
     * It can be added to document DOM tree.
     * @param data content of text node
     * @see Fl_XmlNode
     */
    Fl_XmlNode *create_text(const char *data);

    /**
     * Creates new named node of type Fl_XmlNode::DOM_COMMENT.
     * It can be added to document DOM tree.
     * @param data content of comment node
     * @see Fl_XmlNode
     */
    Fl_XmlNode *create_comment(const char *data);

    /**
     * Creates new named node of type Fl_XmlNode::DOM_CDATA_SECTION.
     * It can be added to document DOM tree.
     * @param data content of CDATA section node
     * @see Fl_XmlNode
     */
    Fl_XmlNode *create_CDATA_section(const char *data);

    /**
     * Creates new named node of type Fl_XmlNode::DOM_PI.
     * It can be added to document DOM tree.
     * @param target is target of processing instruction
     * @param data is data of processing instruction
     * @see Fl_XmlNode
     */
    Fl_XmlNode *create_PI(const char *target, const char *data);

    /**
     * Returns doctype of document.
     * You can use it to add e.g. custom entities.
     <pre>
     mydoc->doctype().set_entity("myentity", "myreplacement");
     </pre>
     */
    Fl_XmlDocType &doctype() { return m_doctype; }
    const Fl_XmlDocType &doctype() const { return m_doctype; }

    /**
     * Returns pointer to root element of document.
     */
    Fl_XmlNode *root_node();

    /**
     * Returns indentation in save.
     */
    static int indent_spaces() { return m_indent_spaces; }

    /**
     * Set indentation in save, defaults to 2
     * @param i as new indent spaces
     */
    static void indent_spaces(int i) { m_indent_spaces = i; }

    /**
     * Save document to buffer.
     * @param buffer as Fl_Buffer to save document
     */
    void save(Fl_Buffer &buffer) const;

private:
    Fl_XmlDocType m_doctype;
    static int m_indent_spaces;
};

/*@}*/

#endif

