//
// "$Id$"
//
// Input widget for the Fast Light Tool Kit (FLTK).
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

#include <efltk/Fl.h>
#include <efltk/fl_ask.h>
#include <efltk/Fl_Widget.h>
#include <efltk/Fl_Float_Input.h>
#include <efltk/Fl_Int_Input.h>
#include <string.h>
#include <stdlib.h>

// Data source support
// loading data from DS
bool Fl_Float_Input::load_data(Fl_Data_Source *ds)
{
    if (field_name().empty())
        return false;

    Fl_Variant fld_value;
    if (ds->read_field(field_name().c_str(), fld_value)) {
        value(fld_value.as_float());
        return true;
    }
    return false;
}

// saving data to DS
bool Fl_Float_Input::save_data(Fl_Data_Source *ds)
{
    if(field_name().empty())
        return false;

    Fl_Variant  fld_value;
    fld_value.set_float(strtod(value(), 0));
    return ds->write_field(field_name().c_str(), fld_value);
}

bool Fl_Float_Input::replace(int b, int e, const char* text, int ilen)
{
    for (int n = 0; n < ilen; n++)
    {
        char ascii = text[n];
        Fl::compose_reset();     // ignore any foreign letters...
        // This is complex to allow "0xff12" hex to be typed:
        if (b+n==0 && (ascii == '+' || ascii == '-') ||
            (ascii >= '0' && ascii <= '9') ||
            (b+n==1 && index(0)=='0' && (ascii=='x' || ascii == 'X')) ||
            (b+n>1 && index(0)=='0' && (index(1)=='x'||index(1)=='X')
                && (ascii>='A'&& ascii<='F' || ascii>='a'&& ascii<='f')) ||
            input_type()==FLOAT && ascii && strchr(".eE+-", ascii))
            continue;            // it's ok;
        return false;
    }

    bool ret=false;
    if (readonly()) fl_beep();
    else ret=Fl_Input::replace(b,e,text,ilen);

    return ret;
}

////////////////////////////////////////

// Data source support
// loading data from DS
bool Fl_Int_Input::load_data(Fl_Data_Source *ds)
{
    if (field_name().empty())
        return false;

    Fl_Variant fld_value;
    if (ds->read_field(field_name().c_str(), fld_value)) {
        value(fld_value.as_int());
        return true;
    }
    return false;
}

// saving data to DS
bool Fl_Int_Input::save_data(Fl_Data_Source *ds)
{
    if(field_name().empty())
        return false;

    Fl_Variant  fld_value;
    fld_value.set_int(strtol(value(), 0, 10));
    return ds->write_field(field_name().c_str(), fld_value);
}


//
// End of "$Id$"
//
