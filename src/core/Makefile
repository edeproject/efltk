#
# "$Id$"
#
# Library makefile for the Fast Light Tool Kit (FLTK).
#
# Copyright 1998 by Bill Spitzak and others.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# Please report all bugs and problems to "fltk-bugs@easysw.com".
#

OUT_MAGIC := $(shell mkdir ../../lib > /dev/null 2>&1 || :)

CPPFILES = \
	Fl.cpp \
	Fl_Bitmap.cpp \
	Fl_Bmp.cpp \
	Fl_Boxtype.cpp \
	Fl_Callback.cpp \
	Fl_Config.cpp \
	Fl_Data_Source.cpp \
	Fl_Date_Time.cpp \
	Fl_Gif.cpp \
	Fl_Group.cpp \
	Fl_Image.cpp \
	Fl_Image_Filter.cpp \
	Fl_Pixmap.cpp \
	Fl_Renderer.cpp \
	Fl_String.cpp \
	Fl_Style.cpp \
	Fl_Style_Set.cpp \
	Fl_Thread.cpp \
	Fl_Util.cpp \
	Fl_Variant.cpp \
	Fl_WM.cpp \
	Fl_Widget.cpp \
	Fl_Window.cpp \
	Fl_Window_fullscreen.cpp \
	Fl_Window_hotspot.cpp \
	Fl_Window_iconize.cpp \
	Fl_Xpm.cpp \
	Fl_abort.cpp \
	Fl_add_idle.cpp \
	Fl_arg.cpp \
	Fl_compose.cpp \
	Fl_display.cpp \
	Fl_get_key.cpp \
	Fl_init.cpp \
	Fl_key_name.cpp \
	Fl_lock.cpp \
	Fl_own_colormap.cpp \
	Fl_visual.cpp \
	filename_absolute.cpp \
	filename_expand.cpp \
	filename_ext.cpp \
	filename_isdir.cpp \
	filename_list.cpp \
	filename_match.cpp \
	filename_setext.cpp \
	fl_arc.cpp \
	fl_arci.cpp \
	fl_oval_box.cpp \
	fl_plastic_box.cpp \
	fl_round_box.cpp \
	fl_rounded_box.cpp \
	fl_shadow_box.cpp \
	fl_diamond_box.cpp \
	fl_blit.cpp \
	fl_blit_1.cpp \
	fl_blit_a.cpp \
	fl_blit_n.cpp \
	fl_clip.cpp \
	fl_color.cpp \
	fl_cursor.cpp \
	fl_curve.cpp \
	fl_dnd.cpp \
	fl_draw.cpp \
	fl_draw_image.cpp \
	fl_draw_pixmap.cpp \
	fl_font.cpp \
	fl_glyph.cpp \
	fl_labeltype.cpp \
	fl_list_fonts.cpp \
	fl_load_plugin.cpp \
	fl_locale.cpp \
	fl_map.cpp \
	fl_overlay.cpp \
	fl_overlay_visual.cpp \
	fl_rect.cpp \
	fl_rgb.cpp \
	fl_scroll_area.cpp \
	fl_stretch.cpp \
	fl_utf8.cpp \
	fl_vertex.cpp \
	fl_theme.cpp

CFILES = \
	scandir.c \
	numericsort.c \
	vsnprintf.c \
	fl_utf8_x.c \
	fl_utf8_x_input.c \
	fl_utf8_x_utils.c \
	fl_utf_keysym2ucs.c 

################################################################

include ../../makeinclude
DSOCFLAGS += -DFL_LIBRARY
DSOCXXFLAGS += -DFL_LIBRARY

LIBNAME = libefltk_core
DSOLIBNAME = $(LIBNAME)
LIBRARY = ../../lib/$(LIBNAME)
DSO = ../../lib/$(LIBNAME)
DSONAME = $(LIBNAME)$(DSOEXT)

OBJECTS = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)

all: $(BUILDTARGETS)

static: $(LIBRARY)$(LIBEXT)

shared: $(DSO)$(DSOEXT)

programs:

$(LIBRARY).a: $(OBJECTS) fl_call_main.o
	@rm -f $@
	@echo $(LIBCOMMAND) $@ ...
	@$(LIBCOMMAND) $@ $(OBJECTS) fl_call_main.o
	@$(RANLIB) $@

$(DSO).so.2 $(DSO).sl.2: $(OBJECTS:.o=.shared.o)
	@rm -f $@
	@echo $(DSOCOMMAND) $(DSONAME) ...
	@$(DSOCOMMAND) $(DSONAME) $(OBJECTS:.o=.shared.o) $(DSOLIBS)
	@mv $(DSONAME) $@

DLLIMPORTNAME = $(LIBNAME).2.dll$(LIBEXT)
$(DSO).2.dll: $(OBJECTS:.o=.shared.o)
	@-rm -f $@
	@echo $(DSOCOMMAND) $@ ...
	@$(DSOCOMMAND) $@ $(OBJECTS:.o=.shared.o) $(DSOLIBS)
	-mv $@.import ../../lib/$(DLLIMPORTNAME)

clean :
	@rm -f *.o $(LIBRARY)$(LIBEXT) $(DSO)$(DSOEXT) ../lib/$(DLLIMPORTNAME) \
	       core *~ makedepend cmap
	@touch makedepend

depend:
	$(MAKEDEPEND) -I../.. $(CXXFLAGS) $(CPPFILES) $(CFILES) > makedepend
	sed -e "s'\.o'\.shared\.o'" makedepend > foo
	cat foo >> makedepend
	rm foo

include makedepend

################################################################

install: $(INSTALLTARGETS)

install_static: static
	@echo "Installing static libraries..."
	@mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIBNAME)$(LIBEXT)
	@cp -f $(LIBRARY)$(LIBEXT) $(libdir)
	@-chmod 644 $(libdir)/$(LIBNAME)$(LIBEXT)

install_shared: shared
	@echo "Installing shared libraries..."
	@rm -f $(libdir)/$(DLLIMPORTNAME)
	@rm -f $(libdir)/$(DSOLIBNAME)$(DSOEXT)
	@if [ "$(DSOSHORTEXT)" ]; then rm -f $(libdir)/$(DSOLIBNAME)$(DSOSHORTEXT); fi
	@cp -f $(DSO)$(DSOEXT) $(libdir)
	@-chmod 755 $(libdir)/$(DSOLIBNAME)$(DSOEXT)
	@if [ "$(DSOSHORTEXT)" ]; then \
		ln -s $(DSOLIBNAME)$(DSOEXT) $(libdir)/$(DSOLIBNAME)$(DSOSHORTEXT); fi
	@if [ -f "../../lib/$(DLLIMPORTNAME)" ]; then cp ../../lib/$(DLLIMPORTNAME) $(libdir); fi

install_programs:

#
# End of "$Id$".
#
