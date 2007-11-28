# Microsoft Developer Studio Generated NMAKE File, Based on wed.dsp
!IF "$(CFG)" == ""
CFG=wed - Win32 Debug
!MESSAGE No configuration specified. Defaulting to wed - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "wed - Win32 Release" && "$(CFG)" != "wed - Win32 Debug" && "$(CFG)" != "wed - Win32 Release_Alpha"
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
!MESSAGE "wed - Win32 Release_Alpha" (based on "Win32 (ALPHA) Application")
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

ALL : ".\Release\wed.hlp" "$(OUTDIR)\wed.exe"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\AppTop.obj"
	-@erase "$(INTDIR)\BufferList.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\coco.obj"
	-@erase "$(INTDIR)\diff.obj"
	-@erase "$(INTDIR)\editor.obj"
	-@erase "$(INTDIR)\FileInfo.obj"
	-@erase "$(INTDIR)\gotoline.obj"
	-@erase "$(INTDIR)\HoldHead.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\notepad.obj"
	-@erase "$(INTDIR)\oleComm.obj"
	-@erase "$(INTDIR)\page1.obj"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Search.obj"
	-@erase "$(INTDIR)\sellist.obj"
	-@erase "$(INTDIR)\Setup.obj"
	-@erase "$(INTDIR)\spell.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\src.obj"
	-@erase "$(INTDIR)\srcsel.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\stringex.obj"
	-@erase "$(INTDIR)\StrList.obj"
	-@erase "$(INTDIR)\SubClass.obj"
	-@erase "$(INTDIR)\undo.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\ViewText.obj"
	-@erase "$(INTDIR)\wed.obj"
	-@erase "$(INTDIR)\wed.pch"
	-@erase "$(INTDIR)\wed.res"
	-@erase "$(INTDIR)\wedDoc.obj"
	-@erase "$(INTDIR)\wedView.obj"
	-@erase "$(OUTDIR)\wed.exe"
	-@erase ".\Release\wed.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\wed.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\wed.pdb" /machine:IX86 /out:"$(OUTDIR)\wed.exe" 
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\AppTop.obj" \
	"$(INTDIR)\BufferList.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\coco.obj" \
	"$(INTDIR)\diff.obj" \
	"$(INTDIR)\editor.obj" \
	"$(INTDIR)\FileInfo.obj" \
	"$(INTDIR)\gotoline.obj" \
	"$(INTDIR)\HoldHead.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\notepad.obj" \
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
	-@erase "$(INTDIR)\FileInfo.obj"
	-@erase "$(INTDIR)\FileInfo.sbr"
	-@erase "$(INTDIR)\gotoline.obj"
	-@erase "$(INTDIR)\gotoline.sbr"
	-@erase "$(INTDIR)\HoldHead.obj"
	-@erase "$(INTDIR)\HoldHead.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.sbr"
	-@erase "$(INTDIR)\notepad.obj"
	-@erase "$(INTDIR)\notepad.sbr"
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
	"$(INTDIR)\FileInfo.sbr" \
	"$(INTDIR)\gotoline.sbr" \
	"$(INTDIR)\HoldHead.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\misc.sbr" \
	"$(INTDIR)\notepad.sbr" \
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
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\wed.pdb" /debug /machine:I386 /out:"$(OUTDIR)\wed.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\AppTop.obj" \
	"$(INTDIR)\BufferList.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\coco.obj" \
	"$(INTDIR)\diff.obj" \
	"$(INTDIR)\editor.obj" \
	"$(INTDIR)\FileInfo.obj" \
	"$(INTDIR)\gotoline.obj" \
	"$(INTDIR)\HoldHead.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\notepad.obj" \
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

!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

OUTDIR=.\wed___Win32_Release_Alpha
INTDIR=.\wed___Win32_Release_Alpha
# Begin Custom Macros
OutDir=.\wed___Win32_Release_Alpha
# End Custom Macros

ALL : ".\wed___Win32_Release_Alpha\wed.hlp" "$(OUTDIR)\wed.exe"


CLEAN :
	-@erase "$(INTDIR)\wed.res"
	-@erase "$(OUTDIR)\wed.exe"
	-@erase ".\wed___Win32_Release_Alpha\wed.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\wed.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wed.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\wed.pdb" /machine:ALPHA /out:"$(OUTDIR)\wed.exe" 
LINK32_OBJS= \
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


!IF "$(CFG)" == "wed - Win32 Release" || "$(CFG)" == "wed - Win32 Debug" || "$(CFG)" == "wed - Win32 Release_Alpha"
SOURCE=.\about.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\about.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\about.obj"	"$(INTDIR)\about.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\AppTop.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\AppTop.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\AppTop.obj"	"$(INTDIR)\AppTop.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\BufferList.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\BufferList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\BufferList.obj"	"$(INTDIR)\BufferList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\coco.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\coco.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\coco.obj"	"$(INTDIR)\coco.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\diff.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\diff.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\diff.obj"	"$(INTDIR)\diff.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\editor.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\editor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\editor.obj"	"$(INTDIR)\editor.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\FileInfo.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\FileInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\FileInfo.obj"	"$(INTDIR)\FileInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\gotoline.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\gotoline.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\gotoline.obj"	"$(INTDIR)\gotoline.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\HoldHead.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\HoldHead.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\HoldHead.obj"	"$(INTDIR)\HoldHead.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\misc.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\misc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\misc.obj"	"$(INTDIR)\misc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\notepad.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\notepad.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\notepad.obj"	"$(INTDIR)\notepad.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\oleComm.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\oleComm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\oleComm.obj"	"$(INTDIR)\oleComm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\page1.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\page1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\page1.obj"	"$(INTDIR)\page1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\Page2.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\Page2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\Page2.obj"	"$(INTDIR)\Page2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\regex.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\regex.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\regex.obj"	"$(INTDIR)\regex.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\Register.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\Register.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\Register.obj"	"$(INTDIR)\Register.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\Search.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\Search.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\Search.obj"	"$(INTDIR)\Search.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\sellist.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\sellist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\sellist.obj"	"$(INTDIR)\sellist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\Setup.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\Setup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\Setup.obj"	"$(INTDIR)\Setup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\spell.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\spell.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\spell.obj"	"$(INTDIR)\spell.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\Splash.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\Splash.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\Splash.obj"	"$(INTDIR)\Splash.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\src.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\src.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\src.obj"	"$(INTDIR)\src.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\srcsel.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\srcsel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\srcsel.obj"	"$(INTDIR)\srcsel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\wed.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\wed.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\wed.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\wed.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\stringex.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\stringex.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\stringex.obj"	"$(INTDIR)\stringex.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\StrList.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\StrList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\StrList.obj"	"$(INTDIR)\StrList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\SubClass.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\SubClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\SubClass.obj"	"$(INTDIR)\SubClass.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\undo.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\undo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\undo.obj"	"$(INTDIR)\undo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\ViewText.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\ViewText.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\ViewText.obj"	"$(INTDIR)\ViewText.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\wed.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\wed.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\wed.obj"	"$(INTDIR)\wed.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

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
	

!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

OutDir=.\wed___Win32_Release_Alpha
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

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\wedDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\wedDoc.obj"	"$(INTDIR)\wedDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 

SOURCE=.\wedView.cpp

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\wedView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\wedView.obj"	"$(INTDIR)\wedView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Release_Alpha"

!ENDIF 


!ENDIF 

