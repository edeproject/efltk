   File db_test_template.cpp contains a basic test. Any new eFLTK DB driver 
developed should be able to pass it. The only possible correction is that 
not all the databases support the conception of temporary table. For such
databases the SQL statement 'CREATE TEMP TABLE t1..' should be replaced 
with 'CREATE TABLE t1 ..'. In that case user should have at least resourse
permissions - to have enough rights to create a new table in the database.

   AFAIK, at least the following databases support temporary tables:

   - Oracle
   - Informix
   - MS SQL
   - Sybase

The test contains several steps. If any step is unsuccessful the test is 
interrupted and error message is printed.

First, the test tries to connect to the database using ODBC DSN 'demo_odbc'.
User name and password, as well as other DB server specific connect parameters 
should be defined in that DSN, or in the connect string.

Second, the test creates the (temporary) table '_test_' and fills it with 
data. I'm pretty sure that it will be no such table in your existing database.
If such table already exists you can change the table name in the test.

Next, test reads just created data from table '_test_', and prints it on the 
screen row by row.

Finally, the table '_test_' is deleted, and the database is closed.


---------------------------
Alexey Parshin, eFLTK team.
