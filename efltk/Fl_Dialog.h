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
#include "Fl_Widget_List.h"
#include "Fl_Variant.h"

#define FL_DLG_OK       1
#define FL_DLG_CANCEL   2
#define FL_DLG_YES      4
#define FL_DLG_NO       8
#define FL_DLG_RETRY    16
#define FL_DLG_CONFIRM  32
#define FL_DLG_IGNORE   64
#define FL_DLG_HELP     128

class Fl_Button;
class Fl_Multi_Tabs;

enum Fl_Dlg_Widget_Types {
   DWT_UNKNOWN,
   DWT_BOX=1,
   DWT_HTMLBOX=2,
   DWT_STRING=4,
   DWT_MEMO=8,
   DWT_INTEGER=16,
   DWT_FLOAT=32,
   DWT_DATE=64,
   DWT_TIME=128,
   DWT_DATETIME=256,
   DWT_DATEINTERVAL=512,
   DWT_COMBO=1024,
   DWT_INTVALUECOMBO=2048,
   DWT_LISTBOX=4096,
   DWT_CHECKBUTTONS=8192,
   DWT_RADIOBUTTONS=16384,
   DWT_PHONE=32768
};

enum FGENTRYFLAGS {
   FGE_NONE,
   FGE_SPELLCHECK=1,
   FGE_MANDATORY=2,
   FGE_CFIELD=4,
   FGE_USEPARENTCOLOR=8,
   FGE_SINGLELINEENTRY=256,
   FGE_MULTILINEENTRY=512
};

#define SINGLE_EDIT_ENTRY_HEIGHT 23

class Fl_Dialog_Data_Source;

class FL_API Fl_Dialog : public Fl_Window {
public:
    Fl_Dialog(int w,int h,Fl_Data_Source *ds=NULL);
    ~Fl_Dialog();

    virtual bool  load_data(Fl_Data_Source *ds=NULL);
    virtual bool  save_data(Fl_Data_Source *ds=NULL) const;

    const Fl_Variant& operator [] (const char *field_name) const;
    Fl_Variant& operator [] (const char *field_name);

    int show_modal();

    bool  valid();
    void  buttons(int buttons_mask,int default_button);
    void  user_button(Fl_Button *);
    void  clear_buttons();

    Fl_Group *new_page(const char *label,bool autoColor=false);

    virtual int handle(int);
    virtual void layout();

protected:
    Fl_Widget *find_widget(const char *field_name) const;

private:
    typedef Fl_Window inherited;

    static void escape_callback(Fl_Widget *,void *);
    static void buttons_callback(Fl_Widget *,void *);
    static void help_callback(Fl_Widget *,void *);

    Fl_Button      *m_defaultButton;
    Fl_Group       *m_buttonPanel;
    Fl_Multi_Tabs  *m_tabs;
    Fl_Widget_List  m_buttonList;
    int             m_buttons;
    int             m_modalResult;
    bool            m_externalDataSource;

    Fl_Data_Source *m_dataSource;
};

#endif
