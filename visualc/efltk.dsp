# Microsoft Developer Studio Project File - Name="efltk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=efltk - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "efltk.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "efltk.mak" CFG="efltk - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "efltk - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "efltk - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "efltk - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "efltk - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W1 /Gm /GX /ZI /Od /I "../visualc" /I "../.." /I "../" /I "." /D "_DEBUG" /D "_MSC_DLL" /D "WIN32" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\efltkd.lib"

!ENDIF 

# Begin Target

# Name "efltk - Win32 Release"
# Name "efltk - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\core\cmap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\filename_absolute.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\filename_expand.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\filename_ext.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\filename_isdir.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\filename_list.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\filename_match.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\filename_setext.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_abort.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_add_idle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Adjuster.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Align_Group.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_arc.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_arci.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_arg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\fl_ask.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Bar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Bitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_blit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_blit_1.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_blit_a.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_blit_n.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Bmp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Box.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Boxtype.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Browser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Button.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_call_main.c
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Check_Button.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Choice.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_clip.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Clock.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_color.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Color_Chooser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_compose.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Config.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_cursor.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_curve.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Dial.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_diamond_box.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_display.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_dnd.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Double_Window.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_draw.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_draw_image.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_draw_pixmap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\fl_engraved_label.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_File_Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_FileBrowser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_FileInput.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Float_Input.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_font.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_get_key.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Gif.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_glyph.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Group.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Help_Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Highlight_Button.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Image.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Image_Filter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_init.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Input.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Input_Browser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Item.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_key_name.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_labeltype.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Light_Button.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_list_fonts.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_ListView.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_ListView_Item.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_load_plugin.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_locale.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_lock.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Main_Window.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_map.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_MDI_Window.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Menu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Menu_.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Menu_add.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Menu_Bar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Menu_Button.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Menu_global.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Menu_Item.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Menu_Window.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Multi_Image.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Numeric_Input.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Output.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_oval_box.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_overlay.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_overlay_visual.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Overlay_Window.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_own_colormap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Pack.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Pixmap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_plastic_box.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_ProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Radio_Button.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_rect.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Renderer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Repeat_Button.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Return_Button.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_rgb.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Roller.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_round_box.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_rounded_box.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Scroll.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_scroll_area.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Scrollbar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_shadow_box.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Shaped_Window.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\fl_show_colormap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Simple_Html.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Single_Window.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Slider.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_stretch.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_String.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Style.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Style_Set.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\fl_symbols.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Tabs.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Text_Buffer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Text_Display.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Text_Editor.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_theme.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Thread.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Tile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Tool_Bar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Tooltip.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Util.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Valuator.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Value_Input.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Value_Slider.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_vertex.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_visual.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Widget.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Window.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Window_fullscreen.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Window_hotspot.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Window_iconize.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_WM.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Workspace.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Xpm.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\numericsort.c
# End Source File
# Begin Source File

SOURCE=..\src\core\scandir.c
# End Source File
# Begin Source File

SOURCE=..\src\core\vsnprintf.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\core\ARRAY.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\fastarrow.h
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_cmap.h
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_XColor.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\mediumarrow.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Pixmaps.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\slowarrow.h
# End Source File
# End Group
# End Target
# End Project
