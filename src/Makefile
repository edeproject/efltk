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

OUT_MAGIC := $(shell mkdir ../lib > /dev/null 2>&1 || :)

include ../makeinclude

CPPFILES = \
	core/Fl.cpp \
	core/Fl_Bitmap.cpp \
	core/Fl_Bmp.cpp \
	core/Fl_Boxtype.cpp \
	core/Fl_Callback.cpp \
	core/Fl_Config.cpp \
	core/Fl_Data_Source.cpp \
	core/Fl_Date_Time.cpp \
	core/Fl_Gif.cpp \
	core/Fl_Group.cpp \
	core/Fl_Image.cpp \
	core/Fl_Image_Filter.cpp \
        core/Fl_Lists.cpp \
	core/Fl_Pixmap.cpp \
	core/Fl_Renderer.cpp \
	core/Fl_String.cpp \
	core/Fl_Style.cpp \
	core/Fl_Style_Set.cpp \
	core/Fl_Thread.cpp \
	core/Fl_Util.cpp \
	core/Fl_Variant.cpp \
	core/Fl_WM.cpp \
	core/Fl_Widget.cpp \
	core/Fl_Window.cpp \
	core/Fl_Window_fullscreen.cpp \
	core/Fl_Window_hotspot.cpp \
	core/Fl_Window_iconize.cpp \
	core/Fl_Xpm.cpp \
	core/Fl_abort.cpp \
	core/Fl_add_idle.cpp \
	core/Fl_arg.cpp \
	core/Fl_compose.cpp \
	core/Fl_display.cpp \
	core/Fl_get_key.cpp \
	core/Fl_init.cpp \
	core/Fl_key_name.cpp \
	core/Fl_lock.cpp \
	core/Fl_own_colormap.cpp \
	core/Fl_visual.cpp \
	core/filename_absolute.cpp \
	core/filename_expand.cpp \
	core/filename_ext.cpp \
	core/filename_isdir.cpp \
	core/filename_list.cpp \
	core/filename_match.cpp \
	core/filename_setext.cpp \
	core/fl_arc.cpp \
	core/fl_arci.cpp \
	core/fl_oval_box.cpp \
	core/fl_plastic_box.cpp \
	core/fl_round_box.cpp \
	core/fl_rounded_box.cpp \
	core/fl_shadow_box.cpp \
	core/fl_diamond_box.cpp \
	core/fl_blit.cpp \
	core/fl_blit_1.cpp \
	core/fl_blit_a.cpp \
	core/fl_blit_n.cpp \
	core/fl_clip.cpp \
	core/fl_color.cpp \
	core/fl_cursor.cpp \
	core/fl_curve.cpp \
	core/fl_dnd.cpp \
	core/fl_draw.cpp \
	core/fl_draw_image.cpp \
	core/fl_draw_pixmap.cpp \
	core/fl_font.cpp \
	core/fl_glyph.cpp \
	core/fl_labeltype.cpp \
	core/fl_list_fonts.cpp \
	core/fl_load_plugin.cpp \
	core/fl_locale.cpp \
	core/fl_map.cpp \
	core/fl_overlay.cpp \
	core/fl_overlay_visual.cpp \
	core/fl_rect.cpp \
	core/fl_rgb.cpp \
	core/fl_scroll_area.cpp \
	core/fl_stretch.cpp \
	core/fl_vertex.cpp \
	core/fl_theme.cpp \
	widgets/Fl_Adjuster.cpp \
	widgets/Fl_Align_Group.cpp \
	widgets/Fl_Bar.cpp \
	widgets/Fl_Browser.cpp \
	widgets/Fl_Box.cpp \
	widgets/Fl_Button.cpp \
	widgets/Fl_Calendar.cpp \
	widgets/Fl_Check_Button.cpp \
	widgets/Fl_Choice.cpp \
	widgets/Fl_Clock.cpp \
	widgets/Fl_Color_Chooser.cpp \
	widgets/Fl_Date_Time_Input.cpp \
	widgets/Fl_Dial.cpp \
	widgets/Fl_Dialog.cpp \
	widgets/Fl_Dialog_Data_Source.cpp \
	widgets/Fl_Double_Window.cpp \
	widgets/Fl_FileBrowser.cpp \
	widgets/Fl_FileInput.cpp \
	widgets/Fl_File_Dialog.cpp \
	widgets/Fl_Float_Input.cpp \
        widgets/Fl_Help_Dialog.cpp \
	widgets/Fl_Highlight_Button.cpp \
	widgets/Fl_Input.cpp \
        widgets/Fl_Input_Browser.cpp \
	widgets/Fl_Item.cpp \
	widgets/Fl_Light_Button.cpp \
        widgets/Fl_ListView.cpp \
        widgets/Fl_ListView_Header.cpp \
        widgets/Fl_ListView_Item.cpp \
        widgets/Fl_MDI_Window.cpp \
        widgets/Fl_Main_Window.cpp \
        widgets/Fl_Masked_Input.cpp \
	widgets/Fl_Menu.cpp \
	widgets/Fl_Menu_.cpp \
	widgets/Fl_Menu_add.cpp \
	widgets/Fl_Menu_Bar.cpp \
	widgets/Fl_Menu_Button.cpp \
	widgets/Fl_Menu_Item.cpp \
	widgets/Fl_Menu_Window.cpp \
	widgets/Fl_Menu_global.cpp \
	widgets/Fl_Multi_Image.cpp \
	widgets/Fl_Multi_Tabs.cpp \
	widgets/Fl_Numeric_Input.cpp \
	widgets/Fl_Output.cpp \
	widgets/Fl_Overlay_Window.cpp \
	widgets/Fl_Pack.cpp \
	widgets/Fl_Popup_Window.cpp \
	widgets/Fl_ProgressBar.cpp \
	widgets/Fl_Radio_Button.cpp \
	widgets/Fl_Repeat_Button.cpp \
	widgets/Fl_Return_Button.cpp \
	widgets/Fl_Roller.cpp \
	widgets/Fl_Scroll.cpp \
	widgets/Fl_Scrollbar.cpp \
	widgets/Fl_Shaped_Window.cpp \
        widgets/Fl_Simple_Html.cpp \
	widgets/Fl_Single_Window.cpp \
	widgets/Fl_Slider.cpp \
	widgets/Fl_Tabs.cpp \
	widgets/Fl_Text_Buffer.cpp \
	widgets/Fl_Text_Display.cpp \
	widgets/Fl_Text_Editor.cpp \
	widgets/Fl_Tile.cpp \
        widgets/Fl_Tool_Bar.cpp \
	widgets/Fl_Tooltip.cpp  \
	widgets/Fl_Valuator.cpp \
	widgets/Fl_Value_Input.cpp \
	widgets/Fl_Value_Slider.cpp \
        widgets/Fl_Workspace.cpp \
	widgets/fl_ask.cpp \
	widgets/fl_engraved_label.cpp \
	widgets/fl_show_colormap.cpp \
	widgets/fl_symbols.cpp


CFILES = \
	core/fl_utf8.c \
	core/scandir.c \
	core/numericsort.c \
	core/vsnprintf.c

ifeq ($(COMPILE_XUTF), 1)

CFILES += \
	xutf/case.c \
	xutf/is_spacing.c \
	xutf/keysym2Ucs.c \
	xutf/utf8Utils.c \
	xutf/utf8Wrap.c \
	xutf/utf8Input.c \
	xutf/is_right2left.c
        
endif

################################################################

DSOCFLAGS += -DFL_LIBRARY
DSOCXXFLAGS += -DFL_LIBRARY

LIBNAME = libefltk
DSOLIBNAME = $(LIBNAME)
LIBRARY = ../lib/$(LIBNAME)
DSO = ../lib/$(LIBNAME)
DSONAME = $(LIBNAME)$(DSOEXT)

OBJECTS = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)

all: $(BUILDTARGETS)

static: $(LIBRARY)$(LIBEXT)

shared: $(DSO)$(DSOEXT)

programs:

$(LIBRARY).a: $(OBJECTS)
	@rm -f $@
	@echo $(LIBCOMMAND) $@ ...
	@$(LIBCOMMAND) $@ $(OBJECTS)
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
	-mv $@.import ../lib/$(DLLIMPORTNAME)

clean :
	@rm -f core/*.o widgets/*.o $(LIBRARY)$(LIBEXT) $(DSO)$(DSOEXT) ../lib/$(DLLIMPORTNAME) \
	       *~ makedepend cmap
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
	@if [ -f "../lib/$(DLLIMPORTNAME)" ]; then cp ../lib/$(DLLIMPORTNAME) $(libdir); fi

install_programs:

#
# End of "$Id$".
#
