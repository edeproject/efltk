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
# %FirstUniqueId:	0x400358
PROJECT_DIR = .

IDE_WORKING_DIR = $(PROJECT_DIR)

MAKE = make

IDE_BLIND_INCLUDES = -I- -I./ -Iefltk -Isrc -Isrc/images -Isrc/xml -Isrc/db/odbc -Itest -Itest/net -Itest/db

DEPEND_INCLUDES = -I- -I./ -Iefltk -Isrc -Isrc/images -Isrc/xml -Isrc/db/odbc -Itest -Itest/net -Itest/db

ALLDEFINES = $(ALLINCLUDES)

ALLINCLUDES = $(INCLUDES)

IDE_BLIND_LIBS = -L./

MAKEFLAGS = $(MAKEOPTIONS)

MAKEOPTIONS = -j1

CCLINK = $(CC)

LD = $(CC)

LDOPTIONS = $(IDE_BLIND_LDOPTIONS) $(LDFLAGS)

LDFLAGS = -L. -L./lib -L/usr/X11R6/lib -lXext -liconv -lodbc

IDE_BLIND_LDOPTIONS = -L./

IDE_PROJECT_TOOLS = MAKE CCLINK G++ IDE_C_PARSER GCC TAGS IDE_CXX_PARSER

IDE_RCS_TYPE = none

G++ = g++

CXX = g++

CXXFLAGS = $(INCLUDES) $(CXXWARNFLAGS) $(CXXDEBUGFLAGS) $(CXXOPTIMIZEFLAGS) $(CXXCODEFLAGS) $(CXXLANGFLAGS) $(CXXSPECIFICFLAGS)

INCLUDES = -I./ -DFL_SHARED -DHAVE_CONFIG_H

CXXWARNFLAGS = -Wall

CXXDEBUGFLAGS = -g

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

CDEBUGFLAGS = -g

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
	lib/Fl_Gdi.o\
	lib/Fl_Gif.o\
	lib/Fl_Group.o\
	lib/Fl_Hashs.o\
	lib/Fl_Image.o\
	lib/Fl_Image_Filter.o\
	lib/Fl_Lists.o\
	lib/Fl_Maps.o\
	lib/Fl_Pixmap.o\
	lib/Fl_PostScript.o\
	lib/Fl_Printer.o\
	lib/Fl_Renderer.o\
	lib/Fl_Socket.o\
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
	lib/fl_symbols.o\
	lib/Fl_Database.o\
	lib/Fl_Params.o\
	lib/Fl_Query.o
	rm -f $@
	$(LD) -shared -o $@ $^ $(LDOPTIONS)

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
	pwd
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

# %UniqueId:	0x400272
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/cursor ::	test/cursor.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400284
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/editor ::	test/editor.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x40033a
# %TargetType:	C_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/sockets ::	test/socket.o\
	test/Fl_Socket.o\
	test/Fl_Buffer.o
	$(CC) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x40033c
# %TargetType:	DLL
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	src
# %IncDir:	efltk
# %ObjsDir:	lib
lib/libefltk_net.so ::	lib/Fl_FTP_Socket.o
	rm -f $@
	$(LD) -shared -o $@ $^ $(LDOPTIONS)

# %UniqueId:	0x40033f
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test/net
# %IncDir:	test/net
# %ObjsDir:	test/net
test/net/ftp_socket ::	test/net/ftp_socket.o\
	test/net/Fl_FTP_Socket.o\
	test/net/Fl_Socket.o\
	test/net/Fl_Buffer.o\
	test/net/Fl_FTP_Connect.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400345
# %TargetType:	C_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test/db
# %IncDir:	test/db
# %ObjsDir:	test/db
test/db/db_odbc ::	test/db/db_odbc.o
	$(CC) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk -lefltk_odbc

# %UniqueId:	0x40034e
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/curve ::	test/curve.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400350
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/dialog ::	test/dialog.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400352
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/directory ::	test/directory.o
	$(CXX) -o $@ $^ $(LDOPTIONS) $(LOCAL_LIBRARIES) -lefltk

# %UniqueId:	0x400354
# %TargetType:	C++_EXE
# %IDEFlags:	0x8
# %ComplexTarget
# %SrcDir:	test
# %IncDir:	test
# %ObjsDir:	test
test/doublebuffer ::	test/doublebuffer.o
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
# %ParentTarget:	0x400284
# %SourceTarget:	0x400285
test/editor.o : test/editor.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400272
# %SourceTarget:	0x400287
test/cursor.o : test/cursor.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400288
lib/Fl.o : src/core/Fl.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400289
lib/Fl_Bitmap.o : src/core/Fl_Bitmap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40028a
lib/Fl_Bmp.o : src/core/Fl_Bmp.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40028b
lib/Fl_Boxtype.o : src/core/Fl_Boxtype.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400343
lib/Fl_Buffer.o : src/core/Fl_Buffer.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40028d
lib/Fl_Config.o : src/core/Fl_Config.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40028e
lib/Fl_Data_Fields.o : src/core/Fl_Data_Fields.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40028f
lib/Fl_Data_Source.o : src/core/Fl_Data_Source.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400290
lib/Fl_Date_Time.o : src/core/Fl_Date_Time.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400291
lib/Fl_Exception.o : src/core/Fl_Exception.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400292
lib/Fl_Gif.o : src/core/Fl_Gif.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400293
lib/Fl_Group.o : src/core/Fl_Group.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400294
lib/Fl_Hashs.o : src/core/Fl_Hashs.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400295
lib/Fl_Image.o : src/core/Fl_Image.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400296
lib/Fl_Image_Filter.o : src/core/Fl_Image_Filter.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400297
lib/Fl_Lists.o : src/core/Fl_Lists.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400298
lib/Fl_Maps.o : src/core/Fl_Maps.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400299
lib/Fl_Pixmap.o : src/core/Fl_Pixmap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40029a
lib/Fl_Renderer.o : src/core/Fl_Renderer.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40029b
lib/Fl_String.o : src/core/Fl_String.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40029c
lib/Fl_Style.o : src/core/Fl_Style.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40029d
lib/Fl_Style_Set.o : src/core/Fl_Style_Set.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40029e
lib/Fl_Thread.o : src/core/Fl_Thread.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40029f
lib/Fl_Translator.o : src/core/Fl_Translator.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a0
lib/Fl_Util.o : src/core/Fl_Util.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a1
lib/Fl_Variant.o : src/core/Fl_Variant.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a2
lib/Fl_WM.o : src/core/Fl_WM.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a3
lib/Fl_Widget.o : src/core/Fl_Widget.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a4
lib/Fl_Window.o : src/core/Fl_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a5
lib/Fl_Window_fullscreen.o : src/core/Fl_Window_fullscreen.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a6
lib/Fl_Window_hotspot.o : src/core/Fl_Window_hotspot.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a7
lib/Fl_Window_iconize.o : src/core/Fl_Window_iconize.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a8
lib/Fl_Xpm.o : src/core/Fl_Xpm.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002a9
lib/Fl_abort.o : src/core/Fl_abort.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002aa
lib/Fl_add_idle.o : src/core/Fl_add_idle.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ab
lib/Fl_arg.o : src/core/Fl_arg.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ac
lib/Fl_compose.o : src/core/Fl_compose.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ad
lib/Fl_display.o : src/core/Fl_display.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ae
lib/Fl_get_key.o : src/core/Fl_get_key.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002af
lib/Fl_init.o : src/core/Fl_init.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b0
lib/Fl_key_name.o : src/core/Fl_key_name.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b1
lib/Fl_lock.o : src/core/Fl_lock.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b2
lib/Fl_own_colormap.o : src/core/Fl_own_colormap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b3
lib/Fl_visual.o : src/core/Fl_visual.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b4
lib/KStoUCS.o : src/core/KStoUCS.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b5
lib/cmap.o : src/core/cmap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b6
lib/filename.o : src/core/filename.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b7
lib/filename_list.o : src/core/filename_list.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b8
lib/filename_match.o : src/core/filename_match.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002b9
lib/filename_setext.o : src/core/filename_setext.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ba
lib/fl_arc.o : src/core/fl_arc.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002bb
lib/fl_arci.o : src/core/fl_arci.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002bc
lib/fl_blit.o : src/core/fl_blit.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002bd
lib/fl_blit_1.o : src/core/fl_blit_1.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002be
lib/fl_blit_a.o : src/core/fl_blit_a.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002bf
lib/fl_blit_n.o : src/core/fl_blit_n.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c0
lib/fl_call_main.o : src/core/fl_call_main.c
	$(CC) -c -o $@ $< -Iefltk -Isrc $(CFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c1
lib/fl_clip.o : src/core/fl_clip.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c2
lib/fl_color.o : src/core/fl_color.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c3
lib/fl_converters.o : src/core/fl_converters.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c4
lib/fl_cursor.o : src/core/fl_cursor.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c5
lib/fl_curve.o : src/core/fl_curve.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c6
lib/fl_diamond_box.o : src/core/fl_diamond_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c7
lib/fl_dnd.o : src/core/fl_dnd.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c8
lib/fl_draw.o : src/core/fl_draw.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002c9
lib/fl_draw_image.o : src/core/fl_draw_image.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ca
lib/fl_draw_pixmap.o : src/core/fl_draw_pixmap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002cb
lib/fl_font.o : src/core/fl_font.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002cc
lib/fl_glyph.o : src/core/fl_glyph.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002cd
lib/fl_iconv_converters.o : src/core/fl_iconv_converters.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ce
lib/fl_labeltype.o : src/core/fl_labeltype.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002cf
lib/fl_list_fonts.o : src/core/fl_list_fonts.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d0
lib/fl_load_plugin.o : src/core/fl_load_plugin.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d1
lib/fl_locale.o : src/core/fl_locale.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d2
lib/fl_map.o : src/core/fl_map.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d3
lib/fl_oval_box.o : src/core/fl_oval_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d4
lib/fl_overlay.o : src/core/fl_overlay.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d5
lib/fl_overlay_visual.o : src/core/fl_overlay_visual.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d6
lib/fl_plastic_box.o : src/core/fl_plastic_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d7
lib/fl_rect.o : src/core/fl_rect.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d8
lib/fl_rgb.o : src/core/fl_rgb.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002d9
lib/fl_round_box.o : src/core/fl_round_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002da
lib/fl_rounded_box.o : src/core/fl_rounded_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002db
lib/fl_scroll_area.o : src/core/fl_scroll_area.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002dc
lib/fl_shadow_box.o : src/core/fl_shadow_box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002dd
lib/fl_stretch.o : src/core/fl_stretch.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002de
lib/fl_theme.o : src/core/fl_theme.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002df
lib/fl_utf8.o : src/core/fl_utf8.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002e0
lib/fl_vertex.o : src/core/fl_vertex.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002e1
lib/scandir.o : src/core/scandir.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002e2
lib/vsnprintf.o : src/core/vsnprintf.c
	$(CC) -c -o $@ $< -Iefltk -Isrc $(CFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x4002e3
lib/Fl_Gl_Choice.o : src/opengl/Fl_Gl_Choice.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x4002e4
lib/Fl_Gl_Overlay.o : src/opengl/Fl_Gl_Overlay.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x4002e5
lib/Fl_Gl_Window.o : src/opengl/Fl_Gl_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x4002e6
lib/gl_draw.o : src/opengl/gl_draw.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40026b
# %SourceTarget:	0x4002e7
lib/gl_start.o : src/opengl/gl_start.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002e8
lib/Fl_Adjuster.o : src/widgets/Fl_Adjuster.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002e9
lib/Fl_Align_Group.o : src/widgets/Fl_Align_Group.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ea
lib/Fl_Bar.o : src/widgets/Fl_Bar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002eb
lib/Fl_Box.o : src/widgets/Fl_Box.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ec
lib/Fl_Browser.o : src/widgets/Fl_Browser.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ed
lib/Fl_Button.o : src/widgets/Fl_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ee
lib/Fl_Calendar.o : src/widgets/Fl_Calendar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ef
lib/Fl_Check_Button.o : src/widgets/Fl_Check_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f0
lib/Fl_Choice.o : src/widgets/Fl_Choice.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f1
lib/Fl_Clock.o : src/widgets/Fl_Clock.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f2
lib/Fl_Color_Chooser.o : src/widgets/Fl_Color_Chooser.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f3
lib/Fl_Date_Time_Input.o : src/widgets/Fl_Date_Time_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f4
lib/Fl_Dial.o : src/widgets/Fl_Dial.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f5
lib/Fl_Dialog.o : src/widgets/Fl_Dialog.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f6
lib/Fl_Directory_DS.o : src/widgets/Fl_Directory_DS.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f7
lib/Fl_Double_Window.o : src/widgets/Fl_Double_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f8
lib/Fl_FileBrowser.o : src/widgets/Fl_FileBrowser.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002f9
lib/Fl_FileInput.o : src/widgets/Fl_FileInput.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002fa
lib/Fl_File_Dialog.o : src/widgets/Fl_File_Dialog.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002fb
lib/Fl_Float_Input.o : src/widgets/Fl_Float_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002fc
lib/Fl_Help_Dialog.o : src/widgets/Fl_Help_Dialog.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002fd
lib/Fl_Highlight_Button.o : src/widgets/Fl_Highlight_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002fe
lib/Fl_Input.o : src/widgets/Fl_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x4002ff
lib/Fl_Input_Browser.o : src/widgets/Fl_Input_Browser.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400300
lib/Fl_Item.o : src/widgets/Fl_Item.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400301
lib/Fl_Light_Button.o : src/widgets/Fl_Light_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400302
lib/Fl_ListView.o : src/widgets/Fl_ListView.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400303
lib/Fl_ListView_Header.o : src/widgets/Fl_ListView_Header.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400304
lib/Fl_ListView_Item.o : src/widgets/Fl_ListView_Item.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400305
lib/Fl_MDI_Bar.o : src/widgets/Fl_MDI_Bar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400306
lib/Fl_MDI_Window.o : src/widgets/Fl_MDI_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400307
lib/Fl_Main_Window.o : src/widgets/Fl_Main_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400308
lib/Fl_Masked_Input.o : src/widgets/Fl_Masked_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400309
lib/Fl_Menu.o : src/widgets/Fl_Menu.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40030a
lib/Fl_Menu_.o : src/widgets/Fl_Menu_.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40030b
lib/Fl_Menu_Bar.o : src/widgets/Fl_Menu_Bar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40030c
lib/Fl_Menu_Button.o : src/widgets/Fl_Menu_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40030d
lib/Fl_Menu_Item.o : src/widgets/Fl_Menu_Item.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40030e
lib/Fl_Menu_Window.o : src/widgets/Fl_Menu_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40030f
lib/Fl_Menu_add.o : src/widgets/Fl_Menu_add.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400310
lib/Fl_Menu_global.o : src/widgets/Fl_Menu_global.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400311
lib/Fl_Multi_Image.o : src/widgets/Fl_Multi_Image.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400312
lib/Fl_Multi_Tabs.o : src/widgets/Fl_Multi_Tabs.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400313
lib/Fl_Numeric_Input.o : src/widgets/Fl_Numeric_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400314
lib/Fl_Output.o : src/widgets/Fl_Output.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400315
lib/Fl_Overlay_Window.o : src/widgets/Fl_Overlay_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400316
lib/Fl_Pack.o : src/widgets/Fl_Pack.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400317
lib/Fl_Popup_Window.o : src/widgets/Fl_Popup_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400318
lib/Fl_ProgressBar.o : src/widgets/Fl_ProgressBar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400319
lib/Fl_Radio_Button.o : src/widgets/Fl_Radio_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40031a
lib/Fl_Repeat_Button.o : src/widgets/Fl_Repeat_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40031b
lib/Fl_Return_Button.o : src/widgets/Fl_Return_Button.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40031c
lib/Fl_Roller.o : src/widgets/Fl_Roller.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40031d
lib/Fl_Scroll.o : src/widgets/Fl_Scroll.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40031e
lib/Fl_Scrollbar.o : src/widgets/Fl_Scrollbar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40031f
lib/Fl_Shaped_Window.o : src/widgets/Fl_Shaped_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400320
lib/Fl_Simple_Html.o : src/widgets/Fl_Simple_Html.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400321
lib/Fl_Single_Window.o : src/widgets/Fl_Single_Window.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400322
lib/Fl_Slider.o : src/widgets/Fl_Slider.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400323
lib/Fl_Tabs.o : src/widgets/Fl_Tabs.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400324
lib/Fl_Text_Buffer.o : src/widgets/Fl_Text_Buffer.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400325
lib/Fl_Text_Display.o : src/widgets/Fl_Text_Display.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400326
lib/Fl_Text_Editor.o : src/widgets/Fl_Text_Editor.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400327
lib/Fl_Tile.o : src/widgets/Fl_Tile.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400328
lib/Fl_Tool_Bar.o : src/widgets/Fl_Tool_Bar.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400329
lib/Fl_Tooltip.o : src/widgets/Fl_Tooltip.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40032a
lib/Fl_Valuator.o : src/widgets/Fl_Valuator.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40032b
lib/Fl_Value_Input.o : src/widgets/Fl_Value_Input.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40032c
lib/Fl_Value_Slider.o : src/widgets/Fl_Value_Slider.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40032d
lib/Fl_Workspace.o : src/widgets/Fl_Workspace.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40032e
lib/fl_ask.o : src/widgets/fl_ask.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40032f
lib/fl_engraved_label.o : src/widgets/fl_engraved_label.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400330
lib/fl_show_colormap.o : src/widgets/fl_show_colormap.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400331
lib/fl_symbols.o : src/widgets/fl_symbols.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400332
lib/Fl_Database.o : src/db/Fl_Database.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400333
lib/Fl_Params.o : src/db/Fl_Params.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400334
lib/Fl_Query.o : src/db/Fl_Query.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400342
lib/Fl_Socket.o : src/core/Fl_Socket.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40033a
# %SourceTarget:	0x40033b
test/socket.o : test/socket.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40033a
# %SourceTarget:	0x400342
test/Fl_Socket.o : src/core/Fl_Socket.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40033c
# %SourceTarget:	0x400341
lib/Fl_FTP_Socket.o : src/net/Fl_FTP_Socket.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40033f
# %SourceTarget:	0x400340
test/net/ftp_socket.o : test/net/ftp_socket.cpp
	$(CXX) -c -o $@ $< -Itest/net -Itest/net $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40033f
# %SourceTarget:	0x400341
test/net/Fl_FTP_Socket.o : src/net/Fl_FTP_Socket.cpp
	$(CXX) -c -o $@ $< -Itest/net -Itest/net $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40033f
# %SourceTarget:	0x400342
test/net/Fl_Socket.o : src/core/Fl_Socket.cpp
	$(CXX) -c -o $@ $< -Itest/net -Itest/net $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40033a
# %SourceTarget:	0x400343
test/Fl_Buffer.o : src/core/Fl_Buffer.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400345
# %SourceTarget:	0x400346
test/db/db_odbc.o : test/db/db_odbc.cpp
	$(CXX) -c -o $@ $< -Itest/db -Itest/db $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40033f
# %SourceTarget:	0x400343
test/net/Fl_Buffer.o : src/core/Fl_Buffer.cpp
	$(CXX) -c -o $@ $< -Itest/net -Itest/net $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x400347
lib/Fl_Gdi.o : src/core/Fl_Gdi.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40034b
lib/Fl_PostScript.o : src/core/Fl_PostScript.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400002
# %SourceTarget:	0x40034d
lib/Fl_Printer.o : src/core/Fl_Printer.cpp
	$(CXX) -c -o $@ $< -Iefltk -Isrc $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40034e
# %SourceTarget:	0x40034f
test/curve.o : test/curve.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400350
# %SourceTarget:	0x400351
test/dialog.o : test/dialog.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400352
# %SourceTarget:	0x400353
test/directory.o : test/directory.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x400354
# %SourceTarget:	0x400355
test/doublebuffer.o : test/doublebuffer.cpp
	$(CXX) -c -o $@ $< -Itest -Itest $(CXXFLAGS)


# %TargetType:	C++_OBJ
# %ParentTarget:	0x40033f
# %SourceTarget:	0x400356
test/net/Fl_FTP_Connect.o : src/net/Fl_FTP_Connect.cpp
	$(CXX) -c -o $@ $< -Itest/net -Itest/net $(CXXFLAGS)


# DO NOT DELETE

lib/Fl_ODBC_Database.o :	src/db/odbc/fl_odbc.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/db/Fl_Query.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/db/Fl_Params.h\
	efltk/db/Fl_ODBC_Database.h\
	efltk/db/Fl_Database.h\
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
test/editor.o :	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Text_Editor.h\
	efltk/Fl_Text_Display.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Text_Buffer.h\
	efltk/Fl_Ptr_Stack.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/fl_draw.h\
	efltk/Fl_Return_Button.h\
	efltk/Fl_Button.h\
	efltk/Fl_Input.h\
	efltk/Fl_Menu_Bar.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Menu_.h\
	efltk/Fl_Menu_Item.h\
	efltk/Fl_File_Dialog.h\
	efltk/Fl_FileBrowser.h\
	efltk/Fl_Directory_DS.h\
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
	efltk/Fl_ListView.h\
	efltk/Fl_ListView_Header.h\
	efltk/Fl_Highlight_Button.h\
	efltk/Fl_Check_Button.h\
	efltk/Fl_Box.h\
	efltk/Fl_Item.h\
	efltk/Fl_Input_Browser.h\
	efltk/Fl_Image_Cache.h\
	efltk/fl_ask.h\
	efltk/Fl_Double_Window.h\
	efltk/Fl_Pack.h\
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
lib/Fl_Database.o :	efltk/db/Fl_Query.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/db/Fl_Params.h\
	efltk/db/Fl_Database.h\
	efltk/Fl_Thread.h\
	efltk/Fl_Thread_Linux.h\
	efltk/Fl_Thread_w32.h\
	efltk/Fl_Exception.h
lib/Fl_Params.o :	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/db/Fl_Params.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h
lib/Fl_Query.o :	efltk/db/Fl_Query.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/db/Fl_Params.h\
	efltk/db/Fl_Database.h\
	efltk/Fl_Thread.h\
	efltk/Fl_Thread_Linux.h\
	efltk/Fl_Thread_w32.h\
	efltk/Fl_Exception.h
lib/Fl_Socket.o :	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Socket.h\
	efltk/Fl_Buffer.h
test/socket.o :	efltk/fl_ask.h\
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
	efltk/Fl_Simple_Html.h\
	efltk/Fl_Image_Cache.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/fl_draw.h\
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
	efltk/Fl.h\
	efltk/Fl_Text_Editor.h\
	efltk/Fl_Text_Display.h\
	efltk/Fl_Text_Buffer.h\
	efltk/Fl_Buffer.h\
	efltk/Fl_Ptr_Stack.h\
	efltk/Fl_Button.h\
	efltk/Fl_Input.h\
	efltk/Fl_Box.h\
	efltk/Fl_Window.h\
	efltk/Fl_Socket.h
test/Fl_Socket.o :	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Socket.h\
	efltk/Fl_Buffer.h
lib/Fl_FTP_Socket.o :	efltk/net/Fl_FTP_Socket.h\
	efltk/Fl_Socket.h\
	efltk/Fl_Buffer.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Exception.h
test/net/ftp_socket.o :	efltk/net/Fl_FTP_Connect.h\
	efltk/net/Fl_FTP_Socket.h\
	efltk/Fl_Socket.h\
	efltk/Fl_Buffer.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h
test/net/Fl_FTP_Socket.o :	efltk/net/Fl_FTP_Socket.h\
	efltk/Fl_Socket.h\
	efltk/Fl_Buffer.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Exception.h
test/net/Fl_Socket.o :	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Socket.h\
	efltk/Fl_Buffer.h
test/Fl_Buffer.o :	efltk/Fl_Exception.h\
	efltk/Fl_Export.h\
	efltk/Fl_String.h\
	efltk/Enumerations.h\
	efltk/Fl_Buffer.h
test/db/db_odbc.o :	efltk/db/Fl_ODBC_Database.h\
	efltk/db/Fl_Database.h\
	efltk/db/Fl_Query.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/db/Fl_Params.h\
	efltk/Fl_Thread.h\
	efltk/Fl_Thread_Linux.h\
	efltk/Fl_Thread_w32.h\
	efltk/Fl_Exception.h\
	efltk/fl_ask.h\
	efltk/Fl_Style.h\
	efltk/Fl_Font.h\
	efltk/Fl_Int_List.h\
	efltk/Fl_String_List.h\
	efltk/Fl_Labeltype.h\
	efltk/Fl_Color.h\
	efltk/Fl_Boxtype.h\
	efltk/Fl.h
lib/Fl_Gdi.o :	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Color.h\
	efltk/Fl_Flags.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Printer.h\
	efltk/Fl_Gdi.h\
	efltk/fl_draw.h\
	efltk/Fl_Device.h\
	efltk/Fl_Bitmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Ptr_List.h\
	efltk/Fl_Renderer.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_String.h\
	efltk/Fl_Pixmap.h\
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
	efltk/Fl.h\
	config.h
lib/Fl_PostScript.o :	efltk/Fl.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_PostScript.h\
	efltk/Fl_Printer.h\
	efltk/Fl_Gdi.h\
	efltk/fl_draw.h\
	efltk/Fl_Device.h\
	efltk/Fl_Bitmap.h\
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
	efltk/Fl_String.h\
	efltk/Fl_Pixmap.h\
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
	efltk/Fl_Boxtype.h
lib/Fl_Printer.o :	efltk/Fl_Printer.h\
	efltk/Fl_Gdi.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/fl_draw.h\
	efltk/Fl_Device.h\
	efltk/Fl_Bitmap.h\
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
	efltk/Fl_String.h\
	efltk/Fl_Pixmap.h\
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
	efltk/Fl_Boxtype.h
test/curve.o :	efltk/Fl_Toggle_Button.h\
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
	efltk/fl_draw.h\
	efltk/Fl_Device.h\
	efltk/Fl_Bitmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Pixmap.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Hor_Value_Slider.h\
	efltk/Fl_Value_Slider.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Double_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl.h
test/dialog.o :	efltk/fl_ask.h\
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
	efltk/Fl_Input.h\
	efltk/Fl_Widget.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_Exception.h\
	efltk/Fl_Dialog.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Scroll.h\
	efltk/Fl_Scrollbar.h\
	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
	efltk/Fl_Group.h\
	efltk/Fl_Window.h\
	efltk/Fl_Button.h\
	efltk/Fl_Calendar.h\
	efltk/Fl_Box.h\
	efltk/Fl_Popup_Window.h\
	efltk/Fl_Menu_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl.h
test/directory.o :	efltk/Fl_Directory_DS.h\
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
	config.h
test/doublebuffer.o :	efltk/Fl_Slider.h\
	efltk/Fl_Valuator.h\
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
	efltk/Fl_Device.h\
	efltk/Fl_Bitmap.h\
	efltk/Fl_Image.h\
	efltk/Fl_PtrList.h\
	efltk/Fl_Renderer.h\
	efltk/x.h\
	efltk/win32.h\
	efltk/Fl_Util.h\
	efltk/filename.h\
	efltk/Fl_Pixmap.h\
	efltk/Fl_Group.h\
	efltk/Fl_Widget_List.h\
	efltk/Fl_Box.h\
	efltk/Fl_Double_Window.h\
	efltk/Fl_Window.h\
	efltk/Fl_Single_Window.h\
	efltk/Fl.h\
	config.h\
	efltk/fl_math.h
test/net/Fl_FTP_Connect.o :	efltk/net/Fl_FTP_Connect.h\
	efltk/Fl_Data_Source.h\
	efltk/Fl_Data_Fields.h\
	efltk/Fl_Flags.h\
	efltk/Fl_Ptr_List.h\
	efltk/Enumerations.h\
	efltk/Fl_Export.h\
	efltk/Fl_Variant.h\
	efltk/Fl_Date_Time.h\
	efltk/Fl_String.h\
	efltk/Fl_Buffer.h


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
# %TargetInfo test/calendar.cpp	SourceOrHeader,	UniqueId=0x40024a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/checkers.cpp	SourceOrHeader,	UniqueId=0x40024c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/clock.cpp	SourceOrHeader,	UniqueId=0x40025f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/color_chooser.cpp	SourceOrHeader,	UniqueId=0x400263,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/cube.cpp	SourceOrHeader,	UniqueId=0x400267,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/editor.cpp	SourceOrHeader,	UniqueId=0x400285,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/cursor.cpp	SourceOrHeader,	UniqueId=0x400287,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl.cpp	SourceOrHeader,	UniqueId=0x400288,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Bitmap.cpp	SourceOrHeader,	UniqueId=0x400289,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Bmp.cpp	SourceOrHeader,	UniqueId=0x40028a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Boxtype.cpp	SourceOrHeader,	UniqueId=0x40028b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Buffer.cpp	SourceOrHeader,	UniqueId=0x400343,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Config.cpp	SourceOrHeader,	UniqueId=0x40028d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Data_Fields.cpp	SourceOrHeader,	UniqueId=0x40028e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Data_Source.cpp	SourceOrHeader,	UniqueId=0x40028f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Date_Time.cpp	SourceOrHeader,	UniqueId=0x400290,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Exception.cpp	SourceOrHeader,	UniqueId=0x400291,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Gif.cpp	SourceOrHeader,	UniqueId=0x400292,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Group.cpp	SourceOrHeader,	UniqueId=0x400293,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Hashs.cpp	SourceOrHeader,	UniqueId=0x400294,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Image.cpp	SourceOrHeader,	UniqueId=0x400295,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Image_Filter.cpp	SourceOrHeader,	UniqueId=0x400296,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Lists.cpp	SourceOrHeader,	UniqueId=0x400297,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Maps.cpp	SourceOrHeader,	UniqueId=0x400298,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Pixmap.cpp	SourceOrHeader,	UniqueId=0x400299,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Renderer.cpp	SourceOrHeader,	UniqueId=0x40029a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_String.cpp	SourceOrHeader,	UniqueId=0x40029b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Style.cpp	SourceOrHeader,	UniqueId=0x40029c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Style_Set.cpp	SourceOrHeader,	UniqueId=0x40029d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Thread.cpp	SourceOrHeader,	UniqueId=0x40029e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Translator.cpp	SourceOrHeader,	UniqueId=0x40029f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Util.cpp	SourceOrHeader,	UniqueId=0x4002a0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Variant.cpp	SourceOrHeader,	UniqueId=0x4002a1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_WM.cpp	SourceOrHeader,	UniqueId=0x4002a2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Widget.cpp	SourceOrHeader,	UniqueId=0x4002a3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Window.cpp	SourceOrHeader,	UniqueId=0x4002a4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Window_fullscreen.cpp	SourceOrHeader,	UniqueId=0x4002a5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Window_hotspot.cpp	SourceOrHeader,	UniqueId=0x4002a6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Window_iconize.cpp	SourceOrHeader,	UniqueId=0x4002a7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Xpm.cpp	SourceOrHeader,	UniqueId=0x4002a8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_abort.cpp	SourceOrHeader,	UniqueId=0x4002a9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_add_idle.cpp	SourceOrHeader,	UniqueId=0x4002aa,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_arg.cpp	SourceOrHeader,	UniqueId=0x4002ab,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_compose.cpp	SourceOrHeader,	UniqueId=0x4002ac,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_display.cpp	SourceOrHeader,	UniqueId=0x4002ad,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_get_key.cpp	SourceOrHeader,	UniqueId=0x4002ae,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_init.cpp	SourceOrHeader,	UniqueId=0x4002af,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_key_name.cpp	SourceOrHeader,	UniqueId=0x4002b0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_lock.cpp	SourceOrHeader,	UniqueId=0x4002b1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_own_colormap.cpp	SourceOrHeader,	UniqueId=0x4002b2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_visual.cpp	SourceOrHeader,	UniqueId=0x4002b3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/KStoUCS.cpp	SourceOrHeader,	UniqueId=0x4002b4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/cmap.cpp	SourceOrHeader,	UniqueId=0x4002b5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/filename.cpp	SourceOrHeader,	UniqueId=0x4002b6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/filename_list.cpp	SourceOrHeader,	UniqueId=0x4002b7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/filename_match.cpp	SourceOrHeader,	UniqueId=0x4002b8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/filename_setext.cpp	SourceOrHeader,	UniqueId=0x4002b9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_arc.cpp	SourceOrHeader,	UniqueId=0x4002ba,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_arci.cpp	SourceOrHeader,	UniqueId=0x4002bb,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_blit.cpp	SourceOrHeader,	UniqueId=0x4002bc,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_blit_1.cpp	SourceOrHeader,	UniqueId=0x4002bd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_blit_a.cpp	SourceOrHeader,	UniqueId=0x4002be,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_blit_n.cpp	SourceOrHeader,	UniqueId=0x4002bf,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_call_main.c	SourceOrHeader,	UniqueId=0x4002c0,	TargetType=C,	IDEFlags=0x4
# %TargetInfo src/core/fl_clip.cpp	SourceOrHeader,	UniqueId=0x4002c1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_color.cpp	SourceOrHeader,	UniqueId=0x4002c2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_converters.cpp	SourceOrHeader,	UniqueId=0x4002c3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_cursor.cpp	SourceOrHeader,	UniqueId=0x4002c4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_curve.cpp	SourceOrHeader,	UniqueId=0x4002c5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_diamond_box.cpp	SourceOrHeader,	UniqueId=0x4002c6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_dnd.cpp	SourceOrHeader,	UniqueId=0x4002c7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw.cpp	SourceOrHeader,	UniqueId=0x4002c8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw_image.cpp	SourceOrHeader,	UniqueId=0x4002c9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_draw_pixmap.cpp	SourceOrHeader,	UniqueId=0x4002ca,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_font.cpp	SourceOrHeader,	UniqueId=0x4002cb,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_glyph.cpp	SourceOrHeader,	UniqueId=0x4002cc,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_iconv_converters.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x4002cd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_labeltype.cpp	SourceOrHeader,	UniqueId=0x4002ce,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_list_fonts.cpp	SourceOrHeader,	UniqueId=0x4002cf,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_load_plugin.cpp	SourceOrHeader,	UniqueId=0x4002d0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_locale.cpp	SourceOrHeader,	UniqueId=0x4002d1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_map.cpp	SourceOrHeader,	UniqueId=0x4002d2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_oval_box.cpp	SourceOrHeader,	UniqueId=0x4002d3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_overlay.cpp	SourceOrHeader,	UniqueId=0x4002d4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_overlay_visual.cpp	SourceOrHeader,	UniqueId=0x4002d5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_plastic_box.cpp	SourceOrHeader,	UniqueId=0x4002d6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_rect.cpp	SourceOrHeader,	UniqueId=0x4002d7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_rgb.cpp	SourceOrHeader,	UniqueId=0x4002d8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_round_box.cpp	SourceOrHeader,	UniqueId=0x4002d9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_rounded_box.cpp	SourceOrHeader,	UniqueId=0x4002da,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_scroll_area.cpp	SourceOrHeader,	UniqueId=0x4002db,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_shadow_box.cpp	SourceOrHeader,	UniqueId=0x4002dc,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_stretch.cpp	SourceOrHeader,	UniqueId=0x4002dd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_theme.cpp	SourceOrHeader,	UniqueId=0x4002de,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_utf8.cpp	SourceOrHeader,	UniqueId=0x4002df,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/fl_vertex.cpp	SourceOrHeader,	UniqueId=0x4002e0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/scandir.cpp	SourceOrHeader,	UniqueId=0x4002e1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/vsnprintf.c	SourceOrHeader,	UniqueId=0x4002e2,	TargetType=C,	IDEFlags=0x4
# %TargetInfo src/opengl/Fl_Gl_Choice.cpp	SourceOrHeader,	UniqueId=0x4002e3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/opengl/Fl_Gl_Overlay.cpp	SourceOrHeader,	UniqueId=0x4002e4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/opengl/Fl_Gl_Window.cpp	SourceOrHeader,	UniqueId=0x4002e5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/opengl/gl_draw.cpp	SourceOrHeader,	UniqueId=0x4002e6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/opengl/gl_start.cpp	SourceOrHeader,	UniqueId=0x4002e7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Adjuster.cpp	SourceOrHeader,	UniqueId=0x4002e8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Align_Group.cpp	SourceOrHeader,	UniqueId=0x4002e9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Bar.cpp	SourceOrHeader,	UniqueId=0x4002ea,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Box.cpp	SourceOrHeader,	UniqueId=0x4002eb,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Browser.cpp	SourceOrHeader,	UniqueId=0x4002ec,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Button.cpp	SourceOrHeader,	UniqueId=0x4002ed,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Calendar.cpp	SourceOrHeader,	UniqueId=0x4002ee,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Check_Button.cpp	SourceOrHeader,	UniqueId=0x4002ef,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Choice.cpp	SourceOrHeader,	UniqueId=0x4002f0,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Clock.cpp	SourceOrHeader,	UniqueId=0x4002f1,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Color_Chooser.cpp	SourceOrHeader,	UniqueId=0x4002f2,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Date_Time_Input.cpp	SourceOrHeader,	UniqueId=0x4002f3,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Dial.cpp	SourceOrHeader,	UniqueId=0x4002f4,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Dialog.cpp	SourceOrHeader,	UniqueId=0x4002f5,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Directory_DS.cpp	SourceOrHeader,	UniqueId=0x4002f6,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Double_Window.cpp	SourceOrHeader,	UniqueId=0x4002f7,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_FileBrowser.cpp	SourceOrHeader,	UniqueId=0x4002f8,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_FileInput.cpp	SourceOrHeader,	UniqueId=0x4002f9,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_File_Dialog.cpp	SourceOrHeader,	UniqueId=0x4002fa,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Float_Input.cpp	SourceOrHeader,	UniqueId=0x4002fb,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Help_Dialog.cpp	SourceOrHeader,	UniqueId=0x4002fc,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Highlight_Button.cpp	SourceOrHeader,	UniqueId=0x4002fd,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Input.cpp	SourceOrHeader,	UniqueId=0x4002fe,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Input_Browser.cpp	SourceOrHeader,	UniqueId=0x4002ff,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Item.cpp	SourceOrHeader,	UniqueId=0x400300,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Light_Button.cpp	SourceOrHeader,	UniqueId=0x400301,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_ListView.cpp	SourceOrHeader,	UniqueId=0x400302,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_ListView_Header.cpp	SourceOrHeader,	UniqueId=0x400303,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_ListView_Item.cpp	SourceOrHeader,	UniqueId=0x400304,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_MDI_Bar.cpp	SourceOrHeader,	UniqueId=0x400305,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_MDI_Window.cpp	SourceOrHeader,	UniqueId=0x400306,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Main_Window.cpp	SourceOrHeader,	UniqueId=0x400307,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Masked_Input.cpp	SourceOrHeader,	UniqueId=0x400308,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu.cpp	SourceOrHeader,	UniqueId=0x400309,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_.cpp	SourceOrHeader,	UniqueId=0x40030a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_Bar.cpp	SourceOrHeader,	UniqueId=0x40030b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_Button.cpp	SourceOrHeader,	UniqueId=0x40030c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_Item.cpp	SourceOrHeader,	UniqueId=0x40030d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_Window.cpp	SourceOrHeader,	UniqueId=0x40030e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_add.cpp	SourceOrHeader,	UniqueId=0x40030f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Menu_global.cpp	SourceOrHeader,	UniqueId=0x400310,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Multi_Image.cpp	SourceOrHeader,	UniqueId=0x400311,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Multi_Tabs.cpp	SourceOrHeader,	UniqueId=0x400312,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Numeric_Input.cpp	SourceOrHeader,	UniqueId=0x400313,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Output.cpp	SourceOrHeader,	UniqueId=0x400314,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Overlay_Window.cpp	SourceOrHeader,	UniqueId=0x400315,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Pack.cpp	SourceOrHeader,	UniqueId=0x400316,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Popup_Window.cpp	SourceOrHeader,	UniqueId=0x400317,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_ProgressBar.cpp	SourceOrHeader,	UniqueId=0x400318,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Radio_Button.cpp	SourceOrHeader,	UniqueId=0x400319,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Repeat_Button.cpp	SourceOrHeader,	UniqueId=0x40031a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Return_Button.cpp	SourceOrHeader,	UniqueId=0x40031b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Roller.cpp	SourceOrHeader,	UniqueId=0x40031c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Scroll.cpp	SourceOrHeader,	UniqueId=0x40031d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Scrollbar.cpp	SourceOrHeader,	UniqueId=0x40031e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Shaped_Window.cpp	SourceOrHeader,	UniqueId=0x40031f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Simple_Html.cpp	SourceOrHeader,	UniqueId=0x400320,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Single_Window.cpp	SourceOrHeader,	UniqueId=0x400321,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Slider.cpp	SourceOrHeader,	UniqueId=0x400322,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Tabs.cpp	SourceOrHeader,	UniqueId=0x400323,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Text_Buffer.cpp	SourceOrHeader,	UniqueId=0x400324,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Text_Display.cpp	SourceOrHeader,	UniqueId=0x400325,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Text_Editor.cpp	SourceOrHeader,	UniqueId=0x400326,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Tile.cpp	SourceOrHeader,	UniqueId=0x400327,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Tool_Bar.cpp	SourceOrHeader,	UniqueId=0x400328,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Tooltip.cpp	SourceOrHeader,	UniqueId=0x400329,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Valuator.cpp	SourceOrHeader,	UniqueId=0x40032a,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Value_Input.cpp	SourceOrHeader,	UniqueId=0x40032b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Value_Slider.cpp	SourceOrHeader,	UniqueId=0x40032c,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/Fl_Workspace.cpp	SourceOrHeader,	UniqueId=0x40032d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/fl_ask.cpp	SourceOrHeader,	UniqueId=0x40032e,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/fl_engraved_label.cpp	SourceOrHeader,	UniqueId=0x40032f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/fl_show_colormap.cpp	SourceOrHeader,	UniqueId=0x400330,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/widgets/fl_symbols.cpp	SourceOrHeader,	UniqueId=0x400331,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/db/Fl_Database.cpp	SourceOrHeader,	UniqueId=0x400332,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/db/Fl_Params.cpp	SourceOrHeader,	UniqueId=0x400333,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/db/Fl_Query.cpp	SourceOrHeader,	UniqueId=0x400334,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Socket.cpp	SourceOrHeader,	UseWorkingFile,	UniqueId=0x400342,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/socket.cpp	SourceOrHeader,	UniqueId=0x40033b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/net/Fl_FTP_Socket.cpp	SourceOrHeader,	UseWorkingFile,	UniqueId=0x400341,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/net/ftp_socket.cpp	SourceOrHeader,	UseWorkingFile,	UniqueId=0x400340,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/db/db_odbc.cpp	SourceOrHeader,	UniqueId=0x400346,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Gdi.cpp	SourceOrHeader,	UniqueId=0x400347,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_PostScript.cpp	SourceOrHeader,	UniqueId=0x40034b,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/core/Fl_Printer.cpp	SourceOrHeader,	UniqueId=0x40034d,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/curve.cpp	SourceOrHeader,	UniqueId=0x40034f,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/dialog.cpp	SourceOrHeader,	UniqueId=0x400351,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/directory.cpp	SourceOrHeader,	UniqueId=0x400353,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo test/doublebuffer.cpp	SourceOrHeader,	UniqueId=0x400355,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo src/fl_iconv_converters.cpp	SourceOrHeader,	IncludeFile,	UniqueId=0x4001e5,	TargetType=C++,	IDEFlags=0x4
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
# %TargetInfo efltk/Fl_Hor_Value_Slider.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400274,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/db/Fl_Query.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400335,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/db/Fl_Params.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400336,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/db/Fl_Database.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400337,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Socket.h	SourceOrHeader,	IncludeFile,	UseWorkingFile,	UniqueId=0x400339,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/net/Fl_FTP_Socket.h	SourceOrHeader,	IncludeFile,	UseWorkingFile,	UniqueId=0x40033e,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/db/Fl_ODBC_Database.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400344,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Printer.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400348,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Gdi.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400349,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_Device.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40034a,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo efltk/Fl_PostScript.h	SourceOrHeader,	IncludeFile,	UniqueId=0x40034c,	TargetType=INC,	IDEFlags=0xe
# %TargetInfo src/net/Fl_FTP_Connect.cpp	SourceOrHeader,	UniqueId=0x400356,	TargetType=C++,	IDEFlags=0x4
# %TargetInfo efltk/net/Fl_FTP_Connect.h	SourceOrHeader,	IncludeFile,	UniqueId=0x400357,	TargetType=INC,	IDEFlags=0xe


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
#	0x40033c
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
#	0x40034e
#	0x400350
#	0x400284
#	0x40033a
#	0x400354
#	0x400352
#	0x40033f
#	0x400345
#
