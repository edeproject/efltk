# Include makeinclude for UNIXODBCLIB
include ../../../makeinclude

ifeq ($(UNIXODBCLIB), )
CPPFILES =
LIBNAME =
else
CPPFILES = fl_odbc.cpp Fl_ODBC_Database.cpp
LIBNAME = libefltk_odbc
endif

CFILES =

# This MUST be included after FILES
DIRS=
EFLTK_TOPDIR = ../../..
include ../../makeinclude_tmpl

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
