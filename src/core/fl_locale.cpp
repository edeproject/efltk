#include <config.h>

#include <efltk/Fl.h>
# include <efltk/x.h>
#include "fl_internal.h"

#ifndef _WIN32
# include <X11/Xlocale.h>
#endif

char *last_locale = 0;

static void set_locale()
{
    char *current_locale;
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

extern char *get_sys_dir();
bool Fl::init_locale()
{
    set_locale();
#if ENABLE_NLS
    static bool inited=false;
    if(!inited) {
#ifdef _WIN32
		Fl_String path(get_sys_dir());
		path += "/locale";
		Fl_Translator::bindtextdomain("efltk", path);
#else
        Fl_Translator::bindtextdomain("efltk", PREFIX"/share/locale");
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
        Fl_Translator::bindtextdomain(app_domain, directory);
        //textdomain(app_domain);
    }
    return Fl::init_locale();
#else
    return false;
#endif
}
