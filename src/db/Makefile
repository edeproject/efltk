CPPFILES = \
	Fl_Database.cpp \
	Fl_Query.cpp \
	Fl_Params.cpp 

CFILES =

LIBNAME =

# This MUST be included after FILES
DIRS=odbc mysql
EFLTK_TOPDIR = ../..
include ../makeinclude_tmpl

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
