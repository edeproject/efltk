CPPFILES = \
	Fl_XmlCtx.cpp \
        Fl_XmlDoc.cpp \
        Fl_XmlNode.cpp \
        Fl_XmlParser.cpp \
        Fl_XmlTokenizer.cpp

CFILES =

PROGRAM_LIBS = $(FLLIB)
LIBNAME = libefltk_xml

# This MUST be included after FILES
DIRS=
EFLTK_TOPDIR = ../..
include ../makeinclude_tmpl

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
