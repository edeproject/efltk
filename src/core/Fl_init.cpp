
//
// Optional argument initialization code for the Extended Fast Light Tool Kit (EFLTK).
//
// Copyright 2002 by Mikko Lahteenmaki
//

// This call will load userinteface defaults from file.
// e.g. Does menus animate or not.

#include <efltk/Fl.h>

#include <efltk/Fl_Image.h>
#include <efltk/Fl_Menu_Window.h>
#include <efltk/Fl_Menu_.h>
#include <efltk/Fl_Tooltip.h>
#include <efltk/Fl_MDI_Window.h>

#include <efltk/Fl_Config.h>
#include "fl_internal.h"

#include <stdlib.h>

#ifdef _WIN32
# include <winsock.h>
#endif


void clean_up()
{
#ifdef _WIN32
    WSACleanup();
#endif
    // TODO:
    // Call some cleanup handlers!
}

void Fl::init()
{
    atexit(clean_up);

    char *file = 0;
    file = Fl_Config::find_config_file("efltk.conf", false, Fl_Config::USER);
    if(!file) file = Fl_Config::find_config_file("efltk.conf", false, Fl_Config::SYSTEM);

    Fl_Config cfg(file, true, false);
    if(!cfg.error()) {

        bool b_val;
        float f_val;
        int i_val;

        // Read Fl_Image defaults:
        cfg.get("Images", "State Effects", b_val, true);
        Fl_Image::state_effect_all(b_val);

        // Read Fl_Menu_Window defaults:
        cfg.get("Menus", "Effects", b_val, true);
        Fl_Menu_::effects(b_val);
        cfg.get("Menus", "Subwindow Effect", b_val, true);
        Fl_Menu_::subwindow_effect(b_val);
        cfg.get("Menus", "Effect Type", i_val, 1);
        Fl_Menu_::effect_type(i_val);
        cfg.get("Menus", "Speed", f_val, 1.5f);
        Fl_Menu_Window::default_anim_speed(f_val);
        cfg.get("Menus", "Delay", f_val, 0.2f);
        Fl_Menu_::default_delay(f_val);


        // Read Fl_Tooltip defaults:
        cfg.get("Tooltips", "Effects", b_val, true);
        Fl_Tooltip::effects(b_val);
        cfg.get("Tooltips", "Effect Type", i_val, 2);
        Fl_Tooltip::effect_type(i_val);
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

#ifdef _WIN32
	// WIN32 needs sockets to be initialized to get select funtion working...
	WSADATA wsaData;	
	WORD wVersionRequested = MAKEWORD( 2, 0 );
	int err = WSAStartup( wVersionRequested, &wsaData );
	if(err != 0) {
		Fl::warning("WSAStartup failed!");
	}
#endif
}
