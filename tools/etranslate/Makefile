PROGRAM = etranslate

CPPFILES = main.cpp \
	main_ui.cpp \
        etranslate.cpp \
        load_etm.cpp \
        load_pot.cpp \
        extract.cpp \
        modify_info.cpp \
        compile.cpp

PROGRAM = etranslate
PROGRAM_LIBS = $(XMLLIBS)

# This MUST be included after FILES
DIRS=
EFLTK_TOPDIR = ../..
include $(EFLTK_TOPDIR)/src/makeinclude_tmpl

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
