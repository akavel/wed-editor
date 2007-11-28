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
TargetName=wed
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\wed.exe"

!ELSE 

ALL : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\wed.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BufferList.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\coco.obj"
	-@erase "$(INTDIR)\editor.obj"
	-@erase "$(INTDIR)\FileInfo.obj"
	-@erase "$(INTDIR)\gotoline.obj"
	-@erase "$(INTDIR)\HoldHead.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\notepad.obj"
	-@erase "$(INTDIR)\Search.obj"
	-@erase "$(INTDIR)\sellist.obj"
	-@erase "$(INTDIR)\Setup.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\srcsel.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StrList.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\ViewText.obj"
	-@erase "$(INTDIR)\wed.obj"
	-@erase "$(INTDIR)\wed.pch"
	-@erase "$(INTDIR)\wed.res"
	-@erase "$(INTDIR)\wedDoc.obj"
	-@erase "$(INTDIR)\wedView.obj"
	-@erase "$(OUTDIR)\wed.exe"
	-@erase "$(OutDir)\$(TargetName).hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\wed.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\wed.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wed.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\wed.pdb" /machine:I386 /out:"$(OUTDIR)\wed.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BufferList.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\coco.obj" \
	"$(INTDIR)\editor.obj" \
	"$(INTDIR)\FileInfo.obj" \
	"$(INTDIR)\gotoline.obj" \
	"$(INTDIR)\HoldHead.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\notepad.obj" \
	"$(INTDIR)\Search.obj" \
	"$(INTDIR)\sellist.obj" \
	"$(INTDIR)\Setup.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\srcsel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StrList.obj" \
	"$(INTDIR)\ViewText.obj" \
	"$(INTDIR)\wed.obj" \
	"$(INTDIR)\wed.res" \
	"$(INTDIR)\wedDoc.obj" \
	"$(INTDIR)\wedView.obj"

"$(OUTDIR)\wed.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
PostBuild_Desc=Incrementing Build Number
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
TargetName=wed
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\wed.exe"
   c:\myutils\pcalc @build.txt > build.h
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
TargetName=wed
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\wed.exe" "$(OUTDIR)\wed.bsc"

!ELSE 

ALL : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\wed.exe" "$(OUTDIR)\wed.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BufferList.obj"
	-@erase "$(INTDIR)\BufferList.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\coco.obj"
	-@erase "$(INTDIR)\coco.sbr"
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
	-@erase "$(INTDIR)\notepad.obj"
	-@erase "$(INTDIR)\notepad.sbr"
	-@erase "$(INTDIR)\Search.obj"
	-@erase "$(INTDIR)\Search.sbr"
	-@erase "$(INTDIR)\sellist.obj"
	-@erase "$(INTDIR)\sellist.sbr"
	-@erase "$(INTDIR)\Setup.obj"
	-@erase "$(INTDIR)\Setup.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\srcsel.obj"
	-@erase "$(INTDIR)\srcsel.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StrList.obj"
	-@erase "$(INTDIR)\StrList.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
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
	-@erase "$(OutDir)\$(TargetName).hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\wed.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\wed.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wed.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BufferList.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\coco.sbr" \
	"$(INTDIR)\editor.sbr" \
	"$(INTDIR)\FileInfo.sbr" \
	"$(INTDIR)\gotoline.sbr" \
	"$(INTDIR)\HoldHead.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\notepad.sbr" \
	"$(INTDIR)\Search.sbr" \
	"$(INTDIR)\sellist.sbr" \
	"$(INTDIR)\Setup.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\srcsel.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StrList.sbr" \
	"$(INTDIR)\ViewText.sbr" \
	"$(INTDIR)\wed.sbr" \
	"$(INTDIR)\wedDoc.sbr" \
	"$(INTDIR)\wedView.sbr"

"$(OUTDIR)\wed.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\wed.pdb" /debug /machine:I386 /out:"$(OUTDIR)\wed.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BufferList.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\coco.obj" \
	"$(INTDIR)\editor.obj" \
	"$(INTDIR)\FileInfo.obj" \
	"$(INTDIR)\gotoline.obj" \
	"$(INTDIR)\HoldHead.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\notepad.obj" \
	"$(INTDIR)\Search.obj" \
	"$(INTDIR)\sellist.obj" \
	"$(INTDIR)\Setup.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\srcsel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StrList.obj" \
	"$(INTDIR)\ViewText.obj" \
	"$(INTDIR)\wed.obj" \
	"$(INTDIR)\wed.res" \
	"$(INTDIR)\wedDoc.obj" \
	"$(INTDIR)\wedView.obj"

"$(OUTDIR)\wed.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
PostBuild_Desc=Incrementing Build Number
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
TargetName=wed
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\wed.exe"\
 "$(OUTDIR)\wed.bsc"
   c:\myutils\pcalc @build.txt > build.h
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(CFG)" == "wed - Win32 Release" || "$(CFG)" == "wed - Win32 Debug"
SOURCE=.\BufferList.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_BUFFE=\
	".\BufferList.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	

"$(INTDIR)\BufferList.obj" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_BUFFE=\
	".\BufferList.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	

"$(INTDIR)\BufferList.obj"	"$(INTDIR)\BufferList.sbr" : $(SOURCE)\
 $(DEP_CPP_BUFFE) "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\coco.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_COCO_=\
	".\coco.h"\
	".\gotoline.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\ViewText.h"\
	".\wed.h"\
	

"$(INTDIR)\coco.obj" : $(SOURCE) $(DEP_CPP_COCO_) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_COCO_=\
	".\coco.h"\
	".\gotoline.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\ViewText.h"\
	".\wed.h"\
	

"$(INTDIR)\coco.obj"	"$(INTDIR)\coco.sbr" : $(SOURCE) $(DEP_CPP_COCO_)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\editor.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_EDITO=\
	".\editor.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\editor.obj" : $(SOURCE) $(DEP_CPP_EDITO) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_EDITO=\
	".\editor.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\editor.obj"	"$(INTDIR)\editor.sbr" : $(SOURCE) $(DEP_CPP_EDITO)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\FileInfo.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_FILEI=\
	".\editor.h"\
	".\FileInfo.h"\
	".\HoldHead.h"\
	".\MainFrm.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\FileInfo.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_FILEI=\
	".\editor.h"\
	".\FileInfo.h"\
	".\HoldHead.h"\
	".\MainFrm.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\FileInfo.obj"	"$(INTDIR)\FileInfo.sbr" : $(SOURCE) $(DEP_CPP_FILEI)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\gotoline.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_GOTOL=\
	".\editor.h"\
	".\gotoline.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\gotoline.obj" : $(SOURCE) $(DEP_CPP_GOTOL) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_GOTOL=\
	".\editor.h"\
	".\gotoline.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\gotoline.obj"	"$(INTDIR)\gotoline.sbr" : $(SOURCE) $(DEP_CPP_GOTOL)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\HoldHead.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_HOLDH=\
	".\HoldHead.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\HoldHead.obj" : $(SOURCE) $(DEP_CPP_HOLDH) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_HOLDH=\
	".\HoldHead.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\HoldHead.obj"	"$(INTDIR)\HoldHead.sbr" : $(SOURCE) $(DEP_CPP_HOLDH)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\notepad.cpp
DEP_CPP_NOTEP=\
	".\notepad.h"\
	

!IF  "$(CFG)" == "wed - Win32 Release"


"$(INTDIR)\notepad.obj" : $(SOURCE) $(DEP_CPP_NOTEP) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"


"$(INTDIR)\notepad.obj"	"$(INTDIR)\notepad.sbr" : $(SOURCE) $(DEP_CPP_NOTEP)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\Search.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_SEARC=\
	".\notepad.h"\
	".\Search.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\Search.obj" : $(SOURCE) $(DEP_CPP_SEARC) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_SEARC=\
	".\notepad.h"\
	".\Search.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\Search.obj"	"$(INTDIR)\Search.sbr" : $(SOURCE) $(DEP_CPP_SEARC)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\sellist.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_SELLI=\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\sellist.obj" : $(SOURCE) $(DEP_CPP_SELLI) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_SELLI=\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\sellist.obj"	"$(INTDIR)\sellist.sbr" : $(SOURCE) $(DEP_CPP_SELLI)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\Setup.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_SETUP=\
	".\sellist.h"\
	".\Setup.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\Setup.obj" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_SETUP=\
	".\sellist.h"\
	".\Setup.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\Setup.obj"	"$(INTDIR)\Setup.sbr" : $(SOURCE) $(DEP_CPP_SETUP)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\Splash.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_SPLAS=\
	".\sellist.h"\
	".\Splash.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_SPLAS=\
	".\sellist.h"\
	".\Splash.h"\
	".\srcsel.h"\
	".\wed.h"\
	

"$(INTDIR)\Splash.obj"	"$(INTDIR)\Splash.sbr" : $(SOURCE) $(DEP_CPP_SPLAS)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\srcsel.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_SRCSE=\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\srcsel.obj" : $(SOURCE) $(DEP_CPP_SRCSE) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_SRCSE=\
	".\editor.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\srcsel.obj"	"$(INTDIR)\srcsel.sbr" : $(SOURCE) $(DEP_CPP_SRCSE)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "wed - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\wed.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\wed.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\wed.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\wed.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StrList.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_STRLI=\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	

"$(INTDIR)\StrList.obj" : $(SOURCE) $(DEP_CPP_STRLI) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_STRLI=\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	

"$(INTDIR)\StrList.obj"	"$(INTDIR)\StrList.sbr" : $(SOURCE) $(DEP_CPP_STRLI)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\ViewText.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_VIEWT=\
	".\sellist.h"\
	".\srcsel.h"\
	".\ViewText.h"\
	".\wed.h"\
	

"$(INTDIR)\ViewText.obj" : $(SOURCE) $(DEP_CPP_VIEWT) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_VIEWT=\
	".\sellist.h"\
	".\srcsel.h"\
	".\ViewText.h"\
	".\wed.h"\
	

"$(INTDIR)\ViewText.obj"	"$(INTDIR)\ViewText.sbr" : $(SOURCE) $(DEP_CPP_VIEWT)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\wed.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_WED_C=\
	".\ChildFrm.h"\
	".\editor.h"\
	".\MainFrm.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\Splash.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\wed.obj" : $(SOURCE) $(DEP_CPP_WED_C) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_WED_C=\
	".\build.h"\
	".\ChildFrm.h"\
	".\editor.h"\
	".\MainFrm.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\Splash.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\wed.obj"	"$(INTDIR)\wed.sbr" : $(SOURCE) $(DEP_CPP_WED_C)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\hlp\wed.hpj
USERDEP__WED_H="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	

!IF  "$(CFG)" == "wed - Win32 Release"

OutDir=.\Release
ProjDir=.
TargetName=wed
InputPath=.\hlp\wed.hpj

"$(OutDir)\$(TargetName).hlp"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"\
 $(USERDEP__WED_H)
	call "$(ProjDir)\makehelp.bat"

!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

OutDir=.\Debug
ProjDir=.
TargetName=wed
InputPath=.\hlp\wed.hpj

"$(OutDir)\$(TargetName).hlp"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"\
 $(USERDEP__WED_H)
	call "$(ProjDir)\makehelp.bat"

!ENDIF 

SOURCE=.\wed.rc
DEP_RSC_WED_R=\
	".\res\bitmap1.bmp"\
	".\res\bitmap3.bmp"\
	".\res\bitmap4.bmp"\
	".\res\icon1.ico"\
	".\res\icon2.ico"\
	".\res\Toolbar.bmp"\
	".\res\toolbar1.bmp"\
	".\res\wed.ico"\
	".\res\wed.rc2"\
	".\res\wedDoc.ico"\
	

"$(INTDIR)\wed.res" : $(SOURCE) $(DEP_RSC_WED_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\wedDoc.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_WEDDO=\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\wedDoc.obj" : $(SOURCE) $(DEP_CPP_WEDDO) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_WEDDO=\
	".\editor.h"\
	".\notepad.h"\
	".\sellist.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\wedDoc.obj"	"$(INTDIR)\wedDoc.sbr" : $(SOURCE) $(DEP_CPP_WEDDO)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 

SOURCE=.\wedView.cpp

!IF  "$(CFG)" == "wed - Win32 Release"

DEP_CPP_WEDVI=\
	".\BufferList.h"\
	".\coco.h"\
	".\editor.h"\
	".\FileInfo.h"\
	".\gotoline.h"\
	".\HoldHead.h"\
	".\MainFrm.h"\
	".\notepad.h"\
	".\Search.h"\
	".\sellist.h"\
	".\Setup.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\wedView.obj" : $(SOURCE) $(DEP_CPP_WEDVI) "$(INTDIR)"\
 "$(INTDIR)\wed.pch"


!ELSEIF  "$(CFG)" == "wed - Win32 Debug"

DEP_CPP_WEDVI=\
	".\BufferList.h"\
	".\coco.h"\
	".\editor.h"\
	".\FileInfo.h"\
	".\gotoline.h"\
	".\HoldHead.h"\
	".\MainFrm.h"\
	".\notepad.h"\
	".\Search.h"\
	".\sellist.h"\
	".\Setup.h"\
	".\srcsel.h"\
	".\StrList.h"\
	".\wed.h"\
	".\wedDoc.h"\
	".\wedView.h"\
	

"$(INTDIR)\wedView.obj"	"$(INTDIR)\wedView.sbr" : $(SOURCE) $(DEP_CPP_WEDVI)\
 "$(INTDIR)" "$(INTDIR)\wed.pch"


!ENDIF 


!ENDIF 

