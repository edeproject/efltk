# Microsoft Developer Studio Project File - Name="efluid" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=efluid - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "efluid.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "efluid.mak" CFG="efluid - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "efluid - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "efluid - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "efluid - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "efluid___Win32_Release"
# PROP BASE Intermediate_Dir "efluid___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "efluid___Win32_Release"
# PROP Intermediate_Dir "efluid___Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "efluid - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "efluid___Win32_Debug"
# PROP BASE Intermediate_Dir "efluid___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "efluid___Win32_Debug"
# PROP Intermediate_Dir "efluid___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W1 /Gm /GX /ZI /Od /I "../visualc" /I "../.." /I "../" /I "." /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN" /D "_MSC_DLL" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 efltkd.lib efltk_imagesd.lib libpng.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib Mpr.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcd" /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "efluid - Win32 Release"
# Name "efluid - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\fluid\about_panel.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\alignment_panel.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\code.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\coding_style.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\coding_style_func.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\factory.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\file.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\Fl_Function_Type.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\Fl_Group_Type.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\Fl_Menu_Type.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\Fl_Type.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\Fl_Widget_Type.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\Fl_Window_Type.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\fluid.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\Fluid_Image.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\Fluid_Plugins.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\function_panel.cxx
# End Source File
# Begin Source File

SOURCE=..\fluid\widget_panel.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\fluid\about_panel.h
# End Source File
# Begin Source File

SOURCE=..\fluid\alignment_panel.h
# End Source File
# Begin Source File

SOURCE=..\fluid\coding_style.h
# End Source File
# Begin Source File

SOURCE=..\fluid\Fl_Type.h
# End Source File
# Begin Source File

SOURCE=..\fluid\Fluid_Image.h
# End Source File
# Begin Source File

SOURCE=..\fluid\Fluid_Plugins.h
# End Source File
# Begin Source File

SOURCE=..\fluid\function_panel.h
# End Source File
# Begin Source File

SOURCE=..\fluid\Shortcut_Button.h
# End Source File
# Begin Source File

SOURCE=..\fluid\widget_panel.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project