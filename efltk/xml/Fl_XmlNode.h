#ifndef _FL_XMLNODE_H_
#define _FL_XMLNODE_H_

#include <efltk/Fl_Map.h>
#include "Fl_XmlNode_List.h"

class Fl_XmlContext;
class Fl_XmlNode;

// Contains all attributes and values a tag has, represented in a map
typedef Fl_String2String_Map AttrMap;
typedef Fl_String2String_MapPair AttrMap_Pair;

//Nodelist
typedef Fl_XmlNode_List NodeList;

// Node type enumeration
enum {
    //Document node
    FL_XML_TYPE_DOC = 0,
    //Normal node, can contain subnodes
    FL_XML_TYPE_NODE,
    //Comment node
    FL_XML_TYPE_COMMENT
};

// CDATA types
enum {
    //Cdata where all default entities MUST be encoded
    FL_XML_CDATA_NORMAL = 0,
    //Fixed cdata, which can contain preformatted char data. e.g. <[CDATA[ <my text> ]]>
    FL_XML_CDATA_FIXED
};

class Fl_XmlNode
{
    friend class Fl_XmlParser;
public:
    Fl_XmlNode(Fl_XmlContext *ctx, Fl_String name="");
    Fl_XmlNode(Fl_XmlContext *ctx, Fl_XmlNode *parent, Fl_String name="");

    virtual ~Fl_XmlNode();

    // Frees resources, deletes all subnodes
    virtual void clear();

    // Copy constructor
    Fl_XmlNode(const Fl_XmlNode &node) { copy(node); }

    // Copy node 'node' to this
    void copy(const Fl_XmlNode &node);

    // Returns node type
    int type() { return nodetype_; }
    void type(int type) { nodetype_ = (char)type; }

	// Shortcuts to types
	bool is_normal()  { return (nodetype_==FL_XML_TYPE_NODE); }
	bool is_leaf()    { return (chardata_.length()==0 && children()==0); }
	bool is_doc()     { return (nodetype_==FL_XML_TYPE_DOC); }
	bool is_comment() { return (nodetype_==FL_XML_TYPE_COMMENT); }

    // Returns node type
    int cdatatype() { return cdatatype_; }
    void cdatatype(int type) { cdatatype_ = (char)type; }

	// Shortcuts to cdata	
	bool is_fixed_cdata() { return (cdatatype_==FL_XML_CDATA_FIXED); }
	bool has_cdata() { return (chardata_.length()>0); }

    // Returns reference to attribute map
    AttrMap &attributes() { return attributes_; }
    // Sets new attribute map
    void attributes(AttrMap &attr) { attributes_.clear(); attributes_ = attr; }

    // Returns attribute value for given attribute
    Fl_String attribute(Fl_String attr);
    // Sets new value to attribute 'attr'
    void attribute(Fl_String attr, Fl_String value);

    // Returns the node name
    Fl_String name();
    // Sets node name
    void name(Fl_String name);

    // Returns char data of node
    Fl_String &cdata() { return chardata_; }
    // Sets char data
    void cdata(Fl_String cdata) { chardata_ = cdata; }

    // Removes node 'ptr'
    void remove_node(Fl_XmlNode *ptr);
    // Removes all nodes named 'name', returns number of deleted nodes
    int remove_nodes(Fl_String name);

    // Adds new subnode. If 'prepend' flag is true, it's prepended to list,
    // Otherwise appended.
    virtual void add_node(Fl_XmlNode *node, bool prepend=false);
    // Adds new subnode named 'name'. If 'prepend' flag is true, it's prepended to list,
    // Otherwise appended. Returns pointer to added node
    virtual Fl_XmlNode *add_node(Fl_String name, bool preprend=false);

    // Returns reference to subnode list
    NodeList &nodelist() { return nodelist_; }

    // Returns number of subnodes
    int children() { return nodelist_.size(); }
    // Return subnode given index, NULL if out of range.
    Fl_XmlNode *child(int index) { return nodelist_.item(index); }

    // Returns the first occurence of child with the given name.
    // Recursive is true, it will search throught all subnodes
    Fl_XmlNode *child(Fl_String childname, bool recursive=true);

    // Returns list of all subnodes with give name.
    NodeList nodes(Fl_String nodename);

    // Loads xml node from input buffer
    bool load(const char *ptr, int len=0);

    // Saves node to Fl_String 'str'
    void save(Fl_String &str, int indent=0 );

    // Returns parent of this node
    Fl_XmlNode *parent() { return parent_; }
    void parent(Fl_XmlNode *p) { parent_ = p; }

    // Returns context associated with this node
    Fl_XmlContext *context() { return context_; }
    void context(Fl_XmlContext *ctx) { context_ = ctx; }

protected:
    Fl_XmlNode() { }

    // Context pointer
    Fl_XmlContext *context_;
    // Parent pointer
    Fl_XmlNode *parent_;

    // Handle to the real tag name
    unsigned short nodenamehandle_;

    // Nodetype
    char nodetype_, cdatatype_;

    // Attributes of the tag
    AttrMap attributes_;

    // List of subnodes
    NodeList nodelist_;

    // Char data. Used by CDATA or COMMENT
    Fl_String chardata_;
};

#endif
