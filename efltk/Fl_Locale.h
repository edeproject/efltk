#ifndef FL_LOCALE_H_
#define FL_LOCALE_H_

#ifndef _WIN32

#include "Fl_Export.h"

#include <locale.h>
#include <libintl.h>

# define _(String) gettext (String)
# ifdef gettext_noop
#  define N_(String) gettext_noop (String)
# else
#  define N_(String) (String)
# endif

extern void FL_API fl_init_locale_support(const char *, const char *);

#endif //_WIN32

#endif


