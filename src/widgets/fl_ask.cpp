//
// "$Id$"
//
// Standard dialog functions for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

// Implementation of fl_message, fl_ask, fl_choice, fl_input
// The three-message fl_show_x functions are for forms compatibility
// mostly.  In most cases it is easier to get a multi-line message
// by putting newlines in the message.

#include <efltk/Fl.h>
#include <efltk/fl_draw.h>
#include <efltk/fl_ask.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Return_Button.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Secret_Input.h>
#include <efltk/Fl_Pixmap.h>
#include <efltk/vsnprintf.h>

#include "../core/fl_internal.h"

#include <string.h>

static const char * const information_xpm[]={
"32 32 5 1",
". c None",
"c c #000000",
"* c #999999",
"a c #ffffff",
"b c #0000ff",
"...........********.............",
"........***aaaaaaaa***..........",
"......**aaaaaaaaaaaaaa**........",
".....*aaaaaaaaaaaaaaaaaa*.......",
"....*aaaaaaaabbbbaaaaaaaac......",
"...*aaaaaaaabbbbbbaaaaaaaac.....",
"..*aaaaaaaaabbbbbbaaaaaaaaac....",
".*aaaaaaaaaaabbbbaaaaaaaaaaac...",
".*aaaaaaaaaaaaaaaaaaaaaaaaaac*..",
"*aaaaaaaaaaaaaaaaaaaaaaaaaaaac*.",
"*aaaaaaaaaabbbbbbbaaaaaaaaaaac*.",
"*aaaaaaaaaaaabbbbbaaaaaaaaaaac**",
"*aaaaaaaaaaaabbbbbaaaaaaaaaaac**",
"*aaaaaaaaaaaabbbbbaaaaaaaaaaac**",
"*aaaaaaaaaaaabbbbbaaaaaaaaaaac**",
"*aaaaaaaaaaaabbbbbaaaaaaaaaaac**",
".*aaaaaaaaaaabbbbbaaaaaaaaaac***",
".*aaaaaaaaaaabbbbbaaaaaaaaaac***",
"..*aaaaaaaaaabbbbbaaaaaaaaac***.",
"...caaaaaaabbbbbbbbbaaaaaac****.",
"....caaaaaaaaaaaaaaaaaaaac****..",
".....caaaaaaaaaaaaaaaaaac****...",
"......ccaaaaaaaaaaaaaacc****....",
".......*cccaaaaaaaaccc*****.....",
"........***cccaaaac*******......",
"..........****caaac*****........",
".............*caaac**...........",
"...............caac**...........",
"................cac**...........",
".................cc**...........",
"..................***...........",
"...................**..........."};

static const char* const warning_xpm[]={
"32 32 4 1",
". c None",
"a c #ffff00",
"* c #000000",
"b c #999999",
".............***................",
"............*aaa*...............",
"...........*aaaaa*b.............",
"...........*aaaaa*bb............",
"..........*aaaaaaa*bb...........",
"..........*aaaaaaa*bb...........",
".........*aaaaaaaaa*bb..........",
".........*aaaaaaaaa*bb..........",
"........*aaaaaaaaaaa*bb.........",
"........*aaaa***aaaa*bb.........",
".......*aaaa*****aaaa*bb........",
".......*aaaa*****aaaa*bb........",
"......*aaaaa*****aaaaa*bb.......",
"......*aaaaa*****aaaaa*bb.......",
".....*aaaaaa*****aaaaaa*bb......",
".....*aaaaaa*****aaaaaa*bb......",
"....*aaaaaaaa***aaaaaaaa*bb.....",
"....*aaaaaaaa***aaaaaaaa*bb.....",
"...*aaaaaaaaa***aaaaaaaaa*bb....",
"...*aaaaaaaaaa*aaaaaaaaaa*bb....",
"..*aaaaaaaaaaa*aaaaaaaaaaa*bb...",
"..*aaaaaaaaaaaaaaaaaaaaaaa*bb...",
".*aaaaaaaaaaaa**aaaaaaaaaaa*bb..",
".*aaaaaaaaaaa****aaaaaaaaaa*bb..",
"*aaaaaaaaaaaa****aaaaaaaaaaa*bb.",
"*aaaaaaaaaaaaa**aaaaaaaaaaaa*bb.",
"*aaaaaaaaaaaaaaaaaaaaaaaaaaa*bbb",
"*aaaaaaaaaaaaaaaaaaaaaaaaaaa*bbb",
".*aaaaaaaaaaaaaaaaaaaaaaaaa*bbbb",
"..*************************bbbbb",
"....bbbbbbbbbbbbbbbbbbbbbbbbbbb.",
".....bbbbbbbbbbbbbbbbbbbbbbbbb.."};

static Fl_Pixmap information_pix((const char **)information_xpm);
static Fl_Pixmap warning_pix((const char **)warning_xpm);

static void m_revert(Fl_Style* s)
{
    s->box = FL_NO_BOX;
}

static Fl_Named_Style m_style("Message", m_revert, &fl_message_style);
Fl_Named_Style* fl_message_style = &m_style;

static int button_number;
static void set_button_number(Fl_Widget* w, long a)
{
    if (Fl::event() == FL_BUTTON_PRESSED) {
        button_number = a;
        w->window()->hide();
    }
}

#define ICON_W 50
#define ICON_H 50
#define BORDER_W 10
#define BORDER_H 10
#define INPUT_W 270
#define BUTTON_W 80
#define BUTTON_H 23

static Fl_Input *input;

static int innards(int iconlabel, const char *istr, int itype,
		   const char* fmt, va_list ap,
		   const char *b0, const char *b1, const char *b2)
{
    Fl_Window window(3*BORDER_W+ICON_W+INPUT_W, 3*BORDER_H+ICON_H+BUTTON_H);

    // This keeps the icon from resizing.
    Fl_Group ig(BORDER_W, BORDER_H, ICON_W, ICON_H);

    Fl_Box icon(0, 0, ICON_W, ICON_H);
    if (iconlabel==0) {
	icon.image(information_pix);
	window.label(_("Information"));
    }	
    else if (iconlabel==1) {
	icon.image(warning_pix);
	window.label(_("Warning"));
    }
    else { 
	icon.image(information_pix);
	window.label(_("Question"));
    }	
    ig.end();

    Fl_Box message(2*BORDER_W+ICON_W, 0, INPUT_W, 2*BORDER_H+ICON_H);
    message.set_flag(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
    message.style(fl_message_style);

    if (input) {delete input; input = 0;}
    if (istr)
    {
        input = new Fl_Input(2*BORDER_W+ICON_W, 0, INPUT_W, 0);
        input->h(input->text_size()+10);
        input->y(BORDER_H+ICON_H-input->h());
        message.h(input->y());
        input->type(itype);
        input->value(istr);
        window.focus(input);
    }

    window.resizable(message);
    //  w->size_range(window.w(), window.h(), 0, window.h());

    char buffer[1024] = {0};
    if (!strcmp(fmt,"%s"))
    {
        message.label(va_arg(ap, const char*));
    }
    else
    {
        vsnprintf(buffer, 1024, fmt, ap);
        message.label(buffer);
    }

    const char* blabels[3];
    blabels[0] = b0;
    blabels[1] = b1;
    blabels[2] = b2;
    int default_button = b1 ? 1 : 0;

    int i;
    for (i = 0; i <= 2; i++)
        if (blabels[i] && blabels[i][0] == '*') {blabels[i]++; default_button = i;}

        for (i = 3; i--;) if (blabels[i])
    {
        Fl_Button* button;
        if (i == default_button)
        {
            button = new Fl_Return_Button(
                3*BORDER_W+ICON_W+INPUT_W-(BUTTON_W+BORDER_W)*(i+1),
                2*BORDER_H+ICON_H, BUTTON_W, BUTTON_H, blabels[i]);
            window.hotspot(button);
            if (!input) window.focus(button);
        }
        else
        {
            button = new Fl_Button(
                3*BORDER_W+ICON_W+INPUT_W-(BUTTON_W+BORDER_W)*(i+1),
                2*BORDER_H+ICON_H, BUTTON_W, BUTTON_H, blabels[i]);
        }
        button->callback(set_button_number, i);
    }

    window.end();

    button_number = 0;
    window.exec();

     // don't destroy it yet
    if (input) input->parent()->remove(input);
    return button_number;
}

// fltk functions:

void fl_message(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    innards(0, 0, 0, fmt, ap, _("&OK"), 0, 0);
    va_end(ap);
}


void fl_alert(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    innards(1, 0, 0, fmt, ap, _("&OK"), 0, 0);
    va_end(ap);
}


int fl_ask(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int r = innards(2, 0, 0, fmt, ap, _("&No"), _("&Yes"), 0);
    va_end(ap);
    return r;
}


int fl_choice(const char*fmt,const char *b0,const char *b1,const char *b2,...)
{
    va_list ap;
    va_start(ap, b2);
    int r = innards(2, 0, 0, fmt, ap, b0, b1, b2);
    va_end(ap);
    return r;
}


static const char* input_innards(const char* fmt, va_list ap,
			         const char* defstr, uchar type)
{
    int r = innards(2, defstr ? defstr : "", type,
        fmt, ap, _("&Cancel"), _("&OK"), 0);
    return r ? input->value() : 0;
}


const char* fl_input(const char *fmt, const char *defstr, ...)
{
    va_list ap;
    va_start(ap, defstr);
    const char* r = input_innards(fmt, ap, defstr, Fl_Input::NORMAL);
    va_end(ap);
    return r;
}


const char *fl_password(const char *fmt, const char *defstr, ...)
{
    va_list ap;
    va_start(ap, defstr);
    const char* r = input_innards(fmt, ap, defstr, Fl_Input::SECRET);
    va_end(ap);
    return r;
}

#include <efltk/x.h>

// fltk functions: BEEP function from FLTK1.1
void fl_beep(int type) {
#ifdef WIN32
  switch (type) {
    case FL_BEEP_QUESTION :
    case FL_BEEP_PASSWORD :
      MessageBeep(MB_ICONQUESTION);
      break;
    case FL_BEEP_MESSAGE :
      MessageBeep(MB_ICONASTERISK);
      break;
    case FL_BEEP_NOTIFICATION :
      MessageBeep(MB_ICONASTERISK);
      break;
    case FL_BEEP_ERROR :
      MessageBeep(MB_ICONERROR);
      break;
    default :
      MessageBeep(0xFFFFFFFF);
      break;
  }
#elif defined(__APPLE__)
  switch (type) {
    case FL_BEEP_DEFAULT :
    case FL_BEEP_ERROR :
      SysBeep(30);
      break;
    default :
      break;
  }
#else
  fl_open_display();
  switch (type) {
  case FL_BEEP_DEFAULT :
  case FL_BEEP_ERROR :
      XBell(fl_display, 100);
      break;
  default :
      XBell(fl_display, 50);
      break;
  }
#endif // WIN32
}

//
// End of "$Id$".
//
