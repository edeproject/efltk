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
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */
/**
 * @file fl_ask.h
 */

#ifndef _FL_ASK_H_
#define _FL_ASK_H_

#include "Enumerations.h"
#include "Fl_Font.h"
#include "Fl_Style.h"

class FL_API Fl_Widget;

/** BeepTypes */
enum BeepTypes {
    FL_BEEP_DEFAULT = 0,
    FL_BEEP_MESSAGE,
    FL_BEEP_ERROR,
    FL_BEEP_QUESTION,
    FL_BEEP_PASSWORD,
    FL_BEEP_NOTIFICATION
};

/**
 * Produces a short sound notification (beep)
 * @param type is the type of the notification
 */
FL_API void fl_beep(int type = FL_BEEP_DEFAULT);

/**
 * Shows a formatted information notice.
 * @param msg is the message which can contain printf style formatting
 *      characters
 * @see fl_alert,fl_ask
 */
FL_API void fl_message(const char * msg,...);

/**
 * Shows a formatted warning notice.
 * @param msg is the message which can contain printf style formatting
 *      characters
 * @see fl_message,fl_ask
 */
FL_API void fl_alert(const char * msg,...);

/**
 * Shows a formatted warning notice.
 * @param msg is the message which can contain printf style formatting
 *      characters
 */

/**
 * Shows a formatted message and asks for confirmation
 * @param msg is the message which can contain printf style formatting
 *      characters
 * @returns 1 if OK was pressed, otherwise 0
 */
FL_API int fl_ask(const char * msg,...);

/**
 * Shows a formatted message and asks what to do.
 * The labels of the buttons can be 0.
 * @param q is the message which can contain printf style formatting
 *      characters
 * @param b0 the label of the first button
 * @param b1 the label of the second button
 * @param b2 the label of the third button
 * @returns the button number pressed
 */
FL_API int fl_choice(const char *q,const char *b0,const char *b1,const char *b2,...);

/**
 * Shows a formatted message and waits for the user
 * to enter a text.
 * @param label is the message which can contain printf style formatting
 *      characters
 * @param deflt is the default value for the input widget
 * @returns a pointer to the text, or NULL if the user hit cancel.
 * @see fl_password
 */
FL_API const char *fl_input(const char *label, const char *deflt = 0, ...);

/**
 * Shows a formatted message and waits for the user to enter a password
 * @param label is the message which can contain printf style formatting
 *      characters
 * @param deflt is the default value for the input widget
 * @returns a pointer to the text, or NULL if the user hit cancel.
 * @see fl_input
 */
FL_API const char *fl_password(const char *label, const char *deflt = 0, ...);

extern FL_API Fl_Named_Style* fl_icon_style;
extern FL_API Fl_Named_Style* fl_message_style;

#endif
