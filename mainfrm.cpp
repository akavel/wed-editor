// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "wed.h"
#include "MainFrm.h"
#include "notepad.h"
#include "StrList.h"
#include "wedDoc.h"
#include "wedView.h"
#include "misc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define AUTOSAVETICKS 90			  // 3 to a second

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	ON_COMMAND(ID_VIEW_TOOLBAR2, OnViewToolbar2)
	ON_COMMAND(Opensource, OnOpensource)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_MULTIOPEN, OnFileMultiopen)
	ON_WM_SETFOCUS()
	ON_WM_ENTERIDLE()
	ON_WM_DROPFILES()
	ON_COMMAND(ID_HELP_REGISTRATION, OnHelpRegistration)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,         // status line indicator

	ID_INDICATOR_CLOCK,
	ID_INDICATOR_FS,
	ID_INDICATOR_CLOCK2,
	ID_INDICATOR_CLOCK3,

	ID_INDICATOR_HOLD,
	ID_INDICATOR_MACRO,
	ID_INDICATOR_REC,

	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

#ifdef _DEBUG
    static CMemoryState oldMemState, newMemState, diffMemState;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
#ifdef _DEBUG
    oldMemState.Checkpoint();
#endif

}

CMainFrame::~CMainFrame()
{
#ifdef _DEBUG
    newMemState.Checkpoint();
    if( diffMemState.Difference( oldMemState, newMemState ) )
    	{
		//PrintToNotepad("Mainfrm Memory leaked!\r\n");
		//TRACE("Mainframe Diff dump\n");
		//diffMemState.DumpAllObjectsSince();
        TRACE( "Memory leaked!\n" );
    	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)

{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    if(!SetTimer(1, 333, NULL))
		{
		AfxMessageBox("Cannot create timer, autosave will not be available");
		}

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
		{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
		}

	if (!m_wndToolBar1.Create(this) ||
		!m_wndToolBar1.LoadToolBar(IDR_TOOLBAR1))
		{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
		}

	// Hide initally
	OnViewToolbar2();

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
		{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
		}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	//  be dockable
	EnableDocking(CBRS_ALIGN_ANY);

	// ------
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// ------
	m_wndToolBar1.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar1);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)

{
	HICON hi = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	HBRUSH br =		(HBRUSH)GetStockObject(DKGRAY_BRUSH);
	HCURSOR cu = AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);
	//PrintToNotepad("icon %d brush %d cursor: %d \r\n", hi, br, cu);

	const char *str = AfxRegisterWndClass( 0, cu, br, hi);
	//PrintToNotepad("Class = %s \r\n", str);

	//  the CREATESTRUCT cs
	cs.lpszClass = str;
	cs.style |= WS_HSCROLL ;
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::SetPosIndicator()
{
	m_wndStatusBar.SetPaneText(2,"0:1");
	//m_wndStatusBar.SetPaneStyle(1,SBPS_NORMAL);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CMDIFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	DragAcceptFiles();

	//HBRUSH brush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//int ret =  SetClassLong(m_hWnd, GCL_HBRBACKGROUND, (long)brush);
	//PrintToNotepad("brush: %d setclass: %d\r\n",
	//		brush, ret);
	//SetPosIndicator();
}

static baron = 0;
void CMainFrame::OnViewToolbar2()
{
	ShowControlBar(&m_wndToolBar1, baron, 0);
	baron = !baron;

	//RECT rect;
	//CMainFrame::GetWindowRect(&rect);

	//CMainFrame::SetWindowPos( 0,
	//	rect.left, rect.top, rect.right - rect.left,
	//			rect.bottom- rect.top + 1,
	//			SWP_NOZORDER   | SWP_NOREPOSITION   );
	//
    //	CMainFrame::SetWindowPos( 0,
    //		rect.left, rect.top, rect.right - rect.left,
    //				rect.bottom- rect.top - 1,
    //				SWP_NOZORDER   | SWP_NOREPOSITION   );

}
	   ///cwnd


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	return CMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}

void CMainFrame::OnOpensource()
{
	OpenSource(srcdir);
}

//////////////////////////////////////////////////////////////////////
// Timer tick 3 per second

void CMainFrame::OnTimer(UINT nIDEvent)
{
    static int count;
    CString dstr, tstr;

    time_t osBinaryTime;         // C run-time time (defined in <time.h>)
    time( &osBinaryTime ) ;      // Get the current time from the ...
    CTime time3( osBinaryTime ); // operating system.

    tstr.Format("%02d:%02d:%02d",
            (int)time3.GetHour(),
                (int)time3.GetMinute(),
                    (int)time3.GetSecond());

    ((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndStatusBar
                        .SetPaneText(3, tstr);

    dstr.Format("%02d/%02d/%02d",
            (int)time3.GetMonth(),
                (int)time3.GetDay(),
                    (int)time3.GetYear());

    ((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndStatusBar
                        .SetPaneText(4, dstr);

    if(timer_in) 
		timer_in--;

    if(timer_in == 1) 
		message("Idle");

	// Handle autosave
	lastkeypress++;

	if(lastkeypress == AUTOSAVETICKS)
		message("Autosave within 2 seconds ...");

	if(lastkeypress ==  AUTOSAVETICKS + 6)
		AutoSave();

	CMDIFrameWnd::OnTimer(nIDEvent);
}


// Autosave from here

void CMainFrame::AutoSave()

{
    // Tell all documents to autosave
    POSITION Pos = ((CWedApp*)AfxGetApp())->
					pDocTemplate->GetFirstDocPosition();
    for(;;)
        {
        if(!Pos)
            break;

        CWedDoc* doc = (CWedDoc*)
            ((CWedApp*)AfxGetApp())->pDocTemplate->GetNextDoc(Pos);

		if(!doc)
			continue;

		ASSERT_VALID(doc);
		if(doc->IsModified())
			{
			PrintToNotepad("Autosave %s\r\n", doc->GetPathName());
			doc->AutoSave();
			}
        }
}

void CMainFrame::OnFileMultiopen()
{
	OpenSource(targdir);
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	CMDIFrameWnd::OnSetFocus(pOldWnd);
}

void CMainFrame::OnEnterIdle(UINT nWhy, CWnd* pWho)
{
	CMDIFrameWnd::OnEnterIdle(nWhy, pWho);
}


LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)

{
	return CMDIFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{
	CMDIFrameWnd::OnDropFiles(hDropInfo);
}

#include "register.h"

void CMainFrame::OnHelpRegistration() 
{
	Register rr;
	rr.DoModal();	
}

void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	P2N("Char on mainframe\r\n");
	CMDIFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (CMDIFrameWnd::OnCreateClient(lpcs, pContext))
		{
		// Subclass the MDIClient to print the logo in the
		// bottom right corner....See CLogoMdi in logomdi.cpp

        m_LogoMdiClientWnd.SubclassWindow(m_hWndMDIClient) ;
        return TRUE ;
		}
	else
		{
        return FALSE ;
		}
	return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnFileSaveAs() 
{
	//AfxMessageBox("Onsave");
}
