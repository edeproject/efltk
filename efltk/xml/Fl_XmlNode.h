#ifndef _FL_XMLNODE_H_
#define _FL_XMLNODE_H_

#include <efltk/Fl_Map.h>

class Fl_XmlContext;
class Fl_XmlNode;

// Contains all attributes and values a tag has, represented in a map
typedef Fl_String2String_Map AttrMap;
typedef Fl_String2String_MapPair AttrMap_Pair;


class Fl_XmlNode_List : public Fl_Ptr_List {
public:
    Fl_XmlNode_List() : Fl_Ptr_List() { }

    void append(Fl_XmlNode *item) { Fl_Ptr_List::append((void *)item); }
    void prepend(Fl_XmlNode *item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(uint pos, Fl_XmlNode *item) { Fl_Ptr_List::insert(pos, (void *)item); }
    void replace(uint pos, Fl_XmlNode *item) { Fl_Ptr_List::replace(pos, (void *)item); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(Fl_XmlNode *item) { return Fl_Ptr_List::remove((void *)item); }
    int index_of(const Fl_XmlNode *w) const { return Fl_Ptr_List::index_of((void*)w); }
    Fl_XmlNode *item(uint index) const { return (Fl_XmlNode*)Fl_Ptr_List::item(index); }

    Fl_XmlNode **data() { return (Fl_XmlNode**)items; }

    Fl_XmlNode *operator [](uint ind) const { return (Fl_XmlNode *)items[ind]; }

protected:
    void free_item(Fl_XmlNode *item);
};

//Nodelist
typedef Fl_XmlNode_List NodeList;

//node type
enum {
    //document root node
    FL_XML_TYPE_DOC = 0,
    //normal node, can contain subnodes
    FL_XML_TYPE_NODE,
    //a leaf node, which contains no further nodes, eg. <img/>
    FL_XML_TYPE_LEAF,
    //cdata node, which only contains char data
    FL_XML_TYPE_CDATA,
    //fixed cdata node, which only contains preformatted char data. Tag: <[CDATA[text]]>
    FL_XML_TYPE_FIXED_CDATA,
    //comment node
    FL_XML_TYPE_COMMENT
};

class Fl_XmlNode
{
    friend class Fl_XmlParser;

public:
    // ctor, takes xml context pointer
    Fl_XmlNode(Fl_XmlContext *ctx, Fl_String name="");
    Fl_XmlNode(Fl_XmlContext *ctx, Fl_XmlNode *parent, Fl_String name="");

    virtual ~Fl_XmlNode();

    virtual void clear();

    // copy constructor
    Fl_XmlNode( const Fl_XmlNode &node ) { copy(node); }

    // copy node to this
    void copy(const Fl_XmlNode &node);

    // returns attribute map of the node
    AttrMap &attributes() { return attributes_; }
    void attributes(AttrMap &attr) { attributes_.clear(); attributes_ = attr; }

    // returns attribute value for given attribute
    Fl_String attribute(Fl_String attr);
    // sets new attribute value
    void attribute(Fl_String attr, Fl_String value);

    // returns type of node
    int type() { return nodetype_; }
    // sets new nodetype
    void type(int type) { nodetype_ = (char)type; }

    // returns the node name
    Fl_String name();
    // sets the node name
    void name(Fl_String name);

    // returns cdata of node
    Fl_String &cdata() { return cdata_; }
    // sets new cdata
    void cdata(Fl_String &ncdata) { cdata_ = ncdata; }

    void remove_node(Fl_XmlNode *ptr);
    void remove_node(Fl_String name);

    virtual void add_node(Fl_XmlNode *node, bool prepend=false);
    virtual Fl_XmlNode *add_node(Fl_String name, bool preprend=false);

    // navigation through the nodes
    // returns subnode list
    NodeList *nodelist() { return &nodelist_; }

    // returns the first child with the given name
    Fl_XmlNode *child(Fl_String childname, bool recursive=true);

    // select some nodes and put it into a separate nodelist
    NodeList nodes(Fl_String nodename);

    //load/save functions
    //loads xml node from input stream
    bool load( const char *ptr, int len=0 );

    // saves node to xml output stream
    void save(Fl_String &str, int indent=0 );

    Fl_XmlNode *parent() { return parent_; }
    void parent(Fl_XmlNode *p) { parent_ = p; }

    Fl_XmlContext *context() { return context_; }
    void context(Fl_XmlContext *ctx) { context_ = ctx; }

protected:
    Fl_XmlNode() { }

    Fl_XmlContext *context_;
    Fl_XmlNode *parent_;

    //handle to the real tag name
    unsigned short nodenamehandle_;

    //nodetype
    char nodetype_;

    //attributes of the tag
    AttrMap attributes_;

    //list of subnodes
    NodeList nodelist_;

    //char data
    Fl_String cdata_;
};

#endif
