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
    Fl_String text;
    fl_try {
        Fl_XmlDoc xml(&ctx);
        xml.load(fp);
        Fl_XmlNode *node;
        node = xml.root_node()->child("Info");
        if(node) {
            Fl_XmlNode *tmp;
            tmp = node->child("Comment");
            if(tmp) comment = tmp->text();
            tmp = node->child("Project");
            if(tmp) name = tmp->text();
            tmp = node->child("Version");
            if(tmp) version = tmp->text();
            tmp = node->child("Language");
            if(tmp) lang = tmp->text();
            tmp = node->child("Translator");
            if(tmp) translator = tmp->text();
            tmp = node->child("Email");
            if(tmp) email = tmp->text();
            tmp = node->child("StartDate");
            if(tmp) start_date = tmp->text();
            tmp = node->child("ModifyDate");
            if(tmp) mod_date = tmp->text();

            if(start_date.length()==0)
                start_date = Fl_Date_Time::Now().date_string() + " " + Fl_Date_Time::Now().time_string();

            prj_output->value(name.c_str());
            lang_output->value(lang.c_str());
            trans_output->value(translator.c_str());
            email_output->value(email.c_str());
        }

        browser->begin();
        NodeList nodes = xml.root_node()->nodes("String");
        for(uint n=0; n<nodes.size(); n++) {
            node = nodes[n];
            Fl_XmlNode *orig = node->child("Original", false);
            Fl_XmlNode *tr = node->child("Translation", false);
            if(!orig || orig->text()=="") continue;

            TranslateItem *i = new TranslateItem();
            text = orig->text();
            i->orig(ctx.unXMLize(convert_quoted_controls(text)));
            if(tr) {
                text = tr->text();
                i->tr(ctx.unXMLize(convert_quoted_controls(text)));
            }

            i->finished((node->attribute("Finished")=="1"));
            node = node->child("Comment");
            if(node) {
                text = node->text();
                i->comment(ctx.unXMLize(convert_quoted_controls(text)));
            }
        }
        browser->end();

    } fl_catch(exc) {
        fl_alert(exc.text().c_str());
    }
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
        fprintf(fp, "  <Comment>%s</Comment>\n", quote_controls(ctx.XMLize(i->comment())).c_str());
        fprintf(fp, "  <Original>%s</Original>\n", quote_controls(ctx.XMLize(i->orig())).c_str());
        fprintf(fp, "  <Translation>%s</Translation>\n", quote_controls(ctx.XMLize(i->tr())).c_str());
        fprintf(fp, " </String>\n");
    }

    fprintf(fp, "</Messages>\n");

    fclose(fp);
}
