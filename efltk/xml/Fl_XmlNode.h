#ifndef _FL_XMLNODE_H_
#define _FL_XMLNODE_H_

#include <efltk/Fl_Buffer.h>
#include <efltk/Fl_Map.h>
#include "Fl_XmlNode_List.h"

class Fl_XmlDoc;
class Fl_XmlNode;

/**
 * The Fl_XmlAttributes class is map for node attributes.
 */
class Fl_XmlAttributes {
public:
	/**
	 * Attributes are stored as Fl_XmlAttributes::Pair	 
	 <pre> 
	 You can access attribute name and value by:
		Pair::id  = name
		Pair::val = value
	 </pre>
	 */
	typedef const Fl_String_String_Pair Pair;

	/**
	 * Constructs empty attribute map
	 */
	Fl_XmlAttributes() { }

	/**
	 * Assign operator. Makes deep copy of map to another.
	 * @param src as copy source
	 */
    Fl_XmlAttributes& operator = (const Fl_XmlAttributes& src);
    
	/**
	 * Removes all attributes from map.
	 */
	void clear() { m_attrmap.clear(); }

	/**
	 * Search for named attribute.
	 * Returns true, if given attribute is found.
	 * @param attr name of attribute to search
	 */
    bool has_attribute(const char *attr) const;

	/**
     * Returns attribute value for given attribute.
	 * If not found, empty string is returned. 
	 * HTML tags can have empty attributes, for those you should use has_attribute() method.
	 * @param attr name of attribute
	 */
	Fl_String &get_attribute(const char *attr) const;
    
	/** 
	 * Set new value to attribute 'attr'.
	 * If attribute is not found, it's added to map.
	 * @param attr attribute name
	 * @param value attribute value
	 */
	void set_attribute(const char *attr, const char *value);

	/** 
	 * Set new value to attribute 'attr'.
	 * If attribute is not found, it's added to map.
	 * @param attr attribute name
	 * @param value attribute value
	 */
	void set_attribute(const char *attr, const Fl_String &value);

	/**
	 * Return Fl_XmlAttributes::Pair for given index.
	 * Returns NULL if index is out of bound.
	 * @param index of Pair to return. 
	 * @see size()
	 */
	const Pair *item(int index)	const { return m_attrmap.item(index); }

	/**
	 * Returns size of map. This can be used to iterate throught list.
	 <pre>
	 for(unsigned n=0; n<attrmap.size(); n++) {
		Fl_XmlAttributes::Pair *pair = attrmap.item(n);
		printf("%s = %s\n", pair->id.c_str(), pair->val.c_str());
	 }
	 </pre>
	 * @see item(int index)
	 */
	unsigned size() const	{ return m_attrmap.size(); }

	/**
	 * Returns size of map.
	 * This is same as size()
	 * @see size()
	 */
	unsigned length() const	{ return m_attrmap.size(); }

private:
	Fl_String_String_Map m_attrmap;
};

/** node */
class Fl_XmlNode
{    
public:
	/** Node type enumeration */
	enum NodeTypes {		
		DOM_DOCUMENT = 1,	/**< Document node */		
		DOM_ELEMENT,		/**< Normal element node, can contain subnodes */
		DOM_PI,				/**< Processing Instruction node */
		DOM_TEXT,			/**< Cdata where all default entities MUST be escaped. */
		DOM_CDATA_SECTION,	/**< Cdata section, which can contain preformatted char data. e.g. <[CDATA[ <xml rules> ]]> */
		DOM_COMMENT			/**< Comment node */
	};

	/**
	 * Destroys node and all it's children.
	 */
    virtual ~Fl_XmlNode();

	/**
	 * Deletes all children.
	 */
    virtual void clear();

    /**
	 * Returns parent node of this node.
	 * For Fl_XmlDocument this returns NULL.
	 */
    Fl_XmlNode *parent() const { return m_parent; }

    /** 
	 * Returns document context associated with this node.
	 */
    Fl_XmlDoc *document() const { return m_document; }

    /** 
	 * Returns type of node.
	 */
    int type() const { return m_nodetype; }

    /** Returns true node is document type */
    bool is_document()		const { return (type()==DOM_DOCUMENT);  }
    /** Returns true node is element type */
    bool is_element()		const { return (type()==DOM_ELEMENT); }
    /** Returns true node is element type, but has no children */
    bool is_leaf()			const { return (type()==DOM_ELEMENT) && !has_child_nodes(); }
    /** Returns true node is processing instruction (PI) type */
	bool is_pi()			const { return (type()==DOM_PI); }
    /** Returns true node is comment type */
    bool is_comment()		const { return (type()==DOM_COMMENT); }
    /** Returns true node is text type */
    bool is_text()			const { return (type()==DOM_TEXT); }
    /** Returns true node is cdata-section type */
    bool is_cdata_section()	const { return (type()==DOM_CDATA_SECTION); }

    /** 
	 * Returns the node name.
     * The meaning of the value depends on the node type: 
	 <table border=0 bgcolor=#e8e8e8>
	  <tr><td>DOM_DOCUMENT</td>		<td>#document</td>
	  <tr><td>DOM_ELEMENT</td>		<td>The tag name</td>
	  <tr><td>DOM_PI</td>			<td>The target of the processing instruction</td>
	  <tr><td>DOM_COMMENT</td>		<td>#comment</td>
	  <tr><td>DOM_TEXT</td>			<td>#text</td>
	  <tr><td>DOM_CDATA_SECTION</td><td>#cdata-section</td>
	 </table>
	 */
    const Fl_String &name() const { return m_name; }
	/** Set new name for node */
    void name(const Fl_String &name) { m_name = name; }
	/** Set new name for node */
    void name(const char *name) { m_name = name; }

	/**
	 * Returns the value of the node. 
     * The meaning of the value depends on the node type: 
	 <table border=0 bgcolor=#e8e8e8>
	  <tr><td>DOM_DOCUMENT</td>		<td>none</td>
	  <tr><td>DOM_ELEMENT</td>		<td>none</td>
	  <tr><td>DOM_PI</td>			<td>The data of the processing intruction</td>
	  <tr><td>DOM_COMMENT</td>		<td>The comment</td>
	  <tr><td>DOM_TEXT</td>			<td>The text</td>
	  <tr><td>DOM_CDATA_SECTION</td><td>The data of the cdata-section</td>
	 </table>
	 */
    Fl_String &value() { return m_value; }

	/**
	 * Set new value to node.
	 * @param new_value value to set
	 * @see value()
	 */
    void value(const Fl_String &new_value) { m_value = new_value; }

	/**
	 * Set new value to node.
	 * @param new_value value to set
	 * @see value()
	 */
    void value(const char *new_value) { m_value = new_value; }

    /**
	 * Returns cdatas combined from children.
     * e.g. "Some <tag>text</tag> here" becomes: "Some text here"
	 * @param ret string is stored here
	 */
    void text(Fl_String &ret);

    /**
	 * Returns the first occurence of child with the given name.
     * Recursive is true, it will search throught children.
	 * @param name to be searched
	 */
    Fl_XmlNode *child(const char *name, bool recursive=true) const;

    /**
	 * Returns list of all subnodes with give name.
	 * @param name to add list
	 */
    Fl_XmlNode_List nodes(const char *name);

	/**
	 * Creates a deepcopy of the node. 
	 * If deep is true, then the cloning is done recursively which means that all the 
	 * node's children are deep copied too. If deep is false only the node itself is copied and the copy will have no child nodes. 
	 */
    Fl_XmlNode *clone_node(bool deep=false);

	/**
	 * Removes the child node indicated by 'old_child' 
	 * from the list of children, and returns it. 
	 * @param old_child as child to remove
	 */
    Fl_XmlNode *remove_child(Fl_XmlNode *old_child);
	
	/**
	 * Replaces the child node 'old_child' with 'new_child'
	 * in the list of children, and returns the 'old_child' node. 
	 * If the 'new_child' is already in the tree, it is first removed. 
	 */
	Fl_XmlNode *replace_child(Fl_XmlNode *new_child, Fl_XmlNode *old_child);

	/**
	 * Adds the node 'new_child' to the end of the list 
	 * of children of this node. If the 'new_child' is 
	 * already in the tree, it is first removed. 
	 */
	Fl_XmlNode *append_child(Fl_XmlNode *new_child);

	/**
	 * Inserts the node 'new_child' before the existing child node 'ref_child'.
	 * If 'ref_child' is null, insert 'new_child' at the end of the list of children.
	 * If the 'new_child' is already in the tree, it is first removed. 
	 * Returns the node being inserted. 
	 */
	Fl_XmlNode *insert_before(Fl_XmlNode *new_child, Fl_XmlNode *ref_child);                                         
	
	///////////////////////////////////////
	// Child node access

	/**
	 * Returns list of child nodes.
	 */
    const Fl_XmlNode_List &child_nodes() const { return m_child_nodes; }

    /**
	 * Returns number of child nodes
	 */
    unsigned children() const { return m_child_nodes.size(); }

	/**
	 * Returns true, if node has children
	 */
	bool has_child_nodes() const { return m_child_nodes.size()>0; }

    /**
	 * Return child for given index, NULL if out of range.
	 */
    Fl_XmlNode *child(int index) const { return m_child_nodes.item(index); }

	///////////////////////////////////////////
	// Attributes

    /*
	 * Returns reference to attribute map.
	 * @see Fl_XmlAttributes
	 */
    const Fl_XmlAttributes &attributes() const { return m_attributes; }

    /**
	 * Returns true, if node has any attributes
	 */
    bool has_attributes() const { return (m_attributes.size()>0); }

	/**
	 * Returns true, if given attribute is found
	 * @param attr to search
	 */
    bool has_attribute(const char *attr) const { return m_attributes.has_attribute(attr); }

	/**
     * Returns attribute value for given attribute.
	 * If not found, empty string is returned. 
	 * HTML tags can have empty attributes, for those you should use has_attribute() method.
	 * @param attr name of attribute
	 */
	Fl_String &get_attribute(const char *attr) const { return m_attributes.get_attribute(attr); }
    
	/** 
	 * Set new value to attribute 'attr'.
	 * If attribute is not found, it's added to map.
	 * @param attr attribute name
	 * @param value attribute value
	 */
	void set_attribute(const char *attr, const char *value) { m_attributes.set_attribute(attr, value); }
	
	/** 
	 * Set new value to attribute 'attr'.
	 * If attribute is not found, it's added to map.
	 * @param attr attribute name
	 * @param value attribute value
	 */
	void set_attribute(const char *attr, const Fl_String &value) { m_attributes.set_attribute(attr, value); }

    /** 
	 * Saves node to buffer.
	 * @param buffer to save
	 * @param indent how many indent spaces at start
	 */
    virtual void save(Fl_Buffer &buffer, int indent=0);

protected:

	Fl_String m_name;
    Fl_String m_value;

    // Attributes of the tag
    Fl_XmlAttributes m_attributes;

    // Nodetype
    uchar m_nodetype;

    // Document pointer
    Fl_XmlDoc *m_document;
    
	// Parent pointer
    Fl_XmlNode *m_parent;

    // List of subnodes
    Fl_XmlNode_List m_child_nodes;	

private:
	friend class Fl_XmlParser;
	friend class Fl_XmlDoc;

	//Needed by Fl_XmlParser
    void parent(Fl_XmlNode *p) { m_parent = p; }
    void type(int type) { m_nodetype = (uchar)type; }
	Fl_XmlNode(Fl_XmlDoc *doc);	

	//Needed by Fl_XmlDoc
	Fl_XmlNode(const Fl_String &name, int type, Fl_XmlDoc *doc) { m_name = name; m_nodetype = (uchar)type; m_document = doc; m_parent = 0; }

	// Un-implement these.    
    Fl_XmlNode(const Fl_XmlNode &node) { }
	Fl_XmlNode& operator = (const Fl_XmlNode& s) { return *this; }
};

#define FL_XML_TYPE_DOC				Fl_XmlNode::DOM_DOCUMENT
#define FL_XML_TYPE_ELEMENT			Fl_XmlNode::DOM_ELEMENT
#define FL_XML_TYPE_PI				Fl_XmlNode::DOM_PI
#define FL_XML_TYPE_TEXT			Fl_XmlNode::DOM_TEXT
#define FL_XML_TYPE_CDATA_SECTION	Fl_XmlNode::DOM_CDATA_SECTION
#define FL_XML_TYPE_COMMENT			Fl_XmlNode::DOM_COMMENT

#endif
