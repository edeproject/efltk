CPPFILES = \
	Fl_Function_Type.cpp \
	Fl_Menu_Type.cpp \
	Fl_Group_Type.cpp \
	Fl_Widget_Type.cpp \
	Fl_Type.cpp \
	Fl_Window_Type.cpp \
	Fluid_Image.cpp \
	Fluid_Plugins.cpp \
	code.cpp \
	factory.cpp \
	file.cpp \
	fluid.cpp \
	about_panel.cpp \
	widget_panel.cpp \
	alignment_panel.cpp \
	function_panel.cpp \
	coding_style.cpp \
	coding_style_func.cpp 

CFILES =

PROGRAM = efluid
PROGRAM_LIBS = $(IMAGELIBS)

# This MUST be included after FILES
EFLTK_TOPDIR = ../..
include $(EFLTK_TOPDIR)/src/makeinclude_tmpl

rebuild:
	@echo Rebuilding .fl files..
	@for f in *.fl ; do \
		efluid -c $$f;\
        done

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
