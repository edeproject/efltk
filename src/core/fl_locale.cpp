#include <config.h>
#include "fl_internal.h"

void fl_init_locale_support(const char *package, const char *locale_prefix)
{
#if ENABLE_NLS
    // Initialize the i18n stuff
    setlocale(LC_ALL, "");
    bindtextdomain(package, locale_prefix);
    textdomain(package);
#endif
}

