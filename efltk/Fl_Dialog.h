/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Alexey Parshin
 * Email  : alexey@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_DIALOG_H_
#define _FL_DIALOG_H_

#include "Fl_Window.h"
#include "Fl_Scroll.h"
#include "Fl_Widget_List.h"
#include "Fl_Variant.h"
#include "Fl_Pixmap.h"

#include "Fl_Dialog_DS.h"

class Fl_Button;
class Fl_Tabs;

/**
 * The Fl_Dialog is standard dialog window for eFLTK.
 * Idea is to provide standard look and feel for all dialogs in application.
 */
class FL_API Fl_Dialog : public Fl_Window {
public:
    /**
     * Constructs empty dialog with give size.
     * @param label caption of dialog window
     * @param ds pointer to external datasource, if NULL default is used.
     */
    Fl_Dialog(int w, int h, const char *label=0, Fl_Data_Source *ds=0);

    /**
     * Destroys dialog, frees resources.
     */
    ~Fl_Dialog();

    /**
     * Button ID's for Fl_Dialog
     */
    enum ButtonTypes {
        BTN_OK      = 1,   /**< Ok button */
        BTN_CANCEL  = 2,   /**< Cancel button */
        BTN_YES     = 4,   /**< Yes button */
        BTN_NO      = 8,   /**< No button */
        BTN_RETRY   = 16,  /**< Retry button */
        BTN_REFRESH = 32,  /**< Refresh button */
        BTN_CONFIRM = 64,  /**< Confirm button */
        BTN_IGNORE  = 128, /**< Ignore button */
        BTN_HELP    = 256  /**< Help button */
    };

    /**
     * Load dialog widget values from datasource.
     *
     * @param ds as external datasource. If ds is NULL, dialog default datasource is used.
     * @see Fl_Widget::load_data(Fl_Data_Source *ds=0)
     * @see Fl_Group::load_data(Fl_Data_Source *ds=0)
     */
    virtual bool  load_data(Fl_Data_Source *ds=0);

    /**
     * Save dialog widget values to datasource.
     *
     * This function is called from 'Ok' button callback.
     * If return value is true (data saved) the dialog will be closed. 
     *
     * @param ds as external datasource. If ds is NULL, dialog default datasource is used.
     * @see Fl_Widget::save_data(Fl_Data_Source *ds=0)
     * @see Fl_Group::save_data(Fl_Data_Source *ds=0)
     */
    virtual bool  save_data(Fl_Data_Source *ds=0);

    /**
     * This function is designed to access the values in widgets
     * that have field_name() defined, after the save_data() is
     * successfully called and dialog is closed.
     *
     * @return Fl_Variant for field_name.
     * @see test/dialog.cpp
     */
    const Fl_Variant& operator [] (const char *field_name) const;

    /**
     * This function is designed to access the values in widgets
     * that have field_name() defined, after the save_data() is
     * successfully called and dialog is closed.
     *
     * @return Fl_Variant for field_name.
     * @see test/dialog.cpp
     */
    Fl_Variant& operator [] (const char *field_name);

    /**
     * Show dialog as application modal window.
     * @return ID of button pressed
     */
    int show_modal();

    /**
     * This function emulates user button click. 
     * It is 100% same to click CANCEL button in dialog or call submit(Fl_Dialog::BTN_CANCEL);
     *
     * @param button_id for button to submit e.g. Fl_Dialog::BTN_OK
     */
    void submit(int button_id);

    /**
     * Set buttons to dialog, For OK and CANCEL it is:
     * buttons(Fl_Dialog::BTN_OK | Fl_Dialog::BTN_CANCEL, Fl_Dialog::BTN_OK);<BR>
     * Default button has double border.
     *
     * @param buttons_mask bitmask for buttons
     * @param default_button for dialog
     */
    void buttons(int buttons_mask, int default_button);

    /**
     * Enable or disable buttons in dialog. 
     * @note If button is disabled, user cannot click it!
     *
     * @param button_id for button to enable/disable e.g. Fl_Dialog::BTN_OK
     * @param enable whether button should be activated or de-activated
     */
    void enable_button(int button_id, bool enable=true);

    /**
     * Removes all buttons from dialog button group.
     */
    void clear_buttons();

    /**
     * Adds user-defined button to the dialog.
     * The size of the pixmap should be 20x20 or less to conform with the
     * existing dialog buttons and the rest of the system. The id of the
     * button must be greater than BTN_HELP, and unique in the button
     * list for the dialog. If any of these conditions is violated - the
     * exception is thrown. This enforces the dialogs in the system to 
     * more or less standard.
     */
    void user_button(int button_id, Fl_String label, Fl_Pixmap *pixmap=NULL);

    /**
     * Add new scrollable page to dialog.
     * Returns new scroll group.
     *
     * @param label for tab
     */
    Fl_Scroll   *new_scroll(const char *label);

    /**
     * Same as new_scroll(const char *label)
     * @see new_scroll(const char *label)
     */
    Fl_Group    *new_page(const char *label) { return (Fl_Group*)new_scroll(label); }

    /**
     * Add new NON-scrollable page to dialog.
     * Returns new group.
     *
     * @param label for tab
     */
    Fl_Group    *new_group(const char *label);

    /**
     * Internal handle.
     * @see Fl_Widget::handle(int event)
     */
    virtual int handle(int event);

protected:

    /**
     * Returns widget for given field_name, returns NULL if not found.
     */
    Fl_Widget *find_widget(const char *field_name) const;

    /** Internal callback for default dialog buttons */ 
    static void buttons_callback(Fl_Button *btn, long id);

    Fl_Tabs        *m_tabs;

private:
    typedef Fl_Window inherited;

    static void escape_callback(Fl_Dialog *dialog, void *);

    Fl_Widget      *m_defaultButton;
    Fl_Group       *m_buttonPanel;
    Fl_Widget_List  m_buttonList;
    int             m_buttons;
    int             m_modalResult;
	bool			m_alloc_ds;
};

// Backward compatible defines
#define FL_DLG_OK       Fl_Dialog::BTN_OK
#define FL_DLG_CANCEL   Fl_Dialog::BTN_CANCEL
#define FL_DLG_YES      Fl_Dialog::BTN_YES
#define FL_DLG_NO       Fl_Dialog::BTN_NO
#define FL_DLG_RETRY    Fl_Dialog::BTN_RETRY
#define FL_DLG_REFRESH  Fl_Dialog::BTN_REFRESH
#define FL_DLG_CONFIRM  Fl_Dialog::BTN_CONFIRM
#define FL_DLG_IGNORE   Fl_Dialog::BTN_IGNORE
#define FL_DLG_HELP     Fl_Dialog::BTN_HELP

#endif
