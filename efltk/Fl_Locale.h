#ifndef _FL_LOCALE_H_
#define _FL_LOCALE_H_

#include <locale.h>

#include "Fl.h"
#include "Fl_Translator.h"

# define _(String) Fl_Translator::tr(String)
# define N_(String) (String)

// Backward compatibilty
#define fl_init_locale_support(app, dir) Fl::init_locale(app, dir)

#endif
