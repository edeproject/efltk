# Include makeinclude for UNIXODBCLIB
EFLTK_TOPDIR=../../..
OS_NAME := $(shell uname -s | sed "s/\//-/" | sed "s/_/-/" | sed "s/-.*//g")
ifeq ($(OS_NAME), MINGW32)
  OS_NAME = WIN32
endif
ifneq ($(MAKEINCLUDE_INCLUDED), 1)
 ifeq ($(OS_NAME), WIN32)
  include $(EFLTK_TOPDIR)/MinGW/makeinclude
 else
  include $(EFLTK_TOPDIR)/makeinclude
 endif
endif

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
