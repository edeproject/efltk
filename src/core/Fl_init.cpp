
//
// Optional argument initialization code for the Extended Fast Light Tool Kit (EFLTK).
//
// Copyright 2002 by Mikko Lahteenmaki
//

// This call will load userinteface defaults from file.
// e.g. Does menus animate or not.
// This also initializes LOCALE support for EFLTK

#include <efltk/Fl.h>

#include <efltk/Fl_Image.h>
#include <efltk/Fl_Menu_Window.h>
#include <efltk/Fl_Tooltip.h>
#include <efltk/Fl_MDI_Window.h>

#include <efltk/Fl_Config.h>
#include "fl_internal.h"

void Fl::init()
{
    fl_init_locale_support("efltk", PREFIX"/share/locale");

    char *file = 0;
    file = Fl_Config::find_config_file("efltk.conf", false, Fl_Config::USER);
    if(!file) file = Fl_Config::find_config_file("efltk.conf", false, Fl_Config::SYSTEM);

    Fl_Config cfg(file, true, false);
    if(!cfg.error()) {

        bool b_val;
        int  i_val;
        float f_val;

        // Read Fl_Image defaults:
        cfg.get("Images", "State Effects", b_val, true);
        Fl_Image::state_effect_all(b_val);

        // Read Fl_Menu_Window defaults:
        cfg.get("Menus", "Animate", b_val, true);
        Fl_Menu_Window::animate(b_val);
        cfg.get("Menus", "Speed", i_val, 4);
        Fl_Menu_Window::default_step_div = i_val;

        // Read Fl_Tooltip defaults:
        cfg.get("Tooltips", "Animate", b_val, true);
        Fl_Tooltip::animate(b_val);
        cfg.get("Tooltips", "Enabled", b_val, true);
        Fl_Tooltip::enable(b_val);
        cfg.get("Tooltips", "Delay", f_val, 1.0f);
        Fl_Tooltip::delay(f_val);

        // Read Fl_MDI_Window defaults:
        cfg.get("MDI", "Animate", b_val, true);
        Fl_MDI_Window::animate(b_val);
        cfg.get("MDI", "Opaque", b_val, false);
        Fl_MDI_Window::animate_opaque(b_val);
    }
}