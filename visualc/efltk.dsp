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
# ADD CPP /nologo /MD /W3 /GX /Ox /Ot /Op /Ob2 /I "." /I ".." /I "../visualc" /D "NDEBUG" /D "_MSC_DLL" /D "WIN32" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN" /YX /FD /c
# SUBTRACT CPP /Os
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\efltk.lib"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../visualc" /I "../.." /I "../" /I "." /D "_DEBUG" /D "_MSC_DLL" /D "WIN32" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN_MBCS" /D "_LIB" /FD /GZ /c
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

SOURCE=..\src\widgets\Fl_Calendar.cpp
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

SOURCE=..\src\core\Fl_Data_Fields.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Data_Source.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_Date_Time.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Date_Time_Input.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Dial.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Dialog_Data_Source.cpp
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_diamond_box.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_Directory_DS.cpp
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

SOURCE=..\src\core\Fl_Lists.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_ListView.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\Fl_ListView_Header.cpp
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

SOURCE=..\src\widgets\Fl_MDI_Bar.cpp
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

SOURCE=..\src\widgets\Fl_Multi_Tabs.cpp
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

SOURCE=..\src\widgets\Fl_Popup_Window.cpp
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

SOURCE=..\src\core\fl_utf8.c
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

SOURCE=..\src\core\Fl_Variant.cpp
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

SOURCE=..\efltk\Enumerations.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\fastarrow.h
# End Source File
# Begin Source File

SOURCE=..\efltk\filename.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Adjuster.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Align_Group.h
# End Source File
# Begin Source File

SOURCE=..\efltk\fl_ask.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Bar.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Bitmap.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Box.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Boxtype.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Browser.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Calendar.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Check_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Choice.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Clock.h
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_cmap.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Color.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Color_Chooser.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Config.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Data_Source.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Date_Time.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Dial.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Dialog.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Dialog_Data_Source.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Directory_DS.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Divider.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Double_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\fl_draw.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Export.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_File_Dialog.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_FileBrowser.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_FileInput.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Flags.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Float_Input.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Font.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Gl_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Group.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Help_Dialog.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Highlight_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Hor_Fill_Slider.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Hor_Nice_Slider.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Hor_Slider.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Hor_Value_Slider.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Image.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Image_Cache.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Image_Filter.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Image_List.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Images.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Input.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Input_Browser.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Int_Input.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Int_List.h
# End Source File
# Begin Source File

SOURCE=..\src\core\fl_internal.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Item.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Item_Group.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Labeltype.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Light_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Line_Dial.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_ListView.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_ListView_Header.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_ListView_Item.h
# End Source File
# Begin Source File

SOURCE=..\efltk\fl_load_plugin.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Locale.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Main_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_MDI_Bar.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_MDI_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Menu_.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Menu_Bar.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Menu_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Menu_Item.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Menu_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\fl_message.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Multi_Browser.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Multi_Image.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Multi_Tabs.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Multiline_Input.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Multiline_Output.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Nice_Slider.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Numeric_Input.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Output.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Overlay_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Pack.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Pixmap.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Popup_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_ProgressBar.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Ptr_List.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Ptr_Stack.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_PtrList.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Radio_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Radio_Item.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Radio_Light_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Radio_Round_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Renderer.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Repeat_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Return_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Roller.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Round_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Round_Clock.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Scroll.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Scrollbar.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Secret_Input.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Select_Browser.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Shaped_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\fl_show_colormap.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Simple_Counter.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Simple_Html.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Single_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Slider.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_String.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_String_List.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Style.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Style_Set.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Tabs.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Text_Buffer.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Text_Display.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Text_Editor.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Thread.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Thread_Linux.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Thread_w32.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Threads.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Tile.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Timer.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Toggle_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Toggle_Item.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Toggle_Light_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Toggle_Round_Button.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Tool_Bar.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Tooltip.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Tree.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Util.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Valuator.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Value_Input.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Value_List.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Value_Map.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Value_Output.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Value_Slider.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Value_Stack.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Variant.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Widget.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Widget_List.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Window.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_WM.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Wordwrap_Input.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Wordwrap_Output.h
# End Source File
# Begin Source File

SOURCE=..\efltk\Fl_Workspace.h
# End Source File
# Begin Source File

SOURCE=..\src\core\Fl_XColor.h
# End Source File
# Begin Source File

SOURCE=..\efltk\gl.h
# End Source File
# Begin Source File

SOURCE=..\efltk\gl2opengl.h
# End Source File
# Begin Source File

SOURCE=..\efltk\gl_draw.h
# End Source File
# Begin Source File

SOURCE=..\efltk\math.h
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
# Begin Source File

SOURCE=..\efltk\vsnprintf.h
# End Source File
# Begin Source File

SOURCE=..\efltk\win32.h
# End Source File
# Begin Source File

SOURCE=..\efltk\x.h
# End Source File
# End Group
# End Target
# End Project
