
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

# ifndef SPI_GETMENUANIMATION
#  define SPI_GETMENUANIMATION                0x1002
# endif
# ifndef SPI_GETCOMBOBOXANIMATION
#  define SPI_GETCOMBOBOXANIMATION            0x1004
# endif
# ifndef SPI_GETMENUFADE
#  define SPI_GETMENUFADE                     0x1012
# endif
# ifndef SPI_GETTOOLTIPFADE
#  define SPI_GETTOOLTIPFADE                  0x1018
# endif
# ifndef SPI_GETTOOLTIPANIMATION
#  define SPI_GETTOOLTIPANIMATION             0x1016
# ifndef SPI_GETMENUSHOWDELAY
#  define SPI_GETMENUSHOWDELAY       0x006A
# endif
# endif

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
    if(0) {//!cfg.error()) {

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
        Fl_Menu_::default_effect_type(i_val);
        cfg.get("Menus", "Speed", f_val, 1.5f);
        Fl_Menu_::default_anim_speed(f_val);
        cfg.get("Menus", "Delay", f_val, 0.3f);
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
	else {

		// Get system defaults, if efltk configfile NOT found

		bool menu_anim=false, menu_fade=false, tooltip_anim=false, tooltip_fade=false;
	
		SystemParametersInfo(SPI_GETMENUANIMATION, 0, (PVOID)&menu_anim, 0);		
		if(menu_anim) {
			SystemParametersInfo(SPI_GETMENUFADE, 0, (PVOID)&menu_fade, 0);
		}
		
		SystemParametersInfo(SPI_GETTOOLTIPANIMATION, 0, (PVOID)&tooltip_anim, 0);
		if(tooltip_anim) {
			SystemParametersInfo(SPI_GETTOOLTIPFADE, 0, (PVOID)&tooltip_fade, 0);
		}

		Fl_Menu_::effects(menu_anim);
		if(menu_fade) Fl_Menu_::default_effect_type(FL_EFFECT_FADE);
		else Fl_Menu_::default_effect_type(FL_EFFECT_ANIM);

		Fl_Tooltip::effects(tooltip_anim);
		if(tooltip_fade) Fl_Tooltip::effect_type(FL_EFFECT_FADE);
		else Fl_Tooltip::effect_type(FL_EFFECT_ANIM);

		DWORD menu_delay;
		SystemParametersInfo(SPI_GETMENUSHOWDELAY, 0, (PVOID)&menu_delay, 0);		        
		double del = (double)menu_delay/1000;
		Fl_Menu_::default_delay(del);
	}

	// WIN32 needs sockets to be initialized to get select funtion working...
	WSADATA wsaData;	
	WORD wVersionRequested = MAKEWORD( 2, 0 );
	int err = WSAStartup( wVersionRequested, &wsaData );
	if(err != 0) {
		Fl::warning("WSAStartup failed!");
	}


#endif
}
