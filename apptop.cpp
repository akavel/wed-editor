// AppTop.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "AppTop.h"
#include "notepad.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AppTop

// attach

AppTop::AppTop()
{
}

AppTop::~AppTop()
{
}

BEGIN_MESSAGE_MAP(AppTop, CWnd)
	//{{AFX_MSG_MAP(AppTop)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// AppTop message handlers

BOOL AppTop::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void AppTop::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);

	//PrintToNotepad("Got focus on apptop.\r\n");
}

LRESULT AppTop::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	return CWnd::WindowProc(message, wParam, lParam);
}
