// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "Page2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Page2 dialog


Page2::Page2() : 	CPropertyPage(Page2::IDD)
{
	//{{AFX_DATA_INIT(Page2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Page2::Page2(LPCTSTR  str)	: 	CPropertyPage(Page2::IDD)


{
	//{{AFX_DATA_INIT(Page1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	CPropertyPage::CPropertyPage(str);
}




Page2::~Page2()
{
}


void Page2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page2, CPropertyPage)
	//{{AFX_MSG_MAP(Page2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page2 message handlers
