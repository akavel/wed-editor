;///////////////////////////////////////////////////////////////////////////
;//

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;Name and file

  Name "WED Windows Editor"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\WeD"

  BrandingText " Wed Windows Editor "

  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\WeD" ""

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "License.txt"

  ;insertmacro MUI_PAGE_COMPONENTS

  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

    !insertmacro MUI_LANGUAGE "English"

    icon WeD.ico
    uninstallicon WeD.ico

    OutFile ".\bin\setup.exe"

; -------------------------------------------------------------------------
;Installer Sections

section "Install"

    #!error "exit"

    SetShellVarContext all

    SetOutPath "$INSTDIR"

    ; Add your own files here...
    File  /oname=WeD.exe ..\release\wed.exe
    ;File  /oname=logo.jpg ${BANNER}

    ; Copy OEM FILE to target
    ;File /oname=${XBANNER} oem.txt

    File  Readme.txt
    File  License.txt
    File  Welcome.txt
    File  Spell.txt
    File  Spell.idx
    File  wed.html

    SetOutPath "$SYSDIR"

    SetOverwrite off
    File  /nonfatal MFC42D.DLL
    File  /nonfatal MSVCRTD.DLL
    SetOverwrite on

    ; ---------------------------------------------------------------------
    SetOutPath $INSTDIR

    CreateDirectory "$SMPROGRAMS\Wed Windows Editor"
    CreateShortCut "$SMPROGRAMS\Wed Windows Editor\WED.lnk" "$INSTDIR\WeD.exe" "" \
                    "$INSTDIR\WeD.exe" 0  SW_SHOWNORMAL  "ALT|CONTROL|W"

    CreateShortCut "$SMPROGRAMS\Wed Windows Editor\Readme.lnk" "$INSTDIR\Readme.txt"

    CreateShortCut "$QUICKLAUNCH\Wed Windows Editor.lnk" "$INSTDIR\WeD.exe"
    CreateShortCut "$SENDTO\Wed Windows Editor.lnk" "$INSTDIR\WeD.exe"

    ;CreateShortCut "$SMPROGRAMS\WeD\WeD Web Site.lnk" "http:\\www.WeD.com" "" \
    ;                "" 0  SW_SHOWNORMAL  "ALT|CONTROL|W"

    CreateDirectory "$SMPROGRAMS\Wed Windows Editor\Tools"
    CreateShortCut "$SMPROGRAMS\Wed Windows Editor\Tools\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
    CreateShortCut "$SMPROGRAMS\Wed Windows Editor\Tools\License.lnk" "$INSTDIR\License.txt"
    CreateShortCut "$DESKTOP\Wed Windows Editor.lnk" "$INSTDIR\WeD.exe"

    ;Store installation folder
    WriteRegStr HKCU "Software\WeD" "" $INSTDIR

    ; ---------------------------------------------------------------------
    ;Register WeD file as .WeD handler

    ;WriteRegStr HKCR ".WeD" "" "WeD.FileHandler"
    ;WriteRegStr HKCR "WeD.FileHandler" "" ""
    ;WriteRegStr HKCR "WeD.FileHandler\shell" "" "open"
    ;WriteRegStr HKCR "WeD.FileHandler\DefaultIcon" "" "$INSTDIR\WeD.exe,0"
    ;WriteRegStr HKCR "WeD.FileHandler\shell\open\command" "" '$INSTDIR\WeD.exe "%1"'
    ;WriteRegStr HKCR "WeD.FileHandler\shell\edit" "" ""
    ;WriteRegStr HKCR "WeD.FileHandler\shell\edit\command" "" '$INSTDIR\WeD.exe "%1"'

    ;Create uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

    ; Create control panel unistaller
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WeD"  "DisplayName" "Wed Windows Editor"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WeD"  "UninstallString" $INSTDIR\Uninstall.exe
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WeD"  "DisplayIcon" $INSTDIR\WeD.exe,0"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WeD"  "DisplayVersion" "Version 1.0"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WeD"  "HelpLink" "http://www.WeD.com"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WeD"  "NoModify" 1
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WeD"  "NoRepair" 1

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

    SetShellVarContext all

    ;ADD YOUR OWN FILES HERE...

    Delete "$INSTDIR\Uninstall.exe"
    Delete "$INSTDIR\WeD.exe"

    RMDir /r "$INSTDIR"

    Delete "$SMPROGRAMS\Wed Windows Editor\WeD.lnk"
    Delete "$SMPROGRAMS\Wed Windows Editor\Readme.lnk"
    Delete "$SMPROGRAMS\Wed Windows Editor\License.lnk"


    Delete "$QUICKLAUNCH\Wed Windows Editor.lnk"
    Delete "$DESKTOP\Wed Windows Editor.lnk"
    Delete "$SENDTO\Wed Windows Editor.lnk"

    RMDir /r "$SMPROGRAMS\Wed Windows Editor\Tools\"
    RMDir /r "$SMPROGRAMS\Wed Windows Editor\"

    DeleteRegKey HKCU "Software\Wed Windows Editor"
    DeleteRegKey HKCR ".WeD"
    DeleteRegKey HKCR "WeD.FileHandler"
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\WeD"

SectionEnd



