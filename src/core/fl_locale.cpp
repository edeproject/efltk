#include <config.h>

#include <efltk/Fl.h>
# include <efltk/x.h>
#include "fl_internal.h"

#ifndef _WIN32
# include <X11/Xlocale.h>
#endif

#if NO_BIND_TEXTDOMAIN_CODESET_DECLARATION
extern "C" {
    extern char *bind_textdomain_codeset(const char *__domainname,
                                         const char *__codeset);
};
#endif

// This is used on future...
bool fl_gettext_utf8 = false;

static void set_locale()
{
    char *current_locale;
    static char *last_locale = 0;

    // Initialize the i18n stuff
    current_locale = setlocale(LC_ALL, "");

    if(!current_locale)
        Fl::warning("Locale not supported by C library, using default");

    if(last_locale && current_locale && !strcmp(last_locale, current_locale))
        return;

    if(last_locale) delete []last_locale;
    if(current_locale) last_locale = strdup(current_locale);
    else last_locale = strdup("C");

#ifndef _WIN32
    if(!XSupportsLocale())
        Fl::warning("Locale not supported by Xlib");
    if(!XSetLocaleModifiers(""))
        Fl::warning ("Cannot XLib set locale modifiers");
#endif
}

bool Fl::init_locale()
{
    set_locale();
#if ENABLE_NLS

    static bool inited=false;
    if(!inited) {
        bindtextdomain("efltk", PREFIX"/share/locale");
#if HAVE_TEXTDOMAIN_CODESET
        char *charset = bind_textdomain_codeset("efltk", "UTF-8");
        if(charset && !strcmp(charset, "UTF-8"))
            fl_gettext_utf8 = true;
#endif
        inited=true;
    }
    return true;
#else
    return false;
#endif
}

bool Fl::init_locale(const char *app_domain, const char *directory)
{
    set_locale();
#if ENABLE_NLS
    // App specific:
    if(app_domain) {
        bindtextdomain(app_domain, directory);
        textdomain(app_domain);

#if HAVE_TEXTDOMAIN_CODESET
        //Set conversions:
        bind_textdomain_codeset(app_domain, "UTF-8");
#endif
    }
    return Fl::init_locale();
#else
    return false;
#endif
}
