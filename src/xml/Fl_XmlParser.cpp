#include <config.h>

#include <efltk/Fl_Exception.h>
#include <efltk/xml/Fl_XmlParser.h>
#include <efltk/xml/Fl_XmlCtx.h>
#include <efltk/xml/Fl_XmlDoc.h>
#include <efltk/xml/Fl_XmlNode.h>

#include <ctype.h>

///////////////////////////
// BEGIN OF HTML GLOBALS //
///////////////////////////

// HTML "leaf" tags
char *html_leaf_tags[] = {	
    "br",
    "hr",
    "img",
    "meta",
    0
};
// All %blocklevel tags
char *html_block_tags[] = {
    "p",
    "h1",
    "h2",
    "h3",
    "h4",
    "h5",
    "h6",
    "ul",
    "ol",
    "dl",
    "dt",
    "dd",
    "dir",
    "div",
    "pre",
    "menu",
    "form",
    "table",
    "center",
    "isindex",
    "address",
    "noscript",
    "noframes",
    "fieldset",
    "blockquote",
    0
};

bool is_html_leaf(Fl_String &tag) {
    for(int n=0; html_leaf_tags[n]; n++) {
        if(!strcasecmp(html_leaf_tags[n], tag.c_str()))
            return true;
    }
    return false;
}
bool is_html_block(Fl_String &tag) {
    for(int n=0; html_block_tags[n]; n++) {
        if(!strcasecmp(html_leaf_tags[n], tag.c_str()))
            return true;
    }
    return false;
}

///////////////////////////
// END OF HTML GLOBALS ////
///////////////////////////

// xmlparser methods
Fl_XmlParser::Fl_XmlParser(Fl_XmlContext *ctx, Fl_XmlTokenizer &tok)
: tokenizer(tok), ctxptr(ctx)
{
}

void Fl_XmlParser::throw_error(int error)
{
    ctxptr->lasterror_ = error;
    fl_throw(ctxptr->error_string(error));
}

bool Fl_XmlParser::parse_document(Fl_XmlDoc &doc)
{
    if(!parse_header(doc))
        return false;

    // start parsing the content of file
    if(ctxptr->handle_events())
        ctxptr->handler()->start_document(doc.dtd_type(), doc.dtd_location(), doc.dtd_uri());

    // parse the only one subnode
    Fl_XmlNode *subnode = 0;
    if(ctxptr->store_tree()) subnode = new Fl_XmlNode(ctxptr);

    int ret = parse_node(subnode);

    // if successful, put node into nodelist
    if(ctxptr->store_tree()) {
        if(ret==1) {
            doc.add_child( subnode );
        } else {
            delete subnode;
        }
    }

    if(ctxptr->handle_events())
        ctxptr->handler()->end_document();

    return (ret==1);
}

// parses the doctype
bool Fl_XmlParser::parse_doctype(Fl_XmlDoc &doc)
{
    Fl_String token;

    for(int n=0; n<3; n++) {
        token = *tokenizer++;
        if(tokenizer.eos()) {
            //un-expected end of file!
            return false;
        }
        if(token=='[') {
            tokenizer.put_back();
            break;
        }
        if(token=='>')
            return true;

        //Strip quotes
        if(token[0]=='\"' && token[token.length()-1]=='\"') {
            token.sub_delete(0,1);
            token.sub_delete(token.length()-1,1);
        }

        doc.dtds[n] = token;
    }

    do { // read the complete tag till the closing '>'
        token = *tokenizer++;
        if(token == "[") {
            Fl_String tmp = *tokenizer++;
            do {
                if(tmp == '<') {
                    tmp = *tokenizer++;
                    if(tmp == '!') {
                        tmp = *tokenizer++;
                        if(tmp == "ENTITY") {
                            Fl_String key, val;

                            tmp = *tokenizer++;
                            if(tmp == "%") {
                                continue; //Can't handle it...
                            }

                            //key = "&" + tmp + ";";
                            key = tmp;

                            tmp = *tokenizer++;
                            // remove quotes from attribute value
                            for(int n=0; n<tmp.length(); n++)
                                if(tmp[n] != '\"' && tmp[n] != '\'')
                                    val += tmp[n];

                            ctxptr->entity_map().append_pair(EntityMap::pair(key, val));

                            tmp = *tokenizer++;
                            if(tmp != '>') {
                                throw_error(FL_XML_CLOSETAG_EXPECTED);
                                return false;
                            }
                        } else if(tmp[0]=='-' && tmp[1]=='-') {
                            //COMMENT??
                            tokenizer.put_back();
                            Fl_XmlNode *com_node = 0;
                            if(ctxptr->store_tree()) com_node = new Fl_XmlNode(ctxptr);
                            if(!parse_comment(com_node)) {
                                delete com_node;
                                return false;
                            }
                            doc.add_child(com_node);
                        }
                    }
                }
                tmp = *tokenizer++;
            } while(tmp != "]" || tokenizer.eos());
            token = *tokenizer++; //Jump to ']'
            break;
        }
    } while(token != '>');

    if(token != '>') {
        throw_error(FL_XML_CLOSETAG_EXPECTED);
        return false;
    }

    return true;
}

// parses the header, i.e. processing instructions and doctype tag
bool Fl_XmlParser::parse_header(Fl_XmlDoc &doc)
{
    while(true)
    {
        Fl_String token1 = *tokenizer++;
        if(token1 != '<') {
            throw_error(FL_XMP_OPENTAG_EXPECTED);
            return false;
        }

        // token after opening < is a literal?
        Fl_String token2 = *tokenizer++;
        if(!is_literal(token2)) {
            //generic Fl_String encountered: assume no pi and doctype tags
            tokenizer.put_back();
            tokenizer.put_back(token1);
            return true;
        }

        // now check for the literal
        switch(literal(token2))
        {
            // comment or doctype tag
        case '!': {
            Fl_String token3 = *tokenizer++;
            if(!is_literal(token3))
            {
                // now a doctype tag or a comment may follow
                if(token3[0] == '-' && token3[1] == '-') {
                    tokenizer.put_back();
                    Fl_XmlNode *com_node = 0;
                    if(ctxptr->store_tree()) com_node = new Fl_XmlNode(ctxptr);
                    if(!parse_comment(com_node)) {
                        delete com_node;
                        return false;
                    }
                    doc.add_child(com_node);
                }
                else
                {
                    /* transform to upper */
                    Fl_String doctypestr = token3.upper_case();

                    if(doctypestr == "DOCTYPE") {
                        if(!parse_doctype(doc))
                            return false;
                    } else {
                        throw_error(FL_XML_PI_DOCTYPE_EXPECTED);
                        return false;
                    }
                }
            } else {
                throw_error(FL_XML_PI_DOCTYPE_EXPECTED);
                return false;
            }
            break;
        }

        case '?': {
            Fl_String token = *tokenizer++;
            if(is_literal(token)) {
                throw_error(FL_XML_PI_DOCTYPE_EXPECTED);
                return false;
            }

            // parse processing instruction
            Fl_XmlNode *pinode = new Fl_XmlNode(ctxptr);
            pinode->parent(&doc);
            Fl_String tagname( token );
            pinode->nodenamehandle_ = ctxptr->insert_tagname( tagname );

            parse_attributes( &pinode->attributes() );

            doc.procinstructions_.append( pinode );

            if(ctxptr->handle_events()) ctxptr->handler()->processing_instruction(*pinode);

            if(*tokenizer++ != '?') {
                throw_error(FL_XML_PI_DOCTYPE_EXPECTED);
                return false;
            }

            if(*tokenizer++ != '>') {
                throw_error(FL_XML_CLOSETAG_EXPECTED);
                return false;
            }

            break;
        }

        default:
            // unknown literal encountered
            throw_error(FL_XML_PI_DOCTYPE_EXPECTED);
            return false;

        } // end switch
    } // end while

    return true;
}

// parses the contents of the current node
int Fl_XmlParser::parse_node(Fl_XmlNode *node)
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
        if(!is_literal(token1))
        {
            Fl_String *cdata_pointer;
            if(ctxptr->store_tree()) {
                cdata_pointer = &node->cdata();
                node->nodenamehandle_ = ctxptr->insert_tagname("cdata");
                node->type(FL_XML_TYPE_CDATA);
            } else {
                static Fl_String temp_cdata;
                cdata_pointer = &temp_cdata;
            }
            Fl_String &cdata = *cdata_pointer;

            // parse cdata section and return as new node.
            cdata.clear();

            while(!tokenizer.eos() && !is_literal(token1)) {
                cdata += token1;
                token1 = *tokenizer++;
            }
            tokenizer.put_back();

            if(ctxptr->handle_events()) ctxptr->handler()->cdata(cdata);
            return true;
        }

        // no cdata, try to continue parsing node content
        if(token1 != '<') {
            throw_error(FL_XML_OPENTAG_CDATA_EXPECTED);
            return false; // Open tag expected
        }

        // get node name
        token2 = *tokenizer++;
        if(is_literal(token2)) {
            // check the following literal
            switch(literal(token2))
            {
            case '/': { // closing '</...>' follows
                // return, we have a closing node with no more content
                tokenizer.put_back();
                tokenizer.put_back( token1 );
                return false;
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
                        if(ctxptr->store_tree()) {
                            cdata_pointer = &node->cdata();
                            node->nodenamehandle_ = ctxptr->insert_tagname("cdata");
                            node->type(FL_XML_TYPE_CDATA_SECTION);
                        } else {
                            static Fl_String temp_cdata;
                            cdata_pointer = &temp_cdata;
                        }

                        Fl_String &cdata = *cdata_pointer;
                        // parse cdata section and return as new node.
                        cdata.clear();

                        tokenizer.cdata_mode(true);
                        while(!tokenizer.eos()) {
                            cdata += *tokenizer++;
                            if(!strncmp(&cdata[cdata.length()-3], "]]>", 3))
                                break;
                        }
                        tokenizer.cdata_mode(false);

                        cdata.sub_delete(cdata.length()-3, 3); //Delete "]]>"

                        if(ctxptr->handle_events()) ctxptr->handler()->cdata(cdata);
                        return true;
                    }

                    // Skip to next literal, cant do anything with this data :(
                    while(!tokenizer.eos() && !is_literal(*tokenizer++));
                    token1 = *tokenizer++;
                }

                // parse again, until we encounter some useful data
                again = true;
            }
            break;

            default:
                throw_error(FL_XML_TAGNAME_EXPECTED);
                return false; // Tagname expected
            }
        }
    } while(again);

    // Store tagname
    Fl_String tagname( token2 );
    // insert tag name and set handle for it
    if(node) node->nodenamehandle_ = ctxptr->insert_tagname( tagname );

    // HMTL
    if(ctxptr->html_mode())
    {
        // Check for endless blocks, w/o end tag
        /*Fl_String name = node->parent()->name();
         if(is_html_block(name)) {
         if(is_html_block(tagname)) {
         tokenizer.put_back(token2);
         tokenizer.put_back(token1);
         if(handle) ctxptr->handler()->end_node(name);
         return true;
         }
         }*/
    }

    // notify event handler
    if(ctxptr->handle_events()) ctxptr->handler()->start_node(tagname);
    //printf("START %s\n", tagname.c_str());

    // parse attributes
    AttrMap *map;
    if(ctxptr->store_tree())
        map = &node->attributes();
    else {
        static AttrMap temp_map;
        temp_map.clear();
        map = &temp_map;
    }
    if(!parse_attributes(map))
        return false;

    if(ctxptr->handle_events()) ctxptr->handler()->parsed_attributes(tagname, *map);

    // check for leaf
    token1 = *tokenizer++;

    // HMTL, check for leafs
    if(ctxptr->html_mode()) {
        if(is_html_leaf(tagname)) {
            //tokenizer.put_back(token1);
            if(node) node->type(FL_XML_TYPE_LEAF);
            if(ctxptr->handle_events()) ctxptr->handler()->end_node(tagname);
            return true;
        }
    }

    // XML
    if(token1 == '/') {
        // node has finished
        token2 = *tokenizer++;
        if(token2 != '>' ) {
            throw_error(FL_XML_CLOSETAG_EXPECTED);
            return false; // Close Tag expected
        }

        if(node) node->type(FL_XML_TYPE_LEAF);
        if(ctxptr->handle_events()) ctxptr->handler()->end_node(tagname);

        // return, let the caller continue to parse
        return true;
    }

    // now a closing bracket must follow
    if(token1 != '>') {
        throw_error(FL_XML_CLOSETAG_EXPECTED);
        return false; // Close Tag expected
    }

    // loop to parse all subnodes
    Fl_XmlNode *subnode = 0;
    while(true) {

        if(!subnode && ctxptr->store_tree()) {
            subnode = new Fl_XmlNode(ctxptr);
            subnode->parent(node);
        }

        if(parse_node(subnode)) {
            if(subnode && ctxptr->store_tree()) {
                node->add_node(subnode);
                subnode = 0;
            }
        } else {
            break;
        }
    }
    if(subnode)
        delete subnode;

    if(ctxptr->lasterror_)
        return false;

    // parse end tag
    Fl_String token5 = *tokenizer++;
    tokenizer++;
    if(token5 != '<' && *tokenizer != '/') {
        throw_error(FL_XMP_OPENTAG_EXPECTED);
        return false;
    }

    tokenizer++;
    token1 = *tokenizer;
    if(is_literal(token1)) {
        throw_error(FL_XML_TAGNAME_EXPECTED);
        return false;
    }

    // check if open and close tag names are identical
    if(token1 != token2) {
        throw_error(FL_XML_TAGNAME_MISMATCH);
        return false;
    }

    tokenizer++;
    if (*tokenizer != '>') {
        throw_error(FL_XMP_OPENTAG_EXPECTED);
        return false;
    }

    if(ctxptr->handle_events()) ctxptr->handler()->end_node(token1);

    return true;
}

// parses tag attributes
bool Fl_XmlParser::parse_attributes(AttrMap *attr)
{
    Fl_String token1;
    Fl_String name, value;
    while(true) {

        token1 = *tokenizer++;

        if(is_literal(token1)) {
            tokenizer.put_back();
            return true;
        }

        // Get name (key)
        name.clear();
        name = token1;

        token1 = *tokenizer++;
        if(token1 != '=') {
            if(ctxptr->html_mode()) {
                tokenizer.put_back();
                Fl_String str = Fl_String();
                attr->append_pair(AttrMap::pair(name, str));
                return true;
            } else {
                throw_error(FL_XML_EQUAL_EXPECTED);
                return false; // '=' expected: key=value
            }
        }

        token1 = *tokenizer++;
        if(is_literal(token1)) {
            throw_error(FL_XML_VALUE_EXPECTED);
            return false;
        }

        // remove quotes from attribute value
        value.clear();
        Fl_String tmp = token1;
        for(int n=0; n<tmp.length(); n++)
            if(tmp[n] != '\"' && tmp[n] != '\'')
                value += tmp[n];

        // insert attribute into the map
        attr->append_pair(AttrMap::pair(name, value));
    }
    return true;
}

bool Fl_XmlParser::parse_comment(Fl_XmlNode *node)
{
    Fl_String part;
    Fl_String comment;

    tokenizer.cdata_mode(true);
    while(true) {
        if(tokenizer.eos()) {
            throw_error(FL_XML_COMMENT_END_MISSING);
            return false;
        }

        tokenizer++;
        if(part[part.length()-1]=='-' && part[part.length()-2]=='-') {
            if(*tokenizer == '>')
                break;
        }

        part = *tokenizer;

        if( comment.length()==0 && (part[0]!='-' || part[1]!='-') ) {
            throw_error(FL_XML_COMMENT_START_EXPECTED);
            return false;
        }

        comment+=part;
    }
    tokenizer.cdata_mode(false);

    comment.sub_delete(0, 2);
    comment.sub_delete(comment.length()-2, 2);
    if(node && ctxptr->store_tree())
    {
        node->cdata(comment.trim());
        Fl_String tagname("comment");
        node->nodenamehandle_ = ctxptr->insert_tagname( tagname );
        node->type(FL_XML_TYPE_COMMENT);

        if(ctxptr->handle_events())
            ctxptr->handler()->comment(node->cdata());

    } else {

        if(ctxptr->handle_events())
            ctxptr->handler()->comment(comment);
    }

    return true;
}

