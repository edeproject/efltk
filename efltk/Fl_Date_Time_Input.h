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

#ifndef _FL_DATE_TIME_INPUT_H_
#define _FL_DATE_TIME_INPUT_H_

#include "Fl_Group.h"
#include "Fl_Date_Time.h"

class Fl_Masked_Input;
class Fl_Button;

class FL_API Fl_Date_Input : public Fl_Group {
public:
    Fl_Date_Input(int,int,int,int,const char * = 0);

    void value(const char *);
    const char *value();

    void date_value(Fl_Date_Time);
    Fl_Date_Time date_value();

    virtual void layout();

protected:
    static void input_callback(Fl_Widget *,void *);
    static void button_callback(Fl_Widget *,void *);

private:
    Fl_Masked_Input  *m_input;
    Fl_Button        *m_button;
};

#endif
