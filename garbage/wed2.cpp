// wed.cpp : Main application file
//                                

#include "stdafx.h"
#include "io.h"

#include "wed.h"

#include "StrList.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "wedDoc.h"
#include "wedView.h"
#include "splash.h"
#include "editor.h"

#include "notepad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Splash spp;
CBitmap caret;

CFont	ff;
LOGFONT fflf;

CFont	pp;
LOGFONT pplf;

int fgcol = 0;
int bgcol = 0xffffff;
int selcol = 0x808080;
int cselcol = 0xff0000;

CString strHash          = "Hash";
CString strSection       = "Files";
CString strConfig        = "Config";
CString strStringItem    = "File";
CString strIntItem       = "Count";  
CWnd	*currentedit;
char	approot[MAX_PATH];
CString		dataroot;

static	splashed = FALSE;
static	comline  = FALSE;

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
int	wait_exit = 0;   
Search srcdlg;    

/////////////////////////////////////////////////////////////////////////////
// CWedApp construction

CWedApp::CWedApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWedApp object

CWedApp		theApp;
CWedView	*mainview;

/////////////////////////////////////////////////////////////////////////////
// CWedApp initialization

#include "direct.h"
#include "afxtempl.h"

HCURSOR WaitCursor;
HCURSOR NormalCursor;


/////////////////////////////////////////////////////////////////////////////
// BOOL CWedApp::InitInstance()

BOOL CWedApp::InitInstance()
{						  
	CString str;
	char *ptr;

	WaitCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	NormalCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);

	GetModuleFileName(AfxGetInstanceHandle(),
		approot, MAX_PATH);

	ptr = strrchr(approot, '\\');
	if(ptr)	*(ptr+1) = '\0';
	
	dataroot = (CString)approot + "wed\\";

	if(access(dataroot, 0))
		{
		//PrintToNotepad("No data dir\r\n");
		if(mkdir(dataroot))
			{
			//PrintToNotepad("Cannot create data dir\r\n");
			}
		}
	str = dataroot; str += "data";
	// Check if data dir is in order
	if(access(str, 0))
		{
		//PrintToNotepad("No data dir\r\n");
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create data dir\r\n");
			}
		}
	str = dataroot; str += "macros";
	// Check if data dir is in order
	if(access(str, 0))
		{
		//PrintToNotepad("No macro dir\r\n");
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create macro dir\r\n");
			}
		}
	str = dataroot; str += "holdings";
	// Check if data dir is in order
	if(access(str, 0))
		{
		//PrintToNotepad("No holders dir\r\n");
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create holders dir\r\n");
			}
		}
	str = dataroot; str += "coco";
	// Check if coco dir is in order
	if(access(str, 0))
		{
		//PrintToNotepad("No coco dir\r\n");
		if(mkdir(str))
			{
			//PrintToNotepad("Cannot create holders dir\r\n");
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
		AfxMessageBox("IDP_OLE_INIT_FAILED");
		//return FALSE;
	}

	AfxEnableControlContainer();

	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("PeterGlen"));

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

	m_pMainWnd = pMainFrame;

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

	// Get resources we need:
	// 1. Enum fonts
#if 0
	if(!AddFontResource("sample.fnt"))
		MessageBox(NULL, "Cannot add font", "Wed", 0);
#endif

	if(!ff.CreateFont(0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, FIXED_PITCH, "system"))
		{
		MessageBox(NULL, "Cannot set font", "Wed", 0);
		}  

	if(!ff.GetLogFont(&fflf))
		MessageBox(NULL, "Cannot get font parameters", "Wed", 0);

	// logfont
	//PrintToNotepad("Font lfw = %d lfh = %d\r\n", 
	//				fflf.lfWidth, fflf.lfHeight);	

	// Get printer stuff
	if(!pp.CreateFont(80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                FF_MODERN, "system"))
		{
		//PrintToNotepad("Cannot set font\r\n");	
		MessageBox(NULL, "Cannot set font", "Wed", 0);
		} 
	if(!pp.GetLogFont(&pplf))
		MessageBox(NULL, "Cannot get font parameters", "Wed", 0);

	// 2. Enum bimaps
	caret.LoadBitmap(IDB_BITMAP1);

	// Figure out last usage time:
	int last = GetProfileInt(strConfig, "LastUsage", 0);
	CTime tt = CTime::GetCurrentTime();
	CTimeSpan t(tt.GetTime() - (time_t)last);

	//PrintToNotepad("Time diff of last fire %d -- %d \r\n",
	//	t.GetTotalSeconds(), (int)tt.GetTime());

	// Show only if more then 30 seconds pased
	if(t.GetTotalSeconds() > 30)
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

	CString strConfig        = "Config";
	CString strSection       = "Files";
	CString strStringItem    = "File";
    CString strIntItem       = "Count";  

	int num = GetProfileInt(strSection, strIntItem, 0);

	// De serialize hash map
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

		// Empty file, next ...
		
		if(file == "")
			continue;

		doc = (CWedDoc*)OpenDocumentFile(file);

		PrintToNotepad("After Reloading file: %s at %s\r\n", file, buf2);

		if(doc)
			{
			ASSERT_VALID(doc);
        	
			int lrow, lcol;
        	
			lrow = GetProfileInt(strSection,  
				strStringItem + buf2 + "row", 0);
        	
			lcol = GetProfileInt(strSection,  
				strStringItem + buf2 + "col", 0);
        	
			// Update cursor posions
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
					cv->sync_caret();
					YieldToWin() ;
					}
				}
			// This happens after load, set it again
			doc->UpdateAllViews(NULL);
			}
		}
	// Try figure out last current directory	
	int idx;
	if((idx = file.ReverseFind('\\')) != -1)
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
	
	//PrintToNotepad("Done reloading row/col\r\n");
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// BOOL CWedApp::LoadMacros()

BOOL CWedApp::LoadMacros()
{
	int loop;
	// Save numbered macros
	for(loop=0; loop < 10; loop++)
	   {
		CFile cf;
		CString fname;
		fname.Format("%s%s%03d", 
			dataroot, "macros\\macro.", loop);
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

BOOL CWedApp::SaveMacros()

{
	int loop;
			
	// Save numbered macros
	for(loop=0; loop < 10; loop++)
	   {
		// Do not save empty macro
		if(macros[loop].IsEmpty())
			continue;

		CFile cf;
		CString fname;
		fname.Format("%s%s%03d", 
			dataroot, "macros\\macro.", loop);

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

BOOL CWedApp::SaveHoldings()

{
	int loop;
	// Save numbered macros
	for(loop=0; loop < 10; loop++)
	   {
		// Do not save empty macro
		if(holding[loop].IsEmpty())
			continue;

		CFile cf;
		CString fname;
		fname.Format("%s%s%03d", 
			dataroot, "holdings\\holding.", loop);

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

BOOL CWedApp::LoadHoldings()

{
	int loop;
	// Save numbered macros
	for(loop=0; loop < 10; loop++)
	   {
		CFile cf;
		CString fname;
		fname.Format("%s%s%03d", 
			dataroot, "holdings\\holding.", loop);

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
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_build;
	CString	m_date;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_build = _T("");
	m_date = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_EDIT1, m_build);
	DDX_Text(pDX, IDC_EDIT2, m_date);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
/////////////////////////////////////////////////////////////////////////////
// void CWedApp::OnAppAbout()

void CWedApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CWedApp commands

// Put a message to the status bar:

int timer_in = 0;
void message(const char * str)

{	
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar
						.SetPaneText(0, str);
	timer_in = 8;
}


void rowcol(const char * str)

{	
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar
						.SetPaneText(1, str);
}

void hold(const char * str)

{	
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar
						.SetPaneText(4, str);
}


void mac(const char * str)

{	
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar
						.SetPaneText(5, str);
}



void mode(const char * str)

{	
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar
						.SetPaneText(6, str);
}

#define     ROTATE_LONG_LEFT(x, n)  (((x) << (n))  | ((x) >> (32 - (n))))
#define     ROTATE_LONG_RIGHT(x, n) (((x) >> (n))  | ((x) << (32 - (n))))

int	HashString(const char *name)

{
	unsigned int ret_val = 0;

    while(*name != '\0')
        {
        ret_val ^= (int)*name;
        ret_val  = ROTATE_LONG_RIGHT(ret_val, 3);          /* rotate right */
        *name++;
        }
    return((int)ret_val);
}

/////////////////////////////////////////////////////////////////////////////
// void CWedApp::OpenFile()

void CWedApp::OpenFile()
{
	OnFileOpen();
}

/////////////////////////////////////////////////////////////////////////////
// void CWedApp::NewFile()

void CWedApp::NewFile()
{
	OnFileNew();
}

/////////////////////////////////////////////////////////////////////////////
// int CWedApp::ExitInstance() 

int CWedApp::ExitInstance() 
{
#if 0
	if(!RemoveFontResource("sample.fnt"))
		MessageBox(NULL, "Cannot remove font", "Wed", 0);
#endif

	//PrintToNotepad("Terminated Application: %s %s\r\n", 
	//			m_pszAppName, approot);	

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

BOOL CWedApp::SaveAllModified() 

{
	// Save reopen information:
	CString	buf; 
	CPtrList il;
	int		row, col;

	if(!comline)
    {
    // Save list of buffers
	POSITION Pos = pDocTemplate->GetFirstDocPosition();
	int count = 0;

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
		CString file = doc->GetPathName();
		row = ((CWedView*)cv)->row; col = ((CWedView*)cv)->col;
		buf.Format("%d", count + 1);
		
		WriteProfileString(strSection,  strStringItem + buf, file);
		WriteProfileInt(strSection,  strStringItem + buf + "row", row);
		WriteProfileInt(strSection,  strStringItem + buf + "col", col);
		count++;
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
	WriteProfileInt(strConfig, "LastUsage", 
				(int)t.GetTime());

	// Save main frame window placement
	WINDOWPLACEMENT wp;
	pMainFrame->GetWindowPlacement(&wp);
	WriteProfileInt(strConfig, "WindowState",  wp.showCmd);
	// Save file informaion

	// Save current window focus:

	return CWinApp::SaveAllModified();
}

/////////////////////////////////////////////////////////////////////////////
// int CWedApp::Run() 

int CWedApp::Run() 
{
	if(splashed)
		{
		for(int loop=0; loop<100;loop++)
			{
			Sleep(20); 	YieldToWin();
			}
		spp.DestroyWindow();
		}
	return CWinApp::Run();
}


CMenu *GetTemplateMenu()
{
    int iPos;
    CMenu* pViewMenu = NULL;
    CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();

    for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
    {
        CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
        if (pMenu && pMenu->GetMenuItemID(0) == ID_VIEW_TOOLBAR)
        {
            pViewMenu = pMenu;
            break;
        }
    }
    ASSERT(pViewMenu != NULL);

    CMenu* pfMenu = NULL;
    for (iPos = pViewMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
    {
        pfMenu = pViewMenu->GetSubMenu(iPos);
        if(pfMenu)
            break;
    }
    ASSERT(pfMenu != NULL);
    return (pfMenu);
}

// Save all documents ...

void SaveAllDocs()

{
	CWedDoc*  pDoc = NULL;
    CMultiDocTemplate* pDocTemplate = 
				((CWedApp*)AfxGetApp())->pDocTemplate;
	POSITION Pos = 	pDocTemplate->GetFirstDocPosition();
	for(;;)
		{
		if(!Pos)
			break;
		CWedDoc* doc = (CWedDoc*)pDocTemplate->GetNextDoc(Pos);
		
		if(!doc)
			continue;

		ASSERT_VALID(doc);

		if(doc->IsModified())
			doc->OnSaveDocument(doc->GetPathName());
		}
}

#include "build.h"

char bnum[]  = CURRENTBUILD;
char bdate[] = CURRENTDATE;

BOOL CAboutDlg::OnInitDialog() 
{
	m_build = bnum;
	m_date = bdate;

	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

