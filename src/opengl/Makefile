CPPFILES = \
	Fl_Gl_Choice.cpp \
        Fl_Gl_Overlay.cpp \
        Fl_Gl_Window.cpp \
        gl_draw.cpp \
        gl_start.cpp

CFILES =

PROGRAM_LIBS = $(FLLIB) $(GLLIB)
LIBNAME = libefltk_gl

# This MUST be included after FILES
DIRS=
EFLTK_TOPDIR = ../..
include ../makeinclude_tmpl

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
