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

class Fl_Button;
class Fl_Multi_Tabs;

class FL_API Fl_Dialog : public Fl_Window {
public:
    Fl_Dialog(int w, int h, const char *label=0, Fl_Data_Source *ds=0);
    ~Fl_Dialog();

    // Button IDs
    enum {
        OK      = 1,
        CANCEL  = 2,
        YES     = 4,
        NO      = 8,
        RETRY   = 16,
        REFRESH = 32,
        CONFIRM = 64,
        IGNORE  = 128,
        HELP    = 256
    };

    virtual bool  load_data(Fl_Data_Source *ds=0);
    virtual bool  save_data(Fl_Data_Source *ds=0) const;

    const Fl_Variant& operator [] (const char *field_name) const;
    Fl_Variant& operator [] (const char *field_name);

    // Show dialog as application modal window.
    // Returns ID of button pressed
    int show_modal();

    bool  valid();

    void  buttons(int buttons_mask, int default_button);
    Fl_Button *button(int button_mask) const;
    void  clear_buttons();

    // Add new scrollable page
    Fl_Scroll	*new_scroll(const char *label, bool autoColor=false);
    Fl_Group	*new_page(const char *label,bool autoColor=false) { return (Fl_Group*)new_scroll(label, autoColor); }

    // Add non-scrolable page
    Fl_Group	*new_group(const char *label, bool autoColor=false);

    virtual int handle(int);

protected:
    Fl_Widget *find_widget(const char *field_name) const;

private:
    typedef Fl_Window inherited;

    static void escape_callback(Fl_Widget *,void *);
    static void buttons_callback(Fl_Widget *,void *);
    static void help_callback(Fl_Widget *,void *);

    Fl_Multi_Tabs  *m_tabs;

    Fl_Button      *m_defaultButton;
    Fl_Group       *m_buttonPanel;
    Fl_Widget_List  m_buttonList;
    int             m_buttons;
    int             m_modalResult;
    bool            m_externalDataSource;

    Fl_Data_Source *m_dataSource;
};

// Backward compatible defines
#define FL_DLG_OK       Fl_Dialog::OK
#define FL_DLG_CANCEL   Fl_Dialog::CANCEL
#define FL_DLG_YES      Fl_Dialog::YES
#define FL_DLG_NO       Fl_Dialog::NO
#define FL_DLG_RETRY    Fl_Dialog::RETRY
#define FL_DLG_REFRESH  Fl_Dialog::REFRESH
#define FL_DLG_CONFIRM  Fl_Dialog::CONFIRM
#define FL_DLG_IGNORE   Fl_Dialog::IGNORE
#define FL_DLG_HELP     Fl_Dialog::HELP

#endif
