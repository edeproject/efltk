#ifndef _COMPILE_H_
#define _COMPILE_H_

#include "etranslate.h"

class Compiler
{
public:
    Compiler() { }

    void save_hash(Fl_XmlNode *root, FILE *outfp);
    void compile(Fl_String infile, Fl_String outfile);

    static void compile(FILE *fp, uint numstrings, Fl_Int_List &lengths, Fl_String_List &strings);

    Fl_XmlDoc xml;
};

#endif
