/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed Jan  8 13:15:04 PST 2003
    copyright            : (C) 2003 by Alexey Parshin
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

#include <stdio.h>
#include <stdlib.h>

#include <efltk/Fl.h>
#include <efltk/fl_ask.h>
#include <efltk/db/Fl_ODBC_Database.h>

static int stepNumber;

void printStepName (const char *stepName)
{
    stepNumber++;
    printf ("\nstep %02i, %-40s : ", stepNumber, stepName);
    fflush (stdout);
}

int main (int argc, char *argv[])
{
#ifdef _WIN32
    const char *tmp = fl_input("Connect String?");
    if(!tmp)
        Fl::fatal("Usage: %s \"Connect String\"", argv[0]);
    Fl_String connect_string(tmp);
#else
    if(argc<2) Fl::fatal("Usage: %s \"Connect String\"", argv[0]);
    Fl_String connect_string(argv[1]);
#endif

    fl_try
    {
        //"DSN=odbc_demo;UID=username;PWD=password";
        Fl_ODBC_Database db (connect_string);

        printf("Connect string: %s", connect_string.c_str());
	printStepName ("Openning the database");
	fflush (stdout);
	db.open ();
	printf ("Ok");

	printStepName ("Creating the temp table");
        Fl_Query query (&db, "CREATE TEMP TABLE _test_ (id int,name char(40),age int,position char(40))");
	query.exec ();
	printf ("Ok");

	printStepName ("Filling in the temp table");

	query.sql ("INSERT INTO _test_ (id,name,age,position) VALUES (:var_id,:var_name,:var_age,:var_pos)");

	query.param ("var_id") = 1;
	query.param ("var_name") = "Alex";
	query.param ("var_age") = 38;
	query.param ("var_pos") = "EFLTK developer";	
	query.exec ();

	query.param ("var_id") = 2;
	query.param ("var_name") = "Dejan";
	query.param ("var_age") = 32;
	query.param ("var_pos") = "EFLTK developer";	
	query.exec ();

	query.param ("var_id") = 3;
	query.param ("var_name") = "Mikko";
	query.param ("var_age") = 28;
	query.param ("var_pos") = "EFLTK developer";	
	query.exec ();

	printf ("Ok");

	printStepName ("Openning the dataset");
	query.sql ("SELECT * FROM _test_");
	query.open ();
	printf ("Ok");

	printStepName ("Reading all the rows from the table");
	int rows = 0;
        while (!query.eof ()) {
            printf ("\n  Row %i: ", rows);
            for (unsigned i = 0; i < query.field_count (); i++) {
                printf ("%s ", query.field (i).as_string ().c_str ());
            }
            query.fetch ();
            rows++;
        }
        printf ("\nLooks good? Ok");

	printStepName ("Closing the dataset");
	query.close ();
	printf ("Ok");

	printStepName ("Removing temp table");
	query.sql ("DROP TABLE _test_");
	query.exec ();
	printf ("Ok");

	printStepName ("Closing the database");
	fflush (stdout);
	db.close ();
	printf ("Ok");
    }
    fl_catch (exception)
    {
        printf("Exception! %s\n", exception.text ().c_str ());
        return -1;
    }

    printf("\n\nTest completed.\n");

    return EXIT_SUCCESS;
}
