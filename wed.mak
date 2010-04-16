# Microsoft Developer Studio Generated NMAKE File, Based on wed.dsp
!IF "$(CFG)" == ""
CFG=wed - Win32 Debug
!MESSAGE No configuration specified. Defaulting to wed - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "wed - Win32 Release" && "$(CFG)" != "wed - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "wed - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\Release\wed.hlp" "$(OUTDIR)\wed.exe" "$(OUTDIR)\wed.bsc"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\about.sbr"
	-@erase "$(INTDIR)\AppTop.obj"
	-@erase "$(INTDIR)\AppTop.sbr"
	-@erase "$(INTDIR)\BufferList.obj"
	-@erase "$(INTDIR)\BufferList.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\coco.obj"
	-@erase "$(INTDIR)\coco.sbr"
	-@erase "$(INTDIR)\diff.obj"
	-@erase "$(INTDIR)\diff.sbr"
	-@erase "$(INTDIR)\editor.obj"
	-@erase "$(INTDIR)\editor.sbr"
	-@erase "$(INTDIR)\FileDialogST.obj"
	-@erase "$(INTDIR)\FileDialogST.sbr"
	-@erase "$(INTDIR)\FileInfo.obj"
	-@erase "$(INTDIR)\FileInfo.sbr"
	-@erase "$(INTDIR)\gotoline.obj"
	-@erase "$(INTDIR)\gotoline.sbr"
	-@erase "$(INTDIR)\HoldHead.obj"
	-@erase "$(INTDIR)\HoldHead.sbr"
	-@erase "$(INTDIR)\logomdi.obj"
	-@erase "$(INTDIR)\logomdi.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.sbr"
	-@erase "$(INTDIR)\mxpad.obj"
	-@erase "$(INTDIR)\mxpad.sbr"
	-@erase "$(INTDIR)\oleComm.obj"
	-@erase "$(INTDIR)\oleComm.sbr"
	-@erase "$(INTDIR)\page1.obj"
	-@erase "$(INTDIR)\page1.sbr"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\Page2.sbr"
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\regex.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\Search.obj"
	-@erase "$(INTDIR)\Search.sbr"
	-@erase "$(INTDIR)\sellist.obj"
	-@erase "$(INTDIR)\sellist.sbr"
	-@erase "$(INTDIR)\Setup.obj"
	-@erase "$(INTDIR)\Setup.sbr"
	-@erase "$(INTDIR)\spell.obj"
	-@erase "$(INTDIR)\spell.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\src.obj"
	-@erase "$(INTDIR)\src.sbr"
	-@erase "$(INTDIR)\srcsel.obj"
	-@erase "$(INTDIR)\srcsel.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\stringex.obj"
	-@erase "$(INTDIR)\stringex.sbr"
	-@erase "$(INTDIR)\StrList.obj"
	-@erase "$(INTDIR)\StrList.sbr"
	-@erase "$(INTDIR)\SubClass.obj"
	-@erase "$(INTDIR)\SubClass.sbr"
	-@erase "$(INTDIR)\undo.obj"
	-@erase "$(INTDIR)\undo.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\ViewText.obj"
	-@erase "$(INTDIR)\ViewText.sbr"
	-@erase "$(INTDIR)\wed.obj"
	-@erase "$(INTDIR)\wed.pch"
	-@erase "$(INTDIR)\wed.res"
	-@erase "$(INTDIR)\wed.sbr"
	-@erase "$(INTDIR)\wedDoc.obj"
	-@erase "$(INTDIR)\wedDoc.sbr"
	-@erase "$(INTDIR)\wedView.obj"
	-@erase "$(INTDIR)\wedView.sbr"
	-@erase "$(OUTDIR)\wed.bsc"
	-@erase "$(OUTDIR)\wed.exe"
	-@erase ".\Release\wed.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\wed.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\wed.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wed.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\about.sbr" \
	"$(INTDIR)\AppTop.sbr" \
	"$(INTDIR)\BufferList.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\coco.sbr" \
	"$(INTDIR)\diff.sbr" \
	"$(INTDIR)\editor.sbr" \
	"$(INTDIR)\FileDialogST.sbr" \
	"$(INTDIR)\FileInfo.sbr" \
	"$(INTDIR)\gotoline.sbr" \
	"$(INTDIR)\HoldHead.sbr" \
	"$(INTDIR)\logomdi.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\misc.sbr" \
	"$(INTDIR)\mxpad.sbr" \
	"$(INTDIR)\oleComm.sbr" \
	"$(INTDIR)\page1.sbr" \
	"$(INTDIR)\Page2.sbr" \
	"$(INTDIR)\regex.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\Search.sbr" \
	"$(INTDIR)\sellist.sbr" \
	"$(INTDIR)\Setup.sbr" \
	"$(INTDIR)\spell.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\src.sbr" \
	"$(INTDIR)\srcsel.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\stringex.sbr" \
	"$(INTDIR)\StrList.sbr" \
	"$(INTDIR)\SubClass.sbr" \
	"$(INTDIR)\undo.sbr" \
	"$(INTDIR)\ViewText.sbr" \
	"$(INTDIR)\wed.sbr" \
	"$(INTDIR)\wedDoc.sbr" \
	"$(INTDIR)\wedView.sbr"

"$(OUTDIR)\wed.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=msimg32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\wed.pdb" /machine:IX86 /out:"$(OUTDIR)\wed.exe" 
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\AppTop.obj" \
	"$(INTDIR)\BufferList.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\coco.obj" \
	"$(INTDIR)\diff.obj" \
	"$(INTDIR)\editor.obj" \
	"$(INTDIR)\FileDialogST.obj" \
	"$(INTDIR)\FileInfo.obj" \
	"$(INTDIR)\gotoline.obj" \
	"$(INTDIR)\HoldHead.obj" \
	"$(INTDIR)\logomdi.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\mxpad.obj" \
	"$(INTDIR)\oleComm.obj" \
	"$(INTDIR)\page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\regex.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\Search.obj" \
	"$(INTDIR)\sellist.obj" \
	"$(INTDIR)\Setup.obj" \
	"$(INTDIR)\spell.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\src.obj" \
	"$(INTDIR)\srcsel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stringex.obj" \
	"$(INTDIR)\StrList.obj" \
	"$(INTDIR)\SubClass.obj" \
	"$(INTDIR)\undo.obj" \
	"$(INTDIR)\ViewText.obj" \
	"$(INTDIR)\wed.obj" \
	"$(INTDIR)\wedDoc.obj" \
	"$(INTDIR)\wedView.obj" \
	"$(INTDIR)\wed.res"

"$(OUTDIR)\wed.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\Debug\wed.hlp" "$(OUTDIR)\wed.exe" "$(OUTDIR)\wed.bsc"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\about.sbr"
	-@erase "$(INTDIR)\AppTop.obj"
	-@erase "$(INTDIR)\AppTop.sbr"
	-@erase "$(INTDIR)\BufferList.obj"
	-@erase "$(INTDIR)\BufferList.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\coco.obj"
	-@erase "$(INTDIR)\coco.sbr"
	-@erase "$(INTDIR)\diff.obj"
	-@erase "$(INTDIR)\diff.sbr"
	-@erase "$(INTDIR)\editor.obj"
	-@erase "$(INTDIR)\editor.sbr"
	-@erase "$(INTDIR)\FileDialogST.obj"
	-@erase "$(INTDIR)\FileDialogST.sbr"
	-@erase "$(INTDIR)\FileInfo.obj"
	-@erase "$(INTDIR)\FileInfo.sbr"
	-@erase "$(INTDIR)\gotoline.obj"
	-@erase "$(INTDIR)\gotoline.sbr"
	-@erase "$(INTDIR)\HoldHead.obj"
	-@erase "$(INTDIR)\HoldHead.sbr"
	-@erase "$(INTDIR)\logomdi.obj"
	-@erase "$(INTDIR)\logomdi.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.sbr"
	-@erase "$(INTDIR)\mxpad.obj"
	-@erase "$(INTDIR)\mxpad.sbr"
	-@erase "$(INTDIR)\oleComm.obj"
	-@erase "$(INTDIR)\oleComm.sbr"
	-@erase "$(INTDIR)\page1.obj"
	-@erase "$(INTDIR)\page1.sbr"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\Page2.sbr"
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\regex.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\Search.obj"
	-@erase "$(INTDIR)\Search.sbr"
	-@erase "$(INTDIR)\sellist.obj"
	-@erase "$(INTDIR)\sellist.sbr"
	-@erase "$(INTDIR)\Setup.obj"
	-@erase "$(INTDIR)\Setup.sbr"
	-@erase "$(INTDIR)\spell.obj"
	-@erase "$(INTDIR)\spell.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\src.obj"
	-@erase "$(INTDIR)\src.sbr"
	-@erase "$(INTDIR)\srcsel.obj"
	-@erase "$(INTDIR)\srcsel.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\stringex.obj"
	-@erase "$(INTDIR)\stringex.sbr"
	-@erase "$(INTDIR)\StrList.obj"
	-@erase "$(INTDIR)\StrList.sbr"
	-@erase "$(INTDIR)\SubClass.obj"
	-@erase "$(INTDIR)\SubClass.sbr"
	-@erase "$(INTDIR)\undo.obj"
	-@erase "$(INTDIR)\undo.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\ViewText.obj"
	-@erase "$(INTDIR)\ViewText.sbr"
	-@erase "$(INTDIR)\wed.obj"
	-@erase "$(INTDIR)\wed.pch"
	-@erase "$(INTDIR)\wed.res"
	-@erase "$(INTDIR)\wed.sbr"
	-@erase "$(INTDIR)\wedDoc.obj"
	-@erase "$(INTDIR)\wedDoc.sbr"
	-@erase "$(INTDIR)\wedView.obj"
	-@erase "$(INTDIR)\wedView.sbr"
	-@erase "$(OUTDIR)\wed.bsc"
	-@erase "$(OUTDIR)\wed.exe"
	-@erase "$(OUTDIR)\wed.ilk"
	-@erase "$(OUTDIR)\wed.pdb"
	-@erase ".\Debug\wed.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\wed.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\wed.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wed.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\about.sbr" \
	"$(INTDIR)\AppTop.sbr" \
	"$(INTDIR)\BufferList.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\coco.sbr" \
	"$(INTDIR)\diff.sbr" \
	"$(INTDIR)\editor.sbr" \
	"$(INTDIR)\FileDialogST.sbr" \
	"$(INTDIR)\FileInfo.sbr" \
	"$(INTDIR)\gotoline.sbr" \
	"$(INTDIR)\HoldHead.sbr" \
	"$(INTDIR)\logomdi.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\misc.sbr" \
	"$(INTDIR)\mxpad.sbr" \
	"$(INTDIR)\oleComm.sbr" \
	"$(INTDIR)\page1.sbr" \
	"$(INTDIR)\Page2.sbr" \
	"$(INTDIR)\regex.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\Search.sbr" \
	"$(INTDIR)\sellist.sbr" \
	"$(INTDIR)\Setup.sbr" \
	"$(INTDIR)\spell.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\src.sbr" \
	"$(INTDIR)\srcsel.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\stringex.sbr" \
	"$(INTDIR)\StrList.sbr" \
	"$(INTDIR)\SubClass.sbr" \
	"$(INTDIR)\undo.sbr" \
	"$(INTDIR)\ViewText.sbr" \
	"$(INTDIR)\wed.sbr" \
	"$(INTDIR)\wedDoc.sbr" \
	"$(INTDIR)\wedView.sbr"

"$(OUTDIR)\wed.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=msimg32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\wed.pdb" /debug /machine:I386 /out:"$(OUTDIR)\wed.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\AppTop.obj" \
	"$(INTDIR)\BufferList.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\coco.obj" \
	"$(INTDIR)\diff.obj" \
	"$(INTDIR)\editor.obj" \
	"$(INTDIR)\FileDialogST.obj" \
	"$(INTDIR)\FileInfo.obj" \
	"$(INTDIR)\gotoline.obj" \
	"$(INTDIR)\HoldHead.obj" \
	"$(INTDIR)\logomdi.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\mxpad.obj" \
	"$(INTDIR)\oleComm.obj" \
	"$(INTDIR)\page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\regex.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\Search.obj" \
	"$(INTDIR)\sellist.obj" \
	"$(INTDIR)\Setup.obj" \
	"$(INTDIR)\spell.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\src.obj" \
	"$(INTDIR)\srcsel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stringex.obj" \
	"$(INTDIR)\StrList.obj" \
	"$(INTDIR)\SubClass.obj" \
	"$(INTDIR)\undo.obj" \
	"$(INTDIR)\ViewText.obj" \
	"$(INTDIR)\wed.obj" \
	"$(INTDIR)\wedDoc.obj" \
	"$(INTDIR)\wedView.obj" \
	"$(INTDIR)\wed.res"

"$(OUTDIR)\wed.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("wed.dep")
!INCLUDE "wed.dep"
!ELSE 
!MESSAGE Warning: cannot find "wed.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "wed - Win32 Release" || "$(CFG)" == "wed - Win32 Debug"
SOURCE=.\about.cpp

"$(INTDIR)\about.obj"	"$(INTDIR)\about.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\AppTop.cpp

"$(INTDIR)\AppTop.obj"	"$(INTDIR)\AppTop.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\BufferList.cpp

"$(INTDIR)\BufferList.obj"	"$(INTDIR)\BufferList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\ChildFrm.cpp

"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\coco.cpp

"$(INTDIR)\coco.obj"	"$(INTDIR)\coco.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\diff.cpp

"$(INTDIR)\diff.obj"	"$(INTDIR)\diff.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\editor.cpp

"$(INTDIR)\editor.obj"	"$(INTDIR)\editor.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\FileDialogST.cpp

"$(INTDIR)\FileDialogST.obj"	"$(INTDIR)\FileDialogST.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\FileInfo.cpp

"$(INTDIR)\FileInfo.obj"	"$(INTDIR)\FileInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\gotoline.cpp

"$(INTDIR)\gotoline.obj"	"$(INTDIR)\gotoline.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\HoldHead.cpp

"$(INTDIR)\HoldHead.obj"	"$(INTDIR)\HoldHead.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\logomdi.cpp

"$(INTDIR)\logomdi.obj"	"$(INTDIR)\logomdi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\misc.cpp

"$(INTDIR)\misc.obj"	"$(INTDIR)\misc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\mxpad.cpp

"$(INTDIR)\mxpad.obj"	"$(INTDIR)\mxpad.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\oleComm.cpp

"$(INTDIR)\oleComm.obj"	"$(INTDIR)\oleComm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\page1.cpp

"$(INTDIR)\page1.obj"	"$(INTDIR)\page1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\Page2.cpp

"$(INTDIR)\Page2.obj"	"$(INTDIR)\Page2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\regex.cpp

"$(INTDIR)\regex.obj"	"$(INTDIR)\regex.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\Register.cpp

"$(INTDIR)\Register.obj"	"$(INTDIR)\Register.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\Search.cpp

"$(INTDIR)\Search.obj"	"$(INTDIR)\Search.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\sellist.cpp

"$(INTDIR)\sellist.obj"	"$(INTDIR)\sellist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\Setup.cpp

"$(INTDIR)\Setup.obj"	"$(INTDIR)\Setup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\spell.cpp

"$(INTDIR)\spell.obj"	"$(INTDIR)\spell.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\Splash.cpp

"$(INTDIR)\Splash.obj"	"$(INTDIR)\Splash.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\src.cpp

"$(INTDIR)\src.obj"	"$(INTDIR)\src.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\srcsel.cpp

"$(INTDIR)\srcsel.obj"	"$(INTDIR)\srcsel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\wed.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\wed.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\wed.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\wed.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\stringex.cpp

"$(INTDIR)\stringex.obj"	"$(INTDIR)\stringex.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\StrList.cpp

"$(INTDIR)\StrList.obj"	"$(INTDIR)\StrList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\SubClass.cpp

"$(INTDIR)\SubClass.obj"	"$(INTDIR)\SubClass.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\undo.cpp

"$(INTDIR)\undo.obj"	"$(INTDIR)\undo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\ViewText.cpp

"$(INTDIR)\ViewText.obj"	"$(INTDIR)\ViewText.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\wed.cpp

"$(INTDIR)\wed.obj"	"$(INTDIR)\wed.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\hlp\wed.hpj

!IF  "$(CFG)" == "wed - Win32 Release"

OutDir=.\Release
ProjDir=.
TargetName=wed
InputPath=.\hlp\wed.hpj
USERDEP__WED_H="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	

"$(INTDIR)\wed.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__WED_H)
	<<tempfile.bat 
	@echo off 
	call "$(ProjDir)\makehelp.bat"
<< 
	

!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

OutDir=.\Debug
ProjDir=.
TargetName=wed
InputPath=.\hlp\wed.hpj
USERDEP__WED_H="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	

"$(INTDIR)\wed.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__WED_H)
	<<tempfile.bat 
	@echo off 
	call "$(ProjDir)\makehelp.bat"
<< 
	

!ENDIF 

SOURCE=.\wed.rc

"$(INTDIR)\wed.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\wedDoc.cpp

"$(INTDIR)\wedDoc.obj"	"$(INTDIR)\wedDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


SOURCE=.\wedView.cpp

"$(INTDIR)\wedView.obj"	"$(INTDIR)\wedView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"



!ENDIF 

