/***************************************************************************
                          Fl_Dialog.h  -  description
                             -------------------
    begin                : Tue Nov 12 2002
    copyright            : (C) 2002 by Alexey Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef __Fl_Dialog_H__
#define __Fl_Dialog_H__

#include <efltk/Fl_Window.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Widget_List.h>
#include <efltk/Fl_Variant.h>

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
   typedef Fl_Window inherited;

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
protected:
   Fl_Widget *find_widget(const char *field_name) const;
public:
   Fl_Dialog(int w,int h,Fl_Data_Source *ds=NULL);
   ~Fl_Dialog();

   const Fl_Variant& operator [] (const char *field_name) const;
   Fl_Variant& operator [] (const char *field_name);

   virtual bool  load_data(Fl_Data_Source *ds=NULL);
   virtual bool  save_data(Fl_Data_Source *ds=NULL) const;

   int   show_modal();

   bool  valid();
   void  buttons(int buttons_mask,int default_button);
   void  user_button(Fl_Button *);
   void  clear_buttons();

   Fl_Group *new_page(const char *label,bool autoColor=false);

   int   handle(int);
   void  layout();
};

#endif
