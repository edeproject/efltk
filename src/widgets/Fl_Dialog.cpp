/***************************************************************************
                          Fl_Dialog.cpp  -  description
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

#include <efltk/Fl.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Multi_Tabs.h>
#include <efltk/Fl_Dialog.h>
#include <efltk/Fl_Pixmap.h>
#include <efltk/fl_ask.h>
#include <efltk/fl_draw.h>

/* XPM */
static char * cancel_xpm[] = {
"20 20 67 1",
" 	c None",
".	c #F90D04",
"+	c #F70C04",
"@	c #F30C04",
"#	c #F40C04",
"$	c #F60C04",
"%	c #E30C04",
"&	c #F10C04",
"*	c #DB0C04",
"=	c #F80C04",
"-	c #ED0C04",
";	c #B10B04",
">	c #4B0806",
",	c #130706",
"'	c #E40C04",
")	c #BF0B04",
"!	c #9E0A05",
"~	c #BA0B04",
"{	c #5E0905",
"]	c #200706",
"^	c #090706",
"/	c #EE0C04",
"(	c #DF0C04",
"_	c #C00B04",
":	c #C20B04",
"<	c #600905",
"[	c #220706",
"}	c #0C0706",
"|	c #070707",
"1	c #E00C04",
"2	c #F00C04",
"3	c #BB0B04",
"4	c #E50C04",
"5	c #F50C04",
"6	c #BE0B04",
"7	c #630905",
"8	c #230706",
"9	c #E10C04",
"0	c #DA0C04",
"a	c #8F0A05",
"b	c #3A0806",
"c	c #110706",
"d	c #AD0B04",
"e	c #610905",
"f	c #2D0706",
"g	c #EC0C04",
"h	c #D90C04",
"i	c #E20C04",
"j	c #DD0C04",
"k	c #AE0B04",
"l	c #7D0905",
"m	c #BD0B04",
"n	c #AC0B04",
"o	c #DE0C04",
"p	c #B70B04",
"q	c #940A05",
"r	c #3B0806",
"s	c #620905",
"t	c #B80B04",
"u	c #DC0C04",
"v	c #AF0B04",
"w	c #5A0905",
"x	c #860A05",
"y	c #3C0806",
"z	c #120706",
"A	c #3D0806",
"B	c #1A0706",
"                    ",
"                    ",
"              .+@   ",
"   .+#       .+$%   ",
"   +$&*     .+=-;>, ",
"   #&@')!  .+=-~{]^ ",
"    *'/(_:-+=-~<[}| ",
"     _(/'12+-3<[}|  ",
"     !_4@#5-678}|   ",
"      :95=#0abc|    ",
"      -25#@'def     ",
"     .++ghi-jkl     ",
"    .+=-manj-opq    ",
"   .+=-~7rsdo/jn    ",
"  .+=-~<8cfltu9vw   ",
"  .$-~<[}|  qnvxyz  ",
"  .%;{[}|     wAB^  ",
"    >]}|       z^|  ",
"    ,^|             ",
"                    "};
/* XPM */
static char * help_xpm[] = {
"20 20 5 1",
" 	c None",
".	c #BEB8ED",
"+	c #786BE5",
"@	c #000080",
"#	c #261E66",
"                    ",
"                    ",
"        .....       ",
"      ..+++++@      ",
"     .++++++++@     ",
"    .+++@@@+++@#    ",
"    .++@   .++@#    ",
"     @@   .+++@#    ",
"         .+++@##    ",
"        .+++@##     ",
"       .+++@##      ",
"       .++@##       ",
"       .++@#        ",
"        @@##        ",
"         ##         ",
"        ..          ",
"       .++@         ",
"        @@##        ",
"         ##         ",
"                    "};
/* XPM */
static char * no_xpm[] = {
"20 20 5 1",
" 	c None",
".	c #FF0000",
"+	c #800000",
"@	c #542929",
"#	c #808080",
"                    ",
"                    ",
"       ......       ",
"     ..++++++..     ",
"    .+++@@@@+++@    ",
"   .+++@    #+++@   ",
"   .++++.     .+@   ",
"  .++@+++.    .++@  ",
"  .+@ #+++.    .+@  ",
"  .+@  #+++.   .+@  ",
"  .+@   #+++.  .+@  ",
"  .+@    #+++. .+@  ",
"  .++#    #+++.++@  ",
"   .++     #++++@   ",
"   .++..    ++++@   ",
"    @+++....+++@    ",
"     @@++++++@@     ",
"       @@@@@@       ",
"                    ",
"                    "};
/* XPM */
static char * ok_xpm[] = {
"20 20 7 1",
" 	c None",
".	c #ADF4AD",
"+	c #FFFF00",
"@	c #00FF00",
"#	c #156303",
"$	c #ACF298",
"%	c #5AEF34",
"                    ",
"                    ",
"                ... ",
"               .+@# ",
"              .+@@# ",
"             .+@@@# ",
"            .+@@@## ",
"           .+@@@##  ",
"          .+@@@##   ",
"  $.     .+@@@##    ",
" $%+.   .+@@@##     ",
" #%@+. .+@@@##      ",
"  #@@+.+@@@##       ",
"   #@@+@@@##        ",
"    #@@@@##         ",
"     #@@##          ",
"      ###           ",
"                    ",
"                    ",
"                    "};
/* XPM */
static char * refresh_xpm[] = {
"20 20 10 1",
" 	c None",
".	c #262615",
"+	c #000000",
"@	c #27591D",
"#	c #379324",
"$	c #33DB15",
"%	c #141309",
"&	c #79EA62",
"*	c #161010",
"=	c #111108",
"                    ",
"                    ",
"        .+++++      ",
"       .@+###++     ",
"      +@@@+$$$+     ",
"      +@@@@+$$$+    ",
"     +@@+%%%$$$++++ ",
"     +@@@%$$$$$$&%  ",
"     +@@@@+$$$$&%   ",
"     +@@@@+%$$&%    ",
"     +@@@@+ *&%     ",
"     +@@@@+  *      ",
"     +@@@@++++++    ",
"     +@@@=$$$$$+    ",
"      +@=+$$$$+     ",
"      +=+####+      ",
"       =+++++       ",
"                    ",
"                    ",
"                    "};
/* XPM */
static char * retry_xpm[] = {
"20 20 10 1",
" 	c None",
".	c #262615",
"+	c #000000",
"@	c #494912",
"#	c #808000",
"$	c #FFFF00",
"%	c #141309",
"&	c #CCCC0E",
"*	c #161010",
"=	c #111108",
"                    ",
"                    ",
"        .+++++      ",
"       .@+###++     ",
"      +@@@+$$$+     ",
"      +@@@@+$$$+    ",
"     +@@+%%%$$$++++ ",
"     +@@@%$$$$$$&%  ",
"     +@@@@+$$$$&%   ",
"     +@@@@+%$$&%    ",
"     +@@@@+ *&%     ",
"     +@@@@+  *      ",
"     +@@@@++++++    ",
"     +@@@=$$$$$+    ",
"      +@=+$$$$+     ",
"      +=+&&&&+      ",
"       =+++++       ",
"                    ",
"                    ",
"                    "};

// THESE ARE REPLACED BY Fl_Stock_Button?
struct Fl_Dialog_Button_Template {
   int         id;
   const char *label;
   Fl_Pixmap  *pixmap;
};

Fl_Pixmap   pixmap_ok(ok_xpm),
            pixmap_cancel(cancel_xpm),
            pixmap_no(no_xpm),
            pixmap_retry(retry_xpm),
            pixmap_help(help_xpm);

// THESE ARE REPLACED BY Fl_Stock_Button?
static const Fl_Dialog_Button_Template buttonTemplates[] = {
   { FL_DLG_OK,     "Ok",     &pixmap_ok },
   { FL_DLG_CANCEL, "Cancel", &pixmap_cancel },
   { FL_DLG_YES,    "Yes",    &pixmap_ok },
   { FL_DLG_NO,     "No",     &pixmap_no },
   { FL_DLG_RETRY,  "Retry",  &pixmap_retry },
   { FL_DLG_CONFIRM,"Confirm",&pixmap_ok },
   { FL_DLG_IGNORE, "Ignore", &pixmap_no },
   { FL_DLG_HELP,   "Help",   &pixmap_help },
   { 0,             "",       &pixmap_help }
};

void Fl_Dialog::buttons_callback(Fl_Widget *btn,void *id) {
   Fl::exit_modal();
   Fl_Widget *buttonPanel = btn->parent();
   Fl_Dialog *dialog = (Fl_Dialog *)buttonPanel->parent();
   dialog->m_modalResult = (int)id;
}

void Fl_Dialog::help_callback(Fl_Widget *btn,void *id) {
/*
   Fl_Widget *buttonPanel = btn->parent();
   Fl_Dialog *dialog = (Fl_Dialog *)buttonPanel->parent();
*/
   fl_alert("Here we should show some help");
}

Fl_Dialog::Fl_Dialog(int ww,int hh) : Fl_Window(ww,hh) {
   m_defaultButton = NULL;
   m_buttonPanel = new Fl_Group(0,0,10,10);
   m_buttonPanel->end();
   m_tabs = new Fl_Multi_Tabs(0,0,10,10);
   end();
   m_modalResult = 0;
}

const Fl_Variant Fl_Dialog::operator [] (const char *field_name) const {
   // stub
   Fl_Variant tmp;
   return tmp;
}

Fl_Variant Fl_Dialog::operator [] (const char *field_name) {
   // stub
   Fl_Variant tmp;
   return tmp;
}

bool Fl_Dialog::valid() {
   return true;
}

void Fl_Dialog::clear_buttons() {
   unsigned cnt = m_buttonList.count();
   for (unsigned i = 0; i < cnt; i++) {
      Fl_Widget *btn = m_buttonList[i];
      m_buttonPanel->remove(btn);
      delete btn;
   }
}

void Fl_Dialog::buttons(int buttons_mask,int default_button) {
   Fl_Button *btn;
   m_defaultButton = 0L;
   m_buttons = buttons_mask;
   clear_buttons();
   m_buttonPanel->begin();
   for (unsigned i = 0; buttonTemplates[i].id; i++) {
      const Fl_Dialog_Button_Template& buttonTemplate = buttonTemplates[i];
      int id = buttonTemplate.id;
      if (buttons_mask & id) {
         if (id == default_button) {
            Fl_Group *default_box = new Fl_Group(0,0,10,10);
            default_box->color(FL_BLACK);
            default_box->box(FL_THIN_DOWN_BOX);
            btn = new Fl_Button(0,0,10,10,buttonTemplate.label);
            default_box->end();
            m_defaultButton = btn;
         } else
            btn = new Fl_Button(0,0,10,10,buttonTemplate.label);
         if (id == FL_DLG_HELP)
               btn->callback(Fl_Dialog::help_callback);
         else  btn->callback(Fl_Dialog::buttons_callback);
         btn->user_data((void *)id);
         btn->image(buttonTemplate.pixmap);
         m_buttonList.append(btn);
      }
   }
   m_buttonPanel->end();
   relayout();
}

void Fl_Dialog::layout() {
   unsigned cnt = m_buttonList.count();
   unsigned i;
   int maxh = 15;
   if (cnt) {
      Fl_Widget *btn = m_buttonList[0];
      fl_font(btn->textfont(),btn->textsize());
   }

   for (i = 0; i < cnt; i++) {
      Fl_Widget *btn = m_buttonList[i];
      int ww = 0, hh = 0;
      fl_measure(btn->label(),ww,hh);
      if (btn->image()) {
         int ih = btn->image()->height();
         if (ih > hh) hh = ih;
      }
      hh += btn->box()->dh() * 2;
      if (hh > maxh) maxh = hh;
   }

   // resize button panel
   int bpanelh = maxh + 6;
   m_buttonPanel->resize(4,h() - (bpanelh + 2),w()-8,bpanelh);

   // resize widget area
   m_tabs->resize(4,4,w()-8,m_buttonPanel->y()-4);
   //m_tabs->relayout();

   // resize buttons
   int bx = m_buttonPanel->w();

   for (i = 0; i < cnt; i++) {
      Fl_Widget *btn = m_buttonList[i];

      int ww = 0, hh = 0;
      fl_measure(btn->label(),ww,hh);
      if (btn->image())
         ww += btn->image()->width() + 3;
      ww += btn->box()->dw() * 2 + 4;
      bx -= ww + 6;
      if (btn == m_defaultButton) {
         Fl_Widget *default_box = btn->parent();
         default_box->resize(bx-2,2,ww+4,maxh+4);
         btn->resize(2,2,ww,maxh);
      } else {
         btn->resize(bx,4,ww,maxh);
      }
   }
}

int Fl_Dialog::handle(int event) {
   return inherited::handle(event);
}

int Fl_Dialog::show_modal() {
   exec(0,false);
   return m_modalResult;
}