#ifndef _FL_LOCALE_H_
#define _FL_LOCALE_H_

#include "Fl.h"

#include <locale.h>

// THIS MUST BE CHANGED!
#ifndef _WIN32

#include <libintl.h>

# define _(String) gettext (String)
# ifdef gettext_noop
#  define N_(String) gettext_noop (String)
# else
#  define N_(String) (String)
# endif

#else

# define _(String)  (String)
# define N_(String) (String)

#endif

// Backward compatibilty
#define fl_init_locale_support(app, dir) Fl::init_locale(app, dir)

#endif
