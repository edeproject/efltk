# Include makeinclude for UNIXODBCLIB
EFLTK_TOPDIR=../../..
OS_NAME := $(shell uname -s | sed "s/\//-/" | sed "s/_/-/" | sed "s/-.*//g")
ifneq ($(MAKEINCLUDE_INCLUDED), 1)
 ifeq ($(OS_NAME), MINGW32)
  include $(EFLTK_TOPDIR)/MinGW/makeinclude
 else
  include $(EFLTK_TOPDIR)/makeinclude
 endif
endif

ifeq ($(MYSQLLIBS), )
CPPFILES =
LIBNAME =
else
CPPFILES = Fl_MySQL_Database.cpp
LIBNAME = libefltk_mysql
endif

CFILES =

# This MUST be included after FILES
DIRS=
EFLTK_TOPDIR = ../../..
include ../../makeinclude_tmpl

CXXFLAGS += $(MYSQLFLAGS)

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
