#include <efltk/xml/Fl_XmlNode.h>
#include <efltk/xml/Fl_XmlParser.h>
#include <efltk/xml/Fl_XmlCtx.h>

//////////////////

Fl_XmlAttributes& Fl_XmlAttributes::operator = (const Fl_XmlAttributes& s)
{
	for(unsigned n=0; n<s.m_attrmap.size(); n++)
		m_attrmap.append_pair(s.m_attrmap.item(n));
	return *this;
}

bool Fl_XmlAttributes::has_attribute(const char *attr) const
{	
    Fl_String *ret = m_attrmap.get_value(attr);
    return (ret!=0);
}

Fl_String &Fl_XmlAttributes::get_attribute(const char *attr) const
{
	Fl_String *ret = m_attrmap.get_value(attr);
    if(!ret) return Fl_String::null_object;
    return *ret;
}

void Fl_XmlAttributes::set_attribute(const char *attr, const Fl_String &value)
{
	m_attrmap.set_value(attr, value);
}

void Fl_XmlAttributes::set_attribute(const char *attr, const char *value)
{
	m_attrmap.set_value(attr, value);
}

//////////////////

void Fl_XmlNode_List::free_item(Fl_XmlNode *item)
{
    delete (Fl_XmlNode*)(item);
}

//////////////////

Fl_XmlNode::Fl_XmlNode(Fl_XmlDoc *doc)
: m_document(doc)
{
    m_nodetype = 0;    
    m_parent = 0;
}

Fl_XmlNode::~Fl_XmlNode()
{
    if(parent()) parent()->remove_child(this);
    clear();
}

void Fl_XmlNode::clear()
{
    for(uint n=0; n<children(); n++) {
        Fl_XmlNode *np = child(n);
        np->parent(0);
        delete np;
    }
    m_child_nodes.clear();
}

void Fl_XmlNode::text(Fl_String &ret)
{
	if(is_text() || is_cdata_section())
		ret += value();

    for(uint n=0; n<children(); n++) {
        Fl_XmlNode *np = child(n);
        np->text(ret);
    }    
}

Fl_XmlNode *Fl_XmlNode::clone_node(bool deep)
{
	Fl_XmlNode *node = new Fl_XmlNode(m_name, m_nodetype, m_document);
	node->m_attributes	= m_attributes;

	if(deep) {
		for(unsigned n=0; n<children(); n++) {
			Fl_XmlNode *np = child(n);
			Fl_XmlNode *cloned = np->clone_node(true);
			node->append_child(cloned);
		}
	}

	return node;
}

// currently no path-like childname can be passed
Fl_XmlNode *Fl_XmlNode::child(const char *name, bool recursive) const
{
    // search for first occurance of node
    for(uint n=0; n < children(); n++) {
        Fl_XmlNode *np = child(n);
        if(np->name() == name) {
            return np;
        }
        if(recursive) {
            Fl_XmlNode *sub_ch = np->child(name, recursive);
            if(sub_ch) return sub_ch;
        }
    };

    // no valid child found
    return 0;
}

// currently no path-like childname can be passed
Fl_XmlNode_List Fl_XmlNode::nodes(const char *name)
{
    Fl_XmlNode_List nlist;

    // search for all occurances of nodename and insert them into the new list
    for(uint n=0; n<children(); n++) {
        Fl_XmlNode *np = child(n);
        if(np->name() == name)
            nlist.append(np);
    }

    return nlist;
}

// Adds the node 'new_child' to the end of the list 
// of children of this node. If the 'new_child' is 
// already in the tree, it is first removed. 
Fl_XmlNode *Fl_XmlNode::append_child(Fl_XmlNode *new_child)
{
	// Remove, if already in list
	if(m_child_nodes.index_of(new_child)>-1)
		m_child_nodes.remove(new_child);	

	// Append to last
    m_child_nodes.append(new_child);
    new_child->parent(this);

	return new_child;
}

// Removes the child node indicated by 'old_child' 
// from the list of children, and returns it. 
Fl_XmlNode *Fl_XmlNode::remove_child(Fl_XmlNode *old_child)
{
	if(!old_child || child_nodes().index_of(old_child)==-1) {
		return 0;
	}

    m_child_nodes.remove(old_child);
	return old_child;
}

// Replaces the child node 'old_child' with 'new_child'
// in the list of children, and returns the 'old_child' node. 
// If the 'new_child' is already in the tree, it is first removed. 
Fl_XmlNode *Fl_XmlNode::replace_child(Fl_XmlNode *new_child, Fl_XmlNode *old_child)
{
	int index = child_nodes().index_of(old_child);
	if(index==-1) return 0;

	remove_child(new_child);

	m_child_nodes.replace(index, new_child);
	new_child->parent(this);

	return old_child;
}

// Inserts the node newChild before the existing child node refChild.
// If refChild is null, insert newChild at the end of the list of children.
// --
// If newChild is a DocumentFragment object, all of its children are inserted, 
// in the same order, before refChild. If the newChild is already 
// in the tree, it is first removed. Returns the node being inserted. 
Fl_XmlNode *Fl_XmlNode::insert_before(Fl_XmlNode *new_child, Fl_XmlNode *ref_child)
{
	int index = ref_child ? child_nodes().index_of(ref_child) : child_nodes().size()-1;
	if(index==-1) return 0;

	remove_child(new_child);

	m_child_nodes.insert(index, new_child);
	new_child->parent(this);

	return new_child;
}

#define WRITE_INDENT() if(indent > 0) { tmp = Fl_String(' ', indent); buffer.append(tmp); }
#define WRITE(text) tmp=(text); buffer.append(tmp)

void Fl_XmlNode::save(Fl_Buffer &buffer, int indent)
{
	Fl_String tmp;

    // output indendation spaces
    WRITE_INDENT();

    if(is_element()) {
        // Output tag name
        WRITE("<" + name());
        // Output attributes
		const Fl_XmlAttributes &attr_map = attributes();
        for(unsigned n=0; n<attr_map.length(); n++)
        {
			Fl_XmlAttributes::Pair *attr = attr_map.item(n);			

			Fl_String real_id, real_val;
			if(!document()->doctype().encode_entities(attr->id, real_id))
				real_id = attr->id;
			if(!document()->doctype().encode_entities(attr->val, real_val))
				real_val = attr->val;

            WRITE(" " + real_id + "=\"" + real_val + "\"");
        }
    }

    // depending on the nodetype, do output
    switch(m_nodetype)
    {
	case DOM_PI: {
		WRITE("<?" + name() + " " + value() + "?>\n");
	}
	break;

    case DOM_TEXT: {
		Fl_String text;
		if(!document()->doctype().encode_entities(value(), text)) {
			WRITE(value());
		} else {
			WRITE(text);
		}
    }
    break;

    case DOM_CDATA_SECTION: {
        // output all subnodes
        WRITE("<![CDATA[" + value() + "]]>\n");
    }
    break;

    case DOM_COMMENT: {
        // output all subnodes
        WRITE("<!-- " + value() + " -->\n");
    }
    break;

    case DOM_ELEMENT: {

		if(has_child_nodes()) {

			bool only_cdata;
			if(children()==1 && child(0)->is_text()) {
				only_cdata = true;
				WRITE(">");
			} else {
				only_cdata = false;
				WRITE(">\n");
			}

			// output all subnodes
			for(uint n=0; n<children(); n++) {
				Fl_XmlNode *np = child(n);
				if(only_cdata)
					np->save(buffer, -1);
				else {
					np->save(buffer, indent + Fl_XmlDoc::indent_spaces());
					if(buffer.data()[buffer.bytes()-1] != '\n')
						buffer.append('\n');
	            }
		    }
	        // output indendation spaces
		    if(!only_cdata)
			    WRITE_INDENT();

			// output closing tag
			WRITE("</" + name() + ">\n");

		} else {

			//LEAF
			WRITE("/>\n");

		}
    }
    break;

    default:
        // unknown nodetype
        break;
    }
}

