#ifndef FL_LOCALE_H_
#define FL_LOCALE_H_

#ifndef _WIN32

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "Fl_Export.h"

#if ENABLE_NLS

#    include <libintl.h>
#    define _(String) gettext (String)
#    ifdef gettext_noop
#        define N_(String) gettext_noop (String)
#    else
#        define N_(String) (String)
#    endif

#else

/* Stubs that do something close enough.  */
#    define textdomain(String) (String)
#    define gettext(String) (String)
#    define dgettext(Domain,Message) (Message)
#    define dcgettext(Domain,Message,Type) (Message)
#    define bindtextdomain(Domain,Directory) (Domain)
#    define _(String) (String)
#    define N_(String) (String)

#endif

extern void FL_API fl_init_locale_support(const char *, const char *);

#endif //_WIN32

#endif


