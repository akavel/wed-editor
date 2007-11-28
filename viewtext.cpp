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
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ViewText message handlers
