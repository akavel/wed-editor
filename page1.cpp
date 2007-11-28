// page1.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "page1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Page1 property page

IMPLEMENT_DYNCREATE(Page1, CPropertyPage)

Page1::Page1() : CPropertyPage(Page1::IDD)
{
	//{{AFX_DATA_INIT(Page1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Page1::Page1(LPCTSTR  str) : CPropertyPage(Page1::IDD)


{
	//{{AFX_DATA_INIT(Page1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	CPropertyPage::CPropertyPage(str);
}


Page1::~Page1()
{
}

void Page1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page1, CPropertyPage)
	//{{AFX_MSG_MAP(Page1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page1 message handlers

