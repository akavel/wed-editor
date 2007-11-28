# Microsoft Developer Studio Project File - Name="wed" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=wed - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wed.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wed.mak" CFG="wed - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wed - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "wed - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "wed"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wed - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:IX86
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "wed - Win32 Release"
# Name "wed - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\about.cpp
# End Source File
# Begin Source File

SOURCE=.\AppTop.cpp
# End Source File
# Begin Source File

SOURCE=.\BufferList.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\coco.cpp
# End Source File
# Begin Source File

SOURCE=.\diff.cpp
# End Source File
# Begin Source File

SOURCE=.\editor.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDialogST.cpp
# End Source File
# Begin Source File

SOURCE=.\FileInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\gotoline.cpp
# End Source File
# Begin Source File

SOURCE=.\HoldHead.cpp
# End Source File
# Begin Source File

SOURCE=.\logomdi.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\notepad.cpp
# End Source File
# Begin Source File

SOURCE=.\oleComm.cpp
# End Source File
# Begin Source File

SOURCE=.\page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Page2.cpp
# End Source File
# Begin Source File

SOURCE=.\regex.cpp
# End Source File
# Begin Source File

SOURCE=.\Register.cpp
# End Source File
# Begin Source File

SOURCE=.\Search.cpp
# End Source File
# Begin Source File

SOURCE=.\sellist.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup.cpp
# End Source File
# Begin Source File

SOURCE=.\spell.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\src.cpp
# End Source File
# Begin Source File

SOURCE=.\srcsel.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stringex.cpp
# End Source File
# Begin Source File

SOURCE=.\StrList.cpp
# End Source File
# Begin Source File

SOURCE=.\SubClass.cpp
# End Source File
# Begin Source File

SOURCE=.\undo.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewText.cpp
# End Source File
# Begin Source File

SOURCE=.\wed.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\wed.hpj

!IF  "$(CFG)" == "wed - Win32 Release"

USERDEP__WED_H="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	
# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=wed
InputPath=.\hlp\wed.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

USERDEP__WED_H="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=wed
InputPath=.\hlp\wed.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\wed.rc
# End Source File
# Begin Source File

SOURCE=.\wedDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\wedView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppTop.h
# End Source File
# Begin Source File

SOURCE=.\BufferList.h
# End Source File
# Begin Source File

SOURCE=.\build.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\coco.h
# End Source File
# Begin Source File

SOURCE=.\diff.h
# End Source File
# Begin Source File

SOURCE=.\editor.h
# End Source File
# Begin Source File

SOURCE=.\FileDialogST.h
# End Source File
# Begin Source File

SOURCE=.\FileInfo.h
# End Source File
# Begin Source File

SOURCE=.\gotoline.h
# End Source File
# Begin Source File

SOURCE=.\HoldHead.h
# End Source File
# Begin Source File

SOURCE=.\limits.h
# End Source File
# Begin Source File

SOURCE=.\logomdi.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
# End Source File
# Begin Source File

SOURCE=.\notepad.h
# End Source File
# Begin Source File

SOURCE=.\oleComm.h
# End Source File
# Begin Source File

SOURCE=.\page1.h
# End Source File
# Begin Source File

SOURCE=.\Page2.h
# End Source File
# Begin Source File

SOURCE=.\regex.h
# End Source File
# Begin Source File

SOURCE=.\Register.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Search.h
# End Source File
# Begin Source File

SOURCE=.\sellist.h
# End Source File
# Begin Source File

SOURCE=.\Setup.h
# End Source File
# Begin Source File

SOURCE=.\spell.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\srcsel.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\stringex.h
# End Source File
# Begin Source File

SOURCE=.\StrList.h
# End Source File
# Begin Source File

SOURCE=.\SubClass.h
# End Source File
# Begin Source File

SOURCE=.\undo.h
# End Source File
# Begin Source File

SOURCE=.\ViewText.h
# End Source File
# Begin Source File

SOURCE=.\wed.h
# End Source File
# Begin Source File

SOURCE=.\wedDoc.h
# End Source File
# Begin Source File

SOURCE=.\wedView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wed.ico
# End Source File
# Begin Source File

SOURCE=.\res\wed.rc2
# End Source File
# Begin Source File

SOURCE=.\res\wedDoc.ico
# End Source File
# Begin Source File

SOURCE=.\whmarb.bmp
# End Source File
# Begin Source File

SOURCE=.\whtmarb1.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\MakeHelp.bat
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\wed.cnt
# End Source File
# Begin Source File

SOURCE=.\wed.html
# End Source File
# End Group
# Begin Group "Text"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\build.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Group
# End Target
# End Project
# Section wed : {508C381A-21A6-4462-A3D7-C6F99D34C238}
# 	2:16:FileDialogST.cpp:FileDialogST.cpp
# 	2:26:ENUM: SHVIEW_ListViewModes:SHVIEW_ListViewModes
# 	2:14:FileDialogST.h:FileDialogST.h
# 	2:19:Application Include:wed.h
# 	2:20:CLASS: CFileDialogST:CFileDialogST
# End Section
