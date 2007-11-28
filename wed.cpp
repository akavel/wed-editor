/////////////////////////////////////////////////////////////////////////////
// wed.cpp : Main application file
//

#include "stdafx.h"
#include "AFXRES.H"

#include <io.h>
#include <direct.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include "wed.h"
#include "StrList.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "wedDoc.h"
#include "wedView.h"
#include "splash.h"
#include "editor.h"
#include "wedview.h"
#include "notepad.h"
#include "build.h"
#include "about.h"
#include "misc.h"

#include "direct.h"
#include "afxtempl.h"
#include "subclass.h"

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

Splash spp;
CBitmap caret;

CFont	ff;
LOGFONT fflf;

CFont	pp;
LOGFONT pplf;

CString strHash          = "Hash";
CString strSection       = "Files";
CString strStringItem    = "File";
CString strIntItem       = "Count";
CString strConfig        = "Config";

CString strLastUsage     = "LastUsage";
CString strUsage     	 = "Usage";

/////////////////////////////////////////////////////////////////////////////
// Font

CString strFontName	     = "Font";
CString strFontSize	     = "FontSize";
CString strFontWeight	 = "FontWeight";
CString strFontItalic	 = "FontItalic";

/////////////////////////////////////////////////////////////////////////////
// Color

CString strColorFg		 =	"ColorFg";
CString strColorBg		 =	"ColorBg";
CString strColorSel		 =	"ColorSel";
CString strColorCSel  	 =	"ColorCSel";
CString strColorAdd  	 =	"ColorAdd";
CString strColorDel  	 =	"ColorDel";
CString strColorChg  	 =	"ColorChg";
CString strColorComm  	 =	"ColorComm";
CString strColorSrc  	 =	"ColorSrc";
CString strColorLong  	 =	"ColorLong";
CString strBackWrap		=	"BackWrap";
CString strTab2Space	=   "Tab2Space";
CString strTabStop		=   "TabStop";

COLORREF fgcol	= 0x000000;
COLORREF bgcol	= 0xffffff;

COLORREF selcol = 0x808080;
COLORREF cselcol= 0xff0000;

COLORREF cadd   = 0xff0000;
COLORREF cdel   = 0x0000ff;
COLORREF cchg   = 0x00ff00;

COLORREF comm   = 0x008000;
COLORREF prepro = 0x800000;
COLORREF keywor = 0x800000;
COLORREF srcc   = 0x008080;
COLORREF clng   = 0x000020;

int 		use = 0;

CWnd		*currentedit;
int			wantcaret;
char		approot[MAX_PATH];
CString		dataroot;

CStringList combofill;

int		splashed = FALSE;
int 	comline  = FALSE;
int 	lastkeypress = 0;
int		wait_exit = 0;
Search 	srcdlg;

// The one and only CWedApp object

CWedApp		theApp;

/////////////////////////////////////////////////////////////////////////////
// CWedApp

BEGIN_MESSAGE_MAP(CWedApp, CWinApp)
	//{{AFX_MSG_MAP(CWedApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

CMainFrame* pMainFrame;

/////////////////////////////////////////////////////////////////////////////
// Declare the variables needed

#ifdef _DEBUG
    CMemoryState oldMemState, newMemState, diffMemState;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWedApp construction

CWedApp::CWedApp()
{
	#ifdef _DEBUG
    oldMemState.Checkpoint();
	currentedit = NULL;
	wantcaret = FALSE;
	#endif
}

/////////////////////////////////////////////////////////////////////////////

CWedApp::~CWedApp()

{
	#ifdef _DEBUG
    newMemState.Checkpoint();
    if( diffMemState.Difference( oldMemState, newMemState ) )
    	{
		//PrintToNotepad("Memory leaked!\r\n");
        //TRACE( "Memory leaked!\n" );
    	}
	#endif
}

/////////////////////////////////////////////////////////////////////////////
// CWedApp initialization

HCURSOR WaitCursor;
HCURSOR NormalCursor;

SubClass m_sc;

CWnd	*mdiclient;

/////////////////////////////////////////////////////////////////////////////
// BOOL CWedApp::InitInstance()

BOOL 	CWedApp::InitInstance()

{
	CString str;
	char *ptr;

	//SetDialogBkColor(0x00ff0000, 0xffffff);

	WaitCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	NormalCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);

	GetModuleFileName(AfxGetInstanceHandle(), approot, MAX_PATH);

	CTime ct = CTime::GetCurrentTime();
	CString datestr = ct.Format("%A, %B %d, %Y - %I:%M %p");

	PrintToNotepad("\r\nStarted WED application at %s\r\n", datestr);
	//PrintToNotepad("AppRoot=%s\r\n", approot);

	//CString desktop;
	//GetSpecialFolder(CSIDL_DESKTOPDIRECTORY, desktop);
	//desktop += "wed";

	//P2N("Desktop special: %s\r\n", desktop);

	// Create initial desktop xcpt folder
	//if(access(desktop, 0) == -1)
	//	{
	//	P2N("Making %s\r\n", desktop);
	//	//message("Created desktop folder.");
	//	_mkdir(desktop);
	//	}

	ptr = strrchr(approot, '\\');
	if(ptr)
		*(ptr+1) = '\0';

	//dataroot = (CString)approot + "wed\\";

	GetSpecialFolder(CSIDL_PERSONAL, dataroot);
	dataroot += "WedData\\";
	
	P2N("Wed user home directory: %s\r\n", dataroot);

	if(access(dataroot, 0))
		{
		if(mkdir(dataroot))
			{
			//PrintToNotepad("Cannot create data root dir\r\n");
			}
		}

	//////////////////////////////////////////////////////////////////////
	// Create data dirs

	str = dataroot; str += "data";

	// Check if data dir is in order
	if(access(str, 0))
		{
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create data dir\r\n");
			}
		}
	str = dataroot; str += "macros";
	// Check if data dir is in order
	if(access(str, 0))
		{
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create macro dir\r\n");
			}
		}
	str = dataroot; str += "holdings";
	// Check if data dir is in order
	if(access(str, 0))
		{
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create holders dir\r\n");
			}
		}
	str = dataroot; str += "coco";
	// Check if coco dir is in order
	if(access(str, 0))
		{
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create coco dir\r\n");
			}
		}
	str = dataroot; str += "backup";
	// Check if state dir is in order
	if(access(str, 0))
		{
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create state dir\r\n");
			}
		}
	str = dataroot; str += "template";
	// Check if state dir is in order
	if(access(str, 0))
		{
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create template dir\r\n");
			}
		}

	//PrintToNotepad("Started Application: %s %s\r\n",
	//		m_pszAppName, approot);

	getcwd(str.GetBuffer(MAX_PATH), MAX_PATH);
	str.ReleaseBuffer();

	//PrintToNotepad("Initial dir: %s\r\n", str);

	if (!AfxSocketInit())
		{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
		}

	// Initialize OLE 2.0 libraries
	if (!AfxOleInit())
		{
		AfxMessageBox("Failed OLE library init, OLE functions will not be available");
		}
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.

	SetRegistryKey(_T("RobotMonkeySoftware"));

	LoadStdProfileSettings(6);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	pDocTemplate = new CMultiDocTemplate(
			IDR_WEDTYPE,
				RUNTIME_CLASS(CWedDoc),
					RUNTIME_CLASS(CChildFrame), // custom MDI child frame
						RUNTIME_CLASS(CWedView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	pMainFrame = new CMainFrame;

	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	// Global
	m_pMainWnd = pMainFrame;

	// Get resources we need:
	// 1. Fonts

	CString fontname = 	GetProfileString(strConfig, strFontName, "Courier");
	int size    =  		GetProfileInt(strConfig,  strFontSize, 10);
	int weight  =  		GetProfileInt(strConfig, strFontWeight, 0);
	int italic  =  		GetProfileInt(strConfig, strFontItalic, 0);

	if(!ff.CreateFont(size, 0, 0, 0, weight, italic, 0, 0,
				0, 0, 0, 0, FIXED_PITCH, fontname))
		{
		AfxMessageBox("Cannot set font");
		}
	if(!ff.GetLogFont(&fflf))
		{
		AfxMessageBox("Cannot get font parameters");
		}

	// 2. Printer fonts
	if(!pp.CreateFont(80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                FF_MODERN, "system"))
		{
		MessageBox(NULL, "Cannot set font", "Wed", 0);
		}
	if(!pp.GetLogFont(&pplf))
		{
		MessageBox(NULL, "Cannot get font parameters", "Wed", 0);
		}

	// Get colors
	bgcol 	=  GetProfileInt(strConfig,  strColorBg, 	bgcol);
	fgcol 	=  GetProfileInt(strConfig,  strColorFg, 	fgcol);
	selcol 	=  GetProfileInt(strConfig,  strColorSel , 	selcol );
    cselcol =  GetProfileInt(strConfig,  strColorCSel, 	cselcol);
    cadd    =  GetProfileInt(strConfig,  strColorAdd , 	cadd   );
    cdel    =  GetProfileInt(strConfig,  strColorDel , 	cdel   );
    cchg    =  GetProfileInt(strConfig,  strColorChg , 	cchg   );
    comm    =  GetProfileInt(strConfig,  strColorComm, 	comm   );
    srcc    =  GetProfileInt(strConfig,  strColorSrc , 	srcc   );
    clng    =  GetProfileInt(strConfig,  strColorLong, 	clng   );

	// Bimaps
	caret.LoadBitmap(IDB_BITMAP1);
    backwrap  =  GetProfileInt(strConfig,  strBackWrap , 0);
    Tab2Space =  GetProfileInt(strConfig,  strTab2Space, 0);
    tabstop   =  GetProfileInt(strConfig,  strTabStop, 4);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if(cmdInfo.m_strFileName != "")
		{
		comline = TRUE;
		OpenDocumentFile(cmdInfo.m_strFileName);
		}
	else
		{
   		// DON'T display a new MDI child window during startup!!!
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
		}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Key settings

	// Figure out last usage time ...
	int last = GetProfileInt(strConfig, "strLastUsage", 0);
	use = GetProfileInt(strConfig, "strUsage", 	0);
	//PrintToNotepad("Usage count %d \r\n", use);

	// First time ever, display initial file
	if(!use)
		{
		OpenDocumentFile("Welcome.txt");
		comline  = TRUE;
		if(currentedit)
			{
			}
		}

	use++;
	CTime tt = CTime::GetCurrentTime();
	CTimeSpan t(tt.GetTime() - (time_t)last);

	//PrintToNotepad("Time diff of last fire %d -- %d \r\n",
	//	t.GetTotalSeconds(), (int)tt.GetTime());

	// Show sign banner only if more then 60 seconds passed
	//if(t.GetTotalSeconds() > 60)
		{
		spp.Create(IDD_DIALOG5, NULL);

		RECT rect; 	AfxGetMainWnd()->GetClientRect(&rect);
		AfxGetMainWnd()->ClientToScreen(&rect);
		RECT rect2; spp.GetClientRect(&rect2);

		int posx = rect.left + (rect.right - rect.left)/2 -
					(rect2.right - rect2.left)/2;
		int posy = rect.top + (rect.bottom  - rect.top)/2 -
			(rect2.bottom - rect2.top)/2;
		spp.SetWindowPos( NULL, posx, posy, 0, 0,
					SWP_NOOWNERZORDER | SWP_NOSIZE );

 		//spp.SetFocus();
 		spp.ShowWindow(SW_SHOW);
		splashed = TRUE;
		}
	YieldToWin() ;

	//if(GetKeyState(VK_SHIFT))
	//	{
	//	AfxMessageBox("SHIFT HELD on startup\r\n");
	//	return(TRUE);
	//	}

	// The main window has been initialized ...
	// Show and update it.
	m_nCmdShow = GetProfileInt(strConfig, "WindowState", 1);
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	int num = GetProfileInt(strSection, strIntItem, 0);

	// De-serialize hash map
	CMap < int, int&, CString, CString& > HashMap;
	CFile cf;
	CString fname;
	fname.Format("%s%s", dataroot, "macros\\hashes.000");
	if( cf.Open( fname, CFile::modeRead))
		{
		CArchive ar( &cf, CArchive::load);
		HashMap.Serialize(ar);
		}
	else
		{
		//PrintToNotepad("Cannot open hash map file: %s\r\n", fname);
		}
	POSITION rpos;
	rpos = HashMap.GetStartPosition();
	while(rpos)
		{
		int key;
		CString val;
		HashMap.GetNextAssoc(rpos, key, val);
		//PrintToNotepad("In Hashlist: %x %s\r\n", key, val);
		}

	if(!comline)
		{
		// Reopen old documents:
		CString buf2, file;
		for(int count1 = 1; count1 <= num; count1++)
			{
			CWedDoc *doc = NULL;
			buf2.Format("%d", count1);
			file = GetProfileString(strSection, strStringItem + buf2);
			//PrintToNotepad("Reloading file: '%s' at %s\r\n", file, buf2);

			// Empty file, no action
			if(file == "")
				continue;

			doc = (CWedDoc*)OpenDocumentFile(file);

			if(YieldToWinEx())
				break;

			//PrintToNotepad("After Reloading file: %s at %s\r\n", file, buf2);

			if(doc)
				{
				ASSERT_VALID(doc);

				// Document had an error
				if(doc->ssel.m_err)
					break;

				int lrow, lcol;

				lrow = GetProfileInt(strSection,
					strStringItem + buf2 + "row", 0);

				lcol = GetProfileInt(strSection,
					strStringItem + buf2 + "col", 0);

				// Update cursor positions ...
				POSITION pos = doc->GetFirstViewPosition();
				for(;;)
					{
					if(!pos)
						break;
					CWedView *cv = (CWedView*)doc->GetNextView(pos);
					if(cv)
						{
						ASSERT_VALID(cv);
						cv->row = lrow;  cv->col = lcol;
						cv->SyncCaret();
						YieldToWin() ;
						}
					}
				// This happens after load, set it again
				doc->UpdateAllViews(NULL);
				}
			}
	// Try figure out last current directory
	int idx;
	if( (idx = file.ReverseFind('\\')) != -1)
		{
		file = file.Left(idx);
		}
	//PrintToNotepad("Chdir: %s\r\n", file);
	_chdir(file);
    }
	message ("Loading macros");
	LoadMacros();

	message ("Loading holdings");
	LoadHoldings();

	message("");
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// BOOL CWedApp::LoadMacros()

BOOL 	CWedApp::LoadMacros()
{
	int loop;
	// Save numbered macros
	for(loop=0; loop < 10; loop++)
	   {
		CFile cf;
		CString fname;
		fname.Format("%s%s%03d", dataroot, "macros\\macro.", loop);
		if(cf.Open( fname, CFile::modeRead))
			{
			CArchive ar( &cf, CArchive::load);
			macros[loop].Serialize(ar);;
			}
		else
			{
			//PrintToNotepad("Cannot open macro file: %s\r\n", fname);
			}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// BOOL CWedApp::SaveMacros()

BOOL 	CWedApp::SaveMacros()

{
	int loop;

	// Save numbered macros
	for(loop=0; loop < 10; loop++)
	   {
		// Do not save empty macro
		if(macros[loop].IsEmpty())
			continue;

		CFile cf;  CString fname;
		fname.Format("%s%s%03d", dataroot, "macros\\macro.", loop);

		if( cf.Open( fname, CFile::modeCreate | CFile::modeWrite ))
			{
			CArchive ar( &cf, CArchive::store);
			macros[loop].Serialize(ar);
			}
		else
			{
			//PrintToNotepad("Cannot create macro file: %s\r\n", fname);
			}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// BOOL CWedApp::SaveHoldings()

BOOL 	CWedApp::SaveHoldings()

{
	int loop;
	// Save numbered macros
	for(loop=0; loop < 10; loop++)
	   {
		// Do not save empty macro
		if(holding[loop].IsEmpty())
			continue;

		CFile cf;  CString fname;
		fname.Format("%s%s%03d",  dataroot, "holdings\\holding.", loop);

		if( cf.Open( fname, CFile::modeCreate | CFile::modeWrite ))
			{
			CArchive ar( &cf, CArchive::store);
			holding[loop].Serialize(ar);;
			}
		else
			{
			//PrintToNotepad("Cannot create macro file: %s\r\n", fname);
			}
		}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// BOOL CWedApp::LoadHoldings()

BOOL 	CWedApp::LoadHoldings()

{
	int loop;
	// Save numbered macros
	for(loop=0; loop < 10; loop++)
	   {
		CFile cf;  CString fname;
		fname.Format("%s%s%03d",  dataroot, "holdings\\holding.", loop);

		if( cf.Open( fname, CFile::modeRead))
			{
			CArchive ar( &cf, CArchive::load);
			holding[loop].Serialize(ar);;
			}
		else
			{
			//PrintToNotepad("Cannot open holding file: %s\r\n", fname);
			}
		}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// void CWedApp::OnAppAbout()
// App command to run the dialog

void 	CWedApp::OnAppAbout()
{
	CAboutDlg aboutDlg;

// Declare the variables needed
#ifdef _DEBUG
    static CMemoryState oldMemState3, newMemState3, diffMemState3;
#endif


#ifdef _DEBUG
    oldMemState3.Checkpoint();
#endif

	aboutDlg.DoModal();

#ifdef _DEBUG
    newMemState3.Checkpoint();
    if( diffMemState3.Difference( oldMemState3, newMemState3 ) )
    {
		oldMemState3.DumpAllObjectsSince();
		//PrintToNotepad("CDialog Memory leaked!\r\n");
        //TRACE( "CDialog Memory leaked!\n" );
    }
#endif

}

/////////////////////////////////////////////////////////////////////////////
// void CWedApp::OpenFile()
// CWedApp commands

void 	CWedApp::OpenFile()
{
	OnFileOpen();
}

/////////////////////////////////////////////////////////////////////////////
// void CWedApp::NewFile()

void 	CWedApp::NewFile()
{
	OnFileNew();
}

/////////////////////////////////////////////////////////////////////////////
// int CWedApp::ExitInstance()

int 	CWedApp::ExitInstance()
{
#if 0
	if(!RemoveFontResource("sample.fnt"))
		MessageBox(NULL, "Cannot remove font", "Wed", 0);
#endif

	//PrintToNotepad("Terminated Application: %s %s\r\n",
	//				m_pszAppName, approot);

	//if(wait_exit)
	//	{
	//	for(int loop = 0; loop < 10; loop++)
	//		{
	//		YieldToWin(); Sleep(20);
	//		}
	//	}

 	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// BOOL CWedApp::SaveAllModified()

BOOL 	CWedApp::SaveAllModified()

{
	// Save reopen information:
	CString	buf;
	CPtrList il;
	int		row, col;

    // Save list of buffers
	if(!comline)
    	{
		int count = 0;
		POSITION Pos = pDocTemplate->GetFirstDocPosition();
		// Make a list, current edited buffer as last
		for(;;)
			{
			if(!Pos)
				break;
			CWedDoc* doc = (CWedDoc*)pDocTemplate->GetNextDoc(Pos);
			POSITION pos = doc->GetFirstViewPosition();
			CView *cv = doc->GetNextView(pos); 	ASSERT_VALID(cv);
			if(cv != currentedit)
				il.AddTail(cv);
			}

	if(currentedit)
		il.AddTail(currentedit);

	POSITION pos = il.GetHeadPosition();
	for(;;)
		{
		if(!pos)
			break;
		CView *cv = (CView*)il.GetNext(pos);
		if(!cv)
			break;
		ASSERT_VALID(cv);

		CWedDoc* doc = (CWedDoc*)cv->GetDocument();
		if(!doc)
			break;
		ASSERT_VALID(doc);

		CString fline =doc->strlist.GetLine(0);

		// If it is a new doc
 		if(doc->strlist.GetCount() == 1 &&
			fline.GetLength() == 0)
			{
			//PrintToNotepad("New doc: %d\r\n",  doc);
			}
		else
			{
			CString file = doc->GetPathName();
			row = ((CWedView*)cv)->row; col = ((CWedView*)cv)->col;
			buf.Format("%d", count + 1);

			WriteProfileString(strSection,  strStringItem + buf, file);
			WriteProfileInt(strSection,  strStringItem + buf + "row", row);
			WriteProfileInt(strSection,  strStringItem + buf + "col", col);
			count++;
			}
		}
	WriteProfileInt(strSection, strIntItem, count);
	}

	// Serialize holdings
	message ("Saving holdings");
	SaveHoldings();

	// Serialize macros
	message ("Saving macros");
	SaveMacros();

	// Save config information:
	CTime t = CTime::GetCurrentTime();
	WriteProfileInt(strConfig, "strLastUsage", (int)t.GetTime());
	WriteProfileInt(strConfig, "strUsage", use);

	// Save main frame window placement
	WINDOWPLACEMENT wp;
	pMainFrame->GetWindowPlacement(&wp);
	WriteProfileInt(strConfig, "WindowState",  wp.showCmd);
	// Save file informaion

	// Save current window focus:

	// Save font info
    LOGFONT lf; ff.GetObject(sizeof(LOGFONT), &lf);
	WriteProfileString(strConfig,  strFontName, lf.lfFaceName);
	WriteProfileInt(strConfig,  strFontSize, lf.lfHeight);
	WriteProfileInt(strConfig,  strFontWeight, lf.lfWeight);
	WriteProfileInt(strConfig,  strFontItalic, lf.lfItalic);

	// Save color info
	WriteProfileInt(strConfig,  strColorBg, 	bgcol);
	WriteProfileInt(strConfig,  strColorFg, 	fgcol);
	WriteProfileInt(strConfig,  strColorSel , 	selcol );
    WriteProfileInt(strConfig,  strColorCSel, 	cselcol);
    WriteProfileInt(strConfig,  strColorAdd , 	cadd   );
    WriteProfileInt(strConfig,  strColorDel , 	cdel   );
    WriteProfileInt(strConfig,  strColorChg , 	cchg   );
    WriteProfileInt(strConfig,  strColorComm, 	comm   );
    WriteProfileInt(strConfig,  strColorSrc , 	srcc   );
    WriteProfileInt(strConfig,  strColorLong , 	clng   );

	// Save backwrap
	WriteProfileInt(strConfig,  strBackWrap , backwrap);

	// Save tab2space
	WriteProfileInt(strConfig,  strTab2Space, Tab2Space);

	// Save tabstop
	WriteProfileInt(strConfig,  strTabStop, tabstop);




	return CWinApp::SaveAllModified();
}

/////////////////////////////////////////////////////////////////////////////
// int CWedApp::Run()

int 	CWedApp::Run()
{
	if(splashed)
		{
		for(int loop=0; loop < 100;loop++)
			{
			Sleep(20); 	YieldToWin();
			}
		spp.DestroyWindow();
		}
	return CWinApp::Run();
}


/////////////////////////////////////////////////////////////////////////////

void 	CWedApp::WinHelp(DWORD dwData, UINT nCmd)
{
	static int help_in;


	if(help_in)
		return;

	help_in = TRUE;
	message("Opening Help");

	HINSTANCE hi =
		ShellExecute(
		AfxGetMainWnd()->m_hWnd,
		"open",
		"wed.html",
		"",
		approot,
		SW_SHOW);

	if((long)hi <= 32)
		{
		CString num;
		num.Format("Cannot show help. %s", err2str((long)hi));
		AfxMessageBox(num);
		}

	help_in = FALSE;

	// Do not call
	//CWinApp::WinHelp(dwData, nCmd);
}

/////////////////////////////////////////////////////////////////////////////
// Translate error code to string

char 	*CWedApp::err2str(long err)

{
	char *str = "none";
	switch(err)
		{
		case 0 :
			str =  "The operating system is out of memory or resources. ";
			break;

		case ERROR_FILE_NOT_FOUND :
			str =  "The specified file was not found. ";
			break;

		case ERROR_PATH_NOT_FOUND :
			str =  "The specified path was not found. ";
			break;

		case ERROR_BAD_FORMAT :
			str =  "The .EXE file is invalid (non-Win32 .EXE or error in .EXE image). ";
			break;

		case SE_ERR_ACCESSDENIED :
			str =  "The operating system denied access to the specified file. ";
			break;

		case SE_ERR_ASSOCINCOMPLETE :
			str =  "The filename association is incomplete or invalid. ";
			break;

		case SE_ERR_DDEBUSY :
			str =  "The DDE transaction could not be completed (busy) ";
			break;

		case SE_ERR_DDEFAIL :
			str =  "The DDE transaction failed. ";
			break;

		case SE_ERR_DDETIMEOUT :
			str =  "The DDE transaction could not be completed. (timeout) ";
			break;

		case SE_ERR_DLLNOTFOUND :
			str =  "The specified dynamic-link library was not found. ";
			break;

		case SE_ERR_NOASSOC :
			str =  "There is no application associated with the given filename extension. ";
			break;

		case SE_ERR_OOM :
			str =  "There was not enough memory to complete the operation. ";
			break;

		case SE_ERR_SHARE :
			str =  "A sharing violation occurred. ";
			break;
		}
 	return(str);
}


/////////////////////////////////////////////////////////////////////////////

int 	CWedApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
	//nType	&= ~MB_ICONEXCLAMATION ;
	nType	|= MB_ICONINFORMATION  ;

	return CWinApp::DoMessageBox(lpszPrompt, nType, nIDPrompt);
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CWedApp::ProcessWndProcException(CException* e, const MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	AfxMessageBox("Exception");

	return CWinApp::ProcessWndProcException(e, pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// Open document file

CDocument* CWedApp::OpenDocumentFile(LPCTSTR lpszFileName)

{
	CDocument* ret = NULL;
	ret = CWinApp::OpenDocumentFile(lpszFileName);

	if(!ret)
		return ret;

	// See if window creation failed
	if( ((CWedDoc*)ret)->ssel.m_err)
		{
		//Close this one
		pDocTemplate->RemoveDocument(ret);

		//Close some more
		POSITION pos = pDocTemplate->GetFirstDocPosition();

		pDocTemplate->RemoveDocument(pDocTemplate->GetNextDoc(pos));
		pDocTemplate->RemoveDocument(pDocTemplate->GetNextDoc(pos));
		pDocTemplate->RemoveDocument(pDocTemplate->GetNextDoc(pos));

		AfxMessageBox("Windows ran out of windows", MB_ICONSTOP);
		ret = NULL;
		}

	// Maximize it
	// Open up in demonstration/full screen mode:
	POSITION pos = ret->GetFirstViewPosition();
	CView *pView = ret->GetNextView(pos);
	if (pView)
		{
		pView->GetParent()->ShowWindow(SW_SHOWMAXIMIZED);
		ret->UpdateAllViews(NULL);
		}

	return ret;
}

// EOF

