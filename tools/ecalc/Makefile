CPPFILES = Main.cpp \
	SciCalc.cpp

PROGRAM = ecalc

# This MUST be included after FILES
DIRS=
EFLTK_TOPDIR = ../..
include $(EFLTK_TOPDIR)/src/makeinclude_tmpl

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
