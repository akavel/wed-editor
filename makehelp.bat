@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by WED.HPJ. >"hlp\wed.hm"
echo. >>"hlp\wed.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\wed.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\wed.hm"
echo. >>"hlp\wed.hm"
echo // Prompts (IDP_*) >>"hlp\wed.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\wed.hm"
echo. >>"hlp\wed.hm"
echo // Resources (IDR_*) >>"hlp\wed.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\wed.hm"
echo. >>"hlp\wed.hm"
echo // Dialogs (IDD_*) >>"hlp\wed.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\wed.hm"
echo. >>"hlp\wed.hm"
echo // Frame Controls (IDW_*) >>"hlp\wed.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\wed.hm"
REM -- Make help for Project WED


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\wed.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\wed.hlp" goto :Error
if not exist "hlp\wed.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\wed.hlp" Debug
if exist Debug\nul copy "hlp\wed.cnt" Debug
if exist Release\nul copy "hlp\wed.hlp" Release
if exist Release\nul copy "hlp\wed.cnt" Release
echo.
goto :done

:Error
echo hlp\wed.hpj(1) : error: Problem encountered creating help file

:done
echo.
