#include <efltk/xml/Fl_XmlDoc.h>
#include <efltk/xml/Fl_XmlCtx.h>
#include <efltk/xml/Fl_XmlParser.h>

int Fl_XmlDoc::m_indent_spaces = 2;

//////////////////////////

Fl_XmlDoc::Fl_XmlDoc()
: Fl_XmlNode("#document", DOM_DOCUMENT, 0)
{
    m_parent = 0;		
}

Fl_XmlNode *Fl_XmlDoc::root_node()
{
    for(uint n=0; n < children(); n++) {
        Fl_XmlNode *nd = child(n);
        if(nd->type()==DOM_ELEMENT)
            return nd;
    }
    return 0;
}

void Fl_XmlDoc::clear()
{
    Fl_XmlNode::clear();
}

Fl_XmlNode *Fl_XmlDoc::create_element(const char *tagname)
{
	Fl_XmlNode *node = new Fl_XmlNode(tagname, DOM_ELEMENT, this);
	return node;
}

Fl_XmlNode *Fl_XmlDoc::create_text(const char *data)
{
	Fl_XmlNode *node = new Fl_XmlNode("#text", DOM_TEXT, this);
	node->value(data);
	return node;
}

Fl_XmlNode *Fl_XmlDoc::create_comment(const char *data)
{
	Fl_XmlNode *node = new Fl_XmlNode("#comment", DOM_COMMENT, this);
	node->value(data);
	return node;
}

Fl_XmlNode *Fl_XmlDoc::create_CDATA_section(const char *data)
{
	Fl_XmlNode *node = new Fl_XmlNode("#cdata-section", DOM_CDATA_SECTION, this);
	node->value(data);
	return node;
}

Fl_XmlNode *Fl_XmlDoc::create_PI(const char *target, const char *data)
{
	Fl_XmlNode *node = new Fl_XmlNode(target, DOM_PI, this);
	node->value(data);
	return node;
}

#define WRITE(text) tmp.clear(); tmp=(text); buffer.append(tmp)

void Fl_XmlDoc::save(Fl_Buffer &buffer)
{
	Fl_String tmp;
	unsigned n;
	Fl_XmlNode *xml_pi = 0;

	// Write XML PI
	for(n=0; n<children(); n++) {
		if(child(n)->is_pi() && child(n)->name().upper_case()=="XML") {
			xml_pi = child(n);
			xml_pi->save(buffer);
		}
	}
	
    if(!doctype().name().empty()) 
	{
        WRITE("<!DOCTYPE " + doctype().name());
        if(!doctype().system_id().empty()) {
            WRITE(" SYSTEM \"" + doctype().system_id() + "\"");
						
			if(!doctype().public_id().empty()) {
				WRITE(" PUBLIC \"" + doctype().public_id() + "\"");			            
			}
        }
        Fl_XmlEntities &entmap = doctype().entities();
        if(entmap.size() > 0) {
            WRITE(" [\n");
            for(unsigned n=0; n<entmap.size(); n++) {
				Fl_XmlEntities::Pair *p = entmap.item(n);
                WRITE("<!ENTITY " + p->id + " \"" + p->val + "\">\n");                
            }
            WRITE("]");
        }
        WRITE(">\n");
    }

    // call save() method of the first (and hopefully only) node in xmldocument
    for(n=0; n<children(); n++) {
        Fl_XmlNode *nd = child(n);
		if(nd == xml_pi) continue;
        nd->save(buffer, 0);
    }
}

//////////////////////////////////////

Fl_XmlDocType::Fl_XmlDocType(const char *name, const char *public_id, const char *system_id)
{
	m_html = false;
	m_name = name;
	if(public_id) m_public_id = public_id;
	if(system_id) m_system_id = system_id;
}

#include <efltk/fl_utf8.h>
#include <efltk/Fl_Ptr_Hash.h>

#include <ctype.h>
#include <stdlib.h>

struct entity {
    const char *name;
    int replacement_len;
    const char *replacement;
};

struct entity builtin_ent_html[] = {
#include "html_entities.h"
};
int html_ent_size = (int)(sizeof(builtin_ent_html)/sizeof(builtin_ent_html[0]));

class HTML_EntityCache
{
	Fl_Ptr_Hash hash;
public:	
	HTML_EntityCache() : hash(32) {
		for(int n=0; n<html_ent_size; n++) {
			struct entity *ent = &builtin_ent_html[n];
			hash.insert(ent->name, ent);
		}
	}
	const struct entity *find(const Fl_String &ent) const {
		return (const struct entity *)hash.find(ent);
	}
};
static const HTML_EntityCache html_entities;

struct entity builtin_ent_xml[] =
{
    { "amp", 1, "&" },
    { "lt",  1, "<" },
    { "gt",  1, ">" },
    { "apos",  1, "'" },
    { "quot",  1, "\"" }
};
int xml_ent_size = (int)(sizeof(builtin_ent_xml)/sizeof(builtin_ent_xml[0]));

class XML_EntityCache
{
	Fl_Ptr_Hash hash;
public:	
	XML_EntityCache() : hash(8) {
		for(int n=0; n<xml_ent_size; n++) {
			struct entity *ent = &builtin_ent_xml[n];
			hash.insert(ent->name, ent);
		}
	}
	const struct entity *find(const Fl_String &ent) const {
		return (struct entity *)hash.find(ent);
	}
};
static const XML_EntityCache xml_entities;


bool Fl_XmlDocType::decode_entities(const char *str, Fl_String &ret)
{
    //Fast check..
    if(!strchr(str, '&')) return false;

	int str_len = strlen(str);
	bool replaced = false;

    for(int n=0; n<str_len; n++) 
	{
        if(str[n]=='&') {
            int end=n+1;
            for(; end < str_len; end++) {
                if(str[end]==';')
                    break;
            }
            Fl_String ent(str+n+1, end-(n+1));
            Fl_String rep = get_replacement(ent);
            if(rep!=ent) {
                n += ent.length()+1;
                ret += rep;
				replaced = true;
            } else
                ret += str[n];
        } else
            ret += str[n];
    }

    return replaced;
}

bool Fl_XmlDocType::encode_entities(const char *str, Fl_String &ret)
{
    int num;
    struct entity *table;
    if(m_html) {
        num = html_ent_size;
        table = builtin_ent_html;
    } else {
        num = xml_ent_size;
        table = builtin_ent_xml;
    }

	bool replaced = false;

	const char *ptr = str;
    while(*ptr)
    {
        bool found=false;
        for(int i = 0; i < num; i++) {
            if(!strncmp(ptr, table[i].replacement, table[i].replacement_len)) {
                ret += '&';
                ret += table[i].name;
                ret += ';';
                found = replaced = true;				
            }
        }

        if(!found) {
            for(uint a=0; a<m_entities.size(); a++) {
				Fl_XmlEntities::Pair *p = m_entities.item(a);
                if(!strncmp(ptr, p->val.c_str(), p->val.length())) {
                    ret += '&';
                    ret += p->id;
                    ret += ';';
                    found = replaced = true;
                    ptr += p->val.length()-1;
                }
            }
        }

        if(!found)
            ret += *ptr;

		ptr++;
    }

    return replaced;
}


Fl_String Fl_XmlDocType::get_replacement(const char *name) const
{
    int len = 0;

    // &#123; style entity..
    if(name[0]=='#') {
		char tmp[6]; 
        if(isdigit(name[1])) {
            int code = strtol(name+1, NULL, 10);
			len = fl_ucs2utf(code, tmp);            
			tmp[len] = '\0';
            return Fl_String(tmp, len);
        } else if(name[1]=='x' || name[1]=='X') {
			int code = strtol(name+2, NULL, 16);
			len = fl_ucs2utf(code, tmp);
            tmp[len] = '\0';
            return Fl_String(tmp, len);
		}
    }

    // Find in built-ins, see entities.h
    const struct entity *entity;
    if(m_html) 
		entity = html_entities.find(name);
    else
		entity = xml_entities.find(name);
	if(entity) return Fl_String(entity->replacement, entity->replacement_len);

    // Find in custom attributes
	for(uint a=0; a<m_entities.size(); a++) {
		Fl_XmlEntities::Pair *p = m_entities.item(a);
		if(p->id == name) return p->val;
	}
    
	return name;
}

bool Fl_XmlDocType::has_entity(const char *name) const
{
	Fl_String tmp = get_replacement(name);
	return (tmp!=name);
}

void Fl_XmlEntities::set_entity(const char *name, const char *replacement)
{
	m_entitymap.set_value(name, replacement);
}

bool Fl_XmlEntities::remove_entity(const char *name)
{
	Fl_XmlEntities::Pair *p = m_entitymap.find_pair(name);
	if(p) {
		int pos = m_entitymap.index_of(p);
		if(pos>-1) {
			m_entitymap.remove_pair(pos);
			return true;
		}
	}
	return false;
}
