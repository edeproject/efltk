CPPFILES = \
	Fl_Images.cpp \
        Fl_Jpeg.cpp \
        Fl_Png.cpp

CFILES =

LIBNAME = libefltk_images

# These MUST be included after FILES
DIRS=
EFLTK_TOPDIR = ../..
include ../makeinclude_tmpl

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
