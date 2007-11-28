/////////////////////////////////////////////////////////////////////////////
// Splash.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "StrList.h"
#include "wedDoc.h"
#include "wedView.h"
#include "editor.h"
#include "Splash.h"
#include "Notepad.h"

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Splash dialog

Splash::Splash(CWnd* pParent /*=NULL*/)
	: CDialog(Splash::IDD, pParent)
{
	//{{AFX_DATA_INIT(Splash)
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////

void Splash::DoDataExchange(CDataExchange* pDX)

{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Splash)
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Splash, CDialog)
	//{{AFX_MSG_MAP(Splash)
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Splash message handlers

LRESULT Splash::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)

{
	//P2N("Processed message %s\r\n", num2msg(message));
	return CDialog::WindowProc(message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////

void Splash::OnLButtonDown(UINT nFlags, CPoint point)

{
	//P2N("Splash Mouse\r\n");
	DestroyWindow();
	CDialog::OnLButtonDown(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////

void Splash::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)

{
	P2N("Splash char\r\n");
	DestroyWindow();
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////

BOOL Splash::OnInitDialog()

{
	CDialog::OnInitDialog();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

void Splash::OnShowWindow(BOOL bShow, UINT nStatus)

{
	CDialog::OnShowWindow(bShow, nStatus);
	m_edit1.SetWindowText(GetRegStr());
	// TODO: Add your message handler code here
}
