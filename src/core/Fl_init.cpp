
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

// This allows static lib builds...
// widgets lib will use these as external variables.

bool im_state_effects = true;

bool menu_anim   = true;
float menu_speed = 4.0f;

bool mdi_anim        = true;
bool mdi_anim_opaque = false;

bool tt_anim    = true;
bool tt_enabled = true;
float tt_delay  = 1.0f;

void Fl::init()
{
    fl_init_locale_support("efltk", PREFIX"/share/locale");

    char *file = 0;
    file = Fl_Config::find_config_file("efltk.conf", false, Fl_Config::USER);
    if(!file) file = Fl_Config::find_config_file("efltk.conf", false, Fl_Config::SYSTEM);

    Fl_Config cfg(file, true, false);
    if(!cfg.error()) {

        // Read Fl_Image defaults:
        cfg.get("Images", "State Effects", im_state_effects, true);

        // Read Fl_Menu_Window defaults:
        cfg.get("Menus", "Animate", menu_anim, true);
        cfg.get("Menus", "Speed", menu_speed, 4);

        // Read Fl_Tooltip defaults:
        cfg.get("Tooltips", "Animate", tt_anim, true);
        cfg.get("Tooltips", "Enabled", tt_enabled, true);
        cfg.get("Tooltips", "Delay", tt_delay, 1.0f);

        // Read Fl_MDI_Window defaults:
        cfg.get("MDI", "Animate", mdi_anim, true);
        cfg.get("MDI", "Opaque", mdi_anim_opaque, false);
    }
}
