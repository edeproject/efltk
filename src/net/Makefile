CPPFILES = \
	Fl_FTP_Connect.cpp \
	Fl_FTP_DS.cpp \
	Fl_IMAP_Connect.cpp \
	Fl_IMAP_DS.cpp \
	Fl_Base64.cpp

CFILES =

LIBNAME =libefltk_net

# This MUST be included after FILES
DIRS=
EFLTK_TOPDIR = ../..
include ../makeinclude_tmpl

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
