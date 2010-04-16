
/* =====[ LogWin.cpp ]========================================== 
                                                                             
   Description:     The timedim project, implementation of the LogWin.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  8/30/2007  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// LogWin.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "LogWin.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLogWin

CLogWin::CLogWin()

{	
	maxlines = DEFAULT_MAX_LINES;

	magic = LOGWIN_MAGIC;
	in_timer = 0;
	prevnl = false;
	bgcolor = RGB(245, 245, 245);
	firstpaint = true;
}

CLogWin::~CLogWin()

{
//	P2N("Logwind destructor called\r\n");
}

BEGIN_MESSAGE_MAP(CLogWin, CWnd)
	//{{AFX_MSG_MAP(CLogWin)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_VSCROLL()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	ON_WM_MOUSEACTIVATE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogWin message handlers

void CLogWin::AddString(const char *str)

{
	CString newstr(str);
	
	newstr.Replace("\t", "    ");

	//P2N("Addstring: '%s'\r\n", str);

	int hasnewline = false;
	if(newstr.Find("\r\n") >= 0 )
		{
		hasnewline = true;
		newstr.Replace("\r\n", " ");
		}
	if(prevnl)
		{
		// Add to end
		strlist.AddTail(newstr);
		}
	else
		{
		// Append to current last
		if(!strlist.IsEmpty())
			{
			strlist.GetTail() += newstr;
			}
		else
			{
			strlist.AddTail(newstr);
			}
		}

	prevnl = hasnewline;

	//P2N("Added new str %p %s\r\n", newstr, *newstr);

	int cnt		= strlist.GetCount();
	int slen	= newstr.GetLength();

	if(slen > widthcnt)
		{
		//P2N("Adjusted scroll range %d\r\n", slen);
		hs.EnableWindow();
		hs.SetScrollRange(0, slen);
		}

	// Pop first entry
	if(strlist.GetCount() > maxlines)
		{
		//P2N("Removed tail entry\r\n");
		strlist.RemoveHead();
		}

	// Set refresh timer
	if(!in_timer)
		{
		in_timer = true;
		SetTimer(1, 200, NULL);
		}

	if(cnt > heightcnt)
		{
		vs.EnableWindow();
		vs.SetScrollRange(0, cnt - 1);
		vs.SetScrollPos(cnt - (heightcnt - 2));
		}

	// Test to see animation
	//Sleep(20);
}

//////////////////////////////////////////////////////////////////////////

void CLogWin::Clear()

{
	//POSITION pos = strlist.GetHeadPosition();
	//while(pos)
	//	{
	//	CString &str = strlist.GetNext(pos);
	//	//P2N("In Clear() %s\r\n",  str);
	//	}

	strlist.RemoveAll();
	Invalidate(false);
}

//////////////////////////////////////////////////////////////////////////

void CLogWin::OnPaint() 

{
	CPaintDC dc(this); // device context for painting
	
	if(firstpaint)
		{
		firstpaint = false;
		FirstPaint();
		}

	int vscroll = vs.GetScrollPos();

	RECT rc; GetClientRect(&rc);
	
	//dc.SetBoundsRect(&rc, DCB_ACCUMULATE);
	dc.SetBkColor(bgcolor);
	//dc.SetBkMode(TRANSPARENT);
	
	CFont* oldFont = dc.SelectObject(&ff);

	int start = 0;
	// Walk back on 
	POSITION pos = strlist.GetHeadPosition();
	while(pos)
		{
		if(start++ == vscroll)
			break;
	
		strlist.GetNext(pos);
		}

	// Catch at the end
	if(pos <= NULL)
		{
		//P2N("Caught begin boundary error\r\n");
		pos = strlist.GetTailPosition();
		}	

	int xx = 0, yy = 0;
	int scroll  = hs.GetScrollPos();

	int hh = rc.bottom - rc.top;
	
	RECT rc2; GetClientRect(&rc2);
	rc2.bottom -= sh; rc2.right -= sw;

	while(pos)
		{
		CString &str = strlist.GetNext(pos);

		int scr = min(scroll, str.GetLength() );
		
		CString str2 = str.Mid(scr);
		str2 += fill;
		
		//dc.TabbedTextOut (xx, yy, str2, 0, NULL, 0);
		dc.ExtTextOut(xx, yy, ETO_CLIPPED, &rc2, str2, NULL);

		yy += txtss.cy;

		// Stop painting if past bottom
		if(yy >= hh)
			break;
		}

	// Fill in the rest of the page with blanks
	if(yy < hh)
		{
		while(yy < hh)
			{
			//dc.TabbedTextOut (xx, yy, fill, 0, NULL, 0);
			dc.ExtTextOut(xx, yy, ETO_CLIPPED, &rc2, fill, NULL);
			yy += txtss.cy;
			}
		}

	dc.SelectObject(oldFont);
}

//////////////////////////////////////////////////////////////////////////

//DEL void CLogWin::OnDestroy() 
//DEL 
//DEL {
//DEL 	CWnd::OnDestroy();
//DEL 	
//DEL 	//P2N("CLogWin::Destroying\r\n");	
//DEL 
//DEL #if 0
//DEL 	while(true)
//DEL 		{
//DEL 		if(strlist.GetCount() == 0)
//DEL 			break;
//DEL 
//DEL 		CString &str = strlist.RemoveHead();
//DEL 
//DEL 		P2N("String is: %s\r\n", str);
//DEL 		//delete &str;
//DEL 		}
//DEL #endif
//DEL 
//DEL 
//DEL #if 0
//DEL 	//P2N("Called destructor\r\n");
//DEL 
//DEL 	POSITION pos = strlist.GetHeadPosition();
//DEL 	while(true)
//DEL 		{
//DEL 		if(!pos)
//DEL 			break;
//DEL 
//DEL 		CString &str = strlist.GetNext(pos);
//DEL 		P2N("In destructor %s\r\n",  str);
//DEL 		//delete str;
//DEL 		}
//DEL #endif
//DEL 
//DEL }

void CLogWin::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 

{
	//P2N("CLogWin::Hor Scroll code=%d pos=%d  bar=%p %d\r\n", nSBCode, nPos, pScrollBar, hs.GetScrollPos());	

	switch(nSBCode)
		{
		case SB_LINELEFT   :
			hs.SetScrollPos(hs.GetScrollPos()-1);
			Invalidate(false);
			break;

		case SB_LINERIGHT   :
			hs.SetScrollPos(hs.GetScrollPos()+1);
			Invalidate(false);
			break;

		case SB_PAGELEFT    :
			hs.SetScrollPos(hs.GetScrollPos()-10);
			Invalidate(false);
			break;

		case SB_PAGERIGHT:
			hs.SetScrollPos(hs.GetScrollPos()+10);
			Invalidate(false);
			break;

		case SB_THUMBPOSITION      :
			hs.SetScrollPos(nPos);
			Invalidate(false);
			break;

		case SB_THUMBTRACK      :
			hs.SetScrollPos(nPos);
			Invalidate(false);
			break;
		}
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

//////////////////////////////////////////////////////////////////////////

BOOL CLogWin::PreTranslateMessage(MSG* pMsg) 

{

#if 1
	//////////////////////////////////////////////////////////////////////
	// Dispatch messages ourselvs
	if(pMsg->message == WM_CHAR)
		{	
		// Pass chars onto parent
		if(pMsg->wParam == 27 || pMsg->wParam == 9)
			{
			//P2N("CLogWin::PreTranslateMessage  WM_CHAR ESC\r\n");
			return false;
			}
		else
			{
			OnChar(pMsg->wParam, LOWORD(pMsg->lParam), pMsg->lParam); 
			return true;
			}
		}

	if(pMsg->message == WM_KEYDOWN )
		{
		// Pass chars onto parent
		if(pMsg->wParam  == 27 || pMsg->wParam == 9)
			{
			//P2N("CLogWin::PreTranslateMessage  WM_KEYDOWN ESC\r\n");
			return false;
			}
		else
			{
			OnKeyDown(pMsg->wParam, LOWORD(pMsg->lParam), pMsg->lParam); 
			return true;
			}
		}
	if(pMsg->message == WM_KEYUP)
		{
		OnKeyUp(pMsg->wParam, LOWORD(pMsg->lParam), pMsg->lParam); 
		return true;
		}

	if(pMsg->message == WM_SYSCHAR)
		{
		//OnSysChar(pMsg->wParam, LOWORD(pMsg->lParam), pMsg->lParam); 
		return 0;
		}
	if(pMsg->message == WM_SYSKEYDOWN)
		{
		//OnSysKeyDown(pMsg->wParam, LOWORD(pMsg->lParam), pMsg->lParam); 
		return 0;
		}
	if(pMsg->message == WM_SYSKEYUP)
		{
		//OnSysKeyUp(pMsg->wParam, LOWORD(pMsg->lParam), pMsg->lParam); 
		return 0;
		}
#endif

	//P2N("CLogWin::Pretranslage %d %s\r\n", pMsg->message, mxpad.num2msg(pMsg->message));
	return CWnd::PreTranslateMessage(pMsg);
}

void CLogWin::OnLButtonDown(UINT nFlags, CPoint point) 

{
	//P2N("CLogWin::OnLButtonDown\r\n");
	ScanAction(point);
	CWnd::OnLButtonDown(nFlags, point);
}

void CLogWin::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 

{
	//P2N("CLogWin::OnChar() chh=%c\r\n", nChar);

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CLogWin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 

{
	//P2N("CLogWin::OnVScroll size=%d %d \r\n", strlist.GetCount(), vs.GetScrollPos());

	switch(nSBCode)
		{
		case SB_LINEDOWN   :
			vs.SetScrollPos(vs.GetScrollPos()+1);
			Invalidate(false);
			break;

		case SB_LINEUP   :
			vs.SetScrollPos(vs.GetScrollPos()-1);
			Invalidate(false);
			break;

		case SB_PAGEDOWN    :
			vs.SetScrollPos(vs.GetScrollPos()+10);
			Invalidate(false);
			break;

		case SB_PAGEUP :
			vs.SetScrollPos(vs.GetScrollPos()-10);
			Invalidate(false);
			break;

		case SB_THUMBPOSITION      :
			vs.SetScrollPos(nPos);
			Invalidate(false);
			break;

		case SB_THUMBTRACK      :
			vs.SetScrollPos(nPos);
			Invalidate(false);
			break;
		}
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CLogWin::OnRButtonDown(UINT nFlags, CPoint point) 
{
	//P2N("OnRButtonDown() \r\n");
	CWnd::OnRButtonDown(nFlags, point);
} 


void CLogWin::OnTimer(UINT nIDEvent) 

{		
	if(nIDEvent == 1)
		{
		KillTimer(nIDEvent);
		in_timer = false;
		Invalidate(false);
		}

	//ASSERT(IsWindow(AfxGetApp()->m_pMainWnd->m_hWnd));
	//ShowWindow(true);
	
	CWnd::OnTimer(nIDEvent);
}

BOOL CLogWin::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 

{
	//P2N("CLogWin::OnMouseWheel \r\n");

	if(zDelta > 0)
		vs.SetScrollPos(vs.GetScrollPos() - 10);
	else
		vs.SetScrollPos(vs.GetScrollPos() + 10);

	Invalidate(false);

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CLogWin::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 

{
	//P2N("CLogWin::OnKeyDown() %c\r\n", nChar);

	switch(nChar)
		{
		case VK_PRIOR: 
			vs.SetScrollPos(vs.GetScrollPos()-(heightcnt - 4));
			Invalidate(false);
			break;

		case VK_NEXT: 
			vs.SetScrollPos(vs.GetScrollPos()+(heightcnt - 4));
			Invalidate(false);
			break;

		case VK_UP: 
			vs.SetScrollPos(vs.GetScrollPos()-1);
			Invalidate(false);
			break;

		case VK_DOWN: 
			vs.SetScrollPos(vs.GetScrollPos()+1);
			Invalidate(false);
			break;

		case VK_HOME: 
			vs.SetScrollPos(0);
			Invalidate(false);
			break;

		case VK_END: 
			vs.SetScrollPos(32000);
			Invalidate(false);
			break;
		}
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CLogWin::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 

{
	//P2N("CLogWin::OnSysKeyDown() %d\r\n", nChar);
	
	CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}


int CLogWin::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 

{
	//P2N("CLogWin::OnMouseActivate\r\n");
	SetFocus();
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

//////////////////////////////////////////////////////////////////////////

BOOL CLogWin::OnEraseBkgnd(CDC* pDC) 
{
	RECT	rc;	GetClientRect(&rc);

	//P2N("CLogWin::Erase Dialog\r\n");
	pDC->FillSolidRect(&rc, bgcolor);

	return 1;
	//return CWnd::OnEraseBkgnd(pDC);
}

void CLogWin::OnMouseMove(UINT nFlags, CPoint point) 

{
	//P2N("CLogWin::OnMouseMove(x=%d y=%d)\r\n", point.x, point.y);	
	CWnd::OnMouseMove(nFlags, point);
}

void CLogWin::FirstPaint()

{
	ModifyStyle(WS_DISABLED | WS_BORDER, WS_CLIPSIBLINGS | SS_NOTIFY , SWP_DRAWFRAME);
	
	//P2N("CLogWin::Paint firstpaint\r\n");

	sw = GetSystemMetrics(SM_CXVSCROLL);
	sh = GetSystemMetrics(SM_CYHSCROLL);

	RECT rc; GetClientRect(&rc);
	rc.left = rc.right - sw; rc.bottom -= sw;

	vs.Create(SBS_VERT, rc, this, 1000);
	vs.EnableWindow(false);
	vs.SetScrollRange(0,0);
	vs.ShowWindow(true);

	GetClientRect(&rc);
	rc.top = rc.bottom - sh; rc.right -= sh;
	
	hs.Create(SBS_HORZ, rc, this, 1001);
	hs.EnableWindow(false);
	hs.SetScrollRange(0,0);
	hs.ShowWindow(true);

	// Fill in prototype CSize
	CClientDC  dc(this); 
	CFont* oldFont = dc.SelectObject(&ff);
	txtss = dc.GetTextExtent("a");
	dc.SelectObject(oldFont);
	
	GetClientRect(&rc);
	heightcnt = max((rc.bottom - rc.top) / txtss.cy, 0);
	widthcnt  = max((rc.right - rc.left) / txtss.cx, 0);

	for(int loop = 0; loop < widthcnt; loop++)
		fill += " ";

	//P2N("heightcnt=%d\r\n", heightcnt);	
	//P2N("widthcnt=%d\r\n", widthcnt);
}

void CLogWin::OnLButtonDblClk(UINT nFlags, CPoint point) 

{
	ScanAction(point);
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CLogWin::ScanAction(CPoint point)

{
	CString str, num;

	lastoffset = (point.y / txtss.cy) +	vs.GetScrollPos();

	// Is it a valid hit?
	if(lastoffset > strlist.GetCount()-1 || lastoffset < 0)
		return;

	laststr = strlist.GetAt(strlist.FindIndex(lastoffset));

	//P2N("CLogWin::OnLButtonDblClk %s\r\n", str);	

	GetParent()->PostMessage(WM_LOGDBL, 
			(DWORD)((const char *)laststr), (DWORD)this);
}
