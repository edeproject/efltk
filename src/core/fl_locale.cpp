#ifndef _WIN32

#include <efltk/Fl_Locale.h>

void fl_init_locale_support(const char *package, const char *locale_prefix)
{
#ifdef ENABLE_NLS
    // Initialize the i18n stuff
    setlocale(LC_ALL, "");
    bindtextdomain(package, locale_prefix);
    textdomain(package);
#endif
}

#endif

