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
#include "mxpad.h"

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

	splashed = false;
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Splash message handlers

/////////////////////////////////////////////////////////////////////////////

void Splash::OnLButtonDown(UINT nFlags, CPoint point)

{
	P2N("Splash::OnLButtonDown\r\n");
	Hide();
	CDialog::OnLButtonDown(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////

//DEL void Splash::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//DEL
//DEL {
//DEL 	P2N("Splash::OnChar\r\n");
//DEL 	Hide();
//DEL 	CDialog::OnChar(nChar, nRepCnt, nFlags);
//DEL }

/////////////////////////////////////////////////////////////////////////////

BOOL Splash::OnInitDialog()

{
	BOOL ret = CDialog::OnInitDialog();

	//P2N("Splash::OnInitDialog\r\n");

	m_edit1.SetWindowText(GetRegStr());

	RECT rect; 	AfxGetMainWnd()->GetClientRect(&rect);

	//P2N("Main rect top=%d left=%d right=%d bottom=%d\r\n",
	//			rect.top, rect.left, rect.right, rect.bottom);

	AfxGetMainWnd()->ClientToScreen(&rect);

	RECT rect2; GetClientRect(&rect2);

	int posx = rect.left + (rect.right - rect.left)/2 -
				(rect2.right - rect2.left)/2;

	int posy = rect.top + (rect.bottom  - rect.top)/2 -
		(rect2.bottom - rect2.top)/2;

	SetWindowPos( NULL, posx, posy, 0, 0,
				SWP_NOOWNERZORDER | SWP_NOSIZE );
	return ret;
}

/////////////////////////////////////////////////////////////////////////////

//DEL void Splash::OnChangeEdit1()
//DEL {
//DEL 	// send this notification unless you override the CDialog::OnInitDialog()
//DEL 	// function and call CRichEditCtrl().SetEventMask()
//DEL 	// with the ENM_CHANGE flag ORed into the mask.
//DEL
//DEL 	// TODO: Add your control notification handler code here
//DEL }

//DEL BOOL Splash::PreTranslateMessage(MSG* pMsg)
//DEL
//DEL {
//DEL 	//P2N("Splash::PreTranslateMessage\r\n");
//DEL
//DEL 		switch(pMsg->message)
//DEL 			{
//DEL 			case WM_CHAR:
//DEL 				OnChar(pMsg->wParam, pMsg->lParam & 0xff, pMsg->lParam);
//DEL 				return true;
//DEL 			break;
//DEL
//DEL 			case WM_KEYDOWN:
//DEL 				OnKeyDown(pMsg->wParam, pMsg->lParam & 0xff, pMsg->lParam);
//DEL 				break;
//DEL
//DEL 			default:
//DEL 				// None
//DEL 			break;
//DEL 			}
//DEL 	return CDialog::PreTranslateMessage(pMsg);
//DEL }

void Splash::Hide()

{
	if(::IsWindow(m_hWnd))
		if(splashed)
			{
			ShowWindow(SW_HIDE);
			splashed = false;
			}
}

void Splash::Show()

{
	if(!splashed)
		{
		ShowWindow(SW_SHOW);
		splashed = true;
		SetFocus();
		}
}
