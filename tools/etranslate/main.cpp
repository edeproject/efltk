#include "etranslate.h"
#include "extract.h"
#include "compile.h"

#include <efltk/Fl_Translator.h>

Fl_String outfile;

bool show_help = false;

bool compile_only=false;
Fl_String compile_file;

bool extract_only=false;
bool extract_all=false;
Fl_String_List extract_files;

static int arg(int argc, char** argv, int& i)
{
    if((!strcmp("--help", argv[i]) ||
        (argv[i][1] == 'h' && !argv[i][2])) ) {
        i++;
        show_help = true;
        return 1;
    }
    if((!strcmp("--compile", argv[i]) ||
        (argv[i][1] == 'c' && !argv[i][2]))
       && i+1 < argc) {
        compile_only=true;
        compile_file = argv[i+1];
        i+=2;
        return 2;
    }
    if((!strcmp("--output", argv[i]) ||
        (argv[i][1] == 'o' && !argv[i][2]))
       && i+1 < argc) {
        outfile = argv[i+1];
        i+=2;
        return 2;
    }
    if(!strcmp("--extract", argv[i]) ||
       (argv[i][1] == 'e' && !argv[i][2])) {
        extract_only=true;
        i++;
        return 2;
    }
    if(!strcmp(argv[i], "-extract-all") ||
       !strcmp(argv[i], "-ea")) {
        extract_only=true;
        extract_all=true;
        i++;
        return 1;
    }
    if(argv[i][0] != '-') {
        if(extract_only) {
            extract_files.append(argv[i]);
            i++;
            return 1;
        }
    }
    return 0;
}

void show_help_()
{
    Fl::fatal("\n"
              "ETranslate - EFLTK Translator\n"
              "-----------------------------\n"
              "--extract, -e [files]        Extract strings from file(s)\n"
              "--extract-all, -ea [files]   Extract all strings from file(s)\n"
              "--compile, -c [file]         Compiles .etm file to .etb format\n"
              "--output, -o [file]          Output file, otherwise stdout\n"
              "--help, -h                   This message\n"
             );
}

int main(int argc, char *argv[])
{
    Fl::init_locale();
    ETranslate app;

    int i = 1;
    if(!Fl::args(argc,argv,i,arg) || i < argc-1) {
        show_help_();
    }

    if(show_help) show_help_();

    const char *file = argv[i];

    if(extract_only && extract_files.size()>0) {
        Extractor ext(outfile);
        ext.extract_files(extract_files, extract_all);
        return 1;
    } else if(compile_only) {
        Compiler comp;
        comp.compile(compile_file, outfile);
        return 1;
    }

    if(file) app.load(file);
    return Fl::run();
}
