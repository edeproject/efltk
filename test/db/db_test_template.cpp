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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <efltk/db/Fl_ODBC_Database.h>

static int stepNumber;

void printStepName(const char *stepName) {
   stepNumber++;
   printf("\nstep %02i, %-40s : ",stepNumber,stepName);
   fflush(stdout);
}

int main(int argc, char *argv[]) {

   fl_try {
      //Fl_ODBC_Database db("DSN=odbc_demo;UID=username;PWD=password");
      Fl_ODBC_Database db("DSN=odbc_demo");
      printStepName("Openning the database");
      fflush(stdout);
      db.open();
      printf("Ok");

      printStepName("Creating the temp table");
      Fl_Query query(&db,"CREATE TEMP TABLE _test_ (id int,name char(40))");
      query.exec();
      printf("Ok");

      printStepName("Filling in the temp table");

      query.sql("INSERT INTO _test_ (id,name) VALUES (:var_id,:var_name)");

      query.param("var_id")   = 1;
      query.param("var_name") = "Alex";
      query.exec();

      query.param("var_id")   = 2;
      query.param("var_name") = "Dejan";
      query.exec();

      query.param("var_id")   = 3;
      query.param("var_name") = "Mikko";
      query.exec();

      printf("Ok");

      printStepName("Openning the dataset");
      query.sql("SELECT * FROM _test_");
      query.open();
      printf("Ok");

      printStepName("Reading all the rows from the table");
      int rows = 0;
      while (!query.eof()) {
         printf("\n  Row %i: ",rows);
         for (unsigned i = 0; i < query.field_count(); i++) {
            printf("%s ",query.field(i).as_string().c_str());
         }
         query.fetch();
         rows++;
      }
      printf("\nLooks good? Ok");

      printStepName("Closing the dataset");
      query.close();
      printf("Ok");

      printStepName("Removing temp table");
      query.sql("DROP TABLE _test_");
      query.exec();
      printf("Ok");

      printStepName("Closing the database");
      fflush(stdout);
      db.close();
      printf("Ok");
   }
   fl_catch(exception) {
      printf("Error!   %s\n",exception.text().c_str());
   }

   printf("\n\nTest completed.\n");

   return EXIT_SUCCESS;
}
