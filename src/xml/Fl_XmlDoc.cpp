#include <efltk/xml/Fl_XmlDoc.h>
#include <efltk/xml/Fl_XmlCtx.h>
#include <efltk/xml/Fl_XmlParser.h>

Fl_XmlDoc::Fl_XmlDoc()
: Fl_XmlNode()
{
    nodetype_ = FL_XML_TYPE_DOC;
    context_ = new Fl_XmlContext();
    parent_ = 0;
    nodenamehandle_ = context_->insert_tagname("root document");
}

//ctor, takes xml context pointer
Fl_XmlDoc::Fl_XmlDoc( Fl_XmlContext *ctx )
: Fl_XmlNode()
{
    nodetype_ = FL_XML_TYPE_DOC;
    context_ = ctx;
    parent_ = 0;
    nodenamehandle_ = context_->insert_tagname("root document");
}

Fl_XmlNode *Fl_XmlDoc::root_node()
{
    for(uint n=0; n<nodelist_.size(); n++) {
        Fl_XmlNode *nd = nodelist_.item(n);
        if(nd->type()==FL_XML_TYPE_NODE)
            return nd;
    }
    return 0;
}

// xmldocument methods
void Fl_XmlDoc::add_node(Fl_XmlNode *node, bool front)
{
    node->parent(this);

    if(node->type()==FL_XML_TYPE_COMMENT)
    {
        nodelist_.append(node);
    }
    else if(node->type()==FL_XML_TYPE_NODE)
    {
        for(uint n=0; n<nodelist_.size(); n++) {
            Fl_XmlNode *nd = nodelist_.item(n);
            if(nd->type()==FL_XML_TYPE_NODE) {
                nd->parent(0);
                nodelist_.remove(nd);
            }
        }
        nodelist_.append(node);
    }
}

Fl_XmlNode *Fl_XmlDoc::add_node(Fl_String name, bool front)
{
    Fl_XmlNode *tmp = new Fl_XmlNode(context(), this, name);
    return tmp;
}

void Fl_XmlDoc::clear()
{
    Fl_XmlNode *np;

    uint n;
    for(n=0; n<procinstructions_.size(); n++) {
        np = procinstructions_.item(n);
        np->parent(0);
        delete np;
    }
    procinstructions_.clear();

    Fl_XmlNode::clear();
}

/* true if success */
bool Fl_XmlDoc::load( const char *ptr, int len )
{
    clear();
    context_->reset_error();
    Fl_XmlStreamIterator it(context_, ptr, len);
    Fl_XmlParser parser(context_, it);
    return parser.parse_document(*this);
}

/* true if success */
bool Fl_XmlDoc::load(FILE *fp)
{
    clear();
    context_->reset_error();
    Fl_XmlStreamIterator it(context_, fp);
    Fl_XmlParser parser(context_, it);
    return parser.parse_document(*this);
}

#define WRITE_INDENT if(indent > -1) for(int i=0;i<indent;i++) str += ' ';
#define WRITE(text) str += Fl_String(text);

void Fl_XmlDoc::save(Fl_String &str)
{
	uint n;

    // output all processing instructions
    for(n=0; n<procinstructions_.size(); n++) {
        Fl_XmlNode *np = procinstructions_.item(n);
        // output pi tag
        WRITE("<?");
        WRITE(np->name().c_str());

        // output all attributes from current pi
        AttrMap &attr_map = np->attributes();
        for(n=0; n<attr_map.size(); n++)
        {
            AttrMap_Pair *p = attr_map.item(n);
            WRITE(" " + p->id + "=\"" + p->val + "\"");
        }
        // output closing brace
        WRITE("?>\n");
    }

    if(dtds[0] != "") {
        WRITE("<!DOCTYPE " + dtds[0]);
        if(dtds[1].length()>0) {
            WRITE(" " + dtds[1]);
            if(dtds[2].length()>0) WRITE(" " + dtds[2]);
        }
        EntityMap &entmap = context_->entity_map();
        if(entmap.size() > 0) {
            WRITE(" [\n");
            for(uint n=0; n<entmap.size(); n++) {
                EntityMap_Pair *p = entmap.item(n);
                WRITE("<!ENTITY " + p->id + " \"" + p->val + "\">\n");
                //string tmp = ent->key.substr(1, ent->key.length());
            }
            WRITE("]");
        }
        WRITE(">\n");
    }

    // call save() method of the first (and hopefully only) node in xmldocument
    for(n=0; n<nodelist_.size(); n++) {
        Fl_XmlNode *nd = nodelist_.item(n);
        nd->save(str, 0);
    }
}

