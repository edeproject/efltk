#include "etranslate.h"

#include <ctype.h>

static int hexdigit(int x) {
    if(isdigit(x)) return x-'0';
    if(isupper(x)) return x-'A'+10;
    if(islower(x)) return x-'a'+10;
    return 20;
}

Fl_String& convert_quoted_controls(Fl_String str)
{
    static Fl_String ret;
    ret.clear();

    for(int n=0; n<str.length(); n++)
    {
        if(str[n]!='\\') {
            ret+=str[n];
            continue;
        }
        int c,d,x;
        switch(c = str[++n])
        {
        case 'a' : c='\a'; break;
        case 'b' : c='\b'; break;
        case 'f' : c='\f'; break;
        case 'n' : c='\n'; break;
        case 'r' : c='\r'; break;
        case 't' : c='\t'; break;
        case 'v' : c='\v'; break;

        case 'x' : /* read hex */
            for (c=x=0; x<3; x++) {
                int ch = str[++n];
                d = hexdigit(ch);
                if (d > 15) { n--; break; }
                c = (c<<4)+d;
            }
            break;

        default:		/* read octal */
            if (c<'0' || c>'7') break;
            c -= '0';
            for(x=0; x<2; x++) {
                int ch = str[++n];
                d = hexdigit(ch);
                if (d>7) { n--; break; }
                c = (c<<3)+d;
            }
            break;
        }
        ret += (char)c;
    }
    return ret;
}

Fl_String quote_controls(Fl_String str)
{
    Fl_String ret;
    for(int n=0; n<str.length(); n++)
    {
        char *c=0;
        switch(str[n])
        {
        case '\a' : c="\\a"; break;
        case '\b' : c="\\b"; break;
        case '\f' : c="\\f"; break;
        case '\n' : c="\\n"; break;
        case '\r' : c="\\r"; break;
        case '\t' : c="\\t"; break;
        case '\v' : c="\\v"; break;
        }
        if(c) ret += c;
        else ret += str[n];
    }
    return ret;
}

void ETranslate::load_etm(FILE *fp)
{
    try {
        Fl_XmlDoc *xml = Fl_XmlParser::create_dom(fp);
        Fl_XmlNode *node;
        node = xml->root_node()->child("Info");
        if(node) {
            Fl_XmlNode *tmp;
            tmp = node->child("Comment");
            if(tmp) tmp->text(comment);

            tmp = node->child("Project");
            if(tmp) tmp->text(name);

            tmp = node->child("Version");
            if(tmp) tmp->text(version);

            tmp = node->child("Language");
            if(tmp) tmp->text(lang);

            tmp = node->child("Translator");
            if(tmp) tmp->text(translator);

            tmp = node->child("Email");
            if(tmp) tmp->text(email);

            tmp = node->child("StartDate");
            if(tmp) tmp->text(start_date);

            tmp = node->child("ModifyDate");
            if(tmp) tmp->text(mod_date);

            if(start_date.length()==0)
                start_date = Fl_Date_Time::Now().date_string() + " " + Fl_Date_Time::Now().time_string();

            prj_output->value(name.c_str());
            lang_output->value(lang.c_str());
            trans_output->value(translator.c_str());
            email_output->value(email.c_str());
        }

        browser->begin();
        Fl_XmlNode_List nodes = xml->root_node()->nodes("String");
        for(uint n=0; n<nodes.size(); n++) {
            node = nodes[n];
            Fl_XmlNode *orig = node->child("Original", false);
            Fl_XmlNode *tr = node->child("Translation", false);
			Fl_String orig_text; orig->text(orig_text);
            if(!orig || orig_text=="") continue;

            TranslateItem *i = new TranslateItem();
            i->orig(convert_quoted_controls(orig_text));
            if(tr) {
				Fl_String tr_text;
                tr->text(tr_text);
                i->tr(convert_quoted_controls(tr_text));
            }

            i->finished((node->get_attribute("Finished")=="1"));
            node = node->child("Comment");
            if(node) {
				Fl_String comment_text;
                node->text(comment_text);
                i->comment(convert_quoted_controls(comment_text));
            }
        }
        browser->end();

		delete xml;

    } catch(Fl_Exception &exc) {
		Fl::warning(exc.text().c_str());
    }
}

void ETranslate::save_tag(FILE *fp, const Fl_String &str, const char *name)
{
	Fl_String wr;
	Fl_String ret;

	if(doctype.encode_entities(str, ret))
		wr = quote_controls(ret);		
	else
		wr = quote_controls(str);		

	fprintf(fp, "  <%s>%s</%s>\n", name, wr.c_str(), name);	
}

void ETranslate::save(const char *file)
{
    if(!file) {
        const char *f = fl_save_file(filename.c_str(),
                                     _("Translation Files, *.{etm|po|pot},"
                                       "Efltk Tr Files, *.etm,"
                                       "GNU gettext files, *.{po|pot}")
                                    );
        if(!f) return;
        file = f;
    }

    FILE *fp = fopen(file, "w");
    if(!fp) return;
    filename = file;

    mod_date = Fl_Date_Time::Now().date_string() + " " + Fl_Date_Time::Now().time_string();

    fprintf(fp, "<?xml version=\"1.0\"?>\n");
    fprintf(fp, "<Messages>\n");
    fprintf(fp, " <Info>\n");
    fprintf(fp, "  <Comment>%s</Comment>\n", comment.c_str());
    fprintf(fp, "  <Project>%s</Project>\n", name.c_str());
    fprintf(fp, "  <Version>%s</Version>\n", version.c_str());
    fprintf(fp, "  <Language>%s</Language>\n", lang.c_str());
    fprintf(fp, "  <Translator>%s</Translator>\n", translator.c_str());
    fprintf(fp, "  <Email>%s</Email>\n", email.c_str());
    fprintf(fp, "  <StartDate>%s</StartDate>\n", start_date.c_str());
    fprintf(fp, "  <ModifyDate>%s</ModifyDate>\n", mod_date.c_str());
    fprintf(fp, " </Info>\n\n");

    for(uint n=0; n<browser->children(); n++) {
        TranslateItem *i = (TranslateItem *)browser->child(n);

        fprintf(fp, " <String Finished=\"%d\">\n", i->finished());

		save_tag(fp, i->comment(), "Comment");
		save_tag(fp, i->orig(), "Original");
		save_tag(fp, i->tr(), "Translation");

        fprintf(fp, " </String>\n");
    }

    fprintf(fp, "</Messages>\n");

    fclose(fp);
}
