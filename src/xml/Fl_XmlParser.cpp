#include <config.h>

#include <efltk/Fl_Exception.h>

#include <efltk/xml/Fl_XmlParser.h>
#include <efltk/xml/Fl_XmlDoc.h>
#include <efltk/xml/Fl_XmlNode.h>

#include <ctype.h>
#include <stdlib.h>

///////////////////////////
// BEGIN OF HTML GLOBALS //
///////////////////////////

// 
// Our hardcoded DTD :)
// Will be replaced at some time in future.. 
//
// HTML 3.2 / 4.0 STD entities

// %list 
#define content_list		" UL OL DIR MENU "
// %preformatted 
#define content_preform		" PRE "
// %heading 
#define content_heading		" H1 H2 H3 H4 H5 H6 "
// %font 
#define content_font		" TT I B U S STRIKE BIG SMALL "
// %phrase 
#define content_phase		" EM STRONG DFN CODE SAMP KBD VAR CITE ACRONYM "
// %special 
#define content_special		" A IMG APPLET OBJECT FONT BASEFONT BR SCRIPT MAP Q SUB SUP SPAN BDO IFRAME "
// %formctrl
#define content_formctl		" INPUT SELECT TEXTAREA LABEL BUTTON "
// #PCDATA
#define content_cdata		" CDATA "
// %blocklevel
#define content_blocklevel	" P " content_heading content_list content_preform " DL DIV CENTER NOSCRIPT NOFRAMES BLOCKQUOTE FORM ISINDEX HR TABLE FIELDSET ADDRESS "
// #empty
#define content_empty		0

// %inline
#define content_inline		content_cdata content_font content_phase content_special content_formctl
// %block
#define content_block		content_blocklevel content_inline

// Not std entities:
#define content_body		content_block " INS DEL "
#define content_pre			content_inline
#define content_head		" TITLE ISINDEX BASE SCRIPT STYLE META LINK "
#define content_table		" CAPTION TR COL COLGROUP THEAD TFOOT TBODY "

struct html_tag {
	const char *tag;
	const char *cont;
	bool require_endtag;
	bool is_block;
} html_tags[] = {
	{ "A",				content_inline,		true,	false },
	{ "ACRONYM",		content_inline,		true,	false },
	{ "ADDRESS",		content_inline " P ", true, false },
	{ "APPLET",			content_inline,		true,	true },
	{ "AREA",			content_empty,		false,	false },
	
	{ "B",				content_inline,		true,	false },
	{ "BASE",			content_empty,		false,	false },
	{ "BASEFONT",		content_empty,		false,	false },
	{ "BDO",			content_inline,		true,	true },
	{ "BIG",			content_inline,		true,	false },
	{ "BLOCKQUOTE",		content_block,		true,	true },
	{ "BODY",			content_body,		false,	true },
	{ "BR",				content_empty,		false,	false },
	{ "BUTTON",			content_inline,		true,	true },

	{ "CAPTION",		content_inline,		true,	true},
	{ "CENTER",			content_body,		true,	true },
	{ "CITE",			content_inline,		true,	false },
	{ "CODE",			content_inline,		true,	false },
	{ "COL",			content_empty,		false,	false },
	{ "COLGROUP",		content_empty,		false,	false },
	
	{ "DD",				content_block,		false,	true },
	{ "DEL",			content_inline,		true,	true },
	{ "DFN",			content_inline,		true,	true },
	{ "DIR",			" LI "content_block, true,	true },
	{ "DIV",			content_block,		true,	true },
	{ "DL",				" FORM DT DD ",		true,	true },
	{ "DT",				content_inline,		false,	true },

	{ "EM",				content_inline,		true,	false },
	
	// fieldset
	{ "FONT",			content_inline,		true,	false},
	{ "FORM",			content_block " SCRIPT", true,	true },
	// frame
	// frameset

	{ "H1",				content_inline,		true,	true },
	{ "H2",				content_inline,		true,	true },
	{ "H3",				content_inline,		true,	true },
	{ "H4",				content_inline,		true,	true },
	{ "H5",				content_inline,		true,	true },
	{ "H6",				content_inline,		true,	true },
	{ "HEAD",			content_head,		false,	true },
	{ "HR",				content_empty,		false,	false },
	{ "HTML",			" HEAD FRAMESET BODY ", false, true },

	{ "I",				content_inline,		true,	false },
	{ "IMG",			content_empty,		false,	false },
	{ "INPUT",			content_empty,		false,	false },
	{ "ISINDEX",		content_empty,		false,	false },
	{ "KBD",			content_inline,		true,	false },

	{ "LI",				content_block,		false,	true },
	{ "LINK",			content_empty,		false,	false},
	{ "LISTING",		content_cdata,		true,	true },

	{ "MAP",			" AREA ",			true,	false },
	{ "MENU",			content_block " LI ", true, true },
	{ "META",			content_empty,		false,	false },

	{ "NOSCRIPT",		content_block,		true,	true },
	{ "NOFRAMES",		content_body,		true,	true },

	{ "OL",				" FORM LI ",		true,	true },
	{ "OPTION",			content_cdata,		false,	true },

	{ "P",				content_inline,		false,	true },
	{ "PARAM",			content_empty,		false,	false },
	{ "PLAINTEXT",		content_cdata,		false,	true },
	{ "PRE",			content_pre,		true,	true },

	{ "SAMP",			content_inline,		true,	false },
	{ "SCRIPT",			content_cdata,		true,	true },
	{ "SELECT",			" OPTION ",			true,	true },
	{ "SMALL",			content_inline,		true,	false },
	{ "SPAN",			content_inline,		true,	true },
	{ "STRIKE",			content_inline,		true,	false },
	{ "STRONG",			content_inline,		true,	false },
	{ "STYLE",			content_cdata,		true,	true },
	{ "SUB",			content_inline,		true,	false },
	{ "SUP",			content_inline,		true,	false },

	{ "TABLE",			content_table,		true,	true },
	{ "TBODY",			" FORM TR ",		false,	true },
	{ "TD",				content_body,		false,	true },
	{ "TEXTAREA",		content_cdata,		true,	false },
	{ "TFOOT",			" FORM TR ",		false,	true },
	{ "TH",				content_body,		false,	true },
	{ "TITLE",			content_cdata,		true,	false },
	{ "TR",				" FORM TH TD ",		false,	true },
	{ "TT",				content_inline,		true,	false },

	{ "U",				content_inline,		true,	false },
	{ "UL",				" FORM LI ",		true,	true },

	{ "VAR",			content_inline,		true,	false },

	{ "XMP",			content_cdata,		true,	false },
};
static int tag_table_size = sizeof(html_tags) / sizeof(html_tags[0]);

class TagCache
{
public:
    Fl_String_Ptr_Map tag_hash;
    TagCache() : tag_hash() {
        for(int n=0; n<tag_table_size; n++) {
            struct html_tag *tag = &html_tags[n];
            tag_hash.insert(tag->tag, tag);
        }
    }
    const struct html_tag *find(const Fl_String &tag) const {
        return (const struct html_tag *)tag_hash.get_value(tag);
    }
};
static const TagCache cache;

bool is_content(const Fl_String &tag, const Fl_String &content) 
{
	Fl_String search(" "+tag+" ");
	const struct html_tag *cont = cache.find(content);
	if(cont && cont->cont)
		return (strstr(cont->cont, search)!=0);
	return false;
}

bool require_endtag(const Fl_String &tag)
{
	const struct html_tag *cont = cache.find(tag);
    return (cont && cont->require_endtag);
}

bool is_html_leaf(const Fl_String &tag) 
{
	const struct html_tag *cont = cache.find(tag);
	if(cont) return (!cont->require_endtag && !cont->cont);
    return false;
}

bool is_html_block(const Fl_String &tag) 
{
	const struct html_tag *cont = cache.find(tag);
	return (cont && cont->is_block);	
}

bool is_html_tag(const Fl_String &tag) 
{
	const struct html_tag *cont = cache.find(tag);
	return (cont!=0);
}

///////////////////////////
// END OF HTML GLOBALS ////
///////////////////////////

// xmlparser methods
Fl_XmlParser::Fl_XmlParser(Fl_XmlTokenizer &tok)
: tokenizer(tok)
{
    m_eventhandler = 0;

	m_html_mode = false;    
	tag_end = false;
	force_ret = 0;
}

#define throw_error(error) throw Fl_XmlException(error, tokenizer.locator())

bool Fl_XmlParser::parse_document(Fl_XmlDoc *doc)
{
	if(handler()) {
		Fl_XmlLocator *loc = 0;
		handler()->set_locator(&loc);
		if(loc) tokenizer.locator(loc);
		
		handler()->start_document();
	}

	Fl_XmlNode *subnode = 0;
	if(!handler()) subnode = doc->create_element("");

	while(parse_node(doc, subnode)) {
					
		if(!handler()) {
			doc->append_child(subnode);
			subnode = doc->create_element("");				
		}			
	}
	if(subnode) delete subnode;

    // if successful, put node into nodelist
    if(handler()) handler()->end_document();	

    return true;
}

// parses the doctype
bool Fl_XmlParser::parse_doctype(Fl_XmlDocType *doc)
{	
	doc->m_html = html_mode();

	tokenizer.attr_mode(true);

	const Fl_String &token = (*tokenizer);
	bool next_public = false;
	bool next_system = false;

    for(int n=0; n<3; n++) {
		//token = (*tokenizer++);
		tokenizer++;

        if(tokenizer.eos()) {            
			tokenizer.attr_mode(false);
            return false;
        }		

        if(token=='[') {
            tokenizer.put_back();
            break;
        }

        if(token=='>') {
			tokenizer.attr_mode(false);
            return true;
		}

		if(doc->m_name.empty()) {

			doc->m_name = token;

		} else if(next_public) {	
			
			doc->m_public_id = token;
			next_public = false;
			next_system = true;

		} else if(next_system) {

			doc->m_system_id = token;
			next_system = false;

		} else if(token=="PUBLIC") {
			
			next_public = true;

		} else if(token=="SYSTEM") {
	
			next_system = true;

		} 

    }	
	printf("TOKEN %s %s %s\n", doc->name().c_str(), doc->public_id().c_str(), doc->system_id().c_str());
	
    do { 
		// read the complete tag till the closing '>'        
		tokenizer++;		
		
		if(tokenizer.eos()) {
			tokenizer.attr_mode(false);
			return false;
		}

        if(token == "[") 
		{
            tokenizer++;
			do {
                if(token == '<') 
				{					
					tokenizer++;					
                    if(token == "!ENTITY") {	                    

                        Fl_String key = *tokenizer++;
						if(key == "%") {
							continue; //Can't handle it...
                        }

                        const Fl_String &value = *tokenizer++;
						doc->entities().set_entity(key, value);

						tokenizer++;
                        if(token != '>') {
							tokenizer.attr_mode(false);
							throw_error(Fl_XmlException::CLOSETAG_EXPECTED);
                            return false;
                        }
					} else if(token[0]=='-' && (*tokenizer)[1]=='-') {
						// COMMENT??
						// Ignore..
                        tokenizer.put_back();
						if(!parse_comment(0)) {
							tokenizer.attr_mode(false);								
							return false;
						}
					}
                } // token == '<'

                tokenizer++;				

            } while(token != "]" && !tokenizer.eos());
            
			tokenizer++; //Jump over ']'
            break;
        } // token == ']'

    } while(token != '>');

    if(token != '>') {
		tokenizer.attr_mode(false);
        throw_error(Fl_XmlException::CLOSETAG_EXPECTED);
        return false;
    }

	tokenizer.attr_mode(false);
    return true;
}

#define FORCE_CONTINUE 1
#define FORCE_RETURN   2

#define PRESERVE_FORMAT " PRE "

// parses the contents of the current node
bool Fl_XmlParser::parse_node(Fl_XmlDoc *doc, Fl_XmlNode *node)
{		
    Fl_String token1, token2;	

	token1 = *tokenizer++;	
	if(tokenizer.eos())		
		return false;	

    // loop when we encounter a comment
    bool again;
    do {
        again = false;			

        // check if we have cdata
        if(!is_literal(token1, true))
        {			
            Fl_String cdata;
            if(!handler()) {                
                node->name("#text");
                node->type(Fl_XmlNode::DOM_TEXT);
            }            

            while(!tokenizer.eos() && !is_literal(token1, true)) {					
				if(!cdata.empty()) cdata += ' ';
                cdata += token1;				
                token1 = *tokenizer++;
            }

			if(!tokenizer.pre_mode())
				cdata = cdata.trim();

			if(cdata.empty()) return false;			

			Fl_XmlDocType *doctype;
			if(handler())	doctype = &handler()->doctype();
			else			doctype = &doc->doctype();

			Fl_String decoded;
			if(doctype->decode_entities(cdata, decoded)) 
			{				
				if(handler())	handler()->cdata(decoded);
				else			node->value(decoded);
			} else {
				if(handler())	handler()->cdata(cdata);
				else			node->value(cdata);
			}                        

			tokenizer.put_back();				

            return true;
        }		

        // no cdata, try to continue parsing node content
        if(token1 != '<') {
			throw_error(Fl_XmlException::OPENTAG_CDATA_EXPECTED);			
			return false; // Open tag expected
        }
		
        // get node name
        token2 = *tokenizer++;
        if(is_literal(token2)) 
		{			
            // check the following literal
            switch(literal(token2))
            {
            case '/': { 
				// closing '</...>' follows
                // return, we have a closing node with no more content				

				if(html_mode() && !parent_name.empty()) 
				{
					Fl_String closing_tag = (*tokenizer++).upper_case();					
					if(parent_name != closing_tag)
					{							
						if(is_content(parent_name, closing_tag)) {						
							force_ret = FORCE_RETURN;							
						}
						else if(!require_endtag(parent_name)) {							
							force_ret = FORCE_CONTINUE;
							tokenizer++; //Skip '>'
							return false;
						}
					}
					tokenizer.put_back(); //Tag name
				}
				
				// Put back '</'				
				tokenizer.put_back( "/" ); 
				tokenizer.put_back( "<" );
				
                return false;
            }			

			case '?': {
				// Processing instruction!
				token1 = *tokenizer++;
			
				if(is_literal(token1)) {				
					throw_error(Fl_XmlException::PI_DOCTYPE_EXPECTED);
					return false;
				}

				// parse processing instruction
				Fl_String target( token1 );
				Fl_String data;				

				tokenizer.cdata_mode(true);
				tokenizer.prolog_mode(true);
	
				tokenizer++;
				while(!tokenizer.eos()) {										
					data += (*tokenizer);					
					tokenizer++;
					if((*tokenizer) == '?' || (*tokenizer) == '>') {
						break;
					}
				}

				if(handler()) {
					handler()->processing_instruction(target, data);
				} else {					
					node->name(target);
					node->value(data);
					node->type(Fl_XmlNode::DOM_PI);					
				}

				tokenizer.cdata_mode(false);
				tokenizer.prolog_mode(false);

				if(*tokenizer != '?') {									
					throw_error(Fl_XmlException::PI_DOCTYPE_EXPECTED);
					return false;
				}

				tokenizer++;
				if(*tokenizer != '>') {
					throw_error(Fl_XmlException::CLOSETAG_EXPECTED);
					return false;
				}
				return true;
			}

            case '!': {
                token2 = *tokenizer++;
                // now a doctype tag or a comment may follow				

                if(token2[0] == '-' && token2[1] == '-') {
                    tokenizer.put_back();
                    if(!parse_comment(node))
                        return false;
                    return true;

                }
                else if(token2[0] == '[') {

                    if(!strncmp(token2.c_str(), "[CDATA[", 7))
                    {
                        Fl_String *cdata_pointer;
                        if(!handler()) {
                            cdata_pointer = &node->value();
                            node->name("#cdata-section");
                            node->type(Fl_XmlNode::DOM_CDATA_SECTION);
                        } else {
                            static Fl_String temp_cdata;
                            cdata_pointer = &temp_cdata;
                        }

                        Fl_String &cdata = *cdata_pointer;
                        // parse cdata section and return as new node.
                        cdata.clear();

                        tokenizer.cdata_mode(true);
                        while(!tokenizer.eos()) {
                            cdata += *tokenizer;
                            if((*tokenizer)[0]=='>' && !strncmp(cdata.c_str()+cdata.length()-3, "]]>", 3))
                                break;
                            tokenizer++;
                        }
                        tokenizer.cdata_mode(false);

                        if(!strncmp(cdata.c_str(), "[CDATA[", 7))
                            cdata.sub_delete(0, 7); //Delete "[CDATA["
                        cdata.sub_delete(cdata.length()-3, 3); //Delete "]]>"

                        if(handler()) handler()->cdata(cdata);
                        return true;
                    }

                    // Skip to next literal, cant do anything with this data :(
                    while(!tokenizer.eos() && !is_literal(*tokenizer++));
                    token1 = *tokenizer++;
                } 
				else if(token2.upper_case()=="DOCTYPE") 
				{					
					Fl_XmlDocType *dt;
					if(handler()) {
						dt = &handler()->doctype();
					} else {
						dt = &doc->doctype();
					}
                    if(!parse_doctype(dt))
						return false;
					token1 = *tokenizer++;
				}

                // parse again, until we encounter some useful data
                again = true;
            }
            break;

            default:						
                throw_error(Fl_XmlException::TAGNAME_EXPECTED);
                return false; // Tagname expected
            }
        }
    } while(again && !tokenizer.eos());	

	Fl_String tagname;
    // Store tagname
	if(html_mode())
		tagname = token2.upper_case();
	else 
		tagname = token2;

	if(html_mode() && !last_block.empty() && is_html_tag(tagname))
	{
		const Fl_String &last_name = last_block;

		if( (!require_endtag(last_name) && is_html_block(tagname))
			&& (last_name==tagname || !is_content(tagname, last_name)) )
		{
			// Do fake end for HTML tag :)
			tokenizer.put_back(tagname);
			tokenizer.put_back("<");
			tag_end=true;
			return false;
		}
	}

	if(html_mode()) {
		if(is_html_block(tagname)) {
			last_block = tagname;
		}
	}

    // insert tag name 
    if(node) node->name(tagname);		

    // parse attributes
    if(!handler()) {
		if(!parse_attributes(doc, &node->m_attributes))
			return false;
    } else {
        Fl_XmlAttributes temp_map;
		if(!parse_attributes(0, &temp_map))
			return false;

		handler()->start_node(tagname, temp_map);
    }

	// check for leaf
    token1 = *tokenizer++;

    // HMTL, check for leafs
    if(html_mode()) {		
        if(is_html_leaf(tagname)) {
            if(handler()) handler()->end_node(tagname);			
            return true;
        }	    

		Fl_String search(' ');
		search += tagname;
		search += ' ';
		if(strstr(PRESERVE_FORMAT, search))
			tokenizer.pre_mode(true);
		else
			tokenizer.pre_mode(false);			
    }

    // XML
    if(token1 == '/') {
        // node has finished
        token2 = *tokenizer++;
        if(token2 != '>' ) {
            throw_error(Fl_XmlException::CLOSETAG_EXPECTED);
            return false; // Close Tag expected
        }        
        if(handler()) handler()->end_node(tagname);
        // return, let the caller continue to parse
        return true;
    }

    // now a closing bracket must follow
    if(token1 != '>') {		
        throw_error(Fl_XmlException::CLOSETAG_EXPECTED);
        return false; // Close Tag expected
    }

	bool xml_in_html = false;
	if(tagname=="XML") {
		html_mode(false);
		xml_in_html = true;
	}

    // loop to parse all subnodes
	Fl_String saved_parent;
	if(html_mode()) saved_parent = parent_name;

	if(!handler()) 
	{
		// TREE MODE
		Fl_XmlNode *subnode = 0;
		while(true) {
			if(!subnode) subnode = new Fl_XmlNode(doc);			
			subnode->type(Fl_XmlNode::DOM_ELEMENT);
			
			tag_end=false; force_ret = 0;

			parent_name = tagname;
		    if(parse_node(doc, subnode)) {
				
				node->append_child(subnode);
				subnode = 0;

	        } else {			
				if(force_ret != 0) {				
					switch(force_ret) {
					case FORCE_RETURN:											
						parent_name = saved_parent;
						return true;
					case FORCE_CONTINUE:
					default:
						break;
					};								
				} else
					break;
			}
		}
	    if(subnode)
	        delete subnode;

	} else {
	
		// SAX MODE
		while(true) {		
			
			tag_end=false; force_ret = 0;

			parent_name = tagname;
		    if(!parse_node(0, 0)) {
				if(force_ret != 0) {				
					switch(force_ret) {
					case FORCE_RETURN:
						handler()->end_node(tagname);
						parent_name = saved_parent;
						return true;
					case FORCE_CONTINUE:
					default:
						break;
					};								
				} else
					break;
			}
		}

	}
	
	if(html_mode()) parent_name = saved_parent;

	if(xml_in_html) {
		html_mode(true);
	}

	if(html_mode()) {		
		if(tokenizer.pre_mode())
			tokenizer.pre_mode(false);

		last_block = parent_name;
	}

	if(tokenizer.eos()) return true;

	if(html_mode() && tag_end) {
		if(handler()) handler()->end_node(tagname);
		return true;
	}	
	
	// parse end tag
    Fl_String token5 = *tokenizer++;
    tokenizer++;

    if(token5 != '<' && *tokenizer != '/') {
        throw_error(Fl_XmlException::OPENTAG_EXPECTED);
        return false;
    }
	
    token1 = *tokenizer++;
	
    if(is_literal(token1)) {
        throw_error(Fl_XmlException::TAGNAME_EXPECTED);
        return false;
    }	

    // check if open and close tag names are identical
    if(!html_mode() && token1 != tagname) {
        throw_error(Fl_XmlException::TAGNAME_MISMATCH);
        return false;
    }

    if( (*tokenizer++) != '>') {
        throw_error(Fl_XmlException::CLOSETAG_EXPECTED);
        return false;
    }

    if(handler()) handler()->end_node(tagname);

    return true;
}

// parses tag attributes
bool Fl_XmlParser::parse_attributes(Fl_XmlDoc *doc, Fl_XmlAttributes *attr)
{
    while(true) {		

		tokenizer++;
		if(tokenizer.eos()) return false;
		
		if((*tokenizer).empty()) continue;        

        if((*tokenizer) == ">" || (*tokenizer) == "/") {
            tokenizer.put_back();
            return true;
        }		

		Fl_String name = *tokenizer;

        if( (*tokenizer++) != '=') {
            if(html_mode()) {
				tokenizer.put_back();
                attr->set_attribute(name, Fl_String::null_object);
				continue;
            } else {
                throw_error(Fl_XmlException::EQUAL_EXPECTED);
                return false; // '=' expected: key=value
            }
        }
		
		tokenizer.attr_mode(true);
        if(is_literal( (*tokenizer++), true )) {
            tokenizer.attr_mode(false);
			throw_error(Fl_XmlException::VALUE_EXPECTED);			
            return false;
        }
		tokenizer.attr_mode(false);

        const Fl_String &value = (*tokenizer);
		
		Fl_XmlDocType *doctype;
		if(handler())	doctype = &handler()->doctype();
		else			doctype = &doc->doctype();
		
		Fl_String decoded;
		// insert attribute into the map
		if(doctype->decode_entities(value, decoded)) {			
			attr->set_attribute(name, decoded);
		} else {
			attr->set_attribute(name, value);
		}       
    }
    return true;
}

bool Fl_XmlParser::parse_comment(Fl_XmlNode *node)
{
    Fl_String comment;

    tokenizer.cdata_mode(true);
    while(true) {
        if(tokenizer.eos()) {
            throw_error(Fl_XmlException::COMMENT_END_MISSING);
            return false;
        }

        tokenizer++;		

        if(comment[comment.length()-1]=='-' && comment[comment.length()-2]=='-') {
            if(*tokenizer == '>')
                break;
        }

        const Fl_String &part = (*tokenizer);

        if( comment.length()==0 && (part[0]!='-' || part[1]!='-') ) {
            throw_error(Fl_XmlException::COMMENT_START_EXPECTED);
            return false;
        }

        comment+=part;
    }
    tokenizer.cdata_mode(false);    
    
	if(node) {

		comment.sub_delete(0, 2);
		comment.sub_delete(comment.length()-2, 2);
        node->name( "#comment" );
        node->type(Fl_XmlNode::DOM_COMMENT);
        node->value(comment);

    } else if(handler()) {

		comment.sub_delete(0, 2);
		comment.sub_delete(comment.length()-2, 2);
		handler()->comment(comment);
    }

    return true;
}

/////////////////////////////////////////////
/////////////////////////////////////////////

Fl_XmlDoc *Fl_XmlParser::create_dom(Fl_XmlTokenizer &tokenizer, Fl_XmlLocator *locator, bool html_mode)
{
	tokenizer.locator(locator);

	Fl_XmlParser parser(tokenizer);
	parser.html_mode(html_mode);

	Fl_XmlDoc *doc = new Fl_XmlDoc();
	try {
		parser.parse_document(doc);
	} catch(...) {
		delete doc;
		throw;
	}
	return doc;
}

Fl_XmlDoc *Fl_XmlParser::create_dom(const char *buffer, int buffer_len, Fl_XmlLocator *locator, bool html_mode)
{
	Fl_XmlDefaultTokenizer tokenizer(buffer, buffer_len);
	return create_dom(tokenizer, locator, html_mode);
}

Fl_XmlDoc *Fl_XmlParser::create_dom(FILE *fp, Fl_XmlLocator *locator, bool html_mode)
{
	Fl_XmlDefaultTokenizer tokenizer(fp);
	return create_dom(tokenizer, locator, html_mode);
}


bool Fl_XmlParser::create_sax(Fl_XmlHandler &handler, Fl_XmlTokenizer &tokenizer, bool html_mode)
{
	Fl_XmlParser parser(tokenizer);
	parser.handler(&handler);
	parser.html_mode(html_mode);
	
	parser.parse_document(0);
	return true;
}

bool Fl_XmlParser::create_sax(Fl_XmlHandler &handler, const char *buffer, int buffer_len, bool html_mode)
{
	Fl_XmlDefaultTokenizer tokenizer(buffer, buffer_len);
	return create_sax(handler, tokenizer, html_mode);
}

bool Fl_XmlParser::create_sax(Fl_XmlHandler &handler, FILE *fp, bool html_mode)
{
	Fl_XmlDefaultTokenizer tokenizer(fp);
	return create_sax(handler, tokenizer, html_mode);
}

/////////////////////////////////////////////
/////////////////////////////////////////////

#define XMLERRORCODE(x,y)  case x: err = y; break;
const char *Fl_XmlException::error_string(int error)
{
    const char *err="Unknown error";
    switch(error) {
        XMLERRORCODE(Fl_XmlException::NO_ERROR, "Operation success");
        XMLERRORCODE(Fl_XmlException::UNKNOWN, "Unspecified or unknown error");
        XMLERRORCODE(Fl_XmlException::OPENTAG_EXPECTED, "Expected an open tag literal '<'");
        XMLERRORCODE(Fl_XmlException::OPENTAG_CDATA_EXPECTED, "Expected a '<' or cdata");
        XMLERRORCODE(Fl_XmlException::CLOSETAG_EXPECTED, "Expected an '>' closing tag literal");
        XMLERRORCODE(Fl_XmlException::PI_DOCTYPE_EXPECTED, "Expected a processing instruction or doctype tag");
        XMLERRORCODE(Fl_XmlException::TAGNAME_EXPECTED, "Expected a tag name after '<' or '</'");
        XMLERRORCODE(Fl_XmlException::COMMENT_START_EXPECTED, "Expected '--' after comment '<!'");
        XMLERRORCODE(Fl_XmlException::COMMENT_END_MISSING, "Missing '-->' in comment");
        XMLERRORCODE(Fl_XmlException::SLASH_EXPECTED, "Expected a '/' after closing tag literal '<'");
        XMLERRORCODE(Fl_XmlException::TAGNAME_MISMATCH, "Tag name from start and end tag mismatch");
        XMLERRORCODE(Fl_XmlException::EQUAL_EXPECTED, "Expected '=' after attribute name");
        XMLERRORCODE(Fl_XmlException::VALUE_EXPECTED, "Expected value after 'a' in attribute");
    }
    return err;
}

Fl_String Fl_XmlException::text(bool short_version) const
{
    Fl_String ret;
	if(!short_version && locator()) 
		ret.printf("Error at line %d, position %d: (%s)", locator()->line(), locator()->col(), error_string(error()));
	else
		ret = error_string(error());
    return ret;
}
