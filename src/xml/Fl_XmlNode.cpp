#include <efltk/xml/Fl_XmlNode.h>
#include <efltk/xml/Fl_XmlParser.h>
#include <efltk/xml/Fl_XmlCtx.h>

void Fl_XmlNode_List::free_item(Fl_XmlNode *item)
{
    delete (Fl_XmlNode*)(item);
}

Fl_XmlNode::Fl_XmlNode(Fl_XmlContext *ctx, Fl_String name)
: context_(ctx)
{
    nodetype_ = FL_XML_TYPE_NODE;
    nodenamehandle_ = 0;
    parent_ = 0;
    if(name.length()>0)
        nodenamehandle_ = context()->insert_tagname(name);
}

Fl_XmlNode::Fl_XmlNode(Fl_XmlContext *ctx, Fl_XmlNode *parent, Fl_String name)
: context_(ctx)
{
    nodetype_ = FL_XML_TYPE_NODE;
    nodenamehandle_ = 0;
    parent_ = parent;
    parent_->add_node(this);

    if(name.length()>0)
        nodenamehandle_ = context()->insert_tagname(name);
}

Fl_XmlNode::~Fl_XmlNode()
{
    if(parent_) parent_->remove_node(this);
    clear();
}

Fl_String Fl_XmlNode::attribute(Fl_String attr)
{
    Fl_XmlContext *ctx = context();
    if(!ctx) return Fl_String("");

    Fl_String *ret = attributes_.get_value(attr);
    if(!ret) {
        ctx->lasterror_ = FL_XML_NAME_NOT_FOUND;
        return Fl_String("");
    }
    ctx->lasterror_ = FL_XML_NO_ERROR;
    return *ret;
}

void Fl_XmlNode::attribute(Fl_String attr, Fl_String value)
{
    attributes_.set_value(attr, value);
}

// xmlnode methods
void Fl_XmlNode::copy(const Fl_XmlNode &node)
{
    nodenamehandle_	= node.nodenamehandle_;
    nodetype_		= node.nodetype_;
    attributes_		= node.attributes_;
    cdata_		= node.cdata_;
    nodelist_		= node.nodelist_;
    parent_		= node.parent_;
}

void Fl_XmlNode::clear()
{
    for(uint n=0; n<nodelist_.size(); n++) {
        Fl_XmlNode *np = nodelist_.item(n);
        np->parent(0);
        delete np;
    }
    nodelist_.clear();
}

Fl_String Fl_XmlNode::name()
{
    Fl_XmlContext *ctx = context();
    if(!ctx) return Fl_String("");
    return ctx->get_tagname( nodenamehandle_ );
}

void Fl_XmlNode::name( Fl_String nname )
{
    Fl_XmlContext *ctx = context();
    if(ctx) nodenamehandle_ = context()->insert_tagname(nname);
}

// currently no path-like childname can be passed
Fl_XmlNode *Fl_XmlNode::child(Fl_String childname, bool recursive)
{
    // search for first occurance of node
    for(uint n=0; n<nodelist_.size(); n++) {
        Fl_XmlNode *np = nodelist_.item(n);
        if(np->name() == childname) {
            return np;
        }
        if(recursive) {
            Fl_XmlNode *sub_ch = np->child(childname);
            if(sub_ch) return sub_ch;
        }
    };

    // no valid child found
    return 0;
}

// currently no path-like childname can be passed
NodeList Fl_XmlNode::nodes(Fl_String nodename)
{
    NodeList nlist;

    // search for all occurances of nodename and insert them into the new list
    for(uint n=0; n<nodelist_.size(); n++) {
        Fl_XmlNode *np = nodelist_.item(n);
        if(np->name() == nodename)
            nlist.append(np);
    }

    return nlist;
}

void Fl_XmlNode::add_node(Fl_XmlNode *node, bool prepend)
{
    if(prepend)	nodelist_.prepend(node);
    else nodelist_.append(node);
    node->parent(this);
}

Fl_XmlNode *Fl_XmlNode::add_node(Fl_String name, bool prepend)
{
    Fl_XmlNode *tmp = new Fl_XmlNode(context(), name);
    tmp->parent(this);
    
    if(prepend) nodelist_.prepend(tmp);
    else nodelist_.append(tmp);

    return tmp;
}

void Fl_XmlNode::remove_node(Fl_XmlNode *ptr)
{
    if(ptr) nodelist_.remove(ptr);
}

int Fl_XmlNode::remove_nodes(Fl_String name)
{
    int removed=0;
    for(uint n=0; n<nodelist_.size(); n++) {
        Fl_XmlNode *np = nodelist_.item(n);
        if(np->name() == name) {
            delete np;
            nodelist_.remove(n);
            removed++;
        }
    }
    return removed;
}

/* true if success */
bool Fl_XmlNode::load(const char *ptr, int len)
{
    Fl_XmlContext *ctx = context();
    if(!ctx) return false;

    Fl_XmlStreamIterator it(ctx, ptr, len);
    Fl_XmlParser parser(it);
    return parser.parse_node( *this, context() );
}

#define WRITE_INDENT() if(indent > -1) str += Fl_String(' ', indent)
#define WRITE(text) str += Fl_String(text);

void Fl_XmlNode::save(Fl_String &str, int indent)
{
    Fl_XmlContext *ctx = context();
    if(!ctx) return;

    // output indendation spaces
    WRITE_INDENT();

    if(nodetype_ == FL_XML_TYPE_NODE || nodetype_ == FL_XML_TYPE_LEAF) {
        // Output tag name
        WRITE("<" + ctx->get_tagname(nodenamehandle_));
        // Output attributes
        for(uint n=0; n<attributes_.size(); n++) {
            AttrMap_Pair *p = attributes_.item(n);
            WRITE(" " + p->id + "=\"" + p->val + "\"");
        }
    }

    // depending on the nodetype, do output
    switch(nodetype_)
    {
    case FL_XML_TYPE_CDATA: {
        WRITE(cdata_);
    }
    break;

    case FL_XML_TYPE_FIXED_CDATA: {
        // output all subnodes
        WRITE("<![CDATA[" + cdata_ + "]]>\n");
    }
    break;

    case FL_XML_TYPE_COMMENT: {
        // output all subnodes
        WRITE("<!-- " + cdata_ + " -->\n");
    }
    break;

    case FL_XML_TYPE_NODE: {
        bool only_cdata;
        if(nodelist_.size()==1 && nodelist_.item(0)->type()==FL_XML_TYPE_CDATA) {
            WRITE(">");
            only_cdata = true;
        } else {
            WRITE(">\n");
            only_cdata = false;
        }

        // output all subnodes
        for(uint n=0; n<nodelist_.size(); n++) {
            Fl_XmlNode *np = nodelist_.item(n);
            if(only_cdata) {
                np->save(str, -1);
            } else {
                np->save(str, indent+Fl_XmlContext::indent_spaces());
                if(np->type()==FL_XML_TYPE_CDATA && str[str.length()-1]!='\n')
                    str+="\n";
            }
        }

        // output indendation spaces
        if(!only_cdata)
            WRITE_INDENT();

        // output closing tag
        WRITE("</" + ctx->get_tagname(nodenamehandle_) + ">\n");
    }
    break;

    case FL_XML_TYPE_LEAF: {
        // a leaf has no subnodes
        WRITE("/>\n");
    }
    break;

    default:
        // unknown nodetype
        break;
    }
}
