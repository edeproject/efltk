//
// "$Id$"
//
// Demo program from the fltk documentation.
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

#include <efltk/Fl_Window.h>
#ifdef _WIN32_WCE
#include <wince.h>
#else
#include <efltk/x.h>
#endif

#include <efltk/db/Fl_ODBC_Database.h>
#include <efltk/db/Fl_Database.h>
#include <efltk/db/Fl_Query.h>
#include <efltk/Fl_String.h>

int main(int argc, char **argv)
{
    Fl_ODBC_Database db("DSN=europe_store;UID=tmr01;PWD=tmr01");

    try {
        // Create temp table
        Fl_String sql = "CREATE TEMP TABLE tt(";
        sql += "id serial primary key,dt date,dtm datetime year to second,";
        sql += "ival int,fval decimal(16,2),sval varchar(255),tval text)";
        Fl_Query q1(&db,sql);
        q1.exec();

        puts("Table created");

        sql = "insert into tt(dt)";
        sql += " values(:dt)";
        q1.sql(sql);
        q1.param("dt").set_date(Fl_Date_Time::Now());
        //q1.param("dtm") = Fl_Date_Time::Now();
        q1.exec();

        puts("Row(s) inserted");

        q1.sql("select * from tt");
        q1.open();
        for (unsigned i=0;i < q1.field_count(); i++) {
            printf("%s ",q1.field(i).as_string().c_str());
        }
        printf("\n");
        q1.close();
    }
    catch (Fl_Exception& e) {
        puts("\nERROR:");
        puts(e.text());
    }
}

//
// End of "$Id$".
//
