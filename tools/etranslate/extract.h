#ifndef _EXCTRACT_H_
#define _EXCTRACT_H_

#include "etranslate.h"

class Extractor
{
public:
    Extractor(Fl_String file) { outfile = file; }
    ~Extractor();

    void extract_files(Fl_String_List &files, bool all);
    void extract_file(Fl_String &file, bool all);

    void get_strings(const char *filename, FILE *fp, bool all);
    void add_string(Fl_String &str, Fl_String &comment);

    void print_xml(FILE *outfile);
	void print_tag(FILE *outfile, const Fl_String &str, const char *name);

    typedef struct {
        Fl_String str;
        Fl_String comment;
    } TrString;

    Fl_String outfile;
    Fl_Ptr_List list;
    Fl_XmlDocType doctype;
};

#endif
