# Microsoft Developer Studio Project File - Name="efltk_xml" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=efltk_xml - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "efltk_xml.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "efltk_xml.mak" CFG="efltk_xml - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "efltk_xml - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "efltk_xml - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "efltk_xml - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "efltk_xml___Win32_Release"
# PROP BASE Intermediate_Dir "efltk_xml___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "efltk_xml___Win32_Release"
# PROP Intermediate_Dir "efltk_xml___Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../visualc" /I "../.." /I "../" /I "." /D "NDEBUG" /D "_MSC_DLL" /D "WIN32" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN" /D "FL_LIBRARY" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\efltk_xml.lib"

!ELSEIF  "$(CFG)" == "efltk_xml - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "efltk_xml___Win32_Debug"
# PROP BASE Intermediate_Dir "efltk_xml___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "efltk_xml___Win32_Debug"
# PROP Intermediate_Dir "efltk_xml___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../visualc" /I "../.." /I "../" /I "." /D "_DEBUG" /D "_MSC_DLL" /D "WIN32" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\efltk_xmld.lib"

!ENDIF 

# Begin Target

# Name "efltk_xml - Win32 Release"
# Name "efltk_xml - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\xml\Fl_XmlCtx.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\Fl_XmlDoc.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\Fl_XmlNode.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\Fl_XmlParser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\Fl_XmlTokenizer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\efltk\xml\Fl_Xml.h
# End Source File
# Begin Source File

SOURCE=..\efltk\xml\Fl_XmlCtx.h
# End Source File
# Begin Source File

SOURCE=..\efltk\xml\Fl_XmlDoc.h
# End Source File
# Begin Source File

SOURCE=..\efltk\xml\Fl_XmlHandler.h
# End Source File
# Begin Source File

SOURCE=..\efltk\xml\Fl_XmlNode.h
# End Source File
# Begin Source File

SOURCE=..\efltk\xml\Fl_XmlNode_List.h
# End Source File
# Begin Source File

SOURCE=..\efltk\xml\Fl_XmlParser.h
# End Source File
# Begin Source File

SOURCE=..\efltk\xml\Fl_XmlTokenizer.h
# End Source File
# End Group
# End Target
# End Project
