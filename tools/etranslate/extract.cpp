#include "extract.h"

Extractor::~Extractor()
{
    TrString *t;
    for(uint n=0; n<list.size(); n++) {
        t = (TrString*)list[n];
        delete t;
    }

}

void Extractor::add_string(Fl_String &str, Fl_String &comment)
{
    TrString *t;
    for(uint n=0; n<list.size(); n++) {
        t = (TrString*)list[n];
        if(t->str==str) {
            t->comment += " " + comment;
            return;
        }
    }

    t = new TrString;
    t->str = str;
    t->comment = comment;
    list.append(t);
}

#define inc_line() if(c=='\n') line++
#define read_to_c(ch) while(!feof(fp) && c!=ch) c=fgetc(fp)
#define end_cmp(str, len) (token.length()>=len && !strncmp(&token[token.length()-len], str, len))

void Extractor::get_strings(const char *filename, FILE *fp, bool all)
{
    int line=1;
    Fl_String str, token;
    int c=0;
    bool skip=false;
    bool inside_comment=false;
    bool translate=false;

    while(!feof(fp)) {
        if(c==0) c = fgetc(fp);
        token += c;
        inc_line();

        if(!inside_comment && c=='\n') {
            token.clear(); c=0;
            continue;
        }

        // Check for directives and comment line "//"
        if(!inside_comment && (token=="#" || end_cmp("//", 2)))
        {
            read_to_c('\n');
            token.clear();
            continue;
        }

        // Check for "/*" comment start
        if(!inside_comment && end_cmp("/*", 2))
        {
            inside_comment=true;
            c=0;
            continue;
        }

        // Check for "*/" comment end
        if(inside_comment && end_cmp("*/", 2))
        {
            inside_comment=false;
            token.clear(); c=0;
            continue;
        }

        // Found string start
        if(!inside_comment && !skip && c=='\"')
        {
            translate=false;

            if(end_cmp("N_(\"", 4) || end_cmp("_(\"", 3))
                translate = true;

            if(all) translate=true;

            str.clear(); //Clear string
            int str_line = line;
        AGAIN:
            skip=false;
            // Find string end
            while(!feof(fp)) {
                c=fgetc(fp);
                inc_line();

                if(!skip && c=='\"') {
                    // Quote
                    while(!feof(fp)) {
                        c = fgetc(fp);
                        inc_line();

                        if(c==' ' || c=='\t' || c=='\n')
                            continue;
                        else if(c=='\"')
                            goto AGAIN; //Multi-line string
                        else
                            break; //End of string
                    }
                    break;
                } else {
                    bool was_skip = skip;
                    skip = c=='\\'; // Skip char after control char
                    if(was_skip && c=='\n')
                        str.sub_delete(str.length()-1, 1); //Only line change
                    else
                        str += c;
                }
            }

            if(translate && str.length()>0) {
                Fl_String comment = Fl_String(filename) + ":" + Fl_String(str_line);
                add_string(str, comment);
            }
            continue;
        }
        skip = c=='\\'; // Skip control chars
        c=0;
    }
}

void Extractor::extract_files(Fl_String_List &glob_files, bool all)
{
    for(uint f=0; f<glob_files.size(); f++) {
        Fl_String filename = glob_files[f];
        FILE *fp = fopen(filename.c_str(), "r");
        if(fp) {
            get_strings(filename.c_str(), fp, all);
            fclose(fp);
        }
    }

    FILE *fp = fopen(outfile.c_str(), "w");
    if(fp) {
        print_xml(fp);
        fclose(fp);
    } else
        print_xml(stdout);
}

Fl_String& normalize(const Fl_String &str)
{
    static Fl_String ret;
    ret.clear();

    for(int n=0; n<str.length(); n++) {
        switch(str[n]) {
        case '\\': if(n+1<str.length() && (str[n+1]=='\'' || str[n+1]=='\"')) break;
        default:
            ret += str[n];
            break;
        }
    }
    return ret;
}

void Extractor::print_tag(FILE *outfile, const Fl_String &str, const char *name)
{
	Fl_String &norm = normalize(str);
	Fl_String ret;

	if(doctype.encode_entities(norm, ret)) {
		fprintf(outfile, "  <%s>%s</%s>\n", name, ret.c_str(), name);
	} else {
		fprintf(outfile, "  <%s>%s</%s>\n", name, norm.c_str(), name);
	}	
}

void Extractor::print_xml(FILE *outfile)
{
    Fl_String date = Fl_Date_Time::Now().date_string() + " " + Fl_Date_Time::Now().time_string();

    fprintf(outfile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(outfile, "<Messages>\n");
    fprintf(outfile, " <Info>\n");
    fprintf(outfile, "  <Comment>Translation for ...</Comment>\n");
    fprintf(outfile, "  <Project>Project Name</Project>\n");
    fprintf(outfile, "  <Version>0.0</Version>\n");
    fprintf(outfile, "  <Language>Default</Language>\n");
    fprintf(outfile, "  <Translator>None</Translator>\n");
    fprintf(outfile, "  <Email>example@mail.com</Email>\n");
    fprintf(outfile, "  <StartDate>%s</StartDate>\n", date.c_str());
    fprintf(outfile, "  <ModifyDate>%s</ModifyDate>\n", date.c_str());
    fprintf(outfile, " </Info>\n\n");

    TrString *t;
    for(uint n=0; n<list.size(); n++)
    {
        t = (TrString*)list[n];

		fprintf(outfile, " <String Finished=\"0\">\n");

        print_tag(outfile, t->comment, "Comment");
		print_tag(outfile, t->str, "Original");
		print_tag(outfile, t->str, "Translation");
        
        fprintf(outfile, " </String>\n");
    }

    fprintf(outfile, "</Messages>\n");
}


