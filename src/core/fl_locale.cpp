#include <config.h>
#include <efltk/Fl.h>
#include "fl_internal.h"

void fl_init_locale_support(const char *package, const char *locale_prefix)
{
    Fl::init();
#if ENABLE_NLS
    bindtextdomain(package, locale_prefix);
    textdomain(package);

    // Try to bind gettext to convert .po files automaticly to UTF-8
    // capabilities are checked in Fl::init();
    bind_textdomain_codeset(package, "UTF-8");
#endif
}

