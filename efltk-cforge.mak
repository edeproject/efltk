#
#	File is generated automatically! Don't edit it!
#
# %IdeVersion:	2623
#
# %IdeAuthor:	Alexey Parshin
#
# %IdeCreationTime:	Sat Feb  1 19:18:04 2003
#
# %IdeComment:	
#
# %IdeDesc:	
#
# %FirstUniqueId:	0x400275
PROJECT_DIR = .

IDE_WORKING_DIR = $(PROJECT_DIR)

MAKE = make

IDE_BLIND_INCLUDES = -I- -I./ -Iefltk -Isrc -Isrc/images -Isrc/xml -Isrc/db/odbc -Itest

DEPEND_INCLUDES = -I- -I./ -Iefltk -Isrc -Isrc/images -Isrc/xml -Isrc/db/odbc -Itest

ALLDEFINES = $(ALLINCLUDES)

ALLINCLUDES = $(INCLUDES)

IDE_BLIND_LIBS = -L./

MAKEFLAGS = $(MAKEOPTIONS)

MAKEOPTIONS = -j4

CCLINK = $(CC)

LD = $(CC)

LDOPTIONS = $(IDE_BLIND_LDOPTIONS) $(LDFLAGS)

LDFLAGS = -L. -lXm -lXext -liconv -lodbc

IDE_BLIND_LDOPTIONS = -L./

IDE_PROJECT_TOOLS = MAKE CCLINK G++ IDE_C_PARSER GCC TAGS IDE_CXX_PARSER

IDE_RCS_TYPE = none

G++ = g++

CXX = g++

CXXFLAGS = $(INCLUDES) $(CXXWARNFLAGS) $(CXXDEBUGFLAGS) $(CXXOPTIMIZEFLAGS) $(CXXCODEFLAGS) $(CXXLANGFLAGS) $(CXXSPECIFICFLAGS)

INCLUDES = -I./ -DFL_SHARED -DHAVE_CONFIG_H

CXXWARNFLAGS = -Wall

CXXDEBUGFLAGS = 

CXXOPTIMIZEFLAGS = -O2

CXXCODEFLAGS = 

CXXLANGFLAGS = 

CXXSPECIFICFLAGS = 

IDE_C_PARSER = 

IDE_C_PARSER_FLAGS = $(IDE_C_PARSER_OPTIONS)

IDE_C_PARSER_OPTIONS = -I/usr/local/include -I/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/2.95.3/../../../../sparc-sun-solaris2.8/include -I/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/2.95.3/include -I/usr/include -D__GCC_NEW_VARARGS__='1' -D__sparc='1' -D__svr4__='1' -D__GNUC_MINOR__='95' -D__sun='1' -Dsparc='1' -D__sun__='1' -D__unix='1' -D__unix__='1' -D__SVR4='1' -Dsun='1' -D__GNUC__='2' -D__sparc__='1' -Dunix='1'

GCC = gcc

CC = gcc

CFLAGS = $(INCLUDES) $(CWARNFLAGS) $(CDEBUGFLAGS) $(COPTIMIZEFLAGS) $(CLANGFLAGS) $(CCODEFLAGS)

CWARNFLAGS = -Wall

CDEBUGFLAGS = 

COPTIMIZEFLAGS = -O2

CLANGFLAGS = 

CCODEFLAGS = 

TAGS = etags

TAGSFLAGS = $(TAGSOPTIONS)

TAGSOPTIONS = -t tags -t TAGS

IDE_CXX_PARSER = 

IDE_CXX_PARSER_FLAGS = $(IDE_CXX_PARSER_OPTIONS)

IDE_CXX_PARSER_OPTIONS = -I/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/2.95.3/../../../../include/g++-3 -I/usr/local/include -I/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/2.95.3/../../../../sparc-sun-solaris2.8/include -I/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/2.95.3/include -I/usr/include -D__EXCEPTIONS='1' -D__GCC_NEW_VARARGS__='1' -D__sparc='1' -D__cplusplus='1' -D__svr4__='1' -D__GNUC_MINOR__='95' -D__sun='1' -Dsparc='1' -D__sun__='1' -D__unix='1' -D__unix__='1' -D__SVR4='1' -Dsun='1' -D__GNUC__='2' -D__sparc__='1' -D__GNUG__='2' -Dunix='1'

# %UniqueId:	0x400002
# %TargetType:	DLL
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	src
# %IncDir:	efltk
# %ObjsDir:	lib
lib/libefltk.so ::	lib/Fl.o\
	lib/Fl_Bitmap.o\
	lib/Fl_Bmp.o\
	lib/Fl_Boxtype.o\
	lib/Fl_Buffer.o\
	lib/Fl_Config.o\
	lib/Fl_Data_Fields.o\
	lib/Fl_Data_Source.o\
	lib/Fl_Date_Time.o\
	lib/Fl_Exception.o\
	lib/Fl_Gif.o\
	lib/Fl_Group.o\
	lib/Fl_Hashs.o\
	lib/Fl_Image.o\
	lib/Fl_Image_Filter.o\
	lib/Fl_Lists.o\
	lib/Fl_Maps.o\
	lib/Fl_Pixmap.o\
	lib/Fl_Renderer.o\
	lib/Fl_String.o\
	lib/Fl_Style.o\
	lib/Fl_Style_Set.o\
	lib/Fl_Thread.o\
	lib/Fl_Translator.o\
	lib/Fl_Util.o\
	lib/Fl_Variant.o\
	lib/Fl_WM.o\
	lib/Fl_Widget.o\
	lib/Fl_Window.o\
	lib/Fl_Window_fullscreen.o\
	lib/Fl_Window_hotspot.o\
	lib/Fl_Window_iconize.o\
	lib/Fl_Xpm.o\
	lib/Fl_abort.o\
	lib/Fl_add_idle.o\
	lib/Fl_arg.o\
	lib/Fl_compose.o\
	lib/Fl_display.o\
	lib/Fl_get_key.o\
	lib/Fl_init.o\
	lib/Fl_key_name.o\
	lib/Fl_lock.o\
	lib/Fl_own_colormap.o\
	lib/Fl_visual.o\
	lib/KStoUCS.o\
	lib/cmap.o\
	lib/filename.o\
	lib/filename_list.o\
	lib/filename_match.o\
	lib/filename_setext.o\
	lib/fl_arc.o\
	lib/fl_arci.o\
	lib/fl_blit.o\
	lib/fl_blit_1.o\
	lib/fl_blit_a.o\
	lib/fl_blit_n.o\
	lib/fl_call_main.o\
	lib/fl_clip.o\
	lib/fl_color.o\
	lib/fl_converters.o\
	lib/fl_cursor.o\
	lib/fl_curve.o\
	lib/fl_diamond_box.o\
	lib/fl_dnd.o\
	lib/fl_draw.o\
	lib/fl_draw_image.o\
	lib/fl_draw_pixmap.o\
	lib/fl_font.o\
	lib/fl_glyph.o\
	lib/fl_iconv_converters.o\
	lib/fl_labeltype.o\
	lib/fl_list_fonts.o\
	lib/fl_load_plugin.o\
	lib/fl_locale.o\
	lib/fl_map.o\
	lib/fl_oval_box.o\
	lib/fl_overlay.o\
	lib/fl_overlay_visual.o\
	lib/fl_plastic_box.o\
	lib/fl_rect.o\
	lib/fl_rgb.o\
	lib/fl_round_box.o\
	lib/fl_rounded_box.o\
	lib/fl_scroll_area.o\
	lib/fl_shadow_box.o\
	lib/fl_stretch.o\
	lib/fl_theme.o\
	lib/fl_utf8.o\
	lib/fl_vertex.o\
	lib/scandir.o\
	lib/vsnprintf.o\
	lib/Fl_Database.o\
	lib/Fl_Params.o\
	lib/Fl_Query.o\
	lib/Fl_Adjuster.o\
	lib/Fl_Align_Group.o\
	lib/Fl_Bar.o\
	lib/Fl_Box.o\
	lib/Fl_Browser.o\
	lib/Fl_Button.o\
	lib/Fl_Calendar.o\
	lib/Fl_Check_Button.o\
	lib/Fl_Choice.o\
	lib/Fl_Clock.o\
	lib/Fl_Color_Chooser.o\
	lib/Fl_Date_Time_Input.o\
	lib/Fl_Dial.o\
	lib/Fl_Dialog.o\
	lib/Fl_Directory_DS.o\
	lib/Fl_Double_Window.o\
	lib/Fl_FileBrowser.o\
	lib/Fl_FileInput.o\
	lib/Fl_File_Dialog.o\
	lib/Fl_Float_Input.o\
	lib/Fl_Help_Dialog.o\
	lib/Fl_Highlight_Button.o\
	lib/Fl_Input.o\
	lib/Fl_Input_Browser.o\
	lib/Fl_Item.o\
	lib/Fl_Light_Button.o\
	lib/Fl_ListView.o\
	lib/Fl_ListView_Header.o\
	lib/Fl_ListView_Item.o\
	lib/Fl_MDI_Bar.o\
	lib/Fl_MDI_Window.o\
	lib/Fl_Main_Window.o\
	lib/Fl_Masked_Input.o\
	lib/Fl_Menu.o\
	lib/Fl_Menu_.o\
	lib/Fl_Menu_Bar.o\
	lib/Fl_Menu_Button.o\
	lib/Fl_Menu_Item.o\
	lib/Fl_Menu_Window.o\
	lib/Fl_Menu_add.o\
	lib/Fl_Menu_global.o\
	lib/Fl_Multi_Image.o\
	lib/Fl_Multi_Tabs.o\
	lib/Fl_Numeric_Input.o\
	lib/Fl_Output.o\
	lib/Fl_Overlay_Window.o\
	lib/Fl_Pack.o\
	lib/Fl_Popup_Window.o\
	lib/Fl_ProgressBar.o\
	lib/Fl_Radio_Button.o\
	lib/Fl_Repeat_Button.o\
	lib/Fl_Return_Button.o\
	lib/Fl_Roller.o\
	lib/Fl_Scroll.o\
	lib/Fl_Scrollbar.o\
	lib/Fl_Shaped_Window.o\
	lib/Fl_Simple_Html.o\
	lib/Fl_Single_Window.o\
	lib/Fl_Slider.o\
	lib/Fl_Tabs.o\
	lib/Fl_Text_Buffer.o\
	lib/Fl_Text_Display.o\
	lib/Fl_Text_Editor.o\
	lib/Fl_Tile.o\
	lib/Fl_Tool_Bar.o\
	lib/Fl_Tooltip.o\
	lib/Fl_Valuator.o\
	lib/Fl_Value_Input.o\
	lib/Fl_Value_Slider.o\
	lib/Fl_Workspace.o\
	lib/fl_ask.o\
	lib/fl_engraved_label.o\
	lib/fl_show_colormap.o\
	lib/fl_symbols.o
	rm -f $@
	$(LD) -shared -o $@ $^ $(LDOPTIONS)
	cp $@ /usr/local/lib

# %UniqueId:	0x4000ed
# %TargetType:	DLL
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	src/images
# %IncDir:	src/images
# %ObjsDir:	lib
lib/libefltk_images.so ::	lib/Fl_Images.o\
	lib/Fl_Jpeg.o\
	lib/Fl_Png.o
	rm -f $@
	$(LD) -shared -o $@ $^ $(LDOPTIONS)
	cp $@ /usr/local/lib

# %UniqueId:	0x4000f2
# %TargetType:	DLL
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	src/xml
# %IncDir:	src/xml
# %ObjsDir:	lib
lib/libefltk_xml.so ::	lib/Fl_XmlCtx.o\
	lib/Fl_XmlDoc.o\
	lib/Fl_XmlNode.o\
	lib/Fl_XmlParser.o\
	lib/Fl_XmlTokenizer.o
	rm -f $@
	$(LD) -shared -o $@ $^ $(LDOPTIONS)
	cp $@ /usr/local/lib

# %UniqueId:	0x4000f8
# %TargetType:	DLL
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	src/db/odbc
# %IncDir:	src/db/odbc
# %ObjsDir:	lib
lib/libefltk_odbc.so ::	lib/Fl_ODBC_Database.o\
	lib/fl_odbc.o
	rm -f $@
	$(LD) -shared -o $@ $^ $(LDOPTIONS)
	cp $@ /usr/local/lib

# %UniqueId:	0x400184
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/arc ::	test/arc.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400186
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/ask ::	test/ask.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400188
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/bitmap ::	test/bitmap.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x40018c
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/boxtype ::	test/boxtype.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x40018e
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/browser ::	test/browser.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400192
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/button ::	test/button.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400195
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/buttons ::	test/buttons.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400249
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/calendar ::	test/calendar.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x40024b
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/checkers ::	test/checkers.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x40025e
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/clock ::	test/clock.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400262
# %TargetType:	C_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/color_chooser ::	test/color_chooser.o
	$(CC) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400266
# %TargetType:	C_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/cube ::	test/cube.o
	$(CC) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk -lefltk_gl -lGL

# %UniqueId:	0x40026b
# %TargetType:	DLL
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	src
# %IncDir:	efltk
# %ObjsDir:	lib
lib/libefltk_gl.so ::	lib/Fl_Gl_Choice.o\
	lib/Fl_Gl_Overlay.o\
	lib/Fl_Gl_Window.o\
	lib/gl_draw.o\
	lib/gl_start.o
	rm -f $@
	$(LD) -shared -o $@ $^ $(LDOPTIONS)
	cp $@ /usr/local/lib

# %UniqueId:	0x400272
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/cursor ::	test/cursor.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %ObjectFilesLinking
# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000f8
# %SourceTarget:	0x4000cd
lib/Fl_ODBC_Database.o : src/db/odbc/Fl_ODBC_Database.cpp
	$(CXX) -c -o $@ $< -Isrc/db/odbc -Isrc/db/odbc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000f8
# %SourceTarget:	0x4000ce
lib/fl_odbc.o : src/db/odbc/fl_odbc.cpp
	$(CXX) -c -o $@ $< -Isrc/db/odbc -Isrc/db/odbc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000f2
# %SourceTarget:	0x4000f9
lib/Fl_XmlCtx.o : src/xml/Fl_XmlCtx.cpp
	$(CXX) -c -o $@ $< -Isrc/xml -Isrc/xml $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000f2
# %SourceTarget:	0x4000fa
lib/Fl_XmlDoc.o : src/xml/Fl_XmlDoc.cpp
	$(CXX) -c -o $@ $< -Isrc/xml -Isrc/xml $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000f2
# %SourceTarget:	0x4000fb
lib/Fl_XmlNode.o : src/xml/Fl_XmlNode.cpp
	$(CXX) -c -o $@ $< -Isrc/xml -Isrc/xml $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000f2
# %SourceTarget:	0x4000fc
lib/Fl_XmlParser.o : src/xml/Fl_XmlParser.cpp
	$(CXX) -c -o $@ $< -Isrc/xml -Isrc/xml $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000f2
# %SourceTarget:	0x4000fd
lib/Fl_XmlTokenizer.o : src/xml/Fl_XmlTokenizer.cpp
	$(CXX) -c -o $@ $< -Isrc/xml -Isrc/xml $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000ed
# %SourceTarget:	0x4000fe
lib/Fl_Images.o : src/images/Fl_Images.cpp
	$(CXX) -c -o $@ $< -Isrc/images -Isrc/images $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000ed
# %SourceTarget:	0x4000ff
lib/Fl_Jpeg.o : src/images/Fl_Jpeg.cpp
	$(CXX) -c -o $@ $< -Isrc/images -Isrc/images $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x4000ed
# %SourceTarget:	0x400100
lib/Fl_Png.o : src/images/Fl_Png.cpp
	$(CXX) -c -o $@ $< -Isrc/images -Isrc/images $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400184
# %SourceTarget:	0x400185
test/arc.o : test/arc.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400186
# %SourceTarget:	0x400187
test/ask.o : test/ask.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400188
# %SourceTarget:	0x400189
test/bitmap.o : test/bitmap.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40018c
# %SourceTarget:	0x40018d
test/boxtype.o : test/boxtype.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40018e
# %SourceTarget:	0x40018f
test/browser.o : test/browser.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400192
# %SourceTarget:	0x400193
test/button.o : test/button.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400195
# %SourceTarget:	0x400196
test/buttons.o : test/buttons.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a0
lib/Fl.o : src/core/Fl.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a1
lib/Fl_Bitmap.o : src/core/Fl_Bitmap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a2
lib/Fl_Bmp.o : src/core/Fl_Bmp.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a3
lib/Fl_Boxtype.o : src/core/Fl_Boxtype.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a4
lib/Fl_Buffer.o : src/core/Fl_Buffer.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a5
lib/Fl_Config.o : src/core/Fl_Config.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a6
lib/Fl_Data_Fields.o : src/core/Fl_Data_Fields.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a7
lib/Fl_Data_Source.o : src/core/Fl_Data_Source.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a8
lib/Fl_Date_Time.o : src/core/Fl_Date_Time.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001a9
lib/Fl_Exception.o : src/core/Fl_Exception.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001aa
lib/Fl_Gif.o : src/core/Fl_Gif.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ab
lib/Fl_Group.o : src/core/Fl_Group.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ac
lib/Fl_Hashs.o : src/core/Fl_Hashs.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ad
lib/Fl_Image.o : src/core/Fl_Image.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ae
lib/Fl_Image_Filter.o : src/core/Fl_Image_Filter.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001af
lib/Fl_Lists.o : src/core/Fl_Lists.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b0
lib/Fl_Maps.o : src/core/Fl_Maps.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b1
lib/Fl_Pixmap.o : src/core/Fl_Pixmap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b2
lib/Fl_Renderer.o : src/core/Fl_Renderer.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b3
lib/Fl_String.o : src/core/Fl_String.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b4
lib/Fl_Style.o : src/core/Fl_Style.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b5
lib/Fl_Style_Set.o : src/core/Fl_Style_Set.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b6
lib/Fl_Thread.o : src/core/Fl_Thread.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b7
lib/Fl_Translator.o : src/core/Fl_Translator.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b8
lib/Fl_Util.o : src/core/Fl_Util.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001b9
lib/Fl_Variant.o : src/core/Fl_Variant.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ba
lib/Fl_WM.o : src/core/Fl_WM.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001bb
lib/Fl_Widget.o : src/core/Fl_Widget.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001bc
lib/Fl_Window.o : src/core/Fl_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001bd
lib/Fl_Window_fullscreen.o : src/core/Fl_Window_fullscreen.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001be
lib/Fl_Window_hotspot.o : src/core/Fl_Window_hotspot.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001bf
lib/Fl_Window_iconize.o : src/core/Fl_Window_iconize.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c0
lib/Fl_Xpm.o : src/core/Fl_Xpm.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c1
lib/Fl_abort.o : src/core/Fl_abort.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c2
lib/Fl_add_idle.o : src/core/Fl_add_idle.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c3
lib/Fl_arg.o : src/core/Fl_arg.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c4
lib/Fl_compose.o : src/core/Fl_compose.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c5
lib/Fl_display.o : src/core/Fl_display.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c6
lib/Fl_get_key.o : src/core/Fl_get_key.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c7
lib/Fl_init.o : src/core/Fl_init.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c8
lib/Fl_key_name.o : src/core/Fl_key_name.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001c9
lib/Fl_lock.o : src/core/Fl_lock.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ca
lib/Fl_own_colormap.o : src/core/Fl_own_colormap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001cb
lib/Fl_visual.o : src/core/Fl_visual.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001cc
lib/KStoUCS.o : src/core/KStoUCS.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001cd
lib/cmap.o : src/core/cmap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ce
lib/filename.o : src/core/filename.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001cf
lib/filename_list.o : src/core/filename_list.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d0
lib/filename_match.o : src/core/filename_match.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d1
lib/filename_setext.o : src/core/filename_setext.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d2
lib/fl_arc.o : src/core/fl_arc.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d3
lib/fl_arci.o : src/core/fl_arci.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d4
lib/fl_blit.o : src/core/fl_blit.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d5
lib/fl_blit_1.o : src/core/fl_blit_1.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d6
lib/fl_blit_a.o : src/core/fl_blit_a.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d7
lib/fl_blit_n.o : src/core/fl_blit_n.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d8
lib/fl_call_main.o : src/core/fl_call_main.c
	$(CC) -c -o $@ $< -Iefltk -Isrc $(CFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001d9
lib/fl_clip.o : src/core/fl_clip.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001da
lib/fl_color.o : src/core/fl_color.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001db
lib/fl_converters.o : src/core/fl_converters.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001dc
lib/fl_cursor.o : src/core/fl_cursor.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001dd
lib/fl_curve.o : src/core/fl_curve.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001de
lib/fl_diamond_box.o : src/core/fl_diamond_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001df
lib/fl_dnd.o : src/core/fl_dnd.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e0
lib/fl_draw.o : src/core/fl_draw.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e1
lib/fl_draw_image.o : src/core/fl_draw_image.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e2
lib/fl_draw_pixmap.o : src/core/fl_draw_pixmap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e3
lib/fl_font.o : src/core/fl_font.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e4
lib/fl_glyph.o : src/core/fl_glyph.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e5
lib/fl_iconv_converters.o : src/core/fl_iconv_converters.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e6
lib/fl_labeltype.o : src/core/fl_labeltype.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e7
lib/fl_list_fonts.o : src/core/fl_list_fonts.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e8
lib/fl_load_plugin.o : src/core/fl_load_plugin.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001e9
lib/fl_locale.o : src/core/fl_locale.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ea
lib/fl_map.o : src/core/fl_map.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001eb
lib/fl_oval_box.o : src/core/fl_oval_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ec
lib/fl_overlay.o : src/core/fl_overlay.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ed
lib/fl_overlay_visual.o : src/core/fl_overlay_visual.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ee
lib/fl_plastic_box.o : src/core/fl_plastic_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ef
lib/fl_rect.o : src/core/fl_rect.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f0
lib/fl_rgb.o : src/core/fl_rgb.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f1
lib/fl_round_box.o : src/core/fl_round_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f2
lib/fl_rounded_box.o : src/core/fl_rounded_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f3
lib/fl_scroll_area.o : src/core/fl_scroll_area.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f4
lib/fl_shadow_box.o : src/core/fl_shadow_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f5
lib/fl_stretch.o : src/core/fl_stretch.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f6
lib/fl_theme.o : src/core/fl_theme.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f7
lib/fl_utf8.o : src/core/fl_utf8.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f8
lib/fl_vertex.o : src/core/fl_vertex.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001f9
lib/scandir.o : src/core/scandir.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001fa
lib/vsnprintf.o : src/core/vsnprintf.c
	$(CC) -c -o $@ $< -Iefltk -Isrc $(CFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001fc
lib/Fl_Database.o : src/db/Fl_Database.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001fd
lib/Fl_Params.o : src/db/Fl_Params.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001fe
lib/Fl_Query.o : src/db/Fl_Query.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4001ff
lib/Fl_Adjuster.o : src/widgets/Fl_Adjuster.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400200
lib/Fl_Align_Group.o : src/widgets/Fl_Align_Group.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400201
lib/Fl_Bar.o : src/widgets/Fl_Bar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400202
lib/Fl_Box.o : src/widgets/Fl_Box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400203
lib/Fl_Browser.o : src/widgets/Fl_Browser.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400204
lib/Fl_Button.o : src/widgets/Fl_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400205
lib/Fl_Calendar.o : src/widgets/Fl_Calendar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400206
lib/Fl_Check_Button.o : src/widgets/Fl_Check_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400207
lib/Fl_Choice.o : src/widgets/Fl_Choice.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400208
lib/Fl_Clock.o : src/widgets/Fl_Clock.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400209
lib/Fl_Color_Chooser.o : src/widgets/Fl_Color_Chooser.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40020a
lib/Fl_Date_Time_Input.o : src/widgets/Fl_Date_Time_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40020b
lib/Fl_Dial.o : src/widgets/Fl_Dial.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40020c
lib/Fl_Dialog.o : src/widgets/Fl_Dialog.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40020d
lib/Fl_Directory_DS.o : src/widgets/Fl_Directory_DS.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40020e
lib/Fl_Double_Window.o : src/widgets/Fl_Double_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40020f
lib/Fl_FileBrowser.o : src/widgets/Fl_FileBrowser.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400210
lib/Fl_FileInput.o : src/widgets/Fl_FileInput.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400211
lib/Fl_File_Dialog.o : src/widgets/Fl_File_Dialog.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400212
lib/Fl_Float_Input.o : src/widgets/Fl_Float_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400213
lib/Fl_Help_Dialog.o : src/widgets/Fl_Help_Dialog.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400214
lib/Fl_Highlight_Button.o : src/widgets/Fl_Highlight_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400215
lib/Fl_Input.o : src/widgets/Fl_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400216
lib/Fl_Input_Browser.o : src/widgets/Fl_Input_Browser.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400217
lib/Fl_Item.o : src/widgets/Fl_Item.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400218
lib/Fl_Light_Button.o : src/widgets/Fl_Light_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400219
lib/Fl_ListView.o : src/widgets/Fl_ListView.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40021a
lib/Fl_ListView_Header.o : src/widgets/Fl_ListView_Header.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40021b
lib/Fl_ListView_Item.o : src/widgets/Fl_ListView_Item.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40021c
lib/Fl_MDI_Bar.o : src/widgets/Fl_MDI_Bar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40021d
lib/Fl_MDI_Window.o : src/widgets/Fl_MDI_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40021e
lib/Fl_Main_Window.o : src/widgets/Fl_Main_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40021f
lib/Fl_Masked_Input.o : src/widgets/Fl_Masked_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400220
lib/Fl_Menu.o : src/widgets/Fl_Menu.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400221
lib/Fl_Menu_.o : src/widgets/Fl_Menu_.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400222
lib/Fl_Menu_Bar.o : src/widgets/Fl_Menu_Bar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400223
lib/Fl_Menu_Button.o : src/widgets/Fl_Menu_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400224
lib/Fl_Menu_Item.o : src/widgets/Fl_Menu_Item.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400225
lib/Fl_Menu_Window.o : src/widgets/Fl_Menu_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400226
lib/Fl_Menu_add.o : src/widgets/Fl_Menu_add.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400227
lib/Fl_Menu_global.o : src/widgets/Fl_Menu_global.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400228
lib/Fl_Multi_Image.o : src/widgets/Fl_Multi_Image.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400229
lib/Fl_Multi_Tabs.o : src/widgets/Fl_Multi_Tabs.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40022a
lib/Fl_Numeric_Input.o : src/widgets/Fl_Numeric_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40022b
lib/Fl_Output.o : src/widgets/Fl_Output.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40022c
lib/Fl_Overlay_Window.o : src/widgets/Fl_Overlay_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40022d
lib/Fl_Pack.o : src/widgets/Fl_Pack.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40022e
lib/Fl_Popup_Window.o : src/widgets/Fl_Popup_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40022f
lib/Fl_ProgressBar.o : src/widgets/Fl_ProgressBar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400230
lib/Fl_Radio_Button.o : src/widgets/Fl_Radio_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400231
lib/Fl_Repeat_Button.o : src/widgets/Fl_Repeat_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400232
lib/Fl_Return_Button.o : src/widgets/Fl_Return_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400233
lib/Fl_Roller.o : src/widgets/Fl_Roller.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400234
lib/Fl_Scroll.o : src/widgets/Fl_Scroll.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400235
lib/Fl_Scrollbar.o : src/widgets/Fl_Scrollbar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400236
lib/Fl_Shaped_Window.o : src/widgets/Fl_Shaped_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400237
lib/Fl_Simple_Html.o : src/widgets/Fl_Simple_Html.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400238
lib/Fl_Single_Window.o : src/widgets/Fl_Single_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400239
lib/Fl_Slider.o : src/widgets/Fl_Slider.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40023a
lib/Fl_Tabs.o : src/widgets/Fl_Tabs.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40023b
lib/Fl_Text_Buffer.o : src/widgets/Fl_Text_Buffer.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40023c
lib/Fl_Text_Display.o : src/widgets/Fl_Text_Display.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40023d
lib/Fl_Text_Editor.o : src/widgets/Fl_Text_Editor.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40023e
lib/Fl_Tile.o : src/widgets/Fl_Tile.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40023f
lib/Fl_Tool_Bar.o : src/widgets/Fl_Tool_Bar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400240
lib/Fl_Tooltip.o : src/widgets/Fl_Tooltip.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400241
lib/Fl_Valuator.o : src/widgets/Fl_Valuator.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400242
lib/Fl_Value_Input.o : src/widgets/Fl_Value_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400243
lib/Fl_Value_Slider.o : src/widgets/Fl_Value_Slider.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400244
lib/Fl_Workspace.o : src/widgets/Fl_Workspace.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400245
lib/fl_ask.o : src/widgets/fl_ask.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400246
lib/fl_engraved_label.o : src/widgets/fl_engraved_label.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400247
lib/fl_show_colormap.o : src/widgets/fl_show_colormap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400248
lib/fl_symbols.o : src/widgets/fl_symbols.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400249
# %SourceTarget:	0x40024a
test/calendar.o : test/calendar.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40024b
# %SourceTarget:	0x40024c
test/checkers.o : test/checkers.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40025e
# %SourceTarget:	0x40025f
test/clock.o : test/clock.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400262
# %SourceTarget:	0x400263
test/color_chooser.o : test/color_chooser.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400266
# %SourceTarget:	0x400267
test/cube.o : test/cube.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x40026c
lib/Fl_Gl_Choice.o : src/Fl_Gl_Choice.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x40026d
lib/Fl_Gl_Overlay.o : src/Fl_Gl_Overlay.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x40026e
lib/Fl_Gl_Window.o : src/Fl_Gl_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x40026f
lib/gl_draw.o : src/gl_draw.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x400270
lib/gl_start.o : src/gl_start.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400272
# %SourceTarget:	0x400273
test/cursor.o : /distr/develop/CVS/efltk/test/cursor.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# DO NOT DELETE

lib/Fl_ODBC_Database.o :	src/db/odbc/fl_odbc.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Thread.h\
	efltk/Fl_Thread_Linux.h\
	efltk/Fl_Thread_w32.h
lib/fl_odbc.o :	src/db/odbc/fl_odbc.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h
lib/Fl_XmlCtx.o :	src/xml/html_entities.h\
	efltk/fl_utf8.h\
	efltk/Fl_Export.h
lib/Fl_XmlParser.o :	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	config.h
lib/Fl_XmlTokenizer.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h
lib/Fl_Images.o :	efltk/Fl_Image.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Export.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	config.h
lib/Fl_Jpeg.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h
lib/Fl_Png.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h
test/arc.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Value_Slider.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Double_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
test/ask.o :	efltk/fl_ask.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Return_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Input.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
test/bitmap.o :	efltk/Fl_Toggle_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Bitmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
test/boxtype.o :	efltk/Fl_Box.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
test/browser.o :	test/file_small.xpm\
	test/folder_small.xpm\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Item_Group.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Item.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl.h\
	efltk/Fl_Scroll.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Window.h\
	efltk/Fl_Browser.h
test/button.o :	efltk/fl_ask.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
test/buttons.o :	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Highlight_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Light_Button.h\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Radio_Button.h\
	efltk/Fl_Repeat_Button.h\
	efltk/Fl_Return_Button.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
lib/Fl.o :	src/core/Fl_x.cpp\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/fl_utf8.h\
	efltk/Fl_WM.h\
	efltk/x.h\
	efltk/win32.h\
	config.h\
	src/core/Fl_wince.cpp\
	src/core/aimm.h\
	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl.h\
	src/core/Fl_win32.cpp\
	efltk/Fl_Tooltip.h
lib/Fl_Bitmap.o :	efltk/Fl_Bitmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Export.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl.h\
	config.h
lib/Fl_Bmp.o :	efltk/Fl.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Exception.h\
	efltk/Fl_String.h\
	efltk/Fl_Image.h\
	efltk/Fl_Flags.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_String_List.h\
	config.h
lib/Fl_Boxtype.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	config.h
lib/Fl_Buffer.o :	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Buffer.h
lib/Fl_Config.o :	config.h\
	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Config.h\
	efltk/Fl_Color.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Exception.h\
	efltk/Fl_String_List.h\
	efltk/vsnprintf.h\
	src/core/fl_internal.h\
	efltk/Fl_Translator.h
lib/Fl_Data_Fields.o :	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h
lib/Fl_Data_Source.o :	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h
lib/Fl_Date_Time.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Date_Time.h
lib/Fl_Exception.o :	efltk/Fl.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Exception.h\
	efltk/Fl_String.h
lib/Fl_Gif.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h
lib/Fl_Group.o :	efltk/Fl_Tooltip.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	efltk/fl_draw.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h
lib/Fl_Hashs.o :	efltk/Fl_String_Hash.h\
	efltk/Fl_Ptr_Hash.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h
lib/Fl_Image.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/fl_utf8.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_draw.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Image_Filter.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Renderer.h\
	efltk/Fl_Image.h
lib/Fl_Image_Filter.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Image_Filter.h\
	efltk/fl_math.h
lib/Fl_Lists.o :	efltk/Fl_String_Stack.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Callback_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Ptr_Stack.h\
	efltk/vsnprintf.h\
	config.h
lib/Fl_Maps.o :	efltk/Fl_Map.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h
lib/Fl_Pixmap.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Pixmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h
lib/Fl_Renderer.o :	config.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Renderer.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h
lib/Fl_String.o :	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Fl_Flags.h\
	efltk/vsnprintf.h\
	efltk/fl_utf8.h\
	config.h\
	efltk/fl_math.h
lib/Fl_Style.o :	efltk/vsnprintf.h\
	efltk/fl_load_plugin.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Config.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_String.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h\
	efltk/fl_math.h
lib/Fl_Style_Set.o :	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Style_Set.h
lib/Fl_Thread.o :	efltk/Fl_Thread.h\
	efltk/Fl_Thread_Linux.h\
	efltk/Fl_Thread_w32.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	config.h
lib/Fl_Translator.o :	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/vsnprintf.h\
	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Flags.h\
	efltk/Fl_String_Hash.h\
	efltk/Fl_Ptr_Hash.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Translator.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl.h
lib/Fl_Util.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/filename.h\
	efltk/Fl_Util.h\
	config.h
lib/Fl_Variant.o :	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	config.h
lib/Fl_WM.o :	efltk/Fl_Callback_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_utf8.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl.h\
	efltk/Fl_WM.h\
	config.h
lib/Fl_Widget.o :	config.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/Fl_Window.o :	efltk/Fl_WM.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h\
	config.h
lib/Fl_Window_fullscreen.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h
lib/Fl_Window_hotspot.o :	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h
lib/Fl_Window_iconize.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	config.h
lib/Fl_Xpm.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h
lib/Fl_abort.o :	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/vsnprintf.h\
	efltk/Fl.h\
	efltk/Enumerations.h\
	config.h
lib/Fl_add_idle.o :	efltk/Fl.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h
lib/Fl_arg.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h
lib/Fl_compose.o :	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/Fl.h\
	efltk/Enumerations.h\
	config.h
lib/Fl_display.o :	efltk/Fl.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	config.h
lib/Fl_get_key.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl.h\
	src/core/Fl_get_key_win32.cpp\
	config.h
lib/Fl_init.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl_Config.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_MDI_Window.h\
	efltk/Fl.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Box.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Workspace.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/fl_draw.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Tooltip.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h
lib/Fl_key_name.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h
lib/Fl_lock.o :	efltk/Fl.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	config.h
lib/Fl_own_colormap.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl.h\
	config.h
lib/Fl_visual.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl.h\
	config.h
lib/KStoUCS.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h
lib/filename.o :	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Flags.h\
	config.h
lib/filename_list.o :	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl_Flags.h\
	config.h
lib/filename_match.o :	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Flags.h
lib/fl_arc.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/fl_math.h
lib/fl_arci.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	config.h\
	efltk/fl_math.h
lib/fl_blit.o :	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h
lib/fl_blit_1.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h
lib/fl_blit_a.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h
lib/fl_blit_n.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h
lib/fl_call_main.o :	config.h
lib/fl_clip.o :	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/fl_draw.h\
	config.h
lib/fl_color.o :	src/core/fl_color_x.cpp\
	src/core/Fl_XColor.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	config.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl.h\
	src/core/fl_color_win32.cpp\
	efltk/Fl_Renderer.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	src/core/fl_cmap.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h
lib/fl_converters.o :	src/core/headers/dingbats_.h\
	src/core/headers/symbol_.h\
	src/core/headers/koi8_u.h\
	src/core/headers/koi8_r.h\
	src/core/headers/iso8859_16.h\
	src/core/headers/iso8859_15.h\
	src/core/headers/iso8859_14.h\
	src/core/headers/iso8859_13.h\
	src/core/headers/iso8859_11.h\
	src/core/headers/iso8859_10.h\
	src/core/headers/iso8859_9e.h\
	src/core/headers/iso8859_9.h\
	src/core/headers/iso8859_8.h\
	src/core/headers/iso8859_7.h\
	src/core/headers/iso8859_6.h\
	src/core/headers/iso8859_5.h\
	src/core/headers/iso8859_4.h\
	src/core/headers/iso8859_3.h\
	src/core/headers/iso8859_2.h\
	src/core/headers/iso8859_1.h\
	src/core/fl_iconv_converters.cpp\
	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	config.h
lib/fl_cursor.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h
lib/fl_curve.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/fl_math.h
lib/fl_diamond_box.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h
lib/fl_dnd.o :	src/core/fl_dnd_x.cpp\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	src/core/fl_dnd_win32.cpp\
	config.h
lib/fl_draw.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/fl_math.h
lib/fl_draw_image.o :	src/core/fl_draw_image_x_2.cpp\
	src/core/Fl_XColor.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	config.h\
	src/core/fl_draw_image_x.cpp\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	src/core/fl_draw_image_win32_2.cpp\
	src/core/fl_draw_image_win32.cpp
lib/fl_draw_pixmap.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h
lib/fl_font.o :	src/core/fl_font_x.cpp\
	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_String.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl.h\
	efltk/Fl_String_Hash.h\
	efltk/Fl_Ptr_Hash.h\
	src/core/fl_font_xft.cpp\
	src/core/fl_font_win32.cpp\
	config.h\
	efltk/fl_math.h
lib/fl_glyph.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h
lib/fl_labeltype.o :	config.h\
	efltk/Fl_Image.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Export.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_draw.h
lib/fl_list_fonts.o :	src/core/fl_list_fonts_x.cpp\
	config.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	src/core/fl_list_fonts_win32.cpp\
	efltk/fl_utf8.h\
	efltk/Fl.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h
lib/fl_load_plugin.o :	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Flags.h\
	efltk/fl_load_plugin.h\
	config.h
lib/fl_locale.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl.h
lib/fl_map.o :	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h
lib/fl_oval_box.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Boxtype.h
lib/fl_overlay.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/x.h\
	efltk/win32.h\
	config.h
lib/fl_overlay_visual.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl.h\
	config.h
lib/fl_plastic_box.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h
lib/fl_rect.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	config.h
lib/fl_rgb.o :	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/x.h\
	efltk/win32.h\
	config.h
lib/fl_round_box.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h
lib/fl_rounded_box.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Boxtype.h
lib/fl_scroll_area.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/x.h\
	efltk/win32.h\
	config.h
lib/fl_shadow_box.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Boxtype.h
lib/fl_stretch.o :	efltk/Fl.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	config.h
lib/fl_theme.o :	efltk/Fl_Config.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Ptr_List.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_load_plugin.h\
	efltk/vsnprintf.h\
	efltk/Fl.h\
	config.h
lib/fl_utf8.o :	src/core/headers/case.h\
	src/core/headers/spacing.h\
	config.h
lib/fl_vertex.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	config.h\
	efltk/fl_math.h
lib/scandir.o :	src/core/scandir_win32.cpp\
	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Exception.h\
	efltk/fl_utf8.h\
	config.h
lib/vsnprintf.o :	efltk/vsnprintf.h\
	config.h
lib/Fl_Database.o :	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Thread.h\
	efltk/Fl_Thread_Linux.h\
	efltk/Fl_Thread_w32.h\
	efltk/Fl_Exception.h
lib/Fl_Params.o :	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h
lib/Fl_Query.o :	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Thread.h\
	efltk/Fl_Thread_Linux.h\
	efltk/Fl_Thread_w32.h\
	efltk/Fl_Exception.h
lib/Fl_Align_Group.o :	efltk/Fl_Align_Group.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_draw.h
lib/Fl_Bar.o :	efltk/Fl_Bar.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/Fl_Box.o :	efltk/Fl_Box.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h
lib/Fl_Browser.o :	efltk/Fl_Bitmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Export.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Browser.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
lib/Fl_Button.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Button.h\
	efltk/Fl.h
lib/Fl_Calendar.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl.h\
	efltk/Fl_Calendar.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Box.h\
	efltk/Fl_Popup_Window.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h
lib/Fl_Check_Button.o :	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_draw.h\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl.h
lib/Fl_Choice.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Choice.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
lib/Fl_Clock.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Clock.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h\
	efltk/fl_math.h
lib/Fl_Color_Chooser.o :	efltk/Fl_Return_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	config.h\
	efltk/Fl_Item.h\
	efltk/fl_draw.h\
	efltk/Fl_Color_Chooser.h\
	efltk/Fl_Value_Input.h\
	efltk/Fl_Float_Input.h\
	efltk/Fl_Numeric_Input.h\
	efltk/Fl_Input.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Choice.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Box.h\
	efltk/Fl.h\
	efltk/fl_math.h
lib/Fl_Date_Time_Input.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Calendar.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Box.h\
	efltk/Fl_Popup_Window.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Pixmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Masked_Input.h\
	efltk/Fl_Input.h\
	efltk/Fl_Date_Time_Input.h
lib/Fl_Dial.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Dial.h\
	efltk/Fl_Valuator.h\
	efltk/Fl.h\
	config.h\
	efltk/fl_math.h
lib/Fl_Dialog.o :	efltk/Fl_Dialog.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Scroll.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Group.h\
	efltk/Fl_Window.h\
	efltk/fl_draw.h\
	efltk/fl_ask.h\
	efltk/Fl_Pixmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Multi_Tabs.h\
	efltk/Fl_Input.h\
	efltk/Fl_Box.h\
	efltk/Fl_Button.h\
	efltk/Fl.h\
	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	config.h
lib/Fl_Directory_DS.o :	efltk/Fl_Pixmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Export.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Directory_DS.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_String_List.h\
	config.h
lib/Fl_Double_Window.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Double_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h
lib/Fl_FileBrowser.o :	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/filename.h\
	efltk/Fl_Util.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Flags.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Color.h\
	efltk/fl_ask.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Pixmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_FileBrowser.h\
	efltk/Fl_Directory_DS.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_ListView_Item.h\
	efltk/Fl_Image_List.h\
	efltk/Fl.h\
	efltk/Fl_ListView.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_ListView_Header.h\
	efltk/vsnprintf.h\
	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	config.h
lib/Fl_FileInput.o :	efltk/Fl_FileInput.h\
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/Fl_File_Dialog.o :	src/widgets/Pixmaps.h\
	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl_Dialog.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Scroll.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Group.h\
	efltk/Fl_Window.h\
	efltk/fl_utf8.h\
	efltk/fl_draw.h\
	efltk/fl_ask.h\
	efltk/Fl_Pixmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Divider.h\
	efltk/Fl_File_Dialog.h\
	efltk/Fl_FileBrowser.h\
	efltk/Fl_Directory_DS.h\
	efltk/Fl_ListView_Item.h\
	efltk/Fl_Image_List.h\
	efltk/Fl.h\
	efltk/Fl_ListView.h\
	efltk/Fl_ListView_Header.h\
	efltk/Fl_Highlight_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Box.h\
	efltk/Fl_Item.h\
	efltk/Fl_Input_Browser.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Input.h\
	efltk/Fl_Image_Cache.h
lib/Fl_Float_Input.o :	efltk/Fl_Float_Input.h\
	efltk/Fl_Numeric_Input.h\
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_ask.h\
	efltk/Fl.h
lib/Fl_Help_Dialog.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl_Pixmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Help_Dialog.h\
	efltk/Fl_Simple_Html.h\
	efltk/Fl_Image_Cache.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h\
	efltk/Fl_File_Dialog.h\
	efltk/Fl_FileBrowser.h\
	efltk/Fl_Directory_DS.h\
	efltk/Fl_ListView_Item.h\
	efltk/Fl_Image_List.h\
	efltk/Fl_ListView.h\
	efltk/Fl_ListView_Header.h\
	efltk/Fl_Highlight_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Box.h\
	efltk/Fl_Item.h\
	efltk/Fl_Input_Browser.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Input.h\
	efltk/Fl_Item_Group.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Main_Window.h\
	efltk/Fl_Tool_Bar.h\
	efltk/Fl_Menu_Button.h\
	efltk/Fl_Bar.h\
	efltk/Fl_Pack.h\
	efltk/Fl_Double_Window.h
lib/Fl_Highlight_Button.o :	efltk/Fl_Highlight_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/Fl_Input.o :	efltk/Fl_Menu_Button.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	config.h\
	efltk/fl_utf8.h\
	efltk/fl_ask.h\
	efltk/fl_draw.h\
	efltk/Fl_Input.h\
	efltk/Fl.h\
	efltk/fl_math.h
lib/Fl_Input_Browser.o :	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Fl_Flags.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Browser.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h\
	efltk/Fl_Input_Browser.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Input.h
lib/Fl_Item.o :	efltk/Fl_Divider.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Item_Group.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/fl_draw.h\
	efltk/Fl_Item.h
lib/Fl_Light_Button.o :	efltk/Fl_Light_Button.h\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/Fl_ListView.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_ListView.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_ListView_Item.h\
	efltk/Fl_Image_List.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl.h\
	efltk/Fl_ListView_Header.h
lib/Fl_ListView_Header.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_ListView.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_ListView_Item.h\
	efltk/Fl_Image_List.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl.h\
	efltk/Fl_ListView_Header.h
lib/Fl_ListView_Item.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_ListView.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_ListView_Item.h\
	efltk/Fl_Image_List.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl.h\
	efltk/Fl_ListView_Header.h
lib/Fl_MDI_Bar.o :	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_MDI_Window.h\
	efltk/Fl.h\
	efltk/Fl_Box.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Workspace.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/fl_draw.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_MDI_Bar.h
lib/Fl_MDI_Window.o :	efltk/Fl_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_MDI_Bar.h\
	efltk/Fl_MDI_Window.h\
	efltk/Fl.h\
	efltk/Fl_Button.h\
	efltk/Fl_Box.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Workspace.h\
	efltk/fl_draw.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	config.h
lib/Fl_Main_Window.o :	efltk/Fl_Main_Window.h\
	efltk/Fl_Tool_Bar.h\
	efltk/Fl_Menu_Button.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Bar.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl.h\
	efltk/Fl_Pack.h\
	efltk/Fl_Box.h\
	efltk/Fl_Button.h\
	efltk/Fl_Double_Window.h
lib/Fl_Masked_Input.o :	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Masked_Input.h\
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_draw.h\
	efltk/Fl.h\
	efltk/fl_math.h
lib/Fl_Menu.o :	efltk/Fl_Image.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Export.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	efltk/Fl_Tooltip.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	efltk/Fl_Item.h\
	efltk/fl_draw.h\
	efltk/Fl_Choice.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	config.h\
	efltk/fl_math.h
lib/Fl_Menu_.o :	efltk/Fl_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl.h
lib/Fl_Menu_Bar.o :	config.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Item.h\
	efltk/Fl.h
lib/Fl_Menu_Button.o :	efltk/Fl_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/fl_draw.h\
	efltk/Fl_Menu_Button.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl.h
lib/Fl_Menu_Item.o :	efltk/Fl.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Menu_Button.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Divider.h\
	efltk/Fl_Item_Group.h\
	efltk/Fl_Item.h
lib/Fl_Menu_Window.o :	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl.h\
	config.h\
	efltk/fl_math.h
lib/Fl_Menu_add.o :	src/core/ARRAY.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Divider.h\
	efltk/Fl_Item_Group.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Item.h
lib/Fl_Menu_global.o :	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
lib/Fl_Multi_Image.o :	efltk/Fl_Multi_Image.h\
	efltk/Fl_Image.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Export.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h
lib/Fl_Multi_Tabs.o :	efltk/Fl_Image.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Export.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	efltk/Fl_Scroll.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/fl_draw.h\
	efltk/Fl_Multi_Tabs.h\
	efltk/Fl.h\
	efltk/fl_math.h
lib/Fl_Numeric_Input.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/Fl_Numeric_Input.h\
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_ask.h\
	efltk/Fl.h
lib/Fl_Output.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Output.h\
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/Fl_Overlay_Window.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Overlay_Window.h\
	efltk/Fl_Double_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h
lib/Fl_Pack.o :	efltk/Fl_Pack.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h
lib/Fl_Popup_Window.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl.h\
	efltk/Fl_Popup_Window.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h
lib/Fl_ProgressBar.o :	efltk/Fl_ProgressBar.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h
lib/Fl_Radio_Button.o :	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_draw.h\
	efltk/Fl_Radio_Button.h\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl.h
lib/Fl_Repeat_Button.o :	efltk/Fl_Repeat_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/Fl_Return_Button.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Return_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/Fl_Roller.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Roller.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	efltk/fl_math.h
lib/Fl_Scroll.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Scroll.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
lib/Fl_Scrollbar.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h\
	efltk/fl_math.h
lib/Fl_Shaped_Window.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Shaped_Window.h\
	efltk/Fl_Bitmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Renderer.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	efltk/Fl_Double_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	config.h
lib/Fl_Simple_Html.o :	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	config.h\
	efltk/fl_utf8.h\
	efltk/vsnprintf.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl.h\
	efltk/Fl_Simple_Html.h\
	efltk/Fl_Image_Cache.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h
lib/Fl_Single_Window.o :	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h
lib/Fl_Slider.o :	config.h\
	efltk/vsnprintf.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl.h\
	efltk/fl_math.h
lib/Fl_Tabs.o :	efltk/Fl_Tooltip.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	efltk/fl_draw.h\
	efltk/Fl_Tabs.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h
lib/Fl_Text_Buffer.o :	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/Fl_Text_Buffer.h\
	efltk/Fl_Ptr_Stack.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	config.h
lib/Fl_Text_Display.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/fl_utf8.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Text_Display.h\
	efltk/Fl_Text_Buffer.h\
	efltk/Fl_Ptr_Stack.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl.h\
	config.h
lib/Fl_Text_Editor.o :	efltk/Fl_Menu_Button.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Text_Editor.h\
	efltk/Fl_Text_Display.h\
	efltk/Fl_Text_Buffer.h\
	efltk/Fl_Ptr_Stack.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/fl_draw.h\
	efltk/Fl.h\
	config.h
lib/Fl_Tile.o :	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Tile.h\
	efltk/Fl.h
lib/Fl_Tool_Bar.o :	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Item.h\
	efltk/Fl.h\
	efltk/fl_draw.h\
	efltk/Fl_Divider.h\
	efltk/Fl_Tool_Bar.h\
	efltk/Fl_Menu_Button.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Bar.h\
	efltk/fl_math.h
lib/Fl_Tooltip.o :	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_draw.h\
	efltk/Fl_Tooltip.h\
	efltk/Fl.h
lib/Fl_Valuator.o :	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	efltk/fl_math.h
lib/Fl_Value_Input.o :	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Value_Input.h\
	efltk/Fl_Float_Input.h\
	efltk/Fl_Numeric_Input.h\
	efltk/Fl_Input.h\
	efltk/Fl_Valuator.h\
	efltk/Fl.h\
	efltk/fl_math.h
lib/Fl_Value_Slider.o :	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Output.h\
	efltk/Fl_Input.h\
	efltk/fl_draw.h\
	efltk/Fl_Value_Slider.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl.h
lib/Fl_Workspace.o :	efltk/Fl_MDI_Bar.h\
	efltk/Fl_MDI_Window.h\
	efltk/Fl.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Button.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Box.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Workspace.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/fl_draw.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	config.h
lib/fl_ask.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	src/core/fl_internal.h\
	efltk/Fl_Translator.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	config.h\
	efltk/vsnprintf.h\
	efltk/Fl_Pixmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Secret_Input.h\
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Return_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Box.h\
	efltk/fl_ask.h\
	efltk/fl_draw.h\
	efltk/Fl.h
lib/fl_engraved_label.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Boxtype.h
lib/fl_show_colormap.o :	config.h\
	efltk/fl_show_colormap.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/fl_symbols.o :	efltk/Fl_Labeltype.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Color.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Style.h\
	efltk/Fl_Boxtype.h
test/calendar.o :	efltk/fl_utf8.h\
	efltk/Fl_Export.h\
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Button.h\
	efltk/Fl_Calendar.h\
	efltk/Fl_Box.h\
	efltk/Fl_Popup_Window.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
test/checkers.o :	efltk/Fl_Value_Output.h\
	efltk/Fl_Output.h\
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Value_Input.h\
	efltk/Fl_Float_Input.h\
	efltk/Fl_Numeric_Input.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Box.h\
	test/whiteking_4.xbm\
	test/whiteking_3.xbm\
	test/whiteking_2.xbm\
	test/whiteking_1.xbm\
	test/blackking_4.xbm\
	test/blackking_3.xbm\
	test/blackking_2.xbm\
	test/blackking_1.xbm\
	test/white_4.xbm\
	test/white_3.xbm\
	test/white_2.xbm\
	test/white_1.xbm\
	test/black_4.xbm\
	test/black_3.xbm\
	test/black_2.xbm\
	test/black_1.xbm\
	efltk/fl_ask.h\
	efltk/Fl_Menu_Item.h\
	efltk/fl_draw.h\
	efltk/Fl_Bitmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Double_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl.h
test/clock.o :	test/circle.xbm\
	efltk/fl_ask.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Item.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Menu_Button.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Round_Clock.h\
	efltk/Fl_Clock.h\
	efltk/Fl_Shaped_Window.h\
	efltk/Fl_Bitmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Double_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl.h
test/color_chooser.o :	test/list_visuals.cpp\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	config.h\
	efltk/fl_message.h\
	efltk/fl_ask.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	efltk/fl_draw.h\
	efltk/Fl_Color_Chooser.h\
	efltk/Fl_Value_Input.h\
	efltk/Fl_Float_Input.h\
	efltk/Fl_Numeric_Input.h\
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Choice.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Return_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Box.h\
	efltk/fl_show_colormap.h\
	efltk/Fl_Renderer.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Window.h
test/cube.o :	efltk/gl.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Color.h\
	efltk/Fl_Gl_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Radio_Light_Button.h\
	efltk/Fl_Light_Button.h\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Box.h\
	efltk/Fl.h\
	config.h
lib/Fl_Gl_Choice.o :	src/opengl/Fl_Gl_Choice.h\
	efltk/gl.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Color.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h
lib/Fl_Gl_Overlay.o :	efltk/Fl_Gl_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	src/opengl/Fl_Gl_Choice.h\
	efltk/gl.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl.h\
	config.h
lib/Fl_Gl_Window.o :	efltk/Fl_Gl_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	src/opengl/Fl_Gl_Choice.h\
	efltk/gl.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl.h\
	config.h
lib/gl_draw.o :	src/opengl/Fl_Gl_Choice.h\
	efltk/gl.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Color.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_draw.h\
	config.h
lib/gl_start.o :	efltk/fl_draw.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_String_List.h\
	efltk/Fl_String.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	src/opengl/Fl_Gl_Choice.h\
	efltk/gl.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Window.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h\
	config.h
test/cursor.o :	efltk/Fl_Box.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/fl_draw.h\
	efltk/Fl_Choice.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Hor_Value_Slider.h\
	efltk/Fl_Value_Slider.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Window.h\
	efltk/Fl.h


# %TargetInfo src/db/odbc/Fl_ODBC_Database.cpp	SourceOrHeader,	UniqueId=0x4000cd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/db/odbc/fl_odbc.cpp	SourceOrHeader,	UniqueId=0x4000ce,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/xml/Fl_XmlCtx.cpp	SourceOrHeader,	UniqueId=0x4000f9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/xml/Fl_XmlDoc.cpp	SourceOrHeader,	UniqueId=0x4000fa,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/xml/Fl_XmlNode.cpp	SourceOrHeader,	UniqueId=0x4000fb,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/xml/Fl_XmlParser.cpp	SourceOrHeader,	UniqueId=0x4000fc,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/xml/Fl_XmlTokenizer.cpp	SourceOrHeader,	UniqueId=0x4000fd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/images/Fl_Images.cpp	SourceOrHeader,	UniqueId=0x4000fe,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/images/Fl_Jpeg.cpp	SourceOrHeader,	UniqueId=0x4000ff,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/images/Fl_Png.cpp	SourceOrHeader,	UniqueId=0x400100,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/arc.cpp	SourceOrHeader,	UniqueId=0x400185,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/ask.cpp	SourceOrHeader,	UniqueId=0x400187,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/bitmap.cpp	SourceOrHeader,	UniqueId=0x400189,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/boxtype.cpp	SourceOrHeader,	UniqueId=0x40018d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/browser.cpp	SourceOrHeader,	UniqueId=0x40018f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/button.cpp	SourceOrHeader,	UniqueId=0x400193,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/buttons.cpp	SourceOrHeader,	UniqueId=0x400196,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl.cpp	SourceOrHeader,	UniqueId=0x4001a0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Bitmap.cpp	SourceOrHeader,	UniqueId=0x4001a1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Bmp.cpp	SourceOrHeader,	UniqueId=0x4001a2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Boxtype.cpp	SourceOrHeader,	UniqueId=0x4001a3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Buffer.cpp	SourceOrHeader,	UniqueId=0x4001a4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Config.cpp	SourceOrHeader,	UniqueId=0x4001a5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Data_Fields.cpp	SourceOrHeader,	UniqueId=0x4001a6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Data_Source.cpp	SourceOrHeader,	UniqueId=0x4001a7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Date_Time.cpp	SourceOrHeader,	UniqueId=0x4001a8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Exception.cpp	SourceOrHeader,	UniqueId=0x4001a9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Gif.cpp	SourceOrHeader,	UniqueId=0x4001aa,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Group.cpp	SourceOrHeader,	UniqueId=0x4001ab,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Hashs.cpp	SourceOrHeader,	UniqueId=0x4001ac,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Image.cpp	SourceOrHeader,	UniqueId=0x4001ad,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Image_Filter.cpp	SourceOrHeader,	UniqueId=0x4001ae,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Lists.cpp	SourceOrHeader,	UniqueId=0x4001af,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Maps.cpp	SourceOrHeader,	UniqueId=0x4001b0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Pixmap.cpp	SourceOrHeader,	UniqueId=0x4001b1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Renderer.cpp	SourceOrHeader,	UniqueId=0x4001b2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_String.cpp	SourceOrHeader,	UniqueId=0x4001b3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Style.cpp	SourceOrHeader,	UniqueId=0x4001b4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Style_Set.cpp	SourceOrHeader,	UniqueId=0x4001b5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Thread.cpp	SourceOrHeader,	UniqueId=0x4001b6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Translator.cpp	SourceOrHeader,	UniqueId=0x4001b7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Util.cpp	SourceOrHeader,	UniqueId=0x4001b8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Variant.cpp	SourceOrHeader,	UniqueId=0x4001b9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_WM.cpp	SourceOrHeader,	UniqueId=0x4001ba,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Widget.cpp	SourceOrHeader,	UniqueId=0x4001bb,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Window.cpp	SourceOrHeader,	UniqueId=0x4001bc,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Window_fullscreen.cpp	SourceOrHeader,	UniqueId=0x4001bd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Window_hotspot.cpp	SourceOrHeader,	UniqueId=0x4001be,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Window_iconize.cpp	SourceOrHeader,	UniqueId=0x4001bf,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Xpm.cpp	SourceOrHeader,	UniqueId=0x4001c0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_abort.cpp	SourceOrHeader,	UniqueId=0x4001c1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_add_idle.cpp	SourceOrHeader,	UniqueId=0x4001c2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_arg.cpp	SourceOrHeader,	UniqueId=0x4001c3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_compose.cpp	SourceOrHeader,	UniqueId=0x4001c4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_display.cpp	SourceOrHeader,	UniqueId=0x4001c5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_get_key.cpp	SourceOrHeader,	UniqueId=0x4001c6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_init.cpp	SourceOrHeader,	UniqueId=0x4001c7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_key_name.cpp	SourceOrHeader,	UniqueId=0x4001c8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_lock.cpp	SourceOrHeader,	UniqueId=0x4001c9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_own_colormap.cpp	SourceOrHeader,	UniqueId=0x4001ca,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_visual.cpp	SourceOrHeader,	UniqueId=0x4001cb,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/KStoUCS.cpp	SourceOrHeader,	UniqueId=0x4001cc,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/cmap.cpp	SourceOrHeader,	UniqueId=0x4001cd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/filename.cpp	SourceOrHeader,	UniqueId=0x4001ce,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/filename_list.cpp	SourceOrHeader,	UniqueId=0x4001cf,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/filename_match.cpp	SourceOrHeader,	UniqueId=0x4001d0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/filename_setext.cpp	SourceOrHeader,	UniqueId=0x4001d1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_arc.cpp	SourceOrHeader,	UniqueId=0x4001d2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_arci.cpp	SourceOrHeader,	UniqueId=0x4001d3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_blit.cpp	SourceOrHeader,	UniqueId=0x4001d4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_blit_1.cpp	SourceOrHeader,	UniqueId=0x4001d5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_blit_a.cpp	SourceOrHeader,	UniqueId=0x4001d6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_blit_n.cpp	SourceOrHeader,	UniqueId=0x4001d7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_call_main.c	SourceOrHeader,	UniqueId=0x4001d8,	TargetType=C,	IDEFlags=0x4
# %TargetInfo src/core/fl_clip.cpp	SourceOrHeader,	UniqueId=0x4001d9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_color.cpp	SourceOrHeader,	UniqueId=0x4001da,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_converters.cpp	SourceOrHeader,	UniqueId=0x4001db,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_cursor.cpp	SourceOrHeader,	UniqueId=0x4001dc,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_curve.cpp	SourceOrHeader,	UniqueId=0x4001dd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_diamond_box.cpp	SourceOrHeader,	UniqueId=0x4001de,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_dnd.cpp	SourceOrHeader,	UniqueId=0x4001df,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw.cpp	SourceOrHeader,	UniqueId=0x4001e0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw_image.cpp	SourceOrHeader,	UniqueId=0x4001e1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw_pixmap.cpp	SourceOrHeader,	UniqueId=0x4001e2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_font.cpp	SourceOrHeader,	UniqueId=0x4001e3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_glyph.cpp	SourceOrHeader,	UniqueId=0x4001e4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_iconv_converters.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x4001e5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_labeltype.cpp	SourceOrHeader,	UniqueId=0x4001e6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_list_fonts.cpp	SourceOrHeader,	UniqueId=0x4001e7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_load_plugin.cpp	SourceOrHeader,	UniqueId=0x4001e8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_locale.cpp	SourceOrHeader,	UniqueId=0x4001e9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_map.cpp	SourceOrHeader,	UniqueId=0x4001ea,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_oval_box.cpp	SourceOrHeader,	UniqueId=0x4001eb,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_overlay.cpp	SourceOrHeader,	UniqueId=0x4001ec,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_overlay_visual.cpp	SourceOrHeader,	UniqueId=0x4001ed,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_plastic_box.cpp	SourceOrHeader,	UniqueId=0x4001ee,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_rect.cpp	SourceOrHeader,	UniqueId=0x4001ef,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_rgb.cpp	SourceOrHeader,	UniqueId=0x4001f0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_round_box.cpp	SourceOrHeader,	UniqueId=0x4001f1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_rounded_box.cpp	SourceOrHeader,	UniqueId=0x4001f2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_scroll_area.cpp	SourceOrHeader,	UniqueId=0x4001f3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_shadow_box.cpp	SourceOrHeader,	UniqueId=0x4001f4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_stretch.cpp	SourceOrHeader,	UniqueId=0x4001f5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_theme.cpp	SourceOrHeader,	UniqueId=0x4001f6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_utf8.cpp	SourceOrHeader,	UniqueId=0x4001f7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_vertex.cpp	SourceOrHeader,	UniqueId=0x4001f8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/scandir.cpp	SourceOrHeader,	UniqueId=0x4001f9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/vsnprintf.c	SourceOrHeader,	UniqueId=0x4001fa,	TargetType=C,	IDEFlags=0x4
# %TargetInfo src/db/Fl_Database.cpp	SourceOrHeader,	UseWorkingFile,	UniqueId=0x4001fc,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/db/Fl_Params.cpp	SourceOrHeader,	UniqueId=0x4001fd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/db/Fl_Query.cpp	SourceOrHeader,	UniqueId=0x4001fe,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Adjuster.cpp	SourceOrHeader,	UniqueId=0x4001ff,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Align_Group.cpp	SourceOrHeader,	UniqueId=0x400200,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Bar.cpp	SourceOrHeader,	UniqueId=0x400201,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Box.cpp	SourceOrHeader,	UniqueId=0x400202,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Browser.cpp	SourceOrHeader,	UniqueId=0x400203,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Button.cpp	SourceOrHeader,	UniqueId=0x400204,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Calendar.cpp	SourceOrHeader,	UniqueId=0x400205,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Check_Button.cpp	SourceOrHeader,	UniqueId=0x400206,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Choice.cpp	SourceOrHeader,	UniqueId=0x400207,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Clock.cpp	SourceOrHeader,	UniqueId=0x400208,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Color_Chooser.cpp	SourceOrHeader,	UniqueId=0x400209,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Date_Time_Input.cpp	SourceOrHeader,	UniqueId=0x40020a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Dial.cpp	SourceOrHeader,	UniqueId=0x40020b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Dialog.cpp	SourceOrHeader,	UniqueId=0x40020c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Directory_DS.cpp	SourceOrHeader,	UniqueId=0x40020d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Double_Window.cpp	SourceOrHeader,	UniqueId=0x40020e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_FileBrowser.cpp	SourceOrHeader,	UniqueId=0x40020f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_FileInput.cpp	SourceOrHeader,	UniqueId=0x400210,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_File_Dialog.cpp	SourceOrHeader,	UniqueId=0x400211,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Float_Input.cpp	SourceOrHeader,	UniqueId=0x400212,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Help_Dialog.cpp	SourceOrHeader,	UniqueId=0x400213,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Highlight_Button.cpp	SourceOrHeader,	UniqueId=0x400214,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Input.cpp	SourceOrHeader,	UniqueId=0x400215,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Input_Browser.cpp	SourceOrHeader,	UniqueId=0x400216,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Item.cpp	SourceOrHeader,	UniqueId=0x400217,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Light_Button.cpp	SourceOrHeader,	UniqueId=0x400218,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_ListView.cpp	SourceOrHeader,	UniqueId=0x400219,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_ListView_Header.cpp	SourceOrHeader,	UniqueId=0x40021a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_ListView_Item.cpp	SourceOrHeader,	UniqueId=0x40021b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_MDI_Bar.cpp	SourceOrHeader,	UniqueId=0x40021c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_MDI_Window.cpp	SourceOrHeader,	UniqueId=0x40021d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Main_Window.cpp	SourceOrHeader,	UniqueId=0x40021e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Masked_Input.cpp	SourceOrHeader,	UniqueId=0x40021f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu.cpp	SourceOrHeader,	UniqueId=0x400220,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_.cpp	SourceOrHeader,	UniqueId=0x400221,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_Bar.cpp	SourceOrHeader,	UniqueId=0x400222,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_Button.cpp	SourceOrHeader,	UniqueId=0x400223,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_Item.cpp	SourceOrHeader,	UniqueId=0x400224,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_Window.cpp	SourceOrHeader,	UniqueId=0x400225,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_add.cpp	SourceOrHeader,	UniqueId=0x400226,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_global.cpp	SourceOrHeader,	UniqueId=0x400227,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Multi_Image.cpp	SourceOrHeader,	UniqueId=0x400228,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Multi_Tabs.cpp	SourceOrHeader,	UniqueId=0x400229,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Numeric_Input.cpp	SourceOrHeader,	UniqueId=0x40022a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Output.cpp	SourceOrHeader,	UniqueId=0x40022b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Overlay_Window.cpp	SourceOrHeader,	UniqueId=0x40022c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Pack.cpp	SourceOrHeader,	UniqueId=0x40022d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Popup_Window.cpp	SourceOrHeader,	UniqueId=0x40022e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_ProgressBar.cpp	SourceOrHeader,	UniqueId=0x40022f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Radio_Button.cpp	SourceOrHeader,	UniqueId=0x400230,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Repeat_Button.cpp	SourceOrHeader,	UniqueId=0x400231,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Return_Button.cpp	SourceOrHeader,	UniqueId=0x400232,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Roller.cpp	SourceOrHeader,	UniqueId=0x400233,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Scroll.cpp	SourceOrHeader,	UniqueId=0x400234,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Scrollbar.cpp	SourceOrHeader,	UniqueId=0x400235,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Shaped_Window.cpp	SourceOrHeader,	UniqueId=0x400236,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Simple_Html.cpp	SourceOrHeader,	UniqueId=0x400237,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Single_Window.cpp	SourceOrHeader,	UniqueId=0x400238,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Slider.cpp	SourceOrHeader,	UniqueId=0x400239,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Tabs.cpp	SourceOrHeader,	UniqueId=0x40023a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Text_Buffer.cpp	SourceOrHeader,	UniqueId=0x40023b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Text_Display.cpp	SourceOrHeader,	UniqueId=0x40023c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Text_Editor.cpp	SourceOrHeader,	UniqueId=0x40023d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Tile.cpp	SourceOrHeader,	UniqueId=0x40023e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Tool_Bar.cpp	SourceOrHeader,	UniqueId=0x40023f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Tooltip.cpp	SourceOrHeader,	UniqueId=0x400240,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Valuator.cpp	SourceOrHeader,	UniqueId=0x400241,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Value_Input.cpp	SourceOrHeader,	UniqueId=0x400242,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Value_Slider.cpp	SourceOrHeader,	UniqueId=0x400243,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Workspace.cpp	SourceOrHeader,	UniqueId=0x400244,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/fl_ask.cpp	SourceOrHeader,	UniqueId=0x400245,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/fl_engraved_label.cpp	SourceOrHeader,	UniqueId=0x400246,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/fl_show_colormap.cpp	SourceOrHeader,	UniqueId=0x400247,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/fl_symbols.cpp	SourceOrHeader,	UniqueId=0x400248,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/calendar.cpp	SourceOrHeader,	UniqueId=0x40024a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/checkers.cpp	SourceOrHeader,	UniqueId=0x40024c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/clock.cpp	SourceOrHeader,	UniqueId=0x40025f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/color_chooser.cpp	SourceOrHeader,	UniqueId=0x400263,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/cube.cpp	SourceOrHeader,	UniqueId=0x400267,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/Fl_Gl_Choice.cpp	SourceOrHeader,	UniqueId=0x40026c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/Fl_Gl_Overlay.cpp	SourceOrHeader,	UniqueId=0x40026d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/Fl_Gl_Window.cpp	SourceOrHeader,	UniqueId=0x40026e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/gl_draw.cpp	SourceOrHeader,	UniqueId=0x40026f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/gl_start.cpp	SourceOrHeader,	UniqueId=0x400270,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/fl_iconv_converters.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400056,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_get_key_win32.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400029,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_win32.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x40002f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_wince.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400030,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_x.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400031,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_color_win32.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400041,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_color_x.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400042,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_dnd_win32.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400048,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_dnd_x.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400049,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw_image_win32.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x40004c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw_image_win32_2.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x40004d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw_image_x.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x40004e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw_image_x_2.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x40004f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_font_win32.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400052,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_font_x.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400053,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_font_xft.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400054,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_list_fonts_win32.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400059,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_list_fonts_x.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x40005a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/scandir_win32.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x40006d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo efltk/Fl_Style.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40006f,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Font.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400070,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Int_List.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400071,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Ptr_List.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400072,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Enumerations.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400073,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Export.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400074,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_String_List.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400075,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_String.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400076,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Labeltype.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400077,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Flags.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400078,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Color.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400079,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Boxtype.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40007a,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40007b,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Group.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40007c,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Widget_List.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40007d,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Widget.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40007e,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Data_Source.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40007f,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Data_Fields.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400080,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Variant.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400081,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Date_Time.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400082,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Exception.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400083,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/fl_utf8.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400084,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_WM.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400085,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/x.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400086,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/win32.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400087,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/aimm.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400088,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/filename.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400089,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Util.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40008a,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40008b,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Tooltip.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40008c,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Bitmap.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40008d,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Image.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40008e,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_PtrList.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40008f,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Renderer.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400090,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/fl_draw.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400091,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/fl_internal.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400092,	TargetType=INC,	IDEFlags=0x4
# %TargetInfo efltk/Fl_Translator.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400093,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Config.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400094,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/vsnprintf.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400095,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_String_Hash.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400096,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Ptr_Hash.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400097,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Image_Filter.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400098,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_String_Stack.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400099,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Callback_List.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40009a,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Ptr_Stack.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40009b,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Map.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40009c,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Pixmap.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40009d,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/fl_load_plugin.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40009e,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Style_Set.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40009f,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Thread.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a0,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Thread_Linux.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a1,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Thread_w32.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a2,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_MDI_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a3,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a4,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Box.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a5,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Workspace.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a6,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Menu_Bar.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a7,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Menu_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a8,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Single_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000a9,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Menu_.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000aa,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Menu_Item.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000ab,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Scrollbar.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000ac,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Slider.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000ad,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Valuator.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000ae,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/Fl_XColor.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000af,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/fl_cmap.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b0,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/dingbats_.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b1,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/symbol_.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b2,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/koi8_u.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b3,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/koi8_r.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b4,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_16.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b5,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_15.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b6,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_14.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b7,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_13.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b8,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_11.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000b9,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_10.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000ba,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_9e.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000bb,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_9.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000bc,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_8.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000bd,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_7.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000be,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_6.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000bf,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_5.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000c0,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_4.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000c1,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_3.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000c2,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_2.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000c3,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/iso8859_1.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000c4,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/case.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000c5,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/headers/spacing.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000c6,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/db/odbc/fl_odbc.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000cf,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/xml/html_entities.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000d9,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_XmlCtx.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000da,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_XmlHandler.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000db,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_XmlNode.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000dc,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_XmlNode_List.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000dd,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Xml.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000de,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_XmlTokenizer.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000df,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_XmlParser.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000e0,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_XmlDoc.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000e1,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Highlight_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000e4,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Light_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000e5,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Check_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000e6,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Radio_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000e7,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Repeat_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000e8,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Return_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000e9,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo config.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4000f1,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Align_Group.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40014b,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Bar.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40014c,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Browser.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40014d,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Calendar.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40014e,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Popup_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40014f,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Choice.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400150,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Clock.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400151,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Item.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400152,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Color_Chooser.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400153,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Value_Input.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400154,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Float_Input.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400155,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Numeric_Input.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400156,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Input.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400157,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Masked_Input.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400158,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Date_Time_Input.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400159,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Dial.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40015a,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Dialog.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40015b,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Scroll.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40015c,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/fl_ask.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40015d,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Multi_Tabs.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40015e,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Directory_DS.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40015f,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Double_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400160,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_FileBrowser.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400161,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_ListView_Item.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400162,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Image_List.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400163,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_ListView.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400164,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_ListView_Header.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400165,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_FileInput.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400166,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/widgets/Pixmaps.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400167,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Divider.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400168,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_File_Dialog.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400169,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Input_Browser.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40016a,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Image_Cache.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40016b,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Help_Dialog.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40016c,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Simple_Html.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40016d,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Item_Group.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40016e,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Main_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40016f,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Tool_Bar.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400170,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Menu_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400171,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Pack.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400172,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_MDI_Bar.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400173,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/core/ARRAY.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400174,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Multi_Image.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400175,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Output.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400176,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Overlay_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400177,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_ProgressBar.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400178,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Roller.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400179,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Shaped_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40017a,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Tabs.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40017b,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Text_Buffer.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40017c,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Text_Display.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40017d,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Text_Editor.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40017e,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Tile.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40017f,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Value_Slider.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400180,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Secret_Input.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400181,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/fl_show_colormap.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400182,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Toggle_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40018a,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo test/file_small.xpm	SourceOrHeader,	IncludeFile,	UniqueId=0x400190,	TargetType=XPM,	IDEFlags=0xe
# %TargetInfo test/folder_small.xpm	SourceOrHeader,	IncludeFile,	UniqueId=0x400191,	TargetType=XPM,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Buffer.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400198,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/fl_math.h	SourceOrHeader,	IncludeFile,	UniqueId=0x4001fb,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Value_Output.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40024d,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo test/whiteking_4.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x40024e,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/whiteking_3.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x40024f,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/whiteking_2.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400250,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/whiteking_1.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400251,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/blackking_4.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400252,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/blackking_3.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400253,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/blackking_2.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400254,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/blackking_1.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400255,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/white_4.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400256,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/white_3.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400257,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/white_2.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400258,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/white_1.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400259,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/black_4.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x40025a,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/black_3.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x40025b,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/black_2.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x40025c,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/black_1.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x40025d,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo test/circle.xbm	SourceOrHeader,	IncludeFile,	UniqueId=0x400260,	TargetType=XBM,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Round_Clock.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400261,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo test/list_visuals.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x400264,	TargetType=C++,	IDEFlags=0xe
# %TargetInfo efltk/fl_message.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400265,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/gl.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400268,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Gl_Window.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400269,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Radio_Light_Button.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40026a,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/opengl/Fl_Gl_Choice.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400271,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo /distr/develop/CVS/efltk/test/cursor.cpp	SourceOrHeader,	UniqueId=0x400273,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo efltk/Fl_Hor_Value_Slider.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400274,	TargetType=INC,	IDEFlags=0xe


# %UniqueId:	0x400001
# %TreeIndex:	0x2
# %IncludesFolder
# %Folder
# "*** Includes ***" : 
#
# %UniqueId:	0x4000eb
# %TreeIndex:	0x1
# %IDEFlags:	0
# %Folder
# "all" : 
#	0x4000ec
#	0x400183
#
# %UniqueId:	0x4000ec
# %IDEFlags:	0
# %Folder
# "efltk" : 
#	0x400002
#	0x4000ed
#	0x4000f2
#	0x40026b
#	0x4000f8
#
# %UniqueId:	0x400183
# %IDEFlags:	0
# %Folder
# "tests" : 
#	0x400184
#	0x400186
#	0x400188
#	0x40018c
#	0x40018e
#	0x400192
#	0x400195
#	0x400249
#	0x40024b
#	0x40025e
#	0x400262
#	0x400266
#	0x400272
#
