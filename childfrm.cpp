// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "wed.h"
#include "MainFrm.h"
#include "StrList.h"
#include "wedDoc.h"
#include "wedView.h"
#include "AppTop.h"
#include "ChildFrm.h"
#include "misc.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CWnd *mdiclient;

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_ERASEBKGND()
	ON_WM_MDIACTIVATE()
	ON_WM_SIZE()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#if 0
CBrush Brush(0xffff);
HBRUSH br, bmb;
HCURSOR cu;
#endif

#ifdef _DEBUG
    static CMemoryState oldMemState, newMemState, diffMemState;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
#ifdef _DEBUG
    oldMemState.Checkpoint();
#endif

	initial = TRUE;


#if 0
	hi = AfxGetApp()->LoadStandardIcon(IDI_EXCLAMATION);
	br = Brush;
	cu = AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);

	//cwinapp
	HBITMAP hbmp =  LoadBitmap(AfxGetInstanceHandle(),
							MAKEINTRESOURCE(IDB_BITMAP9));

	bmb = CreatePatternBrush( hbmp);
	//P2N("Bitmap %d bmb = %d \r\n", hbmp, bmb);
#endif

}

CChildFrame::~CChildFrame()
{
#ifdef _DEBUG
    newMemState.Checkpoint();
    if( diffMemState.Difference( oldMemState, newMemState ) )
    	{
		//P2N("WedChlframe Memory leaked!\r\n");
        //TRACE( "Memory leaked!\n" );
    	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	//P2N("Creating new ChildFrame\r\n");
	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


#include "subclass.h"
extern SubClass m_sc;

BOOL CChildFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CMDIFrameWnd* pParentWnd, CCreateContext* pContext)
{
	//P2N("ChildFrame: create (Parent= %d)\r\n", pParentWnd);

#if 0
	// Subclass
	m_apptop.OldWndProc = (WNDPROC) SetWindowLong(
						pParentWnd->m_hWnd,
							GWL_WNDPROC,
								(LONG)*m_apptop.NewWndProc);
#endif

	return CMDIChildWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)

{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	//P2N("ChildFrame: activate %d\r\n", pActivateWnd);

	mdiclient = GetParent();

	//Repaint() ;
	if(initial)
		{
		initial = FALSE;
#if 0
		//P2N("Subclassing -- %d from %d\r\n",
		//				m_sc.GetDlgItem(IDC_EDIT1), mdiclient);

		//m_sc.GetDlgItem(IDC_EDIT1);
		//mdiclient->Detach();

		//m_sc.GetDlgItem(IDC_EDIT1)->
		//			SubclassWindow(mdiclient->m_hWnd);

		//P2N("Subclassing2 %d from %d\r\n",
		//				m_sc.GetDlgItem(IDC_EDIT1), mdiclient);
#endif
		}
	else
		{
		//if(pActivateWnd)
		//	{
		//	YieldToWin();
	   	//	((CWedView*)pActivateWnd)->SyncCaret();
		//	YieldToWin();
	    //	}
		}
	//Repaint() ;
}

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWnd::OnSize(nType, cx, cy);

	//P2N("Childframe OnSize %d %d\r\n", cx, cy);

	// if window active, set cursor
	//if(currentedit)
	//	{
		//YieldToWin();
		//((CWedView*)currentedit)->SyncCaret();
		//YieldToWin();
	//	}
	//Repaint() ;
}

void CChildFrame::Repaint()

{
	CRect rec;
	return;

#if 0
	CDC *pDC2 = GetParent()->GetDC();
	GetParent()->GetClientRect(rec);
	pDC2->FillRect(&rec, Brush.FromHandle(bmb));
	GetParent()->ReleaseDC(pDC2);
#endif

}

void CChildFrame::OnMove(int x, int y)
{
	CMDIChildWnd::OnMove(x, y);

	//P2N("Childframe OnMove %d %d\r\n", x, y);

	// if window active, set cursor
	if(currentedit)
		{
		//YieldToWin();
		//((CWedView*)currentedit)->SyncCaret();
		//YieldToWin();
		}
	//Repaint() ;
}

