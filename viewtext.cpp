// ViewText.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "ViewText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ViewText dialog


ViewText::ViewText(CWnd* pParent /*=NULL*/)
	: CDialog(ViewText::IDD, pParent)
{
	//{{AFX_DATA_INIT(ViewText)
	m_str = _T("");
	//}}AFX_DATA_INIT
}


void ViewText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ViewText)
	DDX_Text(pDX, IDC_EDIT1, m_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ViewText, CDialog)
	//{{AFX_MSG_MAP(ViewText)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ViewText message handlers

void ViewText::OnSize(UINT nType, int cx, int cy) 

{
	CDialog::OnSize(nType, cx, cy);
	
	CEdit  *ed = (CEdit*)GetDlgItem(IDC_EDIT1);
	if(!ed)
		return;

	if(!IsWindow(ed->m_hWnd))
		return;

	RECT rc; GetClientRect(&rc);
	ed->SetWindowPos(NULL, 0, 0, rc.right, rc.bottom, SWP_NOZORDER | SWP_NOMOVE);
	
}

BOOL ViewText::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ViewText::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	CEdit  *ed = (CEdit*)GetDlgItem(IDC_EDIT1);	
	ed->SetSel(-1, -1);
}
