#ifndef _FL_TRANSLATOR_H_
#define _FL_TRANSLATOR_H_

#include "Fl_Export.h"
#include "Fl_String_List.h"
#include "Fl_Ptr_List.h"

class FL_API Fl_Translator
{
public:
    static char *tr(const char *string);
    static char *dtr(const char *domain, const char *string);

    static const char *load_translation_file(const char *desired_domain, const char *path);
    static const char *load_translation(const char *domainname);

    static bool has_search_path(const char *path);
    static void add_search_path(const char *path);
    static void remove_search_path(const char *path);

    // GNU gettext compatibility layer
    static char *bindtextdomain(const char *domainname, const char *dirname);
    static char *textdomain(const char *domainname);

private:
    Fl_Translator();
    ~Fl_Translator();

    static Fl_CString_List search_paths_;
    static Fl_Ptr_List catalogs_;
    static Fl_Translator translator;
};

#endif
