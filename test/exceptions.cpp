/***************************************************************************
                          exceptions.cpp  -  description
                             -------------------
    begin                : Mon Dec 23 2002
    copyright            : (C) 2000 by Alexey S.Parshin
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

#define __FL_EXCEPTIONS__ 0

#include <efltk/fl_ask.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Exception.h>

Fl_Check_Button *check;

void throw_func2()
{
    try
    {
        try {
            //fl_throw("test throw");
        } catch(Fl_Exception &) {
            //fl_rethrow; //re-throw
        }

    } catch(Fl_Exception &) {
        //...
    }
}

void throw_func(bool t)
{	
    try {
        try {
            if(t) {
                fl_throw("Error happened");
            }
        } catch(Fl_Exception &exc) {
            fl_alert("INNER TRY STATEMENT:\n%s", exc.text().c_str());
            throw; //Remember re-throw
        }

        fl_message("NOT THROWED:\nInside try statement, after inner try/catch...");

    } catch(Fl_Exception &exc) {
        fl_alert("OUTER TRY STATEMENT:\n%s", exc.text().c_str());
        throw; //Remember re-throw
    }
}

void cb(Fl_Widget *,void *)
{
    try {
        throw_func(check->value());
    }
    catch(Fl_Exception &exc) {
        fl_alert("MAIN TRY STATEMENT:\n%s", exc.text().c_str());
    }
}

int main (int argc,char *argv[])
{
    /*
    int t1 = Fl::ticks();
    for(int n=0; n<100000; n++)
        throw_func2();
    int t2 = Fl::ticks();
    fl_message("Time spend: %d ms", t2-t1);
    */
    Fl_Window window(170,100);	

    Fl_Button button(10, 10, 150, 30, "Create exception");
    button.callback(cb);

    Fl_Check_Button cbutton(10, 50, 150, 30, "THROW");
    cbutton.value(1);
    check = &cbutton;

    window.end();
    window.show();

    return Fl::run();
}

